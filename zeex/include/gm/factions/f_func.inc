this::LoadDynamicFactions()
{
	new rows = cache_num_rows(), time = GetTickCount(), total, id;

	if (!rows)
	{
	    print("[Birlik] Kayit bulunamadi.");
	    return 1;
	}

    mysql_tquery(dbHandle, "SELECT id FROM game_scenarios", "LoadScenarios");

	for(new i = 0; i < rows; i++)
	{	
	    cache_get_value_int(i, "factionid", id);
		Factions[id][fON] = 1;
		cache_get_value_int(i, "id", Factions[id][fID]);
		cache_get_value(i, "name", Factions[id][fName], 32);
		cache_get_value(i, "shortname", Factions[id][fShortName], 8);
		cache_get_value_float(i, "spawnx", Factions[id][fPosX]);
		cache_get_value_float(i, "spawny", Factions[id][fPosY]);
		cache_get_value_float(i, "spawnz", Factions[id][fPosZ]);
		cache_get_value_int(i, "spawnint", Factions[id][fSpawnInt]);
		cache_get_value_int(i, "spawnvw", Factions[id][fSpawnVW]);
		cache_get_value_int(i, "joinrank", Factions[id][fJoinRank]);
		cache_get_value_int(i, "type", Factions[id][fType]);
		Factions[id][fRanks] = 20;

		for(new j = 0; j < 20; j++)
		{
			new field_name[32], temp[128];
			format(field_name, sizeof(field_name), "rank%i", j+1);

	        cache_get_value_name(i, field_name, temp, 128);
	        sscanf(temp, "p<,>iiiiiiiiis[32]",
			FRank[id][j][rInvite], FRank[id][j][rUninvite], FRank[id][j][rRank],
	        FRank[id][j][r_eRank], FRank[id][j][rSpawn], FRank[id][j][rChat], FRank[id][j][rTow],
	        FRank[id][j][rBodyCam], FRank[id][j][r_eRights], FactionRanks[id][j]);		
		}		

		cache_get_value_int(i, "chaton", Factions[id][fChatON]);
		cache_get_value_int(i, "color", Factions[id][fColor]);
		cache_get_value_int(i, "point", Factions[id][fPoint]);
		cache_get_value_int(i, "point_time", Factions[id][fPointTime]);

		//mysql_tquery(dbHandle, sprintf("SELECT * FROM factions WHERE factionid = %d", id), "LoadFactionRanks");

		if (IsFactionLegal(id)) {		
			cache_get_value_float(i, "fix_X", Factions[id][Carfix][fixX]);
			cache_get_value_float(i, "fix_Y", Factions[id][Carfix][fixY]); 
			cache_get_value_float(i, "fix_Z", Factions[id][Carfix][fixZ]);
			cache_get_value_int(i, "fix_Int", Factions[id][Carfix][fixInt]);
			cache_get_value_int(i, "fix_VW", Factions[id][Carfix][fixVW]);

			if (Factions[id][Carfix][fixX]) Factions[id][Carfix][fixPickUp] = CreateDynamicPickup(1650, 1, Factions[id][Carfix][fixX], Factions[id][Carfix][fixY], Factions[id][Carfix][fixZ], Factions[id][Carfix][fixVW], Factions[id][Carfix][fixInt], -1, 20.0);
		}

		total++;
	}
	printf("[Birlikler] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

RemovePlayerFaction(userid)
{
    if (pTemp[userid][pPatrol])
	{
	    new id = pTemp[userid][pPatrol]-1;
	    pTemp[userid][pPatrol] = 0;

        if (PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][0] == userid) PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][0] = INVALID_PLAYER_ID;
        if (PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][1] == userid) PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;
		if (PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][0] == INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(userid)][id][patrulOfficer][0] == INVALID_PLAYER_ID)
		{
		    PatrolInfo[GetPatrolID(userid)][id][patrulExists] = 0;
		}
	}

	if (PlayerInfo[userid][pOnDuty])
	{
		if (IsPlayerAttachedObjectSlotUsed(userid, 5))	RemovePlayerAttachedObject(userid, 5);
		if (IsPlayerAttachedObjectSlotUsed(userid, 6))	RemovePlayerAttachedObject(userid, 6);
		if (IsPlayerAttachedObjectSlotUsed(userid, 7))	RemovePlayerAttachedObject(userid, 7);

        SetPlayerArmour(userid, 0.0);
		Save_User(userid);
	}

    SetRadioChannel(userid, 0);
	SetRadioSlot(userid, 0);

    for(new i; i < 5; i++) PlayerInfo[userid][pOlusumDivision][i] = 0;

	PlayerInfo[userid][pFaction] = 0;
	PlayerInfo[userid][pRank] = 0;
	PlayerInfo[userid][pBadgeNumber] = 0;
	PlayerInfo[userid][pOnDuty] = false;
	PlayerInfo[userid][pSwatDuty] = false;
	PlayerInfo[userid][pAuthwep] = 0;
	PlayerInfo[userid][pSwat] = 0;
	PlayerInfo[userid][pSideJob] = 0;
	PlayerInfo[userid][pChar] = 0;

	SQL_SetInteger("users", "faction", PlayerInfo[userid][pFaction], PlayerInfo[userid][pID]);
	SQL_SetInteger("users", "rank", PlayerInfo[userid][pRank], PlayerInfo[userid][pID]);

	SetPlayerSkin(userid, PlayerInfo[userid][pSkin]);

    if (IsAdminDuty(userid))	SetPlayerColor(userid, COLOR_BREEZEADMIN);
	else							SetPlayerColor(userid, TEAM_HIT_COLOR);
	
	return 1;
}

isLeader(playerid)
{
	return PlayerInfo[playerid][pFaction] != 0 && PlayerInfo[playerid][pRank] == Factions[PlayerInfo[playerid][pFaction]][fRanks] ? 1 : 0;
}

