Dialog:MDCSearchPerson(playerid, response, listitem, inputtext[])
{
	if (!response) 
		return 1;

	new 
		userid,
		query[256]
	;

	if (sscanf(inputtext, "u", userid))	
		return Dialog_Show(playerid, MDCSearch, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - �sime G�re Ara", "{B4B5B7}�SME G�RE K��� ARAYIN\n\n�sim Girin:\n\nFormu Doldurun: Ad_Soyad ((veya oyuncu ID))", "Se�", "�ptal");
	
	if (!IsPlayerLogged(userid))
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e' LIMIT 1", inputtext);
		mysql_tquery(dbHandle, query, "MDCSearchPersonInfo", "i", playerid);
		return 1;
	}
	
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i LIMIT 1", PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query, "MDCSearchPersonInfo", "i", playerid);
	return 1;
}

Dialog:MDCSearchVehicleType(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, MDCSearchVehiclePlayer, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ta��t Arama", "{B4B5B7}ARA� HAKKINDA B�LG� ARAYIN\n\n�sim Girin:\n\nFormu Doldurun: Ad_Soyad ((veya oyuncu ID))", "Se�", "Geri D�n");
		}
		case 1:
		{
			Dialog_Show(playerid, MDCSearchVehicleNum, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ta��t Arama", "{B4B5B7}ARA� HAKKINDA B�LG� ARAYIN\n\nPlakay� Giriniz:\n\n(( Ara� Plakas� ))", "Se�", "Geri D�n");
		}
	}

	return 1;
}

Dialog:MDCSearchVehiclePlayer(playerid, response, listitem, inputtext[])
{
	if (!response) 
		return Dialog_Show(playerid, MDCSearchVehicleType, DIALOG_STYLE_TABLIST, "{8D8DFF}MDC  - Ta��t Arama", "Ki�iye G�re Ta��t Arama\nPlakaya G�re Ta��t Arama", "Se�", "Geri D�n");

    new 
		userid,
		query[164]
	;

	if (sscanf(inputtext, "u", userid))	
		return Dialog_Show(playerid, MDCSearch, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ta��t Arama", "{B4B5B7}ARA� HAKKINDA B�LG� ARAYIN\n\n�sim Girin:\n\nFormu Doldurun: Ad_Soyad  ((veya oyuncu ID))", "Se�", "Geri D�n");
	
	SetPVarInt(playerid, #MDC_VEH_BACK, 1);
	MdcInfo[playerid][mdcListPage] = 0;

	if (!IsPlayerLogged(userid))
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `users` WHERE `name` = '%e' LIMIT 1", inputtext);
		mysql_tquery(dbHandle, query, "MDCSearchVehiclesList_GetID", "i", playerid);
		return 1;
	}

	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `owner` = %i AND `registered`=1 LIMIT 3", PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query, "MDCSearchVehiclesList", "i", playerid);
	return 1;
}

Dialog:MDCSearchVehicleNum(playerid, response, listitem, inputtext[])
{
	if (!response)
		return Dialog_Show(playerid, MDCSearchVehicleType, DIALOG_STYLE_TABLIST, "{8D8DFF}MDC  - Ta��t Arama", "Ki�iye G�re Ta��t Arama\nNumaraya G�re Ta��t Arama", "Se�", "Geri D�n");
	
	if (!strlen(inputtext) || strlen(inputtext) > 10)
	{
		PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________"); //������ ������

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
	}

	SetPVarInt(playerid, #MDC_VEH_BACK, 0);

	SetPVarString(playerid, #MDC_VEHICLE_NUM, inputtext);
	PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], inputtext);

	new query[156];
	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `plate` = '%e' AND `registered`=1", inputtext);
	mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);
	return 1;
}

