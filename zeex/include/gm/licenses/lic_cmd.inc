alias:ehliyetal("ehliyet");
CMD:ehliyetal(playerid, params[])
{
    if (PlayerInfo[playerid][pCarLic] != 0)	return SendErrorMessage(playerid, "Zaten bir ehliyetin mevcut.");
	if (GetCash(playerid) < CARLIC_PRICE)	return SendNotCash(playerid);

	new bizid = LicenseOffice_Nearest(playerid);
	if (bizid != -1) return SendErrorMessage(playerid, "Bir ehliyet kursuna yak�n olmal�s�n.");
	
	GiveBizCash(bizid, CARLIC_PRICE);
	GiveCash(playerid, -CARLIC_PRICE);

    SendSyntaxMessage(playerid, "Ehliyeti ba�ar�yla ald�n�z ve %d$ �dediniz.", CARLIC_PRICE);

	PlayerInfo[playerid][pCarLic] = 1;

	/*
	new vehicle = GetPlayerVehicleID(playerid);
	
	if (!IsADMVCar(vehicle) && !IsADMVHeli(vehicle) && !IsADMVTaxi(vehicle)) return SendErrorMessage(playerid, "Bir ehliyet arac�nda olmal�s�n�z.");
	if (!IsDriver(playerid))												 return SendErrorMessage(playerid, "Ara� kullan�yor olmal�s�n�z.");
    if (pTemp[playerid][pLicenseExam] != 0)									 return SendErrorMessage(playerid, "Zaten mevcut bir s�navdas�n.");
	        
	if (IsADMVCar(vehicle))
	{
        if (PlayerInfo[playerid][pCarLic] != 0)	return SendErrorMessage(playerid, "Zaten bir ehliyetin mevcut.");
		if (GetCash(playerid) < CARLIC_PRICE)	return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Ehliyet s�nav�na ba�ladn�z.");
		SendSyntaxMessage(playerid, "S�nav� tamamlamak i�in  %i dakikan�z var, aksi takdirde ba�ar�s�z olursunuz.", EXAM_TIME / 60);
		
		pTemp[playerid][pLicenseExam] = 1;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, license_exam_cp[0], true);
		GiveCash(playerid, -CARLIC_PRICE);

		new bizid = LicenseOffice_Nearest(playerid);
		if (bizid != -1) GiveBizCash(bizid, CARLIC_PRICE);
	
		if (!IsPlayerInAnyVehicle(playerid)) {
			pTemp[playerid][pLicenseExam] = 0;
			DeletePVar(playerid, #exam_second);
			SendSyntaxMessage(playerid, "Ara�tan indi�iniz i�in s�navda ba�ar�s�z oldunuz.");
			TogglePlayerAllDynamicRaceCPs(playerid, false);
			RespawnVehicle(vehicle);
			return 1;
		}
	}
	else if (IsADMVHeli(vehicle))
	{
	    if (PlayerInfo[playerid][pFlyLic] != 0)	return SendErrorMessage(playerid, "Zaten bir hava arac� lisans�n�z mevcut.");
		if (PlayerInfo[playerid][pFlyLic] == 2)	return SendErrorMessage(playerid, "Hava arac� lisans� sahibi olarak kara listeye al�nd�n�z..");
		if (GetCash(playerid) < FLYLIC_PRICE)	return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Hava arac� lisans� s�nav�na ba�lad�n�z.");
		SendSyntaxMessage(playerid, "[1]: S�nav s�ras�nda hi�bir �eye �arpmamaya �al���n.");
		SendSyntaxMessage(playerid, "[2]: Dikkatli s�r�n ve acele etmeyin.");
		
		pTemp[playerid][pLicenseExam] = 2;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, fly_exam_cp[0], true);
		GiveCash(playerid, -FLYLIC_PRICE);
	}
	else if (IsADMVTaxi(vehicle))
	{
	    if (PlayerInfo[playerid][pCarLic] == 0)		return SendErrorMessage(playerid, "Taksi lisans� almak i�in �ncelikle ara� ehliyeti sahibi olmal�s�n�z..");
        if (PlayerInfo[playerid][pTaxiLic] != 0)	return SendErrorMessage(playerid, "Zaten bir taksi lisans�n�z mevcut..");
		if (PlayerInfo[playerid][pTaxiLic] == 2)	return SendErrorMessage(playerid, "Taksi lisans�n�z kara listeye al�nd�..");
		if (GetCash(playerid) < TAXILIC_PRICE)		return SendNotCash(playerid);

		VehicleEngine(vehicle, true);
		SendSyntaxMessage(playerid, "Taksi lisans s�nav�na ba�lad�n�z.");
		SendSyntaxMessage(playerid, "S�nav� tamamlamak i�in  %i dakikan�z var, aksi takdirde ba�ar�s�z olursunuz.", EXAM_TIME / 60);

		pTemp[playerid][pLicenseExam] = 3;
		SetPVarInt(playerid, #exam_second, EXAM_TIME);
		TogglePlayerDynamicRaceCP(playerid, license_exam_cp[0], true);
		GiveCash(playerid, -TAXILIC_PRICE);

		new bizid = LicenseOffice_Nearest(playerid);

		if (bizid != -1)	GiveBizCash(bizid, TAXILIC_PRICE);
	}*/
	return 1;
}