/*
stock SendFactionMessageF(faction, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != faction || (PlayerInfo[i][pSettings] & togFaction))
				continue;

			SendClientMessage(i, color, string);
		}

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN
		return 1;
	}

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != faction || (PlayerInfo[i][pSettings] & togFaction))
			continue;

		SendClientMessage(i, color, str);
	}
	return 1;
}

stock SendFactionMessage(faction, color, const str[], {Float,_}:...)
{
	printf("sf 0");
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	printf("sf 1");
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	printf("sf 2 : args = %i", args);
	
	if (args > 12)
	{
		printf("sf > args > 12");

		#emit ADDR.pri str
		#emit STOR.pri start

		printf("sf > 01");

		printf("\n\nfor (end = start + (args - 12); end > start; end -= 4)");
		printf("start = %i", start);
		printf("for (end = %i; end > %i; end -= 4)", start + (args - 12), start);
		
	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}

		printf("sf > 02");

		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		printf(">> sf foreach start");
		//foreach(new i : Player)
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			printf(">> sf foreach: %i", i);
		    if (!IsPlayerLogged(i) || PlayerFactionType(i) != faction || 0 == PlayerInfo[i][pOnDuty])
				continue;

			printf(">> sf foreach: message for %i", i);
			SendClientMessage(i, color, string);
		}

		printf("sf > 03");

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN

		printf(">>>>> sf > end");
		return 1;
	}

	printf("sf foreach start");

	foreach(new i : Player)
	{
		printf("sf foreach: %i", i);
	    if (!IsPlayerLogged(i) || PlayerFactionType(i) != faction || 0 == PlayerInfo[i][pOnDuty])
			continue;
		
		printf("sf foreach: message for %i", i);
		SendClientMessage(i, color, str);
	}
	
	printf("end");
	return 1;
}
*/

SendFactionMessageF(factiontype, color, const str[], {Float,_}:...)
{
    static args, start, end, string[144];
 
    #emit LOAD.S.pri 8
    #emit STOR.pri args
 
    if (args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start
 
        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4
 
        foreach(Player, i)
        {
            if(!IsPlayerLogged(i) || Factions[PlayerInfo[i][pFaction]][fType] != factiontype || (PlayerInfo[i][pSettings] & togFaction)) continue;
 
            SendClientMessage(i, color, string);
        }
        return 1;
    }
 
    foreach(Player, i)
    {
		if(!IsPlayerLogged(i) || Factions[PlayerInfo[i][pFaction]][fType] != factiontype || (PlayerInfo[i][pSettings] & togFaction)) continue;
 
		SendClientMessage(i, color, str);
    }
    return 1;
}
 
SendFactionMessage(faction, color, const str[], {Float,_}:...)
{
    static args, start, end, string[144];
 
    #emit LOAD.S.pri 8
    #emit STOR.pri args
 
    if (args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start
 
        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4
 
        foreach(Player, i)
        {
            if(!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != faction) continue;
 
            SendClientMessage(i, color, string);
        }
        return 1;
    }
 
    foreach(Player, i)
    {
        if(!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != faction) continue;
 
        SendClientMessage(i, color, str);
    }
    return 1;
}

stock SendPhoneMessageEx(target, color, const str[], {Float,_}:...)
{
    static args, start, end, string[144];
 
    #emit LOAD.S.pri 8
    #emit STOR.pri args
 
    if (args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start
 
        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4
 
        foreach(Player, i)
        {
            if(!IsPlayerLogged(i) || pTemp[i][pTracePlayer] != target || i != target) continue;
 
            SendClientMessage(i, color, string);
        }
        return 1;
    }
 
    foreach(Player, i)
    {
        if(!IsPlayerLogged(i) || pTemp[i][pTracePlayer] != target || i != target) continue;
 
        SendClientMessage(i, color, str);
    }
    return 1;
}

CreateFactionVehicle(bool: crt, model, Float: x, Float: y, Float: z, Float: a, color1, color2, type, faction, plate[], vw, interior, sqlid = 0)
{
	new vehicle;

    if (IsFactionLegal(faction))					vehicle = CreateVehicle(model, x, y, z, a, color1, color2, -1, 1);
 	else											vehicle = CreateVehicle(model, x, y, z, a, color1, color2, -1);

    if (vehicle == INVALID_VEHICLE_ID)				return 0;

	SetVehicleHealth(vehicle, 1000.0);
	SetVehicleNumberPlate(vehicle, plate);
 	SetVehicleVirtualWorldEx(vehicle, vw);
	SetVehicleInteriorEx(vehicle, interior);

	VehicleInfo[vehicle][carModel] = model;
	VehicleInfo[vehicle][carParkX] = x;
	VehicleInfo[vehicle][carParkY] = y;
	VehicleInfo[vehicle][carParkZ] = z;
	VehicleInfo[vehicle][carParkA] = a;
	VehicleInfo[vehicle][carColor1] = color1;
	VehicleInfo[vehicle][carColor2] = color2;
	VehicleInfo[vehicle][carType] = type;
	VehicleInfo[vehicle][carFaction] = faction;
	VehicleInfo[vehicle][carVW] = vw;
	VehicleInfo[vehicle][carInt] = interior;
    VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
    VehicleInfo[vehicle][carDriver] = INVALID_PLAYER_ID;
	VehicleInfo[vehicle][carBattery] = 100.00;
	VehicleInfo[vehicle][carEngine] = 100.00;

	VehicleLight(vehicle, false);
    
	format(VehicleInfo[vehicle][carPlate], 24, plate);

	if (crt)
	{
	    new query[128 + 256];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `cars` (`date`,`model`,`x`,`y`,`z`,`fa`,`color1`,`color2`,`type`,`faction`,`plate`,`vw`,`int`) VALUES ('%s',%i, %f, %f, %f, %f, %i, %i, %i, %i, '%e', %i, %i)",
		GetFullDate(), model, x, y, z, a, color1, color2, type, faction, plate, vw, interior);
		mysql_tquery(dbHandle, query, "OnVehicleInsert", "d", vehicle);
	}
	else VehicleInfo[vehicle][carID] = sqlid;
	
	return vehicle;
}

IsPlayerAtSecondUniform(playerid)
{
	new vehicle;
	if ((vehicle = GetPlayerVehicleID(playerid)) == 0) return 0;
	    

	if (IsPlayerFactionPolice(playerid) && GetVehicleModel(vehicle) == 427) return 1;
	else if (IsPlayerFactionMedic(playerid) && IsFactionMedic(VehicleInfo[vehicle][carFaction])) return 1;
	else if (IsPlayerFactionFire(playerid) && IsFactionFire(VehicleInfo[vehicle][carFaction])) return 1;

	return 0;
}

