<?php

/*
 +-----------------------------------------------------------------------+
 | localization/<lang>/labels.inc                                        |
 |                                                                       |
 | Localization file of the Roundcube Webmail client                     |
 | Copyright (C) 2005-2013, The Roundcube Dev Team                       |
 |                                                                       |
 | Licensed under the GNU General Public License version 3 or            |
 | any later version with exceptions for skins & plugins.                |
 | See the README file for a full license statement.                     |
 |                                                                       |
 +-----------------------------------------------------------------------+

 For translation see https://www.transifex.com/projects/p/roundcube-webmail/resource/labels/
*/

$labels = array();

// login page
$labels['welcome']   = 'Добро пожаловать в $product!';
$labels['username']  = 'Имя пользователя';
$labels['password']  = 'Пароль';
$labels['server']    = 'Сервер';
$labels['login']     = 'Войти';

// taskbar
$labels['logout']   = 'Выход';
$labels['mail']     = 'Почта';
$labels['settings'] = 'Настройки';
$labels['addressbook'] = 'Контакты';

// mailbox names
$labels['inbox']  = 'Входящие';
$labels['drafts'] = 'Черновики';
$labels['sent']   = 'Отправленные';
$labels['trash']  = 'Корзина';
$labels['junk']   = 'СПАМ';

// message listing
$labels['subject'] = 'Тема';
$labels['from']    = 'От';
$labels['sender']  = 'Отправитель';
$labels['to']      = 'Кому';
$labels['cc']      = 'Копия';
$labels['bcc']     = 'Скрытая';
$labels['replyto'] = 'Ответить';
$labels['followupto'] = 'Followup-To';
$labels['date']    = 'Дата';
$labels['size']    = 'Размер';
$labels['priority'] = 'Приоритет';
$labels['organization'] = 'Организация';
$labels['readstatus'] = 'Статус прочтения';
$labels['listoptions'] = 'Настройки списка...';

$labels['mailboxlist'] = 'Папки';
$labels['messagesfromto'] = 'Сообщения с $from по $to из $count';
$labels['threadsfromto'] = 'Обсуждения с $from по $to из $count';
$labels['messagenrof'] = 'Сообщение $nr из $count';
$labels['fromtoshort'] = '$from – $to из $count';

$labels['copy']     = 'Копировать';
$labels['move']     = 'Переместить';
$labels['moveto']   = 'Переместить в...';
$labels['download'] = 'Загрузить';
$labels['open']     = 'Открыть';
$labels['showattachment'] = 'Показать';
$labels['showanyway'] = 'Все равно показать';

$labels['filename'] = 'Имя файла';
$labels['filesize'] = 'Размер файла';

$labels['addtoaddressbook'] = 'Добавить в контакты';

// weekdays short
$labels['sun'] = 'Вс';
$labels['mon'] = 'Пн';
$labels['tue'] = 'Вт';
$labels['wed'] = 'Ср';
$labels['thu'] = 'Чт';
$labels['fri'] = 'Пт';
$labels['sat'] = 'Сб';

// weekdays long
$labels['sunday']    = 'Воскресенье';
$labels['monday']    = 'Понедельник';
$labels['tuesday']   = 'Вторник';
$labels['wednesday'] = 'Среда';
$labels['thursday']  = 'Четверг';
$labels['friday']    = 'Пятница';
$labels['saturday']  = 'Суббота';

// months short
$labels['jan']	= 'Янв';
$labels['feb']	= 'Фев';
$labels['mar']	= 'Мар';
$labels['apr']	= 'Апр';
$labels['may']	= 'Май';
$labels['jun']	= 'Июн';
$labels['jul'] 	= 'Июл';
$labels['aug']	= 'Авг';
$labels['sep']	= 'Сен';
$labels['oct']	= 'Окт';
$labels['nov']	= 'Ноя';
$labels['dec']	= 'Дек';

// months long
$labels['longjan']	= 'Январь';
$labels['longfeb']	= 'Февраль';
$labels['longmar']	= 'Март';
$labels['longapr']	= 'Апрель';
$labels['longmay']	= 'Май';
$labels['longjun']	= 'Июнь';
$labels['longjul']	= 'Июль';
$labels['longaug']	= 'Август';
$labels['longsep']	= 'Сентябрь';
$labels['longoct']	= 'Октябрь';
$labels['longnov']	= 'Ноябрь';
$labels['longdec']	= 'Декабрь';

