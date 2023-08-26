CMD:atrash(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/atrash [create / remove / edit / goto]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new type;

		if (sscanf(secoption, "i", type))    return SendHelpMessage(playerid, "/atrash create [1 - çöp tenekesi | 2 - çöp konteynýrý]");
		if (type < 1 || type > 2)		    return SendErrorMessage(playerid, "Tip 1 veya 2 olmalýdýr.");

        if (GetPlayerInterior(playerid) != 0 ||
            GetPlayerVirtualWorld(playerid) != 0) return SendErrorMessage(playerid, "Dünyanýz 0 olmalýdýr.");

        new id = Trash_CheckFreeSlot();
		if (id == -1) return SendErrorMessage(playerid, "Maksimum çöp kutusu sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ]);
		TrashData[id][TrashX] += 0.5;

        TrashData[id][TrashType] = (type == 1) ? (TYPE_BIN) : (TYPE_DUMPSTER);
       	TrashData[id][TrashLevel] = (TrashData[id][TrashType] == TYPE_BIN) ? 1 : 2;

		new label[64];
        format(label, sizeof(label), "%s", (TrashData[id][TrashType] == TYPE_BIN) ? ("Çöp Tenekesi") : ("Çöp Konteynýrý"));
		TrashData[id][TrashLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ]+1.25, 15.0, .testlos = 1);
        
        new trashModel = (TrashData[id][TrashType] == TYPE_DUMPSTER) ? 1344 : 1328;
        TrashData[id][TrashObject] = CreateDynamicObject(trashModel, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], 0.0, 0.0, TrashData[id][TrashRZ], 0, 0);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `trashes` (type,x,y,z,rz) VALUES (%i,%f,%f,%f,%f)", 
            TrashData[id][TrashType],
            TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], TrashData[id][TrashRZ]
        );
		mysql_tquery(dbHandle, query, "OnTrashInsert", "d", id);

        SetPVarInt(playerid, #edit_trash, id + 1);
		EditDynamicObject(playerid, TrashData[id][TrashObject]);

		SendServerMessage(playerid, "Baþarýlý þekilde çöp %s oluþturuldu: [ID: %i].", (TrashData[id][TrashType] == TYPE_BIN) ? ("tenekesi"):("konteynýrý"), id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;
		
		if (sscanf(secoption, "i", id))						        return SendHelpMessage(playerid, "/atrash remove [ID]");
		if (id < 0 || id >= MAX_TRASHES || !TrashData[id][TrashID])	return SendErrorMessage(playerid, "Çöp Tenekesi/Konteynýrý bulunamadý.");

		if (IsValidDynamicObject(TrashData[id][TrashObject]))
		{
			DestroyDynamicObject(TrashData[id][TrashObject]);
			TrashData[id][TrashObject] = INVALID_OBJECT_ID;
		}
        
        if (IsValidDynamic3DTextLabel(TrashData[id][TrashLabel]))
		{
			DestroyDynamic3DTextLabel(TrashData[id][TrashLabel]);
			TrashData[id][TrashLabel] = Text3D:INVALID_3DTEXT_ID;
		}

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `trashes` WHERE `id` = %i", TrashData[id][TrashID]);
		mysql_tquery(dbHandle, query);

		TrashData[id][TrashID] = 0;
		SendServerMessage(playerid, "Çöp tenekesi/konteynýrý kaldýrýldý: [ID: %i]", id);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id;

		if (sscanf(secoption, "d", id))						        return SendHelpMessage(playerid, "/atrash edit [ID]");
		if (id < 0 || id > MAX_TRASHES || !TrashData[id][TrashID])	return SendErrorMessage(playerid, "Çöp Tenekesi/Konteynýrý bulunamadý.");
		if (Trash_Nearest(playerid) != id)						    return SendErrorMessage(playerid, "Yakýnýnýzda çöp tenekesi/konteynýrý bulunmuyor.");

		SetPVarInt(playerid, #edit_trash, id + 1);
		EditDynamicObject(playerid, TrashData[id][TrashObject]);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))						        return SendHelpMessage(playerid, "/atrash goto [ID]");
		if (id < 0 || id > MAX_TRASHES || !TrashData[id][TrashID])	return SendErrorMessage(playerid, "Çöp Tenekesi/Konteynýrý bulunamadý.");

		SetPlayerPosEx(playerid, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ]);
		SetWorld(playerid, 0);
		SetInterior(playerid, 0);
		return 1;
	}
	
	else
	{
		SendHelpMessage(playerid, "/atrash [create / remove / edit / goto]");
	}
	return 1;
}

CMD:serverinfo(playerid, params[])
{
	new developer[64];
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))	return SendNotAdmin(playerid);
	format(developer, sizeof(developer), "~r~~h~%i~g~~h~ 0~b~~h~~h~~h~ 65535", GetServerTickRate());
	TextDrawSetString(Developer, developer); 
	TextDrawShowForPlayer(playerid, Developer);
	return 1;
}

alias:saveall("saveserver");
CMD:saveall(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);

	for(new i; i < MAX_BIZ; i++) Save_Business(i);
	for(new i; i < MAX_HOUSES; i++) Save_House(i);
	for(new i; i < MAX_VEHICLES; i++) Save_Car(i);
	for(new i; i < MAX_PLAYERS; i++) Save_User(i);
	for(new i; i < MAX_APART; i++) Save_Apart(i);

	SaveServer();

	SendServerMessage(playerid, "Tüm sunucu verileri kaydedildi.");
	return 1;
}

