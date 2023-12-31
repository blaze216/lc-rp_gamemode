/*CMD:editspawn(playerid,params[])
{
	new factionid = PlayerInfo[playerid][pFaction];

	if (!isLeader(playerid) && !GetSpawnRight(playerid)) return SendErrorMessage(playerid, "Birli�in spawn konumunu de�i�tirmenize izin verilmez.");

    GetPlayerPos(playerid, Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ]);
	Factions[factionid][fSpawnInt] = GetInterior(playerid);
	Factions[factionid][fSpawnVW] = GetWorld(playerid);

    new query[128 + 56];
    mysql_format(dbHandle, query, sizeof(query), "UPDATE `factions` SET `spawnx`=%f, `spawny`=%f, `spawnz`=%f, `spawnint`=%i, `spawnvw`=%i WHERE `id`= %i", Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ], Factions[factionid][fSpawnInt], Factions[factionid][fSpawnVW], Factions[factionid][fID]);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "%s birli�inin bu konumda do�mas�n� ayarlad�n�z.", Factions[factionid][fName]);
	return 1;
}*/

CMD:rutbeisim(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], rank, name[32];

	if (!isLeader(playerid) && !GetRankNameRight(playerid))		return SendErrorMessage(playerid, "R�tbe isimlerini de�i�tirmenize izin verilmiyor.");
	if (sscanf(params,"ds[31]", rank, name))					return SendHelpMessage(playerid, "/rutbeisim [r�tbe numaras�] [yeni isim]");
	if (strlen(name) > 31)										return SendErrorMessage(playerid, "R�tbe ad� en fazla 31 karakter i�erebilir.");
	if (rank < 1 || rank > Factions[faction][fRanks])			return SendErrorMessage(playerid, "1'den %i'ye kadar s�ralay�n.", Factions[faction][fRanks]);
	if (strfind(name, "'", true) != -1) 	                    return SendErrorMessage(playerid, "R�tbe ad�nda t�rnak i�areti kullanamazs�n.");
	
	format(FactionRanks[faction][rank-1], 32, "%s", name);
	UpdateFactionRank(faction, rank);
	SendSyntaxMessage(playerid, "R�tbenin ad�n� [ID: %i] '%s olarak de�i�tirdiniz.", rank, name);
	return 1;
}

alias:fchat("birliksohbet");
CMD:fchat(playerid, params[])
{
	if (PlayerInfo[playerid][pFaction] == 0)			return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n.");
    if (!isLeader(playerid) && !GetChatRight(playerid))	return SendErrorMessage(playerid, "Bunu yapmak i�in yetkiniz yok.");

	new faction = PlayerInfo[playerid][pFaction];
	if (Factions[faction][fChatON] == 1)
	{
		SendFactionMessageF(faction, COLOR_LIGHTBLUE, "** %s birlik sohbet kanal�n� devre d��� b�rakt�.", GetNameEx(playerid));
		SendSyntaxMessage(playerid, "Birlik sohbet kanal� devre d��� b�rak�ld�. Art�k sadece sen yazabilirsin.");
		Factions[faction][fChatON] = 0;
	}
	else
	{
		SendFactionMessageF(faction, COLOR_LIGHTBLUE, "** %s birlik sohbet kanal�n� aktif etti.", GetNameEx(playerid));
		SendSyntaxMessage(playerid, "Birlik sohbet kanal� aktif edildi. T�m �yeler kanala yazabilir. ");
		Factions[faction][fChatON] = 1;
	}
	SQL_SetInteger("factions", "chaton", Factions[faction][fChatON], faction);
	return 1;
}

