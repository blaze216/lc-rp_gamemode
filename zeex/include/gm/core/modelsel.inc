public OnModelSelectionResponse(playerid, extraid, index, modelid, response)
{
	if (extraid == MODEL_SELECTION_COLOR && response == MODEL_RESPONSE_SELECT)
	{
	    if (GetPVarInt(playerid, #veh_color_type) == 1)
	    {
		    new vehicle = GetPlayerVehicleID(playerid);

			if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID]) return 1;

		    if (GetPVarInt(playerid, #veh_color1) == -1)
		    {
		        SetPVarInt(playerid, #veh_color1, index);

		        new colors[256];

		        for(new i; i != 256; i++)
				{
		            colors[i] = i;
				}

		    	ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR, colors, sizeof(colors));
				return 1;
			}
		    StartVehicleUpgrade(playerid, vehicle, 10, 100, GetPVarInt(playerid, #veh_color1), index);
		}

		if (GetPVarInt(playerid, #veh_color_type) == 2)
	    {
		    new vehicle = GetPlayerVehicleID(playerid);

			if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID]) return 1;

		    if (GetPVarInt(playerid, #veh_color1) == -1)
		    {
		        SetPVarInt(playerid, #veh_color1, index);

		        new colors[256];

		        for(new i; i != 256; i++)
				{
		            colors[i] = i;
				}

		    	ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR, colors, sizeof(colors));
				return 1;
			}
		    StartVehicleUpgrade(playerid, vehicle, 10, 500, GetPVarInt(playerid, #veh_color1), index);
		}
	    return 1;
	}

	if (extraid == MODEL_BUING_COLOR && response == MODEL_RESPONSE_SELECT)
	{
	    if (GetPVarInt(playerid, #veh_color_type) == 1)
	    {
			SetPVarInt(playerid, #veh_color_type, 0);
	        SetPVarInt(playerid, #veh_color1, index);

	        new colors[256];

	        for(new i; i != 256; i++)
			{
	            colors[i] = i;
			}

			SendSyntaxMessage(playerid, "Lütfen aracýn {ffc46a}ikinci{FFFFFF} rengini seçin."); //öâåò
	    	ShowColorSelectionMenu(playerid, MODEL_BUING_COLOR, colors, sizeof(colors));
			return 1;
		}
		
		SetPVarInt(playerid, #veh_color2, index);
		
		ShowBuyingVehicleDetails(playerid);
	    return 1;
	}

	BB_OnPlayerModelSelection(playerid, extraid, modelid, response);

	return 1;
}