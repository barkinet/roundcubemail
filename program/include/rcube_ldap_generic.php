<?php

/*
 +-----------------------------------------------------------------------+
 | program/include/rcube_ldap_generic.php                                |
 |                                                                       |
 | This file is part of the Roundcube Webmail client                     |
 | Copyright (C) 2006-2012, The Roundcube Dev Team                       |
 | Copyright (C) 2012, Kolab Systems AG                                  |
 |                                                                       |
 | Licensed under the GNU General Public License version 3 or            |
 | any later version with exceptions for skins & plugins.                |
 | See the README file for a full license statement.                     |
 |                                                                       |
 | PURPOSE:                                                              |
 |   Provide basic functionality for accessing LDAP directories          |
 |                                                                       |
 +-----------------------------------------------------------------------+
 | Author: Thomas Bruederli <roundcube@gmail.com>                        |
 |         Aleksander Machniak <machniak@kolabsys.com>                   |
 +-----------------------------------------------------------------------+
*/


/*
  LDAP connection properties
  --------------------------

  $prop = array(
      'host'          => '<ldap-server-address>',
      // or
      'hosts'         => array('directory.verisign.com'),
      'port'          => 389,
      'use_tls'	      => true|false,
      'ldap_version'  => 3,             // using LDAPv3
      'auth_method'   => '',            // SASL authentication method (for proxy auth), e.g. DIGEST-MD5
      'attributes'    => array('dn'),   // List of attributes to read from the server
      'vlv'           => false,         // Enable Virtual List View to more efficiently fetch paginated data (if server supports it)
      'vlv_sort'      => array('cn'),   // Sort attributes of the VLV index
      'numsub_filter' => '(objectClass=organizationalUnit)',   // with VLV, we also use numSubOrdinates to query the total number of records. Set this filter to get all numSubOrdinates attributes for counting
      'sizelimit'     => '0',           // Enables you to limit the count of entries fetched. Setting this to 0 means no limit.
      'timelimit'     => '0',           // Sets the number of seconds how long is spend on the search. Setting this to 0 means no limit.
      'referrals'     => true|false,    // Sets the LDAP_OPT_REFERRALS option. Mostly used in multi-domain Active Directory setups
  );
*/

/**
 * Model class to access an LDAP directories
 *
 * @package LDAP
 */
class rcube_ldap_generic
{
    const UPDATE_MOD_ADD = 1;
    const UPDATE_MOD_DELETE = 2;
    const UPDATE_MOD_REPLACE = 4;
    const UPDATE_MOD_FULL = 7;

    public $conn;
    public $vlv_active = false;

    /** private properties */
    protected $config = array();
    protected $attributes = array('dn');
    protected $entries = null;
    protected $result = null;
    protected $debug = false;
    protected $list_page = 1;
    protected $page_size = 10;


    /**
    * Object constructor
    *
    * @param array   $p       LDAP connection properties
    * @param boolean $debug   Enables debug mode
    */
    function __construct($p, $debug = false)
    {
        $this->config = $p;

        if (is_array($p['attributes']))
            $this->attributes = $p['attributes'];

        if (!is_array($p['hosts']) && !empty($p['host']))
            $this->config['hosts'] = array($p['host']);

        $this->debug = $debug;
    }

    /**
     * Activate/deactivate debug mode
     *
     * @param boolean $dbg True if LDAP commands should be logged
     */
    public function set_debug($dbg = true)
    {
        $this->debug = $dbg;
    }

    /**
     * Set connection options
     *
     * @param mixed $opt Option name as string or hash array with multiple options
     * @param mixed $val Option value
     */
    public function set_config($opt, $val = null)
    {
        if (is_array($opt))
            $this->config = array_merge($this->config, $opt);
        else
            $this->config[$opt] = $value;
    }


    /**
     * Set properties for VLV-based paging
     *
     * @param  number $page  Page number to list (starting at 1)
     * @param  number $size  Number of entries to display on one page
     */
    public function set_vlv_page($page, $size = 10)
    {
        $this->list_page = $page;
        $this->page_size = $size;
    }