CMD:birlikdavet(playerid, params[])
{
    if (PlayerInfo[playerid][pFaction] == 0)						return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n. ");
    if (!isLeader(playerid) && !GetInviteRight(playerid))			return SendErrorMessage(playerid, "Bir birli�e kabul edilmeye hakk�n�z yok.");
    if (Factions[PlayerInfo[playerid][pFaction]][fJoinRank] == 0)	return SendErrorMessage(playerid, "L�tfen birli�inizin giri� r�tbesini ayarlay�n. ");

	new userid;

	if (sscanf(params,"u",userid))									return SendHelpMessage(playerid, "/birlikdavet [ID / isim]");
	if (!IsPlayerLogged(userid))									return SendNotConnected(playerid);
	if (userid == playerid)											return SendErrorMessage(playerid, "Zaten bir birliktesiniz.");
    if (PlayerInfo[userid][pFaction] != 0)							return SendErrorMessage(playerid, "Oyuncu zaten bir birlikte.");
    if (pTemp[userid][pFactionPlayer] == playerid)					return SendErrorMessage(playerid, "Oyuncuyu birli�e kat�lmaya zaten davet ettiniz.");

	//pTemp[userid][pFactionPlayer] = playerid;
	pTemp[userid][pFactionInvite] = PlayerInfo[playerid][pFaction];
	pTemp[userid][pFactionInvitedBy] = playerid;

	SendSyntaxMessage(userid, "%s seni %s adl� birli�e davet etti. (Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid), Factions[PlayerInfo[playerid][pFaction]][fName]);
	SendSyntaxMessage(playerid, "%s adl� ki�iyi birli�e davet ettin.", GetNameWithMask(userid));
	return 1;
}

CMD:birlikdavetkabul(playerid, params[])
{
	if(PlayerInfo[playerid][pFaction])
		return SendErrorMessage(playerid, "Zaten bir birlikte bulunuyorsunuz.");

	if(!pTemp[playerid][pFactionInvite])
		return SendErrorMessage(playerid, "Herhangi biri taraf�ndan birli�e davet edilmediniz.");

	SendClientMessageEx(pTemp[playerid][pFactionInvitedBy], COLOR_YELLOW, "%s adl� ki�i birlik davetinizi kabul etti.", GetNameWithMask(playerid));
	SendSyntaxMessage(playerid, "Birlik davetini kabul ettiniz.");

	PlayerInfo[playerid][pFaction] = pTemp[playerid][pFactionInvite];
	PlayerInfo[playerid][pRank] = Factions[PlayerInfo[playerid][pFaction]][fJoinRank];

	pTemp[playerid][pFactionInvite] = 0;
	pTemp[playerid][pFactionInvitedBy] = INVALID_PLAYER_ID;

	//SaveCharacter(playerid);
	Save_User(playerid);
	return 1;
}
CMD:birliktenat(playerid, params[])
{
    if (PlayerInfo[playerid][pFaction] == 0)						return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n.");
    if (!isLeader(playerid) && !GetUninviteRight(playerid))			return SendErrorMessage(playerid, "Birlikten birisini atma iznin yok.");
    //if (Factions[PlayerInfo[playerid][pFaction]][fJoinRank] == 0)	return SendErrorMessage(playerid, "Please set join rank in your structure. ");

	new userid;

	if (sscanf(params,"u",userid))										return SendHelpMessage(playerid, "/birliktenat [ID / isim]");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (userid == playerid)												return SendErrorMessage(playerid, "Kendini kovamazs�n.");
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Ki�i sizin birli�inizden de�il.");

	if (!isLeader(playerid) && GetUninviteRight(playerid) && (isLeader(userid) || PlayerInfo[userid][pRank] >= PlayerInfo[playerid][pRank]))
	{
		return SendErrorMessage(playerid, "Sizden daha y�ksek yetkili ki�iyi kovamazs�n�z.");
	}

	SendSyntaxMessage(userid, "%s, sizi %s adl� birlikten kovdu.", GetNameEx(playerid), Factions[PlayerInfo[playerid][pFaction]][fName]);
	SendSyntaxMessage(playerid, "%s adl� ki�iyi birlikten kovdun.", GetNameEx(userid));

    RemovePlayerFaction(userid);
	SendFactionMessageF(PlayerInfo[playerid][pFaction], COLOR_LIGHTBLUE, "[Birlik] %s adl� birlik �yesi %s taraf�ndan kovuldu.", GetNameEx(userid), GetNameEx(playerid));
	return 1;
}

alias:birliktenayril("birlikayril", "birliktencik");
CMD:birliktenayril(playerid, params[])
{
    if (PlayerInfo[playerid][pFaction] == 0)						return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n.");
    //if (Factions[PlayerInfo[playerid][pFaction]][fJoinRank] == 0)	return SendErrorMessage(playerid, "Please set join rank in your structure. ");

	ConfirmDialog(playerid, "Do�rulama", "{FFFFFF}\nBirli�inizden ayr�lmak istedi�inize emin misiniz?","FACTION_LEAVING_REQ");
	return 1;
}

alias:birlik("olusum");
CMD:birlik(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if(faction == 0) return SendErrorMessage(playerid, "Birli�iniz bulunmuyor. Kurmak isterseniz: /birlikkur");

	ShowFactionPanel(playerid, faction);
	return 1;
}

CMD:renkler(playerid)
{
	return ShowColourDialog(playerid, 1);
}

alias:birlikler("olusumlar");
CMD:birlikler(playerid, params[])
{
	Faction_List(playerid);
	return 1;
}

alias:birlikkur("olusumkur");
CMD:birlikkur(playerid, params[])
{
	OlusumKurDialog(playerid);
	return 1;
}

CMD:rutbedegistir(playerid, params[])
{
    if (PlayerInfo[playerid][pFaction] == 0)						return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n.");
    if (!isLeader(playerid) && !GetRankRight(playerid))				return SendErrorMessage(playerid, "Birlik �yelerinin r�tbelerini de�i�tirmenize izin verilmez.");
    if (Factions[PlayerInfo[playerid][pFaction]][fJoinRank] == 0)	return SendErrorMessage(playerid, "L�tfen birli�inizdeki dereceleri ayarlay�n.");

	new userid, rank;

	if (sscanf(params,"ui",userid, rank))										return SendHelpMessage(playerid, "/rutbedegistir [ID / isim] [r�tbe]");
	if (!IsPlayerLogged(userid))												return SendNotConnected(playerid);
	if (userid == playerid)														return SendErrorMessage(playerid, "R�tbenizi de�i�tiremezsiniz.");
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])			return SendErrorMessage(playerid, "Oyuncu, kurulu�unuzun bir �yesi de�il.");
	if (rank < 1 || rank > Factions[PlayerInfo[playerid][pFaction]][fRanks])	return SendErrorMessage(playerid, "R�tbe numaras� 1 ile %i aras�nda olmal�.", Factions[PlayerInfo[playerid][pFaction]][fRanks]);
	if (!isLeader(playerid) && GetRankRight(playerid) && (isLeader(userid) || PlayerInfo[userid][pRank] >= PlayerInfo[playerid][pRank]))
	{
		return SendErrorMessage(playerid, "Sadece r�tbe olarak sizden daha d���k s�rada olan bir oyuncunun r�tbesini de�i�tirebilirsiniz.");
	}
	if (PlayerInfo[playerid][pRank] < rank) return SendErrorMessage(playerid, "Bir oyuncuya sizinkinden daha y�ksek bir r�tbe veremezsiniz.");
			 
	PlayerInfo[userid][pRank] = rank;
	SendSyntaxMessage(userid, "%s sizin r�tbenizi '%s' olarak de�i�tirdi.", GetNameEx(playerid), GetRankName(userid));
	SendSyntaxMessage(playerid, "%s adl� ki�inin r�tbesini '%s' olarak ayarlad�n�z.", GetNameEx(userid), GetRankName(userid));	

	SQL_SetInteger("users", "rank", PlayerInfo[userid][pRank], PlayerInfo[userid][pID]);
	return 1;
}

