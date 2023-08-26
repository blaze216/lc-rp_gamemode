alias:afaction("abirlik");
CMD:afaction(playerid, params[])
{
	new option[16], secoption[128];

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/afaction [create / remove / edit / list / leader / types]");
		return 1;
	}

	else if (CompareStrings(option, "types"))
	{
		new dialog_header[64] = "{FFFFFF}Tip\t{FFFFFF}Ýsim\n", dialog_body[256];
		dialog_body[0] = EOS;

		format(dialog_body, sizeof(dialog_body), "%s1\tCity\n2\tPolis\n3\tMedikal Departman\n4\tYangýn Departmaný\n5\tHapishane(DoC)\n6\tHaberci\n7\tÇete\n8\tMafya\n9\tLegal\n10\tHaberci\n11\tState Bar", dialog_header);
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Birlik Tipi", dialog_body, "Kapat", "");
	}

	if (CompareStrings(option, "create"))
	{
		new factionid = 0, name[32], shortname[8], type;

		if (sscanf(secoption, "is[8]S()[32]", type, shortname, name))
		{
			SendHelpMessage(playerid, "/afaction create [tip] [kýsaltma] [isim]");
			SendHelpMessage(playerid, "Tip: [1] GOV | [2] Polis | [3] Medikal | [4] Yangýn Departmaný | [5] Hapishane | [6] Haber Birliði | [7] Çete | [8] Mafya | [9] Sivil");
			return 1;
		}

		for(new i = 1; i < MAX_FACTIONS; i++)
		{
			if (Factions[i][fON] != 0) continue;

			factionid = i;
			break;
		}

		if (factionid == -1) 						return SendErrorMessage(playerid, "Maksimum birlik sayýsýna ulaþýldý.");
		if (strlen(name) < 1 || strlen(name) > 30)	return SendErrorMessage(playerid, "Birlik adý 30 karakterden fazla olamaz.");
		if (type < 1 || type > 11)					return SendErrorMessage(playerid, "Birlik tipi 1 ile 10 arasýnda olmalýdýr.");
		if (strfind(name, "'", true) != -1) 	return SendErrorMessage(playerid, "Birlik adýnda týrnak iþareti kullanamazsýn.");

		format(Factions[factionid][fName], 32, "%s", name);
		format(Factions[factionid][fShortName], 8, "%s", shortname);
		Factions[factionid][fColor] = 0xFFFFFF00;
		Factions[factionid][fType] = type;
		Factions[factionid][fRanks] = 20;
		Factions[factionid][fChatON] = 1;
		Factions[factionid][fON] = 1;
		Factions[factionid][fJoinRank] = 1;
		Factions[factionid][fPointTime] = 604800 + gettime();

		FRank[factionid][19][rInvite] = 1;
		FRank[factionid][19][rUninvite] = 1;
		FRank[factionid][19][rRank] = 1;
		FRank[factionid][19][r_eRank] = 1;
		FRank[factionid][19][rSpawn] = 1;
		FRank[factionid][19][rChat] = 1;
		FRank[factionid][19][rTow] = 1;
		FRank[factionid][19][rBodyCam] = 1;
		FRank[factionid][19][r_eRights] = 1;

	    UpdateFactionRankLeader(factionid);

		if (type == FACTION_MAFIA)	Factions[factionid][fPoint] = 50;
		else 						Factions[factionid][fPoint] = 30;

		for(new i; i != 20; i++)
		{
			FactionRanks[factionid][i] = "Belirsiz";
		}

		AddFactionToFile(factionid, shortname, name, Factions[factionid][fColor], type, Factions[factionid][fRanks], Factions[factionid][fPointTime], Factions[factionid][fJoinRank]);
		SendAdmMessage("%s adlý yönetici birlik oluþturdu: %s [ID: %i].", GetAccName(playerid), name, factionid);
		SendHelpMessage(playerid, "Birliði düzenlemek için '/afaction edit' komutunu kullanýnýz.");

		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if (sscanf(secoption, "i", id))							 return SendHelpMessage(playerid, "/afaction remove [ID]");
		if (id < 1 || id > MAX_FACTIONS-1 || !Factions[id][fON]) return SendErrorMessage(playerid, "Belirtilen birlik bulunamadý.");
		//if (IsFactionLegal(id))									return SendErrorMessage(playerid, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½.");

		if (IsValidDynamicPickup(Factions[id][fPickUp])) DestroyDynamicPickup(Factions[id][fPickUp]);

		new query[256];

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `factions` WHERE `id` = %i", Factions[id][fID]);
		mysql_tquery(dbHandle, query);
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `char`='0',`swat`='0',`swat_duty`='0',`duty`='0',`faction`='0',`rank`='0',`sidejob`='0' WHERE `faction`=%i", id);
		mysql_tquery(dbHandle, query);

		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != id) continue;

			RemovePlayerFaction(i);
		}

		SendServerMessage(playerid, "Belirtilen birliði baþarýyla sildiniz. %s [ID: %i].", Factions[id][fName], id);
		Factions[id][fON] = 0;
		Factions[id][fID] = 0;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id, parameters[12], arg[36];

		if (sscanf(secoption, "is[12]S()[36]", id, parameters, arg))
		{
			SendHelpMessage(playerid, "/afaction edit [ID factions] [seçenekler] [value]");
			SendSyntaxMessage(playerid, "spawn / color / name / ranks / joinrank / rankname / type / uniform / carfix");
			return 1;
		}
		if (id < 1 || id > MAX_FACTIONS-1 || !Factions[id][fON]) return SendErrorMessage(playerid, "Belirtilen birlik bulunamadý.");

		if (CompareStrings(parameters, "spawn"))
		{
			GetPlayerPos(playerid, Factions[id][fPosX], Factions[id][fPosY], Factions[id][fPosZ]);
			Factions[id][fSpawnInt] = GetInterior(playerid);
			Factions[id][fSpawnVW] = GetWorld(playerid);

			new query[128 + 56];

			mysql_format(dbHandle, query, sizeof(query), "UPDATE `factions` SET `spawnx` = %f, `spawny` = %f, `spawnz` = %f, `spawnint` = %i, `spawnvw` = %i WHERE `id` = %i",
			Factions[id][fPosX], Factions[id][fPosY], Factions[id][fPosZ], Factions[id][fSpawnInt], Factions[id][fSpawnVW], Factions[id][fID]);
			mysql_tquery(dbHandle, query);

			SendServerMessage(playerid, "Belirtilen birliðin spawn noktasýný ayarladýnýz %s [ID: %i].", Factions[id][fName], id);
			return 1;
		}

		else if (CompareStrings(parameters, "color"))
		{
			new color;
			if (sscanf(arg, "h", color)) return SendHelpMessage(playerid, "/afaction edit [ID] color [HEX]");

			Factions[id][fColor] = color;
			SQL_SetInteger("factions", "color", Factions[id][fColor], Factions[id][fID]);
			SendServerMessage(playerid, "Belirtilen birliðin rengini deðiþtirdiniz {%06x}%s{FF6347} [ID: %i].", color >>> 8, Factions[id][fName], Factions[id][fID]);
			return 1;
		}

		else if (CompareStrings(parameters, "name"))
		{
			new factioname[32], shortname[8];

			if (sscanf(arg, "s[8]S()[32]", shortname, factioname)) 	return SendHelpMessage(playerid, "/afaction edit [ID] name [yeni kýsaltma] [yeni isim]");
			if (isnull(factioname) || strlen(factioname) > 32) 		return SendErrorMessage(playerid, "Birlik adý maksimum 32 karakter olabilir.");

			SendServerMessage(playerid, "Belirtilen birliðin isimi deðiþtirildi. Eski: %s [ID: %i] Yeni: %s [%s].", Factions[id][fName], id, factioname, shortname);

			format(Factions[id][fName], 32, "%s", factioname);
			format(Factions[id][fShortName], 8, "%s", shortname);

			SQL_SetString("factions", "name", Factions[id][fName], Factions[id][fID]);
			SQL_SetString("factions", "shortname", Factions[id][fShortName], Factions[id][fID]);
			return 1;
		}

		else if (CompareStrings(parameters, "ranks"))
		{
			new ranks;
			if (sscanf(arg, "i", ranks)) 	return SendHelpMessage(playerid, "/afaction edit [ID] ranks [rank sayýsý]");
			if (ranks < 1 || ranks > 20)	return SendErrorMessage(playerid, "Rütbe sayýsý 1 ile 20 arasýnda olmalýdýr.");

			Factions[id][fRanks] = ranks;
			SQL_SetInteger("factions", "ranks", Factions[id][fRanks], Factions[id][fID]);
			SendServerMessage(playerid, "Belirtilen birliðin rütbe sayýsýný deðiþtirdiniz: %s [ID: %i] Yeni: %i.", Factions[id][fName], id, ranks);
			return 1;
		}

		else if (CompareStrings(parameters, "type"))
		{
			if (isnull(arg) ||  strval(arg) < 1 || strval(arg) > 10)
			{
				SendHelpMessage(playerid, "/afaction edit [ID] type [tip]");
				SendHelpMessage(playerid, "Tip: [1] GOV | [2] Polis | [3] Medikal | [4] Yangýn Departmaný | [5] Hapishane | [6] Haber Birliði | [7] Çete | [8] Mafya | [9] Sivil");
				return 1;
			}

			new type_fr[11][32] = {"GOV", "Polis", "Medikal", "Yangýn Departmaný", "Hapishane", "Haber Birliði", "Çete", "Mafya", "Sivil", "Haber Birliði (Yönetim)", "State Bar"};

			Factions[id][fType] = strval(arg);
			SQL_SetInteger("factions", "type", Factions[id][fType], Factions[id][fID]);
			SendServerMessage(playerid, "Belirtilen birliðin tipi deðiþtirildi. %s [ID: %i] Yeni: %s [%i].", Factions[id][fName], id, type_fr[strval(arg)-1], strval(arg));

			if (IsFactionLegal(id))
			{
				Factions[id][fPickUp] = CreateDynamicPickup(1239, 1, Factions[id][fUniformX], Factions[id][fUniformY], Factions[id][fUniformZ], Factions[id][fUniformVW], Factions[id][fUniformInt], -1, 100.0);
			}
			else
			{
				if (IsValidDynamicPickup(Factions[id][fPickUp])) DestroyDynamicPickup(Factions[id][fPickUp]);
			}
			return 1;
		}

		else if (CompareStrings(parameters, "joinrank"))
		{
			if (isnull(arg))												return SendHelpMessage(playerid, "/afaction edit [ID] joinrank [rütbe]");
			if (strval(arg) < 1 || strval(arg) > Factions[id][fRanks]-1)	return SendErrorMessage(playerid, "Rütbe 1 ile %i arasýnda olmalýdýr.", Factions[id][fRanks]-1);

			Factions[id][fJoinRank] = strval(arg);
			SQL_SetInteger("factions", "joinrank", Factions[id][fJoinRank], Factions[id][fID]);
			SendServerMessage(playerid, "%s [ID: %i] adlý birliðe giren kiþiler %i rütbesiyle katýlacak.", Factions[id][fName], id, strval(arg));
			return 1;
		}
		else if (CompareStrings(parameters, "carfix"))
		{
			if (!IsFactionLegal(id)) return SendErrorMessage(playerid, "Bu deðer sadece devlet kurumlarý için kullanýlabilir.");

			GetPlayerPos(playerid, Factions[id][Carfix][fixX], Factions[id][Carfix][fixY], Factions[id][Carfix][fixZ]);
			Factions[id][Carfix][fixInt] = GetInterior(playerid);
			Factions[id][Carfix][fixVW] = GetWorld(playerid);

			SQL_SetFloat("factions", "fix_X", Factions[id][Carfix][fixX], Factions[id][fID]);
			SQL_SetFloat("factions", "fix_Y", Factions[id][Carfix][fixY], Factions[id][fID]);
			SQL_SetFloat("factions", "fix_Z", Factions[id][Carfix][fixZ], Factions[id][fID]);
			SQL_SetInteger("factions", "fix_Int", Factions[id][Carfix][fixInt], Factions[id][fID]);
			SQL_SetInteger("factions", "fix_VW", Factions[id][Carfix][fixVW], Factions[id][fID]);

			if (IsValidDynamicPickup(Factions[id][Carfix][fixPickUp])) DestroyDynamicPickup(Factions[id][Carfix][fixPickUp]);

			Factions[id][Carfix][fixPickUp] = CreateDynamicPickup(1650, 1, Factions[id][Carfix][fixX], Factions[id][Carfix][fixY], Factions[id][Carfix][fixZ], Factions[id][Carfix][fixVW], Factions[id][Carfix][fixInt], -1, 20.0);
			SendServerMessage(playerid, "%s [ID: %i] adlý birliðin araç tamir pozisyonunu ayarladýnýz.", Factions[id][fName], id);
			return 1;
		}

		else if (CompareStrings(parameters, "rankname"))
		{
			new rank, name[32];

			if (sscanf(arg, "is[32]", rank, name)) 			return SendHelpMessage(playerid, "/afaction edit [ID] rankname [rütbe] [isim]");
			if (rank < 1 || rank > Factions[id][fRanks])	return SendSyntaxMessage(playerid, "Rütbe 1 ile %i arasýnda olmalýdýr.", Factions[id][fRanks]);
			if (strlen(name) > 30)							return SendSyntaxMessage(playerid, "Rütbe isimi maksimum 30 karakter olmalýdýr.");

			format(FactionRanks[id][rank-1], 32, "%s", name);
			UpdateFactionRank(id, rank);
			SendServerMessage(playerid, "%s [ID: %i] adlý birliðin %i rütbesinin adýný deðiþtirdiniz. Yeni: %s.", Factions[id][fName], id, rank, name);
			return 1;
		}

		else
		{
			SendHelpMessage(playerid, "/afaction edit [ID] [spawn/color/name/ranks/joinrank/rankname/type/list/uniform/carfix] [value]");
			return 1;
		}
	}

	else if (CompareStrings(option, "list"))
	{
		new faction_type[][] = {"GOV", "Polis", "Medikal", "Yangýn Departmaný", "Hapishane", "Haber Birliði", "Çete", "Mafya", "Sivil", "Haber Birliði (Yönetim)", "State Bar"},
			faction_body[4096] = "ID\tÝsim [Kýsaltma]\tTip",
			count;

		for(new i = 1; i != MAX_FACTIONS; i++)
		{
		    if (!Factions[i][fON]) continue;
			format(faction_body, sizeof(faction_body), "%s\n%i\t%s [%s]\t%s", faction_body, i, Factions[i][fName], Factions[i][fShortName], faction_type[Factions[i][fType]-1]);
			count++;
		}

		if (!count)	return Dialog_Show(playerid, None, DIALOG_STYLE_LIST, "{FFFFFF}Birlik Listesi", "Birlik listesi boþ...", "Kapat", "");

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Birlik Listesi", faction_body, "Kapat", "");
		return 1;
	}

	else if (CompareStrings(option, "leader"))
	{
		new paramx[8], idx[64];

		if (sscanf(secoption, "s[8]S()[64]", paramx, idx))
		{
			SendHelpMessage(playerid, "/afaction leader [set / remove]");
			return 1;
		}

		if (CompareStrings(paramx, "set"))
		{
			new userid, faction;

			if (sscanf(idx, "iu", faction, userid)) 									return SendHelpMessage(playerid, "/afaction leader set [ID] [ID/Karakter Adý]");
			if (!IsPlayerLogged(userid))												return SendNotConnected(playerid);
			if (faction < 1 || faction > MAX_FACTIONS - 1 || !Factions[faction][fON])	return SendErrorMessage(playerid, "Birlik bulunamadý");

			RemovePlayerFaction(userid);

			PlayerInfo[userid][pFaction] = faction;
			SQL_SetInteger("users", "faction", PlayerInfo[userid][pFaction], PlayerInfo[userid][pID]);

			PlayerInfo[userid][pRank] = Factions[faction][fRanks];
			SQL_SetInteger("users", "rank", PlayerInfo[userid][pRank], PlayerInfo[userid][pID]);

			PlayerInfo[userid][pBadgeNumber] = randomEx(23456, 99999);
			SQL_SetInteger("users", "badgenumber", PlayerInfo[userid][pBadgeNumber], PlayerInfo[userid][pID]);

			SendServerMessage(playerid, "%s adlý oyuncuyu %s  [ID: %i] adlý birliðin lideri olarak tanýmladýnýz.", GetNameEx(userid), Factions[faction][fName], faction);
			SendServerMessage(userid, "%s adlý yönetici sizi %s [ID: %i] adlý birliðin yöneticisi olarak tanýmladý.", GetAccName(playerid), Factions[faction][fName], faction);
			SendAdmMessage("%s adlý yönetici %s adlý oyuncuyu %s [ID: %i] adlý birliðin lideri olarak tanýmladý.", GetAccName(playerid), GetNameEx(userid), Factions[faction][fName], faction);
			return 1;

		}

		else if (CompareStrings(paramx, "remove"))
		{
			new userid;

			if (sscanf(idx, "u", userid))	return SendHelpMessage(playerid, "/afaction leader remove [ID/Karakter Adý]");
			if (!IsPlayerLogged(userid))	return SendNotConnected(playerid);
			if (!isLeader(userid))			return SendErrorMessage(playerid, "Bu oyuncu lider deðil.");

			new faction = PlayerInfo[userid][pFaction];

			SendServerMessage(playerid, "%s adlý oyuncu %s [ID: %i] adlý birliðin liderliðinden çýkartýldý.", GetNameEx(userid), Factions[faction][fName], faction);
			SendServerMessage(userid, "%s adlý yönetici %s [ID: %i] adlý birliðin liderliðini sizden aldý.", GetAccName(playerid), Factions[faction][fName], faction);
			SendAdmMessage("%s adlý yönetici %s [ID: %i] adlý oyuncunun %s [ID: %i] birliðindeki liderliðini aldý.", GetAccName(playerid), GetNameEx(userid), Factions[faction][fName], faction);

			RemovePlayerFaction(userid);
			return 1;
		}

		else
		{
			SendHelpMessage(playerid, "/afaction leader [set / remove]");
			return 1;
		}
	}

	else
	{
		SendHelpMessage(playerid, "/afaction [create / remove / edit / list / leader]");
	}
	return 1;
}

