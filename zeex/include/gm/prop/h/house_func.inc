this::OnHouseInsert(houseid)
{
	return HouseInfo[houseid][hID] = cache_insert_id();
}

this::OnHouseFurnituresLoad(houseid)
{
	if (!cache_num_rows())	return 1;

	new tid;

	for(new i; i < cache_num_rows(); i++)
	{
		cache_get_value_index_int(i, 0, HFurn[houseid][i][fID]);
	    cache_get_value_index_int(i, 1, HFurn[houseid][i][fModel]);
		cache_get_value_index(i, 2, HFurn[houseid][i][fName], 64);
		//HFurn[houseid][i][fBuildingID] = houseid;
		cache_get_value_index_int(i, 5, HFurn[houseid][i][fInterior]);
		cache_get_value_index_int(i, 6, HFurn[houseid][i][fVirtualWorld]);
	    cache_get_value_index_int(i, 7, HFurn[houseid][i][fMarketPrice]);
		cache_get_value_index_float(i, 8, HFurn[houseid][i][fPosX]);
		cache_get_value_index_float(i, 9, HFurn[houseid][i][fPosY]);
		cache_get_value_index_float(i, 10, HFurn[houseid][i][fPosZ]);
		cache_get_value_index_float(i, 11, HFurn[houseid][i][fPosRX]);
		cache_get_value_index_float(i, 12, HFurn[houseid][i][fPosRY]);
		cache_get_value_index_float(i, 13, HFurn[houseid][i][fPosRZ]);
	    cache_get_value_index_int(i, 14, HFurn[houseid][i][fTexture][0]);
		cache_get_value_index_int(i, 15, HFurn[houseid][i][fTexture][1]);
		cache_get_value_index_int(i, 16, HFurn[houseid][i][fTexture][2]);
		cache_get_value_index_int(i, 17, HFurn[houseid][i][fTexture][3]);
		cache_get_value_index_int(i, 18, HFurn[houseid][i][fTexture][4]);
		cache_get_value_index_int(i, 19, HFurn[houseid][i][fCategory]);
		cache_get_value_index_int(i, 20, HFurn[houseid][i][ChemIdx]);

		HFurn[houseid][i][fOn] = 1;
		HFurn[houseid][i][fObject] = CreateDynamicObject(HFurn[houseid][i][fModel], HFurn[houseid][i][fPosX], HFurn[houseid][i][fPosY], HFurn[houseid][i][fPosZ], HFurn[houseid][i][fPosRX], HFurn[houseid][i][fPosRY], HFurn[houseid][i][fPosRZ], HFurn[houseid][i][fVirtualWorld], HFurn[houseid][i][fInterior]);

		for(new a; a != 5; a++)
		{
		    if (HFurn[houseid][i][fTexture][a] == -1) continue;

			tid = HFurn[houseid][i][fTexture][a];
			SetDynamicObjectMaterial(HFurn[houseid][i][fObject], a, ObjectTextures[tid][TModel], ObjectTextures[tid][TXDName], ObjectTextures[tid][TextureName], ObjectTextures[tid][MaterialColor]);
		}

		if (isHouseDoor(HFurn[houseid][i][fModel]))
		{
			HFurn[houseid][i][fLocked] = 1;
			HFurn[houseid][i][fOpened] = 0;
		}

		HouseInfo[houseid][hFurniture]++;

		if (HFurn[houseid][i][fVirtualWorld] != HouseInfo[houseid][hExitVW]) HouseInfo[houseid][hOutsideFurniture]++;

	}
	return 1;
}

/*OnFurnitureInsert_House(building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4)
{
	HFurn[building][furnitureslot][fID] = cache_insert_id();
	HFurn[building][furnitureslot][fBuildingID] = building;
	HFurn[building][furnitureslot][fInterior] = interior;
	HFurn[building][furnitureslot][fVirtualWorld] = world;
	HFurn[building][furnitureslot][fMarketPrice] = price;
	HFurn[building][furnitureslot][fModel] = model;
	HFurn[building][furnitureslot][fPosX] = x;
	HFurn[building][furnitureslot][fPosY] = y;
	HFurn[building][furnitureslot][fPosZ] = z;
	HFurn[building][furnitureslot][fPosRX] = rx;
	HFurn[building][furnitureslot][fPosRY] = ry;
	HFurn[building][furnitureslot][fPosRZ] = rz;
	format(HFurn[building][furnitureslot][fName], 64, name);
	HFurn[building][furnitureslot][fOn] = 1;
	HFurn[building][furnitureslot][fCategory] = category;
	HFurn[building][furnitureslot][fTexture][0] = texture_0;
	HFurn[building][furnitureslot][fTexture][1] = texture_1;
	HFurn[building][furnitureslot][fTexture][2] = texture_2;
	HFurn[building][furnitureslot][fTexture][3] = texture_3;
	HFurn[building][furnitureslot][fTexture][4] = texture_4;

	HouseInfo[building][hFurniture]++;

	if (HFurn[building][furnitureslot][fVirtualWorld] != HouseInfo[building][hExitVW]) HouseInfo[building][hOutsideFurniture]++;

	return 1;
}*/