CMD:afactory(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/afactory [create / remove / goto]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new name[32];

		if (sscanf(secoption, "S()[32]", name))     return SendHelpMessage(playerid, "/afactory create [isim]");
		if (strlen(name) < 4 || strlen(name) > 32)	return SendErrorMessage(playerid, "Belirtilen isim minimum 4, maksimum 32 karakter olmalýdýr.");

        if (GetPlayerInterior(playerid) != 0 ||
            GetPlayerVirtualWorld(playerid) != 0) return SendErrorMessage(playerid, "Dünyanýz 0 olmalýdýr.");

        new id = Factory_CheckFreeSlot();
		if (id == -1) return SendErrorMessage(playerid, "Maksimum geri dönüþüm tesisi sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, FactoryData[id][FactoryX], FactoryData[id][FactoryY], FactoryData[id][FactoryZ]);
		format(FactoryData[id][FactoryName], 32, "%s", name);

		new label[128];
        format(label, sizeof(label), "Geri Dönüþüm Tesisi - %s\n\n{FFFFFF}Geri Dönüþtürülmüþ Atýk Miktarý: {F39C12}0", FactoryData[id][FactoryName]);
		FactoryData[id][FactoryLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, FactoryData[id][FactoryX], FactoryData[id][FactoryY], FactoryData[id][FactoryZ] + 0.5, 15.0, .testlos = 1);
		//FactoryData[id][FactoryCP] = CreateDynamicCP(FactoryData[id][FactoryX], FactoryData[id][FactoryY], FactoryData[id][FactoryZ], 6.0);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `factories` (name,x,y,z) VALUES ('%e',%f,%f,%f)", 
            FactoryData[id][FactoryName],
            FactoryData[id][FactoryX], FactoryData[id][FactoryY], FactoryData[id][FactoryZ]
        );
		mysql_tquery(dbHandle, query, "OnFactoryInsert", "d", id);

		SendServerMessage(playerid, "Geri dönüþüm tesisi oluþturdunuz: %s [ID: %i]", FactoryData[id][FactoryName], id);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new id;
		
		if (sscanf(secoption, "i", id))						                return SendHelpMessage(playerid, "/afactory remove [ID]");
		if (id < 0 || id >= MAX_FACTORIES || !FactoryData[id][FactoryID])	return SendErrorMessage(playerid, "Geçersiz ID.");

		if (IsValidDynamicCP(FactoryData[id][FactoryCP]))
		{
			DestroyDynamicCP(FactoryData[id][FactoryCP]);
			FactoryData[id][FactoryCP] = INVALID_OBJECT_ID;
		}
        
        if (IsValidDynamic3DTextLabel(FactoryData[id][FactoryLabel]))
		{
			DestroyDynamic3DTextLabel(FactoryData[id][FactoryLabel]);
			FactoryData[id][FactoryLabel] = Text3D:INVALID_3DTEXT_ID;
		}

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `factories` WHERE `id` = %i", TrashData[id][TrashID]);
		mysql_tquery(dbHandle, query);

        FactoryData[id][FactoryCurrent] = 0;
        FactoryData[id][FactoryID] = 0;
		
        SendServerMessage(playerid, "Geri dönüþüm tesisi silindi: [ID: %i]", id);
		return 1;
	}

	else if (CompareStrings(option, "goto"))
	{
		new id;

		if (sscanf(secoption, "i", id))						                return SendHelpMessage(playerid, "/afactory goto [ID]");
		if (id < 0 || id >= MAX_FACTORIES || !FactoryData[id][FactoryID])	return SendErrorMessage(playerid, "Geçersiz ID.");

		SetPlayerPosEx(playerid, FactoryData[id][FactoryX], FactoryData[id][FactoryY], FactoryData[id][FactoryZ]);
		SetWorld(playerid, 0);
		SetInterior(playerid, 0);
		return 1;
	}
	
	else
	{
		SendHelpMessage(playerid, "/afactory [create / remove / goto]");
	}
	return 1;
}