CMD:rutbeler(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], mes[1024] = "{FFFFFF}";

	if (!isLeader(playerid) && !GetRankRight(playerid))	return SendErrorMessage(playerid, "Birlik r�tbelerini g�r�nt�leme iznin yok.");

	for(new i = 0; i != Factions[faction][fRanks]; i++)
	{
		format(mes, sizeof(mes), "%s%i. %s\n", mes, i+1, FactionRanks[faction][i]);
	}

	new title[32];
	format(title, sizeof(title), "{FFFFFF}Birlik r�tbeleri [%i]", Factions[faction][fRanks]);
	Dialog_Show(playerid, None, DIALOG_STYLE_LIST, title, mes, "Kapat", "");
	return 1;
}

alias:editrights("birlikizinleri");
CMD:editrights(playerid, params[])
{
	if (!PlayerInfo[playerid][pFaction])					return SendErrorMessage(playerid, "Herhangi bir birli�e �ye de�ilsiniz.");
	if (!isLeader(playerid) && !GetRightsRight(playerid)) 	return SendErrorMessage(playerid, "Birlik izinlerini d�zenleme yetkin yok.");

	new faction = PlayerInfo[playerid][pFaction];
	
	new	faction_ranks[1024] = EOS;
	for(new i = 0; i != Factions[faction][fRanks]; i++)
	{
		if (PlayerInfo[playerid][pRank] >= i && !isLeader(playerid))
		{
			format(faction_ranks, sizeof(faction_ranks), "%s%i\t%s\n", faction_ranks, i+1, FactionRanks[faction][i]);
		}
		else if (isLeader(playerid))
		{
			format(faction_ranks, sizeof(faction_ranks), "%s%i\t%s\n", faction_ranks, i+1, FactionRanks[faction][i]);
		}
	}
	Dialog_Show(playerid, FactionSettings, DIALOG_STYLE_TABLIST, "{FFFFFF}R�tbe ayarlar�", faction_ranks, ">>>", "�ptal");
	return 1;
}

