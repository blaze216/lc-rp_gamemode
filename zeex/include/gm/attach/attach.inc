Attach_EditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if (GetPVarInt(playerid, #edit_attach) == 1)
	{
	    DeletePVar(playerid, #edit_attach);

	    if (index < 0 || index > 4)
	        return SendErrorMessage(playerid, "Aksesuarlar/kýyafetler düzenlenirken hata oluþtu.");

		if (response)
		{
		    AttachInfo[playerid][index][aBone] = boneid;
			AttachInfo[playerid][index][aOffsetX] = fOffsetX;
			AttachInfo[playerid][index][aOffsetY] = fOffsetY;
			AttachInfo[playerid][index][aOffsetZ] = fOffsetZ;
			AttachInfo[playerid][index][aRotX] = fRotX;
			AttachInfo[playerid][index][aRotY] = fRotY;
			AttachInfo[playerid][index][aRotZ] = fRotZ;
			AttachInfo[playerid][index][aScaleX] = fScaleX;
			AttachInfo[playerid][index][aScaleY] = fScaleY;
			AttachInfo[playerid][index][aScaleZ] = fScaleZ;

			UpdatePlayerAttach(playerid, index, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, boneid);

			RemovePlayerAttachedObject(playerid, index);
			SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
		}
		else
		{
			RemovePlayerAttachedObject(playerid, index);
			SetPlayerAttachedObject(playerid, index, modelid, boneid, AttachInfo[playerid][index][aOffsetX], AttachInfo[playerid][index][aOffsetY], AttachInfo[playerid][index][aOffsetZ], AttachInfo[playerid][index][aRotX], AttachInfo[playerid][index][aRotY], AttachInfo[playerid][index][aRotZ], AttachInfo[playerid][index][aScaleX], AttachInfo[playerid][index][aScaleY], AttachInfo[playerid][index][aScaleZ]);
		}
		pc_cmd_aksesuar(playerid, "");
		return 1;
	}

	if (GetPVarInt(playerid, #buy_attach) != 0)
	{
	    new price = GetPVarInt(playerid, #buy_attach);
 		DeletePVar(playerid, #buy_attach);

	    if (index < 0 || index > 4)
	        return SendErrorMessage(playerid, "Aksesuarlar/kýyafetler satýn alýnýrken hata oluþtu.");

		if (response && GetCash(playerid) >= price)
		{
			AttachInfo[playerid][index][aBone] = boneid;
			AttachInfo[playerid][index][aOffsetX] = fOffsetX;
			AttachInfo[playerid][index][aOffsetY] = fOffsetY;
			AttachInfo[playerid][index][aOffsetZ] = fOffsetZ;
			AttachInfo[playerid][index][aRotX] = fRotX;
			AttachInfo[playerid][index][aRotY] = fRotY;
			AttachInfo[playerid][index][aRotZ] = fRotZ;
			AttachInfo[playerid][index][aScaleX] = fScaleX;
			AttachInfo[playerid][index][aScaleY] = fScaleY;
			AttachInfo[playerid][index][aScaleZ] = fScaleZ;

			UpdatePlayerAttach(playerid, index, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, boneid);

			AttachInfo[playerid][index][aUsed] = 1;

   			RemovePlayerAttachedObject(playerid, index);
   			SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);

			GiveCash(playerid, -price);
			InfoMSG(playerid, "~w~Yeni bir urun aldiniz", 5);
			return 1;
		}
		else
		{
			RemovePlayerAttachFromSlot(playerid, index);
			InfoMSG(playerid, "~w~Satin almayi iptal ettiniz", 5);
		} //î
	}
    return 1;
}

Attach_OnPlayerKeyStateChange(playerid, newkeys)
{
	if (HOLDING(KEY_SECONDARY_ATTACK) && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS) && pTemp[playerid][pPizzaBoy])
	{
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		return 1;
	}

    if (HOLDING(KEY_SECONDARY_ATTACK) && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS) && GetPVarInt(playerid, #use_ganja))
	{
	    DeletePVar(playerid, #use_ganja);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		return 1;
	}
	return 1;
}