DestroyAllBort(playerid)
{
	for(new i; i < MAX_BORTES; i++)
	{
	    if (BortInfo[playerid][i][bortOn] == 0) continue;

        BortInfo[playerid][i][bortOn] = 0;
		BortInfo[playerid][i][bortUsing] = 0;
		BortInfo[playerid][i][bortName] = EOS;
		
	    if (IsValidDynamicObject(BortInfo[playerid][i][bortObject])) DestroyDynamicObject(BortInfo[playerid][i][bortObject]);
       		
       	BortInfo[playerid][i][bortObject] = INVALID_OBJECT_ID;
	}
	return 1;
}

AddFactionToFile(factionid, shortname[], name[], color, type, ranks, pointtime, joinrank = 1)
{
    new query[999];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `factions` (factionid,shortname,name,color,type,ranks,point_time,joinrank) VALUES (%i,'%s','%s',%i,%i,%i,%i, %i)", factionid, shortname, name, color, type, ranks, pointtime, joinrank);
	mysql_tquery(dbHandle, query, "FactionInsertId", "i", factionid);
	return 1;
}

this::FactionInsertId(factionid)
{
	Factions[factionid][fID] = cache_insert_id();
	return 1;
}

UpdateFactionRankLeader(FactionID)
{
	new query[777];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `factions` SET `rank20` = '1,1,1,1,1,1,1,1,1,Lider' WHERE `factionid` = %i", FactionID);
	mysql_tquery(dbHandle, query);
	return 1; 
}

Save_Faction(factionid)
{

    new query[1024];
    mysql_format(dbHandle, query, sizeof(query),
       "UPDATE `factions` SET `shortname`='%s',`name`='%s',`spawnx`=%f,`spawny`=%f,`spawnz`=%f,`joinrank`=%d,`type`=%d,`ranks`=%d,`chaton`=%d,`color`=%d,`spawnvw`=%d,`point`=%d,`point_time`=%d, `spawnint`=%d WHERE `id` = %d",
        Factions[factionid][fShortName], Factions[factionid][fName], Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ],
        Factions[factionid][fJoinRank], Factions[factionid][fType], Factions[factionid][fRanks], Factions[factionid][fChatON], Factions[factionid][fColor], Factions[factionid][fSpawnVW], Factions[factionid][fPoint], Factions[factionid][fPointTime], Factions[factionid][fSpawnInt],
        Factions[factionid][fID]);
    mysql_tquery(dbHandle, query);

    mysql_format(dbHandle, query, sizeof(query),
        "UPDATE `factions` SET `uniform_x`=%d,`uniform_y`=%d,`uniform_z`=%f,`uniform_vw`=%d,`uniform_int`=%d WHERE `id` = %d",
        Factions[factionid][fUniformX], Factions[factionid][fUniformY], Factions[factionid][fUniformZ], Factions[factionid][fUniformVW], Factions[factionid][fUniformInt],
        Factions[factionid][fID]);
    mysql_tquery(dbHandle, query);

    for (new j = 0; j < 20; j++)
    {
        UpdateFactionRank(j);
    }
    
    return 1;
}



UpdateFactionRank(FactionID, Rank)
{
	new query[777], update_string[444];
	format(update_string, sizeof(update_string), "%i,%i,%i,%i,%i,%i,%i,%i,%i,%s", 
	FRank[FactionID][Rank-1][rInvite], FRank[FactionID][Rank-1][rUninvite], FRank[FactionID][Rank-1][rRank], FRank[FactionID][Rank-1][r_eRank],
	FRank[FactionID][Rank-1][rSpawn], FRank[FactionID][Rank-1][rChat], FRank[FactionID][Rank-1][rTow], FRank[FactionID][Rank-1][rBodyCam], 
	FRank[FactionID][Rank-1][r_eRights], FactionRanks[FactionID][Rank-1]);
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `factions` SET `rank%i` = '%s' WHERE `factionid` = %i", Rank, update_string, FactionID);
	mysql_tquery(dbHandle, query);
	return 1; 
}

ShowRightsForRank(playerid, listitem)
{
	new faction_rights[750] = "{FFFFFF}Ýzin\tEriþim\tKomut";
	new right[9][16], faction = PlayerInfo[playerid][pFaction];

	if (FRank[faction][listitem][rInvite])		format(right[0], 16, "%s", RIGHT_YES);
	else 										format(right[0], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][rUninvite])	format(right[1], 16, "%s", RIGHT_YES);
	else										format(right[1], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][rRank])		format(right[2], 16, "%s", RIGHT_YES);
	else 										format(right[2], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][r_eRank])		format(right[3], 16, "%s", RIGHT_YES);
	else 										format(right[3], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][rSpawn])		format(right[4], 16, "%s", RIGHT_YES);
	else 										format(right[4], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][rChat])		format(right[5], 16, "%s", RIGHT_YES);
	else										format(right[5], 16, "%s", RIGHT_NO);

	if (FRank[faction][listitem][rTow])			format(right[6], 16, "%s", RIGHT_YES);
	else 										format(right[6], 16, "%s", RIGHT_NO);

    if(IsFactionLegal(faction))
	{
	    if (FRank[faction][listitem][rBodyCam])		format(right[7], 16, "%s", RIGHT_YES);
	    else 										format(right[7], 16, "%s", RIGHT_NO);

	    if (FRank[faction][listitem][r_eRights])	format(right[8], 16, "%s", RIGHT_YES);
	    else 										format(right[8], 16, "%s", RIGHT_NO);
	}	

	for(new i = 0; i < 9; i++)
	{
		format(faction_rights, sizeof(faction_rights), "%s\n%s\t%s\t%s", faction_rights, RS[i][right_name], right[i], RS[i][right_cmd]);
	}

	new title[32];
	format(title, sizeof(title), "{9189EF}%s", FactionRanks[faction][listitem]);
	SetPVarInt(playerid, "Faction:RankEdit", listitem+1);

	Dialog_Show(playerid, FactionSettings_Set, DIALOG_STYLE_TABLIST_HEADERS, title, faction_rights, "Düzenle", "Geri");
	
	return 1;
}

