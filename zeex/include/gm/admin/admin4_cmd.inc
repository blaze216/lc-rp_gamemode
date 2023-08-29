CMD:streamer(playerid, params[])
{
	new objects;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	SendNotAdmin(playerid);

	if (sscanf(params, "i", objects))
	{
		SendHelpMessage(playerid, "/streamer [obje sayýsý]");
		SendSyntaxMessage(playerid, "Geçerli nesne sayýsý: %i", Streamer_GetVisibleItems(STREAMER_TYPE_OBJECT));
		return 1;
	}
	if (objects < 1 || objects > 1499)	return SendErrorMessage(playerid, "Obje sayýsý 1 ile 1499 arasýnda olmalýdýr.");

	new Float:x, Float:y, Float:z;

    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, objects);

    foreach(new i : Player)
	{
		if (!IsPlayerLogged(i))	continue;

		GetPlayerPos(i, x, y, z);
		Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_OBJECT);
		Streamer_UpdateEx(i, x, y, z, -1, -1, STREAMER_TYPE_OBJECT);
	}
	return 1;
}

alias:cekilisyap("cekilis");
CMD:cekilisyap(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return	SendNotAdmin(playerid);
	if(isnull(params))
	{
		new cekilis = getRandomPlayer();

		if(!IsPlayerConnected(cekilis) || playerid == cekilis) return SendErrorMessage(playerid, "Çekiliþ baþarýsýz, tekrar deneyin.");

		foreach(new j : Player)
		{
			if(!IsPlayerConnected(j))continue;
			SendClientMessageEx(j, COLOR_LIGHTRED, "%s elini torbaya soktu ve karýþtýrýyor. Çekiliþi kazanan: %s", GetAccName(playerid), GetNameEx(cekilis));
		}
	}
	if(!isnull(params) && PlayerInfo[playerid][pAdmin] > 2)
	{
		new option[10], Float:menzil;
		if(sscanf(params, "s[10]f", option, menzil))
			return SendSyntaxMessage(playerid, "/cekilisyap <menzil> <35.0 - 120.0>");

		if(!strcmp(option, "menzil", true))
		{
			if(menzil < 5.0)
				return SendSyntaxMessage(playerid, "/cekilisyap <menzil> <35.0 - 120.0>");

			new cekilis = CekilisMesafe(playerid, menzil);

			if(!IsPlayerConnected(cekilis) || playerid == cekilis)
				return SendErrorMessage(playerid, "Çekiliþ baþarýsýz, tekrar deneyin.");

			new Float: x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			new vw = GetPlayerVirtualWorld(playerid);

			foreach(new j : Player)
			{
				if(!IsPlayerConnected(j))continue;
				if(GetPlayerVirtualWorld(j) != vw || !IsPlayerInRangeOfPoint(j, menzil, x, y, z))continue;

				SendClientMessageEx(j, COLOR_LIGHTRED, "%s elini torbaya soktu ve karýþtýrýyor. Çekiliþi kazanan: %s", GetAccName(playerid), GetNameEx(cekilis));
			}
		}
		else SendSyntaxMessage(playerid, "/cekilisyap <menzil> <35.0 - 120.0>");
	}
	return 1;
}

CMD:setstat(playerid, params[])
{
	new userid, option[16], secoption[64];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return	SendNotAdmin(playerid);

	if (sscanf(params, "us[16]s[10]", userid, option, secoption))
	{
		SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] [ayarlar] [deðer]");
		SendSyntaxMessage(playerid, "level/sex/bank/hours/money/druglabaccess/exp"); //exp
		SendSyntaxMessage(playerid, "carlic/weplic/flylic/taxilic/whours/lawlic");
		SendSyntaxMessage(playerid, "race(ten rengi)/origin(köken)/job/age");
		return 1;
	}

	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);

	if (CompareStrings(option, "level"))
	{
		new level;

		if (sscanf(secoption, "i", level))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] level [seviye]");
		if (level <= 1 || level > 100)		return SendErrorMessage(playerid, "Seviye 1 ve 100 arasýnda olmalýdýr.");

		PlayerInfo[userid][pLevel] = level;
		SQL_SetInteger("users", "level", PlayerInfo[userid][pLevel], PlayerInfo[userid][pID]);
		SetPlayerScore(userid, PlayerInfo[userid][pLevel]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþinin seviyesini deðiþtirdi [ID: %i] -> %i.", GetNameEx(playerid), GetNameEx(userid), userid, level);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici, seviyenizi %i olarak deðiþtirdi.", GetAccName(playerid), level);
		return 1;
	}

	if (CompareStrings(option, "druglabaccess"))
	{
		new level;

		if (sscanf(secoption, "i", level))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] druglabaccess [seviye]");
		if (level <= 0 || level > 1)		return SendErrorMessage(playerid, "Eriþim seviyesi 0 veya 1 olmalýdýr.");

		PlayerInfo[userid][pDrugLabAccess] = level;
		SQL_SetInteger("users", "drugaccess", PlayerInfo[userid][pDrugLabAccess], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý oyuncunun uyuþturucu laboratuvarýna eriþim düzeyini deðiþtirdi. Yeni deðer: %i.", GetNameEx(playerid), GetNameEx(userid), userid, level);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici uyuþturucu laboratuvarýna eriþim düzeyinizi deðiþtirdi. Yeni deðer: %i.", GetAccName(playerid), level);
		return 1;
	}
	
	else if (CompareStrings(option, "exp"))
	{
		new exp;

		if (sscanf(secoption, "i", exp))	return SendHelpMessage(playerid, "/setstat [ID / isim] exp [Experience points]");
		if (exp < 0 || exp > 8192)		return SendErrorMessage(playerid, "0 ile 8192 arasý olmalýdýr.");

		PlayerInfo[userid][pExp] = exp;
		SQL_SetInteger("users", "exp", PlayerInfo[userid][pExp], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s adlý oyuncunun EXP deðerini deðiþtirdi: [ID: %i] - %i.", GetNameEx(playerid), GetNameEx(userid), userid, exp);
		SendSyntaxMessage(userid, "%s adlý yönetici EXP deðerinizi %i olarak belirledi.", GetAccName(playerid), exp);
		return 1;
	}

	else if (CompareStrings(option, "job"))
	{
		new job;

		if (sscanf(secoption, "i", job))	return SendHelpMessage(playerid, "/setstat [ID / isim] job [job id]");
		if (job < 0 || job > MAX_JOBS_TYPES)		return SendErrorMessage(playerid, "0 ile %d arasý olmalýdýr.", MAX_JOBS_TYPES);

		PlayerInfo[userid][pJob] = job;
		PlayerInfo[userid][pCareer] = 0;
		SQL_SetInteger("users", "job", PlayerInfo[userid][pJob], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s adlý oyuncunun meslek deðerini deðiþtirdi: [ID: %i] - %i.", GetNameEx(playerid), GetNameEx(userid), userid, job);
		SendSyntaxMessage(userid, "%s adlý yönetici meslek deðerinizi %i olarak belirledi.", GetAccName(playerid), job);
		return 1;
	}	

	else if (CompareStrings(option, "age"))
	{
		new age;

		if (sscanf(secoption, "i", age))	return SendHelpMessage(playerid, "/setstat [ID / isim] age [yaþ]");
		if (age < 0 || age > 100)		return SendErrorMessage(playerid, "Yaþ 0 ile 100 arasýnda olmalý.");

		PlayerInfo[userid][pAge] = age;
		SQL_SetInteger("users", "age", PlayerInfo[userid][pAge], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s adlý oyuncunun yaþýný deðiþtirdi: [ID: %i] - %i.", GetNameEx(playerid), GetNameEx(userid), userid, age);
		SendSyntaxMessage(userid, "%s adlý yönetici yaþýnýzý %i olarak belirledi.", GetAccName(playerid), age);
		return 1;
	}		

	else if (CompareStrings(option, "sex"))
	{
		new sex;

		if (sscanf(secoption, "i", sex))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] sex [1 - erkek | 2 - kadýn]");
		if (sex < 1 || sex > 2) 			return SendErrorMessage(playerid, "Cinsiyet 1 veya 2 olmalýdýr.");

		PlayerInfo[userid][pSex] = sex;
		SQL_SetInteger("users", "sex", PlayerInfo[userid][pSex], PlayerInfo[userid][pID]);

		new sex_naming[16];

		if (sex == 1)	format(sex_naming, sizeof(sex_naming), "Erkek");
		else 			format(sex_naming, sizeof(sex_naming), "Kadýn");

		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý karakterin cinsiyetini deðiþtirdi. Yeni cinsiyet: %s.", GetNameEx(playerid), GetNameEx(userid), userid, sex_naming);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici cinsiyetinizi deðiþtirdi. Yeni cinsiyet: %s.", GetAccName(playerid), sex_naming);
		return 1;
	}

	else if (CompareStrings(option, "race"))
	{
		new race;

		if (sscanf(secoption, "i", race))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] race [1 - beyaz | 2 - siyah]");
		if (race < 1 || race > 2) 			return SendErrorMessage(playerid, "Seçenek 1 veya 2 olmalýdýr.");

		PlayerInfo[userid][pRace] = race;
		SQL_SetInteger("users", "race", PlayerInfo[userid][pRace], PlayerInfo[userid][pID]);

		new race_naming[16];

		if (race == 1)	format(race_naming, sizeof(race_naming), "Beyaz");
		else 			format(race_naming, sizeof(race_naming), "Siyahi");

		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý karakterin ten rengini deðiþtirdi. Yeni cinsiyet: %s.", GetNameEx(playerid), GetNameEx(userid), userid, race_naming);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici ten renginizi deðiþtirdi. Yeni cinsiyet: %s.", GetAccName(playerid), race_naming);
		return 1;
	}	

	else if (CompareStrings(option, "origin"))
	{
		new origin;

		if (sscanf(secoption, "i", origin))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] origin [Origin ID]");

		PlayerInfo[userid][pOrigin] = origin;
		SQL_SetInteger("users", "origin", PlayerInfo[userid][pOrigin], PlayerInfo[userid][pID]);

		new origin_naming[32];

		if (origin > 0)	format(origin_naming, sizeof(origin_naming), "%s", GetOriginName(origin));

		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý karakterin kökenini deðiþtirdi. Yeni köken: %s.", GetNameEx(playerid), GetNameEx(userid), userid, origin_naming);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici kökeninizi deðiþtirdi. Yeni köken: %s.", GetAccName(playerid), origin_naming);
		return 1;
	}	

	else if (CompareStrings(option, "bank"))
	{
		new abank;

		if (sscanf(secoption, "i", abank))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] bank [miktar]");
		if (abank < 0 || abank > 50000000)	return SendErrorMessage(playerid, "Miktar $0 ile $50.000.000 arasýnda olmalýdýr.");

		PlayerInfo[userid][pBank] = abank;
		SQL_SetInteger("users", "bank", PlayerInfo[userid][pBank], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý karakterin banka hesabýný düzenledi. Yeni deðer: $%i.", GetNameEx(playerid), GetNameEx(userid), userid, abank);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici banka paranýzý deðiþtirdi. Yeni miktar: $%i.", GetAccName(playerid), abank);

		new mes[128];
		format(mes, sizeof(mes), "[/givemoney] %s adlý yönetici %s adlý oyuncunun banka parasýný deðiþtirdi: $%i.", GetAccName(playerid), GetNameEx(userid), abank);
		insert_log(mes, ADMIN_LOG, 8, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);
		return 1;
	}

	else if (CompareStrings(option, "hours"))
	{
		new hor;

		if (sscanf(secoption, "i", hor))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] hours [oynama saati]");
		if (hor < 0 || hor > 8192)			return SendErrorMessage(playerid, "Belirtilen saat 0 ile 8192 arasýnda olmalýdýr.");

		PlayerInfo[userid][pHours] = hor;
		SQL_SetInteger("users", "hours", PlayerInfo[userid][pHours], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý oyuncunun oynama saatini deðiþtirdi. Yeni deðer: %i.", GetNameEx(playerid), GetNameEx(userid), userid, hor);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici oynama saatinizi deðiþtirdi. Yeni deðer: %i.", GetAccName(playerid), hor);
		return 1;
	}

	/*else if (CompareStrings(option, "cash"))
	{
		new acash;

		if (sscanf(secoption, "i", acash))	return SendHelpMessage(playerid, "/setstat [ID / isim] cash [money]");
		if (acash < 0 || acash > 50000000)	return SendErrorMessage(playerid, "Ñóììà from $0 to $50000000.");

		SetCash(userid, acash);
		SQL_SetInteger("users", "cash", PlayerInfo[userid][pCash], PlayerInfo[userid][pID]);
		SendAdmMessage("%s èçìåíèë(à) êîëè÷åñòâî äåíåã to ðóêàõ %s [ID: %i] to $%i.", GetNameEx(playerid), GetNameEx(userid), userid, acash);
		SendSyntaxMessage(userid, "Administrator %s èçìåíèë(à) Âàøè äåíüãè to ðóêàõ to $%i.", GetAccName(playerid), acash);
		return 1;
	}*/

	else if (CompareStrings(option, "carlic"))
	{
		new lic;
		
		if (sscanf(secoption, "i", lic)) return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] carlic [0 - took away | 1 - issued]");
		if (lic < 0 || lic > 1)			 return SendErrorMessage(playerid, "Deðer 0 ile 1 arasýnda olmalýdýr.");

		PlayerInfo[userid][pCarLic] = lic;
		SQL_SetInteger("users", "carlic", PlayerInfo[userid][pCarLic], PlayerInfo[userid][pID]);

		new lic_name[16];

		if (PlayerInfo[userid][pCarLic])	format(lic_name, sizeof(lic_name), "issued");
		else 								format(lic_name, sizeof(lic_name), "took away");

		SendAdmMessage("%s %s rights %s [ID: %i].", GetNameEx(playerid), lic_name, GetNameEx(userid), userid);
		SendAdmMessageToPlayer(userid, "Administrator %s %s %s rights.", GetAccName(playerid), lic_name, (PlayerInfo[userid][pCarLic]) ? ("Your") : ("You"));
		return 1;
	}

	else if (CompareStrings(option, "flylic"))
	{
		new lic;

		if (sscanf(secoption, "i", lic)) return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] flylic [0 - took away | 1 - issued | 2 - Blacklist]");
		if (lic < 0 || lic > 2)			 return SendSyntaxMessage(playerid, "Deðer 0 ile 2 arasýnda olmalýdýr.");

		PlayerInfo[userid][pFlyLic] = lic;
		SQL_SetInteger("users", "flylic", PlayerInfo[userid][pFlyLic], PlayerInfo[userid][pID]);

		new lic_name[20];

		switch(PlayerInfo[userid][pFlyLic])
		{
			case 0: format(lic_name, sizeof(lic_name), "took away");
			case 1: format(lic_name, sizeof(lic_name), "issued");
			case 2: format(lic_name, sizeof(lic_name), "added to blacklist");
		}

		SendAdmMessage("%s %s pilot's license %s [ID: %i].", GetNameEx(playerid), lic_name, GetNameEx(userid), userid);
		SendAdmMessageToPlayer(userid, "Administrator %s %s %s pilot's license.", GetAccName(playerid), lic_name, (PlayerInfo[userid][pFlyLic]) ? ("Your") : ("You"));
		return 1;
	}

	else if (CompareStrings(option, "taxilic"))
	{
		new lic;

		if (sscanf(secoption, "i", lic))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] taxilic [0 - geri al | 1 - ver | 2 - blacklist]");
		if (lic < 0 || lic > 2)			return SendSyntaxMessage(playerid, "Deðer 0 ile 2 arasýnda olmalýdýr.");

		PlayerInfo[userid][pTaxiLic] = lic;
		SQL_SetInteger("users", "taxilic", PlayerInfo[userid][pTaxiLic], PlayerInfo[userid][pID]);

		new lic_name[20];

		switch(PlayerInfo[userid][pTaxiLic])
		{
			case 0: format(lic_name, sizeof(lic_name), "geri aldý");
			case 1: format(lic_name, sizeof(lic_name), "verdi");
			case 2: format(lic_name, sizeof(lic_name), "karalisteye ekledi");
		}

		SendAdmMessage("%s kiþinin lisansýný %s: %s [ID: %i].", GetNameEx(playerid), lic_name, GetNameEx(userid), userid);
		SendAdmMessageToPlayer(userid, "%s adlý yönetici taksi lisansýný %s.", GetAccName(playerid), lic_name);
		return 1;
	}

	else if (CompareStrings(option, "lawlic"))
	{
		new lic;

		if (sscanf(secoption, "i", lic)) return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] lawlic [0 - almak | 1 - vermek ]");
		if (lic < 0 || lic > 1)			 return SendSyntaxMessage(playerid, "Deðer 0 ile 1 arasýnda olmalýdýr.");

		PlayerInfo[userid][pLawyer] = lic;
		SQL_SetInteger("users", "lawyer", PlayerInfo[userid][pLawyer], PlayerInfo[userid][pID]);

		new lic_name[20];

		switch(PlayerInfo[userid][pLawyer])
		{
			case 0: format(lic_name, sizeof(lic_name), "aldý");
			case 1: format(lic_name, sizeof(lic_name), "verdi");
		}

		SendAdmMessage("%s adlý yönetici %s(%d) adlý kiþiye avukat lisansýný %s.", GetNameEx(playerid), GetNameEx(userid), userid, lic_name);
		SendAdmMessageToPlayer(userid, "Yönetici %s, %s %s.", GetAccName(playerid), (PlayerInfo[userid][pFlyLic]) ? ("Senin") : ("Sen"), lic_name);
		return 1;
	}

	else if (CompareStrings(option, "weplic"))
	{
		new lic;

		if (sscanf(secoption, "i", lic))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] weplic [0 - geri aldý | 1 - verdi]");
		if (lic < 0 || lic > 1)			return SendSyntaxMessage(playerid, "Deðer 0 ile 1 arasýnda olmalýdýr.");

		PlayerInfo[userid][pWepLic] = lic;
		SQL_SetInteger("users", "weplic", PlayerInfo[userid][pWepLic], PlayerInfo[userid][pID]);

		new lic_name[16];

		if (PlayerInfo[userid][pWepLic])	format(lic_name, sizeof(lic_name), "verdi");
		else							format(lic_name, sizeof(lic_name), "geri aldý");

		SendAdmMessage("%s silah lisansýný %s: %s [ID: %i].", GetNameEx(playerid), lic_name, GetNameEx(userid), userid);
		SendAdmMessageToPlayer(userid, "%s adlý yetkili silah lisansýnýzý %s.", GetAccName(playerid), lic_name);
		return 1;
	}

	else if (CompareStrings(option, "whours"))
	{
		new whours;

		if (sscanf(secoption, "i", whours))	return SendHelpMessage(playerid, "/setstat [ID/Karakter Adý] whours [deðer]");
		if (whours < 0 || whours > 256)		return SendErrorMessage(playerid, "Kariyer saati deðeri 0 ile 256 arasýnda olmalýdýr.");

		PlayerInfo[userid][pCareer] = whours;
		SQL_SetInteger("users", "career", PlayerInfo[userid][pCareer], PlayerInfo[userid][pID]);
		SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý kiþinin kariyer saatini deðiþtirdi. Yeni Deðer: %i.", GetNameEx(playerid), GetNameEx(userid), userid, whours);
		SendAdmMessageToPlayer(playerid, "%s adlý yönetici kariyer saatini deðiþtir. Yeni Saat: %i.", GetAccName(playerid), whours);
	}
	return 1;
}