    /**
    * Establish a connection to the LDAP server
    */
    public function connect()
    {
        if (!function_exists('ldap_connect')) {
            PEAR::raiseError("No ldap support in this installation of PHP", 100);
            return false;
        }

        if (is_resource($this->conn))
            return true;

        if (!is_array($this->config['hosts']))
            $this->config['hosts'] = array($this->config['hosts']);

        if (empty($this->config['ldap_version']))
            $this->config['ldap_version'] = 3;

        foreach ($this->config['hosts'] as $host) {
            $hostname = $host . ($this->config['port'] ? ':'.$this->config['port'] : '');

            $this->_debug("C: Connect [$hostname] [{$this->config['name']}]");

            if ($lc = @ldap_connect($host, $this->config['port']))
            {
                if ($this->config['use_tls'] === true)
                    if (!ldap_start_tls($lc))
                        continue;

                $this->_debug("S: OK");

                ldap_set_option($lc, LDAP_OPT_PROTOCOL_VERSION, $this->config['ldap_version']);
                $this->config['host'] = $host;
                $this->conn = $lc;

                if (isset($this->config['referrals']))
                    ldap_set_option($lc, LDAP_OPT_REFERRALS, $this->config['referrals']);
                break;
            }
            $this->_debug("S: NOT OK");
        }

        if (!is_resource($this->conn)) {
            PEAR::raiseError("Could not connect to any LDAP server, last tried $hostname", 100);
            return false;
        }

        return true;
    }


    /**
     * Bind connection with (SASL-) user and password
     *
     * @param string $authc Authentication user
     * @param string $pass  Bind password
     * @param string $authz Autorization user
     *
     * @return boolean True on success, False on error
     */
    public function sasl_bind($authc, $pass, $authz=null)
    {
        if (!$this->conn) {
            return false;
        }

        if (!function_exists('ldap_sasl_bind')) {
            PEAR::raiseError("Unable to bind: ldap_sasl_bind() not exists", 100);
            return false;
        }

        if (!empty($authz)) {
            $authz = 'u:' . $authz;
        }

        if (!empty($this->config['auth_method'])) {
            $method = $this->config['auth_method'];
        }
        else {
            $method = 'DIGEST-MD5';
        }

        $this->_debug("C: Bind [mech: $method, authc: $authc, authz: $authz] [pass: $pass]");

        if (ldap_sasl_bind($this->conn, NULL, $pass, $method, NULL, $authc, $authz)) {
            $this->_debug("S: OK");
            return true;
        }

        $this->_debug("S: ".ldap_error($this->conn));

        PEAR::raiseError("Bind failed for authcid=$authc ".ldap_error($this->conn), ldap_errno($this->conn));
        return false;
    }


    /**
     * Bind connection with DN and password
     *
     * @param string $dn   Bind DN
     * @param string $pass Bind password
     *
     * @return boolean True on success, False on error
     */
    public function bind($dn, $pass)
    {
        if (!$this->conn) {
            return false;
        }

        $this->_debug("C: Bind [dn: $dn] [pass: $pass]");

        if (@ldap_bind($this->conn, $dn, $pass)) {
            $this->_debug("S: OK");
            return true;
        }

        $this->_debug("S: ".ldap_error($this->conn));

        PEAR::raiseError("Bind failed for dn=$dn: ".ldap_error($this->conn), ldap_errno($this->conn));
        return false;
    }


    /**
     * Close connection to LDAP server
     */
    public function close()
    {
        if ($this->conn) {
            $this->_debug("C: Close");
            ldap_unbind($this->conn);
            $this->conn = null;
        }
    }


    /**
     * Return the last result set
     *
     * @return object rcube_ldap_result Result object
     */
    function get_result()
    {
        return $this->result;
    }


