enum OBJECTS_ENUM
{
	oID,
	oModel,
	oObject,
	oName[32],
	oInt,
	oVW,
	Float:oPosX,
	Float:oPosY,
	Float:oPosZ,
	Float:oPosRX,
	Float:oPosRY,
	Float:oPosRZ,
	oObjectOn
}
new ObjectsInfo[MAX_OBJECTS][OBJECTS_ENUM];

forward LoadDynamicObjects();
forward LoadObjectTexture(objectid);
forward OnObjectTextureInsert(playerid, id, slot, model, txdname[], texturename[]);
forward OnObjectInsert(ObjectID);

public LoadDynamicObjects()
{
	new rows = cache_num_rows(), time = GetTickCount(), total, query[256];

	if (!rows)
	{
	    print("[Objeler] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", ObjectsInfo[i][oID]);
	    cache_get_value_int(i, "model", ObjectsInfo[i][oModel]);
		cache_get_value_float(i, "posx", ObjectsInfo[i][oPosX]);
	    cache_get_value_float(i, "posy", ObjectsInfo[i][oPosY]);
	    cache_get_value_float(i, "posz", ObjectsInfo[i][oPosZ]);
	    cache_get_value_float(i, "posrx", ObjectsInfo[i][oPosRX]);
	    cache_get_value_float(i, "posry", ObjectsInfo[i][oPosRY]);
	    cache_get_value_float(i, "posrz", ObjectsInfo[i][oPosRZ]);
	    cache_get_value_int(i, "interior", ObjectsInfo[i][oInt]);
	    cache_get_value_int(i, "virworld", ObjectsInfo[i][oVW]);

        ObjectsInfo[i][oObject] = CreateDynamicObject(ObjectsInfo[i][oModel], ObjectsInfo[i][oPosX], ObjectsInfo[i][oPosY], ObjectsInfo[i][oPosZ], ObjectsInfo[i][oPosRX], ObjectsInfo[i][oPosRY], ObjectsInfo[i][oPosRZ], ObjectsInfo[i][oVW], ObjectsInfo[i][oInt], -1, 200.0);
		ObjectsInfo[i][oObjectOn] = 1;
		
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `objects_texture` WHERE `objectid` = %i", ObjectsInfo[i][oID]);
		mysql_tquery(dbHandle, query, "LoadObjectTexture", "i", i);
	
		total++;
	}
	printf("[Objeler] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

public OnObjectInsert(ObjectID)
{
	ObjectsInfo[ObjectID][oID] = cache_insert_id();
	return 1;
}

public LoadObjectTexture(objectid)
{
	new rows = cache_num_rows(), slot, model, txdname[32], texturename[32];
	    
	if (!rows) return 1;
	    
    for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "slot", slot);
	    cache_get_value_int(i, "model", model);
		cache_get_value(i, "txd_name", txdname, 32);
		cache_get_value(i, "texture_name", texturename, 32);

		if (IsValidDynamicObject(ObjectsInfo[objectid][oObject])) SetDynamicObjectMaterial(ObjectsInfo[objectid][oObject], slot, model, txdname, texturename, 0);
	}
	return 1;
}

public OnObjectTextureInsert(playerid, id, slot, model, txdname[], texturename[])
{
	if (cache_num_rows())																			return SendErrorMessage(playerid, "Slot %i dokusu zaten belirlenmiþ. (/editobject deltexture - remove texture)", slot);
    if (!SetDynamicObjectMaterial(ObjectsInfo[id][oObject], slot, model, txdname, texturename, 0))	return SendErrorMessage(playerid, "Objenin texture durumu ayarlanýrken problem oluþtu.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `objects_texture` (objectid, slot, model, txd_name, texture_name) VALUES (%i,%i,%i,'%e','%e')", ObjectsInfo[id][oID], slot, model, txdname, texturename);
	mysql_tquery(dbHandle, query);

	SendClientMessageEx(playerid, COLOR_GREEN, "Obje texture durumunu [ID: %i] baþarýyla deðiþtirdin [Slot: %i | Model ID: %i | TXD Ýsmi: %s | Texture Ýsmi: %s]", id, slot, model, txdname, texturename);
	return 1;
}

AddObjectToFile(objectid, modelid, interior, virworld, Float:x, Float:y, Float:z)
{
    new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `objects` (model, posx, posy, posz, posrx, posry, posrz, interior, virworld) VALUES (%i, %f, %f, %f, 0.0, 0.0, 0.0, %i, %i)",modelid,x,y,z,interior,virworld);
	mysql_tquery(dbHandle, query, "OnObjectInsert", "d", objectid);
	return 1;
}

Object_Nearest(playerid)
{
	for(new i; i != MAX_OBJECTS; i++)
	{
	    if (GetWorld(playerid) == ObjectsInfo[i][oVW] && ObjectsInfo[i][oInt] == GetInterior(playerid) && IsPlayerInRangeOfPoint(playerid, 5.0, ObjectsInfo[i][oPosX], ObjectsInfo[i][oPosY], ObjectsInfo[i][oPosZ]) && ObjectsInfo[i][oObjectOn])
		{
			return i;
		}
	}
	return -1;
}

Obj_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

	if (GetPVarInt(playerid, #edit_object) && ObjectsInfo[GetPVarInt(playerid, #edit_object)-1][oObject] == objectid && ObjectsInfo[GetPVarInt(playerid, #edit_object)-1][oObjectOn])
	{
		if (response == EDIT_RESPONSE_FINAL)
		{
		    new objid = GetPVarInt(playerid, #edit_object)-1;

	    	DeletePVar(playerid, #edit_object);
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			GetDynamicObjectPos(objectid, ObjectsInfo[objid][oPosX], ObjectsInfo[objid][oPosY], ObjectsInfo[objid][oPosZ]);
			GetDynamicObjectRot(objectid, ObjectsInfo[objid][oPosRX], ObjectsInfo[objid][oPosRY], ObjectsInfo[objid][oPosRZ]);
			
            new query[256 + 56];
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `objects` SET `posx` = %f, `posy` = %f, `posz` = %f, `posrx` = %f, `posry` = %f, `posrz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, ObjectsInfo[objid][oID]);
			mysql_tquery(dbHandle, query);
	
  			SendSyntaxMessage(playerid, "Obje pozisyonu [ID: %i] baþarýyla düzenlendi.", objid);
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
	    	DeletePVar(playerid, #edit_object);
			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		}
	}
	return 1;
}

Ob_OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT objectid)
{
	if (GetPVarInt(playerid, #edit_objects) == 1)
	{
	    DeletePVar(playerid, #edit_objects);

	    new objid = -1;

		for(new i; i != MAX_OBJECTS; i++)
		{
		    if (!ObjectsInfo[i][oID] || !ObjectsInfo[i][oObjectOn] || ObjectsInfo[i][oObject] != objectid) continue;

			objid = i;
			break;
		}

		if (objid == -1)	return SendErrorMessage(playerid, "Bu obje admin komutuyla oluþturulmamýþ.");

        SetPVarInt(playerid, #edit_object, objid+1);
		EditDynamicObject(playerid, ObjectsInfo[objid][oObject]);
	}
	return 1;
}

Obj_OnGameModeInit()
{
	return mysql_tquery(dbHandle, "SELECT * FROM `objects`", "LoadDynamicObjects");
}