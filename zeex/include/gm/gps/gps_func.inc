Waypoint_Set(playerid, Float: x, Float: y, Float: z, Float: radius = 3.0)
{
	if (IsValidDynamicCP(pTemp[playerid][pWaypoint]))
	{
		DestroyDynamicCP(pTemp[playerid][pWaypoint]);
        pTemp[playerid][pWaypoint] = 0;
	}
    
    pTemp[playerid][pWaypoint] = CreateDynamicCP(x, y, z, radius, 0, 0, playerid, 15000.0);
    TogglePlayerDynamicCP(playerid, pTemp[playerid][pWaypoint], true);
    Streamer_Update(playerid, STREAMER_TYPE_CP);
	return 1;
}

DisableWaypoint(playerid)
{
    if (IsValidDynamicCP(pTemp[playerid][pWaypoint])) DestroyDynamicCP(pTemp[playerid][pWaypoint]);

    pTemp[playerid][pWaypoint] = 0;
	return 1;
}