$labels['today'] = 'Сегодня';

// toolbar buttons
$labels['refresh']          = 'Обновить';
$labels['checkmail']        = 'Доставить почту';
$labels['compose']          = 'Написать сообщение';
$labels['writenewmessage']  = 'Новое сообщение';
$labels['reply']            = 'Ответить';
$labels['replytomessage']   = 'Ответить';
$labels['replytoallmessage'] = 'Ответить по списку или отправителю и всем получателям';
$labels['replyall']         = 'Ответить всем';
$labels['replylist']        = 'Ответить в список рассылки';
$labels['forward']          = 'Переслать';
$labels['forwardinline']    = 'Переслать в теле письма';
$labels['forwardattachment'] = 'Переслать как вложение';
$labels['forwardmessage']   = 'Переслать';
$labels['deletemessage']    = 'В корзину';
$labels['movemessagetotrash'] = 'Переместить сообщение в корзину';
$labels['printmessage']     = 'Печать';
$labels['previousmessage']  = 'Показать предыдущее сообщение';
$labels['firstmessage']     = 'Показать первое сообщение';
$labels['nextmessage']      = 'Показать следующее сообщение';
$labels['lastmessage']      = 'Показать последнее сообщение';
$labels['backtolist']       = 'К списку сообщений';
$labels['viewsource']       = 'Исходный текст';
$labels['mark']             = 'Пометить';
$labels['markmessages']     = 'Пометить сообщение';
$labels['markread']         = 'Как прочитанное';
$labels['markunread']       = 'Как непрочитанное';
$labels['markflagged']      = 'Установить флаг';
$labels['markunflagged']    = 'Снять флаг';
$labels['moreactions']      = 'Дополнительные действия...';
$labels['more']             = 'Еще';
$labels['back']             = 'Назад';
$labels['options']          = 'Параметры';

$labels['select'] = 'Выбрать';
$labels['all'] = 'Все';
$labels['none'] = 'Отсутствует';
$labels['currpage'] = 'Текущая страница';
$labels['unread'] = 'Непрочитанные';
$labels['flagged'] = 'Помеченные';
$labels['unanswered'] = 'Неотвеченные';
$labels['deleted'] = 'Удаленное';
$labels['undeleted'] = 'Не удалено';
$labels['invert'] = 'Инвертное';
$labels['filter'] = 'Фильтр';
$labels['list'] = 'Список';
$labels['threads'] = 'Обсуждения';
$labels['expand-all'] = 'Развернуть все';
$labels['expand-unread'] = 'Развернуть непрочитанные';
$labels['collapse-all'] = 'Свернуть все';
$labels['threaded'] = 'Обсуждения';

$labels['autoexpand_threads'] = 'Развернуть обсуждения';
$labels['do_expand'] = 'все обсуждения';
$labels['expand_only_unread'] = 'только с непрочитанными сообщениями';
$labels['fromto'] = 'Отправитель/Получатель';
$labels['flag'] = 'Флаг';
$labels['attachment'] = 'Вложение';
$labels['nonesort'] = 'Отсутствует';
$labels['sentdate'] = 'Дата отправки';
$labels['arrival'] = 'Дата получения';
$labels['asc'] = 'по возрастанию';
$labels['desc'] = 'по убыванию';
$labels['listcolumns'] = 'Колонки';
$labels['listsorting'] = 'Сортировать по';
$labels['listorder'] = 'Порядок сортировки';
$labels['listmode'] = 'Режим просмотра';

$labels['folderactions'] = 'Операции над папкой...';
$labels['compact'] = 'Сжать';
$labels['empty'] = 'Опустошить';

$labels['quota'] = 'Квота';
$labels['unknown']  = 'неизвестно';
$labels['unlimited']  = 'без ограничений';

$labels['quicksearch']  = 'Быстрый поиск';
$labels['resetsearch']  = 'Сброс';
$labels['searchmod']  = 'Варианты поиска';
$labels['msgtext']  = 'Всё сообщение';
$labels['body']  = 'Тело письма';

$labels['openinextwin'] = 'Открыть в новом окне';
$labels['emlsave'] = 'Сохранить (.eml)';
$labels['changeformattext'] = 'Показать в формате обычного текста';
$labels['changeformathtml'] = 'Показать в HTML формате';

