/*Vehicle_OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if (checkpointid == pTemp[playerid][JackingCP])
	{
		if (!IsPlayerInAnyVehicle(playerid)) 							  return InfoMSG(playerid, "ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ ~r~ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ~w~ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½!", 3);
		if (GetPlayerVehicleID(playerid) != pTemp[playerid][JackingVehID]) return InfoMSG(playerid, "ï¿½ï¿½ ï¿½ï¿½ ~r~ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ~w~ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½!", 3);
		if (IsPoliceNear(playerid)){
			InfoMSG(playerid, "ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ~y~ï¿½ï¿½ï¿½ï¿½ï¿½~w~! ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ~r~ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½", 3);

			DisableWaypoint(playerid);
			if (IsValidDynamicCP(pTemp[playerid][JackingCP])) DestroyDynamicCP(pTemp[playerid][JackingCP]);
			pTemp[playerid][JackingCP] = 0;

			new randomCP = random(sizeof(Jacking_CP));
			pTemp[playerid][JackingCP] = CreateDynamicCP(Jacking_CP[randomCP][0], Jacking_CP[randomCP][1], Jacking_CP[randomCP][2], 1.5, 0, 0, playerid, 15000.0);
			TogglePlayerDynamicCP(playerid, pTemp[playerid][JackingCP], true);
    		Streamer_Update(playerid, STREAMER_TYPE_CP);

			return 1;
		}

		new vehid = pTemp[playerid][JackingVehID],
			model = GetVehicleModel(vehid),
			price = floatround(GetVehiclePrice(model)*0.1);

		VehicleInfo[vehid][carDestroyed]++;

		SQL_SetInteger("cars", "jacking", 1, VehicleInfo[vehid][carID]);
		SQL_SetInteger("cars", "destroys", VehicleInfo[vehid][carDestroyed], VehicleInfo[vehid][carID]);
		
		new userid;
		foreach(new i : Player) {
			if (PlayerInfo[i][pID] == VehicleInfo[vehid][carOwnerID]) {
				userid = i; 
				break;
			}
		}

		SendClientMessageEx(userid, COLOR_LIGHTRED, "[ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ] ï¿½ï¿½ï¿½ %s ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½. (/mycars)", VehicleNames[GetVehicleModel(vehid)-400]);

		InfoMSG(playerid, "ï¿½ï¿½ ~g~ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ~w~ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½", 3);
		GiveCash(playerid, price);
		RemovePlayerFromVehicle(playerid);

		ResetVehicleStuff(vehid);
		DestroyVehicle(vehid);

		if (IsValidDynamicCP(pTemp[playerid][JackingCP])) DestroyDynamicCP(pTemp[playerid][JackingCP]);
		pTemp[playerid][JackingCP] = 0;
		pTemp[playerid][JackingVehID] = 0;
		SetPVarInt(playerid, #JACKING_PROCESS, 0);
	}
	return 1;
}*/

