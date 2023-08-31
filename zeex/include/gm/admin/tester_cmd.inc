alias:testerhelp("helperhelp", "hhelp", "helperyardim");
CMD:testerhelp(playerid, params[])
{
	if (PlayerInfo[playerid][pHelper] == 0) return SendNotAdmin(playerid);
	
	if (PlayerInfo[playerid][pHelper] >= 1)
	{
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/hduty, /micperm, /hchat, /agreegraffiti, /sorular");
		SCM(playerid, COLOR_WHITE, "[Level 1]: {C3C3C3}/sorukabul /sorureddet");
	}
	if (PlayerInfo[playerid][pHelper] >= 2)
	{
		SCM(playerid, COLOR_WHITE, "[Level 2]: {C3C3C3}/goto, /gethere, /getcar, /gotocar, /gonder");
	}
	if (PlayerInfo[playerid][pHelper] >= 3)
	{
		SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/goto, /gethere, /getcar, /gotocar, /gonder");
	}	
	if (PlayerInfo[playerid][pHelper] >= 4)
	{
		SCM(playerid, COLOR_WHITE, "[Level 4]: {C3C3C3}/slap, /near, /rtc");
	}	
		if (PlayerInfo[playerid][pHelper] >= 5)
	{
		SCM(playerid, COLOR_WHITE, "[Level 5]: {C3C3C3}/kick, /skick");
	}	
	return 1;
}

CMD:hduty(playerid, params[])
{
	if (PlayerInfo[playerid][pHelper] < 1)	return SendNotAdmin(playerid);
    if (IsAdminDuty(playerid))				return SendErrorMessage(playerid, "Þu an yetkili iþbaþýndasýnýz.");
        
	if (IsTesterDuty(playerid) == 1)
	{
	    StaffMSG(COLOR_LIGHTRED, "AdmCmd: %s adlý kullanýcý helper iþbaþýndan çýktý.", GetAccName(playerid));
	    pTemp[playerid][pTesterDuty] = 0;
		SetPlayerColor(playerid, TEAM_HIT_COLOR);
	}
	else
	{
		pTemp[playerid][pTesterDuty] = 1;
		StaffMSG(COLOR_LIGHTRED, "AdmCmd: %s adlý kullanýcý helper iþbaþýna girdi.", GetAccName(playerid));
		//SetPlayerColor(playerid, HELPER_DUTY);
	}
	return 1;
}

alias:micperm("mikrofonizni");
CMD:micperm(playerid, params[])
{
	new targetid;

	if(sscanf(params, "u", targetid))
		return SendHelpMessage(playerid, "/micperm [karakter id/isim]");
	
	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "Karakter çevrimiçi deðil.");
	
	new perm_status = pTemp[targetid][pMicPerm];

	switch(perm_status)
	{
		case false: StaffMSG(HELPER_DUTY, "%s, %s karakterine mikrofon izni verdi.", GetNameEx(playerid), GetNameEx(targetid));
		case true: StaffMSG(HELPER_DUTY, "%s, %s karakterinin mikrofon iznini aldý.", GetNameEx(playerid), GetNameEx(targetid));
	}

    switch(perm_status)
	{
		case false: pTemp[targetid][pMicPerm] = true;
		case true:  pTemp[targetid][pMicPerm] = false;
	}
	return 1;
}

