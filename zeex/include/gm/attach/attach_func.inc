forward OnPlayerLoadAttach(playerid);
forward OnAttachInsert(playerid, slot, model, bone, name[]);

public OnPlayerLoadAttach(playerid)
{
	for(new i = 0; i < MAX_PLAYER_ATTACH; i++)
	{
		AttachInfo[playerid][i][aID] = 0;
		AttachInfo[playerid][i][aUsed] = 0;
	}

	if (!cache_num_rows()) return 1;

    for(new i = 0; i < cache_num_rows(); i++)
	{
     	if (i > MAX_PLAYER_ATTACH) break;

	    cache_get_value_int(i, "id", AttachInfo[playerid][i][aID]);
	    cache_get_value(i, "name", AttachInfo[playerid][i][aName], 32);
		cache_get_value_int(i, "model", AttachInfo[playerid][i][aModel]);
		cache_get_value_int(i, "bone", AttachInfo[playerid][i][aBone]);
		cache_get_value_float(i, "offestx", AttachInfo[playerid][i][aOffsetX]);
		cache_get_value_float(i, "offesty", AttachInfo[playerid][i][aOffsetY]);
		cache_get_value_float(i, "offestz", AttachInfo[playerid][i][aOffsetZ]);
		cache_get_value_float(i, "rotx", AttachInfo[playerid][i][aRotX]);
		cache_get_value_float(i, "roty", AttachInfo[playerid][i][aRotY]);
		cache_get_value_float(i, "rotz", AttachInfo[playerid][i][aRotZ]);
		cache_get_value_float(i, "scalex", AttachInfo[playerid][i][aScaleX]);
		cache_get_value_float(i, "scaley", AttachInfo[playerid][i][aScaleY]);
		cache_get_value_float(i, "scalez", AttachInfo[playerid][i][aScaleZ]);
		cache_get_value_int(i, "used", AttachInfo[playerid][i][aUsed]);
	}
	return 1;
}

public OnAttachInsert(playerid, slot, model, bone, name[])
{
	AttachInfo[playerid][slot][aID] = cache_insert_id();
	AttachInfo[playerid][slot][aModel] = model;
	AttachInfo[playerid][slot][aBone] = bone;
	format(AttachInfo[playerid][slot][aName], 128, "%s", name);
	AttachInfo[playerid][slot][aUsed] = 1;
	return 1;
}

InsertPlayerAttach(playerid, slot, model, bone, name[])
{
    new query[128 + 128];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `player_attach` (userid, name, model, bone) VALUES (%i, '%s', %i, %i)", PlayerInfo[playerid][pID], SQL_ReturnEscaped(name), model, bone);
	mysql_tquery(dbHandle, query, "OnAttachInsert", "iiiis", playerid, slot, model, bone, name);
	return 1;
}

UpdatePlayerAttach(playerid, slot, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ, Float:SC, Float:SY, Float:SZ, bone)
{
    new query[128 + 128];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `player_attach` SET `offestx`=%f,`offesty`=%f,`offestz`=%f,`rotx`=%f,`roty`=%f,`rotz`=%f,`scalex`=%f,`scaley`=%f,`scalez`=%f,`used`=%i,`bone`=%i WHERE `id` = %i", X, Y, Z, RX, RY, RZ, SC, SY, SZ, AttachInfo[playerid][slot][aUsed], bone, AttachInfo[playerid][slot][aID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

LoadPlayerAttach(playerid)
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `player_attach` WHERE `userid` = %i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "OnPlayerLoadAttach", "i", playerid);
	return 1;
}