Dialog:MDC_Record(playerid, response, listitem, inputtext[])
{
	if (!response)												return 1;
	if (sscanf(inputtext, "u", pTemp[playerid][pMDCPlayer]))	return Dialog_Show(playerid, MDC_Record, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �ddianame", "{B4B5B7}DOLDURULUYOR\n\n�sim Girin:\n\nFormu Doldurun: Ad_Soyad ((veya oyuncu ID))", "Se�", "�ptal");
	if (!IsPlayerLogged(pTemp[playerid][pMDCPlayer]))			return Dialog_Show(playerid, MDC_Record, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �ddianame", "{B4B5B7}DOLDURULUYOR\n\n�sim Girin:\n\nFormu Doldurun: Ad_Soyad ((veya oyuncu ID))\n"EMBED_RED"This person is not in the database.", "Se�", "�ptal");

	new mes[256];
	format(mes, sizeof(mes), "{B4B5B7}DOLDURULUYOR\n\nSan�k: %s\n\n��lenilen Su�u Giriniz: (( �fade / 128 Karakter))", GetNameEx(pTemp[playerid][pMDCPlayer]));
	Dialog_Show(playerid, MDC_Record2, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - Iddianame", mes, "Giri�", "�ptal");
	return 1;
}

Dialog:MDC_Record2(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
    if (!IsPlayerLogged(pTemp[playerid][pMDCPlayer]))	return 1;
	if (CheckTextDrawString(inputtext))					return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)
	{
	    new mes[256];
		format(mes, sizeof(mes), "{B4B5B7}DOLDURULUYOR\n\nSan�k: %s\n\n��lenilen Su�u Giriniz: (( �fade / 128 Karakter))", GetNameEx(pTemp[playerid][pMDCPlayer]));
		Dialog_Show(playerid, MDC_Record2, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - Iddianame", mes, "Giri�", "�ptal");
		return 1;
	}

    AddCriminalRecord(pTemp[playerid][pMDCPlayer], inputtext, PlayerInfo[playerid][pUsername], PlayerInfo[playerid][pFaction]);
    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[ARANAN] San�k: %s, Davac�: %s, Su�: %s.", GetNameEx(pTemp[playerid][pMDCPlayer]), GetNameEx(playerid), inputtext);
	SendWarningMessage(playerid, "San�k ba�ar�yla arananlar listesine eklendi.");
	pTemp[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
	return 1;
}

Dialog:MDC_Add_Note(playerid, response, listitem, inputtext[])
{
	if (!response)											return 1;
	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)	return Dialog_Show(playerid, MDC_Add_Note, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ara� Kayd� Ekleniyor", "{B4B5B7}ARAC KAYDI EKLENIYOR\n\nNotunuzu Giriniz:", "Tamamla", "Geri");
	if (CheckTextDrawString(inputtext))						return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	new string[7], 
		query[200],
		plates[24];

	GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

	format(string, sizeof(string), "note%i", GetPVarInt(playerid, #MDC_FREE_NOTE));

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `%s` = '%e %s' WHERE `plate` = '%e'", string, inputtext, GetFullDate(), plates);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `plate` = '%e' AND `registered`=1", plates);
	mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);

	return 1;
}

Dialog:MDC_Del_Note(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new string[7], 
		query[200],
		plates[24];

	GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

	format(string, sizeof(string), "note%i", listitem+1);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `%e` = 'None' WHERE `plate` = '%e'", string, plates);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `plate` = '%e' AND `registered`=1", plates);
	mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);

	return 1;
}

Dialog:MDC_ROSTER_CHANGE(playerid, response, listitem, inputtext[])
{
	if (!response)						return 1;
	if (isnull(inputtext))				return Dialog_Show(playerid, MDC_ROSTER_CHANGE, DIALOG_STYLE_INPUT, "Callsign De�i�tir", "{FFFFFF}Yeni callsign giriniz:", "Onayla", "�ptal");
	if (CheckTextDrawString(inputtext))	return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	pc_cmd_ekip(playerid, inputtext);
	MDC_PAGE(playerid, PAGE_ROSTER);
	return 1;
}

Dialog:APB_CREATE_FIRST(playerid, response, listitem, inputtext[])
{
	if (!response)											return DeletePVar(playerid, #MDC_ID);
	if (strlen(inputtext) < 1 || strlen(inputtext) > 23)		return Dialog_Show(playerid, APB_CREATE_FIRST, DIALOG_STYLE_INPUT, "{098d18}APB Olu�turma", "{B4B5B7}��pheli ad�n� girin:\n- Maksimum karakter say�s�: 24", ">>>", "�ptal");
	if (CheckTextDrawString(inputtext))						return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	new apb = GetPVarInt(playerid, #MDC_ID);

	format(ApbInfo[apb][apbOfficer], MAX_PLAYER_NAME, "%s", GetNameEx(playerid));
	format(ApbInfo[apb][apbSuspect], MAX_PLAYER_NAME, "%s", inputtext);
	ApbInfo[apb][apbFaction] = PlayerInfo[playerid][pFaction];
	format(ApbInfo[apb][apbDate], 32, "%s", GetFullDate());
	
	Dialog_Show(playerid, APB_CREATE_SECOND, DIALOG_STYLE_INPUT, "{098d18}APB Olu�turma", "{B4B5B7}��phelinin a��klamas�n� giriniz:\n- Maksimum karakter say�s�: 128", "Tamamla", "Geri D�n");
	return 1;
}

Dialog:APB_CREATE_SECOND(playerid, response, listitem, inputtext[])
{
	if (!response)											return Dialog_Show(playerid, APB_CREATE_FIRST, DIALOG_STYLE_INPUT, "{098d18}APB Olu�turma", "{B4B5B7}��pheli ad�n� girin:\n- Maksimum karakter say�s�: 24", ">>>", "�ptal");
	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)	return Dialog_Show(playerid, APB_CREATE_SECOND, DIALOG_STYLE_INPUT, "{098d18}APB Olu�turma", "{B4B5B7}��phelinin a��klamas�n� giriniz:\n- Maksimum karakter say�s�: 128", "Tamamla", "Geri D�n");
	if (CheckTextDrawString(inputtext))						return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	new apb = GetPVarInt(playerid, #MDC_ID);
	format(ApbInfo[apb][apbCharge], 128, "%s", inputtext);
	
	SendSyntaxMessage(playerid, "Bir APB notu olu�turdun [ID: %i].", apb);
	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s yeni bir APB notu ekledi, numara %i.", GetRankName(playerid), GetNameEx(playerid), apb);
	
	new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `apbs` (faction, charge, suspect, officer, date) VALUES (%i, '%s', '%s', '%s', '%s')", ApbInfo[apb][apbFaction], SQL_ReturnEscaped(ApbInfo[apb][apbCharge]), SQL_ReturnEscaped(ApbInfo[apb][apbSuspect]), GetNameEx(playerid), GetFullDate());
	mysql_tquery(dbHandle, query, "ApbCreate", "i", apb);

	DeletePVar(playerid, #MDC_ID);

	MdcInfo[playerid][mdcPage] = PAGE_NONE;
	Update_MDC(playerid, PAGE_APB);
	MDC_PAGE(playerid, PAGE_APB);
	return 1;
}

Dialog:MDC_APB_SEARCH_NAME(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], inputtext);
	PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
	for(new b = 0; b < 3; b++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
	for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

	SetPVarString(playerid, #MDC_APB_TEXT, inputtext);

	new count,
		string[256];

	for(new i = MAX_APBS-1; i >= 0; i--)
	{
		if (ApbInfo[i][apbOn] != 0 && strfind(ApbInfo[i][apbSuspect], inputtext, true) != -1)
		{
			if (count < 5)
			{
				format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
				PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][count*4+1], string);

				MdcInfo[count][mdcList] = i;

				for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
			}
			count++;
		}
	}

	if (!count)	return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);

	if (count > 5)
	{
		for(new b = 0; b < 3; b++)
		{
			PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
			PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
		}

		count = floatround(float(count)/5.0, floatround_ceil);
		SetPVarInt(playerid, #MAX_MDC_PAGE, count);
		

		format(string, sizeof(string), "1_/_%i", count);
		PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], string);

		SetPVarInt(playerid, #MDC_APB_S, 1);
		MdcInfo[playerid][mdcListPage] = 0;
	}

	return 1;
}

Dialog:MDC_APB_SEARCH_CHARGE(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], inputtext);
	PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
	for(new b = 0; b < 3; b++)
	{
		PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
		PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
	}
	for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

	SetPVarString(playerid, #MDC_APB_TEXT, inputtext);

	new 
		count,
		string[256]
	;

	for(new i = MAX_APBS-1; i >= 0; i--)
	{
		if (ApbInfo[i][apbOn] != 0 && strfind(ApbInfo[i][apbCharge], inputtext, true) != -1)
		{
			if (count < 5)
			{
				format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
				PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][count*4+1], string);

				MdcInfo[count][mdcList] = i;

				for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
			}
			count++;
		}
	}

	if (!count)	return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);

	if (count > 5)
	{
		for(new b = 0; b < 3; b++)
			PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
		
		count = floatround(float(count)/5.0, floatround_ceil);
		SetPVarInt(playerid, #MAX_MDC_PAGE, count);

		format(string, sizeof(string), "1_/_%i", count);
		PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], string);

		SetPVarInt(playerid, #MDC_APB_S, 1);
		MdcInfo[playerid][mdcListPage] = 0;
	}

	return 1;
}

