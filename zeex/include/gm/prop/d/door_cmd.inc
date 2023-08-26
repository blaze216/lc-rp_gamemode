CMD:kapi(playerid, params[])
{
	new id, bid;

	if ((bid = GetNearBuilding(playerid)) == -1) 		return SendErrorMessage(playerid, "Herhangi bir binanýn içinde olmalýsýn!");
	if ((id = GetNearInBuilding(playerid, id)) == -1) 	return SendErrorMessage(playerid, "Herhangi bir binanýn içinde olmalýsýn!");

	switch(bid)
	{
		case 0: HouseDoorMove(id, playerid);
		case 1: BizDoorMove(id, playerid);
		case 2: GarageDoorMove(id, playerid);
	}
		
	return 1;
}

HouseDoorMove(id, playerid)
{
	for(new i = 0; i < MAX_FURNITURE; i++)
	{
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, HFurn[id][i][fPosX], HFurn[id][i][fPosY], HFurn[id][i][fPosZ]) || 0 == HFurn[id][i][fOn] || !isHouseDoor(HFurn[id][i][fModel])) continue;

		if (!HFurn[id][i][fOpened])
		{
			if (HFurn[id][i][fLocked]) return SendErrorMessage(playerid, "Kapý kilitli.");

			MoveDynamicObject(HFurn[id][i][fObject], HFurn[id][i][fPosX], HFurn[id][i][fPosY], HFurn[id][i][fPosZ], 1.5, HFurn[id][i][fPosRX], HFurn[id][i][fPosRY], HFurn[id][i][fPosRZ]-90.0);
			HFurn[id][i][fOpened] = 1;
			return 1;
		}
		else
		{
			HFurn[id][i][fOpened] = 0;
			MoveDynamicObject(HFurn[id][i][fObject], HFurn[id][i][fPosX], HFurn[id][i][fPosY], HFurn[id][i][fPosZ], 1.5, HFurn[id][i][fPosRX], HFurn[id][i][fPosRY], HFurn[id][i][fPosRZ]);
			return 1;
		}
	}
	return 1;
}

BizDoorMove(id, playerid)
{
	for(new i = 0; i < MAX_FURNITURE; i++)
	{
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, BFurn[id][i][fPosX], BFurn[id][i][fPosY], BFurn[id][i][fPosZ]) || 0 == BFurn[id][i][fOn] || !isHouseDoor(BFurn[id][i][fModel])) continue;

		if (!BFurn[id][i][fOpened])
		{
			if (BFurn[id][i][fLocked]) return SendErrorMessage(playerid, "Kapý kilitli.");

			MoveDynamicObject(BFurn[id][i][fObject], BFurn[id][i][fPosX], BFurn[id][i][fPosY], BFurn[id][i][fPosZ], 1.5, BFurn[id][i][fPosRX], BFurn[id][i][fPosRY], BFurn[id][i][fPosRZ]-90.0);
			BFurn[id][i][fOpened] = 1;
			return 1;
		}
		else
		{
			BFurn[id][i][fOpened] = 0;
			MoveDynamicObject(BFurn[id][i][fObject], BFurn[id][i][fPosX], BFurn[id][i][fPosY], BFurn[id][i][fPosZ], 1.5, BFurn[id][i][fPosRX], BFurn[id][i][fPosRY], BFurn[id][i][fPosRZ]);
			return 1;
		}
	}
	return 1;
}

GarageDoorMove(id, playerid)
{
	for(new i = 0; i < MAX_FURNITURE; i++)
	{
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, GFurn[id][i][fPosX], GFurn[id][i][fPosY], GFurn[id][i][fPosZ]) || 0 == GFurn[id][i][fOn] || !isHouseDoor(GFurn[id][i][fModel])) continue;

		if (!GFurn[id][i][fOpened])
		{
			if (GFurn[id][i][fLocked]) return SendErrorMessage(playerid, "Kapý kilitli.");

			MoveDynamicObject(GFurn[id][i][fObject], GFurn[id][i][fPosX], GFurn[id][i][fPosY], GFurn[id][i][fPosZ], 1.5, GFurn[id][i][fPosRX], GFurn[id][i][fPosRY], GFurn[id][i][fPosRZ]-90.0);
			GFurn[id][i][fOpened] = 1;
			return 1;
		}
		else
		{
			GFurn[id][i][fOpened] = 0;
			MoveDynamicObject(GFurn[id][i][fObject], GFurn[id][i][fPosX], GFurn[id][i][fPosY], GFurn[id][i][fPosZ], 1.5, GFurn[id][i][fPosRX], GFurn[id][i][fPosRY], GFurn[id][i][fPosRZ]);
			return 1;
		}
	}
	return 1;
}