    /**
     * Get a specific LDAP entry, identified by its DN
     *
     * @param string $dn Record identifier
     * @return array     Hash array
     */
    function get_entry($dn)
    {
        $rec = null;

        if ($this->conn && $dn) {
            $this->_debug("C: Read [dn: $dn] [(objectclass=*)]");

            if ($ldap_result = @ldap_read($this->conn, $dn, '(objectclass=*)', $this->attributes)) {
                $this->_debug("S: OK");

                if ($entry = ldap_first_entry($this->conn, $ldap_result)) {
                    $rec = ldap_get_attributes($this->conn, $entry);
                }
            }
            else {
                $this->_debug("S: ".ldap_error($this->conn));
            }

            if (!empty($rec)) {
                $rec['dn'] = $dn; // Add in the dn for the entry.
            }
        }

        return $rec;
    }


    /**
     * Execute the LDAP search based on the stored credentials
     *
     * @param string $base_dn  The base DN to query
     * @param string $filter   The LDAP filter for search
     * @param string $scope    The LDAP scope (list|sub|base)
     * @param boolean $count_only  True if only the record count is requested
     * @param string  $vlv_search  The search string to be used for VLV-based searching
     *
     * @return mixed  rcube_ldap_result object or number of entries (if count_only=true) or false on error
     */
    public function search($base_dn, $filter = '', $scope = 'list', $count_only = false, $vlv_search = null)
    {
        if ($this->conn) {
            if (empty($filter))
                $filter = $filter = '(objectclass=*)';

            $this->_debug("C: Search [$filter][dn: $base_dn]");

            $function = self::scope2func($scope, $ns_function);

            // when using VLV, we get the total count by...
            if (!$count_only && $function != 'ldap_read' && $this->config['vlv']) {
                // ...either reading numSubOrdinates attribute
                if ($this->config['numsub_filter'] && ($result_count = @$ns_function($this->conn, $base_dn, $this->config['numsub_filter'], array('numSubOrdinates'), 0, 0, 0))) {
                    $counts = ldap_get_entries($this->conn, $result_count);
                    for ($vlv_count = $j = 0; $j < $counts['count']; $j++)
                        $vlv_count += $counts[$j]['numsubordinates'][0];
                    $this->_debug("D: total numsubordinates = " . $vlv_count);
                }
                else if (!function_exists('ldap_parse_virtuallist_control'))  // ...or by fetching all records dn and count them
                    $vlv_count = $this->search($base_dn, $filter, $scope, true);

                $this->vlv_active = $this->_vlv_set_controls($this->config, $this->list_page, $this->page_size, $vlv_search);
            }
            else
                $this->vlv_active = false;

            // only fetch dn for count (should keep the payload low)
            $attrs = $count_only ? array('dn') : $this->attributes;
            if ($ldap_result = $function($this->conn, $base_dn, $filter,
                $attrs, 0, (int)$this->config['sizelimit'], (int)$this->config['timelimit'])
            ) {
                // when running on a patched PHP we can use the extended functions to retrieve the total count from the LDAP search result
                if ($this->vlv_active && function_exists('ldap_parse_virtuallist_control')) {
                    if (ldap_parse_result($this->conn, $ldap_result, $errcode, $matcheddn, $errmsg, $referrals, $serverctrls)) {
                        ldap_parse_virtuallist_control($this->conn, $serverctrls, $last_offset, $vlv_count, $vresult);
                        $this->_debug("S: VLV result: last_offset=$last_offset; content_count=$vlv_count");
                    }
                    else {
                        $this->_debug("S: ".($errmsg ? $errmsg : ldap_error($this->conn)));
                    }
                }

                $this->result = new rcube_ldap_result($this->conn, $ldap_result, $base_dn, $filter, $vlv_count);

                return $count_only ? $this->result->count() : $this->result;
            }
            else {
                $this->_debug("S: ".ldap_error($this->conn));
            }
        }

        return false;
    }


    /**
     * Modify an LDAP entry on the server
     *
     * @param string $dn      Entry DN
     * @param array  $params  Hash array of entry attributes
     * @param int    $mode    Update mode (UPDATE_MOD_ADD | UPDATE_MOD_DELETE | UPDATE_MOD_REPLACE)
     */
    public function modify($dn, $parms, $mode = 255)
    {
        // TODO: implement this

        return false;
    }

