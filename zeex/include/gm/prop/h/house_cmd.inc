alias:evkontrol("interiorkontrol", "dekorasyonkontrol");
CMD:evkontrol(playerid, params[])
{
	new houseid;

	if ((houseid = GetNearOutsideHouse(playerid)) == -1)	return SendErrorMessage(playerid, "Yak�n�n�zda sat�l�k ev bulunmuyor.");
	if (HouseInfo[houseid][hOwnerID])						return SendErrorMessage(playerid, "Bu ev sat�n al�nm��.");
	if (PlayerInfo[playerid][pInjured] != 0)                     return SendErrorMessage(playerid, "Yaral�yken bu i�lemi yapamazs�n�z.");

	if (!GetWorld(playerid) && !GetInterior(playerid))		GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

	SetPlayerPosEx(playerid,HouseInfo[houseid][hExitX],HouseInfo[houseid][hExitY],HouseInfo[houseid][hExitZ]);
	SetInterior(playerid,HouseInfo[houseid][hExitInt]);
	SetWorld(playerid,HouseInfo[houseid][hExitVW]);
	pTemp[playerid][pHouseEntered] = houseid;

	SetPVarInt(playerid, #check_int, 30);
	SendSyntaxMessage(playerid, "Ev dekorunu g�r�nt�l�yorsunuz, 30 saniyeniz var.");
	return 1;
}

alias:ev("evim");
CMD:ev(playerid, params[])
{
	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/ev [se�enekler]");
		SendSyntaxMessage(playerid, "satinal | menu | yukselt | paracek | parayatir | sistemesat | sat | arkakapi");

		if (!randomEx(0,5)) {
			SendHelpMessage(playerid, "Evinize garaj, ek giri�/��k�� ekletmek i�in veya ana giri�/��k�� d�zenlemeleri i�in");
			SendHelpMessage(playerid, "forum �zerindeki sistem tan�t�m�ndan detaylar�n� ��renebilirsiniz.");
		}

		return 1;
	}

	if (CompareStrings(option, "satinal"))
	{
		new houseid;

		if ((houseid = GetNearOutsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Yak�n�n�zda sat�l�k ev bulunmuyor.");
		if (HouseInfo[houseid][hOwnerID])									return SendErrorMessage(playerid, "Bu ev sat�n al�nm��.");
		if (GetPlayerHouses(playerid) >= GetMaxPlayerHouse(playerid))		return SendErrorMessage(playerid, "Daha fazla ev sat�n alamazs�n�z.");
		if (PlayerInfo[playerid][pLevel] < HouseInfo[houseid][hLevelbuy])	return SendErrorMessage(playerid, "Bu evi sat�n alabilmek i�in %i seviye olmal�s�n�z.", HouseInfo[houseid][hLevelbuy]);
		if (GetCash(playerid) < HouseInfo[houseid][hPrice])					return SendNotCash(playerid);

		HouseInfo[houseid][hOwnerID] = PlayerInfo[playerid][pID];
		HouseInfo[houseid][hLocked] = 1;
		HouseInfo[houseid][hCash] = 0;
		format(HouseInfo[houseid][hOwner], MAX_PLAYER_NAME, GetNameEx(playerid));

		new money = PlayerInfo[playerid][pCash];

		GiveCash(playerid, -HouseInfo[houseid][hPrice]);
		SendSyntaxMessage(playerid, "$%i kar��l���nda ev sat�n ald�n�z: [ID: %i]", HouseInfo[houseid][hPrice], houseid);
		DestroyDynamicPickup(HouseInfo[houseid][hPickup]);
		HouseInfo[houseid][hPickup] = CreateDynamicPickup(19522, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);

		for(new i = 0; i < MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageHouse] != HouseInfo[houseid][hID]) continue;

			SendSyntaxMessage(playerid, "Sat�n alm�� oldu�unuz evin garaj� bulunuyor: [ID: %i]", i);
			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			format(GarageInfo[i][garageOwnerName], 24, "%s", GetNameEx(playerid));

			SQL_SetInteger("garage", "owner", GarageInfo[i][garageOwner], GarageInfo[i][garageID]);
			SQL_SetString("users", "name", GarageInfo[i][garageOwnerName], GarageInfo[i][garageOwner]);
		}

		if (HouseInfo[houseid][hExtX][0] && HouseInfo[houseid][hExtY][0] && HouseInfo[houseid][hExtZ][0]) {
			SendSyntaxMessage(playerid, "Evinizin bir arka kap�s� bulunuyor, evin i�erisinden ��k�� noktas� eklemeniz gerekiyor: ( /h backdoor )");
		}

		SendHelpMessage(playerid, "Ev hakk�nda yard�m almak i�in: /evyardim");
		Save_House(houseid);

		new mes[256];
		format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SIMDIKI): %i] ev sat�n ald� [H_MYSQL: %i] $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid),
		HouseInfo[houseid][hID], HouseInfo[houseid][hPrice]);
    	insert_log(mes, PROPERTY_LOG, 3, PlayerInfo[playerid][pAccID]);
		return 1;
	}
	else if (CompareStrings(option, "menu"))	return pc_cmd_evmenu(playerid, "");
	else if (CompareStrings(option, "yukselt"))
	{
		new houseid;

		if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

		new parameters[16], arg[112];

		if (sscanf(secoption, "s[16]S()[112]", parameters, arg))
		{
			SendHelpMessage(playerid, "/ev yukselt [se�enekler]");
			SendSyntaxMessage(playerid, "radyo {33CC33}[$500]{FFFFFF} | kilit | alarm | gardrop {33CC33}[$600]{FFFFFF} | kapi | kapitamir | can");
			return 1;
		}

		if (CompareStrings(parameters, "radyo"))
		{
			if (HouseInfo[houseid][hRadio])		return SendErrorMessage(playerid, "Bu evde radyo bulunuyor.");
			if (GetCash(playerid) < 500)		return SendErrorMessage(playerid, "Bu i�lemi yapmak i�in yeterli paran�z bulunmuyor. Gereken Tutar: 500$");

			HouseInfo[houseid][hRadio] = 1;
			SQL_SetInteger("houses", "radio", HouseInfo[houseid][hRadio], HouseInfo[houseid][hID]);
			GiveCash(playerid, -500);
			SendSyntaxMessage(playerid, "500$ kar��l���nda bir radyo sat�n ald�n�z, kullan�m: /radyoayarla");
			return 1;
		}

		else if (CompareStrings(parameters, "kilit"))
		{
			new level;

			if (sscanf(arg, "i", level))
			{
				SendHelpMessage(playerid, "/ev yukselt kilit [level (1-5)]");
				SendSyntaxMessage(playerid, "Her seviye aras�nda $250 fark bulunmaktad�r [1 level - $250 | 5 level - $1250].");
				return 1;
			}
			if (level < 1 || level > 5)				return SendErrorMessage(playerid, "Kilit seviyesi 1 ile 5 aras�nda olmal�d�r.");
			if (GetCash(playerid) < 250 * level)	return SendErrorMessage(playerid, "%i seviye kilit i�in yeterli paran�z bulunmuyor, gereken: $%i.", level, level * 250);
			if (HouseInfo[houseid][hLock] >= level)	return SendErrorMessage(playerid, "Evinizin kilit seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hLock]);

			HouseInfo[houseid][hLock] = level;
			SQL_SetInteger("houses", "lock", HouseInfo[houseid][hLock], HouseInfo[houseid][hID]);
			GiveCash(playerid, -level * 250);
			SendSyntaxMessage(playerid, "%i seviye kilit ald�n�z, �denen tutar: $%i.", HouseInfo[houseid][hLock], level * 250);
			return 1;
		}

		else if (CompareStrings(parameters, "alarm"))
		{
			new level;

			if (sscanf(arg, "i", level))
			{
				SendHelpMessage(playerid, "/ev yukselt alarm [level (1-3)]");
				SendSyntaxMessage(playerid, "Her seviye aras�nda $500 fark bulunmaktad�r [1 level - $500 | 3 level - $1500].");
				return 1;
			}
			if (level < 1 || level > 3)					return SendErrorMessage(playerid, "Alarm seviyesi 1 ile 3 aras�nda olmal�d�r.");
			if (GetCash(playerid) < 500 * level)		return SendErrorMessage(playerid, "%i seviye alarm i�in yeterli paran�z bulunmuyor, gereken: $%i.", level, level * 500);
			if (HouseInfo[houseid][hAlarm] >= level)	return SendErrorMessage(playerid, "Evinizin alarm seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hAlarm]);

			HouseInfo[houseid][hAlarm] = level;
			SQL_SetInteger("houses", "alarm", HouseInfo[houseid][hAlarm], HouseInfo[houseid][hID]);
			GiveCash(playerid, -level * 500);
			SendSyntaxMessage(playerid, "%i seviye alarm ald�n�z, �denen tutar: $%i.", HouseInfo[houseid][hAlarm], level * 500);
			return 1;
		}

		else if (CompareStrings(parameters, "kapi"))
		{
			new level;

			if (sscanf(arg, "i", level))
			{
				SendHelpMessage(playerid, "/ev yukselt kapi [level (1-2)]");
				SendSyntaxMessage(playerid, "Her seviye aras�nda $750 fark bulunmaktad�r [1 level - $750 | 2 level - $1500].");
				return 1;
			}
			if (level < 1 || level > 2)				return SendErrorMessage(playerid, "Kap� seviyesi 1 ile 2 aras�nda olmal�d�r.");
			if (GetCash(playerid) < 750 * level)	return SendErrorMessage(playerid, "%i seviye kap� i�in yeterli paran�z bulunmuyor, gereken: $%i.", level, level * 750);
			if (HouseInfo[houseid][hDoor] >= level)	return SendErrorMessage(playerid, "Evinizin kap� seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hDoor]);

			HouseInfo[houseid][hDoor] = level;
			SQL_SetInteger("houses", "door", HouseInfo[houseid][hDoor], HouseInfo[houseid][hID]);
			GiveCash(playerid, -level * 750);
			SendSyntaxMessage(playerid, "%i seviye kap� ald�n�z, �denen tutar: $%i.", HouseInfo[houseid][hDoor], level * 750);
			return 1;
		}

		else if (CompareStrings(parameters, "gardrop"))
		{
			if (HouseInfo[houseid][hCupboard])	return SendErrorMessage(playerid, "Evinizde bir gardrop bulunuyor.");
			if (GetCash(playerid) < 600)			return SendErrorMessage(playerid, "Gardrop sat�n alabilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $600");

			HouseInfo[houseid][hCupboard] = 1;
			SQL_SetInteger("houses", "cupboard", HouseInfo[houseid][hCupboard], HouseInfo[houseid][hID]);
			GiveCash(playerid, -600);
			SendSyntaxMessage(playerid, "$600 kar��l���nda evinize gardrop ald�n�z.");
			SendSyntaxMessage(playerid, "Kullan�m i�in: /kiyafetlerim");
			return 1;
		}

		else if (CompareStrings(parameters, "kapitamir"))
		{
			if (!HouseInfo[houseid][hDDoor])	return SendErrorMessage(playerid,"Evinizin kap�s� kasarl� de�il.");
			if (GetCash(playerid) < 300)		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $300");

			HouseInfo[houseid][hDDoor] = 0;
			SQL_SetInteger("houses", "ddoor", HouseInfo[houseid][hDDoor], HouseInfo[houseid][hID]);
			UpdateHouseDoor(houseid);
			GiveCash(playerid, -300);
			SendSyntaxMessage(playerid, "$300 kar��l���nda evinizin kap�s�n� tamir ettirdiniz.");
			return 1;
		}

		else if (CompareStrings(parameters, "can"))
		{
			new level;

			if (sscanf(arg, "i", level))
			{
				SendHelpMessage(playerid, "/ev yukselt can [seviye (1-5)]");
				SendSyntaxMessage(playerid, "Her seviye aras�nda $400 fark bulunmaktad�r [1 seviye - $400 | 5 seviye - $2000].");
				SendSyntaxMessage(playerid, "Her seviye aras�nda 20 HP fark bulunmaktad�r [1 seviye - +20 HP | 5 seviye - +100 HP].");
				SendSyntaxMessage(playerid, "Her seviye aras�nda 20 saniye gecikme fark� bulunmaktad�r [1 level - 60 saniye | 5 level - 140 saniye].");
				return 1;
			}
			if (HouseInfo[houseid][hHeal])			return SendErrorMessage(playerid, "Evinizde ilk yard�m kiti bulunuyor.");
			if (level < 1 || level > 5)				return SendErrorMessage(playerid, "�lkyard�m Kiti seviyesi 1 ile 5 aras�nda olmal�d�r.");
			if (GetCash(playerid) < level * 400)	return SendErrorMessage(playerid, "%i seviye ilk yard�m kiti i�in yeterli paran�z bulunmuyor, gereken: $%i.", level, level * 400);

			HouseInfo[houseid][hHeal] = level;
			HouseInfo[houseid][hHealAmount] = 3;
			SQL_SetInteger("houses", "heal", HouseInfo[houseid][hHeal], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "heal_amount", HouseInfo[houseid][hHealAmount], HouseInfo[houseid][hID]);
			GiveCash(playerid, -level * 400);
			SendSyntaxMessage(playerid, "%i seviye ilk yard�m kiti ald�n�z, �denen tutar: $%i.", HouseInfo[houseid][hHeal], level * 400);
			return 1;
		}
	}

	else if (CompareStrings(option, "paracek"))
	{
		new houseid;

		if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

		new amount;

		if (sscanf(secoption, "i", amount))
		{
			SendHelpMessage(playerid, "/ev paracek [tutar]");
			SendSyntaxMessage(playerid, "Evin kasas�nda $%i bulunuyor.", HouseInfo[houseid][hCash]);
			return 1;
		}
		if (amount > HouseInfo[houseid][hCash] || amount < 1)	return SendErrorMessage(playerid, "Evin kasas�nda yeterli para bulunmuyor veya ge�ersiz tutar girdiniz.");

		GiveCash(playerid, amount);
		HouseInfo[houseid][hCash] -= amount;
		SendSyntaxMessage(playerid, "Evin kasas�ndan $%i tutar�nda para ald�n�z. Kasada kalan: $%i.", amount, HouseInfo[houseid][hCash]);
		SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
		return 1;
	}

	else if (CompareStrings(option, "parayatir"))
	{
		new houseid;

		if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z. ");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

		new amount;

		if (sscanf(secoption, "i", amount))
		{
			SendHelpMessage(playerid, "/ev parayatir [tutar]");
			SendSyntaxMessage(playerid, "Evin kasas�nda $%i bulunuyor.", HouseInfo[houseid][hCash]);
			return 1;
		}
		if (amount > GetCash(playerid) || amount < 1)	return SendNotCash(playerid);

		GiveCash(playerid, -amount);
		HouseInfo[houseid][hCash] += amount;
		SendSyntaxMessage(playerid, "Evin kasas�ndan $%i tutar�nda para ald�n�z. Kasada kalan: $%i.", amount, HouseInfo[houseid][hCash]);
		SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
		return 1;
	}

	else if (CompareStrings(option, "sistemesat"))
	{
		new houseid;

		if ((houseid = GetNearOutsideHouse(playerid)) == -1)			return SendErrorMessage(playerid, "Satmak istedi�iniz eve yak�n de�ilsiniz.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

		static const str_size[] = "{FFFFFF}Evinizi $%i fiyat�na satmak istedi�inize emin misiniz?";
		new mes[sizeof(str_size) - 2 + 12];
 		format(mes, sizeof(mes), str_size, HouseInfo[houseid][hPrice]/2);
		Dialog_Show(playerid, SellHouse, DIALOG_STYLE_MSGBOX, "{FFFFFF}Ev Sat���", mes, "Sat", "�ptal");
		return 1;
	}

	else if (CompareStrings(option, "sat"))
	{
		new userid, price;

		if (sscanf(secoption, "ui", userid, price))			return SendHelpMessage(playerid, "/ev sat [ID / isim] [fiyat]");

		new houseid;

		if ((houseid = GetNearOutsideHouse(playerid)) == -1)			return SendErrorMessage(playerid, "Satmak istedi�iniz eve yak�n de�ilsiniz.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");
		if (!IsPlayerLogged(userid))									return SendNotConnected(playerid);
		if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
		if (price < 0 || price > 100000000)								return SendErrorMessage(playerid, "Sat�� fiyat� $0 ile $100000000 aras�nda olmal�d�r.");

		pTemp[userid][pHousePrice] = price;
		pTemp[userid][pHousePlayer] = playerid;
		pTemp[userid][pHouseHouse] = houseid;
		SetPVarInt(userid, #accept_time, gettime() + 30);
		SendSyntaxMessage(playerid, "%s adl� ki�iye evinizi satmak i�in teklif g�nderdiniz. Fiyat: $%i", GetNameEx(userid), price);
		SendSyntaxMessage(userid, "%s adl� ki�i size evini satmak istiyor, onaylamak i�in Y tu�una bas�n. Fiyat: $%i", GetNameEx(playerid), price);
	}

	if (CompareStrings(option, "arkakapi"))
	{
		new houseid = GetNearInsideHouse(playerid);

		if (houseid == -1) return SendErrorMessage(playerid, "Evde olmal�s�n�z!");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");
		if (GetInterior(playerid) != HouseInfo[houseid][hExitInt] || GetWorld(playerid) != HouseInfo[houseid][hExitVW]) {
			return SendErrorMessage(playerid, "Evde olmal�s�n�z!");
		}

		if (!HouseInfo[houseid][hExtX][0] && !HouseInfo[houseid][hExtY][0] && !HouseInfo[houseid][hExtZ][0]) {
			return SendErrorMessage(playerid, "Evinizin ek kap�s� bulunmuyor! (Evinize farkl� giri�/��k�� ekletmek i�in sistem tan�t�m�n� inceleyiniz)");
		}

		new Float: posX, Float: posY, Float: posZ;
		GetPlayerPos(playerid, posX, posY, posZ);

		HouseInfo[houseid][hExtX][1] = posX;
		HouseInfo[houseid][hExtY][1] = posY;
		HouseInfo[houseid][hExtZ][1] = posZ;

		HouseInfo[houseid][hExtVW][1] = GetPlayerVirtualWorld(playerid);
		HouseInfo[houseid][hExtInt][1] = GetPlayerInterior(playerid);

		Save_House(houseid);
		SendSyntaxMessage(playerid, "Ba�ar�l� �ekilde evinize ek ��k�� konumu ayarlad�n�z.");
	}

	return 1;
}

CMD:evmenu(playerid, params[])
{
    new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yak�n de�ilsiniz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	static const str_size[] = "[%s]\n\
								Ev geli�tirmeleri\n\
								Mobilya y�netimi\n\
								Kirac�lar\n\
								Ev envanteri\n\
								Ev kasas�\n\
								Gardrop\n\
								Evi Sat";
	new mes[sizeof(str_size) - 6 + 9 + 5 + 5];

	format(mes, sizeof(mes), str_size, (HouseInfo[houseid][hLocked] != 0) ? ("Kilitli") : ("Kilitli De�il"));
	Dialog_Show(playerid, HouseMenu, DIALOG_STYLE_LIST, "Ev Men�s�", mes, "Se�", "�ptal");
	return 1;
}

alias:rentroom("evkirala", "/odakirala");
CMD:rentroom(playerid, params[])
{
    new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z. ");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

    new userid, price;

	if (sscanf(params,"ud", userid, price))							return SendHelpMessage(playerid, "/evkirala [ID / isim] [saatlik kira �creti]");
    if (userid == playerid)											return 1;
	if (!IsPlayerLogged(userid))									return SendNotConnected(playerid);
    if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
	if (price < 0 || price > 500)									return SendErrorMessage(playerid, "Saatlik kira �creti $0 ile $500 aras�nda bir de�er olmal�d�r");
    if (GetPlayerHouses(userid) || PlayerInfo[userid][pRentKey])	return SendErrorMessage(playerid, "Belirtilen oyuncunun bir evi var veya ba�ka bir ev kiralam��.");
	if (GetCash(userid) < price)									return SendErrorMessage(playerid, "Belirtilen oyuncunun yeterli paras� bulunmuyor.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `users` WHERE `rent_key`=%i", HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query, "OfferRentRoom", "iii", playerid, userid, price);
	return 1;
}

alias:unrent("evkiraiptal");
CMD:unrent(playerid, params[])
{
	if (PlayerInfo[playerid][pRentKey] < 1)	return SendErrorMessage(playerid, "Herhangi bir evi kiralam�yorsunuz.");

	PlayerInfo[playerid][pRentKey] = 0;
	SQL_SetInteger("users", "rent_key", 0, PlayerInfo[playerid][pID]);
	SendSyntaxMessage(playerid, "Ev kiras�n� iptal ettiniz.");
	return 1;
}

/*
CMD:tenants(playerid, params[])
{
	new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yak�n de�ilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `id`, `name` FROM `users` WHERE `rent_key` = %i", HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query, "ShowTenantsAmount", "i", playerid);
	return 1;
}*/

CMD:iyilestir(playerid, params[])
{
	new id, userid;

	if ((id = GetNearInsideHouse(playerid)) != -1 && PlayerInfo[playerid][pID] == HouseInfo[id][hOwnerID])
	{
	    if (HouseInfo[id][hHeal] == 0)					return SendErrorMessage(playerid, "Evinizde ilk yard�m kiti bulunmuyor.");
	    if (pTemp[playerid][pHealTime] > gettime())		return SendErrorMessage(playerid, "�lk yard�m kitini %i saniye boyunca kullanamazs�n�z.", pTemp[playerid][pHealTime]-gettime());
	    if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/iyilestir [ID / isim]");
        if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
        if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
        if (PlayerInfo[userid][pInjured])				return SendErrorMessage(playerid, "Belirtilen ki�i �l�/yaral�/bayg�n.");
        if (GetPlayerHealthEx(userid) >= 100.0)			return SendErrorMessage(playerid, "Belirtilen ki�i sa�l�kl�.");

		if (playerid != userid)
		{
        	SendSyntaxMessage(playerid, "%s adl� ki�iye ilk yard�m uygulad�n�z. (+%i HP) Tekrar ilk yard�m uygulayabilmek i�in %i saniye beklemeniz gerekiyor.", GetNameWithMask(userid), (HouseInfo[id][hHeal] * 20), 40 + (HouseInfo[id][hHeal] * 20));
			SendSyntaxMessage(userid, "%s adl� ki�i size ilk yard�m uygulad�. (+%i HP)", GetNameWithMask(playerid), (HouseInfo[id][hHeal] * 20));
		}
		else
		{
		    SendSyntaxMessage(playerid, "Kendinize ilk yard�m uygulad�n�z. (+%i HP) Tekrar ilk yard�m uygulayabilmek i�in %i saniye beklemeniz gerekiyor.", (HouseInfo[id][hHeal] * 20), 40 + (HouseInfo[id][hHeal] * 20));
		}

		ResetDamages(userid);

        StopPlayerAnims(userid);
		UnFreezePlayer(userid);

		pTemp[playerid][pHealTime] = gettime() + 40 + (HouseInfo[id][hHeal] * 20);

		if (PlayerInfo[userid][pHealth]> 100.0)  PlayerInfo[playerid][pHealth] = 100.0;

		HouseInfo[id][hHealAmount]--;
		if (!HouseInfo[id][hHealAmount]) HouseInfo[id][hHeal] = 0;
		Save_House(id);
		return 1;
	}

	else if (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid)) //FD Heal
	{
		if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/iyilestir [ID / isim]");
		if (!PlayerInfo[playerid][pOnDuty])				return SendErrorMessage(playerid, "��ba��nda olmal�s�n�z.");
		if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
		if (userid == playerid)							return 1;
		if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
		if (pTemp[userid][pHealPlayer] == playerid)		return SendErrorMessage(playerid, "Belirtilen ki�iye tedavi teklifi g�nderilmi�.");
		if (PlayerInfo[userid][pInjured] != 0)			return SendErrorMessage(playerid, "Belirtilen ki�i �l� veya yaral�.");
		if (GetPlayerHealthEx(userid) >= 100.0)			return SendErrorMessage(playerid, "Belirtilen ki�i sa�l�kl�.");

		pTemp[userid][pHealPlayer] = playerid;
		SetPVarInt(userid, #accept_time, gettime() + 30);
		SendSyntaxMessage(userid, "%s adl� ki�i sizi tedavi etmek istiyor. Y tu�una basarak teklifi kabul edebilirsin.", GetNameWithMask(playerid));
		SendSyntaxMessage(playerid, "%s adl� ki�iye tedavi teklifi g�nderildi.", GetNameWithMask(userid));
	}

	else return SendErrorMessage(playerid, "Evde de�ilsiniz.");

	return 1;
}

alias:dekorasyonizni("dekorasyonizin");
CMD:dekorasyonizni(playerid, params[])
{
    new userid;

	if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/dekorasyonizni [ID / isim]");
    if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (userid == playerid)							return 1;
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

    new houseid;

	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid,"Bu ev sana ait de�il.");

	if (pTemp[userid][pBuildHouse] == HouseInfo[houseid][hID])
	{
	    SendSyntaxMessage(playerid, "%s adl� ki�inin mobilya d�zenleme eri�imini kald�rd�n�z.", GetNameWithMask(userid));
	    SendSyntaxMessage(userid, "%s adl� ki�i mobilya d�zenleme eri�iminizi kald�rd�.", GetNameWithMask(playerid));
	    pTemp[userid][pBuildHouse] = 0;
	    return 1;
	}
	SendSyntaxMessage(playerid, "%s adl� ki�iye mobilya d�zenleme eri�imi verdiniz.", GetNameWithMask(userid));
 	SendSyntaxMessage(userid, "%s adl� ki�i mobilya d�zenleme eri�imi verdi.", GetNameWithMask(playerid));
    pTemp[userid][pBuildHouse] = HouseInfo[houseid][hID];
	return 1;
}

CMD:depo(playerid, params[])
{
    new houseid;

	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

 	GetPlayerPos(playerid, HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]);

 	Save_House(houseid);
 	SendSyntaxMessage(playerid, "Depo konumunu de�i�tirdiniz.");
	return 1;
}

alias:evkilitkir("ekk", "evkilidikir", "evinkilidinikir");
CMD:evkilitkir(playerid, params[])
{
	if (!PoliceOnline())	return SendErrorMessage(playerid, "Oyunda aktif en az %i polis olmal�d�r.", NEED_COPS_TO_CRIME);

	new houseid = GetNearHouse(playerid);
	if (houseid == -1)						 		  return SendErrorMessage(playerid, "Evin giri�ine yak�n olmal�s�n�z.");
	if (!IsPlayerOutsideHouse(playerid, houseid, 3.0)) return SendErrorMessage(playerid,"Evin giri�ine yak�n olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] == 0)   		  return SendErrorMessage(playerid,"Yaln�zca sat�n al�nan evlerde h�rs�zl�k yap�labilir.");
	if (HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID])   		  return SendErrorMessage(playerid,"Kendi evinizde h�rs�zl�k yapamazs�n�z.");
	if (HouseInfo[houseid][hLocked] == 0)   		  return SendErrorMessage(playerid,"Bu evin kap�s� kilitli de�il.");
	if (JackingLock[playerid] != 0)         		  return SendErrorMessage(playerid, "Kap� kilidini k�rarken tekrar ayn� i�lemi yapamazs�n�z.");
	if (IsPlayerCrouching(playerid) == false) 		  return SendErrorMessage(playerid, "E�ilmek zorundas�n.");

	foreach(new i : Player) {
		if (BreakingHouse[i] == houseid) return SendErrorMessage(playerid, "Ba�ka birisi bu evin kilidini kurcal�yor.");
	}

	new param[18];
	if (sscanf(params, "s[18]", param)) {
		SendHelpMessage(playerid, "/evkilitkir");
		SendSyntaxMessage(playerid, "sessiz - maymuncukla evin kilidini sessizce a�mak (yava�)");
		SendSyntaxMessage(playerid, "sesli - levye ile evin y�ksek sesle soyulmas�, alarm var ise devreye girer. (h�zl�)");
		return 1;
	}

	if (CompareStrings(param, "sessiz"))
	{
		pTemp[playerid][JackingType] = 3;
		BreakingHouse[playerid] = houseid;

		new htime;

		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		static const str_size[] = "{"COL_GREY"}Evin kap�s�n� k�rmaya ba�lamak ister misiniz? [%s] %i saniye s�recek";
		new mes[sizeof(str_size) + 6 + 70];
		format(mes, sizeof(mes), str_size, (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])), htime);
        Dialog_Show(playerid, StartBreakingLock, DIALOG_STYLE_MSGBOX, "{FFFFFF}Kap� K�r", mes, "Ba�la", "�ptal");
	}
	else if (CompareStrings(param, "sesli"))
	{
		if (!CheckHanditem(playerid,18634)) return SendErrorMessage(playerid, "Elinizde bir levye olmal�. (/aksesuar)");
		pTemp[playerid][JackingType] = 4;
		BreakingHouse[playerid] = houseid;

		new htime;

		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = floatround((250+HouseInfo[houseid][hLock]*250)*0.6);
			case 1: htime = floatround((250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05))*0.6);
			case 2: htime = floatround((250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15))*0.6);
		}

		static const str_size[] = "{"COL_GREY"}Evin kap�s�n� k�rmaya ba�lamak ister misin? [%s] %i saniye s�recek";
		new mes[sizeof(str_size) + 76];
		format(mes, sizeof(mes), str_size, (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])), htime);
        Dialog_Show(playerid, StartBreakingLock, DIALOG_STYLE_MSGBOX, "{FFFFFF}Kap� K�r", mes, "Ba�la", "�ptal");
	} else {
		SendHelpMessage(playerid, "/evkilitkir");
		SendSyntaxMessage(playerid, "sessiz - maymuncukla evin kilidini sessizce a�mak (yava�)");
		SendSyntaxMessage(playerid, "sesli - levye ile evin y�ksek sesle soyulmas�, alarm var ise devreye girer. (h�zl�)");
		return 1;
	}

	return 1;
}