CMD:gmx(playerid, params[])
{
	new time;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (restart_time)
	{
		SAMALL("%s adlý yönetici tarafýndan sunucu restartý iptal edildi.", GetAccName(playerid));

		restart_time = 0;
	    return 1;
	}

	if (sscanf(params, "i", time)) 	return SendHelpMessage(playerid, "/gmx [saniye]");
	if (time < 10 || time > 300)	return SendErrorMessage(playerid, "Restart saniyesi 0 ile 300 arasýnda bir deðer olmalýdýr.");

    restart_time = time;

	SAMALL("%s adlý yönetici tarafýndan restart planlandý. %i saniye içinde restart atýlacak.", GetAccName(playerid), time);
	return 1;
}

CMD:copstocrime(playerid, params[])
{
	new amount;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "d", amount))			return SendHelpMessage(playerid, "/copstocrime [deðer]");
	if (amount < 0)								return SendErrorMessage(playerid, "Negatif bir deðer giremezsiniz!");

	NEED_COPS_TO_CRIME = amount;
	SendAdmMessage("%s adlý yönetici polis sayý durumunu deðiþtirdi. Yeni Deðer: %i.", GetAccName(playerid), amount);
	return 1;
}

CMD:firetocrime(playerid, params[])
{
	new amount;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "d", amount))			return SendHelpMessage(playerid, "/firetocrime [miktar]");
	if (amount < 0)								return SendErrorMessage(playerid, "Negatif bir deðer giremezsiniz!");

	NEED_FIRE_TO_CRIME = amount;
	SendAdmMessage("%s adlý yönetici yangýn departmaný sayý durumunu deðiþtirdi. Yeni Deðer: %i.", GetAccName(playerid), amount);
	return 1;
}

alias:admin("setadmin");
CMD:admin(playerid, params[])
{
	new userid, level;
	if (PlayerInfo[playerid][pAdmin] < 1337)			return SendNotAdmin(playerid);
	//if (!CheckAdmin(playerid, DEVELOPER_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params, "ud", userid, level))		return SendHelpMessage(playerid, "/admin [ID/Karakter Adý] [seviye]");
	if(level > 5 || level < 0)						return SendErrorMessage(playerid, "Yönetim seviyesi 0 ile 5 arasýnda olmalýdýr.");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	//if (userid == playerid)							return 1;
	if (!level && !PlayerInfo[userid][pAdmin])		return SendErrorMessage(playerid, "Belirtilen kullanýcý için bu iþlemi uygulayamazsýnýz.");
	
	/*if (PlayerInfo[userid][pAdmin] == HIGH_ADMIN_LEVEL) {
		if (level < 0 || level > HIGH_ADMIN_LEVEL-1)	return SendErrorMessage(playerid, "Yönetim seviyesi 0 ile 3 arasýnda olmalýdýr.");
	} else if (PlayerInfo[userid][pAdmin] == DEVELOPER_LEVEL) {
		if (level < 0 || level > HIGH_ADMIN_LEVEL)		return SendErrorMessage(playerid, "Yönetim seviyesi 0 ile 4 arasýnda olmalýdýr.");
	}*/

	if (!level)
	{
		if (IsAdminDuty(userid)) pc_cmd_awork(userid, "");
		
		SendAdmMessage("%s adlý yönetici %s adlý kiþinin yetkilerini aldý.", GetAccName(playerid), GetAccName(userid));
		SendServerMessage(userid, "%s adlý yönetici yetkilerinizi aldý.", GetAccName(playerid));
		PlayerInfo[userid][pAdmin] = 0;
		SQL_SetIntegerAcc("accounts", "admin", PlayerInfo[userid][pAdmin], PlayerInfo[userid][pAccID]);		
		return 1;
	}

	PlayerInfo[userid][pAdmin] = level;
	SQL_SetIntegerAcc("accounts", "admin", PlayerInfo[userid][pAdmin], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþinin yetkisi güncellendi. Yeni Seviye: %i", GetAccName(playerid), GetNameEx(userid), level);
	SendServerMessage(userid, "%s adlý yönetici yetkinizi güncellendi. Yeni Seviye: %i", GetAccName(playerid), level);
	return 1;
}

CMD:makepremium(playerid, params[])
{
	new userid, rank;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params, "ui", userid, rank))		return SendHelpMessage(playerid, "/makepremium [ID/Karakter Adý] [0-3]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (rank < 0 || rank > 3)					return SendErrorMessage(playerid, "Deðer 0 ile 3 arasýnda olmalýdýr.");

	new status_premium[4][32] = {"normal", "bronz", "silver", "gold"};

	PlayerInfo[userid][pPremium] = rank;
	PlayerInfo[userid][pPremiumTime] = gettime() + 30 * 86400;
	SQL_SetInteger("users", "vip", PlayerInfo[userid][pPremium], PlayerInfo[userid][pID]);
	SQL_SetInteger("users", "vip_time", PlayerInfo[userid][pPremiumTime], PlayerInfo[userid][pID]);
	SQL_SetFloat("users", "spawnhealth", 75.0, PlayerInfo[userid][pID]);
	
	SendAdmMessage("%s adlý yönetici %s adlý karakterin hesap statüsünü güncellendi. Yeni Deðer: %s", GetAccName(playerid), GetAccName(userid), status_premium[rank]);
	SendServerMessage(userid, "%s adlý yönetici hesap statünüzü güncellendi. Yeni Statü: %s", GetAccName(playerid), status_premium[rank]);
	return 1;
}

