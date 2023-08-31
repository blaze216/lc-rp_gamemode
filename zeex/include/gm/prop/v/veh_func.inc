this::LoadDynamicCars()
{
	new rows = cache_num_rows(), time = GetTickCount(), total;

    new sqlid, model, color1, color2, faction, Float:x, Float:y, Float:z, Float:a, type, plate[24], vw, interior, vehicle;

	if (!rows)
	{
	    print("[Cars] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", sqlid);
		cache_get_value_int(i, "model", model);
		cache_get_value_float(i, "x", x);
		cache_get_value_float(i, "y", y);
		cache_get_value_float(i, "z", z);
		cache_get_value_float(i, "fa", a);
		cache_get_value_int(i, "color1", color1);
		cache_get_value_int(i, "color2", color2);
		cache_get_value_int(i, "type", type);
		cache_get_value_int(i, "faction", faction);
		cache_get_value(i, "plate", plate, 24);
		cache_get_value_int(i, "int", interior);
		cache_get_value_int(i, "vw", vw);

		vehicle = CreateFactionVehicle(false, model, x, y, z, a, color1, color2, type, faction, plate, vw, interior, sqlid);

		VehicleInfo[vehicle][carOwnerPlayer] = INVALID_VEHICLE_ID;

		SetVehicleVirtualWorldEx(i, vw);
		SetVehicleInteriorEx(i, interior);

		total++;
	}
    printf("[Cars] Satir - %i. Yuklenen - %i. Yuklenme Zamani: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

this::OnVehicleInsert(vehicleid)
{
    VehicleInfo[vehicleid][carID]= cache_insert_id();
	return 1;
}

this::BuyVehicleForPlayer(playerid)
{
    new Float:x, Float:y, Float:z, Float:fa, model = GetPVarInt(playerid, "BuyingVehicleModel"), plate[24], dealer = -1;

	if (IsABoatModel(model) && (dealer = DealerShip_Nearest(playerid, BIZ_BOATSALON)) == -1)							return SendErrorMessage(playerid, "Su araç galerisinin yakýnýnda olmalýsýnýz.");
    if (IsAPlaneModel(model) && (dealer = DealerShip_Nearest(playerid, BIZ_FLYSALON)) == -1)							return SendErrorMessage(playerid, "Hava aracý galerisinin yakýnýnda olmalýsýnýz.");
	if (!IsABoatModel(model) && !IsAPlaneModel(model) && (dealer = DealerShip_Nearest(playerid, BIZ_AUTOSALON)) == -1)	return SendErrorMessage(playerid, "Araba galerisine yakýn olmalýsýnýz.");
	if (cache_num_rows() >= GetMaxPlayerCars(playerid))																	return SendErrorMessage(playerid,"Maksimum araç sayýsýna ulaþtýnýz daha fazla araç satýn alamazsýnýz.");

    new registerveh = price_reg[GetPVarInt(playerid, "BuyingVehicleRegister")], 
		alarmveh = price_alarm[GetPVarInt(playerid, "BuyingVehicleAlarm")], 
		lockveh = price_lock[GetPVarInt(playerid, "BuyingVehicleLock")],
		immobveh = price_immob[GetPVarInt(playerid, "BuyingVehicleImmob")], 
		insuranceveh = GetInsurancePrice(GetPVarInt(playerid, "BuyingVehicleModel")) * GetPVarInt(playerid, "BuyingVehicleInsurance"),
		xmradioveh = price_radio[GetPVarInt(playerid, "BuyingVehicleRadio")], 
		gpsveh = price_gps[GetPVarInt(playerid, "BuyingVehicleGps")], 
		color1 = GetPVarInt(playerid, #veh_color1),
		color2 = GetPVarInt(playerid, #veh_color2);

	if (!PlayerInfo[playerid][pPremium] && IsDonateVehicle(model))		 return SendErrorMessage(playerid, "Bu aracý yalnýzca premium hesabý olan bir oyuncu satýn alabilir.");
	if (PlayerInfo[playerid][pPremium] < 1 && IsBronzeVehicle(model))	 return SendErrorMessage(playerid, "Bu aracý satýn almak için bronz premium hesabýnýz veya daha yüksek bir hesabýnýzýn olmasý gerekir.");
	if (PlayerInfo[playerid][pPremium] < 2 && IsSilverVehicle(model))	 return SendErrorMessage(playerid, "Bu aracý satýn almak için gümüþ premium hesabýnýz veya daha yüksek bir hesabýnýzýn olmasý gerekir");
	if (PlayerInfo[playerid][pPremium] < 3 && IsGoldVehicle(model))		 return SendErrorMessage(playerid, "Bu aracý satýn almak için altýn premium hesabýnýzýn olmasý gerekir.");
	if (BizInfo[dealer][bizOwnerID] != 0 && !BizInfo[dealer][bizProduct]) return SendErrorMessage(playerid, "Bu galeride yeterince araç kalmamýþ.");
	    
	new price = GetVehiclePrice(model)+registerveh+alarmveh+lockveh+immobveh+insuranceveh+xmradioveh+gpsveh;

	if (GetCash(playerid) < price)	return SendNotCash(playerid);

	SendSyntaxMessage(playerid, "%s model aracý $%i ödeyerek satýn aldýnýz.", VehicleNames[model-400], price);
	SendHelpMessage(playerid, "Araç komutlarýný öðrenmek için /(a)rac komutunu kullanabilirsiniz.");

	new money = PlayerInfo[playerid][pCash];
	
	GiveCash(playerid, -price);
	
	if (BizInfo[dealer][bizOwnerID] != 0)
	{
	    BizInfo[dealer][bizProduct]--;
		GiveBizCash(dealer, price);
	}
	
    new query[256];
	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] bought a car %s(Model: %i) for -- $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), 
	VehicleNames[model-400], model, price);
    insert_log(query, VEHICLE_LOG, 1, PlayerInfo[playerid][pAccID]);

	if (IsABoatModel(model)) {
		if (!BizInfo[dealer][bizSpawn][0] && !BizInfo[dealer][bizSpawn][1] && !BizInfo[dealer][bizSpawn][2]) {
			x = 114.9191;
			y = -1902.8209;
			z = -0.6980;
			fa = 0.0;
		} else {
			x = BizInfo[dealer][bizSpawn][0];
			y = BizInfo[dealer][bizSpawn][1]; 
			z = BizInfo[dealer][bizSpawn][2]; 
			fa = BizInfo[dealer][bizSpawn][3];
		}
	} else if (IsAPlaneModel(model)) {
		if (!BizInfo[dealer][bizSpawn][0] && !BizInfo[dealer][bizSpawn][1] && !BizInfo[dealer][bizSpawn][2]) {
			x = 1943.5498;
			y = -2397.6553;
			z = 14.70;
			fa = 0.0;
		} else {
			x = BizInfo[dealer][bizSpawn][0];
			y = BizInfo[dealer][bizSpawn][1]; 
			z = BizInfo[dealer][bizSpawn][2]; 
			fa = BizInfo[dealer][bizSpawn][3];
		}
	} else {
		if (!BizInfo[dealer][bizSpawn][0] && !BizInfo[dealer][bizSpawn][1] && !BizInfo[dealer][bizSpawn][2]) {
			x = 531.1557;
			y = -1285.5590;
			z = 16.9693;
			fa = 305.9785;
		} else {
			x = BizInfo[dealer][bizSpawn][0];
			y = BizInfo[dealer][bizSpawn][1]; 
			z = BizInfo[dealer][bizSpawn][2]; 
			fa = BizInfo[dealer][bizSpawn][3];
		}
	}							
	

	if (!GetPVarInt(playerid, "BuyingVehicleRegister"))	format(plate, 24, "_");
	else												format(plate, 24, "%s", GetVehicleNumber());

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `cars` (date,model,color1,color2,x,y,z,fa,plate,owner,registered,alarm,locks,immob,insurances,radio,gps,health,fuel) VALUES ('%s',%i,%i,%i,%.1f,%.1f,%.1f,%.1f,'%s',%i,%i,%i,%i,%i,%i,%i,%i,%.1f,%.1f)",
	GetFullDate(), model, color1, color2, x, y, z, fa, plate, PlayerInfo[playerid][pID], GetPVarInt(playerid, "BuyingVehicleRegister"), GetPVarInt(playerid, "BuyingVehicleAlarm"), GetPVarInt(playerid, "BuyingVehicleLock"),
	GetPVarInt(playerid, "BuyingVehicleImmob"), GetPVarInt(playerid, "BuyingVehicleInsurance"), GetPVarInt(playerid, "BuyingVehicleRadio"), GetPVarInt(playerid, "BuyingVehicleGps"), GetVehicleMaxHealth(model), GetVehicleFuelCapacity(model)/2);
	mysql_tquery(dbHandle, query);
	return 1;
}

