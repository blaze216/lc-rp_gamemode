this::ShowCarsTickets(playerid, back)
{
	new 
		fetch[128], 
		string[3500]
	;

    if (cache_num_rows())
    {
		format(string, sizeof(string), "#\tFiyat\tAçýklama\tTarih");
		if (pTemp[playerid][pDialogList]) format(string, sizeof(string), "%s\n{bccd32}<<{FFFFFF}", string);

		if (!back)
		{
			for(new i = 0; i < cache_num_rows(); i++)
			{
				new 
					amount,
					reason[128]
				;

				cache_get_value_int(i, "amount", amount);

				cache_get_value(i, "reason", fetch);
				format(reason, sizeof(reason), fetch);

				cache_get_value_int(i, "id", Tickets[playerid][i][tID]);
				cache_get_value(i, "date", fetch);
				format(string, sizeof(string), "%s\n%i\t$%d\t%.50s...\t%s", string, i+1+pTemp[playerid][pDialogList]*MAX_TICKETS, amount, reason, fetch);
			}
		} else {
			for(new i = cache_num_rows()-1; i >= 0; i--)
			{
				new 
					amount,
					reason[128]
				;

				cache_get_value_int(i, "amount", amount);
	
				cache_get_value(i, "reason", fetch);
				format(reason, sizeof(reason), fetch);

				cache_get_value_int(i, "id", Tickets[playerid][cache_num_rows()-1-i][tID]);
				cache_get_value(i, "date", fetch);
				format(string, sizeof(string), "%s\n%i\t$%d\t%.50s...\t%s", string, cache_num_rows()-i+pTemp[playerid][pDialogList]*MAX_TICKETS, amount, reason, fetch);
			}
		}
		new vehicle;
		cache_get_value_int(0, "vehicle", vehicle);
		if (CountVehicleIDTickets(vehicle) > MAX_TICKETS*(pTemp[playerid][pDialogList]+1)) format(string, sizeof(string), "%s\n{bccd32}>>", string);
    }
    else return SendWarningMessage(playerid, "Bu aracýn herhangi bir cezasý yok.");

	return Dialog_Show(playerid, VehicleFines, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF} Ödenmemiþ cezalarýn listesi", string, "Seç", "Kapat");
}

