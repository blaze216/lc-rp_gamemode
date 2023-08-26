forward OnTruckCargoInsert(cargoid);
forward LoadDynamicTruckCargo();

public OnTruckCargoInsert(cargoid)
{
	TruckCargo[cargoid][tID] = cache_insert_id();
	return 1;
}

public LoadDynamicTruckCargo()
{
	new rows = cache_num_rows(), time = GetTickCount(), total, mes[128];

	if (!rows)
	{
	    print("[Truck Cargo] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", TruckCargo[i][tID]);
	    cache_get_value_int(i, "type", TruckCargo[i][tType]);
		cache_get_value(i, "name", TruckCargo[i][tName], 64);
		cache_get_value_int(i, "storage", TruckCargo[i][tStorage]);
	    cache_get_value_int(i, "storage_size", TruckCargo[i][tStorageSize]);
		cache_get_value_int(i, "price", TruckCargo[i][tPrice]);
		cache_get_value_int(i, "product_id", TruckCargo[i][tProductID]);
		cache_get_value_int(i, "product_amount", TruckCargo[i][tProductAmount]);
		cache_get_value_int(i, "pack", TruckCargo[i][tPack]);
		cache_get_value_int(i, "gps", TruckCargo[i][tGps]);
		cache_get_value_int(i, "locked", TruckCargo[i][tLocked]);
		cache_get_value_float(i, "x", TruckCargo[i][tPosX]);
		cache_get_value_float(i, "y", TruckCargo[i][tPosY]);
		cache_get_value_float(i, "z", TruckCargo[i][tPosZ]);
		TruckCargo[i][tResult] = 0;

		format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nStok: %i / %i\nFiyat: $%i / adet", truckcargo_product[TruckCargo[i][tProductID]], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize], TruckCargo[i][tPrice]);

		TruckCargo[i][tLabel] = CreateDynamic3DTextLabel(mes, 0xFFFFFFFF, TruckCargo[i][tPosX], TruckCargo[i][tPosY], TruckCargo[i][tPosZ]+0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 100.0);
		TruckCargo[i][tPickup] = CreateDynamicPickup(1318, 1, TruckCargo[i][tPosX], TruckCargo[i][tPosY], TruckCargo[i][tPosZ], 0, 0, -1, 100.0);
		TruckCargo[i][tOn] = 1;
        total++;
	}
	printf("[Truck Cargo] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

Show_Industry(playerid, id, gps = 0)
{
	new mes[1024], title[64 + 9], str_len;

	SetPVarInt(playerid, #select_industry, id);

	if (TruckCargo[id][tType] == 0)
	{
	    format(title, sizeof(title), "{9ACD32}%s", TruckCargo[id][tName]);
	    format(mes, sizeof(mes), "{9ACD32}%s {FFFFFF}adlý yere hoþ geldiniz!\n\n\
								{FFFFFF}Burasý þu anda {9ACD32}%s.\n\n\
								{9ACD32}Satýþ:\n\
								{808080}Ürün\t\t\tFiyat\t\tÜretim\t\tStok{FFFFFF}",
		TruckCargo[id][tName], (TruckCargo[id][tLocked] == 0)?("açýk"):("kapalý"));

        for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
			if (!TruckCargo[i][tOn] || (!TruckCargo[id][tPack] && id != i) || TruckCargo[i][tType] || TruckCargo[i][tPack] != TruckCargo[id][tPack]) continue;

            str_len = strlen(truckcargo_product[TruckCargo[i][tProductID]]);
            format(mes, sizeof(mes), "%s\n%s%s\t\t$%i\t\t%s%i {808080}Stok / saat baþý{FFFFFF}\t%i adet {808080}(%i){FFFFFF}", mes, truckcargo_product[TruckCargo[i][tProductID]], (str_len < 6 || TruckCargo[i][tProductID] == 15 || TruckCargo[i][tProductID] == 17 || TruckCargo[i][tProductID] == 10)?("\t"):(""), TruckCargo[i][tPrice], 
			(TruckCargo[i][tProductAmount] > 0) ? ("+") : (""), TruckCargo[i][tProductAmount], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize]);
	    }
	    strcat(mes, "\n\n{9ACD32}Bilgi:\n{808080}Bu iþletme depodur, mal almamaktadýr.");
	}

	else if (TruckCargo[id][tType] == 1 || TruckCargo[id][tType] == 3)
	{
	    format(title, sizeof(title), "{9ACD32}%s", TruckCargo[id][tName]);
	    format(mes, sizeof(mes), "{9ACD32}%s {FFFFFF}adlý yere hoþ geldiniz!\n\n\
								{FFFFFF}Burasý þu anda {9ACD32}%s.\n\n\
								{9ACD32}Satýþ:\n\
								{808080}Ürün\t\t\tFiyat\t\tÜretim\t\tStok{FFFFFF}",
		TruckCargo[id][tName], (TruckCargo[id][tLocked] == 0)?("açýk"):("kapalý"));

        for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
			if (!TruckCargo[i][tOn] || (!TruckCargo[id][tPack] && id != i) || TruckCargo[i][tType] != 1 || TruckCargo[i][tPack] != TruckCargo[id][tPack]) continue;

            str_len = strlen(truckcargo_product[TruckCargo[i][tProductID]]);
            format(mes, sizeof(mes), "%s\n%s%s\t\t$%i\t\t%s%i {808080}Stok / saat baþý{FFFFFF}\t%%i adet {808080}(%i){FFFFFF}", mes, truckcargo_product[TruckCargo[i][tProductID]], (str_len < 6 || TruckCargo[i][tProductID] == 15 || TruckCargo[i][tProductID] == 17 || TruckCargo[i][tProductID] == 10)?("\t"):(""), TruckCargo[i][tPrice],
			(TruckCargo[i][tProductAmount] > 0)?("+"):(""), TruckCargo[i][tProductAmount], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize]);
	    }
	    
	    strcat(mes, "\n\n{9ACD32}Gereken:\n{808080}Ürün\t\t\tFiyat\t\tStok durumu\t\tStok{FFFFFF}");
	    
	    for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
			if (!TruckCargo[i][tOn] || (!TruckCargo[id][tPack] && id != i) || TruckCargo[i][tType] != 3 || TruckCargo[i][tPack] != TruckCargo[id][tPack]) continue;

            str_len = strlen(truckcargo_product[TruckCargo[i][tProductID]]);
            format(mes, sizeof(mes), "%s\n%s%s\t\t$%i\t\t%s%i {808080}Stok / saat baþý{FFFFFF}\t%%i adet {808080}(%i){FFFFFF}", mes, truckcargo_product[TruckCargo[i][tProductID]], (str_len < 6 || TruckCargo[i][tProductID] == 15 || TruckCargo[i][tProductID] == 17 || TruckCargo[i][tProductID] == 10)?("\t"):(""), TruckCargo[i][tPrice],
		    (TruckCargo[i][tProductAmount] > 0)?("+"):(""), TruckCargo[i][tProductAmount], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize]);
	    }
	}
	
	else if (TruckCargo[id][tType] == 2)
	{
	    format(title, sizeof(title), "{9ACD32}Taþýmacýlýk - Gemi");
	    str_len = strlen(truckcargo_product[TruckCargo[id][tProductID]]);
	    format(mes, sizeof(mes), "{9ACD32}Gemi paneline{FFFFFF}hoþgeldin!\n\n\
									{FFFFFF}Gemi þu anda {9ACD32}%s{FFFFFF}.\n\n\
									{9ACD32}Gemi hakkýnda bilgi:{FFFFFF}\n\ 
									Gemi Varýþ Saati:\t\t\t\t%s\n\
									Gemi Kalkýþ Saati:\t\t\t\t%s\n\
									Sonraki Geliþ Saati:\t\t\t%s\n\
									{808080}* Yukarýda belirtilen zamanlar doðru olmayabilir.\n\n",
		(ship_docked == 1)?("demirlenmiþ"):("denize açýlmýþ"),
		get_date("%hh:%ii", ship_arrived), 
		get_date("%hh:%ii", ship_depart), 
		get_date("%hh:%ii", ship_next));

		format(mes, sizeof(mes), "%s{9ACD32}Satýþ:\n\
									{808080}Gemi hiçbir þey satmýyor, sadece getirilen kargolarý alýyor.\n\n{9ACD32}Arananlar:\n\
									{808080}Ürün\t\t\tFiyat\t\tStok{FFFFFF}", mes);

		for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
			if (!TruckCargo[i][tOn] || TruckCargo[i][tType] != 2) continue;

            str_len = strlen(truckcargo_product[TruckCargo[i][tProductID]]);
            format(mes, sizeof(mes), "%s\n%s%s\t\t$%i\t\t%i adet {808080}(%i){FFFFFF}", mes, truckcargo_product[TruckCargo[i][tProductID]], (str_len < 6 || TruckCargo[i][tProductID] == 15 || TruckCargo[i][tProductID] == 17 || TruckCargo[i][tProductID] == 10)?("\t"):(""), TruckCargo[i][tPrice], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize]);
	    }
	}

	if (gps == 1)	Dialog_Show(playerid, SelectIndustry, DIALOG_STYLE_MSGBOX, title, mes, ">>>", "Geri Dön");
	else			Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, title, mes, "Kapat", "");

	return 1;
}

