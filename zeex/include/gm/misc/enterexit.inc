CMD:giris(playerid, params[])
{
    if (pTemp[playerid][pZond] != 0) return 1;
	if (PlayerInfo[playerid][pInjured] != 0) return 1;

	new id = -1;

	if ((id = GetNearEntranceOutside(playerid, 3.0)) != -1)
	{
	   // if (EntranceInfo[id][eLocked] == 1)					return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
	    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
            if (EntranceInfo[id][eVehicle] != 1)					return 1;
			if (PlayerInfo[playerid][pFaction] != EntranceInfo[id][eFaction] && EntranceInfo[id][eFaction] > 0)		return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);
		    new vehicleid = GetPlayerVehicleID(playerid);
            if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		    PlayerInfo[playerid][pLocationPos][0] = EntranceInfo[id][eExitX];
		    PlayerInfo[playerid][pLocationPos][1] = EntranceInfo[id][eExitY];
		    PlayerInfo[playerid][pLocationPos][2] = EntranceInfo[id][eExitZ];

			SetInterior(playerid, EntranceInfo[id][eExitInt]);
			SetWorld(playerid, EntranceInfo[id][eExitVW]);
  
		    foreach (new i : Player)
		    {
			    if (!IsPlayerInVehicle(i, vehicleid)) continue;

			    SetInterior(i, EntranceInfo[id][eExitInt]);
			    SetWorld(i, EntranceInfo[id][eExitVW]);
		    }
			
            PlayerEnterFreeze(playerid); 
		    SetVehiclePos(vehicleid, EntranceInfo[id][eExitX], EntranceInfo[id][eExitY], EntranceInfo[id][eExitZ]);
		    SetVehicleZAngle(vehicleid, EntranceInfo[id][eExitA] - 180);
		    SetVehicleVirtualWorld(vehicleid, EntranceInfo[id][eExitVW]);
		    LinkVehicleToInterior(vehicleid, EntranceInfo[id][eExitInt]);

		    PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
	        return 1;
		}
	}

    if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearEntranceOutside(playerid)) != -1)
	{
	    //if (EntranceInfo[id][eLocked] == 1)					return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
		if (PlayerInfo[playerid][pFaction] != EntranceInfo[id][eFaction] && EntranceInfo[id][eFaction] > 0)		return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);
	    if (!GetWorld(playerid) && !GetInterior(playerid))	GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPos(playerid, EntranceInfo[id][eExitX], EntranceInfo[id][eExitY], EntranceInfo[id][eExitZ]);
		SetPlayerFacingAngle(playerid, EntranceInfo[id][eExitA] - 180.0);
		SetInterior(playerid, EntranceInfo[id][eExitInt]);
		SetWorld(playerid, EntranceInfo[id][eExitVW]);
		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
	    return 1;
	}

    if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearApartmentOutside(playerid)) != -1)
	{
	    if (!GetWorld(playerid) && !GetInterior(playerid))	GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid, ApartInfo[id][aExitX], ApartInfo[id][aExitY], ApartInfo[id][aExitZ]);
		SetWorld(playerid, ApartInfo[id][aExitVW]);
		SetInterior(playerid, ApartInfo[id][aExitInt]);
		PlayerEnterFreeze(playerid);
		pTemp[playerid][pApartEntered] = id;

		PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
		return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearOutsideHouse(playerid)) != -1)
	{
        if (!HouseInfo[id][hOwnerID])	return SendSyntaxMessage(playerid, "Evin içini kontrol etmek için /evkontrol'i kullanýn.");
	    if (HouseInfo[id][hLocked])		return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

        if (!GetWorld(playerid) && !GetInterior(playerid))	GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid,HouseInfo[id][hExitX],HouseInfo[id][hExitY],HouseInfo[id][hExitZ]);
		SetInterior(playerid,HouseInfo[id][hExitInt]);
		SetWorld(playerid,HouseInfo[id][hExitVW]);
		PlayerEnterFreeze(playerid);
		pTemp[playerid][pHouseEntered] = id;

		if (PlayerInfo[playerid][pRentKey] == HouseInfo[id][hID] || HouseInfo[id][hOwnerID] == PlayerInfo[playerid][pID])	GameTextForPlayer(playerid, "~w~EVINE ~y~HOS GELDIN", 4000, 1);

		if (HouseInfo[id][hRadioOn] == 1)
		{
		    pTemp[playerid][pBoombox_house] = id;
			PlayAudioStreamForPlayer(playerid, HouseInfo[id][hRadioURL]);
		}

		PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
		return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearOutsideExtHouse(playerid)) != -1)
	{
		if (!HouseInfo[id][hExtX][1] && !HouseInfo[id][hExtX][1] && !HouseInfo[id][hExtX][1]) return 1;
	    if (HouseInfo[id][hLocked])		return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

        if (!GetWorld(playerid) && !GetInterior(playerid))	GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid,HouseInfo[id][hExtX][1],HouseInfo[id][hExtY][1],HouseInfo[id][hExtZ][1]);
		SetInterior(playerid,HouseInfo[id][hExtInt][1]);
		SetWorld(playerid,HouseInfo[id][hExtVW][1]);
		PlayerEnterFreeze(playerid);
		pTemp[playerid][pHouseEntered] = id;

		if (PlayerInfo[playerid][pRentKey] == HouseInfo[id][hID] || HouseInfo[id][hOwnerID] == PlayerInfo[playerid][pID])	GameTextForPlayer(playerid, "~w~EVINE ~y~HOS GELDIN", 4000, 1); //î

		if (HouseInfo[id][hRadioOn] == 1)
		{
		    pTemp[playerid][pBoombox_house] = id;
			PlayAudioStreamForPlayer(playerid, HouseInfo[id][hRadioURL]);
		}

		PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
		return 1;
	}

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (IsPlayerBizOutside(playerid, i, 5.0) && BizInfo[i][bizType] == BIZ_TUNING && IsDriver(playerid)) return ShowModMenu(playerid);

		if (IsPlayerBizOutside(playerid, i, 5.0) && BizInfo[i][bizType] == BIZ_PAYNSPRAY)
		{
			if (BizInfo[i][bizLocked])									return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
			if (!GetPlayerVehicleID(playerid))							return SendErrorMessage(playerid, "Araçta olmalýsýnýz.");
            if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)			return SendErrorMessage(playerid, "Araçta olmalýsýnýz. ");
			if (VehicleInfo[GetPlayerVehicleID(playerid)][carEngineOn])	return SendErrorMessage(playerid, "Tamire baþlamadan önce motorunuzu durdurun!");
			if (GetCash(playerid) < BizInfo[i][bizEntrance])				return SendErrorMessage(playerid, "Giriþ maliyeti: $%i.", BizInfo[i][bizEntrance]);
			if (BizInfo[i][bizOwnerID] && !BizInfo[i][bizProduct])		return SendErrorMessage(playerid, "Ýþyerinde yeterli ürün yok.");
			    
			new Float: health;
			AntiCheatGetVehicleHealth(GetPlayerVehicleID(playerid), health);

			if (health < 230.0) return SendErrorMessage(playerid, "Bu araç artýk tamir edilemez.");
			
			static const dlgstr[] = "{FFFFFF}Aracýnýzda hasar oluþtu: {FF6347}%i%%\n\
									{FFFFFF}Komple Tamir: {1b8922}$%i {C5C5C5}(( Motor ve Kaporta ))\n\
									{FFFFFF}Parça Tadilatý {C5C5C5}(( Sadece seçilen parçalar ))\n\
									{FFFFFF}Araç Mekanik & Elektrik {1b8922}$%i {C5C5C5}(( Araç caný ))\n\
									{FFFFFF}Akü Tamiri [ durum: {FF6347}%.2f%%{FFFFFF}]: {1b8922}$%i\n\
									{FFFFFF}Motor Tamiri [ durum: {FF6347}%.2f%%{FFFFFF}]: {1b8922}$%i";
			new mes[sizeof(dlgstr) + 64];

			new panels, doors, lights, tires;
			GetVehicleStatus(playerid, panels, doors, lights, tires);

			new 
				vehicle = GetPlayerVehicleID(playerid),
				model = GetVehicleModel(vehicle),
				common_per = floatround((100.0 - ((health/GetVehicleMaxHealth(model))*100) + (panels+doors+lights+tires)) / 5, floatround_ceil), //%
				hp_cost = floatround((100 - ((health/GetVehicleMaxHealth(model))*100)) * (GetVehiclePrice(model)/1000), floatround_ceil)
			;
			if (hp_cost < 0) hp_cost = 0;
			new 
				cost = 1 + floatround(GetVehiclePrice(model) / 100, floatround_ceil),
				common_cost = hp_cost +  floatround((cost * 0.5 * panels/100) + (cost * 0.25 * doors/100) + (cost * 0.1 * lights/100) + (cost * 0.15 * tires/100), floatround_ceil)
			;

			format(mes, sizeof(mes), dlgstr, 
				common_per,
				cost,
				hp_cost,
				VehicleInfo[vehicle][carBattery], floatround(GetVehiclePrice(model) / 100 * 5, floatround_ceil),
				VehicleInfo[vehicle][carEngine], floatround(GetVehiclePrice(model) / 100 * 10, floatround_ceil)
			);
			
			Dialog_Show(playerid, Autoservice, DIALOG_STYLE_TABLIST_HEADERS, "Araç Tamir", mes, "Seç", "Iptal");
			return 1;
		}
		if (IsPlayerBizOutside(playerid, i, 1.0))
		{
			GameTextForPlayer(playerid, "_", 1, 4);
			if (BizInfo[i][bizType] == BIZ_TUNING) 			return 1;
			else if (BizInfo[i][bizType] == BIZ_AUTOSALON) 	return Dialog_Show(playerid, SelectClass, DIALOG_STYLE_LIST, "Bir kategori seçin", "2 kapýlý araçlar\n\
																																				Lowrider araçlar\n\
																																				4 kapýlý ve lüks araçlar\n\
																																				Spor araçlar\n\
																																				Pickuplar ve panelvan araçlar\n\
																																				SUV araçlar\n\
																																				Kamyon ve iþci araclari\n\
																																				Motorsikletler / Bisikletler\n\
																																				Diðerleri\n\
																																				Premium araçlar ",
																																				"Seç", "Kapat");
			else if (BizInfo[i][bizType] == BIZ_BOATSALON) 	return ShowBoats(playerid);
			else if (BizInfo[i][bizType] == BIZ_FLYSALON) 	return ShowFly(playerid);
			else if (BizInfo[i][bizType] == BIZ_GAS_STATION) return SendHelpMessage(playerid, "/benzin - komutu ile yakýt ikmalini baþlatabilir ve durdurabilirsiniz. ");
			else if (BizInfo[i][bizType] == BIZ_ADVERT) 		return SendHelpMessage(playerid, "/reklam - kiþisel reklam, /mekanreklam - iþyerleri için duyuru /panokirala - reklam panosu kiralamak. ");

            if (IsPlayerInAnyVehicle(playerid))																																return 1;
			if (BizInfo[i][bizLocked] == 1)																																	return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
			if (PlayerInfo[playerid][pID] != BizInfo[i][bizOwnerID] && !PlayerInfo[playerid][pOnDuty] && PlayerInfo[playerid][pWorkOn] != BizInfo[i][bizID] && GetCash(playerid) < BizInfo[i][bizEntrance])	return GameTextForPlayer(playerid, "~r~YETERSIZ PARA!", 5000, 1);
            
			if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

			SetPlayerPosEx(playerid,BizInfo[i][bizExitX], BizInfo[i][bizExitY], BizInfo[i][bizExitZ]);
			SetInterior(playerid,BizInfo[i][bizExitInt]);
			SetWorld(playerid,BizInfo[i][bizExitVW]);

			if (strlen(BizInfo[i][bizMes]) > 1) SCM(playerid, COLOR_WHITE, BizInfo[i][bizMes]);

			if (PlayerInfo[playerid][pID] != BizInfo[i][bizOwnerID] && PlayerInfo[playerid][pWorkOn] != BizInfo[i][bizID] && !PlayerInfo[playerid][pOnDuty] && BizInfo[i][bizEntrance] > 0)
			{
				GiveCash(playerid, -BizInfo[i][bizEntrance]);
				GiveBizCash(i, BizInfo[i][bizEntrance]);
			}
             
			PlayerEnterFreeze(playerid); 
			pTemp[playerid][pBizEntered] = i;
			GameTextForPlayer(playerid, BizInfo[i][bizName], 5000, 1);
			
			if (BizInfo[i][bizRadioOn] == 1)
			{
			    pTemp[playerid][pBoombox_biz] = i;
				PlayAudioStreamForPlayer(playerid, BizInfo[i][bizRadioURL]);
			}
			return 1;
		}
	}

	if ((id = GetNearGarage(playerid)) != -1)
	{
	    if (GarageInfo[id][garageOwner] == 0 && IsPlayerInAnyVehicle(playerid))	return SendErrorMessage(playerid, "Bu garaja araç giremez.");
	    if (GarageInfo[id][garageLocked] != 0)									return SendErrorMessage(playerid, "Garaj kapýlarý kapalý.");

		if (IsDriver(playerid))
		{
			new vehicleid = GetPlayerVehicleID(playerid);
            if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

			foreach (new i : Player)
			{
			    if (!IsPlayerInVehicle(i, vehicleid)) continue;

				SetInterior(i, GarageInfo[id][garageExitInt]);
				SetWorld(i, GarageInfo[id][garageExitVW]);
				PlayerPlaySound(i, 1, 0.0, 0.0, 0.0);
			}
			
            PlayerEnterFreeze(playerid); 

			SetInterior(playerid, GarageInfo[id][garageExitInt]);
			SetWorld(playerid, GarageInfo[id][garageExitVW]);

			SetVehiclePos(vehicleid, GarageInfo[id][garageVeh_Exit][0], GarageInfo[id][garageVeh_Exit][1], GarageInfo[id][garageVeh_Exit][2]);
		    SetVehicleZAngle(vehicleid, GarageInfo[id][garageVeh_Exit][3]);
		    SetVehicleVirtualWorld(vehicleid, GarageInfo[id][garageExitVW]);
			LinkVehicleToInterior(vehicleid, GarageInfo[id][garageExitInt]);

			PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
		    return 1;
		}
		else if (!IsPlayerInAnyVehicle(playerid))
		{
		    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

			SetPlayerPosEx(playerid, GarageInfo[id][garagePlayer_Exit][0], GarageInfo[id][garagePlayer_Exit][1], GarageInfo[id][garagePlayer_Exit][2]);
		    SetInterior(playerid, GarageInfo[id][garageExitInt]);
			SetWorld(playerid, GarageInfo[id][garageExitVW]);

			PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
		}
	    return 1;
	}
	return 1;
}