alias:tchat("h", "/hchat", "/hc");
CMD:tchat(playerid, params[])
{
	if (PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1)	return SendNotAdmin(playerid);
    if (PlayerInfo[playerid][pSettings] & togTester)					return SendErrorMessage(playerid, "Bu komutu kullanabilmek için helper sohbetini açmanýz gerekmektedir.");
	if (isnull(params))													return SendHelpMessage(playerid, "/(h)chat [yazý]");

	new prefix[32] = "Supporter";

	if (PlayerInfo[playerid][pAdmin] == DEVELOPER_LEVEL)			prefix = "Management";
	else if (PlayerInfo[playerid][pAdmin] == HIGH_ADMIN_LEVEL) 		prefix = "Lead Admin";
	else if (PlayerInfo[playerid][pAdmin] == 3)						prefix = "Senior Admin";
	else if (PlayerInfo[playerid][pAdmin] == 2)						prefix = "Liberty Admin";
	else if (PlayerInfo[playerid][pAdmin] == 1)						prefix = "Junior Admin";
	else if (PlayerInfo[playerid][pAdmin] == 1337)					prefix = "Founder";

	if (PlayerInfo[playerid][pHelper] == 1)  prefix = "Supporter I";
	else if (PlayerInfo[playerid][pHelper] == 2)  prefix = "Supporter II";
	else if (PlayerInfo[playerid][pHelper] == 3)  prefix = "Supporter III";
	else if (PlayerInfo[playerid][pHelper] == 4)  prefix = "Supporter IV";
	else if (PlayerInfo[playerid][pHelper] == 5)  prefix = "Supporter V";

	//if (PlayerInfo[playerid][pAdmin] > 0) prefix = "ADMIN";

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;
		
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || (!IsTester(i, 1) && !CheckAdmin(i, ADMIN_LEVEL_1)) || (PlayerInfo[i][pSettings] & togTester)) continue;

			SendClientMessageEx(i, COLOR_ORANGE, "** HChat: (%s) %s (%s): %.*s ...", prefix, GetPlayerNameEx(playerid), GetAccName(playerid), pos, params);
			SendClientMessageEx(i, COLOR_ORANGE, "... %s", params[pos]);
		}
		/*format(mes, sizeof(mes), "[HELPER] [%s] %s(%i): %.*s ...", prefix, GetAccName(playerid), playerid, pos, params);
		SendStaffMessage(COLOR_LIGHTGREEN, mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SendStaffMessage(COLOR_LIGHTGREEN, mes);*/
	}
	else
	{
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || (!IsTester(i, 1) && !CheckAdmin(i, ADMIN_LEVEL_1)) || (PlayerInfo[i][pSettings] & togTester)) continue;

			SendClientMessageEx(i, COLOR_ORANGE, "** HChat: (%s) %s (%s): %s", prefix, GetPlayerNameEx(playerid), GetAccName(playerid), params);
		}
		/*format(mes, sizeof(mes), "[HELPER] [%s] %s(%i): %s", prefix, GetAccName(playerid), playerid, params);
		SendStaffMessage(COLOR_LIGHTGREEN, mes);*/
	}
	return 1;
}
/*alias:togtchat("toghchat");
CMD:togtchat(playerid, params[])
{
	if (!IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);

    if (PlayerInfo[playerid][pSettings] & togTester)
	{
		PlayerInfo[playerid][pSettings] &= ~togTester;
    	SendServerMessage(playerid, "Helper sohbeti þu anda aktif.");
	}
	else
	{
		PlayerInfo[playerid][pSettings] |= togTester;
		SendServerMessage(playerid, "Helper sohbeti þu anda deaktif.");
	}
	return 1;
}*/

