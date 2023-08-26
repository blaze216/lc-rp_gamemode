CMD:aracaksesuar(playerid, params[])
{
	new option[24], secoption, thirdoption, fourthoption;

	if (sscanf(params, "s[24]D(-1)D(-1)D(-1)", option, secoption, thirdoption, fourthoption))
	{
		SendHelpMessage(playerid, "/aracaksesuar [ayarlar]");
		SendSyntaxMessage(playerid, "liste / satinal / sat / duzenle");
		return 1;
	}

    new vehicle = GetNearVehicle(playerid, 5.0);

    if (vehicle && IsDriver(playerid))								return SendErrorMessage(playerid, "Bu iþlem için araçtan inmelisin.");
    if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu aracýn sahibi deðilsiniz.");
			
	if (CompareStrings(option, "satinal"))
	{
		new slot, mes[sizeof(car_attach)*64];

		if (sscanf(params, "{s[7]}d", slot))				return SendHelpMessage(playerid, "/aracaksesuar satinal [slot ID]");
        if (VehicleInfo[vehicle][carAttachObj][slot] != 0)	return SendErrorMessage(playerid, "Belirtilen slot kullanýlýyor.");
            
        SetPVarInt(playerid, #veh_editor, vehicle);
		SetPVarInt(playerid, #veh_slot, slot);

		for(new i = 0; i < sizeof(car_attach); i++)
		{
			format(mes, sizeof(mes), "%s%i(0.0, 0.0, 90.0, 1.0)\t~g~~h~$250\n", mes, car_attach[i]);
		}

		Dialog_Show(playerid, MODEL_SELECTION_OBJATT, DIALOG_STYLE_PREVIEW_MODEL, "Araç Eklenti Listesi", mes, "Sec", "Kapat");		
		return 1;
	}

	else if (CompareStrings(option, "sat"))
	{
		new slot;

		if (sscanf(params, "{s[7]}d", slot))							return SendHelpMessage(playerid, "/aracaksesuar sat [slot ID]");
        if (VehicleInfo[vehicle][carAttach][slot] == INVALID_OBJECT_ID)	return SendErrorMessage(playerid, "Belirtilen slot boþ.");
            
        VehicleInfo[vehicle][carAttachObj][slot] = 0;
		VehicleInfo[vehicle][carAttachPosX][slot] = 0.0;
		VehicleInfo[vehicle][carAttachPosY][slot] = 0.0;
		VehicleInfo[vehicle][carAttachPosZ][slot] = 0.0;
		VehicleInfo[vehicle][carAttachRotX][slot] = 0.0;
		VehicleInfo[vehicle][carAttachRotY][slot] = 0.0;
		VehicleInfo[vehicle][carAttachRotZ][slot] = 0.0;
        DestroyDynamicObject(VehicleInfo[vehicle][carAttach][slot]);
		VehicleInfo[vehicle][carAttach][slot] = INVALID_OBJECT_ID;
        SendSyntaxMessage(playerid, "Öðeyi baþarýyla sildiniz.");
		Save_CarAttach(vehicle, slot);
		return 1;
	}

	else if (CompareStrings(option, "duzenle"))
	{
		new slot;

		if (sscanf(params, "{s[7]}d", slot))							return SendHelpMessage(playerid, "/aracaksesuar duzenle [slot ID]");
        if (VehicleInfo[vehicle][carAttach][slot] == INVALID_OBJECT_ID)	return SendErrorMessage(playerid, "Belirtilen slot boþ.");

		new Float:x, Float:y, Float:z;
		AntiCheatGetVehiclePos(vehicle, x, y, z);

		SetPVarInt(playerid, #veh_editor, vehicle);
		SetPVarInt(playerid, #veh_slot, slot);
		SetPVarInt(playerid, #veh_obj, VehicleInfo[vehicle][carAttachObj][slot]);
		SetPVarInt(playerid, "Vehicle:AttEdit", 1);
		
		DestroyDynamicObject(VehicleInfo[vehicle][carAttach][slot]);
		VehicleInfo[vehicle][carAttach][slot] = INVALID_OBJECT_ID;
		VehicleInfo[vehicle][carAttach][slot] = CreateDynamicObject(VehicleInfo[vehicle][carAttachObj][slot], x, y, z + 2.0, 0.0, 0.0, 0.0);
		EditDynamicObject(playerid, VehicleInfo[vehicle][carAttach][slot]);
		return 1;
	}

	else if (CompareStrings(option, "liste"))
	{
		new message[1024] = "{FFFFFF}Slot\t{FFFFFF}Obje ID";

		for(new i = 0; i < MAX_TRUNK_INVENTORY; i++)
		{
			if (VehicleInfo[vehicle][carAttach][i] == INVALID_OBJECT_ID)
			{
				format(message, sizeof(message), "%s\n%i\tHayýr", message, i);
			}
			else
			{
				format(message, sizeof(message), "%s\n%i\t%d", message, i, VehicleInfo[vehicle][carAttachObj][i]);
			}
		}
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Araç Eklenti Listesi", message, "Kapat", "");
	}

	else
	{
		SendHelpMessage(playerid, "/aracaksesuar [ayarlar]");
		SendSyntaxMessage(playerid, "liste / satinal / sat / duzenle");
	}
	return 1;
}

alias:aksesuar("acc", "/aksesuarlar");
CMD:aksesuar(playerid, params[])
{
    if (GetPVarInt(playerid, #edit_attach) == 1 || GetPVarInt(playerid, #buy_attach) != 0)	return SendErrorMessage(playerid, "Alýþveriþi / kýyafetleri düzenlemeyi sonlandýrýn.");

	new count, string[750];

	for(new i; i < MAX_PLAYER_ATTACH; i++)
	{
	    if (AttachInfo[playerid][i][aID] == 0) continue;
	    
		format(string, sizeof(string), "%s\n{FFFFFF}%i: %s %s", string, i+1, AttachInfo[playerid][i][aName], (AttachInfo[playerid][i][aUsed]) ? ("{30A90F}[Kullanýmda]") : ("{AFAFAF}[Kullanýmda Deðil]"));
	    count++;
	}

	if (!count)	return SendErrorMessage(playerid, "Hiçbir aksesuarýn/kýyafetin yok.");

    Dialog_Show(playerid, Clothing, DIALOG_STYLE_LIST, "{FF8000}Slot seç", string, "Seç", "Kapat");
	return 1;
}

CMD:paraobje(playerid, params[])
{
    if (GetPVarInt(playerid, #money_hand) && (
		IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS) ||
		IsPlayerAttachedObjectSlotUsed(playerid, 8)
	))
    {
        SetPVarInt(playerid, #money_hand, 0);
		
 		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		RemovePlayerAttachedObject(playerid, 8);
 		return 1;
    }

	if (GetCash(playerid) < 300)								return SendNotCash(playerid);
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))	return SendWarningMessage(playerid, "Elinizde bir þey varken bunu yapamazsýnýz.");

	new type;
	if (sscanf(params, "d", type)) return SendHelpMessage(playerid, "/paraobje [1 - sað el | 2 - sol el]");

	if (type == 1)		SetPlayerAttachedObject(playerid, ATTACH_HANDS, 1212, 6, 0.062999, 0.004999, 0.013000, -106.300003, -3.699995, -84.700004, 0.766000, 1.000000, 0.773000);
	else if (type == 2)	SetPlayerAttachedObject(playerid, 8, 1212, 5, 0.083999, -0.005000, -0.015000, -106.300003, -3.699995, -84.700004, 0.766000, 1.000000, 0.829999);
	else 				return SendHelpMessage(playerid, "/paraobje [1 - sað el | 2 - sol el]"); 
	
    SetPVarInt(playerid, #money_hand, 1);
	return 1;
}