CMD:cikis(playerid, params[])
{
    if (pTemp[playerid][pZond] != 0) return 1;
	if (PlayerInfo[playerid][pInjured] != 0) return 1;

	new id = -1;

	if (IsDriver(playerid) && (id = GetNearEntranceInside(playerid, 3.0)) != -1)
	{
        if (EntranceInfo[id][eVehicle] != 1)					return 1;
		if (PlayerInfo[playerid][pFaction] != EntranceInfo[id][eFaction] && EntranceInfo[id][eFaction] > 0)		return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);
		new vehicleid = GetPlayerVehicleID(playerid);
        if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		PlayerInfo[playerid][pLocationPos][0] = EntranceInfo[id][eEnterX];
		PlayerInfo[playerid][pLocationPos][1] = EntranceInfo[id][eEnterY];
		PlayerInfo[playerid][pLocationPos][2] = EntranceInfo[id][eEnterZ];

		SetInterior(playerid, EntranceInfo[id][eEnterInt]);
		SetWorld(playerid, EntranceInfo[id][eEnterVW]);
  
		foreach (new i : Player)
		{
			if (!IsPlayerInVehicle(i, vehicleid)) continue;

			SetInterior(i, EntranceInfo[id][eEnterInt]);
			SetWorld(i, EntranceInfo[id][eEnterVW]);
		}
			
        PlayerEnterFreeze(playerid); 
		SetVehiclePos(vehicleid, EntranceInfo[id][eEnterX], EntranceInfo[id][eEnterY], EntranceInfo[id][eEnterZ]);
		SetVehicleZAngle(vehicleid, EntranceInfo[id][eEnterA] - 180);
		SetVehicleVirtualWorld(vehicleid, EntranceInfo[id][eEnterVW]);
		LinkVehicleToInterior(vehicleid, EntranceInfo[id][eEnterInt]);

		PlayerPlaySound(playerid, 1, 0.0, 0.0, 0.0);
	    return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearEntranceInside(playerid)) != -1)
	{
	    //if (EntranceInfo[id][eLocked] == 1)	return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
		if (PlayerInfo[playerid][pFaction] != EntranceInfo[id][eFaction] && EntranceInfo[id][eFaction] > 0)		return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);

	    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPos(playerid, EntranceInfo[id][eEnterX], EntranceInfo[id][eEnterY], EntranceInfo[id][eEnterZ]);
		SetPlayerFacingAngle(playerid, EntranceInfo[id][eEnterA] - 180.0);
		SetInterior(playerid, EntranceInfo[id][eEnterInt]);
		SetWorld(playerid, EntranceInfo[id][eEnterVW]);

		PlayerEnterFreeze(playerid); 

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	    return 1;
	}
	
	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearEntranceInside(playerid)) != -1)
	{
	    //if (EntranceInfo[id][eLocked] == 1)	return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

	    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid, EntranceInfo[id][eEnterX], EntranceInfo[id][eEnterY], EntranceInfo[id][eEnterZ]);
		SetPlayerFacingAngle(playerid, EntranceInfo[id][eEnterA] - 180.0);
		SetInterior(playerid, EntranceInfo[id][eEnterInt]);
		SetWorld(playerid, EntranceInfo[id][eEnterVW]);

		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	    return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearApartmentInside(playerid, 1.0)) != -1)
	{
	    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid, ApartInfo[id][aPosX], ApartInfo[id][aPosY], ApartInfo[id][aPosZ]);
		SetWorld(playerid, ApartInfo[id][aPosVW]);
		SetInterior(playerid, ApartInfo[id][aPosInt]);
		pTemp[playerid][pApartEntered] = -1;

		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearInsideHouse(playerid, 2.0)) != -1)
	{
        if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);
        if (HouseInfo[id][hLocked])		return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

		SetPlayerPosEx(playerid,HouseInfo[id][hPosX],HouseInfo[id][hPosY],HouseInfo[id][hPosZ]);
		SetInterior(playerid, HouseInfo[id][hPosInt]);
		SetWorld(playerid,HouseInfo[id][hPosVW]);
        pTemp[playerid][pHouseEntered] = -1;
        DeletePVar(playerid, #check_int);

		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	    return 1;
	}
	else if (!IsPlayerInAnyVehicle(playerid) && (id = GetNearInsideExtHouse(playerid, 2.0)) != -1)
	{
		if (!HouseInfo[id][hExtX][0] && !HouseInfo[id][hExtX][0] && !HouseInfo[id][hExtX][0]) return 1;
		if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);
		if (HouseInfo[id][hLocked])		return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

		SetPlayerPosEx(playerid,HouseInfo[id][hExtX][0],HouseInfo[id][hExtY][0],HouseInfo[id][hExtZ][0]);
		SetInterior(playerid, HouseInfo[id][hExtInt][0]);
		SetWorld(playerid,HouseInfo[id][hExtVW][0]);
        pTemp[playerid][pHouseEntered] = -1;
        DeletePVar(playerid, #check_int);

		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	    return 1;
	}
	else if ((id = GetNearInsideBiz(playerid, 2.0)) != -1)
	{
	    if (BizInfo[id][bizType] == BIZ_GAS_STATION || BizInfo[id][bizType] == BIZ_AUTOSALON || BizInfo[id][bizType] == BIZ_BOATSALON || BizInfo[id][bizType] == BIZ_FLYSALON || BizInfo[id][bizType] == BIZ_TUNING || BizInfo[id][bizType] == BIZ_ADVERT || BizInfo[id][bizType] == BIZ_LICENSE)
		{
			return 1;
		}

        if (BizInfo[id][bizLocked])									return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
        if (!GetWorld(playerid) && !GetInterior(playerid))	GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

		SetPlayerPosEx(playerid,BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]);
		SetInterior(playerid,BizInfo[id][bizPosInt]);
		SetWorld(playerid,BizInfo[id][bizPosVW]);
		pTemp[playerid][pBizEntered] = -1;

		PlayerEnterFreeze(playerid);

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		return 1;
	}
	else if ((id = GetNearGarage(playerid)) != -1)
	{
	    if (GarageInfo[id][garageLocked] != 0)	return SendErrorMessage(playerid,"Garaj kapýlarý kapalý.");

		if (IsDriver(playerid))
		{
		    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);
			new vehicleid = GetPlayerVehicleID(playerid);

		    PlayerInfo[playerid][pLocationPos][0] = GarageInfo[id][garageVeh_Enter][0];
			PlayerInfo[playerid][pLocationPos][1] = GarageInfo[id][garageVeh_Enter][1];
			PlayerInfo[playerid][pLocationPos][2] = GarageInfo[id][garageVeh_Enter][2];

			foreach (new i : Player)
			{
			    if (!IsPlayerInVehicle(i, vehicleid)) continue;

				SetInterior(i, GarageInfo[id][garageEnterInt]);
				SetWorld(i, GarageInfo[id][garageEnterVW]);
				PlayerPlaySound(i, 0, 0.0, 0.0, 0.0);
			}
			
			SetInterior(playerid, GarageInfo[id][garageEnterInt]);
			SetWorld(playerid, GarageInfo[id][garageEnterVW]);

			SetVehiclePos(vehicleid, GarageInfo[id][garageVeh_Enter][0], GarageInfo[id][garageVeh_Enter][1], GarageInfo[id][garageVeh_Enter][2]);
		    SetVehicleZAngle(vehicleid, GarageInfo[id][garageVeh_Enter][3]);
		    SetVehicleVirtualWorld(vehicleid, GarageInfo[id][garageEnterVW]);
			LinkVehicleToInterior(vehicleid, GarageInfo[id][garageEnterInt]);

			PlayerEnterFreeze(playerid);

			PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		    return 1;
		}
		else if (!IsPlayerInAnyVehicle(playerid))
		{
		    if (!GetWorld(playerid) && !GetInterior(playerid)) GetPlayerPos(playerid, PlayerInfo[playerid][pLocationPos][0], PlayerInfo[playerid][pLocationPos][1], PlayerInfo[playerid][pLocationPos][2]);

			SetPlayerPosEx(playerid, GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2]);
		    SetInterior(playerid, GarageInfo[id][garageEnterInt]);
			SetWorld(playerid, GarageInfo[id][garageEnterVW]);

			PlayerEnterFreeze(playerid);

			PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		}
	    return 1;
	}
	return 1;
}