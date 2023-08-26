BB_OnPlayerModelSelection(playerid, extraid, modelid, response)
{
    if (extraid == MODEL_SELECTION_BB && response == MODEL_RESPONSE_SELECT) 
	{
		if (response)
        {
             if (GetUnusedBillBoard() == -1) return SendErrorMessage(playerid, "Billboard sýnýrý aþýldý!");
	         
			 new Float:X, Float:Y, Float:Z;
	         GetPlayerPos(playerid, X, Y, Z);

	         CreateBillBoard(playerid, X, Y, Z, 0.0, 0.0, 0.0, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid),modelid,GetPVarInt(playerid, #BB_COST));
			 DeletePVar(playerid, #BB_COST);
		}
		else DeletePVar(playerid, #BB_COST);

		return 1;
	}
    return 1;
} //î

BB_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
	GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
	
	if (GetPVarInt(playerid, "BB:Edit") && response == EDIT_RESPONSE_FINAL)
	{
		new i = GetPVarInt(playerid, "BB:Edit")-1;

		BillboardInfo[i][bbPosX] = x; 
		BillboardInfo[i][bbPosY] = y; 
		BillboardInfo[i][bbPosZ] = z; 
		BillboardInfo[i][bbPosRX] = rx;
		BillboardInfo[i][bbPosRY] = ry;
		BillboardInfo[i][bbPosRZ] = rz;
		BillboardInfo[i][bbInt] = GetPlayerInterior(playerid);
		BillboardInfo[i][bbVW] = GetPlayerVirtualWorld(playerid);
				
        Save_BB(i);
		DeletePVar(playerid, "BB:Edit");

		if (IsValidDynamicObject(BillboardInfo[i][bbObject])) DestroyDynamicObject(BillboardInfo[i][bbObject]);
		BillboardInfo[i][bbObject] = CreateDynamicObject(BillboardInfo[i][bbModel], BillboardInfo[i][bbPosX], BillboardInfo[i][bbPosY], BillboardInfo[i][bbPosZ], BillboardInfo[i][bbPosRX], BillboardInfo[i][bbPosRY], BillboardInfo[i][bbPosRZ], BillboardInfo[i][bbInt], BillboardInfo[i][bbVW]);
		
		SetDynamicObjectMaterial(BillboardInfo[i][bbObject], 0, -1, "none", "none", 0xFFFFFFFF);
		SetDynamicObjectMaterialText(BillboardInfo[i][bbObject], 0, BillboardInfo[i][bbText], OBJECT_MATERIAL_SIZE_512x128,"Arial", 28, 0, 0xFF000000, 0x0FFFFFFF, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
		return 1;
	}
	if (GetPVarInt(playerid, "BB:Edit") &&  response == EDIT_RESPONSE_CANCEL)
	{
		SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
		SetDynamicObjectPos(objectid, oldRotX, oldRotY, oldRotZ);		
		DeletePVar(playerid, "BB:Edit");
	}
	return 1;
}

CheckBillBoard()
{
	new time = gettime();

	for(new i = 0; i < MAX_BILLBOARDS; i++)
	{
	    if (!BillboardInfo[i][bbActive] || !BillboardInfo[i][bbRentBy]) continue;
		if (BillboardInfo[i][bbRentDate] < time) BillBoard_Unrent(i);
	}

	return 1;
}