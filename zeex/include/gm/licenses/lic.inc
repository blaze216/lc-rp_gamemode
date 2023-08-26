License_OnGameModeInit()
{
    for(new i; i != sizeof(license_exam_cp)-1; i++)
	{
	    license_exam_cp[i] = CreateDynamicRaceCP(0, license_exam_coord[i][0], license_exam_coord[i][1], license_exam_coord[i][2], license_exam_coord[i+1][0], license_exam_coord[i+1][1], license_exam_coord[i+1][2], 4.0, 0, 0, -1, 1000.0);
	}

    license_exam_cp[sizeof(license_exam_cp)-1] = CreateDynamicRaceCP(1, license_exam_coord[sizeof(license_exam_cp)-1][0], license_exam_coord[sizeof(license_exam_cp)-1][1], license_exam_coord[sizeof(license_exam_cp)-1][2], 0.0, 0.0, 0.0, 4.0, 0, 0, -1, 1000.0);
    
    for(new i; i != sizeof(fly_exam_cp)-1; i++)
	{
	    fly_exam_cp[i] = CreateDynamicRaceCP(3, fly_exam_coord[i][0], fly_exam_coord[i][1], fly_exam_coord[i][2], fly_exam_coord[i+1][0], fly_exam_coord[i+1][1], fly_exam_coord[i+1][2], 4.0);
	}

    fly_exam_cp[sizeof(fly_exam_cp)-1] = CreateDynamicRaceCP(1, fly_exam_coord[sizeof(fly_exam_cp)-1][0], fly_exam_coord[sizeof(fly_exam_cp)-1][1], fly_exam_coord[sizeof(fly_exam_cp)-1][2], 0.0, 0.0, 0.0, 4.0, 0, 0, -1, 1000.0);
    
	return 1;
}

Lic_OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
    if (pTemp[playerid][pLicenseExam] == 1 || pTemp[playerid][pLicenseExam] == 3)
	{
	    for(new i; i != sizeof(license_exam_cp); i++)
		{
		    if (license_exam_cp[i] != checkpointid) continue;
		        
			if (i == sizeof(license_exam_cp)-1)
			{
			    new Float:health, vehicleid = GetPlayerVehicleID(playerid);
				AntiCheatGetVehicleHealth(vehicleid, health);

				if (GetPVarInt(playerid, #exam_second) <= 0) SendSyntaxMessage(playerid, "Zamanýn doldu. Baþarýsýz oldun.");
				
				else if (health >= GetVehicleMaxHealth(vehicleid)-50.0)
				{
					if (pTemp[playerid][pLicenseExam] == 1)	PlayerInfo[playerid][pCarLic] = 1;
					else									PlayerInfo[playerid][pTaxiLic] = 1;
						    
					SendSyntaxMessage(playerid, "Tebrikler!  %s sýnavýný baþarýyla geçtiniz.  /licenses komutuyla kontrol edebilirsiniz..", (pTemp[playerid][pLicenseExam])?("sürücü"):("taksi"));
				}
				else	
				{
					SendSyntaxMessage(playerid, "Düzgün araç sürmediðiniz için baþarýsýz oldunuz.");
				}	

				pTemp[playerid][pLicenseExam] = 0;
				DeletePVar(playerid, #exam_second);
				RespawnVehicle(vehicleid);
			    TogglePlayerDynamicRaceCP(playerid, license_exam_cp[i], false);
			    return 1;
			}

            TogglePlayerDynamicRaceCP(playerid, license_exam_cp[i], false);
            TogglePlayerDynamicRaceCP(playerid, license_exam_cp[i+1], true);
			return 1;
		}
	}

	else if (pTemp[playerid][pLicenseExam] == 2)
	{
	    for(new i; i != sizeof(fly_exam_cp); i++)
		{
		    if (fly_exam_cp[i] != checkpointid) continue;

			if (i == sizeof(fly_exam_cp)-1)
			{
			    new Float:health, vehicleid = GetPlayerVehicleID(playerid);

				AntiCheatGetVehicleHealth(vehicleid, health);

				if (health >= 950.0)
				{
				    if (GetPVarInt(playerid, #exam_second) <= 100)
					{
						PlayerInfo[playerid][pFlyLic] = 1; //ïîëåòû
						SendSyntaxMessage(playerid, "Tebrikler! Baþarýyla hava aracý lisansý aldýnýz. /lisanslar komutuyla kontrol edebilirsiniz.");
					}
					else
					{
						SendSyntaxMessage(playerid, "Çok hýzlý gittiðiniz için sýnav iptal edildi.");
					}
				}
				else
				{
				    SendSyntaxMessage(playerid, "Tehlikeli veya düzgün sürmediðiniz için sýnavýnýz iptal edildi.");
				}
				    
				pTemp[playerid][pLicenseExam] = 0;
				DeletePVar(playerid, #exam_second);
				SetPlayerPos(playerid, 1765.36, -2272.22, 26.796);
				RespawnVehicle(vehicleid);
			    TogglePlayerDynamicRaceCP(playerid, fly_exam_cp[i], false);
			    return 1;
			}
            TogglePlayerDynamicRaceCP(playerid, fly_exam_cp[i], false);
            TogglePlayerDynamicRaceCP(playerid, fly_exam_cp[i+1], true);
			return 1;
		}
	}
    return 1;
}

Lic_OnPlayerStateChange(playerid, newstate) 
{
    if (newstate == PLAYER_STATE_DRIVER)
    {
		new vehicle = GetPlayerVehicleID(playerid);
		
	    if (IsADMVCar(vehicle) && !PlayerInfo[playerid][pCarLic])	SendClientMessageEx(playerid, COLOR_WHITE, "Araç Lisansý: Lisans sýnavýna baþlamak için /ehliyet komutunu kullanabilirsiniz, sýnava baþlamak için gerekli para: {33AA33}$%i{FFFFFF}.",CARLIC_PRICE);
	    if (IsADMVHeli(vehicle) && !PlayerInfo[playerid][pFlyLic])	SendClientMessageEx(playerid, COLOR_WHITE, "Hava Aracý Lisansý: Lisans sýnavýna baþlamak için /ehliyet komutunu kullanabilirsiniz, sýnava baþlamak için gerekli para: {33AA33}$%i{FFFFFF}.",FLYLIC_PRICE);
	    if (IsADMVTaxi(vehicle) && !PlayerInfo[playerid][pTaxiLic])	SendClientMessageEx(playerid, COLOR_WHITE, "Taksi Lisansý: Lisans sýnavýna baþlamak için /ehliyet komutunu kullanabilirsiniz, sýnava baþlamak için gerekli para: {33AA33}$%i{FFFFFF}.",TAXILIC_PRICE);
    }
    return 1;
}

License_OnPlayerExitVehicle(playerid, vehicleid)
{
    if (pTemp[playerid][pLicenseExam])
	{
	    pTemp[playerid][pLicenseExam] = 0;
		DeletePVar(playerid, #exam_second);
		SendSyntaxMessage(playerid, "Araçtan indiðiniz için sýnavda baþarýsýz oldunuz.");
		TogglePlayerAllDynamicRaceCPs(playerid, false);
		RespawnVehicle(vehicleid);
	}
    return 1;
}