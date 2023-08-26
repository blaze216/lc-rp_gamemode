Server_OnGameModeInit()
{
    SendRconCommand("mapname "MAP_NAME"");
	SendRconCommand("hostname "ServerName"");
    
    DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	AllowInteriorWeapons(1);
	EnableStuntBonusForAll(0);
 	DisableNameTagLOS();
	ShowPlayerMarkers(0);
	LimitPlayerMarkerRadius(15.0);
	SetNameTagDrawDistance(20.0);
	SetGameModeText(GameModeText);

	SetCrashDetectLongCallTime(0);
	DisableCrashDetectLongCall();

	mysql_tquery(dbHandle, "SELECT * FROM server_settings", "OnServerSettingsLoaded", "");

	mysql_tquery(dbHandle, "SELECT id FROM ozel_modeller", "LoadModels");
	
	//Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 800);
    return 1;
}

this::OnServerSettingsLoaded()
{
	new rows = cache_num_rows();

	if(rows)
	{
		cache_get_value(0, "hostname", ServerInfo[sHostName], 64);
		cache_get_value(0, "weburl", ServerInfo[sWebUrl], 64);
		cache_get_value(0, "language", ServerInfo[sLanguage], 64);
		cache_get_value(0, "map", ServerInfo[sMap], 32);
		cache_get_value(0, "version", ServerInfo[sVersion], 32);
		cache_get_value_int(0, "maintenance", ServerInfo[sMaintenance]);
		cache_get_value(0, "password", ServerInfo[sPassword], 64);
		cache_get_value_int(0, "weather", ServerInfo[sWeather]);
		cache_get_value_int(0, "price_payday", ServerInfo[sPricePayday]);
		cache_get_value_int(0, "price_park", ServerInfo[sPricePark]);
		cache_get_value_float(0, "dealership_percent", ServerInfo[sDealershipPercent]);

		if(ServerInfo[sMaintenance] && ServerInfo[sPassword] != '0')
		{
			SendRconCommand(sprintf("hostname [BAKIM] %s", ServerInfo[sHostName]));
			SendRconCommand(sprintf("password %s", ServerInfo[sPassword]));
		}

		else SendRconCommand(sprintf("hostname %s", ServerInfo[sHostName]));

		SendRconCommand(sprintf("weburl %s", ServerInfo[sWebUrl]));
		SendRconCommand(sprintf("language %s", ServerInfo[sLanguage]));
		SendRconCommand(sprintf("mapname %s", ServerInfo[sMap]));
		SetGameModeText(ServerInfo[sVersion]);
		
		cache_get_value_int(0, "price_taxi_license", ServerInfo[sPriceTaxiLicense]);
		
		cache_get_value_float(0, "price_vehicle_register_percent", ServerInfo[sPriceVehRegisterPercent]);
		cache_get_value_float(0, "price_vehicle_weekly_tax_percent", ServerInfo[sPriceVehWeeklyTaxPercent]);

		cache_get_value_int(0, "price_driver_license", ServerInfo[sPriceDriverLicense]);

		cache_get_value_int(0, "price_fuel", ServerInfo[sPriceFuel]);
		
		cache_get_value_float(0, "locale_sale_percent", ServerInfo[sLocaleSalePercent]);

		SetWeather(ServerInfo[sWeather]);

		ServerInfo[sDoublePayday] = false;

		ServerInfo[sPriceColour] = 250;
		ServerInfo[sPriceInsurance] = 100;
	}

	else printf("[!] Sunucu ayarlari alinamadi.");

	return 1;
}