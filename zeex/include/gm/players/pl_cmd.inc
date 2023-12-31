alias:konum("lokasyon", "sokak");
CMD:konum(playerid, params[])
{
	new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;

	GetPlayerPos(playerid, x, y, z);
	GetZone(x, y, location, MAX_ZONE_NAME);

	if (IsPlayerInAnyDynamicArea(playerid)) {
		new areas[5], street_area[2], j = GetPlayerNumberDynamicAreas(playerid);
		GetPlayerDynamicAreas(playerid, areas, sizeof(areas));

		if (GetStreet(areas, j, street_area)) {
			if (street_area[1] == -1)
				return SendSpecialMessage(playerid, "%s, %s.", location, street_names[street_area[0]]);
			else
				return SendSpecialMessage(playerid, "%s, %s %s.", location, street_names[street_area[0]],street_names[street_area[1]]);
		}
	}

	SendSpecialMessage(playerid, "%s.", location);
	return 1;
}

alias:evgps("adres", "adress");
CMD:evgps(playerid, params[])
{
	new houseid;
	if (sscanf(params,"d", houseid)) 			return SendHelpMessage(playerid, "/evgps [Ev ID]");
	if (houseid < 0 || houseid >= MAX_HOUSES)	return SendErrorMessage(playerid,"Ge�ersiz Ev ID.");
	if (!HouseInfo[houseid][hID])				return SendErrorMessage(playerid, "B�yle bir adres bulunamad�.");

	if (HouseInfo[houseid][hApart])	Waypoint_Set(playerid, ApartInfo[HouseInfo[houseid][hApart]][aPosX], ApartInfo[HouseInfo[houseid][hApart]][aPosY], ApartInfo[HouseInfo[houseid][hApart]][aPosZ]);
	else 							Waypoint_Set(playerid, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]);

	SendSyntaxMessage(playerid, "Ev (%s) GPS'te i�aretlendi. (/cpsifirla)", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));
	return 1;
}

alias:isyerigps("igps");
CMD:isyerigps(playerid, params[])
{
	new bizid;

	if (sscanf(params, "d", bizid))				return SendHelpMessage(playerid, "/igps [Mekan ID]");
	if(bizid < 0 || bizid >= MAX_BIZ)			return SendErrorMessage(playerid, "Ge�ersiz i�yeri/mekan ID'si.");
	if(!BizInfo[bizid][bizID])					return SendErrorMessage(playerid, "B�yle bir i�letme/mekan bulunamad�.");

	Waypoint_Set(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	SendSyntaxMessage(playerid, "Belirtilen i�letme/mekan GPS'te i�aretlendi. (/cpsifirla)");

	return 1;
}

CMD:paraver(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return SendErrorMessage(playerid, "�u anda bu �zelli�i kullanamazs�n�z.");

	new userid, amount;

	if (sscanf(params,"ud", userid, amount))				return SendHelpMessage(playerid, "/paraver [ID / isim] [tutar]");
	if (userid == playerid)									return 1;
	if (PlayerInfo[playerid][pHours] < 2)					return SendErrorMessage(playerid, "Para g�nderimi yapabilmek i�in sunucuda 2 saat oynamal�s�n�z.");
	if (GetPVarInt(playerid, #just_paid) > gettime())		return SendErrorMessage(playerid, "2 saniye bekleyin.");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (amount > GetCash(playerid) || amount <= 0)			return SendNotCash(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))			return SendNotNearPlayer(playerid);

	SetPVarInt(playerid, #just_paid, gettime() + 2);

	new money1 = PlayerInfo[playerid][pCash], money2 = PlayerInfo[userid][pCash];

	GiveCash(playerid, -amount);
	GiveCash(userid, amount);
	PlaySound(playerid, 1052);
	PlaySound(userid, 1052);
	SendSyntaxMessage(playerid, "%s [ID: %i] adl� ki�iye $%i para verdiniz.", GetNameWithMask(userid), userid, amount);
	SendSyntaxMessage(userid, "%s [ID: %i] adl� ki�i size $%i para verdi.", GetNameWithMask(playerid), playerid, amount);
	SendAdmMessage("%s (ID: %i) adl� ki�i %s (ID: %i) adl� ki�iye $%i elden para verdi.", GetNameEx(playerid), playerid, GetNameEx(userid), userid, amount);

	new mes[256];
	format(mes, 128, ", %s adl� ki�iye bir miktar para verir.", GetNameWithMask(userid));
	pc_cmd_me(playerid, mes);

    format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SONRAKI): %i] elden para verdi %s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SONRAKI): %i] -- $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money1, GetCash(playerid), GetName(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid), money2, GetCash(userid), amount);
    insert_log(mes, MONEY_LOG, 1, playerid);
	return 1;
}
alias:lisansgoster("kimlikgoster", "kimlik", "ehliyetgoster");
CMD:lisansgoster(playerid, params[])
{
	new userid;
	if (sscanf(params,"u", userid))	return SendHelpMessage(playerid, "/kimlikgoster [ID / isim]");
	if (userid == playerid)
	{
		pc_cmd_server_ame(playerid, "kimlik kart�na bakar.");
		ShowLicenses(playerid, playerid);
		return 1;
	}

	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(8.0, playerid, userid))	return SendNotNearPlayer(playerid);

	new mes[128];
	format(mes, sizeof(mes), "%s kimlik kart�n� g�sterir.", GetNameWithMask(playerid));
	SendServerMessage(playerid, "%s adl� ki�iye lisans�n�z� g�sterdiniz.", GetNameEx(userid));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	ShowLicenses(playerid, userid);
	return 1;
}
alias:avukatlisansgoster("algoster", "avukatlisans");
CMD:avukatlisansgoster(playerid, params[])
{
	new userid;
	if (sscanf(params,"u", userid))	return SendHelpMessage(playerid, "/avukatlisansgoster [ID / isim]");
	if (userid == playerid)
	{
		pc_cmd_server_ame(playerid, "avukat lisans�na kart�na bakar.");
		ShowLawyerLicenses(playerid, playerid);
		return 1;
	}

	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(8.0, playerid, userid))	return SendNotNearPlayer(playerid);

	new mes[128];
	format(mes, sizeof(mes), "%s avukat lisans�n� g�sterir.", GetNameWithMask(userid));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	ShowLawyerLicenses(playerid, userid);
	return 1;
}

