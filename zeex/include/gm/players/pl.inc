Player_OnPlayerUpdate(playerid)
{
    if (IsPlayerNPC(playerid) || !IsPlayerLogged(playerid)) 	return 1;
	
    if (IsPlayerAFK(playerid))
	{
	    if (!(PlayerInfo[playerid][pSettings] & togAFK))
	    SendSyntaxMessage(playerid, "%i saniye boyunca AFK kaldýnýz.", pTemp[playerid][pDarkAFK]-2);
	}

	for(new i = 0; i < MAX_ONAYLIHOOD; i++) if(IsPlayerInRangeOfPoint(playerid, 60.0, OnayliHoodlar[i][hoodPos][0],OnayliHoodlar[i][hoodPos][1],OnayliHoodlar[i][hoodPos][2]))
	{
		new str[100];
		format(str, 100, "Bu bolge %s isimli birlige ait.", OnayliHoodlar[i][hoodAd]);
		InfoMSG(playerid, str, 5);
	}    

	if(IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid), location[MAX_ZONE_NAME];
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
		for(new i; i != MAX_SPIKE; i++)
	    {
			if (!SpikeInfo[i][sCreated] && !IsPlayerInRangeOfPoint(playerid, 4.0, SpikeInfo[i][sX], SpikeInfo[i][sY], SpikeInfo[i][sZ])) continue;
			new Float:objectX, Float:objectY, Float:objectZ;			
			GetDynamicObjectPos(SpikeInfo[i][sObject], objectX, objectY, objectZ);

			if(IsPlayerInRangeOfPoint(playerid, 4.0, objectX, objectY, objectZ))
			{
				PlaySound(playerid, 1190);
				BumpTierBlowout(vehicleid);

                SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* HQ: %s[%s] model araç %s lokasyonunda çivi üzerinden geçti ve lastikleri patladý.", GetVehicleModelName(VehicleInfo[vehicleid][carModel]), VehicleInfo[vehicleid][carPlate], location);

			    SpikeInfo[i][sCreated] = 0;
			    SpikeInfo[i][sX] = 
			    SpikeInfo[i][sY] = 
			    SpikeInfo[i][sZ] = 0.0;
			
			    if (IsValidDynamicObject(SpikeInfo[i][sObject]))
			    {
				    DestroyDynamicObject(SpikeInfo[i][sObject]);
				    SpikeInfo[i][sObject] = INVALID_OBJECT_ID;	
			    }				
			}
		}
	}

	if(gettime() > pTemp[playerid][HileKontrol])
	{
		new Float:oyuncu_pos[3];
		GetPlayerPos(playerid, oyuncu_pos[0], oyuncu_pos[1], oyuncu_pos[2]);

		if(!IsPlayerInRangeOfPoint(playerid, 110.0, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]) && PlayerInfo[playerid][pAdmin] < 3) 
		{
		    if((IsPlayerInAnyVehicle(playerid) && IsAPlane(GetPlayerVehicleID(playerid)) == 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleSpeed(GetPlayerVehicleID(playerid)) < 40.0) || GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && !IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) 
		    {
				if(!pTemp[playerid][pLogged] && (PlayerInfo[playerid][pPosX] != 1045.441040)) return KickLine(playerid, "Teleport hilesi.");
				if(GetPVarInt(playerid, "tpOnlem") != 1 && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) SendAdmMessage("[Anti-Cheat] %s (%d), Teleport Hilesi kullanýyor olabilir.", GetNameEx(playerid), playerid);
				else DeletePVar(playerid, "tpOnlem");
				GetPlayerPos(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
			}
			else GetPlayerPos(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
		}
		else if(IsPlayerInRangeOfPoint(playerid, 110.0, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ])) GetPlayerPos(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
		pTemp[playerid][HileKontrol] = gettime() + 2;
	}

    new Float:health;
	GetPlayerHealth(playerid, health);
	if (health != PlayerInfo[playerid][pHealth] && PlayerInfo[playerid][pHealth] > 5)  SetPlayerHealth(playerid, PlayerInfo[playerid][pHealth]);

	if (GetPlayerScore(playerid) != PlayerInfo[playerid][pLevel]) SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);

	pTemp[playerid][pDarkAFK] = 0;
    return 1;
}