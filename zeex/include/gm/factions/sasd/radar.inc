stock RadarHud_Goster(playerid)
{
	PlayerTextDrawShow(playerid, Dashcam[playerid][0]);
	PlayerTextDrawShow(playerid, Dashcam[playerid][1]);
	return 1;
}

stock RadarHud_Gizle(playerid)
{
	PlayerTextDrawHide(playerid, Dashcam[playerid][0]);
	PlayerTextDrawHide(playerid, Dashcam[playerid][1]);
	return 1;
}

stock RadarHud_Sil(playerid)
{
	PlayerTextDrawDestroy(playerid, Dashcam[playerid][0]);
	PlayerTextDrawDestroy(playerid, Dashcam[playerid][1]);
	return 1;
}

stock RadarHud_TD(playerid)
{	
Dashcam[playerid][0] = CreatePlayerTextDraw(playerid, 344.000, -1.000, "mdl-2677:dashcam");
PlayerTextDrawTextSize(playerid, Dashcam[playerid][0], 173.000, 111.000);
PlayerTextDrawAlignment(playerid, Dashcam[playerid][0], 1);
PlayerTextDrawColor(playerid, Dashcam[playerid][0], -1);
PlayerTextDrawSetShadow(playerid, Dashcam[playerid][0], 0);
PlayerTextDrawSetOutline(playerid, Dashcam[playerid][0], 0);
PlayerTextDrawBackgroundColor(playerid, Dashcam[playerid][0], 255);
PlayerTextDrawFont(playerid, Dashcam[playerid][0], 4);
PlayerTextDrawSetProportional(playerid, Dashcam[playerid][0], 1);

Dashcam[playerid][1] = CreatePlayerTextDraw(playerid, 388.000, 39.000, "Model: LSPD Crown Victoria~n~Plaka: 35ABZ5854~n~Hiz: 250 km/h");
PlayerTextDrawLetterSize(playerid, Dashcam[playerid][1], 0.170, 0.999);
PlayerTextDrawAlignment(playerid, Dashcam[playerid][1], 1);
PlayerTextDrawColor(playerid, Dashcam[playerid][1], -1);
PlayerTextDrawSetShadow(playerid, Dashcam[playerid][1], 1);
PlayerTextDrawSetOutline(playerid, Dashcam[playerid][1], 1);
PlayerTextDrawBackgroundColor(playerid, Dashcam[playerid][1], 150);
PlayerTextDrawFont(playerid, Dashcam[playerid][1], 2);
PlayerTextDrawSetProportional(playerid, Dashcam[playerid][1], 1);

    return 1;
}

RadarHud_OnGameModeInit()
{
	for (new i = 1; i < MAX_VEHICLES; i++)
	{
	    VehRadarID[i] = -1;
	    CheckingSpeed[i] = 0;
	}
 	
	return 1;
}

GetVehicleInfrontID (vehid)
{
    new Float: temp = 12.0;
	new j = 0;
	for (new i = 1; i <= MAX_VEHICLES; i++)
	{
	    new Float: a, Float: x1, Float: y1, Float: z1, Float: x2, Float: y2, Float: z2;
    	GetVehiclePos (vehid, x1, y1, z1);
    	GetVehicleZAngle (vehid, a);
 		if (i != vehid)
 		{
	 		if (GetVehiclePos (i, x2, y2, z2))
			{
				new Float: distance = floatsqroot (floatpower ((x1 - x2), 2) + floatpower ((y1 - y2), 2) + floatpower ((z1 - z2), 2));
				GetVehicleZAngle (vehid, a);

				if (distance < 20.0)
				{
    				x1 = x1 + (distance * floatsin(-a, degrees));
					y1 = y1 + (distance * floatcos(-a, degrees));

					distance = floatsqroot ((floatpower ((x1 - x2), 2)) + (floatpower ((y1 - y2), 2)));

					if (temp > distance)
					{
						temp = distance;
						j = i;
					}
				}
			}
		}
	}
	if (temp < 20.0) return j;
	return -1;
}