CMD:id(playerid, params[])
{
	if (isnull(params))		return SendHelpMessage(playerid, "/id [ID / isim]");
	if (isNumeric(params))
	{
	    new userid = strval(params);
	    if (!IsPlayerLogged(userid))	return SendErrorMessage(playerid, "Herhangi bir sonu� bulunamad�.");

	    SendClientMessageEx(playerid, COLOUR_TURBO, "%s (ID: %d, Seviye: %d)", GetNameEx(userid), userid, PlayerInfo[userid][pLevel]);
	    return 1;
	}

	new count;
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || strfind(GetName(i), params, true) == -1) continue;

        SendClientMessageEx(playerid, COLOUR_TURBO, "%s (ID: %d, Seviye: %d)", GetNameEx(i), i, PlayerInfo[i][pLevel]);
        count = 1;
	}

	if (!count) SendErrorMessage(playerid, "Herhangi bir sonu� bulunamad�.");
	return 1;
}

alias:admins("yoneticiler", "adminler");
CMD:admins(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "Aktif Adminler");

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i)) continue;

		if (PlayerInfo[i][pAdmin] >= 1 && PlayerInfo[i][pAdminHide] == 0) {
			new admin[32], prefix[32];

			//if(!PlayerInfo[i]{pAdmin}) continue;
			if(!PlayerInfo[i][pAdmin]) continue;
            
			if (PlayerInfo[i][pRdscripter] == 1)                    admin = "3rd Party Scripter";
            else if (PlayerInfo[i][pAdmin] == DEVELOPER_LEVEL)			admin = "Management";
			else if (PlayerInfo[i][pAdmin] == HIGH_ADMIN_LEVEL) 		admin = "Lead Admin";
			else if (PlayerInfo[i][pAdmin] == 3)					admin = "Senior Admin";
			else if (PlayerInfo[i][pAdmin] == 2)						admin = "Liberty Admin";
			else if (PlayerInfo[i][pRdscripter] == 3)						admin = "Party Scripter";
			else if (PlayerInfo[i][pAdmin] == 1 && !PlayerInfo[i][pMapper])	admin = "Junior Admin";
			else if (PlayerInfo[i][pAdmin] == 1337)					admin = "Founder";
			else if (PlayerInfo[i][pMapper] == 1)                    admin = "Mapper";
			//else													format(admin, sizeof(admin), "%i Yetkili", PlayerInfo[i][pAdmin]);
			if (!IsAdminDuty(i))	SendClientMessageEx(playerid, COLOUR_ALTO, "(%s) %s (%s, ID: %i)", admin, GetNameEx(i), GetAccName(i), i);
			else					SendClientMessageEx(playerid, COLOUR_APPLE, "(%s) %s (%s, ID: %i) - M�sait", admin, GetNameEx(i), GetAccName(i), i);
		 }
	}
	return 1;
}

