stock Update_Phone(playerid)
{
    if(0 == IsPlayerPhoneCreated(playerid) || PlayerInfo[playerid][pPhoneOff] == 1)
		return 1;

	new hours,
		minutes,
		str_time[16];

	gettime(hours, minutes);

	format(str_time, 6, "%02i:%02i", hours, minutes);
	PlayerTextDrawSetString(playerid, TD_iphone[playerid][18], str_time);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][18]);

	new network[11];
	switch(GetPlayerNetwork(playerid))
	{
	    case 0: network = "_";
	    case 1: network = "o";
	    case 2: network = "oo";
	    case 3: network = "ooo";
	    case 4: network = "oooo";
	    case 5: network = "ooooo";
	}
	PlayerTextDrawSetString(playerid, TD_iphone[playerid][23], network);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][23]);

	if(PhoneInfo[playerid][phoneBlock] != 0)
	{
	    format(str_time, 6, "%02i:%02i", hours, minutes);
		PlayerTextDrawSetString(playerid, TD_iphone_block[playerid][0], str_time);
		PlayerTextDrawShow(playerid, TD_iphone_block[playerid][0]);

		new month,
		    day;

		new month_name[12][12] = {"Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};

		getdate(_, month, day);

		format(str_time, 16, "%02i %s", day, month_name[month-1]);
		PlayerTextDrawSetString(playerid, TD_iphone_block[playerid][1], str_time);
		PlayerTextDrawShow(playerid, TD_iphone_block[playerid][1]);
	}
	return 1;
}

stock Phone_Keypad(playerid, status)
{
	if(status)
	{
		PhoneInfo[playerid][phoneKeypad] = 1;
		format(pTemp[playerid][pCallKeypad], 12, "");
		PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], "_");
		PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);
	    for(new i; i != 34; i++) PlayerTextDrawShow(playerid, TD_iphone_keypad[playerid][i]);
	}
	else
	{
	    PhoneInfo[playerid][phoneKeypad] = 0;
	    format(pTemp[playerid][pCallKeypad], 12, "");
	    PlayerTextDrawHide(playerid, TD_iphone_name[playerid]);
    	for(new i; i != 34; i++) PlayerTextDrawHide(playerid, TD_iphone_keypad[playerid][i]);
	}
	return 1;
}


stock Phone_Menu(playerid, status)
{
	if(status)
	{
	    for(new i; i != 12; i++) PlayerTextDrawShow(playerid, TD_iphone_menu[playerid][i]);
	}
	else
	{
    	for(new i; i != 12; i++) PlayerTextDrawHide(playerid, TD_iphone_menu[playerid][i]);
	}
	return 1;
}

stock Phone_Setting(playerid, status)
{
	if(status)
	{
	    PhoneInfo[playerid][phoneSetting] = 1;

        PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][1], (PlayerInfo[playerid][pPhoneAirplane] == 0)?("Ucak Modu: Kapali"):("Ucak Modu: Acik"));

        PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][2], (PlayerInfo[playerid][pPhoneSound] == 0)?("Ses: Acik"):("Ses: Kapali"));

		PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);

		new mes[32];
		format(mes, sizeof(mes), "zil-%i.mp3", PlayerInfo[playerid][pPhoneRingtone]+1);
		PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][10], mes);

	    for(new i; i != 11; i++) PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][i]);
	}
	else
	{
	    PhoneInfo[playerid][phoneSetting] = 0;
    	for(new i; i != 11; i++) PlayerTextDrawHide(playerid, TD_iphone_setting[playerid][i]);
	}
	return 1;
}

