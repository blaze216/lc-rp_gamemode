Admin_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if (pTemp[playerid][pAdminDuty] == 1 && GetInterior(playerid) == 0 || PlayerInfo[playerid][pFMAdmin] == 1)
	{
		//MapAndreas_FindZ_For2DCoord(fX, fY, fZ);
    	SetPlayerPosEx(playerid, fX, fY, fZ + 0.5);
		//SendSpecialMessage(playerid, "Ýþarete ýþýnlandýn.");
	}
    return 1;
}

Admin_OnPlayerKeyStateChange(playerid, newkeys)
{
	if (HOLDING(KEY_SPRINT) && pTemp[playerid][pSpecPlayer] != INVALID_PLAYER_ID)
 	{
		if (IsPlayerInAnyVehicle(pTemp[playerid][pSpecPlayer]))	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(pTemp[playerid][pSpecPlayer]), 1);
		else													PlayerSpectatePlayer(playerid, pTemp[playerid][pSpecPlayer], 1);

		SetInterior(playerid,GetInterior(pTemp[playerid][pSpecPlayer]));
		SetWorld(playerid, GetWorld(pTemp[playerid][pSpecPlayer]));
	}

	if (HOLDING(KEY_ANALOG_LEFT) && pTemp[playerid][pSpecPlayer] != INVALID_PLAYER_ID)
	{
	    new maxplayers = GetMaxPlayers();
		for(new i = pTemp[playerid][pSpecPlayer]+1, bool:secondloop; i < maxplayers; i++)
		{
			if (i == maxplayers && !secondloop)
			{
				secondloop = true;
				i = 0;
				continue;
			}

			if (!IsPlayerLogged(i) || playerid == i) continue;

			new mes[4];
			format(mes, sizeof(mes), "%i", i);
			pc_cmd_spectate(playerid, mes);
			break;
		}
	    return 1;
	}

	else if (HOLDING(KEY_ANALOG_RIGHT) && pTemp[playerid][pSpecPlayer] != INVALID_PLAYER_ID)
	{
	    new maxplayers = GetMaxPlayers();
		
		for(new i = pTemp[playerid][pSpecPlayer]-1, bool:secondloop; i < maxplayers; i--)
		{
			if (i <= 0 && !secondloop)
			{
				secondloop = true;
				i = maxplayers;
				continue;
			}

			if (!IsPlayerLogged(i) || playerid == i) continue;

			new mes[4];
			format(mes, sizeof(mes), "%i", i);
			pc_cmd_spectate(playerid, mes);
			break;
		}
	}
	return 1;
}

Admin_PlayerTimer(playerid)
{
	if (pTemp[playerid][pSpecPlayer] != INVALID_PLAYER_ID)
	{
		new targetid = pTemp[playerid][pSpecPlayer], Float: x, Float: y, Float: z, Float: a, mes[128];

		if (!IsPlayerLogged(targetid))
		{
		    GameTextForPlayer(playerid,"~w~Oyuncu ~r~Cikis Yapti", 2000, 4);
			TogglePlayerSpectating(playerid, 0);
		}
		else
		{
			if (GetWorld(targetid) != GetWorld(playerid))		SetWorld(playerid, GetWorld(targetid));
			if (GetInterior(targetid) != GetInterior(playerid))	SetInterior(playerid, GetWorld(targetid));
	
			GetPlayerPos(targetid, x,y,z);
		    GetPlayerFacingAngle(targetid, a);
	
	       	new weap = AntiCheatGetWeapon(targetid), 
			   ip[24], 
			   Float: thealth, 
			   Float: tarmour;

			GetPlayerIp(targetid, ip, sizeof(ip));
		    AntiCheatGetHealth(targetid, thealth);
		    AntiCheatGetArmour(targetid, tarmour);
	
		    format(mes, sizeof(mes), "XYZ: %.3f, %.3f, %.3f;  Angle: %.0f;  Interior: %i;  Virtual World: %i;", x, y, z, a, GetInterior(targetid),GetWorld(targetid));
		    PlayerTextDrawSetString(playerid, spectate_TD[playerid][0], mes);
		    PlayerTextDrawShow(playerid, spectate_TD[playerid][0]);
			
			format(mes, sizeof(mes), "%s[%i]; IP: %s; PING: %03i; HEALTH: %.0f; ARMOUR: %.0f; WEAPON: %s; AMMO: [Server: %i -- Param: %i];", 
			GetName(targetid), targetid, ip, GetPlayerPing(targetid), thealth, tarmour, inventory_items[weap][itemName], GetPlayerAmmo(targetid), PlayerInfo[targetid][pPlayerAmmo]);

		    PlayerTextDrawSetString(playerid, spectate_TD[playerid][1], mes);
		    PlayerTextDrawShow(playerid, spectate_TD[playerid][1]);
		}
	}
	return 1;
}