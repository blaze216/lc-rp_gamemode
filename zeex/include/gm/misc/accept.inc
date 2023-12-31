GetPlayerAcceptAction(playerid)
{
	if (GetPVarInt(playerid, #accept_time) < gettime()) return 0;

	if (pTemp[playerid][pGreetPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pGreetPlayer], type = pTemp[playerid][pGreetType];

	    pTemp[playerid][pGreetPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pGreetType] = 0;

		if (IsPlayerLogged(userid) == 0)				return SendErrorMessage(playerid, "Size teklif g�nderen oyuncu �evrimi�i de�il.");
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

	    if (!IsPlayerLogged(userid))				return SendErrorMessage(playerid, "Sizi tedavi etmek isteyen oyuncu �evrimi�i de�il.");
        if (PlayerInfo[playerid][pInjured] != 0)	return SendErrorMessage(playerid, "A��r yaraland�n.");

		SendSyntaxMessage(playerid, "%s iyile�tirildi.", GetNameWithMask(userid));
		SendSyntaxMessage(userid, "%s sizi iyile�tirdi.", GetNameWithMask(playerid));
		PlayerInfo[playerid][pHealth] = 100.0;
		return 1;
	}
	else if (pTemp[playerid][pWepPlayer] != INVALID_PLAYER_ID)
	{
		new userid = pTemp[playerid][pWepPlayer],
		    price = pTemp[playerid][pWepPrice];

        pTemp[playerid][pWepPlayer] = INVALID_PLAYER_ID;

		if (!IsPlayerLogged(userid))		return SendErrorMessage(playerid, "Size silah lisans�n� teklif eden oyuncu �evrimi�i de�il.");
		if (GetCash(playerid) < price)	return SendNotCash(playerid);

		GiveCash(playerid, -price);
		PlayerInfo[playerid][pWepLic] = 1;
		PlayerInfo[playerid][pWepWarns] = 0;
        PlayerInfo[playerid][pWepCount] = 3;

        new query[168];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `wep_count`='3',`weplic`='1',`wepwarns`='0',`wep_officer`='%s',`wep_data`='%s',`wep_price`=%i WHERE `id` = %i", GetNameEx(userid), GetFullDate(), price, PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query);

		SendSyntaxMessage(userid, "%s sizden $%i kar��l���nda silah ruhsat� ald�.", GetNameEx(playerid), price);
        SendSyntaxMessage(playerid, "%s adl� oyuncudan $%i kar��l���nda silah ruhsat� ald�n�z.", GetNameEx(userid), price);
		return 1;
	}

	else if (pTemp[playerid][pHirePlayer] != INVALID_PLAYER_ID)
	{
        new userid = pTemp[playerid][pHirePlayer];
		DebugMessage(playerid, sprintf("davet eden %d, davet alan %d", userid, playerid));

        if (!IsPlayerLogged(userid))					return SendErrorMessage(playerid, "Size i� teklif eden oyuncu �evrimi�i de�il.");
        if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

        new bizid = GetNearBiz(playerid);

		if (bizid < 1)	return SendErrorMessage(playerid, "Yak�n�n�zda bir mekan yok.");
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(playerid, "Bulundu�unuz mekan�n sahibi sizi davet eden ki�i de�il.");

		PlayerInfo[playerid][pWorkOn] = BizInfo[bizid][bizID];
		SQL_SetInteger("users", "workon", BizInfo[bizid][bizID], PlayerInfo[playerid][pID]);

		new j = WorkSpace(bizid);
		BizWorkers[bizid][j][bizJobOn] = PlayerInfo[playerid][pID];
		format(BizWorkers[bizid][j][bizWorker], MAX_PLAYER_NAME, "%s", GetNameEx(playerid));
		format(BizWorkers[bizid][j][bizPosition], MAX_PLAYER_NAME, "Pozisyon yok");

		SendSyntaxMessage(playerid, "%s i� teklifini kabul etti.", GetNameEx(userid));
		SendSyntaxMessage(userid, "%s adl� ki�inin i� teklifini kabul ettiniz.", GetNameEx(playerid));

		pTemp[playerid][pHirePlayer] = INVALID_PLAYER_ID;
		return 1;
	}

	else if (pTemp[playerid][pFactionPlayer] != INVALID_PLAYER_ID)
	{
		new targetid = pTemp[playerid][pFactionPlayer];

        if (!IsPlayerLogged(targetid))								return SendErrorMessage(playerid, "Sizi birli�e davet eden oyuncu �evrimi�i de�il.");
        if (!isLeader(targetid) || !GetInviteRight(targetid))		return 1;
	    if (!Factions[PlayerInfo[targetid][pFaction]][fJoinRank])	return SendErrorMessage(playerid, "Giri� yapamazs�n�z. Birlikteki r�tbeler ve maa�lar yap�lmam��.");

		/*PlayerInfo[playerid][pFaction] = PlayerInfo[targetid][pFaction];
		PlayerInfo[playerid][pRank] = Factions[PlayerInfo[targetid][pFaction]][fJoinRank];*/
		
		PlayerInfo[playerid][pFaction] = pTemp[playerid][pFactionInvite];
		PlayerInfo[playerid][pRank] = Factions[PlayerInfo[targetid][pFaction]][fJoinRank];

		pTemp[playerid][pFactionInvite] = 0;
		pTemp[playerid][pFactionInvitedBy] = INVALID_PLAYER_ID;

		PlayerInfo[playerid][pBadgeNumber] = randomEx(23465, 99999);

		SendSyntaxMessage(playerid, "%s birli�ine kat�ld�n.", Factions[PlayerInfo[targetid][pFaction]][fName]);
		SM1(targetid, "%s adl� ki�i birlik davetinizi kabul etti.", GetNameWithMask(playerid));
		SendFactionMessageF(PlayerInfo[targetid][pFaction], COLOR_LIGHTBLUE, "[B�RL�K] %s adl� ki�i %s taraf�ndan birli�e davet edildi ve birli�e kat�ld�.", GetNameEx(targetid), GetNameEx(playerid));

		pTemp[playerid][pFactionPlayer] = INVALID_PLAYER_ID;
		return 1;
	}

	else if (RefillOffer[playerid] != INVALID_PLAYER_ID)
	{
		new userid = RefillOffer[playerid], price = RefillPrice[playerid], vehicle = GetPlayerVehicleID(playerid);

        if (!IsPlayerLogged(userid)) return SendErrorMessage(playerid, "Size yak�t doldurmay� teklif eden oyuncu �evrimi�i de�il.");
		    
        RefillPrice[playerid] = 0;
		RefillOffer[playerid] = INVALID_PLAYER_ID;

		if (!IsDriver(playerid))						return SendErrorMessage(playerid, "Arac�n s�r�c� koltu�unda olmal�s�n�z.");
		if (!PlayerNearPlayer(6.0, playerid, userid))	return SendNotNearPlayer(playerid);
		if (GetCash(playerid) < price)					return SendNotCash(playerid);

		GiveCash(playerid, -price);
		GiveCash(userid, price);
		VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

		new mes[128];
		format(mes, sizeof(mes), "%s ki�isinin arac�na $%i kar��l���nda yak�t doldurur..", GetNameWithMask(userid), price);
		pc_cmd_me(playerid, mes);

		return 1;
	}

	else if (pTemp[playerid][pServePlayer] != INVALID_PLAYER_ID && pTemp[playerid][pServeType] == 5) //����
	{
		new mechanicid = pTemp[playerid][pServePlayer], vehicle = GetPVarInt(playerid, #tow_car);

		pTemp[playerid][pServePlayer] = INVALID_PLAYER_ID;
        pTemp[playerid][pServeType] = 0;

        if (!IsPlayerLogged(mechanicid))															return SendErrorMessage(playerid, "Sizi �a��ran oyuncu �evrimi�i de�il.");
        if (PlayerInfo[mechanicid][pJob] != JOB_MECHANIC)											return SendErrorMessage(playerid, "Bu oyuncu mekanik de�il.");
		if (!IsDriver(mechanicid) || !IsATowTruck(GetPlayerVehicleID(mechanicid)))					return SendErrorMessage(playerid, "Mekanik olarak s�r�c� koltu�unda olmal�s�n�z.");
		if (!PlayerNearPlayer(7.0, playerid, mechanicid))											return SendNotNearPlayer(playerid);
		if (IsPlayerInAnyVehicle(playerid))															return SendErrorMessage(playerid, "Arabada olmamal�s�n�z.");
        if (GetNearVehicle(mechanicid, 7.0, vehicle) == 0)											return SendErrorMessage(playerid, "Arac�n yak�n�nda olmal�s�n�z.");
        if (IsABoat(vehicle) || IsAPlane(vehicle) || IsAHelicopter(vehicle) || IsABiker(vehicle))	return SendErrorMessage(playerid, "Bu ara� �ekilemez.");

		new mes[128];
		format(mes, sizeof(mes), "%s adl� ki�inin %s model arac�n� �eker.", GetNameWithMask(mechanicid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes); 

		AttachTrailerToVehicle(vehicle, GetPlayerVehicleID(mechanicid));
		return 1;
	}

	else if (pTemp[playerid][pServePlayer] != INVALID_PLAYER_ID && (pTemp[playerid][pServeType] > 0 && pTemp[playerid][pServeType] < 5))
	{
		new vehicle = GetPlayerVehicleID(playerid), mechanicid = pTemp[playerid][pServePlayer], type = pTemp[playerid][pServeType], vehid = GetPlayerVehicleID(mechanicid);

        pTemp[playerid][pServePlayer] = INVALID_PLAYER_ID;
        pTemp[playerid][pServeType] = 0;

        if (!IsPlayerLogged(mechanicid))										return SendErrorMessage(playerid, "Size teklif sunan mekanik �evrimi�i de�il.");
        if (PlayerInfo[mechanicid][pJob] != JOB_MECHANIC)						return SendErrorMessage(playerid, "Bu oyuncu mekanik de�il.");
		if (!IsDriver(mechanicid) || !IsATowTruck(vehid))						return SendErrorMessage(playerid, "Mekanik olarak s�r�c� koltu�unda olmal�s�n�z.  ");
		if (!IsDriver(playerid))												return SendErrorMessage(playerid, "S�r�c� koltu�unda olmal�s�n�z. ");
		if (!PlayerNearPlayer(6.0, playerid, mechanicid))						return SendNotNearPlayer(playerid);
        if (VehicleInfo[vehicle][carFaction] != 0 && type != 1 && type != 2)	return SendErrorMessage(playerid, "Bu ara� devlete aittir.");

		new mes[128];

		switch(type)
		{
		    case 1: format(mes, sizeof(mes), "%s model arac�n motor b�l�m�nde i�lem yapmak i�in bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 2: format(mes, sizeof(mes), "%s model arac�n kaportas�nda i�lem yapmak i�in bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 3: format(mes, sizeof(mes), "%s model arac� onarmak i�in bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
		    case 4: format(mes, sizeof(mes), "%s model arac� boyamak i�in bir form onaylar.", VehicleNames[GetVehicleModel(vehicle)-400]);
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

        if (!IsPlayerLogged(userid))									return SendErrorMessage(playerid, "Ev teklifi g�nderen oyuncu �evrimi�i de�il.");
		if (houseid == -1)												return SendErrorMessage(playerid, "Kimse size ev alma teklifi g�ndermedi.");
        if (price < 0 || price > 100000000)								return SendErrorMessage(playerid, "$0 ve $100000000 aras� sat�� tutar� sunabilirsiniz.");
		if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
	    if (IsPlayerOutsideHouse(playerid, houseid) == 0)				return SendErrorMessage(playerid, "Sat�n almak istedi�iniz evin yak�n�nda olmal�s�n�z..");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(playerid, "Bu ev %s 'e ait de�il .", GetNameEx(userid));
		if (GetCash(playerid) < price)									return SendNotCash(playerid);
        if (GetPlayerHouses(playerid) >= GetMaxPlayerHouse(playerid))	return SendErrorMessage(playerid, "Daha fazla ev sat�n alamazs�n�z.");

		HouseInfo[houseid][hOwnerID] = PlayerInfo[playerid][pID];
        format(HouseInfo[houseid][hOwner], MAX_PLAYER_NAME, GetNameEx(playerid));
		GiveCash(playerid, -price);
		GiveCash(userid, price);

        for(new i = 0; i != MAX_GARAGES; i++)
		{
		    if (!GarageInfo[i][garageID] || GarageInfo[i][garageHouse] != HouseInfo[houseid][hID]) continue;

			SendSyntaxMessage(playerid, "Evle birlikte bir garaj�n�zda var. [ID: %i].", i);

			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			format(GarageInfo[i][garageOwnerName], 24, "%s", GetNameEx(playerid));
		
			SQL_SetInteger("garage", "owner", GarageInfo[i][garageOwner], GarageInfo[i][garageID]);
			SQL_SetString("users", "name", GarageInfo[i][garageOwnerName], GarageInfo[i][garageOwner]);
		}

		Save_House(houseid);

		SendSyntaxMessage(playerid, "%s oyuncusundan $%i kar��l���nda bir ev sat�n ald�n�z.", GetNameEx(userid), price);
    	SendSyntaxMessage(userid, "%s  adl� oyuncu sizden $%i kar��l���nda evi sat�n ald�.", GetNameEx(playerid), price);
    	return 1;
	}

	else if (pTemp[playerid][pBizPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pBizPlayer], price = pTemp[playerid][pBizPrice], bizid = pTemp[playerid][pBizID];

        pTemp[playerid][pBizPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pBizPrice] = 0;
		pTemp[playerid][pBizID] = INVALID_PLAYER_ID;

        if (!IsPlayerLogged(userid))									return SendErrorMessage(playerid, "��yeri sat�n alma teklifi g�nderen oyuncu �evrimi�i de�il.");
		if (bizid == -1)												return SendErrorMessage(playerid, "Kimse size bir i�yeri sat�n alma teklifi g�ndermedi. ");
        if (price < 0 || price > 100000000)								return SendErrorMessage(playerid, "$0 ve $100000000 aras� sat�� tutar� sunabilirsiniz.");
		if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[userid][pID])		return SendErrorMessage(playerid, "Bu i�letme %s adl� oyuncuya ait de�il.", GetNameEx(userid));
		if (GetCash(playerid) < price)									return SendNotCash(playerid);
        if (GetPlayerBizes(playerid) >= GetMaxPlayerBiz(playerid))		return SendErrorMessage(playerid, "Daha fazla i�yeri sat�n alamazs�n�z.");

		if (IsPlayerBizOutside(playerid, bizid) == 0 && IsPlayerBizInside(playerid, bizid) == 0) return SendErrorMessage(playerid, "Sat�n almak istedi�iniz i�letmenin yak�n�nda olmal�s�n�z.");
		
		BizInfo[bizid][bizOwnerID] = PlayerInfo[playerid][pID];
		format(BizInfo[bizid][bizOwner], MAX_PLAYER_NAME, "%s", GetName(playerid));

		GiveCash(playerid, -price);
		GiveCash(userid, price);

		for(new i = 0; i != MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageBiz] != BizInfo[bizid][bizID]) continue;

			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			SendSyntaxMessage(playerid, "��yeriniz ile birlikte bir garaj�n�z da var. [ID: %i].", i);

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `garage` SET `owner`=%i WHERE `id`=%i", PlayerInfo[playerid][pID], GarageInfo[i][garageID]);
			mysql_tquery(dbHandle, query);
		}

		RemoveAllWorkers(bizid);
		Save_Business(bizid);

		SendSyntaxMessage(playerid, "%s adl� oyuncudan $%i kar��l���nda bir i�yeri sat�n ald�n�z.", GetNameEx(userid), price);
    	SendSyntaxMessage(userid, "%s adl� oyuncu sizden $%i kar��l���nda bir i�yeri sat�n ald�.", GetNameEx(playerid), price);
    	return 1;
	}

	else if (pTemp[playerid][pRentPlayer] != INVALID_PLAYER_ID)
	{
	    new userid = pTemp[playerid][pRentPlayer], price = pTemp[playerid][pRentPrice];

        pTemp[playerid][pRentPlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pRentPrice] = 0;

		if (!IsPlayerLogged(userid))					return SendErrorMessage(playerid, "Size ev kiras� teklif eden oyuncu �evrimi�i de�il.");
        if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

		new houseid;

		if ((houseid = GetNearInsideHouse(userid)) == -1)				return SendErrorMessage(userid, "Evin i�inde olmal�s�n�z.");
		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[userid][pID])	return SendErrorMessage(userid, "Bu ev size ait de�il.");
        if (GetCash(playerid) < price)									return SendErrorMessage(playerid, "�n �demeniz i�in $%i paran�z yok.", price);

		PlayerInfo[playerid][pRentKey] = HouseInfo[houseid][hID];
		PlayerInfo[playerid][pRentPrice] = price;
		SendSyntaxMessage(playerid, "%s adl� ki�inin evini kiralad�n�z. Her maa� �denecek tutar: $%i.", GetNameWithMask(userid), price);
		SendSyntaxMessage(playerid, "Evden istedi�iniz zaman /evkiraiptal komutunu kullanarak ��kabilirsiniz.");
		SendSyntaxMessage(userid, "%s adl� oyuncu evinizi kiralad�. Her maa�ta gelecek tutar: $%i", GetNameWithMask(playerid), price);

		new query[256];
        format(query, sizeof(query), "UPDATE `users` SET `rent_key`=%i,`rent_price`=%i WHERE `id`=%i", PlayerInfo[playerid][pRentKey], PlayerInfo[playerid][pRentPrice], PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query);

		return 1;
	}

	else if (pTemp[playerid][pInterviewPlayer] != INVALID_PLAYER_ID)
	{
		if (PlayerInfo[playerid][pSettings] & togNews)	return SendErrorMessage(playerid, "�nce SAN'dan gelen mesajlar�n g�r�nt�lenmesini etkinle�tirin. (/tog news).");

		new userid = pTemp[playerid][pInterviewPlayer];

    	pTemp[playerid][pInterviewPlayer] = INVALID_PLAYER_ID;

        if (!IsPlayerLogged(userid))						return SendErrorMessage(playerid, "Size r�portaj teklif eden oyuncu �evrimi�i de�il.");
		if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);

		pTemp[playerid][pInterview] = userid;
		SendSyntaxMessage(playerid, "%s adl� oyuncunun r�portaj teklifini kabul ettiniz.", GetNameWithMask(userid));
    	SendSyntaxMessage(playerid, "Yay�n yapmak i�in normal sohbeti kullan�n. /yayindanayril  komutu ile r�portaj� sonland�rabilirsiniz.");
		SendSyntaxMessage(userid, "%s adl� oyuncu r�portaj yapma teklifinizi kabul etti.", GetNameWithMask(playerid));

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