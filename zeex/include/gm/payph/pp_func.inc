PayPhone_OnGameModeInit()
{
    mysql_tquery(dbHandle, "SELECT * FROM `payphones`", "LoadDynamicPayphones");
    return 1;
}

this::LoadDynamicPayphones()
{
	new rows = cache_num_rows(),
	    time = GetTickCount(),
		total;

	if (!rows)
	{
	    print("[Payphones] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
        cache_get_value_int(i, "id", PayphoneInfo[i][phID]);
        cache_get_value_int(i, "type", PayphoneInfo[i][phType]);
        cache_get_value_int(i, "number", PayphoneInfo[i][phNumber]);
        cache_get_value_float(i, "x", PayphoneInfo[i][phX]);
        cache_get_value_float(i, "y", PayphoneInfo[i][phY]);
        cache_get_value_float(i, "z", PayphoneInfo[i][phZ]);
        cache_get_value_float(i, "rx", PayphoneInfo[i][phRX]);
        cache_get_value_float(i, "ry", PayphoneInfo[i][phRY]);
        cache_get_value_float(i, "rz", PayphoneInfo[i][phRZ]);
        cache_get_value_int(i, "vw", PayphoneInfo[i][phVW]);
        cache_get_value_int(i, "int", PayphoneInfo[i][phInt]); 

		if (PayphoneInfo[i][phType])
			PayphoneInfo[i][phObj] = CreateDynamicObject(PayphoneInfo[i][phType], PayphoneInfo[i][phX], PayphoneInfo[i][phY], PayphoneInfo[i][phZ], PayphoneInfo[i][phRX], PayphoneInfo[i][phRY], PayphoneInfo[i][phRZ], PayphoneInfo[i][phVW], PayphoneInfo[i][phInt]);
	
    	PayphoneInfo[i][phLabel] =
			CreateDynamic3DTextLabel("[Payphone]\n/ankesorlutelefon", COLOR_YELLOWMY, PayphoneInfo[i][phX], PayphoneInfo[i][phY], PayphoneInfo[i][phZ]+1.3, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, PayphoneInfo[i][phVW], PayphoneInfo[i][phInt], -1, 75.0);
        
		PayphoneInfo[i][phUsed] = INVALID_PLAYER_ID;
		PayphoneInfo[i][phCaller] = INVALID_PLAYER_ID;
		PayphoneInfo[i][phState] = PAYPHONE_STATE_NONE;
		PayphoneInfo[i][pp_exist] = true;
		
		total++;
	}
	printf("[Payphones] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

this::OnPayphoneInsert(id)
{
    PayphoneInfo[id][phID] = cache_insert_id();
	return 1;
}

//[23:38:47] [MySQL]: <|| error: Failed to read auto-increment value from storage engine | callback: OnPayphoneInsert | query: INSERT INTO `payphones` (`type`,`number`,`x`,`y`,`z`,`rx`,`ry`,`rz`,`vw`,`int`) VALUES (1216,112, 2194.139, 21.601, 26.504, 0.0, 0.0, 0.0, 0, 0) ||>
//[23:38:56] [MySQL]: <|| error: Failed to reàd auto-increment value from storage engine | callback: OnPayphoneInsert | query: INSERT INTO `payphones` (`type`,`number`,`x`,`y`,`z`,`rx`,`ry`,`rz`,`vw`,`int`) VALUES (1216,1122, 2185.918, 24.94, 26.504, 0.0, 0.0, 0.0, 0, 0) ||>


CreatePayphone(bool: crt, type, number, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz, vw, interior, sqlid = 0)
{
	new id;
	for(new i; i != MAX_PAYPHONES; i++)
	{
	    if (PayphoneInfo[i][phID] != 0)
	        continue;
	        
		id = i;
		break;
	}
	
	if (id == -1) return -1;

    PayphoneInfo[id][phType] = type;
    PayphoneInfo[id][phNumber] = number;
	PayphoneInfo[id][phX] = x,
	PayphoneInfo[id][phY] = y,
	PayphoneInfo[id][phZ] = z,
	PayphoneInfo[id][phRX] = rx,
	PayphoneInfo[id][phRY] = ry,
	PayphoneInfo[id][phRZ] = rz;
	PayphoneInfo[id][phVW] = vw;
	PayphoneInfo[id][phInt] = interior;
	
	PayphoneInfo[id][phObj] = CreateDynamicObject(type, x, y, z, rx, ry, rz, vw, interior);
	
    PayphoneInfo[id][phLabel] =
		CreateDynamic3DTextLabel("[Ankesorlu Telefon]\n/ankesorlutelefon", COLOR_GOLD, x, y, z + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, vw, interior, -1, 15.0);
	
	PayphoneInfo[id][phUsed] = INVALID_PLAYER_ID;
	PayphoneInfo[id][phCaller] = INVALID_PLAYER_ID;
	PayphoneInfo[id][phState] = PAYPHONE_STATE_NONE;
	PayphoneInfo[id][pp_exist] = true;

	if (crt)
	{
	    new query[128 + 128];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `payphones` (`type`,`number`,`x`,`y`,`z`,`rx`,`ry`,`rz`,`vw`,`int`) VALUES (%i,%i,%f,%f,%f,%f,%f,%f,%i,%i)",
		type, number, x,y,z,rx,ry,rz, vw, interior);
		mysql_tquery(dbHandle, query, "OnPayphoneInsert", "d", id);
	}
	else PayphoneInfo[id][phID] = sqlid;

	return id;
}

Update_Payphone(id)
{
	//if (PayphoneInfo[id][pp_exist] == true) return 0;
    if (IsPlayerConnected(PayphoneInfo[id][phCaller]) && PayphoneInfo[id][phState] == PAYPHONE_STATE_RINGING)
	{
	    if (IsValidDynamic3DTextLabel(PayphoneInfo[id][phLabel])) DestroyDynamic3DTextLabel(PayphoneInfo[id][phLabel]);

		PlaySoundForPlayersInRange(20600, 15.0, PayphoneInfo[id][phX], PayphoneInfo[id][phY], PayphoneInfo[id][phZ]);
		
		PayphoneInfo[id][phLabel] = CreateDynamic3DTextLabel("** Ankesorlu telefon caliyor **\n{F6C861}/ankesorlutelefon - yanitla", COLOR_PURPLE, PayphoneInfo[id][phX], PayphoneInfo[id][phY], PayphoneInfo[id][phZ]+1.3, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, PayphoneInfo[id][phVW], PayphoneInfo[id][phInt], -1, 50.0);//15.0);
	}
	else
	{
		if (IsValidDynamic3DTextLabel(PayphoneInfo[id][phLabel])) DestroyDynamic3DTextLabel(PayphoneInfo[id][phLabel]);
		PayphoneInfo[id][phLabel] =	CreateDynamic3DTextLabel("[Ankesorlu Telefon]\n/ankesorlutelefon", COLOR_GOLD, PayphoneInfo[id][phX], PayphoneInfo[id][phY], PayphoneInfo[id][phZ]+1.3, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, PayphoneInfo[id][phVW], PayphoneInfo[id][phInt], -1, 50.0);//15.0);
	}
	return 1;
}

PlayerOnPayphone(playerid)
{
	new 
		hour, 
		minute, 
		second, 
		str[64]
	;

	gettime(hour, minute, second);
	format(str, sizeof(str), "%02d:%02d", hour, minute);
    PlayerTextDrawSetString(playerid, PP_Btn[playerid][0], str);

	SelectTextDraw(playerid, -1);
	
	for(new i = 0; i < 11; i++) TextDrawShowForPlayer(playerid, PP_Framework[i]);
	for(new e = 0; e < 11; e++) PlayerTextDrawShow(playerid, PP_Btn[playerid][e]);
	for(new j = 0; j < 4; j++) PlayerTextDrawShow(playerid, NumberLetters[playerid][j]);

	return 1;
}

cancelPayphone(playerid)
{
	if (pTemp[playerid][pEmergency] || pTemp[playerid][pCallLine] != INVALID_PLAYER_ID) return pc_cmd_telefonkapat(playerid, "");
	
	CancelSelectTextDraw(playerid);

	new id = pTemp[playerid][pPayphone];

	PayphoneInfo[id][phUsed] = INVALID_PLAYER_ID;
	PayphoneInfo[id][phCaller] = INVALID_PLAYER_ID;
	PayphoneInfo[id][phState] = PAYPHONE_STATE_NONE;
	
	pTemp[playerid][pPayphone] = -1;
	pTemp[playerid][pPayphoneNumStr] = EOS;

	for(new i = 0; i < 11; i++) TextDrawHideForPlayer(playerid, PP_Framework[i]);
	for(new e = 0; e < 11; e++) PlayerTextDrawHide(playerid, PP_Btn[playerid][e]);
	for(new j = 0; j < 4; j++) PlayerTextDrawHide(playerid, NumberLetters[playerid][j]);
	
	return 1;
}

IsPlayerAtPayphone(playerid, i)
	return (IsPlayerInRangeOfPoint(playerid, 2.0, PayphoneInfo[i][phX], PayphoneInfo[i][phY], PayphoneInfo[i][phZ]) && PayphoneInfo[i][phInt] == GetInterior(playerid) && PayphoneInfo[i][phVW] == GetWorld(playerid))?(1):(0);

Payphone_Nearest(playerid)
{
	for(new i; i != MAX_PAYPHONES; i++)
	{
        if (IsPlayerInRangeOfPoint(playerid, 2.0, PayphoneInfo[i][phX], PayphoneInfo[i][phY], PayphoneInfo[i][phZ]) && PayphoneInfo[i][phInt] == GetInterior(playerid) && PayphoneInfo[i][phVW] == GetWorld(playerid))
            return i;
	}
	return -1;
}

IsNumberPayphone(number)
{
	if (number == 0)	return 1;

	for(new i = 0; i < MAX_PAYPHONES; i++)
	{
		if (PayphoneInfo[i][phNumber] == 0) 		continue;
		if (number == PayphoneInfo[i][phNumber]) return i;
	}
	return -1;
}