this::LoadDynamicHouses()
{
	new rows = cache_num_rows(), time = GetTickCount(), total, query[256];

	if (!rows)	return print("[Houses] Kayit bulunamadi.");

	for(new i; i < rows; i++)
	{
		cache_get_value_int(i, "id", HouseInfo[i][hID]);
		cache_get_value_float(i, "posx", HouseInfo[i][hPosX]);
		cache_get_value_float(i, "posy", HouseInfo[i][hPosY]);
		cache_get_value_float(i, "posz", HouseInfo[i][hPosZ]);
		cache_get_value_float(i, "exitx", HouseInfo[i][hExitX]);
		cache_get_value_float(i, "exity", HouseInfo[i][hExitY]);
		cache_get_value_float(i, "exitz", HouseInfo[i][hExitZ]);

		cache_get_value_float(i, "ext_ENposX", HouseInfo[i][hExtX][0]);
		cache_get_value_float(i, "ext_ENposY", HouseInfo[i][hExtY][0]);
		cache_get_value_float(i, "ext_ENposZ", HouseInfo[i][hExtZ][0]);
		cache_get_value_float(i, "ext_EXposX", HouseInfo[i][hExtX][1]);
	    cache_get_value_float(i, "ext_EXposY", HouseInfo[i][hExtY][1]);
		cache_get_value_float(i, "ext_EXposZ", HouseInfo[i][hExtZ][1]);
		cache_get_value_int(i, "ext_ENvw", HouseInfo[i][hExtVW][0]);
		cache_get_value_int(i, "ext_EXvw", HouseInfo[i][hExtVW][1]);
		cache_get_value_int(i, "ext_ENint", HouseInfo[i][hExtInt][0]);
		cache_get_value_int(i, "ext_EXint", HouseInfo[i][hExtInt][1]);

		cache_get_value(i, "ownername", HouseInfo[i][hOwner], MAX_PLAYER_NAME);
		strreplace(HouseInfo[i][hOwner], '_', ' ');
		cache_get_value_int(i, "owner", HouseInfo[i][hOwnerID]);
		cache_get_value_int(i, "locked", HouseInfo[i][hLocked]);
		cache_get_value_int(i, "price", HouseInfo[i][hPrice]);
		cache_get_value_int(i, "apartments", HouseInfo[i][hApart]);
		cache_get_value_int(i, "levelbuy", HouseInfo[i][hLevelbuy]);
        cache_get_value_int(i, "cash", HouseInfo[i][hCash]);
		cache_get_value_int(i, "exitint", HouseInfo[i][hExitInt]);
		cache_get_value_int(i, "exitvw", HouseInfo[i][hExitVW]);
		cache_get_value_int(i, "posint", HouseInfo[i][hPosInt]);
		cache_get_value_int(i, "posvw", HouseInfo[i][hPosVW]);
		cache_get_value_float(i, "checkx", HouseInfo[i][hCheckPosX]);
		cache_get_value_float(i, "checky", HouseInfo[i][hCheckPosY]);
		cache_get_value_float(i, "checkz", HouseInfo[i][hCheckPosZ]);
		cache_get_value_int(i, "radio", HouseInfo[i][hRadio]);
		cache_get_value_int(i, "lock", HouseInfo[i][hLock]);
		cache_get_value_int(i, "alarm", HouseInfo[i][hAlarm]);
		cache_get_value_int(i, "door", HouseInfo[i][hDoor]);
		cache_get_value_int(i, "ddoor", HouseInfo[i][hDDoor]);
		cache_get_value_int(i, "class", HouseInfo[i][hClass]);
	    cache_get_value_int(i, "heal", HouseInfo[i][hHeal]);
	    cache_get_value_int(i, "heal_amount", HouseInfo[i][hHealAmount]);
	    cache_get_value_int(i, "cupboard", HouseInfo[i][hCupboard]);
	    cache_get_value_float(i, "furniture_radius", HouseInfo[i][hFurnitureRadius]);
		HouseInfo[i][hFurniture] = 0;
		HouseInfo[i][hOutsideFurniture] = 0;
		UpdateHouseDoor(i);

		if (HouseInfo[i][hExtX][0] > 0 && HouseInfo[i][hExtY][0] > 0 && HouseInfo[i][hExtZ][0] > 0 && !HouseInfo[i][hOwnerID]) {
			HouseInfo[i][hExtPickup] = CreateDynamicPickup(19523, 1, HouseInfo[i][hExtX][0], HouseInfo[i][hExtY][0], HouseInfo[i][hExtZ][0], HouseInfo[i][hExtVW], HouseInfo[i][hExtInt], -1, 100.0);
		}

		if(!HouseInfo[i][hOwnerID]) {
			HouseInfo[i][hPickup] = CreateDynamicPickup(19471, 1, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ] - 0.7, HouseInfo[i][hPosVW], HouseInfo[i][hPosInt], -1, 100.0);
		}
		else if (HouseInfo[i][hLocked] == 1)
		{
			HouseInfo[i][hPickup] = CreateDynamicPickup(19522, 1, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ], HouseInfo[i][hPosVW], HouseInfo[i][hPosInt], -1, 100.0);
		}
		else if (HouseInfo[i][hLocked] == 0)
		{
			HouseInfo[i][hPickup] = CreateDynamicPickup(1273, 1, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ], HouseInfo[i][hPosVW], HouseInfo[i][hPosInt], -1, 100.0);
		}

		mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `furnitures` WHERE `building`=%i AND `bType`=0", HouseInfo[i][hID]);
		mysql_tquery(dbHandle, query, "OnHouseFurnituresLoad", "i", i);

		//mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `inventory` WHERE `houseid`=%i", HouseInfo[i][hID]);
		//mysql_tquery(dbHandle, query, "HouseLoadInventory", "i", i);

		if (HouseInfo[i][hOwnerID] != 0) {
			mysql_format(dbHandle, query, sizeof(query), "SELECT accountid,cash,last_login FROM `users` WHERE `id` = %i LIMIT 1", HouseInfo[i][hOwnerID]);
			mysql_tquery(dbHandle, query, "HouseCheckOwner", "ii", i, HouseInfo[i][hID]);
		}

		total++;
	}
    printf("[Houses] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

this::HouseCheckOwner(houseid, dbid)
{
	if (!cache_num_rows()) return printf("[SQL ERROR] Ev [db ID:%i] sahibi karakter dbsinde bulunamadi.", dbid);

	new accountid,
		money,
		last_login,
		query[256];

	cache_get_value_int(0, "accountid", accountid);	
	cache_get_value_int(0, "cash", money);
	cache_get_value_int(0, "last_login", last_login);

	//if (last_login < gettime()-(60*60*24)*21) {
		//mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `cash`=%i WHERE id=%i LIMIT 1", money+floatround(HouseInfo[houseid][hPrice]/2)/*+GetFurniturePrice(0, i)*/+HouseInfo[houseid][hCash], HouseInfo[houseid][hOwnerID]);
		//mysql_query(dbHandle, query);

		//format(query, sizeof(query), "Ev otomatik olarak sisteme satildi. [H_MYSQL: %i] oyuncu %s [MYSQL: %i] tutar $%i.", HouseInfo[houseid][hID], HouseInfo[houseid][hOwner], HouseInfo[houseid][hOwnerID], HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, i)*/+HouseInfo[houseid][hCash]);
		//insert_log(query, PROPERTY_LOG, 7, accountid);
		//Sell_House(houseid);
	//}
	return 1;
}
/*
this::HouseLoadInventory(houseid)
{
	if (!cache_num_rows())
	{
	    new query[256];
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `inventory` (`houseid`) VALUES (%i)", HouseInfo[houseid][hID]);
	    mysql_tquery(dbHandle, query);
	    return 1;
	}

	new str_inv[24], str_inv2[24], str_inv3[24], str_inv4[24], str_inv5[24], str_inv6[24];

	for(new a = 0; a < MAX_HOUSE_INVENTORY; a++)
	{
        format(str_inv, sizeof(str_inv), "id_%i", a+1);
        cache_get_value_name_int(0, str_inv, HouseInventory[houseid][a][pInvItem]);
        format(str_inv2, sizeof(str_inv2), "a_%i", a+1);
        cache_get_value_name_int(0, str_inv2, HouseInventory[houseid][a][pInvQ]);
        format(str_inv3, sizeof(str_inv3), "ex_%i", a+1);
        cache_get_value_name_int(0, str_inv3, HouseInventory[houseid][a][pInvEx]);
        format(str_inv4, sizeof(str_inv4), "s_%i", a+1);
        cache_get_value_name_int(0, str_inv4, HouseInventory[houseid][a][pInvS]);
        format(str_inv5, sizeof(str_inv5), "f_%i", a+1);
        cache_get_value_name_float(0, str_inv5, HouseInventory[houseid][a][pInvQFloat]);

		new name[16];
		format(str_inv6, sizeof(str_inv6), "n_%i", a+1);
		cache_get_value_name(0, str_inv6, name);

		format(HouseInventory[houseid][a][pInvName], 16, "%s", name);
	}
	return 1;
}*/

this::ShowTenantsAmount(playerid)
{
    //if (!cache_num_rows())	return SendErrorMessage(playerid, "Âàø äîì íèêòî íå àðåíäóåò.");

	static dlgtxt[] = "#\tÝsim\n\
					> Yeni bir kiracý al\n";

	new diatxt[sizeof(dlgtxt) + (MAX_PLAYER_NAME+6)*MAX_TENAT_SPACE], name[MAX_PLAYER_NAME];

    for(new i; i < MAX_TENAT_SPACE; i++) pTemp[playerid][pListed][i] = 0;

	format(diatxt, sizeof(diatxt), "%s", dlgtxt);
	for(new i; i < MAX_TENAT_SPACE; i++)
	{
		if (i == cache_num_rows()) break;

	    cache_get_value_int(i, "id", pTemp[playerid][pListed][i]);

		cache_get_value(i, "name", name);
        strreplace(name, '_', ' ');

		format(diatxt, sizeof(diatxt), "%s%i\t%s\n", diatxt, i, name);
	}
	if (!cache_num_rows()) format(diatxt, sizeof(diatxt), "%sHerhangi bir kiracý bulunmuyor.", dlgtxt);

	Dialog_Show(playerid, EvictTenant, DIALOG_STYLE_TABLIST_HEADERS, "Kiracýlar", diatxt, "Kov", "Geri Dön");
	return 1;

}

this::EvictTenantConfirm(playerid, response)
{
	if (!response)	return DeletePVar(playerid, #Temp);

	new list = GetPVarInt(playerid, #Temp),
		userid = GetIDByID(pTemp[playerid][pListed][list]);

	if (IsPlayerLogged(userid))
	{
	    SendSyntaxMessage(userid, "Ev sahibi %s, sizi evden çýkarttý.", GetNameWithMask(playerid));
        SendSyntaxMessage(playerid, "%s adlý kiracýyý evinizden çýkarttýnýz.", GetNameWithMask(userid));

        PlayerInfo[userid][pRentKey] =
		PlayerInfo[userid][pRentPrice] = 0;
	}
	else
	{
        SendSyntaxMessage(playerid, "Kiracýyý evinizden çýkardýnýz.");
	}

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `rent_key`='0',`rent_price`='0' WHERE `id`=%i", pTemp[playerid][pListed][list]);
	mysql_tquery(dbHandle, query);

	DeletePVar(playerid, #Temp);
	return 1;
}

this::OfferRentRoom(playerid, userid, price)
{
	if (cache_num_rows() > MAX_TENAT_SPACE) return SendErrorMessage(playerid, "En fazla %i kiracýnýz olabilir.", MAX_TENAT_SPACE);

	pTemp[userid][pRentPlayer] = playerid;
	pTemp[userid][pRentPrice] = price;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	SendSyntaxMessage(playerid, "%s adlý kiþiye kiracý olma daveti gönderdiniz, tutar: $%i", GetNameWithMask(userid), price);
    SendSyntaxMessage(userid, "%s adlý kiþi $%i saatlik ücretle evini size kiralýyor. (Onaylamak için Y tuþuna basýn)", GetNameWithMask(playerid), price);
	return 1;
}

AddHouseToFile(houseid, clases, level, price, apart, Float:x, Float:y, Float:z,worldhouse,worldhouseout, interiorout)
{
    new query[128 + 128];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `houses` (posint,class,posx,posy,posz,price,apartments,levelbuy,cash,locked,radio,exitvw,posvw) VALUES (%i,%i,%f,%f,%f,%i,%i,%i,%i,%i,%i,%i,%i)",
	interiorout, clases, x, y, z, price, apart, level, 0, 1, 0, worldhouse, worldhouseout);
	mysql_tquery(dbHandle, query, "OnHouseInsert", "d", houseid);

	return 1;
}

GetHouseZone(houseid, type = 0)
{
	new string[70], zone[28];

	GetZone(HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], zone, sizeof(zone));

	if (IsPointInAnyDynamicArea(HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ])) {
		new areas[5], street_area[1], j = GetNumberDynamicAreasForPoint(HouseInfo[houseid][hPosX],HouseInfo[houseid][hPosY],HouseInfo[houseid][hPosZ]);
		GetDynamicAreasForPoint(HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], areas, sizeof(areas));

		if (GetStreet(areas, j, street_area)) {
			if (type == 0) 		format(string, sizeof(string), "%s, %s %i", zone, street_names[street_area[0]], 35+houseid);
			else if (type == 1) 	format(string, sizeof(string), "%03d %s,~n~%s", 35+houseid, street_names[street_area[0]], zone);
			else if (type == 2) 	format(string, sizeof(string), "%s %i", street_names[street_area[0]], 35+houseid);

			return string;
		}
	}

	format(string, sizeof(string), "%s %i", zone, 35+houseid);
	return string;
}