CMD:helperlead(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/helperlead [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pHelperLead]){
		PlayerInfo[userid][pHelperLead] = 0;
		SQL_SetIntegerAcc("accounts", "helperlead", PlayerInfo[userid][pHelperLead], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiyi Head Of Supporter yetkilerini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin Head Of Supporter yetkilerini aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pHelperLead] = 1;
	SQL_SetIntegerAcc("accounts", "helperlead", PlayerInfo[userid][pHelperLead], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi Head Of Supporter yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi Head Of Supporter yaptý.", GetAccName(playerid));

	return 1;
}

CMD:fmadmin(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/fmadmin [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pFMAdmin]){
		PlayerInfo[userid][pFMAdmin] = 0;
		SQL_SetIntegerAcc("accounts", "fmadmin", PlayerInfo[userid][pFMAdmin], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiyi FM Admin yetkilerini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin FM Admin Supporter yetkilerini aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pFMAdmin] = 1;
	SQL_SetIntegerAcc("accounts", "fmadmin", PlayerInfo[userid][pFMAdmin], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi FM Admin yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi FM Admin yaptý.", GetAccName(playerid));

	return 1;
}

CMD:setmapper(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/setmapper [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pMapper]){
		PlayerInfo[userid][pMapper] = 0;
		SQL_SetIntegerAcc("accounts", "mapper", PlayerInfo[userid][pMapper], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiden mapper yetkisini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin mapper yetkilerinizi aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pMapper] = 1;
	SQL_SetIntegerAcc("accounts", "mapper", PlayerInfo[userid][pMapper], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi mapper yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi mapper yaptý.", GetAccName(playerid));

	return 1;
}

CMD:set3rdscripter(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/set3rdscripter [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pRdscripter]){
		PlayerInfo[userid][pRdscripter] = 0;
		SQL_SetIntegerAcc("accounts", "rdscripter", PlayerInfo[userid][pRdscripter], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiden 3RD Party Scripter yetkisini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin 3RD Party Scripter yetkilerinizi aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pRdscripter] = 1;
	SQL_SetIntegerAcc("accounts", "rdscripter", PlayerInfo[userid][pRdscripter], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi 3RD Party Scripter yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi 3RD Party Scripter yaptý.", GetAccName(playerid));

	return 1;
}

CMD:setebc(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/setebc [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pEbc]){
		PlayerInfo[userid][pEbc] = 0;
		SQL_SetIntegerAcc("accounts", "ebc", PlayerInfo[userid][pEbc], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiden mapper yetkisini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin mapper yetkilerinizi aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pEbc] = 1;
	SQL_SetIntegerAcc("accounts", "ebc", PlayerInfo[userid][pEbc], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi mapper yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi mapper yaptý.", GetAccName(playerid));

	return 1;
}

CMD:setskinyetki(playerid, params[]){
	new userid;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))  return SendHelpMessage(playerid, "/setskinyetki [ID/Karakter]");
	if (!IsPlayerLogged(userid)) return SendNotConnected(playerid);
	
	if(PlayerInfo[userid][pSkinYetki]){
		PlayerInfo[userid][pSkinYetki] = 0;
		SQL_SetIntegerAcc("accounts", "skinyetki", PlayerInfo[userid][pSkinYetki], PlayerInfo[userid][pAccID]);
		SendAdmMessage("%s adlý yönetici %s adlý kiþiden mapper yetkisini aldý.", GetAccName(playerid), GetNameEx(userid));
		SendServerMessage(userid, "%s adlý yönetici sizin mapper yetkilerinizi aldý.", GetAccName(playerid));
		return 1;
	}

	PlayerInfo[userid][pSkinYetki] = 1;
	SQL_SetIntegerAcc("accounts", "skinyetki", PlayerInfo[userid][pSkinYetki], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kiþiyi mapper yaptý.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici sizi mapper yaptý.", GetAccName(playerid));

	return 1;
}

CMD:asetplate(playerid, params[])
{
	new vehid, plate;

    if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) 			return SendNotAdmin(playerid);
	if (sscanf(params,"is[7]", vehid, plate))		return SendHelpMessage(playerid, "/asetplate [Car ID] [Yeni Plate(7)]");
	if (plate > 7) return SendErrorMessage(playerid, "Maksimum 7 haneli bir plaka oluþturabilirsiniz.");
	if (!IsValidVehicle(vehid))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
	if (IsPlayerInVehicle(playerid, vehid))	return SendErrorMessage(playerid, "Belirtilen araçtasýnýz.");

	format(VehicleInfo[vehid][carPlate], 7, "%s", plate);
	SendAdmMessage("%s adlý yönetici ID %d aracýn plakasýný %s olarak belirledi.", GetAccName(playerid), vehid, plate);
	Save_Car(vehid);
	return 1;
}

CMD:helper(playerid, params[])
{
	new userid, level;
	
	if (PlayerInfo[playerid][pAdmin] < 4 && PlayerInfo[playerid][pHelperLead] < 1)	return SendNotAdmin(playerid);
	if (sscanf(params, "ud", userid, level))		return SendHelpMessage(playerid, "/helper [ID/Karakter] [0 - helper deðil | 1-2-3-4-5 seviye]");
	if (!IsPlayerLogged(playerid))					return SendNotConnected(playerid);
	if (level < 0 || level > 5)						return SendErrorMessage(playerid, "Deðer 0 veya 5 olmalýdýr");
	
	if (!level)
	{
		if (IsTesterDuty(userid)) pc_cmd_hduty(userid, "");
		
		SendAdmMessage("%s adlý yönetici %s adlý kiþinin helper yetkilerini aldý.", GetAccName(playerid), GetAccName(userid));
		SendServerMessage(userid, "%s adlý helper yetkilerinizi aldý.", GetAccName(playerid));
		PlayerInfo[userid][pHelper] = 0;
		SQL_SetIntegerAcc("accounts", "helper", PlayerInfo[userid][pHelper], PlayerInfo[userid][pAccID]);		
		return 1;
	}

	PlayerInfo[userid][pHelper] = level;
	SQL_SetIntegerAcc("accounts", "helper", PlayerInfo[userid][pHelper], PlayerInfo[userid][pAccID]);
	SendAdmMessage("%s adlý yönetici %s adlý kullanýcýnýn helper durumunu güncelledi.", GetAccName(playerid), GetNameEx(userid));
	SendServerMessage(userid, "%s adlý yönetici helper statünüzü güncelledi.", GetAccName(playerid));
	return 1;
}

alias:giveskin("ozelmodelver", "/givedonatorskin");
CMD:giveskin(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL && !PlayerInfo[playerid][pSkinYetki]))	return SendNotAdmin(playerid);

    new owner[MAX_PLAYER_NAME], model, query[256];

	if (sscanf(params, "s[64]d", owner, model))
		return SendHelpMessage(playerid, "[özel model] /giveskin [Ýsim_Soyisim] [verilecek özel skin id]");
	
	if(GetAccountByName(owner) == -1) return SendErrorMessage(playerid, "Böyle bir karakter yok.");
	if (model < 0 || model > 40000) 													return SendErrorMessage(playerid, "Skin ID 0'dan küçük 40000'den büyük olamaz.");

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `donator_skinler` (sahip,skinid,yetkili,tarih) VALUES (%i, %i, '%s', '%s')", 
	GetAccountByName(owner), model, GetAccName(playerid), GetFullDate());
	mysql_tquery(dbHandle, query);

	SendServerMessage(playerid, "%s(SQLID: %d) adlý karakterin hesabýna %d ID'li özel modeli tanýmladýn.", owner, GetAccountByName(owner), model);

	return 1;
}

alias:givemoney("aparaver");
CMD:givemoney(playerid, params[])
{
	new userid, amount;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params, "ui", userid, amount))	return SendHelpMessage(playerid, "/givemoney [ID/Karakter Adý] [miktar]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (amount > 100000)			return SendErrorMessage(playerid, "Miktar $0 ile $500000 arasýnda olmalýdýr.");

	GiveCash(userid, amount);
	
	new mes[128];
	format(mes, sizeof(mes), "[/givemoney] %s adlý yönetici %s adlý oyuncuya para verdi: $%i.", GetAccName(playerid), GetNameEx(userid), amount);
	insert_log(mes, ADMIN_LOG, 8, PlayerInfo[userid][pAccID], PlayerInfo[playerid][pAccID]);

	if (amount < 0)
	{
		SendAdmMessage("%s adlý yönetici %s adlý yöneticiden $%i para aldý.", GetAccName(playerid), GetNameEx(userid), amount);
		SendServerMessage(userid, "Yönetici sizden $%i deðerinde para aldý.", amount);
		return 1;
	}
	else
	{
		SendAdmMessage("%s adlý yönetici %s adlý oyuncuya para verdi: $%i.", GetAccName(playerid), GetNameEx(userid), amount);
		SendServerMessage(userid, "Yönetici size para verdi: $%i.", amount);
	}
	return 1;
}

