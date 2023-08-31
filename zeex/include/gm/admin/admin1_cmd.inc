alias:ah("ahelp");
CMD:ah(playerid, params[])
{
	if (PlayerInfo[playerid][pAdmin] == 0 && PlayerInfo[playerid][pFMAdmin] == 0) return SendNotAdmin(playerid);

	if (PlayerInfo[playerid][pFMAdmin] > 0)
	{
		SCM(playerid, COLOR_WHITE, "[FM Staff]: {C3C3C3}/ifmspec /gethere /getcar /changename /sendplayer");
	}

	if (CheckAdmin(playerid, ADMIN_LEVEL_1))
	{
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/aduty /adminchat /duyuru /setinterior(/setint) /setworld(/vw) /masked /flymode");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/kick /skick /ajail /unjail /warn /offlineban /mute /unmute /checkcars /hapisnoktalari");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/clearchat /atp /tp /gethere /goto /sendplayer /freeze /unfreeze /slap /getip /getstats(/astats) /getproperty");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/gotocar /getcar /spec /specoff /disarm /del(ete)ad(vertisment) /aplant");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/aprison /dmlog /near /removebox /check /fixveh /d(elete)pame");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/delaction /revive(/aheal) /reviveall (/agr)eegraffiti /gotolc(-ls/-fc/-d/-m)");
	}
	if (CheckAdmin(playerid, ADMIN_LEVEL_2))
	{
		SCM(playerid, COLOR_WHITE, "[Level 2]: {C3C3C3}/policer /getincar /afire /aengine /fillveh /fillallveh /rtc /rtcall");
		SCM(playerid, COLOR_WHITE, "[Level 2]: {C3C3C3} /delplayertickets /delvehtickets /makemark /gotomark /settime /weather /weatherall");
		SCM(playerid, COLOR_WHITE, "[Level 2]: {C3C3C3}/setskin /sethp /setarmour /aveh /mark /x /y /z /goint");
		SCM(playerid, COLOR_WHITE, "[Level 2]: {C3C3C3}/go /govw /noooc /forbid /unforbid /permaban /unpermaban /opermaban /banip");
	}
	if (CheckAdmin(playerid, ADMIN_LEVEL_3))
	{
		SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/giveitem /alock /changename /acceptname /chopshop /removevehicle /dolapduzenle");
		SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/avehicle /editvehicle /agarage /ahouse /aapart /adoor /abillboard(/abb) /unbanip");
		SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/telecmds /aunimpound /dolapekle /listlockers /dolapsil /arental /meslekdurum /abiz");
		SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/asilah /auver /auyusturucu /hapisekle /hapissil /hapisduzenle /hapisnoktalari");
	}
	if (CheckAdmin(playerid, HIGH_ADMIN_LEVEL))
	{
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/admin /makepremium /helper /helperlead /fmadmin /changefight /copstocrime /firetocrime");
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/asetplate /givemoney /adminhide /setstat /astreet /giveskin");
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/aobject /afood(stand) /alabel /as(peed)c(am) /resetcode");
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/aatm /atower /acctv /agate /ajob /gmx /streamer /hoodolustur /hoodsil");
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/showpm /showpmoff /showpms /nopms /afaction");
	}
	if (CheckAdmin(playerid, DEVELOPER_LEVEL))
	{
		SCM(playerid, COLOR_WHITE, "[DEVELOPER CMD]: {C3C3C3}/payday /paydayall /kickall /anticheat_settings /addskin /createarrest");
	}
	return 1;
}

alias:awork("aduty");
CMD:awork(playerid, params[])
{
	if (PlayerInfo[playerid][pAdmin] < 1) return SendNotAdmin(playerid);

	if (IsAdminDuty(playerid))
	{
		if(PlayerInfo[playerid][pAdmin] == 1337) pTemp[playerid][pDebugMode] = 0;
		SendAdmMessage("%s adlý yetkili artýk müsait deðil.", GetAccName(playerid));
		TextDrawHideForPlayer(playerid, Admin);
		pTemp[playerid][pAdminDuty] = 0;

		SetPlayerColor(playerid, TEAM_HIT_COLOR);

		if (pTemp[playerid][pDMLog] == 1)
		{
			ClearKillFeed(playerid);
			pTemp[playerid][pDMLog] = 0;
		}
		server_admins--;
		return 1;
	}

	else
	{
		if(PlayerInfo[playerid][pAdmin] == 1337) pTemp[playerid][pDebugMode] = 1;
		SetPVarInt(playerid, "Admin:CodeInputted", 1);
		pTemp[playerid][pAdminDuty] = 1;
		pTemp[playerid][pDMLog] = 1;
		SendAdmMessage("%s adlý yetkili artýk müsait.", GetAccName(playerid));
		TextDrawShowForPlayer(playerid, Admin);

		SetPlayerColor(playerid, COLOR_BREEZEADMIN);

		//SetPlayerColor(playerid,TEAM_ADMIN_COLOR);
		server_admins++;
	}
	return 1;
}

CMD:debugcan(playerid)
{
    SendServerMessage(playerid, "%f %f", PlayerInfo[playerid][pHealth], PlayerInfo[playerid][pArmour]);
	return 1;
}

alias:adminchat("ac");
CMD:adminchat(playerid, params[])
{
	if (PlayerInfo[playerid][pAdmin] < 1)	return SendNotAdmin(playerid);
	//if (!pTemp[playerid][pAdminDuty])       return SendErrorMessage(playerid, "Admin iþbaþýnda olmalýsýnýz.");
	if (isnull(params)) 					return SendHelpMessage(playerid, "(/a)dminchat [mesaj ]");
	if (PlayerInfo[playerid][pSettings] & togAdmChat)					return SendErrorMessage(playerid, "Bu komutu kullanabilmek için admin sohbetini açmanýz gerekmektedir.");

	new prefix[32] = "Admin";
	if (PlayerInfo[playerid][pAdmin] == DEVELOPER_LEVEL)			prefix = "Management";
	else if (PlayerInfo[playerid][pAdmin] == HIGH_ADMIN_LEVEL) 		prefix = "Lead Admin";
	else if (PlayerInfo[playerid][pAdmin] == 3)						prefix = "Senior Admin";
	else if (PlayerInfo[playerid][pAdmin] == 2)						prefix = "Liberty Admin";
	else if (PlayerInfo[playerid][pAdmin] == 1)						prefix = "Junior Admin";
	else if (PlayerInfo[playerid][pAdmin] == 1337)					prefix = "Founder";

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		foreach(new i : Player)
		{
		    //if (IsPlayerLogged(i) == 0 || !CheckAdmin(i, ADMIN_LEVEL_1)) continue;
			//if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togAdmCmds)) continue;

		    if (IsPlayerLogged(i) == 0 || (PlayerInfo[i][pSettings] & togAdmChat) || PlayerInfo[i][pAdmin] < 1) continue;

			SendClientMessageEx(i, COLOR_YELLOWG, "** [AdmChat] %s %s(%d): %.*s ...", prefix, GetAccName(playerid), playerid, pos, params);
			SendClientMessageEx(i, COLOR_YELLOWG, "... %s", params[pos]);
		}
	}
	else
	{
		foreach(new i : Player)
		{
			if (IsPlayerLogged(i) == 0 || (PlayerInfo[i][pSettings] & togAdmChat) || PlayerInfo[i][pAdmin] < 1) continue;

			SendClientMessageEx(i, COLOR_YELLOWG, "** [AdmChat] %s %s(%d): %s", prefix, GetAccName(playerid), playerid, params);
		}
		//AMSG(COLOR_YELLOWG, "* [AC] %s (%s): %s", GetPlayerNameEx(playerid), GetAccName(playerid), params);
	}
	return 1;
}

/*alias:an("ans", "/answer");
CMD:an(playerid,params[])
{
	new userid, text[128];

	if (sscanf(params, "us[128]", userid, text))						return SendHelpMessage(playerid, "/an [ID / isim] [answer]");
	if (!IsTester(playerid) && !CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (userid == playerid)												return SendErrorMessage(playerid, "You cannot answer to yourself.");

    new mes[256];

	if (strlen(text) > MAXLEN)
	{
	    new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(mes, sizeof(mes), "%s answers you: %s", GetAccName(playerid), text);
		SendClientMessageEx(userid, 0x00CC99AA, "%.*s", pos, mes);
		SendClientMessageEx(userid, 0x00CC99AA, "... %s", mes[pos]);

		format(mes, sizeof(mes), "[ANSWER]: %s answered %s [ID: %i]: %s", GetAccName(playerid), GetNameEx(userid), userid, text);
		StaffMSG(0x00CC99AA, "%.*s", pos, mes);
		StaffMSG(0x00CC99AA, "... %s", mes[pos]);
	}
	else
	{
	    format(mes, sizeof(mes), "%s answers you: %s", GetAccName(playerid), text);
		SendClientMessage(userid, 0x00CC99AA, mes);
		StaffMSG(0x00CC99AA, "[ANSWER]: %s answered %s [ID: %i]: %s", GetAccName(playerid), GetNameEx(userid), userid, text);
	}
	return 1;
}*/