ShowMyRights(playerid)
{
	new faction_rights[750] = "{FFFFFF}Ýzin\tEriþim\tVar/Yok";
	new right[9][16], faction = PlayerInfo[playerid][pFaction], rank = PlayerInfo[playerid][pRank]-1;

	if (FRank[faction][rank][rInvite])		format(right[0], 16, "%s", RIGHT_YES);
	else 									format(right[0], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rUninvite])	format(right[1], 16, "%s", RIGHT_YES);
	else									format(right[1], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rRank])		format(right[2], 16, "%s", RIGHT_YES);
	else 									format(right[2], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][r_eRank])		format(right[3], 16, "%s", RIGHT_YES);
	else 									format(right[3], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rSpawn])		format(right[4], 16, "%s", RIGHT_YES);
	else 									format(right[4], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rChat])		format(right[5], 16, "%s", RIGHT_YES);
	else									format(right[5], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rTow])			format(right[6], 16, "%s", RIGHT_YES);
	else 									format(right[6], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][rBodyCam])			format(right[7], 16, "%s", RIGHT_YES);
	else 									format(right[7], 16, "%s", RIGHT_NO);

	if (FRank[faction][rank][r_eRights])	format(right[8], 16, "%s", RIGHT_YES);
	else 									format(right[8], 16, "%s", RIGHT_NO);

	for(new i = 0; i < 9; i++)
	{
		format(faction_rights, sizeof(faction_rights), "%s\n%s\t%s\t%s", faction_rights, RS[i][right_name], right[i], RS[i][right_cmd]);
	}

	new title[32];
	format(title, sizeof(title), "{9189EF}%s", FactionRanks[faction][rank]);
	Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, title, faction_rights, "Kapat", "");
	return 1;
}

Dialog:MODEL_SELECTION_UNIFORM(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");

	new modelid = strval(inputtext);
			
	PlayerInfo[playerid][pChar] = modelid;
	SetPlayerSkin(playerid, modelid);
	Save_User(playerid);
	return 1;
}

Dialog:MODEL_SELECTION_SHAPE(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	if (!IsFactionFire(PlayerInfo[playerid][pFaction])) return SendErrorMessage(playerid, "LSFD üyesi olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "Üniformaný deðiþtirmek için önce iþbaþý yapmalýsýn (/isbasi). ");
	
	if (listitem == 0)		listitem = 277;
	else if (listitem == 1)	listitem = 278;
	else if (listitem == 2)	listitem = 279;
	else if (listitem == 3)	listitem = 191;

	SetPlayerSkin(playerid, listitem);
	return 1;
}

Dialog:MODEL_SELECTION_BORT(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))		return SendErrorMessage(playerid, "Legal oluþum üyesi olmalýsýn.");
    if (IsPlayerInAnyVehicle(playerid))	return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýn.");
    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Bu fonksiyon için iþbaþýnda olmalýsýnýz. (/isbasi).");

	for(new i=0; i<MAX_BORTES;i++)
	{
	    if (BortInfo[playerid][i][bortOn] != 0) continue;

		new modelid;
		if (IsFactionMedic(faction) || IsFactionFire(faction))	modelid = bort_list_fd[listitem];
		else if (IsFactionCity(faction))						modelid = bort_list_city[listitem];
		else													modelid = bort_list[listitem];
	
	    new Float:x, Float:y, Float:z;

	  	GetXYInFrontOfPlayer(playerid, x, y, z, 1.5);

		BortInfo[playerid][i][bortOn] = 1;
		BortInfo[playerid][i][bortUsing] = 0;
		BortInfo[playerid][i][bortObject] = CreateDynamicObject(modelid, x, y, z - 0.5, 0.0, 0.0, 0.0, GetWorld(playerid), GetInterior(playerid));
		EditDynamicObject(playerid, BortInfo[playerid][i][bortObject]);
		format(BortInfo[playerid][i][bortName], 32, "%s", (IsFactionMedic(faction) || IsFactionFire(faction))?(bort_names_fd[listitem]):((IsFactionCity(faction))?(bort_names_city[listitem]):(bort_names[listitem])));

		pTemp[playerid][pEditBort] = i+1;
	    return 1;
	}

	SendErrorMessage(playerid, "Maksimum 15 adet engel koyabilirsin.");
    return 1;
}

FireOnline()
{
    new count = 0;
    foreach(new i : Player)
    {
        if (IsPlayerLogged(i) == 0)		continue;
		if (IsPlayerFactionFire(i))	continue;
		if (IsPlayerAFK(i))				continue;
		if (!PlayerInfo[i][pOnDuty])		continue;
		
        count++;
    }
   	if (count < NEED_FIRE_TO_CRIME)	return 0;
	else 							return 1; 
}

stock EditFactionSkin(id = 0, faction_id = -1, model_id = -1)
{
    new query[75 + (11 * 3) + 1];

    if(id < 1)
    {
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO faction_skins SET faction_id = '%d', model_id = '%d'", faction_id, model_id);
    }

    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE faction_skins SET");

        if(faction_id != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, faction_id = '%d'", query, faction_id);
        }

        if(model_id != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, model_id = '%d'", query, model_id);
        }

        if(strfind(query, ", ") != -1)
            strdel(query, strfind(query, ", "), strfind(query, ", ") + 1);

        mysql_format(dbHandle, query, sizeof(query), "%s WHERE id = '%d'", query, id);
    }

    return query;
}

stock GetFactionSkin(const fields[] = "faction_skins.*", const joins[] = "", const wheres[] = "", page = 1, limit = -1, sqlid = -1, faction_id = -1, model_id = -1)
{
    new query[512];

    format(query, sizeof(query), "SELECT %s FROM faction_skins", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(sqlid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND faction_skins.id = '%d'", query, sqlid);
    }

    if(faction_id != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND faction_skins.faction_id = '%d'", query, faction_id);
    }

    if(model_id != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND faction_skins.model_id = '%d'", query, model_id);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY faction_skins.id DESC", query);

    if(limit == -1)
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 10000", query, ((page - 1) * ITEM_PER_PAGE));
    else
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 1", query, ((page - 1) * ITEM_PER_PAGE) + limit);

    return query;
}

this::DisplayFactionSkins(playerid)
{
	new rows = cache_num_rows();

	if(rows)
	{
        new bigstr[4096];

		new skin_id;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_int(i, "model_id", skin_id);

			format(bigstr, sizeof(bigstr), "%s%d\n", bigstr, skin_id);
		}

		Dialog_Show(playerid, MODEL_SELECTION_UNIFORM, DIALOG_STYLE_PREVIEW_MODEL, "Birlik Kiyafetleri", bigstr, "Sec", "Kapat");
	}

	else SendErrorMessage(playerid, "Birlik kýyafeti bulunamadý.");

	return 1;
}

