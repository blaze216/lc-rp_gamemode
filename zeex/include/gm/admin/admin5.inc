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

		SendServerMessage(playerid, "Baþarýlý þekilde çöp %s oluþturuldu: [ID: %i]", (TrashData[id][TrashType] == TYPE_BIN) ? ("tenekesi"):("konteynýrý"), id);
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
