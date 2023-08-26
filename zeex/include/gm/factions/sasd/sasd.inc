APB_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `apbs`", "LoadDynamicAPB");
}

stock GetDriverID(vehicleid) //Araç sürenin idini verir
{
    foreach(new i : Player)
    {
    if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER) return i;
    }
    return INVALID_PLAYER_ID;
}

Police_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
		SetPlayerArmedWeapon(playerid, 0);
	}

    if (IsAHelicopter(vehicleid) && ispassenger)
    {
        SetPVarInt(playerid, #CHOPID, GetPlayerVehicleID(playerid));
        if(GetPVarInt(playerid, #SWATROPE)) DeletePVar(playerid, #SWATROPE);
    }
    return 1;
}

Police_OnPlayerExitVehicle(playerid)
{
    if (GetPVarInt(playerid, #CHOPID))   DeletePVar(playerid, #CHOPID);
    if (GetPVarInt(playerid, #SWATROPE)) DeletePVar(playerid, #SWATROPE);
    return 1;
}

Police_OnPlayerDisconnect(playerid)
{
    if (GetPVarInt(playerid, #SWATROPE))
    {
        for(new i = 0; i < MAX_ROPE_LENGTH; i++) DestroyObject(RopesInfo[playerid][i]);
    }
    return 1;
}
 
Police_OnPlayerDeath(playerid)
{
    if (GetPVarInt(playerid, #SWATROPE))
    {
        for(new i = 0; i < MAX_ROPE_LENGTH; i++) DestroyObject(RopesInfo[playerid][i]);

        DeletePVar(playerid, #SWATROPE);
        DisablePlayerCheckpoint(playerid);
    }
    return 1;
}
 
Police_OnVehicleDeath(vehicleid)
{
    if(IsAHelicopter(vehicleid))
    {
        foreach (new i : Player)
        {
            if(GetPVarInt(i, #CHOPID) == vehicleid && GetPVarInt(i, #SWATROPE))
            {
                for(new j = 0; j < MAX_ROPE_LENGTH; j++) DestroyObject(RopesInfo[i][j]);
                DisablePlayerCheckpoint(i);
                TogglePlayerControllable(i, true);
                ClearAnimations(i);

                DeletePVar(i, #SWATROPE);
            }
        }
    }
    return 1;
}