stock Phone_Block(playerid, status)
{
	if(status)
	{
	    PhoneInfo[playerid][phoneBlock] = 1;
	    PhoneInfo[playerid][phoneBlockSMS][0] = 0;
	    PhoneInfo[playerid][phoneBlockSMS][1] = 0;
	    PhoneInfo[playerid][phoneBlockSMS][2] = 0;
	    for(new i; i != 3; i++) PlayerTextDrawShow(playerid, TD_iphone_block[playerid][i]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `sms` WHERE `to_number` = '%i' AND `read`=0 ORDER BY `id` DESC LIMIT 3", PlayerInfo[playerid][pNumber]);
		mysql_tquery(dbHandle, query, "ShowBlockSMS", "i", playerid);
	}
	else
	{
	    PhoneInfo[playerid][phoneBlock] = 0;
	    PhoneInfo[playerid][phoneBlockSMS][0] = 0;
	    PhoneInfo[playerid][phoneBlockSMS][1] = 0;
	    PhoneInfo[playerid][phoneBlockSMS][2] = 0;
    	for(new i; i != 6; i++) PlayerTextDrawHide(playerid, TD_iphone_block[playerid][i]);
	}
	return 1;
}

forward ShowBlockSMS(playerid);
public ShowBlockSMS(playerid)
{
	if(PhoneInfo[playerid][phoneBlock] != 1 || cache_num_rows() == 0)
	    return 1;

	new name[128];
	for(new i; i != cache_num_rows(); i++)
	{
	    if(i > 2)
	        break;

		cache_get_value(i, "from_name", name, 24);
		cache_get_value_int(i, "id", PhoneInfo[playerid][phoneBlockSMS][i]);
		format(name, sizeof(name), "iMessage~n~~l~%s", name);

		PlayerTextDrawSetString(playerid, TD_iphone_block[playerid][i+3], TurkishCharFix(name));
		PlayerTextDrawShow(playerid, TD_iphone_block[playerid][i+3]);
	}
	return 1;
}

stock Phone_Button(playerid)
{
	for(new i; i != 6; i++) PlayerTextDrawHide(playerid, TD_iphone_button[playerid][i]);
	return 1;
}

stock Phone_Destroy(playerid)
{
    if(PhoneInfo[playerid][phoneCreated] == 0)
	    return 1;

    #include "../include/iphone_destroy.inc"
    PhoneInfo[playerid][phoneCreated] = 0;

    if(pTemp[playerid][pCallLine] == INVALID_PLAYER_ID && !GetPVarInt(playerid, #selfie))
        RemovePlayerAttachedObject(playerid, ATTACH_HANDS);

	return 1;
}

stock Phone_Create(playerid, type = 0)
{
	if(PhoneInfo[playerid][phoneCreated] != 0)
	    return 1;

	new mes[56];

    #include "../include/iphone_create.inc"
 	PhoneInfo[playerid][phoneCreated] = 1;
	PhoneInfo[playerid][phoneContact] = 0;
	PhoneInfo[playerid][phoneSMS] = 0;
	PhoneInfo[playerid][phoneHistory] = 0;
	PhoneInfo[playerid][phoneKeypad] = 0;
	PhoneInfo[playerid][phoneGPS] = 0;
	PhoneInfo[playerid][phoneSetting] = 0;

	if(!IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) SetPlayerAttachedObject(playerid, ATTACH_HANDS, phone_model[PlayerInfo[playerid][pPhoneModel]], 6, 0.111, -0.000999, 0.0, 77.9, -171.6, -3.40001, 1.0, 1.0, 1.0);

	if(type == 0)
	{
	    pc_cmd_ame(playerid, "telefonunu çýkarýr.");
 		SendClientMessage(playerid, -1, "[ ! ] /telefon ile menüyü tekrar kapatabilirsin. /pc komutu ile imleci aktif edebilirsin.");
		SendClientMessage(playerid, -1, "[ ! ] ESC tuþuna basarak yürüyüþ moduna geçebilirsin.");
		SelectTextDraw(playerid, -1);
	}

	if(PlayerInfo[playerid][pPhoneOff] == 1)
		return 1;

 	if(pTemp[playerid][pCallLine] != INVALID_PLAYER_ID)
 	{
		if(pTemp[playerid][pCallStatus] == 1)
		{
		    format(mes, sizeof(mes), "%s~n~hatta", pTemp[playerid][pCallName]);

		    PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], TurkishCharFix(mes));
		    PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);

		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][2]);
		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][3]);
		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][4]);
		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][5]);
		}
		else
		{
		    if(pTemp[playerid][pCallStatus] == 2)
		    	format(mes, sizeof(mes), "%s~n~%s", TurkishCharFix(pTemp[playerid][pCallName]), ConvertSecond(pTemp[playerid][pCallTime]));
			else
			    format(mes, sizeof(mes), "%s~n~araniyor...", TurkishCharFix(pTemp[playerid][pCallName]));

		    PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], mes);
		    PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);

		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][0]);
		    PlayerTextDrawShow(playerid, TD_iphone_button[playerid][1]);
		}
	}
 	else
 	{
 	    Update_Phone(playerid);
 	    Phone_Block(playerid, 1);
 	}
	return 1;
}

this::SmsToPlayerOff(sendernumber_str[], sender_str[], text[])
{
    new rows = cache_num_rows();
	if(!rows) return 1;
	new sendernumber = strval(sendernumber_str),
		month,
 		day,
 		year,
 		hour,
		number,
 		minute
	;

	cache_get_value_int(0, "number", number);
	
	gettime(hour, minute);
	getdate(year, month, day);

	new month_name[12][12] = {"Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};

	new query[256 + 128];

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `sms` (`to_name`,`from_name`,`to_number`,`from_number`,`text`,`date`,`read`) VALUES (%i,'%e',%i,%i,'%e','%s %02i %i, %02i:%02i',%i)",
	number,
	sender_str,
	number,
	sendernumber,
	text,
	month_name[month-1],
	day,
	year,
	hour,
	minute,
	0);
	mysql_tquery(dbHandle, query);

	return 1;
}