alias:aobject("aobj");
CMD:aobject(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL && !PlayerInfo[playerid][pMapper]))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "(/aobj)ect [ayar]");
		SendSyntaxMessage(playerid, "create/remove/edit/editobjects/goto");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new modelid;

		if (sscanf(secoption, "d", modelid))	return SendHelpMessage(playerid, "(/aobj)ect create [ID]");

		new objectid = -1;

		for(new i = 0; i < MAX_OBJECTS; i++)
		{
			if (ObjectsInfo[i][oID] || ObjectsInfo[i][oObjectOn]) continue;

			objectid = i;
			break;
		}

		if (objectid == -1)	return SendErrorMessage(playerid, "Oluþturulacak maksimum nesne sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, ObjectsInfo[objectid][oPosX], ObjectsInfo[objectid][oPosY], ObjectsInfo[objectid][oPosZ]);
		
		ObjectsInfo[objectid][oModel] = modelid;
		ObjectsInfo[objectid][oPosRX] = 
		ObjectsInfo[objectid][oPosRY] = 
		ObjectsInfo[objectid][oPosRZ] = 0.0;
		ObjectsInfo[objectid][oInt] = GetInterior(playerid);
		ObjectsInfo[objectid][oVW] = GetWorld(playerid);
		ObjectsInfo[objectid][oObject] = CreateDynamicObject(modelid, ObjectsInfo[objectid][oPosX], ObjectsInfo[objectid][oPosY], ObjectsInfo[objectid][oPosZ], 0.0, 0.0, 0.0, ObjectsInfo[objectid][oVW], ObjectsInfo[objectid][oInt], -1, 200.0);

		if (ObjectsInfo[objectid][oObject] == INVALID_OBJECT_ID)	return SendErrorMessage(playerid, "Obje oluþturulamadý.");

		ObjectsInfo[objectid][oObjectOn] = 1;

		AddObjectToFile(objectid, modelid, ObjectsInfo[objectid][oInt], ObjectsInfo[objectid][oVW], ObjectsInfo[objectid][oPosX], ObjectsInfo[objectid][oPosY], ObjectsInfo[objectid][oPosZ]);
		SendServerMessage(playerid, "Obje oluþturuldu. [ID: %i | MODEL: %i].", objectid, modelid);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new objectid;

		if (sscanf(secoption, "i", objectid))		return SendHelpMessage(playerid, "(/aobj)ect remove [ID]");
		if (ObjectsInfo[objectid][oObjectOn] != 1)	return SendErrorMessage(playerid, "Obje bulunamadý.");

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `objects` WHERE `id` = %i", ObjectsInfo[objectid][oID]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamicObject(ObjectsInfo[objectid][oObject]))	DestroyDynamicObject(ObjectsInfo[objectid][oObject]);

		ObjectsInfo[objectid][oPosX] = 
		ObjectsInfo[objectid][oPosY] = 
		ObjectsInfo[objectid][oPosZ] = 
		ObjectsInfo[objectid][oPosRX] = 
		ObjectsInfo[objectid][oPosRY] = 
		ObjectsInfo[objectid][oPosRZ] = 0.0;
		ObjectsInfo[objectid][oObjectOn] =
		ObjectsInfo[objectid][oID] = 0;
		
		SendServerMessage(playerid, "Obje silindi. [ID: %i]", objectid);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id, parameters[16], arg[112];

		if (sscanf(secoption, "is[12]S()[112]", id, parameters, arg))
		{
			SendHelpMessage(playerid, "(/aobj)ect edit [ID] [ayar]");
			SendSyntaxMessage(playerid, "pos/texture/deltexture");
			return 1;
		}

		if (id < 0 || id > MAX_OBJECTS - 1 || ObjectsInfo[id][oObjectOn] != 1)	return SendErrorMessage(playerid, "Obje bulunamadý.");

		if (CompareStrings(parameters, "pos"))
		{
			SetPVarInt(playerid, #edit_object, id + 1);
			EditDynamicObject(playerid, ObjectsInfo[id][oObject]);
			return 1;
		}

		else if (CompareStrings(parameters, "texture"))
		{
			new slot, model, txdname[32], texturename[32];

			if (sscanf(arg, "iis[32]s[32]", slot, model, txdname, texturename))
			{
				SendHelpMessage (playerid, "(/aobj)ect edit [obje ID] texture [slot (0-15)] [model ID] [TXD isim] [texture isim]");
				return 1;
			}
			
			if (slot <0 || slot> 15) return SendErrorMessage (playerid, "Slot deðeri 0 ile 15 arasýnda bir deðer olmalýdýr.");
			if (model <0) return SendErrorMessage (playerid, "Model ID 0 deðerinden küçük olamaz.");
			if (strlen (txdname)>= 32) return SendErrorMessage (playerid, "TXD ismi maksimum 32 karakter olmalýdýr.");
			if (strlen (texturename)>= 32) return SendErrorMessage (playerid, "Texture adý maksimum 32 karakter olmalýdýr.");
			
			if (!SetDynamicObjectMaterial(ObjectsInfo[id][oObject], slot, model, txdname, texturename, 0))	return SendErrorMessage(playerid, "Belirtilen objenin texturesi deðiþtirilemedi.");

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `objects_texture` WHERE `objectid` = %i AND `slot` = %i", ObjectsInfo[id][oID], slot);
			mysql_tquery(dbHandle, query, "OnObjectTextureInsert", "iiiiss", playerid, id, slot, model, txdname, texturename);
			return 1;
		}

		else if (CompareStrings(parameters, "deltexture"))
		{
			if (isnull(arg))	return SendHelpMessage(playerid, "(/aobj)ect edit [ID] deltexture [slot (0-15)]");

			new slot = strval(arg);

			if (slot < 0 || slot > 15)	return SendErrorMessage(playerid,"Slot deðeri 0 ile 15 arasýnda bir deðer olmalýdýr.");
			
			if (!SetDynamicObjectMaterial(ObjectsInfo[id][oObject], slot, -1, "none", "none", 0))	return SendErrorMessage(playerid, "Belirtilen objenin texturesi deðiþtirilemedi.");

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `objects_texture` WHERE `objectid` = %i AND `slot` = %i", ObjectsInfo[id][oID], slot);
			mysql_tquery(dbHandle, query);

			SendServerMessage(playerid,"Belirtilen objenin [ID: %i] texture'u baþarýyla silindi [SLOT: %i].", id, slot);
			return 1;
		}
	}

	else if (CompareStrings(option, "goto"))
	{
		new objectid;

		if (sscanf(secoption, "i", objectid))													return SendHelpMessage(playerid, "(/aobj)ect goto [ID]");
		if (objectid < 0 || objectid > MAX_OBJECTS || ObjectsInfo[objectid][oObjectOn] != 1)	return SendErrorMessage(playerid, "Obje bulunamadý.");

		SetPlayerPosEx(playerid, ObjectsInfo[objectid][oPosX], ObjectsInfo[objectid][oPosY], ObjectsInfo[objectid][oPosZ]);
		SetInterior(playerid, ObjectsInfo[objectid][oInt]);
		SetWorld(playerid, ObjectsInfo[objectid][oVW]);
		SendServerMessage(playerid, "Belirtilen objeye ýþýnlandýnýz [ID: %i].", objectid);
		return 1;
	}
	
	else if (CompareStrings(option, "editobjects"))
	{
		SetPVarInt(playerid, #edit_objects, 1);
		SelectObject(playerid);
		SendServerMessage(playerid, "Üzerine týklayarak objelerden birini seçiniz.");
		return 1;
	}

	else 
	{
		SendHelpMessage(playerid, "(/aobj)ect [seçenekler]");
		SendHelpMessage(playerid, "create/remove/edit/editobjects/goto");
	}
	return 1;
}

CMD:atower(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/atower [ayar]");
		SendHelpMessage(playerid, "create/remove/edit/goto");
		return 1;
	}	

	if (CompareStrings(option, "create"))
	{
		if (GetWorld(playerid) || GetInterior(playerid))	return SendErrorMessage(playerid, "Bir interior içerisinde baz istasyonu oluþturamazsýnýz.");

		new type;

		if (sscanf(secoption, "i", type))	return SendHelpMessage(playerid, "/atower create [0 - küçük | 1 - büyük] ");
		if (type < 0 || type > 1)			return SendErrorMessage(playerid, "Baz istasyonu tipi 0 veya 1 olmalýdýr.");
		new towerid = -1;

		for(new i; i < MAX_TOWERS; i++)
		{
			if (TowerInfo[i][towerOn]) continue;

			towerid = i;
			break;
		}

		if (towerid == -1)	return SendErrorMessage(playerid, "Maksimum baz istasyonu sayýsýna ulaþýldý.");

		new Float:x, Float:y, Float:z, Float:angle;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);	
		x += 1.0 * floatsin(-angle, degrees);
		y += 1.0 * floatsin(-angle, degrees);
		z -= 1.6;

		TowerInfo[towerid][towerModel] = (type) ? (3763) : (3030);
		TowerInfo[towerid][towerPosX] = x;
		TowerInfo[towerid][towerPosY] = y;
		TowerInfo[towerid][towerPosZ] = z;
		TowerInfo[towerid][towerPosRX] = 0;
		TowerInfo[towerid][towerPosRY] = 0;
		TowerInfo[towerid][towerPosRZ] = angle;
		TowerInfo[towerid][towerOn] = 1;
		TowerInfo[towerid][towerObject] = CreateDynamicObject(TowerInfo[towerid][towerModel], x, y, z, 0.0, 0.0, angle, 0, 0);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `towers` (`model`, `x`, `y`, `z`, `rz`) VALUES (%i, %f, %f, %f, %f)", type, x, y, z, angle);
		mysql_tquery(dbHandle, query, "OnTowerInsert", "i", towerid);

		new tower_name[16];

		if (!type)	format(tower_name, sizeof(tower_name), "küçük");
		else 		format(tower_name, sizeof(tower_name), "büyük");

		SendServerMessage(playerid, "Baþarýlý þekilde baz istasyonu oluþturuldu: %s [ID: %i].", tower_name, towerid);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new towerid;

		if (sscanf(secoption, "d", towerid))										return SendHelpMessage(playerid, "/atower remove [ID]");
		if (towerid < 0 || towerid > MAX_TOWERS || !TowerInfo[towerid][towerOn])	return SendErrorMessage(playerid, "Baz istasyonu bulunamadý.");
		
		if (IsValidDynamicObject(TowerInfo[towerid][towerObject])) DestroyDynamicObject(TowerInfo[towerid][towerObject]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `towers` WHERE `id` = %i", TowerInfo[towerid][towerID]);
		mysql_tquery(dbHandle, query);

		TowerInfo[towerid][towerOn] = 
		TowerInfo[towerid][towerID] = 0;
		SendServerMessage(playerid, "Baþarýlý þekilde baz istasyonu kaldýrýldý: [ID: %i]", towerid);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new towerid, parameters[16], arg[112];

		if (sscanf(secoption, "d", towerid))
		{
			SendHelpMessage(playerid, "/atower edit [ID] [parametre] ");
			SendHelpMessage(playerid, "Parametre: pos, type");
			return 1;
		}

		if (towerid < 0 || towerid > MAX_TOWERS || !TowerInfo[towerid][towerID])	return SendErrorMessage (playerid, "Baz istasyonu bulunamadý.");

		if (CompareStrings(parameters, "pos"))
		{
			if (GetWorld(playerid) || GetInterior(playerid))																							return SendErrorMessage (playerid, "Baz istasyonunu bir interiorda düzenleyemezsiniz.");
			if (!IsPlayerInRangeOfPoint(playerid, 10.0, TowerInfo[towerid][towerPosX], TowerInfo[towerid][towerPosY], TowerInfo[towerid][towerPosZ]))	return SendErrorMessage (playerid, "Baz istasyonunun yakýnýnda olmalýsýnýz.");
			if (GetPVarInt(playerid, #edit_tower) != 0)																									return SendErrorMessage (playerid, "Baz istasyonunu zaten düzenliyorsunuz.");

			SetPVarInt(playerid, #edit_tower, towerid + 1);
			EditDynamicObject(playerid, TowerInfo[towerid][towerObject]);
			return 1;
		}
		else if (CompareStrings(parameters, "type"))
		{
			new type;
			if (sscanf (arg, "i", type)) return SendHelpMessage (playerid, "/atower edit [ID] type [0 - küçük | 1 - büyük]");
			if (type <0 || type> 1) return SendErrorMessage (playerid, "Baz istasyonu tipi 0 veya 1 olmalýdýr.");

			TowerInfo[towerid][towerModel] = (type) ? (3763) : (3030);
			SQL_SetInteger("towers", "model", TowerInfo[towerid][towerModel], TowerInfo[towerid][towerID]);

			if (IsValidDynamicObject(TowerInfo[towerid][towerObject])) DestroyDynamicObject(TowerInfo[towerid][towerObject]);

			TowerInfo[towerid][towerObject] = CreateDynamicObject(TowerInfo[towerid][towerModel], TowerInfo[towerid][towerPosX], TowerInfo[towerid][towerPosY], TowerInfo[towerid][towerPosZ], TowerInfo[towerid][towerPosRX],
			TowerInfo[towerid][towerPosRY], TowerInfo[towerid][towerPosRZ], 0, 0);
			SendServerMessage(playerid,"Baz istasyonu tipi deðiþtirildi: [ID:%i]", towerid);
			return 1;
		}
	}

	else if (CompareStrings(option, "goto"))
	{
		new towerid; 

		if (sscanf(secoption, "d", towerid))										return SendHelpMessage(playerid, "/atower goto [ID] ");
		if (towerid < 0 || towerid > MAX_TOWERS || !TowerInfo[towerid][towerID])	return SendErrorMessage(playerid, "Baz istasyonu bulunamadý.");

		SetWorld(playerid, 0);
		SetInterior(playerid, 0);
		SetPlayerPosEx(playerid, TowerInfo[towerid][towerPosX], TowerInfo[towerid][towerPosY], TowerInfo[towerid][towerPosZ]);
		SendServerMessage (playerid, "Belirtilen baz istasyonuna ýþýnlandýnýz. [ID: %i]", towerid);
	}
	return 1;
}

CMD:departship(playerid, params[])
{
    if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	new depart;

	if (sscanf(params,"i", depart))	return SendHelpMessage(playerid, "/departship [saniye] ");

	ship_depart = gettime() + depart;
	return 1;
}

CMD:timetruck(playerid, params[])
{
    if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	new depart;

	if (sscanf(params,"i", depart))	return SendHelpMessage(playerid, "/timetruck [saniye] ");

	time_truck = depart;
	return 1;
}

CMD:nexttship(playerid, params[])
{
    if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	new depart;

	if (sscanf(params,"i", depart))	return SendHelpMessage(playerid, "/nexttship [saniye] ");

	ship_next = gettime() + depart;
	return 1;
}

CMD:koprukaldir(playerid)
{
    if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	new Float: ox, Float: oy, Float: oz;
   
	GetPlayerPos(playerid, ox, oy, oz);
	MoveDynamicObject(-22399, ox, oy, oz+60, 2.0);

	return 1;
}

CMD:agarage(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/agarage [ayarlar]");
		SendHelpMessage(playerid, "create/remove/edit/goto/createbiz/createhouse");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new type, price;

		if (sscanf (secoption, "ii", type, price)) return SendHelpMessage (playerid, "/agarage create [tip] [fiyat]");
		if (type <1 || type> 9) return SendErrorMessage (playerid, "Tip 1 ile 9 arasýnda olmalýdýr.");
		if (price <= 0 || price> 1000000) return SendErrorMessage (playerid, "Fiyat $1 ile $ 1,000,000 arasýnda olmalýdýr.");
		if (GetInterior (playerid) || GetWorld (playerid)) return SendErrorMessage (playerid, "Bu komutu normal dünyada kullanmalýsýn.");
		if (IsPlayerInAnyVehicle (playerid)) return SendErrorMessage (playerid, "Herhangi bir araçta olmamalýsýn.");
		if (Garage_Create (playerid, type, price) == -1) return SendErrorMessage (playerid, "Maksimum garaj sayýsýna ulaþýldý.");

		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if (sscanf(secoption, "i", id))								return SendHelpMessage(playerid, "/agarage remove [ID]");
		if (id < 0 || id > MAX_GARAGES || !GarageInfo[id][garageID])	return SendErrorMessage (playerid, "Garaj bulunamadý.");

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `garage` WHERE `id` = %i", GarageInfo[id][garageID]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamicCP(GarageInfo[id][garageCP]))	DestroyDynamicCP(GarageInfo[id][garageCP]);

		GarageInfo[id][garageID] = 0;
		SendServerMessage (playerid, "Baþarýlý þekilde garaj silindi [ID:%i].", id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id, parameters[16], arg[112];

		if (sscanf(secoption, "is[12]S()[112]", id, parameters, arg))
		{
			SendHelpMessage(playerid, "/agarage edit [ID] [ayarlar]");
			SendHelpMessage(playerid, "pos/vehpos/int/price/kilited");
			return 1;
		}

		if (id < 0 || id >= MAX_GARAGES || !GarageInfo[id][garageID])	return SendErrorMessage (playerid, "Garaj bulunamadý.");

		if (CompareStrings(parameters, "pos"))
		{
			if (IsPlayerInAnyVehicle (playerid)) return SendErrorMessage (playerid, "Herhangi bir araçta olmamalýsýn.");
			if (GetInterior (playerid) || GetWorld (playerid)) return SendErrorMessage (playerid, "Bu komutu normal dünyada kullanmalýsýn.");

			GetPlayerPos(playerid, GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2]);
			GarageInfo[id][garageEnterInt] = 
			GarageInfo[id][garageEnterVW] = 0;

			if (IsValidDynamicCP(GarageInfo[id][garageCP]))	DestroyDynamicCP(GarageInfo[id][garageCP]);

			GarageInfo[id][garageCP] = CreateDynamicCP(GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2], 0.9, 0, 0, -1, 3.0);
			SendServerMessage (playerid, "Belirtilen garajýn giriþi deðiþtirildi [ID:%i].", id);

			SQL_SetFloat("garage", "player_enter_x", GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "player_enter_y", GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "player_enter_z", GarageInfo[id][garagePlayer_Enter][2], GarageInfo[id][garageID]);
			SQL_SetInteger("garage", "enter_int", 0, GarageInfo[id][garageID]);
			SQL_SetInteger("garage", "enter_vw", 0, GarageInfo[id][garageID]);
			return 1;
		}
		
		else if (CompareStrings(parameters, "vehpos"))
		{
			if (!IsPlayerInAnyVehicle(playerid))				return SendErrorMessage (playerid, "Araçta olmalýsýnýz.");
			if (GetInterior (playerid) || GetWorld (playerid)) return SendErrorMessage (playerid, "Bu komutu normal dünyada kullanmalýsýn.");

			GetVehiclePos(GetPlayerVehicleID(playerid), GarageInfo[id][garageVeh_Enter][0], GarageInfo[id][garageVeh_Enter][1], GarageInfo[id][garageVeh_Enter][2]);
			GetVehicleZAngle(GetPlayerVehicleID(playerid), GarageInfo[id][garageVeh_Enter][3]);
			SendServerMessage (playerid, "Belirtilen garajýn araç giriþi deðiþtirildi [ID:%i].", id);

			SQL_SetFloat("garage", "veh_enter_x", GarageInfo[id][garageVeh_Enter][0], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_enter_y", GarageInfo[id][garageVeh_Enter][1], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_enter_z", GarageInfo[id][garageVeh_Enter][2], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_enter_fa", GarageInfo[id][garageVeh_Enter][3], GarageInfo[id][garageID]);
			return 1;
		}

		else if (CompareStrings(parameters, "int"))
		{
			new type;

			if (sscanf(arg, "i", type))						return SendHelpMessage(playerid, "/agarage edit [ID] int [tip] ");
			if (type <1 || type> 9) return SendErrorMessage (playerid, "Tip 1 ile 9 arasýnda olmalýdýr.");
			if (GetInterior(playerid) || GetWorld(playerid))	return SendErrorMessage(playerid, "Bu komutu normal dünyada kullanmalýsýn.");

			GarageInfo[id][garagePlayer_Exit][0] = garage_player_pos[type-1][0];
			GarageInfo[id][garagePlayer_Exit][1] = garage_player_pos[type-1][1];
			GarageInfo[id][garagePlayer_Exit][2] = garage_player_pos[type-1][2];
			GarageInfo[id][garageVeh_Exit][0] = garage_veh_pos[type-1][0];
			GarageInfo[id][garageVeh_Exit][1] = garage_veh_pos[type-1][1];
			GarageInfo[id][garageVeh_Exit][2] = garage_veh_pos[type-1][2];
			GarageInfo[id][garageVeh_Exit][3] = garage_veh_pos[type-1][3];
			GarageInfo[id][garageExitInt] = garage_int[type-1];
			SendServerMessage(playerid, "Belirtilen garajýn interioru deðiþtirildi [ID: %i]. Yeni Deðer: %i.", id, type);

			SQL_SetFloat("garage", "player_exit_x", GarageInfo[id][garagePlayer_Exit][0], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "player_exit_y", GarageInfo[id][garagePlayer_Exit][1], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "player_exit_z", GarageInfo[id][garagePlayer_Exit][2], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_exit_x", GarageInfo[id][garageVeh_Exit][0], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_exit_y", GarageInfo[id][garageVeh_Exit][1], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_exit_z", GarageInfo[id][garageVeh_Exit][2], GarageInfo[id][garageID]);
			SQL_SetFloat("garage", "veh_exit_fa", GarageInfo[id][garageVeh_Exit][3], GarageInfo[id][garageID]);
			SQL_SetInteger("garage", "exit_int", GarageInfo[id][garageExitInt], GarageInfo[id][garageID]);
			return 1;
		}

		else if (CompareStrings(parameters, "price"))
		{
			new price;

			if (sscanf(arg, "i", price))			return SendHelpMessage(playerid, "/agarage edit [ID] price [fiyat]");
			if (price <= 0 || price > 1000000)	return SendErrorMessage(playerid, "Fiyat deðer $1 ile $1000000 arasýnda olmalýdýr.");

			GarageInfo[id][garagePrice] = price;
			SQL_SetInteger("garage", "price", GarageInfo[id][garagePrice], GarageInfo[id][garageID]);
			SendServerMessage(playerid, "Belirtilen garajýn fiyatý deðiþtirildi [ID: %i]. Yeni Fiyat: $%i.", id, price);
			return 1;
		}

		else if (CompareStrings(parameters, "locked"))
		{
			new locked;

			if (sscanf(arg, "i", locked))	return SendHelpMessage(playerid, "/agarage edit [ID] locked [0 - açýk | 1 - kapalý]");
			if (locked < 0 || locked > 1)	return SendErrorMessage(playerid, "Deðer 0 veya 1 olmalýdýr.");

			GarageInfo[id][garageLocked] = locked;
			SQL_SetInteger("garage", "locked", GarageInfo[id][garageLocked], GarageInfo[id][garageID]);
			SendServerMessage(playerid, "Garaj %s [ID: %i].", (locked) ? ("kilitli") : ("kilitli deðil"));
			return 1;
		}

		else 
		{
			SendHelpMessage(playerid, "/agarage edit [ID] [ayarlar]");
			SendHelpMessage(playerid, "pos/vehpos/int/price/kilited");
		}
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))									return SendHelpMessage(playerid, "/agarage goto [ID]");
		if (id < 0 || id >= MAX_GARAGES || !GarageInfo[id][garageID])	return SendErrorMessage(playerid, "Garaj bulunamadý.");

		SetPlayerPosEx(playerid, GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2]);
		SetInterior(playerid, GarageInfo[id][garageEnterInt]);
		SetWorld(playerid, GarageInfo[id][garageEnterVW]);
		return 1;
	}

	else if (CompareStrings(option, "createbiz"))
	{
		new type, id, price;

		if (sscanf(secoption, "iii", type, price, id))			return SendHelpMessage(playerid, "/agarage createbiz [tip] [fiyat] [iþletme ID] ");
		if (type <1 || type> 9) return SendErrorMessage (playerid, "Tip 1 ile 9 arasýnda olmalýdýr.");
		if (price <= 0 || price> 1000000) return SendErrorMessage (playerid, "Fiyat $1 ile $1000000 arasýnda olmalýdýr.");
		if (id <0 || id>= MAX_BIZ ||! BizInfo [id] [bizID]) return SendErrorMessage (playerid, "Belirtilen iþletme bulunamadý.");
		if (Garage_Create(playerid, type, price, 2, id) == -1)	return SendErrorMessage(playerid, "Maksimum garaj sayýsýna ulaþýldý.");

		return 1;
	}

	else if (CompareStrings(option, "createhouse"))
	{
		new type, id, price;
		
		if (sscanf(secoption, "iii", type, price, id))			return SendHelpMessage(playerid, "/agarage createhouse [tip] [fiyat] [ev ID]");
		if (type < 1 || type > 9)								return SendErrorMessage(playerid, "Tip 1 ile 9 arasýnda olmalýdýr.");
		if (price <= 0 || price > 1000000)						return SendErrorMessage(playerid, "Fiyat $1 ile $1000000 arasýnda olmalýdýr.");
		if (id < 0 || id >= MAX_HOUSES || !HouseInfo[id][hID])	return SendErrorMessage(playerid, "Ev bulunamadý.");
		if (Garage_Create(playerid, type, price, 1, id) == -1)	return SendErrorMessage(playerid, "Maksimum garaj sayýsýna ulaþýldý.");

		return 1;
	}

	else 
	{
		SendHelpMessage(playerid, "/agarage [ayarlar]");
		SendHelpMessage(playerid, "create/remove/edit/goto/createbiz/createhouse");
	}
	return 1;
}