/*alias:aooc("ao");
CMD:aooc(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (isnull(params))							return SendHelpMessage(playerid, "(/ao)oc [text]");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(mes, sizeof(mes), "[OOC] %s: %.*s ...", GetAccName(playerid), pos, params);
		SCMALL(0xF97804FF,mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SCMALL(0xF97804FF,mes);
	}
	else
	{
		format(mes, sizeof(mes), "[OOC] %s: %s", GetAccName(playerid), params);
		SCMALL(0xF97804FF, mes);
	}
	return 1;
}*/

/*CMD:announce(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (isnull(params))							return SendHelpMessage(playerid, "/announce [text]");

    new mes[128];
    format(mes, sizeof(mes), "~y~%s: ~w~%s", GetNameEx(playerid), params);

    foreach (new i : Player)
	{
	    if (IsPlayerLogged(i) == 0 || GetWorld(playerid) != GetWorld(i)) continue;

		GameTextForPlayer(i, mes, 5000, 4);
	}
	return 1;
}*/

alias:sokaktansesler("sokses");
CMD:sokaktansesler(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (isnull(params))							return SendHelpMessage(playerid, "/sokaktansesler (yazý)");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(mes, sizeof(mes), "[Sokaktan Sesler] %.*s ...", pos, params);
		SCMALL(COLOR_ORANGE,mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SCMALL(COLOR_ORANGE,mes);
	}
	else
	{
		format(mes, sizeof(mes), "[Sokaktan Sesler] %s", params);
		SCMALL(COLOR_ORANGE, mes);
	}
	return 1;
}


CMD:duyuru(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (isnull(params))							return SendHelpMessage(playerid, "/duyuru [Duyuru Yazýsý]");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(mes, sizeof(mes), "[Duyuru] %s: %.*s ...", GetAccName(playerid), pos, params);
		SCMALL(0xF97804FF,mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SCMALL(0xF97804FF,mes);
	}
	else
	{
		format(mes, sizeof(mes), "[Duyuru] %s: %s", GetAccName(playerid), params);
		SCMALL(0xF97804FF, mes);
	}
	return 1;
}

alias:setinterior("setint");
CMD:setinterior(playerid, params[])
{
	new userid, int;
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "ud", userid, int)) 		return SendHelpMessage(playerid, "/setinterior [id/karakter adý] [ID interior (0-255)");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (int < 0 || int > 255)					return SendErrorMessage(playerid, "Interior ID 0 ile 255 arasýnda olabilir");

	SetInterior(userid, int);
	SendServerMessage(userid, "%s adlý yetkili interiorunuzu deðiþtirdi. [ID: %i].", GetAccName(playerid), int);
	SendAdmMessageToPlayer(playerid, "%s adlý kiþinin interioru deðiþtirildi. Interior [ID: %i].", GetNameEx(userid), int);
	return 1;
}

alias:setworld("setvw");
CMD:setworld(playerid, params[])
{
	new userid, wid;
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "ud", userid, wid))		return SendHelpMessage(playerid, "/setworld [ID/karakter adý] [ID virtual world (65535)]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
	if (wid < 0 || wid > 65535)					return SendErrorMessage(playerid, "VW 0 ile 65535 arasýnda olabilir.");

	SetWorld(userid, wid);
	SendServerMessage(userid, "%s adlý yetkili dünyanýzý deðiþtirdi. [ID: %i].", GetAccName(playerid),  wid);
	SendAdmMessageToPlayer(playerid, "%s adlý kiþinin dünyasý deðiþtirildi. Dünya: [ID: %i].", GetNameEx(userid), wid);
	return 1;
}

CMD:getworld(playerid, params[])
{
	new userid;
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid)) 			return SendHelpMessage(playerid, "/getworld [ID / isim]");
	if (!IsPlayerLogged(userid)) 				return SendNotConnected(playerid);

	SendServerMessage(playerid, "%s [ID: %d] adlý oyuncu %i dünyasýnda.", GetNameEx(userid), userid, GetWorld(userid));
	return 1;
}

CMD:vw(playerid, params[])
{
	SendServerMessage(playerid, "%s [ID: %d] adlý oyuncu olarak %i numaralý dünyadasýnýz.", GetNameEx(playerid), playerid, GetWorld(playerid));
	return 1;
}

CMD:gonder(playerid, params[])
{
	new opt[12], userid;
	if(!CheckAdmin(playerid, ADMIN_LEVEL_1) && PlayerInfo[playerid][pHelper] < 3)		return SendNotAdmin(playerid);

	if (sscanf(params, "s[12]u", opt, userid)){
		SendHelpMessage(playerid, "/gonder [seçenek] [ID]");
		SendHelpMessage(playerid, "Seçenekler: lc, spawn");

		return 1;
	}
	if(!IsPlayerLogged(userid))						return SendNotConnected(playerid);

	if(!strcmp(opt, "lc", true)){
		SetPlayerPosEx(userid, 785.9385,-868.3475,35.3712);
		SetPlayerFacingAngle(userid, 180.0);
		SetInterior(userid, 0);
		SetWorld(userid, 0);
		SendServerMessage(playerid, "Belirtilen oyuncuyu Liberty City'e ýþýnladýnýz.");
		SendServerMessage(userid, "Yönetici tarafýndan Liberty City'e ýþýnlandýnýz.");
	} else if(!strcmp(opt, "spawn", true)){
		pTemp[userid][pLastLogin] = 0;
		SetPlayerSpawn(userid);

		SendServerMessage(playerid, "Belirtilen oyuncuyu spawn bölgesine ýþýnladýnýz.");
		SendServerMessage(userid, "Yönetici tarafýndan spawn bölgesine ýþýnlandýnýz.");
	} 
	return 1;
}

alias:masked("maskeliler");
CMD:masked(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	new mask_string[1024];
	mask_string[0] = EOS;

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || !maskOn{i}) continue;
		//SendClientMessageEx(playerid, COLOUR_WHITE, "%s%s (%s, ID: %i)", mask_string, GetNameWithMask(i), GetNameEx(i), i);
		format(mask_string, sizeof(mask_string), "{FFFFFF}%s%s - %s [ID: %i]\n", mask_string, GetNameWithMask(i), GetNameEx(i), i);
	}

	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{FFFFFF}Maskeli Oyuncular", mask_string, ">>>", "");
	return 1;
}

CMD:gotols(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, 1515.2, -1668.1, 14.04);
	SetPlayerFacingAngle(playerid, 272.83);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Los Santos'a ýþýnlandýnýz.");

	return 1;
}

CMD:gotolc(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, 785.9385,-868.3475,35.3712);
	SetPlayerFacingAngle(playerid, 180);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Liberty City'e ýþýnlandýnýz.");

	return 1;
}

CMD:gotopc(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, 2269.4795,-81.2131,26.5414);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Palomino Creek'e ýþýnlandýnýz.");
	return 1;
}

CMD:gotom(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, 1358.6038,251.7677,19.5669);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Montgomery'e ýþýnlandýnýz.");

	return 1;
}

CMD:gotod(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, 207.7609,-64.7452,1.5781);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Blueberry'e ýþýnlandýnýz.");
	return 1;
}

CMD:gotofc(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	SetPlayerPosEx(playerid, -204.1443,1119.1970,19.7422);
	SetInterior(playerid, 0);
	SetWorld(playerid, 0);
	SendServerMessage(playerid, "Fort Carson'a ýþýnlandýnýz.");
	return 1;
}

CMD:kick(playerid, params[])
{
	new userid, reason[64];

    if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && !IsTester(playerid, 5))		return SendNotAdmin(playerid);
	if (sscanf(params, "us[64]", userid, reason)) 	return SendHelpMessage(playerid, "/kick [ID/Karakter Adý] [Sebep]");
	if (!IsPlayerLogged(userid)) 					return SendNotConnected(playerid);
	if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste kickleyemezsin.");


	if (PlayerInfo[userid][pAdmin] < PlayerInfo[playerid][pAdmin])
	{
		new mes[128];

		format(mes, sizeof(mes), "[/kick] %s adlý oyuncu %s adlý yönetici tarafýndan oyundan atýldý. Sebep: %s", GetNameEx(userid), GetAccName(playerid), reason);
		insert_log(mes, ADMIN_LOG, 2, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

		format(mes, sizeof(mes), "(( %s adlý kullanýcý %s tarafýndan oyundan atýldý. Sebep: %s ))", GetNameEx(userid), GetAccName(playerid), reason);
		SendClientMessageByAdmin(COLOUR_TOMATO, mes);

		KickEx(userid);
		pTemp[playerid][pBanTime] = gettime() + 5;
	}
	return 1;
}