alias:izinlerim("birlikizinlerim");
CMD:izinlerim(playerid, params[])
{
	if (!PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Herhangi bir birli�e �ye de�ilsiniz.");
	return ShowMyRights(playerid);
}

alias:towcars("birlikrespawn", "frespawn");
CMD:towcars(playerid, params[])
{
	if (!isLeader(playerid) && !GetTowRight(playerid)) return SendErrorMessage(playerid, "Kullan�lmayan ara�lar� respawnlamaya g�ndermenize izin verilmez.");

	new faction = PlayerInfo[playerid][pFaction];

    SendFactionMessageF(faction, COLOR_LIGHTRED, "%s %s, kullan�lmayan t�m birlik ara�lar�n� yeniden canland�rd�.", GetRankName(playerid), GetNameEx(playerid));

    new vehicle, occupied[MAX_VEHICLES char];

    foreach(new i : Player)
	{
	    if ((vehicle = GetPlayerVehicleID(i)) == 0 || VehicleInfo[vehicle][carFaction] != faction) continue;

		occupied{vehicle} = 1;
	}

	foreach(new i : Vehicle)
	{
		if (occupied{i} == 1 || VehicleInfo[i][carFaction] != faction) continue;

        FixVehicle(i);
		RespawnVehicle(i);
	}
	return 1;
}

alias:birlikuyeleri("birlikaktif");
CMD:birlikuyeleri(playerid, params[])
{
	if (PlayerInfo[playerid][pFaction] == 0)	return SendErrorMessage(playerid, "Herhangi bir birli�e �ye de�ilsiniz.");

	new mes[3072] = "{FFFFFF}�sim\t{FFFFFF}ID\t{FFFFFF}R�tbe\t{FFFFFF}Telefon";

	foreach(new i : Player)
	{
		if (IsPlayerLogged(i) == 0 || PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction])	continue;
		format(mes, sizeof(mes), "%s\n%s\t%i\t%s\tNo: %d", mes, GetNameEx(i), i, GetRankName(i), PlayerInfo[i][pNumber]);	
	}

	Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Aktif Birlik �yeleri", mes, "Kapat", "");
	return 1;
}

alias:operator("op");
CMD:operator(playerid, params[])
{
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Yerel sohbetiniz sistem taraf�ndan engellendi.");
    if (!isLeader(playerid) && !GetTowRight(playerid)) return SendErrorMessage(playerid, "R�tbenizin bu komutu kullanmaya yetkisi yok.");	
	if (isnull(params))								    return SendHelpMessage(playerid, "(/op)erator [mesaj]");
	if (!IsFactionLegal(PlayerInfo[playerid][pFaction])) return SendErrorMessage(playerid, "Bu komut, devlet kurumlar� i�in tasarlanm��t�r.");
    if (!PlayerInfo[playerid][pOnDuty])				    return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z. ");

	for(new i = 1; i != MAX_PLAYERS; i++)
	{
	    if (PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction] && !PlayerInfo[i][pOnDuty]) continue;

        if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendClientMessageEx(i, COLOR_LSPD, "[OPERAT�R]: %.*s ...", pos, params);
			SendClientMessageEx(i, COLOR_LSPD, "... %s **", params[pos]);
		}
		else
		{
			SendClientMessageEx(i, COLOR_LSPD, "[OPERAT�R]: %s **", params);
		}
	}
	return 1;
}

alias:departman("d");
CMD:departman(playerid, params[])
{
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Yerel sohbetiniz sistem taraf�ndan engellendi.");

	new faction[23];

	if (isnull(params))								    return SendHelpMessage(playerid, "(/d)epartman [mesaj]");
	if (!IsFactionLegal(PlayerInfo[playerid][pFaction])) return SendErrorMessage(playerid, "Birlik, devlet kurumlar� i�in tasarlanm��t�r.");
    if (!PlayerInfo[playerid][pOnDuty])				    return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z. ");

	format(faction, sizeof(faction), "%s", Factions[PlayerInfo[playerid][pFaction]][fShortName]);

	for(new i = 1; i != MAX_FACTIONS; i++)
	{
	    if (Factions[i][fON] == 0 || !IsFactionLegal(i)) continue;

        if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendFactionMessage(i, COLOR_ALLDEPT, "** [%s] %s %s: %.*s ...", faction, GetRankName(playerid), GetNameWithMask(playerid), pos, params);
			SendFactionMessage(i, COLOR_ALLDEPT, "... %s **", params[pos]);
		}
		else
		{
			SendFactionMessage(i, COLOR_ALLDEPT, "** [%s] %s %s: %s **", faction, GetRankName(playerid), GetNameWithMask(playerid), params);
		}
	}
	return 1;
}

