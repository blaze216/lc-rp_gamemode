alias:ehliyetal("ehliyet");
CMD:ehliyetal(playerid, params[])
{
    if (PlayerInfo[playerid][pCarLic] != 0)	return SendErrorMessage(playerid, "Zaten bir ehliyetin mevcut.");
	if (GetCash(playerid) < CARLIC_PRICE)	return SendNotCash(playerid);

	new bizid = LicenseOffice_Nearest(playerid);
	if (bizid != -1) return SendErrorMessage(playerid, "Bir ehliyet kursuna yakın olmalısın.");
	
	GiveBizCash(bizid, CARLIC_PRICE);
	GiveCash(playerid, -CARLIC_PRICE);

    SendSyntaxMessage(playerid, "Ehliyeti başarıyla aldınız ve %d$ ödediniz.", CARLIC_PRICE);

	PlayerInfo[playerid][pCarLic] = 1;

	/*
	new vehicle = GetPlayerVehicleID(playerid);
	
	if (!IsADMVCar(vehicle) && !IsADMVHeli(vehicle) && !IsADMVTaxi(vehicle)) return SendErrorMessage(playerid, "Bir ehliyet aracında olmalısınız.");
	if (!IsDriver(playerid))												 return SendErrorMessage(playerid, "Araç kullanıyor olmalısınız.");
    if (pTemp[playerid][pLicenseExam] != 0)									 return SendErrorMessage(playerid, "Zaten mevcut bir sınavdasın.");
	        
	if (IsADMVCar(vehicle))
	{
        if (PlayerInfo[playerid][pCarLic] != 0)	return SendErrorMessage(playerid, "Zaten bir ehliyetin mevcut.");
		if (GetCash(playerid) < CARLIC_PRICE)	return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Ehliyet sınavına başladnız.");
		SendSyntaxMessage(playerid, "Sınavı tamamlamak için  %i dakikanız var, aksi takdirde başarısız olursunuz.", EXAM_TIME / 60);
		
		pTemp[playerid][pLicenseExam] = 1;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, license_exam_cp[0], true);
		GiveCash(playerid, -CARLIC_PRICE);

		new bizid = LicenseOffice_Nearest(playerid);
		if (bizid != -1) GiveBizCash(bizid, CARLIC_PRICE);
	
		if (!IsPlayerInAnyVehicle(playerid)) {
			pTemp[playerid][pLicenseExam] = 0;
			DeletePVar(playerid, #exam_second);
			SendSyntaxMessage(playerid, "Araçtan indiğiniz için sınavda başarısız oldunuz.");
			TogglePlayerAllDynamicRaceCPs(playerid, false);
			RespawnVehicle(vehicle);
			return 1;
		}
	}
	else if (IsADMVHeli(vehicle))
	{
	    if (PlayerInfo[playerid][pFlyLic] != 0)	return SendErrorMessage(playerid, "Zaten bir hava aracı lisansınız mevcut.");
		if (PlayerInfo[playerid][pFlyLic] == 2)	return SendErrorMessage(playerid, "Hava aracı lisansı sahibi olarak kara listeye alındınız..");
		if (GetCash(playerid) < FLYLIC_PRICE)	return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Hava aracı lisansı sınavına başladınız.");
		SendSyntaxMessage(playerid, "[1]: Sınav sırasında hiçbir şeye çarpmamaya çalışın.");
		SendSyntaxMessage(playerid, "[2]: Dikkatli sürün ve acele etmeyin.");
		
		pTemp[playerid][pLicenseExam] = 2;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, fly_exam_cp[0], true);
		GiveCash(playerid, -FLYLIC_PRICE);
	}
	else if (IsADMVTaxi(vehicle))
	{
	    if (PlayerInfo[playerid][pCarLic] == 0)		return SendErrorMessage(playerid, "Taksi lisansı almak için öncelikle araç ehliyeti sahibi olmalısınız..");
        if (PlayerInfo[playerid][pTaxiLic] != 0)	return SendErrorMessage(playerid, "Zaten bir taksi lisansınız mevcut..");
		if (PlayerInfo[playerid][pTaxiLic] == 2)	return SendErrorMessage(playerid, "Taksi lisansınız kara listeye alındı..");
		if (GetCash(playerid) < TAXILIC_PRICE)		return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Taksi lisans sınavına başladınız.");
		SendSyntaxMessage(playerid, "Sınavı tamamlamak için  %i dakikanız var, aksi takdirde başarısız olursunuz.", EXAM_TIME / 60);

		pTemp[playerid][pLicenseExam] = 3;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, license_exam_cp[0], true);
		GiveCash(playerid, -TAXILIC_PRICE);

		new bizid = LicenseOffice_Nearest(playerid);

		if (bizid != -1)	GiveBizCash(bizid, TAXILIC_PRICE);
	}*/
	return 1;
}