forward OfflineSMS(playerid, number, text[]);
public OfflineSMS(playerid, number, text[])
{
	if(!cache_num_rows())
	    return SCM(playerid, -1, "Bir hata oluþtu. Kod: #072");

    new find_phone,
		name_playerid[MAX_PLAYER_NAME],
		name_targetid[MAX_PLAYER_NAME];

    cache_get_value(0, "contact", name_targetid);

    for (new i = 0; i != MAX_PLAYER_CONTACTS; i ++)
	{
		if(PlayerContacts[playerid][i][contactOn] != 0 && PlayerContacts[playerid][i][contactNumber] == number)
		{
 			strmid(name_playerid, PlayerContacts[playerid][i][contactName], 0, strlen(PlayerContacts[playerid][i][contactName]), 32);
 			find_phone = 1;
		}
	}

	if(!find_phone) format(name_playerid, 24, "%i", number);
	if(!strlen(name_targetid) || CompareStrings(name_targetid, "NULL")) format(name_targetid, 24, "%i", PlayerInfo[playerid][pNumber]);

	new month,
 		day,
 		year,
 		hour,
 		minute;

	new month_name[12][12] = {"Ocak","Þubat","Mart","Nisan","Mayýs","Haziran","Temmuz","Aðustos","Eylül","Ekim","Kasým","Aralýk"};
	gettime(hour, minute);
	getdate(year, month, day);

	new query[256 + 128];
    mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `sms` (`to_name`,`from_name`,`to_number`,`from_number`,`text`,`date`,`read`) VALUES ('%e','%e',%i,%i,'%e','%s %02i %i, %02i:%02i','%i')",
	name_playerid,
	name_targetid,
	number,
	PlayerInfo[playerid][pNumber],
	text,
	month_name[month-1],
	day,
	year,
	hour,
	minute,
 	0);
	mysql_tquery(dbHandle, query);

	if(strlen(text) > MAXLEN)
	{
		new pos = MAXLEN;
		if(pos < MAXLEN-1) pos = MAXLEN;
		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %.*s ...", pos, text);
		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: ... %s Gönderen: %s.", text[pos], name_playerid);
	}
	else
		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %s Gönderen: %s.", text, name_playerid);

    pc_cmd_ame(playerid, "bir SMS gönderir.");
	return 1;
}