this::OnStaffListFactionSkins(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new bigstr[4096];

        new id, faction_id, model_id;

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_int(i, "id", id);
            cache_get_value_int(i, "faction_id", faction_id);
            cache_get_value_int(i, "model_id", model_id);

            format(bigstr, sizeof(bigstr), "%s%d\tID: %D~n~B: %d~n~M: %d\n", bigstr, model_id, id, faction_id, model_id);
        }

        Dialog_Show(playerid, 0, DIALOG_STYLE_PREVIEW_MODEL, "Birlik Kýyafetleri", bigstr, "Kapat", "");
    }

    else SendErrorMessage(playerid, "Listelenebilecek birlik kýyafeti verisi bulunamadý.");

    return 1;
}

this::OnStaffEditFactionSkinModel(playerid, skin_id, model_id)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý birlik skininin modelini %d olarak deðiþtirdi.", GetNameEx(playerid), skin_id, model_id);
    }

    else SendErrorMessage(playerid, "Birlik kýyafeti için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffEditFactionSkinFaction(playerid, skin_id, faction_id)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý birlik skininin birliðini %d olarak deðiþtirdi.", GetNameEx(playerid), skin_id, faction_id);
    }

    else SendErrorMessage(playerid, "Birlik kýyafeti için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffDeleteFactionSkin(playerid, faction_id, model_id)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý birliðin %d model numaralý skinini kaldýrdý.", GetNameEx(playerid), faction_id, model_id);
    }

    else SendErrorMessage(playerid, "Geçersiz deðerler girdiniz.");

    return 1;
}

this::OnStaffCreateFactionSkin(playerid, faction_id, model_id)
{
    new skin_id = cache_insert_id();

    SendAdmMessage("%s, %d numarasýyla %d numaralý birliðe %d modelini skin olarak ekledi.", GetNameEx(playerid), skin_id, faction_id, model_id);

    return 1;
}

this::FACTION_DELETE(playerid, response)
{
	if(!response) return pc_cmd_birlik(playerid, "");
	new faction = PlayerInfo[playerid][pFaction];

	if (IsFactionLegal(faction)) return SendErrorMessage(playerid, "Devlet kurumlarý sadece geliþtiriciler tarafýndan kapatýlablilir.");

	if (!isLeader(playerid)) return SendErrorMessage(playerid, "Birliðin lideri olmalýsýnýz.");

	if (IsValidDynamicPickup(Factions[faction][fPickUp])) DestroyDynamicPickup(Factions[faction][fPickUp]);

	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `factions` WHERE `factionid` = %i", faction);
	mysql_tquery(dbHandle, query);
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `char`='0',`swat`='0',`swat_duty`='0',`duty`='0',`faction`='0',`rank`='0' WHERE `faction`=%i", faction);
	mysql_tquery(dbHandle, query);

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || PlayerInfo[i][pFaction] != faction) continue;
		RemovePlayerFaction(i);
	}


    AC_ResetPlayerWeapons(playerid);
	SendServerMessage(playerid, "Birliðiniz kapatýldý. %s [ID: %i].", Factions[faction][fName], faction);
	Factions[faction][fON] = 0;
	Factions[faction][fID] = 0;	
	return 1;	
}

this::FACTION_LEAVING_REQ(playerid, response)
{
	if(!response) return pc_cmd_birlik(playerid, "");
    new factionid = PlayerInfo[playerid][pFaction];
	if(factionid == 0) return SendErrorMessage(playerid, "Zaten bir birliðiniz yok.");

    SendFactionMessageF(factionid, COLOR_LIGHTBLUE, "[Birlik] %s adlý birlik üyesi birlikten ayrýldý.", GetNameEx(playerid));
	SendServerMessage(playerid, "%s adlý birlikten ayrýldýnýz.", Factions[factionid][fName]);

    RemovePlayerFaction(playerid);
    return 1;
}

ShowFactionPanel(playerid, faction = -1)
{
	if(faction == -1) return SendErrorMessage(playerid, "Bir hata oluþtu. Kod: F-01");
	new text[128], string[1024], olusumadi[128], rank = PlayerInfo[playerid][pRank]-1;
	format(olusumadi, sizeof(olusumadi), "Oluþum: %s", Factions[faction][fName]);

	format(text, sizeof(text), "{A9C4E4}Birlik Bilgileri\t{FFFFFF}birliðinize ait bilgiler\n");
	strcat(string, text);

	format(text, sizeof(text), "{A9C4E4}Üye Listesi\t{FFFFFF}birlik üyeleri\n");
	strcat(string, text);

	if (FRank[faction][rank][rInvite]) 
	{
	    format(text, sizeof(text), "{A9C4E4}Üye Davet Et\t{FFFFFF}birliðe üye davet et\n");
	    strcat(string, text);
	}

	if (FRank[faction][rank][rUninvite])
	{
		format(text, sizeof(text), "{A9C4E4}Üye Çýkar\t{FFFFFF}herhangi bir üyeyi çýkarabilirsiniz\n");
	    strcat(string, text);
	}

	if(isLeader(playerid) && !IsFactionLegal(faction))
	{
		format(text, sizeof(text), "{A9C4E4}Birliðe Araç Ekle\t{FFFFFF}birliðe araç ekleyebilirsiniz\n");
	    strcat(string, text);		
	}	

	if (FRank[faction][rank][r_eRank])
	{
		format(text, sizeof(text), "{A9C4E4}Rütbe Deðiþtir\t{FFFFFF}üyelerin rütbesini deðiþtirebilirsin\n");
	    strcat(string, text);
	}	

	if (FRank[faction][rank][r_eRank])
	{
		format(text, sizeof(text), "{A9C4E4}Rütbe Ýsimleri\t{FFFFFF}rütbeleri düzenleyebilirsiniz\n");
	    strcat(string, text);
	}

	if (FRank[faction][rank][r_eRights])
	{
		format(text, sizeof(text), "{A9C4E4}Rütbe Ýzinleri\t{FFFFFF}rütbe izinleri düzenleyebilirsiniz\n");
	    strcat(string, text);		
	}

	if(!isLeader(playerid))
	{
		format(text, sizeof(text), "{A9C4E4}Birlikten Ayrýl\t{FFFFFF}birlikten çýkabilirsiniz\n");
	    strcat(string, text);		
	}

	if(isLeader(playerid))
	{
		format(text, sizeof(text), "{A9C4E4}Birliði Kapat\t{FFFFFF}birliði kapatabilirsiniz\n");
	    strcat(string, text);		
	}	

	Dialog_Show(playerid, Faction_Main, DIALOG_STYLE_TABLIST, olusumadi, string, "Seç", "Geri Dön");
	return 1;
}

