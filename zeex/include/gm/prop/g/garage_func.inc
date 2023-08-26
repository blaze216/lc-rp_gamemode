this::LoadDynamicGarage()
{
	new rows = cache_num_rows(), time = GetTickCount(), total, query[256];

	if (!rows) return print("[Garage] Kayit bulunamadi.");
	
	for(new i = 0; i < rows; i++)
	{
cache_get_value_int(i, "id", GarageInfo[i][garageID]);
cache_get_value_int(i, "owner", GarageInfo[i][garageOwner]);
cache_get_value_int(i, "house", GarageInfo[i][garageHouse]);
cache_get_value_int(i, "biz", GarageInfo[i][garageBiz]);
cache_get_value_int(i, "ddoor", GarageInfo[i][garageDDoor]);
cache_get_value_int(i, "price", GarageInfo[i][garagePrice]);
cache_get_value_int(i, "locked", GarageInfo[i][garageLocked]);
cache_get_value_int(i, "enter_int", GarageInfo[i][garageEnterInt]);
cache_get_value_int(i, "enter_vw", GarageInfo[i][garageEnterVW]);
cache_get_value_float(i, "player_enter_x", GarageInfo[i][garagePlayer_Enter][0]);
cache_get_value_float(i, "player_enter_y", GarageInfo[i][garagePlayer_Enter][1]);
cache_get_value_float(i, "player_enter_z", GarageInfo[i][garagePlayer_Enter][2]);
cache_get_value_int(i, "exit_int", GarageInfo[i][garageExitInt]);
GarageInfo[i][garageExitVW] = GarageInfo[i][garageID] + 100;
cache_get_value_float(i, "player_exit_x", GarageInfo[i][garagePlayer_Exit][0]);
cache_get_value_float(i, "player_exit_y", GarageInfo[i][garagePlayer_Exit][1]);
cache_get_value_float(i, "player_exit_z", GarageInfo[i][garagePlayer_Exit][2]);
cache_get_value_float(i, "veh_enter_x", GarageInfo[i][garageVeh_Enter][0]);
cache_get_value_float(i, "veh_enter_y", GarageInfo[i][garageVeh_Enter][1]);
cache_get_value_float(i, "veh_enter_z", GarageInfo[i][garageVeh_Enter][2]);
cache_get_value_float(i, "veh_enter_fa", GarageInfo[i][garageVeh_Enter][3]);
cache_get_value_float(i, "veh_exit_x", GarageInfo[i][garageVeh_Exit][0]);
cache_get_value_float(i, "veh_exit_y", GarageInfo[i][garageVeh_Exit][1]);
cache_get_value_float(i, "veh_exit_z", GarageInfo[i][garageVeh_Exit][2]);
cache_get_value_float(i, "veh_exit_fa", GarageInfo[i][garageVeh_Exit][3]);
        cache_get_value(i, "ownername", GarageInfo[i][garageOwnerName], MAX_PLAYER_NAME);
		strreplace(GarageInfo[i][garageOwnerName], '_', ' ');
		GarageInfo[i][garageCP] = CreateDynamicCP(GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2], 0.9, GarageInfo[i][garageEnterVW], GarageInfo[i][garageEnterInt], -1, 3.0);
		
		format(query, sizeof(query), "SELECT * FROM `furnitures` WHERE `building`=%i AND `bType`=2", GarageInfo[i][garageID]);
		mysql_tquery(dbHandle, query, "OnGFurnsLoad", "i", i);
		
		total++;
	}
	printf("[Garage] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

this::OnGFurnsLoad(garageid)
{
	if (!cache_num_rows())	return 1;

	new tid;

	for(new i; i < cache_num_rows(); i++)
	{
		cache_get_value_index_int(i, 0, GFurn[garageid][i][fID]);
	    cache_get_value_index_int(i, 1, GFurn[garageid][i][fModel]);
		cache_get_value_index(i, 2, GFurn[garageid][i][fName], 64);
		//GFurn[garageid][i][fBuildingID] = garageid;
		cache_get_value_index_int(i, 5, GFurn[garageid][i][fInterior]);
		cache_get_value_index_int(i, 6, GFurn[garageid][i][fVirtualWorld]);
	    cache_get_value_index_int(i, 7, GFurn[garageid][i][fMarketPrice]);
		cache_get_value_index_float(i, 8, GFurn[garageid][i][fPosX]);
		cache_get_value_index_float(i, 9, GFurn[garageid][i][fPosY]);
		cache_get_value_index_float(i, 10, GFurn[garageid][i][fPosZ]);
		cache_get_value_index_float(i, 11, GFurn[garageid][i][fPosRX]);
		cache_get_value_index_float(i, 12, GFurn[garageid][i][fPosRY]);
		cache_get_value_index_float(i, 13, GFurn[garageid][i][fPosRZ]);
	    cache_get_value_index_int(i, 14, GFurn[garageid][i][fTexture][0]);
		cache_get_value_index_int(i, 15, GFurn[garageid][i][fTexture][1]);
		cache_get_value_index_int(i, 16, GFurn[garageid][i][fTexture][2]);
		cache_get_value_index_int(i, 17, GFurn[garageid][i][fTexture][3]);
		cache_get_value_index_int(i, 18, GFurn[garageid][i][fTexture][4]);
		cache_get_value_index_int(i, 19, GFurn[garageid][i][fCategory]);
		cache_get_value_index_int(i, 20, GFurn[garageid][i][ChemIdx]);

		GFurn[garageid][i][fOn] = 1;
		GFurn[garageid][i][fObject] = CreateDynamicObject(GFurn[garageid][i][fModel], GFurn[garageid][i][fPosX], GFurn[garageid][i][fPosY], GFurn[garageid][i][fPosZ], GFurn[garageid][i][fPosRX], GFurn[garageid][i][fPosRY], GFurn[garageid][i][fPosRZ], GFurn[garageid][i][fVirtualWorld], GFurn[garageid][i][fInterior]);

		for(new a; a != 5; a++)
		{
		    if (GFurn[garageid][i][fTexture][a] == -1) continue;

			tid = GFurn[garageid][i][fTexture][a];
			SetDynamicObjectMaterial(GFurn[garageid][i][fObject], a, ObjectTextures[tid][TModel], ObjectTextures[tid][TXDName], ObjectTextures[tid][TextureName], ObjectTextures[tid][MaterialColor]);
		}

		if (isHouseDoor(GFurn[garageid][i][fModel]))
		{
			GFurn[garageid][i][fLocked] = 1;
			GFurn[garageid][i][fOpened] = 0;
		}
		
		GarageInfo[garageid][gFurniture]++;
		
		if (GFurn[garageid][i][fVirtualWorld] != GarageInfo[garageid][garageExitVW]) GarageInfo[garageid][gOutsideFurniture]++;
		
	}
	return 1;
}

this::GarageInsert(garageid)
{
	return GarageInfo[garageid][garageID] = cache_insert_id();
}

Garage_Create(playerid, type, price, tie = 0, id = 0)
{
    for(new i = 0; i < MAX_GARAGES; i++)
	{
	    if (GarageInfo[i][garageID]) continue;

	    GarageInfo[i][garagePrice] = price;
     	GarageInfo[i][garageHouse] = 0;
	    GarageInfo[i][garageBiz] = 0;
	    GarageInfo[i][garageOwner] = 0;

		GarageInfo[i][garageDDoor] = 0;

     	if (tie == 1)
		{
	 		GarageInfo[i][garageHouse] = HouseInfo[id][hID];
			GarageInfo[i][garageOwner] = HouseInfo[id][hOwnerID];

			format(GarageInfo[id][garageOwnerName], 24, "%s", GetPlayerNameBySqlID(GarageInfo[i][garageOwner]));
			SQL_SetInteger("garage", "owner", GarageInfo[id][garageOwner], GarageInfo[id][garageID]);		
			SQL_SetString("users", "name", GarageInfo[id][garageOwnerName], GarageInfo[id][garageOwner]);
		} else if (tie == 2)	{
		 	GarageInfo[i][garageBiz] = BizInfo[id][bizID];
		 	GarageInfo[i][garageOwner] = BizInfo[id][bizOwnerID];

			format(GarageInfo[id][garageOwnerName], 24, "%s", GetPlayerNameBySqlID(GarageInfo[i][garageOwner]));
			SQL_SetInteger("garage", "owner", GarageInfo[id][garageOwner], GarageInfo[id][garageID]);		
			SQL_SetString("users", "name", GarageInfo[id][garageOwnerName], GarageInfo[id][garageOwner]);
		}
		
	    GetPlayerPos(playerid, GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2]);
	    GetPlayerPos(playerid, GarageInfo[i][garageVeh_Enter][0], GarageInfo[i][garageVeh_Enter][1], GarageInfo[i][garageVeh_Enter][2]);

        GarageInfo[i][garageEnterInt] = GetInterior(playerid);
		GarageInfo[i][garageEnterVW] = GetWorld(playerid);
	    GarageInfo[i][garagePlayer_Exit][0] = garage_player_pos[type-1][0];
	    GarageInfo[i][garagePlayer_Exit][1] = garage_player_pos[type-1][1];
	    GarageInfo[i][garagePlayer_Exit][2] = garage_player_pos[type-1][2];
	    GarageInfo[i][garageVeh_Exit][0] = garage_veh_pos[type-1][0];
	    GarageInfo[i][garageVeh_Exit][1] = garage_veh_pos[type-1][1];
	    GarageInfo[i][garageVeh_Exit][2] = garage_veh_pos[type-1][2];
	    GarageInfo[i][garageVeh_Exit][3] = garage_veh_pos[type-1][3];
	    GarageInfo[i][garageExitInt] = garage_int[type-1];
	    GarageInfo[i][garageExitVW] = GarageInfo[i][garageID] + 100;
	    GarageInfo[i][garageCP] = CreateDynamicCP(GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2], 0.9, GarageInfo[i][garageEnterVW], GarageInfo[i][garageEnterInt], -1, 3.0);
		SendSyntaxMessage(playerid, "Bir garaj oluþturdun. [ID: %i].", i);
        SendSyntaxMessage(playerid, "Garajýn araç spawn pozisyonunu düzenlemeyi unutmayýn - /agarage edit.");

		new query[512];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `garage` (`price`,`house`,`biz`,`ddoor`,`player_enter_x`,`player_enter_y`,`player_enter_z`,`player_exit_x`,`player_exit_y`,`player_exit_z`,`veh_enter_x`,`veh_enter_y`,`veh_enter_z`,`veh_enter_fa`,`veh_exit_x`,`veh_exit_y`,`veh_exit_z`,`veh_exit_fa`,`exit_int`,`enter_int`,`enter_vw`) VALUES (%i,%i,%i,%i,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%i,%i,%i)",
		GarageInfo[i][garagePrice],
		GarageInfo[i][garageHouse],
		GarageInfo[i][garageBiz],
		GarageInfo[i][garageDDoor],
		GarageInfo[i][garagePlayer_Enter][0],
		GarageInfo[i][garagePlayer_Enter][1], 
		GarageInfo[i][garagePlayer_Enter][2], 
		GarageInfo[i][garagePlayer_Exit][0], 
		GarageInfo[i][garagePlayer_Exit][1], 
		GarageInfo[i][garagePlayer_Exit][2], 
		GarageInfo[i][garagePlayer_Enter][0], 
		GarageInfo[i][garagePlayer_Enter][1], 
		GarageInfo[i][garagePlayer_Enter][2], 
		GarageInfo[i][garageVeh_Enter][0], 
		GarageInfo[i][garageVeh_Enter][1], 
		GarageInfo[i][garageVeh_Enter][2],
		GarageInfo[i][garageVeh_Enter][3],
		GarageInfo[i][garageVeh_Exit][0], 
		GarageInfo[i][garageVeh_Exit][1], 
		GarageInfo[i][garageVeh_Exit][2], 
		GarageInfo[i][garageVeh_Exit][3], 
		GarageInfo[i][garageExitInt], 
		GarageInfo[i][garageEnterInt], 
		GarageInfo[i][garageEnterVW]);
		mysql_tquery(dbHandle, query, "GarageInsert", "i", i);
		return i;
	}
	return -1;
}