CheckIndustries()
{
    static const str_storage[] = "[{FFFF00}%s{FFFFFF}]\nStok: %i / %i\nFiyat: $%i / adet";
	new mes[sizeof(str_storage) - 8 + 32 + 12 + 12];
    		
	new
		industires_prods[MAX_TRUCK_PACK char];
	
	for(new i; i != MAX_TRUCK_CARGO; i++)
	{
	    if (TruckCargo[i][tOn] == 0)
	        continue;
	        
		if (TruckCargo[i][tType] == 0)
		{
		    TruckCargo[i][tStorage] += TruckCargo[i][tProductAmount];
		    
		    if (TruckCargo[i][tStorage] > TruckCargo[i][tStorageSize])
		        TruckCargo[i][tStorage] = TruckCargo[i][tStorageSize];
		    
		    else if (TruckCargo[i][tStorage] < 0)
		        TruckCargo[i][tStorage] = 0;
		    
		    format(mes, sizeof(mes), str_storage, truckcargo_product[TruckCargo[i][tProductID]], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize], TruckCargo[i][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[i][tLabel], 0xFFFFFFFF, mes);
		}
		else if (TruckCargo[i][tType] == 3)
		{
			if (TruckCargo[i][tStorage] >= (-TruckCargo[i][tProductAmount]))
			{
		    	TruckCargo[i][tStorage] -= (-TruckCargo[i][tProductAmount]);
				industires_prods{TruckCargo[i][tPack]} += (-TruckCargo[i][tProductAmount]);
			}
			format(mes, sizeof(mes), str_storage, truckcargo_product[TruckCargo[i][tProductID]], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize], TruckCargo[i][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[i][tLabel], 0xFFFFFFFF, mes);
		}
	}
	
	for(new i; i != MAX_TRUCK_CARGO; i++)
	{
	    if (TruckCargo[i][tOn] == 0 || TruckCargo[i][tType] != 1 || TruckCargo[i][tPack] == 0 || TruckCargo[i][tStorage] >= TruckCargo[i][tStorageSize])
	        continue;
			
		if (industires_prods{TruckCargo[i][tPack]} >= TruckCargo[i][tProductAmount])
			TruckCargo[i][tStorage] += TruckCargo[i][tProductAmount];
        
        if (TruckCargo[i][tStorage] > TruckCargo[i][tStorageSize])
        	TruckCargo[i][tStorage] = TruckCargo[i][tStorageSize];
        
        format(mes, sizeof(mes), str_storage, truckcargo_product[TruckCargo[i][tProductID]], TruckCargo[i][tStorage], TruckCargo[i][tStorageSize], TruckCargo[i][tPrice]);
       	UpdateDynamic3DTextLabelText(TruckCargo[i][tLabel], 0xFFFFFFFF, mes);
	}
	return 1;
}

