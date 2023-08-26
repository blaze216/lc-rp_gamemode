new bronze_str[] = {"{9ACD32} Premium: {FFFFFF} BRONZE\n\n {9ACD32} Advantages:\n {FFFFFF} Bronze title on the forum;\nColor and group on the forum;\nThe capacity of the LAN on the forum is 150;\nName change in game 2 times;\n /blockpm (block PM messages from a specific player);\nMaximum amount of health at the entrance;\nDisable AntiAfk system;\nLimit of contacts in the phone book - 25;\nMaximum number of houses for purchase - 2;\nPossibility to change license plate on your vehicle - 3 times "},
	bronze_str_2[] = {"Available vehicles for purchase: Bf Injection, Bandito;\n /setstyle (Change of HUD style (a), available at choice 4);\n /setstyle (Change of style of fight, available at choice 4);\nAvailable limit of accessories in the house - 150 objects;\n\n {9ACD32} Cost: {FFFFFF} 150 rubles."};


new silver_str[] = {"{9ACD32} Premium: {FFFFFF} SILVER\n\n {9ACD32} Advantages:\n {FFFFFF} Silver title on the forum;\nColor and group on the forum;\nThe capacity of the LAN on the forum is 200;\nName change in the game 3 times ;\n /blockpm (block PM messages from a specific player);\nMaximum amount of health upon entry;\nDisable AntiAfk system;\nLimit of contacts in the phone book - 35"},
    silver_str_2[] = {"Quit your job instantly, and not after 2 hours;\nSaving the mask after exiting the game;\nMaximum number of houses for purchase - 4;\nMaximum number of businesses for purchase - 2;\nMaximum number of vehicles for purchase - 5;\nPossibility to set on nitro car (2x, 5x, 10x);\nAbility to change the license plate on your vehicle - 5 times;\nAvailable vehicles for purchase: Bf Injection, Bandito, Sandking, Bullet, Cheetah"},
    silver_str_3[] = {"Reduced ad time /ad /cad (60 seconds for regular accounts, 30 seconds for silver);\n /setstyle (Change HUD style (a), available at choice 4);\n /setstyle (Change battle style, available choice 4);\nAvailable limit of fittings in the house - 250 objects;\n\n {9ACD32} Cost: {FFFFFF} 250 rubles."};


new gold_str[] = {"{9ACD32} Premium: {FFFFFF} GOLD\n\n {9ACD32} Advantages:\n {FFFFFF} Gold title on the forum;\nColor and group on the forum;\nThe capacity of the LAN on the forum is 200;\nName change in the game 5 times ;\n /blockpm (block PM messages from a specific player);\nMaximum amount of health when entering;\nDisable AntiAfk system"},
    gold_str_2[] = {"The limit of contacts in the phone book is 40;\nQuitting from work instantly, not after 2 hours;\nSaving the mask after leaving the game;\nMaximum number of houses to buy - 5;\nMaximum number of businesses to buy - 3;\nMaximum number of vehicles for purchase - 7;\nAbility to install nitro (2x, 5x, 10x) on the car;\nAbility to change the license plate on your vehicle - 7 times"},
    gold_str_3[] = {"Available vehicles for purchase: Infernus, Bullet, Cheetah, NRG-500, FBI Rancher, Sandking, Bf Injection, Bandito;\nReduced ad /ad /cad time (For regular accounts, feed 60 seconds, for gold 30 seconds);\n /setstyle (Change HUD style (a), available at choice 4);\n /setstyle (Change style in combat, available at choice 4);\nAvailable hardware limit in the house - 400 objects;\n\n {9ACD32} Cost: {FFFFFF} 450 rubles."};
		
Donate_OnGameModeInit()
{
	new query[256];
	format(query, sizeof(query), "DELETE FROM `donate` WHERE `status`='0' AND `dateDelete` > %i", gettime());
	mysql_tquery(dbHandle, query);

	bronze_str[sizeof(bronze_str)-1] = '\n';
	bronze_str_2[sizeof(bronze_str_2)-1] = '\0';
	
    silver_str[sizeof(silver_str)-1] = '\n';
	silver_str_2[sizeof(silver_str_2)-1] = '\n';
	silver_str_3[sizeof(silver_str_3)-1] = '\0';

    gold_str[sizeof(gold_str)-1] = '\n';
	gold_str_2[sizeof(gold_str_2)-1] = '\n';
	gold_str_3[sizeof(gold_str_3)-1] = '\0';
}


CMD:donate(playerid, params[])
{
    Dialog_Show(playerid, DonateMenu, DIALOG_STYLE_LIST, "Privileges", "1. Purchase\n\
	2. Information\n\
	{6EA3FF}"WeburlName"", "Seç", "Ýptal");
	return 1;
}