alias:testers("helpers", "supports", "supporters");
CMD:testers(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "Aktif Supporterlar");

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i)) continue;

		if (PlayerInfo[i][pHelper] >= 1) {
			new admin[16];

			//if(!PlayerInfo[i]{pAdmin}) continue;
			if(!PlayerInfo[i][pHelper]) continue;

			new helper[32];

			if (PlayerInfo[i][pHelper] == 1)  helper = "Supporter I";
			else if (PlayerInfo[i][pHelper] == 2)  helper = "Supporter II";
			else if (PlayerInfo[i][pHelper] == 3)  helper = "Supporter III";
			else if (PlayerInfo[i][pHelper] == 4)  helper = "Supporter IV";
			else if (PlayerInfo[i][pHelper] == 5)  helper = "Supporter V";
			//else													format(admin, sizeof(admin), "%i Yetkili", PlayerInfo[i][pAdmin]);
			if (!IsTesterDuty(i))	SendClientMessageEx(playerid, COLOUR_ALTO, "(%s) %s (%s, ID: %i)", helper, GetNameEx(i), GetAccName(i), i);
			else					SendClientMessageEx(playerid, COLOUR_APPLE, "(%s) %s (%s, ID: %i) - M�sait", helper, GetNameEx(i), GetAccName(i), i);
		 }
	}
	return 1;
}

alias:pmengel("pmkapat", "pmengelle");
CMD:pmengel(playerid, params[])
{
    //if (PlayerInfo[playerid][pPremium] < 1) return SendErrorMessage(playerid, "Bu �zelli�i yaln�zca premium hesaplar kullanabilir.");

	new userid;

	if (sscanf(params,"u", userid))	return SendHelpMessage(playerid, "/pmengel [ID / isim]");
	if (userid == playerid)			return 1;
	if (!IsPlayerLogged(userid)) 	return SendNotConnected(playerid);

    if (people_blocking[playerid][userid] == 1)
    {
		SendSyntaxMessage(playerid, "%s [ID: %i] adl� ki�iyi PM blok listesinden kald�rd�n�z.", GetNameEx(userid), userid);
		people_blocking[playerid][userid] = 0;
		return 1;
	}

    SendSyntaxMessage(playerid, "PM blok listesine %s [ID: %i] adl� ki�iyi eklediniz.", GetNameEx(userid), userid);
	people_blocking[playerid][userid] = 1;
	return 1;
}

alias:engellistesi("pmengelliste", "listepmengel");
CMD:engellistesi(playerid, params[])
{
	//if (PlayerInfo[playerid][pPremium] < 1) return SendErrorMessage(playerid, "Bu �zelli�i yaln�zca premium hesaplar kullanabilir.");

	SCM(playerid, COLOR_LIGHTRED, "|______PM ENGEL L�STES� "ProjectName"______|");
	foreach(new i : Player)
	{
		if (people_blocking[playerid][i] == 0) continue;

		SendClientMessageEx(playerid, COLOR_INFO, "[ID: %i] %s", i, GetNameEx(i));
	}
	return 1;
}

alias:sonarac("lastcar", "oldcar");
CMD:sonarac(playerid, params[])
{
	new targetid = playerid;

	if(PlayerInfo[playerid][pAdmin] > 0)
	{
		sscanf(params, "u", targetid);
	}

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "Karakter �evrimi�i de�il.");

	new lastEnteredVehicleID;

	lastEnteredVehicleID = GetPVarInt(targetid, PVAR_LASTENTEREDVEH_ID);

	if(!IsValidVehicle(lastEnteredVehicleID))
		return SendErrorMessage(playerid, "En son binilen ara� bulunamad�.");

	SM1(playerid, "En son %d numaral� araca binildi.", lastEnteredVehicleID);

	return 1;
}

alias:saat("zaman", "tarih");
CMD:saat(playerid, params[])
{
	new hour, minute, mes[128];

	gettime(hour,minute);
	format(mes, sizeof(mes), "~w~%02d:%02d~n~Maas: %02i dakika", hour, minute, 60 - PlayerInfo[playerid][pPayDayTime]);

	if (PlayerInfo[playerid][pMutedTime] > 0)	format(mes, sizeof(mes), "%s~n~~r~Susturma Bitisi: %i", mes, PlayerInfo[playerid][pMutedTime]);

	if (PlayerInfo[playerid][pJailed] == PALOMINO_JAIL) //|| PlayerInfo[playerid][pJailed] == LSPD_JAIL || PlayerInfo[playerid][pJailed] == SASD_JAIL)
	{
		format(mes, sizeof(mes), "~y~Kalan hapis: %i~n~%s", PlayerInfo[playerid][pJailTime], mes);
		GameTextForPlayer(playerid, mes, 5000, 1);
		ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0,1);
		return 1;
	}
	else if (PlayerInfo[playerid][pIsolateTime] != 0)
	{
		format(mes, sizeof(mes), "~y~Kalan izole suresi: %i~n~%s", PlayerInfo[playerid][pIsolateTime], mes);
		GameTextForPlayer(playerid, mes, 5000, 1);
		ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0,1);
		return 1;
	}
	else if (PlayerInfo[playerid][pJailed] == PRISON_JAIL)
	{
		format(mes, sizeof(mes), "~y~Kalan hapis: %i~n~%s", PlayerInfo[playerid][pJailTime], mes);
		GameTextForPlayer(playerid, mes, 5000, 1);
		ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0,1);
		return 1;
	}
	else
	{
		GameTextForPlayer(playerid, mes, 5000, 1);
		pc_cmd_server_ame(playerid, "saatine bakar.");

		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)	ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0,1);
	}
	return 1;
}

