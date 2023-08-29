this::OneHourTimer()
{
	for(new i; i < MAX_BIZ; i++) Save_Business(i);
	for(new i; i < MAX_HOUSES; i++) Save_House(i);
	for(new i; i < MAX_VEHICLES; i++) Save_Car(i);
	for(new i; i < MAX_PLAYERS; i++) Save_User(i);
	for(new i; i < MAX_APART; i++) Save_Apart(i);

	printf("saatlik timer dondu");

	SaveServer();
	return 1;	
}

this::OneMinuteTimer()
{
	//=============================================================================
	new tmp_hour, tmp_min;

	gettime(tmp_hour, tmp_min);
	
	if (tmp_hour != server_hour)
	{		
    	server_hour = tmp_hour;
    	SetWorldTime(server_hour);

		for(new i = 0; i < MAX_BIZ; i++) {
			if (!BizInfo[i][bizID] || BizInfo[i][bizType] != BIZ_GAS_STATION) continue;
			if (!BizInfo[i][bizOwnerID] && BizInfo[i][bizProduct] > 10) BizInfo[i][bizProduct]--;
		}
		
		
		/*if(server_hour == 19 || server_hour == 20 || server_hour == 21 || server_hour == 22) 
		{ 
			SCMALL(COLOR_WHITE, ">> Happy hour sistemi aktif. 22:00'a kadar geçerlidir.");
		}*/
	}
	//==========================================================================
	for(new i = 0; i < MAX_CHOPSHOP; i++)
	{
		if (!chopshop_data[i][chopshop_exist]) continue;
		
		if (chopshop_data[i][chopshop_timer] >= 60) 	GetRandomModel(i);
		else 										chopshop_data[i][chopshop_timer]++;
	}
    //========================================================================== 
	for(new i; i != MAX_LAST_ADVERT; i++)
	{
		if (strlen(LastAdvertInfo[i][advertText]) < 3)	continue;

		if (gettime() - LastAdvertInfo[i][adverttime] > 3600)
		{
			LastAdvertInfo[i][advertText] = EOS;
			LastAdvertInfo[i][adverttime] = 0;
			LastAdvertInfo[i][advertnumber] = 0;
		}
	}	
	//==========================================================================
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i)) 					continue;

        PlayerInfo[i][pPayDayTime]++;
        if (PlayerInfo[i][pPayDayTime] >= 60) 	PayDay(i);
		
		SetPVarInt(i, #pDelay, 0);

		PlayerInfo[i][pMinutes]++;
		
		if(GetPlayerPing(i) < 300 && IsPlayerLoggedIn(i) && GetPlayerState(i) != PLAYER_STATE_SPECTATING && GetPlayerState(i) != PLAYER_STATE_WASTED && GetPlayerState(i) != PLAYER_STATE_SPAWNED) {
			GetPlayerPos(i, PlayerInfo[i][pPosX], PlayerInfo[i][pPosY], PlayerInfo[i][pPosZ]);
			GetPlayerFacingAngle(i, PlayerInfo[i][pPosA]);
		}		

		if(PlayerInfo[i][pBagimlilikSeviye] > 0)
		{
			PlayerInfo[i][pKrizSure]--;
			if(PlayerInfo[i][pUTedaviSure] > 0)
			{
				PlayerInfo[i][pUTedaviSure]--;
				if(PlayerInfo[i][pUTedaviSure] == 0) SendClientMessageEx(i, COLOR_YELLOW, "[SMS] >> UMV: Uyuþturucu tedavinizdeki %d. seansýnýzýn vakti gelmiþ bulunmakta, sizi hastaneye bekliyoruz.", PlayerInfo[i][pUTedaviEXP] + 1);				
			}

			if(PlayerInfo[i][pKrizSure] <= 0 && PlayerInfo[i][pKrizSure]%10 == 0)
			{
				SendClientMessage(i, COLOR_WHITE, "Gözlerin kanlanýyor, terliyor ve kötü hissediyorsun. Kaygýlarýnýn arttýðý ortada.");
				PlayerAME(i, "gözleri kýzarmýþ, terliyor.");
				SetPlayerDrunkLevel(i, 1500);
			}
		}		
	}
	//==========================================================================
	for(new i = 0; i < MAX_CORPS; i++)
	{
		if (!CorpInfo[i][cUsed]) continue;

		if ((CorpInfo[i][cTime] - gettime()) > 60*30) 	RemoveCorpse(i);
	
		if ((CorpInfo[i][cTime] - gettime()) > 60*1 && CorpInfo[i][cVeh] > 0 && GetVehicleModel(CorpInfo[i][cVeh]) > 0) 
		{
			new Float: x, Float: y, Float: z;
			GetBootPos(CorpInfo[i][cVeh], x, y, z);
			
			CorpInfo[i][cText] = CreateDynamic3DTextLabel("*** bagajdan ceset kokusu gelmektedir ***", 0xC2A2DAFF, x, y, z, 20.0, INVALID_PLAYER_ID, CorpInfo[i][cVeh]);
		}
	}
    //==========================================================================
    for(new i; i != MAX_FOOD_DROPS; i++)
	{
	    if (FoodDrop[i][foodDropped] == 0) continue;
	        
		if (FoodDrop[i][foodTime]-- == 0)
		{
        	FoodDrop[i][foodModel] = 0;
        	FoodDrop[i][foodDropped] = 0;

        	if (IsValidDynamicObject(FoodDrop[i][foodObject])) DestroyDynamicObject(FoodDrop[i][foodObject]);
		}
	}
	
	//==========================================================================
	CheckBillBoard();
	TohumlariGuncelle();
	//==========================================================================
	return 1;
}