CMD:skick(playerid, params[])
{
	new userid, reason[128], mes[64];
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && !IsTester(playerid, 5)) 		return SendNotAdmin(playerid);
	if (sscanf(params, "us[128]", userid, reason)) 	return SendHelpMessage(playerid, "/skick [ID/Karakter Adý] [Sebep]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);

	if (PlayerInfo[userid][pAdmin] < PlayerInfo[playerid][pAdmin])
	{
		SendServerMessage(playerid, "%s adlý kiþiyi oyundan attýnýz.", GetNameEx(userid));
		format(mes, sizeof(mes), "[/skick] %s adlý oyuncu %s adlý yönetici tarafýndan sunucudan atýldý. Sebep: %s", GetNameEx(userid), GetAccName(playerid), reason);
		insert_log(mes, ADMIN_LOG, 2, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

		KickEx(userid);
	}
	return 1;
}

alias:offjail("ojail");
CMD:offjail(playerid, params[])
{
	new username[MAX_PLAYER_NAME + 1], reason[32], time;

    if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 					return SendNotAdmin(playerid);
	if (sscanf(params,"s[32]ds[32]", username, time, reason)) 	return SendHelpMessage(playerid, "/offjail [karakter adý] [(1-2880) dakika] [sebep]");
	if (!IsValidPlayerName(username)) 							return SendErrorMessage(playerid, "Geçersiz karakter adý");
	if (time <= 0 || time > 2880) 								return SendErrorMessage(playerid, "Dakika 1 ile 2880 arasýnda olmalýdýr.");

    foreach (new i : Player)
	{
	    if (IsPlayerLogged(i) == 0 || !CompareStrings(username, GetNameEx(i))) continue;
	    SendErrorMessage(playerid, "Belirtilen oyuncu çevrimiçi: %s [ID: %i]", GetNameEx(i), i);
		return 1;
	}

	new query[256];
	mysql_format(dbHandle, query,sizeof(query),"SELECT * FROM users WHERE `name` = '%e'", username);
	mysql_tquery(dbHandle, query, "OnPlayerOfflineJail", "dsds", playerid, username, time, reason);
	return 1;
}

CMD:ajail(playerid, params[])
{
	new userid, time, reason[128];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))				return SendNotAdmin(playerid);
	if (sscanf(params,"uds[128]", userid, time, reason)) 	return SendHelpMessage(playerid, "/ajail [ID/Karakter Adý] [(1-999999) dakika] [sebep]");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (time <= 0 || time > 999999)							return SendErrorMessage(playerid, "Dakika 1 ile 999999 arasýnda olmalýdýr.");

	PlayerInfo[userid][pAJailed] = 1;
	PlayerInfo[userid][pAJailTime] = time*60;
	SetInterior(userid, 18);
	SetWorld(userid, userid + 100);
	SetPlayerPosEx(userid, 1017.3297,-807.2664,2003.0758);
	SetSpawnInfoEx(userid, 1017.3297,-807.2664,2003.0758);
	for(new j; j < 12; j++)
	{
		AC_ResetPlayerWeapons(userid);

		PlayerInfo[userid][pWeapons][j] = 0;
		PlayerInfo[userid][pAmmo][j] = 0;
	}

	new mes[128];

	if(time > 10) 
	{
	    format(mes, sizeof(mes), "(( %s adlý kiþi yönetici tarafýndan %i dakika hapise gönderildi. Sebep: %s ))", GetNameEx(userid), time, reason);
        SendClientMessageByAdmin(COLOUR_TOMATO, mes);
    }	

	format(mes, sizeof(mes), "[AJAIL] %s adlý karakter %s adlý yönetici tarafýndan %i dakika hapise gönderildi. Sebep: %s", GetNameEx(userid), GetAccName(playerid), time, reason);
	insert_log(mes, ADMIN_LOG, 5, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);
	return 1;
}

CMD:unjail(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 									return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))											return SendHelpMessage(playerid, "/unjail [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))												return SendNotConnected(playerid);
	if (PlayerInfo[userid][pJailed] == 0 && PlayerInfo[userid][pAJailed] == 0)	return SendErrorMessage(playerid, "Belirtilen oyuncu hapiste deðil");

	PlayerInfo[userid][pJailed] =
	PlayerInfo[userid][pIsolateTime] =
	PlayerInfo[userid][pJailTime] =
	PlayerInfo[userid][pAJailed] =
	PlayerInfo[userid][pAJailTime] = 0;

	if (IsValidDynamic3DTextLabel(PrisonLabel[userid]))
	{
		DestroyDynamic3DTextLabel(PrisonLabel[userid]);
  		PrisonLabel[userid] = Text3D:INVALID_3DTEXT_ID;
	}

	SetInterior(userid, 0);
	SetWorld(userid, 0);
	SetPlayerPosEx(userid, 785.9385,-868.3475,35.3712);
 	SetSpawnInfoEx(userid, 785.9385,-868.3475,35.3712, 3.9650);

	SendAdmMessageToPlayer(userid, "Yönetici tarafýndan hapisten çýkartýldýnýz.");
	SendAdmMessageToPlayer(playerid, "%s [ID: %i] adlý oyuncuyu hapisten çýkarttýnýz.", GetAccName(userid), userid);
	return 1;
}

CMD:delaction(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "/delaction [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
    if (!GetPVarInt(userid, "3DLabel"))			return SendErrorMessage(playerid, "Oyuncu herhangi bir 3D yazý oluþturmamýþ.");

    DestroyDynamic3DTextLabel(Text3D:GetPVarInt(playerid, "3DLabel"));
    DeletePVar(userid, "3DLabel");

	SendServerMessage(userid, "Ortam açýklamanýz %s adlý yönetici tarafýndan silindi.", GetAccName(playerid));
    AMSG(COLOR_LIGHTRED,"[LOG] %s adlý yönetici tarafýndan %s [ID:%i] adlý oyuncunun ortam açýklamalarý silindi.", GetAccName(playerid), GetNameEx(userid), userid);
    return 1;
}

CMD:warn(playerid, params[])
{
	new userid, reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 		return SendNotAdmin(playerid);
	if (sscanf(params, "us[125]", userid, reason))	return SendHelpMessage(playerid, "/warn [ID/Karakter Adý] [Sebep]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (strlen(reason) > 63) 						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olabilir.");

    new mes[128], query[256];

	PlayerInfo[userid][pWarns]++;
	SQL_SetInteger("users", "warn", PlayerInfo[userid][pWarns], PlayerInfo[userid][pID]);

	if (PlayerInfo[userid][pWarns] >= 3)
	{
		format(mes,sizeof(mes),"(( %s adlý oyuncu yasaklandý. Sebep: %s (3 uyarý) ))", GetNameEx(userid), reason,PlayerInfo[userid][pWarns]);
		SendClientMessageByAdmin(COLOUR_TOMATO, mes);

		format(query, sizeof(query), "[/ban] %s adlý oyuncu %s adlý yönetici tarafýndan engellendi. Sebep: %s (3 uyarý)", GetAccName(userid), GetAccName(playerid), reason);
		insert_log(query, ADMIN_LOG, 1, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

		new ip[24];
		GetPlayerIp(userid, ip, sizeof(ip));

		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `bans` (accountid, ip, name, admin, reason, date) VALUES (%i, '%e', '%e', '%e', '%e', '%e')", PlayerInfo[playerid][pAccID], ip, GetAccName(userid), GetAccName(playerid), reason, GetFullDate());
		mysql_tquery(dbHandle, query);

		KickEx(userid);
		return 1;
	}

	SendAdmMessageToPlayer(userid, "Bir uyarý aldýnýz. %s [%i/3].", GetAccName(playerid), PlayerInfo[userid][pWarns]);

    format(query, sizeof(query), "[/warn] %s adlý oyuncuya %s adlý yönetici tarafýndan bir uyarý verildi. Sebep: %s", GetAccName(userid), GetAccName(playerid), reason);
	insert_log(query, ADMIN_LOG, 4, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

    format(mes, sizeof(mes), "(( %s adlý oyuncuya yönetici tarafýndan bir uyarý verildi. Sebep: %s [%i/3] ))", GetNameEx(userid), reason, PlayerInfo[userid][pWarns]);
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);
	return 1;
}

CMD:ban(playerid, params[])
{
	new userid, reason[64];
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))		return SendNotAdmin(playerid);
	if (sscanf(params, "us[64]", userid, reason))	return SendHelpMessage(playerid, "/ban [ID/Karakter Adý] [Sebep]");
	if (!IsPlayerLogged(userid)) 					return SendNotConnected(playerid);
	if (strlen(reason) > 63)						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
	if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste yasaklama yapamazsýnýz.");

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `block_name`='%e', `block_reason` ='%e', `status` = '3' WHERE `id` = '%i'", GetAccName(playerid), reason, PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query);

	new mes[128];
    format(mes, sizeof(mes), "(( %s adlý karakter yönetici tarafýndan yasaklandý. Sebep: %s ))", GetNameEx(userid), reason);
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);

	pTemp[playerid][pBanTime] = gettime() + 5;

    KickEx(userid);
	return 1;
}

alias:oban("offlineban");
CMD:oban(playerid, params[])        
{
	new name[MAX_PLAYER_NAME], reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))		return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]s[64]", name, reason))	return SendHelpMessage(playerid, "/oban [karakter adý] [sebep]");
    if (!IsValidPlayerName(name)) 					return SendErrorMessage(playerid, "Geçersiz karakter adý.");
	if (strlen(reason) > 63)						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
	if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste yasaklama yapamazsýnýz.");

    foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !CompareStrings(GetNameEx(i), name))	continue;

		SendErrorMessage(playerid, "Belirtilen karakter þu an oyunda. %s [ID: %i]", GetNameEx(i), i);
		return 1;
	}

    pTemp[playerid][pBanTime] = gettime() + 5;

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e'", name);
	mysql_tquery(dbHandle, query, "OfflineBlockPlayer", "iss", playerid, name, reason);
	return 1;
}