GetNearOutsideGarage(playerid, Float:radius = 2.0)
{
	if (GetInterior(playerid)) return -1;

    for(new i = 0; i < MAX_GARAGES; i++)
	{
	    if (!GarageInfo[i][garageID]) continue;

		if(!IsPlayerInAnyVehicle(i)) {
			if (GetWorld(playerid) == GarageInfo[i][garageEnterVW] && GetInterior(playerid) == GarageInfo[i][garageEnterInt] && IsPlayerInRangeOfPoint(playerid, radius, GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2])) {
				return i;
			}
		}	
        else if (GetWorld(playerid) == GarageInfo[i][garageEnterVW] && GetInterior(playerid) == GarageInfo[i][garageEnterInt] && IsPlayerInRangeOfPoint(playerid, radius+1.0, GarageInfo[i][garageVeh_Enter][0], GarageInfo[i][garageVeh_Enter][1], GarageInfo[i][garageVeh_Enter][2])) {
			return i;
		}
	}
	return -1;
}

GetNearInsideGarage(playerid, Float:radius = 2.5)
{
	if (!GetInterior(playerid)) return -1;

    for(new i = 0; i < MAX_GARAGES; i++)
	{
	    if (!GarageInfo[i][garageID]) continue;
		
		if(!IsPlayerInAnyVehicle(i)) {
			if (IsPlayerInRangeOfPoint(playerid, radius, GarageInfo[i][garagePlayer_Exit][0], GarageInfo[i][garagePlayer_Exit][1], GarageInfo[i][garagePlayer_Exit][2]) && GetInterior(playerid) == GarageInfo[i][garageExitInt] && GetWorld(playerid) == GarageInfo[i][garageExitVW])
			{
				return i;
			}	
		}
        else if (IsPlayerInRangeOfPoint(playerid, radius+1.0, GarageInfo[i][garageVeh_Exit][0], GarageInfo[i][garageVeh_Exit][1], GarageInfo[i][garageVeh_Exit][2]) && GetInterior(playerid) == GarageInfo[i][garageExitInt] && GetWorld(playerid) == GarageInfo[i][garageExitVW])
		{
			return i;
		}
	}
	return -1;
}