TruckRank1(mv)
{
	return (mv == 600 || mv == 605 || mv == 543 || mv == 422 || mv == 478 || mv == 554) ? (1):(0);
}

TruckRank2(mv)
{
	return (TruckRank1(mv) == 1 || mv == 413 || mv == 459 || mv == 482) ? (1):(0);
}

TruckRank3(mv)
{
	return (TruckRank1(mv) == 1 || TruckRank2(mv) == 1 || mv == 440 || mv == 498) ? (1):(0);
}

TruckRank4(mv)
{
	return (TruckRank1(mv) == 1 || TruckRank2(mv) == 1 || TruckRank3(mv) == 1 || mv == 499 || mv == 414 || mv == 578 || mv == 443 || mv == 428) ? (1):(0);
}

TruckRank5(mv)
{
	return (TruckRank1(mv) == 1 || TruckRank2(mv) == 1 || TruckRank3(mv) == 1 || TruckRank4(mv) == 1 || mv == 456 || mv == 455) ? (1):(0);
}

TruckRank6(mv)
{
	return (TruckRank1(mv) == 1 || TruckRank2(mv) == 1 || TruckRank3(mv) == 1 || TruckRank4(mv) == 1 || TruckRank5(mv) == 1 || mv == 584 || mv == 591 || mv == 435 || mv == 450) ? (1):(0);
}