this::BuyVehicleAtPlayer(playerid)
{
	if (pTemp[playerid][pCarPlayer] == INVALID_PLAYER_ID)	return 1;

	new userid = pTemp[playerid][pCarPlayer], price = pTemp[playerid][pCarPrice], vehicle = PlayerInfo[userid][pCarKey];

    pTemp[playerid][pCarPlayer] = INVALID_PLAYER_ID;
    pTemp[playerid][pCarPrice] = 0;

    if (cache_num_rows() >= GetMaxPlayerCars(playerid))									return SendErrorMessage(playerid, "Maksimum araç sayýsýna ulaþtýnýz, daha fazla araç satýn alamazsýnýz.");
    if (!IsPlayerLogged(userid))														return SendNotConnected(playerid);
	if (!IsValidVehicle(vehicle))														return SendErrorMessage(playerid, "Kiþinin aracý park bölgesinde.");
	if (!IsPlayerInVehicle(userid, vehicle))											return SendNotInVehicle(userid);
	if (IsADonateModel(GetVehicleModel(vehicle)))										return SendErrorMessage(userid, "Premium yoluyla alýnan araçlarý satamazsýnýz..");
    if (PlayerInfo[userid][pPremium] < 2 && VehicleInfo[vehicle][carComponent][5] != 0)	return SendErrorMessage(playerid, "Bu oyuncunun nitroya eriþimi yok.");
	if (userid == playerid)																return 1;
	if (!IsABicycle(vehicle) && !VehicleInfo[vehicle][carRegistered])					return SendErrorMessage(playerid, "Bu araç sisteme kayýtlý deðil. ");
	if (!PlayerNearPlayer(3.0, playerid, userid))										return SendNotNearPlayer(playerid);
	if (IsValidVehicle(PlayerInfo[playerid][pCarKey]))									return SendErrorMessage(playerid, "Aracýnýz zaten spawnlanmýþ!");

    if (GetCash(playerid) < price)
    {
        SendErrorMessage(playerid, "Bu aracý alacak kadar yeterli paranýz yok!");
		SendErrorMessage(userid, "Satýþ teklifi gönderdiðiniz oyuncunun yeterli parasý olmadýðý için aracý oyuncuya satamazsýnýz.");
		return 1;
    }

	new money1 = PlayerInfo[userid][pCash], money2 = PlayerInfo[playerid][pCash];

	SendSyntaxMessage(playerid, "%s model aracý %s adlý kiþiden $%i karþýlýðýnda satýn aldýnýz.", VehicleNames[GetVehicleModel(vehicle)-400],  GetNameWithMask(userid), price);
	SendSyntaxMessage(userid, "%s model aracýnýzý %s adlý kiþiye $%i karþýlýðýnda sattýnýz.", VehicleNames[GetVehicleModel(vehicle)-400], GetNameWithMask(playerid), price);

	GiveCash(userid, price);
	GiveCash(playerid, -price);
	VehicleInfo[vehicle][carOwnerID] = PlayerInfo[playerid][pID];
	VehicleInfo[vehicle][carOwnerPlayer] = playerid;
	PlayerInfo[playerid][pCarKey] = vehicle;
	PlayerInfo[userid][pCarKey] = 0;
	format(VehicleInfo[vehicle][carOwner], 24, GetNameEx(playerid));

	new query[256];
	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] bought %s(Model: %i) from player %s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] for -- $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money1, GetCash(playerid), VehicleNames[GetVehicleModel(vehicle)-400], GetVehicleModel(vehicle), GetName(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid), 
	money2, GetCash(userid), price);
    insert_log(query, VEHICLE_LOG, 2, PlayerInfo[playerid][pAccID]);

	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] sold %s(Model: %i) to player %s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] for -- $%i",
	GetName(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid), money2, GetCash(userid), VehicleNames[GetVehicleModel(vehicle)-400], GetVehicleModel(vehicle), GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid),
	money1, GetCash(playerid), price);
 	insert_log(query, VEHICLE_LOG, 4, PlayerInfo[playerid][pAccID]);

	mysql_format(dbHandle,query, sizeof(query), "UPDATE `cars` SET `owner` = %i WHERE `id` = %i", VehicleInfo[vehicle][carOwnerID], VehicleInfo[vehicle][carID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

this::ShowListVeh(playerid)
{
	if (!cache_num_rows())	return SendErrorMessage(playerid, "Araç sahibi deðilsiniz.");
	
	new 
		dlgmes[8*288] = "#\tPlaka\tAraç\tDurum\n",
		model,
		impound,
		jacking,
		id,
		plate[32],
		status[128]
	;
	
	for(new i; i < cache_num_rows(); i++)
	{
		cache_get_value_int(i, "model", model);
		cache_get_value_int(i, "impound", impound);
		cache_get_value_int(i, "jacking", jacking);
		cache_get_value_int(i, "id", id);

		cache_get_value(i, "plate", plate, 24);
		if (isempty(plate))	format(plate, sizeof(plate), "-");

		if (impound == 1) format(status, sizeof(status), ""EMBED_RED"Haciz edilmiþ(impound alanýnda){FFFFFF}");
		else {
			if (jacking == 1) format(status, sizeof(status), ""EMBED_RED"Çalýnmýþ(bilgi için týklayýn){FFFFFF}");
			else {
				if (IsValidVehicle(PlayerInfo[playerid][pCarKey]) && VehicleInfo[PlayerInfo[playerid][pCarKey]][carID] == id) {
					pTemp[playerid][MyCarSpawn][i] = 1;
					format(status, sizeof(status), "{FFFF00}Spawnlanmýþ{FFFFFF} (ID: %d)", PlayerInfo[playerid][pCarKey]);
				} else {
					pTemp[playerid][MyCarSpawn][i] = 0;
					format(status, sizeof(status), "Spawnlanmamýþ");
				}		
			}
		}

		pTemp[playerid][MyCars][i] = id;
		
		format(dlgmes, sizeof(dlgmes), "%s{FFFFFF}%i\t%s\t%s\t%s\n", dlgmes, i+1, plate, VehicleNames[model-400], status);
	}

	Dialog_Show(playerid, MyCars, DIALOG_STYLE_TABLIST_HEADERS, "Araçlarým", dlgmes, "Seç", "Ýptal");
	return 1;
}

this::ShowCarsForPlayer(playerid, targetid)
{
	if (!cache_num_rows())	return SendErrorMessage(playerid, "Araç sahibi deðilsiniz.");

	new hour, minute, second, model, _alarm, lock, immob, insurance, destroyed, id, plate[24], vehicle = PlayerInfo[targetid][pCarKey];
	
	gettime(hour, minute, second);

	SendClientMessageEx(playerid, COLOR_SERVER2, "____________________[Araç Listesi %s, %02d:%02d:%02d]____________________", GetNameEx(targetid), hour, minute, second);

	new count = 0;

	for(new i; i < cache_num_rows(); i++)
	{
	    cache_get_value_int(i, "model", model);
		cache_get_value_int(i, "alarm", _alarm);
	    cache_get_value_int(i, "locks", lock);
	    cache_get_value_int(i, "immob", immob);
	    cache_get_value_int(i, "insurances", insurance);
	    cache_get_value_int(i, "destroys", destroyed);

		cache_get_value(i, "plate", plate, 24);
        cache_get_value_int(i, "id", id);

	    if (VehicleInfo[vehicle][carID] == id)
	    {
			if (destroyed)	SendClientMessageEx(playerid, COLOUR_ALTO, "Slot %i: %s [%s] [ID: %i], Alarm [%i], Kilit [%i], Immobilizer [%i], Sigorta [%i], Çalýnma Sayýsý [%i / 5]", i+1, VehicleNames[model-400], plate, vehicle, VehicleInfo[vehicle][carAlarm], VehicleInfo[vehicle][carLock], VehicleInfo[vehicle][carImmob], VehicleInfo[vehicle][carInsurance], VehicleInfo[vehicle][carDestroyed]);
			else			SendClientMessageEx(playerid, COLOUR_ALTO, "Slot %i: %s [%s] [ID: %i], Alarm [%i], Kilit [%i], Immobilizer [%i], Sigorta [%i]", i+1, VehicleNames[model-400], plate, vehicle, VehicleInfo[vehicle][carAlarm], VehicleInfo[vehicle][carLock], VehicleInfo[vehicle][carImmob], VehicleInfo[vehicle][carInsurance]);
		}
		else
		{
		    if (destroyed)	SendClientMessageEx(playerid, COLOUR_ALTO, "Slot %i: %s [%s], Alarm [%i], Kilit [%i], Immobilizer [%i], Sigorta [%i], Çalýnma Sayýsý [%i / 5]", i+1, VehicleNames[model-400], plate, _alarm, lock, immob, insurance, destroyed);
			else			SendClientMessageEx(playerid, COLOUR_ALTO, "Slot %i: %s [%s], Alarm [%i], Kilit [%i], Immobilizer [%i], Sigorta [%i]", i+1, VehicleNames[model-400], plate, _alarm, lock, immob, insurance);
		}
		count++;
	}

	if (count > 3) SendClientMessageEx(playerid, COLOR_SERVER2, "____________________[Araç Listesi %s, %02d:%02d:%02d]____________________", GetNameEx(targetid), hour, minute, second);
	
	return 1;
}

this::OnPlayerSpawnVehicle(playerid)
{
	if (!cache_num_rows())
		return SendErrorMessage(playerid, "[ID: %i] slotunda aracýnýz yok.", GetPVarInt(playerid, #spawnveh_id));

	new jacking;
	cache_get_value_int(0, "jacking", jacking);	

	if (jacking) {
		new mes[300];
		new id, model;
		cache_get_value_int(0, "id", id);
		cache_get_value_int(0, "model", model);

		SetPVarInt(playerid, #RansomVehID, id);
		SetPVarInt(playerid, #RansomVehModel, model);

		format(mes, sizeof(mes), "%s model aracýnýzý yarý fiyatýna\nhurdalýktan çýkarmak ister misiniz?\n\nÖdemeniz gereken miktar: $%i\n\n'Ýleri' butonuna basarak devam edebilirsiniz: araç sizin veya yok olacak\n{FF6347}KABUL ETMEZSENÝZ ARAÇ SONSUZA DEK SÝLÝNECEK!", VehicleNames[model-400], floatround(GetVehiclePrice(model)*0.5));
		return Dialog_Show(playerid, RansomVehicle, DIALOG_STYLE_MSGBOX, "Araç Satýn Alýmý", mes, "Ýleri", "Ýptal");
	}
		
	new vehicle, Float:hp, panels, doorss, lightss, tires;

	vehicle = CreateVehicle(400, 0.0, 0.0, 0.0, 0.0, 0, 0, -1);

	if (vehicle == INVALID_VEHICLE_ID) return SendErrorMessage(playerid, "Araç spawnlanamadý.");

	cache_get_value_int(0, "id", VehicleInfo[vehicle][carID]);
	cache_get_value_int(0, "model", VehicleInfo[vehicle][carModel]);	
	cache_get_value_int(0, "color1", VehicleInfo[vehicle][carColor1]);
	cache_get_value_int(0, "color2", VehicleInfo[vehicle][carColor2]);
	cache_get_value_float(0, "x", VehicleInfo[vehicle][carParkX]);
	cache_get_value_float(0, "y", VehicleInfo[vehicle][carParkY]);
	cache_get_value_float(0, "z", VehicleInfo[vehicle][carParkZ]);
	cache_get_value_float(0, "fa", VehicleInfo[vehicle][carParkA]);
	
	cache_get_value(0, "plate", VehicleInfo[vehicle][carPlate], 24);

	cache_get_value_int(0, "wanted", VehicleInfo[vehicle][carWanted]);

	cache_get_value_int(0, "owner", VehicleInfo[vehicle][carOwnerID]);
	cache_get_value_float(0, "armour", VehicleInfo[vehicle][carArmour]);
	cache_get_value_int(0, "alarm", VehicleInfo[vehicle][carAlarm]);
	cache_get_value_int(0, "locks", VehicleInfo[vehicle][carLock]);
	cache_get_value_int(0, "immob", VehicleInfo[vehicle][carImmob]);
	cache_get_value_int(0, "insurances", VehicleInfo[vehicle][carInsurance]);
	cache_get_value_int(0, "destroys", VehicleInfo[vehicle][carDestroyed]);
	cache_get_value_int(0, "impound", VehicleInfo[vehicle][Impounded]);
	cache_get_value_int(0, "gps", VehicleInfo[vehicle][carGps]);
	cache_get_value_float(0, "fuel", VehicleInfo[vehicle][carFuel]);
	cache_get_value_int(0, "registered", VehicleInfo[vehicle][carRegistered]);
	cache_get_value_float(0, "battery", VehicleInfo[vehicle][carBattery]);
	cache_get_value_float(0, "engine", VehicleInfo[vehicle][carEngine]);
	VehicleInfo[vehicle][carType]			= 0;

	for(new i = 0; i < 14; i++)
	{
		new field_name[16];

		format(field_name, sizeof(field_name), "comp%i", i);
		cache_get_value_name_int(0, field_name, VehicleInfo[vehicle][carComponent][i]);

		if (i > 9) continue;

		format(field_name, sizeof(field_name), "attach%i_pos0", i);
	    cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachPosX][i]);
		format(field_name, sizeof(field_name), "attach%i_pos1", i);
		cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachPosY][i]);
		format(field_name, sizeof(field_name), "attach%i_pos2", i);
		cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachPosZ][i]);
		format(field_name, sizeof(field_name), "attach%i_rot0", i);
		cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachRotX][i]);
		format(field_name, sizeof(field_name), "attach%i_rot1", i);
		cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachRotY][i]);
		format(field_name, sizeof(field_name), "attach%i_rot2", i);
		cache_get_value_name_float(0, field_name, VehicleInfo[vehicle][carAttachRotZ][i]);
	}

	cache_get_value_int(0, "paintjob", VehicleInfo[vehicle][carPaintJob]);
	cache_get_value_int(0, "radio", VehicleInfo[vehicle][carRadio]);
	cache_get_value_int(0, "comps", VehicleInfo[vehicle][carComps]);
	cache_get_value_float(0, "health", hp);
	cache_get_value_int(0, "panels", panels);
	cache_get_value_int(0, "doors", doorss);
	cache_get_value_int(0, "lights", lightss);
	cache_get_value_int(0, "tires", tires);
	cache_get_value_float(0, "milliage", VehicleInfo[vehicle][carMilliage]);
	cache_get_value_int(0, "hidednum", VehicleInfo[vehicle][carHidedPlate]);
	cache_get_value_int(0, "fakenum", VehicleInfo[vehicle][carFakePlate]);

	cache_get_value(0, "fakenum_str", VehicleInfo[vehicle][carFakePlateS], 24);

	new model;
	cache_get_value_int(0, "model", model);

    VehicleInfo[vehicle][carDriver] 			= INVALID_PLAYER_ID;
	format(VehicleInfo[vehicle][carOwner], 24, GetNameEx(playerid));
	format(VehicleInfo[vehicle][carPlate], 24, "%s", VehicleInfo[vehicle][carPlate]);

/*
	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `inventory` WHERE `carid`=%i", VehicleInfo[vehicle][carID]);
	mysql_tquery(dbHandle, query, "C_LoadInventory", "i", vehicle);

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `inventory` WHERE `trunkid`=%i", VehicleInfo[vehicle][carID]);
	mysql_tquery(dbHandle, query, "T_LoadInventory", "i", vehicle);*/


	PlayerInfo[playerid][pCarKey] = vehicle;
	VehicleInfo[vehicle][carOwnerPlayer] = playerid;

	DestroyVehicle(vehicle);
	
	vehicle = CreateVehicle(VehicleInfo[vehicle][carModel], VehicleInfo[vehicle][carParkX], VehicleInfo[vehicle][carParkY], VehicleInfo[vehicle][carParkZ], VehicleInfo[vehicle][carParkA], VehicleInfo[vehicle][carColor1], VehicleInfo[vehicle][carColor2], -1);

	if (VehicleInfo[vehicle][carFakePlate])
	{
		SetVehicleNumberPlate(vehicle, VehicleInfo[vehicle][carFakePlateS]);
	}
	else
	{
		SetVehicleNumberPlate(vehicle, VehicleInfo[vehicle][carPlate]);
	}

	LoadComp(vehicle);

    if (VehicleInfo[vehicle][carInsurance] > 1)	UpdateVehicleDamageStatus(vehicle, 0, 0, 0, 0);
	else										UpdateVehicleDamageStatus(vehicle, panels, doorss, lightss, tires);

	if (VehicleInfo[vehicle][carInsurance] != 0)	SetVehicleHealth(vehicle, GetVehicleMaxHealth(GetVehicleModel(vehicle)) + VehicleInfo[vehicle][carArmour]);
	
	else
	{
	    if (hp < 390.0)		SetVehicleHealth(vehicle, 500.0);
	    else if (hp > 750.0)	SetVehicleHealth(vehicle, 750.0);
		else				SetVehicleHealth(vehicle, hp);
	}
	
 	ToggleVehicleLock(vehicle, false);
	SendClientMessageEx(playerid, COLOR_SERVER2, "Araç:{FFFFFF} %s (ID: %i) model aracýnýz son park yerine çýkartýlmýþtýr. ", VehicleNames[model-400], vehicle);

	SendClientMessageEx(playerid, COLOR_SERVER2, "Araç:{FFFFFF} Motor durumu: [%.2f], Akü durumu: [%.2f], Çalýnma sayýsý: [%d]", 
		VehicleInfo[vehicle][carEngine], 
		VehicleInfo[vehicle][carBattery], 
		VehicleInfo[vehicle][carDestroyed]);

	new count = CountVehicleTickets(vehicle);
	if (count)	SendWarningMessage(playerid, "Aracýnýzýn %i adet ödenmemiþ cezasý var.", count);
	
	if (VehicleInfo[vehicle][Impounded]) SendWarningMessage(playerid, "Arabanýza el konuldu ve haciz durumunda. (/hacizdencikar) komutunu kullanabilirsiniz.");
	//if (VehicleInfo[vehicleid][eVehicleStolen]) SendClientMessage(playerid, COLOR_YELLOWEX, "Your vehicle is stolen.");

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, VehicleInfo[vehicle][carParkX], VehicleInfo[vehicle][carParkY], VehicleInfo[vehicle][carParkZ])) {
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "[BÝLGÝ]{FFFFFF} Aracý almak için checkpointe gidiniz.");
		Waypoint_Set(playerid, VehicleInfo[vehicle][carParkX],VehicleInfo[vehicle][carParkY],VehicleInfo[vehicle][carParkZ]);
	}
	
	for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
	{
		if (VehicleInfo[vehicle][carAttachObj][i])
		{
			VehicleInfo[vehicle][carAttach][i] = CreateDynamicObject(VehicleInfo[vehicle][carAttachObj][i], VehicleInfo[vehicle][carAttachPosX][i],VehicleInfo[vehicle][carAttachPosY][i],VehicleInfo[vehicle][carAttachPosZ][i],VehicleInfo[vehicle][carAttachRotX][i],VehicleInfo[vehicle][carAttachRotY][i],VehicleInfo[vehicle][carAttachRotZ][i]);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carAttach][i], vehicle, VehicleInfo[vehicle][carAttachPosX][i],VehicleInfo[vehicle][carAttachPosY][i],VehicleInfo[vehicle][carAttachPosZ][i],VehicleInfo[vehicle][carAttachRotX][i],VehicleInfo[vehicle][carAttachRotY][i],VehicleInfo[vehicle][carAttachRotZ][i]);
		}
		else 
		{
			VehicleInfo[vehicle][carAttach][i] = INVALID_OBJECT_ID;
		}
	}
	
	CancelSelectTextDraw(playerid);
	DeletePVar(playerid, #spawnveh_id);

	VehicleLight(vehicle, false);
	VehicleTrunk(vehicle, false);

	PlayerTextDrawHide(playerid, SpawnVeh_Model[playerid]);
	PlayerTextDrawHide(playerid, SpawnVeh_Box[playerid]);
	for(new i = 0; i < 2; i++) PlayerTextDrawHide(playerid, SpawnVeh_Arrows[playerid][i]);
	for(new e = 0; e < 3; e++) PlayerTextDrawHide(playerid, SpawnVeh_Base[playerid][e]);

	DebugMessage(playerid, sprintf("%d SQLID, %d script id", VehicleInfo[vehicle][carID], vehicle));

	return 1;
}
/*
this::C_LoadInventory(vehicle)
{
	if (!cache_num_rows())
	{
	    new query[256];
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `inventory` (`carid`) VALUES (%i)", VehicleInfo[vehicle][carID]);
	    mysql_tquery(dbHandle, query);
	    return 1;
	}

	new str_inv[24], str_inv2[24], str_inv3[24], str_inv4[24], str_inv5[24], str_inv6[24];

	for(new a = 0; a < MAX_CAR_INVENTORY; a++)
	{
		format(str_inv, sizeof(str_inv), "id_%i", a+1);
		cache_get_value_name_int(0, str_inv, CarInventory[vehicle][a][pInvItem]);
		format(str_inv2, sizeof(str_inv2), "a_%i", a+1);
		cache_get_value_name_int(0, str_inv2, CarInventory[vehicle][a][pInvQ]);
		format(str_inv3, sizeof(str_inv3), "ex_%i", a+1);
		cache_get_value_name_int(0, str_inv3, CarInventory[vehicle][a][pInvEx]);
		format(str_inv4, sizeof(str_inv4), "s_%i", a+1);
		cache_get_value_name_int(0, str_inv4, CarInventory[vehicle][a][pInvS]);
		format(str_inv5, sizeof(str_inv5), "f_%i", a+1);
		cache_get_value_name_float(0, str_inv5, CarInventory[vehicle][a][pInvQFloat]);

		new name[16];
		format(str_inv6, sizeof(str_inv6), "n_%i", a+1);
		cache_get_value_name(0, str_inv6, name);	
		
		format(CarInventory[vehicle][a][pInvName], 16, "%s", name);
	}
	return 1;
}

this::T_LoadInventory(vehicle)
{
	if (!cache_num_rows())
	{
	    new query[256];
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `inventory` (`trunkid`) VALUES (%i)", VehicleInfo[vehicle][carID]);
	    mysql_tquery(dbHandle, query);
	    return 1;
	}

	new str_inv[24], str_inv2[24], str_inv3[24], str_inv4[24], str_inv5[24], str_inv6[24];

	for(new a = 0; a < MAX_TRUNK_INVENTORY; a++)
	{
		format(str_inv, sizeof(str_inv), "id_%i", a+1);
		cache_get_value_name_int(0, str_inv, TrunkInventory[vehicle][a][pInvItem]);
		format(str_inv2, sizeof(str_inv2), "a_%i", a+1);
		cache_get_value_name_int(0, str_inv2, TrunkInventory[vehicle][a][pInvQ]);
		format(str_inv3, sizeof(str_inv3), "ex_%i", a+1);
		cache_get_value_name_int(0, str_inv3, TrunkInventory[vehicle][a][pInvEx]);
		format(str_inv4, sizeof(str_inv4), "s_%i", a+1);
		cache_get_value_name_int(0, str_inv4, TrunkInventory[vehicle][a][pInvS]);
		format(str_inv5, sizeof(str_inv5), "f_%i", a+1);
		cache_get_value_name_float(0, str_inv5, TrunkInventory[vehicle][a][pInvQFloat]);

		new name[16];
		format(str_inv6, sizeof(str_inv6), "n_%i", a+1);
		cache_get_value_name(0, str_inv6, name);	
		
		format(TrunkInventory[vehicle][a][pInvName], 16, "%s", name);
	}
	return 1;
}*/