Veh_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new Float:oldX, Float:oldY, Float:oldZ,
	Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if (GetPVarInt(playerid, #veh_editor) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
	    new vehicle = GetPVarInt(playerid, #veh_editor), slot = GetPVarInt(playerid, #veh_slot), attobj = GetPVarInt(playerid, #veh_obj);

		DeletePVar(playerid, #veh_editor);
		DeletePVar(playerid, #veh_slot);
		DeletePVar(playerid, #veh_obj);

		new Float:ofx, Float:ofy, Float:ofz, Float:ofaz, Float:finalx, Float:finaly, Float:px, Float:py, Float:pz, Float:roz;
			
		GetVehiclePos(vehicle, px, py, pz);
		GetVehicleZAngle(vehicle, roz);
			
		ofx = x-px, ofy = y-py, ofz = z-pz, ofaz = rz-roz;
		finalx = ofx*floatcos(roz, degrees)+ofy*floatsin(roz, degrees);
		finaly = -ofx*floatsin(roz, degrees)+ofy*floatcos(roz, degrees);
		AttachDynamicObjectToVehicle(objectid, vehicle, finalx, finaly, ofz, rx, ry, ofaz);
		VehicleInfo[vehicle][carAttachObj][slot] = attobj;
		VehicleInfo[vehicle][carAttachPosX][slot] = finalx;
		VehicleInfo[vehicle][carAttachPosY][slot] = finaly;
		VehicleInfo[vehicle][carAttachPosZ][slot] = ofz;
		VehicleInfo[vehicle][carAttachRotX][slot] = rx;
		VehicleInfo[vehicle][carAttachRotY][slot] = ry;
		VehicleInfo[vehicle][carAttachRotZ][slot] = ofaz;

	    if (!GetPVarInt(playerid, "Vehicle:AttEdit")) 
		{
			GiveCash(playerid, -250);
			InfoMSG(playerid, "~w~Tebrikler, ~y~objeyi ~w~~g~$250 ~w~karsiliginda aldin~n~~y~~w~/aracaksesuar - arac objelerini kontrol edebilirsiniz.", 5);
		}
		else InfoMSG(playerid, "~w~Basarili bir sekilde ~y~objenin~w~ pozisyonunu duzenledin!", 5);

		Save_CarAttach(vehicle, slot);
	}
	return 1;
}
 
this::Cars_OnGameModeInit()
{
	mysql_tquery(dbHandle, "SELECT * FROM `cars` WHERE (owner = 0 OR owner = 65535) AND type = 0", "LoadDynamicCars", "");
	mysql_tquery(dbHandle, "DELETE FROM `cars` WHERE (owner = 0 OR owner = 65535) AND type > 0");
	return 1;
}

this::OneHourSave()
{
	for(new i; i < MAX_BIZ; i++) Save_Business(i);
	for(new i; i < MAX_HOUSES; i++) Save_House(i);
	for(new i; i < MAX_APART; i++) Save_Apart(i);
	//for(new i; i < MAX_ARREST; i++) Save_Arre(i);

	SaveServer();
    return 1;
}

this::Vehicle_OnGameModeInit()
{
	mysql_tquery(dbHandle, "SELECT * FROM `rental_points`", "LoadDynamicRentalPoint");
	for(new v = 1; v < MAX_VEHICLES; v++)
	{
		SetVehicleVirtualWorldEx(v, 0);
		SetVehicleInteriorEx(v, 0);
    	VehicleInfo[v] = default_VehicleInfo;
	    VehicleInfo[v][carOwnerPlayer] = INVALID_PLAYER_ID;
	    VehicleInfo[v][carDriver] = INVALID_PLAYER_ID;
		VehicleInfo[v][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(v));
	}
	return 1;
}

Vehicle_OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
	{
		SetPlayerArmedWeapon(playerid, 0);
	}

	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		if(GetPlayerWeapon(playerid) == WEAPON_DEAGLE)
		{
			SetPlayerArmedWeapon(playerid, 0);
		}
	}		

	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
	{
	    new vehicleid;

	    vehicleid = GetPVarInt(playerid, PVAR_LASTENTEREDVEH_ID);		
	    if (VehicleInfo[vehicleid][carType] != 0 && !VehicleInfo[vehicleid][carFaction]) SendServerMessage(playerid, "Kiralýk araçlar eðer 5 dakika içinde tekrar binilmezse, silinir."), VehicleInfo[vehicleid][carTerminate] = 300;
	    if (VehicleInfo[vehicleid][carOwnerID] > 0 && !VehicleInfo[vehicleid][carFaction]) SendServerMessage(playerid, "Aracýnýzla 10 dakika boyunca etkileþime geçmezseniz bulunduðu yerde gizlenecek."), VehicleInfo[vehicleid][carTerminateEx] = 600;		
	}

	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	{
		if(GetTickCount() - pTemp[playerid][pCarTick] < 300) Kick(playerid);
		pTemp[playerid][pCarTick] = GetTickCount();
	}	

	if (newstate == PLAYER_STATE_DRIVER)
	{
		if(!PlayerInfo[playerid][pAdmin] && GetPlayerVehicleID(playerid) != pTemp[playerid][pCarWarpVehicleID] && IsPlayerLoggedIn(playerid)) {
			if(pTemp[playerid][pCarWarpTime] > gettime()) 
			{
				SendClientMessageEx(playerid, COLOR_WHITE, "LIBERTY-AC tarafýndan kalýcý olarak yasaklandýn. Sebep: Vehicle-Hack (#2)");

	            new query[256];
	            mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `block_name`='Blaze Guard', `block_reason` ='Vehicle Troll', `status` = '3' WHERE `id` = '%i'", PlayerInfo[playerid][pID]);
	            mysql_tquery(dbHandle, query);

	            new mes[128];
                format(mes, sizeof(mes), "(( %s adlý karakter Blaze Guard tarafýndan yasaklandý. Sebep: Vehicle Troll ))", GetNameEx(playerid));
	            SendClientMessageByAdmin(COLOUR_TOMATO, mes);

				KickEx(playerid);
				return 1;
			}
			pTemp[playerid][pCarWarpTime] = gettime() + 1;
			pTemp[playerid][pCarWarpVehicleID] = GetPlayerVehicleID(playerid);
		}

		new vehicle = GetPlayerVehicleID(playerid), Float: vhealth;
 		
		AntiCheatGetVehicleHealth(vehicle, vhealth);

		if (!GetPlayerHasRightDrive(playerid, vehicle))  return 1;
	    if (IsABicycle(vehicle)) 						VehicleEngine(vehicle, true);
		
	    VehicleInfo[vehicle][carDriver] = playerid;
	    pTemp[playerid][pDriver] = vehicle;	

		if (IsRentCar(vehicle) && VehicleInfo[vehicle][carRent] == 0)
		{
		    SendClientMessage(playerid, COLOR_GRAY, "[Araç] Bilgi: " EMBED_SILVER "Bu aracý $300 ödeyerek 1 saatliðine kiralayabilirsin. " EMBED_GRAY " '/arac kirala'");
		}

		if (	!VehicleInfo[vehicle][carRent] &&
			((IsPizzaCar(vehicle) && PlayerInfo[playerid][pSideJob] == JOB_PIZZA) ||
			(IsTaxiCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TAXI) ||
			(IsMechanicCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_MECHANIC) ||
			(IsTrashMasterCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TRASHMASTER) ||
			(IsTruckCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TRUCKER && GetAvailableTruck(playerid, GetVehicleModel(vehicle))))
		) {
			SendClientMessage(playerid, COLOR_GRAY, "[Araç] Bilgi: " EMBED_SILVER "Bu araç meslek aracýdýr, kiralamak için: " EMBED_GRAY " '/meslekarackirala'");
		}

        if (VehicleInfo[vehicle][carFaction] > 0)
        {
            SendClientMessageEx(playerid, COLOR_GRAY, "[Araç] Birlik: " EMBED_SILVER "%s " EMBED_GRAY "/ Model: " EMBED_SILVER "%s " EMBED_GRAY "/ ID: " EMBED_SILVER "%d", Factions[VehicleInfo[vehicle][carFaction]][fName], VehicleNames[GetVehicleModel(vehicle) - 400], vehicle);
        }
        else if(VehicleInfo[vehicle][carOwnerID] > 0 && VehicleInfo[vehicle][carOwnerID] != INVALID_PLAYER_ID && !IsRentCar(vehicle) && VehicleInfo[vehicle][carType] <= 0)
        {
            SendClientMessageEx(playerid, COLOR_GRAY, "[Araç] Sahip: " EMBED_SILVER "%s " EMBED_GRAY "/ Model: " EMBED_SILVER "%s " EMBED_GRAY "/ ID: " EMBED_SILVER "%d", GetPlayerNameBySqlID(VehicleInfo[vehicle][carOwnerID]), VehicleNames[GetVehicleModel(vehicle) - 400], vehicle);
        }

        else SendClientMessageEx(playerid, COLOR_GRAY, "[Araç] Model: " EMBED_SILVER "%s " EMBED_GRAY "/ ID: " EMBED_SILVER "%d", VehicleNames[GetVehicleModel(vehicle) - 400], vehicle);

        if(IsEngineVehicle(vehicle))
        {
            SendClientMessageEx(playerid, COLOR_GRAY, "[Araç] Plaka: " EMBED_SILVER "%s " EMBED_GRAY "/ Kilometre: " EMBED_SILVER "%.2f ", VehicleInfo[vehicle][carPlate], VehicleInfo[vehicle][carMilliage]);
        }

        if (CheckAdmin(playerid, DEVELOPER_LEVEL))
        {
            SendClientMessageEx(playerid, COLOR_GRAY, "[Araç] [DEV] Database ID: " EMBED_SILVER "%d " EMBED_GRAY "/ Sahip ID: " EMBED_SILVER "%d", VehicleInfo[vehicle][carID], VehicleInfo[vehicle][carOwnerID]);
        }
		
		//if (!VehicleInfo[vehicle][carEngineOn] && !IsADMVCar(vehicle) && !IsADMVTaxi(vehicle) && !IsADMVHeli(vehicle) && !IsABicycle(vehicle))
			//SCM(playerid, COLOR_GREEN,"-> Engine not started - press '2' or type /(en)gine.");

		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
			SetPlayerCellphoneAction(playerid, 1);

		SetPVarInt(playerid, PVAR_LASTENTEREDVEH_ID, vehicle);	
		SetPVarInt(playerid, PVAR_LASTENTEREDVEH_SEAT, GetPlayerVehicleSeat(playerid));	

//		TextDrawShowForPlayer(playerid, TD_vehicle_info[0]);
//    	TextDrawShowForPlayer(playerid, TD_vehicle_info[1]);
//	    PlayerTextDrawSetString(playerid, TD_vehicle_name[playerid], VehicleNames[GetVehicleModel(vehicle)-400]);
//		PlayerTextDrawShow(playerid, TD_vehicle_name[playerid]);
//		SetPVarInt(playerid, #vehicle_info, 5);
	}

	if (oldstate == PLAYER_STATE_DRIVER)
	{
     	new veh = pTemp[playerid][pDriver];
     	
		pTemp[playerid][pDriver] = INVALID_VEHICLE_ID;

		if (veh != INVALID_VEHICLE_ID && VehicleInfo[veh][carDriver] == playerid)	VehicleInfo[veh][carDriver] = INVALID_PLAYER_ID;
		if (JackingEngine[playerid]) 												StopJackingEngine(playerid);
		if (GetPVarInt(playerid, #UsePump))											Fuel_ResetPlayer(playerid);

	}
	return 1;
}

Vehicle_OnPlayerExitVehicle(playerid, vehicleid)
{
	if (JackingEngine[playerid]) 			StopJackingEngine(playerid);
	if (PlayerInfo[playerid][InMission])	LeaveMission(playerid);
	if (IsPlayerUseMDC(playerid))			MDC_Hide(playerid);
	if (VehicleInfo[vehicleid][carRadioOn])	StopAudioStreamForPlayer(playerid);
	if (pTemp[playerid][pPizzaBoy])         SendServerMessage(playerid, "Kurye motorunun yakýnýnda /pizza komutuyla pizzayý elinize alabilirsiniz.");
	if (pTemp[playerid][pTruckerOn])        SendServerMessage(playerid, "Taþýmacýlýk kamyonunun yakýnýnda /koli komutuyla kutuyu elinize alabilirsiniz.");
	return 1;
}

V_OnVehicleDamageStatusUpdate(vehicleid)
{
	new panels, doorsd, lightsf, tires;

	GetVehicleDamageStatus(vehicleid, panels, doorsd, lightsf, tires);

	if (!VehicleInfo[vehicleid][carOwnerID]) return 1;

	if (!panels && !doorsd && !lightsf && !tires) return 1;

	new Float:health;

	AntiCheatGetVehicleHealth(vehicleid, health);

	if (health > 750.0)	UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, 0);
	
	if (health < 350.0)
	{
	   	if (VehicleInfo[vehicleid][carEngine] > 0.0)	VehicleInfo[vehicleid][carEngine] -= 1.0;
		if (VehicleInfo[vehicleid][carEngine] < 0.0)
		{
	    	if (VehicleInfo[vehicleid][carEngineOn])	VehicleEngine(vehicleid, false);
			
			VehicleInfo[vehicleid][carEngine] = 0.0;
		}
	}
	return 1;
}