CMD:changefight(playerid, params[]) //TO DO MOVE TO SETSTAT
{
	new pid;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "u", pid)) 				return SendHelpMessage(playerid, "/changefight [ID/Karakter Adý]");
	if (!IsPlayerLogged(pid)) 					return SendNotConnected(playerid);
	
	SetPVarInt(playerid, "ChangeFightTo", pid);
	Dialog_Show(playerid, ChangeFight, DIALOG_STYLE_LIST, "{FFFFFF}Dövüþ stili deðiþtir","Normal\nBox\nKungFu\n-\nGrabKick","Deðiþtir","Ýptal");
	return 1;
}

alias:adminhide("ahide");
CMD:adminhide(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);

    PlayerInfo[playerid][pAdminHide] = (PlayerInfo[playerid][pAdminHide]) ? (0) : (1);
    SendServerMessage(playerid, "Yönetici gizlilik durumunuz deðiþtirildi. [%s]", (PlayerInfo[playerid][pAdminHide]) ? ("gizli") : ("görünür"));

	if (PlayerInfo[playerid][pAdminHide] && IsAdminDuty(playerid))		SetPlayerColor(playerid, TEAM_HIT_COLOR);
	else if (!PlayerInfo[playerid][pAdminHide] && IsAdminDuty(playerid))	SetPlayerColor(playerid, TEAM_ADMIN_COLOR);

	return 1;
}

alias:afoodstand("afood");
CMD:afoodstand(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "(/food)stand [ayarlar]");
		SendHelpMessage(playerid, "create/remove/goto");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new type;

		if (sscanf (secoption, "i", type)) return SendHelpMessage (playerid, "(/food) stand create [0 - nesnesiz | 1 - nesneli]");
		if (type <0 || type> 1) return SendErrorMessage (playerid, "Tip 0 veya 1 olmalýdýr.");
		if (IsPlayerInAnyVehicle (playerid)) return SendErrorMessage (playerid, "Bu komutu herhangi bir araçtayken kullanamazsýnýz.");

		new standid = -1;

		for(new i; i < MAX_FOOD_STAND; i++)
		{
			if (FoodStand[i][fStandOn]) continue;

			standid = i;
			break;
		}

		if (standid == -1)	return SendErrorMessage(playerid, "Maksimum tezgah sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, FoodStand[standid][fPosX], FoodStand[standid][fPosY], FoodStand[standid][fPosZ]);
		
		FoodStand[standid][fPosRX] = 
		FoodStand[standid][fPosRY] = 
		FoodStand[standid][fPosRZ] = 0.0;
		FoodStand[standid][fVW] = GetWorld(playerid);
		FoodStand[standid][fInt] = GetInterior(playerid);
		FoodStand[standid][fType] = type;

		if (type)
		{
			FoodStand[standid][fObject] = CreateDynamicObject(1340, FoodStand[standid][fPosX], FoodStand[standid][fPosY], FoodStand[standid][fPosZ], 0.0, 0.0, 0.0, FoodStand[standid][fVW], FoodStand[standid][fInt], -1, 200.0);
		}

		//FoodStand[standid][fLabel] = CreateDynamic3DTextLabel(""EMBED_CYAN"/yemekal", -1, FoodStand[standid][fPosX] + 1.5, FoodStand[standid][fPosY], FoodStand[standid][fPosZ], 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FoodStand[standid][fVW], FoodStand[standid][fInt], -1, 100.0);
		FoodStand[standid][fPickUp] = CreateDynamicPickup(1239, 1, FoodStand[standid][fPosX] + 1.5, FoodStand[standid][fPosY], FoodStand[standid][fPosZ], FoodStand[standid][fVW], FoodStand[standid][fInt], -1, 100.0);
		FoodStand[standid][fStandOn] = 1;
		AddFoodStandToFile(standid, FoodStand[standid][fType], FoodStand[standid][fPosX], FoodStand[standid][fPosY], FoodStand[standid][fPosZ], FoodStand[standid][fVW], FoodStand[standid][fInt]);
		SendServerMessage(playerid, "Tezgah oluþturuldu [ID: %i].", standid);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new standid;

		if (sscanf(secoption, "i", standid))											return SendHelpMessage(playerid, "(/food)stand remove [ID]");
		if (standid < 0 || standid >= MAX_FOOD_STAND || !FoodStand[standid][fStandOn])	return SendErrorMessage(playerid, "Tezgah bulunamadý.");

		if (FoodStand[standid][fType] && IsValidDynamicObject(FoodStand[standid][fObject]))
		{
			DestroyDynamicObject(FoodStand[standid][fObject]);
			FoodStand[standid][fObject] = INVALID_OBJECT_ID;
		}

		/*if (IsValidDynamic3DTextLabel(FoodStand[standid][fLabel]))
		{
			DestroyDynamic3DTextLabel(FoodStand[standid][fLabel]);
			FoodStand[standid][fLabel] = Text3D:INVALID_3DTEXT_ID;
		}*/

		if (IsValidDynamicPickup(FoodStand[standid][fPickUp]))	DestroyDynamicPickup(FoodStand[standid][fPickUp]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `foodstand` WHERE `id` = %i", FoodStand[standid][fID]);
		mysql_tquery(dbHandle, query);

		FoodStand[standid][fStandOn] = 
		FoodStand[standid][fID] = 0;
		SendServerMessage(playerid, "Tezgah kaldýrýldý [ID: %i].", standid);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new standid;

		if (sscanf(secoption, "i", standid))											return SendHelpMessage(playerid, "(/food)stand goto [ID]");
		if (standid < 0 || standid >= MAX_FOOD_STAND || !FoodStand[standid][fStandOn])	return SendErrorMessage(playerid, "Tezgah bulunamadý.");

		SetPlayerPosEx(playerid, FoodStand[standid][fPosX], FoodStand[standid][fPosY], FoodStand[standid][fPosZ]);
		SetWorld(playerid, FoodStand[standid][fVW]);
		SetInterior(playerid, FoodStand[standid][fInt]);
	}

	else 
	{
		SendHelpMessage(playerid, "(/food)stand [ayarlar]");
		SendHelpMessage(playerid, "create/remove/goto");
	}
	return 1;
}

