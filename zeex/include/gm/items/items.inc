Item_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
	
	GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

	if (GetPVarInt(playerid, #edit_item) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
	    new id = GetPVarInt(playerid, #edit_item)-1;
	    DeletePVar(playerid, #edit_item);

	    if (GetDistanceBetweenPoints(x, y, z, ItemDrop[id][dropPosX], ItemDrop[id][dropPosY], ItemDrop[id][dropPosZ]) > 5.0)
	    {
     		SetDynamicObjectPos(ItemDrop[id][dropObject], ItemDrop[id][dropPosX], ItemDrop[id][dropPosY], ItemDrop[id][dropPosZ]);
        	SetDynamicObjectRot(ItemDrop[id][dropObject], ItemDrop[id][dropPosRX], ItemDrop[id][dropPosRY], ItemDrop[id][dropPosRZ]);
	        return SendErrorMessage(playerid, "Obje baþlangýç konumundan çok uzakta."); //îøèáêà
	    }

	    if (objectid != ItemDrop[id][dropObject]) return SendErrorMessage(playerid, "Öðe düzenlenirken hata oluþtu.");

		SetDynamicObjectPos(ItemDrop[id][dropObject], x, y, z);
		SetDynamicObjectRot(ItemDrop[id][dropObject], rx, ry, rz);

        GetDynamicObjectPos(ItemDrop[id][dropObject], ItemDrop[id][dropPosX], ItemDrop[id][dropPosY], ItemDrop[id][dropPosZ]);
        GetDynamicObjectRot(ItemDrop[id][dropObject], ItemDrop[id][dropPosRX], ItemDrop[id][dropPosRY], ItemDrop[id][dropPosRZ]);

		ItemDrop_Update(id);
	}
	return 1;
}