OlusumKurDialog(playerid, admin = 0)
{
	if(admin == 0)
	{
		if(PlayerInfo[playerid][pFaction] != 0) return SendErrorMessage(playerid, "Birlik üyeleri, bu özellikten faydalanamazlar.");
		if(PlayerInfo[playerid][pLevel] < OLUSUM_BIRLIK_KUR_SEVIYE) return SendErrorMessage(playerid, "Birlik kurmak için "#OLUSUM_BIRLIK_KUR_SEVIYE" seviye ve üstü bir seviyeye sahip olmalýsýnýz.");
		if(PlayerInfo[playerid][pCash] < OLUSUM_BIRLIK_KUR_PARA) return SendErrorMessage(playerid, "Birlik kurmak için yeterli paranýz bulunmuyor.");
		new liste[1500];
		format(liste, sizeof(liste), "* Birlik kurmak için "#OLUSUM_BIRLIK_KUR_SEVIYE" seviye olmalýsýnýz.");
		format(liste, sizeof(liste), "%s\n* Birlik kurmak için $"#OLUSUM_BIRLIK_KUR_PARA" paranýz olmalý.", liste);
		format(liste, sizeof(liste), "%s\n* Birlik kurduktan sonra birlik 144 saat içinde birlik tanýtýmý açmalýsýnýz.", liste);
		format(liste, sizeof(liste), "%s\n\n[Birlik Tipleri]\n", liste);
		for(new i; i < sizeof(OyuncuOlusumlar); i++)
		{
			format(liste, sizeof(liste), "%s\n[%d] %s", liste, OyuncuOlusumlar[i], OlusumTipleri[OyuncuOlusumlar[i]]);
		}
		format(liste, sizeof(liste), "%s\n\nAþaðýdaki kutuya birlik adýný, birliðin kýsaltmasýný ve birlik tipini girin: (virgül kullanmayý unutmayýn)", liste);
		format(liste, sizeof(liste), "%s\nÖrnek: LC Gang, LCG, 13", liste);
		OlusumDialog[playerid][1] = 0;
		Dialog_Show(playerid, DialogOlusum, DIALOG_STYLE_INPUT, "Birlik Kur", liste, "Oluþtur", "Kapat");
	}
	else
	{
		new liste[1500];
		format(liste, sizeof(liste), "* Birlik kurmak için "#OLUSUM_BIRLIK_KUR_SEVIYE" seviye olmalýsýnýz.");
		format(liste, sizeof(liste), "%s\n* Birlik kurmak için $"#OLUSUM_BIRLIK_KUR_PARA" paranýz olmalý.", liste);
		format(liste, sizeof(liste), "%s\n* Birlik kurduktan sonra birlik 144 saat içinde birlik tanýtýmý açmalýsýnýz.", liste);
		format(liste, sizeof(liste), "%s\n\n[Birlik Tipleri]\n", liste);
		for(new i; i < sizeof(OlusumTipleri); i++)
		{
			format(liste, sizeof(liste), "%s\n[%d] %s", liste, i, OlusumTipleri[i]);
		}
		format(liste, sizeof(liste), "%s\n\nAþaðýdaki kutuya birlik adýný, birliðin kýsaltmasýný ve birlik tipini girin: (virgül kullanmayý unutmayýn)", liste);
		format(liste, sizeof(liste), "%s\nÖrnek: LC Gang, LCG, 1", liste);
		OlusumDialog[playerid][1] = 2;
		Dialog_Show(playerid, DialogOlusum, DIALOG_STYLE_INPUT, "Birlik Kur", liste, "Oluþtur", "Kapat");
	}
	return 1;
}

OlusumYarat(playerid, type, name[], shortname[])
{
    new factionid = 0;

	for(new i = 1; i < MAX_FACTIONS; i++)
	{
		if (Factions[i][fON] != 0) continue;

		factionid = i;
		break;
	}

	if (factionid == -1) 						return SendErrorMessage(playerid, "Maksimum birlik sayýsýna ulaþýldý.");
	if (strfind(name, "'", true) != -1) 	    return SendErrorMessage(playerid, "Birlik adýnda týrnak iþareti kullanamazsýn.");
	if (strfind(shortname, "'", true) != -1) 	return SendErrorMessage(playerid, "Birlik adýnda týrnak iþareti kullanamazsýn.");

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

	PlayerInfo[playerid][pFaction] = factionid;
	SQL_SetInteger("users", "faction", PlayerInfo[playerid][pFaction], PlayerInfo[playerid][pID]);

	PlayerInfo[playerid][pRank] = Factions[factionid][fRanks];
	SQL_SetInteger("users", "rank", PlayerInfo[playerid][pRank], PlayerInfo[playerid][pID]);	

	for(new i; i != 20; i++)
	{
		FactionRanks[factionid][i] = "Belirsiz";
	}

	AddFactionToFile(factionid, shortname, name, Factions[factionid][fColor], type, Factions[factionid][fRanks], Factions[factionid][fPointTime], Factions[factionid][fJoinRank]);	
	return factionid;
}

Faction_MemberCount(factionid)
{
	new
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `users` WHERE `faction` = %i", factionid);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
	
	cache_get_value_int(0, "total", count);
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}

stock convertDate(timestamp, _form = 1)
{
    new year = 1970, day = 0, month = 0, hour = 0, mins = 0, sec = 0;

    new days_of_month[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
    };
    
    new names_of_month[12][10] = {
        "Ocak",
        "Subat",
        "Mart",
        "Nisan",
        "Mayis",
        "Haziran",
        "Temmuz",
        "Agustos",
        "Eylul",
        "Ekim",
        "Kasim",
        "Aralik"
    };
    
    new returnstring[36];

    while(timestamp > 31622400)
    {
        timestamp -= 31536000;
        
        if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        {
            timestamp -= 86400;
        }
        
        year++;
    }

    if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        days_of_month[1] = 29;
    }

    else
    {
        days_of_month[1] = 28;
    }


    while(timestamp > 86400)
    {
        timestamp -= 86400;
        day++;
        
        if(day == days_of_month[month])
        {
            day = 0;
            month++;
        }
    }

    while(timestamp > 60)
    {
        timestamp -= 60;
        mins++;
        
        if(mins == 60)
        {
            mins = 0;
            hour++;
        }
    }

    sec = timestamp;

    new zamanfix = hour + 3;
    
    if(zamanfix >= 24)
    {
        zamanfix = 0;
    }
    
    switch(_form)
    {
        case 1: format(returnstring, 31, "%02d/%02d/%d %02d:%02d", day + 1, month + 1, year, zamanfix, mins);
        case 2: format(returnstring, 31, "%s %02d, %d, %02d:%02d", names_of_month[month], day + 1, year, zamanfix, mins);
        case 3: format(returnstring, 31, "%d %c%c%c %d, %02d:%02d", day + 1, names_of_month[month][0], names_of_month[month][1], names_of_month[month][2], year, zamanfix, mins);
        case 4: format(returnstring, 31, "%02d.%02d.%d", day + 1, month + 1, year);
        default: format(returnstring, 31, "%02d.%02d.%d - %02d:%02d:%02d", day + 1, month + 1, year, zamanfix, mins, sec);
    }

    return returnstring;
}

this::FactionCharacterList(playerid)
{
	new rows = cache_num_rows();
	new faction = PlayerInfo[playerid][pFaction];

	if(rows)
	{
		new str[14000];

		str = "Karakter\tRütbe\tAktiflik\tSon Giriþ\n";

		new name[MAX_PLAYER_NAME], rank, last_login, online;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_int(i, "rank", rank);
			cache_get_value_int(i, "last_login", last_login);
			cache_get_value_int(i, "online", online);
			cache_get_value(i, "name", name, MAX_PLAYER_NAME);

			format(str, sizeof(str), "%s" EMBED_SILVER "%s\t" EMBED_WHITE "%s\t%s\t%s\n", str, name, FactionRanks[faction][rank-1], (online) ? (EMBED_PASTELGREEN "oyunda") : (EMBED_TOMATO "oyunda deðil"), convertDate(last_login));
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "Birlik Üyeleri", str, "Seç", "Kapat");
	}

	else SendErrorMessage(playerid, "Üye listesi getirilemedi. Lütfen yöneticilerle iletiþime geçiniz.");

	return 1;
}

Faction_List(playerid)
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

this::CountOnlineMembers(factionid)
{
    new count = 0;

    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFaction] == factionid){
            count++;
        }
    }

    return count;
}

