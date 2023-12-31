CMD:tamir(playerid, params[])
{
	new userid, type, vehid = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC) 	return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid) || !IsATowTruck(vehid))		return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");

	if (sscanf(params,"ui",userid, type))
	{
		SendHelpMessage(playerid, "/tamir [ID / isim] [tip]");
		SendSyntaxMessage(playerid, "tip 1: Motor sa�l���n� d�zeltme (Ara� can� y�kselir) ");
		SendSyntaxMessage(playerid, "tip 2: Kaporta tamiri (k�r�k par�alar� yeniler) ");
		SendSyntaxMessage(playerid, "tip 3: Motor tamiri (T�kenmi� motoru yeniler) ");
		return 1;
	}

	if (type < 1 || type > 3)
	{
	    SendSyntaxMessage(playerid, "tip 1: Motor sa�l���n� d�zeltme (Ara� can� y�kselir) ");
		SendSyntaxMessage(playerid, "tip 2: Kaporta tamiri (k�r�k par�alar� yeniler) ");
		SendSyntaxMessage(playerid, "tip 3: Motor tamiri (T�kenmi� motoru yeniler) ");
	    return 1;
	}

	if (userid == playerid)								return SendErrorMessage(playerid, "Bu i�lemi kendinize uygulayamazs�n�z. ");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))								return SendErrorMessage(playerid, "Belirtti�iniz ki�i ara�ta olmal�.");

	new vehicle = GetPlayerVehicleID(userid);

	if (VehicleInfo[vehicle][carFaction] != 0 && type != 1 && type != 2)												return SendErrorMessage(playerid, "Birlik ara�lar�na bu i�lemi uygulayamazs�n.");
    if (pTemp[userid][pServePlayer] == playerid && (pTemp[userid][pServeType] > 0 && pTemp[userid][pServeType] < 4))	return SendErrorMessage(playerid, "%s adl� ki�iye zaten bir teklif g�ndermi�siniz.", GetNameEx(userid));
	    
	if (type == 1)
	{
		if (VehicleInfo[vehid][carComps] < 75)	return SendErrorMessage(playerid, "Bu i�lem i�in yeterli materyaliniz yok.");

		new mes[128];
    	format(mes, sizeof(mes), "%s adl� ki�inin %s model arac�na tamir teklifi verir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size tamir iste�i g�nderdi. (Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	else if (type == 2)
	{
	    if (VehicleInfo[vehid][carComps] < 75)	return SendErrorMessage(playerid, "Bu i�lem i�in yeterli materyaliniz yok.");

		new mes[128];
    	format(mes, sizeof(mes), "%s adl� ki�iye %s model arac�na kaporta tamiri teklifi g�nderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size tamir teklifi g�nderdi. (Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	else if (type == 3)
	{
		if (VehicleInfo[vehid][carComps] < 75)		return SendErrorMessage(playerid, "Bu i�lem i�in 75 adet materyale ihtiyac�n�z var.");
		if (VehicleInfo[vehicle][carEngine] >= 20.0)	return SendErrorMessage(playerid, "Bu ara� motorunun revizyona ihtiyac� yok ( > 20%%).");

        new mes[128];
    	format(mes, sizeof(mes), "%s adl� ki�inin %s model arac�na motor revizyon teklifi verir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
		pc_cmd_me(playerid, mes);
		SendSyntaxMessage(userid, "%s size ara� motoru i�in revizyon teklifi g�nderdi. (Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	}
	
	pTemp[userid][pServePlayer] = playerid;
	pTemp[userid][pServeType] = type;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}

CMD:materyalal(playerid, params[]) //����
{
	new amount;
	
	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid))								return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))	return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (!PlayerToPoint(6.0, playerid, 892.8326,-1322.4624,31.9593))
	{
		Waypoint_Set(playerid, 892.8326,-1322.4624,31.9593, 8.0);
		return SendSyntaxMessage(playerid, "Yedek par�a sat�lan yer haritan�zda i�aretlendi. (/cpsifirla)");
	}

	if (sscanf(params,"d",amount))
	{
		SendHelpMessage(playerid, "/materyalal [miktar]");
		SendSyntaxMessage(playerid, "Materyal�n 1 adeti 1 dolara e�ittir.");
		return 1;
	}

	if (amount < 1 || amount > 300)											return SendErrorMessage(playerid, "1 ile 300 aras�nda bir se�im yap�n.");
    if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] >= 300)			return SendErrorMessage(playerid, "Bulundu�unuz tamir arac�nda zaten yeterince materyal var. ");
	if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] + amount > 300)	return SendErrorMessage(playerid, "Sadece %i adet par�a alma hakk�n�z kald�.", 300 - VehicleInfo[GetPlayerVehicleID(playerid)][carComps]);
	if (GetCash(playerid) < amount)											return SendErrorMessage(playerid, "%i adet materyal i�in yeterli paran�z yok.", amount);

	GiveCash(playerid, -amount);
	SendSyntaxMessage(playerid, "%i adet materyali $%i kar��l���nda sat�n ald�n.", amount, amount);
	JobMessage(playerid, "~w~ARACA PARCALARI YERLESTIRDIN.", 6);
	VehicleInfo[GetPlayerVehicleID(playerid)][carComps] += amount;
	return 1;
}

CMD:materyallerim(playerid, params[])
{
	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid))							return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))		return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");

    SendSyntaxMessage(playerid, "Tamir arac�nda %i adet par�a bulunuyor.", VehicleInfo[GetPlayerVehicleID(playerid)][carComps]);
	return 1;
}

