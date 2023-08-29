CMD:rehbergoster(playerid, params[])
{
    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

    if (PlayerInfo[playerid][pPhoneOff] != 0)
        return SendErrorMessage(playerid, "Telefon kapalý.");

	new userid;
	if (sscanf(params,"u", userid)) 				return SendHelpMessage(playerid, "/rehbergoster [ID / isim]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

	new count;
	for(new i = 0; i < MAX_PLAYER_CONTACTS; i++)
	{
		if (PlayerContacts[playerid][i][contactOn] == 0)
		    continue;

		count++;
		break;
	}

	if (count == 0)
	    return SendErrorMessage(playerid, "Kiþi yok!");


	SendClientMessageEx(userid, COLOR_HELPS, "%s sana kiþilerimin bir listesini gösterdim.", GetNameWithMask(playerid));
   	SendClientMessageEx(playerid, COLOR_HELPS, "%s adlý kiþiye kiþilerinizin listesini gösterdiniz. ", GetNameWithMask(userid));

	count = 0;
	for(new i = 0; i < MAX_PLAYER_CONTACTS; i++)
	{
		if (PlayerContacts[playerid][i][contactOn] == 0)
		    continue;

		count++;
		SendClientMessageEx(userid, COLOR_GRAD2, "%i. %s - telefon numarasý: %i", count, PlayerContacts[playerid][i][contactName], PlayerContacts[playerid][i][contactNumber]);
	}

    new mes[128];
	format(mes, sizeof(mes), "%s %s adlý kiþiye rehberini gösterir.", GetNameWithMask(playerid), GetNameWithMask(userid));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 15.0, 3000);
	return 1;
}

CMD:rehberkisigoster(playerid, params[])
{
    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

    if (PlayerInfo[playerid][pPhoneOff] != 0)
        return SendErrorMessage(playerid, "Telefon kapalý.");

    new userid,
        contact[32];

	if (sscanf(params,"us[32]", userid, contact)) 	return SendHelpMessage(playerid, "/rehberkisigoster [ID / isim] [rehberde kayýtlý isim]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

	new count = -1;
	for(new i = 0; i < MAX_PLAYER_CONTACTS; i++)
	{
		if (PlayerContacts[playerid][i][contactOn] == 0 || !CompareStrings(contact, PlayerContacts[playerid][i][contactName]))
		    continue;

		count = i;

        SendClientMessageEx(userid, COLOR_HELPS, "%s size %s adlý kiþinin bilgilerini gösterdi", GetNameWithMask(playerid), PlayerContacts[playerid][i][contactName]);
   		SendClientMessageEx(playerid, COLOR_HELPS, "%s adlý kiþiye %s adlý kiþinin bilgilerini gösterdin.", GetNameWithMask(userid), PlayerContacts[playerid][i][contactName]);

		SendClientMessageEx(userid, COLOR_GRAD2, "1. %s - telefon numarasý: %i", PlayerContacts[playerid][i][contactName], PlayerContacts[playerid][i][contactNumber]);

        new mes[128];
		format(mes, sizeof(mes), "%s %s adlý kiþiye rehberi gösterir.", GetNameWithMask(playerid), GetNameWithMask(userid));
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 15.0, 3000);
		break;
	}

	if (count == -1)
	    return SendWarningMessage(playerid, "Bu kiþi bulunamadý.");

	return 1;
}