UpdateSpeed(playerid, vehid)
{
    new id = GetVehicleInfrontID (vehid);
	if (id < 0 || id == 0)
	{
		PlayerTextDrawSetString(playerid, Dashcam[playerid][1],"~b~MODEL:~w~ N/A~n~~b~PLAKA:~w~ N/A~n~~b~HIZ:~w~ N/A");
	}
	else
	{
		new str[128], 
            plates[16], 
            speed = GetVehicleSpeed(id);

        format(plates, sizeof(plates), "%s", VehicleInfo[id][carPlate]);
		
        format (str, sizeof (str), "~b~MODEL:~w~ %s ~n~~b~PLAKA: ~w~%s~n~~b~HIZ:~w~ %d km/h", GetVehicleModelName(VehicleInfo[id][carModel]), plates, speed);
		PlayerTextDrawSetString(playerid, Dashcam[playerid][1], str);
	}

 	if (IsPlayerInVehicle(playerid, vehid))  	RadarHud_Gizle(playerid);
    else                                    	RadarHud_Goster(playerid);

	return 1;
}

CheckValidTextDraws(playerid)
{
	if (IsPlayerConnected (playerid))
	{
	    if (IsPlayerInAnyVehicle (playerid))
		{
			new vehid = GetPlayerVehicleID(playerid);
		    if (CheckingSpeed[vehid])
		    {
                UpdateSpeed(playerid, vehid);
		        RadarHud_Goster(playerid);
		    }
		    else
		    {
		        RadarHud_Gizle(playerid);
		    }
		}
			
		else
		{
		    RadarHud_Gizle(playerid);
		    OldVehID[playerid] = 0;
		}
	}
	return 1;
}

Radar_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if ((oldstate == PLAYER_STATE_ONFOOT) && (newstate == PLAYER_STATE_PASSENGER || newstate == PLAYER_STATE_DRIVER))
	{
	    OldVehID [playerid] = GetPlayerVehicleID (playerid);
	}
	return 1;
}

Radar_OnVehicleDeath(vehicleid)
{
    DestroyObject (VehRadarID [vehicleid]);
    VehRadarID [vehicleid] = -1;
  	CheckingSpeed [vehicleid] = 0;

 	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerInVehicle(i, vehicleid))    RadarHud_Gizle(i);
	}
}

alias:radar("dashcam");
CMD:radar(playerid, params[])
{	
    new vehid = GetPlayerVehicleID (playerid);

    if (!IsFactionPolice(PlayerInfo[playerid][pFaction])) 	return SendErrorMessage(playerid, "Polis deðilsin!");
    if (!PlayerInfo[playerid][pOnDuty])				 		return SendErrorMessage(playerid, "Ýþbaþýnda deðilsin!");
    if (!IsFactionPolice(VehicleInfo[vehid][carFaction])) 	return SendErrorMessage(playerid, "Polis aracýnda olmalýsýn!");
		
    if (!CheckingSpeed[vehid])
    {
		RadarHud_TD(playerid);

        new Float: x, Float: y, Float: z, Float: a;
        GetVehiclePos (vehid, x, y, z);
        GetVehicleZAngle (vehid, a);
        VehRadarID [vehid] = CreateObject (367, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 300.0);
        AttachObjectToVehicle (VehRadarID [vehid], vehid, 0.2, 0.50, 0.3, 0.0, 0.0, 90.0);
        
        RadarHud_Goster(playerid);

        CheckingSpeed [vehid] = 1;

        SendWarningMessage(playerid, "Radar oluþturuldu.");
    }   
    else    
    {
		DestroyObject(VehRadarID [vehid]);
		VehRadarID [vehid] = -1;
		CheckingSpeed [vehid] = 0;

		RadarHud_Gizle(playerid);
		RadarHud_Sil(playerid);	

        SendWarningMessage(playerid, "Radar kaldýrýldý.");
	}
	return 1;
}