SetHouseInterior(houseid, id)
{
	HouseInfo[houseid][hExitX] = AdminTeles[id][telesPosX];
	HouseInfo[houseid][hExitY] = AdminTeles[id][telesPosY];
	HouseInfo[houseid][hExitZ] = AdminTeles[id][telesPosZ];
	HouseInfo[houseid][hExitInt] = AdminTeles[id][telesInt];

	HouseInfo[houseid][hExtX][1] =
	HouseInfo[houseid][hExtY][1] =
	HouseInfo[houseid][hExtZ][1] = 0.0;
	HouseInfo[houseid][hExtVW][1] =
	HouseInfo[houseid][hExtInt][1] = 0;

	Save_House(houseid);
	return 1;
}

SetHouseInteriorEx(houseid, class) {
	new houseIntID = random(GetCountHouseType(class)),
		index;

	for(new i = 0; i < MAX_INTERIORS; i++)
	{
		if (!AdminTeles[i][telesOn] || class != AdminTeles[i][telesType]) continue;

		if (index == houseIntID)
		{
		    SetHouseInterior(houseid, i);
		    break;
		}
		index++;
	}
	return 1;
}

GetCountHouseType(class) {
	new count;
	for(new i = 1; i < MAX_INTERIORS; i++)
	{
		if (!AdminTeles[i][telesOn] || class != AdminTeles[i][telesType]) continue;
		count++;
	}
	return count;
}