CMD:aindustry(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))	return SendNotAdmin(playerid);

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/aindustry [create / remove / edit / goto / list]");
		return 1;
	}

	if (CompareStrings(option, "create"))
	{
		new type, name[64];

		if (sscanf(secoption, "is[64]", type, name)) return SendHelpMessage(playerid, "/aindustry create [0 - Hammadde | 1 - Üretim | 2 - Gemi | 3 - Üretim Gereksinimi] [Endüstri Ýsmi]");
		if (type < 0 || type > 3)					 return SendErrorMessage(playerid, "Taþýmacýlýk tipi 0 ile 3 arasýnda olmalýdýr.");
		if (strlen(name) < 4 || strlen(name) > 63)	 return SendErrorMessage(playerid, "Taþýmacýlýk ismi minimum 4, maksimum 63 karakter olmalýdýr.");
		
		new cargoid = -1;

		for(new i = 0; i < MAX_TRUCK_CARGO; i++)
		{
			if (TruckCargo[i][tOn]) continue;

			cargoid = i;
			break;
		}

		if (cargoid == -1) return SendErrorMessage(playerid, "Maksimum taþýmacýlýk sayýsýna ulaþýldý.");

		GetPlayerPos(playerid, TruckCargo[cargoid][tPosX], TruckCargo[cargoid][tPosY], TruckCargo[cargoid][tPosZ]);

		TruckCargo[cargoid][tType] = type;
		TruckCargo[cargoid][tStorageSize] = 200;
		TruckCargo[cargoid][tProductID] =
		TruckCargo[cargoid][tProductAmount] = 
		TruckCargo[cargoid][tPrice] = 
		TruckCargo[cargoid][tStorage] = 
		TruckCargo[cargoid][tPack] = 
		TruckCargo[cargoid][tGps] =
		TruckCargo[cargoid][tLocked] = 0;
		format(TruckCargo[cargoid][tName], 64, "%s", name);

		new mes[128];

		format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\n%i/%i\nFiyat: $%i/miktar.", truckcargo_product[TruckCargo[cargoid][tProductID]], TruckCargo[cargoid][tStorage], TruckCargo[cargoid][tStorageSize], TruckCargo[cargoid][tPrice]);
		TruckCargo[cargoid][tLabel] = CreateDynamic3DTextLabel(mes, 0xFFFFFFFF, TruckCargo[cargoid][tPosX], TruckCargo[cargoid][tPosY], TruckCargo[cargoid][tPosZ]+0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 100.0);
		TruckCargo[cargoid][tPickup] = CreateDynamicPickup(1318, 1, TruckCargo[cargoid][tPosX], TruckCargo[cargoid][tPosY], TruckCargo[cargoid][tPosZ], 0, 0, -1, 100.0);
		TruckCargo[cargoid][tOn] = 1;

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `truck_cargo` (x, y, z, type, name, storage_size) VALUES (%f, %f, %f, %i, '%e', 200)", TruckCargo[cargoid][tPosX], TruckCargo[cargoid][tPosY], TruckCargo[cargoid][tPosZ], 
		type, name);
		mysql_tquery(dbHandle, query, "OnTruckCargoInsert", "d", cargoid);

		SendServerMessage(playerid, "Bir taþýmacýlýk oluþturdunuz: [Ýsim: %s | ID: %i | Tip: %s]", TruckCargo[cargoid][tName], cargoid, TruckCargo[cargoid][tPack]);
		return 1;
	}

	else if (CompareStrings(option, "remove"))
	{
		new cargoid, query[256];

		if (sscanf(secoption, "i", cargoid))										return SendHelpMessage(playerid, "/aindustry remove [ID]");
		if (cargoid < 0 || cargoid >= MAX_TRUCK_CARGO || !TruckCargo[cargoid][tOn])	return SendErrorMessage(playerid, "Belirtilen þirket bulunamadý.");

		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `truck_cargo` WHERE `id` = %i", TruckCargo[cargoid][tID]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamic3DTextLabel(TruckCargo[cargoid][tLabel]))
		{
			DestroyDynamic3DTextLabel(TruckCargo[cargoid][tLabel]);
			TruckCargo[cargoid][tLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		if (IsValidDynamicPickup(TruckCargo[cargoid][tPickup]))	DestroyDynamicPickup(TruckCargo[cargoid][tPickup]);

		TruckCargo[cargoid][tOn] = 
		TruckCargo[cargoid][tID] = 0;
		SendServerMessage(playerid, "Taþýmacýlýk silindi: [ID: %i]", cargoid);
		return 1;
	}

	else if (CompareStrings(option, "edit"))
	{
		new id, parameters[16], arg[112];

		if (sscanf(secoption, "is[12]S()[112]", id, parameters, arg))
		{
			SendHelpMessage(playerid, "/aindustry edit [ID] [storage / size / price / unit / group / locked / gps]");
			return 1;
		}

		if (id < 0 || id >= MAX_TRUCK_CARGO || !TruckCargo[id][tOn])	return SendErrorMessage(playerid, "Belirtilen þirket bulunamadý.");

		new mes[128];

		if (CompareStrings(parameters, "storage"))
		{
			new storage;

			if (sscanf(arg, "i", storage))								return SendHelpMessage(playerid, "/aindustry edit [ID] storage [stok limiti] ");
			if (storage < 0 || storage > TruckCargo[id][tStorageSize])	return SendErrorMessage(playerid, "Stok limiti 0 ile %i arasýnda olmalýdýr.", TruckCargo[id][tStorageSize]);

			TruckCargo[id][tStorage] = storage;
			SQL_SetInteger("truck_cargo", "storage", TruckCargo[id][tStorage], TruckCargo[id][tID]);
			format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nDepo %i/%i\nFiyat $%i/miktar.", truckcargo_product[TruckCargo[id][tProductID]], TruckCargo[id][tStorage], TruckCargo[id][tStorageSize], TruckCargo[id][tPrice]);
			UpdateDynamic3DTextLabelText(TruckCargo[id][tLabel], 0xFFFFFFFF, mes);
			SendServerMessage(playerid, "Belirtilen iþletmenin stok durumu güncellendi: [ID: %i] | Yeni: %i.", id, TruckCargo[id][tStorage]);
			return 1;
		}

		else if (CompareStrings(parameters, "locked"))
		{
			new locked;

			if (sscanf(arg, "i", locked))	return SendHelpMessage(playerid, "/aindustry edit [ID] locked [0 - açýk | 1 - kapalý] ");
			if (locked < 0 || locked > 1)	return SendErrorMessage (playerid, "Deðer 0 veya 1 olmalýdýr.");

			TruckCargo[id][tLocked] = locked;
			SQL_SetInteger("truck_cargo", "locked", TruckCargo[id][tLocked], TruckCargo[id][tID]);
			SendServerMessage(playerid, "Taþýmacýlýk durumu deðiþtirildi: %s [ID: %i].", (!locked) ? ("açýk") : ("kapalý"), id);
			return 1;
		}

		else if (CompareStrings(parameters, "type"))
		{
			new type;

			if (sscanf(arg, "i", type))	return SendHelpMessage(playerid, "/aindustry edit [ID] type [0 - Hammadde | 1 - Üretim | 2 - Gemi | 3 - Üretim Gereksinimi]");
			if (type < 0 || type > 3)	return SendErrorMessage(playerid, "Tip 0 ile 3 arasýnda olmalýdýr.");

			TruckCargo[id][tType] = type;
			SQL_SetInteger("truck_cargo", "type", TruckCargo[id][tType], TruckCargo[id][tID]);
			SendServerMessage(playerid, "Taþýmacýlýk tipi deðiþtirildi: [ID: %i] | Yeni Tip: %i.", id, type);
			return 1;
		}
		
		else if (CompareStrings(parameters, "gps"))
		{
			new locked;

			if (sscanf(arg, "i", locked))	return SendHelpMessage(playerid, "/aindustry edit [ID] gps [0 - gizli / 1 - görünür]");
			if (locked < 0 || locked > 1)	return SendErrorMessage(playerid, "Deðer 0 veya 1 olmalýdýr.");

			TruckCargo[id][tGps] = locked;
			SQL_SetInteger("truck_cargo", "gps", TruckCargo[id][tGps], TruckCargo[id][tID]);
			SendServerMessage(playerid, "Taþýmacýlýk GPS görünürlüðü deðiþtirildi: %s [ID: %i]", (!locked) ? ("Görünür") : ("Gizli"), id);
			return 1;
		}

		else if (CompareStrings(parameters, "size"))
		{
			new size;

			if (sscanf(arg, "i", size))		return SendHelpMessage(playerid, "/aindustry edit [ID] size [büyüklük]");
			if (size <= 0 || size > 10000)	return SendErrorMessage(playerid, "Büyüklük 1 ile 10000 arasýnda bir deðer olmalýdýr.");

			TruckCargo[id][tStorageSize] = size;
			SQL_SetInteger("truck_cargo", "storage_size", TruckCargo[id][tStorageSize], TruckCargo[id][tID]);
			format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nDepo %i/%i\nFiyat $%i/miktar.", truckcargo_product[TruckCargo[id][tProductID]], TruckCargo[id][tStorage], TruckCargo[id][tStorageSize], TruckCargo[id][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[id][tLabel], 0xFFFFFFFF, mes);
			SendServerMessage(playerid, "Deponun boyutunu deðiþtirdiniz: [ID: %i] | Yeni Deðer: %i.", id, TruckCargo[id][tStorageSize]);
			return 1;
		}

		else if (CompareStrings(parameters, "price"))
		{
			new price;

			if (sscanf(arg, "i", price))		return SendHelpMessage(playerid, "/aindustry edit [ID] price [fiyat]");
			if (price < 1 || price > 10000)	return SendErrorMessage(playerid, "Fiyat $1 ile $10000 arasýnda olmalýdýr.");
			
			TruckCargo[id][tPrice] = price;
			SQL_SetInteger("truck_cargo", "price", TruckCargo[id][tPrice], TruckCargo[id][tID]);
			format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nDepo %i/%i\nFiyat $%i/miktar.", truckcargo_product[TruckCargo[id][tProductID]], TruckCargo[id][tStorage], TruckCargo[id][tStorageSize], TruckCargo[id][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[id][tLabel], 0xFFFFFFFF, mes);
			SendServerMessage(playerid, "Deponun birim fiyatýný deðiþtirdiniz: [ID: %i] | Yeni Deðer: $%i.", id, TruckCargo[id][tPrice]);
			return 1;
		}

		else if (CompareStrings(parameters, "unit"))
		{
			new unit;

			if (sscanf(arg, "i", unit))		return SendHelpMessage(playerid, "/aindustry edit [ID] unit [saat baþýna birim]");
			if (unit < -100 || unit > 100)	return SendErrorMessage(playerid, "Birim deðeri -100 ile 100 arasýnda olmalýdýr.");

			TruckCargo[id][tProductAmount] = unit;
			SQL_SetInteger("truck_cargo", "product_amount", TruckCargo[id][tProductAmount], TruckCargo[id][tID]);
			format(mes, sizeof(mes), "[{FFFF00}%s{FFFFFF}]\nDepo %i/%i\nFiyat $%i/miktar.", truckcargo_product[TruckCargo[id][tProductID]], TruckCargo[id][tStorage], TruckCargo[id][tStorageSize], TruckCargo[id][tPrice]);
        	UpdateDynamic3DTextLabelText(TruckCargo[id][tLabel], 0xFFFFFFFF, mes);
			SendServerMessage(playerid, "Depodaki saat baþýna mal ilave durumun deðiþtirdiniz: [ID: %i] | Yeni Deðer: %i", id, TruckCargo[id][tProductAmount]);
			return 1;
		}

		else if (CompareStrings(parameters, "group"))
		{
			new pack;

			if (sscanf(arg, "i", pack))	
			{
				SendHelpMessage(playerid, "/aindustry edit [ID] group [grup]");
				SendServerMessage(playerid, "Mevcut taþýmacýlýk grubu: %i.", TruckCargo[id][tPack]);
				return 1;
			}	//î
			if (pack < 0 || pack > MAX_TRUCK_PACK)	return SendErrorMessage(playerid, "Taþýmacýlýk grubu 0 ile %i arasýnda bir deðer olmalýdýr.", MAX_TRUCK_PACK);

			TruckCargo[id][tPack] = pack;
			SQL_SetInteger("truck_cargo", "pack", TruckCargo[id][tPack], TruckCargo[id][tID]);
			SendServerMessage(playerid, "Taþýmacýlýk grubu deðiþtirildi: [ID: %i] | Yeni Deðer: %i.", id, TruckCargo[id][tPack]);
			return 1;
		}
		
		else 
		{
			SendHelpMessage(playerid, "/aindustry edit [ID] [storage / size / price / unit / group / locked / gps]");
			return 1;
		}
	}
	
	else if (CompareStrings(option, "goto"))
	{
		new cargoid;

		if (sscanf(secoption, "i", cargoid))										return SendHelpMessage(playerid, "/aindustry goto [ID]");
		if (cargoid < 0 || cargoid >= MAX_TRUCK_CARGO || !TruckCargo[cargoid][tOn])	return SendErrorMessage(playerid, "Endüstri bulunamadý.");

		SetPlayerPosEx(playerid, TruckCargo[cargoid][tPosX], TruckCargo[cargoid][tPosY], TruckCargo[cargoid][tPosZ]);
		SetInterior(playerid, 0);
		SetWorld(playerid, 0);
		SendServerMessage(playerid, "Belirtilen yere ýþýnlandýnýz: %s [ID: %i].", TruckCargo[cargoid][tName], cargoid);
		return 1;
	}

	else if (CompareStrings(option, "list"))
	{
		pTemp[playerid][pDialogList] = 0;
		DisplayCargoGroups(playerid);
	}
	return 1;
}

CMD:payday(playerid, params[])
{
	new userid;
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
	if (sscanf(params, "u", userid))		return SendHelpMessage(playerid, "/payday [ID/Karakter Adý]");
	if (userid == INVALID_PLAYER_ID)		return SendErrorMessage(playerid, "Belirtilen oyuncu bulunamadý.");
	
	PayDay(userid);
	
	SendServerMessage(userid, "Yönetici size payday verdi.");
	SendServerMessage(playerid, "%s adlý oyuncuya payday verdiniz.", GetNameEx(userid));
	return 1;
}

CMD:paydayall(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);

	for(new i = 0; i < MAX_PLAYERS; i++)
		PayDay(i);

	SendAdmMessageToAll("%s adlý yönetici tüm aktif oyunculara payday verdi.", GetAccName(playerid));
	return 1;
}

