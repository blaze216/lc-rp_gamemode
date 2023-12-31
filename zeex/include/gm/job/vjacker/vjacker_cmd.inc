alias:aracteslim("aracparcala");
CMD:aracteslim(playerid, params[])
{
	if (IsPoliceNear(playerid))	return InfoMSG(playerid, "Yakinlarda ~p~~b~polis memurlari ~w~var!", 4);
	if (!PoliceOnline())		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmen i�in oyunda %i polis olmas� gerekiyor", NEED_COPS_TO_CRIME);

	new
		id = GetChopshopID(playerid),
		vehID = GetPlayerVehicleID(playerid)
	;
	
	if (id == -1 || !IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Yak�nlar�n�zda ara� par�alama istasyonu yok veya ara� kullanm�yorsunuz.");
	
	if (VehicleInfo[vehID][carOwnerID] == PlayerInfo[playerid][pID] || PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehID][carID])
		return SendErrorMessage(playerid, "Bu arac� par�alatamazs�n.");

	if (VehicleInfo[vehID][carOwnerID] == INVALID_PLAYER_ID) 			return SendErrorMessage(playerid, "Yaln�zca ki�isel ara�lar �al�nabilir.");
	if (PlayerInfo[playerid][InMission]) 				return SendErrorMessage(playerid,"Zaten bir g�revdesiniz.");
	if (!CheckWantedModel(id, GetVehicleModel(vehID))) 	return SendErrorMessage(playerid, "Bu ara� aranan bir ara� de�il.");
	
	new count, time[64];
	for(new i; i < 14; i++) if (VehicleInfo[vehID][carComponent][i] > 0) count++;

	if (VehicleInfo[vehID][carEngineOn]) ToggleVehicleEngine(vehID, playerid);

	PlayerInfo[playerid][InMission] = CARJACKER_DELIVER;
	PlayerInfo[playerid][MissionTime] = 15 + count;
	PlayerInfo[playerid][MissionTarget][0] = vehID;
	PlayerInfo[playerid][MissionTarget][1] = id;
			
	format(time, sizeof(time), "~r~ARAC PARCALARI SOKULUYOR~n~~w~KALAN ~y~%d ~w~SANIYE", PlayerInfo[playerid][MissionTime]);
	InfoMSG(playerid, time, 2);
	
	return 1;
}

CMD:gorevibitir(playerid, params[])
{
	if (!PlayerInfo[playerid][InMission]) return SendErrorMessage(playerid, "Bir g�revde de�ilsiniz.");
	LeaveMission(playerid);
	return 1;
}

CMD:aracibirak(playerid, params[])
{
	if (IsPoliceNear(playerid))	return InfoMSG(playerid, "Yakinlarda ~p~~b~polis memurlari ~w~var!", 4);
	
	new vehID = PlayerInfo[playerid][MissionTarget][0],
		id = PlayerInfo[playerid][MissionTarget][1],
		Float: playerPos[3];

	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);

	if (!PlayerInfo[playerid][InMission]) 				return SendErrorMessage(playerid, "Bir g�revde de�ilsiniz.");

	if (PlayerInfo[playerid][InMission] != CARJACKER_DROPOFF) 				   	return SendErrorMessage(playerid, "Herhangi bir arac� par�alatmam��s�n�z.");
	if (GetPlayerVehicleID(playerid) != PlayerInfo[playerid][MissionTarget][0]) return SendErrorMessage(playerid, "Bu do�ru ara� de�il!");

	if (!IsPlayerInRangeOfPoint(playerid, 50.0, chopshop_data[id][chopshop_pos][0], chopshop_data[id][chopshop_pos][1], chopshop_data[id][chopshop_pos][2]))
	{
	    new Float: distance_reward = XB_GetDistanceBetweenTPoints(playerPos[0], playerPos[1], playerPos[2], chopshop_data[id][chopshop_pos][0], chopshop_data[id][chopshop_pos][1], chopshop_data[id][chopshop_pos][2]);

	    if (distance_reward > 200.0) PlayerInfo[playerid][MissionReward] += 400;
	    else 						PlayerInfo[playerid][MissionReward] += floatround(distance_reward) * 2;
	    
	    new money[32];
	    format(money, 32, "~g~GOREV TAMAMLANDI~n~~w~KAZANILAN TUTAR ~y~$%s", FormatNumber(PlayerInfo[playerid][MissionReward]));
		InfoMSG(playerid, money, 5);

		GiveCash(playerid, PlayerInfo[playerid][MissionReward]);
			
		//GetPlayerPos(playerid, VehicleInfo[vehID][eVehicleStolenPos][0], VehicleInfo[vehID][eVehicleStolenPos][1], VehicleInfo[vehID][eVehicleStolenPos][2]);
		//VehicleInfo[vehID][eVehicleStolen] = true;
		
		new userid;
		foreach(new i : Player) {
			if (PlayerInfo[i][pID] == VehicleInfo[vehID][carOwnerID]) {
				userid = i; 
				break;
			}
		}

		SendClientMessageEx(userid, COLOR_LIGHTRED, "Ara�: %s model arac�n�z �al�nd�! (/araclarim)", VehicleNames[GetVehicleModel(vehID)-400]);

		VehicleInfo[vehID][carDestroyed]++;

		SQL_SetInteger("cars", "jacking", 1, VehicleInfo[vehID][carID]);
		SQL_SetInteger("cars", "destroys", VehicleInfo[vehID][carDestroyed], VehicleInfo[vehID][carID]);

		new money_str[70];
		format(money_str, sizeof(money_str), "BASARIYLA ARACTAN ~g~KURTULDUN ~w~KAZANILAN TUTAR ~g~$%i", PlayerInfo[playerid][MissionReward]);
		InfoMSG(playerid, money_str, 5);
		RemovePlayerFromVehicle(playerid);

		ResetVehicleStuff(vehID);
		DestroyVehicleEx(vehID, 1);

		PlayerInfo[playerid][MissionReward] = 0;
		PlayerInfo[playerid][InMission] = MISSION_NONE;
		PlayerInfo[playerid][MissionTime] = 0;
		PlayerInfo[playerid][MissionTarget][0] = 0;
		PlayerInfo[playerid][MissionTarget][1] = 0;
	}
	else return SendErrorMessage(playerid, "Par�alama istasyonuna �ok yak�ns�n�z.");

	return 1;
}