this::ShowCarTicket(playerid, vehicle)
{
	new 
		fetch[128], 
		mes[256],
		vehicleid = vehicle
	;
    if (!cache_num_rows())	return 1;
	
	cache_get_value_int(0, "id", Ticket[playerid][tID]);
	
	format(mes, sizeof(mes), "{a9c4e4}Uygulanan Araç:\t\t {ffffff}%s\n", VehicleNames[GetVehicleModel(vehicleid)-400]); 

	cache_get_value(0, "officer", fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Memur:\t\t {ffffff}%s ", mes, fetch);

	cache_get_value(0, "faction", fetch);
	format(mes, sizeof(mes), "%s[%s]\n", mes, GetInitials(Factions[strval(fetch)][fName]));

	cache_get_value_int(0, "amount", Ticket[playerid][tAmount]);
	format(mes, sizeof(mes), "%s{a9c4e4}Ücret:\t\t\t {ffffff}$%i{a9c4e4}\n", mes, Ticket[playerid][tAmount]);

	cache_get_value(0, "date", fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Tarih:\t\t\t {ffffff}%s\n\n", mes, fetch);

	cache_get_value(0, "reason", fetch);
	format(Ticket[playerid][tReason], 128, "%s", fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Açýklama:{ffffff}\n%s", mes, Ticket[playerid][tReason]);

	if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{F5DEB3}Ceza detaylarý", mes, "Kapat", "");
	else Dialog_Show(playerid, VehicleFinesTake, DIALOG_STYLE_MSGBOX, "{F5DEB3}Ceza detaylarý", mes, "Ödeme Yap", "Geri Dön");

	return 1;
}

this::ShowPlayersTickets(playerid, back)
{
	new 
		fetch[128], 
		string[600]
	;

    if (cache_num_rows())
    {
		format(string, sizeof(string), "#\tFiyat\tAçýklama\tTarih");
		if (pTemp[playerid][pDialogList]) format(string, sizeof(string), "%s\n{bccd32}<<{FFFFFF}", string);

		if (!back)
		{
			for(new i = 0; i < cache_num_rows(); i++)
			{
				new 
					amount,
					reason[12]
				;

				cache_get_value_int(i, "amount", amount);

				cache_get_value(i, "reason", fetch);
				format(reason, sizeof(reason), fetch);

				cache_get_value_int(i, "id", Tickets[playerid][i][tID] );

				cache_get_value(i, "date", fetch);
				format(string, sizeof(string), "%s\n%i\t$%d\t%.50s...\t%s", string, i+1+pTemp[playerid][pDialogList]*MAX_TICKETS, amount, reason, fetch);
			}
		}
		else
		{
			for(new i = cache_num_rows()-1; i >= 0; i--)
			{
				new 
					amount,
					reason[12]
				;

				cache_get_value_int(i, "amount", amount);

				cache_get_value(i, "reason", fetch);
				format(reason, sizeof(reason), fetch);

				cache_get_value_int(i, "id", Tickets[playerid][cache_num_rows()-1-i][tID]);

				cache_get_value(i, "date", fetch);
				format(string, sizeof(string), "%s\n%i\t$%d\t%.50s...\t%s", string, cache_num_rows()-i+pTemp[playerid][pDialogList]*MAX_TICKETS, amount, reason, fetch);
			}
		}
		
		if (CountPlayerTickets(playerid) > MAX_TICKETS*(pTemp[playerid][pDialogList]+1)) format(string, sizeof(string), "%s\n{bccd32}>>", string);
    }
    else return SendWarningMessage(playerid, "Ödenmemiþ ceza yok!");

	Dialog_Show(playerid, ShowPlayerFinesShow, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Ödenmemiþ Ceza Listesi", string, "Seç", "Kapat");
	return 1;
}


this::ShowPlayerTicket(playerid)
{
	new fetch[128], 
		mes[256],
		ownername[MAX_PLAYER_NAME]
	;

    if (!cache_num_rows())	return 1;
	
	cache_get_value_int(0, "id", Ticket[playerid][tID]);

	cache_get_value(0, "name", ownername);
	strreplace(fetch, '_', ' ');
	format(mes, sizeof(mes), "{a9c4e4}Kiþi:\t\t {ffffff}%s\n", ownername);

	cache_get_value(0, "officer", fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Memur:\t\t {ffffff}%s ", mes, fetch);

	cache_get_value(0, "faction", fetch);
	format(mes, sizeof(mes), "%s[%s]\n", mes, GetInitials(Factions[strval(fetch)][fName]));

	cache_get_value_int(0, "amount", Ticket[playerid][tAmount]);
	format(mes, sizeof(mes), "%s{a9c4e4}Fiyat:\t\t\t {ffffff}$%i\n", mes, Ticket[playerid][tAmount]);

	cache_get_value(0, "date", fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Tarih:\t\t\t {ffffff}%s\n\n", mes, fetch);

	cache_get_value(0, "reason", fetch);
	format(Ticket[playerid][tReason], 128, fetch);
	format(mes, sizeof(mes), "%s{a9c4e4}Açýklama:{ffffff}\n%s", mes, fetch);

	if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{F5DEB3}Ceza Ayrýntýlarý", mes, "Kapat", "");
	else Dialog_Show(playerid, PlayerFinesPay, DIALOG_STYLE_MSGBOX, "{F5DEB3}Ceza Ayrýntýlarý", mes, "Öde", "Geri");

	return 1;
}

GivePlayerTicket(officerid, playerid, amount, reason[], iscam = 0)
{  
    new query[96 + 11 + MAX_PLAYER_NAME + 1 + 64 + 24 + 1];

	if (!iscam)
	{
    	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `tickets` (userid, officer, faction, amount, reason, date) VALUES (%i, '%e', %i, %i, '%e', '%s')", PlayerInfo[playerid][pID], GetNameEx(officerid), PlayerInfo[officerid][pFaction], amount, reason, GetFullDate());
	}
	else
	{
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `tickets` (userid, officer, faction, amount, reason, date) VALUES (%i, 'Hýz Kamerasý', 3, %i, '%e', '%s')", playerid, amount, reason, GetFullDate());
	}
    
	mysql_tquery(dbHandle, query);
	return 1;
}

GiveVehicleTicket(officerid, vehicle, amount, reason[], iscam = 0)
{
    new query[97 + 11 + MAX_PLAYER_NAME + 1 + 64 + 24 + 1];

	if (!iscam)
	{
    	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `tickets` (vehicle, officer, faction, amount, reason, date) VALUES (%i, '%e', %i, %i, '%e', '%s')", VehicleInfo[vehicle][carID], GetNameEx(officerid), PlayerInfo[officerid][pFaction], amount, reason, GetFullDate());
	}
	else
	{
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `tickets` (vehicle, officer, faction, amount, reason, date) VALUES (%i, 'Hýz Kamerasý', 3, %i, '%e', '%s')", VehicleInfo[vehicle][carID], amount, reason, GetFullDate());
	}
	mysql_tquery(dbHandle, query);
	return 1;
}//ï¿½

DeleteVehicleTickets(vehicle)
{
	new query[256];
  	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `tickets` WHERE `vehicle`=%i", VehicleInfo[vehicle][carID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

DeletePlayerTickets(playerid)
{
	new query[256];
  	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `tickets` WHERE `userid`=%i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

CountPlayerTickets(playerid)
{
	new 
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `userid` = %i AND `paid` = 0", PlayerInfo[playerid][pID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
     
	cache_get_value_int(0, "total", count); 

	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}


CountPlayerTicketsID(userid)
{
	new 
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `userid` = %i AND `paid` = 0", userid);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
     
	cache_get_value_int(0, "total", count); 
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}

CountVehicleTickets(vid)
{
	new query[512];

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `vehicle` = %i AND `paid` = 0", VehicleInfo[vid][carID]);
	new Cache:cache = mysql_query(dbHandle, query), count;
	
	cache_get_value_int(0, "total", count); 
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}
 
CountVehicleIDTickets(vid)
{
	new query[512];

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `vehicle` = %i AND `paid` = 0", vid);
	new Cache:cache = mysql_query(dbHandle, query), count;
    cache_get_value_int(0, "total", count); 
	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}

/*
MDC_CountPlayerTickets(playerid)
{
	new 
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `userid` = %i", PlayerInfo[playerid][pID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count = cache_get_value_int(0, "total");
	
	cache_delete(cache);
	return count;
}

MDC_CountVehicleTickets(vehicle)
{
	new 
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `vehicle` = %i", VehicleInfo[vehicle][carID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count = cache_get_value_int(0, "total");
	
	cache_delete(cache);
	return count;
}*/