IsTruckerJob(vehicle)
{
    new mv = GetVehicleModel(vehicle);
	return (TruckRank6(mv) == 0)?(0):(1);
}

ValidTruckForPlayer(playerid, vehicle)
{
	new mv = GetVehicleModel(vehicle);
	switch(PlayerInfo[playerid][pCareer])
	{
	    case 0..11: if (TruckRank1(mv) == 0) return 0;
		case 12..23: if (TruckRank2(mv) == 0) return 0;
	    case 24..31: if (TruckRank3(mv) == 0) return 0;
	    case 32..47: if (TruckRank4(mv) == 0) return 0;
	    case 48..58: if (TruckRank5(mv) == 0) return 0;
	    default: if (TruckRank6(mv) == 0) return 0;
	}
	return 1;
}

GetMaxCargoVehicle(vehicle)
{
	switch(GetVehicleModel(vehicle))
	{
	    case 600, 543, 605, 443: return 2;
	    case 422: return 3;
	    case 478: return 4;
		case 554: return 6;
		case 413, 459, 482: return 10;
	    case 440, 498: return 12;
	    case 499: return 14;
	    case 414, 455, 428: return 16;
	    case 578: return 18;
		case 456: return 24;
		case 450: return 30;
		case 435, 591: return 36;
		case 584: return 40;
	}
	return 0;
}

IsValidProductVehicle(vehicle, prod)
{
	switch(GetVehicleModel(vehicle))
	{
	    case 600, 543, 605, 422, 478, 413, 459, 482, 440, 498:
		{
			switch(prod)
			{
			    case 1, 2, 3, 5, 6, 7, 12, 15, 18, 19, 20, 23, 24: return 1;
			}
		}
		
		case 554, 499, 414, 456, 435, 591:
		{
			switch(prod)
			{
			    case 1, 2, 3, 5, 6, 7, 12, 15, 18, 19, 20, 23, 24, TRUCKER_BRICKS: return 1;
			}
		}
		
        case 584:
		{
			switch(prod)
			{
			    case 0, 8, 11, 19: return 1;
			}
		}

		case 450, 455:
        {
			switch(prod)
			{
			    case 9, 10, 13, 16, TRUCKER_SCRAP: return 1;
			}
		}

		case 578:
		{
			switch(prod)
			{
			    case TRUCKER_WOODS, TRUCKER_BRICKS: return 1;
			}
		}
		case 443:
		{
			switch(prod)
			{
			    case 4: return 1;
			}
		}
		case 428:
		{
			switch(prod)
			{
			    case 14, 21: return 1;
			}
		}
	}
	return 0;
}