isHouseDoor(model)
{
	switch(model)
	{
	    case 1493, 1495..1498, 1500, 1501, 1504, 1506, 1507, 1522, 1532, 1533, 1535, 1536, 1557, 1566, 1567, 3089: return 1;
	}
	return 0;
}

Sell_House(houseid)
{
    for(new i; i < MAX_FURNITURE; i++)
	{
	    if (!HFurn[houseid][i][fID] || !HFurn[houseid][i][fOn]) continue;

	    HFurn[houseid][i][fID] =
	    HFurn[houseid][i][fOn] = 0;
	    DestroyDynamicObject(HFurn[houseid][i][fObject]);
	}

    HouseInfo[houseid][hLocked] = 1;
 	StopHouseBoomBox(houseid);
	HouseInfo[houseid][hOwnerID] =
	HouseInfo[houseid][hRadio] =
	HouseInfo[houseid][hRadioOn] =
	HouseInfo[houseid][hDDoor] =
    HouseInfo[houseid][hCash] =
    HouseInfo[houseid][hFurniture] =
    HouseInfo[houseid][hOutsideFurniture] = 0;
    HouseInfo[houseid][hFurnitureRadius] = 7.0;

	for(new i = 0; i < MAX_HOUSE_INVENTORY; i++)
	{
		HouseInventory[houseid][i][pInvItem] =
		HouseInventory[houseid][i][pInvQ] =
		HouseInventory[houseid][i][pInvEx] =
		HouseInventory[houseid][i][pInvS] = 0;
	}

	for(new i = 0; i != MAX_GARAGES; i++)
	{
	    if (!GarageInfo[i][garageID] || GarageInfo[i][garageHouse] != HouseInfo[houseid][hID]) continue;

        GarageInfo[i][garageOwner] = 0;

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `garage` SET `owner`='0' WHERE `id`=%i", GarageInfo[i][garageID]);
		mysql_tquery(dbHandle, query);
	}

	Save_House(houseid);
	return 1;
}

Save_House(houseid)
{
	if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID]) return 1;

	new query[512];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `houses` SET `owner`=%i,`locked`=%i,`price`=%i,`lock`=%i,`levelbuy`=%i,`cash`=%i,`class`=%i,`heal`=%i,`heal_amount`=%i,`checkx`=%f,`checky`=%f,`checkz`=%f,`radio`=%i,`alarm`=%i,`door`=%i,`ddoor`=%i WHERE `id`=%i",
	HouseInfo[houseid][hOwnerID], HouseInfo[houseid][hLocked], HouseInfo[houseid][hPrice],
	HouseInfo[houseid][hLock], HouseInfo[houseid][hLevelbuy], HouseInfo[houseid][hCash], HouseInfo[houseid][hClass],
	HouseInfo[houseid][hHeal], HouseInfo[houseid][hHealAmount], HouseInfo[houseid][hCheckPosX], HouseInfo[houseid][hCheckPosY],
	HouseInfo[houseid][hCheckPosZ], HouseInfo[houseid][hRadio], HouseInfo[houseid][hAlarm], HouseInfo[houseid][hDoor], HouseInfo[houseid][hDDoor],
	HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `houses` SET `ext_EXposX`=%f,`ext_EXposY`=%f,`ext_EXposZ`=%f,`ext_EXvw`=%i,`ext_EXint`=%i,`ext_ENposX`=%f,`ext_ENposY`=%f,`ext_ENposZ`=%f,`ext_ENvw`=%i,`ext_ENint`=%i,`exitx`=%f,`exity`=%f,`exitz`=%f,`exitvw`=%i,`exitint`=%i,`posx`=%f,`posy`=%f,`posz`=%f,`posvw`=%i,`posint`=%i WHERE `id`=%i",
	HouseInfo[houseid][hExtX][1],HouseInfo[houseid][hExtY][1],HouseInfo[houseid][hExtZ][1],HouseInfo[houseid][hExtVW][1],HouseInfo[houseid][hExtInt][1],
	HouseInfo[houseid][hExtX][0],HouseInfo[houseid][hExtY][0],HouseInfo[houseid][hExtZ][0],HouseInfo[houseid][hExtVW][0],HouseInfo[houseid][hExtInt][0],
	HouseInfo[houseid][hExitX],HouseInfo[houseid][hExitY],HouseInfo[houseid][hExitZ],HouseInfo[houseid][hExitVW],HouseInfo[houseid][hExitInt],
	HouseInfo[houseid][hPosX],HouseInfo[houseid][hPosY],HouseInfo[houseid][hPosZ],HouseInfo[houseid][hPosVW],HouseInfo[houseid][hPosInt],
	HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query);
	return 1;
}