CountFactionMembers(factionid)
{
    new query[60], count;
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM users WHERE faction = %i", factionid);
	new Cache: cache = mysql_query(dbHandle, query);
	if(!cache_num_rows()) count = 0;
    count = cache_num_rows();
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
    return count;
}

stock ShowColourDialog(playerid, page = 1)
{
    new str[2048], count = 0;

    for(new i = ((page - 1) * ITEM_PER_PAGE); i != 255; i++)
    {
        if(count < ITEM_PER_PAGE)
        {
            format(str, sizeof(str), "%s%s%s " EMBED_ALTO "(Renk Kodu: %d)\n", str, Colours[i][coEmbedValue], Colours[i][coName], Colours[i][coVehicleColorID]);

            count++;
        }
        else
        {
            format(str, sizeof(str), "%s" EMBED_PASTELGREEN "» " EMBED_WHITE "Sonraki Sayfa\n", str);

            break;
        }
    }

    if(pTemp[playerid][pColorPage] > 1)
    {
        format(str, sizeof(str), "%s" EMBED_TOMATO "» " EMBED_WHITE "Önceki Sayfa\n", str);
    }

    return Dialog_Show(playerid, Colours, DIALOG_STYLE_LIST, "Renkler", str, "Seç", "Vazgeç");
}

Dialog:Colours(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(strfind(inputtext, "Sonraki Sayfa") != -1)
        {
            pTemp[playerid][pColorPage]++;

            ShowColourDialog(playerid, pTemp[playerid][pColorPage]);
        }

        else if(strfind(inputtext, "Önceki Sayfa") != -1)
        {
            pTemp[playerid][pColorPage]--;

            ShowColourDialog(playerid, pTemp[playerid][pColorPage]);
        }
    }

    return 1;
}

OlusumTipGetir(olusumid)
{
	new tip = -1;
	if((olusumid >= 0 && olusumid <= MAX_FACTIONS) && Factions[olusumid][fON]) tip = Factions[olusumid][fType];
	return tip;
}

this::OnPlayerDeleteScenario(playerid, id)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new Text3D:label_id;

        cache_get_value_index_int(0, 0, _:label_id);

        if(IsValidDynamic3DTextLabel(Text3D:label_id))
            DestroyDynamic3DTextLabel(Text3D:label_id);

        mysql_query(dbHandle, sprintf("DELETE FROM game_scenarios WHERE id = '%d'", id));

        SendServerMessage(playerid, "#%d numaralý senaryoyu kaldýrdýnýz.", id);
    }

    else SendErrorMessage(playerid, "Geçersiz senaryo numarasý girdiniz.");

    return 1;
}

this::OnPlayerCreateScenario(playerid)
{
    new id = cache_insert_id();

    SendServerMessage(playerid, "#%d numaralý senaryoyu eklediniz.", id);
    RefreshScenario(id);

    return 1;
}

this::LoadScenarios()
{
    new rows = cache_num_rows();

    if(rows)
    {
        new id;

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_index_int(i, 0, id);

            RefreshScenario(id, false);
        }
    }

    return 1;
}

this::ListScenarios(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new id, name[MAX_PLAYER_NAME], placed_date, Float:x, Float:y;

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_index_int(i, 0, id);
            cache_get_value_index(i, 1, name);
            cache_get_value_index_int(i, 2, placed_date);
            cache_get_value_index_float(i, 3, x);
            cache_get_value_index_float(i, 4, y);

            SendServerMessage(playerid, "#%d - Ekleyen: %s - Tarih: %s", id, name, convertDate(placed_date));
        }
    }

    else SendErrorMessage(playerid, "Listelenebilecek senaryo kaydý bulunamadý.");

    return 1;
}