GetNearGarage(playerid, Float:radius = 3.0)
{
    new garage = GetNearInsideGarage(playerid, radius);

	if (garage == -1)		garage = GetNearOutsideGarage(playerid, radius);
	if (garage != -1)		return garage;
	
	return -1;
}
/* çàãðóçêà
OnFurnitureInsert_Garage(building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4)
{
	GFurn[building][furnitureslot][fID] = cache_insert_id();
	GFurn[building][furnitureslot][fBuildingID] = building;
	GFurn[building][furnitureslot][fInterior] = interior;
	GFurn[building][furnitureslot][fVirtualWorld] = world;
	GFurn[building][furnitureslot][fMarketPrice] = price;
	GFurn[building][furnitureslot][fModel] = model;
	GFurn[building][furnitureslot][fPosX] = x;
	GFurn[building][furnitureslot][fPosY] = y;
	GFurn[building][furnitureslot][fPosZ] = z;
	GFurn[building][furnitureslot][fPosRX] = rx;
	GFurn[building][furnitureslot][fPosRY] = ry;
	GFurn[building][furnitureslot][fPosRZ] = rz;
	format(GFurn[building][furnitureslot][fName], 64, name);
	GFurn[building][furnitureslot][fOn] = 1;
	GFurn[building][furnitureslot][fCategory] = category;
	GFurn[building][furnitureslot][fTexture][0] = texture_0;
	GFurn[building][furnitureslot][fTexture][1] = texture_1;
	GFurn[building][furnitureslot][fTexture][2] = texture_2;
	GFurn[building][furnitureslot][fTexture][3] = texture_3;
	GFurn[building][furnitureslot][fTexture][4] = texture_4;
			
	GarageInfo[building][gFurniture]++;

	if (GFurn[building][furnitureslot][fVirtualWorld] != GarageInfo[building][garageExitVW]) GarageInfo[building][gOutsideFurniture]++;

	return 1;
}*/