UpdateHouseDoor(houseid)
{
    if (IsValidDynamic3DTextLabel(HouseInfo[houseid][hLabelDDoor]))
	{
		DestroyDynamic3DTextLabel(HouseInfo[houseid][hLabelDDoor]);
        HouseInfo[houseid][hLabelDDoor] = Text3D:INVALID_3DTEXT_ID;
	}
	if (!HouseInfo[houseid][hDDoor]) return 1;

	new door_str[][] = {"KAPI", "KAPI KIRIK"};

	HouseInfo[houseid][hLabelDDoor] = CreateDynamic3DTextLabel(door_str[HouseInfo[houseid][hDDoor]-1], COLOR_LIGHTRED, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, HouseInfo[houseid][hPosInt], HouseInfo[houseid][hPosVW], -1, -1, 100.0);
	return 1;
}

GetHouseIDByMysql(mysqlid)
{
    for(new i; i != MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == mysqlid) return i;
	}
	return -1;
}

GetPlayerHouses(playerid)
{
	new total;

    for(new i; i != MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0 || HouseInfo[i][hOwnerID] != PlayerInfo[playerid][pID]) continue;

		total++;
	}
	return total;
}

GetMaxPlayerHouse(playerid)
{
	switch(PlayerInfo[playerid][pPremium])
	{
	    case 0: return 1;
	    case 1: return 2;
	    case 2: return 3;
	    case 3: return 5;
	}
	return 1;
}

IsPlayerOutsideHouse(playerid, i, Float: radius = 5.0)
{
    return (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ]) && GetWorld(playerid) == HouseInfo[i][hPosVW] && GetInterior(playerid) == HouseInfo[i][hPosInt]) ? (1) : (0);
}

IsPlayerInsideHouse(playerid, i, Float: radius = 50.0)
{
    return (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExitX], HouseInfo[i][hExitY], HouseInfo[i][hExitZ]) && GetWorld(playerid) == HouseInfo[i][hExitVW] && GetInterior(playerid) == HouseInfo[i][hExitInt]) ? (1) : (0);
}

/*IsPlayerOutsideExtHouse(playerid, i, Float: radius = 5.0)
{
    return (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExtX][0], HouseInfo[i][hExtY][0], HouseInfo[i][hExtZ][0]) && GetWorld(playerid) == HouseInfo[i][hExtVW][0] && GetInterior(playerid) == HouseInfo[i][hExtInt][0]) ? (1) : (0);
}*/

IsPlayerInsideExtHouse(playerid, i, Float: radius = 30.0)
{
    return (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExtX][1], HouseInfo[i][hExtY][1], HouseInfo[i][hExtZ][1]) && GetWorld(playerid) == HouseInfo[i][hExtVW][1] && GetInterior(playerid) == HouseInfo[i][hExtInt][1]) ? (1) : (0);
}

GetNearHouse(playerid, Float: radius_inside = 30.0, Float: radius_outside = 5.0)
{
    if (pTemp[playerid][pHouseEntered] != -1 && IsPlayerInsideHouse(playerid, pTemp[playerid][pHouseEntered], radius_inside)) return pTemp[playerid][pHouseEntered];

    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID])										continue;
	    if (IsPlayerInsideHouse(playerid, i, radius_inside))			return i;
		else if (IsPlayerOutsideHouse(playerid, i, radius_outside))	return i;
	}
	return -1;
}

GetNearOutsideHouse(playerid, Float: radius = 1.5)
{
    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) continue;

	    if (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hPosX], HouseInfo[i][hPosY], HouseInfo[i][hPosZ]) && GetWorld(playerid) == HouseInfo[i][hPosVW] && GetInterior(playerid) == HouseInfo[i][hPosInt]) return i;
	}
	return -1;
}

GetNearInsideHouse(playerid, Float:radius = 30.0)
{
	if (pTemp[playerid][pHouseEntered] != -1 && IsPlayerInsideHouse(playerid, pTemp[playerid][pHouseEntered], radius)) return pTemp[playerid][pHouseEntered];

    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) continue;

	    if (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExitX], HouseInfo[i][hExitY], HouseInfo[i][hExitZ]) && GetWorld(playerid) == HouseInfo[i][hExitVW] && GetInterior(playerid) == HouseInfo[i][hExitInt])
		{
		    pTemp[playerid][pHouseEntered] = i;
  			return i;
		}
	}
	return -1;
}

GetNearOutsideExtHouse(playerid, Float: radius = 1.5)
{
    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) continue;
	    if (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExtX][0], HouseInfo[i][hExtY][0], HouseInfo[i][hExtZ][0]) && GetWorld(playerid) == HouseInfo[i][hExtVW][0] && GetInterior(playerid) == HouseInfo[i][hExtInt][0]) return i;
	}
	return -1;
}
GetNearInsideExtHouse(playerid, Float:radius = 30.0)
{
	if (pTemp[playerid][pHouseEntered] != -1 && IsPlayerInsideExtHouse(playerid, pTemp[playerid][pHouseEntered], radius)) return pTemp[playerid][pHouseEntered];

    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) continue;

	    if (IsPlayerInRangeOfPoint(playerid, radius, HouseInfo[i][hExtX][0], HouseInfo[i][hExtY][0], HouseInfo[i][hExtZ][0]) && GetWorld(playerid) == HouseInfo[i][hExitVW] && GetInterior(playerid) == HouseInfo[i][hExitInt])
		{
		    pTemp[playerid][pHouseEntered] = i;
  			return i;
		}
	}
	return -1;
}

GetNextHouseID()
{
	for(new i; i < MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) return i;
	}
	return -1;
}

