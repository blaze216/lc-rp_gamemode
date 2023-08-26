Dialog:BuyStandFood(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new price_food[4] = {PRICE_BURGER, PRICE_PIZZA, PRICE_CHICKEN, PRICE_HOTDOG}, name_food[4][8] = {"burger", "pizza", "tavuk", "hot-dog"};

	if (GetCash(playerid) < price_food[listitem])				return SendNotCash(playerid);
	
	switch(listitem)
	{
        case 0:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");
            InfoMSG(playerid, "Yemegi yemek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            
            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health + 10 > 100.0) PlayerInfo[playerid][pHealth] = 100.0;
            else                    PlayerInfo[playerid][pHealth] = health + 10.0;
            
            SetPVarInt(playerid, #use_food, 5);
            SetPVarInt(playerid, #time_food, gettime());
            SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2703, 6, 0.055999, 0.028000, 0.008000, 2.599998, 0.000000, 16.599998, 0.844000, 0.871000, 0.870000);
            pc_cmd_server_ame(playerid, "burger yer.");
        }
        case 1:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");
            InfoMSG(playerid, "Yemegi yemek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            
            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health + 15.0 > 100.0) PlayerInfo[playerid][pHealth] = 100.0;
            else                       PlayerInfo[playerid][pHealth] = health + 15.0;

            SetPVarInt(playerid, #use_food, 5);
            SetPVarInt(playerid, #time_food, gettime());
            SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2703, 6, 0.055999, 0.028000, 0.008000, 2.599998, 0.000000, 16.599998, 0.844000, 0.871000, 0.870000);
            pc_cmd_server_ame(playerid, "pizza yer.");
        }
        case 2:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Yemegi yemek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            
            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health + 7.0 > 100.0) PlayerInfo[playerid][pHealth] = 100.0;
            else                      PlayerInfo[playerid][pHealth] = health + 7.0;
            

            SetPVarInt(playerid, #use_food, 5);
            SetPVarInt(playerid, #time_food, gettime());
            SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2703, 6, 0.055999, 0.028000, 0.008000, 2.599998, 0.000000, 16.599998, 0.844000, 0.871000, 0.870000);
            pc_cmd_server_ame(playerid, "tavuk yer");
        }
        case 3:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Yemegi yemek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            
            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health + 5.0 > 100.0)    PlayerInfo[playerid][pHealth] = 100.0;
            else                       PlayerInfo[playerid][pHealth] = health + 5.0;
            

            SetPVarInt(playerid, #use_food, 5);
		    SetPVarInt(playerid, #time_food, gettime());
		    SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2703, 6, 0.055999, 0.028000, 0.008000, 2.599998, 0.000000, 16.599998, 0.844000, 0.871000, 0.870000);
            pc_cmd_server_ame(playerid, "hot-dog yer.");
        }		
	}

	SendSyntaxMessage(playerid, "%s satýn aldýnýz, ödenen: $%i.", name_food[listitem], price_food[listitem]);
	GiveCash(playerid, -price_food[listitem]);
	return 1;
}