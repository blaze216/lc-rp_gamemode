this::OnPlayerUseItem(playerid, slotid) //�������������
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) 
        return SendErrorMessage(playerid, "Envanteri �u anda kullanamazs�n�z.");
    if (slotid < 0 || slotid > MAX_INV_SLOTS-1) return 1; 
    
    new itemid = Inventory[playerid][slotid][pInvItem];
	
    switch(itemid)
    {
        case INV_SIGN: pc_cmd_aracilan(playerid, "");
        case INV_HEAL:
        {
            SM1(playerid, "Bu e�ya �u anda kullan�lamaz.");
           /* if (GetPVarInt(playerid, #heal_time) > gettime())   return SendErrorMessage(playerid, "Her dakikada bir kez kullanabilir.");

            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health >= 100.0) return SendErrorMessage(playerid, "Sa�l���n�z tam.");
            
            if (health + 15.0 > 100.0)   SetPlayerHealth(playerid, 100.0);
            else                        SetPlayerHealth(playerid, health + 100.0);
            
            
            SetPVarInt(playerid, #heal_time, gettime() + 60);
            Inventory[playerid][slotid][pInvQ]--;
            if (!Inventory[playerid][slotid][pInvQ]) Inventory[playerid][slotid][pInvItem] = 0;*/
        }


        case INV_BOOMBOX:   PlaceBoombox(playerid);
        case INV_RADIO:     pc_cmd_telsizyardim(playerid, "");
        case INV_MASK:      pc_cmd_maske(playerid, "");
        case INV_LIGHTER:   SendHelpMessage(playerid, "Yakmak i�in envanterden bir sigara se�in.");
        case INV_CIGAR:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))  return SendWarningMessage(playerid, "Elinizde bir e�ya bulunuyor.");
            
            Inventory[playerid][slotid][pInvQ]--;
            
            if (Inventory[playerid][slotid][pInvQ] == 0) Inventory[playerid][slotid][pInvItem] = 0;
            
            pc_cmd_server_ame(playerid, "bir adet sigara ��kar�r ve �akma��yla yakar.");
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
            SM2(playerid, "Bir sigara yakt�n.");

            InfoMSG(playerid, "Sigara icmek icin \" ~g~LKM ~w~\" tusuna basin, sigarayi atmak icin \" ~r~ENTER ~w~\" tusuna basin", 5);

        }
        case INV_CUBANPURO:
        {
            if (!PlayerInfo[playerid][pCakmak])                return SendErrorMessage(playerid, "�zerinde �akmak yok.");
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))  return SendWarningMessage(playerid, "Elinizde bir e�ya bulunuyor.");
            
            Inventory[playerid][slotid][pInvQ]--;
            
            if (Inventory[playerid][slotid][pInvQ] == 0) Inventory[playerid][slotid][pInvItem] = 0;
            
            pc_cmd_server_ame(playerid, "k�ba purosunu �akma��yla yakar.");
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
            SM2(playerid, "K�ba purosu yakt�n. +5 HP");
            PlayerInfo[playerid][pHealth] += 5;

            InfoMSG(playerid, "Sigara icmek icin \" ~g~LKM ~w~\" tusuna basin, sigarayi atmak icin \" ~r~ENTER ~w~\" tusuna basin", 5);

        }        
        case INV_DICE:      SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d ))", GetNameWithMask(playerid), random(6)+1);
        case INV_PEN:       pc_cmd_not(playerid, "");
        case INV_GASCAN:
        {
            if (IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Ara�tayken bu i�levi ger�ekle�tiremezsiniz.");
            
            new vehicle;

            if ((vehicle = GetNearVehicle(playerid, 2.5)) == 0) return SendErrorMessage(playerid, "Yak�n�n�zda ara� yok.");
            if (VehicleInfo[vehicle][carFuel] + 20.0 > GetVehicleFuelCapacity(GetVehicleModel(vehicle))) return SendErrorMessage(playerid, "Arac�n yak�t deposu dolu.");

            VehicleInfo[vehicle][carFuel] += 20.0;
            SM2(playerid, "Arac�n�za bidon ile yak�t ikmali yap�l�yor.");
            pc_cmd_me(playerid, "arac�na yak�t doldurur.");
            Inventory[playerid][slotid][pInvQ]--;
            if (Inventory[playerid][slotid][pInvQ] == 0) Inventory[playerid][slotid][pInvItem] = 0;
        }
        case INV_BURGER:
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
            RemovePlayerItem(playerid, INV_BURGER, 1);
            pc_cmd_server_ame(playerid, "burger yer.");
        }
        case INV_PIZZA:
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
            RemovePlayerItem(playerid, INV_PIZZA, 1);
            pc_cmd_server_ame(playerid, "pizza yer.");
        }
        case INV_CHICKEN:
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
            RemovePlayerItem(playerid, INV_CHICKEN, 1);
            pc_cmd_server_ame(playerid, "tavuk yer");
        }
        case INV_HOTDOG:
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
            RemovePlayerItem(playerid, INV_HOTDOG, 1);
            pc_cmd_server_ame(playerid, "hot-dog yer.");
        }
        case INV_WATER, INV_SODA, INV_COLA:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
            RemovePlayerItem(playerid, itemid, 1);

            if (itemid == INV_WATER)     pc_cmd_server_ame(playerid, "su i�er.");
            else if (itemid == INV_SODA) pc_cmd_server_ame(playerid, "soda i�er.");
            else if (itemid == INV_COLA) pc_cmd_server_ame(playerid, "kola i�er.");
        }
        case INV_BEER:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
            RemovePlayerItem(playerid, itemid, 1);
            pc_cmd_server_ame(playerid, "bira i�er.");
        }
        case INV_VODKA, INV_WHISKEY, INV_BRANDY, INV_WINE:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
            RemovePlayerItem(playerid, itemid, 1);

            if (itemid == INV_VODKA)         pc_cmd_server_ame(playerid, "vodka i�er.");
            else if (itemid == INV_WHISKEY)  pc_cmd_server_ame(playerid, "viski i�er.");
            else if (itemid == INV_BRANDY)   pc_cmd_server_ame(playerid, "brendi i�er.");
            else                             pc_cmd_server_ame(playerid, "�arap i�er.");
        }
        case INV_PICKLOCK: pc_cmd_evkilitkir(playerid, "");
        case INV_CARSOUND:
        {
            new vehicle = GetPlayerVehicleID(playerid);

            if (vehicle == 0) return SendSyntaxMessage(playerid, "Arac�n�za radyo teyp takabilirsiniz veya rehin d�kkan�nda(pawnshop) satabilirsiniz. (( /sell ))");
            if (VehicleInfo[vehicle][carOwnerID] == INVALID_PLAYER_ID)    return SendErrorMessage(playerid, "Radyo kay�t cihaz� yaln�zca ki�isel araca tak�labilir.");
            if (VehicleInfo[vehicle][carRadio] == 1)      return SendErrorMessage(playerid, "Bu ara�ta hali haz�rda bir radyo teyp zaten var.");
            if (!IsPlayerHasItem(playerid, INV_CARSOUND)) return SendErrorMessage(playerid, "Bir radyo cihaz�n�z yok.");

            new mes[128];
            format(mes, sizeof(mes), "%s arac�na radyo takar.", VehicleNames[GetVehicleModel(vehicle)-400]);
            pc_cmd_me(playerid, mes);
            RemovePlayerItem(playerid, itemid, 1);
            VehicleInfo[vehicle][carRadio] = 1;
        }
        //case INV_SKATE: pc_cmd_kaykay(playerid, "");

	}
	return 1;
}