CMD:editvehicle(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

	new option[48], secoption[128];

	if (sscanf(params, "s[48]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/editvehicle [kilitseviye / renk / alarmseviye / birlik / immobilizer / gps / radyo / plaka / park / sil]");

	else if (CompareStrings(option, "sil"))
	{
		new vehid;

		if (sscanf(secoption, "i", vehid))		 return SendHelpMessage(playerid, "/editvehicle sil [Araç ID]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

        new query[256];
	    mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", VehicleInfo[vehid][carID]);
		mysql_tquery(dbHandle, query);

		DestroyVehicleEx(vehid);
	}

	else if (CompareStrings(option, "birlik"))
	{
		new vehid, birlik;

		if (sscanf(secoption, "ii", vehid, birlik))		 return SendHelpMessage(playerid, "/editvehicle birlik [Araç ID] [birlik ID]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

        VehicleInfo[vehid][carFaction] = birlik;
		SendAdmMessage("%s adlý yönetici ID %d aracýn birliðini %d olarak belirledi.", GetAccName(playerid), vehid, birlik);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "alarmseviye"))
	{
		new vehid, level;

		if (sscanf(secoption, "ii", vehid, level))		 return SendHelpMessage(playerid, "/editvehicle alarmseviye [Araç ID] [alarm seviyesi]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

        VehicleInfo[vehid][carAlarm] = level;
		SendAdmMessage("%s adlý yönetici ID %d aracýn alarm seviyesini %d olarak belirledi.", GetAccName(playerid), vehid, level);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "kilitseviye"))
	{
		new vehid, level;

		if (sscanf(secoption, "ii", vehid, level))		 return SendHelpMessage(playerid, "/editvehicle kilitseviye [Araç ID] [kilit seviyesi]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");
		if (level < 0 || level > 5)              return SendErrorMessage(playerid, "Seviye 1 ile 5 arasýnda olmalý.");

        VehicleInfo[vehid][carLock] = level;
		SendAdmMessage("%s adlý yönetici ID %d aracýn kilit seviyesini %d olarak belirledi.", GetAccName(playerid), vehid, level);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "renk"))
	{
		new vehid, renk1, renk2;

		if (sscanf(secoption, "iii", vehid, renk1, renk2))		 return SendHelpMessage(playerid, "/editvehicle renk [Araç ID] [renk1] [renk2] (/renkler)");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

        VehicleInfo[vehid][carColor1] = renk1;
		VehicleInfo[vehid][carColor2] = renk2;
		ChangeVehicleColor(vehid, renk1, renk2);
		SendAdmMessage("%s adlý yönetici ID %d aracýn rengini %d - %d olarak belirledi.", GetAccName(playerid), vehid, renk1, renk2);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "immobilizer"))
	{
		new vehid, level;

		if (sscanf(secoption, "ii", vehid, level))		 return SendHelpMessage(playerid, "/editvehicle immobilizer [Araç ID] [immobilizer seviyesi]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");
		if (level < 0 || level > 5)              return SendErrorMessage(playerid, "Seviye 1 ile 5 arasýnda olmalý.");

        VehicleInfo[vehid][carImmob] = level;
		SendAdmMessage("%s adlý yönetici ID %d aracýn immobilizer seviyesini %d olarak belirledi.", GetAccName(playerid), vehid, level);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "gps"))
	{
		new vehid, level;

		if (sscanf(secoption, "ii", vehid, level))		 return SendHelpMessage(playerid, "/editvehicle gps [Araç ID] [0 yok | 1 var]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");
		if (level < 0 || level > 1)              return SendErrorMessage(playerid, "Seviye 0 veya 1 olmalýdýr.");

        VehicleInfo[vehid][carGps] = level;
		SendAdmMessage("%s adlý yönetici ID %d aracýn GPS durumunu %d olarak belirledi.", GetAccName(playerid), vehid, level);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "radyo"))
	{
		new vehid, level;

		if (sscanf(secoption, "ii", vehid, level))		 return SendHelpMessage(playerid, "/editvehicle radyo [Araç ID] [0 yok | 1 var]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");
		if (level < 0 || level > 1)              return SendErrorMessage(playerid, "Seviye 0 veya 1 olmalýdýr.");

        VehicleInfo[vehid][carRadio] = level;
		SendAdmMessage("%s adlý yönetici ID %d aracýn radyo durumunu %d olarak belirledi.", GetAccName(playerid), vehid, level);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "plaka"))
	{
		new vehid, plate;

		if (sscanf(secoption, "is[24]", vehid, plate))		 return SendHelpMessage(playerid, "/editvehicle plaka [Araç ID] [plaka]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

        format(VehicleInfo[vehid][carPlate], 24, "%s", plate);
		SendAdmMessage("%s adlý yönetici ID %d aracýn plakasýný %s olarak belirledi.", GetAccName(playerid), vehid, plate);
		Save_Car(vehid);
	}

	else if (CompareStrings(option, "tip"))
	{
		new vehid, type;

		if (sscanf(secoption, "is[24]", vehid, type))		 return SendHelpMessage(playerid, "/editvehicle tip [Araç ID] [tip(/avehicle types)]");
    	if (!IsValidVehicle(vehid))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
		if (type < 1 || type > 12)               return SendErrorMessage(playerid, "Tip 1 ile 12 arasýnda olmalýdýr. /avehicle types");

        VehicleInfo[vehid][carType] = type;
		SendAdmMessage("%s adlý yönetici ID %d aracýn tipini %d olarak belirledi.", GetAccName(playerid), vehid, type);
		Save_Car(vehid);
	}	

	else if (CompareStrings(option, "park"))
	{
		new vehid;

		if (sscanf(secoption, "i", vehid))		return SendHelpMessage(playerid, "/editvehicle park [Araç ID]");
		if (!IsValidVehicle(vehid))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
		if (VehicleInfo[vehid][carOwnerID])		return SendErrorMessage(playerid, "Sahibi olan araçlarý park edemezsiniz.");

		GetVehiclePos(vehid, VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carParkZ]);
		GetVehicleZAngle(vehid, VehicleInfo[vehid][carParkA]);

		SQL_SetFloat("cars", "x", VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "y", VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "z", VehicleInfo[vehid][carParkZ], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "fa", VehicleInfo[vehid][carParkA], VehicleInfo[vehid][carID]);

		new vehicle = CreateFactionVehicle(false, VehicleInfo[vehid][carModel], VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carParkZ], VehicleInfo[vehid][carParkA], VehicleInfo[vehid][carColor1],
		VehicleInfo[vehid][carColor2], VehicleInfo[vehid][carType], VehicleInfo[vehid][carFaction], VehicleInfo[vehid][carPlate], VehicleInfo[vehid][carVW], VehicleInfo[vehid][carInt], VehicleInfo[vehid][carID]);

		if (!vehicle) return SendErrorMessage(playerid, "Araç oluþturulamadý.");

		DestroyVehicleEx(vehid, 1);
		SendServerMessage(playerid, "Araç [ID: %i | NID: %i] park edildi ve belirtilen yerde doðacak", vehid, vehicle);
	}

	else return SendHelpMessage(playerid, "/editvehicle [kilitseviye / alarmseviye / immobilizer / gps / radyo / plaka / park / sil]");
	return 1;
}

CMD:giveitem(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

    new targetid, esya, esyaadi[28];

	if (sscanf(params, "ud", targetid, esya))
	{
		SendHelpMessage(playerid, "/giveitem [kiþi id] [eþya numarasý]");
		SendSyntaxMessage(playerid, "0 - boombox, 1 - sigara, 2 - çakmak, 3 - telsiz, 4 - maske");
		SendSyntaxMessage(playerid, "5 - benzin bidonu, 6 - zar, 7 - kalem, 8 - oyun kartý");
		return 1;
	}	

	if(!IsPlayerLogged(targetid)) return SendNotConnected(playerid);

	switch(esya)
	{
		case 0: esyaadi = "Boombox";
		case 1: esyaadi = "Sigara";
		case 2: esyaadi = "Çakmak";
		case 3: esyaadi = "Telsiz";
		case 4: esyaadi = "Maske";
		case 5: esyaadi = "Benzin Bidonu";
		case 6: esyaadi = "Zar";
		case 7: esyaadi = "Kalem";
		case 8: esyaadi = "Oyun Kartý";
	}

	switch(esya)
	{
		case 0: PlayerInfo[targetid][pBoombox] = 1;
		case 1: PlayerInfo[targetid][pSigara] = 1;
		case 2: PlayerInfo[targetid][pCakmak] = 1;
		case 3: PlayerInfo[targetid][pTelsiz] = 1;
		case 4: PlayerInfo[targetid][pMaske] = 1;
		case 5: PlayerInfo[targetid][pBenzinBidonu] = 1;
		case 6: PlayerInfo[targetid][pZar] = 1;
		case 7: PlayerInfo[targetid][pKalem] = 1;
		case 8: PlayerInfo[targetid][pOyunKarti] = 1;
	}

    SendServerMessage(playerid, "%s adlý kiþiye %s eþyasýný verdiniz.", GetNameEx(targetid), esyaadi);
	SendServerMessage(targetid, "%s adlý yönetici size %s eþyasýný verdi.", GetAccName(playerid), esyaadi);
	return 1;
}

alias:givevehicle("givecar", "/aracver");
CMD:givevehicle(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

    new model, ownerid, color1, color2, Float:x, Float:y, Float:z, Float:a;
	new lock = 0, alarm = 0, immobilizer = 0, insurance = 0, radio = 0, gps = 0, registered = 1, query[512];

	if (sscanf(params, "uddd", ownerid, model, color1, color2))
		return SendHelpMessage(playerid, "/givevehicle [ID / isim] [model] [renk 1] [renk 2]");


	if(!IsPlayerLogged(ownerid)) return SendNotConnected(playerid);
	if (model < 400 || model > 611) 													return SendErrorMessage(playerid, "Araç modelleri 400 ile 611 arasýnda olmalýdýr.");
	if (color1 > 255 || color1 < 0 || color2 > 255 || color2 < 0)						return SendErrorMessage(playerid, "Renk 0 ile 255 arasýnda olmalýdýr");
	if (model == 520 || model == 425 || model == 432 || model == 447 || model == 476)	return SendErrorMessage(playerid, "Belirtilen araç modeli sunucuda yasaklanmýþtýr.");

    GetPlayerPos(ownerid, x, y, z);
	GetPlayerFacingAngle(ownerid, a);

	SendServerMessage(ownerid, "%s adlý yönetici size %s model araç verdi. (/araclarim)", GetAccName(playerid), VehicleNames[model-400]);
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `cars` (date,model,color1,color2,x,y,z,fa,plate,owner,registered,alarm,locks,immob,insurances,radio,gps,health,fuel) VALUES ('%s',%i,%i,%i,%.1f,%.1f,%.1f,%.1f,'%s',%i,%i,%i,%i,%i,%i,%i,%i,%.1f,%.1f)",
	GetFullDate(), model, color1, color2, x, y, z, a, GetVehicleNumber(), PlayerInfo[ownerid][pID], registered, alarm, lock, immobilizer, insurance, radio, gps, GetVehicleMaxHealth(model), GetVehicleFuelCapacity(model)/2);
	mysql_tquery(dbHandle, query);

	return 1;
}