IsTakeProduct(prod)
{
	switch(prod)
	{
	    case TRUCKER_FUEL, TRUCKER_CARS, TRUCKER_MILK, TRUCKER_CEREAL, TRUCKER_COTTON, TRUCKER_DYES, TRUCKER_MALT, TRUCKER_AGGREGATE, TRUCKER_WOODS, TRUCKER_SCRAP, TRUCKER_BRICKS: return 0;
	}
	return 1;
}


NullPagesVar(playerid)
{
	DeletePVar(playerid, "Trucker:BizLastNext");
	DeletePVar(playerid, "Trucker:BizLastPrev");
	return 1;
}

ShowBizMenuPDA(playerid, list = 0, page_type = PAGE_NEXT)
{
	new mes[1024] = "{9ACD32}Ürün\t{9ACD32}Fiyat / adet\t{9ACD32}Ýþletme\n";

	new bnext = GetPVarInt(playerid, "Trucker:BizLastNext"), bprev = GetPVarInt(playerid, "Trucker:BizLastPrev"), count = 0, id;

	if (list < 0 || list > 30) list = 0;

	if (list) strcat(mes, "{9ACD32}[Geri]\n");

	for(new i; i < MAX_TRUCK_PRODUCT; i++) pTemp[playerid][pCargoListed][i] = -1;

	if (page_type == PAGE_NEXT)
	{
		for(new i = bnext; i < MAX_BIZ; i++)
		{
			id = biz_prod_types[BizInfo[i][bizType]];

			if (!BizInfo[i][bizID] || id == -1 || BizInfo[i][bizProduct] >= 400) continue;
			
			format(mes, sizeof(mes), "%s\n%s\t$%i\t%s", mes, truckcargo_product[id], BizInfo[i][bizBuyPrice], BizInfo[i][bizName]);
			pTemp[playerid][pCargoListed][count+1] = i;
			count++;

			if (count + 1 == 11) 
			{
				if (!list)
				{
					SetPVarInt(playerid, "Trucker:BizLastNext", i + 1);
				}
				else
				{
					SetPVarInt(playerid, "Trucker:BizLastPrev", bnext);
					SetPVarInt(playerid, "Trucker:BizLastNext", i + 1);	
				}
				break;
			}
		}
	}
	else if (page_type == PAGE_PREV)
	{
		for(new i = bprev; i > 0; i--)
		{
			id = biz_prod_types[BizInfo[i][bizType]];

			if (!BizInfo[i][bizID] || id == -1 || BizInfo[i][bizProduct] >= 400) continue;

			format(mes, sizeof(mes), "%s\n%s\t$%i\t%s", mes, truckcargo_product[id], BizInfo[i][bizBuyPrice], BizInfo[i][bizName]);
			pTemp[playerid][pCargoListed][count+1] = i;
			count++;

			if (count == 1)
			{
				SetPVarInt(playerid, "Trucker:BizLastNext", i + 1);
			}

			if (count + 1 == 11)
			{
				SetPVarInt(playerid, "Trucker:BizLastPrev", i - 1);
				break;
			}
		}
	}

	if (count == 0) return SendErrorMessage(playerid, "Aktif sipariþ bulunmuyor!");
	if (count == 10) strcat(mes, "\n{9ACD32}[Ýleri]");
	
	Dialog_Show(playerid, PDABiz, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Taþýmacýlýk - Ýþletme", mes, "GPS", "Geri Dön");
	SetPVarInt(playerid, #pda_list, list);
	return 1;
} 

TruckCargo_Nearest(playerid, Float: radius = 10.0)
{
	for(new i; i != MAX_TRUCK_CARGO; i++)
	{
	    if (TruckCargo[i][tOn] == 0)	continue;

        if (IsPlayerInRangeOfPoint(playerid, radius, TruckCargo[i][tPosX], TruckCargo[i][tPosY], TruckCargo[i][tPosZ]) && 0 == GetInterior(playerid) && 0 == GetWorld(playerid)) return i;
	}
	return -1;
}

IsPlayerNearCargo(playerid)
{
	new id = -1;

	for(new i; i != MAX_CARGO_OBJ; i++)
	{
		if (CargoObject[i][oOn] == 0 || !IsPlayerInRangeOfPoint(playerid, 2.0, CargoObject[i][oX], CargoObject[i][oY], CargoObject[i][oZ]) || GetWorld(playerid) != CargoObject[i][oVW] || CargoObject[i][oInt] != GetInterior(playerid)) continue;
		return i;
	}

	return id;
}

GetAvailableTruck(playerid, vehicle)
{
	switch(PlayerInfo[playerid][pCareer])
	{
		case 0..11: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 543: return true;
				case 413: return true;
				default: return false;
			}
		}
		case 12..23: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 413: return true;
				case 459: return true;
				case 482: return true;
				case 543: return true;
				default: return false;
			}
		}
		case 24..31: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 413: return true;
				case 459: return true;
				case 482: return true;
				case 440: return true;
				case 609: return true;
				case 498: return true;
				case 543: return true;
				default: return false;
			}
		}
		case 32..47: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 413: return true;
				case 459: return true;
				case 482: return true;
				case 440: return true;
				case 609: return true;
				case 498: return true;
				case 499: return true;
				case 414: return true;
				case 578: return true;
				case 514: return true;
				case 428: return true;
				case 543: return true;
				default: return false;
			}
		}
		case 48..58: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 413: return true;
				case 459: return true;
				case 482: return true;
				case 440: return true;
				case 609: return true;
				case 498: return true;
				case 499: return true;
				case 414: return true;
				case 578: return true;
				case 514: return true;
				case 428: return true;
				case 456: return true;
				case 455: return true;
				case 543: return true;
				default: return false;
			}
		}
		default: {
			switch(vehicle) {
				case 600: return true;
				case 605: return true;
				case 422: return true;
				case 478: return true;
				case 554: return true;
				case 413: return true;
				case 459: return true;
				case 482: return true;
				case 440: return true;
				case 609: return true;
				case 498: return true;
				case 499: return true;
				case 414: return true;
				case 578: return true;
				case 514: return true;
				case 428: return true;
				case 456: return true;
				case 455: return true;
				case 543: return true;
				default: return false;
			}
		}
	}
	return 0;
}