CMD:yazitura(playerid, params[])
{
	SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s bozuk paray� havaya atar. (( %s ))", GetNameWithMask(playerid), (random(2) == 0)?("Yaz�"):("Tura"));
	return 1;
}
CMD:dene(playerid)
{
	new const status[2][18] = {EMBED_PASTELGREEN "Ba�ar�l�", EMBED_TOMATO "Ba�ar�s�z"};

	SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, sprintf("> %s " EMBED_VISTABLUE "oldu. (( %s ))", status[random(sizeof(status))], GetNameWithMask(playerid)));
	return 1;
}
CMD:zar(playerid, params[])
{
     if (!PlayerInfo[playerid][pZar])	return SendErrorMessage(playerid, "Zar�n bulunmuyor.");	
	 
	new opt[12];

	if(sscanf(params, "s[12]", opt)) return SendHelpMessage(playerid, "/zar [tek/cift]");

	if(!strcmp(opt, "tek", true)){
		new playerdice;

		playerdice = random(6)+1;

		SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d ))", GetNameWithMask(playerid), playerdice);
	} else if(!strcmp(opt, "�ift", true) || !strcmp(opt, "cift", true)){
		new firstDice, secondDice;

		firstDice = random(6)+1;
		secondDice = random(6)+1;

		SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d, %d ))", GetNameWithMask(playerid), firstDice, secondDice);
	}
	/*if (!IsPlayerHasItem(playerid, INV_DICE))	return SendErrorMessage(playerid, "Zar�n bulunmuyor.");

	SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %i )).", GetNameWithMask(playerid), random(6)+1);*/
	return 1;
}
CMD:azar(playerid, params[])
{
	if(!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return 0;

	new opt;
	if(sscanf(params, "d", opt)) return SendHelpMessage(playerid, "/azar [say�]");
	if(opt < 1 || opt > 6) return SendErrorMessage(playerid, "Girilen say� de�er 1 ile 6 aras�nda olmal�d�r.");
	SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d ))", GetNameWithMask(playerid), opt);

	return 1;
}
CMD:azar2(playerid, params[])
{
	if(!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return 0;

	new opt, opt2;
	if(sscanf(params, "dd", opt, opt2)) return SendHelpMessage(playerid, "/azar2 [say�] [say� 2]");
	if(opt < 1 || opt > 6 || opt2 < 1 || opt > 6) return SendErrorMessage(playerid, "Girilen say� de�erleri 1 ile 6 aras�nda olmal�d�r.");
	SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d, %d ))", GetNameWithMask(playerid), opt, opt2);

	return 1;
}
alias:maske("masketak");
CMD:maske(playerid, params[])
{
	if (PlayerInfo[playerid][pOnDuty])			return SendErrorMessage(playerid, "G�revdeyken maske takamazs�n�z!");

	if (!maskOn{playerid})
	{
		if (!PlayerInfo[playerid][pMaske])	return SendErrorMessage(playerid, "Maskeniz yok.");

	    pc_cmd_server_ame(playerid, "* maske takar. ");
		GameTextForPlayer(playerid, "~w~MASKE TAKTINIZ", 4000, 4);
		maskOn{playerid} = true;
		ShowPlayerName(playerid, false);
		format(PlayerInfo[playerid][pMaskname], 32, "Maske_%i", randomEx(100000, 999999));
		cNametag[playerid] = CreateDynamic3DTextLabel("Maske takar...", 0xFFFFFFFF, 0.0, 0.0, 0.1, NT_DISTANCE, .attachedplayer = playerid, .testlos = 1);
	}
	else
	{
	    pc_cmd_server_ame(playerid, "* maskesini ��kart�r. ");
		GameTextForPlayer(playerid, "~w~MASKENIZI CIKARTTINIZ", 4000, 4);
		RemovePlayerMask(playerid);
	}
	return 1;
}

alias:isafk("afkkontrol", "afk");
CMD:isafk(playerid, params[])
{
	new id;

	if (sscanf(params, "u", id))	return SendHelpMessage(playerid, "/isafk [ID / isim]");
	if (!IsPlayerLogged(id))		return SendNotConnected(playerid);

	if (IsPlayerAFK(id))	SendClientMessageEx(playerid, COLOR_LIGHTRED, "%s (%i), %i saniyedir AFK.", GetNameEx(id), id, pTemp[id][pDarkAFK]-2);
	else					SendClientMessageEx(playerid, COLOR_LIGHTRED, "%s (%i), AFK de�il.", GetNameEx(id), id);
	return 1;
}