CMD:benzindoldur(playerid, params[])
{
	new userid, price;

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)			return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid))								return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))			return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (sscanf(params,"ud",userid,price))					return SendHelpMessage(playerid, "/benzindoldur [ID / isim] [�cret]");
	if (userid == playerid)									return SendErrorMessage(playerid, "Bu i�lemi kendine uygulayamazs�n.");
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))			return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))									return SendErrorMessage(playerid, "Belirtti�iniz ki�i ara�ta olmal�.");

    new vehicle = GetPlayerVehicleID(userid);

    if (VehicleInfo[vehicle][carFuel] >= GetVehicleFuelCapacity(GetVehicleModel(vehicle)))	
		return SendErrorMessage(playerid, "Arac�n deposu tamamen dolu.");
	if (price < 1 || price > 500)															
		return SendErrorMessage(playerid, "$1 ile $500 dolar aras�nda bir teklif sunabilirsin.");

    new mes[128];
    format(mes, sizeof(mes), "%s adl� ki�inin arac�na $%i kar��l���nda yak�t doldurmay� teklif eder.", GetNameWithMask(userid), price);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "%s adl� tamirci $%i kar��l���nda araca yak�t koymay� teklif etti. (Y tu�una basarak kabul edebilirsin)", GetNameWithMask(playerid), price);
	RefillPrice[userid] = price;
	RefillOffer[userid] = playerid;
	return 1;
}

CMD:aracboya(playerid, params[])
{
	new userid, color1, color2;

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)						return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid))											return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (!IsATowTruck(GetPlayerVehicleID(playerid)))						return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (sscanf(params,"udd", userid, color1, color2))					return SendHelpMessage(playerid, "/aracboya [ID / isim] [renk 1] [renk 2](/renkler)");
	if (color1 > 255 || color2 > 255 || color1 < 0 || color2 < 0)		return SendErrorMessage(playerid, "Renk numaras� 0 ile 255 aras�nda olmal�. /renkler");
	if (userid == playerid)												return SendErrorMessage(playerid, "Bu i�lemi kendine uygulayamazs�n.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(6.0, playerid, userid))						return SendNotNearPlayer(playerid);
	if (!IsDriver(userid))												return SendErrorMessage(playerid, "Belirtti�iniz ki�i ara�ta olmal�.");

	new vehicle = GetPlayerVehicleID(userid);

	if (VehicleInfo[vehicle][carFaction] != 0)										return SendErrorMessage(playerid, "Birlik ara�lar�na bu i�lemi uygulayamazs�n. ");
	if (VehicleInfo[GetPlayerVehicleID(playerid)][carComps] < 45)					return SendErrorMessage(playerid, "Ara� boyamak i�in 45 materyale ihtiyac�n�z var. ");
    if (pTemp[userid][pServePlayer] == playerid && pTemp[userid][pServeType] == 4)	return SendErrorMessage(playerid, "%s adl� ki�iye zaten bir teklif g�ndermi�siniz.", GetNameEx(userid));

	new mes[128];
    format(mes, sizeof(mes), "%s adl� ki�inin %s model arac�na boyama teklifi g�nderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehicle)-400]);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "%s arac�n�za boyama teklifi g�nderdi. (Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));

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

	if (PlayerInfo[playerid][pJob] != JOB_MECHANIC)		return SendErrorMessage(playerid, "Tamirci mesle�inde de�ilsiniz.");
	if (!IsDriver(playerid) || !IsATowTruck(vehicle))	return SendErrorMessage(playerid, "�ekici arac�n�n i�erisinde olmal�s�n�z.");
	if (IsTrailerAttachedToVehicle(vehicle))
	{
		DetachTrailerFromVehicle(vehicle);
		return SendErrorMessage(playerid, "�ekti�iniz arac�n kancas�n� ��kard�n�z.");
	}

	if (sscanf(params,"u", userid))						return SendHelpMessage(playerid, "/aracicek [ID / isim]");
	if (userid == playerid)								return SendErrorMessage(playerid, "Bu i�lemi kendine uygulayamazs�n.");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(8.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (!IsPlayerInAnyVehicle(userid))					return SendErrorMessage(playerid, "Belirtti�iniz ki�i ara�ta olmal�.");

	if (pTemp[userid][pServePlayer] == playerid && pTemp[userid][pServeType] == 5) 	return SendErrorMessage(playerid, "%s adl� ki�iye zaten bir teklif g�ndermi�siniz.", GetNameEx(userid));

	new vehid = GetPlayerVehicleID(userid);

    if (IsABoat(vehid) || IsAPlane(vehid) || IsAHelicopter(vehid) || IsABiker(vehid))	return SCM(playerid, COLOR_GREY,"Bu ara� �ekilemez.");

    new mes[128];
    format(mes, sizeof(mes), "%s adl� ki�inin %s model arac�n� �ekme teklifi g�nderir.", GetNameWithMask(userid), VehicleNames[GetVehicleModel(vehid)-400]);
	pc_cmd_me(playerid, mes);

	SendClientMessageEx(userid, COLOR_INFO, "* %s arac�n�za �ekme teklifi g�nderdi. (Ara�tan inip Y tu�una basarak teklifi kabul edebilirsin)", GetNameWithMask(playerid));
	SetPVarInt(userid, #tow_car, vehid);
	pTemp[userid][pServePlayer] = playerid;
	pTemp[userid][pServeType] = 5;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}