/*
SendTruckerRequest(playerid, bizid)
{
    foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !TaxiDuty[i] || PlayerInfo[i][pJob] != JOB_TAXI) continue;

        SendClientMessage(i, COLOR_GREEN, "|___________Çâîíîê â òàêñè___________|");
		if (pTemp[playerid][pPayphone] == -1) 
			SendClientMessageEx(i, COLOR_WHITE, "Call from: %s Ph: %i", GetNameEx(playerid), PlayerInfo[playerid][pNumber]);
		else
			SendClientMessageEx(i, COLOR_WHITE, "Call from: Òàêñîôîí, Ph: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
		SendClientMessageEx(i, COLOR_WHITE, "Ìåñòîïîëîæåíèå: %s", location);
		SendClientMessageEx(i, COLOR_WHITE, "*taxi accept %i ÷òîáû ïðèíÿòü âûçîâ **", playerid);
	}
	return 1;
}*/

/*// 0..11
Picador 	600
Sadler		605
Bobcat		422
Walton		478
Yosemite	554
//2
Pony		413
topfun van  459
Burrito		482
// 3
Rumpo		440
Boxville	609/498
// 4
Benson		499
Mule		414
DFT-30		578
Tanker		514
Securicar	428
//5 and 6
Yankee		456
Flatbed		455*/