IsPlayerHasItem(playerid, itemid, amount = 0)
{
	if (!IsPlayerLogged(playerid) || !itemid) return 0;
    
    new result = -1;
	for(new i = 0; i != MAX_INV_SLOTS; i++)
	{
	    if (amount > 0 && Inventory[playerid][i][pInvItem] == itemid && Inventory[playerid][i][pInvQ] >= amount) 
        { 
            result = i;
            break; 
        }  
	    else if (amount < 1 && Inventory[playerid][i][pInvItem] == itemid) 
        {
            result = i;
            break; 
        }
	}

    if (result == -1) return 0;
    else return 1;
}

RemovePlayerItem(playerid, itemid, amount = -1)
{
    for(new i; i != MAX_INV_SLOTS; i++)
	{
	    if (Inventory[playerid][i][pInvItem] != itemid) continue;

	    if (amount == -1)
	    {
	        Inventory[playerid][i][pInvItem] = 0;
	        Inventory[playerid][i][pInvQ] = 0;
			return 1;
		}

        Inventory[playerid][i][pInvQ] -= amount;

		if (Inventory[playerid][i][pInvQ] < 1)
		{
		    Inventory[playerid][i][pInvItem] = 0;
	        Inventory[playerid][i][pInvQ] = 0;      
  		}
        return 1;
	}
	return 0;
}

GetWeaponType(weaponid)
{
    switch(weaponid)
    {
        case 2,3,5,6,7,8,15:    return 1; //WEAPON_TYPE_HAND
        case 22,23,24,28,29,32: return 2; //WEAPON_TYPE_SEC
        case 25,26,30,31,33,34: return 3; //WEAPON_TYPE_PRIM
    }
    return -1;
}
    
