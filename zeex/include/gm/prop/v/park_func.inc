Park_OnGameModeInit() //çàãðóçêà
{
	for(new i; i < MAX_METERS; i++)
	{
		pMeter[i][parkID] = -1;
		pMeter[i][parkX] = 0.0;
		pMeter[i][parkY] = 0.0;
		pMeter[i][parkZ] = 0.0;
		pMeter[i][parkA] = 0.0;
		pMeter[i][parkVehicle] = 0;
		pMeter[i][parkAvailable] = false;
	}
	
    mysql_tquery(dbHandle, "SELECT * FROM `pmeters` ORDER BY `id`", "LoadParkMeters");
	return 1;
}

MeterCheck()
{
	new string[128], vid;

	for(new i; i < MAX_METERS; i++)
	{
	    if (pMeter[i][parkID] > -1)
	    {
	        vid = GetClosestVehicleInObject(pMeter[i][parkObject]);
	    
	        switch(pMeter[i][parkAvailable])
	        {
	            case true:
				{
					if (vid == -1) format(string, sizeof(string), "#%d\nPARK EDÝLEBÝLÝR", i);
					else 
					{
						if (VehicleInfo[vid][carFaction] == 1 || VehicleInfo[vid][carFaction] == 2 || VehicleInfo[vid][carFaction] == 3 || VehicleInfo[vid][carFaction] == 4)
						{
							pMeter[i][parkAvailable] = false;
							format(string, sizeof(string), "#%d\nPARK EDÝLEMEZ", i);
				   			UpdateDynamic3DTextLabelText(pMeter[i][parkLabel], 0xFF6347FF, string);
							return 1;
						}
						else format(string, sizeof(string), "#%d\nPARK EDÝLEBÝLÝR\n(( ÖDENMEMÝÞ ))\n/paypark", i); 
					}
					
				    UpdateDynamic3DTextLabelText(pMeter[i][parkLabel], 0x33AA33FF, string);
	            }
	            case false:
				{
				    if (pMeter[i][parkVehicle] != vid)
				    {
				        pMeter[i][parkAvailable] = true;
				        pMeter[i][parkVehicle] = 0;
						return 1;
				    }
					    
				    format(string, sizeof(string), "#%d\nPARK EDÝLEBÝLÝR", i);
				    UpdateDynamic3DTextLabelText(pMeter[i][parkLabel], 0xFF6347FF, string);
	            }
	        }
	    }
	}
	return 1;
}