ResetVehicleStuff(vehicleid, x = 0)
{
	new panels, doors, lights, tires;

	if (IsABicycle(vehicleid))	return 1;
	    
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
		
	foreach(new i : Player) {
		if (JackingVehicle[i] == vehicleid)
		{
			if (IsValidVehicle(JackingVehicle[i]))
			{
				new Float:ccX, Float:ccY, Float:ccZ;
				GetVehiclePos(JackingVehicle[i], ccX, ccY, ccZ);

				VehicleInfo[JackingVehicle[i]][ePhysicalAttack] = false;
				DestroyDynamic3DTextLabel(VehicleInfo[JackingVehicle[i]][eVehicleLabel]);
				VehicleInfo[JackingVehicle[i]][vCooldown] = false;
				JackingVehicle[i] = 0;
			}
		}
	}

	for(new i; i != MAX_TRUCK_PRODUCT; i++)
	{
	    if (i < 6 && IsValidDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]))
		{
			DestroyDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]);
            VehicleInfo[vehicleid][carCargoObj][i] = INVALID_OBJECT_ID;
		}

		if (i < 5 && IsValidDynamicObject(VehicleInfo[vehicleid][carSiren][i]))
		{
		    DestroyDynamicObject(VehicleInfo[vehicleid][carSiren][i]);
		    VehicleInfo[vehicleid][carSiren][i] = INVALID_OBJECT_ID;
		}

	    VehicleInfo[vehicleid][carCargoAmount][i] = 0;
		break;
	}
    
    DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicleid]);

	if (x)	return Save_Car(vehicleid);
	/*
	if (!VehicleInfo[vehicleid][carInsurance])
	{
		for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
		{
			TrunkInventory[vehicleid][i][pInvName] = EOS;
			TrunkInventory[vehicleid][i][pInvQFloat] = 0.0;
			TrunkInventory[vehicleid][i][pInvItem] =
			TrunkInventory[vehicleid][i][pInvQ] =
			TrunkInventory[vehicleid][i][pInvEx] =
			TrunkInventory[vehicleid][i][pInvS] = 
			VehicleInfo[vehicleid][carAttachObj][i] = 0;
		}

		for(new i = 0; i < MAX_CAR_INVENTORY; i++)
		{
			CarInventory[vehicleid][i][pInvName] = EOS;
			CarInventory[vehicleid][i][pInvQFloat] = 0.0;
			CarInventory[vehicleid][i][pInvItem] =
			CarInventory[vehicleid][i][pInvQ] =
			CarInventory[vehicleid][i][pInvEx] =
			CarInventory[vehicleid][i][pInvS] = 0;
		}

		VehicleInfo[vehicleid][carPaintJob] = 3;
		VehicleInfo[vehicleid][carRadio] =
		VehicleInfo[vehicleid][carComps] = 0;
		UpdateVehicleDamageStatus(vehicleid, 17895697, 16843009, 15, tires);
		
		for(new i = 0; i < 14; i++)
		{
		    if (VehicleInfo[vehicleid][carComponent][i] != 0)		RemoveVehicleComponent(vehicleid, VehicleInfo[vehicleid][carComponent][i]);
		        
            VehicleInfo[vehicleid][carComponent][i] = 0;
		}
	}
	else
	{
		if (VehicleInfo[vehicleid][carInsurance] != 3)
		{
			for(new i = 0; i < 14; i++)
			{
			    if (VehicleInfo[vehicleid][carComponent][i] != 0)	RemoveVehicleComponent(vehicleid, VehicleInfo[vehicleid][carComponent][i]);

	            VehicleInfo[vehicleid][carComponent][i] = 0;
			}

            VehicleInfo[vehicleid][carPaintJob] = 3;
			VehicleInfo[vehicleid][carRadio] =
			VehicleInfo[vehicleid][carComps] = 0;

			if (VehicleInfo[vehicleid][carInsurance] < 2)			UpdateVehicleDamageStatus(vehicleid, 17895697, 16843009, 15, tires);
		}
		
		if (VehicleInfo[vehicleid][carDestroyed]++ >= 4)
		{
		    VehicleInfo[vehicleid][carDestroyed] = 
		    VehicleInfo[vehicleid][carInsurance] = 0;
		}
	}*/

	if (VehicleInfo[vehicleid][carEngine] > 0.0)
	{
		VehicleInfo[vehicleid][carEngine] -= 5.0 + random(6);

		if (VehicleInfo[vehicleid][carEngine] <= 0.0)	VehicleInfo[vehicleid][carEngine] = 0.0;
	}

	if (VehicleInfo[vehicleid][carBattery] > 0.0)
	{
		VehicleInfo[vehicleid][carBattery] -= 10.0;

		if (VehicleInfo[vehicleid][carBattery] <= 0.0)	VehicleInfo[vehicleid][carBattery] = 0.0;
	}

	new userid = GetVehicleOwner(vehicleid);

	if (userid != INVALID_PLAYER_ID)
	{
	    VehicleInfo[vehicleid][carOwnerPlayer] = INVALID_PLAYER_ID;
        SendClientMessageEx(userid, COLOR_WHITE, "{FF6347}[%s]{FFFFFF} Aracýnýzýn motoru hasar aldý. Motor durumu: {FF6347}%.2f{FFFFFF}.", VehicleNames[GetVehicleModel(vehicleid)-400], VehicleInfo[vehicleid][carEngine]);
		SendClientMessageEx(userid, COLOR_WHITE, "{FF6347}[%s]{FFFFFF} Aracýnýzýn aküsü hasar aldý. Akü durumu: {FF6347}%.2f{FFFFFF}.", VehicleNames[GetVehicleModel(vehicleid)-400], VehicleInfo[vehicleid][carBattery]);
	}

	Save_Car(vehicleid);
    VehicleInfo[vehicleid][carDeath] = 1;
	return 1;
}

DestroyVehicleEx(vehicleid, save = 0) {

if(save)
{
    Save_Car(vehicleid);
}	

for(new p; p < MAX_CAR_WEAPONS; p++) VehicleInfo[vehicleid][carSlotUsed][p] = 0;

DestroyObject (VehRadarID [vehicleid]);
VehRadarID [vehicleid] = -1;
CheckingSpeed [vehicleid] = 0;

StopCarBoomBox(vehicleid);
VehicleInfo[vehicleid][carID] = -1;
VehicleInfo[vehicleid][carModel] = -1;
VehicleInfo[vehicleid][carColor1] = 0;
VehicleInfo[vehicleid][carColor2] = 0;
VehicleInfo[vehicleid][carOwnerID] = INVALID_PLAYER_ID;
VehicleInfo[vehicleid][carOwnerPlayer] = INVALID_PLAYER_ID;
VehicleInfo[vehicleid][carLock] = 0;
VehicleInfo[vehicleid][carImmob] = 0;
VehicleInfo[vehicleid][Impounded] = 0;
VehicleInfo[vehicleid][carFaction] = 0;

VehicleInfo[vehicleid][carTrunkLock] = 0;
VehicleInfo[vehicleid][carHoodLock] = 0;
VehicleInfo[vehicleid][carType] = 0;
VehicleInfo[vehicleid][carInt] = 0;
VehicleInfo[vehicleid][carVW] = 0;
VehicleInfo[vehicleid][carLocked] = 0;
VehicleInfo[vehicleid][carLights] = 0;
VehicleInfo[vehicleid][carEngineOn] = 0;
VehicleInfo[vehicleid][carAlarmTime] = 0;
VehicleInfo[vehicleid][carAdmin] = 0;
VehicleInfo[vehicleid][carDriver] = -1;
VehicleInfo[vehicleid][carRent] = 0;
VehicleInfo[vehicleid][carTerminate] = 0;
VehicleInfo[vehicleid][carTerminateEx] = 0;

VehicleInfo[vehicleid][carHidedPlate] = 0;
VehicleInfo[vehicleid][carFakePlate] = 0;
VehicleInfo[vehicleid][carWanted] = 0;
VehicleInfo[vehicleid][vCorp] = 0;

VehicleInfo[vehicleid][carPaintJob] = 0;
VehicleInfo[vehicleid][carComps] = 0;
VehicleInfo[vehicleid][carDestroyed] = 0;

    if (IsValidDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel])) DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel]);

	for(new i; i != MAX_TRUCK_PRODUCT; i++)
	{
	    if (i < 6 && IsValidDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]))
		{
			DestroyDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]);
            VehicleInfo[vehicleid][carCargoObj][i] = INVALID_OBJECT_ID;
		}

		if (i < 5 && IsValidDynamicObject(VehicleInfo[vehicleid][carSiren][i]))
		{
		    DestroyDynamicObject(VehicleInfo[vehicleid][carSiren][i]);
		    VehicleInfo[vehicleid][carSiren][i] = INVALID_OBJECT_ID;
		}

	    VehicleInfo[vehicleid][carCargoAmount][i] = 0;
		break;
	}
    
    DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicleid]);

    for(new i = 0; i < 14; i++)
	{
		if (VehicleInfo[vehicleid][carComponent][i] != 0)	RemoveVehicleComponent(vehicleid, VehicleInfo[vehicleid][carComponent][i]);

	        VehicleInfo[vehicleid][carComponent][i] = 0;
		}

		for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
		{
			TrunkInventory[vehicleid][i][pInvName] = EOS;
			TrunkInventory[vehicleid][i][pInvQFloat] = 0.0;
			TrunkInventory[vehicleid][i][pInvItem] =
			TrunkInventory[vehicleid][i][pInvQ] =
			TrunkInventory[vehicleid][i][pInvEx] =
			TrunkInventory[vehicleid][i][pInvS] = 
			VehicleInfo[vehicleid][carAttachObj][i] = 0;
		}

		for(new i = 0; i < MAX_CAR_INVENTORY; i++)
		{
			CarInventory[vehicleid][i][pInvName] = EOS;
			CarInventory[vehicleid][i][pInvQFloat] = 0.0;
			CarInventory[vehicleid][i][pInvItem] =
			CarInventory[vehicleid][i][pInvQ] =
			CarInventory[vehicleid][i][pInvEx] =
			CarInventory[vehicleid][i][pInvS] = 0;
	    }
			
	DestroyVehicle(vehicleid);	
    return 1;
}

AracKiraBitir(vehicleid) {

new query[256];
mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", VehicleInfo[vehicleid][carID]);
mysql_tquery(dbHandle, query);

for(new p; p < MAX_CAR_WEAPONS; p++) VehicleInfo[vehicleid][carSlotUsed][p] = 0;

VehicleInfo[vehicleid][carID] = -1;
VehicleInfo[vehicleid][carModel] = -1;
VehicleInfo[vehicleid][carColor1] = 0;
VehicleInfo[vehicleid][carColor2] = 0;
VehicleInfo[vehicleid][carOwnerID] = INVALID_PLAYER_ID;
VehicleInfo[vehicleid][carOwnerPlayer] = INVALID_PLAYER_ID;
VehicleInfo[vehicleid][carLock] = 0;
VehicleInfo[vehicleid][carImmob] = 0;
VehicleInfo[vehicleid][Impounded] = 0;
VehicleInfo[vehicleid][carFaction] = 0;

VehicleInfo[vehicleid][carTrunkLock] = 0;
VehicleInfo[vehicleid][carHoodLock] = 0;
VehicleInfo[vehicleid][carType] = 0;
VehicleInfo[vehicleid][carInt] = 0;
VehicleInfo[vehicleid][carVW] = 0;
VehicleInfo[vehicleid][carLocked] = 0;
VehicleInfo[vehicleid][carLights] = 0;
VehicleInfo[vehicleid][carEngineOn] = 0;
VehicleInfo[vehicleid][carAlarmTime] = 0;
VehicleInfo[vehicleid][carAdmin] = 0;
VehicleInfo[vehicleid][carDriver] = -1;
VehicleInfo[vehicleid][carRent] = 0;
VehicleInfo[vehicleid][carTerminate] = 0;
VehicleInfo[vehicleid][carTerminateEx] = 0;

VehicleInfo[vehicleid][carHidedPlate] = 0;
VehicleInfo[vehicleid][carFakePlate] = 0;
VehicleInfo[vehicleid][carWanted] = 0;
VehicleInfo[vehicleid][vCorp] = 0;

VehicleInfo[vehicleid][carPaintJob] = 0;
VehicleInfo[vehicleid][carComps] = 0;
VehicleInfo[vehicleid][carDestroyed] = 0;

    if (IsValidDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel])) DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel]);

	for(new i; i != MAX_TRUCK_PRODUCT; i++)
	{
	    if (i < 6 && IsValidDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]))
		{
			DestroyDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]);
            VehicleInfo[vehicleid][carCargoObj][i] = INVALID_OBJECT_ID;
		}

		if (i < 5 && IsValidDynamicObject(VehicleInfo[vehicleid][carSiren][i]))
		{
		    DestroyDynamicObject(VehicleInfo[vehicleid][carSiren][i]);
		    VehicleInfo[vehicleid][carSiren][i] = INVALID_OBJECT_ID;
		}

	    VehicleInfo[vehicleid][carCargoAmount][i] = 0;
		break;
	}
    
    DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicleid]);

    for(new i = 0; i < 14; i++)
	{
		if (VehicleInfo[vehicleid][carComponent][i] != 0)	RemoveVehicleComponent(vehicleid, VehicleInfo[vehicleid][carComponent][i]);

	        VehicleInfo[vehicleid][carComponent][i] = 0;
		}

		for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
		{
			TrunkInventory[vehicleid][i][pInvName] = EOS;
			TrunkInventory[vehicleid][i][pInvQFloat] = 0.0;
			TrunkInventory[vehicleid][i][pInvItem] =
			TrunkInventory[vehicleid][i][pInvQ] =
			TrunkInventory[vehicleid][i][pInvEx] =
			TrunkInventory[vehicleid][i][pInvS] = 
			VehicleInfo[vehicleid][carAttachObj][i] = 0;
		}

		for(new i = 0; i < MAX_CAR_INVENTORY; i++)
		{
			CarInventory[vehicleid][i][pInvName] = EOS;
			CarInventory[vehicleid][i][pInvQFloat] = 0.0;
			CarInventory[vehicleid][i][pInvItem] =
			CarInventory[vehicleid][i][pInvQ] =
			CarInventory[vehicleid][i][pInvEx] =
			CarInventory[vehicleid][i][pInvS] = 0;
	    }
			
	DestroyVehicle(vehicleid);	
    return 1;
}

HasComponent(vehicleid, compid)
{
	for(new i = 0; i < 14; i++)
	{
		if (VehicleInfo[vehicleid][carComponent][i] == compid) return 1;
	}
	return 0;
}

SetVehicleComponent(vehicleid, component, slot)
{
	VehicleInfo[vehicleid][carComponent][slot] = component;
	AddVehicleComponent(vehicleid, component);
	Save_Car(vehicleid);
	return 1;
}

SaveComponent(vehicleid, slot)
{
    if (!IsValidVehicle(vehicleid))	return 1;

	new component_str[6];
	format(component_str, sizeof(component_str), "comp%i", slot);

	SQL_SetInteger("vehicle", component_str, VehicleInfo[vehicleid][carComponent][slot], VehicleInfo[vehicleid][carID]);
	return 1;
}


ShowBuyingVehicleDetails(playerid)
{
	if (GetPVarInt(playerid, "BuyingVehicleModel") < 400 || GetPVarInt(playerid, "BuyingVehicleModel") > 611) return 1;

	new registerveh = price_reg[GetPVarInt(playerid, "BuyingVehicleRegister")], 
		alarmveh = price_alarm[GetPVarInt(playerid, "BuyingVehicleAlarm")], 
		lockveh = price_lock[GetPVarInt(playerid, "BuyingVehicleLock")], 
		immobveh = price_immob[GetPVarInt(playerid, "BuyingVehicleImmob")], 
		insuranceveh = GetInsurancePrice(GetPVarInt(playerid, "BuyingVehicleModel")) * GetPVarInt(playerid, "BuyingVehicleInsurance"),
		xmradioveh = price_radio[GetPVarInt(playerid, "BuyingVehicleRadio")], gpsveh = price_gps[GetPVarInt(playerid, "BuyingVehicleGps")];

    new mes[56];
	format(mes, sizeof(mes), "{bab9ba}%s - {35B835}$%i", VehicleNames[GetPVarInt(playerid, "BuyingVehicleModel")-400], GetVehiclePrice(GetPVarInt(playerid, "BuyingVehicleModel"))+registerveh+alarmveh+lockveh+immobveh+insuranceveh+xmradioveh+gpsveh);
	Dialog_Show(playerid, BuyingVehicleDetails, DIALOG_STYLE_LIST, mes, "Sisteme Kayýt\nAlarm\nKilit\nImmobilizer\nSigorta\nMultimedya(Radyo)\nGPS\nRenk", "Seç", "<<");
	return 1;
}