// message compose
$labels['editasnew']      = 'Редактировать как новое';
$labels['send']           = 'Отправить';
$labels['sendmessage']    = 'Отправить сейчас';
$labels['savemessage']    = 'Сохранить черновик';
$labels['addattachment']  = 'Добавить вложение';
$labels['charset']        = 'Кодировка';
$labels['editortype']     = 'Редактор';
$labels['returnreceipt']  = 'Запрос ответа';
$labels['dsn']            = 'Уведомление о состоянии доставки';
$labels['mailreplyintro'] = '$sender писал $date:';
$labels['originalmessage'] = 'Исходное сообщение';

$labels['editidents']    = 'Изменить данные';
$labels['spellcheck']    = 'Орфография';
$labels['checkspelling'] = 'Проверить орфографию';
$labels['resumeediting'] = 'Продолжить редактирование';
$labels['revertto']      = 'Отменить правки';

$labels['attach'] = 'Вложить';
$labels['attachments'] = 'Вложения';
$labels['upload'] = 'Загрузить';
$labels['uploadprogress'] = '$percent ($current из $total)';
$labels['close']  = 'Закрыть';
$labels['messageoptions']  = 'Настройки сообщений...';

$labels['low']     = 'Низкий';
$labels['lowest']  = 'Нижайш.';
$labels['normal']  = 'Норм.';
$labels['high']    = 'Высокий';
$labels['highest'] = 'Высоч.';

$labels['nosubject']  = '(без темы)';
$labels['showimages'] = 'Показать изображения';
$labels['alwaysshow'] = 'Всегда показывать изображенияв письмах от $sender';
$labels['isdraft']    = 'Это черновик.';
$labels['andnmore']   = 'ещё $nr...';
$labels['togglemoreheaders'] = 'Загрузить ещё заголовки сообщений';
$labels['togglefullheaders'] = 'Показать оригинальные заголовки сообщения';

$labels['htmltoggle'] = 'HTML';
$labels['plaintoggle'] = 'Текст';
$labels['savesentmessagein'] = 'Сохранить в';
$labels['dontsave'] = 'не сохранять';
$labels['maxuploadsize'] = 'Максимальный размер файла $size';

$labels['addcc'] = 'Копия';
$labels['addbcc'] = 'Скрытая копия';
$labels['addreplyto'] = 'Кому ответить';
$labels['addfollowupto'] = 'Добавить Followup-To';

// mdn
$labels['mdnrequest'] = 'Отправитель этого сообщения запросил уведомление о прочтении. Отправить уведомление?';
$labels['receiptread'] = 'Уведомление о прочтении';
$labels['yourmessage'] = 'Это уведомление о прочтении вашего сообщения';
$labels['receiptnote'] = 'Это уведомление означает только, что сообщение было открыто получателем, и не гарантирует того, что оно было прочитано и (или) понято.';

// address boook
$labels['name']         = 'Отображаемое имя';
$labels['firstname']    = 'Имя';
$labels['surname']      = 'Фамилия';
$labels['middlename']   = 'Отчество';
$labels['nameprefix']   = 'Префикс';
$labels['namesuffix']   = 'Суффикс';
$labels['nickname']     = 'Прозвище';
$labels['jobtitle']     = 'Должность';
$labels['department']   = 'Отдел';
$labels['gender']       = 'Пол';
$labels['maidenname']   = 'Девичья фамилия';
$labels['email']        = 'E-Mail';
$labels['phone']        = 'Телефон';
$labels['address']      = 'Адрес';
$labels['street']       = 'Улица';
$labels['locality']     = 'Город';
$labels['zipcode']      = 'Индекс';
$labels['region']       = 'Область';
$labels['country']      = 'Страна';
$labels['birthday']     = 'День рождения';
$labels['anniversary']  = 'Годовщина';
$labels['website']      = 'Веб-сайт';
$labels['instantmessenger'] = 'IM';
$labels['notes'] = 'Заметки';
$labels['male']   = 'мужской';
$labels['female'] = 'женский';
$labels['manager'] = 'Менеджер';
$labels['assistant'] = 'Помощник';
$labels['spouse'] = 'Супруг';
$labels['allfields'] = 'Все поля';
$labels['search'] = 'Поиск';
$labels['advsearch'] = 'Расширенный поиск';
$labels['advanced'] = 'Дополнительно';
$labels['other'] = 'Другое';

