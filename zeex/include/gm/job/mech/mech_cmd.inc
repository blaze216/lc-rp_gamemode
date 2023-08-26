CMD:tamir(playerid, params[])
{
	new userid, type, vehid = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC) 	return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid) || !IsATowTruck(vehid))		return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");

	if (sscanf(params,"ui",userid, type))
	{
		SendHelpMessage(playerid, "/tamir [ID / isim] [tip]");
		SendSyntaxMessage(playerid, "tip 1: Motor saðlýðýný düzeltme (Araç caný yükselir) ");
		SendSyntaxMessage(playerid, "tip 2: Kaporta tamiri (kýrýk parçalarý yeniler) ");
		SendSyntaxMessage(playerid, "tip 3: Motor tamiri (Tükenmiþ motoru yeniler) ");
		return 1;
	}

	if (type < 1 || type > 3)
	{
	    SendSyntaxMessage(playerid, "tip 1: Motor saðlýðýný düzeltme (Araç caný yükselir) ");
		SendSyntaxMessage(playerid, "tip 2: Kaporta tamiri (kýrýk parçalarý yeniler) ");
		SendSyntaxMessage(playerid, "tip 3: Motor tamiri (Tükenmiþ motoru yeniler) ");
	    return 1;
	}

	if (userid == playerid)								return SendErrorMessage(playerid, "Bu iþlemi kendinize uygulayamazsýnýz. ");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))								return SendErrorMessage(playerid, "Belirttiðiniz kiþi araçta olmalý.");

	new vehicle = GetPlayerVehicleID(userid);

	if (VehicleInfo[vehicle][carFaction] != 0 && type != 1 && type != 2)												return SendErrorMessage(playerid, "Birlik araçlarýna bu iþlemi uygulayamazsýn.");
    if (pTemp[userid][pServePlayer] == playerid && (pTemp[userid][pServeType] > 0 && pTemp[userid][pServeType] < 4))	return SendErrorMessage(playerid, "%s adlý kiþiye zaten bir teklif göndermiþsiniz.", GetNameEx(userid));
	    
	if (type == 1)
	{
		if (VehicleInfo[vehid][carComps] < 75)	return SendErrorMessage(playerid, "Bu iþlem için yeterli materyaliniz yok.");

		new mes[128];
    	format(mes, sizeof(mes), "%s adlý kiþinin %s model aracýna tamir teklifi verir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size tamir isteði gönderdi. (Y tuþuna basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	else if (type == 2)
	{
	    if (VehicleInfo[vehid][carComps] < 75)	return SendErrorMessage(playerid, "Bu iþlem için yeterli materyaliniz yok.");

		new mes[128];
    	format(mes, sizeof(mes), "%s adlý kiþiye %s model aracýna kaporta tamiri teklifi gönderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size tamir teklifi gönderdi. (Y tuþuna basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	else if (type == 3)
	{
		if (VehicleInfo[vehid][carComps] < 75)		return SendErrorMessage(playerid, "Bu iþlem için 75 adet materyale ihtiyacýnýz var.");
		if (VehicleInfo[vehicle][carEngine] >= 20.0)	return SendErrorMessage(playerid, "Bu araç motorunun revizyona ihtiyacý yok ( > 20%%).");

        new mes[128];
    	format(mes, sizeof(mes), "%s adlý kiþinin %s model aracýna motor revizyon teklifi verir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size araç motoru için revizyon teklifi gönderdi. (Y tuþuna basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	
	pTemp[userid][pServePlayer] = playerid;
	pTemp[userid][pServeType] = type;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}

CMD:materyalal(playerid, params[]) //êîìï
{
	new amount;
	
	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid))								return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))	return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (!PlayerToPoint(6.0, playerid, 892.8326,-1322.4624,31.9593))
	{
		Waypoint_Set(playerid, 892.8326,-1322.4624,31.9593, 8.0);
		return SendSyntaxMessage(playerid, "Yedek parça satýlan yer haritanýzda iþaretlendi. (/cpsifirla)");
	}

	if (sscanf(params,"d",amount))
	{
		SendHelpMessage(playerid, "/materyalal [miktar]");
		SendSyntaxMessage(playerid, "Materyalýn 1 adeti 1 dolara eþittir.");
		return 1;
	}

	if (amount < 1 || amount > 300)											return SendErrorMessage(playerid, "1 ile 300 arasýnda bir seçim yapýn.");
    if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] >= 300)			return SendErrorMessage(playerid, "Bulunduðunuz tamir aracýnda zaten yeterince materyal var. ");
	if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] + amount > 300)	return SendErrorMessage(playerid, "Sadece %i adet parça alma hakkýnýz kaldý.", 300 - VehicleInfo[GetPlayerVehicleID(playerid)][carComps]);
	if (GetCash(playerid) < amount)											return SendErrorMessage(playerid, "%i adet materyal için yeterli paranýz yok.", amount);

	GiveCash(playerid, -amount);
	SendSyntaxMessage(playerid, "%i adet materyali $%i karþýlýðýnda satýn aldýn.", amount, amount);
	JobMessage(playerid, "~w~ARACA PARCALARI YERLESTIRDIN.", 6);
	VehicleInfo[GetPlayerVehicleID(playerid)][carComps] += amount;
	return 1;
}