Dialog:MDC_APB_DETAIL(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	Dialog_Show(playerid, MDC_APB_OPTIONS, DIALOG_STYLE_TABLIST, "{098d18}APB D�zenleme", "'��pheli' sat�r�n� d�zenleyin\n'A��klama' sat�r�n� d�zenleyin", "Se�", "Geri D�n");
	return 1;
}

Dialog:MDC_APB_OPTIONS(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		new
			mes[256],
			i_apb = MdcInfo[GetPVarInt(playerid, #MDC_ID)][mdcList]
		;

		format(mes, sizeof(mes), "{a9c4e4}#%i\n\n{a9c4e4}��pheli:{ffffff}\t %s\n{a9c4e4}A��klama:{ffffff}\t\t %s\n\n{a9c4e4}Olu�turan:{ffffff}\t\t %s\n{a9c4e4}Tarih:{ffffff}\t\t\t %s\n", ApbInfo[i_apb][apbID]+90214, ApbInfo[i_apb][apbSuspect], ApbInfo[i_apb][apbCharge], ApbInfo[i_apb][apbOfficer], ApbInfo[i_apb][apbDate]);
		Dialog_Show(playerid, MDC_APB_DETAIL, DIALOG_STYLE_MSGBOX, "{098d18}APB D�zenleme", mes, "D�zenle", "�ptal");
		return 1;
	}

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, APB_EDIT_NAME, DIALOG_STYLE_INPUT, "{098d18}APB D�zenleme", "{B4B5B7}��pheli ad�n� girin:\n- Maksimum karakter say�s�: 24", "Tamamla", "Geri");
		}

		case 1:
		{
			Dialog_Show(playerid, APB_EDIT_CHARGE, DIALOG_STYLE_INPUT, "{098d18}APB D�zenleme", "{B4B5B7}��phelinin a��klamas�n� giriniz:\n- Maksimum karakter say�s�: 128", "Tamamla", "Geri");
		}
	}

	return 1;
}