Save_Car(vehicleid)
{
	if (!VehicleInfo[vehicleid][carOwnerID]) return 1;
	if (!IsValidVehicle(vehicleid)) return 1;
	
	new Float:hp, panels, doorss, lightss, tires;

	GetVehicleHealth(vehicleid, hp);
	GetVehicleDamageStatus(vehicleid, panels, doorss, lightss, tires);
	
	new query[2550];

	
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `color1`=%i,`color2`=%i,`x`=%.1f,`y`=%.1f,`z`=%.1f,`fa`=%.1f,`engine`=%.2f,`milliage`=%.1f",
		VehicleInfo[vehicleid][carColor1],
		VehicleInfo[vehicleid][carColor2],
		VehicleInfo[vehicleid][carParkX],
		VehicleInfo[vehicleid][carParkY],
		VehicleInfo[vehicleid][carParkZ],
		VehicleInfo[vehicleid][carParkA],
		VehicleInfo[vehicleid][carEngine],
		VehicleInfo[vehicleid][carMilliage]
	);
	
	mysql_format(dbHandle, query, sizeof(query), "%s,`plate`='%s',`owner`=%i,`battery`=%.2f,`health`=%.1f,`armour`=%.1f,`vw`=%i,`int`=%i",
        query,
		VehicleInfo[vehicleid][carPlate],
		VehicleInfo[vehicleid][carOwnerID],
		VehicleInfo[vehicleid][carBattery],
		hp,
		VehicleInfo[vehicleid][carArmour],
		VehicleInfo[vehicleid][carVW],
		VehicleInfo[vehicleid][carInt]
	);
	
	mysql_format(dbHandle, query, sizeof(query), "%s,`alarm`=%i,`locks`=%i,`immob`=%i,`insurances`=%i,`destroys`=%i,`impound`=%i,`gps`=%i,`fuel`=%.1f, `faction`=%i, `registered`=%i",
		query,
		VehicleInfo[vehicleid][carAlarm],
		VehicleInfo[vehicleid][carLock],
		VehicleInfo[vehicleid][carImmob],
		VehicleInfo[vehicleid][carInsurance],
		VehicleInfo[vehicleid][carDestroyed],
		VehicleInfo[vehicleid][Impounded],
		VehicleInfo[vehicleid][carGps],
		VehicleInfo[vehicleid][carFuel],
		VehicleInfo[vehicleid][carFaction],
		VehicleInfo[vehicleid][carRegistered]
	);
	
	mysql_format(dbHandle, query, sizeof(query), "%s,`comp0`=%i,`comp1`=%i,`comp2`=%i,`comp3`=%i,`comp4`=%i,`comp5`=%i,`comp6`=%i",
        query,
		VehicleInfo[vehicleid][carComponent][0],
		VehicleInfo[vehicleid][carComponent][1],
		VehicleInfo[vehicleid][carComponent][2],
		VehicleInfo[vehicleid][carComponent][3],
		VehicleInfo[vehicleid][carComponent][4],
		VehicleInfo[vehicleid][carComponent][5],
		VehicleInfo[vehicleid][carComponent][6]
	);
	
	mysql_format(dbHandle, query, sizeof(query), "%s,`comp7`=%i,`comp8`=%i,`comp9`=%i,`comp10`=%i,`comp11`=%i,`comp12`=%i,`comp13`=%i,`paintjob`=%i",
        query,
		VehicleInfo[vehicleid][carComponent][7],
		VehicleInfo[vehicleid][carComponent][8],
		VehicleInfo[vehicleid][carComponent][9],
		VehicleInfo[vehicleid][carComponent][10],
		VehicleInfo[vehicleid][carComponent][11],
		VehicleInfo[vehicleid][carComponent][12],
		VehicleInfo[vehicleid][carComponent][13],
		VehicleInfo[vehicleid][carPaintJob]
	);
	
	mysql_format(dbHandle, query, sizeof(query), "%s,`radio`=%i,`comps`=%i,`panels`=%i,`doors`=%i,`lights`=%i,`tires`=%i WHERE `id`=%i LIMIT 1",
        query,
		VehicleInfo[vehicleid][carRadio],
		VehicleInfo[vehicleid][carComps],
		panels,
		doorss,
		lightss,
		tires,
		VehicleInfo[vehicleid][carID]
	);
	mysql_tquery(dbHandle, query);

	for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
	{
		if (VehicleInfo[vehicleid][carAttachObj][i] != 0)
		{
			DestroyDynamicObject(VehicleInfo[vehicleid][carAttach][i]);
			VehicleInfo[vehicleid][carAttach][i] = INVALID_OBJECT_ID;
		}
	}
	
	return 1;	
}