GetNextHouseTrunkSlot(house)
{
	for(new i = 0; i < MAX_HOUSE_INVENTORY; i++)
	{
		if (!HouseInventory[house][i][pInvItem]) return i;
	}
	return -1;
}

HouseFurn(playerid)
{
	new houseid = GetNearHouse(playerid);
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID] && HouseInfo[houseid][hID] != pTemp[playerid][pBuildHouse])	return SendErrorMessage(playerid, "Bu evin mobilyalarýný deðiþtirme izniniz yok.");

	new title[30 + 64];
	format(title, sizeof(title), "{FFFFFF}Mobilyalar [ %s ]", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid, 2)):(GetApartmentZone(HouseInfo[houseid][hApart], 2)));

	pTemp[playerid][pFurniture] = houseid;
	pTemp[playerid][pFurnitureB] = 0;
	Dialog_Show(playerid, FurnitureDialog, DIALOG_STYLE_LIST, title, "Mobilya satýn al\nMobilya düzenle\nTüm mobilyalarý sat", "Seç", "Ýptal");
	return 1;
}

HouseFurnCopy(playerid, building, slot)
{
	if (GetCash(playerid) < HFurn[building][slot][fMarketPrice])
		return SendNotCash(playerid);

    if (HFurn[building][slot][fCategory] == 28 && HouseInfo[building][hOutsideFurniture] > 9)
		return SendErrorMessage(playerid, "Evin dýþýna sadece 10 nesne yerleþtirilebilir.");

	new i = -1;

	for(new a; a < MAX_FURNITURE; a++)
	{
	    if (HFurn[building][a][fOn] != 0) continue;

   		i = a;
		break;
	}

	if (i == -1) return 1;

	//HFurn[building][i][fObject] = CreateDynamicObject(HFurn[building][slot][fModel], HFurn[building][slot][fPosX], HFurn[building][slot][fPosY], HFurn[building][slot][fPosZ], HFurn[building][slot][fPosRX], HFurn[building][slot][fPosRY], HFurn[building][slot][fPosRZ], HFurn[building][slot][fVirtualWorld], HFurn[building][slot][fInterior]);

	new tid[5];
    for(new b; b != 5; b++)
	{
		tid[b] = -1;
 		if (HFurn[building][slot][fTexture][b] != -1) tid[b] = HFurn[building][slot][fTexture][b];
	}

	new f_index = GetFurnitureIndex(HFurn[building][slot][fCategory], HFurn[building][slot][fModel]);
	SetPVarInt(playerid, "buy_furniture", 2);
	OnPlayerCallBuyFurniture(playerid, building, 0, i, HFurn[building][slot][fModel], HFurn[building][slot][fCategory], f_index, HFurn[building][slot][fPosX], HFurn[building][slot][fPosY], HFurn[building][slot][fPosZ], HFurn[building][slot][fPosRX], HFurn[building][slot][fPosRY], HFurn[building][slot][fPosRZ], tid[0], tid[1], tid[2], tid[3], tid[4]);
	return 1;
}

HouseHandleSellFurn(playerid, building)
{
	new paycheck;

	for(new i; i < MAX_FURNITURE; i++)
	{
	    if (!HFurn[building][i][fID] || !HFurn[building][i][fOn]) continue;

	    paycheck += (HFurn[building][i][fMarketPrice] - (HFurn[building][i][fMarketPrice] & 2))  / 2;
	    HFurn[building][i][fID] =
	    HFurn[building][i][fOn] = 0;
	    DestroyDynamicObject(HFurn[building][i][fObject]);
	}

    HouseInfo[building][hFurniture] =
    HouseInfo[building][hOutsideFurniture] = 0;

   	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `building` = %i AND `bType` = 0", HouseInfo[building][hID]);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "Tüm mobilyalarý yarý fiyatýna sattýnýz, toplam geri ödenen miktar: {FFFF00}$%i{FFFFFF}.", paycheck);
	GiveCash(playerid, paycheck);
	return 1;
}

CreateExplosionInHouse(building, idx, f)
{
	new count = 0;

	for(new i; i < MAX_FURNITURE; i++)
	{
		if (count > 5) break;

	    if (!HFurn[building][i][fOn] || !IsValidDynamicObject(HFurn[building][i][fObject])) continue;
		if (HFurn[building][i][fInterior] != HouseInfo[building][hExitInt] && HFurn[building][i][fVirtualWorld] != HouseInfo[building][hExitVW])	continue;
		if (GetDistanceBetweenPoints(HFurn[building][f][fPosX],HFurn[building][f][fPosY],HFurn[building][f][fPosZ],HFurn[building][i][fPosX],HFurn[building][i][fPosY],HFurn[building][i][fPosZ]) > 10.0) continue;
		if (!IsFurnitureFirable(HFurn[building][i][fCategory])) continue;

		new Float:fHitPosX = HFurn[building][i][fPosX],
			Float:fHitPosY = HFurn[building][i][fPosY],
			Float:fHitPosZ = HFurn[building][i][fPosZ],
			furnint = HFurn[building][i][fInterior],
			furnvw = HFurn[building][i][fVirtualWorld]
		;

		if (GetNearFire(fHitPosX,fHitPosY,fHitPosZ,furnint,furnvw) != -1) continue;
		if (floatround(randomEx(0,100)) > 80) OnPlayerSellFurniture(0, building, i);
		count ++;

		new fireid = -1;
		for(new j; j != MAX_FIRES; j++)
		{
		    if (FiresInfo[j][fireOn] != 0) continue;

			fireid = j;
			break;
		}
		if (fireid == -1)	continue;

		FiresInfo[fireid][fireOn] = 1;
		FiresInfo[fireid][fireObj] = CreateDynamicObject(18691, fHitPosX, fHitPosY, fHitPosZ-2.0, 0.0, 0.0, 0.0, furnvw, furnint);
		FiresInfo[fireid][firePos][0] = fHitPosX;
		FiresInfo[fireid][firePos][1] = fHitPosY;
		FiresInfo[fireid][firePos][2] = fHitPosZ;
		FiresInfo[fireid][fireVW] = furnvw;
		FiresInfo[fireid][fireInt] = furnint;
		FiresInfo[fireid][fireHealth] = 100;
		FiresInfo[fireid][fireTimer] = 1800;

		FiresInfo[fireid][fireLabel] = CreateDynamic3DTextLabel("100 %", 0xCC0500FFF, fHitPosX, fHitPosY, fHitPosZ+2.3, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, furnvw, furnint, -1, 100.0);
	}

	CreateDynamicExplosion(HFurn[building][f][fPosX],HFurn[building][f][fPosY],HFurn[building][f][fPosZ], 11, 10.0, HFurn[building][f][fVirtualWorld], HFurn[building][f][fInterior]);
	ClearFurnitureData(f, idx);

	HouseAlarm(building, true);

	new Float:fHitPosX = HouseInfo[building][hPosX],
		Float:fHitPosY = HouseInfo[building][hPosY],
		Float:fHitPosZ = HouseInfo[building][hPosZ],
		furnint = HouseInfo[building][hPosInt],
		furnvw = HouseInfo[building][hPosVW]
	;

	new fireid = -1;
	for(new j; j != MAX_FIRES; j++)
	{
		if (FiresInfo[j][fireOn] != 0) continue;

		fireid = j;
		break;
	}
	if (fireid == -1)	return 1;

	FiresInfo[fireid][fireOn] = 1;
	FiresInfo[fireid][fireObj] = CreateDynamicObject(18691, fHitPosX, fHitPosY, fHitPosZ-2.0, 0.0, 0.0, 0.0, furnvw, furnint);
	FiresInfo[fireid][firePos][0] = fHitPosX;
	FiresInfo[fireid][firePos][1] = fHitPosY;
	FiresInfo[fireid][firePos][2] = fHitPosZ;
	FiresInfo[fireid][fireVW] = furnvw;
	FiresInfo[fireid][fireInt] = furnint;
	FiresInfo[fireid][fireHealth] = 100;
	FiresInfo[fireid][fireTimer] = 1800;

	FiresInfo[fireid][fireLabel] = CreateDynamic3DTextLabel("100 %", 0xCC0500FFF, fHitPosX, fHitPosY, fHitPosZ+2.3, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, furnvw, furnint, -1, 100.0);

	return 1;
}