CMD:ajob(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/ajob [ayarlar]");
		SendHelpMessage(playerid, "create/remove/goto");
	}

	if (CompareStrings(option, "create"))
	{
		new type;

		if (sscanf(secoption, "i", type))
		{
			SendHelpMessage(playerid, "/ajob create [meslek tipi]");
			SendHelpMessage(playerid, "[1] Kamyon Þoförü | [2] Tamirci | [3] Taksicilik | [4] Pizza Teslimatçýsý | [7] Araç Hýrsýzý");
			SendHelpMessage(playerid, "[8] Oduncu | [9] Çöpçü | [10] Madenci");
			return 1;
		}
		if (type < 0 || type > 10)			return SendErrorMessage(playerid, "Geçersiz meslek tipi seçtiniz.");
		if (IsPlayerInAnyVehicle (playerid)) return SendErrorMessage (playerid, "Bu komutu araçtayken kullanamazsýnýz.");

		new jobid = -1;

		for(new i = 0; i < MAX_JOBS; i++)
		{
			if (JobsInfo[i][jobOn])	continue;

			jobid = i;
			continue;
		}

		if (jobid == -1)	return SendErrorMessage(playerid, "Maksimum meslek limitine ulaþýldý.");

		GetPlayerPos(playerid, JobsInfo[jobid][jobX], JobsInfo[jobid][jobY], JobsInfo[jobid][jobZ]);
		
		JobsInfo[jobid][jobVW] = GetWorld(playerid);
		JobsInfo[jobid][jobInt] = GetInterior(playerid);
		JobsInfo[jobid][jobType] = type;
		JobsInfo[jobid][jobOn] = 1;

		JobsInfo[jobid][jobPickUp] = CreateDynamicPickup(1210, 1, JobsInfo[jobid][jobX], JobsInfo[jobid][jobY], JobsInfo[jobid][jobZ], JobsInfo[jobid][jobVW], JobsInfo[jobid][jobInt], -1, 100.0);

		new jobtext[32];

		switch(type)
		{
			case JOB_MECHANIC:	jobtext = "Tamirci";
			case JOB_TRUCKER:	jobtext = "Kamyon Þoförü";
			case JOB_TAXI:		jobtext = "Taksici";
			case JOB_PIZZA:		jobtext = "Pizzacý";
			case JOB_CARJACKER: jobtext = "Araç Hýrsýzý";
		}

		AddJobToFile(jobid, JobsInfo[jobid][jobType], JobsInfo[jobid][jobX], JobsInfo[jobid][jobY], JobsInfo[jobid][jobZ], JobsInfo[jobid][jobInt], JobsInfo[jobid][jobVW]);
		SendServerMessage(playerid, "Meslek oluþturuldu: %s [ID: %i].", jobtext, jobid);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new jobid;

		if (sscanf(secoption, "i", jobid))								return SendHelpMessage(playerid, "/ajob remove [ID]");
		if (jobid < 0 || jobid >= MAX_JOBS || !JobsInfo[jobid][jobOn])	return SendErrorMessage(playerid, "Meslek bulunamadý.");

		if (IsValidDynamicPickup(JobsInfo[jobid][jobPickUp]))		DestroyDynamicPickup(JobsInfo[jobid][jobPickUp]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `jobs` WHERE `id` = %i", JobsInfo[jobid][jobID]);
		mysql_tquery(dbHandle, query);

		JobsInfo[jobid][jobID] = 
		JobsInfo[jobid][jobOn] = 0;
		SendServerMessage(playerid, "Meslek silindi: [ID: %i].", jobid);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new jobid;

		if (sscanf(secoption, "i", jobid))								return SendHelpMessage(playerid, "/ajob goto [ID] ");
		if (jobid <0 || jobid>= MAX_JOBS ||! JobsInfo [jobid] [jobOn]) return SendErrorMessage (playerid, "Meslek bulunamadý.");

		SetPlayerPosEx(playerid, JobsInfo[jobid][jobX], JobsInfo[jobid][jobY], JobsInfo[jobid][jobZ]);
		SetInterior(playerid, JobsInfo[jobid][jobInt]);
		SetWorld(playerid, JobsInfo[jobid][jobVW]);
	}

	else 
	{
		SendHelpMessage(playerid, "/ajob [ayarlar]");
		SendHelpMessage(playerid, "create/remove/goto");
	}
	return 1;
}

alias:asc("aspeedcam");
CMD:asc(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/asc [ayarlar]");
		SendHelpMessage(playerid, "create/remove/edit/list");
	}

	if (CompareStrings(option, "create"))
	{
		new sp_limit, sp_zone[64], id = SC_GetFreeID();
		if (id == -1)									return SendErrorMessage (playerid, "Tüm kamera slotlarý dolu");
		if (sscanf(secoption, "d", sp_limit))			return SendHelpMessage (playerid, "/asc create [hýz limiti]");
		if (sp_limit <= 0 || sp_limit > SC_MAX_SPEED)	return SendErrorMessage (playerid, "Hýz limiti 1 ile %d arasýnda olmalýdýr.", SC_MAX_SPEED);
		
        GetPlayerPos(playerid, speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z]);
        GetPlayer2DZone(playerid, sp_zone, sizeof(sp_zone));

		format(speedcam[id][sc_name], 64, "%s 12%i", sp_zone, id);

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z); 

        speedcam[id][sc_speed] = sp_limit;
        speedcam[id][sc_x] = x;
        speedcam[id][sc_y] = y+1;
        speedcam[id][sc_z] = z;
		speedcam[id][sc_rx] = 0;
        speedcam[id][sc_ry] = 0;
        speedcam[id][sc_rz] = 0;
        speedcam[id][sc_int] = GetPlayerInterior(playerid);
        speedcam[id][sc_vw] = GetPlayerVirtualWorld(playerid);
        speedcam[id][sc_object] = CreateDynamicObject(18880, speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], speedcam[id][sc_rx], speedcam[id][sc_ry], speedcam[id][sc_rz], speedcam[id][sc_vw], speedcam[id][sc_int]);
		Iter_Add(speedcamObjects, id);

		speedcam[id][sc_areaid] = CreateDynamicSphere(speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], SC_DEF_RADIUS, speedcam[id][sc_vw], speedcam[id][sc_int]);

		AddSpeedcamToFile(id, sp_limit, speedcam[id][sc_name], speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], 0.0, 0.0, 0.0, speedcam[id][sc_int], speedcam[id][sc_vw]);
        SendServerMessage(playerid, "Yeni bir hýz kamerasý eklendi: [ID: %i] %s | Hýz limiti: %d.", id, speedcam[id][sc_name], sp_limit);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new scid;
        if (sscanf(secoption, "i", scid))  return  SendHelpMessage(playerid, "/sc remove [id]");
		if(!Iter_Contains(speedcamObjects, scid)) return SendErrorMessage(playerid, "Hatalý dolap ID girdin.");

        if (IsValidDynamicObject(speedcam[scid][sc_object]))
        {
            DestroyDynamicObject(speedcam[scid][sc_object]);
            speedcam[scid][sc_object] = INVALID_OBJECT_ID;
        }

        new sql_query[256];

        SendServerMessage(playerid, "Belirtilen hýz kamerasý kaldýrýldý: [ID: %i | %s].", scid, speedcam[scid][sc_name]);

        speedcam[scid][sc_name] = EOS;
        Iter_Remove(speedcamObjects, scid);
		
        mysql_format(dbHandle, sql_query, sizeof(sql_query), "DELETE FROM `speedcams` WHERE `id` = %i", scid);
        mysql_tquery(dbHandle, sql_query);
        return 1;
	}

	else if (CompareStrings(option, "edit"))
    {
        new sp_near = GetNearestSpeed(playerid, 15.0), thirdoption[64], fouroption[64];

        if (sp_near == -1)	return SendErrorMessage(playerid, "Yakýnýnýzda hýz kamerasý yok.");     

        if (sscanf(secoption, "s[64]S()[64]", thirdoption, fouroption))        
        {
            SendHelpMessage(playerid, "/sc edit [ayarlar]");
            SendHelpMessage(playerid, "pos/limit");
            return 1;
        }
        else if (CompareStrings(thirdoption, "limit"))
        {
            new sp_limit;

            if (sscanf(fouroption, "d", sp_limit))          return SendHelpMessage(playerid, "/sc edit limit [hýz limiti]");
            if (sp_limit <= 0 || sp_limit > SC_MAX_SPEED) 	return SendErrorMessage(playerid, "Hýz limiti 1 ile %d arasýnda olmalýdýr..", SC_MAX_SPEED);

            speedcam[sp_near][sc_speed] = sp_limit;
            SQL_SetInteger("speedcams", "speed", speedcam[sp_near][sc_speed], speedcam[sp_near][sc_id]);
            SendServerMessage(playerid, "Belirtilen hýz kamerasýnýn hýz limiti deðiþtirildi: [ID: %i] %s | Yeni Limit: %d.", sp_near, speedcam[sp_near][sc_name], sp_limit);
            return 1;
        }

        else if (CompareStrings(thirdoption, "pos"))
        {
            SetPVarInt(playerid, "SC:ID", sp_near + 1);
            SetPVarInt(playerid, "SC:Edit", 1);
            EditDynamicObject(playerid, speedcam[sp_near][sc_object]);
            return 1;
        }
    }

    else if (CompareStrings(option, "list"))
    {
		new dialog_header[96] = "{FFFFFF}Hýz Kamerasý\t{FFFFFF}Hýz Kamerasý ID\t{FFFFFF}Hýz Limiti\n", dialog_body[3072];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

		for(new i = 0; i < Iter_Count(speedcamObjects); i++)
		{
			format(dialog_body, sizeof(dialog_body), "%s%s\t%i\t%d\n", dialog_body, speedcam[i][sc_name], i, speedcam[i][sc_speed]);
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Hýz Kamerasý Listesi", dialog_body, "Kapat", "");
    }  
	return 1;
}

