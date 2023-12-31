Dialog:LSPDElevator(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2268.0640,2448.2449,3.5313) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2781.0559,-1056.2823,1028.4969) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2874.6665,-940.6707,1035.9259) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2872.8813,-1072.9934,1037.1782)) return 1;
		
	new world_list[] = {2, 1, 2, 3};

	switch(listitem)
	{
	    case 0: SetPlayerPosEx(playerid, 2268.0640,2448.2449,3.5313), SetPlayerFacingAngle(playerid, 181.2476);
	    case 1: SetPlayerPosEx(playerid, 2780.9036,-1056.2358,1028.4969), SetPlayerFacingAngle(playerid, 87.9492);
	    case 2: SetPlayerPosEx(playerid, 2873.9063,-940.8126,1035.9259), SetPlayerFacingAngle(playerid, 84.3340);
	    case 3: SetPlayerPosEx(playerid, 2872.7168,-1072.2004,1037.1770), SetPlayerFacingAngle(playerid, 0.2384);
	}

	SetWorld(playerid, world_list[listitem]);
	SetInterior(playerid, (listitem == 0)?(0):(1));
	return 1;
}

Dialog:MDCCall(playerid, response, listitem, inputtext[])
{
	if (!response)						return 1;
    if (!IsPlayerFactionPolice(playerid) &&
		!IsPlayerFactionMedic(playerid) &&
		!IsPlayerFactionFire(playerid))	return 1;

	new mes[512], count, type = (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid))?(2):(1);

    for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
	{
	    if (!CallInfo[i][callExists]) continue;
		if (CallInfo[i][callType] != 3) {
			if (CallInfo[i][callType] != type) continue;
		}

		if (listitem == count)
		{
			new statusmes[65];
			if (CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
			else format(statusmes, sizeof(statusmes), "{A9C4E4}�a�r� kabul edilmemi�{B4B5B7}");

			format(mes, sizeof(mes), "{B4B5B7}911-CAGRI BILGISI - #%i\n\n\
            						Arayan:\t\t%s\n\
            						Numara:\t%i\n\
           							Durum:\t\t%s\n\
            						Lokasyon:\t%s\n\
            						Tarih:\t\t\t%s\n\n\
									Stat�:\t\t\t%s\n\
            						�a�r� %i kez cevapland�", 
			i+1, CallInfo[i][callName], CallInfo[i][callPhone], CallInfo[i][callText], CallInfo[i][callLocation], CallInfo[i][callDate], statusmes, CallInfo[i][callAccept]);
			
			Dialog_Show(playerid, MDCCall2, DIALOG_STYLE_MSGBOX, "{8D8DFF}MDC - �a�r� Bilgilendirmesi", mes, "Ayarlar", "Geri D�n");
			SetPVarInt(playerid, #last_call, i);
		    return 1;
		}
		count++;
	}
	return 1;
}

Dialog:MDCCall2(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    Dialog_Show(playerid, MDCCallRespond, DIALOG_STYLE_LIST, "{8D8DFF}MDC - �a�r� Bilgilendirmesi", "- Acil �a�r�y� kabul et\n- �a�r�y� sil", "Se�", "Geri D�n");
	return 1;
}

Dialog:MDCCallRespond(playerid, response, listitem, inputtext[])
{
	if (!response) 																													
		return 1;

    if (!IsPlayerFactionPolice(playerid) &&
		!IsPlayerFactionMedic(playerid) &&
		!IsPlayerFactionFire(playerid))
		return 1;

	new type = (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid))? (2) : (1), 
		id = GetPVarInt(playerid, #last_call);

    if (!CallInfo[id][callExists]) return 1;
	if (CallInfo[id][callType] != 3) {
		if (CallInfo[id][callType] != type) return 1;
	}

	if (!listitem)
	{
		if (pTemp[playerid][pPatrol])	SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s [%s] 911 acil �a�r�s�n� kabul etti. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], id+1);
		else							SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s 911 acil �a�r�s�n� kabul etti. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), id+1);
		
		if (pTemp[playerid][pPatrol])    format(CallInfo[id][callAcceptBy], 64, "%s (%s) taraf�ndan ilgileniliyor", GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName]);
        else                             format(CallInfo[id][callAcceptBy], 64, "%s taraf�ndan ilgileniliyor", GetNameEx(playerid));
		
		Waypoint_Set(playerid, CallInfo[id][callPosX],CallInfo[id][callPosY],CallInfo[id][callPosZ], 3.0);

	    CallInfo[id][callAccept]++;
		pTemp[playerid][pPoliceCalls]++;

		MDC_PAGE(playerid, PAGE_CALLS);
	}
	else
	{
		SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s 911 acil �a�r�s�n� kald�rd� #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), id+1);
		
		SendWarningMessage(playerid, "�a�r� [ID: %i] kald�r�ld�.", id+1);
	    CallInfo[id][callExists] = 0;
 		CallInfo[id][callType] = 0;
		CallInfo[id][callAccept] = 0;

		MDC_PAGE(playerid, PAGE_MAIN);
	}
	
	return 1;
}