stock CancelCall(playerid)
{
	if(pTemp[playerid][pCallLine] == INVALID_PLAYER_ID)
	    return 1;

	new targetid = pTemp[playerid][pCallLine];

	new month,
 		day,
 		year,
 		hour,
 		minute,
 		name_1[24],
 		name_2[24];

	format(name_1, 24, "%s", pTemp[targetid][pCallName]);
	format(name_2, 24, "%s", pTemp[playerid][pCallName]);

	new month_name[12][12] = {"Oca","Sub","Mar","Nis","May","Haz","Tem","Agu","Eyl","Eki","Ksm","Ara"};
	gettime(hour, minute);
	getdate(year, month, day);

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `history_calls` (`to_number`,`from_number`,`to_name`,`from_name`,`time`,`date_hour`,`date_month`) VALUES ('%i','%i','%s','%s','%i','%02i:%02i','%s %02i %i')",
	(pTemp[playerid][pCallIncoming] == 1)?(PlayerInfo[playerid][pNumber]):(PlayerInfo[targetid][pNumber]),
    (pTemp[playerid][pCallIncoming] == 0)?(PlayerInfo[targetid][pNumber]):(PlayerInfo[playerid][pNumber]),
    (pTemp[playerid][pCallIncoming] == 1)?(name_2):(name_1),
    (pTemp[playerid][pCallIncoming] == 0)?(name_1):(name_2),
    pTemp[playerid][pCallTime],
	hour,
	minute,
	month_name[month-1],
	day,
	year);
	mysql_tquery(dbHandle, query);

	pTemp[playerid][pCallLine] = INVALID_PLAYER_ID;
	pTemp[playerid][pCallStatus] = 0;
	pTemp[playerid][pCallIncoming] = 0;
	pTemp[playerid][pCallTime] = 0;
	format(pTemp[playerid][pCallName], 24, "");

	pTemp[targetid][pCallLine] = INVALID_PLAYER_ID;
	pTemp[targetid][pCallStatus] = 0;
	pTemp[targetid][pCallIncoming] = 0;
	pTemp[targetid][pCallTime] = 0;
	format(pTemp[targetid][pCallName], 24, "");


	if(0 != IsPlayerPhoneCreated(playerid))
		Phone_Destroy(playerid);

	if(0 != IsPlayerPhoneCreated(targetid))
	    Phone_Destroy(targetid);

	SetPVarInt(playerid, #loud_speak, 0);
	SetPVarInt(targetid, #loud_speak, 0);

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	SetPlayerSpecialAction(targetid, SPECIAL_ACTION_STOPUSECELLPHONE);

	RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
	RemovePlayerAttachedObject(targetid, ATTACH_HANDS);
	return 1;
}

GetMaxPlayerContacts(playerid)
{
	switch(PlayerInfo[playerid][pPremium])
	{
	    case 0: return 40;
	    case 1: return 40;
	    case 2: return 40;
	    case 3: return 40;
	}
	return 100;
}

GetNumberOwner(number)
{
	if (number == 0)
		return INVALID_PLAYER_ID;

	foreach (new i : Player)
	{
		if (IsPlayerLogged(i) && PlayerInfo[i][pNumber] == number)
			return i;
	}
	return INVALID_PLAYER_ID;
}

GetPlayerNetwork(playerid)
{
    new
	    Float: fDistance[2] = {99999.0, 0.0},
	    iIndex = -1,
        Float:fX,
	    Float:fY,
		Float:fZ;

	if (GetInterior(playerid) || GetWorld(playerid))
	{
		fX = PlayerInfo[playerid][pLocationPos][0];
		fY = PlayerInfo[playerid][pLocationPos][1];
		fZ = PlayerInfo[playerid][pLocationPos][2];
	}
	else GetPlayerPos(playerid, fX, fY, fZ);

	for (new i = 0; i < MAX_TOWERS; i ++)
	{
	    if (TowerInfo[i][towerOn] == 0)
	        continue;

		fDistance[1] = GetDistanceBetweenPoints(fX, fY, fZ, TowerInfo[i][towerPosX], TowerInfo[i][towerPosY], TowerInfo[i][towerPosZ]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}

	if (iIndex == -1)
		return 0;

 	switch(floatround(fDistance[0]))
	{
 		case 0..400: return 5;
   		case 401..600: return 4;
     	case 601..800: return 3;
      	case 801..1000: return 2;
		case 1001..1200: return 1;
		default: return 0;
  	}
	return 0;
}

SendSMStoPlayer(playerid, sendernumber_str[], sender_str[], text[], showsmstxt = 1)
{
    if (PlayerInfo[playerid][pNumber] == 0)
		return 1;


	new sendernumber = strval(sendernumber_str),
		month,
 		day,
 		year,
 		hour,
 		minute
	;

    new month_name[12][12] = {"Ocak","Þubat","Mart","Nisan","Mayýs","Haziran","Temmuz","Aðustos","Eylül","Ekim","Kasým","Aralýk"};

	gettime(hour, minute);
	getdate(year, month, day);

	new query[256 + 128];

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `sms` (`to_name`,`from_name`,`to_number`,`from_number`,`text`,`date`,`read`) VALUES (%i,'%e',%i,%i,'%e','%s %02i %i, %02i:%02i',%i)",
	PlayerInfo[playerid][pNumber],
	sender_str,
	PlayerInfo[playerid][pNumber],
	sendernumber,
	text,
	month_name[month-1],
	day,
	year,
	hour,
	minute,
    (PlayerInfo[playerid][pPhoneAirplane] == 0 && PlayerInfo[playerid][pPhoneOff] == 0 && IsPlayerLogged(playerid))?(0):(-1));
	mysql_tquery(dbHandle, query);

	if (PlayerInfo[playerid][pPhoneAirplane] == 0 && PlayerInfo[playerid][pPhoneOff] == 0)
	{
		if (PlayerInfo[playerid][pPhoneSound] != 0)
		{
		    pc_cmd_my(playerid, "telefonu çalar.");
			PlaySound(playerid, 1084);

			if (!IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))
			{
				if (!IsPlayerPhoneCreated(playerid)) Phone_Create(playerid);
			}
		}
	}
	if (showsmstxt)
	{
		if (strlen(text) > MAXLEN)
		{
			new pos = MAXLEN;
			if (pos < MAXLEN-1) pos = MAXLEN;
			if (PlayerInfo[playerid][pPhoneAirplane] == 0 && PlayerInfo[playerid][pPhoneOff] == 0)
			{
				SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %.*s ...", pos, text);
				SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: ... %s Gönderen: %s.", text[pos], sender_str);
			}
		}
		else
		{
			if (PlayerInfo[playerid][pPhoneAirplane] == 0 && PlayerInfo[playerid][pPhoneOff] == 0)
				SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %s Gönderen: %s.", text, sender_str);
		}
	}
	return 1;
}

stock PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z)
{
    for(new i=0; i<MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i,range,x,y,z))
        {
            PlayerPlaySound(i, soundid, x, y, z);
        }
    }
	return 1;
}


stock TextTab(text[], minlen = 32, maxlen = 40, cellphone = 1, n = 1)
{
    new string[256],
		temporystring[256]
	;

	format(temporystring, sizeof(temporystring), "%s", text);

	if (n) if (strfind(temporystring, "\n", true) != -1)	return temporystring;
	else
	{
		new pos = strfind(temporystring, "\n", true);
		format(string, sizeof(string), "%.*s", string, pos+1, temporystring);
		strdel(temporystring, 0, pos+1);

	}
	for(new i = 0; i < floatround(strlen(text)/maxlen, floatround_floor); i++)
	{
		new pos = maxlen;
		while(temporystring[--pos] != ' ') {}

		if (pos < minlen)
		{
			pos = maxlen;
			if (temporystring[pos] == ' ')
			{
				format(string, sizeof(string), "%s%.*s", string, pos, temporystring);
				format(temporystring, 256, "%s",temporystring[pos+1]);
			} else {
				format(string, sizeof(string), "%s%.*s-", string, pos, temporystring);
				format(temporystring, 256, "%s",temporystring[pos]);
			}
		}
		else
		{
			format(string, sizeof(string), "%s%.*s", string, pos, temporystring);
			format(temporystring, 256, "%s",temporystring[pos+1]);
		}

		if (i+1 <= floatround(strlen(text)/maxlen, floatround_floor))
		{
			if (cellphone)	format(string, sizeof(string), "%s\n", string);
			else			format(string, sizeof(string), "%s~n~", string);
		}
	}

	format(string, sizeof(string), "%s%s", string, temporystring);
	return string;
}