CMD:unban(playerid, params[])
{
	new name[MAX_PLAYER_NAME];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]", name))			return SendHelpMessage(playerid, "/unban [karakter adý]");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e'", name);
	mysql_tquery(dbHandle, query, "UnBlockPlayer", "is", playerid, name);
	return 1;
}

alias:opermaban("offpermaban");
CMD:opermaban(playerid, params[])
{
	new name[MAX_PLAYER_NAME], reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 		return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]s[64]", name, reason)) return SendHelpMessage(playerid, "/opermaban [hesap adý] [sebep]");
    if (!IsValidPlayerName(name)) 					return SendErrorMessage(playerid, "Geçersiz hesap adý.");
	if (strlen(reason) > 63)						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");

    foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !CompareStrings(GetAccName(i), name)) continue;

		SendErrorMessage(playerid, "%s adlý hesap þu an aktif. %s [ID: %i]", name, GetNameEx(i), i);
		return 1;
	}

	new query[288];
	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `id` FROM `bans` WHERE `name` = '%e') as banid FROM `accounts` WHERE `login` = '%e'", name, name);
	mysql_tquery(dbHandle, query, "OfflineBanPlayer", "iss", playerid, name, reason);
	return 1;
}

CMD:permaban(playerid, params[])
{
	new userid, reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))		return SendNotAdmin(playerid);
	if (sscanf(params, "us[64]", userid, reason))	return SendHelpMessage(playerid, "((hesabý tamamen yasaklar)) /permaban [ID/Karakter Adý] [sebep]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (strlen(reason) > 63)						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
	if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste yasaklama yapamazsýnýz.");

	new mes[128];
    format(mes, sizeof(mes), "(( %s adlý oyuncu yönetici tarafýndan yasaklandý. Sebep: %s ))", GetNameEx(userid), reason);
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);

	new ip[24], query[512];
	GetPlayerIp(userid, ip, sizeof(ip));

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `bans` (accountid, ip, name, admin, reason, date) VALUES (%i, '%e', '%e', '%e', '%e', '%e')", PlayerInfo[userid][pAccID], ip, GetAccName(userid), GetAccName(playerid), reason, GetFullDate());
	mysql_tquery(dbHandle, query);

	format(query, sizeof(query), "[/ban] %s adlý kullanýcý %s adlý yönetici tarafýndan yasaklandý. Sebep: %s", GetAccName(userid), GetAccName(playerid), reason);
	insert_log(query, ADMIN_LOG, 1, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

	pTemp[playerid][pBanTime] = gettime() + 5;

    KickEx(userid);
	return 1;
}

CMD:ck(playerid, params[])
{
	new userid, reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))		return SendNotAdmin(playerid);
	if (sscanf(params, "us[64]", userid, reason))	return SendHelpMessage(playerid, "/ck [ID/Karakter Adý] [sebep]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (strlen(reason) > 63)						return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
    if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste yasaklama yapamazsýnýz.");	

	new mes[128];
    format(mes, sizeof(mes), "[Karakter Ölümü] %s adlý karakter hayatýný kaybetti. Sebep: %s", GetNameEx(userid), reason);
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `block_name`='%e', `block_reason` ='%e', `status` = '3' WHERE `id` = '%i'", GetAccName(playerid), reason, PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query);

	format(query, sizeof(query), "[/ck] %s adlý kullanýcý %s adlý yönetici tarafýndan CK edildi. Sebep: %s", GetAccName(userid), GetAccName(playerid), reason);
	insert_log(query, ADMIN_LOG, 1, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

	pTemp[playerid][pBanTime] = gettime() + 5;

    KickEx(userid);
	return 1;
}

CMD:unpermaban(playerid, params[])
{
	new name[MAX_PLAYER_NAME];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]", name))			return SendHelpMessage(playerid, "/unpermaban [hesap adý]");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `bans` WHERE `name` = '%e'", name);
	mysql_tquery(dbHandle, query, "UnBanPlayer", "is", playerid, name);
	return 1;
}

CMD:banip(playerid, params[])
{
	new ip[24], reason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]s[64]", ip))		return SendHelpMessage(playerid, "/banip [IP] [sebep]");
	if (!IsAnIP(ip))							return SendErrorMessage(playerid, "Hatalý IP formatý.");
	if (strlen(reason) > 63)					return SendErrorMessage(playerid, "Sebep minimum 63 karakter olmalýdýr.");
	if (pTemp[playerid][pBanTime] > gettime() && PlayerInfo[playerid][pAdmin] != 1337)      return SendErrorMessage(playerid, "Üst üste yasaklama yapamazsýnýz.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `bans` WHERE `ip` = '%e'", ip);
	mysql_tquery(dbHandle, query, "BanAnIP", "iss", playerid, ip, reason);

	pTemp[playerid][pBanTime] = gettime() + 5;
	return 1;
}

CMD:unbanip(playerid, params[])
{
	new ip[24];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params, "s[24]", ip))				return SendHelpMessage(playerid, "/unbanip [IP]");
	if (!IsAnIP(ip))								return SendErrorMessage(playerid, "Hatalý IP formatý.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `bans` WHERE `ip` = '%e'", ip);
	mysql_tquery(dbHandle, query, "UnBanAnIP", "is", playerid, ip);

	return 1;
}

CMD:mute(playerid, params[])
{
	new userid, time, mreason[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))				return SendNotAdmin(playerid);
	if (sscanf(params,"uds[128]", userid, time, mreason)) 	return SendHelpMessage(playerid, "/mute [ID/Karakter Adý] [(1-1440) dakika] [sebep]");
	if (!IsPlayerLogged(userid)) 							return SendNotConnected(playerid);
	if (time < 1 || time > 1440)							return SendErrorMessage(playerid, "Süre 1 ile 1440 dakika arasýnda olmalýdýr.");
	if (strlen(mreason) > 63)								return SendErrorMessage(playerid, "Sebep minimum 63 karakter olmalýdýr.");

	PlayerInfo[userid][pMutedTime] = time*60;

	new mes[128];
	format(mes, sizeof(mes), "(( %s adlý oyuncu yönetici tarafýndan %i dakika susturuldu. Sebep: %s ))", GetNameEx(userid), time, mreason);
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);
	return 1;
}
CMD:unmute(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/unmute [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (PlayerInfo[userid][pMutedTime] == 0)		return SendErrorMessage(playerid, "Belirtilen oyuncu susturulmuþ.");

	PlayerInfo[userid][pMutedTime] = 0;

	new mes[128];
	format(mes, sizeof(mes), "(( %s adlý oyuncunun susturulmasý yönetici tarafýndan kaldýrýldý. ))", GetNameEx(userid));
	SendClientMessageByAdmin(COLOUR_TOMATO, mes);
	return 1;
}
alias:clearchat("ccall");
CMD:clearchat(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	ClearChatboxForAll(50);
	SAMALL("%s adlý yönetici tarafýndan sohbet temizlendi.", GetAccName(playerid)); // AdmCmd
	return 1;
}

alias:sohbettemizle("sohbetsil", "sc", "ccmy", "cc");
CMD:sohbettemizle(playerid)
{
	ClearChatbox(playerid, 50);
	GameTextForPlayer(playerid, "~y~sohbet temizlendi", 1000, 5);
	return 1;
}

/*CMD:testmsg(playerid, params[])
{
	new Float:hp;
	AntiCheatGetHealth(playerid, hp);

	SM1(playerid, "%f", hp);
	return 1;
}*/


/*CMD:test(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "/gethere [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	SetPlayerMarkerForPlayer(playerid, userid, 0xA52A2AFF);
	return 1;
}*/

CMD:tp(playerid, params[])
{
	new telestring[3072], part[40];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	for(new OrT = 0; OrT < sizeof(OrTeleports); OrT++)
	{
		format(part, sizeof(part), "%s\n", OrTeleports[OrT][tele_name]);
		strcat(telestring, part, sizeof(telestring));
	}

	Dialog_Show(playerid, Teles, DIALOG_STYLE_LIST, "{FFFFFF}Iþýnlanacak bir yer seçin", telestring, ">>>", "Ýptal");
	return 1;
}

CMD:osilahkontrol(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1) return 0;
	
	new name[32];

	if(sscanf(params, "s[32]", name))
		return SendSyntaxMessage(playerid, "/osilahkontrol (Karakter Adý)");

	mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM users WHERE name = '%e' AND online = 0", name);
	new Cache:idveri = mysql_query(dbHandle, queryx, true);
	new rows;
	cache_get_row_count(rows);

	if(!rows)
	{
		SendErrorMessage(playerid, "%s adlý karakter bulunamadý. (%s)", name, ReturnDate());
		cache_delete(idveri);
	}
	else
	{
		new tmpID;
		cache_get_value_int(0, "id", tmpID);
		cache_delete(idveri);
		rows = 0;

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d'", tmpID);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		cache_get_row_count(rows);

		if(!rows)
		{
			SendErrorMessage(playerid, "%s adlý karaktere kayýtlý silah bulunamadý. (%s)", name, ReturnDate());
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_GREEN, "%s adlý karaktere baðlý silahlar %s tarihinde listelendi:", name, ReturnDate());

			new id, weaponid, ammo, status, house, vehicle, biz, olusumid, idstr[6], statusstr[24];

			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", id);
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				cache_get_value_int(j, "status", status);
				cache_get_value_int(j, "house", house);
				cache_get_value_int(j, "vehicle", vehicle);
				cache_get_value_int(j, "biz", biz);
				cache_get_value_int(j, "faction_id", olusumid);
				format(idstr, 6, "%d", id);

				if(id < 1000)
					format(idstr, 6, "0%d", id);

				if(id < 100)
					format(idstr, 6, "00%d", id);

				if(id < 10)
					format(idstr, 6, "000%d", id);

				switch(status)
				{
					case 0: format(statusstr, 24, "Üzerinizde");
					case 1: format(statusstr, 24, "Evde (%d)", house);
					case 2: format(statusstr, 24, "Araçta (%d)", vehicle);
					case 3: format(statusstr, 24, "Ýþletmede (%d)", biz);
					case 4: format(statusstr, 24, "Polis Zimmeti");
					case 5: format(statusstr, 24, "Yönetici Müdahalesi");
					case 6: format(statusstr, 24, "Geri Ödeme Yapýldý");
				case 7: format(statusstr, 24, "Birlik kasasýnda (%d)", olusumid);
				}
				SendClientMessageEx(playerid, COLOR_GREY, "Slot[%d] - ID[%s] - Silah[%s] - Mermi[%d] - Durum[%s]", j+1, idstr, GetWeaponNameEx(weaponid), ammo, statusstr);
			}
		}
		cache_delete(veri);
	}
	return 1;
}