Dialog:DonateMenu(playerid, response, listitem, inputtext[])
{
	if (!response)
	    return 1;

	switch(listitem)
	{
	    case 0:
	    {
			new title[32];
			format(title, sizeof(title), "Your account: {9ACD32}%i rub.", PlayerInfo[playerid][pDonate]);
	    
	        Dialog_Show(playerid, DonateBuy, DIALOG_STYLE_TABLIST, title, "Premium \"BRONZE\"\t{9ACD32}[250 rubles]\n\
	        Premium \"SILVER\"\t{9ACD32}[350 rubles]\n\
	        Premium \"GOLD\"\t{9ACD32}[450 rubles]\n\
	        Nickname change\t{9ACD32}[80 rubles]\n\
	        Phone number change\t{9ACD32}[100 rubles]\n\
	        Change of vehicle number\t{9ACD32}[70 rubles]", "Seç", "Geri Dön");
	    }
	    case 1:
	    {
	        new mes[256];
	        format(mes, sizeof(mes), "{ffffff}On your account {9ACD32}%i {FFFFFF}donate rubles.\nAbility to change nickname: %i time. (/changenick)\nThe ability to change the vehicle number: %i time. (/changeplate)", PlayerInfo[playerid][pDonate], PlayerInfo[playerid][pNameChanges], PlayerInfo[playerid][pNumberChanges]);
	        
	        new premium_info[4][8] =
				{"Usual", "BRONZE", "SILVER", "GOLD"};

			if (PlayerInfo[playerid][pPremium])
			{
				new Float:days = float(PlayerInfo[playerid][pPremiumTime] - gettime()) /86400.0;
			    format(mes, sizeof(mes), "%s\nBeneficiezi de cont {9ACD32}%s{FFFFFF}. {9ACD32}%i{FFFFFF}zile ramase.",mes, premium_info[PlayerInfo[playerid][pPremium]], floatround(days));
			}
			Dialog_Show(playerid, DonateCancel, DIALOG_STYLE_MSGBOX, "Information", mes, "Geri Dön", "");
	    }
		case 2: return pc_cmd_donate(playerid, "");
		
	}
	return 1;
}

Dialog:DonateBuy(playerid, response, listitem, inputtext[])
{
	if (!response)
		return pc_cmd_donate(playerid, "");

	switch(listitem)
	{
		case 0: Dialog_Show(playerid, BuyPremium, DIALOG_STYLE_MSGBOX, "Premium", bronze_str, "Buy", "Geri Dön");
		case 1: Dialog_Show(playerid, BuyPremium, DIALOG_STYLE_MSGBOX, "Premium", silver_str, "Buy", "Geri Dön");
		case 2: Dialog_Show(playerid, BuyPremium, DIALOG_STYLE_MSGBOX, "Premium", gold_str, "Buy", "Geri Dön");
		case 3: Dialog_Show(playerid, BuyName, DIALOG_STYLE_MSGBOX, "Nickname change", "{FFFFFF}Do you want to purchase the ability to change your nickname? Price: 80 rubles.", "Buy", "Geri Dön");
        case 4: Dialog_Show(playerid, BuyNumber, DIALOG_STYLE_INPUT, "Phone number change", "{FFFFFF}Enter your new number, minimum Characters is 4. Cost: 100 rubles.", "Buy", "Geri Dön");
        case 5: Dialog_Show(playerid, BuyNumberplate, DIALOG_STYLE_MSGBOX, "Vehicle number change", "{FFFFFF} Do you want to purchase the ability to change the vehicle number? Cost: 70 rubles.", "Buy", "Geri Dön");
	}
	SetPVarInt(playerid, #premium_buy, listitem+1);
	return 1;
}

Dialog:BuyName(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_donate(playerid, "");

	#define PRICE_CHANGE_NAME (80)
	
	if (PlayerInfo[playerid][pDonate] < PRICE_CHANGE_NAME) return SendErrorMessage(playerid, "There are not enough donate rubles on your account.");

	SendSyntaxMessage(playerid, "You have acquired the opportunity to change your nickname for %i rubles.", PRICE_CHANGE_NAME);

	PlayerInfo[playerid][pDonate] -= PRICE_CHANGE_NAME;
	PlayerInfo[playerid][pNameChanges]++;

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `donate`=%i,`name_changes`=%i WHERE `forum_id` = %i", PlayerInfo[playerid][pDonate], PlayerInfo[playerid][pNameChanges], PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);

	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] bought a nickname change",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid));
 	insert_log(query, DONATE_LOG, 1, PlayerInfo[playerid][pAccID]);
	return 1;
}