stock TextTabQ(text[])
{
    new string[400],
		temporystring[400],
		pos,
		i = 0
	;

	format(temporystring, sizeof(temporystring), "%s", text);

	while((pos = strfind(temporystring, "\n")) != -1)
	{
		if (!i)
		{
			format(string, sizeof(string), "{AFAFAF}| %.*s", pos+1, temporystring);
			strdel(temporystring, 0, pos+1);
		}
		else
		{
			format(string, sizeof(string), "%s{AFAFAF}|{FFFFFF} %.*s", string, pos+1, temporystring);
			strdel(temporystring, 0, pos+1);
		}
		i++;
	}

	format(string, sizeof(string), "%s{AFAFAF}|{FFFFFF} %s", string, temporystring);
	return string;
}

stock LoadPlayerContacts(playerid)
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `player_contacts` WHERE `userid` = '%i'", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "OnPlayerLoadContacts", "i", playerid);
	return 1;
}

stock PlacePlayerContact(playerid, contactid, contact[], number)
{
    new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `player_contacts` (userid, contact, number) VALUES (%i, '%e', %i)", PlayerInfo[playerid][pID], SQL_ReturnEscaped(contact), number);
	mysql_tquery(dbHandle, query, "OnContactInsert", "ii", playerid, contactid);
	return 1;
}

forward OnContactInsert(playerid, contactid);
public OnContactInsert(playerid, contactid)
{
    PlayerContacts[playerid][contactid][contactID] = cache_insert_id();
	return 1;
}

forward OnPlayerLoadContacts(playerid);
public OnPlayerLoadContacts(playerid)
{
	if(!cache_num_rows())
	    return 1;

	for(new i = 0; i < cache_num_rows(); i++)
	{
	    cache_get_value_int(i, "id", PlayerContacts[playerid][i][contactID]);
	    cache_get_value(i, "contact", PlayerContacts[playerid][i][contactName], 32);
	    cache_get_value_int(i, "number", PlayerContacts[playerid][i][contactNumber]);

		PlayerContacts[playerid][i][contactOn] = 1;
	}
	return 1;
}

SetPlayerCellphoneAction(playerid, enable)
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return 0;
	else
	{
		if (VehicleHasDoors(GetPlayerVehicleID(playerid)) && PlayerInfo[playerid][pTalk])
			return 0;

	    if (enable)
	    {
	        if (VehicleHasDoors(GetPlayerVehicleID(playerid)))
	        {
				ApplyAnimation(playerid, "CAR_CHAT", "carfone_in", 4.1, 0, 0, 0, 1, 0, 1);
			}
			else
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
			}
		}
		else
		{
		    if (VehicleHasDoors(GetPlayerVehicleID(playerid)))
	        {
				ApplyAnimation(playerid, "CAR_CHAT", "carfone_out", 4.1, 0, 0, 0, 0, 0, 1);
			}
			else
			{
		    	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			}
		}
	}
	return 1;
}

HangupCall(playerid)
{
	SetPlayerCellphoneAction(playerid, false);

	if (pTemp[playerid][pPayphone] == -1)
	{
		if (IsPlayerPhoneCreated(playerid)) Phone_Destroy(playerid);

		SetPVarInt(playerid, #loud_speak, 0);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);

		if (!pTemp[playerid][pEmergency]) {
			SaveCall(playerid);
		}
	}

	new id = -1;
	for(new i = 0; i < MAX_PAYPHONES; i++)
	{
		if (PayphoneInfo[i][phCaller] == playerid)
		{
			id = i;
			break;
		}
	}
	if (id != -1)
	{
		PayphoneInfo[id][phState] = PAYPHONE_STATE_NONE;
		Update_Payphone(id);
	}

	pTemp[playerid][pCallLine] = INVALID_PLAYER_ID;
	pTemp[playerid][pCallStatus] = 0;
	pTemp[playerid][pCallIncoming] = 0;
	pTemp[playerid][pCallTime] = 0;
	format(pTemp[playerid][pCallName], 25, "");
	pTemp[playerid][pEmergency] = 0;

	if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
	return 1;
}

SaveCall(playerid)
{
	if (pTemp[playerid][pCallLine] == INVALID_PLAYER_ID) return 1;

	new targetid = pTemp[playerid][pCallLine],
		month,
		day,
		year,
		hour,
	 	minute,
		name_1[24],
		name_2[24];

	format(name_1, 25, "%s", pTemp[targetid][pCallName]);
	format(name_2, 25, "%s", pTemp[playerid][pCallName]);

	new month_name[12][12] = {"Oca","Sub","Mar","Nis","May","Haz","Tem","Agu","Eyl","Eki","Ksm","Ara"};

	gettime(hour, minute);
	getdate(year, month, day);

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `history_calls` (`to_number`,`from_number`,`to_name`,`from_name`,`time`,`date_hour`,`date_month`) VALUES (%i,%i,'%s','%s',%i,'%02i:%02i','%s %02i, %i')",
	(pTemp[playerid][pCallIncoming] == 1) ? (PlayerInfo[playerid][pNumber]) : (PlayerInfo[targetid][pNumber]),
	(pTemp[playerid][pCallIncoming] == 0) ? (PlayerInfo[targetid][pNumber]) : (PlayerInfo[playerid][pNumber]),
    (pTemp[playerid][pCallIncoming] == 1) ? (name_2) : (name_1),
	(pTemp[playerid][pCallIncoming] == 0) ? (name_1) : (name_2),
	pTemp[playerid][pCallTime],
	hour,
	minute,
	month_name[month-1],
	day,
	year);
	mysql_tquery(dbHandle, query);

	return 1;
}