CMD:avehicle(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/avehicle [create / remove / park / types]");

	if (CompareStrings(option, "create"))
	{
		new model, type, faction, plate[24], color1, color2, Float:x, Float:y, Float:z, Float:a, vw, interior;

		if (sscanf(secoption, "iiiiI(0)S()[24]", model, type, color1, color2, faction, plate)) {
			return SendHelpMessage(playerid, "/avehicle create [model] [tür (0 - birlikler için)] [renk 1] [renk 2] {c7c7c7}[birlik] [plaka]");
		}
		
		if (model < 400 || model > 611) 													return SendErrorMessage(playerid, "Girilen model deðeri 400 ile 611 arasý olmalýdýr.");
		if (color1 > 255 || color1 < 0 || color2 > 255 || color2 < 0)						return SendErrorMessage(playerid, "Girilen renk deðeri 0 ve 255 arasý olmalýdýr.");
		if (model == 425 || model == 432 || model == 447 || model == 476)	return SendErrorMessage(playerid, "Belirtilen model sunucuda yasak.");

		if (isempty(plate)) format(plate, 24, "%s", GetVehicleNumber());

		GetXYInFrontOfPlayer(playerid, x, y, z, 5.0);
		GetPlayerFacingAngle(playerid, a);
		vw = GetWorld(playerid);
		interior = GetInterior(playerid);

		if (!CreateFactionVehicle(true, model, x, y, z, a, color1, color2, type, faction, plate, vw, interior)) return SendErrorMessage(playerid, "Araç oluþturulamadý.");
		SendAdmMessageToPlayer(playerid, "Araç oluþturuldu. [Model %d - Plaka %s - Tür %d - Birlik %d - VW %d - Interior %d]", model, plate, type, faction, vw, interior);
	}

	else if (CompareStrings(option, "remove"))
	{
		new vehid;

		if (sscanf(secoption, "i", vehid))		 return SendHelpMessage(playerid, "/avehicle remove [Araç ID]");
    	if (!IsValidVehicle(vehid))				 return SendErrorMessage(playerid, "Araç bulunamadý.");

	    if (VehicleInfo[vehid][carAdmin] == 0)
		{
        	new query[256];
	    	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", VehicleInfo[vehid][carID]);
			mysql_tquery(dbHandle, query);
		}

		DestroyVehicleEx(vehid);
	}

	else if (CompareStrings(option, "park"))
	{
		new vehid;

		if (sscanf(secoption, "i", vehid))		return SendHelpMessage(playerid, "/avehicle park [Araç ID]");
		if (!IsValidVehicle(vehid))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
		//if (VehicleInfo[vehid][carOwnerID])		return SendErrorMessage(playerid, "Belirtilen araç park edilemez.");

		GetVehiclePos(vehid, VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carParkZ]);
		GetVehicleZAngle(vehid, VehicleInfo[vehid][carParkA]);

		SQL_SetFloat("cars", "x", VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "y", VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "z", VehicleInfo[vehid][carParkZ], VehicleInfo[vehid][carID]);
		SQL_SetFloat("cars", "fa", VehicleInfo[vehid][carParkA], VehicleInfo[vehid][carID]);

		new vehicle = CreateFactionVehicle(false, VehicleInfo[vehid][carModel], VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carParkZ], VehicleInfo[vehid][carParkA], VehicleInfo[vehid][carColor1],
		VehicleInfo[vehid][carColor2], VehicleInfo[vehid][carType], VehicleInfo[vehid][carFaction], VehicleInfo[vehid][carPlate], VehicleInfo[vehid][carVW], VehicleInfo[vehid][carInt], VehicleInfo[vehid][carID]);

		if (!vehicle) return SendErrorMessage(playerid, "Araç oluþturulamadý.");

		DestroyVehicleEx(vehid, 1);
		SendServerMessage(playerid, "Araç [ID: %i | NID: %i] park edildi ve belirtilen yerde doðacak", vehid, vehicle);
	}

	else if (CompareStrings(option, "types"))
	{
		new dialog_header[64] = "{FFFFFF}Tip\t{FFFFFF}Ýsim\n", dialog_body[256];
		dialog_body[0] = EOS;

		format(dialog_body, sizeof(dialog_body), "%s0\tUsual\n1\tDMV car\n2\tDMV helicopter\n3\tWith siren\n4\tDMV taxi\n5\tRent\n6\tTaxi\n7\tPizzaboy\n8\tTruckers\n9\tMechanics", dialog_header);
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Araç Tipi", dialog_body, "Kapat", "");
	}

	else return SendHelpMessage(playerid, "/avehicle [create / remove / park / types]");
	return 1;
}

alias:apayphone("app");
CMD:apayphone(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/apayphone [create / remove / edit / goto]");

	if (CompareStrings(option, "create"))
	{
		new number, type;
		if (sscanf(secoption,"iI(0)", number, type)) return SendHelpMessage(playerid, "/apayphone create [numara] {c7c7c7}[model id]");

		if (!type) type = 1216;

		new Float:x, Float:y, Float:z, Float:a, vw, interior;
		GetXYInFrontOfPlayer(playerid, x, y, z, 2.0);
		GetPlayerFacingAngle(playerid, a);
		vw = GetWorld(playerid);
		interior = GetInterior(playerid);

		new id;
		if ((id = CreatePayphone(true, type, number, x, y, z, 0.0, 0.0, 0.0, vw, interior)) == -1) return SendErrorMessage(playerid, "Maksimum ankesörlü telefon sayýsýna ulaþýldý.");

		SetPVarInt(playerid, #edit_pp, id + 1);
		EditDynamicObject(playerid, PayphoneInfo[id][phObj]);

		SendServerMessage(playerid, "Ankesörlü telefon oluþturuldu: %i [ID: %i].", number, id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if (sscanf(secoption, "i", id))									return SendHelpMessage(playerid, "/apayphone remove [ID]");
		if (id < 0 || id >= MAX_PAYPHONES || !PayphoneInfo[id][phID])	return SendErrorMessage(playerid, "Ankesörlü telefon bulunamadý.");

		if (IsValidDynamicObject(PayphoneInfo[id][phObj])) 			DestroyDynamicObject(PayphoneInfo[id][phObj]);
		if (IsValidDynamic3DTextLabel(PayphoneInfo[id][phLabel])) 	DestroyDynamic3DTextLabel(PayphoneInfo[id][phLabel]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `payphones` WHERE `id` = %i", PayphoneInfo[id][phID]);
		mysql_tquery(dbHandle, query);

		PayphoneInfo[id][phID] = 0;
		SendAdmMessageToPlayer(playerid, "Belirtilen ankesörlü telefon kaldýrýldý. [ID: %i].", id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id;

		if (sscanf(secoption, "d", id))								 return SendHelpMessage(playerid, "/apayphone edit [ID]");
		if (id < 0 || id > MAX_PAYPHONES || !PayphoneInfo[id][phID]) return SendErrorMessage(playerid, "Ankesörlü telefon bulunamadý.");
		if (Payphone_Nearest(playerid) != id)						 return SendErrorMessage(playerid, "Ankesörlü telefonun yanýnda olmalýsýn.");

		SetPVarInt(playerid, #edit_pp, id + 1);
		EditDynamicObject(playerid, PayphoneInfo[id][phObj]);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))								return SendHelpMessage(playerid, "/apayphone goto [ID]");
		if (id < 0 || id > MAX_PAYPHONES || !PayphoneInfo[id][phID])	return SendErrorMessage(playerid, "Ankesörlü telefon bulunamadý.");

		SetPlayerPosEx(playerid, PayphoneInfo[id][phX], PayphoneInfo[id][phY], PayphoneInfo[id][phZ]);
		SetWorld(playerid, PayphoneInfo[id][phVW]);
		SetInterior(playerid, PayphoneInfo[id][phInt]);
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/apayphone [create / remove / edit / goto]");
	}
	return 1;
}

alias:aparkmeter("aparkm");
CMD:aparkmeter(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/aparkm [create / remove / edit / goto]");

	if (CompareStrings(option, "create"))
	{
		if (ParkMeter_Nearest(playerid) != -1) return SendErrorMessage(playerid, "Herhangi bir parkmetreye çok yakýnsýnýz.");

		new Float:x, Float:y, Float:z, Float:a;
		GetXYInFrontOfPlayer(playerid, x, y, z, 2.0);
		GetPlayerFacingAngle(playerid, a);

    	new id;
		if ((id = InsertParkMeters(playerid, x, y, z, a)) == -1) return SendErrorMessage(playerid, "Sýnýra ulaþýldýðýndan ötürü ("#MAX_METERS") yeni parkmetre ekleyemezsiniz.");

		SetPVarInt(playerid, #edit_pm, id + 1);
		EditDynamicObject(playerid, pMeter[id][parkObject]);

		SendAdmMessageToPlayer(playerid, "Parkmetre oluþturuldu [ID: %i].", id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if (sscanf(secoption, "i", id))							return SendHelpMessage(playerid, "/aparkm remove [ID Parking meter]");
		if (id < 0 || !pMeter[id][parkID] || id >= MAX_METERS)	return SendErrorMessage(playerid, "Parkmetre bulunamadý.");

		SendAdmMessageToPlayer(playerid, "Belirtilen parkmetre baþarýlý þekilde kaldýrýldý [ID:%d].", id);
    	EraseParkMeter(id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id;

		if (sscanf(secoption, "d", id))							return SendHelpMessage(playerid, "/aparkm edit [ID]");
		if (id < 0 || !pMeter[id][parkID] || id >= MAX_METERS)	return SendErrorMessage(playerid, "Parkmetre bulunamadý.");
		if (ParkMeter_Nearest(playerid) != id)					return SendErrorMessage(playerid, "Parkmetreye yakýn olmalýsýnýz.");

		SetPVarInt(playerid, #edit_pm, id + 1);
		EditDynamicObject(playerid, pMeter[id][parkObject]);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))							return SendHelpMessage(playerid, "/aparkm goto [ID]");
		if (id < 0 || !pMeter[id][parkID] || id >= MAX_METERS)	return SendErrorMessage(playerid, "Parkmetre bulunamadý.");

		SetPlayerPosEx(playerid, pMeter[id][parkX], pMeter[id][parkY], pMeter[id][parkZ]);
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/aparkm [create / remove / edit / goto]");
	}
	return 1;
}

CMD:acceptname(playerid, params[])
{
	new userid;

    if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/acceptname [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!strlen(pTemp[userid][pChangeNick]))		return SendErrorMessage(playerid, "Belirtilen oyuncu isim deðiþikliði için talepte bulunmamýþ.");

    new query[256];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e'", pTemp[userid][pChangeNick]);
	mysql_tquery(dbHandle, query, "OnChangeName", "iis", playerid, userid, pTemp[userid][pChangeNick]);
	return 1;
}

CMD:auver(playerid, params[])
{
	new hedefid, tip, kalite, gram;
	if(sscanf(params, "uddd", hedefid, tip, gram, kalite))
	{
		SendHelpMessage(playerid, "/auver [oyuncu isim yada ID] [uyuþturucu (sayýlarý kullanýn)] [gram] [kalite]");
		SendServerMessage(playerid, "UYUÞTURUCULAR: [LSD 0] - [Kokain 1] - [Eroin 2] - [Amfetamin 3] - [Metamfetamin 4]");
		SendServerMessage(playerid, "UYUÞTURUCULAR: [Ekstazi 5] - [PCP 6] - [Ketamin 7] - [Marijuana 8] - [Haþhaþ 9] - [Aþk Suyu 10]");
		return 1;
	}
	if(!(0 <= tip <= 10)) return SendErrorMessage(playerid, "Uyuþturucu tipi 0 ve 10 arasýnda olmalýdýr.");
	if(!(0 <= kalite <= 100)) return SendErrorMessage(playerid, "Uyuþturucu kalitesi 0 ve 100 arasýnda olmalýdýr.");
	if(!IsPlayerConnected(hedefid) || !pTemp[hedefid][pLogged]) return SendErrorMessage(playerid, "Geçersiz oyuncu.");

	if(OyuncuUyusturucuSayi(PlayerInfo[hedefid][pID]) >= MAX_OYUNCU_UYUSTURUCU_SAYI)
		return SendErrorMessage(playerid, "Bu oyuncunun boþ slotu yok. Uyuþturucu düzenlemek istersen /auyusturucu komutunu kullan.");
	
	OyuncuUyusturucuVer(PlayerInfo[hedefid][pID], tip, gram, kalite);
	SendServerMessage(hedefid, "%s tarafýndan %s türünde %d gram ve %d kalite uyuþturucu aldýn.", GetAccName(playerid), UyusTipleri[tip][Ad], gram, kalite);
	SendServerMessage(playerid, "%s adlý oyuncuya %s türünde %d gram ve %d kalite uyuþturucu verdin.", GetNameEx(hedefid), UyusTipleri[tip][Ad], gram, kalite);
	return 1;
}

CMD:auyusturucu(playerid, params[])
{
	new sqlid;
	if(!isnull(params) && !sscanf(params, "u", sqlid)) {
		if(!IsPlayerConnected(sqlid)) return SendErrorMessage(playerid, "Oyuncu bulunamadý.");
		if(!pTemp[sqlid][pLogged]) return pc_cmd_auyusturucu(playerid, Oyuncu_Isim(sqlid));
		sqlid = PlayerInfo[sqlid][pID];
	}
	else if(!isnull(params) && !isNumeric(params)) {
		mysql_format(dbHandle, queryx, sizeof queryx, "SELECT id FROM users WHERE name = '%s'", params);
		new Cache:char_check = mysql_query(dbHandle, queryx);

		if(!cache_num_rows()) {
			cache_delete(char_check);
			return SendErrorMessage(playerid, "Veri tabanýnda '%s' isminde bir karakter bulunamadý.", params);
		}

		cache_get_value_int(0, "id", sqlid);
	}
	else return SendHelpMessage(playerid, "/auyusturucu [Oyuncu isim/ID]");

	OyuncuUyusturucuGoster(playerid, sqlid, 1);
	return 1;
}

CMD:meslekdurum(playerid)
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);
	MeslekSistemleri = !MeslekSistemleri;
	SendServerMessage(playerid, "Meslek sistemleri %s.", !MeslekSistemleri ? "pasife çekildi" : "aktif edildi");

	new mes[128];
	format(mes, sizeof(mes), "[Duyuru] Meslek sistemleri %s.", !MeslekSistemleri ? "pasife çekildi" : "aktif edildi");
	SCMALL(0xF97804FF,mes);	
	return 1;
}

CMD:alock(playerid, params[])
{
    if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	for(new i; i != MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0 || (0 == IsPlayerInsideHouse(playerid, i) && 0 == IsPlayerOutsideHouse(playerid, i))) continue;

        HouseInfo[i][hLocked] = !HouseInfo[i][hLocked];
		SQL_SetInteger("houses", "locked", HouseInfo[i][hLocked], HouseInfo[i][hID]);

        if (HouseInfo[i][hLocked] == 0)
        {
			SendAdmMessage("%s adlý yönetici evin kilidini açtý [ID: %i].", GetAccName(playerid), i);
			GameTextForPlayer(playerid, "~w~KAPI ~g~KILIDI ACILDI", 5000, 6);
			DestroyDynamicPickup(HouseInfo[i][hPickup]);
			CreateDynamicPickup(1273, 1, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ], HouseInfo[i][hPosVW], HouseInfo[i][hPosInt], -1, 100.0);

        }
        else
        {
			SendAdmMessage("%s adý yönetici evi kilitledi [ID: %i].", GetAccName(playerid), i);
			GameTextForPlayer(playerid, "~w~KAPI ~r~KILITLENDI", 5000, 6);
			DestroyDynamicPickup(HouseInfo[i][hPickup]);
			CreateDynamicPickup(19522, 1, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ], HouseInfo[i][hPosVW], HouseInfo[i][hPosInt], -1, 100.0);
        }
        return 1;
	}

	for(new i = 0; i != MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0 || (0 == IsPlayerBizOutside(playerid, i) && 0 == IsPlayerBizInside(playerid, i)))	continue;

        BizInfo[i][bizLocked] = !BizInfo[i][bizLocked];
		SQL_SetInteger("business", "locked", BizInfo[i][bizLocked], BizInfo[i][bizID]);

		if (BizInfo[i][bizLocked] == 0)
		{
			SendAdmMessage("%s adlý yönetici iþletmenin kilidini açtý [ID: %i].", GetAccName(playerid), i);
			GameTextForPlayer(playerid, "~w~KAPI ~g~KILIDI ACILDI", 5000, 6);
		}
		else
		{
			SendAdmMessage("%s adlý yönetici iþletmenin kilidini açtý [ID: %i].", GetAccName(playerid), i);
			GameTextForPlayer(playerid, "~w~KAPI ~r~KILITLENDI", 5000, 6);
		}
		return 1;
	}

	for(new i = 0; i != MAX_ENTRANCE; i++)
	{
	    if (EntranceInfo[i][eFaction] == 0 || EntranceInfo[i][entranceOn] == 0 || (IsPlayerEntranceOutside(playerid, i) == 0 && IsPlayerEntranceInside(playerid, i) == 0)) continue;

        EntranceInfo[i][eLocked] = !EntranceInfo[i][eLocked];
        PlaySound(playerid, 1145);

        if (EntranceInfo[i][eLocked])
        {
			SendAdmMessage("%s adlý yönetici birlik kapýsýný kilitledi [ID: %i].", GetAccName(playerid), i);
            GameTextForPlayer(playerid, "~w~KAPI ~g~KILIDI ACILDI", 5000, 6);
		}
		else
		{
			SendAdmMessage("%s adlý yönetici birlik kapýsýnýn kilidini açtý [ID: %i].", GetAccName(playerid), i);
		    GameTextForPlayer(playerid, "~w~KAPI ~r~KILITLENDI", 5000, 6);
		}
		break;
	}

	for(new i = 1; i < MAX_VEHICLES; i++)
	{
		if (!IsValidVehicle(i)) continue;
		new vehicle = GetNearVehicle(playerid, 5.0, i), mes[128];
        
		if(!vehicle) return SendErrorMessage(playerid, "Herhangi bir aracýn yanýnda deðilsiniz.");

		if (VehicleInfo[vehicle][carLocked]) format(mes, sizeof(mes), "KILIT ~g~ACILDI");
		else format(mes, sizeof(mes), "ARAC ~r~KILITLENDI");
		GameTextForPlayer(playerid, mes, 2500, 4);

		ToggleVehicleLock(vehicle, (VehicleInfo[vehicle][carLocked]) ? (false): (true));	
		return 1;	
	}	
	SendErrorMessage(playerid, "Evinizin/iþ yerinizin/giriþinizin yakýnýnda olmalýsýnýz.");
	return 1;
}