$labels['typehome']   = 'Дом';
$labels['typework']   = 'Работа';
$labels['typeother']  = 'Другое';
$labels['typemobile']  = 'Мобильный';
$labels['typemain']  = 'Основной';
$labels['typehomefax']  = 'Домашний факс';
$labels['typeworkfax']  = 'Рабочий факс';
$labels['typecar']  = 'Автомобиль';
$labels['typepager']  = 'Пэйджер';
$labels['typevideo']  = 'Видео';
$labels['typeassistant']  = 'Помощник';
$labels['typehomepage']  = 'Домашняя страница';
$labels['typeblog'] = 'Блог';
$labels['typeprofile'] = 'Профиль';

$labels['addfield'] = 'Добавить поле...';
$labels['addcontact'] = 'Добавить выбранные контакты в список контактов';
$labels['editcontact'] = 'Редактировать контакт';
$labels['contacts'] = 'Контакты';
$labels['contactproperties'] = 'Свойства контакта';
$labels['personalinfo'] = 'Личная информация';

$labels['edit']   = 'Правка';
$labels['cancel'] = 'Отмена';
$labels['save']   = 'Сохранить';
$labels['delete'] = 'Удалить';
$labels['rename'] = 'Переименовать';
$labels['addphoto'] = 'Добавить';
$labels['replacephoto'] = 'Заменить';
$labels['uploadphoto'] = 'Загрузить фотографию';

$labels['newcontact']     = 'Создать новый контакт';
$labels['deletecontact']  = 'Удалить выбранные контакты';
$labels['composeto']      = 'Создать сообщение для выбранных контактов';
$labels['contactsfromto'] = 'Контакты с $from по $to из $count';
$labels['print']          = 'Печать';
$labels['export']         = 'Экспорт';
$labels['exportall']      = 'Экспортировать все';
$labels['exportsel']      = 'Экспортировать выделенные';
$labels['exportvcards']   = 'Экспортировать контакты в формате vCard';
$labels['newcontactgroup'] = 'Создать группу контактов';
$labels['grouprename']    = 'Переименовать группу';
$labels['groupdelete']    = 'Удалить группу';
$labels['groupremoveselected'] = 'Удалить выбранные контакты из группы';

$labels['previouspage']   = 'Показать предыдущий';
$labels['firstpage']      = 'Показать первую страницу';
$labels['nextpage']       = 'Показать следующую страницу';
$labels['lastpage']       = 'Показать последнюю страницу';

$labels['group'] = 'Группа';
$labels['groups'] = 'Группы';
$labels['personaladrbook'] = 'Персональные адреса';

$labels['searchsave'] = 'Сохранить запрос';
$labels['searchdelete'] = 'Удалить запрос';

$labels['import'] = 'Импортировать';
$labels['importcontacts'] = 'Импортировать контакты';
$labels['importfromfile'] = 'Импортировать из файла:';
$labels['importtarget'] = 'Добавить новые контакты в адресную книгу:';
$labels['importreplace'] = 'Заменить всю адресную книгу';
$labels['importdesc'] = 'Вы можете загрузить контакты из существующей адресной книги. <br/>В настоящее время мы поддерживаем импорт адресов в формате визитной карточки <a href="http://en.wikipedia.org/wiki/VCard">vCard</a> или CSV (данные разделённые запятой).';
$labels['done'] = 'Завершено';

// settings
$labels['settingsfor'] = 'Настройки для';
$labels['about'] = 'О программе';
$labels['preferences'] = 'Настройки';
$labels['userpreferences'] = 'Настройки пользователя';
$labels['editpreferences'] = 'Редактировать настройки пользователя';

$labels['identities'] = 'Профили';
$labels['manageidentities'] = 'Управление профилями';
$labels['newidentity'] = 'Новый профиль';

$labels['newitem'] = 'Новый';
$labels['edititem'] = 'Правка';

