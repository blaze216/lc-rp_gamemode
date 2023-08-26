enum MOVEABLE_GATES_ENUM
{
	gateID,
	gateModel,
	gateObject,
	gateInt,
	gateVW,
	gateFaction,
	gateOpened,
	Float:gatePosX,
	Float:gatePosY,
	Float:gatePosZ,
	Float:gatePosRX,
	Float:gatePosRY,
	Float:gatePosRZ,
	Float:gateSpeed,
	Float:gateRadius,
	Float:gateMoveX,
	Float:gateMoveY,
	Float:gateMoveZ,
	Float:gateMoveRX,
	Float:gateMoveRY,
	Float:gateMoveRZ,
	gateSound,
	gateObjectOn
}
new Gates[MAX_GATES][MOVEABLE_GATES_ENUM];

this::LoadDynamicGates()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)	return print("[Gates] Kayit bulunamadi.");
	
	for ( new i = 0; i < rows; i++)
	{
		cache_get_value_int(i, "id", Gates[i][gateID]);
		cache_get_value_int(i, "model", Gates[i][gateModel]);
		cache_get_value_int(i, "faction", Gates[i][gateFaction]);
        cache_get_value_float(i, "posx", Gates[i][gatePosX]);
        cache_get_value_float(i, "posy", Gates[i][gatePosY]);
        cache_get_value_float(i, "posz", Gates[i][gatePosZ]);
        cache_get_value_float(i, "posrx", Gates[i][gatePosRX]);
        cache_get_value_float(i, "posry", Gates[i][gatePosRY]);
        cache_get_value_float(i, "posrz", Gates[i][gatePosRZ]);
        cache_get_value_float(i, "speed", Gates[i][gateSpeed]);
        cache_get_value_float(i, "radius", Gates[i][gateRadius]);
        cache_get_value_float(i, "movex", Gates[i][gateMoveX]);
        cache_get_value_float(i, "movey", Gates[i][gateMoveY]);
        cache_get_value_float(i, "movez", Gates[i][gateMoveZ]);
        cache_get_value_float(i, "moverx", Gates[i][gateMoveRX]);
        cache_get_value_float(i, "movery", Gates[i][gateMoveRY]);
        cache_get_value_float(i, "moverz", Gates[i][gateMoveRZ]);
        cache_get_value_int(i, "interior", Gates[i][gateInt]);
		cache_get_value_int(i, "virworld", Gates[i][gateVW]);
        cache_get_value_int(i, "sound", Gates[i][gateSound]);
        Gates[i][gateObject] = CreateDynamicObject(Gates[i][gateModel], Gates[i][gatePosX], Gates[i][gatePosY], Gates[i][gatePosZ], Gates[i][gatePosRX], Gates[i][gatePosRY], Gates[i][gatePosRZ], Gates[i][gateVW], Gates[i][gateInt], -1, 200.0);
        Gates[i][gateOpened] = 0;
		Gates[i][gateObjectOn] = 1;

		total++;
	}
	printf("[Gates] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

AddGateToFile(gateid, modelid, faction, interior, virworld, Float:x, Float:y, Float:z)
{
    new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `gates` (model,faction,posx,posy,posz,interior,virworld) VALUES (%i,%i,%f,%f,%f,%i,%i)", modelid, faction, x, y, z, interior, virworld);
	mysql_tquery(dbHandle, query, "OnGateInsert", "d", gateid);
	return 1;
}

this::OnGateInsert(gateid) {
	return Gates[gateid][gateID] = cache_insert_id();
}

Gate_Nearest(playerid)
{
	for(new i; i != MAX_GATES; i++)
	{
	    if (GetWorld(playerid) == Gates[i][gateVW] && Gates[i][gateInt] == GetInterior(playerid) && IsPlayerInRangeOfPoint(playerid, Gates[i][gateRadius], Gates[i][gatePosX], Gates[i][gatePosY], Gates[i][gatePosZ]) && Gates[i][gateObjectOn])
	    {
			return i;
		}
	}
	return -1;
}

alias:gateac("gate");
CMD:gateac(playerid, params[])
{
	new gate = -1;

	if ((gate = Gate_Nearest(playerid)) == -1)	return 1;

	if (IsFactionDocs(Gates[gate][gateFaction]) && (!IsPlayerFactionPolice(playerid) || !IsPlayerFactionDocs(playerid))) return 1;
	else	if (Gates[gate][gateFaction] != 0 && Gates[gate][gateFaction] != PlayerInfo[playerid][pFaction]) return 1;

    Gates[gate][gateOpened] = (Gates[gate][gateOpened] == 1) ? (0) : (1);

	if (Gates[gate][gateOpened])	MoveDynamicObject(Gates[gate][gateObject], Gates[gate][gatePosX], Gates[gate][gatePosY], Gates[gate][gatePosZ], Gates[gate][gateSpeed], Gates[gate][gatePosRX], Gates[gate][gatePosRY], Gates[gate][gatePosRZ]);
	else	 					MoveDynamicObject(Gates[gate][gateObject], Gates[gate][gateMoveX], Gates[gate][gateMoveY], Gates[gate][gateMoveZ], Gates[gate][gateSpeed], Gates[gate][gateMoveRX], Gates[gate][gateMoveRY], Gates[gate][gateMoveRZ]);

	if (Gates[gate][gateSound] != 0) PlayerPlaySoundEx(playerid, Gates[gate][gateSound]);
	return 1;
}

Gate_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

	if (GetPVarInt(playerid, #edit_gate) && Gates[GetPVarInt(playerid, #edit_gate)-1][gateObject] == objectid && Gates[GetPVarInt(playerid, #edit_gate)-1][gateObjectOn])
	{
		if (response == EDIT_RESPONSE_FINAL)
		{
		    new gate = GetPVarInt(playerid, #edit_gate)-1;
	    	
	    	DeletePVar(playerid, #edit_gate);
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);

			new query[128 + 56];
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `gates` SET `posx`=%f,`posy`=%f,`posz`=%f,`posrx`=%f,`posry`=%f,`posrz`=%f WHERE `id`=%i", x, y, z, rx, ry, rz, Gates[gate][gateID]);
			mysql_tquery(dbHandle, query);
			
            GetDynamicObjectPos(objectid, Gates[gate][gatePosX], Gates[gate][gatePosY], Gates[gate][gatePosZ]);
			GetDynamicObjectRot(objectid, Gates[gate][gatePosRX], Gates[gate][gatePosRY], Gates[gate][gatePosRZ]);
	        Gates[gate][gateOpened] = 0;
			SendSyntaxMessage(playerid, "Gate kapalý pozisyonu düzenlendi [ID: %i]", gate);
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
	    	DeletePVar(playerid, #edit_gate);
			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		}
		return 1;
	}
	if (GetPVarInt(playerid, #2_edit_gate) && Gates[GetPVarInt(playerid, #2_edit_gate)-1][gateObject] == objectid && Gates[GetPVarInt(playerid, #2_edit_gate)-1][gateObjectOn])
	{
		if (response == EDIT_RESPONSE_FINAL)
		{
		    new gate = GetPVarInt(playerid, #2_edit_gate)-1;
	    	
			DeletePVar(playerid, #2_edit_gate);
            SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
				
			new query[128 + 56];
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `gates` SET `movex`=%f,`movey`=%f,`movez`=%f,`moverx`=%f,`movery`=%f,`moverz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, Gates[gate][gateID]);
			mysql_tquery(dbHandle, query);
			
			GetDynamicObjectPos(objectid, Gates[gate][gateMoveX], Gates[gate][gateMoveY], Gates[gate][gateMoveZ]);
			GetDynamicObjectRot(objectid, Gates[gate][gateMoveRX], Gates[gate][gateMoveRY], Gates[gate][gateMoveRZ]);
	        Gates[gate][gateOpened] = 1;
	        
			SendSyntaxMessage(playerid, "Gate açýk pozisyonu düzenlendi [ID: %i]", gate);
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
	    	DeletePVar(playerid, #2_edit_gate);
	    	DeletePVar(playerid, #edit_gate);
			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		}
	}
	return 1;
}

Gate_OnGameModeInit()
{
	mysql_tquery(dbHandle, "SELECT * FROM `gates`", "LoadDynamicGates");
	return 1;
}