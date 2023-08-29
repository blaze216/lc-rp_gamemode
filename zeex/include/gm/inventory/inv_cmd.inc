alias:envanter("env");
CMD:envanter(playerid, params[])
{
	DeletePVar(playerid, #inventory_house);
    DeletePVar(playerid, #inventory_vehicle);
	
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Envanteri þu an kullanamazsýnýz.");
	
	if (GetPVarInt(playerid, #pDelay)) return 1;

    SendClientMessageEx(playerid, COLOR_SERVER2, "Envanter:{FFFFFF} Maske: [%s], Çakmak: [%s], Sigara: [%d dal], Kalem: [%s], Boombox: [%s], Burner Tel.: [%s]", (PlayerInfo[playerid][pMaske] ? "Var" : "Yok"), (PlayerInfo[playerid][pCakmak] ? "Var" : "Yok"),
	PlayerInfo[playerid][pSigara], (PlayerInfo[playerid][pKalem] ? "Var" : "Yok"), (PlayerInfo[playerid][pBoombox] ? "Var" : "Yok"), (PlayerInfo[playerid][pBurnerTelefon] ? "Var" : "Yok"));

    SendClientMessageEx(playerid, COLOR_SERVER2, "Envanter:{FFFFFF} Telsiz: [%s], Zar: [%s], Oyun Kartý: [%s], Bidon: [%s], Çalýntý Radyo: [%s]", (PlayerInfo[playerid][pTelsiz] ? "Var" : "Yok"), (PlayerInfo[playerid][pZar] ? "Var" : "Yok"),
	(PlayerInfo[playerid][pOyunKarti] ? "Var" : "Yok"), (PlayerInfo[playerid][pBenzinBidonu] ? "Var" : "Yok"), (PlayerInfo[playerid][pCalintiRadyo] ? "Var" : "Yok"));	

    SendClientMessageEx(playerid, COLOR_SERVER2, "Envanter:{FFFFFF} Kullaným yollarý için /envanteryardim yazýnýz.");		
/*
	new	
		count,
		diatxt[64] = "Karakter envanteri"
	;
	
	new houseid;
	if ((houseid = GetNearHouse(playerid)) != -1 && (HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID] || HouseInfo[houseid][hID] == PlayerInfo[playerid][pRentKey]) && PlayerToPoint(10.0, playerid,HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]))
	{
		format(diatxt, sizeof(diatxt), "%s\nEv envanteri", diatxt);
		count++;
	}

	new vehicle = GetNearVehicle(playerid, 4.0);
	if (vehicle != 0 && (!IsADontTrunk(vehicle) || !IsAPlane(vehicle) || !IsABiker(vehicle) || !IsAHelicopter(vehicle) || !IsABoat(vehicle) || !IsABicycle(vehicle)))
	{
		if ((VehicleInfo[vehicle][carTrunkLock] && !IsPlayerInAnyVehicle(playerid)) || (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]))
		{
			if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]) format(diatxt, sizeof(diatxt), "%s\nBagaj envanteri", diatxt);
			else 																										format(diatxt, sizeof(diatxt), "%s\nBagaj envanteri", diatxt);
			count++;
		}
	}
	
	vehicle = GetPlayerVehicleID(playerid);
	if (IsPlayerInAnyVehicle(playerid) && vehicle != 0 && GetPlayerHasRightDrive(playerid, vehicle))
	{
		format(diatxt, sizeof(diatxt), "%s\nTorpido envanteri", diatxt);
		count++;
	}

	if (count)	Dialog_Show(playerid, InventoryMenu, DIALOG_STYLE_LIST, "Envanter seçimi:", diatxt, "Seç", "Ýptal");
	else		PrintInv(playerid);*/

 	return 1;
}

CMD:envanteryardim(playerid)
{
	SendSyntaxMessage(playerid, "/sigara, /boombox, /benzinbidonu(bidondoldur)");
	return 1;
}

CMD:boombox(playerid)
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Envanteri þu an kullanamazsýnýz.");	
	if(!PlayerInfo[playerid][pBoombox]) return SendErrorMessage(playerid, "Boomboxa sahip deðilsiniz.");

	PlaceBoombox(playerid);
	return 1;
}

alias:sigara("sigarayak");
CMD:sigara(playerid)
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Envanteri þu an kullanamazsýnýz.");	
	if(!PlayerInfo[playerid][pSigara]) return SendErrorMessage(playerid, "Sigaranýz yok.");

   	PlayerInfo[playerid][pSigara]--;
    pc_cmd_server_ame(playerid, "bir adet sigara çýkarýr ve çakmaðýyla yakar.");
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
    SM2(playerid, "Bir sigara yaktýn. Pakette kalan sigara dallarý: %d", PlayerInfo[playerid][pSigara]);

    InfoMSG(playerid, "Sigara icmek icin \" ~g~LKM ~w~\" tusuna basin, sigarayi atmak icin \" ~r~ENTER ~w~\" tusuna basin", 5);
	return 1;
}

alias:bidondoldur("benzinbidonu");
CMD:bidondoldur(playerid)
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Envanteri þu an kullanamazsýnýz.");	
	if(!PlayerInfo[playerid][pBenzinBidonu]) return SendErrorMessage(playerid, "Benzin bidonunuz yok.");

    if (IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araçtayken bu iþlevi gerçekleþtiremezsiniz.");
            
    new vehicle;

    if ((vehicle = GetNearVehicle(playerid, 2.5)) == 0) return SendErrorMessage(playerid, "Yakýnýnýzda araç yok.");
    if (VehicleInfo[vehicle][carFuel] + 20.0 > GetVehicleFuelCapacity(GetVehicleModel(vehicle))) return SendErrorMessage(playerid, "Aracýn yakýt deposu dolu.");

    VehicleInfo[vehicle][carFuel] += 20.0;
    SM2(playerid, "Aracýnýza bidon ile yakýt ikmali yaptýnýz.");
    pc_cmd_me(playerid, "aracýna yakýt doldurur.");
	PlayerInfo[playerid][pBenzinBidonu] = 0;

	return 1;
}

CMD:objesil(playerid, params[])
{
	if (!IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))	return SendWarningMessage(playerid, "Elinizde envantere konulacak bir þey yok. ");
	if (!GetPVarInt(playerid, #attach_item))						return SendErrorMessage(playerid, "Bu komut ile sadece belirli eþyalarý envanterine koyabilirsin! ");

	RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SetPVarInt(playerid, #attach_item, 0);

	if (GiveInvItem(playerid, pTemp[playerid][tempItem], pTemp[playerid][tempQ], pTemp[playerid][tempEx]) == -1) return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

	pTemp[playerid][tempItem] = 0;
	pTemp[playerid][tempEx] = 0;
	pTemp[playerid][tempQ] = 0;
			
	SendSyntaxMessage(playerid, "Elinizde bulunan objeyi sildiniz. ");
	return 1;
}

PrintInv(playerid)
{
	new result[(MAX_INV_SLOTS+5) * 128] = "#\tEþya\tAdet"; //{ffffff}
	if (GetPVarInt(playerid, #pDelay)) return PrintInv(playerid);

	FixInv(playerid);
    for(new i = 0; i < MAX_INV_SLOTS; i++) {
		switch(Inventory[playerid][i][pInvItem])
		{
			case 0:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t{C3C3C3}Boþ Slot", result, i+1);
			}
			case 22 .. 34:
			{
				if (Inventory[playerid][i][pInvQ] == 0) format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]); 
				else 									format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], inventory_items[Inventory[playerid][i][pInvEx]][itemName], Inventory[playerid][i][pInvQ]); 
			}

			case 78, 79:
			{
				if (Inventory[playerid][i][pInvEx] == 0) format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]); 
				else 									 format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %f]{FFFFFF}\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], inventory_items[Inventory[playerid][i][pInvEx]][itemName], Inventory[playerid][i][pInvQFloat]); 
			}
			
			case INV_GANJA, INV_MED_GANJA, 103 .. 118:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s{FFFFFF}\t%.1fg", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], Inventory[playerid][i][pInvQFloat]);
			}
			case INV_DRUG:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[Kalite: %i%%]{FFFFFF}\t%.1fg", result, i+1, Inventory[playerid][i][pInvName], Inventory[playerid][i][pInvEx], Inventory[playerid][i][pInvQFloat]);
			}
			case INV_GASCAN: 
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}
			/*case 103 .. 114:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {}[OAS: %i]{FFFFFF}\t%.1fg", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], PlayerInfo[playerid][pInvQFloat][i]);
			}*/

			/*case 103 .. 114:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}Ñîðò: %s]{FFFFFF}\t%.1fg", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], PlayerInfo[playerid][pInvQFloat][i]);
			}*/


			/*case FISHING_LOWEST_ID .. FISHING_HIGHEST_ID:
			{
				format(result, sizeof(result), "%s\n{FFFFFF}%s (%dlbs)", result, PrintIName(PlayerInfo[playerid][pInvItem][i]), PlayerInfo[playerid][pInvEx][i]);
			}
			case INV_GASCAN:
			{
				//if (PlayerInfo[playerid][pInvQ][i] > 0) 
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);//, PlayerInfo[playerid][pInvEx][i], PlayerInfo[playerid][pInvQ][i]);//FuelName(PlayerInfo[playerid][pInvEx][i]), PlayerInfo[playerid][pInvQ][i]);
				//else 									format(result, sizeof(result), "%s\n{ffffff}%i.\t%s [{C3C3C3}Ïóñòàÿ{FFFFFF}]", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}
			*/
			
			default:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s\t%i", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], Inventory[playerid][i][pInvQ]);
			}
	    }
	}

	if (GetPVarInt(playerid, #attach_item))
	{
		format(result, sizeof(result), "%s\n{ffffff}%i.\t{FF6347}> {FFFFFF}ELÝNDEN AL\n{ffffff}%i.\t{FF6347}> {FFFFFF}YERE BIRAK", result, MAX_INV_SLOTS+1, MAX_INV_SLOTS+2);
	}

	Dialog_Show(playerid, Inventory, DIALOG_STYLE_TABLIST_HEADERS, "Envanter", result, "Seç", "Ýptal");
	return true;
}

PrintInvEx(playerid, userid)
{
	new result[(MAX_INV_SLOTS+1) * 64] = "#\tEþya\tAdet"; //{ffffff}
	if (GetPVarInt(playerid, #pDelay)) return PrintInvEx(playerid, userid);
	
	format(result, sizeof(result), "#\t{33AA33}Para $%i\tEþya Adeti{FFFFFF}\n", PlayerInfo[playerid][pCash]);

    for(new i = 0; i < MAX_INV_SLOTS; i++) 
	{
		switch(Inventory[playerid][i][pInvItem])
		{
			case 0:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i\t{C3C3C3}Boþ Slot", result, i+1);
			}
			case 22 .. 34:
			{
				if (Inventory[playerid][i][pInvQ] == 0) format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]); 
				else 									format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], inventory_items[Inventory[playerid][i][pInvEx]][itemName], Inventory[playerid][i][pInvQ]); 
			}

			case 78, 79:
			{
				if (Inventory[playerid][i][pInvEx] == 0) format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]); 
				else 									format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i]{FFFFFF}\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], inventory_items[Inventory[playerid][i][pInvEx]][itemName], Inventory[playerid][i][pInvQ]); 
			}
			case INV_GASCAN: 
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}
			default:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s\t%i", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], Inventory[playerid][i][pInvQ]);
			}
	    }
	}
	new title[34];

	if (!PlayerInfo[userid][pAdmin])
	{
		new mes[64];
		format(mes,sizeof(mes),"%s adlý kiþinin üstünü arar.", GetNameWithMask(playerid));
		pc_cmd_me(userid, mes);

		title = "Arama %s";
	}
	else title = "Envanter %s";

	format(title, sizeof(title), title, GetNameWithMask(playerid));
	Dialog_Show(userid, None, DIALOG_STYLE_TABLIST_HEADERS, title, result, ">>", "");
	return true;
}

