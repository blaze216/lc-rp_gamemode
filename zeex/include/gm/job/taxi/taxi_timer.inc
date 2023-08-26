forward Taxi_FiveSecTimer();
public Taxi_FiveSecTimer()
{
    foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || !TaxiDuty[i] || TaxiPassenger[i] == INVALID_PLAYER_ID)     continue;

		new targetid = TaxiPassenger[i], vehicle = GetPlayerVehicleID(i);

		new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;

	    GetPlayerPos(i, x, y, z);
	    GetZone(x, y, location, MAX_ZONE_NAME);

		if (!IsDriver(i))
		{
		    new mes[32];
   			format(mes, sizeof(mes),"~r~+$%i TOPLAM: $%i", TaxiMoney[i], TaxiMade[i]);
	    	GameTextForPlayer(i, mes, 2000, 1);

        	TaxiPassenger[i] = INVALID_PLAYER_ID;
        	TaxiMoney[i] = 0;
        	continue;
		}  

		if (!IsPlayerLogged(targetid) || !IsPlayerInVehicle(targetid, vehicle))
		{
		    new mes[32];
   			format(mes, sizeof(mes),"~r~+$%i TOPLAM: $%i", TaxiMoney[i], TaxiMade[i]);
	    	GameTextForPlayer(i, mes, 2000, 1);

        	TaxiPassenger[i] = INVALID_PLAYER_ID;
        	TaxiMoney[i] = 0;
        	continue;
		}

        if(strfind(location, "Portland View", true) != -1 || strfind(location, "Little Italy", true) != -1 || strfind(location, "Chinatown", true) != -1 && GetVehicleSpeed(vehicle) > 15)
		{
			TaxiMade[i] += 3;
		}

		if (GetCash(targetid) >= TaxiFare[i])
		{
		    GiveCash(targetid, -TaxiFare[i]);
		    TaxiMade[i] += TaxiFare[i];
			TaxiMoney[i] += TaxiFare[i];

			new mes[32];
   			format(mes, sizeof(mes),"~y~UCRET: $%i", TaxiMoney[i]);
	    	GameTextForPlayer(i, mes, 5050, 1);
	    	GameTextForPlayer(targetid, mes, 5050, 1);
		}
		else
		{
		    new mes[32];
   			format(mes, sizeof(mes),"~r~+$%i TOPLAM: $%i", TaxiMoney[i], TaxiMade[i]);
	    	GameTextForPlayer(i, mes, 2000, 1);
		    SendSyntaxMessage(i, "Yolcunun parasý bitti, bedavaya taþýyorsun.");
		    TaxiPassenger[i] = INVALID_PLAYER_ID;
		    TaxiMoney[i] = 0;
		}
	}
	SetTimer("Taxi_FiveSecTimer", 5000, false);
	return 1;
}