CMD:materyallerim(playerid, params[])
{
	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid))							return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))		return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");

    SendSyntaxMessage(playerid, "Tamir aracýnda %i adet parça bulunuyor.", VehicleInfo[GetPlayerVehicleID(playerid)][carComps]);
	return 1;
}

CMD:benzindoldur(playerid, params[])
{
	new userid, price;

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)			return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid))								return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))			return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (sscanf(params,"ud",userid,price))					return SendHelpMessage(playerid, "/benzindoldur [ID / isim] [ücret]");
	if (userid == playerid)									return SendErrorMessage(playerid, "Bu iþlemi kendine uygulayamazsýn.");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))			return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))									return SendErrorMessage(playerid, "Belirttiðiniz kiþi araçta olmalý.");

    new vehicle = GetPlayerVehicleID(userid);

    if (VehicleInfo[vehicle][carFuel] >= GetVehicleFuelCapacity(GetVehicleModel(vehicle)))	
		return SendErrorMessage(playerid, "Aracýn deposu tamamen dolu.");
	if (price < 1 || price > 500)															
		return SendErrorMessage(playerid, "$1 ile $500 dolar arasýnda bir teklif sunabilirsin.");

    new mes[128];
    format(mes, sizeof(mes), "%s adlý kiþinin aracýna $%i karþýlýðýnda yakýt doldurmayý teklif eder.", GetNameWithMask(userid), price);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "%s adlý tamirci $%i karþýlýðýnda araca yakýt koymayý teklif etti. (Y tuþuna basarak kabul edebilirsin)", GetNameWithMask(playerid), price);
	RefillPrice[userid] = price;
	RefillOffer[userid] = playerid;
	return 1;
}

CMD:aracboya(playerid, params[])
{
	new userid, color1, color2;

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)						return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid))											return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))						return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (sscanf(params,"udd", userid, color1, color2))					return SendHelpMessage(playerid, "/aracboya [ID / isim] [renk 1] [renk 2](/renkler)");
	if (color1 > 255 || color2 > 255 || color1 < 0 || color2 < 0)		return SendErrorMessage(playerid, "Renk numarasý 0 ile 255 arasýnda olmalý. /renkler");
	if (userid == playerid)												return SendErrorMessage(playerid, "Bu iþlemi kendine uygulayamazsýn.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))						return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))												return SendErrorMessage(playerid, "Belirttiðiniz kiþi araçta olmalý.");

	new vehicle = GetPlayerVehicleID(userid);

	if (VehicleInfo[vehicle][carFaction] != 0)										return SendErrorMessage(playerid, "Birlik araçlarýna bu iþlemi uygulayamazsýn. ");
	if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] < 45)					return SendErrorMessage(playerid, "Araç boyamak için 45 materyale ihtiyacýnýz var. ");
    if (pTemp[userid][pServePlayer] == playerid && pTemp[userid][pServeType] == 4)	return SendErrorMessage(playerid, "%s adlý kiþiye zaten bir teklif göndermiþsiniz.", GetNameEx(userid));

	new mes[128];
    format(mes, sizeof(mes), "%s adlý kiþinin %s model aracýna boyama teklifi gönderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "%s aracýnýza boyama teklifi gönderdi. (Y tuþuna basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));

	SetPVarInt(playerid, "color1", color1);
	SetPVarInt(playerid, "color2", color2);
	pTemp[userid][pServePlayer] = playerid;
 	pTemp[userid][pServeType] = 4;
 	SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}

CMD:aracicek(playerid, params[])
{
	new userid, vehicle = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesleðinde deðilsiniz.");
	if (!IsDriver(playerid) || !IsATowTruck(vehicle))	return SendErrorMessage(playerid, "Çekici aracýnýn içerisinde olmalýsýnýz.");
	if (IsTrailerAttachedToVehicle(vehicle))
	{
		DetachTrailerFromVehicle(vehicle);
		return SendErrorMessage(playerid, "Çektiðiniz aracýn kancasýný çýkardýnýz.");
	}

	if (sscanf(params,"u", userid))						return SendHelpMessage(playerid, "/aracicek [ID / isim]");
	if (userid == playerid)								return SendErrorMessage(playerid, "Bu iþlemi kendine uygulayamazsýn.");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(8.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (!IsPlayerInAnyVehicle(userid))					return SendErrorMessage(playerid, "Belirttiðiniz kiþi araçta olmalý.");

	if (pTemp[userid][pServePlayer] == playerid && pTemp[userid][pServeType] == 5) 	return SendErrorMessage(playerid, "%s adlý kiþiye zaten bir teklif göndermiþsiniz.", GetNameEx(userid));

	new vehid = GetPlayerVehicleID(userid);

    if (IsABoat(vehid) || IsAPlane(vehid) || IsAHelicopter(vehid) || IsABiker(vehid))	return SCM(playerid, COLOR_GREY,"Bu araç çekilemez.");

    new mes[128];
    format(mes, sizeof(mes), "%s adlý kiþinin %s model aracýný çekme teklifi gönderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehid)-400]);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "* %s aracýnýza çekme teklifi gönderdi. (Araçtan inip Y tuþuna basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	SetPVarInt(userid, #tow_car, vehid);
	pTemp[userid][pServePlayer] = playerid;
	pTemp[userid][pServeType] = 5;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}