PrintVehInv(playerid, vehid, frisk = 0)
{
	new result[(MAX_TRUNK_INVENTORY+1) * 64] = "#\tEþya\tAdet"; //{ffffff}
	if (GetPVarInt(playerid, #pDelay)) return PrintVehInv(playerid, vehid, frisk);

    for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
	{
		switch(TrunkInventory[vehid][i][pInvItem])
		{
			case 0:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i\t{C3C3C3}Boþ Slot", result, i+1);
			}
			case 22 .. 34:
			{
				if (TrunkInventory[vehid][i][pInvQ] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[TrunkInventory[vehid][i][pInvItem]][itemName]); 
				else 										format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", result, i+1, inventory_items[TrunkInventory[vehid][i][pInvItem]][itemName], inventory_items[TrunkInventory[vehid][i][pInvEx]][itemName], TrunkInventory[vehid][i][pInvQ]); 
			}

			case 78, 79:
			{
				if (TrunkInventory[vehid][i][pInvEx] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[TrunkInventory[vehid][i][pInvItem]][itemName]); 
				else 										format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i]{FFFFFF}\t1", result, i+1, inventory_items[TrunkInventory[vehid][i][pInvItem]][itemName], inventory_items[TrunkInventory[vehid][i][pInvEx]][itemName], TrunkInventory[vehid][i][pInvQ]); 
			}
			case INV_GASCAN: 
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}
			default: format(result, sizeof(result), "%s\n{ffffff}%i.\t%s\t%i", result, i+1, inventory_items[TrunkInventory[vehid][i][pInvItem]][itemName], TrunkInventory[vehid][i][pInvQ]);
	    }
	}

	new title[64];

	if (!frisk)
	{
		if (VehicleInfo[vehid][carFaction] && VehicleInfo[vehid][carFaction] == PlayerInfo[playerid][pFaction])  title = "Bagaj: %s";
		else																									title = "Bagaj: %s";

		format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400]);
		Dialog_Show(playerid, InventoryOther, DIALOG_STYLE_TABLIST_HEADERS, title, result, "Seç", "Ýptal");
	}
	else 
	{
		if (!PlayerInfo[playerid][pAdmin])
		{
			new mes[64];
			format(mes,sizeof(mes),"%s adlý aracýn bagajýný arar.", VehicleNames[GetVehicleModel(vehid)-400]);
			pc_cmd_me(playerid, mes);

			title = "Bagaj aramasý %s";
			format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400]);
		} 
		else 
		{
			title = "%s Bagaj | Sahip: %s";
			if (VehicleInfo[vehid][carOwnerID]) 	format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400], VehicleInfo[vehid][carOwner]);
			else   								format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400], GetInitials(Factions[VehicleInfo[vehid][carFaction]][fName])); 
		}
		
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, title, result, ">>", "");
	}

	if (VehicleInfo[vehid][vCorp] > 0 && CorpInfo[VehicleInfo[vehid][vCorp]][cUsed] == 1) SendWarningMessage(playerid,"Aracýn bagajýnda ceset bulunmuyor.");

	return 1;
}

