Taxi_OnPlayerStateChange(playerid, newstate)
{
    if (newstate == PLAYER_STATE_PASSENGER)
	{
	    new vehicle = GetPlayerVehicleID(playerid), driver = VehicleInfo[vehicle][carDriver];
        if (IsPlayerLogged(driver) && TaxiDuty[driver] && TaxiPassenger[driver] == INVALID_PLAYER_ID)
        {
            if (GetCash(playerid) < TaxiFare[driver])
			{
		 		SendErrorMessage(playerid, "Yeterli paranýz bulunmuyor.");
		 		SendErrorMessage(driver, "Yolcunun yeterli parasý yok.");
		 		return 1;
			}
			TaxiPassenger[driver] = playerid;
            SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSI] %s kiþisinin taksisini tuttunuz. Ücretlendirme: $%i/5 saniye.", GetNameEx(driver), TaxiFare[driver]);
		}
	}
    return 1;
}