stock Phone_Contact_Info(playerid, contact = -1)
{
	if(contact == -1)
	{
	    PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][0]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][1]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][2]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][3]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][4]);
		DeletePVar(playerid, #select_contact);
	    return 1;
	}

	if(PlayerContacts[playerid][contact][contactOn] == 0)
	    return 1;

	new mes[128];
	format(mes, sizeof(mes), "%s~n~(%i)", PlayerContacts[playerid][contact][contactName], PlayerContacts[playerid][contact][contactNumber]);
    PlayerTextDrawSetString(playerid, TD_iphone_contact[playerid][0], TurkishCharFix(mes));
    PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][0]);

    PlayerTextDrawSetString(playerid, TD_iphone_contact[playerid][1], "Ara");
    PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][1]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][2]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][3]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][4]);

	SetPVarInt(playerid, #select_contact, contact);
	return 1;
}

stock Phone_Contacts(playerid, list = -1)
{
	if(list == -1)
	{
	    for(new i; i != 13;i++) PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i]);
	    PhoneInfo[playerid][phoneContact] = 0;
	    return 1;
	}
    PhoneInfo[playerid][phoneContact] = 1;
	new
	    number,
		count = 0,
		mes[MAX_PLAYER_NAME + 4];

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][0], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][0]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][1]);

    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][2]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][3], "Kisi ekle");
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][3]);

	for(new i = list * 9; i != MAX_PLAYER_CONTACTS; i++)
	{
	    if(PlayerContacts[playerid][i][contactOn] == 0)
	        continue;

		count++;
		break;
 	}

	if(count == 0)
	    return 1;

	count = 0;

	for(new i; i != 9;i++)
	{
 		PhoneInfo[playerid][phoneListed][i] = -1;
  		PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i + 4]);
 	}

	for(new i = 0; i != MAX_PLAYER_CONTACTS; i++)
	{
	    if(PlayerContacts[playerid][i][contactOn] == 0)
	        continue;

        number++;
		if(i < (list * 9))
		    continue;

		format(mes, sizeof(mes), "%i. %s", number, PlayerContacts[playerid][i][contactName]);
	    PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][count + 4], TurkishCharFix(mes));
	    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_list[playerid][count + 4]);

        PhoneInfo[playerid][phoneListed][count] = i;

		if(count++ >= 8)
			break;
	}

	SetPVarInt(playerid, #contacts_list, list);
	return 1;
}

stock Phone_GPS(playerid, list = -1)
{
    if(list == -1)
	{
	    for(new i; i != 13;i++) PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i]);
	    PhoneInfo[playerid][phoneGPS] = 0;
	    return 1;
	}
    PhoneInfo[playerid][phoneGPS] = 1;

	new count,
		mes[MAX_PLAYER_NAME + 4];

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][0], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][0]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][1]);

    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][2]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][3], "-GPS-");
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][3]);

	for(new i; i != 9;i++)
	{
 		PhoneInfo[playerid][phoneListed][i] = -1;
  		PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i + 4]);
 	}

	for(new i = list * 9; i != sizeof(gps_location); i++)
	{
		format(mes, sizeof(mes), "%i. %s", i+1, gps_location[i][gpsName]);
	    PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][count + 4], mes);
	    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_list[playerid][count + 4]);

        PhoneInfo[playerid][phoneListed][count] = i;

		if(count++ >= 8)
			break;
	}

	SetPVarInt(playerid, #contacts_list, list);
	return 1;
}

stock Phone_History(playerid, list = -1)
{
	if(list == -1)
	{
	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][0]);
	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][1]);
	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][2]);

	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][13]);
	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][14]);
	    PlayerTextDrawHide(playerid, TD_iphone_list[playerid][15]);
	    PhoneInfo[playerid][phoneHistory] = 0;
	    return 1;
	}

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `history_calls` WHERE `to_number` = %i OR `from_number` = %i ORDER BY `id` DESC", PlayerInfo[playerid][pNumber], PlayerInfo[playerid][pNumber]);
	mysql_tquery(dbHandle, query, "ShowPhoneHistory", "ii", playerid, list);
	return 1;
}