this::OnScenarioRefreshed(id, bool:forcedestroy)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new text[144], placed_by, Text3D:label_id, interior, world, Float:x, Float:y, Float:z;
        
        cache_get_value_index(0, 0, text);
        cache_get_value_index_int(0, 1, placed_by);
        cache_get_value_index_int(0, 2, _:label_id);
        cache_get_value_index_int(0, 3, interior);
        cache_get_value_index_int(0, 4, world);
        cache_get_value_index_float(0, 5, x);
        cache_get_value_index_float(0, 6, y);
        cache_get_value_index_float(0, 7, z);
    
        if(forcedestroy == true)
        {
            if(IsValidDynamic3DTextLabel(Text3D:label_id))
            {
                DestroyDynamic3DTextLabel(Text3D:label_id);
            }
        }

        ReplaceText(text, "#kirmizi", "{FF0000}");
        ReplaceText(text, "#mavi", "{0000FF}");
        ReplaceText(text, "#sari", "{FFFF00}");
        ReplaceText(text, "#yesil", "{00FF00}");
        ReplaceText(text, "#mor", "{FF80FF}");
        ReplaceText(text, "#acikmavi", "{00FFFF}");
        ReplaceText(text, "#beyaz", "{FFFFFF}");
        ReplaceText(text, "#turuncu", "{FF8000}");
        ReplaceText(text, "#siyah", "{000000}");
        ReplaceText(text, "#c", "\n");

        format(text, sizeof(text), "%s\n" EMBED_ALTO "((#%d - ID: %d))", text, placed_by, id);

        label_id = CreateDynamic3DTextLabel(text, -1, x, y, z, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
    
        mysql_query(dbHandle, EditScenario(id, -1, -1, "", label_id));
    }

    return 1;
}
stock RefreshScenario(id, bool:forcedestroy = true)
{
    mysql_tquery(dbHandle, GetScenario("game_scenarios.text, game_scenarios.placed_by, game_scenarios.label_id, game_scenarios.interior, game_scenarios.world, game_scenarios.x, game_scenarios.y, game_scenarios.z", "", "", id), "OnScenarioRefreshed", "dd", id, forcedestroy);

    return 1;
}

stock EditScenario(id, placed_by = -1, placed_date = -1, text[] = "", Text3D:label_id = Text3D:-1, interior = -1, world = -1, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
    new query[350];

    if(id < 1)
    {
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO game_scenarios SET placed_by = '%d', placed_date = '%d', text = '%e', label_id = '%d', interior = '%d', world = '%d', x = '%f', y = '%f', z = '%f'", placed_by, placed_date, text, _:label_id, interior, world, x, y, z);
    }

    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE game_scenarios SET");

        if(placed_by != -1)
            mysql_format(dbHandle, query, sizeof(query), "%s, placed_by = '%d'", query, placed_by);

        if(placed_date != -1)
            mysql_format(dbHandle, query, sizeof(query), "%s, placed_date = '%d'", query, placed_date);

        if(!isnull(text))
            mysql_format(dbHandle, query, sizeof(query), "%s, text = '%e'", query, text);

        if(Text3D:label_id != Text3D:-1)
            mysql_format(dbHandle, query, sizeof(query), "%s, label_id = '%d'", query, _:label_id);

        if(interior != -1)
            mysql_format(dbHandle, query, sizeof(query), "%s, interior = '%d'", query, interior);

        if(world != -1)
            mysql_format(dbHandle, query, sizeof(query), "%s, world = '%d'", query, world);

        if(x != 0.0)
            mysql_format(dbHandle, query, sizeof(query), "%s, x = '%f'", query, x);

        if(y != 0.0)
            mysql_format(dbHandle, query, sizeof(query), "%s, y = '%f'", query, y);

        if(z != 0.0)
            mysql_format(dbHandle, query, sizeof(query), "%s, z = '%f'", query, z);

        if(strfind(query, ", ") != -1)
            strdel(query, strfind(query, ", "), strfind(query, ", ") + 1);

        mysql_format(dbHandle, query, sizeof(query), "%s WHERE id = '%d'", query, id);
    }

    return query;
}

stock GetScenario(const fields[] = "game_scenarios.*", const joins[] = "", const wheres[] = "", id = -1, placed_by = -1)
{
    new query[300];

    format(query, sizeof(query), "SELECT %s FROM game_scenarios", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(id != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_scenarios.id = '%d'", query, id);
    }

    if(placed_by != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_scenarios.placed_by = '%d'", query, placed_by);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY game_scenarios.id DESC", query);

    return query;
}

this::Vehicle_AddToFaction(playerid, response, id)
{
	if (!response)    return 1;

	new vehicle = GetPlayerVehicleID(playerid);
	new faction = PlayerInfo[playerid][pFaction];
	if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Herhangi bir araçta deðilsin.");
	if(!IsValidVehicle(vehicle))        return SendErrorMessage(playerid, "Herhangi bir araçta deðilsin.");  
	if(VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Kendine ait bir araçta deðilsin.");


    if(PlayerInfo[playerid][pCarKey] != 0) PlayerInfo[playerid][pCarKey] = 0;
	VehicleInfo[vehicle][carOwnerID] = INVALID_PLAYER_ID;
	VehicleInfo[vehicle][carFaction] = faction;
	Save_Car(vehicle);

	SendServerMessage(playerid, "%s model aracý %s adlý birliðe eklediniz.", GetVehicleModelName(GetVehicleModel(vehicle)), Factions[faction][fName]);
	return 1;
}

this::OfflineFactionKick(playerid, account[])
{
	new rows = cache_num_rows();
    if (!rows) return SendErrorMessage(playerid, "%s adlý karakter veritabanýnda bulunamadý.", account);

	new faction, rank;
	cache_get_value_int(0, "faction", faction);
	cache_get_value_int(0, "rank", rank);
	if (faction != PlayerInfo[playerid][pFaction]) return SendErrorMessage(playerid, "%s adlý karakter sizin birliðinizde deðil.", account);
	if (rank > PlayerInfo[playerid][pRank])        return SendErrorMessage(playerid, "%s adlý karakterin rütbesi sizden üstün.", account);

	new query[388];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `char`='0',`swat`='0',`swat_duty`='0',`duty`='0',`faction`='0',`rank`='0' WHERE `name`='%e'", account);
	mysql_tquery(dbHandle, query);

	SendServerMessage(playerid, "%s adlý kiþiyi birliðinizden attýnýz.", account);
	return 1;
}