CMD:recetegoster(playerid, params[])
{
    if (PlayerInfo[playerid][pPrescribe] < gettime())	return SendErrorMessage(playerid, "Re�eteniz yok.");

    new userid;

	if (sscanf(params,"u",userid))					return SendHelpMessage(playerid, "/recetegoster [ID / isim]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

    SCM(userid, COLOR_SERVER2, "_____________Re�ete______________");
	SendClientMessageEx(userid, COLOR_WHITE, "Hasta: %s Ya�: %s", GetNameEx(playerid), PlayerInfo[playerid][pAge]);
	SendClientMessage(userid, COLOR_WHITE, "Re�eteyi Veren: All Saints General Hospital.");
	SendClientMessage(userid, COLOR_WHITE, "T�bbi esrar�n sat�n al�nmas�, saklanmas� ve kullan�lmas� i�in re�ete.");
	SCM(userid, COLOR_SERVER2, "_________________________________");

	new mes[128];
	format(mes, sizeof(mes), ", %s adl� ki�iye re�etesini g�sterir.", GetNameWithMask(userid));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	return 1;
}

alias:karakter("karakterim", "bilgilerim");
CMD:karakter(playerid, params[])
{
	ShowStats(playerid, playerid);
	return 1;
}

alias:bagis("bagisyap");
CMD:bagis(playerid, params[])
{
	new amount;

	if (sscanf(params,"d",amount))					return SendHelpMessage(playerid, "/bagis [tutar]");
	if (amount > GetCash(playerid) || amount <= 0)	return SendNotCash(playerid);

	PlaySound(playerid, 1052);
	SendSyntaxMessage(playerid, "Devlet kasas�na $%i ba���lad�n�z.", amount);
	AMSG(COLOUR_ALTO, "Bilgi: %s taraf�ndan devlet kasas�na ba��� yap�ld�: $%i.", GetNameEx(playerid), amount);

	new money = PlayerInfo[playerid][pCash];
	GiveCash(playerid, -amount);

	new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SIMDIKI): %i] ba��� yapt� (/charity) -- $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), amount);
    insert_log(mes, MONEY_LOG, 5, PlayerInfo[playerid][pAccID]);
	return 1;
}

alias:kogusnumaram("hapisnumaram", "hapisbilgi");
CMD:kogusnumaram(playerid, params[])
{
	if (PlayerInfo[playerid][pJailed] != PRISON_JAIL)	return SendErrorMessage(playerid, "Hapiste de�ilsiniz.");

	SendClientMessageEx(playerid, COLOR_GRAD2, "�sim: %s | Kodes Numaras�: %s%i", GetNameEx(playerid), (PlayerInfo[playerid][pIsolateTime] != 0)?("B"):("A"),PlayerInfo[playerid][pPrisoned]+100);
	return 1;
}

/*alias:destek("destekbildirimi", "/ticket");
CMD:destek(playerid, params[])
{
	if (isnull(params)) 				return SendHelpMessage(playerid, "/destek [destek talebi]");
	if (request_time > gettime())	return SendSpecialMessage(playerid, "L�tfen %i saniye bekleyin.", request_time - gettime());

	request_time = gettime() + 60;
	SendSyntaxMessage(playerid, "Talebiniz m�sait y�neticilere iletildi, l�tfen sab�rla bekleyiniz.");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !CheckAdmin(i, ADMIN_LEVEL_1) || (PlayerInfo[i][pSettings] & togService)) continue;

			SendClientMessageEx(i, 0x00CC99AA, "[DESTEK] %s (ID: %i): %.*s ...", GetNameEx(playerid), playerid, pos, params);
			SendClientMessageEx(i, 0x00CC99AA, "... %s", params[pos]);
		}
	}
 	else
	{
	    foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !CheckAdmin(i, ADMIN_LEVEL_1) || (PlayerInfo[i][pSettings] & togService)) continue;

			SendClientMessageEx(i, 0x00CC99AA, "[DESTEK] %s (ID: %i): %s", GetNameEx(playerid), playerid, params);
		}
	}
	return 1;
}*/

CMD:debugsoygun(playerid, params[])
{
	JackingLock[playerid] = 5;
	pTemp[playerid][JackingType] = 5;
	return 1;
}

CMD:sat(playerid, params[])
{
	new bizid;

	if ((bizid = GetNearInsideBiz(playerid)) != -1)
	{
		if (BizInfo[bizid][bizType] == BIZ_PAWN)
		{
			Dialog_Show(playerid, SellPawn, DIALOG_STYLE_LIST, "Pawnshop", "Radyo Sat\n�al�nt� E�yalar� Sat", "Sat", "�ptal");
		}
	}
	return 1;
}

