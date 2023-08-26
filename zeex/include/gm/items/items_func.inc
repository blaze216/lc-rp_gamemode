this::OnPlayerUseItem(playerid, slotid) //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) 
        return SendErrorMessage(playerid, "Envanteri þu anda kullanamazsýnýz.");
    if (slotid < 0 || slotid > MAX_INV_SLOTS-1) return 1; 
    
    new itemid = Inventory[playerid][slotid][pInvItem];
	
    switch(itemid)
    {
        case INV_SIGN: pc_cmd_aracilan(playerid, "");
        case INV_HEAL:
        {
            SM1(playerid, "Bu eþya þu anda kullanýlamaz.");
           /* if (GetPVarInt(playerid, #heal_time) > gettime())   return SendErrorMessage(playerid, "Her dakikada bir kez kullanabilir.");

            new Float:health;
            AntiCheatGetHealth(playerid, health);

            if (health >= 100.0) return SendErrorMessage(playerid, "Saðlýðýnýz tam.");
            
            if (health + 15.0 > 100.0)   SetPlayerHealth(playerid, 100.0);
            else                        SetPlayerHealth(playerid, health + 100.0);
            
            
            SetPVarInt(playerid, #heal_time, gettime() + 60);
            Inventory[playerid][slotid][pInvQ]--;
            if (!Inventory[playerid][slotid][pInvQ]) Inventory[playerid][slotid][pInvItem] = 0;*/
        }


        case INV_BOOMBOX:   PlaceBoombox(playerid);
        case INV_RADIO:     pc_cmd_telsizyardim(playerid, "");
        case INV_MASK:      pc_cmd_maske(playerid, "");
        case INV_LIGHTER:   SendHelpMessage(playerid, "Yakmak için envanterden bir sigara seçin.");
        case INV_CIGAR:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))  return SendWarningMessage(playerid, "Elinizde bir eþya bulunuyor.");
            
            Inventory[playerid][slotid][pInvQ]--;
            
            if (Inventory[playerid][slotid][pInvQ] == 0) Inventory[playerid][slotid][pInvItem] = 0;
            
            pc_cmd_server_ame(playerid, "bir adet sigara çýkarýr ve çakmaðýyla yakar.");
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
            SM2(playerid, "Bir sigara yaktýn.");

            InfoMSG(playerid, "Sigara icmek icin \" ~g~LKM ~w~\" tusuna basin, sigarayi atmak icin \" ~r~ENTER ~w~\" tusuna basin", 5);

        }
        case INV_CUBANPURO:
        {
            if (!PlayerInfo[playerid][pCakmak])                return SendErrorMessage(playerid, "Üzerinde çakmak yok.");
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))  return SendWarningMessage(playerid, "Elinizde bir eþya bulunuyor.");
            
            Inventory[playerid][slotid][pInvQ]--;
            
            if (Inventory[playerid][slotid][pInvQ] == 0) Inventory[playerid][slotid][pInvItem] = 0;
            
            pc_cmd_server_ame(playerid, "küba purosunu çakmaðýyla yakar.");
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
            SM2(playerid, "Küba purosu yaktýn. +5 HP");
            PlayerInfo[playerid][pHealth] += 5;

            InfoMSG(playerid, "Sigara icmek icin \" ~g~LKM ~w~\" tusuna basin, sigarayi atmak icin \" ~r~ENTER ~w~\" tusuna basin", 5);

        }        
        case INV_DICE:      SendNearbyMessage(Range_Normal, playerid, COLOUR_VISTABLUE, "> %s zar atar (( %d ))", GetNameWithMask(playerid), random(6)+1);
        case INV_PEN:       pc_cmd_not(playerid, "");
        case INV_GASCAN:
        {
            if (IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araçtayken bu iþlevi gerçekleþtiremezsiniz.");
            
            new vehicle;

            if ((vehicle = GetNearVehicle(playerid, 2.5)) == 0) return SendErrorMessage(playerid, "Yakýnýnýzda araç yok.");
            if (VehicleInfo[vehicle][carFuel] + 20.0 > GetVehicleFuelCapacity(GetVehicleModel(vehicle))) return SendErrorMessage(playerid, "Aracýn yakýt deposu dolu.");

            VehicleInfo[vehicle][carFuel] += 20.0;
            SM2(playerid, "Aracýnýza bidon ile yakýt ikmali yapýlýyor.");
            pc_cmd_me(playerid, "aracýna yakýt doldurur.");
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

            if (itemid == INV_WATER)     pc_cmd_server_ame(playerid, "su içer.");
            else if (itemid == INV_SODA) pc_cmd_server_ame(playerid, "soda içer.");
            else if (itemid == INV_COLA) pc_cmd_server_ame(playerid, "kola içer.");
        }
        case INV_BEER:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
            RemovePlayerItem(playerid, itemid, 1);
            pc_cmd_server_ame(playerid, "bira içer.");
        }
        case INV_VODKA, INV_WHISKEY, INV_BRANDY, INV_WINE:
        {
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

            InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
            RemovePlayerItem(playerid, itemid, 1);

            if (itemid == INV_VODKA)         pc_cmd_server_ame(playerid, "vodka içer.");
            else if (itemid == INV_WHISKEY)  pc_cmd_server_ame(playerid, "viski içer.");
            else if (itemid == INV_BRANDY)   pc_cmd_server_ame(playerid, "brendi içer.");
            else                             pc_cmd_server_ame(playerid, "þarap içer.");
        }
        case INV_PICKLOCK: pc_cmd_evkilitkir(playerid, "");
        case INV_CARSOUND:
        {
            new vehicle = GetPlayerVehicleID(playerid);

            if (vehicle == 0) return SendSyntaxMessage(playerid, "Aracýnýza radyo teyp takabilirsiniz veya rehin dükkanýnda(pawnshop) satabilirsiniz. (( /sell ))");
            if (VehicleInfo[vehicle][carOwnerID] == INVALID_PLAYER_ID)    return SendErrorMessage(playerid, "Radyo kayýt cihazý yalnýzca kiþisel araca takýlabilir.");
            if (VehicleInfo[vehicle][carRadio] == 1)      return SendErrorMessage(playerid, "Bu araçta hali hazýrda bir radyo teyp zaten var.");
            if (!IsPlayerHasItem(playerid, INV_CARSOUND)) return SendErrorMessage(playerid, "Bir radyo cihazýnýz yok.");

            new mes[128];
            format(mes, sizeof(mes), "%s aracýna radyo takar.", VehicleNames[GetVehicleModel(vehicle)-400]);
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
    