alias:agreegraffiti("agr");
CMD:agreegraffiti(playerid, params[])
{
	new option[16], parameters[128];
	if (!IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);
	if (sscanf(params, "s[16]S()[127]", option, parameters))
	{
		SendHelpMessage(playerid, "(/agr)eegraffiti [ayarlar]");
		if (CheckAdmin(playerid, ADMIN_LEVEL_1))
		{
			return SendHelpMessage(playerid, "liste / git / goster / kabul / red / bilgi / sil");
		}
		else
		{
			return SendHelpMessage(playerid, "liste / git / goster / kabul / red");
		}
	}
	if (CompareStrings(option, "liste"))
	{
		return Graffity_GetAcceptList(playerid);
	}
	else if (CompareStrings(option, "git"))
	{
		new grafid;

		if (sscanf(parameters, "d", grafid)) 															 return SendHelpMessage(playerid, "/agreegraffitigoto [ID]");
		if (grafid < 0 || grafid >= MAX_GRAFFITIES || !E_GRAFFITY[grafid][gON])							 return SendErrorMessage(playerid, "Bu ID'ye sahip grafiti bulunamadý.");
		if (IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1) && E_GRAFFITY[grafid][gAccepted]) return SendErrorMessage(playerid, "Onaylanmýþ bir grafitiye ýþýnlamazsýnýz.");

		SetPlayerPosEx(playerid, E_GRAFFITY[grafid][gGotoX], E_GRAFFITY[grafid][gGotoY], E_GRAFFITY[grafid][gGotoZ]);
		SetInterior(playerid, E_GRAFFITY[grafid][gInterior]);
		SetWorld(playerid, E_GRAFFITY[grafid][gVW]);
	}
	else if (CompareStrings(option, "goster"))
	{
		new g_id = Graffity_Nearest(playerid);

		if (g_id == -1) 										return SendErrorMessage(playerid, "Yakýnýnýzda grafiti bulunmuyor.");
		if (E_GRAFFITY[g_id][gAccepted])						return SendErrorMessage(playerid, "Grafitinin dikkate alýnmasýna gerek yok.");
		if (E_GRAFFITY[g_id][gEditing])							return SendErrorMessage(playerid, "Grafiti þu anda düzenleniyor, lütfen biraz bekleyin.");
		if (IsValidDynamicObject(E_GRAFFITY[g_id][gObject])) 	return SendErrorMessage(playerid, "Grafiti zaten var.");

		E_GRAFFITY[g_id][gObject] = CreateDynamicObject(GRAFFITY_OBJECT_ID, E_GRAFFITY[g_id][gPosX], E_GRAFFITY[g_id][gPosY], E_GRAFFITY[g_id][gPosZ], E_GRAFFITY[g_id][gRotX], E_GRAFFITY[g_id][gRotY], E_GRAFFITY[g_id][gRotZ], E_GRAFFITY[g_id][gVW], E_GRAFFITY[g_id][gInterior]);
    	SetDynamicObjectMaterial(E_GRAFFITY[g_id][gObject], 0, 0, "none", "none", 0);
    	SetDynamicObjectMaterialText(E_GRAFFITY[g_id][gObject], 0, E_GRAFFITY[g_id][gText], OBJECT_MATERIAL_SIZE_256x32, E_GRAFFITY[g_id][gFont], E_GRAFFITY[g_id][gFontSize], E_GRAFFITY[g_id][gBold], E_GRAFFITY[g_id][gColor], E_GRAFFITY[g_id][gBackColor], 0);
		SetPVarInt(playerid, "Tester:Graffity", g_id+1);
		SetPVarInt(playerid, "Tester:GraffityTime", 10);
		SendServerMessage(playerid, "10 saniye sonra grafiti kaybolacaktýr.");
	}
	else if (CompareStrings(option, "kabul"))
	{
		new g_id = Graffity_Nearest(playerid);

		if (g_id == -1) 				 return SendErrorMessage(playerid, "Yakýnýnýzda grafiti bulunmuyor.");
		if (E_GRAFFITY[g_id][gAccepted]) return SendErrorMessage(playerid, "Grafitinin dikkate alýnmasýna gerek yok.");
		if (E_GRAFFITY[g_id][gEditing])	 return SendErrorMessage(playerid, "Grafiti þu anda düzenleniyor, lütfen biraz bekleyin.");
		
		Graffity_Accept(g_id, playerid);
		return 1;
	}
	else if (CompareStrings(option, "red"))
	{
		new g_id = Graffity_Nearest(playerid);

		if (g_id == -1)					 return SendErrorMessage(playerid, "Yakýnýnýzda grafiti bulunmuyor.");
		if (E_GRAFFITY[g_id][gAccepted]) return SendErrorMessage(playerid, "Grafitinin dikkate alýnmasýna gerek yok.");
		if (E_GRAFFITY[g_id][gEditing])	 return SendErrorMessage(playerid, "Grafiti þu anda düzenleniyor, lütfen biraz bekleyin.");

		Graffity_Decline(g_id, playerid);
		return 1;
	}
	else if (CompareStrings(option, "bilgi"))
	{
		new g_id = Graffity_Nearest(playerid);

		if (IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);
		if (g_id == -1)												   	return SendErrorMessage(playerid, "Yakýnýnýzda grafiti bulunmuyor.");
		if (E_GRAFFITY[g_id][gEditing])								 	return SendErrorMessage(playerid, "Grafiti þu anda düzenleniyor, lütfen biraz bekleyin.");

		new msg[1024] = "{FFFFFF}", msgcat[128];
		format(msg, sizeof(msg), "{FFFFFF}Grafiti ID\t%d\nOluþturan\t%s\nOluþturulma Tarihi\t%s\nFont\t%s\n", g_id, E_GRAFFITY[g_id][gCreator], E_GRAFFITY[g_id][gCreateDate], E_GRAFFITY[g_id][gFont]);
		if (E_GRAFFITY[g_id][gAccepted])
		{
			format(msgcat, sizeof(msgcat), "	\nOnaylý\t%s\nOnay Tarihi\t%s\n", E_GRAFFITY[g_id][gAcceptor], E_GRAFFITY[g_id][gAcceptDate]); //î
		}
		strcat(msg, msgcat);

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST, "{FFFFFF}Grafiti Bilgisi", msg, "Kapat", "");
	}
	else if (CompareStrings(option, "sil"))
	{
		new g_id;

		if (IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1))		return SendNotAdmin(playerid);
		if (sscanf(parameters, "d", g_id)) 									return SendErrorMessage(playerid, "/agreegraffitidestroy [ID]");
		if (g_id < 0 || g_id >= MAX_GRAFFITIES || !E_GRAFFITY[g_id][gON])	return SendErrorMessage(playerid, "Bu ID'ye sahip grafiti bulunamadý.");
		if (E_GRAFFITY[g_id][gEditing])										return SendErrorMessage(playerid, "Grafiti þu anda düzenleniyor, lütfen biraz bekleyin.");
		if (!E_GRAFFITY[g_id][gAccepted])									return SendErrorMessage(playerid, "Grafiti henüz onaylanmadý. Kaldýrmak istiyorsanýz /gr komutunu kullanýn.");
		
		Graffity_Destroy(g_id);
		SendServerMessage(playerid, "Belirtilen grafiti kaldýrýldý: [ID: %i]", g_id);
	}
	else 
	{
		SendHelpMessage(playerid, "/agreegraffiti [ayarlar]");
		if (CheckAdmin(playerid, ADMIN_LEVEL_1))
		{
			return SendHelpMessage(playerid, "liste / git / goster / kabul / red / bilgi / sil");
		}
		else
		{
			return SendHelpMessage(playerid, "liste / git / goster / kabul / red");
		}
	}
	return 1;
}