CreateFireInHouse(building)
{
	new count = 0;

	new Float:fHitPosX = HouseInfo[building][hPosX],
		Float:fHitPosY = HouseInfo[building][hPosY],
		Float:fHitPosZ = HouseInfo[building][hPosZ],
		furnint = HouseInfo[building][hPosInt],
		furnvw = HouseInfo[building][hPosVW]
	;

	new fireid = -1;
	for(new j; j != MAX_FIRES; j++)
	{
		if (FiresInfo[j][fireOn] != 0) continue;

		fireid = j;
		break;
	}
	if (fireid == -1)	return 1;

	FiresInfo[fireid][fireOn] = 1;
	FiresInfo[fireid][fireObj] = CreateDynamicObject(18691, fHitPosX, fHitPosY, fHitPosZ-2.0, 0.0, 0.0, 0.0, furnvw, furnint);
	FiresInfo[fireid][firePos][0] = fHitPosX;
	FiresInfo[fireid][firePos][1] = fHitPosY;
	FiresInfo[fireid][firePos][2] = fHitPosZ;
	FiresInfo[fireid][fireVW] = furnvw;
	FiresInfo[fireid][fireInt] = furnint;
	FiresInfo[fireid][fireHealth] = 100;
	FiresInfo[fireid][fireTimer] = 1800;

	FiresInfo[fireid][fireLabel] = CreateDynamic3DTextLabel("100 %", 0xCC0500FFF, fHitPosX, fHitPosY, fHitPosZ+2.3, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, furnvw, furnint, -1, 100.0);

	fHitPosX = HouseInfo[building][hExitX];
	fHitPosY = HouseInfo[building][hExitY];
	fHitPosZ = HouseInfo[building][hExitZ];

	HouseAlarm(building, true);
	HouseInfo[building][hFireTimer] = gettime()+3600;

	for(new i; i < MAX_FURNITURE; i++)
	{
		if (count > 5) break;

	    if (!HFurn[building][i][fOn] || !IsValidDynamicObject(HFurn[building][i][fObject])) continue;
		if (HFurn[building][i][fInterior] != HouseInfo[building][hExitInt] && HFurn[building][i][fVirtualWorld] != HouseInfo[building][hExitVW])	continue;
		if (GetDistanceBetweenPoints(fHitPosX,fHitPosY,fHitPosZ,HFurn[building][i][fPosX],HFurn[building][i][fPosY],HFurn[building][i][fPosZ]) > 10.0) continue;
		if (!IsFurnitureFirable(HFurn[building][i][fCategory])) continue;

		fHitPosX = HFurn[building][i][fPosX];
		fHitPosY = HFurn[building][i][fPosY];
		fHitPosZ = HFurn[building][i][fPosZ];
		furnint = HFurn[building][i][fInterior];
		furnvw = HFurn[building][i][fVirtualWorld];

		if ( GetNearFire(fHitPosX,fHitPosY,fHitPosZ,furnint,furnvw) != -1 ) continue;
		count++;

		for(new j; j != MAX_FIRES; j++)
		{
		    if (FiresInfo[j][fireOn] != 0) continue;

			fireid = j;
			break;
		}
		if (fireid == -1)	continue;

		FiresInfo[fireid][fireOn] = 1;
		FiresInfo[fireid][fireObj] = CreateDynamicObject(18691, fHitPosX, fHitPosY, fHitPosZ-2.0, 0.0, 0.0, 0.0, furnvw, furnint);
		FiresInfo[fireid][firePos][0] = fHitPosX;
		FiresInfo[fireid][firePos][1] = fHitPosY;
		FiresInfo[fireid][firePos][2] = fHitPosZ;
		FiresInfo[fireid][fireVW] = furnvw;
		FiresInfo[fireid][fireInt] = furnint;
		FiresInfo[fireid][fireHealth] = 100;
		FiresInfo[fireid][fireTimer] = 1800;

		FiresInfo[fireid][fireLabel] = CreateDynamic3DTextLabel("100 %", 0xCC0500FFF, fHitPosX, fHitPosY, fHitPosZ+2.3, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, furnvw, furnint, -1, 100.0);
	}
	return 1;
}