PM_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rz)
{
    if (GetPVarInt(playerid, #edit_pm) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
		new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

		GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
		GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		
	    new id = GetPVarInt(playerid, #edit_pm)-1;
		DeletePVar(playerid, #edit_pm);

	    if (id < 0 || !pMeter[id][parkID] || id >= MAX_METERS) 	return SendErrorMessage(playerid, "Parkmetre bulunamadý.");
	    if (objectid != pMeter[id][parkID])						return SendErrorMessage(playerid, "Parkmetre düzenlenemedi.");

		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, 0.0, 0.0, rz);

        GetDynamicObjectPos(objectid, pMeter[id][parkX], pMeter[id][parkY], pMeter[id][parkZ]);
       	pMeter[id][parkA] = rz;

		if (IsValidDynamic3DTextLabel(pMeter[id][parkLabel]))
		    DestroyDynamic3DTextLabel(pMeter[id][parkLabel]);

		pMeter[id][parkLabel] = CreateDynamic3DTextLabel("> PARKMETRE DÜZENLENDÝ", 0xFF6347AA, pMeter[id][parkX], pMeter[id][parkY], pMeter[id][parkZ], 3.0);
        
		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `pmeters` SET `x`=%f,`y`=%f,`z`=%f,`angle`=%f WHERE `id`=%i", x, y, z, rz, pMeter[id][parkID]);
		mysql_tquery(dbHandle, query);

		SendAdmMessageToPlayer(playerid, "Parkmetrenin konumu [ID: %i] düzenlendi.", id);
	}
    return 1;
}


stock InsertParkMeters(playerid, Float:x, Float:y, Float:z, Float:angle)
{
	new nextid = -1, query[256];

	for(new i; i < MAX_METERS; i++)
	{
	    if (pMeter[i][parkID] == -1)
	    {
	        nextid = i;
	        break;
	    }
	}
	
	if (nextid < 0)
	{
	    SendErrorMessage(playerid, "Maksimum parkmetre sayýsýna ulaþýldý.");
	}
	else
	{
		pMeter[nextid][parkID] = nextid;
		pMeter[nextid][parkX] = x;
		pMeter[nextid][parkY] = y;
		pMeter[nextid][parkZ] = z;
		pMeter[nextid][parkA] = angle;
		pMeter[nextid][parkAvailable] = true;
		pMeter[nextid][parkVehicle] = 0;

		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `pmeters` (`x`, `y`, `z`, `angle`) VALUES (%.4f, %.4f, %.4f, %.4f)", pMeter[nextid][parkX], pMeter[nextid][parkY], pMeter[nextid][parkZ], pMeter[nextid][parkA]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamicObject(pMeter[nextid][parkObject]))
		    DestroyDynamicObject(pMeter[nextid][parkObject]);

		if (IsValidDynamic3DTextLabel(pMeter[nextid][parkLabel]))
		    DestroyDynamic3DTextLabel(pMeter[nextid][parkLabel]);

		pMeter[nextid][parkObject] = CreateDynamicObject(1269, pMeter[nextid][parkX], pMeter[nextid][parkY], pMeter[nextid][parkZ] - 0.50, 0.0, 0.0, pMeter[nextid][parkA]);
		pMeter[nextid][parkLabel] = CreateDynamic3DTextLabel("> PARKMETRE OLUÞTURULDU", 0xFF6347AA, pMeter[nextid][parkX], pMeter[nextid][parkY], pMeter[nextid][parkZ], 3.0);
	}
	return nextid;
}

stock EraseParkMeter(id)
{
	new query[92];

	if (pMeter[id][parkID] > - 1)
	{
		if (IsValidDynamicObject(pMeter[id][parkObject]))
		    DestroyDynamicObject(pMeter[id][parkObject]);

		if (IsValidDynamic3DTextLabel(pMeter[id][parkLabel]))
		    DestroyDynamic3DTextLabel(pMeter[id][parkLabel]);

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `pmeters` WHERE `id` = %d", pMeter[id][parkID]);
		mysql_tquery(dbHandle, query);

		pMeter[id][parkID] = -1;
		pMeter[id][parkX] = 0.0;
		pMeter[id][parkY] = 0.0;
		pMeter[id][parkZ] = 0.0;
		pMeter[id][parkA] = 0.0;
		pMeter[id][parkAvailable] = true;
		pMeter[id][parkVehicle] = 0;
	}
	return 1;
}

this::LoadParkMeters()
{
    if (cache_num_rows() == 0) 
		return 1;
        
    new
        idx
	;

    for (new i, j = cache_num_rows(); i != j; i++)
    {
		cache_get_value_int(i, "id", pMeter[i][parkID]);
		cache_get_value_float(i, "x", pMeter[i][parkX]);
		cache_get_value_float(i, "y", pMeter[i][parkY]);
	    cache_get_value_float(i, "z", pMeter[i][parkZ]);
		cache_get_value_float(i, "angle", pMeter[i][parkA]);
		pMeter[i][parkAvailable] = true;
		pMeter[i][parkVehicle] = 0;

		if (IsValidDynamicObject(pMeter[i][parkObject]))
		    DestroyDynamicObject(pMeter[i][parkObject]);

		if (IsValidDynamic3DTextLabel(pMeter[i][parkLabel]))
		    DestroyDynamic3DTextLabel(pMeter[i][parkLabel]);

		pMeter[i][parkObject] = CreateDynamicObject(1269, pMeter[i][parkX], pMeter[i][parkY], pMeter[i][parkZ] - 0.50, 0.0, 0.0, pMeter[i][parkA]);
		pMeter[i][parkLabel] = CreateDynamic3DTextLabel("_", 0xFF6347AA, pMeter[i][parkX], pMeter[i][parkY], pMeter[i][parkZ], 3.0);

		idx++;
	}

	printf("[Parkometers] Rows - %i. Load - %i. Time - 0 ms.", cache_num_rows(), idx);
	return 1;
}

stock ParkMeter_Nearest(playerid)
{
	new id = -1;

	for(new i; i < MAX_METERS; i++)
	{
		if (pMeter[i][parkID] > -1 && IsPlayerInRangeOfPoint(playerid, 3.0, pMeter[i][parkX], pMeter[i][parkY], pMeter[i][parkZ]))
		{
		    if (id != -1) { 
				new Float: x, Float: y, Float: z;

				GetPlayerPos(playerid, x, y, z);
				if (GetDistanceBetweenPoints(x, y, z, pMeter[i][parkX], pMeter[i][parkY], pMeter[i][parkZ]) <
					GetDistanceBetweenPoints(x, y, z, pMeter[id][parkX], pMeter[id][parkY], pMeter[id][parkZ])) id = i;
			}
			else id = i;
		}
	}
	return id;
}

stock GetClosestVehicleInObject(objectid)
{
	new vid = -1, Float:x, Float:y, Float:z, Float:distance;
	GetDynamicObjectPos(objectid, x, y, z);
	for(new i; i < MAX_VEHICLES; i++)
	{
	    if (IsValidVehicle(i) && (!IsAPlane(i) || !IsABiker(i) || !IsAHelicopter(i) || !IsABoat(i) || !IsABicycle(i)))
	    {
	        distance = GetVehicleDistanceFromPoint(i, x, y, z);
	        if (distance <= 6)
	        {
				vid = i;
				break;
	        }
	    }
	}
	return vid;
}