forward ShowPhoneHistory(playerid, list);
public ShowPhoneHistory(playerid, list)
{
    PhoneInfo[playerid][phoneHistory] = 1;

	new
		count,
		mes[256],
		rows = cache_num_rows(),
		to_name[MAX_PLAYER_NAME],
		from_name[MAX_PLAYER_NAME],
		to_number,
		date_hour[24],
		date_month[24],
		time;


    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][0], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][0]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][1]);

    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][2]);

	if(!rows || rows < (list * 3))
	    return 1;

	for(new i; i != 3;i++)
	{
 		PhoneInfo[playerid][phoneListed][i] = -1;
  		PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i + 13]);
 	}

	for(new i = list * 3; i != rows; i++)
	{

	    cache_get_value_int(i, "to_number", to_number);
        cache_get_value(i, "to_name", to_name);
        cache_get_value(i, "from_name", from_name);
        cache_get_value(i, "date_hour", date_hour);
        cache_get_value(i, "date_month", date_month);
		cache_get_value_int(i, "time", time);

		format(mes, sizeof(mes), "Tarih: %s    %s~n~%s~n~~n~%s~n~", date_hour, date_month, (to_number == PlayerInfo[playerid][pNumber])?("Gelen arama"):("Giden arama"), (to_number == PlayerInfo[playerid][pNumber])?(to_name):(from_name));
		if(to_number == PlayerInfo[playerid][pNumber] && time == 0)
		{
		    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 13], -1523963137);
		    strcat(mes, "Cevapsiz arama");
		}
		else
		{
		    format(mes, sizeof(mes), "%sCagri suresi: %s", mes, ConvertSecond(time));
		    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 13], 8388863);
		}
	    PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][count + 13], TurkishCharFix(mes));
        PlayerTextDrawShow(playerid, TD_iphone_list[playerid][count + 13]);

        cache_get_value_int(i, "id", PhoneInfo[playerid][phoneListed][count]);

        count++;
		if(count >= 3)
			break;
	}
	SetPVarInt(playerid, #contacts_list, list);
	return 1;
}

this::ShowHistoryInfo(playerid)
{
    if (!cache_num_rows())
    	return 1;

	new
		mes[256],
		to_name[MAX_PLAYER_NAME],
		from_name[MAX_PLAYER_NAME],
		to_number,
		from_number,
		date_hour[24],
		date_month[24],
		time
	;

    cache_get_value_int(0, "to_number", to_number);
    cache_get_value(0, "to_name", to_name);

	cache_get_value_int(0, "from_number", from_number);
    cache_get_value(0, "from_name", from_name);

	cache_get_value(0, "date_hour", date_hour);
 	cache_get_value(0, "date_month", date_month);
    cache_get_value_int(0, "time", time);

	new callstatus[70],
		numberstatus[55];

	if (time == 0)
	{
		if (to_number == PlayerInfo[playerid][pNumber])
		{
			format(callstatus, sizeof(callstatus), "%s\t\t{c12a2a}Cevapsýz çaðrý\t\t{FFFFFF}-", date_hour);
			format(numberstatus, sizeof(numberstatus), "%s", from_name);
			if (from_number != strval(numberstatus))
				format(numberstatus, sizeof(numberstatus), "%s (%i)", numberstatus, from_number);
		}
		else
		{
			format(callstatus, sizeof(callstatus), "%s\t\t{c12a2a}Ýptal edilen çaðrý\t\t{FFFFFF}-", date_hour);
			format(numberstatus, sizeof(numberstatus), "%s", to_name);
			if (to_number != strval(numberstatus))
				format(numberstatus, sizeof(numberstatus), "%s (%i)", numberstatus, to_number);
		}
	}
	else
	{
		if (to_number == PlayerInfo[playerid][pNumber])
		{
			format(callstatus, sizeof(callstatus), "%s\t\t{a9c4e4}Gelen{FFFFFF}\t\t%s", date_hour, ConvertSecond(time));
			format(numberstatus, sizeof(numberstatus), "%s", from_name);
			if (from_number != strval(numberstatus))
				format(numberstatus, sizeof(numberstatus), "%s (%i)", numberstatus, from_number);
		}
		else
		{
			format(callstatus, sizeof(callstatus), "%s\t\t{a9c4e4}Giden{FFFFFF}\t\t%s", date_hour, ConvertSecond(time));
			format(numberstatus, sizeof(numberstatus), "%s", to_name);
			if (to_number != strval(numberstatus))
				format(numberstatus, sizeof(numberstatus), "%s (%i)", numberstatus, to_number);
		}
	}

	format(mes, sizeof(mes), "Telefon:{FFFFFF} %s\n\n%s\n{FFFFFF}%s", numberstatus, date_month, callstatus);
	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Çaðrý bilgileri", mes, "X", "");
	return 1;
}

stock Phone_SMS(playerid, list = -1)
{
	if(list == -1)
	{
	    for(new i; i != 13;i++) PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i]);
	    PhoneInfo[playerid][phoneSMS] = 0;
	    return 1;
	}

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `sms` WHERE `to_number`='%i' AND `read`!='-1' ORDER BY `id` DESC", PlayerInfo[playerid][pNumber]);
	mysql_tquery(dbHandle, query, "ShowPhoneSMS", "ii", playerid, list);
	return 1;
}

