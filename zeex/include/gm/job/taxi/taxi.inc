Taxi_OnPlayerStateChange(playerid, newstate)
{
    if (newstate == PLAYER_STATE_PASSENGER)
	{
	    new vehicle = GetPlayerVehicleID(playerid), driver = VehicleInfo[vehicle][carDriver];
        if (IsPlayerLogged(driver) && TaxiDuty[driver] && TaxiPassenger[driver] == INVALID_PLAYER_ID)
        {
            if (GetCash(playerid) < TaxiFare[driver])
			{
		 		SendErrorMessage(playerid, "Yeterli paran�z bulunmuyor.");
		 		SendErrorMessage(driver, "Yolcunun yeterli paras� yok.");
		 		return 1;
			}
			TaxiPassenger[driver] = playerid;
            SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSI] %s ki�isinin taksisini tuttunuz. �cretlendirme: $%i/5 saniye.", GetNameEx(driver), TaxiFare[driver]);
		}
	}
    return 1;
}