this::OneSecondTimer()
{
	PlayerTimer();
	OtherTimer();
	//MeterCheck();
	return 1;
}

forward TalkTimer(playerid);
public TalkTimer(playerid)
{
	return ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
}

Timer_OnGameModeInit()
{
	SetTimer("OneSecondTimer", 1000, true);
	SetTimer("OneMinuteTimer", 60000, true);
	SetTimer("OneHourTimer", 60000 * 10, true);
    return 1;
}

OtherTimer()
{
	/*
	if (time_truck-- == 0)
	{
	    time_truck = 3600;
	    CheckIndustries();
	}
	
    if (ship_depart <= gettime() && ship_docked == 1)
	{
	    new mes[128];
	    for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
	        if (TruckCargo[i][tOn] == 0 || TruckCargo[i][tType] != 2) continue;

            TruckCargo[i][tStorage] = 0;
            format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nDurum: %i / %i\nÜcret: $%i / birim.", truckcargo_product[TruckCargo[i][tProductID]], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize], TruckCargo[i][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[i][tLabel], 0xFFFFFFFF, mes);
        	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TruckCargo[i][tLabel], E_STREAMER_INTERIOR_ID, 1);
        	Streamer_SetIntData(STREAMER_TYPE_PICKUP, TruckCargo[i][tPickup], E_STREAMER_INTERIOR_ID, 1);
	    }
		mysql_tquery(dbHandle, "UPDATE `truck_cargo` SET `storage`=0 WHERE `type`=2");

	    ship_docked = 2;
	    ship_depart = ship_next + 2400;

	    new Float: ox, Float: oy, Float: oz;
        
		for(new i; i != 11; i++)
	    {
	        if (i < 8)	Streamer_SetIntData(STREAMER_TYPE_OBJECT, obj_lamp[i], E_STREAMER_MODEL_ID, 19124);
	        if (i < 4)
	        {
	            GetDynamicObjectPos(obj_gate[i], ox, oy, oz);
	        	MoveDynamicObject(obj_gate[i], ox - 10.0, oy, oz, 1.5);
	        }

			GetDynamicObjectPos(obj_ship[i], ox, oy, oz);
	        MoveDynamicObject(obj_ship[i], ox + 600, oy, oz, 3.0);
		}
	}

	if (ship_next <= gettime() && ship_docked == 0)
	{
	    ship_docked = 3;
        ship_next = ship_depart + 340;

	    new Float: ox, Float: oy, Float: oz;

		for(new i; i != 11; i++)
	    {
			GetDynamicObjectPos(obj_ship[i], ox, oy, oz);
	        MoveDynamicObject(obj_ship[i], ox - 600, oy, oz, 3.0);
		}
	}*/

	for(new i = 0; i < MAX_CCTV; i++)
	{
		if (CCTVInfo[i][tvObjectOn])
		{
			if (CCTVInfo[i][tvSignal])
			{
				if (CCTVInfo[i][tvSignalTime] > 0)
				{
					CCTVInfo[i][tvSignalTime]--; 
				}
				else
				{
					CCTVInfo[i][tvSignalTime] = 0;
					CCTVInfo[i][tvSignal] = 0;
				}	
			}	
		}
	}

	for(new i; i < MAX_HOUSES; i++)
	{
		if (HouseInfo[i][hAlarmTime])
	    {
	        HouseInfo[i][hAlarmTime]--;
	        if (HouseInfo[i][hAlarmTime] == 0) HouseAlarm(i, false);
		}
	}
	
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i ++)
	{
        new Float:health;

		AntiCheatGetVehicleHealth(i, health);

		if (health < 330.0 && IsABicycle(i) == 0)
		{
			if (VehicleInfo[i][carEngineOn])											VehicleEngine(i, false);
			if (VehicleInfo[i][carOwnerID] > 0 && VehicleInfo[i][carOwnerID] != INVALID_PLAYER_ID && VehicleInfo[i][carDeath] != 1)	ResetVehicleStuff(i);
	    
		    SetVehicleHealth(i, 330.0);
		}

		if (VehicleInfo[i][carTerminateEx])
		{
		    VehicleInfo[i][carTerminateEx]--;
			if (VehicleInfo[i][carTerminateEx] == 1 && VehicleInfo[i][carOwnerID] != INVALID_PLAYER_ID && VehicleInfo[i][carOwnerID] > 0)
	        {
				new sahip = GetVehicleOwner(i);
				if(IsPlayerLogged(sahip)) PlayerInfo[sahip][pCarKey] = 0, SendServerMessage(sahip, "Aracýnla 10 dakika boyunca etkileþime geçmedin ve son bulunduðu yere park edildi.");
				new vehid = i;

		        GetVehiclePos(vehid, VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carParkZ]);
		        GetVehicleZAngle(vehid, VehicleInfo[vehid][carParkA]);

		        SQL_SetFloat("cars", "x", VehicleInfo[vehid][carParkX], VehicleInfo[vehid][carID]);
		        SQL_SetFloat("cars", "y", VehicleInfo[vehid][carParkY], VehicleInfo[vehid][carID]);
		        SQL_SetFloat("cars", "z", VehicleInfo[vehid][carParkZ], VehicleInfo[vehid][carID]);
		        SQL_SetFloat("cars", "fa", VehicleInfo[vehid][carParkA], VehicleInfo[vehid][carID]);
		        DestroyVehicleEx(vehid, 1);
			}
		}

		if (VehicleInfo[i][carTerminate])
		{
		    VehicleInfo[i][carTerminate]--;
			if (VehicleInfo[i][carTerminate] == 1 && VehicleInfo[i][carType] != 0)
	        {
				new sahip = GetIDByID(VehicleInfo[i][carRent]);
				if(IsPlayerLogged(sahip)) pTemp[sahip][pRentveh] = 0, pTemp[sahip][pJob] = 0, SendServerMessage(sahip, "Kiralýk aracýnla 5 dakika boyunca etkileþime geçmedin ve silindi.");
				VehicleInfo[i][carRent] = 0;
				AracKiraBitir(i);
			}
		}
		
        if (VehicleInfo[i][carAlarmTime])
	    {
			new engine,lights,alarm,doors,bonnet,boot,objective;
			GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
			if (VehicleInfo[i][carAlarmTime] == 0) SetVehicleParamsEx(i, engine, lights, VEHICLE_PARAMS_OFF, doors, bonnet, boot, objective);

	        VehicleInfo[i][carAlarmTime]--;
			if (VehicleInfo[i][carAlarmTime] % 2 == 1) SetVehicleParamsEx(i, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
			else 									  SetVehicleParamsEx(i, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
		}

	    if (VehicleInfo[i][carObjectiveTime])
	    {
	        VehicleInfo[i][carObjectiveTime]--;
	        if (VehicleInfo[i][carObjectiveTime] == 0)
	        {
	            new engine,lights,alarm,doors,bonnet,boot,objective;

				GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, VEHICLE_PARAMS_OFF);
			}
		}

		if (VehicleInfo[i][carOwnerID] == INVALID_PLAYER_ID || IsABicycle(i) || VehicleInfo[i][carEngineOn] == 0) continue;

		new iEngine, iLights, iAlarm,
			iDoors, iBonnet, iBoot,
			iObjective
		;	
		GetVehicleParamsEx(i, iEngine, iLights, iAlarm, iDoors, iBonnet, iBoot, iObjective);
		
		
		//new Float:fl = (float(GetVehicleSpeed(i))+float(random(5))+1.0)/3600 * GetVehicleFuelUsage(GetVehicleModel(i)) * 0.05;
		//SAMALL("SPEED: %d, ÐÀÑÕÎÄ: %f, -%f", GetVehicleSpeed(i), GetVehicleFuelUsage(GetVehicleModel(i)), fl);
		
		VehicleInfo[i][carFuel] -= (float(GetVehicleSpeed(i))+float(random(5))+1.0)/3600 * GetVehicleFuelUsage(GetVehicleModel(i)) * 0.10;

		if (VehicleInfo[i][carFuel] < 0.0)
		{
			VehicleInfo[i][carFuel] = 0.0;
			VehicleEngine(i, false);
			if (IsPlayerLogged(VehicleInfo[i][carDriver]) && IsPlayerInVehicle(VehicleInfo[i][carDriver], i))
				GameTextForPlayer(VehicleInfo[i][carDriver], "~y~BENZIN BITTI!", 5000, 3);
		}

		//SAMALL("%f", VehicleInfo[i][carFuel]);

		if (GetVehicleSpeed(i)) VehicleInfo[i][carEngine] -= 0.004/10;
		if (VehicleInfo[i][carRadioOn])	VehicleInfo[i][carBattery] -= 0.02/10;
		if (iLights == 1)	VehicleInfo[i][carBattery] -= 0.012/10;

		new Float:vehhp;
		GetVehicleHealth(i, vehhp);

		if (vehhp < 400 && GetVehicleSpeed(i) && VehicleInfo[i][carEngine] < 35)
		{
			VehicleInfo[i][carEngine] -= 0.02/10;
			VehicleInfo[i][carBattery] -= 0.012/10;
		}

		if (VehicleInfo[i][carBattery] < 0.0)
		{
			VehicleInfo[i][carBattery] = 0.0;
			if (VehicleInfo[i][carEngineOn]) VehicleEngine(i, false);
		}
		
		if (VehicleInfo[i][carEngine] < 0.0)
		{
			VehicleInfo[i][carEngine] = 0.0;
			if (VehicleInfo[i][carEngineOn]) VehicleEngine(i, false);
		}
	}

	for(new i = 0; i != MAX_FIRES; i++)
	{
	    if (FiresInfo[i][fireOn] == 0) continue;
	    if (FiresInfo[i][fireTimer]-- < 1) 					DeleteFire(i);
		if (FiresInfo[i][fireTimer] == CROSSFIRE_TIMER*60) 	CrossFire(i);
	}

	for(new i = 0; i != MAX_TOLLS; i++)
	{
		if (aTolls[i][E_tOpenTime] < 1) continue;

		aTolls[i][E_tOpenTime]--;

		if (aTolls[i][E_tOpenTime] == 1)	Toll_CloseToll(i);
	}


	for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
	{
	    if (CallInfo[i][callExists] != 0 && CallInfo[i][callDelete] < gettime())
		{
        	CallInfo[i][callExists] =
			CallInfo[i][callAccept] =
        	CallInfo[i][callType] = 0;
			CallInfo[i][callAcceptBy] = EOS;
		}

		if (ArrestInfo[i][arrestExists] != 0 && ArrestInfo[i][arrestDelete] < gettime())
		{
			ArrestInfo[i][arrestExists] = 
			ArrestInfo[i][arrestDelete] = 0;
		}
	}


	for(new i = 1; i != MAX_FACTIONS; i++)
	{
	    if (Factions[i][fON] == 0 || 
			(Factions[i][fType] != FACTION_MAFIA && Factions[i][fType] != FACTION_GANG) ||
			Factions[i][fPointTime] > gettime()
		) continue;
		
		if (Factions[i][fType] == FACTION_MAFIA)	Factions[i][fPoint] = 50;
        else										Factions[i][fPoint] = 30;
            
    	Factions[i][fPointTime] = 604800 + gettime();
		SQL_SetInteger("factions", "point", Factions[i][fPoint], Factions[i][fID]);
		SQL_SetInteger("factions", "point_time", Factions[i][fPointTime], Factions[i][fID]);
	}

	for(new i = 0; i < MAX_CORPS; i++)
	{
		if (!CorpInfo[i][cUsed]) continue;
		if (!CorpInfo[i][cVeh])	SetActorPos(CorpInfo[i][cBody], CorpInfo[i][cX], CorpInfo[i][cY], CorpInfo[i][cZ]);
	}

	return 1;
} 