Save_CarAttach(vehicleid, i)
{
    new query[2500];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `attach%i_pos0`=%.1f,`attach%i_pos1`=%.1f,`attach%i_pos2`=%.1f,`attach%i_rot0`=%.1f,`attach%i_rot1`=%.1f,`attach%i_rot2`=%.1f, `arg_%i`=%i WHERE `id`=%i",
	i,VehicleInfo[vehicleid][carAttachPosX][i], i,VehicleInfo[vehicleid][carAttachPosY][i], i,VehicleInfo[vehicleid][carAttachPosZ][i], i,VehicleInfo[vehicleid][carAttachRotX][i], i,VehicleInfo[vehicleid][carAttachRotY][i],
	i,VehicleInfo[vehicleid][carAttachRotZ][i], i+1,VehicleInfo[vehicleid][carAttachObj][i], VehicleInfo[vehicleid][carID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

GetMaxPlayerCars(playerid)
{
	switch(PlayerInfo[playerid][pPremium])
	{
	    case 0, 1: return 3;
	    case 2: return 5;
	    case 3: return 7;
	}
	return 3;
}

ShowAclass(playerid)
{
	SetPVarInt(playerid, #Selection, 2);

	new mes[sizeof(a_class_model)*128];

	for(new i = 0; i < sizeof(a_class_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, a_class_model[i], VehicleNames[a_class_model[i]-400], FormatNumber(GetVehiclePrice(a_class_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "4 KAPILI ARACLAR", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowBclass(playerid)
{
	SetPVarInt(playerid, #Selection, 0);

	new mes[sizeof(b_class_model)*128];

	for(new i = 0; i < sizeof(b_class_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, b_class_model[i], VehicleNames[b_class_model[i]-400], FormatNumber(GetVehiclePrice(b_class_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "2 KAPILI ARACLAR", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowLowriders(playerid)
{
	SetPVarInt(playerid, #Selection, 1);

	new mes[sizeof(lowride_class_model)*128];

	for(new i = 0; i < sizeof(lowride_class_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, lowride_class_model[i], VehicleNames[lowride_class_model[i]-400], FormatNumber(GetVehiclePrice(lowride_class_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "Lowriders", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowPickups(playerid)
{
	SetPVarInt(playerid, #Selection, 4);

	new mes[sizeof(pickups_class_model)*128];

	for(new i = 0; i < sizeof(pickups_class_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, pickups_class_model[i], VehicleNames[pickups_class_model[i]-400], FormatNumber(GetVehiclePrice(pickups_class_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "Pickup ve  Vanlar", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowSport(playerid)
{
	SetPVarInt(playerid, #Selection, 3);

	new mes[sizeof(sport_model)*128];
	for(new i = 0; i < sizeof(sport_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, sport_model[i], VehicleNames[sport_model[i]-400], FormatNumber(GetVehiclePrice(sport_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "SPOR ARACLAR", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowOffRoad(playerid)
{
	SetPVarInt(playerid, #Selection, 5);

	new mes[sizeof(offroad_model)*128];
	for(new i = 0; i < sizeof(offroad_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, offroad_model[i], VehicleNames[offroad_model[i]-400], FormatNumber(GetVehiclePrice(offroad_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "SUV ARACLAR", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowMotoBike(playerid)
{
	SetPVarInt(playerid, #Selection, 7);

	new mes[sizeof(motobike_model)*128];
	for(new i = 0; i < sizeof(motobike_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, motobike_model[i], VehicleNames[motobike_model[i]-400], FormatNumber(GetVehiclePrice(motobike_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "Motorsiklet / Bisikletler", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowIndustrial(playerid)
{
	SetPVarInt(playerid, #Selection, 6);
	new mes[sizeof(industrial_model)*128];
	for(new i = 0; i < sizeof(industrial_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, industrial_model[i], VehicleNames[industrial_model[i]-400], FormatNumber(GetVehiclePrice(industrial_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "KAMYON VE IS ARACLARI", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowOther(playerid)
{
	SetPVarInt(playerid, #Selection, 8);
	new mes[sizeof(other_model)*128];
	for(new i = 0; i < sizeof(other_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, other_model[i], VehicleNames[other_model[i]-400], FormatNumber(GetVehiclePrice(other_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "DIGERLERI", mes, "Sec", "Geri Don");
	
	return 1;
}

ShowBoats(playerid)
{
	SetPVarInt(playerid, #Selection, 10);
	new mes[sizeof(boat_model)*128];
	for(new i = 0; i < sizeof(boat_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, boat_model[i], VehicleNames[boat_model[i]-400], FormatNumber(GetVehiclePrice(boat_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "Botlar", mes, "Sec", "Kapat");
	
	return 1;
}

ShowFly(playerid)
{
	SetPVarInt(playerid, #Selection, 11);
	new mes[sizeof(fly_model)*128];
	for(new i = 0; i < sizeof(fly_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, fly_model[i], VehicleNames[fly_model[i]-400], FormatNumber(GetVehiclePrice(fly_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "HAVA ARACLARI", mes, "Sec", "Kapat");
	
	return 1;
}

ShowDonate(playerid)
{
	SetPVarInt(playerid, #Selection, 9);

	new mes[sizeof(donate_model)*128];

	for(new i = 0; i < sizeof(donate_model); i++)
	{
		format(mes, sizeof(mes), "%s%i(0.0, 0.0, -27.0, 0.8)\t~w~%s~n~~g~~h~$%s\n", mes, donate_model[i], VehicleNames[donate_model[i]-400], FormatNumber(GetVehiclePrice(donate_model[i]))); 
	}
	Dialog_Show(playerid, MODEL_SELECTION_BUYCAR, DIALOG_STYLE_PREVIEW_MODEL, "ULTRA LUKS ARACLAR", mes, "Seç", "Geri Don");
	
	return 1;
}


Dialog:MODEL_SELECTION_BUYCAR(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, SelectClass, DIALOG_STYLE_LIST, "Bir kategori seçin", "2 Kapýlý araçlar\n\
																									Lowrider araçlar\n\
																									4 kapýlý ve lüks araçlar\n\
																									Spor araçlar\n\
																									Pickuplar ve panelvan araçlar\n\
																									SUV araçlar\n\
																									Kamyon ve iþci araçlarý\n\
																									Motorsiklet / Bisikletler\n\
																									Diðerleri\n\
																									Premium araçlar", "Seç", "Kapat");
	
	new price, modelid;

	switch(GetPVarInt(playerid, #Selection))
	{
		case 0: modelid = b_class_model[listitem];
		case 1: modelid = lowride_class_model[listitem];
		case 2: modelid = a_class_model[listitem];
		case 3: modelid = sport_model[listitem];
		case 4: modelid = pickups_class_model[listitem];
		case 5: modelid = offroad_model[listitem];
		case 6: modelid = industrial_model[listitem];
		case 7: modelid = motobike_model[listitem];
		case 8: modelid = other_model[listitem];
		case 9: modelid = donate_model[listitem];
		case 10: modelid = boat_model[listitem];
		case 11: modelid = fly_model[listitem];
	}
	
	DeletePVar(playerid, #Selection);

	if ((price = GetVehiclePrice(modelid)) == 0)	return SendErrorMessage(playerid, "Bu araç mevcut deðil!");
	        
	if (!PlayerInfo[playerid][pPremium] && IsDonateVehicle(modelid))	return SendErrorMessage(playerid, "Bu aracý satýn almak için bronz premium hesabýnýz veya daha yüksek bir hesabýnýzýn olmasý gerekir.");
	if (PlayerInfo[playerid][pPremium] < 1 && IsBronzeVehicle(modelid))	return SendErrorMessage(playerid, "Bu aracý satýn almak için gümüþ premium hesabýnýz veya daha yüksek bir hesabýnýzýn olmasý gerekir");
	if (PlayerInfo[playerid][pPremium] < 2 && IsSilverVehicle(modelid))	return SendErrorMessage(playerid, "Bu aracý satýn almak için altýn premium hesabýnýzýn olmasý gerekir.");
	if (PlayerInfo[playerid][pPremium] < 3 && IsGoldVehicle(modelid))	return SendErrorMessage(playerid, "Bu aracý satýn alabilmeniz için altýn premium hesabýna sahip olmanýz gerekir.");

	DeletePVar(playerid, "BuyingVehicleModel");
	SetPVarInt(playerid, "BuyingVehicleRegister", 0);
	SetPVarInt(playerid, "BuyingVehicleAlarm", 0);
	SetPVarInt(playerid, "BuyingVehicleLock", 0);
	SetPVarInt(playerid, "BuyingVehicleImmob", 0);
	SetPVarInt(playerid, "BuyingVehicleInsurance", 0);
	SetPVarInt(playerid, "BuyingVehicleRadio", 0);
	SetPVarInt(playerid, "BuyingVehicleGps", 0);
	SetPVarInt(playerid, "BuyingVehicleModel", modelid);

	new mes[56];

	format(mes, sizeof(mes), "{ffffff}%s - {35B835}$%s", VehicleNames[modelid-400], FormatNumber(price));

	if (modelid == 481 || modelid == 509 || modelid == 510)
	{
		Dialog_Show(playerid, BuyingVehicleDone, DIALOG_STYLE_MSGBOX, mes, "Bu aracý satýn almak istediðinizden emin misiniz?", "Kabul", "Ýptal");
	}
	else
	{
		SetPVarInt(playerid, #veh_color1, random(255));
		SetPVarInt(playerid, #veh_color2, random(255));

		new vehFuel[15], vehDrive[20];

		new Float:vehMass = GetVehicleModelInfoAsFloat(modelid, "fMass"); 
						
        if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nDriveType") == 'F')
	    	vehDrive = "Ön çekiþli";
	    else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nDriveType") == 'R')
	    	vehDrive = "Arka çekiþli";
	    else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nDriveType") == '4')
	    	vehDrive = "4x4";
											
	    if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'P')
	    	vehFuel = "Benzin";
	    else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'D')
	    	vehFuel = "Dizel";
	    else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'E')
	   		vehFuel = "Elektrik";
					
	    static const str_size[] = "{ecc317}Ücret: \t\t			{ffffff}$%s\n\
                                    {ecc317}Maksimum hýz: \t		{ffffff}%.1f km/h\n\
                                    {ecc317}Saðlamlýk: \t		{ffffff}%.1f\n\
                                    {ecc317}Aðýrlýk: \t\t		{ffffff}%.1f kf\n\n\
                                    {ecc317}Sürüþ dinamiði: \t		{ffffff}%s\n\
                                    {ecc317}Yakýt tipi: \t\t			{ffffff}%s\n\
                                    {ecc317}Yakýt tüketimi: \t		{ffffff}%.1f l/100 km\n\
                                    {ecc317}Bagaj kapasitesi: \t	{ffffff}%.1f l\n\n";
									
        new string[sizeof(str_size) + 15 + 20 + 6 + 128*2 + 128],
			registerveh = price_reg[GetPVarInt(playerid, "BuyingVehicleRegister")];
		
        format(string, sizeof(string), str_size,
			FormatNumber(GetVehiclePrice(modelid)), 
			GetVehicleMaxSpeed[modelid-400], 
			GetVehicleMaxHealth(modelid), 
			vehMass, 
			vehDrive, 
			vehFuel,
			GetVehicleFuelUsage(modelid),
			GetVehicleFuelCapacity(modelid)
		);

		format(string, sizeof(string), "%s{ecc317}Renk 1{ffffff} - [{%06x}#%i{ffffff}]\n{ecc317}Renk 2{ffffff} - [{%06x}#%i{ffffff}]\n\n", string, VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color1)] >>> 8, GetPVarInt(playerid, #veh_color1), VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color2)] >>> 8, GetPVarInt(playerid, #veh_color2));
		
		SetPVarInt(playerid, "BuyingVehicleRegister", 1);
		format(string, sizeof(string), "%s{ffffff}Sisteme Kayýt: \t{ecc317}$%i\n{ecc317}+ {ffffff}DMV sistemine kayýt olan plaka\n\n", string, registerveh);

		format(string, sizeof(string), "%s{ffffff}Aracý satýn almak için '{ecc317}Öde{ffffff}' butonuna basabilirsiniz.", string);

		Dialog_Show(playerid, BuyingVehicleList, DIALOG_STYLE_MSGBOX, mes, string, "Düzenle", "Öde");
	}
	return 1;
}

LoadComp(vehicle)
{
	if (VehicleInfo[vehicle][carPaintJob] != 3) ChangeVehiclePaintjob(vehicle, VehicleInfo[vehicle][carPaintJob]);

	for(new i = 0; i < 14; i++)
	{
		if (VehicleInfo[vehicle][carComponent][i] == 0) continue;

		AddVehicleComponent(vehicle, VehicleInfo[vehicle][carComponent][i]);
	}
	return 1;
}

SendVehicleMessage(vehicleid,color,string[]) 
{
	foreach(new i : Player) 
	{
	    if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicleid)) continue;

        SendClientMessage(i,color,string);
	}
	return 1;
}

GetVehicleNumber()
{
	new str[24], allowedchars[][2] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	
	format(str, 24, "%i%s%s%s%i%i%i", random(9), allowedchars[random(sizeof(allowedchars))], allowedchars[random(sizeof(allowedchars))], allowedchars[random(sizeof(allowedchars))], random(9), random(9), random(9));
	return str;
}

RepairVehicleBody(vehicle)
{
	return UpdateVehicleDamageStatus(vehicle, 0, 0, 0, 0);
}

DealerShip_Nearest(playerid, type)
{
	if (!IsPlayerLogged(playerid)) return -1;

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (!BizInfo[i][bizID]) continue;
		if (PlayerToPoint(35.0,playerid,BizInfo[i][bizPosX], BizInfo[i][bizPosY], BizInfo[i][bizPosZ]) && GetWorld(playerid) == BizInfo[i][bizPosVW] && GetInterior(playerid) == BizInfo[i][bizPosInt] && BizInfo[i][bizType] == type) 
		{
			return i;
		}
	}
	return -1;
}

GetInsurancePrice(modelid)
{
	for(new i = 0; i < sizeof(InsurancesPrice); i++)
	{
		if (modelid == InsurancesPrice[i][insuranceModel]) return InsurancesPrice[i][insurancePrice];
	}
	return 350;
}

FindVehicleByPlate(plate[])
{
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i ++)
	{
		if (isnull(VehicleInfo[i][carPlate])) continue;
		if (CompareStrings(plate, VehicleInfo[i][carPlate])) return i;
	}
	return -1;
}

Vehicle_OnVehicleSpawn(vehicleid)
{
	if(IsValidVehicle(vehicleid))
	{
	for(new i; i != MAX_TRUCK_PRODUCT; i++)
	{
	    if (i < 6 && IsValidDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]))
		{
			DestroyDynamicObject(VehicleInfo[vehicleid][carCargoObj][i]);
            VehicleInfo[vehicleid][carCargoObj][i] = INVALID_OBJECT_ID;
		}

		if (i < 5 && IsValidDynamicObject(VehicleInfo[vehicleid][carSiren][i]))
		{
		    DestroyDynamicObject(VehicleInfo[vehicleid][carSiren][i]);
		    VehicleInfo[vehicleid][carSiren][i] = INVALID_OBJECT_ID;
		}

	    VehicleInfo[vehicleid][carCargoAmount][i] = 0;
	}

	SetVehicleParamsEx(vehicleid, 0, 0, 0, 0, 0, 0, 0);
 	VehicleInfo[vehicleid][carLocked] = 0;
 	VehicleInfo[vehicleid][carTrunkLock] = 0;
 	VehicleInfo[vehicleid][carEngineOn] = 0;

    if (VehicleInfo[vehicleid][carOwnerID] == INVALID_PLAYER_ID)
    {
		FixVehicle(vehicleid);
		VehicleInfo[vehicleid][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicleid));
		ToggleVehicleLock(vehicleid, false);
	}

    if (VehicleInfo[vehicleid][carFaction] > 0 || VehicleInfo[vehicleid][carOwnerID] > 0 && VehicleInfo[vehicleid][carOwnerID] != INVALID_PLAYER_ID)	ToggleVehicleLock(vehicleid, false);
	if (VehicleInfo[vehicleid][carOwnerID] && VehicleInfo[vehicleid][carDeath])		SetVehicleHealth(vehicleid, GetVehicleMaxHealth(GetVehicleModel(vehicleid)) + VehicleInfo[vehicleid][carArmour]);
	
	if(OlusumTipGetir(VehicleInfo[vehicleid][carFaction]) == FACTION_POLICE && VehicleInfo[vehicleid][carOwnerID] == INVALID_PLAYER_ID && VehicleInfo[vehicleid][carOwnerID] == 0) {
		for(new j; j < MAX_CAR_WEAPONS; j++) VehicleInfo[vehicleid][carSlotUsed][j] = 0;
	}

	if (VehicleInfo[vehicleid][carType] == RENT_CAR)
	{
	    for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
		{
			TrunkInventory[vehicleid][i][pInvName] = EOS;
			TrunkInventory[vehicleid][i][pInvQFloat] = 0.0;
			TrunkInventory[vehicleid][i][pInvItem] =
			TrunkInventory[vehicleid][i][pInvQ] =
			TrunkInventory[vehicleid][i][pInvEx] =
			TrunkInventory[vehicleid][i][pInvS] = 
			VehicleInfo[vehicleid][carAttachObj][i] = 0;
		}

		for(new i = 0; i < MAX_CAR_INVENTORY; i++)
		{
			CarInventory[vehicleid][i][pInvName] = EOS;
			CarInventory[vehicleid][i][pInvQFloat] = 0.0;
			CarInventory[vehicleid][i][pInvItem] =
			CarInventory[vehicleid][i][pInvQ] =
			CarInventory[vehicleid][i][pInvEx] =
			CarInventory[vehicleid][i][pInvS] = 0;
		}
	}

	VehicleInfo[vehicleid][carDeath] = 0;
	LoadedTrash[vehicleid] = 0;
	}
}

Float:GetVehicleSpeedS(vehicleid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if(GetVehicleVelocity(vehicleid, x, y, z))
	{
		return floatsqroot((x * x) + (y * y) + (z * z)) * 181.5;
	}

	return 0.0;
}

Vehicle_OnVehicleDeath(vehicleid, killerid)
{
	if (IsValidDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel])) DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel]);

	if (killerid == GetVehicleOwner(vehicleid) && !VehicleInfo[vehicleid][carDeath]) ResetVehicleStuff(vehicleid);

	SendAdmMessage("DEBUG: %s [%d] adlý oyuncu araç patlattý. ID: %d.", GetNameEx(killerid), killerid, vehicleid);

	if (VehicleInfo[vehicleid][carOwnerID] && VehicleInfo[vehicleid][carOwnerID] != INVALID_PLAYER_ID)
	{
	    new userid = GetVehicleOwner(vehicleid);

		if (IsPlayerLogged(userid)) PlayerInfo[userid][pCarKey] = 0;
	
		DestroyVehicleEx(vehicleid);
	}
	
	if (VehicleInfo[vehicleid][carRent] != 0)
	{
	    new userid = GetIDByID(VehicleInfo[vehicleid][carRent]);
	    if (IsPlayerLogged(userid))
	    {
	        pTemp[userid][pRentveh] = 0;

			if (pTemp[userid][pJob] ) {
				EndJob(userid);
				SendErrorMessage(userid, "Araç respawn edildi.");
			} else {
				SendErrorMessage(userid, "Kiralanan araç patladýðý için mesleðiniz iptal edildi.");
			}
	    }
	    VehicleInfo[vehicleid][carRent] = 0;
		VehicleInfo[vehicleid][carOwnerPlayer] = INVALID_PLAYER_ID;
	}

	if (VehicleInfo[vehicleid][vCorp]) RemoveCorpse(VehicleInfo[vehicleid][vCorp]-1);
}

Vehicle_OnPlayerUpdate(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
    if (vehicleid)
	{	
		if (IsABicycle(vehicleid)) return 1;
		
		new string[128], 
			kmh = GetVehicleSpeed(vehicleid),
			vfuel = floatround(VehicleInfo[vehicleid][carFuel]/GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) * 100);

		switch(vfuel)
		{
			case 90 .. 100:	string="~b~YAKIT___________~l~I~w~IIIIIIIIII~r~I~l~I";
			case 80 .. 89: 	string="~b~YAKIT___________~l~I~w~IIIIIIIII~r~I~w~I~l~I";
			case 70 .. 79: 	string="~b~YAKIT___________~l~I~w~IIIIIIII~r~I~w~II~l~I";
			case 60 .. 69: 	string="~b~YAKIT___________~l~I~w~IIIIIII~r~I~w~III~l~I";
			case 50 .. 59: 	string="~b~YAKIT___________~l~I~w~IIIIII~r~I~w~IIII~l~I"; 
			case 40 .. 49: 	string="~b~YAKIT___________~l~I~w~IIIII~r~I~w~IIIII~l~I";
			case 30 .. 39: 	string="~b~YAKIT___________~l~I~w~IIII~r~I~w~IIIIII~l~I";
			case 20 .. 29: 	string="~b~YAKIT___________~l~I~w~III~r~I~w~IIIIIII~l~I";
			case 10 .. 19: 	string="~b~YAKIT___________~l~I~w~II~r~I~w~IIIIIIII~l~I";
			case 1 .. 9:	string="~b~YAKIT___________~l~I~w~I~r~I~w~IIIIIIIII~l~I";
			case 0:			string="~b~YAKIT___________~l~I~r~I~w~IIIIIIIIII ~l~I"; 
		}

		switch(kmh) {
			case 100 .. 5000: format(string, sizeof(string), "%s~n~~b~HIZ______________~r~%d_km/h", string, kmh);
			case 91 .. 99:    format(string, sizeof(string), "%s~n~~b~HIZ______________~y~%d_km/h", string, kmh);
			case 10 .. 90:    format(string, sizeof(string), "%s~n~~b~HIZ______________~w~%d_km/h", string, kmh);
			case 0 .. 9:      format(string, sizeof(string), "%s~n~~b~HIZ______________~w~%d_km/h", string, kmh);
		} 
		
		format(string, sizeof(string), "%s~n~~b~KILOMETRE__~w~%0.2f_km", string, VehicleInfo[vehicleid][carMilliage]);
		PlayerTextDrawSetString(playerid, SpeedText[playerid], string);
	}
	return 1;
} 

GetNextVehicleTrunkSlot(vehicleid)
{
	for(new i; i != MAX_TRUNK_INVENTORY; i++)
	{
	    if (TrunkInventory[vehicleid][i][pInvItem] == 0) return i;
	}
	return -1;
}

GetNextVehicleGBSlot(vehicleid)
{
	for(new i; i != MAX_TRUNK_INVENTORY; i++)
	{
	    if (CarInventory[vehicleid][i][pInvItem] == 0) return i;
	}
	return -1;
}

VehicleTrunk(vehicle, bool:toggle)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;

	GetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet,boot,objective);
	if (toggle)
	{
		SetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet, 1,objective);
		VehicleInfo[vehicle][carTrunkLock] = 1;
	}
	else
	{
		SetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet, 0, objective);
		VehicleInfo[vehicle][carTrunkLock] = 0;
	}
	return 1;
}

VehicleHood(vehicle, bool:toggle)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;

	GetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet,boot,objective);
	if (toggle)
	{
		SetVehicleParamsEx(vehicle,engine,lights,alarm,doors,1,boot,objective);
		VehicleInfo[vehicle][carHoodLock] = 1;
	}
	else
	{
		SetVehicleParamsEx(vehicle,engine,lights,alarm,doors,0,boot,objective);
		VehicleInfo[vehicle][carHoodLock] = 0;
	}
	return 1;
}

IsDriver(playerid)
{
	return IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER ? 1 : 0;
}

VehicleEmpty(vehicleid)
{
	foreach(new i : Player)
	{
		if (IsPlayerInVehicle(i, vehicleid) && !IsPlayerAFK(i) && IsPlayerLogged(i)) return 0;
	}
	return 1;
}

GetVehicleZone(vehicleid)
{
	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);

	new string[128], zone[28];

	if (IsValidVehicle(vehicleid)) GetZone(x, y, zone, sizeof(zone));
	
	if (IsPointInAnyDynamicArea(x, y, z)) {
		new areas[10], street_area[2], j = GetNumberDynamicAreasForPoint(x,y,z);
		GetDynamicAreasForPoint(x, y, z, areas, sizeof(areas));

		if (GetStreet(areas, j, street_area)) {
			if (street_area[1] == -1) format(string, sizeof(string), "%s, %s", zone, street_names[street_area[0]]); 
			else					 format(string, sizeof(string), "%s, %s sokaðý ile %s sokaðý arasýnda.", zone, street_names[street_area[0]],street_names[street_area[1]]);
			
			return string;
		}
	}

	format(string, sizeof(string), "%s", zone);
	return string;
}

FixVehicle(vehicleid)
{
    VehicleInfo[vehicleid][carDeath] = 0;
	RepairVehicle(vehicleid);

    if (VehicleInfo[vehicleid][carOwnerID] > 0 && VehicleInfo[vehicleid][carOwnerID] != INVALID_PLAYER_ID)	
		SetVehicleHealth(vehicleid, GetVehicleMaxHealth(GetVehicleModel(vehicleid)) + VehicleInfo[vehicleid][carArmour]);
	
	else
	{
	    if (GetVehicleModel(vehicleid) == 601 || GetVehicleModel(vehicleid) == 528 || GetVehicleModel(vehicleid) == 427)	\
				SetVehicleHealth(vehicleid, 10000.0);
	    else	SetVehicleHealth(vehicleid, 1000.0);
	}
	return 1;
}

GetMaxPassengers(model)
{
    model -= 400;
    if (0 <= model <= 211)
    {
        static seekBlock_vSeats[27] = {0x10331113, 0x11311131, 0x11331313, 0x80133301, 0x1381F110, 0x10311103, 0x10001F10, 0x11113311, 0x13113311, 0x31101100, 0x30001301, 0x11031311, 0x11111331, 0x10013111, 0x01131100, 0x11111110, 
		0x11100031, 0x11130221, 0x33113311, 0x11111101, 0x33101133, 0x101001F0, 0x03133111, 0xFF11113F, 0x13330111, 0xFF131111, 0x0000FF3F};

        return ((seekBlock_vSeats[model >>> 3] >>> ((model & 7) << 2)) & 15);
    }
    return 15;
}

this::MyCarsSpawn(playerid, response)
{
	if (!response)	return 1;
	
	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `owner` = %i AND `id` = %i LIMIT 1", PlayerInfo[playerid][pID], pTemp[playerid][MyCars][pTemp[playerid][MyCarSpawn][0]]);
	mysql_tquery(dbHandle, query, "OnPlayerSpawnVehicle", "i", playerid);

	return 1;
}

GetVehName(id)
{
	new 
		query[80],
		name[24],
		model
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT `model` FROM `cars` WHERE `id` = %i LIMIT 1", id);
	new Cache:cache = mysql_query(dbHandle, query);
	
	cache_get_value_int(0, "model", model);

	format(name, sizeof(name), "%s", VehicleNames[model-400]);
	cache_delete(cache);
	return name;
}


GetCarsignPosition(vehicle, &Float:x, &Float:y, &Float:z)
{
    new modelid = GetVehicleModel(vehicle);

	for(new i = 0; i < sizeof(CarSignPosition); i++)
	{
	    if (modelid != CarSignPosition[i][Model]) continue;
	        
        x = CarSignPosition[i][positionX];
		y = CarSignPosition[i][positionY];
		z = CarSignPosition[i][positionZ];
		break;
	}
	return 1;
}

GetNearBootVehicle(playerid)
{
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i ++)
	{
	    if (IsVehicleStreamedIn(i, playerid) && IsOnBootVehicle(playerid, i)) return i;
	}
	return 0;
}

GetBootPos(vehicleid, &Float:x, &Float:y, &Float:z)
{
	new Float:angle, Float:distance, model = GetVehicleModel(vehicleid);

	GetVehicleModelInfo(model, 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x += (distance * floatsin(-angle+180, degrees));
    y += (distance * floatcos(-angle+180, degrees));
	return 1;
}

IsOnBootVehicle(playerid, vehicleid)
{
    new Float: x, Float: y, Float: z, model = GetVehicleModel(vehicleid);
	GetBootPos(vehicleid, x, y, z);
    
    if (model == 435 || model == 450 || model == 584 || model == 591)	return IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z);
        
    return IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z);
}

IsOnHoodVehicle(playerid, vehicleid)
{
    new Float:angle,Float:distance, Float: x, Float: y, Float: z;

    GetVehicleModelInfo(GetVehicleModel(vehicleid), 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x -= (distance * floatsin(-angle+180, degrees));
    y -= (distance * floatcos(-angle+180, degrees));
    return IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z);
}

IsWindowsClose(vehicle)
{
    new wi_state[4];
	GetVehicleParamsCarWindows(vehicle, wi_state[0], wi_state[1], wi_state[2], wi_state[3]);
	return (wi_state[0] != 0 && wi_state[1] != 0 && wi_state[2] != 0 && wi_state[3] != 0) ? (1):(0);
}

GetVehicleSpeed(vehicleid)
{
    new Float:x,
        Float:y,
        Float:z,
        vel;

    GetVehicleVelocity(vehicleid, x, y, z);

    vel = floatround(floatsqroot(x*x + y*y + z*z) * 180);

    return vel;
}
stock GetNearVehicle(playerid, Float:radius = 3.0, vehicleid = 0) 
{
	new 
		Float:px, 
		Float:py, 
		Float:pz;

	if (vehicleid != 0)
	{
		if (GetVehiclePos(vehicleid, px, py, pz) && IsPlayerInRangeOfPoint(playerid, radius, px, py, pz) && GetWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) return 1;
		return 0;
	}

	new closet = 0;

	GetPlayerPos(playerid, px, py, pz);
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (i != INVALID_VEHICLE_ID)
		{
			if (GetVehicleDistanceFromPoint(i, px, py, pz) <= radius && GetWorld(playerid) == GetVehicleVirtualWorldEx(i))
			{
				GetVehiclePos(i, px, py, pz);
				closet = i;
			}
		}
	}
	return closet;
}

stock RespawnVehicle(vehicleid, spawned = 0)
{
	new Float: health,
		Float: x,
		Float: y,
		Float: z,
		Float: fa,
		world = veh_vw[vehicleid],
		interior = veh_int[vehicleid];

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, fa);
	GetVehicleHealth(vehicleid, health);

    DestroyObject (VehRadarID [vehicleid]);
    VehRadarID [vehicleid] = -1;
  	CheckingSpeed [vehicleid] = 0;
	
    DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicleid]);

    new
		panels,
		doorss,
		lightss,
		tires;

	GetVehicleDamageStatus(vehicleid, panels, doorss, lightss, tires);
	
	SetVehicleToRespawn(vehicleid);

	if (spawned == 1)
	{
	    SetVehicleVirtualWorld(vehicleid, world);
		LinkVehicleToInterior(vehicleid, interior);
		//SetVehicleVirtualWorldEx(vehicleid, world);
		//SetVehicleInteriorEx(vehicleid, interior);
	    SetVehiclePos(vehicleid, x, y, z);
	    SetVehicleZAngle(vehicleid, fa);
	}
	else
	{
		SetVehicleVirtualWorld(vehicleid, VehicleInfo[vehicleid][carVW]);
		LinkVehicleToInterior(vehicleid, VehicleInfo[vehicleid][carInt]);
		//SetVehicleVirtualWorldEx(vehicleid, VehicleInfo[vehicleid][carVW]);
		//SetVehicleInteriorEx(vehicleid, VehicleInfo[vehicleid][carInt]);
	}

	if (VehicleInfo[vehicleid][carOwnerID] == INVALID_PLAYER_ID)
	    return 1;

	if(OlusumTipGetir(VehicleInfo[vehicleid][carFaction]) == FACTION_POLICE && VehicleInfo[vehicleid][carOwnerID] == INVALID_PLAYER_ID && VehicleInfo[vehicleid][carOwnerID] == 0) {
		for(new j; j < MAX_CAR_WEAPONS; j++) VehicleInfo[vehicleid][carSlotUsed][j] = 0;
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doorss, lightss, tires);
	LoadComp(vehicleid);
	SetVehicleHealth(vehicleid, health);

	if (IsValidDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel])) DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel]);
	return 1;
}

ToggleVehicleLock(vehicleid, bool:toggle)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;

    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

    if (toggle == true)
	{
		SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
		VehicleInfo[vehicleid][carLocked] = 1;
	}
	else
	{
 	   SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
 	   VehicleInfo[vehicleid][carLocked] = 0;
 	}
	return 1;
}

VehicleLight(vehicleid, bool:toggle)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;

	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

	if (toggle == true)	SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
	else				SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);

	return 1;
}

VehicleEngine(vehicleid, bool:toggle)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;

	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

	if (toggle == true)
	{
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
 		VehicleInfo[vehicleid][carEngineOn] = 1;
 	}
	else
	{
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
  		VehicleInfo[vehicleid][carEngineOn] = 0;
 	}
	return 1;
}

ToggleVehicleEngine(vehicleid, playerid)
{
    new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (VehicleInfo[vehicleid][carEngineOn])
	{
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);

		new mes[128];
		format(mes, sizeof(mes), "%s model aracýn motorunu kapattý.", VehicleNames[GetVehicleModel(vehicleid)-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

		format(mes, sizeof(mes), "~w~%s MOTORU ~r~KAPANDI",VehicleNames[GetVehicleModel(vehicleid)-400]);
		GameTextForPlayer(playerid, mes, 2500, 4);

		VehicleInfo[vehicleid][carEngineOn] = false;	
	
		return 1;
	}

	if (VehicleInfo[vehicleid][carOwnerID] && VehicleInfo[vehicleid][carEngine] <= 0.0)		return GameTextForPlayer(playerid, "~r~ARAC CALISMIYOR~n~MOTOR ARIZA LAMBASI YANIYOR!", 3000, 4);
    if (VehicleInfo[vehicleid][carOwnerID] && VehicleInfo[vehicleid][carBattery] <= 0.0)	return GameTextForPlayer(playerid, "~r~ARAC CALISMIYOR~n~AKU ARIZA LAMBASI YANIYOR!", 3000, 4);

	new Float: health;
	AntiCheatGetVehicleHealth(vehicleid, health);

	if (health <= 330.0) return GameTextForPlayer(playerid, "~r~MOTOR HASARLI~w~ OLDUGU ICIN ~y~CALISTIRILAMADI!", 3000, 4);
	   
	else if (health < 390.0 && health > 330.0)
	{
	    SendSyntaxMessage(playerid, "Aracýn motoru bozuk durumda.");
	    SendSyntaxMessage(playerid, "{FFFF00}W {ffffff}tuþuna {FFFF00}10 saniye{ffffff} basýlý tutun ve motorun çalýþmasýný bekleyin..");
        GameTextForPlayer(playerid, "~r~MOTOR HASARLI~w~ OLDUGU ICIN ~y~CALISTIRILAMADI!", 30000, 4);
		SetPVarInt(playerid, #try_engine, 2);
		return 1;
	}
	else if (health < 600.0 && health > 390.0 && random(2) == 0) return GameTextForPlayer(playerid, "~r~CALISTIRILAMADI!", 3000, 4);

	SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);

	new mes[128];
	format(mes, sizeof(mes), "%s model aracýn motorunu çalýþtýrýr.", VehicleNames[GetVehicleModel(vehicleid)-400]);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

	format(mes, sizeof(mes), "~w~%s MOTORU ~g~CALISTI",VehicleNames[GetVehicleModel(vehicleid)-400]);
	GameTextForPlayer(playerid, mes, 2500, 4);

	VehicleInfo[vehicleid][carEngineOn] = true;

	return 1;
}

AlarmOn(vehicle)
{
    if (VehicleInfo[vehicle][carAlarm] < 1) 		return 1;
	if (VehicleInfo[vehicle][carObjectiveTime])	return 1;

    new engine,lights,alarm,doors,bonnet,boot,objective;

    GetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet,boot,objective);
    SetVehicleParamsEx(vehicle,engine,lights,VEHICLE_PARAMS_ON,doors,bonnet,boot,objective);

    if (VehicleInfo[vehicle][carAlarm] < 2) return 1;

	GetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet,boot,objective);
	
	SendFactionMessageF(FACTION_POLICE, COLOR_YELLOWG, "[Araç Alarmý] %s[%s], %s bölgesinde alarm çaldý.", VehicleNames[GetVehicleModel(vehicle)-400], VehicleInfo[vehicle][carPlate], GetVehicleZone(vehicle));

	if (VehicleAlertNote[vehicle] - gettime() < 0) {
		new str_vehalarm[256]; 
		format(str_vehalarm, sizeof(str_vehalarm), "%s model aracýn alarmý tetiklendi.", GetVehicleZone(vehicle));

		VehicleAlertNote[vehicle] = gettime() + 1800;
		CarWanted(vehicle, str_vehalarm);
	}
	
	VehicleInfo[vehicle][carObjectiveTime] = 150;
    VehicleInfo[vehicle][carAlarmTime] = 60;
	SetVehicleParamsEx(vehicle,engine,lights,VEHICLE_PARAMS_ON,doors,bonnet,boot,VEHICLE_PARAMS_ON);

    if (VehicleInfo[vehicle][carAlarm] < 3) return 1;

	new mes[256];
	if (VehicleInfo[vehicle][carAlarm] == 4)	format(mes, sizeof(mes), "Aracýnýzýn alarmý tetiklendi.");
	else format(mes, sizeof(mes), "%s model aracýnýzýn alarmý tetiklendi, Konum: %s.", VehicleNames[GetVehicleModel(vehicle)-400], GetVehicleZone(vehicle));
			
	foreach(new i : Player)
	{
		if (IsPlayerLogged(i) && PlayerInfo[i][pCarKey] == vehicle) return SendSMStoPlayer(i, "9199", "LCSecurity", mes);
	}

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i", VehicleInfo[vehicle][carOwnerID]);
	mysql_tquery(dbHandle, query, "SmsToPlayerOff", "sss", "9199", "LCSecurity", mes); 
	
	return 1;
}

AlarmOff(vehicleid)
{
    VehicleInfo[vehicleid][carObjectiveTime] = 0;
    VehicleInfo[vehicleid][carAlarmTime] = 30;

    new engine,lights,alarm,doors,bonnet,boot,objective;

	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,engine,lights,VEHICLE_PARAMS_OFF,doors,bonnet,boot,VEHICLE_PARAMS_OFF);
	return 1;
}

CarWanted(vehicleid, text[])
{
	VehicleInfo[vehicleid][carWanted] = 1;
	SQL_SetInteger("cars", "wanted", 1, VehicleInfo[vehicleid][carID]);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `Note1`,`Note2`,`Note3`,`Note4`,`Note5` FROM `cars` WHERE `id` = %i", VehicleInfo[vehicleid][carID]);
	mysql_tquery(dbHandle, query); 

	if (!cache_num_rows()) return SQL_SetString("cars", "Note1", text, VehicleInfo[vehicleid][carID]);
	else {
		new notesadd[5];
		for(new i = 0; i < 5; i++) {
			new notei[6];
			format(notei, sizeof(notei), "Note%i", i+1);
			cache_get_value_name(0, notei, notesadd[i]);

			if (CompareStrings(notesadd[i], "None"))
			{
				SQL_SetString("cars", notei, text, VehicleInfo[vehicleid][carID]);
				break;
			}
		}
	}
	return 1;
}

IsPizzaCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == PIZZA_CAR ? 1 : 0;
}

IsTaxiCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == TAXI_CAR ? 1 : 0;
}

IsTrashMasterCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == TRASHMASTER_CAR ? 1 : 0;
}

IsMechanicCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == MECHANIC_CAR ? 1 : 0;
}

IsTruckCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == TRUCK_CAR ? 1 : 0;
}

IsADMVCar(vehicle)
{
	return VehicleInfo[vehicle][carType] == DMV_VEHICLE ? 1 : 0;
}

IsADMVTaxi(vehicle)
{
	return VehicleInfo[vehicle][carType] == DMV_TAXI ? 1 : 0;
}

IsADMVHeli(vehicle)
{
	return VehicleInfo[vehicle][carType] == DMV_HELICOPTER ? 1 : 0;
}

IsRentCar(vehicle)
{
    return VehicleInfo[vehicle][carType] == RENT_CAR ? 1 : 0;
}

IsABicycle(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 481 || model == 509 || model == 510)?(1):(0);
}

IsATowTruck(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 525)?(1):(0);
}

IsAPlane(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 592 || model == 577 || model == 511 || model == 512 || model == 593 || model == 520 || model == 553 || model == 476 || model == 519 || model == 460 || model == 513 || model == 548 || model == 417 || model == 487 ||
	model == 488 || model == 497 || model == 563 || model == 447 || model == 469 )?(1):(0);
}

IsADontTrunk(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 457 || model == 424 || model == 568 || model == 525 || model == 531 || model == 530 || model == 572)?(1):(0);
}

IsAHelicopter(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 548 || model == 425 || model == 417 || model == 487 || model == 488 || model == 497 || model == 563 || model == 447 || model == 469)?(1):(0);
}

IsATaxi(vehicle)
{
	return (GetVehicleModel(vehicle) == 420 || GetVehicleModel(vehicle) == 438)?(1):(0);
}

IsATrashTruck(vehicle)
{
	return (GetVehicleModel(vehicle) == 408)?(1):(0);
}

IsADontWindow(vehicle)
{
	new model = GetVehicleModel(vehicle);
	return (model == 586 || model == 424 || model == 448 || model == 457 || model == 461 || model == 462 || model == 463 || model == 468 || model == 471 || model == 481 || model == 509 || model == 572 || model == 510 || model == 521 || 
	model == 522 || model == 523 || model == 530 || model == 531 || model == 532 || model == 539 || model == 568 || model == 571 ||model == 581 || model == 582 || model == 430 || model == 446 || model == 452 || model == 453 || 
	model == 454 || model == 472 || model == 473 || model == 484 || model == 493 || model == 595)?(1):(0);
}

IsABiker(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	return (model == 522 || model == 521 || model == 461 || model == 463 || model == 581 || model == 448 || model == 586 || model == 523 || model == 468 || model == 471 || model == 462)?(1):(0);
}

IsABoat(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	return (model == 472 || model == 473 || model == 493 || model == 595 || model == 484 || model == 430 || model == 453 || model == 452 || model == 446 || model == 454)?(1):(0);
}

IsDonateVehicle(model)
{
    switch(model)
	{
	    case 424, 568, 495, 541, 411, 490, 522: return 1;
	}
	return 0;
}

IsBronzeVehicle(model)
{
	switch(model)
	{
	    case 424, 568: return 1;
	}
	return 0;
}

IsSilverVehicle(model)
{
	switch(model)
	{
	    case 495, 541: return 1;
	}
	return 0;
}

IsGoldVehicle(model)
{
    switch(model)
	{
	    case 411, 490, 522: return 1;
	}
	return 0;
}

IsABoatModel(model)
{
	return (model == 472 || model == 473 || model == 493 || model == 595 || model == 484 || model == 430 || model == 453 || model == 452 || model == 446 || model == 454)?(1):(0);
}

IsAPlaneModel(model)
{
	return (model == 592 || model == 577 || model == 511 || model == 512 || model == 593 || model == 520 || model == 553 || model == 476 || model == 519 || model == 460 || model == 513 || model == 548 || model == 417 || model == 487 ||
	model == 488 || model == 497 || model == 563 || model == 447 || model == 469 ) ? (1) : (0);
}

/*
IsTruckCar(vehicle)
{
	switch(GetVehicleModel(vehicle))
	{
	    case 403, 514, 515: return 1;
	}
	return 0;
}*/

GetPlayerHasRightTrunk(playerid, vehicleid)
{
	if (!VehicleInfo[vehicleid][carOwnerID]) {
		if (VehicleInfo[vehicleid][carFaction] != 0 && VehicleInfo[vehicleid][carFaction] != PlayerInfo[playerid][pFaction] && PlayerInfo[playerid][pAdmin] == 0)
		{
			return 0;
		}

		if ((VehicleInfo[vehicleid][carType] > 5 && VehicleInfo[vehicleid][carType] < 10 && VehicleInfo[vehicleid][carRent] && GetIDByID(VehicleInfo[vehicleid][carRent]) != playerid) || IsPizzaCar(vehicleid) && PlayerInfo[playerid][pSideJob] != JOB_PIZZA || IsTaxiCar(vehicleid) && PlayerInfo[playerid][pJob] != JOB_TAXI || IsMechanicCar(vehicleid) && PlayerInfo[playerid][pJob] != JOB_MECHANIC || IsTruckCar(vehicleid) && PlayerInfo[playerid][pJob] == JOB_TRUCKER && GetAvailableTruck(playerid, GetVehicleModel(vehicleid) && PlayerInfo[playerid][pAdmin] == 0)) {
			return 0;
		}
	}

	if ((IsAPlane(vehicleid) || IsAHelicopter(vehicleid)) && !IsADMVHeli(vehicleid) && PlayerInfo[playerid][pFlyLic] == 0)
	{
		return 0;
	}

  	if (IsADMVCar(vehicleid) && PlayerInfo[playerid][pCarLic])
	{
		return 0;
	}
	else if (IsADMVHeli(vehicleid) && PlayerInfo[playerid][pFlyLic] == 1)
	{
		return 0;
	}
	else if (IsADMVTaxi(vehicleid) && PlayerInfo[playerid][pTaxiLic] == 1)
	{
		return 0;
	}
	else if (IsADMVTaxi(vehicleid) && PlayerInfo[playerid][pCarLic] == 0)
	{
		return 0;
	}	
	return 1;
}		

GetPlayerHasRightDrive(playerid, vehicleid)
{
	if (!VehicleInfo[vehicleid][carOwnerID] && VehicleInfo[vehicleid][carOwnerID] != INVALID_PLAYER_ID) {
		if (VehicleInfo[vehicleid][carFaction] != 0 && VehicleInfo[vehicleid][carFaction] != PlayerInfo[playerid][pFaction] && PlayerInfo[playerid][pAdmin] == 0)
		{
			SendErrorMessage(playerid, "Bu aracýn anahtarlarý sizde mevcut deðil!");
			RemovePlayerFromVehicle(playerid);
			return 0;
		}

		if ((VehicleInfo[vehicleid][carType] > 5 && VehicleInfo[vehicleid][carType] < 10 && pTemp[playerid][pRentveh] != vehicleid) || IsPizzaCar(vehicleid) && PlayerInfo[playerid][pSideJob] != JOB_PIZZA || IsTaxiCar(vehicleid) && PlayerInfo[playerid][pJob] != JOB_TAXI || IsMechanicCar(vehicleid) && PlayerInfo[playerid][pJob] != JOB_MECHANIC || IsTruckCar(vehicleid) && PlayerInfo[playerid][pJob] == JOB_TRUCKER && GetAvailableTruck(playerid, GetVehicleModel(vehicleid) && PlayerInfo[playerid][pAdmin] == 0)) {
			SendErrorMessage(playerid, "Bu aracýn anahtarlarý sizde mevcut deðil!");
			RemovePlayerFromVehicle(playerid);
			return 0;
		}
	}	

	if ((IsAPlane(vehicleid) || IsAHelicopter(vehicleid)) && !IsADMVHeli(vehicleid) && PlayerInfo[playerid][pFlyLic] == 0)
	{
		SendErrorMessage(playerid, "Bu hava aracýný çalýþtýrmak için gereken lisansýnýz yok!");
        RemovePlayerFromVehicle(playerid);
		return 0;
	}

  	if (IsADMVCar(vehicleid) && PlayerInfo[playerid][pCarLic])
	{
		SendErrorMessage(playerid, "Zaten ehliyetiniz var!");
		RemovePlayerFromVehicle(playerid);
		return 0;
	}
	else if (IsADMVHeli(vehicleid) && PlayerInfo[playerid][pFlyLic] == 1)
	{
		SendErrorMessage(playerid, "Zaten hava aracý lisansýnýz var!");
		RemovePlayerFromVehicle(playerid);
		return 0;
	}
	else if (IsADMVTaxi(vehicleid) && PlayerInfo[playerid][pTaxiLic] == 1)
	{
		SendErrorMessage(playerid, "Zaten taksi lisansýnýz var.");
		RemovePlayerFromVehicle(playerid);
		return 0;
	}
	else if (IsADMVTaxi(vehicleid) && PlayerInfo[playerid][pCarLic] == 0)
	{
		SendErrorMessage(playerid, "Taksi lisansý almanýz için normal ehliyete ihtiyacýnýz var.");
		RemovePlayerFromVehicle(playerid);
		return 0;
	}
	return 1;
}

ModShop_Nearest(playerid)
{
	if (!IsPlayerLogged(playerid)) return -1;

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0 || BizInfo[i][bizType] != BIZ_TUNING) continue;

	    if (PlayerToPoint(15.0,playerid,BizInfo[i][bizPosX], BizInfo[i][bizPosY], BizInfo[i][bizPosZ]) && GetWorld(playerid) == BizInfo[i][bizPosVW] && GetInterior(playerid) == BizInfo[i][bizPosInt]) return i;
	}
	return -1;
}

Dialog:ShowComponentMenu(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)										return 1;

	if (listitem == 2) return SendErrorMessage(playerid, "Bu eklenti pasiftir.");
	ShowComponentMenu2(playerid, vehicle, listitem);
return 1;
}

ShowComponentMenu2(playerid, vehicle, listitem)
{
	new mes[512], str[56];
	new count = 0;

	for(new i; i != max_vehicle_components[listitem]; i++)
	{
		if (vehicle_component[listitem][i][compID] == 0 || IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), vehicle_component[listitem][i][compID]) != 1) continue;
		format(str, sizeof(str), "%s\t$%i\n", GetComponentName(vehicle_component[listitem][i][compID]), vehicle_component[listitem][i][compPrice]);
		strcat(mes, str);
		count++;
   	}

	if (!count)
	{
	    ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Aracýnýz için uygun parça bulunmamaktadýr.");
	}

	SetPVarInt(playerid, #component_type, listitem);
   	Dialog_Show(playerid, SelectModDialog, DIALOG_STYLE_TABLIST, "{33AA33}Araç Modifiyesi", mes, "Seç", "Geri Dön");
	return 1;
}

ShowModMenu(playerid)
{
	new vehicle = GetPlayerVehicleID(playerid);

    if (!vehicle || !IsDriver(playerid))								return SendErrorMessage(playerid, "Sürücü koltuðunda olmanýz gerekmektedir.");
    if (IsABicycle(vehicle))											return Dialog_Show(playerid, ModDialogBike, DIALOG_STYLE_LIST, "{33AA33}Bisiklet Tamiricisi", "Boyama [$100]", "Seç", "Kapat");
	//if (!IsABicycle(vehicle) && !VehicleInfo[vehicle][carRegistered])	return SendErrorMessage(playerid,"Bu araç sisteme kayýtlý deðil.");
	if (!IsABicycle(vehicle) && VehicleInfo[vehicle][carEngineOn])		return SendErrorMessage(playerid, "Aracýnýzda deðiþiklik yapmadan önce motoru durdurmalýsýnýz.");

    new cost = GetVehiclePrice(GetVehicleModel(vehicle));
	static const str_size[] = "Nitro\nPaintjob\nAraç Boyama [$500]\nHidrolik [$8.000]\nXM Radyo [$400]\nGPS [$1500]\nAraç Motoru Deðiþtirme [$%i]\nAraç Aküsü Deðiþtirme[$%i]\nÝmmobilizer Tak [$300]\nEkstralar\nModifiye Parçalarý Tak\nModifiyeyi Sil";
	new mes[sizeof(str_size) - 4 + 1 + 24];
	
	format(mes, sizeof(mes), str_size, cost / 100 * 10, cost / 100 * 5);
	Dialog_Show(playerid, ModDialog, DIALOG_STYLE_LIST, "{33AA33}Araç Modifiyesi", mes, "Seç", "Kapat");
	return 1;
}

SetVehicleInteriorEx(vehicleid, interior)
{
    veh_int[vehicleid] = interior;
	return LinkVehicleToInterior(vehicleid, interior);
}

GetVehicleInteriorEx(vehicleid)
{
	if (!IsValidVehicle(vehicleid)) return INVALID_VEHICLE_ID;
	return veh_int[vehicleid];
}

SetVehicleVirtualWorldEx(vehicleid, world)
{
    veh_vw[vehicleid] = world;
	return SetVehicleVirtualWorld(vehicleid, world);
}

GetVehicleVirtualWorldEx(vehicleid)
{
	if (!IsValidVehicle(vehicleid)) return INVALID_VEHICLE_ID;
	return veh_vw[vehicleid];
}

stock GetVehicleOwner(vehicleid)
{
	new playerid = VehicleInfo[vehicleid][carOwnerPlayer];
	if(playerid == INVALID_PLAYER_ID) return INVALID_PLAYER_ID;

	if(IsPlayerLogged(playerid) && PlayerInfo[playerid][pID] == VehicleInfo[vehicleid][carOwnerID]) return playerid;
	return INVALID_PLAYER_ID;
}

IsVehicleInRangeOfPoint(vehicleid, Float: radius, Float: x, Float: y, Float: z)
{
	return (GetVehicleDistanceFromPoint(vehicleid, x, y, z) <= radius)?(1):(0);
}

IsNearTrunk(vehicle, playerid, Float: dist = 4.0)
{
	if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))
		return 0;
	
	new Float: x, Float: y, Float: z;
    GetVehicleBoot(vehicle, x, y, z);

    if (GetPlayerDistanceFromPoint(playerid, x, y, z) > dist) return 0;
	
	return 1;
}

VehicleHasDoors(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 400..424, 426..429, 431..440, 442..445, 451, 455, 456, 458, 459, 466, 467, 470, 474, 475, 477..480, 482, 483, 486, 489, 490..492, 494..496, 498..500, 502..508, 514..518, 524..529, 533..536, 540..547, 549..552, 554..562, 565..568, 573, 575, 576, 578..580, 582, 585, 587..589, 596..605, 609:
			return 1;
	}
	return 0;
}

CountPlayerVehicles(playerid)
{
	new 
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `cars` WHERE `owner` = %i", PlayerInfo[playerid][pID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
    
	cache_get_value_int(0, "total", count);
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}

this::Vh_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	new query[256];

	//for(new x = 0; x < MAX_VEHICLES; x++)
	//{
	//	if (VehicleInfo[x][eVehicleDBID] == PlayerInfo[playerid][pOwnedVehicles][i+1])
	//	return SendErrorMessage(playerid, "That vehicle's already spawned.");
	//}
	
	if (playertextid == SpawnVeh_Arrows[playerid][0]) //right
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM cars WHERE owner = %i AND impound = 0 AND jacking = 0 AND id > %i LIMIT 1", PlayerInfo[playerid][pID], GetPVarInt(playerid, #spawnveh_id));
		mysql_tquery(dbHandle, query, "Query_ShowVehicleList", "i", playerid);
    }
	else if (playertextid == SpawnVeh_Arrows[playerid][1]) //left
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM cars WHERE owner = %i AND impound = 0 AND jacking = 0 AND id < %i ORDER BY `id` DESC LIMIT 1", PlayerInfo[playerid][pID], GetPVarInt(playerid, #spawnveh_id));
		mysql_tquery(dbHandle, query, "Query_ShowVehicleList", "i", playerid);
    }
	else if (playertextid == SpawnVeh_Model[playerid]) //spawn
    {
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `owner` = %i AND impound = 0 AND jacking = 0 AND `id` = %i LIMIT 1", PlayerInfo[playerid][pID], GetPVarInt(playerid, #spawnveh_id));
		mysql_tquery(dbHandle, query, "OnPlayerSpawnVehicle", "i", playerid);
	}
	return 1;
}

stock ShowVehicleList(playerid)
{
	PlayerTextDrawShow(playerid, SpawnVeh_Model[playerid]);
	PlayerTextDrawShow(playerid, SpawnVeh_Box[playerid]);
	for(new i = 0; i < 2; i++) PlayerTextDrawShow(playerid, SpawnVeh_Arrows[playerid][i]);
	for(new e = 0; e < 3; e++) PlayerTextDrawShow(playerid, SpawnVeh_Base[playerid][e]);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM cars WHERE owner = %i AND impound = 0 AND jacking = 0 LIMIT 1", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "Query_ShowVehicleList", "ii", playerid, CountPlayerVehicles(playerid));

	return 1;
}

//#define COLOR_TEST 0xEC9F0EFF

this::Query_ShowVehicleList(playerid, idx)
{
	if (!cache_num_rows()) return 1;

	new 
		vehicleModel,
		vehicleColor1,
		vehicleColor2
	;

	new id;
	cache_get_value_int(0, "id", id);
	
	SetPVarInt(playerid, #spawnveh_id, id);

	cache_get_value_int(0, "model", vehicleModel);
	cache_get_value_int(0, "color1", vehicleColor1);
	cache_get_value_int(0, "color2", vehicleColor2);
	
	new str[64];
    format(str, sizeof(str), "%s", VehicleNames[vehicleModel-400]);
    PlayerTextDrawSetString(playerid, SpawnVeh_Base[playerid][0], str);
    
    PlayerTextDrawSetPreviewModel(playerid, SpawnVeh_Model[playerid], vehicleModel);
    PlayerTextDrawSetPreviewVehCol(playerid, SpawnVeh_Model[playerid], vehicleColor1, vehicleColor2);

	PlayerTextDrawShow(playerid, SpawnVeh_Model[playerid]);

	SelectTextDraw(playerid, 0xEC9F0EFF);
	return 1;
}

NewScrambleWord(playerid)
{
	new vehid = GetPlayerVehicleID(playerid);
	pTemp[playerid][pUnscrambleID] = random(sizeof(UnscrambleInfo));
		
	switch(VehicleInfo[vehid][carImmob])
	{
		case 0: JackingEngine[playerid] = 125;
		case 1: JackingEngine[playerid] = 100;
		case 2: JackingEngine[playerid] = 75;
		case 3: JackingEngine[playerid] = 50;
		case 4: JackingEngine[playerid] = 25;
	}

	return 1;
}

StopJackingEngine(playerid) 
{
	RemovePlayerFromVehicle(playerid);
	JackingEngine[playerid] = 0;
	pTemp[playerid][pUnscrambleID] = 0;
	pTemp[playerid][pScrambleFailed] = 0;
	pTemp[playerid][pScrambleSuccess] = 0;

	InfoMSG(playerid, "ARAC ~r~DUZ KONTAK ISLEMI ~w~BASARISIZ!", 3);

	return 1;
}


LeaveMission(playerid)
{
	InfoMSG(playerid, "~r~ISLEM IPTAL EDILDI!", 3);

	PlayerInfo[playerid][InMission] = MISSION_NONE;
	PlayerInfo[playerid][MissionTime] = 0;
	PlayerInfo[playerid][MissionTarget][0] = 0;
	PlayerInfo[playerid][MissionTarget][1] = 0;
	
	return 1;
}

StopJackingLock(playerid, x = 1) 
{
	VehicleInfo[JackingVehicle[playerid]][ePhysicalAttack] = false;
	DestroyDynamic3DTextLabel(VehicleInfo[JackingVehicle[playerid]][eVehicleLabel]);
	VehicleInfo[JackingVehicle[playerid]][vCooldown] = false;
	
	JackingVehicle[playerid] = 0;
	pTemp[playerid][JackingType] = 0;
	JackingLock[playerid] = 0;
	pTemp[playerid][JackingWarnings] = 0;
						
	if (x) InfoMSG(playerid, "ARAC ~r~KIRMA ISLEMI ~w~BASARISIZ!", 3);

	return 1;
}

this::DELETE_VEHICLE(playerid, response)
{
	new model = GetPVarInt(playerid, #RansomVehModel),
		vehid = GetPVarInt(playerid, #RansomVehID);
		
	DeletePVar(playerid, #RansomVehModel);
	DeletePVar(playerid, #RansomVehID);

	if (!response) return 1;
	
	new query[256];

	format(query, sizeof(query), "%s [IP: %s] %s aracýný sildi", GetName(playerid), PlayerInfo[playerid][pID], VehicleNames[model-400]);
	insert_log(query, VEHICLE_LOG, 4, PlayerInfo[playerid][pAccID]);

	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `tickets` WHERE `vehicle` = %i", vehid);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", vehid);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "%s baþarýyla silindi!", VehicleNames[model-400]);
	return 1;
}

IsPlayerInFrontVDoor(playerid, vehid) {
	new Float:ccX, Float:ccY, Float:ccZ;
	new Float:dX, Float:dY, Float:dZ;

	GetVehicleModelInfo(VehicleInfo[vehid][carModel], VEHICLE_MODEL_INFO_FRONTSEAT, ccX, ccY, ccZ);
	GetVehicleRelativePos(vehid, dX, dY, dZ, -ccX - 0.5, ccY, ccZ);
	if (!IsPlayerInRangeOfPoint(playerid, 1.2, dX, dY, dZ)) 	return 0;
	else 													return 1;
}

GetVehicleRelativePos(vehicleid, &Float:x, &Float:y, &Float:z, Float:xoff= 0.0, Float:yoff= 0.0, Float:zoff= 0.0)
{
    new Float:rot;
    GetVehicleZAngle(vehicleid, rot);
    rot = 360 - rot;
    GetVehiclePos(vehicleid, x, y, z);
    x = floatsin(rot, degrees) * yoff + floatcos(rot, degrees) * xoff + x;
    y = floatcos(rot, degrees) * yoff - floatsin(rot, degrees) * xoff + y;
    z = zoff + z;

    return 1;
}

this::OnCoolDown(vehicleid)
{
    VehicleInfo[vehicleid][vCooldown] = false;
}

IsWindowOpened(vehicleid)
{
    new wi_state[4];

	GetVehicleParamsCarWindows(vehicleid, wi_state[0], wi_state[1], wi_state[2], wi_state[3]);
	if (!wi_state[0]) return true;
	else 			 return false;
}

//Panels
decode_panels(panels, &front_left_panel, &front_right_panel, &rear_left_panel, &rear_right_panel, &windshield, &front_bumper, &rear_bumper)
{
    front_left_panel = panels & 15;
    front_right_panel = panels >> 4 & 15;
    rear_left_panel = panels >> 8 & 15;
    rear_right_panel = panels >> 12 & 15;
    windshield = panels >> 16 & 15;
    front_bumper = panels >> 20 & 15;
    rear_bumper = panels >> 24 & 15;
}
/*encode_panels(front_left_panel, front_right_panel, rear_left_panel, rear_right_panel, windshield, front_bumper, rear_bumper)
{
    return front_left_panel | (front_right_panel << 4) | (rear_left_panel << 8) | (rear_right_panel << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}*/
 
//Doors
decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door, &behind_driver_door, &behind_passenger_door)
{
    bonnet = doors & 7;
    boot = doors >> 8 & 7;
    driver_door = doors >> 16 & 7;
    passenger_door = doors >> 24 & 7;
	behind_driver_door = doors >> 32 & 7;
	behind_passenger_door = doors >> 40 & 7;
}
/*encode_doors(bonnet, boot, driver_door, passenger_door)
{
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}*/

encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door)
{
   // #pragma unused behind_driver_door
   // #pragma unused behind_passenger_door

    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24) | (behind_driver_door << 32) | (behind_passenger_door << 40);
}

 
//Lights
decode_lights(lights, &front_left_light, &front_right_light, &back_lights)
{
    front_left_light = lights & 1;
    front_right_light = lights >> 2 & 1;
    back_lights = lights >> 6 & 1;
}
/*encode_lights(front_left_light, front_right_light, back_lights)
{
    return front_left_light | (front_right_light << 2) | (back_lights << 6);
}*/
 
//Tires
decode_tires(tires, &rear_right_tire, &front_right_tire, &rear_left_tire, &front_left_tire)
{
    rear_right_tire = tires & 1;
    front_right_tire = tires >> 1 & 1;
    rear_left_tire = tires >> 2 & 1;
    front_left_tire = tires >> 3 & 1;
}
/*encode_tires(rear_right_tire, front_right_tire, rear_left_tire, front_left_tire)
{
	return rear_right_tire | (front_right_tire << 1) | (rear_left_tire << 2) | (front_left_tire << 3);
}*/

GetVehicleStatus(playerid, &dmg_panel, &dmg_door, &dmg_light, &dmg_tire)
{
	new vehicle = GetPlayerVehicleID(playerid);
	if (!vehicle) 	return 1;

	new panels, doors, lights, tires,
		panel[7], door[6], light[3], tire[4];

	GetVehicleDamageStatus(vehicle, panels, doors, lights, tires);
			
	decode_panels(panels, panel[0], panel[1], panel[2], panel[3], panel[4], panel[5], panel[6]);
	decode_doors(doors, door[0], door[1], door[2], door[3], door[4], door[5]);
	decode_lights(lights, light[0], light[1], light[2]);
	decode_tires(tires, tire[0], tire[1], tire[2], tire[3]);

	for(new i; i < sizeof(panels); i++) if (panel[i]) 	dmg_panel++; 
	for(new i; i < sizeof(door); i++) 	if (door[i]) 	dmg_door++; 
	for(new i; i < sizeof(light); i++) 	if (light[i]) 	dmg_light++; 
	for(new i; i < sizeof(tire); i++)	if (tire[i]) 	dmg_tire++; 

	dmg_panel = 	floatround(dmg_panel*100/sizeof(panel), floatround_ceil);
	dmg_door =		floatround(dmg_door*100/sizeof(door), floatround_ceil);
	dmg_light =		floatround(dmg_light*100/sizeof(light), floatround_ceil);
	dmg_tire = 		floatround(dmg_tire*100/sizeof(tire), floatround_ceil);

	return 1;
}

this::RepairAll(playerid, response)
{
    if (!response)    return 1;
	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);
	
	new
		vehicle = GetPlayerVehicleID(playerid),
		carfaction = VehicleInfo[vehicle][carFaction],
		bizid = PAS_Nearest(playerid)
	;

    if (IsFactionLegal(carfaction))                                 return FixVehicle(vehicle), SendServerMessage(playerid, "Aracý tamir ettirdin ve faturasý hükümete yazýldý.");
    if (VehicleInfo[vehicle][carType] != 0)                         return FixVehicle(vehicle), SendServerMessage(playerid, "Aracý 150 dolar karþýlýðýnda tamir ettirdin."), GiveCash(playerid, -150);
	if (bizid == -1)												return SendErrorMessage(playerid, "Yakýnýnýzda araç tamirhanesi bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])							return SendErrorMessage(playerid, "Araç tamirini baþlatmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])									return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Araç tamirhanesinde gerekli parçalar bulunmuyor.");
	
	new Float: health;
	AntiCheatGetVehicleHealth(GetPlayerVehicleID(playerid), health);

	new panels, doors, lights, tires;
	GetVehicleStatus(playerid, panels, doors, lights, tires);

	new
		model = GetVehicleModel(vehicle),
		hp_cost = floatround((100 - ((health/GetVehicleMaxHealth(model))*100)) * (GetVehiclePrice(model)/1000), floatround_ceil),
		cost = floatround(GetVehiclePrice(model) / 100, floatround_ceil)
	;

	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Tamir için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	StartVehicleUpgrade(playerid, vehicle, 13, cost);
	return 1;
}

this::RepairList(playerid, response)
{
    if (!response)    return 1;
	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);
	
	new
		vehicle = GetPlayerVehicleID(playerid),
		bizid = PAS_Nearest(playerid)
	;

	if (bizid == -1)												return SendErrorMessage(playerid, "Yakýnýnýzda araç tamirhanesi bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])							return SendErrorMessage(playerid, "Araç tamirini baþlatmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])									return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Araç tamirhanesinde gerekli parçalar bulunmuyor.");

	new panels, doors, lights, tires;
	GetVehicleStatus(playerid, panels, doors, lights, tires);

	new cost = GetPVarInt(playerid, #auto_cost);

	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Tamir için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	StartVehicleUpgrade(playerid, vehicle, 14, cost);
	return 1;
}

this::RepairHP(playerid, response)
{
    if (!response)    return 1;
	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);
	
	new
		vehicle = GetPlayerVehicleID(playerid),
		bizid = PAS_Nearest(playerid)
	;

	if (bizid == -1)												return SendErrorMessage(playerid, "Yakýnýnýzda araç tamirhanesi bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])							return SendErrorMessage(playerid, "Araç tamirini baþlatmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])									return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Araç tamirhanesinde gerekli parçalar bulunmuyor.");
	
	new Float: health;
	AntiCheatGetVehicleHealth(GetPlayerVehicleID(playerid), health);

	new panels, doors, lights, tires;
	GetVehicleStatus(playerid, panels, doors, lights, tires);

	new
		model = GetVehicleModel(vehicle),
		hp_cost = floatround((100 - ((health/GetVehicleMaxHealth(model))*100)) * (GetVehiclePrice(model)/1000), floatround_ceil)
	;

	if (GetCash(playerid) < hp_cost)	return SendErrorMessage(playerid, "Tamir için yeterli paranýz bulunmuyor, gereken: $%i", hp_cost);

	StartVehicleUpgrade(playerid, vehicle, 13, hp_cost);
	return 1;
}

this::ChangeBattery(playerid, response)
{
    if (!response)    return 1;
	
	new
		vehicle = GetPlayerVehicleID(playerid),
		bizid = PAS_Nearest(playerid)
	;

	if (bizid == -1)												return SendErrorMessage(playerid, "Yakýnýnýzda araç tamirhanesi bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])							return SendErrorMessage(playerid, "Araç tamirini baþlatmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])									return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Araç tamirhanesinde gerekli parçalar bulunmuyor.");

	new cost = GetVehiclePrice(GetVehicleModel(vehicle)) / 100 * 5;

	if (cost < 1)					return 1;
	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Akü tamiri için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Tamir için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	StartVehicleUpgrade(playerid, vehicle, 11, cost);
	return 1;
}

this::ChangeEngine(playerid, response)
{
    if (!response)    return 1;
	
	new
		vehicle = GetPlayerVehicleID(playerid),
		bizid = PAS_Nearest(playerid)
	;

	if (bizid == -1)												return SendErrorMessage(playerid, "Yakýnýnýzda araç tamirhanesi bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])							return SendErrorMessage(playerid, "Araç tamirini baþlatmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])									return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Araç tamirhanesinde gerekli parçalar bulunmuyor.");

	new cost = GetVehiclePrice(GetVehicleModel(vehicle)) / 100 * 10;

	if (cost < 1) 					return 1;
	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Motor tamiri için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Tamir için yeterli paranýz bulunmuyor, gereken: $%i", cost);

	StartVehicleUpgrade(playerid, vehicle, 9, cost);
	return 1;
}

this::ConfirmFilling(playerid, response)
{
    if (!response)    return 1;

	new vehicle = GetPlayerVehicleID(playerid), bizid;

	if (!IsDriver(playerid))					return SendNotInVehicle(playerid);
	if ((bizid = AZC_Nearest(playerid)) == -1)	return SendErrorMessage(playerid, "Yakýnýnýzda benzin istasyonu bulunmuyor.");
	if (VehicleInfo[vehicle][carEngineOn])		return SendErrorMessage(playerid, "Yakýt doldurmak için motoru kapatmalýsýnýz.");
	if (BizInfo[bizid][bizLocked])				return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);
	
    if (BizInfo[bizid][bizOwnerID] && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Benzin istasyonunda yeterli yakýt yok.");
	
	SendSyntaxMessage(playerid, "Yakýt doldurmayý durdurmak için: /benzin");

	SetPVarInt(playerid, #UsePump, bizid+1);
	RefuelTimer[playerid] = SetTimerEx("Refuel", 350, true, "iii", playerid, vehicle, bizid);
	return 1;
}

this::Refuel(playerid, vehicleid, bizid)
{
    new price, Float: f_price,  modelid = GetVehicleModel(vehicleid);
	
	if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'P') 	  f_price = float(BizInfo[bizid][bizEntrance]) * 1.2 * 0.5;
	else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'E') f_price = float(BizInfo[bizid][bizEntrance]) * 0.8 * 0.5;
	else f_price = float(BizInfo[bizid][bizEntrance]) * 0.5;
	
	price = floatround(f_price, floatround_ceil);
    if (GetPlayerMoney(playerid) < price)
    {
        Fuel_ResetPlayer(playerid);
        ToggleVehicleEngine(vehicleid, playerid);
        return SendNotCash(playerid);
    }
 
    SetPVarFloat(playerid, #FuelBought, GetPVarFloat(playerid, #FuelBought) + 0.5);
    VehicleInfo[vehicleid][carFuel] += 0.5;
	GiveCash(playerid, -price);
	GiveBizCash(bizid, price);
 
    new string[120];
    format(string, sizeof(string), "~b~~h~Yakit dolduruluyor ...~n~~n~~w~Ucret: ~g~~h~$%d ~y~~h~(%.2fL)", floatround(GetPVarFloat(playerid, #FuelBought) * float(price)), GetPVarFloat(playerid, #FuelBought));
    PlayerTextDrawSetString(playerid, FuelText[playerid], string);
	PlayerTextDrawShow(playerid, FuelText[playerid]);
 
    if (VehicleInfo[vehicleid][carFuel] > GetVehicleFuelCapacity(modelid))
    {
        VehicleInfo[vehicleid][carFuel] = GetVehicleFuelCapacity(modelid);
        Fuel_ResetPlayer(playerid);
        ToggleVehicleEngine(vehicleid, playerid);
    }
 
    return 1;
}

stock GetPlayerNameBySqlID(sqlid)
{
    new name[MAX_PLAYER_NAME] = "Yok", query[43 + 11 + 1], Cache:search;

    mysql_format(dbHandle, query, sizeof(query), "SELECT name FROM users WHERE id = '%d'", sqlid);
    search = mysql_query(dbHandle, query);

    if(cache_num_rows())
    {
        cache_get_value(0, "name", name);
    }

    cache_delete(search);
    search = MYSQL_INVALID_CACHE;

    return name;
}

GetVehicleNameS(vehicleid)
{
	new
		modelid = GetVehicleModel(vehicleid),
		name[32];

	if(400 <= modelid <= 611)
	    strcat(name, modelNames[modelid - 400]);
	else
	    name = "Bilinmeyen";

	return name;
}

AracSayiKontrol(playerid)
{
	new __sayi=0, Float:pPos[3];
	GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
	for(new i;i<MAX_VEHICLES;i++)
	{
	    if(!IsValidVehicle(i)) continue;
	    if(IsVehicleInRangeOfPoint(i, 4.5, pPos[0], pPos[1], pPos[2]) && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(i))
		{
			__sayi++;
		}
	}
	if(__sayi == 1) return 1;
	return 0;
}

stock BumpTierBlowout(vehicleid)
{
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, encode_tires(1, 1, 1, 1));
	return 1;
}

encode_tires(tire1, tire2, tire3, tire4) return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);