alias:faction("f");
CMD:faction(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
    
	if (PlayerInfo[playerid][pMutedTime] > 0)						return SendErrorMessage(playerid, "Yerel sohbetiniz sistem taraf�ndan engellendi.");
	if (isnull(params))												return SendHelpMessage(playerid, "(/f)action [OOC chat]");
	if (PlayerInfo[playerid][pFaction] == 0)						return SendErrorMessage(playerid, "Herhangi bir birlikte olmal�s�n. ");
	if (Factions[faction][fChatON] == 0 && !isLeader(playerid))		return SendErrorMessage(playerid, "OOC birlik sohbeti devre d��� b�rak�ld�.");
	if (PlayerInfo[playerid][pSettings] & togFaction)				return SendErrorMessage(playerid, "Birlik mesajlar�n�n g�r�nt�lenmesini devre d��� b�rakm��s�n�z. (/ayarlar)");

	if (IsFactionLegal(faction))
	{
		if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] %s %s: %.*s ...", GetRankName(playerid), GetNameEx(playerid), pos, params);
			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] ... %s", params[pos]);
		}
		else
		{
			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] %s %s: %s", GetRankName(playerid), GetNameEx(playerid), params);
		}
	}
	else
	{
		if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] ... %s", params[pos]);
		}
		else
		{
			SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[Birlik] %s: %s", GetNameEx(playerid), params);
		}
	}
	return 1;
}

alias:birlikaksesuar("birlikaksesuarlari");
CMD:birlikaksesuar(playerid, params[])
{
	if (GetNextToySlot(playerid) == -1)	return SendErrorMessage(playerid, "T�m aksesuar slotlar� dolu.");

	
	if (!IsFactionLegal(PlayerInfo[playerid][pFaction])) return 1;

    if (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid))
	{
		new mes[sizeof(attach_fd_model)*64];
		for(new i = 0; i < sizeof(attach_fd_model); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t~w~%s\n", mes, attach_fd_model[i], attach_fd_name[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_FA, DIALOG_STYLE_PREVIEW_MODEL, "Birlik Aksesuarlar�", mes, "Sec", "Kapat");
	}			
    else if (IsPlayerFactionCity(playerid))
	{
		new mes[sizeof(attach_city_model)*64];
		for(new i = 0; i < sizeof(attach_city_model); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t~w~%s\n", mes, attach_city_model[i], attach_city_name[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_FA, DIALOG_STYLE_PREVIEW_MODEL, "Birlik Aksesuarlar�", mes, "Sec", "Kapat");
	}
	else if (IsPlayerFactionPolice(playerid))
	{
		new mes[sizeof(attach_police_model)*64];
		for(new i = 0; i < sizeof(attach_police_model); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t~w~%s\n", mes, attach_police_model[i], attach_police_name[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_FA, DIALOG_STYLE_PREVIEW_MODEL, "Birlik Aksesuarlar�", mes, "Sec", "Kapat");
	}

	return 1;
}

CMD:rozetbelirle(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (Factions[faction][fType] == FACTION_MAFIA || Factions[faction][fType] == FACTION_GANG)	return SendErrorMessage(playerid, "Bir h�k�met olu�umu lideri olmal�s�n.");
	if (PlayerInfo[playerid][pRank] < 11)														return SendErrorMessage(playerid, "Ge�ersiz r�tbe.");

    new userid, badge;
        
    if (sscanf(params, "ui", userid, badge))													return SendHelpMessage(playerid, "/rozetbelirle [ID / isim] [numara]");
    if (!IsPlayerLogged(userid))																return SendNotConnected(playerid);
	if (badge < 1 || badge > 9999999)															return SendErrorMessage(playerid, "Rozet numaras� 1 ile 9999999 aras�nda olmal�d�r. ");

	PlayerInfo[userid][pBadgeNumber] = badge;
	SendSyntaxMessage(playerid, "%s adl� ki�inin rozet numaras�n� de�i�tirdin [%i].", GetNameEx(userid), badge);
	SendSyntaxMessage(userid, "%s rozet numaran� de�i�tirdi [%i].", GetNameEx(playerid), badge);
	return 1;
}

CMD:aractamir(playerid,params[])
{
	if (IsPlayerAtCarfix(playerid) == 0) return SendErrorMessage(playerid, "Ara� tamir noktas�nda de�ilsiniz.");

	new vehicle = GetPlayerVehicleID(playerid);

	if (!vehicle || VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Birlik arac�nda de�ilsiniz.");
		
	FixVehicle(vehicle);
	VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
	SendSyntaxMessage(playerid, "Ara� tamamen tamir edildi.");
	return 1;
}

alias:barikatliste("engeller", "barikatlar");
CMD:barikatliste(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))		return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru / sa�l�k g�revlisi olmal�s�n�z.");
    if (IsPlayerInAnyVehicle(playerid))	return SendErrorMessage(playerid, "Bu i�lem i�in ara�ta olmamal�s�n. ");
    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z. ");

    new count, str[512] = "- T�m barikatlar� kald�r\n";

    for (new i = 0; i != MAX_BORTES; i ++)
	{
		if (BortInfo[playerid][i][bortOn] == 0) continue;

        format(str, sizeof(str), "%s%i: %s\n", str, i+1, BortInfo[playerid][i][bortName]);
        count++;
	}

	if (!count) return SendErrorMessage(playerid, "Olu�turulmu� yol nesneniz yok.");

	Dialog_Show(playerid, BortList, DIALOG_STYLE_LIST, "{FFFFFF}Barikat Listesi", str, "Se�", "�ptal");
	return 1;
}

alias:barikat("engel");
CMD:barikat(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");
		
    new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))		return SendErrorMessage(playerid, "Bu komutu kullanma yetkiniz yok.");
    if (IsPlayerInAnyVehicle(playerid))	return SendErrorMessage(playerid, "Bu i�lem i�in ara�ta olmamal�s�n.");
    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z.");

	if (IsFactionMedic(faction) || IsFactionFire(faction))
    {
		new mes[sizeof(bort_list_fd)*128];
		for(new i = 0; i < sizeof(bort_list_fd); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t%s\n", mes, bort_list_fd[i], bort_names_fd[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_BORT, DIALOG_STYLE_PREVIEW_MODEL, "_", mes, "Sec", "Kapat");
	}
	else if (IsFactionCity(faction))
	{
		new mes[sizeof(bort_list_city)*128];
		for(new i = 0; i < sizeof(bort_list_city); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t%s\n", mes, bort_list_city[i], bort_names_city[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_BORT, DIALOG_STYLE_PREVIEW_MODEL, "_", mes, "Sec", "Kapat");
	}
	else
	{
		new mes[sizeof(bort_list)*128];
		for(new i = 0; i < sizeof(bort_list); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 0.0, 1.0)\t%s\n", mes, bort_list[i], bort_names[i]); 
		}
		Dialog_Show(playerid, MODEL_SELECTION_BORT, DIALOG_STYLE_PREVIEW_MODEL, "_", mes, "Sec", "Kapat");
	}

	return 1;
}