PrintGBInv(playerid, vehid, frisk = 0)
{
	new result[(MAX_CAR_INVENTORY+1) * 64] = "#\tEþya\tAdet"; //{ffffff}
	if (GetPVarInt(playerid, #pDelay)) return PrintGBInv(playerid, vehid, frisk);

    for(new i = 0; i < MAX_CAR_INVENTORY; i++)
	{
		switch(CarInventory[vehid][i][pInvItem])
		{
			case 0:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i\t{C3C3C3}Boþ Slot", result, i+1);
			}
			case 22 .. 34:
			{
				if (CarInventory[vehid][i][pInvQ] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[CarInventory[vehid][i][pInvItem]][itemName]); 
				else 									format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", result, i+1, inventory_items[CarInventory[vehid][i][pInvItem]][itemName], inventory_items[CarInventory[vehid][i][pInvEx]][itemName], CarInventory[vehid][i][pInvQ]); 
			}

			case 78, 79:
			{
				if (CarInventory[vehid][i][pInvEx] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[CarInventory[vehid][i][pInvItem]][itemName]); 
				else 										format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i]{FFFFFF}\t1", result, i+1, inventory_items[CarInventory[vehid][i][pInvItem]][itemName], inventory_items[CarInventory[vehid][i][pInvEx]][itemName], CarInventory[vehid][i][pInvQ]); 
			}
			
			case INV_GASCAN: 
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}

			default:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s\t%i", result, i+1, inventory_items[CarInventory[vehid][i][pInvItem]][itemName], CarInventory[vehid][i][pInvQ]);
			}
	    }
	}

	new title[64];

	if (!frisk)
	{
		title = "Torpido: %s";
		format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400]);
		Dialog_Show(playerid, InventoryOther, DIALOG_STYLE_TABLIST_HEADERS, title, result, "Seç", "Ýptal");
	}
	else 
	{
		if (!PlayerInfo[playerid][pAdmin])
		{
			new mes[64];
			format(mes,sizeof(mes),"%s model aracýn torpidosunu açar.", VehicleNames[GetVehicleModel(vehid)-400]);
			pc_cmd_me(playerid, mes);

			title = "Torpido: %s";
			format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400]);
		}
		else 
		{
			title = "Torpido: %s | Sahip: %s";
			if (VehicleInfo[vehid][carOwnerID]) 	format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400], VehicleInfo[vehid][carOwner]);
			else   								format(title, sizeof(title), title, VehicleNames[GetVehicleModel(vehid)-400], GetInitials(Factions[VehicleInfo[vehid][carFaction]][fName])); 
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, title, result, ">>", "");
	}	

	return 1;
}