CMD:hoparlor(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");

    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

	if (pTemp[playerid][pCallLine] == INVALID_PLAYER_ID || pTemp[playerid][pCallStatus] != 2)
	    return SendWarningMessage(playerid, "Herhangi bir aramada deðilsin.");

	if (GetPVarInt(playerid, #loud_speak) == 0)
	{
		SetPVarInt(playerid, #loud_speak, 1);
		SM2(playerid, "Hoparlörü açtýnýz.");
	}
	else
	{
		SetPVarInt(playerid, #loud_speak, 0);
		SM2(playerid, "Hoparlörü kapattýnýz.");
	}
	return 1;
}

alias:telefon("telef");
CMD:telefon(playerid, params[])
{
	if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

	if (GetPVarInt(playerid, #pDelay))	return 1;
	if (IsPlayerUseMDC(playerid)) 		return SendErrorMessage(playerid, "MDC açýkken telefonu kullanamazsýn.");

	if (IsPlayerPhoneCreated(playerid))
	{
		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
			pc_cmd_telefonkapat(playerid, "");
			
	    return Phone_Destroy(playerid);
	}

	if(GetPVarInt(playerid, #selfie))
	    pc_cmd_selfie(playerid, "");

	if (pTemp[playerid][pPayphone] != -1)
		return SendErrorMessage(playerid, "Zaten ankesörlü telefon kullanýyorsunuz.");		

	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");		

	Phone_Create(playerid);
	return 1;
}

alias:fare("pc", "imlec");
CMD:fare(playerid, params[])
{
	if (IsPlayerPhoneCreated(playerid)) SelectTextDraw(playerid, COLOR_LIGHTRED);
	else SelectTextDraw(playerid, 255);
	return 1;
}

alias:sms("smsgonder");
CMD:sms(playerid, params[])
{
    if(PlayerInfo[playerid][pInjured] != 0  || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return SCM(playerid, COLOR_GREY, "Bu komutu þu an kullanamazsýnýz.");

    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

    if (PlayerInfo[playerid][pPhoneOff] != 0)
        return SendCellMessage(playerid, "Telefon kapalý.");

	if (PlayerInfo[playerid][pPhoneAirplane] == 1)
	    return SendCellMessage(playerid, "Arama ve SMS yapýlamaz - telefonunuz uçuþ modundadýr.");

	new number_str[24],
	    number,
	    targetid,
	    text[128];

	if (sscanf(params,"s[24]s[128]", number_str, text))
		return SendHelpMessage(playerid, "/sms [telefon numarasý / rehberde kayýtlý isim] [mesaj]");

	number = strval(number_str);

	for(new i = 0; i != MAX_PLAYER_CONTACTS; i++)
    {
        if(PlayerContacts[playerid][i][contactOn] == 0 || strcmp(PlayerContacts[playerid][i][contactName], number_str, true) != 0)
            continue;

        number = PlayerContacts[playerid][i][contactNumber];
        break;
    }

    if (number == PlayerInfo[playerid][pNumber])
    	return SendErrorMessage(playerid, "Kendinize SMS atamazsýnýz.");
    	
    targetid = GetNumberOwner(number);
	if(!IsPlayerLogged(targetid))
	{
	    new query[201];
	    mysql_format(dbHandle, query, sizeof(query), "\
	    SELECT number, (SELECT `contact` FROM `player_contacts` WHERE users.id = player_contacts.userid AND player_contacts.number = '%i') as contact \
 		FROM `users` WHERE `number` = '%i'", PlayerInfo[playerid][pNumber], number);
 		
 		mysql_tquery(dbHandle, query, "OfflineSMS", "iis", playerid, number, text);
	    return 1;
	}

    new find_phone[2] = {0, 0},
		name_playerid[MAX_PLAYER_NAME],
		name_targetid[MAX_PLAYER_NAME];

    for (new i = 0; i != MAX_PLAYER_CONTACTS; i ++)
	{
		if(PlayerContacts[playerid][i][contactOn] != 0 && PlayerContacts[playerid][i][contactNumber] == number)
		{
 			strmid(name_playerid, PlayerContacts[playerid][i][contactName], 0, strlen(PlayerContacts[playerid][i][contactName]), 32);
 			find_phone[0] = 1;
		}
		if(PlayerContacts[targetid][i][contactOn] != 0 && PlayerContacts[targetid][i][contactNumber] == PlayerInfo[playerid][pNumber])
		{
 			strmid(name_targetid, PlayerContacts[targetid][i][contactName], 0, strlen(PlayerContacts[targetid][i][contactName]), 32);
	        find_phone[1] = 1;
		}
	}

	if(!find_phone[0]) format(name_playerid, 24, "%i", number);
	if(!find_phone[1]) format(name_targetid, 24, "%i", PlayerInfo[playerid][pNumber]);

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
	SQL_ReturnEscaped(text),
	month_name[month-1],
	day,
	year,
	hour,
	minute,
    (PlayerInfo[targetid][pPhoneAirplane] == 0 && PlayerInfo[targetid][pPhoneOff] == 0)?(0):(-1));
	mysql_tquery(dbHandle, query);

	if(PlayerInfo[targetid][pPhoneAirplane] == 0 && PlayerInfo[targetid][pPhoneOff] == 0)
	{
		if(PlayerInfo[targetid][pPhoneSound] == 0)
		{
		    pc_cmd_do(targetid, "Telefonuna mesaj bildirim sesi geldi.");
			PlaySound(targetid, 1084);
		}

    	else if(PlayerInfo[targetid][pPhoneSound] == 1)
		{
		    if(0 == IsPlayerPhoneCreated(targetid)) Phone_Create(targetid, 1);
		}	
	}

	if(strlen(text) > MAXLEN)
	{
		new pos = MAXLEN;
		if(pos < MAXLEN-1) pos = MAXLEN;
		if(PlayerInfo[targetid][pPhoneAirplane] == 0 && PlayerInfo[targetid][pPhoneOff] == 0)
		{
			SendClientMessageEx(targetid, COLOR_YELLOWG, "SMS: %.*s ...", pos, text);
			SendClientMessageEx(targetid, COLOR_YELLOWG, "SMS: ... %s Kiþi: %s.", text[pos], name_targetid);
		}
		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %.*s ...", pos, text);
		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: ... %s Kiþi: %s.", text[pos], name_playerid);
	}
	else
	{
	    if(PlayerInfo[targetid][pPhoneAirplane] == 0 && PlayerInfo[targetid][pPhoneOff] == 0)
			SendClientMessageEx(targetid, COLOR_YELLOWG, "SMS: %s Kiþi: %s.", text, name_targetid);

		SendClientMessageEx(playerid, COLOR_YELLOWG, "SMS: %s Kiþi: %s.", text, name_playerid);
	}
	
	pc_cmd_ame(playerid, "birisine SMS atar.");
	return 1;
}

CMD:selfie(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");

    if(!GetPVarInt(playerid, #selfie))
    {
		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || IsPlayerInAnyVehicle(playerid))
		    return SendErrorMessage(playerid, "Þu anda kamerayý kullanamazsýnýz.");

        new Float: x,
			Float: y,
			Float: z,
			Float: new_x,
			Float: new_y,
			Float: radius = 0.9,
			Float: rot;

        TogglePlayerControllable(playerid, 0);

	    GetPlayerPos(playerid, x, y, z);
	    GetPlayerFacingAngle(playerid, rot);
     	new_x = x + radius * floatcos(rot, degrees);
	    new_y = y + radius * floatsin(rot, degrees);

		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
	   	SetPlayerAttachedObject(playerid, ATTACH_HANDS, phone_model[PlayerInfo[playerid][pPhoneModel]], 6, 0.06, 0.01, 0.08, 180.0, 90.0, 0.0);

		SetPlayerCameraPos(playerid, new_x, new_y, z + 0.78);
		SetPlayerCameraLookAt(playerid, x, y, z + 0.60);
	    SetPlayerFacingAngle(playerid, rot -90.0);

		SetPVarFloat(playerid, #selfie_z, 0.60);

		ApplyAnimation(playerid, "PED", "gang_gunstand", 4.1, 1, 1, 1, 1, 1, 1);
  		SetPVarInt(playerid, #selfie, 1);

		SetPlayerArmedWeapon(playerid, 0);

        InfoMSG(playerid, "~y~F8~w~ tusuna basarak ekran goruntusu alabilir, ~y~F7~w~ tusuna basarak sohbeti gizleyebilirsiniz.~n~~r~W, A, S~w~ ve ~r~D~w~ tuslariyla kamerayi kontrol edebilir, ~y~ENTER~w~ tusuyla geri donebilirsiniz.~n~~r~/headmove~w~ komutuyla karakterinizin kafasini sabitleyebilirsiniz.", 5);
		CancelSelectTextDraw(playerid);
		return 1;
 	}
	TogglePlayerControllable(playerid, 1);
 	SetCameraBehindPlayer(playerid);

	RemovePlayerAttachedObject(playerid, ATTACH_HANDS);

	if(IsPlayerPhoneCreated(playerid))
 		SetPlayerAttachedObject(playerid, ATTACH_HANDS, phone_model[PlayerInfo[playerid][pPhoneModel]], 6, 0.111, -0.000999, 0.0, 77.9, -171.6, -3.40001, 1.0, 1.0, 1.0);

	ApplyAnimation(playerid, "PED", "ATM", 4.1, 0, 1, 1, 0, 1, 1);
 	DeletePVar(playerid, #selfie);
	return 1;
}

alias:telefonac("tac");
CMD:telefonac(playerid, params[])
{
    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

    new targetid = pTemp[playerid][pCallLine],
        mes[128];

    if(pTemp[playerid][pCallStatus] == 2)
        return SendCellMessage(playerid, "Baþkasýyla konuþuyorsun.");

	if(targetid == INVALID_PLAYER_ID || pTemp[playerid][pCallStatus] != 1)
        return SendCellMessage(playerid, "Geçersiz numara.");

	if(pTemp[targetid][pCallLine] != playerid)
	    return SendErrorMessage(playerid, "Bir hata oluþtu.");

	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);

    pTemp[playerid][pCallIncoming] = 1;
    pTemp[targetid][pCallIncoming] = 0;

    pTemp[playerid][pCallStatus] = 2;
    pTemp[targetid][pCallStatus] = 2;

    pTemp[playerid][pCallTime] = 0;
    pTemp[targetid][pCallTime] = 0;

    if(0 == IsPlayerPhoneCreated(targetid))
	    Phone_Create(targetid);
	else
	{
	    Phone_Menu(targetid, 0);
	    Phone_Block(targetid, 0);

	   	format(mes, sizeof(mes), "%s~n~%s", pTemp[targetid][pCallName], ConvertSecond(pTemp[targetid][pCallTime]));
   		PlayerTextDrawSetString(targetid, TD_iphone_name[targetid], mes);
	   	PlayerTextDrawShow(targetid, TD_iphone_name[targetid]);
	}

    if(0 == IsPlayerPhoneCreated(playerid))
	    Phone_Create(playerid);
	else
	{
	    Phone_Menu(playerid, 0);
	    Phone_Block(playerid, 0);

	   	format(mes, sizeof(mes), "%s~n~%s", pTemp[playerid][pCallName], ConvertSecond(pTemp[playerid][pCallTime]));
   		PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], mes);
	   	PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);

	   	PlayerTextDrawShow(playerid, TD_iphone_button[playerid][0]);
  		PlayerTextDrawShow(playerid, TD_iphone_button[playerid][1]);

  		PlayerTextDrawHide(playerid, TD_iphone_button[playerid][2]);
  		PlayerTextDrawHide(playerid, TD_iphone_button[playerid][3]);
  		PlayerTextDrawHide(playerid, TD_iphone_button[playerid][4]);
  		PlayerTextDrawHide(playerid, TD_iphone_button[playerid][5]);
	}

	SCM(targetid, -1, "> Kiþi telefonu açtý.");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	return 1;
}

alias:telefonkapat("tkapat", "/telkapat");
CMD:telefonkapat(playerid, params[])
{
    if(PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Telefonunuz bulunmuyor.");

	if(pTemp[playerid][pEmergency])
	{
	    pTemp[playerid][pEmergency] = 0;
	    SCM(playerid, -1, "> Görüþmeyi sonlandýrdýnýz.");

	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
	    return 1;
	}

	if(pTemp[playerid][pCallLine] == INVALID_PLAYER_ID)
	    return 1;

	new targetid = pTemp[playerid][pCallLine];

	if (!pTemp[playerid][pEmergency] && pTemp[playerid][pCallStatus] == 2)
	{
	    SendCellMessage(playerid, "%s kiþisiyle görüþmeni sonlandýrdýn.", pTemp[playerid][pCallName]);
	    SendCellMessage(targetid, "Kýsa bip sesleri duyuldu.");
 	}

	else if (!pTemp[playerid][pEmergency] && pTemp[playerid][pCallStatus] == 1)
	{
	    SendCellMessage(targetid, "Aradýðýnýz numara çaðrýyý reddetti.");
	    SendCellMessage(playerid, "Telefon çaðrýsý sona erdi.");

 	}
	CancelCall(playerid);
	return 1;
}

CMD:ara(playerid, params[])
{
    if(PlayerInfo[playerid][pInjured] != 0  || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return SCM(playerid, COLOR_GREY, "Bu durumdayken arama yapamazsýn.");
		
    if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

    if (PlayerInfo[playerid][pPhoneOff] != 0)
        return SendCellMessage(playerid, "Telefon kapalý.");

	if (PlayerInfo[playerid][pPhoneAirplane] == 1)
	    return SendCellMessage(playerid, "Arama ve SMS yapýlamaz - telefonunuz uçuþ modundadýr.");

    if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
	    return SendCellMessage(playerid, "Bitirilmemiþ bir aramanýz var. Kapatmak için '/tkapat' yazýn.");

	if (pTemp[playerid][pPayphone] != -1)
		return SendErrorMessage(playerid, "Zaten ankesörlü telefon kullanýyorsunuz.");

	new number_str[32],
	    number,
	    targetid,
	    mes[52];

	if (sscanf(params,"s[32]", number_str))
	{
		SendHelpMessage(playerid, "/ara [numara / rehberde kayýtlý isim / liste]");

		if (CompareStrings(number_str, "liste"))
		{
			SM2(playerid, "Acil Durum: 911");
			//SM2(playerid, "Polis: 991");
			SM2(playerid, "Taksi: 555");
			//SM2(playerid, "Tamirhane: 444");
		}
		return 1;
	}

	number = strval(number_str);

	for(new i = 0; i != MAX_PLAYER_CONTACTS; i++)
    {
        if(PlayerContacts[playerid][i][contactOn] == 0 || strcmp(PlayerContacts[playerid][i][contactName], number_str, true) != 0)
            continue;

        number = PlayerContacts[playerid][i][contactNumber];
        break;
    }

	if((number == 544 || number == 555 || number == 911 || number == 991) && PlayerInfo[playerid][pJailed] == 0 && PlayerInfo[playerid][pAJailed] == 0)
	{
	    if(IsPlayerPhoneCreated(playerid))
	    	Phone_Destroy(playerid);

	    pTemp[playerid][pEmergency] = number;
	    switch(number)
	    {
	        case 444: SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Merhaba, Liberty City Tamirci Servisi, size nasýl yardýmcý olabiliriz?");
	        case 555: SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Alo, taksi servisini aradýnýz, sizi nereden alalým?");
	        case 911:
			{
				SCM(playerid, COLOR_YELLOWG, "911 Operatörü (telefon): Acil servise hoþ geldiniz. Hangi hizmetlere ihtiyacýnýz var? Rakamý tuþlayýn.");
			    SCM(playerid, COLOR_YELLOWG, "(1) Polis, (2) Ambulans ve Ýtfaiye, (3) Her ikisi. (( Rakamý sohbete yazýn ))");	
			}
	        case 991: SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Polis hattýný aradýnýz, size nasýl yardýmcý olabilirim?");
	    }

	    pc_cmd_ame(playerid, "telefonla birisini arar.");
		SetPlayerAttachedObject(playerid, ATTACH_HANDS, phone_model[PlayerInfo[playerid][pPhoneModel]], 6, 0.111, -0.000999, 0.0, 77.9, -171.6, -3.40001, 1.0, 1.0, 1.0);
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	    return 1;
	}

	if((targetid = GetNumberOwner(number)) == INVALID_PLAYER_ID)
	{
	    SCM(playerid, -1, "Geçersiz numara.");
		return SCM(playerid, -1, "Hat düþtü.");
	}

    if (targetid == playerid)
    	return SendErrorMessage(playerid, "Kendinizi arayamazsýnýz.");

	if(pTemp[targetid][pCallLine] != INVALID_PLAYER_ID || pTemp[targetid][pEmergency])
	    return SendErrorMessage(playerid, "Kiþi þu an baþkasýyla görüþüyor.");

    if(PlayerInfo[targetid][pPhoneOff] != 0 || PlayerInfo[targetid][pPhoneAirplane] != 0)
        return SendErrorMessage(playerid, "Kiþinin telefon sinyali alýnamadý.");

    new find_phone[2] = {0, 0};
    for (new i = 0; i != MAX_PLAYER_CONTACTS; i ++)
	{
		if(PlayerContacts[playerid][i][contactOn] != 0 && PlayerContacts[playerid][i][contactNumber] == number)
		{
 			strmid(pTemp[playerid][pCallName], PlayerContacts[playerid][i][contactName], 0, strlen(PlayerContacts[playerid][i][contactName]), 32);
 			find_phone[0] = 1;
		}
		if(PlayerContacts[targetid][i][contactOn] != 0 && PlayerContacts[targetid][i][contactNumber] == PlayerInfo[playerid][pNumber])
		{
 			strmid(pTemp[targetid][pCallName], PlayerContacts[targetid][i][contactName], 0, strlen(PlayerContacts[targetid][i][contactName]), 32);
	        find_phone[1] = 1;
		}
	}

	if(!find_phone[0]) format(pTemp[playerid][pCallName], 24, "%i", number);
	if(!find_phone[1]) format(pTemp[targetid][pCallName], 24, "%i", PlayerInfo[playerid][pNumber]);


	pTemp[playerid][pCallLine] = targetid;
	pTemp[playerid][pCallStatus] = 0;
	pTemp[playerid][pCallTime] = 0;
	//
	pTemp[targetid][pCallLine] = playerid;
	pTemp[targetid][pCallStatus] = 1;
	pTemp[targetid][pCallTime] = 0;

	if(0 == IsPlayerPhoneCreated(targetid))
	    Phone_Create(targetid, 1);
	else
	{
	    Phone_Menu(targetid, 0);
	    Phone_Block(targetid, 0);
	    Phone_Contacts(targetid);
	    Phone_SMS(targetid);
	    Phone_History(targetid);
	    Phone_Contact_Info(targetid);
	    Phone_Setting(targetid, 0);
	    Phone_Keypad(targetid, 0);

	    format(mes, sizeof(mes), "%s~n~hatta", pTemp[targetid][pCallName]);

		PlayerTextDrawSetString(targetid, TD_iphone_name[targetid], mes);
	   	PlayerTextDrawShow(targetid, TD_iphone_name[targetid]);

	   	PlayerTextDrawShow(targetid, TD_iphone_button[targetid][2]);
	    PlayerTextDrawShow(targetid, TD_iphone_button[targetid][3]);
	    PlayerTextDrawShow(targetid, TD_iphone_button[targetid][4]);
	    PlayerTextDrawShow(targetid, TD_iphone_button[targetid][5]);
	}

    if(0 == IsPlayerPhoneCreated(playerid))
	    Phone_Create(playerid, 1);
	else
	{
	    Phone_Menu(playerid, 0);
	    Phone_Block(playerid, 0);
	    Phone_Contacts(playerid);
	    Phone_SMS(playerid);
	    Phone_History(playerid);
	    Phone_Contact_Info(playerid);
	    Phone_SMS_Info(playerid);
	    Phone_Setting(playerid, 0);
	    Phone_Keypad(playerid, 0);

	    format(mes, sizeof(mes), "%s~n~araniyor...", pTemp[playerid][pCallName]);

		PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], mes);
	   	PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);

	   	PlayerTextDrawShow(playerid, TD_iphone_button[playerid][0]);
  		PlayerTextDrawShow(playerid, TD_iphone_button[playerid][1]);
	}

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);

	PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

	if(PlayerInfo[targetid][pPhoneSound] == 0)
 		PlayerPlaySound(targetid, phone_ringtons[PlayerInfo[targetid][pPhoneRingtone]], 0.0, 0.0, 0.0);


    pc_cmd_my(targetid, "telefonu çalýyor.");
	SendCellMessage(targetid, "Not: Telefonu /telefon ile çýkarýn. Ýmleci kullanmak için /fare.");
	SendCellMessage(targetid, "Aramayý cevaplamak için /tac kullanýn.");

	pc_cmd_ame(playerid, "telefonla birisini arar.");
	CancelSelectTextDraw(playerid);
	return 1;
}

CMD:telefonat(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");

 	if (PlayerInfo[playerid][pNumber] == 0)
		return SendErrorMessage(playerid, "Bir telefona sahip deðilsin.");

	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency] != 0)
	    return SendErrorMessage(playerid, "Aramayý sonlandýr. - /tkapat.");

	if (IsPlayerPhoneCreated(playerid))
		Phone_Destroy(playerid);

    new query[256];
   	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `sms` WHERE `to_number` = %i", PlayerInfo[playerid][pNumber]);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `player_contacts` WHERE `userid` = %i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query);

	for(new i; i != MAX_PLAYER_CONTACTS; i++)
	{
	    PlayerContacts[playerid][i][contactNumber] = 0;
		PlayerContacts[playerid][i][contactOn] = 0;
		PlayerContacts[playerid][i][contactID] = 0;
	}

	SendCellMessage(playerid, "Cep telefonunu çöpe attýn.");
	SendHelpMessage(playerid, "Telefonunuzu tekrar kullanabilmeniz için - yeni bir SIM kart satýn alýn.");

	SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s telefonunu çöpe atar.", GetNameWithMask(playerid));

    PlayerInfo[playerid][pBurnerTelefon] = 0;
	PlayerInfo[playerid][pNumber] = 0;
	PlayerInfo[playerid][pPhoneModel] = 0;
	return 1;
}