$labels['preferhtml'] = 'Предпочитать HTML';
$labels['defaultcharset'] = 'Набор символов по-умолчанию';
$labels['htmlmessage'] = 'Сообщение HTML';
$labels['messagepart'] = 'Часть';
$labels['digitalsig'] = 'Цифровая подпись';
$labels['dateformat'] = 'Формат даты';
$labels['timeformat'] = 'Формат времени';
$labels['prettydate'] = 'Красивые даты';
$labels['setdefault']  = 'Использовать по умолчанию';
$labels['autodetect']  = 'Определять автоматически';
$labels['language']  = 'Язык';
$labels['timezone']  = 'Часовой пояс';
$labels['pagesize']  = 'Строк на странице';
$labels['signature'] = 'Подпись';
$labels['dstactive']  = 'Летнее время';
$labels['showinextwin'] = 'Открыть сообщение в новом окне';
$labels['composeextwin'] = 'Создать в новом окне';
$labels['htmleditor'] = 'Создавать сообщения в HTML';
$labels['htmlonreply'] = 'только в ответ на сообщение в HTML';
$labels['htmlonreplyandforward'] = 'при пересылке или ответе на HTML сообщение';
$labels['htmlsignature'] = 'Подпись в HTML';
$labels['previewpane'] = 'Показать панель превью';
$labels['skin'] = 'Стиль оформления';
$labels['logoutclear'] = 'Очищать корзину при выходе';
$labels['logoutcompact'] = 'Сжать Входящие при выходе';
$labels['uisettings'] = 'Пользовательский интерфейс';
$labels['serversettings'] = 'Настройки сервера';
$labels['mailboxview'] = 'Вид почтового ящика';
$labels['mdnrequests'] = 'Уведомления о прочтении';
$labels['askuser'] = 'спросить перед отправкой';
$labels['autosend'] = 'отправлять автоматически';
$labels['autosendknown'] = 'отправлять уведомления контактам из адресной книги, в противном случае спросить';
$labels['autosendknownignore'] = 'отправлять уведомления только контактам из адресной книги, остальных игнорировать';
$labels['ignore'] = 'игнорировать';
$labels['readwhendeleted'] = 'Помечать как прочитанное при удалении';
$labels['flagfordeletion'] = 'Помечать для удаления вместо удаления';
$labels['skipdeleted'] = 'Не показывать удаленные сообщения';
$labels['deletealways'] = 'Удалять сообщения, если не получается поместить их в корзину';
$labels['deletejunk'] = 'Удалять сообщения из папки СПАМ минуя Корзину';
$labels['showremoteimages'] = 'Показывать удаленные изображения';
$labels['fromknownsenders'] = 'от известных отправителей';
$labels['always'] = 'всегда';
$labels['showinlineimages'] = 'Показывать вложенные изображения внизу сообщения';
$labels['autosavedraft']  = 'Автосохранение черновика';
$labels['everynminutes']  = 'каждые $n минут';
$labels['refreshinterval']  = 'Обновить (проверить новые сообщения и т.п.)';
$labels['never']  = 'никогда';
$labels['immediately']  = 'немедленно';
$labels['messagesdisplaying'] = 'Отображение сообщений';
$labels['messagescomposition'] = 'Создание сообщений';
$labels['mimeparamfolding'] = 'Имена вложений';
$labels['2231folding'] = 'RFC 2231 (только для новейших программ)';
$labels['miscfolding'] = 'RFC 2047/2231  (наибольшая совместимость)';
$labels['2047folding'] = 'RFC 2047  (для старых программ)';
$labels['force7bit'] = 'Использовать MIME для 8-битных символов';
$labels['advancedoptions'] = 'Дополнительные настройки';
$labels['focusonnewmessage'] = 'Фокусировать окно браузера при новом сообщении';
$labels['checkallfolders'] = 'Проверять новые сообщения во всех папках';
$labels['displaynext'] = 'Показать следующее сообщение, после удаления или перемещения данного';
$labels['defaultfont'] = 'Шрифт по умолчанию HTML сообщения';
$labels['mainoptions'] = 'Основные настройки';
$labels['browseroptions'] = 'Настройки обозревателя';
$labels['section'] = 'Раздел';
$labels['maintenance'] = 'Обслуживание';
$labels['newmessage'] = 'Новое сообщение';
$labels['signatureoptions'] = 'Опции подписи';
$labels['whenreplying'] = 'При ответе';
$labels['replyempty'] = 'не цитировать оригинальное сообщение';
$labels['replytopposting'] = 'начать новое сообщение перед цитируемым';
$labels['replybottomposting'] = 'начать новое сообщение после цитируемого';
$labels['replyremovesignature'] = 'Удалить подпись при ответе';
$labels['autoaddsignature'] = 'Автоматически добавлять подпись';
$labels['newmessageonly'] = 'только в новых сообщениях';
$labels['replyandforwardonly'] = 'только в ответах и пересылках';
$labels['replysignaturepos'] = 'Прикрепить подпись при ответе и пересылке';
$labels['belowquote'] = 'после цитаты';
$labels['abovequote'] = 'до цитаты';
$labels['insertsignature'] = 'Вставить подпись';
$labels['previewpanemarkread']  = 'Отмечать просмотренные сообщения как прочитанные';
$labels['afternseconds']  = 'через $n секунд';
$labels['reqmdn'] = 'Всегда запрашивать уведомление о доставке';
$labels['reqdsn'] = 'Всегда запрашивать уведомление о состоянии доставки';
$labels['replysamefolder'] = 'Помещать ответы в ту же папку, где находится оригинал';
$labels['defaultabook'] = 'Адресная книга по умолчанию';
$labels['autocompletesingle'] = 'Пропускать дополнительные адреса в автозавершении';
$labels['listnamedisplay'] = 'Выводить список контактов как';
$labels['spellcheckbeforesend'] = 'Проверять орфографию перед отправкой';
$labels['spellcheckoptions'] = 'Параметры проверки орфографии';
$labels['spellcheckignoresyms'] = 'Пропускать слова с символами';
$labels['spellcheckignorenums'] = 'Пропускать слова с цифрами';
$labels['spellcheckignorecaps'] = 'Пропускать слова из прописных букв';
$labels['addtodict'] = 'Добавить в словарь';
$labels['mailtoprotohandler'] = 'Зарегистрировать обработчик для ссылок mailto:';
$labels['forwardmode'] = 'Пересылка сообщений';
$labels['inline'] = 'в тексте';
$labels['asattachment'] = 'как вложение';

