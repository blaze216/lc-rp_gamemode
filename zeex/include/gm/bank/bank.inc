ATM_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rz)
{
    new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if (GetPVarInt(playerid, #edit_atm) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
	    new id = GetPVarInt(playerid, #edit_atm)-1;
	    
		DeletePVar(playerid, #edit_atm);
	    if (id < 0 || id >= MAX_ATMS || !ATMInfo[id][atmID]) return SendErrorMessage(playerid, "ATM bulunamadý");
	    if (objectid != ATMInfo[id][atmObject])				return SendErrorMessage(playerid, "ATM düzenlenirken hata oluþtu.");

		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, 0.0, 0.0, rz);

        GetDynamicObjectPos(objectid, ATMInfo[id][atmPosX], ATMInfo[id][atmPosY], ATMInfo[id][atmPosZ]);
        ATMInfo[id][atmPosRZ] = rz;
        
		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `atms` SET `posx`=%f,`posy`=%f,`posz`=%f,`posrz`=%f WHERE `id`=%i", x, y, z, rz, ATMInfo[id][atmID]);
		mysql_tquery(dbHandle, query);

		SendAdmMessageToPlayer(playerid, "ATM pozisyonu deðiþtirildi: [ID:%i]", id);
	} //î
    return 1;
}

ATM_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `atms`", "LoadDynamicATMS");
}