PrintHouseInv(playerid, houseid, frisk = 0)
{
	new result[(MAX_HOUSE_INVENTORY+1) * 64] = "#\tEþya\tMiktar"; //{ffffff}
	if (GetPVarInt(playerid, #pDelay)) return PrintHouseInv(playerid, houseid, frisk);

    for(new i = 0; i < MAX_HOUSE_INVENTORY; i++)
	{
		switch(HouseInventory[houseid][i][pInvItem])
		{
			case 0:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i\t{C3C3C3}Boþ Slot", result, i+1);
			}
			case 22 .. 34:
			{
				if (HouseInventory[houseid][i][pInvQ] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[HouseInventory[houseid][i][pInvItem]][itemName]); 
				else 										format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", result, i+1, inventory_items[HouseInventory[houseid][i][pInvItem]][itemName], inventory_items[HouseInventory[houseid][i][pInvEx]][itemName], HouseInventory[houseid][i][pInvQ]); 
			}

			case 78, 79:
			{
				if (HouseInventory[houseid][i][pInvEx] == 0) 	format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", result, i+1, inventory_items[HouseInventory[houseid][i][pInvItem]][itemName]); 
				else 											format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i]{FFFFFF}\t1", result, i+1, inventory_items[HouseInventory[houseid][i][pInvItem]][itemName], inventory_items[HouseInventory[houseid][i][pInvEx]][itemName], HouseInventory[houseid][i][pInvQ]); 
			}
			
			case INV_GASCAN: 
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s {33FF66}(20L)\t1", result, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
			}
			
			default:
			{
				format(result, sizeof(result), "%s\n{ffffff}%i.\t%s\t%i", result, i+1, inventory_items[HouseInventory[houseid][i][pInvItem]][itemName], HouseInventory[houseid][i][pInvQ]);
			}
	    }
	}

	if (!frisk) Dialog_Show(playerid, InventoryOther, DIALOG_STYLE_TABLIST_HEADERS, "Depo", result, "Seç", "Ýptal");
	else 
	{	
		new title[42];
		if (!PlayerInfo[playerid][pAdmin])
		{
			pc_cmd_me(playerid, "evi araþtýrýr.");
			title = "Evi araþtýrdýn: %s";
		}
		else title = "Ev: %s";

		format(title, sizeof(title), title, HouseInfo[houseid][hOwner]);
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, title, result, ">>", "");
	}	

	return 1;
}