CMD:gethere(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && !IsTester(playerid, 3) && !PlayerInfo[playerid][pEbc] && PlayerInfo[playerid][pFMAdmin] < 1)		return SendNotAdmin(playerid);
	
	if (sscanf(params, "u", userid))						return SendHelpMessage(playerid, "/gethere [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (GetPlayerState(userid) == PLAYER_STATE_SPECTATING)	return SendErrorMessage(playerid, "Belirtilen oyuncu izleme modunda.");

    SendPlayerToPlayer(userid, playerid);
	SendServerMessage(userid, "Yönetici tarafýndan çekildiniz.");
	return 1;
}

alias:ptp("p2p");
CMD:ptp(playerid, params[])
{
    if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 2)))	return SendNotAdmin(playerid);	
    new gelen, id;
    if(sscanf(params, "uu", gelen, id)) return SendHelpMessage(playerid, "/ptp [kiþi id] [ýþýnlanacaðý kiþi id]");
    if (!IsPlayerLogged(gelen)) return SendErrorMessage(playerid, "Iþýnlatýlacaðý kiþi aktif deðil");
    if (!IsPlayerLogged(id)) return SendErrorMessage(playerid, "Iþýnlanan aktif degil.");
    SendPlayerToPlayer(gelen, id);

	SendServerMessage(playerid, "%s adlý kiþiyi %s adlý kiþiye ýþýnladýnýz.", GetNameEx(gelen), GetNameEx(id));
    return 1;
}

CMD:goto(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 3)))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))						return SendHelpMessage(playerid, "/goto [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
    if (GetPlayerState(userid) == PLAYER_STATE_SPECTATING)	return SendErrorMessage(playerid, "Belirtilen oyuncu izleme modunda.");

    SendPlayerToPlayer(playerid, userid);
	SendServerMessage(playerid, "%s adlý kiþinin yanýna ýþýnlandýnýz.", GetNameEx(userid));
	return 1;
}

CMD:sendplayer(playerid, params[])
{
	new userid, targetid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 2)) && PlayerInfo[playerid][pFMAdmin] < 1)	return SendNotAdmin(playerid);
	if (sscanf(params, "uu", userid, targetid))						return SendHelpMessage(playerid, "/sendplayer [Gönderilen ID] [Yanýna göndereceðiniz kiþi ID]");
	if (!IsPlayerLogged(userid) && !IsPlayerLogged(targetid))							return SendNotConnected(playerid);
    if (GetPlayerState(userid) == PLAYER_STATE_SPECTATING && GetPlayerState(targetid) == PLAYER_STATE_SPECTATING)	return SendErrorMessage(playerid, "Belirtilen oyuncu izleme modunda.");

    SendPlayerToPlayer(userid, targetid);
	SendServerMessage(playerid, "%s, %s adlý kiþinin yanýna ýþýnladýnýz.", GetNameEx(userid), GetNameEx(targetid));
	return 1;
}

CMD:freeze(playerid, params[])
{
	new userid;

	if (!IsTester(playerid, 4) && !CheckAdmin(playerid, ADMIN_LEVEL_1))
		return SendNotAdmin(playerid);

	if (sscanf(params,"u", userid))
		return SendHelpMessage(playerid, "/freeze [ID/Karakter Adý]");

	if (!IsPlayerLogged(userid))
		return SendNotConnected(playerid);	

	SendServerMessage(userid, "Yönetici tarafýndan donduruldunuz.");
	SendAdmMessageToPlayer(playerid, "%s [ID: %i] adlý oyuncuyu dondurdunuz.", GetNameEx(userid), userid);
	FreezePlayer(userid);

	return 1;
}

CMD:unfreeze(playerid, params[])
{
	new userid;

	if (!IsTester(playerid, 4) && !CheckAdmin(playerid, ADMIN_LEVEL_1))
		return SendNotAdmin(playerid);

	if (sscanf(params,"u", userid))
		return SendHelpMessage(playerid, "/freeze [ID/Karakter Adý]");

	if (!IsPlayerLogged(userid))
		return SendNotConnected(playerid);

	SendServerMessage(userid, "Yönetici tarafýndan çözüldünüz.");
	SendAdmMessageToPlayer(playerid, "%s [ID: %i] adlý oyuncuyu çözdünüz.", GetNameEx(userid), userid);
	UnFreezePlayer(userid);
	return 1;
}

CMD:slap(playerid, params[])
{
	new userid, Float:slx, Float:sly, Float:slz;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 4)))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/slap [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);

	AntiCheatGetPos(userid, slx, sly, slz);
	SetPlayerPosEx(userid, slx, sly, slz+10, 0);
	PlayerPlaySound(userid, 1130, slx, sly, slz+10);

	SendServerMessage(userid, "Yönetici sizi tokatladý.");
	SendAdmMessageToPlayer(playerid, "%s [ID: %i] adlý oyuncuyu tokatladýnýz.", GetNameEx(userid), userid);
	return 1;
}

CMD:getip(playerid, params[])
{
	new ip[24], userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/getip [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);

	GetPlayerIp(userid, ip, sizeof(ip));
	SendAdmMessageToPlayer(playerid, "%s adlý kullanýcýnýn IP adresi: %s", GetNameEx(userid), ip);
	return 1;
}

alias:getstats("astats");
CMD:getstats(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "/getstats [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	ShowStats(playerid, userid);
	return 1;
}

CMD:getproperty(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "/getproperty [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	ShowProperty(playerid, userid);
	return 1;
}

CMD:reviveall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	//if (pTemp[userid][pInvulnerable] != 0.0)	return SendErrorMessage(playerid, "Tekrar deneyin!");

	new count;

	foreach(new i : Player)
	{
		if(!IsPlayerLoggedIn(i))
			continue;

		if(PlayerInfo[playerid][pInjured] == 0)
			continue;

	    PlayerInfo[i][pHealth] = 100;
	    ResetDamages(i);
	    StopPlayerAnims(i);
	    UnFreezePlayer(i);
	    SetPlayerSkill(i);
		count++;
	}
	SendAdmMessage("%s adlý yönetici %i kiþiyi canlandýrdý. (/reviveall)", GetAccName(playerid), count);

	return 1;
}

alias:healplayer("aheal", "revive");
CMD:healplayer(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "/healplayer [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
	if (PlayerInfo[userid][pInjured] == 0)		return SendErrorMessage(playerid, "Bu kiþi yaralý deðil.");
	//if (pTemp[userid][pInvulnerable] != 0.0)	return SendErrorMessage(playerid, "Tekrar deneyin!");

	PlayerInfo[userid][pHealth] = 100;
	ResetDamages(userid);
	StopPlayerAnims(userid);
	UnFreezePlayer(userid);
	SetPlayerSkill(userid);
	AC_ResetPlayerWeapons(userid);
	SetTimerEx("OnPlayerSetData", 1000, false, "d", userid);

	SendServerMessage(userid, "%s adlý yönetici tarafýndan iyileþtirildiniz.", GetAccName(playerid));
	SendAdmMessageToPlayer(playerid, "%s adlý oyuncuyu iyileþtirdiniz.", GetNameEx(userid));
	return 1;
}

CMD:gotocar(playerid, params[])
{
	new vehicle, Float:x, Float:y, Float:z;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 3)))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", vehicle))			return SendHelpMessage(playerid, "/gotocar [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

	GetVehiclePos(vehicle, x, y, z);
	SetPlayerPosEx(playerid, x+1, y+1, z);
	SetWorld(playerid, GetVehicleVirtualWorldEx(vehicle));
	SetInterior(playerid, GetVehicleInteriorEx(vehicle));
	SendServerMessage(playerid, "%i ID'li araca ýþýnlandýnýz.", vehicle);
	return 1;
}