Dialog:APB_EDIT_NAME(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, MDC_APB_OPTIONS, DIALOG_STYLE_TABLIST, "{098d18}APB D�zenleme", "'��pheli' sat�r�n� d�zenleyin\n'A��klama' sat�r�n� d�zenleyin", "Se�", "Geri D�n");

	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)	Dialog_Show(playerid, APB_EDIT_NAME, DIALOG_STYLE_INPUT, "{098d18}APB D�zenleme", "{B4B5B7}��pheli ad�n� girin:\n- Maksimum karakter say�s�: 24", "Tamamla", "Geri");
	if (CheckTextDrawString(inputtext))						return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	new number = GetPVarInt(playerid, #MDC_ID);

	SendSyntaxMessage(playerid, "APB notunu d�zenlediniz [ID: %i].", number);
	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s %i numaral� APB notunu d�zenledi.", GetRankName(playerid), GetNameEx(playerid), number);
		
	new query[256];
	mysql_format(dbHandle,query, sizeof(query), "UPDATE `apbs` SET `suspect` = '%e' WHERE `id` = %i", SQL_ReturnEscaped(inputtext), ApbInfo[number][apbID]);
	mysql_tquery(dbHandle, query);
	
	DeletePVar(playerid, #MDC_ID);
	return 1;
}

Dialog:APB_EDIT_CHARGE(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, MDC_APB_OPTIONS, DIALOG_STYLE_TABLIST, "{098d18}APB D�zenleme", "'��pheli' sat�r�n� d�zenleyin\n'A��klama' sat�r�n� d�zenleyin", "Se�", "Geri D�n");

	if (strlen(inputtext) < 1 || strlen(inputtext) > 23)	return Dialog_Show(playerid, APB_EDIT_CHARGE, DIALOG_STYLE_INPUT, "{098d18}APB D�zenleme", "{B4B5B7}��phelinin a��klamas�n� giriniz:\n- Maksimum karakter say�s�: 128", "Tamamla", "Geri");
	if (CheckTextDrawString(inputtext))						return SendErrorMessage(playerid, "'~' bu karakter kullan�lamaz.");

	new number = GetPVarInt(playerid, #MDC_ID);

	SendSyntaxMessage(playerid, "APB notunu de�i�tirdiniz [NUMARA: %i].", number);
	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s %i numaral� APB notunu d�zenledi.", GetRankName(playerid), GetNameEx(playerid), number);
		
	new query[128 + 50];
	mysql_format(dbHandle,query, sizeof(query), "UPDATE `apbs` SET `charge` = '%s' WHERE `id` = %i", SQL_ReturnEscaped(inputtext), ApbInfo[number][apbID]);
	mysql_tquery(dbHandle, query);

	DeletePVar(playerid, #MDC_ID);
	return 1;
}
