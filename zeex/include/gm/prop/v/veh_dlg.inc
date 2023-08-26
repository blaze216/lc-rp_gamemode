Dialog:DuplicateKey(playerid, response, listitem, inputtext[])
{
	if (!response)																			return 1;
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))										return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
	if (VehicleInfo[PlayerInfo[playerid][pCarKey]][carOwnerID] != PlayerInfo[playerid][pID])	return 1;

    static const str_size[] = "{ffffff}%s için anahtarlar kopyalandý. Tipi {C3C3C3}[ID/Ýsim] {ffffff}kopyalanan anahtarlarý kime vermek istiyorsunuz?";
	new mes[sizeof(str_size) - 2 + 1 + 32];

	format(mes, sizeof(mes), str_size, VehicleNames[GetVehicleModel(PlayerInfo[playerid][pCarKey])-400]);

    new userid;

	if (sscanf(inputtext, "u", userid))
	{
	    Dialog_Show(playerid, DuplicateKey, DIALOG_STYLE_INPUT, "{FFFFFF}Anahtarlarý Kopyala", mes, "Satýn Al", "Ýptal");
	    return SendErrorMessage(playerid, "Oyuncu ID'si giriniz.");
	}

	if (!IsPlayerLogged(userid) || userid == playerid)
	{
	    Dialog_Show(playerid, DuplicateKey, DIALOG_STYLE_INPUT, "{FFFFFF}Anahtarlarý Kopyala", mes, "Satýn Al", "Ýptal");
		return SendNotConnected(playerid);
	}

	if (!PlayerNearPlayer(7.0, playerid, userid))
	{
	    Dialog_Show(playerid, DuplicateKey, DIALOG_STYLE_INPUT, "{FFFFFF}Anahtarlarý Kopyala", mes, "Satýn Al", "Ýptal");
		return SendNotNearPlayer(playerid);
	}
	
	PlayerInfo[userid][pSpareKey] = VehicleInfo[PlayerInfo[playerid][pCarKey]][carID];
	SendSyntaxMessage(playerid, "Kopyalanan anahtarlar %s tarafýndan oluþturuldu ve %s oyuncusuna verildi.", VehicleNames[GetVehicleModel(PlayerInfo[playerid][pCarKey])-400], GetNameEx(userid));
    SendSyntaxMessage(userid, "%s, %s adlý kiþiden anahtarlarýn bir kopyasýný satýn aldý. (/anahtarat - aracýn anahtarýný yere atarsýnýz)", GetNameEx(playerid), VehicleNames[GetVehicleModel(PlayerInfo[playerid][pCarKey])-400]);
	return 1;
}

Dialog:ScrapSell(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new veh = PlayerInfo[playerid][pCarKey], string1[128], mes[32];

	if (IsABicycle(veh)) format(mes, sizeof(mes), "%s", VehicleNames[VehicleInfo[veh][carModel]-400]);

	else
	{
		if (VehicleInfo[veh][carRegistered])	format(mes, sizeof(mes), "{FFFFFF}%s [%s]", VehicleNames[VehicleInfo[veh][carModel]-400], VehicleInfo[veh][carPlate]);
		else								format(mes, sizeof(mes), "{FFFFFF}%s", VehicleNames[VehicleInfo[veh][carModel]-400]);
	}

	format(string1, sizeof(string1), "{FFFFFF}Bu aracý $%i karþýlýðýnda satmak istediðinizden emin misiniz?", GetVehiclePrice(VehicleInfo[veh][carModel])/2);
	Dialog_Show(playerid, ScrapVehicle, DIALOG_STYLE_MSGBOX, mes, string1, "Evet", "Hayýr");
	return 1;
}

Dialog:ScrapVehicle(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new veh = PlayerInfo[playerid][pCarKey];

        SendSyntaxMessage(playerid, "Aracýn \"%s\" $%i karþýlýðýnda sattýnýz.", VehicleNames[VehicleInfo[veh][carModel]-400], GetVehiclePrice(VehicleInfo[veh][carModel])/2);
		GiveCash(playerid,  GetVehiclePrice(VehicleInfo[veh][carModel])/2);

        new query[256], money = PlayerInfo[playerid][pCash];

		format(query, sizeof(query), "%s [MYSQL: %i | IP: %s | Money(WAS): %i | Money(BECOME): %i] sold the car %s(Model: %i) for -- $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money,
		GetCash(playerid), VehicleNames[VehicleInfo[veh][carModel]-400], VehicleInfo[veh][carModel], GetVehiclePrice(VehicleInfo[veh][carModel])/2);
	    insert_log(query, VEHICLE_LOG, 3, PlayerInfo[playerid][pAccID]);

		DeleteVehicleTickets(veh);

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `cars` WHERE `id` = %i", VehicleInfo[veh][carID]);
		mysql_tquery(dbHandle, query);

		PlayerInfo[playerid][pCarKey] = 0;
		VehicleInfo[veh][carOwnerPlayer] = INVALID_PLAYER_ID;
		DestroyVehicleEx(veh);
	}
	return 1;
}

Dialog:BuyingVehicleList(playerid, response, listitem, inputtext[])
{
	if (response)	ShowBuyingVehicleDetails(playerid);
	else
	{
	    new registerveh 	= price_reg[GetPVarInt(playerid, "BuyingVehicleRegister")],
			alarmveh 		= price_alarm[GetPVarInt(playerid, "BuyingVehicleAlarm")],
			lockveh 		= price_lock[GetPVarInt(playerid, "BuyingVehicleLock")],
			immobveh 		= price_immob[GetPVarInt(playerid, "BuyingVehicleImmob")],
			insuranceveh 	= GetInsurancePrice(GetPVarInt(playerid, "BuyingVehicleModel")) * GetPVarInt(playerid, "BuyingVehicleInsurance"),
			xmradioveh 		= price_radio[GetPVarInt(playerid, "BuyingVehicleRadio")],
			gpsveh 			= price_gps[GetPVarInt(playerid, "BuyingVehicleGps")];

    	new mes[56];

		format(mes, sizeof(mes), "{FFFFFF}%s - {35B835}$%i", VehicleNames[GetPVarInt(playerid, "BuyingVehicleModel")-400], GetVehiclePrice(GetPVarInt(playerid, "BuyingVehicleModel"))+registerveh+alarmveh+lockveh+immobveh+insuranceveh+xmradioveh+gpsveh);
		Dialog_Show(playerid, BuyingVehicleDone, DIALOG_STYLE_MSGBOX, mes, "{FFFFFF}Bu aracý satýn almak istediðinizden emin misiniz?", "Satýn Al", "Ýptal");
	}
	return 1;
}

Dialog:BuyingVehicleDone(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new query[256];
   	mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `cars` WHERE `owner` = %i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "BuyVehicleForPlayer", "i", playerid);
	return 1;
}