$labels['folder']  = 'Папка';
$labels['folders']  = 'Папки';
$labels['foldername']  = 'Имя папки';
$labels['subscribed']  = 'Подписан';
$labels['messagecount'] = 'Сообщения';
$labels['create']  = 'Создать';
$labels['createfolder']  = 'Создать новую папку';
$labels['managefolders']  = 'Управление папками';
$labels['specialfolders'] = 'Особые папки';
$labels['properties'] = 'Свойства';
$labels['folderproperties'] = 'Свойства папки';
$labels['parentfolder'] = 'Родительская папка';
$labels['location'] = 'Расположение';
$labels['info'] = 'Информация';
$labels['getfoldersize'] = 'Показать размер папки';
$labels['changesubscription'] = 'Изменить подписку';
$labels['foldertype'] = 'Тип каталога';
$labels['personalfolder']  = 'Приватный каталог';
$labels['otherfolder']  = 'Каталог другого пользователя';
$labels['sharedfolder']  = 'Совместный каталог';

$labels['sortby'] = 'Сортировать по';
$labels['sortasc']  = 'Возрастанию';
$labels['sortdesc'] = 'Убыванию';
$labels['undo'] = 'Отмена';

$labels['installedplugins'] = 'Установленные дополнения';
$labels['plugin'] = 'Дополнение';
$labels['version'] = 'Версия';
$labels['source'] = 'Источник';
$labels['license'] = 'Лицензия';
$labels['support'] = 'Поддержка';

// units
$labels['B'] = 'Б';
$labels['KB'] = 'КБ';
$labels['MB'] = 'МБ';
$labels['GB'] = 'ГБ';

// character sets
$labels['unicode'] = 'Unicode';
$labels['english'] = 'Английский';
$labels['westerneuropean'] = 'Западноевропейский';
$labels['easterneuropean'] = 'Восточноевропейский';
$labels['southeasterneuropean'] = 'Юго-Восточноевропейский';
$labels['baltic'] = 'Прибалтийский';
$labels['cyrillic'] = 'Кириллица';
$labels['arabic'] = 'Арабский';
$labels['greek'] = 'Греческий';
$labels['hebrew'] = 'Иврит';
$labels['turkish'] = 'Турецкий';
$labels['nordic'] = 'Скандинавский';
$labels['thai'] = 'Тайский';
$labels['celtic'] = 'Кельтский';
$labels['vietnamese'] = 'Вьетнамский';
$labels['japanese'] = 'Японский';
$labels['korean'] = 'Корейский';
$labels['chinese'] = 'Китайский';

?>
