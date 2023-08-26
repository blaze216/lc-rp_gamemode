Fire_Check(playerid)
{
	new Float: health, mes[64];

	for(new i = 0; i != MAX_FIRES; i++)
	{
	    if (FiresInfo[i][fireOn] == 0 || GetWorld(playerid) != FiresInfo[i][fireVW] || GetInterior(playerid) != FiresInfo[i][fireInt]) continue;

        if (PlayerInfo[playerid][pInjured] == 0 && IsPlayerInRangeOfPoint(playerid, 1.5, FiresInfo[i][firePos][0], FiresInfo[i][firePos][1], FiresInfo[i][firePos][2]) && 0 == IsPlayerInAnyVehicle(playerid))
        {
            AntiCheatGetHealth(playerid, health);

			if (GetPlayerSkin(playerid) == 277 || GetPlayerSkin(playerid) == 278 || GetPlayerSkin(playerid) == 279)
			{
                PlayerInfo[playerid][pHealth] = health - 1.0;
                RecordDamage(-1, playerid, 51, BODY_PART_TORSO, 1.0, 0);
			}
			else
			{
				PlayerInfo[playerid][pHealth] = health - 3.5;
                RecordDamage(-1, playerid, 51, BODY_PART_TORSO, 3.5, 0);
			}

			if (health - 3.5 <= 5.0) SilahlariKaydet(playerid), SetTimerEx("InjuredPlayer", 1200, 0, "iii", playerid, INVALID_PLAYER_ID, 51);
        }

        if (!HoldingKey(playerid, KEY_FIRE) || (AntiCheatGetWeapon(playerid) != 42 && GetVehicleModel(GetPlayerVehicleID(playerid)) != 407))						return 1;
	    if (!IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 5.0, FiresInfo[i][firePos][0], FiresInfo[i][firePos][1], FiresInfo[i][firePos][2]))	continue;
        if (IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 30.0, FiresInfo[i][firePos][0], FiresInfo[i][firePos][1], FiresInfo[i][firePos][2]))	continue;

		FiresInfo[i][fireHealth]--;
		if (FiresInfo[i][fireHealth] > 1)
		{
			format(mes, sizeof(mes), "(ID:{FFFFFF}%d{FF6347})\nCan:{FFFFFF}%i", i, FiresInfo[i][fireHealth]);
			UpdateDynamic3DTextLabelText(FiresInfo[i][fireLabel], 0xFF6347FF, mes);
		}
		else
		{
			DeleteFire(i);
		}
	}
	return 1;
}

DeleteFire(id)
{
	if (FiresInfo[id][fireOn] != 1)						return 1;

    FiresInfo[id][fireOn] = 0;

    if (IsValidDynamicObject(FiresInfo[id][fireObj]))	DestroyDynamicObject(FiresInfo[id][fireObj]);

    if (IsValidDynamic3DTextLabel(FiresInfo[id][fireLabel]))
	{
		DestroyDynamic3DTextLabel(FiresInfo[id][fireLabel]);
        FiresInfo[id][fireLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	return 1;
}

GetNearFire(Float:x, Float:y, Float:z, int = 0, world = 0, Float:radius = 2.0)
{
	for(new i; i != MAX_FIRES; i++)
	{
	    if (FiresInfo[i][fireOn] == 0) continue;
	    if (world == FiresInfo[i][fireVW] && int == FiresInfo[i][fireInt] && GetDistanceBetweenPoints(x,y,z,FiresInfo[i][firePos][0], FiresInfo[i][firePos][1], FiresInfo[i][firePos][2]) <= radius)
		{
			return i;
		}
	}
	return -1;
}

DeleteNearFire(playerid)
{
	new count = 0;
	for(new i = 0; i != MAX_FIRES; i++)
	{
	    if (FiresInfo[i][fireOn] == 0 || GetWorld(playerid) != FiresInfo[i][fireVW] || GetInterior(playerid) != FiresInfo[i][fireInt]) continue;
        if (IsPlayerInRangeOfPoint(playerid, 2.5, FiresInfo[i][firePos][0], FiresInfo[i][firePos][1], FiresInfo[i][firePos][2]) && 0 == IsPlayerInAnyVehicle(playerid))
        {
			count++;
			DeleteFire(i);
		}
	}
	if (count)	return 1;
	return 0;
}

CrossFire(idx)
{
	new type;
	if ((type = GetXYZNearBuilding(FiresInfo[idx][firePos][0],FiresInfo[idx][firePos][1],FiresInfo[idx][firePos][2],30.0,30.0,FiresInfo[idx][fireInt],FiresInfo[idx][fireVW])) == -1) return 0;

	new building;
	switch(type)
	{
		case 0: {
			building = GetXYZNearHouse(FiresInfo[idx][firePos][0],FiresInfo[idx][firePos][1],FiresInfo[idx][firePos][2],30.0,30.0,FiresInfo[idx][fireInt],FiresInfo[idx][fireVW]);
			//if (gettime()-HouseInfo[building][hFireTimer] >= 0)
			if (building != -1) CreateFireInHouse(building);
		}
		case 1: {
			building = GetXYZNearBiz(FiresInfo[idx][firePos][0],FiresInfo[idx][firePos][1],FiresInfo[idx][firePos][2],30.0,30.0,FiresInfo[idx][fireInt],FiresInfo[idx][fireVW]);
			//if (gettime()-BizInfo[building][bFireTimer] >= 0)
			if (building != -1) CreateFireInBiz(building);
		}
		case 2: {
			building = GetXYZNearGarage(FiresInfo[idx][firePos][0],FiresInfo[idx][firePos][1],FiresInfo[idx][firePos][2],30.0,30.0,FiresInfo[idx][fireInt],FiresInfo[idx][fireVW]);
			//if (gettime()-GarageInfo[building][gFireTimer] >= 0)
			if (building != -1) CreateFireInGarage(building);
		}
	}
	return 1;
}