Dialog:RansomVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) {
		DeletePVar(playerid, #RansomVehModel);
		DeletePVar(playerid, #RansomVehID);
		return 1;
	}

	Dialog_Show(playerid, RansomVehicle2, DIALOG_STYLE_LIST, "Kullaným seçenekleri", "Aracý kullan\nAracýmý sil", "Seç", "<<");
	return 1;
}
Dialog:RansomVehicle2(playerid, response, listitem, inputtext[])
{
	if (!response) {
		DeletePVar(playerid, #RansomVehModel);
		DeletePVar(playerid, #RansomVehID);
		return 1;
	}

	if (listitem == 0)
	{
		new model = GetPVarInt(playerid, #RansomVehModel),
			vehid = GetPVarInt(playerid, #RansomVehID);

		DeletePVar(playerid, #RansomVehModel);
		DeletePVar(playerid, #RansomVehID);

		new price = floatround(GetVehiclePrice(model)*0.5);
		if (GetCash(playerid) < price)	return SendNotCash(playerid);

		SendSyntaxMessage(playerid, "%s'nizi $%i karþýlýðýnda satýn aldýnýz.", VehicleNames[model-400], price);
		SQL_SetInteger("cars", "jacking", 0, vehid);
		GiveCash(playerid, -price);
	} else {
		new mes[128];
		format(mes, sizeof(mes), "{FFFFFF}Aracýnýz %s {FF6347}onayýnýz{FFFFFF} ile birlikte silenecek, onaylýyor musunuz?", GetVehName(pTemp[playerid][MyCars][listitem]));
		ConfirmDialog(playerid, "Araç imha onayý", mes, "DELETE_VEHICLE");
	}
	return 1;
}

Dialog:MyCars(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	if (IsValidVehicle(PlayerInfo[playerid][pCarKey]) && pTemp[playerid][MyCarSpawn][listitem])
		return pc_cmd_aracmenu(playerid, "");
	else
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))
		{
			pTemp[playerid][MyCarSpawn][0] = listitem;

			new dlgmes[88];
			format(dlgmes, sizeof(dlgmes), "{FFFFFF} %s model aracýnýzý spawn etmek istiyor musunuz?", GetVehName(pTemp[playerid][MyCars][listitem]));
			ConfirmDialog(playerid, "Doðrulama", dlgmes, "MyCarsSpawn");
		}
		else
		{
			SendErrorMessage(playerid, "Baþka bir aracý spawnlamadan önce spawnlanmýþ araçlarýnýzý park etmelisiniz.");
			pc_cmd_araclarim(playerid, "");
		}
	}

	return 1;
}

Dialog:BuyingVehicleDetails(playerid, response, listitem, inputtext[])
{
	new registerveh = price_reg[GetPVarInt(playerid, "BuyingVehicleRegister")],
		alarmveh = price_alarm[GetPVarInt(playerid, "BuyingVehicleAlarm")],
		lockveh = price_lock[GetPVarInt(playerid, "BuyingVehicleLock")],
		immobveh = price_immob[GetPVarInt(playerid, "BuyingVehicleImmob")],
		insuranceveh = GetInsurancePrice(GetPVarInt(playerid, "BuyingVehicleModel")) * GetPVarInt(playerid, "BuyingVehicleInsurance"),
		xmradioveh = price_radio[GetPVarInt(playerid, "BuyingVehicleRadio")], gpsveh = price_gps[GetPVarInt(playerid, "BuyingVehicleGps")];

	new registeruse[128], lockuse[128], alarmuse[250], immobuse[260], insuranceuse[260], xmradiouse[128], gpsuse[128];

	if (GetPVarInt(playerid, "BuyingVehicleRegister"))			format(registeruse, sizeof(registeruse), "{ffffff}Sisteme kayýt: \t{ecc317}$%i\n{ecc317}+ {ffffff}Araç plseviye.\n\n", registerveh);

	if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 1)			format(alarmuse, sizeof(alarmuse), "{ffffff}Alarm: \t{bab9ba}1 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Yüksek sesli alarm\n\n", alarmveh);
	else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 2)	format(alarmuse, sizeof(alarmuse), "{ffffff}Alarm: \t{bab9ba}2 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Yüksek sesli alarm\n{ecc317}+ {ffffff}Polis ihbarý.\n\n", alarmveh);
	else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 3)	format(alarmuse, sizeof(alarmuse), "{ffffff}Alarm: \t{bab9ba}3 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Yüksek sesli alarm\n{ecc317}+ {ffffff}Polis ihbarý.\n{ecc317}+ {ffffff}SMS bildirimi\n\n", alarmveh);
	else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 4)	format(alarmuse, sizeof(alarmuse), "{ffffff}Alarm: \t{bab9ba}4 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Yüksek sesli alarm\n{ecc317}+ {ffffff}Polis ihbarý.\n{ecc317}+ {ffffff}Hýrsýzlýk bildirimi araç sahibine bildirilir ve fatura bilgisi gelir.\n\n", alarmveh);

	if (GetPVarInt(playerid, "BuyingVehicleLock") > 0)			format(lockuse, sizeof(lockuse), "{ffffff}Kilit: \t\t\t{bab9ba}%i seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}%i seconds lock picking vehicle.\n\n", GetPVarInt(playerid, "BuyingVehicleLock"), lockveh, 250 + (GetPVarInt(playerid, "BuyingVehicleLock") * 250));

	if (GetPVarInt(playerid, "BuyingVehicleImmob") > 0)			format(immobuse, sizeof(immobuse), "{ffffff}immobilizer: \t{bab9ba}%i seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Kontak anahtarýnýn kýrýlmasýný önlemeye yardýmcý olur.\n\n", GetPVarInt(playerid, "BuyingVehicleImmob"), immobveh);

	if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 1)		format(insuranceuse, sizeof(insuranceuse), "{ffffff}Sigorta: \t\t{bab9ba}1 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr\n\n", insuranceveh);
	else if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 2)	format(insuranceuse, sizeof(insuranceuse), "{ffffff}Sigorta: \t\t{bab9ba}2 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr\n{ecc317}+ {ffffff}Araç hasarlý doðmayacaktýr.\n\n", insuranceveh);
	else if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 3)	format(insuranceuse, sizeof(insuranceuse), "{ffffff}Sigorta: \t\t{bab9ba}3 seviye \t{ecc317}$%i\n{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr\n{ecc317}+ {ffffff}Araç hasarlý doðmayacaktýr.\n{ecc317}+ {ffffff}Modifiyeniz ve radyonuz sigorta tarafýndan karþýlanacaktýr.\n\n", insuranceveh);


	if (GetPVarInt(playerid, "BuyingVehicleRadio") == 1)	format(xmradiouse, sizeof(xmradiouse), "{ffffff}XM Radyo: \t{ecc317}$%i\n{ecc317}+ {ffffff}Radyo ve ses sisteminin diðer bileþenlerinin kurulumu..\n\n", xmradioveh);

	if (GetPVarInt(playerid, "BuyingVehicleGps") == 1) 	format(gpsuse, sizeof(gpsuse), "{ffffff}GPS: \t\t{ecc317}$%i\n{ecc317}+ {ffffff}Araca GPS kurulseviye\n\n", gpsveh);

	new mes[56];

	format(mes, sizeof(mes), "{ffffff}%s - {35B835}$%i", VehicleNames[GetPVarInt(playerid, "BuyingVehicleModel")-400], GetVehiclePrice(GetPVarInt(playerid, "BuyingVehicleModel"))+registerveh+alarmveh+lockveh+immobveh+insuranceveh+xmradioveh+gpsveh);
	if (!response)
	{
		new vehFuel[32],
			vehDrive[32],
			modelid = GetPVarInt(playerid, "BuyingVehicleModel"),
			Float:vehMass = GetVehicleModelInfoAsFloat(modelid, "fMass");

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

		new string[sizeof(str_size) + 1228];

		format(string, sizeof(string), str_size,
            FormatNumber(GetVehiclePrice(modelid)),
            GetVehicleMaxSpeed[modelid-400],
            GetVehicleMaxHealth(modelid),
            vehMass,
            vehDrive,
            vehFuel,
            GetVehicleFuelUsage(modelid),
            GetVehicleFuelCapacity(modelid),
			VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color1)] >>> 8, GetPVarInt(playerid, #veh_color1),
			VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color2)] >>> 8, GetPVarInt(playerid, #veh_color2)
		);

		format(string, sizeof(string), "%s{ecc317}Renk 1{ffffff} - [{%06x}#%i{ffffff}]\n{ecc317}Renk 2{ffffff} - [{%06x}#%i{ffffff}]\n\n", string, VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color1)] >>> 8, GetPVarInt(playerid, #veh_color1), VehicleColoursTableRGBA[GetPVarInt(playerid, #veh_color2)] >>> 8, GetPVarInt(playerid, #veh_color2));
		format(string, sizeof(string), "%s%s%s%s%s%s%s%s\n{ffffff}'{ecc317}Ödeme Yap{ffffff}' butonuna týklayarak aracý satýn alabilirsin.", string, lockuse, alarmuse, immobuse, insuranceuse, registeruse, xmradiouse, gpsuse);

		Dialog_Show(playerid, BuyingVehicleList, DIALOG_STYLE_MSGBOX, mes, string, "Düzenle", "Ödeme Yap");
	    return 1;
	}

	new string[301];
	switch(listitem)
	{
		case 0:
		{
				if (GetPVarInt(playerid, "BuyingVehicleRegister") == 0)		format(string, sizeof(string), "{eaf133}>> {ffffff}Ekli Deðil\nDMV kayýt - $%i", price_reg[1]);
				else if (GetPVarInt(playerid, "BuyingVehicleRegister") == 1)	format(string, sizeof(string), "{ffffff}Ekli Deðil\n{eaf133}>> {ffffff}DMV kayýt - $%i", price_reg[1]);

				Dialog_Show(playerid, BuyVehDetReg, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 1:
		{
				if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 0)			format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\n1 seviye alarm- $%i\n2 seviye alarm- $%i\n3 seviye alarm- $%i\n4 seviye alarm- $%i", price_alarm[1], price_alarm[2], price_alarm[3], price_alarm[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 1)	format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}1 seviye alarm- $%i\n2 seviye alarm- $%i\n3 seviye alarm- $%i\n4 seviye alarm- $%i", price_alarm[1], price_alarm[2], price_alarm[3], price_alarm[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 2)	format(string, sizeof(string), "Ekli Deðil\n1 seviye alarm- $%i\n{ecc317}» {ffffff}2 seviye alarm- $%i\n3 seviye alarm- $%i\n4 seviye alarm- $%i", price_alarm[1], price_alarm[2], price_alarm[3], price_alarm[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 3)	format(string, sizeof(string), "Ekli Deðil\n1 seviye alarm- $%i\n2 seviye alarm- $%i\n{ecc317}» {ffffff}3 seviye alarm- $%i\n4 seviye alarm- $%i", price_alarm[1], price_alarm[2], price_alarm[3], price_alarm[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleAlarm") == 4)	format(string, sizeof(string), "Ekli Deðil\n1 seviye alarm- $%i\n2 seviye alarm- $%i\n3 seviye alarm- $%i\n{ecc317}» {ffffff}4 seviye alarm- $%i", price_alarm[1], price_alarm[2], price_alarm[3], price_alarm[4]);

				Dialog_Show(playerid, BuyVehDetAlarm, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 2:
		{
				if (GetPVarInt(playerid, "BuyingVehicleLock") == 0)		format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\n1 seviye kilit - $%i\n2 seviye kilit - $%i\n3 seviye kilit - $%i\n4 seviye kilit - $%i\n5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);
				else if (GetPVarInt(playerid, "BuyingVehicleLock") == 1)	format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}1 seviye kilit - $%i\n2 seviye kilit - $%i\n3 seviye kilit - $%i\n4 seviye kilit - $%i\n5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);
				else if (GetPVarInt(playerid, "BuyingVehicleLock") == 2)	format(string, sizeof(string), "Ekli Deðil\n1 seviye kilit - $%i\n{ecc317}» {ffffff}2 seviye kilit - $%i\n3 seviye kilit - $%i\n4 seviye kilit - $%i\n5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);
				else if (GetPVarInt(playerid, "BuyingVehicleLock") == 3)	format(string, sizeof(string), "Ekli Deðil\n1 seviye kilit - $%i\n2 seviye kilit - $%i\n{ecc317}» {ffffff}3 seviye kilit - $%i\n4 seviye kilit - $%i\n5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);
				else if (GetPVarInt(playerid, "BuyingVehicleLock") == 4)	format(string, sizeof(string), "Ekli Deðil\n1 seviye kilit - $%i\n2 seviye kilit - $%i\n3 seviye kilit - $%i\n{ecc317}» {ffffff}4 seviye kilit - $%i\n5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);
				else if (GetPVarInt(playerid, "BuyingVehicleLock") == 5)	format(string, sizeof(string), "Ekli Deðil\n1 seviye kilit - $%i\n2 seviye kilit - $%i\n3 seviye kilit - $%i\n4 seviye kilit - $%i\n{ecc317}» {ffffff}5 seviye kilit - $%i", price_lock[1], price_lock[2], price_lock[3], price_lock[4], price_lock[5]);

				Dialog_Show(playerid, BuyVehDetLock, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 3:
		{
				if (GetPVarInt(playerid, "BuyingVehicleImmob") == 0)			format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\n1 seviye immobilizer - $%i\n2 seviye immobilizer - $%i\n3 seviye immobilizer - $%i\n4 seviye immobilizer - $%i", price_immob[1], price_immob[2], price_immob[3], price_immob[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleImmob") == 1)	format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}1 seviye immobilizer - $%i\n2 seviye immobilizer - $%i\n3 seviye immobilizer - $%i\n4 seviye immobilizer - $%i", price_immob[1], price_immob[2], price_immob[3], price_immob[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleImmob") == 2)	format(string, sizeof(string), "Ekli Deðil\n1 seviye immobilizer - $%i\n{ecc317}» {ffffff}2 seviye immobilizer - $%i\n3 seviye immobilizer - $%i\n4 seviye immobilizer - $%i", price_immob[1], price_immob[2], price_immob[3], price_immob[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleImmob") == 3)	format(string, sizeof(string), "Ekli Deðil\n1 seviye immobilizer - $%i\n2 seviye immobilizer - $%i\n{ecc317}» {ffffff}3 seviye immobilizer - $%i\n4 seviye immobilizer - $%i", price_immob[1], price_immob[2], price_immob[3], price_immob[4]);
				else if (GetPVarInt(playerid, "BuyingVehicleImmob") == 4)	format(string, sizeof(string), "Ekli Deðil\n1 seviye immobilizer - $%i\n2 seviye immobilizer - $%i\n3 seviye immobilizer - $%i\n{ecc317}» {ffffff}4 seviye immobilizer - $%i");

				Dialog_Show(playerid, BuyVehDetImmob, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 4:
		{
			    new amount = GetInsurancePrice(GetPVarInt(playerid, "BuyingVehicleModel"));

				if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 0)			format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\n1 seviye sigorta - $%i\n2 seviye sigorta - $%i\n3 seviye sigorta - $%i", amount * 1, amount * 2, amount * 3);
				else if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 1)	format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}1 seviye sigorta - $%i\n2 seviye sigorta - $%i\n3 seviye sigorta - $%i", amount * 1, amount * 2, amount * 3);
				else if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 2)	format(string, sizeof(string), "Ekli Deðil\n1 seviye sigorta - $%i\n{ecc317}» {ffffff}2 seviye sigorta - $%i\n3 seviye sigorta - $%i", amount * 1, amount * 2, amount * 3);
				else if (GetPVarInt(playerid, "BuyingVehicleInsurance") == 3)	format(string, sizeof(string), "Ekli Deðil\n1 seviye sigorta - $%i\n2 seviye sigorta - $%i\n{ecc317}» {ffffff}3 seviye sigorta - $%i", amount * 1, amount * 2, amount * 3);

				Dialog_Show(playerid, BuyVehDetInsur, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 5:
		{
				if (GetPVarInt(playerid, "BuyingVehicleRadio") == 0)			format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\nXM Radyo - $%i", price_radio[1]);
				else if (GetPVarInt(playerid, "BuyingVehicleRadio") == 1)	format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}XM Radyo - $%i", price_radio[1]);

				Dialog_Show(playerid, BuyVehDetRadio, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 6:
		{
				if (GetPVarInt(playerid, "BuyingVehicleGps") == 0)			format(string, sizeof(string), "{ecc317}» {ffffff}Ekli Deðil\nGPS - $%i", price_gps[1]);
				else if (GetPVarInt(playerid, "BuyingVehicleGps") == 1)		format(string, sizeof(string), "Ekli Deðil\n{ecc317}» {ffffff}GPS - $%i", price_gps[1]);

				Dialog_Show(playerid, BuyVehDetGPS, DIALOG_STYLE_LIST, mes, string, "Seç", "<<");
		}
		case 7:
		{
			SendSyntaxMessage(playerid, "Lütfen {ffc46a}ilk rengi{FFFFFF} seçin.");

			new colors[256];

			for(new i; i != 256; i++)
			{
				colors[i] = i;
			}
			SetPVarInt(playerid, #veh_color_type, 1);
			ShowColorSelectionMenu(playerid, MODEL_BUING_COLOR, colors, sizeof(colors));
		}
	}
	return 1;
}

Dialog:BuyVehDetGPS(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleGps", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetRadio(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleRadio", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetInsur(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleInsurance", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetImmob(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleImmob", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetLock(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleLock", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetAlarm(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleAlarm", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:BuyVehDetReg(playerid, response, listitem, inputtext[])
{
	if (response) SetPVarInt(playerid, "BuyingVehicleRegister", listitem);

	ShowBuyingVehicleDetails(playerid);
	return 1;
}

Dialog:VehFastAccess(playerid, response, listitem, inputtext[])
{
	if (!response) 										return 1;
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Bir araç kullanýyor olmalýsýn.");

	switch(listitem)
	{
		case 0: pc_cmd_motor(playerid, "");
		case 1: pc_cmd_arac(playerid, "kilit");
		case 2: pc_cmd_farlar(playerid, "");
		case 3: pc_cmd_bagaj(playerid, "");
		case 4: pc_cmd_kaput(playerid, "");
		case 5: pc_cmd_camlar(playerid, "1");
		case 6: pc_cmd_radyoayarla(playerid, "");
		case 7:	pc_cmd_ahe(playerid, "");
		case 8: pc_cmd_aracmenu(playerid, "");
	}

	return 1;
}

Dialog:VehMenu(playerid, response, listitem, inputtext[])
{
	if (!response) 										return 1;
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

	new vehicle = PlayerInfo[playerid][pCarKey];
	if (!vehicle || VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID]) return 1;

	switch(listitem)
	{
	    case 0: pc_cmd_arac(playerid, "bilgi");
		case 1: pc_cmd_arac(playerid, "cezalar");
	    case 2: pc_cmd_arac(playerid, "park");
		case 3:	pc_cmd_arac(playerid, "bul");
		case 4: pc_cmd_alarmkapat(playerid, "");
		case 5: pc_cmd_arac(playerid, "sistemesat");
		case 6: Dialog_Show(playerid, SellVehTo, DIALOG_STYLE_INPUT, "Araç satýþ", "{ffffff}Aþaðýda belirtilen formata uygun þekilde yazýnýz: {C3C3C3}[ID / isim] [satýþ fiyatý]\nÖrnek: 1 35000", "Sat", "Ýptal");
	}
	return 1;
}

Dialog:SellVehTo(playerid, response, listitem, inputtext[])
{
	if (!response)										return pc_cmd_aracmenu(playerid, "");
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

	new vehicle = GetPlayerVehicleID(playerid);

	if (!vehicle)														return 1;
	if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");

    new userid, price;

	if (sscanf(inputtext, "ui", userid, price))
	{
	    Dialog_Show(playerid, SellVehTo, DIALOG_STYLE_INPUT, "Araç satýþ", "{ffffff}Aþaðýda belirtilen formata uygun þekilde yazýnýz: {C3C3C3}[ID / isim] [satýþ fiyatý]\nÖrnek: 1 35000", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "Geçersiz format.");
	}

	if (!IsPlayerLogged(userid))
	{
	    Dialog_Show(playerid, SellVehTo, DIALOG_STYLE_INPUT, "Araç satýþ", "{ffffff}Aþaðýda belirtilen formata uygun þekilde yazýnýz: {C3C3C3}[ID / isim] [satýþ fiyatý]\nÖrnek: 1 35000", "Sat", "Ýptal");
		return SendNotConnected(playerid);
	}

	if (!PlayerNearPlayer(7.0, playerid, userid))
	{
	    Dialog_Show(playerid, SellVehTo, DIALOG_STYLE_INPUT, "Araç satýþ", "{ffffff}Aþaðýda belirtilen formata uygun þekilde yazýnýz: {C3C3C3}[ID / isim] [satýþ fiyatý]\nÖrnek: 1 35000", "Sat", "Ýptal");
		return SendNotNearPlayer(playerid);
	}

	if (price < 0 || price > 100000000)
	{
	    Dialog_Show(playerid, SellVehTo, DIALOG_STYLE_INPUT, "Araç satýþ", "{ffffff}Aþaðýda belirtilen formata uygun þekilde yazýnýz: {C3C3C3}[ID / isim] [satýþ fiyatý]\nÖrnek: 1 35000", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "Satýþ fiyatýný bu kadar yüksek yazamazsýnýz.");
	}

	new str[32];
	format(str, sizeof(str), "sat %i %i", userid, price);
	pc_cmd_arac(playerid, str);
	return 1;
}

Dialog:SelectClass(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	switch(listitem)
	{
		case 0: ShowBclass(playerid);
		case 1: ShowLowriders(playerid);
		case 2: ShowAclass(playerid);
		case 3: ShowSport(playerid);
		case 4: ShowPickups(playerid);
		case 5: ShowOffRoad(playerid);
		case 6: ShowIndustrial(playerid);
		case 7: ShowMotoBike(playerid);
		case 8: ShowOther(playerid);
		case 9: ShowDonate(playerid);
	}
	return 1;
}

Dialog:Autoservice(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);

	new Float: health;
	AntiCheatGetVehicleHealth(GetPlayerVehicleID(playerid), health);

	new panels, doors, lights, tires;
	GetVehicleStatus(playerid, panels, doors, lights, tires);

	new
		vehicle = GetPlayerVehicleID(playerid),
		model = GetVehicleModel(vehicle),
		hp_cost = 1 + floatround((100 - ((health/GetVehicleMaxHealth(model))*100)) * (GetVehiclePrice(model)/1000), floatround_ceil)
	;
	if (hp_cost < 0) hp_cost = 0;
	new
		cost = 1 + floatround(GetVehiclePrice(model) / 100, floatround_ceil),
		common_cost = hp_cost +  floatround((cost * 0.5 * panels/100) + (cost * 0.25 * doors/100) + (cost * 0.1 * lights/100) + (cost * 0.15 * tires/100), floatround_ceil)
	;


		if(strfind(inputtext, "Komple Tamir", true) != -1)
		{
			if (common_cost <= 0)	return pc_cmd_giris(playerid, "");
			static const dlgstr[] = "{FFFFFF}Aracýnýzý {1b8922}$%i{FFFFFF} karþýlýðýnda tamamen onarmak istediðinizden emin misiniz?";
			new mes[sizeof(dlgstr)+6];

			format(mes, sizeof(mes), dlgstr, cost);

			ConfirmDialog(playerid, "Doðrulama", mes, "RepairAll");
		}
		else if(strfind(inputtext, "Parça Tadilatý", true) != -1)
		{
			new panel_cost = floatround((cost * 0.5 * panels/100), floatround_ceil),
				door_cost = floatround((cost * 0.25 * doors/100), floatround_ceil),
				light_cost = floatround((cost * 0.1 * lights/100), floatround_ceil),
				tire_cost = floatround((cost * 0.15 * tires/100), floatround_ceil);

			if (panel_cost+door_cost+light_cost+tire_cost<=0)	return pc_cmd_giris(playerid, "");

			static const dlgstr[] = "Tamir seçenekleri aþaðýda belirtilmiþtir:\n\
									{C5C5C5}[ - ]{FFFFFF} Gövde bölgesi tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n\
									{C5C5C5}[ - ]{FFFFFF} Kapý tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n\
									{C5C5C5}[ - ]{FFFFFF} Far tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n\
									{C5C5C5}[ - ]{FFFFFF} Lastik tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n\
									{C5C5C5} >> TAMÝRAT >>";
			new mes[526+8*4];

			format(mes, sizeof(mes), dlgstr,
				panel_cost, panels,
				door_cost, doors,
				light_cost, lights,
				tire_cost, tires
			);

			for(new i; i < 4; i++) pTemp[playerid][pListed][i] = 0;
			Dialog_Show(playerid, SELECT_Autoservice, DIALOG_STYLE_TABLIST_HEADERS, "Araç Tamiri", mes, "Seç", "Ýptal");
		}
		else if(strfind(inputtext, "Araç Mekanik & Elektrik", true) != -1)
		{
			if (hp_cost == 0)	return pc_cmd_giris(playerid, "");
			static const dlgstr[] = "{FFFFFF}Aracýn genel durumunu {1b8922}$%i{FFFFFF} karþýlýðýnda tamir etmek istediðinizden emin misiniz?";
			new mes[sizeof(dlgstr)+6];

			format(mes, sizeof(mes), dlgstr, hp_cost);

			ConfirmDialog(playerid, "Doðrulama", mes, "RepairHP");
		}
		else if(strfind(inputtext, "Akü Tamiri", true) != -1)
		{
			if (VehicleInfo[vehicle][carBattery] >= 20.0)	{
				pc_cmd_giris(playerid, "");
				return SendErrorMessage(playerid, "Bu aracýn aküsünün onarýma ihtiyacý yoktur.( > 20%%).");
			}
			static const dlgstr[] = "{FFFFFF}Araç aküsünü {1b8922}$%i{FFFFFF} karþýlýðýnda deðiþtirmek istediðinizden emin misiniz?";
			new mes[sizeof(dlgstr)+6];

			format(mes, sizeof(mes), dlgstr, floatround(GetVehiclePrice(model) / 100 * 5, floatround_ceil));

			ConfirmDialog(playerid, "Doðrulama", mes, "ChangeBattery");
		}
		else if(strfind(inputtext, "Motor Tamiri", true) != -1)
		{
			if (VehicleInfo[vehicle][carEngine] >= 20.0)	{
				pc_cmd_giris(playerid, "");
				return SendErrorMessage(playerid, "Bu aracýn motorunun tamire ihtiyacý yoktur. ( > 20%%).");
			}
			static const dlgstr[] = "{FFFFFF}{1b8922}$%i{FFFFFF} için araç motorunu  tamir etmek istediðinizden emin misiniz?";
			new mes[sizeof(dlgstr)+6];

			format(mes, sizeof(mes), dlgstr, floatround(GetVehiclePrice(model) / 100 * 10, floatround_ceil));

			ConfirmDialog(playerid, "Doðrulama", mes, "ChangeEngine");
		}

	return 1;
}


Dialog:SELECT_Autoservice(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_giris(playerid, "");

	new panels, doors, lights, tires;
	GetVehicleStatus(playerid, panels, doors, lights, tires);

	new vehicle = GetPlayerVehicleID(playerid),
		model = GetVehicleModel(vehicle),
		cost = floatround(GetVehiclePrice(model) / 100, floatround_ceil),
		panel_cost = floatround((cost * 0.5 * panels/100), floatround_ceil),
		door_cost = floatround((cost * 0.25 * doors/100), floatround_ceil),
		light_cost = floatround((cost * 0.1 * lights/100), floatround_ceil),
		tire_cost = floatround((cost * 0.15 * tires/100), floatround_ceil);

	if (listitem == 4) {
		new count;
		for(new i; i < 4; i++) if (pTemp[playerid][pListed][i]) count++;

		if (count) {
			count = 0;

			if (pTemp[playerid][pListed][0]) count += panel_cost;
			if (pTemp[playerid][pListed][1]) count += door_cost;
			if (pTemp[playerid][pListed][2]) count += light_cost;
			if (pTemp[playerid][pListed][3]) count += tire_cost;

			if (count) {
				static const dlgstr[] = "{FFFFFF}Aracýnýzý {1b8922}$%i{FFFFFF} karþýlýðýnda tamir ettirmek istediðinizden emin misiniz?";
				new mes[sizeof(dlgstr)+6];

				SetPVarInt(playerid, #auto_cost, count);

				format(mes, sizeof(mes), dlgstr, count);
				return ConfirmDialog(playerid, "Doðrulama", mes, "RepairList");
			}
		}
	}

	if (!pTemp[playerid][pListed][listitem]) 	pTemp[playerid][pListed][listitem] = 1;
	else 										pTemp[playerid][pListed][listitem] = 0;

	if (listitem == 0 && !panel_cost)		pTemp[playerid][pListed][listitem] = 0;
	else if (listitem == 1 && !door_cost)	pTemp[playerid][pListed][listitem] = 0;
	else if (listitem == 2 && !light_cost)	pTemp[playerid][pListed][listitem] = 0;
	else if (listitem == 3 && !tire_cost)	pTemp[playerid][pListed][listitem] = 0;

	static const select[] = "{FFFF00}[ X ]{FFFFFF}";
	static const unselect[] = "{C5C5C5}[ - ]{FFFFFF}";

	new mes[526 + 8*4] = "Tamir seçeneði:\n";

	if (pTemp[playerid][pListed][0]) format(mes, sizeof(mes), "%s%s Gövde bölgesi tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, select, panel_cost, panels);
	else							format(mes, sizeof(mes), "%s%s Gövde bölgesi tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, unselect, panel_cost, panels);

	if (pTemp[playerid][pListed][1]) format(mes, sizeof(mes), "%s%s Kapý tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, select, door_cost, doors);
	else							format(mes, sizeof(mes), "%s%s Kapý tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, unselect, door_cost, doors);

	if (pTemp[playerid][pListed][2]) format(mes, sizeof(mes), "%s%s Far tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, select, light_cost, lights);
	else							format(mes, sizeof(mes), "%s%s Far tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, unselect, light_cost, lights);

	if (pTemp[playerid][pListed][3]) format(mes, sizeof(mes), "%s%s Lastik tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, select, tire_cost, tires);
	else							format(mes, sizeof(mes), "%s%s Lastik tamiri: {1b8922}$%i {c5c5c5}(Hasar: {FF6347}%i%%{c5c5c5})\n", mes, unselect, tire_cost, tires);

	format(mes, sizeof(mes), "%s{C5C5C5} >> TAMÝRAT >>", mes);
	Dialog_Show(playerid, SELECT_Autoservice, DIALOG_STYLE_TABLIST_HEADERS, "Araç Tamiri", mes, "Seç", "Ýptal");
	return 1;
}


Dialog:ModDialog(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)										return 1;

	if (listitem == 0)
	{
	    if (IsABicycle(vehicle) || IsABiker(vehicle) || IsATaxi(vehicle))	return SendErrorMessage(playerid, "Bu komut bisikletler, motosikletler ve taksiler için mevcut deðildir.");

	    if (IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), 1008) != 1 && IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), 1009) != 1 && IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), 1010) != 1)
		{
		    ShowModMenu(playerid);
			return SendErrorMessage(playerid, "Bu araca nitro yüklemezsiniz.");
		}

        Dialog_Show(playerid, NitroDialog, DIALOG_STYLE_TABLIST, "{33AA33}Araç Modifiyesi", "Nitro x2\t$4.500\nNitro x5\t$9.000\nNitro x10\t$15000", "Seç", "Geri Dön");
		return 1;
	}

	else if (listitem == 1)
	{
	    if (!IsVehiclePaintJob(GetVehicleModel(vehicle)))	return SendErrorMessage(playerid, "Bu araç için paintjob yapýlamýyor.");

		new mes[128];

		for(new i; i != IsVehiclePaintJob(GetVehicleModel(vehicle)); i++)
		{
			format(mes, sizeof(mes), "%s\nPaintjob %i", mes, i+1);
	    }

	    Dialog_Show(playerid, PaintjobDialog, DIALOG_STYLE_LIST, "{33AA33}Fiyat: $3.000", mes, "Seç", "Geri Dön");
	    return 1;
	}

	else if (listitem == 2)
	{
	    new colors[256];

     	for(new i; i != 256; i++)
		{
      		colors[i] = i;
		}

		ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR, colors, sizeof(colors));
	    SetPVarInt(playerid, #veh_color1, -1);
	    SetPVarInt(playerid, #veh_color_type, 2);
	    return 1;
	}

	else if (listitem == 3)
	{
	    if (IsABicycle(vehicle) || IsABiker(vehicle) || IsATaxi(vehicle))	return SendErrorMessage(playerid, "Bu komut bisikletler, motosikletler ve taksiler için mevcut deðildir.");

	    if (VehicleInfo[vehicle][carComponent][CARMODTYPE_HYDRAULICS])
		{
		    ShowModMenu(playerid);
			return SendErrorMessage(playerid, "Hidroliði zaten kurdunuz.");
		}
	    Dialog_Show(playerid, HydralicConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyesi", "{FFFFFF}8.000$'a hidroliði kurmak istiyor musunuz?", "Evet", "Geri");
		return 1;
	}

	else if (listitem == 4)
	{
	    if (IsABicycle(vehicle) || IsABiker(vehicle) || IsATaxi(vehicle))	return SendErrorMessage(playerid, "Bu komut bisikletler, motosikletler ve taksiler için mevcut deðildir.");

		if (VehicleInfo[vehicle][carRadio])
		{
		    ShowModMenu(playerid);
			return SendErrorMessage(playerid, "Aracýnýzda zaten bir radyo var.");
		}

		Dialog_Show(playerid, RadioConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyesi", "{FFFFFF}400$'a radyoyu kurmak istiyor musunuz?", "Evet", "Geri");
	    return 1;
	}
	else if (listitem == 5)
	{
		if (VehicleInfo[vehicle][carGps])
		{
		    ShowModMenu(playerid);
			return SendErrorMessage(playerid, "Zaten GPS'niz mevcut.");
		}

		Dialog_Show(playerid, GPSConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyesi", "{FFFFFF}1.500$'a GPS kurmak istiyor musunuz?", "Evet", "Geri");
	    return 1;
	}
	else if (listitem == 6)
	{
		new cost = GetVehiclePrice(GetVehicleModel(vehicle)) / 100 * 10;

		if (cost < 1) 					return 1;
		if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Motoru deðiþtirmenin maliyeti $%i'dir.", cost);

		StartVehicleUpgrade(playerid, vehicle, 9, cost);
		return 1;
	}
	else if (listitem == 7)
	{
		new cost = GetVehiclePrice(GetVehicleModel(vehicle)) / 100 * 5;

		if (cost < 1)					return 1;
		if (GetCash(playerid) < cost)	return SendErrorMessage(playerid, "Akü deðiþtirmenin maliyeti $%i'dir.", cost);

		StartVehicleUpgrade(playerid, vehicle, 11, cost);
		return 1;
	}
	else if (listitem == 8)
	{
		Dialog_Show(playerid, ChangeLock, DIALOG_STYLE_MSGBOX, "{33AA33}Kilit Deðiþtirme", "{FFFFFF}Kilidi 300$ karþýlýðýnda deðiþtirmek istediðinize emin misiniz?\nVerdiðiniz tüm yedek anahtarlar geçersiz olacaktýr.", "Evet", "Geri");
	    return 1;
	}
	else if (listitem == 9)
	{
	    static const str_size[] = "1. Kilit\t[%i seviye]\n2. Alarm\t[%i seviye]\n3. Immobilizer\t[%i seviye]\n4. Sigorta\t[%i seviye]\n5. Zýrh\t[%.0f HP]";
		new mes[sizeof(str_size) - 18 + 1 + 48];

		format(mes, sizeof(mes), str_size, VehicleInfo[vehicle][carLock], VehicleInfo[vehicle][carAlarm], VehicleInfo[vehicle][carImmob], VehicleInfo[vehicle][carInsurance], VehicleInfo[vehicle][carArmour]);
  		Dialog_Show(playerid, VehUpgrade, DIALOG_STYLE_TABLIST, "{FFFFFF}Araç Geliþtirme ", mes, "Seç", "Geri Dön");
		return 1;
	}
	else if (listitem == 10)
	{
		 if (IsABicycle(vehicle) || IsATaxi(vehicle)) return SendErrorMessage(playerid, "Bu komut bisikletler, motosikletler ve taksiler için mevcut deðildir. ");
		 new mes[512] = "Tekerlekler\nSpoiler\n{ab2a20}Pasif\nÇatý\nYan Etekler\nEgzoz\nÖn Tampon\nArka Tampon";
		 Dialog_Show(playerid, ShowComponentMenu, DIALOG_STYLE_LIST, "{33AA33}Araç Modifiyesi", mes, "Seç", "Geri Dön");
	}
	else if (listitem == 11)
	{
	    if (IsABicycle(vehicle) || IsABiker(vehicle) || IsATaxi(vehicle)) return SendErrorMessage(playerid, "Bu komut bisikletler, motosikletler ve taksiler için mevcut deðildir. ");

		new mes[512] = "{FFFFFF}Jantlarý {33AA33}Kaldýr\n{FFFFFF}Rüzgarlýk {33AA33}Kaldýr\n{FFFFFF}Air {33AA33}Kaldýr\n{FFFFFF}Çatý {33AA33}Kaldir\n{FFFFFF}Yan Etek {33AA33}Kaldýr\n{FFFFFF}Egzoz {33AA33}Kaldýr\n{FFFFFF}Ön Tampon {33AA33}Kaldýr\n{FFFFFF}Arka Tampon {33AA33}Kaldir\n{FFFFFF}Nitro {33AA33}Kaldýr\n{FFFFFF}Paintwork {33AA33}Kaldir\n{FFFFFF}Hidrolik {33AA33}Kaldýr\n{FFFFFF}Radyo {33AA33}Kaldýr";
	    Dialog_Show(playerid, DeleteTuning, DIALOG_STYLE_LIST, "{33AA33}Modifiyeyi Sil", mes, "Seç", "Geri Dön");
	    return 1;
	}
	return 1;
}

Dialog:ModDialogBike(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;

	if (listitem == 0)
	{
	    new colors[256];

     	for(new i; i != 256; i++)
		{
      		colors[i] = i;
		}

		ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR, colors, sizeof(colors));
	    SetPVarInt(playerid, #veh_color1, -1);
	    SetPVarInt(playerid, #veh_color_type, 1);
	    return 1;
	}
	return 1;
}

Dialog:BuyVehArmour(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;

	new amount = strval(inputtext);

    if (amount < 10 || amount > 250)
	{
	    Dialog_Show(playerid, BuyVehArmour, DIALOG_STYLE_INPUT, "{FFFFFF}Araç Zýrhý", "{ffffff}Satýn almak istediðiniz zýrh miktarýný 10 - 250 girin [1 birim 10$'dýr]:", "Buy", "Geri Dön");
	    return SendErrorMessage(playerid, "{FFFFFF}miktar 10 ile 250 arasýnda olmalýdýr.");
	}

    if (VehicleInfo[vehicle][carArmour] + amount > 250.0)
	{
	    Dialog_Show(playerid, BuyVehArmour, DIALOG_STYLE_INPUT, "{FFFFFF}Araç Zýrhý", "{ffffff}Satýn almak istediðiniz zýrh miktarýný 10 - 250 girin [1 birim 10$'dýr]:", "Buy", "Geri Dön");
	    return SendErrorMessage(playerid, "Sadece %.0f kadar zýrh satýn alabilirsin..", 250.0 - VehicleInfo[vehicle][carArmour]);
	}

	if (GetCash(playerid) < amount * 10)
	{
	    Dialog_Show(playerid, BuyVehArmour, DIALOG_STYLE_INPUT, "{FFFFFF}Araç Zýrhý", "{ffffff}Satýn almak istediðiniz zýrh miktarýný 10 - 250 girin [1 birim 10$'dýr]:", "Buy", "Geri Dön");
 		return SendErrorMessage(playerid, "Zýrhýn fiyatý $%i.", amount * 10);
	}

	StartVehicleUpgrade(playerid, vehicle, 6, 10 * amount, amount);
	FreezePlayer(playerid);
	return 1;
}

Dialog:BuyVehInsurance(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowModMenu(playerid);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)										return 1;

    new cost = GetInsurancePrice(GetVehicleModel(vehicle));

    if (!cost)										return SendErrorMessage(playerid, "Bu araç için sigorta yapýlmamaktadýr.");
    if (!VehicleInfo[vehicle][carRegistered])		return SendErrorMessage(playerid, "Bu araç sisteme kayýtlý deðil.");

	new level = strval(inputtext);

	if (level < 1 || level > 3)						return SendErrorMessage(playerid, "Sigorta seviyesi 1'den 3'e kadardýr.");
	if (VehicleInfo[vehicle][carInsurance] >= level)	return SendErrorMessage(playerid, "Zaten %i sigorta seviyeniz var.", VehicleInfo[vehicle][carInsurance]);
	if (GetCash(playerid) < cost * level)			return SendNotCash(playerid);

	StartVehicleUpgrade(playerid, vehicle, 5, cost * level, level);
	return 1;
}

Dialog:VehUpgrade(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;

    if (listitem == 3)
	{
	    new cost = GetInsurancePrice(GetVehicleModel(vehicle));

	    if (!cost)	return SendErrorMessage(playerid, "Bu araç için sigorta yapýlmamaktadýr.");

	    new mes[590] = "{ffffff}1 seviye \t- $%i\n{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr.\n\n{ffffff}2 seviye \t- $%i\n\
		{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr.\n{ecc317}+ {ffffff}Araçlar tam can ile spawnlanýr.\n\n{ffffff}3 seviye \t- $%i\n";

	    strcat(mes, "{ecc317}+ {ffffff}Araçlar her zaman tamir edilmiþ þekilde býrakýlýr.\n{ecc317}+ {ffffff}Araçlar tam can ile spawnlanýr.\n{ecc317}+ {ffffff}Radyo ve modifiye korumasý\n\nSeviyeyi girin \taþaðýdaki kutuya satýn almak istediðiniz sigortayý girin:");
	    format(mes, sizeof(mes), mes, cost * 1, cost * 2, cost * 3);
	    Dialog_Show(playerid, BuyVehInsurance, DIALOG_STYLE_INPUT, "{FFFFFF}Sigorta Satýn Al", mes, "Satýn Al", "Geri");
	    return 1;
	}

	else if (listitem == 4)
	{
	    return Dialog_Show(playerid, BuyVehArmour, DIALOG_STYLE_INPUT, "{FFFFFF}Araç Zýrhý", "{ffffff}satýn almak istediðiniz zýrh miktarýný girin (10 - 250) [1 birim 10$]", "Satýn Al", "Geri");
	}

	new alarm_mes[][] =
	{
	    {"{ecc317}+ {ffffff}Yüksek Sesli Alarm"}, {"{ecc317}+ {ffffff}Yüksek Sesli Alarm\n{ecc317}+ {ffffff}Polise ihbar gönderme"},
		{"{ecc317}+ {ffffff}Yüksek Sesli Alarm\n{ecc317}+ {ffffff}Polise ihbar gönderme\n{ecc317}+ {ffffff}Çalýnma sonucu sahibe SMS gitmesi"},
		{"{ecc317}+ {ffffff}Yüksek Sesli Alarm\n{ecc317}+ {ffffff}Polise ihbar gönderme\n{ecc317}+ {ffffff}Çalýnma sonucu sahibe SMS gitmesi+ kasko. "}
	};

	new mes[256];

	switch(listitem)
	{
	    case 0:
		{
		    if (VehicleInfo[vehicle][carLock] >= sizeof(price_mod_lock))		return SendErrorMessage(playerid, "Aracýnýz zaten en yüksek kilit seviyesinde.");

			format(mes, sizeof(mes), "{ffffff}%i kilit seviyesine $%i karþýlýðýnda seviye yükseltilsin mi?\n{ecc317}+ {ffffff}Araç kilidi  %i saniyede kýrýlýr.", VehicleInfo[vehicle][carLock]+1, price_mod_lock[VehicleInfo[vehicle][carLock]], 250 + (GetPVarInt(playerid, "BuyingVehicleLock") * 250));
		}
		case 1:
		{
		    if (VehicleInfo[vehicle][carAlarm] >= sizeof(price_mod_alarm))	return SendErrorMessage(playerid, "Aracýnýz zaten en yüksek alarm seviyesinde.");

			format(mes, sizeof(mes), "{ffffff}Alarm seviyesi %i olarak güncellenecek, $%i ödemeyi kabul ediyor musun?\n%s", VehicleInfo[vehicle][carAlarm]+1, price_mod_alarm[VehicleInfo[vehicle][carAlarm]], alarm_mes[VehicleInfo[vehicle][carAlarm]]);
		}
		case 2:
		{
		    if (VehicleInfo[vehicle][carImmob] >= sizeof(price_mod_immob))	return SendErrorMessage(playerid, "Aracýnýz zaten en yüksek immoblilizer seviyesinde.");

			format(mes, sizeof(mes), "{ffffff}Ýmmobilizer seviyesi %i olarak güncellenecek, $%i ödemeyi kabul ediyor musun?\n{ecc317}+ {ffffff}Kontak anahtarýnýn kýrýlmasýný önlemeye yardýmcý olur.", VehicleInfo[vehicle][carImmob]+1, price_mod_immob[VehicleInfo[vehicle][carImmob]]);
		}
	}

	SetPVarInt(playerid, #upgrade_veh, listitem);
	Dialog_Show(playerid, BuyVehUpgrade2, DIALOG_STYLE_MSGBOX, "{FFFFFF}Yükseltme Satýn Al", mes, "Satýn Al", "Geri");
 	return 1;
}

Dialog:BuyVehUpgrade2(playerid, response, listitem, inputtext[])
{
    if (!response)	return ShowModMenu(playerid);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)										return 1;

    listitem = GetPVarInt(playerid, #upgrade_veh);

    switch(listitem)
    {
        case 0: StartVehicleUpgrade(playerid, vehicle, 2, price_mod_lock[VehicleInfo[vehicle][carLock]], VehicleInfo[vehicle][carLock]+1);
        case 1: StartVehicleUpgrade(playerid, vehicle, 3, price_mod_alarm[VehicleInfo[vehicle][carAlarm]], VehicleInfo[vehicle][carAlarm]+1);
        case 2: StartVehicleUpgrade(playerid, vehicle, 4, price_mod_immob[VehicleInfo[vehicle][carImmob]], VehicleInfo[vehicle][carImmob]+1);
    }
	return 1;
}

Dialog:SelectModDialog(playerid, response, listitem, inputtext[])
{
    new vehicle = GetPlayerVehicleID(playerid), comptype = GetPVarInt(playerid, #component_type), compid = -1;

    if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
    if (!response)																return ShowModMenu(playerid);
   	if (ModShop_Nearest(playerid) == -1)										return 1;

    for(new i; i != max_vehicle_components[comptype]; i++)
	{
		if (!vehicle_component[comptype][i][compID] || IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), vehicle_component[comptype][i][compID]) != 1) continue;

		compid++;
		if (listitem == compid)
		{
			compid = i;
			break;
		}
   	}

   	new modelid = vehicle_component[comptype][compid][compID];

   	if (GetVehicleComponentType(modelid) == -1 || IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), modelid) != 1)
	{
		ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Bu parça aranýza uymuyor.");
	}

	if (comptype == -1 || compid == -1)	return SendErrorMessage(playerid, "Bir sorun yaþandý, yöneticilerle iletiþime geçiniz.");

    new mes[128];
    format(mes, sizeof(mes), "{FFFFFF}%s adlý parçayý $%i karþýlýðýnda aracýnýza eklemek istiyor musunuz?", GetComponentName(modelid), vehicle_component[comptype][compid][compPrice]);

    Dialog_Show(playerid, ModConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyeleri", mes, "Evet", "Geri");
    SetPVarInt(playerid, #component_model, modelid);
    SetPVarInt(playerid, #component_type, comptype);
    AddVehicleComponent(vehicle, modelid);
	return 1;
}

Dialog:DeleteTuning(playerid, response, listitem, inputtext)
{
    if (!response)	return ShowModMenu(playerid);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;
	if (listitem == 9 && VehicleInfo[vehicle][carPaintJob] == 3)
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Araçta zaten paintjob bulunmuyor.");
	}
    if (listitem == 11 && VehicleInfo[vehicle][carRadio] == 0)
    {
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Araçta zaten radyo bulunmuyor.");
	}

  	new comp_type[11] = {CARMODTYPE_WHEELS, CARMODTYPE_SPOILER, CARMODTYPE_HOOD, CARMODTYPE_ROOF, CARMODTYPE_SIDESKIRT, CARMODTYPE_EXHAUST, CARMODTYPE_FRONT_BUMPER, CARMODTYPE_REAR_BUMPER, CARMODTYPE_NITRO, 0, CARMODTYPE_HYDRAULICS};

	if (listitem != 9 && listitem != 11 && VehicleInfo[vehicle][carComponent][comp_type[listitem]] == 0)
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Bu modifikasyon aracýnýza ekli deðil.");
	}

	new comp_name[12][32] = {"Tekerlekler", "spoiler", "air intake","the roof","side skirts "," exhaust pipes "," front bumper "," rear bumper "," nitro "," paint work "," hydraulics "," radio "};

	new mes[128];
	format(mes, sizeof(mes), "{FFFFFF}%s parçasýný silmek istiyor musunuz?", comp_name[listitem]);
	Dialog_Show(playerid, DeleteTuningConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Modifiye silme", mes, "Evet", "Geri");
    SetPVarInt(playerid, #select_deltun, listitem);
	return 1;
}

Dialog:DeleteTuningConfrim(playerid, response, listitem, inputtext)
{
    if (!response)	return ShowModMenu(playerid);

    listitem = GetPVarInt(playerid, #select_deltun);

    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;
	if (listitem == 9 && VehicleInfo[vehicle][carPaintJob] == 3)
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Araçta zaten paintjob bulunmuyor.");
	}

    if (listitem == 11 && VehicleInfo[vehicle][carRadio] == 0)
    {
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Araçta zaten radyo bulunmuyor.");
	}

  	new comp_type[11] = {CARMODTYPE_WHEELS, CARMODTYPE_SPOILER, CARMODTYPE_HOOD, CARMODTYPE_ROOF, CARMODTYPE_SIDESKIRT, CARMODTYPE_EXHAUST, CARMODTYPE_FRONT_BUMPER, CARMODTYPE_REAR_BUMPER, CARMODTYPE_NITRO, 0, CARMODTYPE_HYDRAULICS};

	if (listitem != 9 && listitem != 11 && VehicleInfo[vehicle][carComponent][comp_type[listitem]] == 0)
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Aracýnýzda bu modifikasyon ekli deðil.");
	}
    if (listitem == 9)
	{
	    VehicleInfo[vehicle][carPaintJob] = 3;
	    ChangeVehiclePaintjob(vehicle, 3);
	}
    else if (listitem == 11)
	{
        VehicleInfo[vehicle][carRadio] = 0;
	}
	else
	{
	    RemoveVehicleComponent(vehicle, VehicleInfo[vehicle][carComponent][comp_type[listitem]]);
	    VehicleInfo[vehicle][carComponent][comp_type[listitem]] = 0;
	}

	new comp_name[12][32] = {"wheels", "spoiler", "air intake", "roof", "side skirts", "exhaust pipes", "front bumper", "rear bumper", "nitro", "paint work", "hydraulics", " radio "};

	SendSyntaxMessage(playerid, "%s parçasýný araçtan baþarýyla kaldýrdýnýz.", comp_name[listitem]);
	return 1;
}

Dialog:HydralicConfrim(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if ((modshop = ModShop_Nearest(playerid)) == -1)							return 1;
	if (GetCash(playerid) < 8000)
	{
	   	ShowModMenu(playerid);
		return SendNotCash(playerid);
	}
	if (IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), 1087) != 1)
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Bu araca hidrolik takýlamaz.");
	}

    if (BizInfo[modshop][bizOwnerID] && !BizInfo[modshop][bizProduct])	return SendErrorMessage(playerid, "Modifiye garajýnda yeterli parça mevcut deðil.");

	GiveCash(playerid, -8000);
    SetVehicleComponent(vehicle, 1087, GetVehicleComponentType(1087));
	SendSyntaxMessage(playerid, "Hidroliði 8000$ satýn aldýnýz.");

	if (BizInfo[modshop][bizOwnerID])
	{
		BizInfo[modshop][bizProduct]--;
		GiveBizCash(modshop, 8000 / 100 * 80);
	}

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:RadioConfrim(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if ((modshop = ModShop_Nearest(playerid)) == -1)								return 1;

	if (VehicleInfo[vehicle][carRadio] == 1)
	{
	    ShowModMenu(playerid);
		return SCM(playerid, COLOR_LIGHTRED, "Araç radyonuz zaten var!");
	}
	if (GetCash(playerid) < 400)
	{
	    ShowModMenu(playerid);
		return SendNotCash(playerid);
	}

	GiveCash(playerid, -400);
	VehicleInfo[vehicle][carRadio] = 1;
	SendSyntaxMessage(playerid, "Radyoyu 400$ satýn aldýnýz, bir radyo istasyonuna baðlanmak istersen /set station komutunu kullanabilirsin.");
    GiveBizCash(modshop, 400);
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:GPSConfrim(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if ((modshop = ModShop_Nearest(playerid)) == -1)								return 1;
	if (VehicleInfo[vehicle][carGps] == 1)
	{
	    ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Zaten bir GPS'niz var!");
	}

	if (GetCash(playerid) < 1500)
	{
	    ShowModMenu(playerid);
		return SendNotCash(playerid);
	}

	GiveCash(playerid, -1500);
	VehicleInfo[vehicle][carGps] = 1;
	SendSyntaxMessage(playerid, "1.500 dolara GPS satýn aldýnýz. Aracýnýzý bulmak için /arac bul komutunu kullanabilirsiniz.");
    GiveBizCash(modshop, 1500);
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ChangeLock(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Kiþisel araçlarda olmalýsýnýz.");
   	if ((modshop = ModShop_Nearest(playerid)) == -1)														return 1;

	if (VehicleInfo[vehicle][carGps] == 1)
	{
	    ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Zaten bir GPS'niz var!");
	}

	if (GetCash(playerid) < 300)
	{
	    ShowModMenu(playerid);
		return SendNotCash(playerid);
	}

	GiveCash(playerid, -300);
	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || PlayerInfo[i][pSpareKey] != VehicleInfo[vehicle][carID]) continue;

        PlayerInfo[i][pSpareKey] = 0;
	}

	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `sparekey`='0' WHERE `sparekey`=%i", VehicleInfo[vehicle][carID]);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "Kilidi 300$'a deðiþtirdiniz.");
	VehicleInfo[vehicle][carLock] = listitem;
    GiveBizCash(modshop, 300);
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:ModConfrim(playerid, response, listitem, inputtext[])
{
   	new modshop = -1, vehicle = GetPlayerVehicleID(playerid), modelid = GetPVarInt(playerid, #component_model);

	RemoveVehicleComponent(vehicle, modelid);
    LoadComp(vehicle);

   	if (!response)																return ShowComponentMenu2(playerid, vehicle, GetPVarInt(playerid, #component_type));
	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
	if ((modshop = ModShop_Nearest(playerid)) == -1)							return 1;
	if (GetVehicleComponentType(modelid) == -1 || IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), modelid) != 1)
	{
 		ShowModMenu(playerid);
   		return SendErrorMessage(playerid, "Bu parça araca uymuyor.");
	}

	new compid = -1, comptype = -1;

	for(new i; i != sizeof(vehicle_component); i++)
	{
	    for(new a; a != max_vehicle_components[i]; a++)
		{
	    	if (vehicle_component[i][a][compID] != modelid) continue;

			comptype = i;
			compid = a;
			break;
		}

		if (comptype != -1 && compid != -1) break;
	}

	if (comptype == -1 || compid == -1)	return SendErrorMessage(playerid,"Bir sorun yaþandý, yöneticilerle iletiþime geçiniz.");

	if (GetCash(playerid) < vehicle_component[comptype][compid][compPrice])
	{
	    ShowModMenu(playerid);
	    return SendErrorMessage(playerid, "Yeterli paranýz yok. Bu parçanýn maliyeti $%i.", vehicle_component[comptype][compid][compPrice]);
	}

	if (HasComponent(vehicle, modelid))
 	{
  		ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Bu parça zaten sizde mevcut!");
	}

    if (BizInfo[modshop][bizOwnerID] && !BizInfo[modshop][bizProduct])	return SendErrorMessage(playerid, "Modifiye garajýnda yeterli parça yok!");

	GiveCash(playerid, -vehicle_component[comptype][compid][compPrice]);

	if (BizInfo[modshop][bizOwnerID] != 0)
	{
		BizInfo[modshop][bizProduct]--;
		GiveBizCash(modshop, vehicle_component[comptype][compid][compPrice] / 100 * 80);
	}
	
	SendSyntaxMessage(playerid, "%s adlý parçayý $%i karþýlýðýnda satýn aldýnýz.", GetComponentName(modelid), vehicle_component[comptype][compid][compPrice]);
	SetVehicleComponent(vehicle, modelid, GetVehicleComponentType(modelid));
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:PaintjobDialog(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
    if (IsVehiclePaintJob(GetVehicleModel(vehicle)) < listitem+1)				return 1;
   	if (ModShop_Nearest(playerid) == -1)											return 1;

    if (VehicleInfo[vehicle][carPaintJob] == listitem)
    {
        ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Zaten paintjobunuz var.");
	}

	new mes[128];

	format(mes, sizeof(mes), "{FFFFFF}%i numaralý paintjob $3.000 karþýlýðýnda aracýnýza eklensin mi?", listitem+1);
	Dialog_Show(playerid, PaintjobConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyesi", mes, "Evet", "Geri");
    SetPVarInt(playerid, #select_paintjob, listitem);

	ChangeVehiclePaintjob(vehicle, listitem);
	return 1;
}

Dialog:PaintjobConfrim(playerid, response, listitem, inputtext[])
{
    listitem = GetPVarInt(playerid, #select_paintjob);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

    ChangeVehiclePaintjob(vehicle, VehicleInfo[vehicle][carPaintJob]);

    if (!response)																return ShowModMenu(playerid);
	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if ((modshop = ModShop_Nearest(playerid)) == -1)							return 1;
	if (!IsVehiclePaintJob(GetVehicleModel(vehicle)))							return SendErrorMessage(playerid, "Bu araç için paintjob yoktur!");
	if (VehicleInfo[vehicle][carPaintJob] == listitem)
    {
        ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Zaten böyle bir paintjobunuz var!");
	}
	if (GetCash(playerid) < 3000)
	{
	    ShowModMenu(playerid);
		return SendNotCash(playerid);
	}
	if (BizInfo[modshop][bizOwnerID] && !BizInfo[modshop][bizProduct])	return SendErrorMessage(playerid,"Modifye garajýnda yeterli parça yok.");

	GiveCash(playerid, -3000);
	VehicleInfo[vehicle][carPaintJob] = listitem;
	ChangeVehiclePaintjob(vehicle, listitem);
	Save_Car(vehicle);
	SendSyntaxMessage(playerid, "%i numaralý paintjob 3.000$ karþýlýðýnda satýn alýndý.", listitem+1);

    if (BizInfo[modshop][bizOwnerID] != 0)
    {
		BizInfo[modshop][bizProduct]--;
		GiveBizCash(modshop, 3000 / 100 * 80);
	}
	PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:NitroDialog(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowModMenu(playerid);

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if (ModShop_Nearest(playerid) == -1)										return 1;

	new nitro_id[3] = {1009, 1008, 1010}, nitro_price[3] = {4500, 9000, 15000};

    if (HasComponent(vehicle, nitro_id[listitem]))
    {
        ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Bu araçta zaten bir nitro var!");
	}

	new mes[128];

	format(mes, sizeof(mes), "{FFFFFF}%i seviye nitroyu  $%i karþýlýðýnda satýn almak mý istiyorsunuz?", (listitem == 0)?(2):((listitem == 1)?(5):(10)), nitro_price[listitem]);
	Dialog_Show(playerid, NitroConfrim, DIALOG_STYLE_MSGBOX, "{33AA33}Araç Modifiyesi", mes, "Evet", "Geri");
    SetPVarInt(playerid, #select_nitro, listitem);
	return 1;
}

Dialog:NitroConfrim(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowModMenu(playerid);

    listitem = GetPVarInt(playerid, #select_nitro);

	new modshop = -1, vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid) || !VehicleInfo[vehicle][carOwnerID])	return 1;
   	if ((modshop = ModShop_Nearest(playerid)) == -1)								return 1;

	new nitro_id[3] = {1009, 1008, 1010}, nitro_price[3] = {15000, 15500, 16000}, nitro_level[3] = {2, 5, 10};

    if (HasComponent(vehicle, nitro_id[listitem]))
    {
        ShowModMenu(playerid);
		return SendErrorMessage(playerid, "Bu araçta zaten bir nitro var!");
	}

    if (IsVehicleUpgradeCompatible(GetVehicleModel(vehicle), nitro_id[listitem]) != 1)
    {
        ShowModMenu(playerid);
    	return SendErrorMessage(playerid, "Bu araca nitro takýlamaz.");
	}

	if (GetCash(playerid) < nitro_price[listitem])
	{
	    ShowModMenu(playerid);
		return SendNotCash(playerid);
	}

	if (PlayerInfo[playerid][pPremium] < 2)								return SendErrorMessage(playerid, "Yalnýzca premium hesabý 'Gümüþ' veya daha yüksek olan bir oyuncu nitro satýn alabilir.");
    if (BizInfo[modshop][bizOwnerID] && !BizInfo[modshop][bizProduct])	return SendErrorMessage(playerid, "Modifiye garajýnda yeterli parça yok.");

	GiveCash(playerid, -nitro_price[listitem]);
	SetVehicleComponent(vehicle, nitro_id[listitem], CARMODTYPE_NITRO);
	SendSyntaxMessage(playerid, "%i seviye nitroyu $%i karþýlýðýnda aldýn.", nitro_level[listitem], nitro_price[listitem]);

    if (BizInfo[modshop][bizOwnerID] != 0)
    {
		BizInfo[modshop][bizProduct]--;
		GiveBizCash(modshop, nitro_price[listitem] / 100 * 80);
	}
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:StartJackingLock(playerid, response, listitem, inputtext[])
{
	if (!response)											 return 1;

	new vehicle = GetPVarInt(playerid, #JackingVehicle);
	if (!vehicle || !GetNearVehicle(playerid, 3.0, vehicle)) return SendErrorMessage(playerid, "Aracýn yakýnýnda olmalýsýnýz.");
	if (!IsPlayerInFrontVDoor(playerid, vehicle)) 			 return SendErrorMessage(playerid, "Sürücü kapýsýnýn yanýnda olmalýsýnýz.");
	if (!VehicleInfo[vehicle][carLocked])					 return SendErrorMessage(playerid, "Araç kapýlarý açýk.");

	if (pTemp[playerid][JackingType] == 2) {
		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Kalkamalýsýnýz.");
		switch(VehicleInfo[vehicle][carLock])
		{
			case 0: VehicleInfo[vehicle][eDoorHealth] = 25, VehicleInfo[vehicle][eDoorEffect] = BLOCK_NONE;
			case 1: VehicleInfo[vehicle][eDoorHealth] = 50, VehicleInfo[vehicle][eDoorEffect] = LESS_DAMAGE_FIST;
			case 2: VehicleInfo[vehicle][eDoorHealth] = 75, VehicleInfo[vehicle][eDoorEffect] = BLOCK_FIST;
			case 3: VehicleInfo[vehicle][eDoorHealth] = 150, VehicleInfo[vehicle][eDoorEffect] = LESS_DAMAGE_MELEE;
			case 4: VehicleInfo[vehicle][eDoorHealth] = 200, VehicleInfo[vehicle][eDoorEffect] = BLOCK_PHYSICAL;
			case 5: VehicleInfo[vehicle][eDoorHealth] = 250, VehicleInfo[vehicle][eDoorEffect] = BLOCK_PHYSICAL;
		}

		PlaySound(playerid, 1138);
		AlarmOn(vehicle);
		SendHelpMessage(playerid, "Aracý açmak için kapýyý kýrmaya baþlamalýsýn!");
		VehicleInfo[vehicle][ePhysicalAttack] = true;

		new doorhealth[12];
		format(doorhealth, 12, "%d%%", VehicleInfo[vehicle][eDoorHealth]);
		VehicleInfo[vehicle][eVehicleLabel] = CreateDynamic3DTextLabel(doorhealth, COLOR_WHITE, 0.0, 0.0, 0.0, 15.0, INVALID_PLAYER_ID, vehicle, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerid);

	} else if (pTemp[playerid][JackingType] == 1) {
		if (IsPlayerCrouching(playerid) == false) return SendErrorMessage(playerid, "Eðilmelisiniz.");
		if (!CheckHanditem(playerid,18634)) 	  return SendErrorMessage(playerid, "Elinizde bir levye olmalý.");

		JackingLock[playerid] = 250 + VehicleInfo[vehicle][carLock] * 250;

		new mes[128];
		format(mes, sizeof(mes), "%s model aracýn kilidini kýrmaya çalýþýr.", VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);

	} else return 1;

	JackingVehicle[playerid] = vehicle;
	return 1;
}

Dialog:StartJackingEngine(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new vehicle = GetPlayerVehicleID(playerid);

    if (!vehicle || !IsDriver(playerid))					return SendErrorMessage(playerid, "Sürücü koltuðunun arkasýnda oturmalýsýnýz.");
	if (!VehicleInfo[vehicle][carOwnerID])					return SendErrorMessage(playerid, "Bu araç açýlamaz.");
	if (JackingEngine[playerid])							return SendErrorMessage(playerid, "Zaten motoru çalýþtýrmaya çalýþýyorsunuz!");
	if (VehicleInfo[vehicle][carEngineOn])					return SendErrorMessage(playerid, "Motor zaten çalýþýyor!");
    if (VehicleInfo[vehicle][carFuel] == 0.0)				return SendErrorMessage(playerid, "Aracanýzda benzin yok!");
	if (GetPVarInt(playerid, #UsePump))						return SendErrorMessage(playerid, "Þu anda motoru çalýþtýramazsýnýz.");
    if (!IsPlayerHasItem(playerid, INV_TOOLS))				return SendErrorMessage(playerid, "Aracý çalýþtýracak hiçbir aletiniz yok.");

	new mes[128];
	format(mes, sizeof(mes), "%s model aracý düz kontak yapmaya çalýþýr.", VehicleNames[GetVehicleModel(vehicle)-400]);
	pc_cmd_me(playerid, mes);

	pTemp[playerid][pUnscrambleID] = random(sizeof(UnscrambleInfo));

	switch(VehicleInfo[vehicle][carImmob])
	{
		case 0: JackingEngine[playerid] = 125;
		case 1: JackingEngine[playerid] = 100;
		case 2: JackingEngine[playerid] = 75;
		case 3: JackingEngine[playerid] = 50;
		case 4: JackingEngine[playerid] = 25;
	}

	return 1;
}

Dialog:Rent_Vehicle_Personal(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;

    if(response)
	{
        new Float:x, Float:y, Float:z, Float:a, model;
     	GetPlayerPos(playerid, x, y, z);
	    GetPlayerFacingAngle(playerid, a);

	    switch(listitem)
        {
		    case 0: model = 507;
		    case 1: model = 467;
		    case 2: model = 516;
		    case 3: model = 547;
		    case 4: model = 566;
		    case 5: model = 540;
		    case 6: model = 491;
	    	case 7: model = 436;
		    case 8: model = 492;	
		    case 9: model = 466;					
	    }

		new vehicle = CreateFactionVehicle(false, model, x, y, z, a, 1, 1, 5, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		if(!vehicle) return SendErrorMessage(playerid, "Bir sorun oluþtu. Kod: 1055");

	    GiveCash(playerid, -300);
	    pTemp[playerid][pRentveh] = vehicle;
        VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	    FixVehicle(vehicle);
	    VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

		PutPlayerInVeh(playerid, vehicle, 0);
	
	    SendSyntaxMessage(playerid, "%s model aracý $300'a kiraladýnýz. Kullanabileceðiniz komutlar: /arackirabitir, /a kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	    SendSyntaxMessage(playerid, "Dikkat! Aracý 5 dakika boyunca kullanmazsanýz araç silinecektir!");	
	}
	return 1;
}