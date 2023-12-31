alias:garaj("g");
CMD:garaj(playerid, params[])
{
	new id = GetNearGarage(playerid);

	if (id == -1)	return SendErrorMessage(playerid, "Garaj�n yak�n�nda de�ilsiniz.");

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "(/g)araj [bilgi / satinal / sistemesat / kapitamir]");
		return 1;
	}

	if (CompareStrings(option, "bilgi"))
	{
		new dialog_header[64] = "{FFFFFF}Bilgi\t{FFFFFF}De�er\n", dialog_body[1024], temp[128];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

		format(temp, sizeof(temp), "ID\t%i\n�cret\t%i\nKap�\t%s\n", id, GarageInfo[id][garagePrice], (GarageInfo[id][garageLocked]) ? ("Kilitli") : ("A��k"));
		strcat(dialog_body, temp);

		if (GarageInfo[id][garageHouse])
		{
			format(temp, sizeof(temp), "Bir eve ba�l�\t%i\n", GarageInfo[id][garageHouse]);
			strcat(dialog_body, temp);
		}

		if (GarageInfo[id][garageBiz])
		{
			format(temp, sizeof(temp), "Bir i�yerine ba�l�\t%i\n", GarageInfo[id][garageBiz]);
			strcat(dialog_body, temp);
		}

		if (GarageInfo[id][garageOwner])
		{
			format(temp, sizeof(temp), "Sahip\t%s", GarageInfo[id][garageOwnerName]);
			strcat(dialog_body, temp);
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Garaj Bilgisi", dialog_body, "Kapat", "");
		return 1;
	}

	else if (CompareStrings(option, "satinal"))
	{
		if (GarageInfo[id][garageOwner])	return SendErrorMessage(playerid, "Bu garaj sat�l�k de�il.");
		if (GarageInfo[id][garageHouse])	return SendErrorMessage(playerid, "Bu garaj bir eve ba�l�.");
		if (GarageInfo[id][garageBiz])		return SendErrorMessage(playerid, "Bu garaj bir mekana ba�l�.");

		new count = 0;

		for(new i = 0; i < MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageHouse] || GarageInfo[i][garageBiz] || PlayerInfo[playerid][pID] != GarageInfo[i][garageOwner]) continue;

			count++;
			break;
		}

		if (count)												return SendErrorMessage(playerid, "Daha fazla garaj sat�n alamazs�n.");
		if (GetCash(playerid) < GarageInfo[id][garagePrice])	return SendNotCash(playerid);

		new money = PlayerInfo[playerid][pCash];

		GiveCash(playerid, -GarageInfo[id][garagePrice]);
		SendSyntaxMessage(playerid, "Bir garaj sat�n ald�n: [ID: %i] - $%i.", id, GarageInfo[id][garagePrice]);
		GarageInfo[id][garageOwner] = PlayerInfo[playerid][pID];
		format(GarageInfo[id][garageOwnerName], 24, "%s", GetNameEx(playerid));
		
		SQL_SetInteger("garage", "owner", GarageInfo[id][garageOwner], GarageInfo[id][garageID]);
		SQL_SetString("users", "name", GarageInfo[id][garageOwnerName], GarageInfo[id][garageOwner]);

		new mes[256];
		format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money (ONCEKI): %s | Money (SIMDIKI): %s] garaj sat�n al�nd� [G_MYSQL: %i] $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid),
		GarageInfo[id][garageID], GarageInfo[id][garagePrice]);
		insert_log(mes, PROPERTY_LOG, 5, PlayerInfo[playerid][pAccID]);
		return 1;
	}

	else if (CompareStrings(option, "sistemesat"))
	{
		if (GarageInfo[id][garageOwner] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu garaj size ait de�il.");
		if (GarageInfo[id][garageHouse])								return SendErrorMessage(playerid, "Bu garaj bir eve ba�l�.");
		if (GarageInfo[id][garageBiz])									return SendErrorMessage(playerid, "Bu garaj bir mekana ba�l�.");

		

		new money = PlayerInfo[playerid][pCash];
		
		GiveCash(playerid, GarageInfo[id][garagePrice]);
		SendSyntaxMessage(playerid, "Garaj� satt�n: [ID: %i] - $%i.", id, GarageInfo[id][garagePrice]);
		GarageInfo[id][garageOwner] = 0;
		GarageInfo[id][garageOwnerName][0] = EOS;
		SQL_SetInteger("garage", "owner", 0, GarageInfo[id][garageID]);
		//SQL_SetString("garage", "ownername", "", GarageInfo[id][garageID]);

		new mes[256];
		format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money (ONCEKI): %i | Money (SIMDIKI): %i] garaj sat�ld� [G_MYSQL: %i] $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid),
		GarageInfo[id][garageID], GarageInfo[id][garagePrice]);
		insert_log(mes, PROPERTY_LOG, 6, PlayerInfo[playerid][pAccID]);
	}

	else if (CompareStrings(option, "kapitamir"))
	{
		if (!GarageInfo[id][garageDDoor])	 return SendErrorMessage(playerid,"Kap� hasarl� de�il.");
		if (GetCash(playerid) < 300)		 return SendErrorMessage(playerid, "Kap� tamir �creti 300 dolard�r.");

		GarageInfo[id][garageDDoor] = 0;
		SQL_SetInteger("garage", "ddoor", GarageInfo[id][garageDDoor], GarageInfo[id][garageID]);
		UpdateGarageDoor(id);
		GiveCash(playerid, -300); //���������� ��� givecashex
		SendSyntaxMessage(playerid, "$300 kar��l���nda kap�y� tamir ettirdin.");
		return 1;
	}
	return 1;
}