GarageFurn(playerid)
{
	new garage = GetNearGarage(playerid);
	if (GarageInfo[garage][garageOwner] != PlayerInfo[playerid][pID] && GarageInfo[garage][garageID] != pTemp[playerid][pBuildHouse])	
		return SendErrorMessage(playerid, "Bu garajýn mobilyalarýný düzenleme yetkiniz yok.");
	
	new title[37];
	format(title, sizeof(title), "{FFFFFF}Garaj Mobilyalarý [ %i ]", GarageInfo[garage][garageID]);

	pTemp[playerid][pFurniture] = garage;
	pTemp[playerid][pFurnitureB] = 2; 
	Dialog_Show(playerid, FurnitureDialog, DIALOG_STYLE_LIST, title, "Mobilya satýn al\nMobilya düzenle\nTüm mobilyalarý sat", "Seç", "Ýptal");
	return 1;
}

GarageFurnCopy(playerid, building, slot)
{
	if (GetCash(playerid) < GFurn[building][slot][fMarketPrice])
		return SendNotCash(playerid);

    if (GFurn[building][slot][fCategory] == 28 && GarageInfo[building][gOutsideFurniture] > 9) 
		return SendErrorMessage(playerid, "Dýþarýya maksimum 10 mobilya koyabilirsiniz.");
            
	new i = -1;

	for(new a; a < MAX_FURNITURE; a++)
	{
	    if (GFurn[building][a][fOn] != 0) continue;

   		i = a;
		break;
	}

	if (i == -1) return 1;

	//GFurn[building][i][fObject] = CreateDynamicObject(GFurn[building][slot][fModel], GFurn[building][slot][fPosX], GFurn[building][slot][fPosY], GFurn[building][slot][fPosZ], GFurn[building][slot][fPosRX], GFurn[building][slot][fPosRY], GFurn[building][slot][fPosRZ], GFurn[building][slot][fVirtualWorld], GFurn[building][slot][fInterior]);

	new tid[5];
    for(new b; b != 5; b++)
	{
		tid[b] = -1;
 		if (GFurn[building][slot][fTexture][b] != -1) tid[b] = GFurn[building][slot][fTexture][b];
	}

	new f_index = GetFurnitureIndex(GFurn[building][slot][fCategory], GFurn[building][slot][fModel]);
	SetPVarInt(playerid, "buy_furniture", 2);
	OnPlayerCallBuyFurniture(playerid, building, 2, i, GFurn[building][slot][fModel], GFurn[building][slot][fCategory], f_index, GFurn[building][slot][fPosX], GFurn[building][slot][fPosY], GFurn[building][slot][fPosZ], GFurn[building][slot][fPosRX], GFurn[building][slot][fPosRY], GFurn[building][slot][fPosRZ], tid[0], tid[1], tid[2], tid[3], tid[4]);
	return 1;
}