stock Phone_SMS_Info(playerid, sms = -1)
{
	if(sms == -1)
	{
	    PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][0]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][1]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][2]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][3]);
		PlayerTextDrawHide(playerid, TD_iphone_contact[playerid][4]);
		DeletePVar(playerid, #select_sms);
	    return 1;
	}

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `read`=1 WHERE `id` = %i", sms);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `sms` WHERE `id` = %i", sms);
	mysql_tquery(dbHandle, query, "ShowPhoneSMSInfo", "ii", playerid, sms);
	return 1;
}

this::ShowSMS(playerid)
{
	if (!cache_num_rows())
	{
	    pc_cmd_telefon(playerid, "");
	    return SendErrorMessage(playerid, "Mesaj bulunamadý.");
	}

	new
		from_name[24],
		to_name[24],
	    from_number,
		to_number,
	    date[30],
	    text[256],
	    mes[500]
	;

    cache_get_value_int(0, "from_number", from_number);
	cache_get_value(0, "from_name", from_name);
	cache_get_value_int(0, "to_number", to_number);
	cache_get_value(0, "to_name", to_name);
	cache_get_value(0, "date", date);
	cache_get_value(0, "text", text);

	if (from_number == PlayerInfo[playerid][pNumber])
	{
		if (to_number == strval(to_name))
		{
			format(mes, sizeof(mes), "{a9c4e4}Alýcý:\t\t\t{ffffff}%s\n\
			{a9c4e4}Tarih:\t\t\t{ffffff}%s\n\n", to_name, date);
		}
		else
		{
			format(mes, sizeof(mes), "{a9c4e4}Alýcý:\t\t\t{ffffff}%s (%i)\n\
			{a9c4e4}Tarih:\t\t\t{ffffff}%s\n\n", to_name, to_number, date);
		}
	}
	else
	{
		if (from_number == strval(from_name))
		{
			format(mes, sizeof(mes), "{a9c4e4}Gönderen:\t\t{ffffff}%s\n\
			{a9c4e4}Tarih:\t\t\t{ffffff}%s\n\n", from_name, date);
		}
		else
		{
			format(mes, sizeof(mes), "{a9c4e4}Gönderen:\t\t{ffffff}%s (%i)\n\
			{a9c4e4}Tarih:\t\t\t{ffffff}%s\n\n", from_name, from_number, date);
		}
	}

	new forward_id, id;
	cache_get_value_int(0, "forward", forward_id);
	cache_get_value_int(0, "id", id);

	if (forward_id)	format(mes, sizeof(mes), "%s%s", mes, TextTabQ(TextTab(text)));
	else 											format(mes, sizeof(mes), "%s%s", mes, TextTab(text));

	SetPVarString(playerid, #sms_number, from_name);
	SetPVarInt(playerid, #select_sms, id);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `read`='1' WHERE `id`=%i", id);
	mysql_tquery(dbHandle, query);

	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Mesaj", mes, "", "Ýptal");

	return 1;
}

forward ShowPhoneSMSInfo(playerid, sms);
public ShowPhoneSMSInfo(playerid, sms)
{
	if(!cache_num_rows())
	    return 1;

    new mes[128],
        name[24],
		from_number,
        date[21];

	cache_get_value(0, "from_name", name);
	cache_get_value(0, "date", date);
	cache_get_value_int(0, "from_number", from_number);

	format(mes, sizeof(mes), "%s~n~(%i)~n~%s", name, from_number, date);
    PlayerTextDrawSetString(playerid, TD_iphone_contact[playerid][0], TurkishCharFix(mes));
    PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][0]);

    PlayerTextDrawSetString(playerid, TD_iphone_contact[playerid][1], "Goster");
	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][1]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][2]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][3]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_contact[playerid][4]);

	SetPVarInt(playerid, #select_sms, sms);
	SetPVarString(playerid, #sms_number, name);
	return 1;
}

forward ShowPhoneSMS(playerid, list);
public ShowPhoneSMS(playerid, list)
{
    PhoneInfo[playerid][phoneSMS] = 1;

	new
		count,
		mes[MAX_PLAYER_NAME + 4],
		rows = cache_num_rows(),
		name[MAX_PLAYER_NAME];


    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][0], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][0]);

	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][1]);

    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][2]);

	PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][3], "Cevapla");
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawShow(playerid, TD_iphone_list[playerid][3]);

	if(!rows || rows < (list * 9))
	    return 1;

	for(new i; i != 9;i++)
	{
 		PhoneInfo[playerid][phoneListed][i] = -1;
  		PlayerTextDrawHide(playerid, TD_iphone_list[playerid][i + 4]);
 	}

	for(new i = list * 9; i != rows; i++)
	{
		new read;
		cache_get_value_int(i, "read", read);
        cache_get_value(i, "from_name", name);

		format(mes, sizeof(mes), "%i. %s", i+1, name);
	    PlayerTextDrawSetString(playerid, TD_iphone_list[playerid][count + 4], mes);

	    if(read == 1)
		    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		else
		    PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][count + 4], 0xFFFF00FF);

		PlayerTextDrawShow(playerid, TD_iphone_list[playerid][count + 4]);

        cache_get_value_int(i, "id", PhoneInfo[playerid][phoneListed][count]);

        count++;
		if(count >= 8)
			break;
	}
	SetPVarInt(playerid, #contacts_list, list);
	return 1;
}