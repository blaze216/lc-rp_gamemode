Dialog:VehicleFines(playerid, response, listitem, inputtext[])
{
	if (!response)						return 1;

	new vehicle;
	if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
	{
		vehicle = GetPVarInt(playerid, #tickets_show); 
	}
	else 
	{
		if (!IsPlayerInAnyVehicle(playerid))	
			return SendNotInVehicle(playerid);

		vehicle = GetPlayerVehicleID(playerid);

		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])
			return SendErrorMessage(playerid, "Bu aracýn sahibi deðilsiniz.");
	}
    
	new query[255];
	if (listitem == 0 && pTemp[playerid][pDialogList])
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `paid`=0 AND `id` > %i LIMIT %i", VehicleInfo[vehicle][carID], Tickets[playerid][0][tID], MAX_TICKETS);
		mysql_tquery(dbHandle, query, "ShowCarsTickets", "ii", playerid, 1);
		pTemp[playerid][pDialogList]--;
		return 1;
	}
	
	else if ((listitem == MAX_TICKETS + 1 && pTemp[playerid][pDialogList]) || (listitem == MAX_TICKETS && !pTemp[playerid][pDialogList]))
	{		
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `paid`=0 AND `id` < %i ORDER BY `id` DESC LIMIT %i", VehicleInfo[vehicle][carID], Tickets[playerid][MAX_TICKETS-1][tID], MAX_TICKETS);
		mysql_tquery(dbHandle, query, "ShowCarsTickets", "ii", playerid, 0);
		pTemp[playerid][pDialogList]++;
		return 1;
	}

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `id`=%i LIMIT 1", 
		VehicleInfo[vehicle][carID], 
		(!pTemp[playerid][pDialogList])?(Tickets[playerid][listitem][tID]):(Tickets[playerid][listitem-1][tID]));
	mysql_tquery(dbHandle, query, "ShowCarTicket", "ii", playerid, vehicle);

	return 1;
}

Dialog:VehicleFinesTake(playerid, response, listitem, inputtext[])
{
	if (!response)	
	{
		if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
			return pc_cmd_araccezakontrol(playerid, ""); 
		else return pc_cmd_aracceza(playerid, "");
	}

    new vehicle = GetPlayerVehicleID(playerid);

	if (vehicle == 0)													return SendNotInVehicle(playerid);
	if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu aracýn sahibi deðilsiniz.");
	if (GetCash(playerid) < Ticket[playerid][tAmount])                  return SendErrorMessage(playerid, "Yeterince paran yok.");

    GiveCash(playerid, -Ticket[playerid][tAmount]);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `tickets` SET `paid`=1 WHERE `id`=%i", Ticket[playerid][tID]);
	mysql_tquery(dbHandle, query, "VehicleFineTook", "i", playerid);

    for(new i = 0; i < MAX_TICKETS; i++) Tickets[playerid][i][tID] = 0;
	return 1;
}

this::VehicleFineTook(playerid)
{
	SM1(playerid, "Faturayý baþarýyla ödediniz.");
	pc_cmd_server_ame(playerid, "faturayý alýr ve ödeme yapar.");
	return 1;
}

Dialog:ShowPlayerFinesShow(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new userid;
	if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
	{
		userid = GetPVarInt(playerid, #tickets_show); 
	}
	else 
	{
		userid = playerid;
	}
    
	new query[555];
	if (listitem == 0 && pTemp[playerid][pDialogList])
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i AND `paid`=0 AND `id` > %i LIMIT %i", PlayerInfo[userid][pID], Tickets[playerid][0][tID], MAX_TICKETS);
		mysql_tquery(dbHandle, query, "ShowPlayersTickets", "ii", playerid, 1);
		pTemp[playerid][pDialogList]--;
		return 1;
	}

	else if ((listitem == MAX_TICKETS + 1 && pTemp[playerid][pDialogList]) || (listitem == MAX_TICKETS && !pTemp[playerid][pDialogList]))
	{	
		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i AND `paid`=0 AND `id` < %i ORDER BY `id` DESC LIMIT %i", PlayerInfo[userid][pID], Tickets[playerid][MAX_TICKETS-1][tID], MAX_TICKETS);
		mysql_tquery(dbHandle, query, "ShowPlayersTickets", "ii", playerid, 0);
		pTemp[playerid][pDialogList]++;
		return 1;
	}
	
	mysql_format(dbHandle, query, sizeof(query), "SELECT t.*, u.`name` as ownername FROM `tickets` t LEFT JOIN `users` u ON t.`userid` = u.`id` WHERE t.`userid` = %i AND u.`id` = %i AND t.`id` = %i LIMIT %i", 
		PlayerInfo[userid][pID], PlayerInfo[userid][pID], 
		Tickets[playerid][listitem][tID], MAX_TICKETS);
	mysql_tquery(dbHandle, query, "ShowPlayerTicket", "i", playerid);
	
	return 1;
}


Dialog:PlayerFinesPay(playerid, response, listitem, inputtext[])
{
	if (!response)	
	{
		if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty] && GetPVarInt(playerid, #ticketsuse))
			return pc_cmd_cezakontrol(playerid, ""); 
		else return pc_cmd_cezalarim(playerid, "");
	}
	
    if (!Bank_Nearest(playerid))	return SendErrorMessage(playerid, "Cezayý ödemek için bankada olmalýsýnýz.");

	if (GetCash(playerid) < Tickets[playerid][0][tAmount])	return SendErrorMessage(playerid, "Cezayý ödemek  için yeterli paranýz yok, $%i.", Ticket[playerid][tAmount]);

	SM1(playerid, "Ceza ödediniz: \"%.20s...\", ödenen $%i.", Ticket[playerid][tReason], Ticket[playerid][tAmount]);
    SendHelpMessage(playerid, "Ödenmemiþ cezalarýnýz var - %i.", CountPlayerTickets(playerid)-1);
	GiveCash(playerid, -Ticket[playerid][tAmount]);
	
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `tickets` SET `paid`= 1 WHERE `id`=%i", Ticket[playerid][tID]);
	mysql_tquery(dbHandle, query);

	return 1;
} //î