CMD:acctv(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	
	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/acctv [create/remove/edit/list/repall/goto]");

	if (CompareStrings(option, "create"))
	{
		new name[32];

		if (sscanf(secoption, "s[32]", name))			return SendHelpMessage(playerid, "/acctv create [isim]");
		if (strlen (name) < 4 || strlen (name) > 30) 	return SendErrorMessage (playerid, "Kamera adý minimum 4, maksimum 30 karakter olmalýdýr.");
		if (!CheckCCTVEquals(name)) 					return SendErrorMessage (playerid, "Bu kamera adý kullanýlýyor.");

		new nearcam = GetNearestCamera(playerid, 40.0);

		if (nearcam!= -1) return SendErrorMessage (playerid, "Yakýnýnýzda zaten bir kamera çalýþýyor.");

		new id = -1;

		for(new i = 0; i < MAX_CCTV; i++)
		{
			if (CCTVInfo[i][tvObjectOn])	continue;

			id = i;
			break;
		}

		if (id == -1)	return SendErrorMessage(playerid, "Maksimum CCTV sayýsýna ulaþýldý.");
		format(CCTVInfo[id][tvName], 32, "%s", name);
		GetPlayerPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);

		CCTVInfo[id][tvPosRX] = 
		CCTVInfo[id][tvPosRY] = 
		CCTVInfo[id][tvPosRZ] = 0.0;
		CCTVInfo[id][tvInt] = GetInterior(playerid);
		CCTVInfo[id][tvVW] = GetWorld(playerid);
		CCTVInfo[id][tvObject] = CreateDynamicObject(1886, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], 0.0, 0.0, 0.0, CCTVInfo[id][tvVW], CCTVInfo[id][tvInt]);
		CCTVInfo[id][tvCollision] = CreateDynamicObject(3800, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]-1.0, CCTVInfo[id][tvPosRX], CCTVInfo[id][tvPosRY], CCTVInfo[id][tvPosRZ], CCTVInfo[id][tvVW], CCTVInfo[id][tvInt]);
		SetDynamicObjectMaterial(CCTVInfo[id][tvCollision], 0, 16644, "a51_detailstuff", "roucghstonebrtb", 0x00000000);
		CCTVInfo[id][tvObjectOn] = 1;
		AddCameraToFile(id, CCTVInfo[id][tvInt], CCTVInfo[id][tvVW], CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], 0.0, 0.0, 0.0, name);
		SendServerMessage(playerid, "Yeni CCTV kamerasý eklendi: %s [ID: %i].", CCTVInfo[id][tvName], id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if (sscanf(secoption, "i", id))								return SendHelpMessage(playerid, "/acctv remove [ID]");
		if (id < 0 || id >= MAX_CCTV || !CCTVInfo[id][tvObjectOn])	return SendErrorMessage(playerid, "CCTV bulunamadý.");

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cctvs` WHERE `id` = %i", CCTVInfo[id][tvID]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamicObject(CCTVInfo[id][tvObject]))
		{
			DestroyDynamicObject(CCTVInfo[id][tvObject]);
			DestroyDynamicObject(CCTVInfo[id][tvCollision]);
			CCTVInfo[id][tvObject] = INVALID_OBJECT_ID;
			CCTVInfo[id][tvCollision] = INVALID_OBJECT_ID;
		}
		
		CCTVInfo[id][tvID] = 
		CCTVInfo[id][tvObjectOn] = 0;
		SendAdmMessageToPlayer(playerid, "CCTV kaldýrýldý: [ID: %i]", id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id, parameters[16], arg[112];

		if (sscanf(secoption, "is[16]S()[112]", id, parameters, arg)) return SendHelpMessage(playerid, "/acctv edit [ID] [pos/name]");

		if (id < 0 || id >= MAX_CCTV || !CCTVInfo[id][tvObjectOn] || !IsValidDynamicObject(CCTVInfo[id][tvObjectOn]))	return SendErrorMessage (playerid, "CCTV bulunamadý");

		if (CompareStrings(parameters, "pos"))
		{
			if (GetPVarInt(playerid, #edit_cctv))																			return SendErrorMessage(playerid, "Þu an zaten CCTV editliyorsunuz.");
			if (!IsPlayerInRangeOfPoint(playerid, 5.0, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]))	return SendErrorMessage(playerid, "CCTV yakýnýnýzda deðil.");

			SetPVarInt(playerid, #edit_cctv, id + 1);
			EditDynamicObject(playerid, CCTVInfo[id][tvObject]);
			return 1;
		}

		else if (CompareStrings(parameters, "name"))
		{
			new name[32];

			if (sscanf(arg, "s[32]", name))				return SendHelpMessage(playerid, "/acctv edit [ID] name [yeni isim]");
			if (strlen(name) < 4 || strlen(name) > 30)	return SendErrorMessage(playerid, "CCTV adý minimum 4, maksimum 30 karakter olmalýdýr.");
			if (!CheckCCTVEquals(name))					return SendErrorMessage(playerid, "Belirtilen CCTV adý kullanýlýyor.");

			format(CCTVInfo[id][tvName], 32, "%s", name);
			SQL_SetString("cctvs", "info", CCTVInfo[id][tvName], CCTVInfo[id][tvID]);
			SendAdmMessageToPlayer(playerid, "Belirtilen CCTV'nin adý deðiþtirildi: [ID: %i] Yeni Ad: %s.", id, CCTVInfo[id][tvName]);
			return 1;
		}
	}
	
	else if (CompareStrings(option, "list"))
	{
		new dialog_header[96] = "{FFFFFF}CCTV Adý\t{FFFFFF}ID\tDurum\n", dialog_body[3072];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

		for(new i = 0; i < MAX_CCTV; i++)
		{
			if (!CCTVInfo[i][tvObjectOn]) continue;

			new break_str[24];

            if (CCTVInfo[i][tvBreak])    format(break_str, sizeof(break_str), "{CC0000}DEAKTIF");
            else                        format(break_str, sizeof(break_str), "{00B200}AKTIF");

			format(dialog_body, sizeof(dialog_body), "%s%s\t%i\t%s\n", dialog_body, CCTVInfo[i][tvName], i, break_str);
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF} CCTV Listesi", dialog_body, "Kapat", "");
		return 1;
	}

	else if (CompareStrings(option, "repall"))
	{
		for(new i = 0; i < MAX_CCTV; i++)
		{
			if (!CCTVInfo[i][tvObjectOn])                        continue;
        	if (!IsValidDynamicObject(CCTVInfo[i][tvObject])) continue;
			if (!CCTVInfo[i][tvBreak])							continue;

			SetCameraBreakState(i, 0);	
		}

		SendServerMessage(playerid,"Tüm CCTV'ler tamir edildi.");
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))								return SendHelpMessage(playerid, "/acctv goto [ID]");
		if (id < 0 || id > MAX_CCTV || !CCTVInfo[id][tvObjectOn])	return SendErrorMessage(playerid, "Belirtilen CCTV bulunamadý.");

		SetPlayerPosEx(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);
		SetWorld(playerid, CCTVInfo[id][tvVW]);
		SetInterior(playerid, CCTVInfo[id][tvInt]);
		return 1;
	}
	
	else SendHelpMessage(playerid, "/acctv [create/remove/edit/list/repall/goto]");
	
	return 1;
}

CMD:aatm(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];
	
	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/aatm [create/remove/edit/goto]");

	if (CompareStrings(option, "create"))
	{
		new id = -1;

		for(new i; i < MAX_ATMS; i++)
		{
			if (ATMInfo[i][atmID]) continue;

			id = i;
			break;
		}

		if (id == -1)	return SendErrorMessage (playerid, "Maksimum ATM sayýsýna ulaþýldý.");

		new Float:x, Float:y, Float:z, Float:angle;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		x += 1.0 * floatsin(-angle, degrees);
		y += 1.0 * floatcos(-angle, degrees);

		ATMInfo[id][atmPosX] = x;
		ATMInfo[id][atmPosY] = y;
		ATMInfo[id][atmPosZ] = z - 0.4;
		ATMInfo[id][atmPosRZ] = angle;
		ATMInfo[id][atmInt] = GetInterior(playerid);
		ATMInfo[id][atmVW] = GetWorld(playerid);
		ATMInfo[id][atmObject] = CreateDynamicObject(19324, ATMInfo[id][atmPosX], ATMInfo[id][atmPosY], ATMInfo[id][atmPosZ], 0.0, 0.0, ATMInfo[id][atmPosRZ], ATMInfo[id][atmVW], ATMInfo[id][atmInt]);
		
		SetPVarInt(playerid, #edit_atm, id + 1);
		EditDynamicObject(playerid, ATMInfo[id][atmObject]);

		AddATMToFile(id, ATMInfo[id][atmPosX], ATMInfo[id][atmPosY], ATMInfo[id][atmPosZ], ATMInfo[id][atmPosRZ], ATMInfo[id][atmInt], ATMInfo[id][atmVW]);
		SendServerMessage(playerid, "ATM oluþturuldu: [ID: %i].", id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;
		
		if (sscanf(secoption, "i", id))							return SendHelpMessage(playerid, "/aatm remove [ID]");
		if (id < 0 || id >= MAX_ATMS || !ATMInfo[id][atmID])	return SendErrorMessage(playerid, "ATM bulunamadý.");

		if (IsValidDynamicObject(ATMInfo[id][atmObject]))
		{
			DestroyDynamicObject(ATMInfo[id][atmObject]);
			ATMInfo[id][atmObject] = INVALID_OBJECT_ID;
		}

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `atms` WHERE `id` = %i", ATMInfo[id][atmID]);
		mysql_tquery(dbHandle, query);

		ATMInfo[id][atmID] = 0;
		SendServerMessage(playerid, "ATM kaldýrýldý: [ID: %i].", id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id;

		if (sscanf(secoption, "d", id))						return SendHelpMessage(playerid, "/aatm edit [ID]");
		if (id < 0 || id > MAX_ATMS || !ATMInfo[id][atmID])	return SendErrorMessage (playerid, "ATM bulunamadý.");
		if (ATM_Nearest (playerid)!= id) 					return SendErrorMessage (playerid, "Yakýnýnýzda ATM bulunmuyor.");

		SetPVarInt(playerid, #edit_atm, id + 1);
		EditDynamicObject(playerid, ATMInfo[id][atmObject]);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))						return SendHelpMessage(playerid, "/aatm goto [ID] ");
		if (id < 0 || id > MAX_ATMS || !ATMInfo[id][atmID])	return SendErrorMessage(playerid, "ATM bulunamadý.");

		SetPlayerPosEx(playerid, ATMInfo[id][atmPosX], ATMInfo[id][atmPosY], ATMInfo[id][atmPosZ]);
		SetWorld(playerid, ATMInfo[id][atmVW]);
		SetInterior(playerid, ATMInfo[id][atmInt]);
		return 1;
	}
	
	else
	{
		SendHelpMessage(playerid, "/aatm [create/remove/edit/goto]");
	}
	return 1;
}

CMD:agate(playerid, params[])
{
	new option[16], secoption[128], modelid, faction, gateid, Float:o_rad, toption;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/agate [create/remove/edit/goto]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		if (sscanf(secoption, "ii", modelid, faction)) 	return SendHelpMessage(playerid, "/agate create [obje ID] [Birlik ID (/afaction list)]");
		if (faction < 0 || faction > MAX_FACTIONS-1) 	return SendErrorMessage(playerid, "Belirtilen birlik ID'si geçersiz.");

		new gate = -1;
		for(new i; i < MAX_GATES; i++)
		{
			if (Gates[i][gateID] != 0 || Gates[i][gateObjectOn] != 0) continue;
			gate = i;
			break;
		}

		if (gate == -1) return SendErrorMessage(playerid, "Maksimum gate sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, Gates[gate][gatePosX], Gates[gate][gatePosY], Gates[gate][gatePosZ]);
		GetPlayerPos(playerid, Gates[gate][gateMoveX], Gates[gate][gateMoveY], Gates[gate][gateMoveZ]);

		Gates[gate][gateObject] = CreateDynamicObject(modelid, Gates[gate][gatePosX], Gates[gate][gatePosY], Gates[gate][gatePosZ], 0.0, 0.0, 0.0, GetWorld(playerid), GetInterior(playerid), -1, 200.0);

		if (Gates[gate][gateObject] == INVALID_OBJECT_ID) return SendErrorMessage(playerid, "Obje oluþturulamadý.");

		Gates[gate][gateSpeed] = 0.5;
		Gates[gate][gateRadius] = 5.0;
		Gates[gate][gateModel] = modelid;
		Gates[gate][gateMoveRX] = 
		Gates[gate][gateMoveRY] = 
		Gates[gate][gateMoveRZ] = 
		Gates[gate][gatePosRX] = 
		Gates[gate][gatePosRY] = 
		Gates[gate][gatePosRZ] = 0.0;
		Gates[gate][gateInt] = GetInterior(playerid);
		Gates[gate][gateVW] = GetWorld(playerid);
		Gates[gate][gateSound] = 0;
		Gates[gate][gateFaction] = faction;
		Gates[gate][gateOpened] = 0;
		Gates[gate][gateObjectOn] = 1;

		AddGateToFile(gate, modelid, faction, GetInterior(playerid), GetWorld(playerid), Gates[gate][gatePosX], Gates[gate][gatePosY], Gates[gate][gatePosZ]);
		SendServerMessage(playerid, "Gate oluþturuldu: [ID: %i]", gate);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		if (sscanf(secoption, "i", gateid)) return SendHelpMessage(playerid, "/agate remove [ID]");
		if (!Gates[gateid][gateObjectOn])	return SendErrorMessage(playerid, "Belirtilen gate bulunamadý.");

		new query[256];

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `gates` WHERE `id`= %i", Gates[gateid][gateID]);
		mysql_tquery(dbHandle, query, "OnGateRemove", "i", gateid);

		if (IsValidDynamicObject(Gates[gateid][gateObject])) DestroyDynamicObject(Gates[gateid][gateObject]);

		Gates[gateid][gatePosX] = 
		Gates[gateid][gatePosY] = 
		Gates[gateid][gatePosZ] = 
		Gates[gateid][gatePosRX] =
		Gates[gateid][gatePosRY] = 
		Gates[gateid][gatePosRZ] = 
		Gates[gateid][gateSpeed] = 
		Gates[gateid][gateRadius] =
		Gates[gateid][gateMoveX] = 
		Gates[gateid][gateMoveY] = 
		Gates[gateid][gateMoveZ] = 
		Gates[gateid][gateMoveRX] = 
		Gates[gateid][gateMoveRY] =
		Gates[gateid][gateMoveRZ] = 0.0;
		Gates[gateid][gateObjectOn] = 
		Gates[gateid][gateInt] = 
		Gates[gateid][gateFaction] = 
		Gates[gateid][gateOpened] = 
		Gates[gateid][gateVW] = 
		Gates[gateid][gateID] = 0;

		SendServerMessage(playerid, "Gate kaldýrýldý: [ID: %i]", gateid);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new parameters[16], arg[112];

		if (sscanf(secoption, "s[16]S()[5]", parameters, arg))
		{
			SendHelpMessage(playerid, "/agate edit [pos/move/speed/radius/sound]");
			return 1;
		}

		if (CompareStrings(parameters, "pos"))
		{
			if (sscanf(arg, "i", gateid)) 															return SendHelpMessage(playerid, "/agate edit pos [ID]");
			if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn]) 					return SendErrorMessage(playerid, "Gate bulunamadý.");
			if (GetPVarInt(playerid, #2_edit_gate) != 0 || GetPVarInt(playerid, #edit_gate) != 0) 	return SendErrorMessage(playerid, "Þu an obje düzenliyorsunuz.");

			SetPVarInt(playerid, #edit_gate, gateid+1);
			EditDynamicObject(playerid, Gates[gateid][gateObject]);
			return 1;

		}

		else if (CompareStrings(parameters, "move"))
		{
			if (sscanf(arg, "i", gateid)) 															return SendHelpMessage(playerid, "/agate edit move [ID]");
			if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn])					return SendErrorMessage(playerid, "Gate bulunamadý.");
			if (GetPVarInt(playerid, #2_edit_gate) != 0 || GetPVarInt(playerid, #edit_gate) != 0) 	return SendErrorMessage(playerid, "Þu an obje düzenliyorsunuz.");

			SetPVarInt(playerid, #2_edit_gate, gateid+1);
			EditDynamicObject(playerid, Gates[gateid][gateObject]);
			return 1;
		}

		else if (CompareStrings(parameters, "speed"))
		{
			if (sscanf(arg, "if", gateid, o_rad)) 									return SendHelpMessage(playerid, "/agate edit speed [Gate ID] [hýz (0.1 - 255.0)]");
			if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn]) 	return SendErrorMessage(playerid, "Gate bulunamadý.");
			if (o_rad < 0.1 || o_rad > 255.0) 										return SendErrorMessage(playerid, "Hareket hýzý 0.1 ile 255.0 arasýnda olmalýdýr.");

			Gates[gateid][gateSpeed] = o_rad;
			SQL_SetFloat("gates", "speed", Gates[gateid][gateSpeed], Gates[gateid][gateID]);
			SendServerMessage(playerid, "Gate hareket hýzýný ayarladýnýz: [ID: %i] | Yeni Hýz: %.2f", gateid, o_rad);
			return 1;
		}

		else if (CompareStrings(parameters, "radius"))
		{
			if (sscanf(arg, "if", gateid, o_rad)) 									return SendHelpMessage(playerid, "/agate edit radius [ID] [yarýçap (0.1 - 30.0)] ");
			if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn])	return SendErrorMessage(playerid, "Gate bulunamadý.");
			if (o_rad < 0.1 || o_rad > 30.0)										return SendErrorMessage (playerid, "Yarýçap 0.1 ile 30.0 arasýnda olmalýdýr.");

			Gates[gateid][gateRadius] = o_rad;
			SQL_SetFloat("gates", "radius", Gates[gateid][gateRadius], Gates[gateid][gateID]);
			SendServerMessage(playerid, "Gate yarýçapýný ayarladýnýz: [ID: %i] | Yeni Yarýçap: %.2f", gateid, o_rad);
			return 1;
		}

		else if (CompareStrings(parameters, "sound"))
		{
			if (sscanf(arg, "ii", gateid, toption))									return SendHelpMessage(playerid, "/agate edit sound [ID] [Ses ID | 0 - sessiz] ");
			if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn]) 	return SendErrorMessage(playerid, "Gate bulunamadý.");
			if (toption < 0)														return SendErrorMessage(playerid, "Ses bulunamadý.");

			Gates[gateid][gateSound] = toption;
			SQL_SetInteger("gates", "sound", Gates[gateid][gateSound], Gates[gateid][gateID]);
			SendServerMessage(playerid, "Gate sesini ayarladýnýz: [ID: %i] | Yeni Ses: %d.", gateid, toption);
			return 1;
		}

		else 
		{
			SendHelpMessage(playerid, "/agate edit [pos/move/speed/radius/sound]");
		}
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		if (sscanf(secoption, "i", gateid)) 									return SendHelpMessage(playerid, "/agate goto [ID]");
		if (gateid < 0 || gateid >= MAX_GATES || !Gates[gateid][gateObjectOn])	return SendErrorMessage(playerid, "Gate bulunamadý.");

		SetPlayerPosEx(playerid, Gates[gateid][gatePosX], Gates[gateid][gatePosY], Gates[gateid][gatePosZ]);
		SetWorld(playerid, Gates[gateid][gateVW]);
		SetInterior(playerid, Gates[gateid][gateInt]);
		return 1;	
	}

	else 
	{
		SendHelpMessage(playerid, "/agate [ayarlar]");
		SendHelpMessage(playerid, "create/remove/edit/goto");
	}
	return 1;
}

CMD:astreet(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new option[5], secoption[5];
	if (sscanf(params, "s[7]S()[5]", option, secoption)) return SendHelpMessage(playerid, "/astreet [add/edit/remove/goto]");

	if (CompareStrings(option, "add")) {
		if (!GetPlayerVirtualWorld(playerid) && !GetPlayerInterior(playerid)) {
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);

			x += 1.0;

			/*pTemp[playerid][editPos][0] = x;
			pTemp[playerid][editPos][1] = y;
			pTemp[playerid][editPos][2] = z;

			pTemp[playerid][editPos][3] = x;
			pTemp[playerid][editPos][4] = y;
			pTemp[playerid][editPos][5] = z;*/

			//GetGroupCenter(pTemp[playerid][editPos][3], pTemp[playerid][editPos][4], pTemp[playerid][editPos][5]);
			SetPVarInt(playerid, #edit_street, 1);

			new Street_Sign = CreateDynamicObject(19981, x, y, z, 0.0, 0.0, 0.0, -1, -1, -1, 300.00, 300.00);
			EditDynamicObject(playerid, Street_Sign);
		}
	}
	else if (CompareStrings(option, "edit")) {
		new id;
		if (sscanf(secoption,"i", id)) 	return SendHelpMessage(playerid, "/astreet edit [id]");
		if (!street_data[id][street_id])	return SendErrorMessage(playerid, "Geçersiz ID. (( /near ))");
		if (GetPlayerDistanceFromPoint(playerid, street_data[id][sSign][0], street_data[id][sSign][1], street_data[id][sSign][2]) > 5.0)
			return SendErrorMessage(playerid, "Sokaktan çok uzaksýn!");

		SetPVarInt(playerid, #edit_street, 2);
		SetPVarInt(playerid, #id_street, id);

		EditDynamicObject(playerid, street_data[id][street_object][0]);
	}
	else if (CompareStrings(option, "remove")) {
		new id;
		if (sscanf(secoption,"i", id))	return SendHelpMessage(playerid, "/astreet remove [id]");
		if (!street_data[id][street_id])	return SendErrorMessage(playerid, "Geçersiz ID. (( /near ))");

		DeleteStreet(playerid, id);
	}
	else if (CompareStrings(option, "goto")) {
		new id;
		if (sscanf(secoption,"i", id))	return SendHelpMessage(playerid, "/astreet goto [id]");
		if (!street_data[id][street_id])	return SendErrorMessage(playerid, "Geçersiz ID. (( /near ))");

		SetPlayerPosEx(playerid, street_data[id][sSign][0],street_data[id][sSign][1],street_data[id][sSign][2]);
	}
	return 1;
}

CMD:stname(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	
	new id;
	if (sscanf(params,"i", id)) 		return SendHelpMessage(playerid, "/stname [id]");
	if (!street_data[id][street_id])	return SendErrorMessage(playerid, "Geçersiz ID. (( /near ))");
	if (GetPlayerDistanceFromPoint(playerid, street_data[id][sSign][0], street_data[id][sSign][1], street_data[id][sSign][2]) > 5.0)
		return SendErrorMessage(playerid, "Çok uzaktasýnýz!");

	SetPVarInt(playerid, #edit_street, 3);
	EditDynamicObject(playerid, street_data[id][street_object][1]); //Name
	return 1;
}

CMD:stdir(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	new id;
	if (sscanf(params,"i", id)) 		return SendHelpMessage(playerid, "/stdir [id]");
	if (!street_data[id][street_id])	return SendErrorMessage(playerid, "Geçersiz ID. (( /near ))");
	if (GetPlayerDistanceFromPoint(playerid, street_data[id][sSign][0], street_data[id][sSign][1], street_data[id][sSign][2]) > 5.0)
		return SendErrorMessage(playerid, "Çok uzaktasýnýz!");

	SetPVarInt(playerid, #edit_street, 3);
	EditDynamicObject(playerid, street_data[id][street_object][2]); //sDirection
	return 1; 
}

CMD:getareas(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	
	new areas[10], j = GetPlayerNumberDynamicAreas(playerid);
	GetPlayerDynamicAreas(playerid, areas, sizeof(areas));
	SM2(playerid, "[_________ TOPLAM: %i _________]", j);
	for(new s; s < 10; s ++) {
		for(new i; i < sizeof(street_names); i++) {
			if (IsValidDynamicArea(areas[s]) && areas[s] == street_zones[i]) {
				SM1(playerid, "[%i] %i. %s", s, i, street_names[i]);
			}
		}
	}


	return 1;
}

alias:abillboard("abb");
CMD:abillboard(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);
	
	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[7]", option, secoption))
	{
		SendHelpMessage(playerid, "/abillboard [create/delete/edit/goto]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
        new bb = GetUnusedBillBoard();
	    if (bb == -1) return SendErrorMessage(playerid, "Billboard sýnýrý aþýldý!");
		
		if (strval(secoption) <= 0) return SendHelpMessage(playerid, "/abb create [fiyat]");

		SetPVarInt(playerid, #BB_COST, strval(secoption));
        ShowModelSelectionMenu(playerid, "Billboards", MODEL_SELECTION_BB, billboard_obj, sizeof(billboard_obj));
	}
	if (CompareStrings(option, "remove"))
	{
		new id;
		if (sscanf(secoption, "I(-1)", id)) return SendHelpMessage(playerid, "/abb remove {c7c7c7}[ID]");
		
		if (id == -1) {
			if ((id = GetClosestBillBoard(playerid, 15.0)) == -1) return SendErrorMessage(playerid, "Yanýnda billboard yok!");
		}
		
		if (id >= MAX_BILLBOARDS || id < 0)	return SendErrorMessage(playerid, "Geçersiz ID.");
		if (!BillboardInfo[id][bbActive])	return SendErrorMessage(playerid, "Geçersiz ID.");

		SendServerMessage(playerid, "Billboard baþarýlý þekilde kaldýrýldý. [#%i]", id+1);
		DeleteBillBoard(id);
	}
	if (CompareStrings(option, "edit"))
	{
		new id;
		if (sscanf(secoption, "I(-1)", id)) return SendHelpMessage(playerid, "/abb edit {c7c7c7}[ID]");
		
		if (id == -1) {
			if ((id = GetClosestBillBoard(playerid, 25.0)) == -1) return SendErrorMessage(playerid, "Yakýnýnýzda billboard yok!");
		}
		
		if (id >= MAX_BILLBOARDS || id < 0)	return SendErrorMessage(playerid, "Geçersiz ID.");
		if (!BillboardInfo[id][bbActive])	return SendErrorMessage(playerid, "Geçersiz ID.");

		SetPVarInt(playerid, "BB:Edit", id+1);
		EditDynamicObject(playerid, BillboardInfo[id][bbObject]);
	}
	if (CompareStrings(option, "goto"))
	{
		new id;
		if (sscanf(secoption, "i", id)) return SendHelpMessage(playerid, "/abb goto {c7c7c7}[ID]");
		
		if (id >= MAX_BILLBOARDS || id < 0)	return SendErrorMessage(playerid, "Geçersiz ID.");
		if (!BillboardInfo[id][bbActive])	return SendErrorMessage(playerid, "Geçersiz ID.");

		SetPlayerPosEx(playerid, BillboardInfo[id][bbPosX], BillboardInfo[id][bbPosY], BillboardInfo[id][bbPosZ]);
		SetInterior(playerid, BillboardInfo[id][bbInt]);
		SetWorld(playerid, BillboardInfo[id][bbVW]);
	} 
	else SendHelpMessage(playerid, "/abillboard [create/remove/edit/goto]");

	return 1;
}