CMD:testmsgs(playerid, params[]) 
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);

	new type, str[64];
	if (sscanf(params, "is[64]", type, str))		return SendHelpMessage(playerid, "/testmsgs [tip] [yazý]");
	if (type < 0 || type > 1)					return 1;

	switch(type)
	{
		case 0: JobMessage(playerid, str, 10);
		case 1: InfoMSG(playerid, str, 10);
	}
	
	return 1;
}

///////////////////////////////////
CMD:server(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);

	new opt[19], str[64];

	if(sscanf(params, "s[19]S()[64]", opt, str))
	{
		SendHelpMessage(playerid, "/server [seçenek]");
		SM1(playerid, "isim, url, dil, harita, versiyon, bakim, hava, paydayfiyati, parkfiyati, 2xpayday");
		SM1(playerid, "galerisatisyuzdesi, minimummaas, maksimummaas, spawnbolgesi, mekansistemesatisyuzdesi");
		SM1(playerid, "taksilisansucret, taksireklamucret, arackayityuzdesi, arachaftalik, suruculisansucreti");

		return 1;
	}

	if(!strcmp(opt, "isim", true))
	{
		new name[64];

		if(sscanf(str, "s[64]", name))
			return SendHelpMessage(playerid, "/server <isim> [sunucu ismi]");

		format(ServerInfo[sHostName], sizeof(ServerInfo[sHostName]), name);	
		SaveServer();

		SendRconCommand(sprintf("hostname %s%s", (ServerInfo[sMaintenance]) ? ("[BAKIM] ") : (""), name));
	
		SendAdmMessage("%s, sunucu adýný \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), name);
	}

	else if(!strcmp(opt, "url", true))
	{
		new url[64];

		if(sscanf(str, "s[64]", url))
			return SendHelpMessage(playerid, "/server <url> [site url]");

		format(ServerInfo[sWebUrl], sizeof(ServerInfo[sWebUrl]), url);
		SaveServer();

		SendRconCommand(sprintf("weburl %s", url));

		SendAdmMessage("%s, sunucu urlsini \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), url);
	}

	else if(!strcmp(opt, "dil", true))
	{
		new language[32];

		if(sscanf(str, "s[32]", language))
			return SendHelpMessage(playerid, "/server <dil> [sunucu dili]");
		
		format(ServerInfo[sLanguage], sizeof(ServerInfo[sLanguage]), language);
		SaveServer();

		SendRconCommand(sprintf("language %s", language));

		SendAdmMessage("%s, sunucu dilini \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), language);
	}

	else if(!strcmp(opt, "harita", true))
	{
		new map[32];

		if(sscanf(str, "s[32]", map))
			return SendHelpMessage(playerid, "/server <harita> [sunucu haritasý]");
		
		format(ServerInfo[sMap], sizeof(ServerInfo[sMap]), map);
		SaveServer();

		SendRconCommand(sprintf("mapname %s", map));

		SendAdmMessage("%s, sunucu haritasýný \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), map);
	}

	else if(!strcmp(opt, "versiyon", true))
	{
		new version[32];

		if(sscanf(str, "s[32]", version))
			return SendHelpMessage(playerid, "/server <versiyon> [sunucu versiyonu]");
		
		format(ServerInfo[sVersion], sizeof(ServerInfo[sVersion]), version);
		SaveServer();

		SetGameModeText(version);

		SendAdmMessage("%s, sunucu versiyonunu \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), version);
	}

	else if(!strcmp(opt, "bakim", true))
	{
		switch(ServerInfo[sMaintenance])
		{
			case false:
			{
				new password[64];

				if(sscanf(str, "s[64]", password))
					return SendHelpMessage(playerid, "/server <bakim> [bakým modu þifresi]");
				
				if(!strcmp(password, "0", true))
					return SendErrorMessage(playerid, "Geçersiz þifre girdiniz.");

				ServerInfo[sMaintenance] = true;
				format(ServerInfo[sPassword], sizeof(ServerInfo[sPassword]), password);
				
				SaveServer();

				SendRconCommand(sprintf("hostname [BAKIM] %s", ServerInfo[sHostName]));
				SendRconCommand(sprintf("password %s", password));

				SendAdmMessage("%s, sunucu bakým modu þifresini \"%s\" olarak deðiþtirdi.", GetNameEx(playerid), password);
				
			}

			case true:
			{
				ServerInfo[sMaintenance] = false;
				format(ServerInfo[sPassword], sizeof(ServerInfo[sPassword]), "0");

				SaveServer();

				SendRconCommand(sprintf("hostname %s", ServerInfo[sHostName]));
				SendRconCommand("password 0");

				SendAdmMessage("%s, sunucuyu bakým modundan çýkarttý.", GetNameEx(playerid));
			}
		}
	}

	else if(!strcmp(opt, "2xpayday", true))
	{
		switch(ServerInfo[sDoublePayday])
		{
			case false:
			{
				ServerInfo[sDoublePayday] = true;
				
				SaveServer();

				SendRconCommand(sprintf("hostname [2x PayDay] %s", ServerInfo[sHostName]));
			
	            new mes[128];
	            format(mes, sizeof(mes), "[Duyuru] Çift maaþ(2x PayDay) aktif edildi.");
	            SCMALL(0xF97804FF,mes);					
			}

			case true:
			{
				ServerInfo[sDoublePayday] = false;

                SaveServer();

				SendRconCommand(sprintf("hostname %s", ServerInfo[sHostName]));

	            new mes[128];
	            format(mes, sizeof(mes), "[Duyuru] Çift maaþ(2x PayDay) pasife çekildi.");
	            SCMALL(0xF97804FF,mes);		
			}
		}
	}

	else if(!strcmp(opt, "hava", true))
	{
		new weather;

		if(sscanf(str, "d", weather))
			return SendHelpMessage(playerid, "/server <hava> [hava numarasý]");

		pc_cmd_weatherall(playerid, sprintf("%d", weather));
	}

	else if(!strcmp(opt, "paydayfiyati", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <paydayfiyati> [fiyat]");

		if(price < 1 || price > 5000)
			return SendErrorMessage(playerid, "Geçersiz payday fiyatý girdiniz.");
		
		SendAdmMessage("%s, paydayi $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[sPricePayday]);

		ServerInfo[sPricePayday] = price;
		SaveServer();
	}

	else if(!strcmp(opt, "parkfiyati", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <parkfiyati> [fiyat]");

		if(price < 1 || price > 1000)
			return SendErrorMessage(playerid, "Geçersiz payday fiyatý girdiniz.");
		
		SendAdmMessage("%s, park fiyatýný $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[sPricePark]);

		ServerInfo[sPricePark] = price;
		SaveServer();
	}

	else if(!strcmp(opt, "galerisatisyuzdesi", true))
	{
		new Float:percent;

		if(sscanf(str, "f", percent))
			return SendHelpMessage(playerid, "/server <galerisatisyuzdesi> [yüzde]");

		if(percent < 1.0 || percent > 100.0)
			return SendErrorMessage(playerid, "Geçersiz galeri satýþ yüzdesi girdiniz.");
		
		SendAdmMessage("%s, galeri satýþ yüzdesini %.2f olarak deðiþtirdi. (eski: %.2f)", GetNameEx(playerid), percent, ServerInfo[sDealershipPercent]);

		ServerInfo[sDealershipPercent] = percent;
		SaveServer();
	}

	else if(!strcmp(opt, "minimummaas", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <minimummaas> [fiyat]");

		if(price < 1 || price > 2500)
			return SendErrorMessage(playerid, "Geçersiz minimum maaþ fiyatý girdiniz.");
		
		SendAdmMessage("%s, mekanlar için minimum maaþý $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[lMinSalary]);

		ServerInfo[lMinSalary] = price;
		SaveServer();
	}

	else if(!strcmp(opt, "maksimummaas", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <maksimummaas> [fiyat]");

		if(price < 1 || price > 2500)
			return SendErrorMessage(playerid, "Geçersiz maksimum maaþ fiyatý girdiniz.");
		
		SendAdmMessage("%s, mekanlar için maksimum maaþý $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[lMaxSalary]);

		ServerInfo[lMaxSalary] = price;
		SaveServer();
	}

	else if(!strcmp(opt, "spawnbolgesi", true))
	{
		ServerInfo[sSpawnInterior] = GetPlayerInterior(playerid);
		ServerInfo[sSpawnWorld] = GetPlayerVirtualWorld(playerid);
	
		GetPlayerPos(playerid, ServerInfo[sSpawnX], ServerInfo[sSpawnY], ServerInfo[sSpawnZ]);
		GetPlayerFacingAngle(playerid, ServerInfo[sSpawnA]);

		SendAdmMessage("%s, sunucunun spawn bölgesini deðiþtirdi.", GetNameEx(playerid));
	}

	else if(!strcmp(opt, "mekansistemesatisyuzdesi", true))
	{
		new Float:percent;

		if(sscanf(str, "f", percent))
			return SendHelpMessage(playerid, "/server <mekansistemesatisyuzdesi> [yüzde]");

		if(percent < 1.0 || percent > 100.0)
			return SendErrorMessage(playerid, "Geçersiz mekan sisteme satýþ yüzdesi girdiniz.");
		
		SendAdmMessage("%s, mekan sisteme satýþ yüzdesini %.2f olarak deðiþtirdi. (eski: %.2f)", GetNameEx(playerid), percent, ServerInfo[sLocaleSalePercent]);

		ServerInfo[sLocaleSalePercent] = percent;
		SaveServer();
	}

	else if(!strcmp(opt, "taksilisansucret", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <taksilisansucret> [ücret]");

		if(price < 0)
			return SendErrorMessage(playerid, "Geçersiz ücret girdiniz.");
		
		SendAdmMessage("%s, taksi lisans ücretini $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price);

		ServerInfo[sPriceTaxiLicense] = price;
	}

	else if(!strcmp(opt, "taksireklamucret", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <taksireklamucret> [ücret]");

		if(price < 0)
			return SendErrorMessage(playerid, "Geçersiz ücret girdiniz.");

		SendAdmMessage("%s, taksi reklam ücretini $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[sPriceTaxiAd]);

		ServerInfo[sPriceTaxiAd] = price;
	}

	else if(!strcmp(opt, "arackayityuzdesi", true))
	{
		new Float:percent;

		if(sscanf(str, "f", percent))
			return SendHelpMessage(playerid, "/server <arackayityuzdesi> [yüzde deðeri]");
		
		if(percent < 1)
			return SendErrorMessage(playerid, "Geçersiz yüzde deðeri girdiniz.");
		
		SendAdmMessage("%s, araç kayýt ücretinin yüzdesini aracýn %.2f deðeri olarak deðiþtirdi. (eski: %.2f)", GetNameEx(playerid), percent, ServerInfo[sPriceVehRegisterPercent]);

		ServerInfo[sPriceVehRegisterPercent] = percent;
	}

	else if(!strcmp(opt, "arachaftalikvergi", true))
	{
		new Float:percent;

		if(sscanf(str, "f", percent))
			return SendHelpMessage(playerid, "/server <arachaftalikvergi> [yüzde deðeri]");
		
		if(percent < 1)
			return SendErrorMessage(playerid, "Geçersiz yüzde deðeri girdiniz.");
		
		SendAdmMessage("%s, araç haftalýk vergi yüzdesini %.2f deðeri olarak deðiþtirdi. (eski: %.2f)", GetNameEx(playerid), percent, ServerInfo[sPriceVehWeeklyTaxPercent]);

		ServerInfo[sPriceVehWeeklyTaxPercent] = percent;
	}

	else if(!strcmp(opt, "suruculisansucreti", true))
	{
		new price;

		if(sscanf(str, "d", price))
			return SendHelpMessage(playerid, "/server <suruculisansucreti> [ücret]");
		
		if(price < 1)
			return SendErrorMessage(playerid, "Geçersiz ücret girdiniz.");
		
		SendAdmMessage("%s, sürücü lisans ücretini $%d olarak deðiþtirdi. (eski: $%d)", GetNameEx(playerid), price, ServerInfo[sPriceDriverLicense]);

		ServerInfo[sPriceDriverLicense] = price;
	}

	else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

	return 1;
}

CMD:createskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new model_id, gender, race, price;

    if(sscanf(params, "dddd", model_id, gender, race, price))
        return SendHelpMessage(playerid, "/createskin [model id] [cinsiyet (1: Erkek, 2: Kadýn)] [ten rengi (1: Beyaz, 2: Siyah)] [fiyat]");

    if(model_id < 1 || model_id == 74)
        return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

    if(gender != GENDER_MALE && gender != GENDER_FEMALE)
        return SendErrorMessage(playerid, "Geçersiz cinsiyet girdiniz.");

    if(price < 1)
        return SendErrorMessage(playerid, "Geçersiz fiyat girdiniz.");

    mysql_tquery(dbHandle, GetSkin("game_skins.id", "", "", 1, -1, -1, model_id, gender, race), "OnStaffCreateSkin", "ddddd", playerid, model_id, gender, race, price);

    return 1;
}

CMD:deleteskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new model_id;

    if(sscanf(params, "d", model_id))
        return SendHelpMessage(playerid, "/deleteskin [model id]");

    if(model_id < 1 || model_id == 74)
        return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

    mysql_tquery(dbHandle, GetSkin("game_skins.id, game_skins.gender, game_skins.race", "", "", 1, -1, -1, model_id), "OnStaffDeleteSkin", "dd", playerid, model_id);

    return 1;
}

CMD:editskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new skin_id, opt[12], str[32];

    if(sscanf(params, "ds[12]S()[32]", skin_id, opt, str))
    {
        SendHelpMessage(playerid, "/editskin [skin veritabaný numarasý] [seçenek]");
        SM1(playerid, "cinsiyet, ten, fiyat");
        return 1;
    }

    if(skin_id < 1)
        return SendErrorMessage(playerid, "Geçersiz skin numarasý girdiniz.");

    if(!strcmp(opt, "cinsiyet", true))
    {
        new gender;

        if(sscanf(str, "d", gender))
            return SendHelpMessage(playerid, "/editskin <skin veritabaný numarasý> <cinsiyet> [cinsiyet (1: Erkek, 2: Kadýn)]");

        if(gender != GENDER_MALE && gender != GENDER_FEMALE)
            return SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

        mysql_tquery(dbHandle, EditSkin(skin_id, -1, gender), "OnStaffEditSkinGender", "ddd", playerid, skin_id, gender);
    }

    else if(!strcmp(opt, "ten", true))
    {
        new race;

        if(sscanf(str, "d", race))
            return SendHelpMessage(playerid, "/editskin <skin veritabaný numarasý> <ten> [ten (1: Beyaz, 2: Siyah)]");
    
        if(race != RACE_WHITE && race != RACE_BLACK && race != 3)
            return SendErrorMessage(playerid, "Geçersiz ten rengi girdiniz.");
    
        mysql_tquery(dbHandle, EditSkin(skin_id, -1, -1, race), "OnStaffEditSkinRace", "ddd", playerid, skin_id, race);
    }

    else if(!strcmp(opt, "fiyat", true))
    {
        new price;

        if(sscanf(str, "d", price))
            return SendHelpMessage(playerid, "/editskin <skin veritabaný numarasý> <fiyat> [fiyat]");

        if(price < 1)
            return SendErrorMessage(playerid, "Geçersiz fiyat girdiniz.");

        mysql_tquery(dbHandle, EditSkin(skin_id, -1, -1, -1, price), "OnStaffEditSkinPrice", "ddd", playerid, skin_id, price);
    }

    else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

    return 1;
}

CMD:listskins(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))		return SendNotAdmin(playerid);
    new opt[9], str[32];

    if(sscanf(params, "s[9]S()[32]", opt, str))
    {
        SendHelpMessage(playerid, "/listskins [seçenek]");
        SM1(playerid, "hepsi, cinsiyet, ten");
        return 1;
    }

    if(!strcmp(opt, "hepsi", true))
    {
        mysql_tquery(dbHandle, GetSkin("game_skins.model_id, game_skins.id, game_skins.gender, game_skins.race"), "OnStaffListSkins", "d", playerid);   
    }

    else if(!strcmp(opt, "cinsiyet", true))
    {
        new gender;

        if(sscanf(str, "d", gender))
            return SendHelpMessage(playerid, "/listskins <cinsiyet> [cinsiyet (1: Erkek, 2: Kadýn)]");

        if(gender != GENDER_MALE && gender != GENDER_FEMALE)
            return SendErrorMessage(playerid, "Geçersiz cinsiyet girdiniz.");

        mysql_tquery(dbHandle, GetSkin("game_skins.model_id, game_skins.id, game_skins.gender, game_skins.race", "", "", 1, -1, -1, -1, gender), "OnStaffListSkins", "d", playerid);
    }

    else if(!strcmp(opt, "ten", true))
    {
        new race;

        if(sscanf(str, "d", race))
            return SendHelpMessage(playerid, "/listskins <ten> [ten (1: Beyaz, 2: Siyahi)]");

        if(race != RACE_WHITE && race != RACE_BLACK)
            return SendErrorMessage(playerid, "Geçersiz ten girdiniz.");

        mysql_tquery(dbHandle, GetSkin("game_skins.model_id, game_skins.id, game_skins.gender, game_skins.race", "", "", 1, -1, -1, -1, -1, race), "OnStaffListSkins", "d", playerid);
    }

    else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

    return 1;
}

////////////////////////////////////////

CMD:createfactionskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new faction_id, model_id;

    if(sscanf(params, "dd", faction_id, model_id))
        return SendHelpMessage(playerid, "/createfactionskin [birlik id] [model id]");

    if(faction_id < 1)
        return SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");

    if(model_id < 1 || model_id == 74)
        return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

    mysql_tquery(dbHandle, EditFactionSkin(0, faction_id, model_id), "OnStaffCreateFactionSkin", "ddd", playerid, faction_id, model_id);

    return 1;
}
CMD:deletefactionskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new faction_id, model_id;

    if(sscanf(params, "dd", faction_id, model_id))
        return SendHelpMessage(playerid, "/deletefactionskin [birlik id] [model id]");

    if(faction_id < 1)
        return SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");

    if(model_id < 1 || model_id == 74)
        return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

    mysql_tquery(dbHandle, sprintf("DELETE FROM faction_skins WHERE faction_id = '%d' AND model_id = '%d'", faction_id, model_id), "OnStaffDeleteFactionSkin", "ddd", playerid, faction_id, model_id);

    return 1;
}

CMD:editfactionskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
    new skin_id, opt[7], str[32];

    if(sscanf(params, "ds[7]S()[32]", skin_id, opt, str))
    {
        SendHelpMessage(playerid, "/editfactionskin [skin veritabaný id] [seçenek]");
        SM1(playerid, "birlik, model");
        return 1;
    }

    if(skin_id < 1)
        return SendErrorMessage(playerid, "Geçersiz skin veritabaný numarasý girdiniz. (/listfactionskins)");

    if(!strcmp(opt, "birlik", true))
    {
        new faction_id;

        if(sscanf(str, "d", faction_id))
            return SendHelpMessage(playerid, "/editfactionskin <skin veritabaný id> <birlik> [birlik id]");
    
        if(faction_id < 1)
            return SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");
    
        mysql_tquery(dbHandle, EditFactionSkin(skin_id, faction_id), "OnStaffEditFactionSkinFaction", "ddd", playerid, skin_id, faction_id);
    }

    else if(!strcmp(opt, "model", true))
    {
        new model_id;

        if(sscanf(str, "d", model_id))
            return SendHelpMessage(playerid, "/editfactionskin <skin veritabaný id> <model> [model id]");

        if(model_id < 1 || model_id == 74)
            return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

        mysql_tquery(dbHandle, EditFactionSkin(skin_id, -1, model_id), "OnStaffEditFactionSkinModel", "ddd", playerid, skin_id, model_id);
    }

    else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

    return 1;
}

CMD:listfactionskins(playerid, params[])
{
    new opt[7], str[32];
	if (!CheckAdmin(playerid, ADMIN_LEVEL_1))		return SendNotAdmin(playerid);

    if(sscanf(params, "s[7]S()[32]", opt, str))
    {
        SendHelpMessage(playerid, "/listfactionskins [seçenek]");
        SM1(playerid, "hepsi, birlik, model");
        return 1;
    }

    if(!strcmp(opt, "hepsi", true))
    {
        mysql_tquery(dbHandle, GetFactionSkin("faction_skins.id, faction_skins.faction_id, faction_skins.model_id"), "OnStaffListFactionSkins", "d", playerid);
    }

    else if(!strcmp(opt, "birlik", true))
    {
        new faction_id;

        if(sscanf(str, "d", faction_id))
            return SendHelpMessage(playerid, "/listfactionskins <birlik> [birlik id]");

        if(faction_id < 1)
            return SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");

        mysql_tquery(dbHandle, GetFactionSkin("faction_skins.id, faction_skins.faction_id, faction_skins.model_id", "", "", 1, -1, -1, faction_id), "OnStaffListFactionSkins", "d", playerid);
    }

    else if(!strcmp(opt, "model", true))
    {
        new model_id;

        if(sscanf(str, "d", model_id))
            return SendHelpMessage(playerid, "/listfactionskins <model> [model id]");

        if(model_id < 1 || model_id == 74)
            return SendErrorMessage(playerid, "Geçersiz model numarasý girdiniz.");

        mysql_tquery(dbHandle, GetFactionSkin("faction_skins.id, faction_skins.faction_id, faction_skins.model_id", "", "", 1, -1, -1, -1, model_id), "OnStaffListFactionSkins", "d", playerid);
    }

    else SendErrorMessage(playerid, "Geçersiz seçenek girdiniz.");

    return 1;
}

CMD:addskin(playerid, params[])
{
	if (!CheckAdmin(playerid, DEVELOPER_LEVEL))		return SendNotAdmin(playerid);
	new skinID, baseID;

	if(sscanf(params, "dd", skinID, baseID))
		return SendSyntaxMessage(playerid, "/addskin [skin id] [kemik id]");

	new txd[32 + 4], dff[32 + 4];

	format(txd, sizeof txd, "ozel_model/%s.txd", valstrEx(skinID));
	format(dff, sizeof dff, "ozel_model/%s.dff", valstrEx(skinID));

	if(AddCharModel(baseID, skinID, dff, txd))
	{
		g_ModelsAwaiting += 1;
		SendServerMessage(playerid, "%d ID'li skin eklendi ve kemik ID'si %d olarak belirlendi.", skinID, baseID);
		SendServerMessage(playerid, "Kemik ID'sini yanlýþ girmek gibi bir salaklýk yaptýysanýz eðer skini baþka bir ID'ye yükleyin.");
		mysql_tquery(dbHandle, sprintf("INSERT INTO ozel_modeller (baseid, newid) VALUES (%d, %d)", baseID, skinID));
	}
	else SendErrorMessage(playerid, "Dosya adýnda .txd ve .dff kullanmadýðýndan ve bu dosyalarýn yüklü olduðundan emin ol.");

	return 1;
}

alias:givemoneyall("herkeseparaver");
CMD:givemoneyall(playerid, params[])
{
	new amount, count;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params, "i", amount))	return SendHelpMessage(playerid, "/givemoneyall [miktar]");
	if (amount > 50000000)			return SendErrorMessage(playerid, "Miktar $-55555550 ile $50000000 arasýnda olmalýdýr.");
	
	new mes[128];
	format(mes, sizeof(mes), "[/givemoneyall] %s adlý yönetici herkese para verdi: $%i.", GetAccName(playerid), amount);
	insert_log(mes, ADMIN_LOG, 8, -1, PlayerInfo[playerid][pAccID]);

	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerLoggedIn(i))
			continue;

	    GiveCash(i, amount);
		count++;
	}
	SAMALL("%s adlý yönetici bir sürpriz yaparak %d kiþiye %d$ para verdi.", GetAccName(playerid), count, amount);
	return 1;
}

CMD:kickall(playerid, params[])
{
	new reason[32];
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params, "s[32]", reason)) return SendSyntaxMessage(playerid, "/kickall [Sebep]");
	if(strlen(reason) > 32) return SendErrorMessage(playerid, "32 karakterden fazla giremezsin.");

	//if (pTemp[userid][pInvulnerable] != 0.0)	return SendErrorMessage(playerid, "Tekrar deneyin!");

	new count;

	foreach(new i : Player)
	{
		if(PlayerInfo[i][pAdmin] != 0) continue;

		KickLine(i, sprintf("%s sebebiyle oyundan atýldýnýz.", reason));
		count++;
	}
	SAMALL("%s adlý yönetici %s sebebi ile herkesi oyundan attý.", GetAccName(playerid), reason);
	SendAdmMessage("%s adlý yönetici %i kiþiyi oyundan attý. (/kickall)", GetAccName(playerid), count);

	return 1;
}

CMD:ozeltassaklikomut(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1337) return SendNotAdmin(playerid);
    new vehicleid, derece;

    if (sscanf(params, "dd", vehicleid, derece))
        return SendSyntaxMessage(playerid, "/ozeltassaklikomut [Araç ID] [derece]");

    if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
        return SendErrorMessage(playerid, "Geçersiz araç ID'si belirttin.");

    SetVehicleZAngle(vehicleid, derece);
    return 1;
}