alias:soygun("evsoygun");
CMD:soygun(playerid, params[])
{
	if (!PoliceOnline())	return SendErrorMessage(playerid, "Oyunda aktif en az %i polis olmal�d�r.", NEED_COPS_TO_CRIME);

	new houseid = GetNearHouse(playerid);
	if (houseid == -1)						 		  return SendErrorMessage(playerid, "Evin giri�ine yak�n olmal�s�n�z.");
	if (!IsPlayerInsideHouse(playerid, houseid, 50.0)) return SendErrorMessage(playerid,"Evin giri�ine yak�n olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] == 0)   		  return SendErrorMessage(playerid,"Yaln�zca sahibi olan evlerde h�rs�zl�k yap�labilir.");
	if (JackingLock[playerid] != 0)         		  return SendErrorMessage(playerid, "Soygun i�lemine zaten ba�lam��s�n�z.");

	foreach(new i : Player) {
		if (StealingHouse[i] == houseid) return SendErrorMessage(playerid, "Ba�ka birisi bu evi soyuyor.");
	}

	new param[18];
	if (sscanf(params, "s[18]", param)) {
		SendHelpMessage(playerid, "/soygun (parametre)");
		SendSyntaxMessage(playerid, "sessiz - maymuncukla kasay� teknik bir �ekilde a�mak (yava�)");
		SendSyntaxMessage(playerid, "sesli - levye ile e�yalar� parampar�a ederek h�zl�ca ara�t�r. (h�zl�)");
		return 1;
	}

	if (CompareStrings(param, "sessiz"))
	{
		pTemp[playerid][JackingType] = 5;
		StealingHouse[playerid] = houseid;

		new htime;

		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		static const str_size[] = "{"COL_GREY"}Ev soygununa ba�lamak ister misin? [%s] %i saniye s�recek";
		new mes[sizeof(str_size) + 6 + 70];
		format(mes, sizeof(mes), str_size, (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])), htime);
        Dialog_Show(playerid, StartStealingHouse, DIALOG_STYLE_MSGBOX, "{FFFFFF}Ev Soygunu", mes, "Ba�la", "�ptal");
	}
	else if (CompareStrings(param, "sesli"))
	{
		if (!CheckHanditem(playerid,18634)) return SendErrorMessage(playerid, "Elinizde bir levye olmal�. (/aksesuar)");
		pTemp[playerid][JackingType] = 6;
		StealingHouse[playerid] = houseid;

		new htime;

		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = floatround((250+HouseInfo[houseid][hLock]*250)*0.6);
			case 1: htime = floatround((250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05))*0.6);
			case 2: htime = floatround((250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15))*0.6);
		}

		static const str_size[] = "{"COL_GREY"}Ev soygununa ba�lamak ister misin? [%s] %i saniye s�recek";
		new mes[sizeof(str_size) + 76];
		format(mes, sizeof(mes), str_size, (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])), htime);
        Dialog_Show(playerid, StartStealingHouse, DIALOG_STYLE_MSGBOX, "{FFFFFF}Ev Soygunu", mes, "Ba�la", "�ptal");
	} else {
		SendHelpMessage(playerid, "/soygun (parametre)");
		SendSyntaxMessage(playerid, "sessiz - maymuncukla kasay� teknik bir �ekilde a�mak (yava�)");
		SendSyntaxMessage(playerid, "sesli - levye ile e�yalar� parampar�a ederek h�zl�ca ara�t�r. (h�zl�)");
		return 1;
	}

	return 1;
}