Dialog:BuyNumberplate(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_donate(playerid, "");

	#define PRICE_CHANGE_NUMBERPLATE (70)

	if (PlayerInfo[playerid][pDonate] < PRICE_CHANGE_NUMBERPLATE) return SendErrorMessage(playerid, "There is not enough donation on your account rubles.");

	SendSyntaxMessage(playerid, "You have acquired the opportunity to change the license plate of the vehicle from %i rubles.", PRICE_CHANGE_NUMBERPLATE);

	PlayerInfo[playerid][pDonate] -= PRICE_CHANGE_NUMBERPLATE;
	PlayerInfo[playerid][pNumberChanges]++;

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `donate`=%i,`number_changes`=%i WHERE `forum_id` = %i", PlayerInfo[playerid][pDonate], PlayerInfo[playerid][pNumberChanges], PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);

	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] bought a change of license plate",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid));
 	insert_log(query, DONATE_LOG, 3, PlayerInfo[playerid][pAccID]);
	return 1;
}

Dialog:BuyNumber(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_donate(playerid, "");

	if (strlen(inputtext) < 4 || strval(inputtext) < 1000)
	{
	    return Dialog_Show(playerid, BuyNumber, DIALOG_STYLE_MSGBOX, "{FFFFFF}Phone number change", "{FFFFFF}Enter your new number, minimum characters - 4. Cost: 100 rubles.", "Buy", "Geri Dön");
	}

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `number` FROM `users` WHERE `number` = %i", strval(inputtext));
	mysql_tquery(dbHandle, query, "OnPlayerBuyDonateNumber", "ii", playerid, strval(inputtext));
	return 1;
}

forward OnPlayerBuyDonateNumber(playerid, number);
public OnPlayerBuyDonateNumber(playerid, number)
{
	if (cache_num_rows())
	{
	    Dialog_Show(playerid, BuyNumber, DIALOG_STYLE_MSGBOX, "Change phone number", "Enter your new number, minimum characters - 4. Cost: 100 rubles.", "Buy", "Geri Dön");
	    return SendErrorMessage(playerid, "This number is already in use by someone.");
	}
	
	#define PRICE_CHANGE_NUMBER (100)

	if (PlayerInfo[playerid][pDonate] < PRICE_CHANGE_NUMBER) return SendErrorMessage(playerid, "There are not enough donate rubles on your account.");
	if (!CheckNumberAvailable(number))						 return SendErrorMessage(playerid, "This phone number is already in use! ");

	SendSyntaxMessage(playerid, "You purchased a room [%i] for %i rubles.", number, PRICE_CHANGE_NUMBER);
	PlayerInfo[playerid][pDonate] -= PRICE_CHANGE_NUMBERPLATE;
	PlayerInfo[playerid][pNumber] = number;

	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `donate`=%i WHERE `forum_id` = %i", PlayerInfo[playerid][pDonate], PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);
    mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `number`=%i WHERE `id` = %i", number, PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query);

	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] bought a phone number- %i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), number);
 	insert_log(query, DONATE_LOG, 4, PlayerInfo[playerid][pAccID]);
	return 1;
}

Dialog:BuyPremium(playerid, response, listitem, inputtext[])
{
	if (!response) 						return pc_cmd_donate(playerid, "");
	if (PlayerInfo[playerid][pPremium])	return SendErrorMessage(playerid, "To buy a premium, you have to wait until it ends.");
	        
	listitem = GetPVarInt(playerid, #premium_buy)-1;
	
	if (listitem < 0 || listitem > 2) return 1;
	    
	new price_premium[3] = {150, 250, 350}, premium_name_changes[3] = {2, 3, 5}, premium_number_changes[3] = {3, 5, 7};
	new premium_info[3][8] = {"BRONZE", "SILVER", "GOLD"};
			
	if (PlayerInfo[playerid][pDonate] < price_premium[listitem]) return SendErrorMessage(playerid, "There are not enough donate rubles on your account.");

	SendSyntaxMessage(playerid, "You have purchased a premium %s for 30 days in advance %i rubles.", premium_info[listitem], price_premium[listitem]);

	PlayerInfo[playerid][pDonate] -= price_premium[listitem];
	PlayerInfo[playerid][pNameChanges] += premium_name_changes[listitem];
	PlayerInfo[playerid][pNumberChanges] += premium_number_changes[listitem];
	PlayerInfo[playerid][pPremium] = listitem + 1;
    PlayerInfo[playerid][pPremiumTime] = gettime() + 30 * 86400;
	
	new query[256];
	
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `donate`=%i,`name_changes`=%i,`number_changes`=%i WHERE `forum_id` = %i", PlayerInfo[playerid][pDonate], PlayerInfo[playerid][pNameChanges], PlayerInfo[playerid][pNumberChanges], PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `vip`=%i,`vip_time`=%i,`spawnhealth`=100.0 WHERE `id` = %i", PlayerInfo[playerid][pPremium], PlayerInfo[playerid][pPremiumTime], PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query);
    
	format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] bought a premium %s", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), premium_info[listitem]);
 	insert_log(query, DONATE_LOG, 2, PlayerInfo[playerid][pAccID]);
	return 1;
}

