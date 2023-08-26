Dialog:Inventory(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
	if (GetPVarInt(playerid, "pDelay"))					return pc_cmd_envanter(playerid, "");

	new title[56], mes[256];

	if (listitem == MAX_INV_SLOTS) // STORE WEAPON SECTION !
	{
		if (GetPVarInt(playerid, #attach_item)) 	return pc_cmd_objesil(playerid, "");
	}
	else if (listitem == MAX_INV_SLOTS + 1) // DROP WEAPON SECTION !
	{
		if (GetPVarInt(playerid, #attach_item))	return pc_cmd_yerebirak(playerid, "");
	}

	if (Inventory[playerid][listitem][pInvItem] == 0)	return pc_cmd_envanter(playerid, "");

	if (inventory_items[Inventory[playerid][listitem][pInvItem]][itemSplit])
		if ((inventory_items[Inventory[playerid][listitem][pInvItem]][itemType] == ITEM_TYPE_DRUGS || inventory_items[Inventory[playerid][listitem][pInvItem]][itemType] == ITEM_TYPE_SEEDS) && (IsPlayerHasItem(playerid, 78) || IsPlayerHasItem(playerid, 79)))
			mes = "Eþyayý kullan\nEþyayý ver\nEþyayý at\nEþyayý sil\nBöl\nBirleþtir\nPakete koy /paket";
		else
			mes = "Eþyayý kullan\nEþyayý ver\nEþyayý at\nEþyayý sil\nBöl\nBirleþtir";
	else
	{
		if (inventory_items[Inventory[playerid][listitem][pInvItem]][itemType] == ITEM_TYPE_INSIDEABLE_OBJECT)
		{
			if (Inventory[playerid][listitem][pInvEx]) 
				format(mes, sizeof(mes), "Slot %s(%f)\nEþyayý ver\nEþyayý býrak\nEþyayý sil", inventory_items[Inventory[playerid][listitem][pInvEx]][itemName], Inventory[playerid][listitem][pInvQFloat]);
			else mes = "Eþyayý yerleþtir\nEþyayý ver\nEþyayý býrak\nEþyayý sil";

			if (!GetPVarInt(playerid, #attach_item)) format(mes, sizeof(mes), "%s\nYerden al", mes);
		}
		else
			mes = "Eþyayý kullan\nEþyayý ver\nEþyayý at\nEþyayý sil";
	}

    new houseid = -1;
	if ((houseid = GetNearInsideHouse(playerid)) != -1 && houseid >= 0 && houseid < MAX_HOUSES && PlayerToPoint(7, playerid,HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]))
	{
	    SetPVarInt(playerid, #inventory_house, houseid+1);
 		format(mes, sizeof(mes), "%s\n{ffff00}Eve býrak (ID: %i)", mes, houseid);
	}

	new vehicle = GetNearVehicle(playerid, 4.0);
	if (vehicle != 0 && (!IsADontTrunk(vehicle) || !IsAPlane(vehicle) || !IsABiker(vehicle) || !IsAHelicopter(vehicle) || !IsABoat(vehicle) || !IsABicycle(vehicle)))
	{
		if ((VehicleInfo[vehicle][carTrunkLock] && !IsPlayerInAnyVehicle(playerid)) || (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]))
		{
			SetPVarInt(playerid, #inventory_vehicle, vehicle);
			format(mes, sizeof(mes), "%s\n{ffff00}%s adlý araca yerleþtir (ID: %i)", mes, VehicleNames[GetVehicleModel(vehicle)-400], vehicle);
		}
	}

	if (GetPVarInt(playerid, #inventory_vehicle) == 0 && inventory_items[Inventory[playerid][listitem][pInvItem]][itemSize] == ITEM_SIZE_SMALL)
	{
		vehicle = GetPlayerVehicleID(playerid);
		if (IsPlayerInAnyVehicle(playerid) && vehicle != 0 && VehicleInfo[vehicle][carOwnerID] == PlayerInfo[playerid][pID])
		{
			format(mes, sizeof(mes), "%s\n{ffff00}%s model aracýn torpido gözüne yerleþtir (ID: %i)", mes, VehicleNames[GetVehicleModel(vehicle)-400], vehicle);	
		}
	}

	SetPVarInt(playerid, #inventory_choose, listitem);
	format(title, sizeof(title), "{FFFFFF}Envanter > %s", inventory_items[Inventory[playerid][listitem][pInvItem]][itemName]);
    Dialog_Show(playerid, InventoryChoose, DIALOG_STYLE_LIST, title, mes, "Seç", "Geri Dön");
	return 1;
}

Dialog:InventoryChoose(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_envanter(playerid, "");

	new slot = GetPVarInt(playerid, #inventory_choose);

	if (slot < 0 || slot > MAX_INV_SLOTS-1 || Inventory[playerid][slot][pInvItem] == 0)	return pc_cmd_envanter(playerid, "");
	
	if (listitem > 3 || (listitem == 0 && inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_INSIDEABLE_OBJECT))
	{
		new listadd;
		if (inventory_items[Inventory[playerid][slot][pInvItem]][itemSplit])
			if ((inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_DRUGS || inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_SEEDS) && (IsPlayerHasItem(playerid, 78) || IsPlayerHasItem(playerid, 79)))
				listadd = 3;
			else
				listadd = 2;
		else 
		{
			if (inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_INSIDEABLE_OBJECT)
			{
				if (listitem == 4)
				{
					if (!GetPVarInt(playerid, #attach_item))	listadd = 6; //Âçÿòü â ðóêè								
				}
				else
				{
					if (Inventory[playerid][slot][pInvEx]) 	listadd = 4; // Äîñòàòü
					else 									listadd = 5; // Ïîëîæèòü
				}											
			}
			else listadd = 0;
		}

		switch(listitem)
		{
			case 0:
			{
				switch(listadd)
				{
					case 4: listitem = 8; // Äîñòàòü
					case 5: listitem = 9; // Ïîëîæèòü
				}
			}
			case 4:
			{
				switch(listadd)
				{
					case 0: listitem = 4; // ÁÀÃÀÆÍÈÊ
					case 2: listitem = 5; // ÐÀÇÄÅËÈÒÜ
					case 3: listitem = 5; // ÐÀÇÄÅËÈÒÜ
					case 6: listitem = 10; // ÂÇßÒÜ Â ÐÓÊÈ
				}
			}
			case 5:
			{
				switch(listadd)
				{
					case 2: listitem = 6; // ÎÁÚÅÄÈÍÈÒÜ
					case 3: listitem = 6; // ÎÁÚÅÄÈÍÈÒÜ
				}
			}
			case 6:
			{
				switch(listadd)
				{
					case 2: listitem = 4; //ÁÀÃÀÆÍÈÊ
					case 3: listitem = 7; // ÏÎËÎÆÈÒÜ Â
				}
			}
			case 7:
			{
				listitem = 4;// ÁÀÃÀÆÍÈÊ
			}
		}
	}

	switch(listitem)
	{
	    case 0: CallLocalFunction("OnPlayerUseItem", "ii", playerid, slot);
		case 1: Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "{FFFFFF}Eþyayý ver", "{ffffff}Eþyayý vermek istediðiniz kiþinin ID'sini giriniz.", ">>>", "Geri Dön");
		case 2:
		{
			if (inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_AMMO || inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_WEAPON)
			{
				if (IsAdminDuty(playerid) || IsTesterDuty(playerid))	return SendErrorMessage(playerid, "Ýlk önce /aduty'den çýkýþ yapýn.");
				if (PlayerInfo[playerid][pOnDuty])								return SendErrorMessage(playerid, "Bu fonksiyon iþbaþýnda kullanýlamaz.");
			}

			if (Inventory[playerid][slot][pInvQ])	
			{
				if (inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_WEAPON)
				{
					if (ItemDrop_Drop(playerid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQ], Inventory[playerid][slot][pInvQFloat], Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)	return SendErrorMessage(playerid, "The maximum number of dropped items has been reached.");
					switch(inventory_items[Inventory[playerid][slot][pInvItem]][itemType]) {
						case 22..34: SendSyntaxMessage(playerid, "Eþya býraktýnýz: %s [%s / %i mermi]. {ffc46a}/yerdenal{FFFFFF} komutunu kullanabilirsiniz.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], inventory_items[Inventory[playerid][slot][pInvEx]][itemName], inventory_items[Inventory[playerid][slot][pInvQ]][itemName]);
						default: 	 SendSyntaxMessage(playerid, "Eþya býraktýnýz: %s. {ffc46a}/yerdenal{FFFFFF} komutunu kullanabilirsiniz.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
					}
				}
				else if (inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_DRUGS || inventory_items[Inventory[playerid][slot][pInvItem]][itemType] == ITEM_TYPE_REACT)
				{
					
				}
				else 
				{
					if (ItemDrop_Drop(playerid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQ], Inventory[playerid][slot][pInvQFloat], Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)	return SendErrorMessage(playerid, "The maximum number of dropped items has been reached.");
					SendSyntaxMessage(playerid, "Eþya býraktýnýz: %s [%i adet]. {ffc46a}/yerdenal{FFFFFF} komutunu kullanabilirsiniz.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);
				}
			}
			else
			{
				if (ItemDrop_Drop(playerid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQ], Inventory[playerid][slot][pInvQFloat], Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)	return SendErrorMessage(playerid, "The maximum number of dropped items has been reached.");
				SendSyntaxMessage(playerid, "Eþya býraktýnýz: %s. {ffc46a}/yerdenal{FFFFFF} komutunu kullanabilirsiniz.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);			
			}
			RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
		}
		case 3:
		{
			new mes[128];
			format(mes, sizeof(mes), "{ffffff}Bu eþyayý silmek istediðine emin misin? - %s", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
   			Dialog_Show(playerid, DeleteItem, DIALOG_STYLE_MSGBOX, "{FFFFFF}Eþyayý sil", mes, "Kabul", "Ýptal");
		}
		case 4:
		{
		    new mes[128];

		    if (GetPVarInt(playerid, #inventory_house) != 0)
			{
				if (Inventory[playerid][slot][pInvQ] > 1 && inventory_items[Inventory[playerid][slot][pInvItem]][itemSplit]) 
				{
					format(mes, sizeof(mes), "{ffffff}Eþya: %s (Miktar: %i)\n\nEvde saklamak istediðiniz miktarý girin: ",
					inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);
				}
				else
				{
					new 
						houseid = GetNearInsideHouse(playerid),
						i = GetNextHouseTrunkSlot(houseid),
						item = Inventory[playerid][slot][pInvItem]
					;

					if (houseid >= 0 && houseid < MAX_HOUSES && PlayerToPoint(1, playerid,HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]))
					{

						if (i == -1)		return SendErrorMessage(playerid, "Evde boþ oda kalmamýþ.");
						if (item == 0) 		return pc_cmd_envanter(playerid, "");
						
						SM2(playerid, "%s adlý eþyayý eve býraktýn.", inventory_items[item][itemName]);

						HouseInventory[houseid][i][pInvItem] 	= Inventory[playerid][slot][pInvItem];
						HouseInventory[houseid][i][pInvQ]		= Inventory[playerid][slot][pInvQ];
						HouseInventory[houseid][i][pInvEx]		= Inventory[playerid][slot][pInvEx];
						HouseInventory[houseid][i][pInvS]		= Inventory[playerid][slot][pInvS];
						HouseInventory[houseid][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
						format(HouseInventory[houseid][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
						RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
						
						format(mes, sizeof(mes), "%s adlý eþyayý eve býrakýr.", inventory_items[item][itemName]);
						SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

						
						return pc_cmd_envanter(playerid, "");
					}
				}
			}
			else if (GetPVarInt(playerid, #inventory_vehicle) != 0)
			{
				if (Inventory[playerid][slot][pInvQ] > 1 && inventory_items[Inventory[playerid][slot][pInvItem]][itemSplit]) 
				{
   			    	format(mes, sizeof(mes), "{ffffff}Eþya: %s (Miktar: %i)\n\nBagaja býrakmak istediðiniz miktarý girin: ",
					inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);
				}
				else 
				{
					new vehicle = GetPVarInt(playerid, #inventory_vehicle);

					new item = Inventory[playerid][slot][pInvItem];
					if (item == 0) return pc_cmd_envanter(playerid, "");

					if (vehicle > 0 && GetNearVehicle(playerid, 5.0, vehicle) != 0)
					{
						if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))		return SendErrorMessage(playerid, "Bu aracýn bagajý bulunmuyor.");
						if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])										return SendErrorMessage(playerid, "Kendine ait olmayan birlik aracýnýn bagajýna bakamazsýnýz.");
						if (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction]) 	return SendErrorMessage(playerid, "Bagaja yakýn olmalýsýn");
						if (!IsPlayerInAnyVehicle(playerid) && !VehicleInfo[vehicle][carTrunkLock]) 																	return SendErrorMessage(playerid, "Bu aracýn bagajý kapalý.");

						new i = GetNextVehicleTrunkSlot(vehicle);
						if (i == -1)	return SendErrorMessage(playerid, "Araçta boþ yer yok. ");

						TrunkInventory[vehicle][i][pInvItem] 	= Inventory[playerid][slot][pInvItem];
						TrunkInventory[vehicle][i][pInvQ] 		= Inventory[playerid][slot][pInvQ];
						TrunkInventory[vehicle][i][pInvEx]		= Inventory[playerid][slot][pInvEx];
						TrunkInventory[vehicle][i][pInvS] 		= Inventory[playerid][slot][pInvS];
						TrunkInventory[vehicle][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
						format(TrunkInventory[vehicle][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
						RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
						
						SM2(playerid, "%s adlý eþyayý %s model araca yerleþtirdin.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);

						format(mes, sizeof(mes), "%s adlý eþyayý %s model aracýn %s yerleþtirir.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400], (VehicleInfo[vehicle][carFaction])?("bagaja"):("bagaja"));
						SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
						return pc_cmd_envanter(playerid, "");
					}
				}
			}
			else if (GetPVarInt(playerid, #inventory_vehicle) == 0 && IsPlayerInAnyVehicle(playerid))
			{
				new vehicle = GetPlayerVehicleID(playerid);
				if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID] && vehicle == 0) return pc_cmd_envanter(playerid, "");

				if (Inventory[playerid][slot][pInvQ] > 1 && inventory_items[Inventory[playerid][slot][pInvItem]][itemSplit]) 
				{
   			    	format(mes, sizeof(mes), "{ffffff}Eþya: %s (Miktar: %i)\n\nBagaja koymak istediðiniz eþya miktarýný girin:", 
					inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);
				}
				else 
				{
					new 
						i = GetNextVehicleGBSlot(vehicle),
						item = Inventory[playerid][slot][pInvItem]
					;

					if (vehicle == 0) 	return pc_cmd_envanter(playerid, "");
					if (item == 0) 		return pc_cmd_envanter(playerid, "");
					if (i == -1)		return SendErrorMessage(playerid, "Araçta boþ yer yok. ");

					if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])		  									
						return SendErrorMessage(playerid, "Bu aracýn torpido gözünü kullanamazsýn.");
					
					CarInventory[vehicle][i][pInvItem]		= Inventory[playerid][slot][pInvItem];
					CarInventory[vehicle][i][pInvQ]			= Inventory[playerid][slot][pInvQ];
					CarInventory[vehicle][i][pInvEx] 		= Inventory[playerid][slot][pInvEx];
					CarInventory[vehicle][i][pInvS]			= Inventory[playerid][slot][pInvS];
					CarInventory[vehicle][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
					format(CarInventory[vehicle][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
					RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
						
					SM2(playerid, "%s adlý eþyayý %s model aracýn torpidosuna yerleþtirdin.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);

					format(mes, sizeof(mes), "%s adlý eþyayý %s model aracýn torpidosuna yerleþtirir.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);
					SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

					
					return pc_cmd_envanter(playerid, "");
				}
			}
			else return SendErrorMessage(playerid, "Bir þeyler ters gitti, geliþtiriciye ulaþýn.!");
			
			Dialog_Show(playerid, PutItemInProperty, DIALOG_STYLE_INPUT, "{FFFFFF}Eþyayý yerleþtir", mes, "Yerleþtir", "Ýptal");
			return 1;
		}
		case 5: // Ðàçäåëèòü 
		{
			if (!inventory_items[Inventory[playerid][slot][pInvItem]][itemFloat]) {
				if (Inventory[playerid][slot][pInvQ] < 2)	
					return SendErrorMessage(playerid, "Ayýrmak için daha yüksek miktar girmelisin.");
						
				new divide_string[128];
				format(divide_string, sizeof(divide_string), "{FFFFFF}Eþyadan ayýrmak istediðiniz miktarý girin: %s {ffc46a}(%i){FFFFFF}?", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);
				Dialog_Show(playerid, DivideInvInt, DIALOG_STYLE_INPUT, "Eþya bölme", divide_string, ">>>","Return");
			} else {
				if (Inventory[playerid][slot][pInvQFloat] < 0.2)	
					return SendErrorMessage(playerid, "Bölmek için geçerli sayý giriniz: (0,2)");
						
				new divide_string[128];
				format(divide_string, sizeof(divide_string), "{FFFFFF}Eþyadan kaç gram ayýrmak istediðinizi seçiniz: %s {ffc46a}(%.1fg){FFFFFF}?", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQFloat]);
				Dialog_Show(playerid, DivideInvFloat, DIALOG_STYLE_INPUT, "Eþya bölme", divide_string, ">>>","Return");
			}
			
			return 1;
		}
		case 6: // Îáúåäèíèòü
		{
			FixInv(playerid);

			SendHelpMessage(playerid, "%s (%i) eþyasýný birleþtirmek istediðiniz eþyayý seçin.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ]);

			new dlgstr[20 * 128] = "#\tEþya\tAdet";

			new ccount;
			for(new i = 0; i < MAX_INV_SLOTS; i++) 
			{
				switch(Inventory[playerid][i][pInvItem])
				{
					case 0:	format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i\t{C3C3C3}Boþ Slot", dlgstr, i+1);
					case 22 .. 34:
					{
						if (Inventory[playerid][i][pInvQ] == 0) 	format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i.\t%s {C3C3C3}[boþ]\t1", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]); 
						else 									format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i.\t%s {C3C3C3}[%s / %i mermi]{FFFFFF}\t1", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], inventory_items[Inventory[playerid][i][pInvEx]][itemName], Inventory[playerid][i][pInvQ]); 
					}
					case INV_GANJA, INV_MED_GANJA, 103 .. 118:
					{
						format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i.\t%s{FFFFFF}\t%.1fg", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], Inventory[playerid][i][pInvQFloat]);
					}
					case INV_DRUG:
					{
						format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i.\t%s {C3C3C3}[OAS: %i%%]{FFFFFF}\t%.1fg", dlgstr, i+1, Inventory[playerid][i][pInvName], Inventory[playerid][i][pInvEx], Inventory[playerid][i][pInvQFloat]);
					}
					default: format(dlgstr, sizeof(dlgstr), "%s\n{ffffff}%i.\t%s\t%i", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName], Inventory[playerid][i][pInvQ]);	
				}
				ccount++;
			}
			if (!ccount) return SendErrorMessage(playerid, "Objeler eþleþmiyor!");

			Dialog_Show(playerid, CombInv, DIALOG_STYLE_TABLIST_HEADERS, "Envanter", dlgstr, "Seç", "Ýptal");
			return 1;
		}
		case 7: //Ïîëîæèòü â
		{
			new dlgstr[32*MAX_INV_SLOTS];

			format(dlgstr, sizeof(dlgstr), "Eþyayý nereye yerleþtireceðinizi seçin '%s':{FFFFFF}\n", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

			new ccount;
			for(new i = 0; i < MAX_INV_SLOTS; i++) 
			{
				if (inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_INSIDEABLE_OBJECT)
				{
					if (!Inventory[playerid][i][pInvEx])
					{
						ccount++;
						format(dlgstr, sizeof(dlgstr), "%s%i. %s\n", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
					}
				}
			}
			if (!ccount) return SendErrorMessage(playerid, "Objeler eþleþmiyor!");

			Dialog_Show(playerid, InventoryPut, DIALOG_STYLE_TABLIST_HEADERS, "Envanter", dlgstr, "Seç", "Ýptal");
			return 1;
		}
		case 8: // äîñòàòü
		{
			if (!Inventory[playerid][slot][pInvEx])	return 1;

			if (!CheckInv(playerid))					
			{
				pc_cmd_envanter(playerid, "");
				return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
			}

			if (GiveInvItem(playerid, Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvQ]) == -1) return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
			SendSyntaxMessage(playerid, "Eþyayý aldýnýz: %s (%i) - %s.", inventory_items[Inventory[playerid][slot][pInvEx]][itemName], Inventory[playerid][slot][pInvQ], inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

			Inventory[playerid][slot][pInvEx] = 0;
			Inventory[playerid][slot][pInvQ] = 1;

			return 1;	
		}
		case 9: // ïîëîæèòü
		{
			new dlgstr[32*MAX_INV_SLOTS];

			format(dlgstr, sizeof(dlgstr), "Silmek istediðiniz eþyayý seçin '%s':{FFFFFF}\n", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

			new ccount;
			for(new i = 0; i < MAX_INV_SLOTS; i++) 
			{
				if (inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_DRUGS || inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_SEEDS)
				{
					ccount++;
					if (inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_DRUGS){
						format(dlgstr, sizeof(dlgstr), "%s%i. %s\n", dlgstr, i+1, Inventory[playerid][i][pInvName]);
					} else {
						format(dlgstr, sizeof(dlgstr), "%s%i. %s\n", dlgstr, i+1, inventory_items[Inventory[playerid][i][pInvItem]][itemName]);
					}
					
				}
			}

			if (!ccount) return SendErrorMessage(playerid, "Objeler eþleþmiyor!");

			Dialog_Show(playerid, InventoryPut2, DIALOG_STYLE_TABLIST_HEADERS, "Envanter", dlgstr, "Seç", "Ýptal");
			return 1;
		}
		case 10:
		{
			if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
				return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

			if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))	return SendWarningMessage(playerid, "Elleriniz dolu.");
			if (GetPlayerVehicleID(playerid) != 0)						return SendErrorMessage(playerid, "Herhangi bir araçta deðilsin.");
			
			if (Inventory[playerid][slot][pInvItem] == 78)
			{
    			SetPlayerAttachedObject(playerid, ATTACH_HANDS, 19571, 6, -0.157999, -0.002000, -0.169000, -21.999990, 87.000022, 0.000000, 1.186000, 1.000000, 1.170000);
  				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			}
			else if (Inventory[playerid][slot][pInvItem] == 79)
			{
				SetPlayerAttachedObject(playerid, ATTACH_HANDS, inventory_items[Inventory[playerid][slot][pInvItem]][itemModel], 6, 0.204, 0.012, 0.026, 0.0, -101.3, -10.5, 0.838, 0.5, 0.597);
			}

			SetPVarInt(playerid, #attach_item, 1);

			pTemp[playerid][tempItem]	= Inventory[playerid][slot][pInvItem];
			pTemp[playerid][tempEx] 	= Inventory[playerid][slot][pInvEx];
			pTemp[playerid][tempQ] 		= Inventory[playerid][slot][pInvQ];

			InfoMSG(playerid, "~n~~y~Envanterine~w~ esyayi yerlestirmek icin  ~y~/PUT~w~ veya ~y~/DROP~w~ komutunu kullanabilirsin", 5);
			SendSyntaxMessage(playerid, "%s adlý eþyayý aldýn.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

			RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
			return 1;
		}
	}
	return 1;
}

Dialog:InventoryPut2(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_envanter(playerid, "");

	new count,
		slot = GetPVarInt(playerid, #inventory_choose);

	for(new i = 0; i < MAX_INV_SLOTS; i++) 
	{
		if (inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_DRUGS || inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_SEEDS)
		{
			if (listitem == count)	
			{
				count = i;
				break;
			}
			else count++;
		}
	}

	Inventory[playerid][slot][pInvEx] = Inventory[playerid][count][pInvItem];
	Inventory[playerid][slot][pInvQ] = Inventory[playerid][count][pInvQ];

	SendSyntaxMessage(playerid, "Baþarýyla eþyayý sildin: %s (%i) - %s.", inventory_items[Inventory[playerid][slot][pInvEx]][itemName], Inventory[playerid][slot][pInvQ], inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

	RemoveInvItem(playerid, Inventory[playerid][count][pInvItem], 0, count);
	return 1;
}


Dialog:InventoryPut(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_envanter(playerid, "");

	new count,
		slot = GetPVarInt(playerid, #inventory_choose);

	for(new i = 0; i < MAX_INV_SLOTS; i++) 
	{
		if (inventory_items[Inventory[playerid][i][pInvItem]][itemType] == ITEM_TYPE_INSIDEABLE_OBJECT)
		{
			if (!Inventory[playerid][i][pInvEx])
			{
				if (listitem == count)	
				{
					count = i;
					break;
				}
				else count++;
			}
		}
	}

	Inventory[playerid][count][pInvEx] = Inventory[playerid][slot][pInvItem];
	Inventory[playerid][count][pInvQ] = Inventory[playerid][slot][pInvQ];

	SendSyntaxMessage(playerid, "Baþarýyla eþyayý sildin: %s (%i) - %s.", inventory_items[Inventory[playerid][count][pInvEx]][itemName], Inventory[playerid][count][pInvQ], inventory_items[Inventory[playerid][count][pInvItem]][itemName]);

	RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
	return 1;
}

Dialog:CombInv(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_envanter(playerid, "");

	new slot1 = GetPVarInt(playerid, #inventory_choose),
		slot2 = listitem;

	if (Inventory[playerid][slot1][pInvItem] != Inventory[playerid][slot2][pInvItem])
	{
		SendErrorMessage(playerid, "Sadece ayný eþyalarý birleþtirebilirsin.");
		return pc_cmd_envanter(playerid, "");
	}

	if (slot1 == slot2)
	{
		SendErrorMessage(playerid, "Bir öðeyi kendisiyle birleþtiremezsiniz. ");
		return pc_cmd_envanter(playerid, "");
	}
	
	switch(Inventory[playerid][slot1][pInvItem])
	{
		case INV_GANJA, INV_MED_GANJA, 103 .. 118:
		{
			if (Inventory[playerid][slot1][pInvQFloat] + Inventory[playerid][slot2][pInvQFloat] > 999.0) {
				SendErrorMessage(playerid, "Birleþtirilen eþyalar için maksimum belirlenen sýnýr - 999g. ");
				return pc_cmd_envanter(playerid, "");
			}

			Inventory[playerid][slot2][pInvQFloat] += Inventory[playerid][slot1][pInvQFloat];
			SendSyntaxMessage(playerid, "Eþyayý baþarýyla birleþtirdin: %s (%.1fg).", inventory_items[Inventory[playerid][slot2][pInvItem]][itemName], Inventory[playerid][slot2][pInvQFloat]);

			RemoveFloatInvItem(playerid, Inventory[playerid][slot1][pInvItem], 0.0, slot1);
		}
		case INV_DRUG:
		{
			if (!CompareStrings(Inventory[playerid][slot2][pInvName], Inventory[playerid][slot2][pInvName])) {
				SendErrorMessage(playerid, "Ýki ayrý uyuþturucuyu birleþtiremezsin. (Farklý isimler!) ");
				return pc_cmd_envanter(playerid, "");
			}
			if (Inventory[playerid][slot1][pInvEx] != Inventory[playerid][slot2][pInvEx]) {
				SendErrorMessage(playerid, "Ýki ayrý uyuþturucuyu birleþtiremezsin. (Saflýk dereceleri farklý!) ");
				return pc_cmd_envanter(playerid, "");
			}
			if (Inventory[playerid][slot1][pInvQFloat] + Inventory[playerid][slot2][pInvQFloat] > 999.0) {
				SendErrorMessage(playerid, "Birleþtirilen iki eþyanýn aðýrlýðý þunu geçemez: 999g. ");
				return pc_cmd_envanter(playerid, "");
			}

			Inventory[playerid][slot2][pInvQFloat] += Inventory[playerid][slot1][pInvQFloat];
			SendSyntaxMessage(playerid, "Eþyayý baþarýyla birleþitrdin: %s {C3C3C3}[OAS: %i%%]{FFFFFF} (%.1fg).", Inventory[playerid][slot2][pInvName], Inventory[playerid][slot2][pInvEx], Inventory[playerid][slot2][pInvQFloat]);

			RemoveFloatInvItem(playerid, Inventory[playerid][slot1][pInvItem], 0.0, slot1);
		}
		default: {
			if ((Inventory[playerid][slot1][pInvQ] + Inventory[playerid][slot2][pInvQ] > 100) && (inventory_items[Inventory[playerid][slot1][pInvQ]][itemType] == ITEM_TYPE_SEEDS || inventory_items[Inventory[playerid][slot1][pInvQ]][itemType] == ITEM_TYPE_DRUGS))
			{
				SendErrorMessage(playerid, "Birleþtirilen eþyalarýn toplam miktarý 100 sayýsýný geçemez. ");
				return pc_cmd_envanter(playerid, "");
			} 
			else if (Inventory[playerid][slot1][pInvQ] + Inventory[playerid][slot2][pInvQ] > 10)
			{
				SendErrorMessage(playerid, "Birleþtirilen eþyalarýn toplam miktarý 10 sayýsýný geçemez. ");
				return pc_cmd_envanter(playerid, "");
			}

			Inventory[playerid][slot2][pInvQ] += Inventory[playerid][slot1][pInvQ];
			SendSyntaxMessage(playerid, "Eþyayý baþarýyla birleþtirdin: %s (%i).", inventory_items[Inventory[playerid][slot2][pInvItem]][itemName], Inventory[playerid][slot2][pInvQ]);

			RemoveInvItem(playerid, Inventory[playerid][slot1][pInvItem], 0, slot1);
		}
	}

	return 1;
}

Dialog:DivideInvInt(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_envanter(playerid, "");

	new slot1 = GetPVarInt(playerid, #inventory_choose);
	
	if (CheckInv(playerid) == 0) 
		return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
	if (strval(inputtext) <= 0 || strval(inputtext) >= Inventory[playerid][slot1][pInvQ]) 
		return SendErrorMessage(playerid, "Geçersiz deðer.");

	SendSyntaxMessage(playerid, "Baþarýlý bir þekilde eþyayý böldün: {ffc46a}%s{ffffff} - %.1fg ve %.1fg.", inventory_items[Inventory[playerid][slot1][pInvItem]][itemName], strval(inputtext), Inventory[playerid][slot1][pInvQ]-strval(inputtext));
	
	Inventory[playerid][slot1][pInvQ] -= strval(inputtext);

	new str[1] = EOS;
	GiveInvItem(playerid, Inventory[playerid][slot1][pInvItem], strval(inputtext), 0, 0, str, 1);
	return 1;
}

Dialog:DivideInvFloat(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_envanter(playerid, "");

	new slot1 = GetPVarInt(playerid, #inventory_choose);
	
	if (CheckInv(playerid) == 0)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

	if (floatstr(inputtext) < 0.1 || floatstr(inputtext) >= Inventory[playerid][slot1][pInvQFloat])  
		return SendErrorMessage(playerid, "Geçersiz deðer.");

	SendSyntaxMessage(playerid, "Baþarýlý bir þekilde eþyayý böldün: {ffc46a}%s{ffffff} - %.1fg ve %.1fg.", inventory_items[Inventory[playerid][slot1][pInvItem]][itemName], floatstr(inputtext), Inventory[playerid][slot1][pInvQFloat]-floatstr(inputtext));
	
	Inventory[playerid][slot1][pInvQFloat] -= floatstr(inputtext);
	
	new str[1] = EOS;
	GiveFloatInvItem(playerid, Inventory[playerid][slot1][pInvItem], floatstr(inputtext), 0, 0, str, 1);
	return 1;
}

Dialog:PutItemInProperty(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_envanter(playerid, "");

    new 
		slot = GetPVarInt(playerid, #inventory_choose), 
		houseid = GetPVarInt(playerid, #inventory_house)-1, 
		vehicle = GetPVarInt(playerid, #inventory_vehicle),
		item = Inventory[playerid][slot][pInvItem]
	;

	if (slot < 0 || slot > MAX_INV_SLOTS-1 || item == 0)	
		return pc_cmd_envanter(playerid, "");
    if (strval(inputtext) < 1 || Inventory[playerid][slot][pInvQ] < strval(inputtext))	
		return SendErrorMessage(playerid, "Miktar yeterli deðil. ");

	if (GetPVarInt(playerid, #inventory_vehicle) != 0)
	{
		if (vehicle > 0 && GetNearVehicle(playerid, 5.0, vehicle) != 0)
		{
			if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))		return SendErrorMessage(playerid, "Bu aracýn bagajý bulunmuyor.");
			if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])										return SendErrorMessage(playerid, "Bu aracýn bagajýný kullanamazsýn. ");
			if (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction]) 	return SendErrorMessage(playerid, "Bagajýn yanýnda durmalýsýn. ");
			if (!IsPlayerInAnyVehicle(playerid) && !VehicleInfo[vehicle][carTrunkLock]) 																	return SendErrorMessage(playerid, "Bu aracýn bagajý kapalý. ");
			
			new i = GetNextVehicleTrunkSlot(vehicle);
			if (i == -1)	return SendErrorMessage(playerid, "Araçta yeteri kadar yer kalmamýþ.");

			TrunkInventory[vehicle][i][pInvItem] 	= Inventory[playerid][slot][pInvItem];
			TrunkInventory[vehicle][i][pInvQ] 		= Inventory[playerid][slot][pInvQ];
			TrunkInventory[vehicle][i][pInvEx] 		= Inventory[playerid][slot][pInvEx];
			TrunkInventory[vehicle][i][pInvS] 		= Inventory[playerid][slot][pInvS];
			TrunkInventory[vehicle][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
			format(TrunkInventory[vehicle][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
			Inventory[playerid][slot][pInvQ] -= strval(inputtext);
						
			SM2(playerid, "%s adlý eþyayý %s model aracýn bagajýna koydun.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);

			new mes[128];
			format(mes, sizeof(mes), "%s (%i) eþyasýný %s model aracýn %s yerleþtirir.", inventory_items[item][itemName], strval(inputtext), VehicleNames[GetVehicleModel(vehicle)-400], (VehicleInfo[vehicle][carFaction])?("bagajýna"):("bagajýna"));
			SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

			
			return pc_cmd_envanter(playerid, "");
		}
	}

    else if (GetPVarInt(playerid, #inventory_vehicle) == 0 && IsPlayerInAnyVehicle(playerid))
	{
	    vehicle = GetPlayerVehicleID(playerid);
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID] && vehicle == 0) return pc_cmd_envanter(playerid, "");

		new i = GetNextVehicleGBSlot(vehicle);
		if (i == -1)	return SendErrorMessage(playerid, "Araçta boþ yer yok.");

		CarInventory[vehicle][i][pInvItem]		= Inventory[playerid][slot][pInvItem];
		CarInventory[vehicle][i][pInvQ]			= Inventory[playerid][slot][pInvQ];
		CarInventory[vehicle][i][pInvEx] 		= Inventory[playerid][slot][pInvEx];
		CarInventory[vehicle][i][pInvS]			= Inventory[playerid][slot][pInvS];
		CarInventory[vehicle][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
		format(CarInventory[vehicle][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
		Inventory[playerid][slot][pInvQ] -= strval(inputtext);
						
		SM2(playerid, "%s (%i) adlý eþyayý %s model aracýn torpidosuna yerleþtirdin.", inventory_items[item][itemName], strval(inputtext), VehicleNames[GetVehicleModel(vehicle)-400]);
		
		new mes[128];
		format(mes, sizeof(mes), "%s adlý eþyayý %s model aracýn torpidosuna yerleþtirir.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

		
		return pc_cmd_envanter(playerid, "");
	}

	else if (GetPVarInt(playerid, #inventory_house) != 0)
	{
		new i = GetNextHouseTrunkSlot(houseid);

		if ((houseid = GetNearInsideHouse(playerid)) != -1 && houseid >= 0 && houseid < MAX_HOUSES && PlayerToPoint(1, playerid,HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]))
		{

			if (i == -1)	return SendErrorMessage(playerid,"Boþ yer bulunamadý.");
			SM2(playerid, "%s adlý eþyayý eve býrakýr.", inventory_items[item][itemName]);

			HouseInventory[houseid][i][pInvItem] 	= Inventory[playerid][slot][pInvItem];
			HouseInventory[houseid][i][pInvQ]		= Inventory[playerid][slot][pInvQ];
			HouseInventory[houseid][i][pInvEx]		= Inventory[playerid][slot][pInvEx];
			HouseInventory[houseid][i][pInvS]		= Inventory[playerid][slot][pInvS];
			HouseInventory[houseid][i][pInvQFloat]	= Inventory[playerid][slot][pInvQFloat];
			format(HouseInventory[houseid][i][pInvName],16, "%s", Inventory[playerid][slot][pInvName]);
						
			Inventory[playerid][slot][pInvQ] -= strval(inputtext);
						
			new mes[128];
			format(mes, sizeof(mes), "%s (%i) eþyasýný eve býrakýr.", inventory_items[item][itemName], strval(inputtext));
			SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

			
			return pc_cmd_envanter(playerid, "");
		}
	}

	else 
	{
		SendErrorMessage(playerid, "Oops .. Bir þeyler ters gitti, geliþtiriciye ulaþýn.");
		return pc_cmd_envanter(playerid, "");
	}
	
	return 1;
}

Dialog:InventoryOther(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new houseid = -1;

	if ((houseid = GetNearInsideHouse(playerid)) != -1 && houseid >= 0 && houseid < MAX_HOUSES && PlayerToPoint(1, playerid,HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY], HouseInfo[houseid][hCheckPosZ]))
	{
        if (!HouseInventory[houseid][listitem][pInvItem]) return 1;

        new item = HouseInventory[houseid][listitem][pInvItem];
		if (GivePlayerInvItem(playerid, item, HouseInventory[houseid][listitem][pInvQ], HouseInventory[houseid][listitem][pInvQFloat], HouseInventory[houseid][listitem][pInvEx], HouseInventory[houseid][listitem][pInvS], HouseInventory[houseid][listitem][pInvName]) == -1) 
			return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

        SendSyntaxMessage(playerid, "%s adlý eþyayý evden aldýn.", inventory_items[item][itemName]);
		
		HouseInventory[houseid][listitem][pInvName] = EOS;
		HouseInventory[houseid][listitem][pInvQFloat] = 0.0;
        HouseInventory[houseid][listitem][pInvItem] = 
		HouseInventory[houseid][listitem][pInvQ] =
		HouseInventory[houseid][listitem][pInvEx] =
		HouseInventory[houseid][listitem][pInvS] = 0;

		

		new mes[128];
		format(mes, sizeof(mes), "%s adlý eþyayý evden alýr.", inventory_items[item][itemName]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
		return 1;
	}
	
	new vehicle = GetPlayerVehicleID(playerid);

	if (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carOwnerID] == PlayerInfo[playerid][pID])
	{
	    if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])	
			return SendErrorMessage(playerid, "Bu aracýn torpido gözünü kullanamazsýn.");
        if (!CarInventory[vehicle][listitem][pInvItem])																
			return 1;

	    new item = CarInventory[vehicle][listitem][pInvItem];

		if (GivePlayerInvItem(playerid, item, CarInventory[vehicle][listitem][pInvQ], CarInventory[vehicle][listitem][pInvQFloat], CarInventory[vehicle][listitem][pInvEx], CarInventory[vehicle][listitem][pInvS], CarInventory[vehicle][listitem][pInvName]) == -1) 
			return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
		//if (IsValidDynamicObject(VehicleInfo[vehicle][carAttach][listitem])) DestroyDynamicObject(VehicleInfo[vehicle][carAttach][listitem]);

		CarInventory[vehicle][listitem][pInvName] = EOS;
		CarInventory[vehicle][listitem][pInvQFloat] = 0.0;
        CarInventory[vehicle][listitem][pInvItem] =
		CarInventory[vehicle][listitem][pInvS] =
		CarInventory[vehicle][listitem][pInvEx] =
		CarInventory[vehicle][listitem][pInvQ] = 0;
		
		

		new mes[128];
		format(mes, sizeof(mes), "%s adlý eþyayý %s model aracýn torpidosundan alýr.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	    return 1;
	}

	if ((vehicle = GetNearVehicle(playerid, 5.0)) != 0)
	{
		new item = TrunkInventory[vehicle][listitem][pInvItem];

	    if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))									return SendErrorMessage(playerid,"Bu aracýn bagajý bulunmuyor.");
		if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])																	return SendErrorMessage(playerid, "Bu aracýn bagajýný kullanamazsýn.");
		if (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction]) 								return SendErrorMessage(playerid, "Bagajýn yanýnda durmalýsýn. ");
		if (!IsPlayerInAnyVehicle(playerid) && !VehicleInfo[vehicle][carTrunkLock]) 																									return SendErrorMessage(playerid, "Bu aracýn bagajý kapalý.");
        if (!TrunkInventory[vehicle][listitem][pInvItem])																																return pc_cmd_envanter(playerid, "");
		if (GivePlayerInvItem(playerid, item, TrunkInventory[vehicle][listitem][pInvQ], TrunkInventory[vehicle][listitem][pInvQFloat], TrunkInventory[vehicle][listitem][pInvEx], TrunkInventory[vehicle][listitem][pInvS], TrunkInventory[vehicle][listitem][pInvName]) == -1) 
			return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
		if (IsValidDynamicObject(VehicleInfo[vehicle][carAttach][listitem])) 													
			DestroyDynamicObject(VehicleInfo[vehicle][carAttach][listitem]);

		TrunkInventory[vehicle][listitem][pInvName] = EOS;
		TrunkInventory[vehicle][listitem][pInvQFloat] = 0.0;
        TrunkInventory[vehicle][listitem][pInvItem] =
		TrunkInventory[vehicle][listitem][pInvS] =
		TrunkInventory[vehicle][listitem][pInvEx] =
		TrunkInventory[vehicle][listitem][pInvQ] = 0;

		new mes[128];
		format(mes, sizeof(mes), "%s adlý eþyayý %s model aracýn %s alýr.", inventory_items[item][itemName], VehicleNames[GetVehicleModel(vehicle)-400], (VehicleInfo[vehicle][carFaction])?("bagajýndan"):("bagajýndan"));
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	    return 1;
	}
	
	pc_cmd_envanter(playerid, "");
	return 1;
}

Dialog:DeleteItem(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_envanter(playerid, "");

    new slot = GetPVarInt(playerid, #inventory_choose);

	if (slot < 0 || slot > MAX_INV_SLOTS-1 || Inventory[playerid][slot][pInvItem] == 0)	return pc_cmd_envanter(playerid, "");
	if (Inventory[playerid][slot][pInvItem] == 21 && maskOn{playerid}) pc_cmd_maske(playerid, ""); 

/*	if (InfoSkate[playerid][sActive] == true)
	{
		InfoSkate[playerid][sActive] = false;
        DestroyDynamicObject(InfoSkate[playerid][sSkate]);
	}*/
	SM2(playerid, "%s adlý eþyayý envanterinizden sildiniz.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
	//SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "** (( %s %s adlý eþyayý envanterinden siler. ))", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);

	RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
	return 1;
}

Dialog:GiveItem(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_envanter(playerid, "");

    new slot = GetPVarInt(playerid, #inventory_choose);

	if (slot < 0 || slot > MAX_INV_SLOTS-1 || Inventory[playerid][slot][pInvItem] == 0)	return pc_cmd_envanter(playerid, "");

	new userid;

    if (sscanf(inputtext, "u", userid))	return Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "{FFFFFF}Eþyayý ver", "{ffffff}Eþyayý vermek istediðiniz kiþinin ID'sini giriniz:", ">>>", "Geri Dön");

    if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (playerid == userid)								return SendErrorMessage(playerid, "Kendine eþya veremezsin.");

	if (inventory_items[Inventory[playerid][slot][pInvItem]][itemSplit] == 0 || Inventory[playerid][slot][pInvQFloat] == 0.1)
	{
		switch(Inventory[playerid][slot][pInvItem])
		{
			case 22..34: // WEAPON
			{
				if (GiveInvItem(userid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQ], Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)
					return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

				new str[128];
				format(str, sizeof(str), "%s adlý silahý %s adlý kiþiye verir.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], GetNameWithMask(userid));
				SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

				SM1(userid, "%s sana %s adlý silahý verdi.", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
				SM1(playerid, "%s adlý kiþiye %s adlý silahý verdin.", GetNameWithMask(userid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
					
				RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
			}
			case INV_GANJA, INV_MED_GANJA, 103 .. 118: // ðåàãåíòû è òðàâà
			{
				if (GiveFloatInvItem(userid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQFloat]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu!");

				new str[128];
				format(str, sizeof(str), "%s adlý eþyayý %s adlý kiþiye verir.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], GetNameWithMask(userid));
				SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

				SM1(userid, "%s sana %s adlý eþyayý verdi (%.1fg).", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQFloat]);
				SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin (%.1fg).", GetNameWithMask(userid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQFloat]);
				
				RemoveFloatInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
			}
			case INV_DRUG: // íàðêîòèêè
			{
				if (GiveDrugInvItem(userid, Inventory[playerid][slot][pInvName], Inventory[playerid][slot][pInvQFloat], Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu!");

				new str[128];
				format(str, sizeof(str), "%s adlý uyuþturucuyu %s adlý kiþiye verir.", Inventory[playerid][slot][pInvName], GetNameWithMask(userid));
				SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

				SM1(userid, "%s sana %s adlý uyuþturucudan verdi (%.1fg).", GetNameWithMask(playerid), Inventory[playerid][slot][pInvName], Inventory[playerid][slot][pInvQFloat]);
				SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin (%.1fg).", GetNameWithMask(userid), Inventory[playerid][slot][pInvName], Inventory[playerid][slot][pInvQFloat]);
				
				RemoveFloatInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
			}
			default:
			{
				if (GiveInvItem(userid, Inventory[playerid][slot][pInvItem], Inventory[playerid][slot][pInvQ]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu!");

				new str[128];
				format(str, sizeof(str), "%s adlý kiþiye %s adlý eþyayý verir.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], GetNameWithMask(userid));
				SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

				SM1(userid, "%s sana %s adlý eþyayý verdi.", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
				SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin.", GetNameWithMask(userid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName]);
					
				RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], 0, slot);
			}
		}
	
	    return 1;
	}

	SetPVarInt(playerid, #give_item, userid);

	new mes[256];
	format(mes, sizeof(mes), "{ffffff}Eþya: %s (miktar: %i)\n\n%s adlý kiþiye vereceðiniz eþyanýn miktarýný giriniz:", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ], GetNameWithMask(userid));
	Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Eþya", mes, "Ver", "Ýptal");
	return 1;
}

Dialog:GiveQuantity(playerid, response, listitem, inputtext[])
{
	if (!response)									return pc_cmd_envanter(playerid, "");

	new slot = GetPVarInt(playerid, #inventory_choose),	userid = GetPVarInt(playerid, #give_item);
	
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);
    if (playerid == userid)								return SendErrorMessage(playerid, "Kendine eþya veremezsin.");

	if (slot < 0 || slot > MAX_INV_SLOTS-1 || Inventory[playerid][slot][pInvItem] == 0)	return pc_cmd_envanter(playerid, "");

	switch(Inventory[playerid][slot][pInvItem])
	{
		case 22..34: // WEAPON
		{
			return 1;
		}
		case INV_GANJA, INV_MED_GANJA, 103 .. 118: // ðåàãåíòû è òðàâà
		{
			format(inputtext, 5, "%.1f", floatstr(inputtext));
			new Float:amount = floatstr(inputtext);
	
			if (amount < 0.1 || Inventory[playerid][slot][pInvQFloat] < amount)
			{
				SendErrorMessage(playerid, "Yeterli eþyanýz yok. ");

				new mes[256];
				format(mes, sizeof(mes), "{ffffff}Eþya: %s (miktar: %i)\n\n%s adlý kiþiye vereceðiniz eþyanýn miktarýný giriniz:", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ], GetNameWithMask(userid));
				Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Eþya", mes, "Ver", "Ýptal");
				return 1;
			}

			if (GiveFloatInvItem(userid, Inventory[playerid][slot][pInvItem], amount) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu!");

			new str[128];
			format(str, sizeof(str), "%s adlý eþyayý %s adlý kiþiye verir.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], GetNameWithMask(userid));
			SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

			SM1(userid, "%s sana %s adlý eþyayý verdi (%.1fg).", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], amount);
			SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin (%.1fg).", GetNameWithMask(userid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], amount);
			
			new query[256];
			format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] conveyed %s (amount: %i) player %s [MYSQL: %i | IP: %s]",
			GetNameEx(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], amount, GetNameEx(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid));
			insert_log(query, ITEM_LOG, 3, PlayerInfo[playerid][pAccID], PlayerInfo[userid][pAccID]);

			RemoveFloatInvItem(playerid, Inventory[playerid][slot][pInvItem], amount, slot);
		}
		case INV_DRUG: // íàðêîòèêè
		{
			format(inputtext, 5, "%.1f", floatstr(inputtext));
			new Float:amount = floatstr(inputtext);

			if (amount < 0.1 || Inventory[playerid][slot][pInvQFloat] < amount)
			{
				SendErrorMessage(playerid, "Bu kadar miktara sahip deðilsin. ");

				new mes[256];
				format(mes, sizeof(mes), "{ffffff}Eþya: %s (miktar): %i)\n\nKiþiye vermek istediðiniz %s adlý eþya miktarýný girin:", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ], GetNameWithMask(userid));
				Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Eþya", mes, "Ver", "Ýptal");
				return 1;
			}
			
			if (GiveDrugInvItem(userid, Inventory[playerid][slot][pInvName], amount, Inventory[playerid][slot][pInvEx], Inventory[playerid][slot][pInvS]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu!");

			new str[128];
			format(str, sizeof(str), "%s adlý eþyayý %s adlý kiþiye verir.", Inventory[playerid][slot][pInvName], GetNameWithMask(userid));
			SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

			SM1(userid, "%s sana %s adlý eþyayý verdi (%.1fg).", GetNameWithMask(playerid), Inventory[playerid][slot][pInvName], amount);
			SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin (%.1fg).", GetNameWithMask(userid), Inventory[playerid][slot][pInvName], amount);
			
			new query[256];
			format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] conveyed %s [drug] (amount: %i / OAS: %i%%) player %s [MYSQL: %i | IP: %s]",
			GetNameEx(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), Inventory[playerid][slot][pInvName], amount, Inventory[playerid][slot][pInvEx], GetNameEx(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid));
			insert_log(query, ITEM_LOG, 3, PlayerInfo[playerid][pAccID], PlayerInfo[userid][pAccID]);

			RemoveFloatInvItem(playerid, Inventory[playerid][slot][pInvItem], amount, slot);
		}
		default: // 
		{
			new amount = strval(inputtext);

			if (amount < 1 || Inventory[playerid][slot][pInvQ] < amount)
			{
				SendErrorMessage(playerid, "Yeterli miktar bulunmuyor. ");

				new mes[256];
				format(mes, sizeof(mes), "{ffffff}Eþya: %s (miktar): %i)\n\nKiþiye vermek istediðiniz %s adlý eþya miktarýný girin:", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], Inventory[playerid][slot][pInvQ], GetNameWithMask(userid));
				Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Eþya", mes, "Ver", "Ýptal");
				return 1;
			}
		
			if (GiveInvItem(userid, Inventory[playerid][slot][pInvItem], amount) == -1)	return SendErrorMessage(playerid, "Kiþinin envanteri tamamen dolu.");
			new str[128];
			format(str, sizeof(str), "%s adlý eþyayý %s adlý kiþiye verdi.", inventory_items[Inventory[playerid][slot][pInvItem]][itemName], GetNameWithMask(userid));
			SetPlayerChatBubble(playerid, str, COLOR_PURPLE, 20.0, 4000);

			SM1(userid, "%s sana %s adlý eþyayý verdi [miktar: %i].", GetNameWithMask(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], strval(inputtext));
			SM1(playerid, "%s adlý kiþiye %s adlý eþyayý verdin [miktar: %i].", GetNameWithMask(userid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], strval(inputtext));
			
			new query[256];
			format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] conveyed %s (amount: %i) player %s [MYSQL: %i | IP: %s]",
			GetNameEx(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), inventory_items[Inventory[playerid][slot][pInvItem]][itemName], strval(inputtext), GetNameEx(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid));
			insert_log(query, ITEM_LOG, 3, PlayerInfo[playerid][pAccID], PlayerInfo[userid][pAccID]);

			RemoveInvItem(playerid, Inventory[playerid][slot][pInvItem], amount, slot);
		}
	}

	return 1;
}

Dialog:InventoryMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	
	switch(listitem)
	{
		case 0: return PrintInv(playerid);
		case 1:
		{
			new houseid;
			if ((houseid = GetNearHouse(playerid)) != -1 && HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID])
			{
				return PrintHouseInv(playerid, houseid);
			}

			new vehicle = GetNearVehicle(playerid, 4.0);
			if (vehicle != 0 && (!IsADontTrunk(vehicle) || !IsAPlane(vehicle) || !IsABiker(vehicle) || !IsAHelicopter(vehicle) || !IsABoat(vehicle) || !IsABicycle(vehicle)))
			{
				if ((VehicleInfo[vehicle][carTrunkLock] && !IsPlayerInAnyVehicle(playerid)) || (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]))
				{
					return PrintVehInv(playerid, vehicle);
				}
			}
			
			vehicle = GetPlayerVehicleID(playerid);
			if (IsPlayerInAnyVehicle(playerid) && vehicle != 0 && VehicleInfo[vehicle][carOwnerID] == PlayerInfo[playerid][pID])
			{
				return PrintGBInv(playerid, vehicle);
			}
		}
	}

	SendErrorMessage(playerid, "Bu kýsma eriþiminiz yok. Kod: 073");
	return 1;
}