CMD:satinal(playerid, params[])
{
	new string[1024], bizid = -1;

	if ((bizid = GetNearInsideBiz(playerid)) != -1)
	{
	    if (BizInfo[bizid][bizType] == BIZ_BUILD)
	    {
	        Dialog_Show(playerid, BuyInterior, DIALOG_STYLE_INPUT, "{FFFFFF}Dekorasyon", "{FFFFFF}Interiorunu de�i�tirmek istedi�iniz evin ID'sini giriniz: \nAyr�ca ev sana ait olmal�d�r (/mulklerim)", ">>>", "Kapat");
	    }

	    else if (BizInfo[bizid][bizType] == BIZ_STORE || BizInfo[bizid][bizType] == BIZ_PHARMACY || BizInfo[bizid][bizType] == BIZ_BAR || BizInfo[bizid][bizType] == BIZ_PAWN) //4
	    {
			new type;
			switch(BizInfo[bizid][bizType])
			{
				case BIZ_STORE: type = 4;
				case BIZ_BAR: type = 5;
				case BIZ_PHARMACY: type = 6;
				case BIZ_PAWN: type = 7;
			}
			if (!type)	return SendErrorMessage(playerid, "[#PL-493] Sistem Hatas�!"); //return 1;
			if (type == 7) SendHelpMessage(playerid, "/sat komutunu unutma, �al�nt� e�yalar�n� satabilirsin.");

			new diatxt[LIMIT_MAX_PRODUCTS*256];

			for(new i = 0; i < max_product[type]; i++)
			{
				format(diatxt, sizeof(diatxt), "%s%i(0.0, 0.0, 63.0, 0.8)\t~w~%s~n~~g~~h~$%i\n", diatxt, model_order[type][i], TurkishCharFix(name_order[type][i]), BizInfo[bizid][bizProductPrice][i]);
			}

			new title[32+23];
			format(title, sizeof(title), "%s____-____Urun Secimi", BizInfo[bizid][bizName]);

			Dialog_Show(playerid, StoreDialog, DIALOG_STYLE_PREVIEW_MODEL, title, diatxt, "Satin Al", "Iptal");
	    }
	    else if (BizInfo[bizid][bizType] == BIZ_BARBER)
	    {
	        if (GetPVarInt(playerid, #buy_attach))	return SendErrorMessage(playerid, "Ge�erli i�lemi bitir.");
			if (GetNextToySlot(playerid) == -1)		return SendWarningMessage(playerid, "T�m giysi dolaplar� dolu.");

			for(new x; x < sizeof(BarberShop); x++)
			{
				format(string, sizeof(string), "%s%s - $%i\n", string, BarberShop[x][toyName], BarberShop[x][toyPrice]);
			}

			Dialog_Show(playerid, BarberDialog, DIALOG_STYLE_LIST, "{FFFFFF}Secenekler", string, "Sec", "Iptal");
		}
		else if (BizInfo[bizid][bizType] == BIZ_PIZZA || BizInfo[bizid][bizType] == BIZ_CLUCKIN || BizInfo[bizid][bizType] == BIZ_BURGER || BizInfo[bizid][bizType] == BIZ_DONUT)
		{
			for(new i; i != 4; i++)
			{
			    TextDrawShowForPlayer(playerid, TD_restaurant[i]);
			}

			new mes[128], type = BizInfo[bizid][bizType] - BIZ_PIZZA;

			for(new i; i != max_product[type]; i++)
			{
			    format(mes, sizeof(mes), "%s~n~~r~Can: +%i~n~~r~Acligi giderir~n~~p~Fiyat: $%i~n~", TurkishCharFix(name_order[type][i]), 30 + (i * 10), BizInfo[bizid][bizProductPrice][i]);
				PlayerTextDrawSetString(playerid, TD_restaurant_prod[playerid][i], mes);
				PlayerTextDrawShow(playerid, TD_restaurant_prod[playerid][i]);
	            PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][i + 4], model_order[type][i]);
	            PlayerTextDrawShow(playerid, TD_restaurant_prod[playerid][i + 4]);
			}

			SelectTextDraw(playerid, 0x00cb77FF);
			SetPVarInt(playerid, #restaurant, 1);
		}
		else if (BizInfo[bizid][bizType] == BIZ_CLOTHES)
		{
			if (PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "��ba��ndayken bu komutu kullanamazs�n�z.");
	        if (GetCash(playerid) < 100) return SendErrorMessage(playerid, "Yeterli paran�z yok. ($100)");

			mysql_tquery(dbHandle, GetSkin("game_skins.model_id, game_skins.price", "", "", 1, -1, -1, -1, PlayerInfo[playerid][pSex], PlayerInfo[playerid][pRace]), "OnPlayerListSkins", "d", playerid);

		}
		else if (pTemp[playerid][pBizEntered] != -1 && BizInfo[pTemp[playerid][pBizEntered]][bizType] == BIZ_BARBER)
		{
			if (GetPVarInt(playerid, #buy_attach))	return SendErrorMessage(playerid, "Mevcut i�lemi bitirin.");
			if (GetNextToySlot(playerid) == -1)		return SendErrorMessage(playerid, "T�m giysi dolaplar� dolu.");

			for(new x; x < sizeof(BarberShop); x++)
			{
				format(string, sizeof(string), "%s%s - $%i\n", string, BarberShop[x][toyName], BarberShop[x][toyPrice]);
			}
			Dialog_Show(playerid, BarberDialog, DIALOG_STYLE_LIST, "{FFFFFF}Secenekler", string, "Sec", "Kapat");
		}
		else if (BizInfo[bizid][bizType] == BIZ_ATTACH)
		{
			if (GetPVarInt(playerid, #buy_attach))	return SendErrorMessage(playerid, "Mevcut i�lemi bitirin.");
			if (GetNextToySlot(playerid) == -1)		return SendErrorMessage(playerid, "T�m giysi dolaplar� dolu.");

			Dialog_Show(playerid, BizAttachDialog, DIALOG_STYLE_LIST, "{FFFFFF}Kategori Se�", "1. M�zik Enstr�manlar�\n2. Saat\n3. Aletler\n4. Spor Ekipmanlar�\n5. Aksesuarlar", "Se�", "Kapat");
		}
	}

	return 1;
}

alias:atesyak("evyak", "ates", "isyeriyak", "mekanyak");
CMD:atesyak(playerid, params[])
{
	if (!FireOnline() || !PoliceOnline())	return SendErrorMessage(playerid,"Bu komutu kullanabilmek i�in i�ba��nda %i polis ve %i itfaiye olmal�d�r!", NEED_COPS_TO_CRIME, NEED_FIRE_TO_CRIME);

	if (!PlayerInfo[playerid][pCakmak]) return SendErrorMessage(playerid, "�akma��n yok.");
	if (!PlayerInfo[playerid][pBenzinBidonu])  return SendErrorMessage(playerid, "Yak�t bidonunuz yok.");
	if (pTemp[playerid][pFireTime] > 0)			return SendErrorMessage(playerid, "Zaten ate� yakm��s�n�z.");

	new type = GetNearBuilding(playerid, 0.0, 2.0), building;
	switch(type) {
		case 0: {
			building = GetNearOutsideHouse(playerid);
			if (building == -1 || (gettime()-HouseInfo[building][hFireTimer] <= 0)) return SendErrorMessage(playerid, "Tekrar dene!");
		}
		case 1: {
			building = GetNearOutsideGarage(playerid);
			if (building == -1 || (gettime()-BizInfo[building][bFireTimer] <= 0)) return SendErrorMessage(playerid,"Tekrar dene!");
		}
		case 2: {
			building = GetNearOutsideBiz(playerid);
			if (building == -1 || (gettime()-GarageInfo[building][gFireTimer] <= 0)) return SendErrorMessage(playerid, "Tekrar dene!");
		}

		default: return SendErrorMessage(playerid, "Binan�n giri�ine gidin.");
	}

	if (building == -1) return SendErrorMessage(playerid, "Binan�n giri�ine gidin.");

	pTemp[playerid][pFireTime] = 30;
	SetPVarInt(playerid, #firetype, type);
	SetPVarInt(playerid, #firebuildID, building);

	SendSyntaxMessage(playerid, "Ate� yakmaya ba�lad�n�z. ��lemi geri almak i�in: {FF6347}/durdur");

	PlayerInfo[playerid][pBenzinBidonu] = 0;

	SavePlayerPos(playerid);
	FreezePlayer(playerid);
	ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0, 0);
	return 1;
}

CMD:soyun(playerid, params[])
{
	new	race = PlayerInfo[playerid][pRace];

	if (PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "��ba��nda bu komutu kullanamazs�n.");

	if (PlayerInfo[playerid][pSkin] != GetPlayerSkin(playerid))
	{
	    if (!PlayerInfo[playerid][pSkin]) return SendErrorMessage(playerid, "K�yafetler size ait olmad��� i�in iade edemezsiniz.");

	    SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	    SendSyntaxMessage(playerid, "K�yafetlerini geri ald�n.");
	    return 1;
	}

    switch (PlayerInfo[playerid][pSex])
   	{
  		case 1:
  		{
			switch(race)
			{
			    case 2: SendSyntaxMessage(playerid, "K�yafetlerinizi ��kard�n�z."), SetPlayerSkin(playerid, 18);
			    case 1:
				{
				    switch(random(3))
				    {
				        case 0: SetPlayerSkin(playerid, 45);
				        case 1: SetPlayerSkin(playerid, 97);
				        case 2: SetPlayerSkin(playerid, 154);
				    }
					SendSyntaxMessage(playerid, "K�yafetlerinizi ��kard�n�z.");
				}
			}
		}
		case 2:
		{
			switch(race)
			{
			    case 2: SendSyntaxMessage(playerid, "Elbisenizi ��kard�n�z."), SetPlayerSkin(playerid, 139);
			    case 1:
				{
				    switch(random(3))
				    {
				        case 0: SetPlayerSkin(playerid, 251);
				        case 1: SetPlayerSkin(playerid, 140);
				        case 2: SetPlayerSkin(playerid, 138);
				    }
					SendSyntaxMessage(playerid, "Elbisenizi ��kard�n�z.");
				}
			}
		}
  	}
	return 1;
}

alias:stildegistir("konusmastili", "yuruyusstili", "stiller");
CMD:stildegistir(playerid, params[])
{
	new option, secoption;

	if (sscanf(params,"iI(-1)", option, secoption))	return SendHelpMessage(playerid, "/stildegistir ([1] Y�r�me Stili | [2] Konu�ma Tarz� | [3] D�v�� Tarz� | [4] Hud G�stergesi)");

	if (option == 1)
	{
		new style;

		if (sscanf(params,"{d}d",style))			return SendHelpMessage(playerid, "/stildegistir 1 [Y�r�me tarz� (0-11)]");
		if (style < 0 || style > 11)				return SendErrorMessage(playerid, "Y�r�me tarz� 0 ve 11 aras� olmal�d�r.");

		PlayerInfo[playerid][pWalk] = style;

		if (!style)		SendSyntaxMessage(playerid, "Y�r�y�� tarz�n� devre d��� b�rakt�n.");
		else			SendSyntaxMessage(playerid, "Y�r�y�� tarz�n %d numaral� stil ile de�i�tirildi.", style);
		return 1;
	}
	else if (option == 2)
	{
		new style;

		if (sscanf(params,"{d}d",style))		return SendHelpMessage(playerid, "/stildegistir [Konu�ma Tarz� (0-9)]");
		if (style < 0 || style > 9)				return SendErrorMessage(playerid, "Konu�ma tarz�n�z 0 ile 9 aras�nda olmal�d�r.");

		PlayerInfo[playerid][pTalk] = style;

		if (!style)		SendSyntaxMessage(playerid, "Konu�ma animasyonunu kapatt�n�z.");
		else			SendSyntaxMessage(playerid, "Konu�ma animasyonunu de�i�tirdiniz. Yenisi: %i.", style);

		return 1;
	}
	else if (option == 3)
	{
	    //if (PlayerInfo[playerid][pPremium] < 1)	return SendErrorMessage(playerid, "D�v�� stilini sadece premium oyuncular eri�ebilir..");

		new style;

		if (sscanf(params,"{i}i",style))			return SendHelpMessage(playerid, "/stildegistir [D�v�� Tarz� (1-5)]");
		if (style < 1 || style > 5)				return SendErrorMessage(playerid, "D�v�� tarz�n�z 0 ile 5 aras�nda olmal�d�r.");

        SetPlayerFightingStyle(playerid, fight_id[style-1]);
        PlayerInfo[playerid][pFightStyle] = fight_id[style-1];
		SendSyntaxMessage(playerid, "D�v�� tarz�n�z� de�i�tirdiniz. Yenisi: %s.", fight_name[style-1]);

		return 1;
	}
	else if (option == 4)
	{
	    //if (PlayerInfo[playerid][pPremium] < 1)	return SendErrorMessage(playerid, "HUD'u yaln�zca premium hesab�n�z varsa de�i�tirebilirsiniz.");

		new style;

		if (sscanf(params,"{d}d",style))			return SendHelpMessage(playerid, "/stildegistir [Hud G�stergesi (1-4)]");
		if (style < 1 || style > 4)				return SendSyntaxMessage(playerid, "Hud g�stergeniz 1 ile 4 aras�nda olmal�d�r.");

       // PlayerInfo[playerid][pHud] = style-1;
        HideHudTextDraw(playerid);

        if (!(PlayerInfo[playerid][pSettings] & togHUD))	ShowHudTextDraw(playerid);

	}
	return 1;
}

alias:bugkurtar("vwduzelt", "intduzelt", "vwsifirla", "vwkurtar", "intkurtar", "bugkurtar2", "bugkurtar3");
CMD:bugkurtar(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu �zelli�i �u anda kullanamazs�n�z.");

	Dialog_Show(playerid, BugKurtar, DIALOG_STYLE_LIST, "Bug Kurtarma Opsiyonlar�", "Objeleri g�remiyorum/Haritadan d���yorum.\nObjenin i�ine s�k��t�m. (Yukar� at)\nObjenin i�ine girdim. (Alta at)\nObjelerin baz�lar� g�z�km�yor. (objeleriyeniler)", "Se�", "�ptal");
	return 1;
}

CMD:mapfix(playerid, params[])
{
	new Float:pXa, Float:pYa, Float:pZa;
	GetPlayerPos(playerid, pXa, pYa, pZa);
	if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0 && pZa < -20.0)
	{
		if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazs�n.");
		SendClientMessageEx(playerid, COLOUR_TOMATO, "Bulundu�un bug durumundan kurtuldun.");
		SetPlayerPosEx(playerid, 785.9385,-868.3475,35.3712);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		Log_Kaydet("genelLog.txt", sprintf("[/bugkurtar] %s (C_ID: %d | A_ID: %d), disaridayken /bugkurtar komutunu kullandi. (vw/int sifirla, lc gonder) [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetFullDate()));
	}	
	else return SendErrorMessage(playerid, "�u an bug durumunda de�ilsin.");
	return 1;
}