Dialog:DonateCancel(playerid, response, listitem, inputtext[])
{
	pc_cmd_donate(playerid, "");
	return 1;
}

CMD:changeplate(playerid, params[])
{
	if (PlayerInfo[playerid][pNumberChanges] < 1)		return SendErrorMessage(playerid, "To change the license plate, you must purchase this privilege. (/donate)");

	new vehicleid = GetPlayerVehicleID(playerid);

	if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))						return SendErrorMessage(playerid, "Your vehicle is not spawned.");
	if (vehicleid == 0)														return SendNotInVehicle(playerid);
	if (VehicleInfo[vehicleid][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "You are not the owner of this vehicle.");

	Dialog_Show(playerid, ChangeNumberplate, DIALOG_STYLE_INPUT, "{FFFFFF}Entering a new character ", "{FFFFFF}Enter a new license plate for your vehicle:", "Change", "Ýptal");
	return 1;
}


Dialog:ChangeNumberplate(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
	if (strlen(inputtext) < 3 || strlen(inputtext) > 11)	return SendErrorMessage(playerid,"the number of characters in the license plate is from 3 to 11.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `plate` FROM `cars` WHERE `plate` = '%e'", inputtext);
	mysql_tquery(dbHandle, query, "DonateSetPlate", "is", playerid, inputtext);
    return 1;
}

this::DonateSetPlate(playerid, plate[])
{
	if (cache_num_rows())							return SendErrorMessage(playerid, "The license plate is already in use by another vehicle.");
    if (PlayerInfo[playerid][pNumberChanges] < 1)	return SendErrorMessage(playerid, "To change the license plate, you must purchase this privilege. (/donate)");

	new vehicleid = GetPlayerVehicleID(playerid);

	if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Your vehicle is not spawned.");
	if (vehicleid == 0)													return SendNotInVehicle(playerid);
	if (VehicleInfo[vehicleid][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "You are not the owner of this vehicle.");

	PlayerInfo[playerid][pNumberChanges]--;
    DeleteVehicleTickets(vehicleid);
    format(VehicleInfo[vehicleid][carPlate], 24, "%s", plate);
	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][carPlate]);
	RespawnVehicle(vehicleid, 1);
	Save_Car(vehicleid);
	SendSyntaxMessage(playerid, "You changed your license plate %s. New plates: %s", VehicleNames[GetVehicleModel(vehicleid)-400], plate);
	SendSyntaxMessage(playerid, "Vehicleation fines have been paid.");

    new query[256];

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `number_changes`=%i WHERE `forum_id` = %i", PlayerInfo[playerid][pNumberChanges], PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);
	return 1;
}
/*
CMD:changenick(playerid, params[])
{
	if (PlayerInfo[playerid][pNameChanges] < 1) return SendErrorMessage(playerid, "To apply for a name change, you must purchase this privilege. (/donate)");

	if (strlen(pTemp[playerid][pChangeNick]))
	{
	    pTemp[playerid][pChangeNick] = EOS;
	    return SendErrorMessage(playerid, "You have canceled your nickname change application. ");
	}

	Dialog_Show(playerid, ChangeNick, DIALOG_STYLE_INPUT, "{FFFFFF}Entering a new name", "{FFFFFF}Enter a new nickname (Name_Surname):", ">>>", "Ýptal");
	return 1;
}*/

Dialog:ChangeNick(playerid, response, listitem, inputtext[])
{
	if (!response) 										return 1;
    if (!IsValidPlayerName(inputtext))					return SendErrorMessage(playerid, "Invalid nickname format. ");
	if (strlen(inputtext) < 4 || strlen(inputtext) > 24)	return SendErrorMessage(playerid, "Characters from 4 to 24.");

	format(pTemp[playerid][pChangeNick], MAX_PLAYER_NAME, inputtext);
	SendSyntaxMessage(playerid, "You have applied for a nickname change - %s", inputtext);
	SendAdmMessage("%s (ID: %i) applied for a nickname change - %s. (/acceptname - to confirm)", GetNameEx(playerid), playerid, inputtext);
	return 1;
}