alias:specmode("flymode");
CMD:specmode(playerid, params[])
{
	new weapons[12];
	new ammo[12];
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 	return SendNotAdmin(playerid);
	if(FlyMode[playerid]) CancelFlyMode(playerid);
	else
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		{
			for(new x; x < 12; x++)
			{
				BWH_GetPlayerWeaponData(playerid, x, weapons[x], ammo[x]);
				if(!AC_PlayerHasWeapon(playerid, weapons[x]) || !ammo[x])
				{
					weapons[x] = 0;
					ammo[x] = 0;
				}
				PlayerInfo[playerid][pWeapons][x] = weapons[x];
				PlayerInfo[playerid][pAmmo][x] = ammo[x];
			}
		}		
		StartFlyMode(playerid);
	}	
	return 1;
}

CMD:getcar(playerid, params[])
{
	new vehicle, Float:x, Float:y, Float:z, interior = GetInterior(playerid), vw = GetWorld(playerid);

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && !IsTester(playerid, 3) && PlayerInfo[playerid][pFMAdmin] < 1) 	return SendNotAdmin(playerid);
	if (sscanf(params, "d", vehicle)) 			return SendHelpMessage(playerid, "/getcar [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
	if (IsPlayerInVehicle(playerid, vehicle))	return SendErrorMessage(playerid, "Belirtilen araçtasýnýz.");

    GetXYInFrontOfPlayer(playerid, x, y, z, 5.0);
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicle))
	        continue;

		SetPlayerPosEx(i, x, y, z);
		SetInterior(i, interior);
		SetWorld(i, vw);
	}

	SetVehiclePos(vehicle, x, y, z);
	SetVehicleVirtualWorld(vehicle, vw);
	LinkVehicleToInterior(vehicle, interior);
	SendServerMessage(playerid, "%i ID'li aracý kendinize çektiniz.", vehicle);
	return 1;
}

alias:fixveh("carfix", "repaircar");
CMD:fixveh(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", vehicle))			return SendHelpMessage(playerid, "/fixveh [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

	FixVehicle(vehicle);
	SendServerMessage(playerid, "%i ID'li aracý tamir ettiniz.", vehicle);
	return 1;
}

alias:spectate("spec");
CMD:spectate(playerid, params[])
{
	/*new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "(/spec)tate [ID/Karakter Adý]");
	if (userid == playerid)						return SendErrorMessage(playerid, "Kendini izleyemezsin.");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	if (pTemp[playerid][pSpecPlayer] == INVALID_PLAYER_ID) SavePlayerPos(playerid);
	pTemp[playerid][pSpecPlayer] = userid;
    TogglePlayerSpectating(playerid, 1);

	if (IsPlayerInAnyVehicle(userid)) 	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userid));
	else 								PlayerSpectatePlayer(playerid, userid);

	SetInterior(playerid, GetInterior(userid));
	SetWorld(playerid, GetWorld(userid));
	SendServerMessage(playerid, "%s adlý kiþiyi izlemeye baþladýnýz.", GetNameEx(userid));*/

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	new targetid;
	new weapons[12];
	new ammo[12];

	if(sscanf(params, "u", targetid))
		return SendHelpMessage(playerid, "/spec [karakter id/isim]");

	if(targetid == playerid)
		return SendErrorMessage(playerid, "Kendinizi izleyemezsiniz.");
	
	if(targetid == 65535)
		return SendErrorMessage(playerid, "Bir hata oluþtu, ID ile deneyin.");

	if(PlayerInfo[playerid][pAdmin] < PlayerInfo[targetid][pAdmin])
		return SendErrorMessage(playerid, "Bu kiþi sizden daha yetkili, izlemeyezsin.");

	if(!IsPlayerLogged(targetid))
		return SendErrorMessage(playerid, "Karakter çevrimiçi deðil.");

	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	{
		for(new x; x < 12; x++)
		{
			BWH_GetPlayerWeaponData(playerid, x, weapons[x], ammo[x]);
			if(!AC_PlayerHasWeapon(playerid, weapons[x]) || !ammo[x])
			{
				weapons[x] = 0;
				ammo[x] = 0;
			}
			PlayerInfo[playerid][pWeapons][x] = weapons[x];
			PlayerInfo[playerid][pAmmo][x] = ammo[x];
		}
	}

	new Float:paX, Float:paY, Float:paZ, Float:paA;
	GetPlayerPos(playerid, paX, paY, paZ);
	GetPlayerFacingAngle(playerid, paA);

    StaffInfo[playerid][sSpecX] = paX;
	StaffInfo[playerid][sSpecY] = paY;
	StaffInfo[playerid][sSpecZ] = paZ;
	StaffInfo[playerid][sSpecA] = paA;

    new Float:x, Float:y, Float:z, Float:a;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	new int = GetPlayerInterior(playerid);
	new vw = GetPlayerVirtualWorld(playerid);
	SetPVarFloat(playerid, "SpecX", x);
	SetPVarFloat(playerid, "SpecY", y);
	SetPVarFloat(playerid, "SpecZ", z);
	SetPVarFloat(playerid, "SpecA", a);
	SetPVarInt(playerid, "SpecINT", int);
	SetPVarInt(playerid, "SpecVW", vw);	
	DebugMessage(playerid, sprintf("%f, %f, %f", x, y, z));

	Spectate(playerid, SPECTATE_TYPE_PLAYER, targetid);
	SendServerMessage(playerid, "%s adlý kiþiyi izlemeye baþladýnýz.", GetNameEx(targetid));
	if(CheckAdmin(targetid, ADMIN_LEVEL_1)) SendServerMessage(targetid, "%s isimli yönetici seni izliyor.", GetNameEx(playerid));

	return 1;
}

CMD:ifmspec(playerid, params[])
{
	/*new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))			return SendHelpMessage(playerid, "(/spec)tate [ID/Karakter Adý]");
	if (userid == playerid)						return SendErrorMessage(playerid, "Kendini izleyemezsin.");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	if (pTemp[playerid][pSpecPlayer] == INVALID_PLAYER_ID) SavePlayerPos(playerid);
	pTemp[playerid][pSpecPlayer] = userid;
    TogglePlayerSpectating(playerid, 1);

	if (IsPlayerInAnyVehicle(userid)) 	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userid));
	else 								PlayerSpectatePlayer(playerid, userid);

	SetInterior(playerid, GetInterior(userid));
	SetWorld(playerid, GetWorld(userid));
	SendServerMessage(playerid, "%s adlý kiþiyi izlemeye baþladýnýz.", GetNameEx(userid));*/

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && PlayerInfo[playerid][pFMAdmin] == 0)	return SendNotAdmin(playerid);
	new targetid;

	if(sscanf(params, "u", targetid))
		return SendHelpMessage(playerid, "/ifmspec [karakter id/isim]");

	if(targetid == playerid)
		return SendErrorMessage(playerid, "Kendinizi izleyemezsiniz.");

	if(!IsPlayerFactionMafia(targetid) && !IsPlayerFactionGang(targetid))
		return SendErrorMessage(playerid, "Sadece illegal oyuncularý izleyebilirsin.");

	if(PlayerInfo[playerid][pAdmin] < PlayerInfo[targetid][pAdmin])
		return SendErrorMessage(playerid, "Bu kiþi sizden daha yetkili, izlemeyezsin.");

	if(!IsPlayerLogged(targetid))
		return SendErrorMessage(playerid, "Karakter çevrimiçi deðil.");

	new Float:paX, Float:paY, Float:paZ, Float:paA;
	GetPlayerPos(playerid, paX, paY, paZ);
	GetPlayerFacingAngle(playerid, paA);

    StaffInfo[playerid][sSpecX] = paX;
	StaffInfo[playerid][sSpecY] = paY;
	StaffInfo[playerid][sSpecZ] = paZ;
	StaffInfo[playerid][sSpecA] = paA;

    new Float:x, Float:y, Float:z, Float:a;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	new int = GetPlayerInterior(playerid);
	new vw = GetPlayerVirtualWorld(playerid);
	SetPVarFloat(playerid, "SpecX", x);
	SetPVarFloat(playerid, "SpecY", y);
	SetPVarFloat(playerid, "SpecZ", z);
	SetPVarFloat(playerid, "SpecA", a);
	SetPVarInt(playerid, "SpecINT", int);
	SetPVarInt(playerid, "SpecVW", vw);	
	DebugMessage(playerid, sprintf("%f, %f, %f", x, y, z));

	Spectate(playerid, SPECTATE_TYPE_PLAYER, targetid);
	SendServerMessage(playerid, "%s adlý kiþiyi izlemeye baþladýnýz.", GetNameEx(targetid));

	return 1;
}

CMD:speccar(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	new targetid;

	if(sscanf(params, "d", targetid))
		return SendHelpMessage(playerid, "/speccar [araç id]");

	if(!IsValidVehicle(targetid))
		return SendErrorMessage(playerid, "Geçersiz araç numarasý girdiniz.");

	Spectate(playerid, SPECTATE_TYPE_VEHICLE, targetid);

	if(!CheckAdmin(playerid, DEVELOPER_LEVEL)) SendAdmMessage("%s, %s (ID: %d) aracýný izlemeye baþladý.", GetNameEx(playerid), GetVehicleModelName(GetVehicleModel(targetid)), targetid);

	return 1;
}