RemovePlayerAttachFromSlot(playerid, slot)
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `player_attach` WHERE `id` = %i", AttachInfo[playerid][slot][aID]);
	mysql_tquery(dbHandle, query);

	AttachInfo[playerid][slot][aID] = 0;
	AttachInfo[playerid][slot][aName] = EOS;
	AttachInfo[playerid][slot][aModel] = 0;
	AttachInfo[playerid][slot][aBone] = 0;
	AttachInfo[playerid][slot][aOffsetX] = 0.0;
	AttachInfo[playerid][slot][aOffsetY] = 0.0;
	AttachInfo[playerid][slot][aOffsetZ] = 0.0;
	AttachInfo[playerid][slot][aRotX] = 0.0;
	AttachInfo[playerid][slot][aRotY] = 0.0;
	AttachInfo[playerid][slot][aRotZ] = 0.0;
	AttachInfo[playerid][slot][aScaleX] = 0.0;
	AttachInfo[playerid][slot][aScaleY] = 0.0;
	AttachInfo[playerid][slot][aScaleZ] = 0.0;
	AttachInfo[playerid][slot][aUsed] = 0;

	if (IsPlayerAttachedObjectSlotUsed(playerid, slot))	RemovePlayerAttachedObject(playerid, slot);
	return 1;
}

Save_AttachWeapon(playerid, i)
{
	new query[256];
	
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `weap_%i_bone` = %i, `weap_%i_x` = %f, `weap_%i_y` = %f, `weap_%i_z` = %f, `weap_%i_rx` = %f, `weap_%i_ry` = %f, `weap_%i_rz` = %f WHERE `id` = %i",
	i, PlayerInfo[playerid][pWeaponBone][i], i, PlayerInfo[playerid][pWeaponX][i], i, PlayerInfo[playerid][pWeaponY][i], i, PlayerInfo[playerid][pWeaponZ][i], i, PlayerInfo[playerid][pWeaponRX][i], i, PlayerInfo[playerid][pWeaponRY][i],
	i, PlayerInfo[playerid][pWeaponRZ][i], PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

GetNextToySlot(playerid)
{
	for(new i = 0; i < MAX_PLAYER_ATTACH; i++)
	{
		if (AttachInfo[playerid][i][aID] == 0) return i;
	}
	return -1;
}

Dialog:MODEL_SELECTION_FA(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru / saðlýk görevlisi / hükümet olmalýsýnýz.");

	Dialog_Show(playerid, SelectBone, DIALOG_STYLE_LIST, "Vücut Bölgeleri","- Deðiþmeden Býrak\n1: Arka\n2: Kafa\n3: Sol Omuz\n4: Sað Omuz\n5: Sol Kol\n6:Sað Kol\n7: Sol Uyluk\n8: Sað Uyluk\n9: Sol Bacak\n10: Sað Bacak\n11: Sað Baldýr\n12: Sol Baldýr\n13: Sol Ön Kol\n14: Sað Ön Kol\n15: Sol Köprücük Kemiði\n16: Sol Köprücük Kemiði\n17: Boyun\n18: Çene","Seç","Ýptal");
	SetPVarInt(playerid, #select_attach, listitem);
	return 1;
}//î

Dialog:MODEL_SELECTION_OBJATT(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new 
		vehicle = GetPVarInt(playerid, #veh_editor), 
		carslot = GetPVarInt(playerid, #veh_slot), 
		attobj = car_attach[listitem],

		Float:x, 
		Float:y, 
		Float:z
	;

	GetVehiclePos(vehicle, x, y, z);
	VehicleInfo[vehicle][carAttach][carslot] = CreateDynamicObject(attobj, x, y, z+2, 0.0, 0.0, 0.0);
	
	SetPVarInt(playerid, #veh_obj, attobj);
	SetPVarInt(playerid, "Vehicle:AttEdit", 0);

	EditDynamicObject(playerid, VehicleInfo[vehicle][carAttach][carslot]);
		
	if (IsPlayerInAnyVehicle(playerid))	InfoMSG(playerid, "kamerayi hareket ettirmek icin \"~y~W~w~\"~n~tuslarini kullanabilirsiniz", 5);
	else								InfoMSG(playerid, "kamerayi hareket ettirmek icin \"~y~SPACE~w~\",~n~tuslarini kullanabilirsiniz", 5);
		
	return 1;
}