CMD:senaryo(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");
		
    new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))		return SendErrorMessage(playerid, "Bu komutu kullanma yetkiniz yok.");

    new opt[6], str[90];

    if(sscanf(params, "s[6]S()[90]", opt, str))
        return SendSyntaxMessage(playerid, "/senaryo [liste/ekle/sil]");

    if(!strcmp(opt, "liste", true))
    {
        mysql_tquery(dbHandle, GetScenario("game_scenarios.id, users.name, game_scenarios.placed_date, game_scenarios.x, game_scenarios.y", "INNER JOIN users ON users.id = game_scenarios.placed_by"), "ListScenarios", "d", playerid);
    }

    else if(!strcmp(opt, "ekle", true))
    {
        new message[90];

        if(sscanf(str, "s[90]", message))
            return SendSyntaxMessage(playerid, "/senaryo <ekle> [senaryo mesaj�]");

        new interior, world, Float:x, Float:y, Float:z;

        interior = GetPlayerInterior(playerid);
        world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, x, y, z);

        mysql_tquery(dbHandle, EditScenario(0, PlayerInfo[playerid][pID], gettime(), message, Text3D:-1, interior, world, x, y, z), "OnPlayerCreateScenario", "d", playerid);
    }

    else if(!strcmp(opt, "sil", true))
    {
        new id;

        if(sscanf(str, "d", id))
            return SendSyntaxMessage(playerid, "/senaryo <sil> [senaryo numaras�]");

        if(id < 1)
            return SendErrorMessage(playerid, "Ge�ersiz senaryo numaras� girdiniz.");

        mysql_tquery(dbHandle, GetScenario("game_scenarios.label_id", "", "", id), "OnPlayerDeleteScenario", "dd", playerid, id);
    }

    return 1;
}
alias:senaryo("senaryoekle", "senaryosil", "senaryoduzenle");

alias:megafon("m");
CMD:megafon(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], text[144];

	if (sscanf(params, "s[144]", text))                                                     return SendHelpMessage(playerid, "(/m)egafon[mesaj]"); 
    if (!IsFactionLegal(faction))															return SendErrorMessage(playerid, "Herhangi bir devlet kurumuna �ye de�ilsin.");

	if(IsPlayerInAnyVehicle(playerid)) SendNearbyMessage(65.0, playerid, COLOR_YELLOWG, "[ o< %s: %s ]", GetNameWithMask(playerid), text);
	else SendNearbyMessage(60.0, playerid, COLOR_YELLOWG, "(El Megafonu) %s: %s", GetNameWithMask(playerid), text);
	return 1;
}