CMD:specoff(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))				return SendNotAdmin(playerid);
	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) return SendErrorMessage(playerid, "Þu anda spec modunda deðilsiniz.");

	SpectateOff(playerid);
	SendServerMessage(playerid, "Ýzleme modundan çýktý.", GetNameEx(playerid));

	return 1;
}


CMD:izlemeyibirak(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionPolice(faction)) return SendErrorMessage(playerid, "Bu komutu kullanabilmek için polis olmalýsýn.");
	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) return SendErrorMessage(playerid, "Þu anda kamera modunda deðilsiniz.");

	SpectateOff(playerid);
	SendServerMessage(playerid, "Ýzleme modundan çýktý.", GetNameEx(playerid));

	return 1;
}

CMD:aprison(playerid, params[])
{
	//return SendErrorMessage(playerid, "The prison is still disabled!");
	new userid, time, reason[128];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 			 return SendNotAdmin(playerid);
	if (sscanf(params,"uds[128]", userid, time, reason)) return SendHelpMessage(playerid, "/aprison [ID/Karakter Adý] [dakika] [sebep]");
	if (!IsPlayerLogged(userid))						 return SendNotConnected(playerid);
	if (time < 1 || time > 99999)						 return SendErrorMessage(playerid, "Süre 1 ile 99999 dakika arasýnda olmalýdýr.");

	new mes[128];
	format(mes, sizeof(mes), "(( %s adlý oyuncu %s adlý yönetici tarafýndan %s dakika IC hapise gönderildi, Sebep: %s", GetNameEx(userid), GetAccName(playerid), FormatNumber(time), reason);
    SendClientMessageByAdmin(COLOUR_TOMATO, mes);

	PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));
	PlayerInfo[userid][pJailed] = PRISON_JAIL;
	PlayerInfo[userid][pJailTime] = time*60;

	SendHelpMessage(userid, "%s adlý yönetici tarafýndan %s dakika hapise gönderildiniz. Sebep: %s", GetAccName(playerid), FormatNumber(time), reason);
	SendHelpMessage(userid, "Mahkum numaranýz - A%i (/kogusnumaram)", PlayerInfo[playerid][pPrisoned]+100);

	SetPlayerSpawn(userid);
	return 1;
}

CMD:check(playerid, params[])
{
	new option[10], secoption[5];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);

	if (sscanf(params, "s[10]S()[5]", option, secoption))
	{
		SendHelpMessage(playerid, "/check [inv / gb / trunk / prop] [ID]");
		return 1;
	}
	if (CompareStrings(option, "inv"))
	{
		new userid;
		if (sscanf(secoption,"u", userid))			return SendHelpMessage(playerid, "/check inv [ID/Karakter Adý]");
		if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);

		PrintInvEx(userid, playerid);
	}
	else if (CompareStrings(option, "trunk"))
	{
		new vehid;
		if (sscanf(secoption,"i", vehid))		return SendHelpMessage(playerid, "/check trunk [Araç ID]");
		if (vehid < 1 || vehid >= MAX_VEHICLES)	return SendErrorMessage(playerid, "Geçersiz Araç ID");

		PrintVehInv(playerid, vehid, 1);
	}
	else if (CompareStrings(option, "gb"))
	{
		new vehid;
		if (sscanf(secoption,"i", vehid))		return SendHelpMessage(playerid, "/check gb [Araç ID]");
		if (vehid < 1 || vehid >= MAX_VEHICLES)	return SendErrorMessage(playerid, "Geçersiz Araç ID");

		PrintGBInv(playerid, vehid, 1);
	}
	else if (CompareStrings(option, "prop"))
	{
		new houseid;
		if (sscanf(secoption,"i", houseid))			return SendHelpMessage(playerid, "/check prop [Ev ID]");
		if (houseid < 1 || houseid >= MAX_HOUSES)	return SendErrorMessage(playerid, "Geçersiz Ev ID");
		if (!HouseInfo[houseid][hOwnerID])			return SendErrorMessage(playerid, "Bu evin sahibi yok!");

		PrintHouseInv(playerid, houseid, 1);
	}
	else
	{
		SendHelpMessage(playerid, "/check [inv / gb / trunk / prop] [ID]");
	}
	return 1;
}

/*
CMD:checkprop(playerid, params[])
{
	new house, mes[MAX_HOUSE_INVENTORY * 32] = "{ffffff}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?\t{ffffff}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?";

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))							return SendNotAdmin(playerid);
	if (sscanf(params,"d",house))										return SendHelpMessage(playerid, "/checkprop [ID ¯õ?¯õ?¯õ?¯õ?]");
    if (house < 0 || house > MAX_HOUSES || 0 == HouseInfo[house][hID])	return SendErrorMessage(playerid, "¯õ?¯õ?¯õ? ¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?.");

	for(new i = 0; i < MAX_HOUSE_INVENTORY; i++)
	{
		if (HouseInfo[house][pInvItem][i] == 0)	format(mes, sizeof(mes), "%s\n{C3C3C3}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?\t", mes);
		else								format(mes, sizeof(mes), "%s\n%s\t%i", mes, inventory_items[HouseInfo[house][pInvItem][i]][itemName], HouseInfo[house][hInvAmount][i]);
	}

	new housename[MAX_PLAYER_NAME + 24];
	format(housename, sizeof(housename), "{F5DEB3}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?: %s", HouseInfo[house][hOwner]);
	Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, housename, mes, "¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?", "");
	return 1;
}


CMD:checkcar(playerid, params[])
{
	new title[56], vehicle, mes[MAX_TRUNK_INVENTORY * 32] = "{ffffff}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?\t{ffffff}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?";

    if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) 																									return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))																												return SendHelpMessage(playerid, "/checkcar [id ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?]");
    if (!IsValidVehicle(vehicle))																												return SendErrorMessage(playerid, "¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?.");
	if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))	return SendErrorMessage(playerid, "¯õ? ¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?.");

	for(new i; i != MAX_TRUNK_INVENTORY; i++)
	{
	    if (VehicleInfo[vehicle][i][pInvItem] == 0)	format(mes, sizeof(mes), "%s\n{C3C3C3}¯õ?¯õ?¯õ?¯õ?¯õ?¯õ? ¯õ?¯õ?¯õ?¯õ?\t", mes);
		else										format(mes, sizeof(mes), "%s\n%s\t%i", mes, inventory_items[VehicleInfo[vehicle][i][pInvItem]][itemName], VehicleInfo[vehicle][carInvAmount][i]);
	}

	format(title, sizeof(title), "{F5DEB3}%s | ¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?: %s", VehicleNames[GetVehicleModel(vehicle)-400], VehicleInfo[vehicle][carOwner]);
    Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, title, mes, "¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?¯õ?", "");
	return 1;
}*/


CMD:dmlog(playerid,params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);

	if (pTemp[playerid][pDMLog] == 0)
	{
		SendServerMessage(playerid, "DM loglarýný aktif ettiniz.");
		pTemp[playerid][pDMLog] = 1;
	}
	else
	{
		SendServerMessage(playerid, "DM loglarýný deaktif ettiniz");
		ClearKillFeed(playerid);
		pTemp[playerid][pDMLog] = 0;
	}
	return 1;
}

alias:removevehicle("rveh", "dcar", "removecar", "dveh", "rcar");
CMD:removevehicle(playerid,params[])
{
	new vehid = GetPlayerVehicleID(playerid);
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))				return SendNotAdmin(playerid);
	if (!IsValidVehicle(vehid) && sscanf(params,"d",vehid))	return SendHelpMessage(playerid, "/removevehicle [Araç ID]");
    if (!IsValidVehicle(vehid))								return SendErrorMessage(playerid, "Belirtilen araç bulunamadý");

    if (VehicleInfo[vehid][carAdmin] == 0)
	{
	    if (!CheckAdmin(playerid, ADMIN_LEVEL_3))			return SendErrorMessage(playerid, "Bu araç silinemez.");

        new query[256];
	    mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", VehicleInfo[vehid][carID]);
		mysql_tquery(dbHandle, query);
	}

	DestroyVehicleEx(vehid);
	SendServerMessage(playerid, "%i ID'li araç silindi.", vehid);
	return 1;
}