/*Dialog:MDCSearch(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    new userid;
	if (sscanf(inputtext, "u", userid))	return Dialog_Show(playerid, MDCSearch, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - ����� �� �����", "{B4B5B7}����� �� �����\n\n������� ���:\n\n����� �����: ���_������� (( ��� ID ������ ))", "Done", "�ptal");
	if (!IsPlayerLogged(userid))			return Dialog_Show(playerid, MDCSearch, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - ����� �� �����", "{B4B5B7}����� �� �����\n\n������� ���:\n\n����� �����: ���_������� (( ��� ID ������ ))\n"EMBED_RED"������ ������� ����������� � ���� ������.", "Done", "�ptal");

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid` = %i", PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query, "PersonInfo", "ii", playerid, userid);
	return 1;
}*/

Dialog:MDCRecord(playerid, response, listitem, inputtext[])
{
	if (!response)												return 1;
	if (sscanf(inputtext, "u", pTemp[playerid][pMDCPlayer]))	return SendErrorMessage(playerid, "Oyuncu aktif de�il!");
	if (!IsPlayerLogged(pTemp[playerid][pMDCPlayer]))			return SendErrorMessage(playerid, "Eri�im i�in yetkiniz yok!");

	new mes[256];
	format(mes, sizeof(mes), "{B4B5B7}SU�\n\nSan�k: %s\n\nSu�lama metnini giriniz: (( Su� / 128 karakter))", GetNameEx(pTemp[playerid][pMDCPlayer]));
	Dialog_Show(playerid, MDCRecord2, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �ddianame", mes, "Gir", "�ptal");
	return 1;
}

Dialog:MDCRecord2(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
    if (!IsPlayerLogged(pTemp[playerid][pMDCPlayer]))	return 1;

	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)
	{
	    new mes[256];
		format(mes, sizeof(mes), "{B4B5B7}SU�\n\nSan�k: %s\n\nSu�lama metnini giriniz: (( Su� / 128 karakter))", GetNameEx(pTemp[playerid][pMDCPlayer]));
		Dialog_Show(playerid, MDCRecord2, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �ddianame", mes, "Gir", "�ptal");
		return 1;
	}

    AddCriminalRecord(pTemp[playerid][pMDCPlayer], inputtext, PlayerInfo[playerid][pUsername], PlayerInfo[playerid][pFaction]);
    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[ARANIYOR] San�k: %s, Savc�: %s, Su�: %s.", GetNameEx(pTemp[playerid][pMDCPlayer]), GetNameEx(playerid), inputtext);
	SendWarningMessage(playerid, "San�k ba�ar�l� bir �ekilde arananlar listesine eklendi.");
	pTemp[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
	return 1;
}

Dialog:MDCAddWarn(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new userid;

    //if (sscanf(inputtext, "u", userid))	return Dialog_Show(playerid, MDCAddWarn, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �������������� �� ��������", "{B4B5B7}�������� �������������� �� ��������\n\n������� ���:\n\n(( ���_������� / ID ������ ))\n"EMBED_RED"������ ������� ����������� � ���� ������.", "Done", "�ptal");
	//if (!IsPlayerLogged(userid))			return Dialog_Show(playerid, MDCAddWarn, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �������������� �� ��������", "{B4B5B7}�������� �������������� �� ��������\n\n������� ���:\n\n(( ���_������� / ID ������ ))\n"EMBED_RED"������ ������� ����������� � ���� ������.", "Done", "�ptal");
    //if (!PlayerInfo[userid][pCarLic])	return Dialog_Show(playerid, MDCAddWarn, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - �������������� �� ��������", "{B4B5B7}�������� �������������� �� ��������\n\n������� ���:\n\n(( ���_������� / ID ������ ))\n"EMBED_RED"� ������� �������� ����������� �������� �� ��������.", "Done", "�ptal");

	new mes[128];
	format(mes, sizeof(mes), ", %s adl� ki�inin ehliyetine uyar� verir.", GetNameEx(userid));
	pc_cmd_me(playerid, mes);

	SendSyntaxMessage(playerid, "%s adl� ki�inin ehliyetine uyar� eklediniz.", GetName(userid));

	PlayerInfo[userid][pDriveWarns]++;
	SQL_SetInteger("users", "drivewarns", PlayerInfo[userid][pDriveWarns], PlayerInfo[userid][pID]);

	if (PlayerInfo[userid][pDriveWarns] >= 3)
	{
		SendSyntaxMessage(playerid, "%s adl� ki�inin ehliyetinde 3 uyar� oldu�u i�in otomatik olarak ehliyeti iptal edildi.", GetNameEx(userid));
		PlayerInfo[userid][pDriveWarns] = 0;
		PlayerInfo[userid][pCarLic] = 0;

		SQL_SetInteger("users", "drivewarns", PlayerInfo[userid][pDriveWarns], PlayerInfo[userid][pID]);
		SQL_SetInteger("users", "carlic", PlayerInfo[userid][pCarLic], PlayerInfo[userid][pID]);
	}
	return 1;
}

/*Dialog:MDCVehicle(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
	if (!strlen(inputtext) || strlen(inputtext) > 23)	return Dialog_Show(playerid, MDCVehicle, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - ����� ����������", "{B4B5B7}����� ���������� �� ����������\n\n������� �������� ����:\n\n(( ����� �� ))", "Done", "Geri D�n");
	    
	new query[156];
	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id =cars.owner) as ownername FROM `cars` WHERE `plate` = '%e' AND `registered`=1", inputtext);
	mysql_tquery(dbHandle, query, "OnCheckNumber", "d", playerid);
	return 1;
}*/

Dialog:MDCWeaponPlayer(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowWeaponLicense(playerid, GetPVarInt(playerid, #weapon_list));
	    
	if (listitem == 5)
	{
	    if (IsPlayerFactionPolice(playerid))	 return SendErrorMessage(playerid, "Bu i�lemi LSPD �yelerine ger�ekle�tiremezsiniz.");
		if (PlayerInfo[playerid][pAuthwep] != 1) return SendErrorMessage(playerid, "Silah ruhsat�n� iptal etme yetkin yok.");
		    
		new userid;

	    if ((userid = GetIDByID(pTemp[playerid][pMDCWepPlayer])) != INVALID_PLAYER_ID)
		{
		    SendSyntaxMessage(userid, "%s %s silah ruhsat�n� iptal etti.", GetRankName(playerid), GetNameEx(playerid));
			PlayerInfo[userid][pWepLic] = 0;
			PlayerInfo[userid][pWepWarns] = 0;
			PlayerInfo[userid][pWepCount] = 0;
		}
	    new query[156];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `weplic`='0',`wepwarns`='0',`wep_officer`='-',`wep_data`='-',`wep_price`='0',`wep_count`='0' WHERE `id` = %i", pTemp[playerid][pMDCWepPlayer]);
		mysql_tquery(dbHandle, query);
		
		SendSyntaxMessage(playerid, "%s silah ruhsat�n� iptal ettin.", pTemp[playerid][pMDCWepName]);
	    return 1;
	}

	else if (listitem == 6)
	{
		new userid;
	    if ((userid = GetIDByID(pTemp[playerid][pMDCWepPlayer])) != INVALID_PLAYER_ID)
	    {
	        SendSyntaxMessage(userid, "%s %s silah ruhsat�na uyar� verdi.", GetRankName(playerid), GetNameEx(playerid));
			PlayerInfo[userid][pWepWarns]++;
		}
		
	    new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `wepwarns`= `wepwarns` + 1 WHERE `id` = %i", pTemp[playerid][pMDCWepPlayer]);
		mysql_tquery(dbHandle, query);

		SendSyntaxMessage(playerid, "%s silah ruhsat�na uyar� verdiniz.", pTemp[playerid][pMDCWepName]);
	    return 1;
	}
	
	ShowWeaponLicense(playerid, GetPVarInt(playerid, #weapon_list));
	return 1;
}

Dialog:ShowTrace(playerid, response, listitem, inputtext[])
{
	if (pTemp[playerid][pTraceStage] < 7)
	{
		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "�zleme Sistemi - ��kmak i�in ESC / ENTER tu�una bas�n", "{B4B5B7}Takip sisteminden ��k�� yapt�n�z.", "Onayla", "");
		
		if (pTemp[playerid][pTraceGZ] != -1)	GangZoneDestroy(pTemp[playerid][pTraceGZ]);
 		
		pTemp[playerid][pTraceGZ] = -1;
		pTemp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
 		pTemp[playerid][pTraceStage] = 0;
	}
	return 1;
}

Dialog:DialogLSPDEkipman(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    if (!IsPlayerFactionPolice(playerid))									return 1;
	if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "��ba��nda olmal�s�n�z.");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
		
	if(response)
	{
		if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE && PlayerInfo[playerid][pOnDuty])
		{
			switch(listitem)
			{
				case 0:
				{ // patrol
					AC_ResetPlayerWeapons(playerid);
					AC_GivePlayerWeapon(playerid, 3, 1);
					AC_GivePlayerWeapon(playerid, 24, 100);
					AC_GivePlayerWeapon(playerid, 41, 1000);
					PlayerInfo[playerid][pHealth] = 100;
					SetPlayerArmour(playerid, 100);
				}
				case 1:
				{ // dedektif
					AC_ResetPlayerWeapons(playerid);
					AC_GivePlayerWeapon(playerid, 24, 100);
					AC_GivePlayerWeapon(playerid, 43, 500);
					PlayerInfo[playerid][pHealth] = 100;
				}
				case 2:
				{ // SWAT
					if(PlayerInfo[playerid][pRank] < 17 && !PlayerInfo[playerid][pOlusumDivision][1]) return SendServerMessage(playerid, "Bu komutu kullanmak i�in yetkiniz bulunmuyor.");
					AC_ResetPlayerWeapons(playerid);
					AC_GivePlayerWeapon(playerid, 24, 500);
					AC_GivePlayerWeapon(playerid, 17, 10);
					AC_GivePlayerWeapon(playerid, 31, 300);

					PlayerInfo[playerid][pHealth] = 200;
					SetPlayerArmour(playerid, 100);
					SendClientMessageEx(playerid, -1, "SWAT olarak ku�and���n�z z�rh�n patrol �zerinde kullan�m�, yasaklama ile sonu�lanabilir. Dikkatli olun.");
				}
				case 3:
				{
					AC_ResetPlayerWeapons(playerid);
					SendServerMessage(playerid, "G�rev silahlar�n� teslim ettiniz.");
				}
			}
			GameTextForPlayer(playerid, "~g~+", 1500, 4);
		} else return SendErrorMessage(playerid, "��ba��nda de�ilsiniz.");
	}
	return 1;
}

Dialog:LSPDArmoury(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
	
	switch(listitem) {
		case 0: {
			return Dialog_Show(playerid, DialogLSPDEkipman, DIALOG_STYLE_TABLIST_HEADERS, "PD/SD Ekipman Men�s�", "�sim\tA��klama\nDevriye Ekipman�\tStandart devriye ekipmanlar�.\nDedektif Ekipman�\tStandart dedektif ekipmanlar�.\nSWAT\tSWAT ekipmanlar�(Sadece SWAT'a �zel)\nTeslimat\tG�rev silahlar�n� teslim edebilirsin", "Se�", "�ptal");
		}
		case 1: {
			if (!PlayerInfo[playerid][pSwat]&& !isLeader(playerid)) return SendErrorMessage(playerid, "S.W.A.T. sizin i�in uygun de�il!");

			if (!PlayerInfo[playerid][pSwatDuty])
			{
				PlayerInfo[playerid][pSwatDuty] = 1;
				SetPlayerArmour(playerid, 150);
				PlayerInfo[playerid][pChar] = (!IsPlayerFactionPolice(playerid))?(287):(285);
				SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
				SetPlayerColor(playerid, RemoveAlpha(Factions[PlayerInfo[playerid][pFaction]][fColor]));
				SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s SWAT ekibine kat�ld� **",GetRankName(playerid), GetNameEx(playerid));
				return 1;
			}
			
			PlayerInfo[playerid][pSwatDuty] = 0;
			SetPlayerArmour(playerid, 100);
			PlayerInfo[playerid][pChar] = 0;
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s SWAT ekibinden ��kt�. **",GetRankName(playerid), GetNameEx(playerid));
		}
	}

	return 1;
}