CMD:ahouse(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/ahouse [create / remove / edit / sell / goto / backdoor]");
		return 1;
	}

	new houseid,
		level,
		price,
		clases,
		classes_name[3][10] = {"Küçük", "Orta", "Büyük"};

	if (CompareStrings(option, "create"))
	{
		new Float:x, Float:y, Float:z, Float:newZ;

		if (sscanf(secoption, "iiF(0.0)", clases, price, newZ)) 	return SendHelpMessage(playerid, "/ahouse create [tip (1 - deneme | 2 - küçük | 3 - orta | 4 - büyük] [fiyat]");
		if (clases < 1 || clases > 4)				return SendErrorMessage(playerid, "Ev tipi 1 ile 4 arasýnda olmalýdýr.");
		//if (price < 1 || price > 2000000)			return SendErrorMessage(playerid, "Ev fiyatý $1 ile $2000000 arasýnda olmalýdýr.");
		if ((houseid = GetNextHouseID()) == -1)		return SendErrorMessage(playerid, "Maksimum ev miktarýna ulaþtýnýz.");

		new vw, interior;

		if (clases > 2) 	level = 1;
		else 			level = 0;

		GetPlayerPos(playerid, x, y, z);
		vw = GetWorld(playerid);
		interior = GetInterior(playerid);

		if (vw != 0 || interior != 0) HouseInfo[houseid][hApart] = GetNearApartmentInside(playerid);
		else 						 HouseInfo[houseid][hApart] = 0;

		HouseInfo[houseid][hPosX] = x;
		HouseInfo[houseid][hPosY] = y;
		HouseInfo[houseid][hPosZ] = z+newZ;
		HouseInfo[houseid][hPosVW] = vw;
		HouseInfo[houseid][hPosInt] = interior;

		HouseInfo[houseid][hExitX] =
		HouseInfo[houseid][hExitY] =
		HouseInfo[houseid][hExitZ] = 0.0;
		HouseInfo[houseid][hExitVW] = 5000 + houseid;

		if (clases == 1) 		SetHouseInterior(houseid, 0);
		else if (clases == 2)	SetHouseInteriorEx(houseid, 0);
		else if (clases == 3)	SetHouseInteriorEx(houseid, 1);
		else if (clases == 4)	SetHouseInteriorEx(houseid, 2);

		switch(clases)
		{
			case 1: clases = 0;
			case 2: clases = 0;
			case 3: clases = 1;
			case 4: clases = 2;
		}

		HouseInfo[houseid][hClass] = clases;

		for(new i = 0; i < 2; i++) {
			HouseInfo[houseid][hExtX][i] =
			HouseInfo[houseid][hExtY][i] =
			HouseInfo[houseid][hExtZ][i] = 0.0;
			HouseInfo[houseid][hExtVW][i] =
			HouseInfo[houseid][hExtInt][i] = 0;
		}

		HouseInfo[houseid][hCheckPosX] =
		HouseInfo[houseid][hCheckPosY] =
		HouseInfo[houseid][hCheckPosZ] = 0.0;
		HouseInfo[houseid][hLevelbuy] = level;
		HouseInfo[houseid][hPrice] = price;
		HouseInfo[houseid][hLocked] = 1;
		HouseInfo[houseid][hFurnitureRadius] = 7.0;
		HouseInfo[houseid][hOwnerID] =
		HouseInfo[houseid][hCash] =
		HouseInfo[houseid][hRadio] =
		HouseInfo[houseid][hHeal] =
		HouseInfo[houseid][hHealAmount] =
		HouseInfo[houseid][hCupboard] = 0;

		new door[11];
		HouseInfo[houseid][hPickup] = CreateDynamicPickup(19471, 1, x, y, z, HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);

		switch(HouseInfo[houseid][hDoor])
		{
			case 0: door = "Normal";
			case 1: door = "Ahþap";
			case 2: door = "Demir";
		}
		AddHouseToFile(houseid, HouseInfo[houseid][hClass], level, price, HouseInfo[houseid][hApart], x, y, z+newZ, 5000 + houseid, vw, interior);
		SendAdmMessageToPlayer(playerid, "Ev oluþturuldu [ID: %i | Level: %i | Fiyat: %i | Tip: %s [%i] ].", houseid, level, price, classes_name[clases], clases);
		return 1;
	}
	else if (CompareStrings(option, "remove"))
	{
		if (sscanf(secoption, "i", houseid))
			return SendHelpMessage(playerid, "/ahouse remove [ID]");

		if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID])
			return SendErrorMessage(playerid, "Ev bulunamadý.");

		if(IsValidDynamicPickup(HouseInfo[houseid][hPickup])) DestroyDynamicPickup(HouseInfo[houseid][hPickup]);

		if (IsValidDynamic3DTextLabel(HouseInfo[houseid][hLabelDDoor]))
		{
			DestroyDynamic3DTextLabel(HouseInfo[houseid][hLabelDDoor]);
			HouseInfo[houseid][hLabelDDoor] = Text3D:INVALID_3DTEXT_ID;
		}

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `houses` WHERE `id` = %i", HouseInfo[houseid][hID]);
		mysql_tquery(dbHandle, query);

		HouseInfo[houseid][hID] = 0;
		SendAdmMessageToPlayer(playerid, "Ev [ID: %i] silindi.", houseid);
	}

	else if (CompareStrings(option, "edit"))
	{
		new parameters[12], arg[12];

		if (sscanf(secoption,"is[12]S()[12]", houseid, parameters, arg))
		{
			SendHelpMessage(playerid, "/ahouse edit [ID] [ayar] [deðer]");
			SendSyntaxMessage(playerid, "price / level / type / radius / int / exterior / interior / extenter / extexit");
			return 1;
		}

		if (houseid < 0 || houseid > MAX_HOUSES || !HouseInfo[houseid][hID]) return SendErrorMessage(playerid, "Ev bulunamadý.");

		if (CompareStrings(parameters, "price"))
		{
			if (sscanf(arg, "i", price))		return SendHelpMessage(playerid, "/ahouse edit [ID] price [fiyat]");
			//if (price < 1 || price > 2000000)	return SendErrorMessage(playerid, "Ev fiyatý $1 ile $2000000 arasýnda olmalýdýr.");

			HouseInfo[houseid][hPrice] = price;
			SQL_SetInteger("houses", "price", HouseInfo[houseid][hPrice], HouseInfo[houseid][hID]);
			SendAdmMessageToPlayer(playerid, "Belirtilen evin [ID: %i] fiyatý deðiþtirildi: $%i.", houseid, HouseInfo[houseid][hPrice]);
		}

		else if (CompareStrings(parameters, "level"))
		{
			if (sscanf(arg, "i", level))	return SendHelpMessage(playerid, "/ahouse edit [ID] level [level]");
			if (level < 0 || level > 35)	return SendErrorMessage(playerid, "Ev seviyesi 0 ile 35 arasýnda olmalýdýr.");

			HouseInfo[houseid][hLevelbuy] = level;
			SQL_SetInteger("houses", "levelbuy", HouseInfo[houseid][hLevelbuy], HouseInfo[houseid][hID]);
			SendAdmMessageToPlayer(playerid, "Belirlenen evin [ID: %i] seviyesi deðiþtirildi: %i.", houseid, HouseInfo[houseid][hLevelbuy]);
		}

		else if (CompareStrings(parameters, "type"))
		{
			if (sscanf(arg, "i", clases))	return SendHelpMessage(playerid, "/ahouse edit [ID] type [tip]");
			if (clases < 1 || clases > 3)	return SendErrorMessage(playerid, "Tip [1 - küçük | 2 - orta | 3 - büyük.");

			HouseInfo[houseid][hClass] = clases - 1;
			SQL_SetInteger("houses", "class", HouseInfo[houseid][hClass], HouseInfo[houseid][hID]);
			SendAdmMessageToPlayer(playerid, "Belirlenen evin [ID: %i] tipi deðiþtirildi: %s [%i].", houseid, classes_name[clases-1], HouseInfo[houseid][hClass]);
		}

		else if (CompareStrings(parameters, "radius"))
		{
			new Float:radius;

			if (sscanf(arg, "f", radius))		return SendHelpMessage(playerid, "/ahouse edit [ID] radius [obje yerleþtirmek için yarýçap].");
			if (radius < 0.0 || radius > 30.0)	return SendErrorMessage(playerid, "Yarýçap 0.0 ile 30.0 arasýnda olmalýdýr.");

			HouseInfo[houseid][hFurnitureRadius] = radius;
			SQL_SetFloat("houses", "furniture_radius", HouseInfo[houseid][hFurnitureRadius], HouseInfo[houseid][hID]);
			SendAdmMessageToPlayer(playerid, "Belirlenen evin [ID: %i] radiusu deðiþtirildi: %.2f", houseid, HouseInfo[houseid][hFurnitureRadius]);
		}

		else if (CompareStrings(parameters, "int"))
		{
			new string[2048];

			for(new i = 0; i < MAX_INTERIORS; i++)
			{
				if (!AdminTeles[i][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[i][telesType]) continue;
				format(string, sizeof(string), "%s\n<%i> {66FF66}%s", string, i, AdminTeles[i][telesMapName]);
			}

			if (isempty(string)) return SendErrorMessage(playerid, "Bu sýnýftaki evler için interior bulunamadý");

			SetPVarInt(playerid, "house_change", houseid);
			Dialog_Show(playerid, ChangeHouseInterior, DIALOG_STYLE_LIST, "{FFFFFF}Ev interioru", string, "Seç", "Ýptal");
		}

		else if (CompareStrings(parameters, "exterior"))
		{
			if (IsValidDynamicPickup(HouseInfo[houseid][hPickup])) DestroyDynamicPickup(HouseInfo[houseid][hPickup]);

			GetPlayerPos(playerid, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]);
			HouseInfo[houseid][hPosVW] = GetWorld(playerid);
			HouseInfo[houseid][hPosInt] = GetInterior(playerid);

			SQL_SetFloat("houses", "posx", HouseInfo[houseid][hPosX], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "posy", HouseInfo[houseid][hPosY], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "posz", HouseInfo[houseid][hPosZ], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "posint", HouseInfo[houseid][hPosInt], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "posvw", HouseInfo[houseid][hPosVW], HouseInfo[houseid][hID]);

			if(!HouseInfo[houseid][hOwnerID]) {
				HouseInfo[houseid][hPickup] = CreateDynamicPickup(19471, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			}
			else if (HouseInfo[houseid][hLocked] == 1)
			{
				HouseInfo[houseid][hPickup] = CreateDynamicPickup(19522, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			}
			else if (HouseInfo[houseid][hLocked] == 0)
			{
				HouseInfo[houseid][hPickup] = CreateDynamicPickup(1273, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			}
			SendAdmMessageToPlayer(playerid, "Evin giriþini düzenlediniz [ID: %i].", houseid);
		}

		else if (CompareStrings(parameters, "interior"))
		{
			GetPlayerPos(playerid, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY], HouseInfo[houseid][hExitZ]);
			HouseInfo[houseid][hExitInt] = GetInterior(playerid);

			SQL_SetFloat("houses", "exitx", HouseInfo[houseid][hExitX], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "exity", HouseInfo[houseid][hExitY], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "exitz", HouseInfo[houseid][hExitZ], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "exitint", HouseInfo[houseid][hExitInt], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "exitvw", HouseInfo[houseid][hExitVW], HouseInfo[houseid][hID]);

			SendAdmMessageToPlayer(playerid, "Evin çýkýþýný düzenlediniz [ID: %i].", houseid);
		}

		else if (CompareStrings(parameters, "extenter"))
		{
			if (IsValidDynamicPickup(HouseInfo[houseid][hExtPickup])) DestroyDynamicPickup(HouseInfo[houseid][hExtPickup]);

			GetPlayerPos(playerid, HouseInfo[houseid][hExtX][0], HouseInfo[houseid][hExtY][0], HouseInfo[houseid][hExtZ][0]);
			HouseInfo[houseid][hExtVW][0] = GetWorld(playerid);
			HouseInfo[houseid][hExtInt][0] = GetInterior(playerid);

			SQL_SetFloat("houses", "ext_ENposX", HouseInfo[houseid][hExtX][0], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "ext_ENposY", HouseInfo[houseid][hExtY][0], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "ext_ENposZ", HouseInfo[houseid][hExtZ][0], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "ext_ENint", HouseInfo[houseid][hExtInt][0], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "ext_ENvw", HouseInfo[houseid][hExtVW][0], HouseInfo[houseid][hID]);

			HouseInfo[houseid][hExtPickup] = CreateDynamicPickup(19523, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			SendAdmMessageToPlayer(playerid, "Evin ek giriþini taþýdýnýz [ID: %i].", houseid);
		}

		else if (CompareStrings(parameters, "extexit"))
		{
			GetPlayerPos(playerid, HouseInfo[houseid][hExtX][1], HouseInfo[houseid][hExtY][1], HouseInfo[houseid][hExtZ][1]);
			HouseInfo[houseid][hExtInt][1] = GetInterior(playerid);

			SQL_SetFloat("houses", "ext_EXposX", HouseInfo[houseid][hExtX][1], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "ext_EXposY", HouseInfo[houseid][hExtY][1], HouseInfo[houseid][hID]);
			SQL_SetFloat("houses", "ext_EXposZ", HouseInfo[houseid][hExtZ][1], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "ext_EXint", HouseInfo[houseid][hExtInt][1], HouseInfo[houseid][hID]);
			SQL_SetInteger("houses", "ext_EXvw", HouseInfo[houseid][hExtVW][1], HouseInfo[houseid][hID]);

			SendAdmMessageToPlayer(playerid, "Evin ek çýkýþýný taþýdýnýz. [ID: %i].", houseid);
		}

		else
		{
			SendHelpMessage(playerid, "/ahouse edit [ID] [ayar] [deðer]");
			SendSyntaxMessage(playerid, "price / level / type / radius / int / enter / exit / extenter / extexit");
			return 1;
		}
	}

	else if (CompareStrings(option, "sell"))
	{
		if (sscanf(secoption, "i", houseid)) 									 return SendHelpMessage(playerid, "/ahouse sell [ID]");
		if (houseid < 0 || houseid > MAX_HOUSES - 1 || !HouseInfo[houseid][hID]) return SendErrorMessage(playerid, "Belirtilen ev bulunamadý");
		if (!HouseInfo[houseid][hOwnerID])										 return SendErrorMessage(playerid, "Bu ev satýþa çýkartýlamaz.");

		new userid = GetIDByID(HouseInfo[houseid][hOwnerID]);

		if (IsPlayerLogged(userid)) {
			GiveCash(playerid, HouseInfo[houseid][hPrice]/2/* + GetFurniturePrice(0, houseid)*/);
			if (HouseInfo[houseid][hCash] > 0) GiveCash(playerid, HouseInfo[houseid][hCash]);

			SendAdmMessageToPlayer(userid, "%s adlý yönetici evinizi sattý. Geri ödenen: $%i Ev fiyatý: $%i.", GetAccName(playerid), HouseInfo[houseid][hPrice]/2/* + GetFurniturePrice(0, houseid)*/, HouseInfo[houseid][hCash]);
		} else {
			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT cash FROM `users` WHERE id=%i LIMIT 1", HouseInfo[houseid][hOwnerID]);
			new Cache:cache = mysql_query(dbHandle, query),
				money;

            cache_get_value_int(0, "cash", money);
			money += HouseInfo[houseid][hPrice]/2/*+ GetFurniturePrice(0, houseid)*/ + HouseInfo[houseid][hCash];

			mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `cash`=%i WHERE id=%i LIMIT 1", money, HouseInfo[houseid][hOwnerID]);
			mysql_query(dbHandle, query);
			cache_delete(cache);
			cache = MYSQL_INVALID_CACHE;
		}

		Sell_House(houseid);
		SendAdmMessageToPlayer(playerid, "Evi [%i] satýþa çýkardýnýz.", houseid);
	}

	else if (CompareStrings(option, "goto"))
	{
		if (!PlayerInfo[playerid][pEbc] && !CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

		if (sscanf(secoption, "i", houseid)) 									 return SendHelpMessage(playerid, "/ahouse goto [ID]");
		if (houseid < 0 || houseid > MAX_HOUSES - 1 || !HouseInfo[houseid][hID]) return SendErrorMessage(playerid, "Belirtilen ev bulunamadý");

		SetPlayerPosEx(playerid, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]);
		SetInterior(playerid, HouseInfo[houseid][hPosInt]);
		SetWorld(playerid, HouseInfo[houseid][hPosVW]);
		SendSpecialMessage(playerid, "Eve ýþýnlandýnýz [ID: %i].", houseid);
	}

	else if (CompareStrings(option, "backdoor")) {
		if (sscanf(secoption, "i", houseid))									 return SendHelpMessage(playerid, "/ahouse backdoor [ID]");
		if (houseid < 0 || houseid > MAX_HOUSES - 1 || !HouseInfo[houseid][hID]) return SendErrorMessage(playerid, "Belirtilen ev bulunamadý.");
		if (HouseInfo[houseid][hApart])											 return SendErrorMessage(playerid, "Bu ev için arka giriþ/çýkýþ oluþturulamýyor.");

		if (pTemp[playerid][pHouseEntered] == houseid) {
			new Float: posX, Float: posY, Float: posZ;
			GetPlayerPos(playerid, posX, posY, posZ);

			HouseInfo[houseid][hExtX][0] = posX;
			HouseInfo[houseid][hExtY][0] = posY;
			HouseInfo[houseid][hExtZ][0] = posZ;

			Save_House(houseid);

			HouseInfo[houseid][hExtVW][0] = GetPlayerVirtualWorld(playerid);
			HouseInfo[houseid][hExtInt][0] = GetPlayerInterior(playerid);

			return SendAdmMessageToPlayer(playerid, "Belirtilen ev [ID: %i] için ek bir çýkýþ ayarladýnýz.", houseid);
		} else {
			new garageid = GetNearInsideGarage(playerid);
			if (garageid != -1) {
				if (HouseInfo[houseid][hID] == GarageInfo[garageid][garageHouse]) {
					if (IsValidDynamicPickup(HouseInfo[houseid][hExtPickup])) DestroyDynamicPickup(HouseInfo[houseid][hExtPickup]);

					new Float: posX, Float: posY, Float: posZ;
					GetPlayerPos(playerid, posX, posY, posZ);

					HouseInfo[houseid][hExtX][0] = posX;
					HouseInfo[houseid][hExtY][0] = posY;
					HouseInfo[houseid][hExtZ][0] = posZ;

					HouseInfo[houseid][hExtVW][0] = GetPlayerVirtualWorld(playerid);
					HouseInfo[houseid][hExtInt][0] = GetPlayerInterior(playerid);

					Save_House(houseid);

					HouseInfo[houseid][hExtPickup] = CreateDynamicPickup(19523, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
					return SendAdmMessageToPlayer(playerid, "Belirtilen ev [ID: %i] için ek bir giriþ ayarladýnýz.", houseid);
				}
				else return SendErrorMessage(playerid, "Burada ek bir giriþ/çýkýþ oluþturamazsýnýz.");
			}
			else if (GetNearOutsideHouse(playerid, 30)) {
				if (IsValidDynamicPickup(HouseInfo[houseid][hExtPickup])) DestroyDynamicCP(HouseInfo[houseid][hExtPickup]);

				new Float: posX, Float: posY, Float: posZ;
				GetPlayerPos(playerid, posX, posY, posZ);

				HouseInfo[houseid][hExtX][0] = posX;
				HouseInfo[houseid][hExtY][0] = posY;
				HouseInfo[houseid][hExtZ][0] = posZ;

				HouseInfo[houseid][hExtVW][0] = GetPlayerVirtualWorld(playerid);
				HouseInfo[houseid][hExtInt][0] = GetPlayerInterior(playerid);

				Save_House(houseid);

				HouseInfo[houseid][hExtPickup] = CreateDynamicPickup(19523, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
				return SendAdmMessageToPlayer(playerid, "Belirtilen ev [ID: %i] için ek bir giriþ oluþturdunuz.", houseid);
			}
			else return SendErrorMessage(playerid, "Burada ek bir giriþ/çýkýþ oluþturamazsýnýz.");
		}
	}

	else
	{
		SendHelpMessage(playerid, "/ahouse [ayar]");
		SendSyntaxMessage(playerid, "create / remove / edit / sell / goto / backdoor");
	}

	return 1;
}

alias:abiz("abusiness");
CMD:abiz(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/abiz [create / remove / edit / goto / sell / types / list]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
		new bizid = -1, level, price, freeze, type, name[32];

		if (sscanf(secoption, "iI(0)I(0)S()[32]",type,freeze,price,name)) return SendHelpMessage(playerid, "/abiz create [tip] {c7c7c7}[0 - satýn alýnabilir | 1 - satýn alýnamaz] [fiyat] [isim]");
		if (freeze < 0 || freeze > 1)					  	 return SendErrorMessage(playerid, "Freezing 0 ile 1 arasýnda olmalýdýr.");
		if (type > sizeof(biz_types) - 1 || type < 0) 	  	 return SendErrorMessage(playerid, "Ýþyeri tipi 0 ile %i arasýnda olmalýdýr.", sizeof(biz_types) - 1);
		if ((bizid = GetNextBizID()) == -1)				 	 return SendErrorMessage(playerid, "Maksimum iþletme sayýsýna ulaþýldý.");
		if (strfind(name, "'", true) != -1) 	return SendErrorMessage(playerid, "Mekan adýnda týrnak iþareti kullanamazsýn.");

		if (!price) {
			switch(type) {
				case 0:							 price = 10000;
				case 1,2,4,5,15..19,21,22,23,24: price = 15000;
				case 3,6,7,12,20: 				 price = 25000;
				case 8,9,10,11,13: 				 price = 45000;
				case 14: 						 price = 100000;
			}
		}

		if (price < 0) return SendErrorMessage(playerid, "Ýþletme fiyatý sýfýrdan küçük olamaz.");

		level = 1;

		GetPlayerPos(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
		BizInfo[bizid][bizPosInt] = GetInterior(playerid);
		BizInfo[bizid][bizPosVW] = GetWorld(playerid);

		GetPlayerPos(playerid, BizInfo[bizid][bizExitX], BizInfo[bizid][bizExitY], BizInfo[bizid][bizExitZ]);
		BizInfo[bizid][bizExitInt] = GetInterior(playerid);
		BizInfo[bizid][bizExitVW] = 6000 + bizid;

		BizInfo[bizid][bizMes] = EOS;
		BizInfo[bizid][bizType] = type;
		BizInfo[bizid][bizLevelbuy] = level;
		BizInfo[bizid][bizPrice] = price;
		BizInfo[bizid][bizFreeze] = freeze;
		BizInfo[bizid][bizOwnerID] =
		BizInfo[bizid][bizLocked] =
		BizInfo[bizid][bizCash] =
		BizInfo[bizid][bizEntrance] =
		BizInfo[bizid][bizRadioOn] =
		BizInfo[bizid][bizRadio] = 0;
		BizInfo[bizid][bFurnitureRadius] = 10.0;

		new biztype = -1;

		switch(type)
		{
			case BIZ_PIZZA:		biztype = 0;
			case BIZ_CLUCKIN:	biztype = 1;
			case BIZ_BURGER:	biztype = 2;
			case BIZ_DONUT:		biztype = 3;
			case BIZ_STORE:		biztype = 4;
			case BIZ_BAR:		biztype = 5;
			case BIZ_PHARMACY:	biztype = 6;
		}

		if (biztype != -1) {
			for (new i = 0; i < max_product[type]; i++) {
				BizInfo[bizid][bizProductPrice][i] = biz_prices[biztype][i];
			}
		}

		DebugMessage(playerid, sprintf("bizpricetype: %d", biztype));

		new modelid;
		switch(BizInfo[bizid][bizType])
		{
			case BIZ_PIZZA:		modelid = 1582;
			case BIZ_BAR:       modelid = 1484;
			case BIZ_ATTACH:    modelid = 2710;
			case BIZ_PHARMACY:	modelid = 1241;
			case BIZ_CLOTHES:   modelid = 1275;
			case BIZ_LICENSE:   modelid = 1581;
			case BIZ_GAS_STATION: modelid = 1650;
			case BIZ_TUNING: modelid = 3096;
			case BIZ_PAYNSPRAY: modelid = 3096;
			default:       modelid = 1272;
		}

		if (BizInfo[bizid][bizOwnerID] == 0 && BizInfo[bizid][bizFreeze] == 0)
		{
			modelid = 19471;
		}

		BizInfo[bizid][bizProduct] = 400;
		BizInfo[bizid][bizBuyPrice] = price;

		format(BizInfo[bizid][bizOwner], MAX_PLAYER_NAME, "Sahipsiz");

		if (isempty(name))	format(BizInfo[bizid][bizName], 32, "%s", biz_types[type]);
		else				format(BizInfo[bizid][bizName], 32, "%s", name);

		BizInfo[bizid][bizPickUp] = CreateDynamicPickup(modelid, 1, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ], BizInfo[bizid][bizPosVW], BizInfo[bizid][bizPosInt], -1, 100.0);
		AddBizToFile(bizid, level, price, freeze, type, BizInfo[bizid][bizName], BizInfo[bizid][bizMes], BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ], BizInfo[bizid][bizExitX], BizInfo[bizid][bizExitY],
		BizInfo[bizid][bizExitZ], BizInfo[bizid][bizPosInt], BizInfo[bizid][bizPosVW], BizInfo[bizid][bizExitInt], BizInfo[bizid][bizExitVW]);
		SendSyntaxMessage(playerid, "Ýþletme oluþturuldu [ID: %i | Level: %i | Fiyat: %i | Satýn Alma: %s | Tip: %s].", bizid, level, price, (freeze) ? ("Hayýr") : ("Evet"), biz_types[BizInfo[bizid][bizType]]);

		if(BizInfo[bizid][bizType] == BIZ_AUTOSALON || BizInfo[bizid][bizType] == BIZ_BOATSALON || BizInfo[bizid][bizType] == BIZ_FLYSALON)  {
			SendHelpMessage(playerid, "Ýþletmede araç spawnlanma noktasýný belirlemek için: '/abiz edit %i vehspawn'", bizid);
		}

		Save_Business(bizid);
	}

	else if (CompareStrings(option, "remove"))
	{
		if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
		new bizid;

		if (sscanf(secoption, "i", bizid))							 return SendHelpMessage(playerid, "/abiz remove [ID]");
		if (bizid < 0 || bizid >= MAX_BIZ || !BizInfo[bizid][bizID]) return SendErrorMessage(playerid, "Belirtilen iþletme bulunamadý.");

		if (IsValidDynamicPickup(BizInfo[bizid][bizPickUp]))	DestroyDynamicPickup(BizInfo[bizid][bizPickUp]);

		new ownerid = GetIDByID(BizInfo[bizid][bizOwnerID]), query[256];

		if (IsPlayerLogged(ownerid))
		{
			SendSyntaxMessage(ownerid, "%s adlý yönetici iþletmenizi sildi.", GetAccName(playerid));
			SendSyntaxMessage(ownerid, "Ýþletmenizin silinmesinden kaynaklý olarak size geri ödeme yapýldý. Geri ödeme: [$%i] Ýþletme fiyatý: [$%i].", BizInfo[bizid][bizPrice], BizInfo[bizid][bizCash]);
			GiveCash(ownerid, BizInfo[bizid][bizPrice]);

			if (BizInfo[bizid][bizCash] > 0) GiveCash(ownerid, BizInfo[bizid][bizCash]);
		}
		else
		{
			new biz_cost = BizInfo[bizid][bizPrice];

			if (BizInfo[bizid][bizCash] > 0) biz_cost += BizInfo[bizid][bizCash];

			mysql_format(dbHandle, query, sizeof(query), "SELECT `cash` FROM `users` WHERE `id` = %i", BizInfo[bizid][bizOwnerID]);
			mysql_tquery(dbHandle, query, "GivePlayerBizMoney", "ii", biz_cost, BizInfo[bizid][bizOwnerID]);
		}

		RemoveAllWorkers(bizid);

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `business` WHERE `id` = %i", BizInfo[bizid][bizID]);
		mysql_tquery(dbHandle, query);

		BizInfo[bizid][bizID] =
		BizInfo[bizid][bizOwnerID] = 0;
		SendSyntaxMessage(playerid, "Belirtilen iþletme silindi [ID: %i].", bizid);
	}

	else if (CompareStrings(option, "edit"))
	{
		if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
		new id, parameters[16], arg[64];

		if (sscanf(secoption, "is[16]S()[64]", id, parameters, arg))
		{
			SendHelpMessage(playerid, "/abiz edit [ID] [ayarlar] [deðer]");
			SendSyntaxMessage(playerid, "price / products / level / type / name / owner / fee / cash / freeze / exterior / interior / int(map) / vehspawn");
			return 1;
		}

		if (id < 0 || id >= MAX_BIZ || !BizInfo[id][bizID]) return SendErrorMessage(playerid, "Ýþletme bulunamadý.");

		if (CompareStrings(parameters, "price"))
		{
			new price;

			if (sscanf(arg, "i", price)) 		return SendHelpMessage(playerid, "/abiz edit [ID] price [fiyat]");
			//if (price < 2 || price > 5000000)	return SendErrorMessage(playerid, "Ýþletme fiyatý $2 ile $5000000 arasýnda olmalýdýr.");

			BizInfo[id][bizPrice] = price;
			SQL_SetInteger("business", "price", BizInfo[id][bizPrice], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Ýþletmenin satýþ fiyatý deðiþtirildi [ID: %i] Yeni fiyat: $%i.", id, BizInfo[id][bizPrice]);
		}
		else if (CompareStrings(parameters, "vehspawn"))
		{
			new Float: posX, Float: posY, Float: posZ, Float: posR;
			GetPlayerPos(playerid, posX, posY, posZ);
			GetPlayerFacingAngle(playerid, posR);

			if (GetDistanceBetweenPoints(posX, posY, posZ, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]) > 30.0)
				return SendErrorMessage(playerid, "Belirlenen nokta iþletmeden çok uzak!");

			GetPlayerPos(playerid, BizInfo[id][bizSpawn][0], BizInfo[id][bizSpawn][1], BizInfo[id][bizSpawn][2]);
			BizInfo[id][bizSpawnInt] = GetInterior(playerid);
			BizInfo[id][bizSpawnVW] = GetWorld(playerid);
			BizInfo[id][bizSpawn][3] = posR;

			SQL_SetFloat("business", "spawnX", BizInfo[id][bizSpawn][0], BizInfo[id][bizID]);
			SQL_SetFloat("business", "spawnY", BizInfo[id][bizSpawn][1], BizInfo[id][bizID]);
			SQL_SetFloat("business", "spawnZ", BizInfo[id][bizSpawn][2], BizInfo[id][bizID]);
			SQL_SetFloat("business", "spawnR", BizInfo[id][bizSpawn][3], BizInfo[id][bizID]);
			SQL_SetInteger("business", "spawnInt", BizInfo[id][bizSpawnInt], BizInfo[id][bizID]);
			SQL_SetInteger("business", "spawnVW", BizInfo[id][bizSpawnVW], BizInfo[id][bizID]);

			SendSyntaxMessage(playerid, "Ýþletmedeki satýn alýmdan sonra aracýn spawnlanacaðý noktayý deðiþtirdiniz [ID: %i].", id);
		}

		else if (CompareStrings(parameters, "products"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new products;

			if (sscanf(arg, "i", products)) 	return SendHelpMessage(playerid, "/abiz edit [ID] products [miktar]");
			if (products < 1 || products > 500)	return SendErrorMessage(playerid, "Ýþletme ürünleri 1 ile 500 arasýnda olabilir.");

			BizInfo[id][bizProduct] = products;
			SQL_SetInteger("business", "product", BizInfo[id][bizProduct], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Belirtilen iþletmenin ürün miktarý deðiþtirildi. [ID: %i] %i.", id, BizInfo[id][bizProduct]);
		}

		else if (CompareStrings(parameters, "owner"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new userid;

			if (sscanf(arg, "i", userid)) 	return SendHelpMessage(playerid, "/abiz edit [ID] owner [yeni sahip]");
			if (!IsPlayerLoggedIn(userid))   return SendErrorMessage(playerid, "Kiþi oyunda deðil.");

			BizInfo[id][bizOwnerID] = PlayerInfo[userid][pID];

            format(BizInfo[id][bizOwner], MAX_PLAYER_NAME, GetName(userid));	
					
			SQL_SetInteger("business", "owner", BizInfo[id][bizOwnerID], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Belirtilen iþletmenin sahibi deðiþtirildi. [ID: %i] %i.", id, BizInfo[id][bizOwnerID]);
		}		

		else if (CompareStrings(parameters, "level"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new level;

			if (sscanf(arg, "i", level))	return SendHelpMessage(playerid, "/abiz edit [ID] level [seviye]");
			if (level < 0 || level > 35)	return SendErrorMessage(playerid, "Seviye 0 ile 35 arasýnda olmalýdýr.");

			BizInfo[id][bizLevelbuy] = level;
			SQL_SetInteger("business", "levelbuy", BizInfo[id][bizLevelbuy], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Belirtilen iþletmenin satýn alma seviyesi deðiþtirildi [ID: %i]. Seviye: %i.", id, BizInfo[id][bizLevelbuy]);
		}

		else if (CompareStrings(parameters, "type"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new type;

			if (sscanf(arg, "i", type)) 					return SendHelpMessage(playerid, "/abiz edit [ID] type [tip]");
			if (type < 0 || type > sizeof(biz_types))	return SendErrorMessage(playerid, "Ýþletme tipi 0 ile %i arasýnda olmalýdýr.", sizeof(biz_types));

			BizInfo[id][bizType] = type;
			SQL_SetInteger("business", "type", BizInfo[id][bizType], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Ýþletmenin tipini deðiþtirdiniz [ID: %i]. Yeni Tip: %s.", id, biz_types[BizInfo[id][bizType]]);
		}

		else if (CompareStrings(parameters, "name"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new name[32];

			if (sscanf(arg, "s[32]", name))	return SendHelpMessage(playerid, "/abiz edit [ID] name [yazý]");
			if (strlen(name) > 30)			return SendErrorMessage(playerid, "Ýþletme adý maksimum 30 karakter olmalýdýr.");
			if (CheckTextDrawString(name))	return SendErrorMessage(playerid, "Ýþletme adýnda geçersiz karakterler olmamalýdýr. '~'.");

			format(BizInfo[id][bizName], 32, "%s", name);
			SQL_SetString("business", "name", BizInfo[id][bizName], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Ýþletmenin adýný deðiþtirdiniz [ID: %i]. Yeni Ad: %s.", id, BizInfo[id][bizName]);
		}

		else if (CompareStrings(parameters, "fee"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new fee;

			if (sscanf(arg, "i", fee))		return SendHelpMessage(playerid, "/abiz edit [ID] fee [fiyat]");
			if (fee < 0 || fee > 100)		return SendErrorMessage(playerid, "Giriþ fiyatý 0 ile 100 arasýnda olmalýdýr.");

			BizInfo[id][bizEntrance] = fee;
			SQL_SetInteger("business", "entrance", BizInfo[id][bizEntrance], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Ýþletmenin giriþ fiyatýný deðiþtirdiniz [ID: %i]. Yeni Fiyat: $%i.", id, BizInfo[id][bizEntrance]);
		}

		else if (CompareStrings(parameters, "cash"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new cash;

			if (sscanf(arg, "i", cash))		return SendHelpMessage(playerid, "/abiz edit [ID] cash [para]");
			if (cash < 0 || cash > 5000000)	return SendErrorMessage(playerid, "Para miktarý $0 ile $5000000 arasýnda olmalýdýr.");

			BizInfo[id][bizCash] = cash;
			SQL_SetInteger("business", "cash", BizInfo[id][bizCash], BizInfo[id][bizID]);
			SendSyntaxMessage(playerid, "Ýþletmenin kasasýnda bulunan parayý düzenlediniz. [ID: %i] Yeni Miktar: $%i.", id, BizInfo[id][bizCash]);
		}

		else if (CompareStrings(parameters, "freeze"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new freeze;

			if (sscanf(arg, "i", freeze))	return SendHelpMessage(playerid, "/abiz edit [ID] freeze [durum]");
			if (freeze < 0 || freeze > 1)	return SendErrorMessage(playerid, "Satýþ durumu 0 ile 1 olmalýdýr.");

			BizInfo[id][bizFreeze] = freeze;
			SQL_SetInteger("business", "freeze", BizInfo[id][bizFreeze], BizInfo[id][bizID]);

			new freeze_naming[4];

			if (BizInfo[id][bizFreeze]) format(freeze_naming, sizeof(freeze_naming), "Hayýr");
			else 						format(freeze_naming, sizeof(freeze_naming), "Evet");

			SendSyntaxMessage(playerid, "Ýþletmenin satýn alýnma durumunu deðiþtirdiniz. [ID: %i] Yeni: %s.", id, freeze_naming);
		}

		else if (CompareStrings(parameters, "exterior"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			if (IsValidDynamicPickup(BizInfo[id][bizPickUp])) DestroyDynamicPickup(BizInfo[id][bizPickUp]);

			GetPlayerPos(playerid, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]);
			BizInfo[id][bizPosInt] = GetInterior(playerid);
			BizInfo[id][bizPosVW] = GetWorld(playerid);

			UpdateBusinessDoor(id);

		    new modelid;
		    switch(BizInfo[id][bizType])
		    {
			    case BIZ_PIZZA:		modelid = 1582;
			    case BIZ_BAR:       modelid = 1484;
			    case BIZ_ATTACH:    modelid = 2710;
			    case BIZ_PHARMACY:	modelid = 1241;
			    case BIZ_CLOTHES:   modelid = 1275;
			    case BIZ_LICENSE:   modelid = 1581;
			    case BIZ_GAS_STATION: modelid = 1650;
			    case BIZ_TUNING: modelid = 3096;
			    case BIZ_PAYNSPRAY: modelid = 3096;
			    default:       modelid = 1272;
		    }

		    if (BizInfo[id][bizOwnerID] == 0 && BizInfo[id][bizFreeze] == 0)
		    {
			modelid = 19471;
		    }

			BizInfo[id][bizPickUp] = CreateDynamicPickup(modelid, 1, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ], BizInfo[id][bizPosVW], BizInfo[id][bizPosInt], -1, 100.0);

			SQL_SetFloat("business", "posx", BizInfo[id][bizPosX], BizInfo[id][bizID]);
			SQL_SetFloat("business", "posy", BizInfo[id][bizPosY], BizInfo[id][bizID]);
			SQL_SetFloat("business", "posz", BizInfo[id][bizPosZ], BizInfo[id][bizID]);
			SQL_SetInteger("business", "posvw", BizInfo[id][bizPosVW], BizInfo[id][bizID]);
			SQL_SetInteger("business", "posint", BizInfo[id][bizPosInt], BizInfo[id][bizID]);

			SendSyntaxMessage(playerid, "Ýþletmenin exterior noktasýný deðiþtirdiniz [ID: %i].", id);
		}

		else if (CompareStrings(parameters, "interior"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			GetPlayerPos(playerid, BizInfo[id][bizExitX], BizInfo[id][bizExitY], BizInfo[id][bizExitZ]);
			BizInfo[id][bizExitInt] = GetInterior(playerid);
			//BizInfo[id][bizExitVW] = GetWorld(playerid);

			SQL_SetFloat("business", "exitx", BizInfo[id][bizExitX], BizInfo[id][bizID]);
			SQL_SetFloat("business", "exity", BizInfo[id][bizExitY], BizInfo[id][bizID]);
			SQL_SetFloat("business", "exitz", BizInfo[id][bizExitZ], BizInfo[id][bizID]);
			SQL_SetInteger("business", "exitint", BizInfo[id][bizExitInt], BizInfo[id][bizID]);
			SQL_SetInteger("business", "exitvw", BizInfo[id][bizExitVW], BizInfo[id][bizID]);

			SendSyntaxMessage(playerid, "Ýþletmenin interior noktasýný deðiþtirdiniz [ID: %i].", id);
		}

		else if (CompareStrings(parameters, "int"))
		{
			if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
			new string[3072];

			for(new i = 0; i < MAX_INTERIORS; i++)
			{
				if (!AdminTeles[i][telesOn] || BUSSINESS_INT_TYPE != AdminTeles[i][telesType]) continue;
				format(string, sizeof(string), "%s\n<%i> {66FF66}%s", string, i, AdminTeles[i][telesMapName]);
			}

			if (isempty(string)) SendErrorMessage(playerid, "Ýþletmeler için interior bulunamadý.");

			SetPVarInt(playerid, "biz_change", id);
			Dialog_Show(playerid, ChangeBizInterior, DIALOG_STYLE_LIST, "{FFFFFF}Ýþletme Interiorlarý", string, "Seç", "Ýptal");
		}

		else
		{
			SendHelpMessage(playerid, "/abiz edit [ID] [ayar] [deðer]");
			SendSyntaxMessage(playerid, "price / products / level / type / name / fee / cash / freeze / enter / exit / int");
			return 1;
		}
	}

	else if (CompareStrings(option, "sell"))
	{
		if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
		new bizid;

		if (sscanf(secoption, "i", bizid))								return SendHelpMessage(playerid, "/abiz sell [ID]");
		if (bizid < 0 || bizid > MAX_BIZ - 1 || !BizInfo[bizid][bizID])	return SendErrorMessage(playerid, "Belirtilen iþletme bulunamadý.");
		if (!BizInfo[bizid][bizOwnerID])								return SendErrorMessage(playerid, "Bu iþletme zaten satýlýk.");

		new ownerid = GetIDByID(BizInfo[bizid][bizOwnerID]);

		if (IsPlayerLogged(ownerid))
		{
			SendSyntaxMessage(ownerid, "%s adlý yönetici iþletmenizi sattý.", GetAccName(playerid));
			SendSyntaxMessage(ownerid, "Ýþletmenizin satýþýyla birlikte tarafýnýza geri ödeme yapýldý. Geri ödeme: [$%i] Ýþletme fiyatý: [$%i].", BizInfo[bizid][bizPrice], BizInfo[bizid][bizCash]);

			GiveCash(ownerid, BizInfo[bizid][bizPrice]);
			if (BizInfo[bizid][bizCash] > 0) GiveCash(ownerid, BizInfo[bizid][bizCash]);
		}
		else
		{
			new biz_cost = BizInfo[bizid][bizPrice];

			if (BizInfo[bizid][bizCash] > 0) biz_cost += BizInfo[bizid][bizCash];

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT `cash` FROM `users` WHERE `id` = %i", BizInfo[bizid][bizOwnerID]);
			mysql_tquery(dbHandle, query, "GivePlayerBizMoney", "ii", biz_cost, BizInfo[bizid][bizOwnerID]);
		}

		Sell_Business(bizid);
		SendSyntaxMessage(playerid, "Belirtilen iþletme satýldý [ID: %i].", bizid);
	}

	else if (CompareStrings(option, "goto"))
	{
		new bizid;

		if (sscanf(secoption, "i", bizid))								return SendHelpMessage(playerid, "/abiz goto [ID]");
		if (bizid < 0 || bizid > MAX_BIZ - 1 || !BizInfo[bizid][bizID])	return SendErrorMessage(playerid, "Belirtilen iþletme bulunamadý.");

		SetPlayerPosEx(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
		SetInterior(playerid, BizInfo[bizid][bizPosInt]);
		SetWorld(playerid, BizInfo[bizid][bizPosVW]);
		SendSpecialMessage(playerid, "Belirtilen iþletmeye ýþýnlandýnýz [ID: %i].", bizid);
	}

	else if (CompareStrings(option, "types"))
	{
		new dialog_header[64] = "{FFFFFF}Ýsim\t{FFFFFF}ID\n", dialog_body[1024];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

		for(new i = 0; i != sizeof(biz_types); i++)
		{
			format(dialog_body, sizeof(dialog_body), "%s%s\t%i\n", dialog_body, biz_types[i], i);
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Ýþletme Tipleri", dialog_body, "Kapat", "");
	}

	else if (CompareStrings(option, "list"))
	{
		pTemp[playerid][pDialogList] = 0;
		DisplayBizList(playerid);
	}

	else
	{
		SendHelpMessage(playerid, "/abiz [create / remove / edit / goto / sell / types / list]");
	}
	return 1;
}

CMD:aapart(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/aapart [create / remove / int / enter / exit / goto]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new apart;

		if ((apart = GetNextApartID()) == -1)	return SendErrorMessage(playerid, "Maksimum apartman sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, ApartInfo[apart][aPosX], ApartInfo[apart][aPosY], ApartInfo[apart][aPosZ]);
		ApartInfo[apart][aPosInt] = GetInterior(playerid);
		ApartInfo[apart][aPosVW] = GetWorld(playerid);
		ApartInfo[apart][aApartOn] = 1;
		ApartInfo[apart][aExitVW] = apart + 1000;

		AddApartToFile(apart, ApartInfo[apart][aPosX], ApartInfo[apart][aPosY], ApartInfo[apart][aPosZ], ApartInfo[apart][aPosInt], ApartInfo[apart][aPosVW]);
		SetAparmentInterior(playerid, apart, 1);

        ApartInfo[apart][aPickup] = CreateDynamicPickup(1314, 1, ApartInfo[apart][aPosX], ApartInfo[apart][aPosY], ApartInfo[apart][aPosZ], ApartInfo[apart][aPosVW], ApartInfo[apart][aPosInt], -1, 50.0);
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;

		if ((id = GetNearApartmentOutside(playerid)) == -1)	return SendErrorMessage(playerid, "Yakýnýnýzda apartman bulunmuyor.");

		DestroyDynamicPickup(ApartInfo[id][aPickup]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `apartment` WHERE `id` = %i", ApartInfo[id][aID]);
		mysql_tquery(dbHandle, query, "OnApartRemove", "i", id);

		SendSyntaxMessage(playerid, "Apartman [ID: %i] silindi.", id);
	}

	else if (CompareStrings(option, "int"))
	{
		new id, interior;

		if ((id = GetNearApartmentOutside(playerid)) == -1)	return SendErrorMessage(playerid, "Yakýnýnýzda apartman bulunmuyor.");
		if (sscanf(secoption, "i", interior))
		{
			SendHelpMessage(playerid, "/aapart int [1-17]");
			SendSyntaxMessage(playerid, "[1] Ghetto Hotel | [2] Ghetto Hotel(2) | [3] Hotel | [4] Hotel(2) | [5] Apartment 1");
			SendSyntaxMessage(playerid, "[6] Apartment 2 | [7] Apartment 3 | [8] Apartment 4");
			SendSyntaxMessage(playerid, "[9] Apartment 5 | [10] Apartment 6 | [11] Apartment 7 | [12] Apartment 8");
			SendSyntaxMessage(playerid, "[13] Apartment 9 | [14] Apartment 10 | [15] Entrance | [16] Motel | [17] Motel (2)");
			return 1;
		}
		if (interior < 1 || interior > 17) return SendErrorMessage(playerid, "Interior ID 1 ile 17 arasýnda olmalýdýr.");

		SetAparmentInterior(playerid, id, interior);
	}

	else if (CompareStrings(option, "enter"))
	{
		new apartid;

		if (sscanf(secoption, "i", apartid))											return SendHelpMessage(playerid, "/aapart enter [ID]");
		if (apartid < 0 || apartid > MAX_APART - 1 || !ApartInfo[apartid][aApartOn])	return SendErrorMessage(playerid, "Apartman bulunamadý.");

		if (IsValidDynamicCP(ApartInfo[apartid][aPickup]))	DestroyDynamicCP(ApartInfo[apartid][aPickup]);

		GetPlayerPos(playerid, ApartInfo[apartid][aPosX], ApartInfo[apartid][aPosY], ApartInfo[apartid][aPosZ]);
		ApartInfo[apartid][aPosInt] = GetInterior(playerid);
		ApartInfo[apartid][aPosVW] = GetWorld(playerid);

		SQL_SetFloat("apartment", "posx", ApartInfo[apartid][aPosX], ApartInfo[apartid][aID]);
		SQL_SetFloat("apartment", "posy", ApartInfo[apartid][aPosY], ApartInfo[apartid][aID]);
		SQL_SetFloat("apartment", "posz", ApartInfo[apartid][aPosZ], ApartInfo[apartid][aID]);
		SQL_SetInteger("apartment", "posint", ApartInfo[apartid][aPosInt], ApartInfo[apartid][aID]);
		SQL_SetInteger("apartment", "posvw", ApartInfo[apartid][aPosVW], ApartInfo[apartid][aID]);

		ApartInfo[apartid][aPickup] = ApartInfo[apartid][aPickup] = CreateDynamicPickup(1314, 1, ApartInfo[apartid][aPosX], ApartInfo[apartid][aPosY], ApartInfo[apartid][aPosZ], ApartInfo[apartid][aPosVW], ApartInfo[apartid][aPosInt], -1, 50.0);
		SendSyntaxMessage(playerid, "Apartman giriþi deðiþtirildi [ID: %i].", apartid);
	}

	else if (CompareStrings(option, "exit"))
	{
		new apartid;

		if (sscanf(secoption, "i", apartid)) 											return SendHelpMessage(playerid, "/aapart exit [ID]");
		if (apartid < 0 || apartid > MAX_APART - 1 || !ApartInfo[apartid][aApartOn])	return SendErrorMessage(playerid, "Apartman bulunamadý.");

		GetPlayerPos(playerid, ApartInfo[apartid][aExitX], ApartInfo[apartid][aExitY], ApartInfo[apartid][aExitZ]);
		ApartInfo[apartid][aExitInt] = GetInterior(playerid);
		//ApartInfo[apartid][aExitVW] = GetWorld(playerid);

		SQL_SetFloat("apartment", "exitx", ApartInfo[apartid][aExitX], ApartInfo[apartid][aID]);
		SQL_SetFloat("apartment", "exity", ApartInfo[apartid][aExitY], ApartInfo[apartid][aID]);
		SQL_SetFloat("apartment", "exitz", ApartInfo[apartid][aExitZ], ApartInfo[apartid][aID]);
		SQL_SetInteger("apartment", "exitint", ApartInfo[apartid][aExitInt], ApartInfo[apartid][aID]);
		SQL_SetInteger("apartment", "exitvw", ApartInfo[apartid][aExitVW], ApartInfo[apartid][aID]);

		SendSyntaxMessage(playerid, "Apartman giriþi deðiþtirildi [ID: %i].", apartid);
	}

	else if (CompareStrings(option, "goto"))
	{
		new apartid;

		if (sscanf(secoption, "i", apartid))										 return SendHelpMessage(playerid, "/aapart goto [ID]");
		if (apartid < 0 || apartid > MAX_APART - 1 || !ApartInfo[apartid][aApartOn]) return SendErrorMessage(playerid, "Apartman bulunamadý");

		SetPlayerPosEx(playerid, ApartInfo[apartid][aPosX], ApartInfo[apartid][aPosY], ApartInfo[apartid][aPosZ]);
		SetInterior(playerid, ApartInfo[apartid][aPosInt]);
		SetWorld(playerid, ApartInfo[apartid][aPosVW]);
		SendSpecialMessage(playerid, "Belirtilen apartmana ýþýnlandýnýz [ID: %i].", apartid);
	}

	else
	{
		SendHelpMessage(playerid, "/aapart [create/remove/int/enter/exit/goto]");
	}

	return 1;
}

alias:changenickname("changenick");
CMD:changenickname(playerid, params[])
{
	new userid, newname[MAX_PLAYER_NAME];

    if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) 			return SendNotAdmin(playerid);
	if (sscanf(params,"us[36]", userid, newname))		return SendHelpMessage(playerid, "/changename [ID/Karakter Adý] [Yeni Ad]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
    if (!IsValidPlayerName(newname))					return SendErrorMessage(playerid, "Geçersiz isim formatý.");
	if (strlen(newname) < 4 || strlen(newname) > 36)	return SendErrorMessage(playerid, "Belirtilen ad minimum 4, maksimum 36 karakter olmalýdýr.");

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `login` = '%e'", newname);
	mysql_tquery(dbHandle, query, "OnAdminChangeNickName", "iis", playerid, userid, newname);
	return 1;
}

alias:changename("setname");
CMD:changename(playerid, params[])
{
	new userid, newname[MAX_PLAYER_NAME];

    if (!CheckAdmin(playerid, ADMIN_LEVEL_3) && PlayerInfo[playerid][pFMAdmin] < 1) 			return SendNotAdmin(playerid);
	if (sscanf(params,"us[24]", userid, newname))		return SendHelpMessage(playerid, "/changename [ID/Karakter Adý] [Yeni Ad]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
    if (!IsValidPlayerName(newname))					return SendErrorMessage(playerid, "Geçersiz isim formatý.");
	if (strlen(newname) < 4 || strlen(newname) > 24)	return SendErrorMessage(playerid, "Belirtilen ad minimum 4, maksimum 24 karakter olmalýdýr.");

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e'", newname);
	mysql_tquery(dbHandle, query, "OnAdminChangeName", "iis", playerid, userid, newname);
	return 1;
}

alias:tracenumber("numarasorgu");
CMD:tracenumber(playerid, params[])
{
	new number;

    if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && PlayerInfo[playerid][pFMAdmin] < 1) 			return SendNotAdmin(playerid);
	if (sscanf(params,"i", number))		return SendHelpMessage(playerid, "/tracenumber [numara]");

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `number` = '%i'", number);
	mysql_tquery(dbHandle, query, "OnAdminTraceNumber", "ii", playerid, number);
	return 1;
}

CMD:adoor(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/adoor [create / remove / faction / vehicle / text / enter / exit / goto / namegps]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new enterid = -1;

		for(new i = 0; i < MAX_ENTRANCE; i++)
		{
			if (EntranceInfo[i][entranceOn])	continue;

			enterid = i;
			break;
		}

		if (enterid == -1)	return SendErrorMessage(playerid, "Maksimum giriþ/çýkýþ sayýsýna ulaþtýnýz.");

		GetPlayerPos(playerid, EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ]);
		GetPlayerFacingAngle(playerid, EntranceInfo[enterid][eEnterA]);

	    EntranceInfo[enterid][eEnterInt] = GetInterior(playerid);
	    EntranceInfo[enterid][eEnterVW] = GetWorld(playerid);

	    GetPlayerPos(playerid, EntranceInfo[enterid][eExitX], EntranceInfo[enterid][eExitY], EntranceInfo[enterid][eExitZ]);
		GetPlayerFacingAngle(playerid, EntranceInfo[enterid][eExitA]);

	    EntranceInfo[enterid][eExitInt] = GetInterior(playerid);
	    EntranceInfo[enterid][eExitVW] = 1000 + enterid;
   		EntranceInfo[enterid][eEnterPickup] = CreateDynamicPickup(1239, 1, EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ], EntranceInfo[enterid][eEnterVW], EntranceInfo[enterid][eEnterInt], -1, 100.0);
		EntranceInfo[enterid][eExitPickup] = CreateDynamicPickup(1239, 1, EntranceInfo[enterid][eExitX], EntranceInfo[enterid][eExitY], EntranceInfo[enterid][eExitZ], EntranceInfo[enterid][eExitVW], EntranceInfo[enterid][eExitInt], -1, 100.0);
		EntranceInfo[enterid][entranceOn] = 1;
		EntranceInfo[enterid][eLocked] = 0;

    	new query[156];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `entrance` (`enterx`,`entery`,`enterz`,`entera`,`entervw`,`enterint`) VALUES (%f,%f,%f,%f,%i,%i)", EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ], EntranceInfo[enterid][eEnterA], EntranceInfo[enterid][eEnterVW], EntranceInfo[enterid][eEnterInt]);
		mysql_tquery(dbHandle, query, "OnInsertEntrance", "i", enterid);

    	SendSyntaxMessage(playerid, "Yeni giriþ/çýkýþ oluþturuldu [ID: %i].", enterid);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new enterid;

		if (sscanf(secoption, "i", enterid))	return SendHelpMessage(playerid, "/adoor remove [ID]");
		if (!EntranceInfo[enterid][entranceOn])	return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");

		if (IsValidDynamicPickup(EntranceInfo[enterid][eEnterPickup]))	DestroyDynamicPickup(EntranceInfo[enterid][eEnterPickup]);
		if (IsValidDynamicPickup(EntranceInfo[enterid][eExitPickup]))	DestroyDynamicPickup(EntranceInfo[enterid][eExitPickup]);

		EntranceInfo[enterid][entranceOn] = 0;

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `entrance` WHERE `id` = %i", EntranceInfo[enterid][eID]);
		mysql_tquery(dbHandle, query);

		SendSyntaxMessage(playerid, "Belirtilen giriþ/çýkýþ [ID: %i] silindi.", enterid);
		return 1;
	}

	else if (CompareStrings(option, "faction"))
	{
		new enterid, faction = 0;

		if (sscanf(secoption, "iI(0)", enterid, faction))										 return SendHelpMessage(playerid, "/adoor faction [ID giriþ/çýkýþ] {c7c7c7}[Faction ID]");
		if (faction < 0 || faction >= MAX_FACTIONS || (faction != 0 && !Factions[faction][fON])) return SendErrorMessage(playerid, "Birlik bulunamadý.");
		if (!EntranceInfo[enterid][entranceOn])													 return SendErrorMessage(playerid, "Giriþ/çýkýþ bulunamadý.");

		EntranceInfo[enterid][eFaction] = faction;
		SQL_SetInteger("entrance", "faction", EntranceInfo[enterid][eFaction], EntranceInfo[enterid][eID]);
		SendSyntaxMessage(playerid, "Birlik giriþ/çýkýþýný deðiþtirdiniz [ID: %i]. Yeni Deðer: %i.", enterid, EntranceInfo[enterid][eFaction]);
		return 1;
	}

	else if (CompareStrings(option, "vehicle"))
	{
		new enterid, vehicle;

		if (sscanf(secoption, "ii", enterid, vehicle))	return SendHelpMessage(playerid, "/adoor vehicle [ID giriþ/çýkýþ] [araç geçiþi (0 - kapalý | 1 - açýk)]");
		if (vehicle < 0 || vehicle > 1)					return SendErrorMessage(playerid, "Deðer 0 veya 1 olmalýdýr.");
		if (!EntranceInfo[enterid][entranceOn])			return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý");

		EntranceInfo[enterid][eVehicle] = vehicle;
		SQL_SetInteger("entrance", "vehicle", EntranceInfo[enterid][eVehicle], EntranceInfo[enterid][eID]);

		new entrance_state[16];

		if (EntranceInfo[enterid][eVehicle])	format(entrance_state, sizeof(entrance_state), "izin verildi");
		else									format(entrance_state, sizeof(entrance_state), "yasaklandý");

		SendSyntaxMessage(playerid, "Belirtilen iþletmenin araç giriþ/çýkýþ yetkisi düzenlendi. [ID: %i] Yeni Deðer: %s.", enterid, entrance_state);
		return 1;
	}

	else if (CompareStrings(option, "text"))
	{
		new enterid, text[128];

		if (sscanf(secoption, "is[128]", enterid, text)) return SendHelpMessage(playerid, "/adoor text [ID giriþ/çýkýþ] [yazý]");
		if (!EntranceInfo[enterid][entranceOn])			 return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");
		if (strlen(text) < 1 || strlen(text) > 127)		 return SendErrorMessage(playerid, "Belirtilen yazý minimum 1, maksimum 127 karakter olmalýdýr.");

		format(EntranceInfo[enterid][eText], 128, "%s", text);
		SQL_SetString("entrance", "text", EntranceInfo[enterid][eText], EntranceInfo[enterid][eID]);
		SendSyntaxMessage(playerid, "Belirtilen giriþ/çýkýþýn yazýsý deðiþtirildi [ID: %i]. Yeni deðer: %s.", enterid, EntranceInfo[enterid][eText]);
		return 1;
	}

	else if (CompareStrings(option, "enter"))
	{
		new enterid;

		if (sscanf(secoption, "i", enterid))	return SendHelpMessage(playerid, "/adoor enter [ID giriþ/çýkýþ]");
		if (!EntranceInfo[enterid][entranceOn])	return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");

		GetPlayerPos(playerid, EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ]);
		GetPlayerFacingAngle(playerid, EntranceInfo[enterid][eEnterA]);

		EntranceInfo[enterid][eEnterInt] = GetInterior(playerid);
		EntranceInfo[enterid][eEnterVW] = GetWorld(playerid);

		if (IsValidDynamicPickup(EntranceInfo[enterid][eEnterPickup]))	DestroyDynamicPickup(EntranceInfo[enterid][eEnterPickup]);

		EntranceInfo[enterid][eEnterPickup] = CreateDynamicPickup(1239, 1, EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ], EntranceInfo[enterid][eEnterVW], EntranceInfo[enterid][eEnterInt], -1, 100.0);

		SQL_SetFloat("entrance", "enterx", EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "entery", EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "enterz", EntranceInfo[enterid][eEnterZ], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "entera", EntranceInfo[enterid][eEnterA], EntranceInfo[enterid][eID]);
		SQL_SetInteger("entrance", "entervw", EntranceInfo[enterid][eEnterVW], EntranceInfo[enterid][eID]);
		SQL_SetInteger("entrance", "enterint", EntranceInfo[enterid][eEnterInt], EntranceInfo[enterid][eID]);

		SendSyntaxMessage(playerid, "Belirtilen yerin giriþ pozisyonu deðiþtirildi. [ID: %i].", enterid);
		return 1;
	}

	else if (CompareStrings(option, "exit"))
	{
		new enterid;

		if (sscanf(secoption, "i", enterid))	return SendHelpMessage(playerid, "/adoor exit [ID giriþ/çýkýþ]");
		if (!EntranceInfo[enterid][entranceOn])	return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");

		GetPlayerPos(playerid, EntranceInfo[enterid][eExitX], EntranceInfo[enterid][eExitY], EntranceInfo[enterid][eExitZ]);
		GetPlayerFacingAngle(playerid, EntranceInfo[enterid][eExitA]);

		EntranceInfo[enterid][eExitInt] = GetInterior(playerid);
		EntranceInfo[enterid][eExitVW] = GetWorld(playerid);

		if (IsValidDynamicPickup(EntranceInfo[enterid][eExitPickup]))	DestroyDynamicPickup(EntranceInfo[enterid][eExitPickup]);

		EntranceInfo[enterid][eExitPickup] = CreateDynamicPickup(1239, 1, EntranceInfo[enterid][eExitX], EntranceInfo[enterid][eExitY], EntranceInfo[enterid][eExitZ], EntranceInfo[enterid][eExitVW], EntranceInfo[enterid][eExitInt], -1, 100.0);

		SQL_SetFloat("entrance", "exitx", EntranceInfo[enterid][eExitX], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "exity", EntranceInfo[enterid][eExitY], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "exitz", EntranceInfo[enterid][eExitZ], EntranceInfo[enterid][eID]);
		SQL_SetFloat("entrance", "exita", EntranceInfo[enterid][eExitA], EntranceInfo[enterid][eID]);
		SQL_SetInteger("entrance", "exitvw", EntranceInfo[enterid][eExitVW], EntranceInfo[enterid][eID]);
		SQL_SetInteger("entrance", "exitint", EntranceInfo[enterid][eExitInt], EntranceInfo[enterid][eID]);

		SendSyntaxMessage(playerid, "Belirtilen yerin çýkýþ pozisyonu deðiþtirildi [ID: %i].", enterid);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new enterid;

		if (sscanf(secoption, "i", enterid))		return SendHelpMessage(playerid, "/adoor goto [ID giriþ/çýkýþ]");
		if (!EntranceInfo[enterid][entranceOn])		return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");
		if (enterid >= MAX_ENTRANCE || enterid < 0)	return SendErrorMessage(playerid, "Belirtilen deðer 0 ile %i arasýnda olmalýdýr.", MAX_ENTRANCE);

		SetPlayerPosEx(playerid, EntranceInfo[enterid][eEnterX], EntranceInfo[enterid][eEnterY], EntranceInfo[enterid][eEnterZ]);
		SetInterior(playerid, EntranceInfo[enterid][eEnterInt]);
		SetWorld(playerid, EntranceInfo[enterid][eEnterVW]);
	}

	else if (CompareStrings(option, "namegps"))
	{
		new enterid, text[128];

		if (sscanf(secoption, "is[128]", enterid, text)) return SendHelpMessage(playerid, "/adoor namegps [ID giriþ/çýkýþ] [yazý]");
		if (!EntranceInfo[enterid][entranceOn])			 return SendErrorMessage(playerid, "Belirtilen giriþ/çýkýþ bulunamadý.");
		if (strlen(text) < 1 || strlen(text) > 127)		 return SendErrorMessage(playerid, "Yazý deðeri minimum 1, maksimum 127 karakter olmalýdýr.");

		format(EntranceInfo[enterid][gpsText], 128, "%s", text);
		SQL_SetString("entrance", "gpsname", EntranceInfo[enterid][gpsText], EntranceInfo[enterid][eID]);
		SendSyntaxMessage(playerid, "Belirtilen giriþ/çýkýþýn GPS adý deðiþtirildi [ID: %i]. Yeni deðer: %s.", enterid, EntranceInfo[enterid][gpsText]);
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/adoor [create / remove / faction / vehicle / text / enter / exit / goto / namegps]");
	}
	return 1;
}

CMD:arental(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);

	new option[16], secoption[128];
	
	if (sscanf(params, "s[16]S()[128]", option, secoption)) return SendHelpMessage(playerid, "/arental [create / remove / goto / job]");

	if (CompareStrings(option, "create"))
	{
		new rental_type;

		if (sscanf(secoption, "d", rental_type))
		{
			SendHelpMessage(playerid, "/arental [kiralama türü] [1- meslek, 2- normal araç kiralama]");
			return 1;
		}
		if (rental_type < 1 || rental_type > 2) return SendErrorMessage(playerid, "Geçersiz bir deðer girdiniz.");

		if (Rental_Nearest(playerid) != -1) return SendErrorMessage(playerid, "Baþka bir noktaya yakýnsýnýz.");

		new id = Iter_Free(RentalPoints);
		if (id == -1) 
			return SendErrorMessage(playerid, "Maksimum eklenebilecek dolap sýnýrýna ulaþýlmýþ.");

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
    	InsertRental(playerid, x, y, z, rental_type);

		SendAdmMessageToPlayer(playerid, "Kiralama noktasý oluþturuldu. [ID: %d].", id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;
		
		if (sscanf(secoption, "i", id))							return SendHelpMessage(playerid, "/arental remove [Rental ID]");
		if(!Iter_Contains(RentalPoints, id)) return SendErrorMessage(playerid, "Hatalý nokta ID girdin.");
        
		if (IsValidDynamic3DTextLabel(RentalPoint[id][rental3D]))
		{
			DestroyDynamic3DTextLabel(RentalPoint[id][rental3D]);
			RentalPoint[id][rental3D] = Text3D:INVALID_3DTEXT_ID;
		}

		if(IsValidDynamicPickup(RentalPoint[id][rentalPickup]))
			DestroyDynamicPickup(RentalPoint[id][rentalPickup]);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `rental_points` WHERE `id` = %d", RentalPoint[id][rentalID]);
		mysql_tquery(dbHandle, query);

		RentalPoint[id][rentalID] = 0;
		RentalPoint[id][rentalX] = 0.0;
		RentalPoint[id][rentalY] = 00.0;
		RentalPoint[id][rentalZ] = -500.0;
		Iter_Remove(RentalPoints, id);
		
		SendAdmMessageToPlayer(playerid, "Dolap kaldýrýldý. [ID:%d]", id);	
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))							return SendHelpMessage(playerid, "/arental goto [Rental ID]");
		if(!Iter_Contains(RentalPoints, id)) return SendErrorMessage(playerid, "Hatalý nokta ID girdin.");

		SetPlayerPosEx(playerid, RentalPoint[id][rentalX], RentalPoint[id][rentalY], RentalPoint[id][rentalZ]);
		return 1;
	}

	else if (CompareStrings(option, "job"))
	{
		new id, job;

		if (sscanf(secoption, "ii", id, job))							return SendHelpMessage(playerid, "/arental job [rental id] [meslek id]");
		if(!Iter_Contains(RentalPoints, id)) return SendErrorMessage(playerid, "Hatalý nokta ID girdin.");

		RentalPoint[id][rentalJob] = job;
		SendServerMessage(playerid, "Noktanýn ID'si %d olarak deðiþtirildi.", job);

        SQL_SetInteger("rental_points", "job", RentalPoint[id][rentalJob], RentalPoint[id][rentalID]);		
		return 1;
	}	
	
	else
	{
		SendHelpMessage(playerid, "/arental [create / remove / goto]");
	}
	return 1;
}

CMD:setfaction(playerid, params[])
{
	new userid, faction, rank;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params,"udd", userid, faction, rank))		return SendHelpMessage(playerid, "/setfaction [ID/Karakter Adý] [faction id] [rütbe]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
	if (rank < 1 || rank > 20)                  return SendErrorMessage(playerid, "Rütbe 1 ile 20 arasýnda olmalýdýr.");
    if (faction < 1 || faction > MAX_FACTIONS-1 || !Factions[faction][fON]) return SendErrorMessage(playerid, "Belirtilen birlik bulunamadý.");

    RemovePlayerFaction(userid);

	PlayerInfo[userid][pFaction] = faction;
	SQL_SetInteger("users", "faction", PlayerInfo[userid][pFaction], PlayerInfo[userid][pID]);

	PlayerInfo[userid][pRank] = Factions[faction][fRanks];
	SQL_SetInteger("users", "rank", PlayerInfo[userid][pRank], PlayerInfo[userid][pID]);

	SendServerMessage(playerid, "%s adlý kiþinin birliði deðiþtirildi. Birlik: %s Rütbe: %s", GetNameEx(userid), Factions[faction][fName], GetRankName(userid));
	SendServerMessage(playerid, "%s adlý yönetici birliðinizi deðiþtirdi. Birlik: %s Rütbe: %s", GetNameEx(playerid), Factions[faction][fName], GetRankName(userid));
	return 1;
}

CMD:createlocker(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	new faction_id;

	if(sscanf(params, "d", faction_id))
		return SendHelpMessage(playerid, "/createlocker [birlik numarasý]");

	if(faction_id < 1)
		return SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");

	mysql_tquery(dbHandle, sprintf("SELECT name FROM factions WHERE factionid = %i", faction_id), "OnStaffCreateLocker", "dd", playerid, faction_id);

	return 1;
}
alias:createlocker("dolapekle");

CMD:deletelocker(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	new locker_id;

	if(sscanf(params, "d", locker_id))
		return SendHelpMessage(playerid, "/deletelocker [dolap numarasý (/listlockers)]");

	if(locker_id < 1)
		return SendErrorMessage(playerid, "Geçersiz dolap numarasý girdiniz.");

	mysql_tquery(dbHandle, GetLocker("factions.name, faction_lockers.faction_id, faction_lockers.label_id", "LEFT JOIN factions ON factions.factionid = faction_lockers.faction_id", "", 1, -1, locker_id), "OnStaffDeleteLocker", "dd", playerid, locker_id);

	return 1;
}
alias:deletelocker("dolapsil");

CMD:editlocker(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	new locker_id, opt[9], str[32];

	if(sscanf(params, "ds[9]S()[32]", locker_id, opt, str))
	{
		SendHelpMessage(playerid, "/editlocker [dolap numarasý] [seçenek]");
		SendSyntaxMessage(playerid, "birlikid, pozisyon");
		return 1;
	}

	if(locker_id < 1)
		return SendErrorMessage(playerid, "Geçersiz dolap numarasý girdiniz.");

	if(!strcmp(opt, "birlikid", true) || !strcmp(opt, "birlik", true))
	{
		new faction_id;

		if(sscanf(str, "d", faction_id))
			return SendHelpMessage(playerid, "/editlocker <dolap numarasý> <birlikid> [birlik numarasý]");

		mysql_tquery(dbHandle, EditLocker(locker_id, faction_id), "OnStaffEditLockerFaction", "ddd", playerid, locker_id, faction_id);
	}

	else if(!strcmp(opt, "pozisyon", true) || !strcmp(opt, "pos", true))
	{
		new interior, world, Float:x, Float:y, Float:z;

		interior = GetPlayerInterior(playerid);
		world = GetPlayerVirtualWorld(playerid);

		GetPlayerPos(playerid, x, y, z);

		mysql_tquery(dbHandle, EditLocker(locker_id, -1, Text3D:-1, interior, world, x, y, z), "OnStaffEditLockerPos", "dd", playerid, locker_id);
	}

	else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

	return 1;
}
alias:editlocker("dolapduzenle");

CMD:listlockers(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
	mysql_tquery(dbHandle, GetLocker("faction_lockers.id, factions.name, faction_lockers.faction_id", "LEFT JOIN factions ON factions.factionid = faction_lockers.faction_id"), "OnStaffListLockers", "d", playerid);

	return 1;
}
alias:listlockers("listlocker", "dolaplar", "dolapliste");

// arrest

CMD:createarrestpoint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
    Dialog_Show(playerid, CreateArrestConfirmation, DIALOG_STYLE_MSGBOX, "Hapis Noktasý Eklenmesi", EMBED_WHITE "Bulunduðunuz noktaya hapis noktasý eklenecektir. Emin misiniz?", "Ekle", "Ýptal");
    return 1;
}
alias:createarrestpoint("hapisekle");

CMD:deletearrestpoint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);	
    new id;

    if(sscanf(params, "d", id))
        return SendHelpMessage(playerid, "/deletarrestpoint [hapis noktasý numarasý]");

    if(id < 1)
        return SendErrorMessage(playerid, "Geçersiz hapis noktasý numarasý girdiniz.");

    mysql_tquery(dbHandle, GetArrestPoint("arrest_points.pickup_id, arrest_points.label_id", "", "", 1, -1, id), "OnStaffDeleteArrestPoint", "dd", playerid, id);

    return 1;
}
alias:deletearrestpoint("hapissil", "hapiskaldir");

CMD:editarrestpoint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);	
    new id, opt[9];

    if(sscanf(params, "ds[9]", id, opt))
    {
        SendHelpMessage(playerid, "/editarrestpoint [hapis noktasý numarasý] [seçenek]");
        SendSyntaxMessage(playerid, "pozisyon");

        return 1;
    }

    if(id < 1)
        return SendErrorMessage(playerid, "Geçersiz hapis noktasý numarasý girdiniz.");

    if(!strcmp(opt, "pozisyon", true))
    {
        new interior, world, Float:x, Float:y, Float:z;

        interior = GetPlayerInterior(playerid);
        world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, x, y, z);

        mysql_tquery(dbHandle, EditArrestPoint(id, -1, Text3D:-1, interior, world, x, y, z), "OnStaffEditArrestPointPos", "dd", playerid, id);
    }

    else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

    return 1;
}
alias:editarrestpoint("hapisduzenle", "hapisduzen");

CMD:listarrestpoints(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotAdmin(playerid);
    mysql_tquery(dbHandle, GetArrestPoint("arrest_points.id"), "OnStaffListArrestPoints", "d", playerid);

    return 1;
}
alias:listarrestpoints("arrestpoints", "hapisnoktalari", "hapisler");