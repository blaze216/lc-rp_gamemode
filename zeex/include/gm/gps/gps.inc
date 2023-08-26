GPS_OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if (IsValidDynamicCP(pTemp[playerid][pWaypoint]) && checkpointid == pTemp[playerid][pWaypoint])
	{
	    GameTextForPlayer(playerid, "~r~X", 3000, 3);
	    DisableWaypoint(playerid);
	}
    return 1;
}