CMD:m1(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionLegal(faction))															return SendErrorMessage(playerid, "Herhangi bir devlet kurumuna �ye de�ilsin.");
	new Float:pXaz, Float:pYaz, Float:pZaz, string[100];
	GetPlayerPos(playerid, pXaz, pYaz, pZaz);
	format(string, sizeof(string), "[ %s: o< Liberty City Polis Departman�, oldu�un yerde kal! ]", GetNameEx(playerid));
	SendLocalMessage(45.0, playerid, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, string);
	PlaySoundEx(15800, pXaz, pYaz, pZaz, 40);
	return 1;
}

CMD:m2(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
    if (!IsFactionLegal(faction))															return SendErrorMessage(playerid, "Herhangi bir devlet kurumuna �ye de�ilsin.");	
	new Float:pXaz, Float:pYaz, Float:pZaz, string[100];
	GetPlayerPos(playerid, pXaz, pYaz, pZaz);
	format(string,sizeof(string), "%s(ba��rarak): Ellerin ba��n�n �st�nde kalacak �ekilde ara�tan in!", GetNameEx(playerid));
	SendLocalMessage(Range_Long, playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string);
	PlaySoundEx(34403, pXaz, pYaz, pZaz, 30);
	return 1;
}

CMD:m3(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionLegal(faction))															return SendErrorMessage(playerid, "Herhangi bir devlet kurumuna �ye de�ilsin.");
	new Float:pXaz, Float:pYaz, Float:pZaz, string[100];
	GetPlayerPos(playerid, pXaz, pYaz, pZaz);
	format(string,sizeof(string), "%s(ba��rarak): Hey sen! Dur polis!", GetNameEx(playerid));
	SendLocalMessage(Range_Long, playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string);
	PlaySoundEx(10200, pXaz, pYaz, pZaz, 30);
	return 1;
}

CMD:m4(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionLegal(faction))															return SendErrorMessage(playerid, "Herhangi bir devlet kurumuna �ye de�ilsin.");
	new Float:pXaz, Float:pYaz, Float:pZaz, string[100];
	GetPlayerPos(playerid, pXaz, pYaz, pZaz);
	format(string,sizeof(string), "%s(ba��rarak): Oldu�un yerde kal, yoksa ate� a�aca��z!", GetNameEx(playerid));
	SendLocalMessage(Range_Long, playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string);
	PlaySoundEx(15801, pXaz, pYaz, pZaz, 30);
	return 1;
}

CMD:pdkisayol(playerid, params[])
{
	SendClientMessage(playerid, COLOR_FADE1, "(( {90EE90}_______________(KISAYOL KOMUTLARI)_______________ {E6E6E6}))");
	SendClientMessage(playerid, COLOR_GREEN, "(( {FFFFFF}/m1: Liberty City Polis Departman�, oldu�un yerde kal! (This is LSPD, stay where you're){90EE90} ))");
	SendClientMessage(playerid, COLOR_GREEN, "(( {FFFFFF}/m2: Ellerin ba��n�n �st�nde kalacak �ekilde ara�tan in! (Get outta the car with your hands in the air!){90EE90} ))");
	SendClientMessage(playerid, COLOR_GREEN, "(( {FFFFFF}/m3: Hey sen! Dur polis! (Hey you, police. Stop!){90EE90} ))");
	SendClientMessage(playerid, COLOR_GREEN, "(( {FFFFFF}/m4: Oldu�un yerde kal, yoksa ate� a�aca��z! (Freeze, or we'll open fire!){90EE90} ))");
	return 1;
}

CMD:mdc(playerid, params[])
{	
	if (IsPlayerPhoneCreated(playerid))	return SendErrorMessage(playerid, "Telefonu kapatmal�s�n!");

	if (!IsPlayerFactionPolice(playerid) &&
		!IsPlayerFactionMedic(playerid) &&
		!IsPlayerFactionFire(playerid))	return SendErrorMessage(playerid, "H�k�met �yesi olmal�s�n�z.");

	new id = PlayerInfo[playerid][pFaction];

	if (IsPlayerFactionPolice(playerid))
	{
		if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z.");

		if (IsPlayerUseMDC(playerid))
			return MDC_Hide(playerid);

		if (pTemp[playerid][pCCTV])
			return 1;

		MdcInfo[playerid][mdcPage] = PAGE_NONE;

		MDC_Show(playerid);

		SelectTextDraw(playerid, 255);
		return 1;
	}

	if (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid))
	{
		if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z. ");
		
		return Get_Calls(playerid);
	}
	return 1;
}

