Box_OnPlayerLeaveArea(playerid, areaid)
{
    new userid = pTemp[playerid][pBoombox];
	if (userid != INVALID_PLAYER_ID && areaid == BoomboxInfo[userid][bArea])
	{
	    pTemp[playerid][pBoombox] = INVALID_PLAYER_ID;
        StopAudioStreamForPlayer(playerid);
	    return 1;
	}
    return 1;
}

Box_OnPlayerEnterArea(playerid, areaid)
{
	if (!IsPlayerInAnyVehicle(playerid))
	{
		for(new i; i < Iter_Count(boomboxIter); i++)
		{
	    	if (!BoomboxInfo[i][bUsed] || areaid != BoomboxInfo[i][bArea])	continue;
	        
        	pTemp[playerid][pBoombox] = i;
        	StopAudioStreamForPlayer(playerid);
        	
        	if (strlen(BoomboxInfo[i][bUrl])) PlayAudioStreamForPlayer(playerid, BoomboxInfo[i][bUrl], BoomboxInfo[i][bPosX], BoomboxInfo[i][bPosY], BoomboxInfo[i][bPosZ], 50.0, 1);

			break;
		}
	}
	return 1;
}

Box_OnPlayerStateChange(playerid, newstate)
{
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new vehicle = GetPlayerVehicleID(playerid), Float:x, Float:y, Float:z;

		GetVehiclePos(vehicle, x, y, z);

	    if (pTemp[playerid][pBoombox] != INVALID_PLAYER_ID)
	    {
	        pTemp[playerid][pBoombox] = INVALID_PLAYER_ID;
			StopAudioStreamForPlayer(playerid);
	    }

		if (VehicleInfo[vehicle][carRadioOn] == 1) PlayAudioStreamForPlayer(playerid, VehicleInfo[vehicle][carRadioURL]);
	}
	return 1;
}

Radio_OnGameModeInit()
{
	return mysql_tquery(dbHandle, "SELECT * FROM `radios`", "LoadDynamicRadios");
}

Box_OnPlayerExitVehicle(playerid)
{
	foreach(new i : Player)
	{
    	if (!IsPlayerLogged(i) || !BoomboxInfo[i][bUsed] || !IsPlayerInDynamicArea(playerid, BoomboxInfo[i][bArea])) continue;

		pTemp[playerid][pBoombox] = i;
 		StopAudioStreamForPlayer(playerid);

		if (strlen(BoomboxInfo[i][bUrl])) PlayAudioStreamForPlayer(playerid, BoomboxInfo[i][bUrl], BoomboxInfo[i][bPosX], BoomboxInfo[i][bPosY], BoomboxInfo[i][bPosZ], 50.0, 1);

		break;
	}
	return 1;
}