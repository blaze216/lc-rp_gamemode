this::VehicleUpgrade(playerid, cost, level, color2, upgrade)
{
	new 
		uptime = 1000,
		vehicleid = GetPlayerVehicleID(playerid),
		string[256],
		model = GetVehicleModel(vehicleid)
	;

	if(vehicleid == 0 || vehicleid == -1 || vehicleid == INVALID_PLAYER_ID) vehicleid = pTemp[playerid][pRentveh];
	
	if (!IsValidVehicle(vehicleid) && VehicleInfo[vehicleid][carEngineOn] && !IsPlayerLoggedIn(playerid))
	{
		SendErrorMessage(playerid, "Araç yükseltilirken bir hata oluþtu.");
		return 1;
	}

	if (upgrade == 0) return SendErrorMessage(playerid, "Bir hata oluþtu.");

	new dealer = -1;

	if (upgrade != 13 && upgrade != 12 && upgrade != 1 && upgrade != 7 && (dealer = ModShop_Nearest(playerid)) == -1) 
		return SendErrorMessage(playerid, "Modifiye dükkanýna yakýn olmalýsýn. ");
	if (upgrade == 12 && AZC_Nearest(playerid) == -1) 
		return SendErrorMessage(playerid, "Benzinlik istasyonuna yakýn olmalýsýnýz.");
	if (upgrade == 13 && PAS_Nearest(playerid) == -1)
		return SendErrorMessage(playerid, "Araç tamircisine yakýn olmalýsýnz. "); 
	
	if (upgrade == 1)
	{
	    if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		RespawnVehicle(vehicleid);
		return SendSyntaxMessage(playerid, "%s aracýnýz baþarýyla park bölgesine çekildi.", VehicleNames[model-400]);
	}
	else if (upgrade == 2)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "%i seviye araç kilidi $%i karþýlýðýnda aracýnýza takýldý.", level, cost);
        UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carLock] = level;
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 3)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "%i seviye araç alarmý $%i karþýlýðýnda aracýnýza takýldý.", level, cost);
        UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carAlarm] = level;
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 4)
	{
	    if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "%i seviye araç immobilizer $%i karþýlýðýnda aracýnýza takýldý.", level, cost);
        UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carImmob] = level;
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 5)
	{
        if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "%i seviye araç sigortasý $%i karþýlýðýnda aracýnýza yapýldý.", level, cost);
        UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carInsurance] = level;
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 6)
	{
	    if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "%i miktarýnda araç zýrhý $%i karþýlýðýnda aracýnýza eklendi.", level, cost);
        UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carArmour] += float(level);

		if (VehicleInfo[vehicleid][carArmour] > 250.0)	VehicleInfo[vehicleid][carArmour] = 250.0;
		
		SetVehicleHealth(vehicleid, GetVehicleMaxHealth(GetVehicleModel(vehicleid)) + VehicleInfo[vehicleid][carArmour]);
		UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, 0);
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 7)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		format(VehicleInfo[vehicleid][carPlate], 24, "%s", GetVehicleNumber());
		VehicleInfo[vehicleid][carRegistered] = 1;
		SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][carPlate]);
		RespawnVehicle(vehicleid, 1);
		GiveCash(playerid, -cost);
		SendSyntaxMessage(playerid, "Araç $%i karþýlýðýnda DMV sistemine kayýt ettirildi. Yeni plakanýz: %s", cost, VehicleInfo[vehicleid][carPlate]);
		UnFreezePlayer(playerid);

		new mes[128];
		format(mes, sizeof(mes), "~w~Aracin yeni plakasi~n~~y~%s oldu ve $%i odedin.", VehicleInfo[vehicleid][carPlate], cost);
		JobMessage(playerid, mes, 6);

		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
        return 1;
	}
	else if (upgrade == 8)
	{
	    if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		format(VehicleInfo[vehicleid][carPlate], 24, "_");
		VehicleInfo[vehicleid][carRegistered] = 0;
		SetVehicleNumberPlate(vehicleid, "_");
		RespawnVehicle(vehicleid, 1);
		Save_Car(vehicleid);

		SendSyntaxMessage(playerid, "Aracýn kaydý silindi. ");
		JobMessage(playerid, "~w~Arac artik kaytili degil.", 2);
		UnFreezePlayer(playerid);
		return 1;
	}
	else if (upgrade == 9)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);
			
		format(string, sizeof(string), "~w~Motor degistirildi (100.00) ve $%i odedin.", cost);
		JobMessage(playerid, string, 6);
        SendSyntaxMessage(playerid, "Aracýn motoru $%i karþýlýðýnda deðiþtirildi.", cost);
		GiveCash(playerid, -cost);
		UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carEngine] = 100.00;
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 10)
	{
	    if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		SendSyntaxMessage(playerid, "$%i karþýlýðýnda aracý boyadýnýz.", cost);
		GiveCash(playerid, -cost);
		UnFreezePlayer(playerid);
		ChangeVehicleColor(vehicleid, level, color2);
		VehicleInfo[vehicleid][carColor1] = level;
		VehicleInfo[vehicleid][carColor2] = color2;
		Save_Car(vehicleid);
		GiveBizCash(dealer, cost / 100 * 80);
	    return 1;
	}
	else if (upgrade == 11)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);

		format(string, sizeof(string), "~w~Aku degistirildi (100.00) ve $%i odedin.", cost);
		JobMessage(playerid, string, 6);
        SendSyntaxMessage(playerid, "Aracýn aküsü deðiþtirildi. Ücret: $%i.", cost);
		GiveCash(playerid, -cost);
		UnFreezePlayer(playerid);
		VehicleInfo[vehicleid][carBattery] = 100.00;
		GiveBizCash(dealer, cost / 100 * 80);
		return 1;
	}
	else if (upgrade == 12)
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);
		/*GiveCash(playerid, -cost);

		new Float:toFill = GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) - VehicleInfo[vehicleid][carFuel];
		VehicleInfo[vehicleid][carFuel] += toFill;

		if (BizInfo[GetPVarInt(playerid, #bizid)][bizOwnerID] != 0)
		{
			if (BizInfo[GetPVarInt(playerid, #bizid)][bizProduct] > 10) BizInfo[GetPVarInt(playerid, #bizid)][bizProduct]--;
			GiveBizCash(GetPVarInt(playerid, #bizid), cost);
		}

		format(string, sizeof(string), "~w~Âû óñïåøíî çàïðàâèëèñü çà ~h~~g~$%i.", cost);
		InfoMSG(playerid, string, 5);
		SM2(playerid,"Âàøå òðàíñïîðòíîå ñðåäñòâî áûëî çàïðàâëåíî çà $%i.", cost);*/
		
		return 1;
	}
	else if (upgrade == 13) //all
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);
		GiveCash(playerid, -cost);

		FixVehicle(vehicleid);

		if (BizInfo[GetPVarInt(playerid, #bizid)][bizOwnerID] != 0)
		{
			if (BizInfo[GetPVarInt(playerid, #bizid)][bizProduct] > 10) BizInfo[GetPVarInt(playerid, #bizid)][bizProduct]--;
			GiveBizCash(GetPVarInt(playerid, #bizid), cost);
		}

		format(string, sizeof(string), "~w~Basariyla araci\ntamir ettiniz\nucret: ~h~~g~$%i.", cost);
		InfoMSG(playerid, string, 5);
		SM2(playerid,"Aracý $%i karþýlýðýnda tamir ettirdin.", cost);		
		
		return 1;
	}
	else if (upgrade == 14) //list
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);
		GiveCash(playerid, -cost);

		UpdateVehicleDamageStatus(vehicleid, pTemp[playerid][pListed][0], pTemp[playerid][pListed][1], pTemp[playerid][pListed][2], pTemp[playerid][pListed][3]);
		for(new i; i < 4; i++) pTemp[playerid][pListed][i] = 0;

		if (BizInfo[GetPVarInt(playerid, #bizid)][bizOwnerID] != 0)
		{
			if (BizInfo[GetPVarInt(playerid, #bizid)][bizProduct] > 10) BizInfo[GetPVarInt(playerid, #bizid)][bizProduct]--;
			GiveBizCash(GetPVarInt(playerid, #bizid), cost);
		}

		format(string, sizeof(string), "~w~Arac tamir eidldi\nUcret: ~h~~g~$%i.", cost);
		InfoMSG(playerid, string, 5);
		SM2(playerid,"Ýþlemi $%i karþýlýðýnda bitirdiniz.", cost);		
		
		return 1;
	}
	else if (upgrade == 15)//HP
	{
		if (GetCash(playerid) < cost)	return SendNotCash(playerid);
		GiveCash(playerid, -cost);
		
		SetVehicleHealth(vehicleid, GetVehicleMaxHealth(GetVehicleModel(vehicleid)));

		if (BizInfo[GetPVarInt(playerid, #bizid)][bizOwnerID] != 0)
		{
			if (BizInfo[GetPVarInt(playerid, #bizid)][bizProduct] > 10) BizInfo[GetPVarInt(playerid, #bizid)][bizProduct]--;
			GiveBizCash(GetPVarInt(playerid, #bizid), cost);
		}

		format(string, sizeof(string), "~w~Arac tamir edildi\nUcret: ~h~~g~$%i.", cost);
		InfoMSG(playerid, string, 5);
		SM2(playerid,"Ýþlemi $%i karþýlýðýnda bitirdiniz.", cost);		
		
		return 1;
	}
	return 1;
}

SendMechanicHelp(playerid, location[])
{
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || PlayerInfo[i][pJob] != JOB_MECHANIC) continue;

       	SendClientMessage(i, COLOR_SERVER2, "|_________Acil tamirci çaðrýsý_________|");
		if (pTemp[playerid][pPayphone] == -1) 	SendClientMessageEx(i, COLOR_WHITE, "Arayan: %s No: %i", GetNameEx(playerid), PlayerInfo[playerid][pNumber]);
		else 									SendClientMessageEx(i, COLOR_WHITE, "Arayan: Ankesörlü Telefon, No: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
		SendClientMessageEx(i, COLOR_WHITE, "Lokasyon: %s", location);
 	}
	return 1;
}

Mechanic_OnPlayerExitVehicle(playerid)
{
    if (RepairService[playerid] != 0)
	{
		ShowJobMessage(playerid, "~h~~p~ARACI BOYAMAYA BASLADINIZ");
		AC_GivePlayerWeapon(playerid, 41, 999);
	}
    return 1;
}

StartVehicleUpgrade(playerid, vehicleid, type, cost, level = 0, color2 = 0)
{
	if (type != 12 && type != 13 && type != 14 && VehicleInfo[vehicleid][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu araç size ait deðil. ");
	VehicleUpgrade(playerid, cost, level, color2, type);
	return 1;
}