GetPlayerAcceptAction(playerid)
{
	if (GetPVarInt(playerid, #accept_time) < gettime()) return 0;

	if (pTemp[playerid][pGreetPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pGreetPlayer], type = pTemp[playerid][pGreetType];

	    pTemp[playerid][pGreetPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pGreetType] = 0;

		if (IsPlayerLogged(userid) == 0)				return SendErrorMessage(playerid, "Size teklif gönderen oyuncu çevrimiçi deðil.");
		if (!PlayerNearPlayer(1.0, playerid, userid))	return SendNotNearPlayer(playerid);

		StopPlayerAnims(playerid);
		StopPlayerAnims(userid);
		SetPlayerFacePlayer(playerid, userid);
		SetPlayerFacePlayer(userid, playerid);
		
		switch(type)
		{
			case 1:
			{
				ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 2.0, 0, 0, 1, 0, 0, 1);
				ApplyAnimation(userid, "KISSING", "Playa_Kiss_02", 2.0, 0, 0, 1, 0, 0, 1);
			}
			case 2:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkfa_swt", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkfa_swt", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 3:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkba", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkba", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 4:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkca", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkca", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 5:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkcb", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkcb", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 6:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkda", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkda", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 7:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkda", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkda", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 8:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkaa", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "hndshkaa", 2.0, 0, 0, 0, 0, 0, 1);
			}
			case 9:
			{
				ApplyAnimation(playerid, "GANGS", "prtial_hndshk_biz_01", 2.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(userid, "GANGS", "prtial_hndshk_biz_01", 2.0, 0, 0, 0, 0, 0, 1);
			}
		}
		return 1;
	}

    else if (pTemp[playerid][pCarPlayer] != INVALID_PLAYER_ID)
	{
  		new query[256];
    	mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `cars` WHERE `owner` = %i", PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query, "BuyVehicleAtPlayer", "i", playerid);
   		return 1;
	}

    else if (pTemp[playerid][pHealPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pHealPlayer];
	    pTemp[playerid][pHealPlayer] = INVALID_PLAYER_ID;

	    if (!IsPlayerLogged(userid))				return SendErrorMessage(playerid, "Sizi tedavi etmek isteyen oyuncu çevrimiçi deðil.");
        if (PlayerInfo[playerid][pInjured] != 0)	return SendErrorMessage(playerid, "Aðýr yaralandýn.");

		SendSyntaxMessage(playerid, "%s iyileþtirildi.", GetNameWithMask(userid));
		SendSyntaxMessage(userid, "%s sizi iyileþtirdi.", GetNameWithMask(playerid));
		PlayerInfo[playerid][pHealth] = 100.0;
		return 1;
	}
	else if (pTemp[playerid][pWepPlayer] != INVALID_PLAYER_ID)
	{
		new userid = pTemp[playerid][pWepPlayer],
		    price = pTemp[playerid][pWepPrice];

        pTemp[playerid][pWepPlayer] = INVALID_PLAYER_ID;

		if (!IsPlayerLogged(userid))		return SendErrorMessage(playerid, "Size silah lisansýný teklif eden oyuncu çevrimiçi deðil.");
		if (GetCash(playerid) < price)	return SendNotCash(playerid);

		GiveCash(playerid, -price);
		PlayerInfo[playerid][pWepLic] = 1;
		PlayerInfo[playerid][pWepWarns] = 0;
        PlayerInfo[playerid][pWepCount] = 3;

        new query[168];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `wep_count`='3',`weplic`='1',`wepwarns`='0',`wep_officer`='%s',`wep_data`='%s',`wep_price`=%i WHERE `id` = %i", GetNameEx(userid), GetFullDate(), price, PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query);

		SendSyntaxMessage(userid, "%s sizden $%i karþýlýðýnda silah ruhsatý aldý.", GetNameEx(playerid), price);
        SendSyntaxMessage(playerid, "%s adlý oyuncudan $%i karþýlýðýnda silah ruhsatý aldýnýz.", GetNameEx(userid), price);
		return 1;
	}

	else if (pTemp[playerid][pHirePlayer] != INVALID_PLAYER_ID)
	{
        new userid = pTemp[playerid][pHirePlayer];
		DebugMessage(playerid, sprintf("davet eden %d, davet alan %d", userid, playerid));

        if (!IsPlayerLogged(userid))					return SendErrorMessage(playerid, "Size iþ teklif eden oyuncu çevrimiçi deðil.");
        if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

        new bizid = GetNearBiz(playerid);

		if (bizid < 1)	return SendErrorMessage(playerid, "Yakýnýnýzda bir mekan yok.");
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(playerid, "Bulunduðunuz mekanýn sahibi sizi davet eden kiþi deðil.");

		PlayerInfo[playerid][pWorkOn] = BizInfo[bizid][bizID];
		SQL_SetInteger("users", "workon", BizInfo[bizid][bizID], PlayerInfo[playerid][pID]);

		new j = WorkSpace(bizid);
		BizWorkers[bizid][j][bizJobOn] = PlayerInfo[playerid][pID];
		format(BizWorkers[bizid][j][bizWorker], MAX_PLAYER_NAME, "%s", GetNameEx(playerid));
		format(BizWorkers[bizid][j][bizPosition], MAX_PLAYER_NAME, "Pozisyon yok");

		SendSyntaxMessage(playerid, "%s iþ teklifini kabul etti.", GetNameEx(userid));
		SendSyntaxMessage(userid, "%s adlý kiþinin iþ teklifini kabul ettiniz.", GetNameEx(playerid));

		pTemp[playerid][pHirePlayer] = INVALID_PLAYER_ID;
		return 1;
	}

	else if (pTemp[playerid][pFactionPlayer] != INVALID_PLAYER_ID)
	{
		new targetid = pTemp[playerid][pFactionPlayer];

        if (!IsPlayerLogged(targetid))								return SendErrorMessage(playerid, "Sizi birliðe davet eden oyuncu çevrimiçi deðil.");
        if (!isLeader(targetid) || !GetInviteRight(targetid))		return 1;
	    if (!Factions[PlayerInfo[targetid][pFaction]][fJoinRank])	return SendErrorMessage(playerid, "Giriþ yapamazsýnýz. Birlikteki rütbeler ve maaþlar yapýlmamýþ.");

		/*PlayerInfo[playerid][pFaction] = PlayerInfo[targetid][pFaction];
		PlayerInfo[playerid][pRank] = Factions[PlayerInfo[targetid][pFaction]][fJoinRank];*/
		
		PlayerInfo[playerid][pFaction] = pTemp[playerid][pFactionInvite];
		PlayerInfo[playerid][pRank] = Factions[PlayerInfo[targetid][pFaction]][fJoinRank];

		pTemp[playerid][pFactionInvite] = 0;
		pTemp[playerid][pFactionInvitedBy] = INVALID_PLAYER_ID;

		PlayerInfo[playerid][pBadgeNumber] = randomEx(23465, 99999);

		SendSyntaxMessage(playerid, "%s birliðine katýldýn.", Factions[PlayerInfo[targetid][pFaction]][fName]);
		SM1(targetid, "%s adlý kiþi birlik davetinizi kabul etti.", GetNameWithMask(playerid));
		SendFactionMessageF(PlayerInfo[targetid][pFaction], COLOR_LIGHTBLUE, "[BÝRLÝK] %s adlý kiþi %s tarafýndan birliðe davet edildi ve birliðe katýldý.", GetNameEx(targetid), GetNameEx(playerid));

		pTemp[playerid][pFactionPlayer] = INVALID_PLAYER_ID;
		return 1;
	}

	else if (RefillOffer[playerid] != INVALID_PLAYER_ID)
	{
		new userid = RefillOffer[playerid], price = RefillPrice[playerid], vehicle = GetPlayerVehicleID(playerid);

        if (!IsPlayerLogged(userid)) return SendErrorMessage(playerid, "Size yakýt doldurmayý teklif eden oyuncu çevrimiçi deðil.");
		    
        RefillPrice[playerid] = 0;
		RefillOffer[playerid] = INVALID_PLAYER_ID;

		if (!IsDriver(playerid))						return SendErrorMessage(playerid, "Aracýn sürücü koltuðunda olmalýsýnýz.");
		if (!PlayerNearPlayer(6.0, playerid, userid))	return SendNotNearPlayer(playerid);
		if (GetCash(playerid) < price)					return SendNotCash(playerid);

		GiveCash(playerid, -price);
		GiveCash(userid, price);
		VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

		new mes[128];
		format(mes, sizeof(mes), "%s kiþisinin aracýna $%i karþýlýðýnda yakýt doldurur..", GetNameWithMask(userid), price);
		pc_cmd_me(playerid, mes);

		return 1;
	}

	else if (pTemp[playerid][pServePlayer] != INVALID_PLAYER_ID && pTemp[playerid][pServeType] == 5) //ýâèê
	{
		new mechanicid = pTemp[playerid][pServePlayer], vehicle = GetPVarInt(playerid, #tow_car);

		pTemp[playerid][pServePlayer] = INVALID_PLAYER_ID;
        pTemp[playerid][pServeType] = 0;

        if (!IsPlayerLogged(mechanicid))															return SendErrorMessage(playerid, "Sizi çaðýran oyuncu çevrimiçi deðil.");
        if (PlayerInfo[mechanicid][pJob] != JOB_MECHANIC)											return SendErrorMessage(playerid, "Bu oyuncu mekanik deðil.");
		if (!IsDriver(mechanicid) || !IsATowTruck(GetPlayerVehicleID(mechanicid)))					return SendErrorMessage(playerid, "Mekanik olarak sürücü koltuðunda olmalýsýnýz.");
		if (!PlayerNearPlayer(7.0, playerid, mechanicid))											return SendNotNearPlayer(playerid);
		if (IsPlayerInAnyVehicle(playerid))															return SendErrorMessage(playerid, "Arabada olmamalýsýnýz.");
        if (GetNearVehicle(mechanicid, 7.0, vehicle) == 0)											return SendErrorMessage(playerid, "Aracýn yakýnýnda olmalýsýnýz.");
        if (IsABoat(vehicle) || IsAPlane(vehicle) || IsAHelicopter(vehicle) || IsABiker(vehicle))	return SendErrorMessage(playerid, "Bu araç çekilemez.");

		new mes[128];
		format(mes, sizeof(mes), "%s adlý kiþinin %s model aracýný çeker.", GetNameWithMask(mechanicid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes); 

		AttachTrailerToVehicle(vehicle, GetPlayerVehicleID(mechanicid));
		return 1;
	}

	else if (pTemp[playerid][pServePlayer] != INVALID_PLAYER_ID && (pTemp[playerid][pServeType] > 0 && pTemp[playerid][pServeType] < 5))
	{
		new vehicle = GetPlayerVehicleID(playerid), mechanicid = pTemp[playerid][pServePlayer], type = pTemp[playerid][pServeType], vehid = GetPlayerVehicleID(mechanicid);

        pTemp[playerid][pServePlayer] = INVALID_PLAYER_ID;
        pTemp[playerid][pServeType] = 0;

        if (!IsPlayerLogged(mechanicid))										return SendErrorMessage(playerid, "Size teklif sunan mekanik çevrimiçi deðil.");
        if (PlayerInfo[mechanicid][pJob] != JOB_MECHANIC)						return SendErrorMessage(playerid, "Bu oyuncu mekanik deðil.");
		if (!IsDriver(mechanicid) || !IsATowTruck(vehid))						return SendErrorMessage(playerid, "Mekanik olarak sürücü koltuðunda olmalýsýnýz.  ");
		if (!IsDriver(playerid))												return SendErrorMessage(playerid, "Sürücü koltuðunda olmalýsýnýz. ");
		if (!PlayerNearPlayer(6.0, playerid, mechanicid))						return SendNotNearPlayer(playerid);
        if (VehicleInfo[vehicle][carFaction] != 0 && type != 1 && type != 2)	return SendErrorMessage(playerid, "Bu araç devlete aittir.");

		new mes[128];

		switch(type)
		{
		    case 1: format(mes, sizeof(mes), "%s model aracýn motor bölümünde iþlem yapmak için bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 2: format(mes, sizeof(mes), "%s model aracýn kaportasýnda iþlem yapmak için bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 3: format(mes, sizeof(mes), "%s model aracý onarmak için bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 4: format(mes, sizeof(mes), "%s model aracý boyamak için bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		}
		pc_cmd_me(playerid, mes);

		RepairOffer[mechanicid] = playerid;
		RepairToVehicle[mechanicid] = vehicle;
		RepairService[mechanicid] = type;
		RepairTowTruck[mechanicid] = vehid;

		ShowJobMessage(mechanicid, "~h~~p~SPREY KUTUSUNU CIKARTIN");
		return 1;
	}

	else if (pTemp[playerid][pHousePlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pHousePlayer], price = pTemp[playerid][pHousePrice], houseid = pTemp[playerid][pHouseHouse];

        pTemp[playerid][pHouseHouse] = -1;
		pTemp[playerid][pHousePrice] = 0;
		pTemp[playerid][pHousePlayer] = INVALID_PLAYER_ID;

        if (!IsPlayerLogged(userid))									return SendErrorMessage(playerid, "Ev teklifi gönderen oyuncu çevrimiçi deðil.");
		if (houseid == -1)												return SendErrorMessage(playerid, "Kimse size ev alma teklifi göndermedi.");
        if (price < 0 || price > 100000000)								return SendErrorMessage(playerid, "$0 ve $100000000 arasý satýþ tutarý sunabilirsiniz.");
		if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
	    if (IsPlayerOutsideHouse(playerid, houseid) == 0)				return SendErrorMessage(playerid, "Satýn almak istediðiniz evin yakýnýnda olmalýsýnýz..");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(playerid, "Bu ev %s 'e ait deðil .", GetNameEx(userid));
		if (GetCash(playerid) < price)									return SendNotCash(playerid);
        if (GetPlayerHouses(playerid) >= GetMaxPlayerHouse(playerid))	return SendErrorMessage(playerid, "Daha fazla ev satýn alamazsýnýz.");

		HouseInfo[houseid][hOwnerID] = PlayerInfo[playerid][pID];
        format(HouseInfo[houseid][hOwner], MAX_PLAYER_NAME, GetNameEx(playerid));
		GiveCash(playerid, -price);
		GiveCash(userid, price);

        for(new i = 0; i != MAX_GARAGES; i++)
		{
		    if (!GarageInfo[i][garageID] || GarageInfo[i][garageHouse] != HouseInfo[houseid][hID]) continue;

			SendSyntaxMessage(playerid, "Evle birlikte bir garajýnýzda var. [ID: %i].", i);

			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			format(GarageInfo[i][garageOwnerName], 24, "%s", GetNameEx(playerid));
		
			SQL_SetInteger("garage", "owner", GarageInfo[i][garageOwner], GarageInfo[i][garageID]);
			SQL_SetString("users", "name", GarageInfo[i][garageOwnerName], GarageInfo[i][garageOwner]);
		}

		Save_House(houseid);

		SendSyntaxMessage(playerid, "%s oyuncusundan $%i karþýlýðýnda bir ev satýn aldýnýz.", GetNameEx(userid), price);
    	SendSyntaxMessage(userid, "%s  adlý oyuncu sizden $%i karþýlýðýnda evi satýn aldý.", GetNameEx(playerid), price);
    	return 1;
	}

	else if (pTemp[playerid][pBizPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pBizPlayer], price = pTemp[playerid][pBizPrice], bizid = pTemp[playerid][pBizID];

        pTemp[playerid][pBizPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pBizPrice] = 0;
		pTemp[playerid][pBizID] = INVALID_PLAYER_ID;

        if (!IsPlayerLogged(userid))									return SendErrorMessage(playerid, "Ýþyeri satýn alma teklifi gönderen oyuncu çevrimiçi deðil.");
		if (bizid == -1)												return SendErrorMessage(playerid, "Kimse size bir iþyeri satýn alma teklifi göndermedi. ");
        if (price < 0 || price > 100000000)								return SendErrorMessage(playerid, "$0 ve $100000000 arasý satýþ tutarý sunabilirsiniz.");
		if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[userid][pID])		return SendErrorMessage(playerid, "Bu iþletme %s adlý oyuncuya ait deðil.", GetNameEx(userid));
		if (GetCash(playerid) < price)									return SendNotCash(playerid);
        if (GetPlayerBizes(playerid) >= GetMaxPlayerBiz(playerid))		return SendErrorMessage(playerid, "Daha fazla iþyeri satýn alamazsýnýz.");

		if (IsPlayerBizOutside(playerid, bizid) == 0 && IsPlayerBizInside(playerid, bizid) == 0) return SendErrorMessage(playerid, "Satýn almak istediðiniz iþletmenin yakýnýnda olmalýsýnýz.");
		
		BizInfo[bizid][bizOwnerID] = PlayerInfo[playerid][pID];
		format(BizInfo[bizid][bizOwner], MAX_PLAYER_NAME, "%s", GetName(playerid));

		GiveCash(playerid, -price);
		GiveCash(userid, price);

		for(new i = 0; i != MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageBiz] != BizInfo[bizid][bizID]) continue;

			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			SendSyntaxMessage(playerid, "Ýþyeriniz ile birlikte bir garajýnýz da var. [ID: %i].", i);

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `garage` SET `owner`=%i WHERE `id`=%i", PlayerInfo[playerid][pID], GarageInfo[i][garageID]);
			mysql_tquery(dbHandle, query);
		}

		RemoveAllWorkers(bizid);
		Save_Business(bizid);

		SendSyntaxMessage(playerid, "%s adlý oyuncudan $%i karþýlýðýnda bir iþyeri satýn aldýnýz.", GetNameEx(userid), price);
    	SendSyntaxMessage(userid, "%s adlý oyuncu sizden $%i karþýlýðýnda bir iþyeri satýn aldý.", GetNameEx(playerid), price);
    	return 1;
	}

	else if (pTemp[playerid][pRentPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pRentPlayer], price = pTemp[playerid][pRentPrice];

        pTemp[playerid][pRentPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pRentPrice] = 0;

		if (!IsPlayerLogged(userid))					return SendErrorMessage(playerid, "Size ev kirasý teklif eden oyuncu çevrimiçi deðil.");
        if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

		new houseid;

		if ((houseid = GetNearInsideHouse(userid)) == -1)				return SendErrorMessage(userid, "Evin içinde olmalýsýnýz.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(userid, "Bu ev size ait deðil.");
        if (GetCash(playerid) < price)									return SendErrorMessage(playerid, "Ön ödemeniz için $%i paranýz yok.", price);

		PlayerInfo[playerid][pRentKey] = HouseInfo[houseid][hID];
		PlayerInfo[playerid][pRentPrice] = price;
		SendSyntaxMessage(playerid, "%s adlý kiþinin evini kiraladýnýz. Her maaþ ödenecek tutar: $%i.", GetNameWithMask(userid), price);
		SendSyntaxMessage(playerid, "Evden istediðiniz zaman /evkiraiptal komutunu kullanarak çýkabilirsiniz.");
		SendSyntaxMessage(userid, "%s adlý oyuncu evinizi kiraladý. Her maaþta gelecek tutar: $%i", GetNameWithMask(playerid), price);

		new query[256];
        format(query, sizeof(query), "UPDATE `users` SET `rent_key`=%i,`rent_price`=%i WHERE `id`=%i", PlayerInfo[playerid][pRentKey], PlayerInfo[playerid][pRentPrice], PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query);

		return 1;
	}

	else if (pTemp[playerid][pInterviewPlayer] != INVALID_PLAYER_ID)
	{
		if (PlayerInfo[playerid][pSettings] & togNews)	return SendErrorMessage(playerid, "Önce SAN'dan gelen mesajlarýn görüntülenmesini etkinleþtirin. (/tog news).");

		new userid = pTemp[playerid][pInterviewPlayer];

    	pTemp[playerid][pInterviewPlayer] = INVALID_PLAYER_ID;

        if (!IsPlayerLogged(userid))						return SendErrorMessage(playerid, "Size röportaj teklif eden oyuncu çevrimiçi deðil.");
		if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);

		pTemp[playerid][pInterview] = userid;
		SendSyntaxMessage(playerid, "%s adlý oyuncunun röportaj teklifini kabul ettiniz.", GetNameWithMask(userid));
    	SendSyntaxMessage(playerid, "Yayýn yapmak için normal sohbeti kullanýn. /yayindanayril  komutu ile röportajý sonlandýrabilirsiniz.");
		SendSyntaxMessage(userid, "%s adlý oyuncu röportaj yapma teklifinizi kabul etti.", GetNameWithMask(playerid));

		return 1;
	}

	DeletePVar(playerid, #accept_time);
	
	return 0;
}

GetPlayerDeniedAction(playerid) {
	if (GetPVarInt(playerid, #accept_time) < gettime()) return 0;
	DeletePVar(playerid, #accept_time);
	return 1;
}