stock HouseAlarm(houseid, bool:toggle)
{
	if (!HouseInfo[houseid][hAlarm])	return 1;

	new aapart = HouseInfo[houseid][hApart];

	switch(toggle)
	{
	    case 0:
	    {
	        if (HouseInfo[houseid][hAlarmA] == 1)
	        {
	            HouseInfo[houseid][hAlarmA]=0;
				HouseInfo[houseid][hAlarmTime]=0;

				if (IsValidDynamic3DTextLabel(HouseInfo[houseid][hAText]))
				{
					DestroyDynamic3DTextLabel(HouseInfo[houseid][hAText]);
					HouseInfo[houseid][hAText] = Text3D:INVALID_3DTEXT_ID;
				}

				if (aapart != 0) PlaySoundInArea(1154, ApartInfo[aapart][aPosX], ApartInfo[aapart][aPosY], ApartInfo[aapart][aPosZ], 20.0);
				else			PlaySoundInArea(1154, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], 20.0);
	        }
	    }
	    case 1:
	    {
	        if (HouseInfo[houseid][hAlarmA] == 0)
	        {
	            HouseInfo[houseid][hAlarmA]=1;
				HouseInfo[houseid][hAlarmTime]=300;

				if (IsValidDynamic3DTextLabel(HouseInfo[houseid][hAText]))
				{
					DestroyDynamic3DTextLabel(HouseInfo[houseid][hAText]);
					HouseInfo[houseid][hAText] = Text3D:INVALID_3DTEXT_ID;
				}

				if (aapart != 0) {
					HouseInfo[houseid][hAText]=CreateDynamic3DTextLabel("*** ALARM ÇALIYOR ***", 0xC2A2DAFF, ApartInfo[aapart][aPosX], ApartInfo[aapart][aPosY], ApartInfo[aapart][aPosZ]+0.50, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 50.0);

					foreach(new i : Player) {
						if (IsPlayerInRangeOfPoint(i, 30.0, ApartInfo[aapart][aPosX], ApartInfo[aapart][aPosY], ApartInfo[aapart][aPosZ]) && GetPlayerVirtualWorld(i) == ApartInfo[aapart][aPosVW])
							SendClientMessageEx(i, COLOR_PURPLE, "*** Dýþarýda alarm çalýyor (%s).", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));
					}

					if (HouseInfo[houseid][hAlarm] < 2) return 1;

					SendFactionMessageF(FACTION_POLICE, COLOR_YELLOWG, "[Ev Alarmý] %s bölgesinde alarm çalýyor!", GetApartmentZone(aapart));

					if (HouseInfo[houseid][hAlarm] < 3) return 1;

					new mes[128];
					format(mes, sizeof(mes), "Evinizin alarmý çalýyor: [%s]", GetApartmentZone(aapart));

					foreach(new i : Player)
					{
						if (IsPlayerLogged(i) && PlayerInfo[i][pID] != HouseInfo[houseid][hOwnerID]) return SendSMStoPlayer(i, "9199", "LCSecurity", mes);
					}

					new query[256];

					mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i", HouseInfo[houseid][hOwnerID]);
					mysql_tquery(dbHandle, query, "SmsToPlayerOff", "sss", "9199", "LCSecurity", mes);
				} else {
					HouseInfo[houseid][hAText]=CreateDynamic3DTextLabel("*** ALARM ÇALIYOR ***", 0xC2A2DAFF, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]+0.50, 50.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 50.0);

					foreach(new i : Player) {
						if (IsPlayerInRangeOfPoint(i, 30.0, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]) && GetPlayerVirtualWorld(i) == HouseInfo[houseid][hPosVW])
							SendClientMessageEx(i, COLOR_PURPLE, "*** Dýþarýda alarm çalýyor (%s).", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));
					}

					if (HouseInfo[houseid][hAlarm] < 2) return 1;

					SendFactionMessageF(FACTION_POLICE, COLOR_YELLOWG, "[Ev Alarmý] %s bölgesinde alarm çalýyor!", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));

					if (HouseInfo[houseid][hAlarm] < 3) return 1;

					new mes[128];
					format(mes, sizeof(mes), "Evinizin alarmý çalýyor: [%s]", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));

					foreach(new i : Player)
					{
						if (IsPlayerLogged(i) && PlayerInfo[i][pID] != HouseInfo[houseid][hOwnerID]) return SendSMStoPlayer(i, "9199", "LCSecurity", mes);
					}

					new query[256];

					mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i", HouseInfo[houseid][hOwnerID]);
					mysql_tquery(dbHandle, query, "SmsToPlayerOff", "sss", "9199", "LCSecurity", mes);
				}
	        }
	    }
	}
	return 1;
}

StopStealing(playerid)
{
	JackingLock[playerid] = 0;
	BreakingHouse[playerid] = 0;
	pTemp[playerid][JackingType] = 0;
	pTemp[playerid][JackingWarnings] = 0;

	for(new i; i < 2; i++) if(IsValidDynamicObject(PlayerInfo[playerid][SafeObject][i])) DestroyDynamicObject(PlayerInfo[playerid][SafeObject][i]);
	PlayerInfo[playerid][SafeObject][0] = PlayerInfo[playerid][SafeObject][1] = INVALID_OBJECT_ID;

	InfoMSG(playerid, "EV SOYGUNUNU ~r~BASARAMADINIZ!", 3);

	return 1;
}

StopBreakingLock(playerid)
{
	JackingLock[playerid] = 0;
	BreakingHouse[playerid] = 0;
	pTemp[playerid][JackingType] = 0;
	pTemp[playerid][JackingWarnings] = 0;

	InfoMSG(playerid, "EVIN KAPISINI ~r~ACAMADINIZ!", 3);

	return 1;
}

stock IsPlayerFalling(playerid)
{
    if(GetPlayerAnimationIndex(playerid) == 1133 || GetPlayerAnimationIndex(playerid) == 1130)
    {
        new Float:Z, Float:Y, Float:X;
        GetPlayerVelocity(playerid, X, Y, Z);
        if(Z != 0)
        {
            return 1;
        }

    }
    return 0;
}