alias:removebox("rbox");
CMD:removebox(playerid, params[])
{
	new id = -1;

    if (!CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);

	for(new i; i != MAX_CARGO_OBJ; i++)
	{
		if (CargoObject[i][oOn] == 0 || !IsPlayerInRangeOfPoint(playerid,2.0,CargoObject[i][oX],CargoObject[i][oY],CargoObject[i][oZ]) || GetWorld(playerid) != CargoObject[i][oVW] || CargoObject[i][oInt] != GetInterior(playerid)) continue;

		id = i;
		break;
	}

	if (id == -1)	return SendErrorMessage(playerid, "Yakýnýnýzda kutu yok.");

	CargoObject[id][oOn] = 0;
 	if (IsValidDynamicObject(CargoObject[id][oObj]))	DestroyDynamicObject(CargoObject[id][oObj]);
	if (IsValidDynamic3DTextLabel(CargoObject[id][oLabel]))
	{
		DestroyDynamic3DTextLabel(CargoObject[id][oLabel]);
	    CargoObject[id][oLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	SendAdmMessageToPlayer(playerid, "Kutu [ID: %i] silindi.", id);
	return 1;
}

CMD:near(playerid, params[])
{
	new id = -1;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !IsTester(playerid, 4)))			return SendNotAdmin(playerid);
	if ((id = Gate_Nearest(playerid)) == -1 && (id = GetNearHouse(playerid)) == -1 && (id = ATM_Nearest(playerid)) == -1 && (id = GetNearGarage(playerid)) == -1 && (id = GetNearApartment(playerid)) == -1 && (id = GetNearBiz(playerid)) == -1 && (id = TruckCargo_Nearest(playerid, 2.0)) == -1 && (id = Object_Nearest(playerid)) == -1 && (id = Job_Nearest(playerid)) == -1 && (id = GetNearestCamera(playerid)) == -1 && (id = Payphone_Nearest(playerid)) == -1 && (id = ParkMeter_Nearest(playerid)) == -1 && (id = GetStreetID(playerid)) == -1 && (id = GetClosestBillBoard(playerid,9.0)) == -1 && (id = Trash_Nearest(playerid, 9.0)) == -1 && (id = Factory_Nearest(playerid, 9.0)) == -1) SendErrorMessage(playerid, "Yakýnýnýzda herhangi bir þey yok.");

	if ((id = Gate_Nearest(playerid)) != -1)			SendSyntaxMessage(playerid, "[GATE] Yakýnýnda bulunan: [ID: %i | Model: %i].", id, Gates[id][gateModel]);
    if ((id = GetNearHouse(playerid)) != -1)			SendSyntaxMessage(playerid, "[EV] Yakýnýnda bulunan: [ID: %i].", id);
    if ((id = ATM_Nearest(playerid)) != -1)				SendSyntaxMessage(playerid, "[ATM] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = GetNearGarage(playerid)) != -1)			SendSyntaxMessage(playerid, "[GARAJ] Yakýnýnda bulunan: [ID: %i].", id);
    if ((id = GetNearApartment(playerid)) != -1)		SendSyntaxMessage(playerid, "[APARTMAN] Yakýnýnda bulunan: [ID: %i].", id);
    if ((id = GetNearBiz(playerid)) != -1)				SendSyntaxMessage(playerid, "[ISLETME] Yakýnýnda bulunan: [ID: %i].", id);
    if ((id = TruckCargo_Nearest(playerid, 2.0)) != -1) SendSyntaxMessage(playerid, "[ENDUSTRI] Yakýnýnda bulunan: [ID: %i].", id);
    if ((id = Object_Nearest(playerid)) != -1)			SendSyntaxMessage(playerid, "[OBJE] Yakýnýnda bulunan: [ID: %i | Model: %i].", id, ObjectsInfo[id][oModel]);
	if ((id = Job_Nearest(playerid)) != -1)				SendSyntaxMessage(playerid, "[JOB] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = GetNearestCamera(playerid)) != -1)		SendSyntaxMessage(playerid, "[SPEEDCAMERA] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = Payphone_Nearest(playerid)) != -1)		SendSyntaxMessage(playerid, "[PAYPHONE] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = ParkMeter_Nearest(playerid)) != -1)		SendSyntaxMessage(playerid, "[PARKMETRE] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = GetStreetID(playerid)) != -1)				SendSyntaxMessage(playerid, "[SIGN STREET] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = GetClosestBillBoard(playerid,9.0)) != -1)	SendSyntaxMessage(playerid, "[BILLBOARD] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = Trash_Nearest(playerid, 9.0)) != -1)		SendSyntaxMessage(playerid, "[GARBAGE TANK] Yakýnýnda bulunan: [ID: %i].", id);
	if ((id = Factory_Nearest(playerid, 9.0)) != -1)	SendSyntaxMessage(playerid, "[GERI DONUSUM FABRIKASI] Yakýnýnda bulunan: [ID: %i].", id);

    for(new i; i != MAX_ENTRANCE; i++)
	{
	    if (EntranceInfo[i][entranceOn] == 0)		continue;

		if (IsPlayerEntranceOutside(playerid, i))	SendSyntaxMessage(playerid, "Giriþe yakýnsýn: [ID: %i].", i);
		if (IsPlayerEntranceInside(playerid, i))	SendSyntaxMessage(playerid, "Çýkýþa yakýnsýn: [ID: %i].", i);
	}

	for(new i = 0; i != MAX_LABELS; i++)
	{
	    if (LabelsInfo[i][tLabelOn] != 1 || !PlayerToPoint(3,playerid,LabelsInfo[i][tPosX],LabelsInfo[i][tPosY],LabelsInfo[i][tPosZ]) || LabelsInfo[i][tVW] != GetWorld(playerid) || LabelsInfo[i][tInt] != GetInterior(playerid)) continue;

		SendSyntaxMessage(playerid, "Belirtilen labela yakýnsýn [ID: %i].", i);
	}

	//SendSyntaxMessage(playerid, "There is nothing near you.");
	return 1;
}

CMD:disarm(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/disarm [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	PlayerInfo[userid][pKamera] = 0;
    PlayerInfo[userid][pCicek] = 0;
	AC_ResetPlayerWeapons(userid);
	SetTimerEx("OnPlayerSetData", 1000, false, "d", userid);
	SendServerMessage(userid, "Yönetici üstündeki silahlarýnýzý sýfýrladý.");
	SendAdmMessageToPlayer(playerid, "%s adlý karakterin üstündeki silahlarýný sýfýrladýnýz.", GetNameEx(userid));
	return 1;
}

alias:teles("atp");
CMD:teles(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	new id;
	if (sscanf(params,"i", id))  pTemp[playerid][pDialogList] = 0;
	else  						pTemp[playerid][pDialogList] = id;

	new string[4096],
		min_tp = pTemp[playerid][pDialogList] * MAX_ADMIN_TELES,
		max_tp = (pTemp[playerid][pDialogList]+1)* MAX_ADMIN_TELES;

	if (pTemp[playerid][pDialogList]) string="{bccd32}Geri{FFFFFF}\n";

	for(new i = min_tp; i < max_tp; i++)
	{
		if (!AdminTeles[i][telesOn]) continue;


		format(string, sizeof(string), "%s<%i>{66FF66}%s\n", string, i, AdminTeles[i][telesMapName]);
	}

	if (AdminTeles[max_tp][telesOn]) format(string, sizeof(string), "%s{bccd32}Ýleri", string);

	Dialog_Show(playerid, AdminTeles, DIALOG_STYLE_LIST,"{FFFFFF}Teleport", string, ">>>", "Ýptal");

	return 1;
}

CMD:checkcars(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/checkcars [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `owner` = '%i'", PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query, "ShowCarsForPlayer", "ii", playerid, userid);
	return 1;
}

CMD:forbid(playerid, params[])
{
	new userid,
		hr;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"ui", userid, hr))		return SendHelpMessage(playerid, "/forbid [ID/Karakter Adý] [saat]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
	if (hr > 10 && hr < 1)						return SendHelpMessage(playerid, "/forbid [ID/Karakter adý] [(1-10) saat]");

	PlayerInfo[userid][pForbid] = hr;
	SQL_SetInteger("users", "Forbid", hr, PlayerInfo[userid][pID]);

	SendServerMessage(userid, "Yönetici %i dakika boyunca silah kullanmanýzý yasakladý. (%i saat).", hr*60, hr);
	SendAdmMessageToPlayer(playerid, "%s adlý oyuncunun %i dakika boyunca silah kullanýmýný yasakladýnýz. (%i saat).", GetNameEx(userid), hr*60, hr);

	return 1;
}

CMD:unforbid(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid)) 			return SendHelpMessage(playerid, "/unforbid [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerInfo[userid][pForbid])			return SendErrorMessage(playerid, "Belirtilen oyuncunun silah kullaným yasaðý yok.");

	PlayerInfo[userid][pForbid] = 0;
	SQL_SetInteger("users", "Forbid", 0, PlayerInfo[userid][pID]);

	SendServerMessage(userid, "Yönetici silah kullaným yasaðýnýzý kaldýrdý");
	SendAdmMessageToPlayer(playerid, "%s adlý kullanýcýnýn silah kullaným yasaðýný kaldýrdýnýz.", GetNameEx(userid));
	return 1;
}

alias:deletepame("dpame");
CMD:deletepame(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	if (sscanf(params,"i",userid)) 	return SendHelpMessage(playerid, "/deletepame [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))		return SendNotConnected(playerid);

	format(PlayerInfo[userid][pDescribe], PAME_MAX_LEN, "NULL");
	format(PlayerInfo[userid][pDescribe2], PAME_MAX_LEN, "NULL");

	SQL_SetString("users", "Desc1", "NULL", PlayerInfo[userid][pID]);
	SQL_SetString("users", "Desc1", "NULL", PlayerInfo[userid][pID]);

	SendAdmMessageToPlayer(playerid, "%s adlý karakterin karakter açýklamasýný sildiniz.", GetNameEx(userid));
	SendServerMessage(userid, "Yönetici karakter açýklamanýzý sildi!");

	return 1;
}