    /**
     * Wrapper for ldap_add()
     *
     * @see ldap_add()
     */
    public function add($dn, $entry)
    {
        $this->_debug("C: Add [dn: $dn]: ".print_r($entry, true));

        $res = ldap_add($this->conn, $dn, $entry);
        if ($res === false) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_delete()
     *
     * @see ldap_delete()
     */
    public function delete($dn)
    {
        $this->_debug("C: Delete [dn: $dn]");

        $res = ldap_delete($this->conn, $dn);
        if ($res === false) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_mod_replace()
     *
     * @see ldap_mod_replace()
     */
    public function mod_replace($dn, $entry)
    {
        $this->_debug("C: Replace [dn: $dn]: ".print_r($entry, true));

        if (!ldap_mod_replace($this->conn, $dn, $entry)) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_mod_add()
     *
     * @see ldap_mod_add()
     */
    public function mod_add($dn, $entry)
    {
        $this->_debug("C: Add [dn: $dn]: ".print_r($entry, true));

        if (!ldap_mod_add($this->conn, $dn, $entry)) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_mod_del()
     *
     * @see ldap_mod_del()
     */
    public function mod_del($dn, $entry)
    {
        $this->_debug("C: Delete [dn: $dn]: ".print_r($entry, true));

        if (!ldap_mod_del($this->conn, $dn, $entry)) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_rename()
     *
     * @see ldap_rename()
     */
    public function rename($dn, $newrdn, $newparent = null, $deleteoldrdn = true)
    {
        $this->_debug("C: Rename [dn: $dn] [dn: $newrdn]");

        if (!ldap_rename($this->conn, $dn, $newrdn, $newparent, $deleteoldrdn)) {
            $this->_debug("S: ".ldap_error($this->conn));
            return false;
        }

        $this->_debug("S: OK");
        return true;
    }

    /**
     * Wrapper for ldap_list() + ldap_get_entries()
     *
     * @see ldap_list()
     * @see ldap_get_entries()
     */
    public function list_entries($dn, $filter, $attributes = array(''))
    {
        $list = array();
        $this->_debug("C: List [dn: $dn] [{$filter}]");

        if ($result = ldap_list($this->conn, $dn, $filter, $attributes)) {
            $list = ldap_get_entries($this->conn, $result);

            if ($list === false) {
                $this->_debug("S: ".ldap_error($this->conn));
                return array();
            }

            $count = $list['count'];
            unset($list['count']);

            $this->_debug("S: $count record(s)");
        }
        else {
            $this->_debug("S: ".ldap_error($this->conn));
        }

        return $list;
    }

    /**
     * Wrapper for ldap_read() + ldap_get_entries()
     *
     * @see ldap_read()
     * @see ldap_get_entries()
     */
    public function read_entries($dn, $filter, $attributes = null)
    {
        $this->_debug("C: Read [dn: $dn] [{$filter}]");

        if ($this->conn) {
            if (!$attributes)
                $attributes = $this->attributes;

            $result = ldap_read($dn, $filter, $attributes, 0, (int)$this->config['sizelimit'], (int)$this->config['timelimit']);
            if ($result === false) {
                $this->_debug("S: ".ldap_error($this->conn));
                return false;
            }

            $this->_debug("S: OK");
            return ldap_get_entries($this->conn, $result);
        }

        return false;
    }


    /**
     * Choose the right PHP function according to scope property
     *
     * @param string $scope         The LDAP scope (sub|base|list)
     * @param string $ns_function   Function to be used for numSubOrdinates queries
     * @return string  PHP function to be used to query directory
     */
    public static function scope2func($scope, &$ns_function = null)
    {
        switch ($scope) {
          case 'sub':
            $function = $ns_function  = 'ldap_search';
            break;
          case 'base':
            $function = $ns_function = 'ldap_read';
            break;
          default:
            $function = 'ldap_list';
            $ns_function = 'ldap_read';
            break;
        }

        return $function;
    }

    /**
     * Escapes the given value according to RFC 2254 so that it can be safely used in LDAP filters.
     *
     * @param string $val Value to quote
     * @return string The escaped value
     */
    public static function escape_value($val)
    {
        return strtr($str, array('*'=>'\2a', '('=>'\28', ')'=>'\29',
            '\\'=>'\5c', '/'=>'\2f'));
    }

    /**
     * Escapes a DN value according to RFC 2253
     *
     * @param string $dn DN value o quote
     * @return string The escaped value
     */
    public static function escape_dn($dn)
    {
        return strtr($str, array(','=>'\2c', '='=>'\3d', '+'=>'\2b',
            '<'=>'\3c', '>'=>'\3e', ';'=>'\3b', '\\'=>'\5c',
            '"'=>'\22', '#'=>'\23'));
    }

    /**
     * Turn an LDAP entry into a regular PHP array with attributes as keys.
     *
     * @param array $entry Attributes array as retrieved from ldap_get_attributes() or ldap_get_entries()
     * @return array       Hash array with attributes as keys
     */
    public static function normalize_entry($entry)
    {
        $rec = array();
        for ($i=0; $i < $entry['count']; $i++) {
            $attr = $entry[$i];
            for ($j=0; $j < $entry[$attr]['count']; $j++) {
                $rec[$attr][$j] = $entry[$attr][$j];
            }
        }

        return $rec;
    }

    /**
     * Set server controls for Virtual List View (paginated listing)
     */
    private function _vlv_set_controls($prop, $list_page, $page_size, $search = null)
    {
        $sort_ctrl = array('oid' => "1.2.840.113556.1.4.473",  'value' => self::_sort_ber_encode((array)$prop['sort']));
        $vlv_ctrl  = array('oid' => "2.16.840.1.113730.3.4.9", 'value' => self::_vlv_ber_encode(($offset = ($list_page-1) * $page_size + 1), $page_size, $search), 'iscritical' => true);

        $sort = (array)$prop['sort'];
        $this->_debug("C: set controls sort=" . join(' ', unpack('H'.(strlen($sort_ctrl['value'])*2), $sort_ctrl['value'])) . " ($sort[0]);"
            . " vlv=" . join(' ', (unpack('H'.(strlen($vlv_ctrl['value'])*2), $vlv_ctrl['value']))) . " ($offset/$page_size)");

        if (!ldap_set_option($this->conn, LDAP_OPT_SERVER_CONTROLS, array($sort_ctrl, $vlv_ctrl))) {
            $this->_debug("S: ".ldap_error($this->conn));
            $this->set_error(self::ERROR_SEARCH, 'vlvnotsupported');
            return false;
        }

        return true;
    }


    /**
     * Returns unified attribute name (resolving aliases)
     */
    private static function _attr_name($namev)
    {
        // list of known attribute aliases
        static $aliases = array(
            'gn' => 'givenname',
            'rfc822mailbox' => 'email',
            'userid' => 'uid',
            'emailaddress' => 'email',
            'pkcs9email' => 'email',
        );

        list($name, $limit) = explode(':', $namev, 2);
        $suffix = $limit ? ':'.$limit : '';

        return (isset($aliases[$name]) ? $aliases[$name] : $name) . $suffix;
    }


    /**
     * Prints debug info to the log
     */
    private function _debug($str)
    {
        if ($this->debug && class_exists('rcube')) {
            rcube::write_log('ldap', $str);
        }
    }


    /**
     * Quotes attribute value string
     *
     * @param string $str Attribute value
     * @param bool   $dn  True if the attribute is a DN
     *
     * @return string Quoted string
     */
    private static function _quote_string($str, $dn=false)
    {
        // take firt entry if array given
        if (is_array($str))
            $str = reset($str);

        if ($dn)
            $replace = array(','=>'\2c', '='=>'\3d', '+'=>'\2b', '<'=>'\3c',
                '>'=>'\3e', ';'=>'\3b', '\\'=>'\5c', '"'=>'\22', '#'=>'\23');
        else
            $replace = array('*'=>'\2a', '('=>'\28', ')'=>'\29', '\\'=>'\5c',
                '/'=>'\2f');

        return strtr($str, $replace);
    }


    /**
     * Generate BER encoded string for Virtual List View option
     *
     * @param integer List offset (first record)
     * @param integer Records per page
     * @return string BER encoded option value
     */
    private static function _vlv_ber_encode($offset, $rpp, $search = '')
    {
        # this string is ber-encoded, php will prefix this value with:
        # 04 (octet string) and 10 (length of 16 bytes)
        # the code behind this string is broken down as follows:
        # 30 = ber sequence with a length of 0e (14) bytes following
        # 02 = type integer (in two's complement form) with 2 bytes following (beforeCount): 01 00 (ie 0)
        # 02 = type integer (in two's complement form) with 2 bytes following (afterCount):  01 18 (ie 25-1=24)
        # a0 = type context-specific/constructed with a length of 06 (6) bytes following
        # 02 = type integer with 2 bytes following (offset): 01 01 (ie 1)
        # 02 = type integer with 2 bytes following (contentCount):  01 00
        
        # whith a search string present:
        # 81 = type context-specific/constructed with a length of 04 (4) bytes following (the length will change here)
        # 81 indicates a user string is present where as a a0 indicates just a offset search
        # 81 = type context-specific/constructed with a length of 06 (6) bytes following
        
        # the following info was taken from the ISO/IEC 8825-1:2003 x.690 standard re: the
        # encoding of integer values (note: these values are in
        # two-complement form so since offset will never be negative bit 8 of the
        # leftmost octet should never by set to 1):
        # 8.3.2: If the contents octets of an integer value encoding consist
        # of more than one octet, then the bits of the first octet (rightmost) and bit 8
        # of the second (to the left of first octet) octet:
        # a) shall not all be ones; and
        # b) shall not all be zero
        
        if ($search)
        {
            $search = preg_replace('/[^-[:alpha:] ,.()0-9]+/', '', $search);
            $ber_val = self::_string2hex($search);
            $str = self::_ber_addseq($ber_val, '81');
        }
        else
        {
            # construct the string from right to left
            $str = "020100"; # contentCount

            $ber_val = self::_ber_encode_int($offset);  // returns encoded integer value in hex format

            // calculate octet length of $ber_val
            $str = self::_ber_addseq($ber_val, '02') . $str;

            // now compute length over $str
            $str = self::_ber_addseq($str, 'a0');
        }
        
        // now tack on records per page
        $str = "020100" . self::_ber_addseq(self::_ber_encode_int($rpp-1), '02') . $str;

        // now tack on sequence identifier and length
        $str = self::_ber_addseq($str, '30');

        return pack('H'.strlen($str), $str);
    }


    /**
     * create ber encoding for sort control
     *
     * @param array List of cols to sort by
     * @return string BER encoded option value
     */
    private static function _sort_ber_encode($sortcols)
    {
        $str = '';
        foreach (array_reverse((array)$sortcols) as $col) {
            $ber_val = self::_string2hex($col);

            # 30 = ber sequence with a length of octet value
            # 04 = octet string with a length of the ascii value
            $oct = self::_ber_addseq($ber_val, '04');
            $str = self::_ber_addseq($oct, '30') . $str;
        }

        // now tack on sequence identifier and length
        $str = self::_ber_addseq($str, '30');

        return pack('H'.strlen($str), $str);
    }

    /**
     * Add BER sequence with correct length and the given identifier
     */
    private static function _ber_addseq($str, $identifier)
    {
        $len = dechex(strlen($str)/2);
        if (strlen($len) % 2 != 0)
            $len = '0'.$len;

        return $identifier . $len . $str;
    }

    /**
     * Returns BER encoded integer value in hex format
     */
    private static function _ber_encode_int($offset)
    {
        $val = dechex($offset);
        $prefix = '';

        // check if bit 8 of high byte is 1
        if (preg_match('/^[89abcdef]/', $val))
            $prefix = '00';

        if (strlen($val)%2 != 0)
            $prefix .= '0';

        return $prefix . $val;
    }

    /**
     * Returns ascii string encoded in hex
     */
    private static function _string2hex($str)
    {
        $hex = '';
        for ($i=0; $i < strlen($str); $i++)
            $hex .= dechex(ord($str[$i]));
        return $hex;
    }

}