CMD:talepkontrol(playerid) 
{
	if(PlayerInfo[playerid][pHelperLead] != 1) return SendErrorMessage(playerid, "Bu komuta sadece Lead Helper yetkilileri yetiþebilir.");

	new Cache:veri = mysql_query(dbHandle, "SELECT login, talepsayi FROM accounts WHERE helper > 0");
	new rows = cache_num_rows(), adminUser[MAX_PLAYER_NAME], adminPuan, adminPuanString[2048];
	if(!rows) return SendErrorMessage(playerid, "Veri bulunamadý.");
	for(new i; i < rows; i++) {
		cache_get_value_int(i, "talepsayi", adminPuan);
		cache_get_value(i, "login", adminUser, 36);
		format(adminPuanString, sizeof adminPuanString, "%s%s\t%d\n", adminPuanString, adminUser, adminPuan);
	}
	Dialog_Show(playerid, DialogAdminPuanKontrol, DIALOG_STYLE_TABLIST_HEADERS, "Supporter Skor Tablosu", "Supporter Adý\tSupporter Puaný\n%s", "Tamam", "", adminPuanString);
	cache_delete(veri);
	veri = MYSQL_INVALID_CACHE;
	return 1;
}

CMD:raporbakanlar(playerid) 
{
	if(PlayerInfo[playerid][pAdmin] < 4) return SendErrorMessage(playerid, "Bu komuta sadece helper yetkilileri yetiþebilir.");

	new Cache:veri = mysql_query(dbHandle, "SELECT login, raporsayi FROM accounts WHERE admin > 0");
	new rows = cache_num_rows(), adminUser[MAX_PLAYER_NAME], adminPuan, adminPuanString[2048];
	if(!rows) return SendErrorMessage(playerid, "Veri bulunamadý.");
	for(new i; i < rows; i++) {
		cache_get_value_int(i, "raporsayi", adminPuan);
		cache_get_value(i, "login", adminUser, 36);
		format(adminPuanString, sizeof adminPuanString, "%s%s\t%d\n", adminPuanString, adminUser, adminPuan);
	}
	Dialog_Show(playerid, DialogAdminPuanKontrol, DIALOG_STYLE_TABLIST_HEADERS, "Admin Skor Tablosu", "Admin Adý\tAdmin Puaný\n%s", "Tamam", "", adminPuanString);
	cache_delete(veri);
	veri = MYSQL_INVALID_CACHE;
	return 1;
}