GarageHandleSellFurn(playerid, building)
{
	new paycheck;

	for(new i; i < MAX_FURNITURE; i++)
	{
	    if (!GFurn[building][i][fID] || !GFurn[building][i][fOn]) continue;

	    paycheck += (GFurn[building][i][fMarketPrice] - (GFurn[building][i][fMarketPrice] & 2))  / 2;
	    GFurn[building][i][fID] =
	    GFurn[building][i][fOn] = 0;
	    DestroyDynamicObject(GFurn[building][i][fObject]);
	}

    GarageInfo[building][gFurniture] =
    GarageInfo[building][gOutsideFurniture] = 0;
    
   	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `building` = %i AND `bType` = 2", GarageInfo[building][garageID]);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "Garajda bulunan tüm mobilyalar satýldý, geri ödenen: {FFFF00}$%i{FFFFFF}.", paycheck);
	GiveCash(playerid, paycheck);
	return 1;
}

CreateExplosionInGarage(building, idx, f)
{
	new count = 0;

	for(new i; i < MAX_FURNITURE; i++)
	{
		if (count > 5) break;

	    if (!GFurn[building][i][fOn] || !IsValidDynamicObject(GFurn[building][i][fObject])) continue;
		if (GFurn[building][i][fInterior] != GarageInfo[building][garageEnterInt] && GFurn[building][i][fVirtualWorld] != GarageInfo[building][garageEnterVW]) continue;
		if (GetDistanceBetweenPoints(GFurn[building][f][fPosX],GFurn[building][f][fPosY],GFurn[building][f][fPosZ],GFurn[building][i][fPosX],GFurn[building][i][fPosY],GFurn[building][i][fPosZ]) > 10.0) continue;
		if (!IsFurnitureFirable(GFurn[building][i][fCategory])) continue;

		new 
			Float:fHitPosX = GFurn[building][i][fPosX], 
			Float:fHitPosY = GFurn[building][i][fPosY],
			Float:fHitPosZ = GFurn[building][i][fPosZ],
			furnint = GFurn[building][i][fInterior],
			furnvw = GFurn[building][i][fVirtualWorld]
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

	CreateDynamicExplosion(GFurn[building][f][fPosX],GFurn[building][f][fPosY],GFurn[building][f][fPosZ], 11, 10.0, GFurn[building][f][fVirtualWorld], GFurn[building][f][fInterior]);
	ClearFurnitureData(f, idx);	

	new Float:fHitPosX = GarageInfo[building][garagePlayer_Enter][0], 
		Float:fHitPosY = GarageInfo[building][garagePlayer_Enter][1],
		Float:fHitPosZ = GarageInfo[building][garagePlayer_Enter][2],
		furnint = GarageInfo[building][garageEnterInt],
		furnvw = GarageInfo[building][garageEnterVW]
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

CreateFireInGarage(building)
{
	new count = 0;

	new Float:fHitPosX = GarageInfo[building][garagePlayer_Enter][0], 
		Float:fHitPosY = GarageInfo[building][garagePlayer_Enter][1],
		Float:fHitPosZ = GarageInfo[building][garagePlayer_Enter][2],
		furnint = GarageInfo[building][garageEnterInt],
		furnvw = GarageInfo[building][garageEnterVW]
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

	fHitPosX = GarageInfo[building][garagePlayer_Exit][0];
	fHitPosY = GarageInfo[building][garagePlayer_Exit][1];
	fHitPosZ = GarageInfo[building][garagePlayer_Exit][2];

	GarageInfo[building][gFireTimer] = gettime()+3600;

	new Float: x, Float: y, Float: z;
	for(new i; i < GetVehiclePoolSize(); i++)
	{    
        GetVehiclePos(i, x, y, z);
		if (GetVehicleInteriorEx(i) == furnint && GetVehicleVirtualWorldEx(i) == furnvw) {
			if (GetDistanceBetweenPoints(fHitPosX,fHitPosY,fHitPosZ,x,y,z) < 30.0) {
				SetVehicleHealth(i, 350);
				if (VehicleInfo[i][carEngine] > 11) VehicleInfo[i][carEngine] -= 10;
				if (VehicleInfo[i][carBattery] > 11) VehicleInfo[i][carBattery] -= 10;
			}
		}
	}

	for(new i; i < MAX_FURNITURE; i++)
	{
		if (count > 5) break;

	    if (!GFurn[building][i][fOn] || !IsValidDynamicObject(GFurn[building][i][fObject])) continue;
		if (GFurn[building][i][fInterior] != GarageInfo[building][garageEnterInt] && GFurn[building][i][fVirtualWorld] != GarageInfo[building][garageEnterVW]) continue;
		if (GetDistanceBetweenPoints(fHitPosX,fHitPosY,fHitPosZ,GFurn[building][i][fPosX],GFurn[building][i][fPosY],GFurn[building][i][fPosZ]) > 10.0) continue;
		if (!IsFurnitureFirable(GFurn[building][i][fCategory])) continue;

		fHitPosX = GFurn[building][i][fPosX]; 
		fHitPosY = GFurn[building][i][fPosY];	
		fHitPosZ = GFurn[building][i][fPosZ];
		furnint = GFurn[building][i][fInterior];
		furnvw = GFurn[building][i][fVirtualWorld];

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

Save_Garage(i)
{
    new query[1024];
    
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `garage` SET `price`=%i,`house`=%i,`biz`=%i,`ddoor`=%i,`player_enter_x`=%f,`player_enter_y`=%f,`player_enter_z`=%f,`player_exit_x`=%f,`player_exit_y`=%f,`player_exit_z`=%f,`veh_enter_x`=%f,`veh_enter_y`=%f,`veh_enter_z`=%f,`veh_enter_fa`=%f,`veh_exit_x`=%f,`veh_exit_y`=%f,`veh_exit_z`=%f,`veh_exit_fa`=%f,`exit_int`=%i,`enter_int`=%i,`enter_vw`=%i WHERE `id`=%i",
		GarageInfo[i][garagePrice],GarageInfo[i][garageHouse],GarageInfo[i][garageBiz], GarageInfo[i][garageDDoor], GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2], GarageInfo[i][garagePlayer_Exit][0], 
		GarageInfo[i][garagePlayer_Exit][1], GarageInfo[i][garagePlayer_Exit][2], GarageInfo[i][garagePlayer_Enter][0], GarageInfo[i][garagePlayer_Enter][1], GarageInfo[i][garagePlayer_Enter][2], GarageInfo[i][garageVeh_Exit][0], 
		GarageInfo[i][garageVeh_Exit][1], GarageInfo[i][garageVeh_Exit][2], GarageInfo[i][garageExitInt], GarageInfo[i][garageEnterInt], GarageInfo[i][garageEnterVW], GarageInfo[i][garageID]);
	mysql_tquery(dbHandle, query);

	return 1;
}

UpdateGarageDoor(garageid)
{
	if (IsValidDynamic3DTextLabel(GarageInfo[garageid][garageLabelDDoor]))
	{
	    DestroyDynamic3DTextLabel(GarageInfo[garageid][garageLabelDDoor]);
        GarageInfo[garageid][garageLabelDDoor] = Text3D:INVALID_3DTEXT_ID;
	}
	if (!GarageInfo[garageid][garageDDoor])	return 1;

    new door_str[][] =	{"KAPI CALDI", "KAPI PATLATILDI"};
		
	GarageInfo[garageid][garageLabelDDoor] = CreateDynamic3DTextLabel(door_str[GarageInfo[garageid][garageDDoor]-1], COLOR_LIGHTRED, GarageInfo[garageid][garagePlayer_Enter][0], GarageInfo[garageid][garagePlayer_Enter][1], GarageInfo[garageid][garagePlayer_Enter][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GarageInfo[garageid][garageEnterVW], GarageInfo[garageid][garageEnterInt], -1, 100.0);
	return 1;
}