CMD:rozetgoster(playerid, params[])
{
	new userid;
	
	if (!PlayerInfo[playerid][pFaction] || !IsFactionLegal(PlayerInfo[playerid][pFaction]))	return SendErrorMessage(playerid, "Bir h�k�met birli�inde de�ilsin. ");
	if (sscanf(params, "u", userid))														return SendHelpMessage(playerid, "/rozetgoster [ID / isim]");
	if (!IsPlayerLogged(userid))															return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))											return SendNotNearPlayer(playerid);

	SCM(userid, COLOR_POLICECHAT, "_______________________");
	SendClientMessageEx(userid, COLOR_WHITE, Factions[PlayerInfo[playerid][pFaction]][fName]);
	SendClientMessageEx(userid, COLOR_WHITE, "%s - %s", GetRankName(playerid), GetNameWithMask(playerid));
	SendClientMessageEx(userid, COLOR_WHITE, "Rozet Numaras�: %i", PlayerInfo[playerid][pBadgeNumber]);
	SCM(userid, COLOR_POLICECHAT, "_______________________");

	SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s, %s adl� ki�iye rozetini g�sterir.", GetNameWithMask(playerid), GetNameWithMask(userid));
	return 1;
}

CMD:aracaat(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], vehicle = GetNearVehicle(playerid, 5.0), userid, seat;

	if (!IsPlayerFactionPolice(playerid) &&
		!IsPlayerFactionMedic(playerid) &&
		!IsPlayerFactionFire(playerid))						return SendErrorMessage(playerid, "Legal olu�um �yesi olmal�s�n. ");
    if (!vehicle || IsABoat(vehicle) || IsABiker(vehicle))	return SendErrorMessage(playerid, "Ara� i�erisinde olmal�s�n. ");

	new maxseat = GetMaxPassengers(GetVehicleModel(vehicle));

	if (sscanf(params,"ud", userid, seat))			return SendHelpMessage(playerid, "/aracaat [ID / isim] [koltuk (1-%i)]", maxseat);
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (seat > maxseat || seat < 1)					return SendSyntaxMessage(playerid, "Koltuk numaras� 1 ile %i aras�nda olmal�d�r.", maxseat);
	if (userid == playerid)							return 1;
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (PlayerInfo[userid][pInjured])				return SendErrorMessage(playerid, "Yaral�lar� ara�la ta��yamazs�n�z.");
	if (IsPlayerInAnyVehicle(userid))				return SendErrorMessage(playerid,"Oyuncu ara�ta.");
    if (!PutPlayerInVehicle(userid, vehicle, seat))	return SendErrorMessage(playerid, "Oyuncu araca bindirilemedi.");

	if (IsFactionMedic(faction) || IsFactionFire(faction))
	{
		StopPlayerAnims(userid);
		SendSyntaxMessage(playerid, "%s adl� ki�iyi bir araca bindirdiniz.", GetNameEx(userid));
		SendSyntaxMessage(userid, "%s sizi ambulansa s�r�kledi.", GetNameEx(playerid));
	}
	else
	{
	    SendSyntaxMessage(playerid, "%s adl� ki�iyi bir araca s�r�klediniz.", GetNameEx(userid));
		SendSyntaxMessage(userid, "%s sizi bir araca s�r�kledi.", GetNameEx(playerid));
	}
	PutPlayerInVeh(userid, vehicle, seat);
	return 1;
}

/*
CMD:pullout(playerid, params[])
{
	//new faction = PlayerInfo[playerid][pFaction], vehicle = GetPlayerVehicleID(playerid), userid, seat;
	//if (faction != LSPD && faction != SASD && faction != LSFD)	return SendErrorMessage(playerid, "�� ������ ���� �����������/�����������.");

	new userid;

	if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/pullout [ID / isim]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (userid == playerid)							return 1;
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (!IsPlayerInAnyVehicle(userid))				return SendErrorMessage(playerid, "����� �� ��������� � ����������.");
	if (PlayerInfo[userid][pInjured] == 0 &&
		pTemp[userid][pTaserTime] == 0)				return SendErrorMessage(playerid, "����� �� �����/�����/�����������.");
	
	new vehid = GetPlayerVehicleID(userid);
	if (VehicleInfo[vehid][carLock] != 0)			return SendErrorMessage(playerid, "�� �������. ����������� /ram !");

	new mes[128];
	format(mes, sizeof(mes), "������� %s �� ����������.", GetNameWithMask(userid));
	pc_cmd_me(playerid, mes);
	
	SavePlayerPos(playerid);

	SetPlayerPosEx(userid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	SavePlayerPos(userid);

	ApplyAnimation(userid, "PED", "KO_SHOT_STOM", 4.0, 1, 0, 0, 0, 0, 1);

	UnFreezePlayer(userid);
	return 1;
}*/