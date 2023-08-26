this::OnFurnitureInsert(type, building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4)
{
	switch(type)
	{
		case 0: { //OnFurnitureInsert_House(building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4);
			HFurn[building][furnitureslot][fID] = cache_insert_id();
			//HFurn[building][furnitureslot][fBuildingID] = building;
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
			HFurn[building][furnitureslot][ChemIdx] = -1;
					
			HouseInfo[building][hFurniture]++;

			if (HFurn[building][furnitureslot][fVirtualWorld] != HouseInfo[building][hExitVW]) HouseInfo[building][hOutsideFurniture]++;

			return 1;
		}
		case 1: { //OnFurnitureInsert_Biz(building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4);
			BFurn[building][furnitureslot][fID] = cache_insert_id();
			//BFurn[building][furnitureslot][fBuildingID] = building;
			BFurn[building][furnitureslot][fInterior] = interior;
			BFurn[building][furnitureslot][fVirtualWorld] = world;
			BFurn[building][furnitureslot][fMarketPrice] = price;
			BFurn[building][furnitureslot][fModel] = model;
			BFurn[building][furnitureslot][fPosX] = x;
			BFurn[building][furnitureslot][fPosY] = y;
			BFurn[building][furnitureslot][fPosZ] = z;
			BFurn[building][furnitureslot][fPosRX] = rx;
			BFurn[building][furnitureslot][fPosRY] = ry;
			BFurn[building][furnitureslot][fPosRZ] = rz;
			format(BFurn[building][furnitureslot][fName], 64, name);
			BFurn[building][furnitureslot][fOn] = 1;
			BFurn[building][furnitureslot][fCategory] = category;
			BFurn[building][furnitureslot][fTexture][0] = texture_0;
			BFurn[building][furnitureslot][fTexture][1] = texture_1;
			BFurn[building][furnitureslot][fTexture][2] = texture_2;
			BFurn[building][furnitureslot][fTexture][3] = texture_3;
			BFurn[building][furnitureslot][fTexture][4] = texture_4;
			BFurn[building][furnitureslot][ChemIdx] = -1;
					
			BizInfo[building][bFurniture]++;

			if (BFurn[building][furnitureslot][fVirtualWorld] != BizInfo[building][bizExitVW]) BizInfo[building][bOutsideFurniture]++;

			return 1;
		}
		case 2: { //OnFurnitureInsert_Garage(building, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx, Float:ry, Float:rz, texture_0, texture_1, texture_2, texture_3, texture_4);
			GFurn[building][furnitureslot][fID] = cache_insert_id();
			//GFurn[building][furnitureslot][fBuildingID] = building;
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
			GFurn[building][furnitureslot][ChemIdx] = -1;
					
			GarageInfo[building][gFurniture]++;

			if (GFurn[building][furnitureslot][fVirtualWorld] != GarageInfo[building][garageExitVW]) GarageInfo[building][gOutsideFurniture]++;

			return 1;
		}
	}
	
	return 0;
}

GetNearBuilding(playerid, Float: radius_inside = 30.0, Float: radius_outside = 1.5)
{
    new building = GetNearHouse(playerid, radius_inside, radius_outside),
        bizid = GetNearBiz(playerid, radius_inside, radius_outside),
        garage = GetNearGarage(playerid);

    if (building != -1 && bizid != -1)
    {
        for(new i = 5; i != 0; i--)
        {
            building = GetNearHouse(playerid, radius_inside, i);
            bizid = GetNearBiz(playerid, radius_inside, i);

            if (building == -1)   return 1;
            if (bizid == -1)     return 0;
        }
        
        if (building != -1 && bizid != -1) return -1;
    }
    else
    {
        if (building != -1)   return 0;
        if (bizid != -1)     return 1;
        if (garage != -1)    return 2;
    }

    return -1;
}

GetXYZNearHouse(Float: x, Float: y, Float: z, Float: radius_outside = 10.0, Float: radius_inside = 30.0, int = 0, world = 0, use_fire = 1)
{
    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID]) continue;	
		if (use_fire && gettime()-HouseInfo[i][hFireTimer] < 0)	continue;
		if (HouseInfo[i][hPosVW] == world && HouseInfo[i][hPosInt] == int && GetDistanceBetweenPoints(x,y,z,HouseInfo[i][hPosX],HouseInfo[i][hPosY],HouseInfo[i][hPosZ]) <= radius_outside) return i;
		if (HouseInfo[i][hExitVW] == world && HouseInfo[i][hExitInt] == int && GetDistanceBetweenPoints(x,y,z,HouseInfo[i][hExitX],HouseInfo[i][hExitY],HouseInfo[i][hExitZ]) <= radius_inside) return i;
	}
	return -1;
}

GetXYZNearBiz(Float: x, Float: y, Float: z, Float: radius_outside = 10.0, Float: radius_inside = 30.0, int = 0, world = 0, use_fire = 1)
{
    for(new i; i != MAX_BIZ; i++)
	{
	    if (!BizInfo[i][bizID]) continue;
		if (use_fire && gettime()-BizInfo[i][bFireTimer] < 0)	continue;
		if (BizInfo[i][bizPosVW] == world && BizInfo[i][bizPosInt] == int && GetDistanceBetweenPoints(x,y,z,BizInfo[i][bizPosX],BizInfo[i][bizPosY],BizInfo[i][bizPosZ]) <= radius_outside) return i;
		if (BizInfo[i][bizExitVW] == world && BizInfo[i][bizExitInt] == int && GetDistanceBetweenPoints(x,y,z,BizInfo[i][bizExitX],BizInfo[i][bizExitY],BizInfo[i][bizExitZ]) <= radius_inside) return i;
	}
	return -1;
}

GetXYZNearGarage(Float: x, Float: y, Float: z, Float: radius_outside = 10.0, Float: radius_inside = 30.0, int = 0, world = 0, use_fire = 1)
{
    for(new i; i != MAX_HOUSES; i++)
	{
	    if (!GarageInfo[i][garageID]) continue;	
		if (use_fire && gettime()-GarageInfo[i][gFireTimer] < 0)	continue;
		if (GarageInfo[i][garageEnterVW] == world && GarageInfo[i][garageEnterInt] == int && GetDistanceBetweenPoints(x,y,z,GarageInfo[i][garageVeh_Enter][0], GarageInfo[i][garageVeh_Enter][1], GarageInfo[i][garageVeh_Enter][2]) <= radius_outside) return i;
		if (GarageInfo[i][garageExitVW] == world && GarageInfo[i][garageExitInt] == int && GetDistanceBetweenPoints(x,y,z,GarageInfo[i][garagePlayer_Exit][0], GarageInfo[i][garagePlayer_Exit][1], GarageInfo[i][garagePlayer_Exit][2]) <= radius_inside) return i;
	}
	return -1;
}

GetXYZNearBuilding(Float: x, Float: y, Float: z, Float: radius_inside = 30.0, Float: radius_outside = 5.0, int = 0, world = 0, use_fire = 1)
{
    new house = GetXYZNearHouse(x, y, z, radius_inside, radius_outside, int, world, use_fire),
        bizid = GetXYZNearBiz(x, y, z, radius_inside, radius_outside, int, world, use_fire),
        garage = GetXYZNearGarage(x, y, z, radius_inside, radius_outside, int, world, use_fire);

    if (house != -1)			return 0;
	else if (bizid != -1) 	return 1;
	else if (garage != -1)	return 2;
    return -1;
}

Check3DMenu(playerid)
{
	if (pTemp[playerid][p3DMenu] != -1)
	{
	   	Destroy3DMenu(pTemp[playerid][p3DMenu]);
		pTemp[playerid][p3DMenu] = -1;
	}
	return 1;
}

GetNearInBuilding(playerid, type)
{
    new building = -1;

    switch(type)
    {
        case 0: building = GetNearInsideHouse(playerid);
        case 1: building = GetNearInsideBiz(playerid);
        case 2: building = GetNearInsideGarage(playerid);
    }

    return building;
}

GetNearOutBuilding(playerid, type)
{
    new building = -1;

    switch(type)
    {
        case 0: building = GetNearOutsideHouse(playerid);
        case 1: building = GetNearOutsideBiz(playerid);
        case 2: building = GetNearOutsideGarage(playerid);
    }

    return building;
}

GetFurnitures(playerid) {
    switch(pTemp[playerid][pFurnitureB])
    {
        case 0: return HouseInfo[pTemp[playerid][pFurniture]][hFurniture];
        case 1: return BizInfo[pTemp[playerid][pFurniture]][bFurniture];
        case 2: return GarageInfo[pTemp[playerid][pFurniture]][gFurniture];
    }
    return -1;
}

GetOutsideFurnitures(playerid) {
    switch(pTemp[playerid][pFurnitureB])
    {
        case 0: return HouseInfo[pTemp[playerid][pFurniture]][hOutsideFurniture];
        case 1: return BizInfo[pTemp[playerid][pFurniture]][bOutsideFurniture];
        case 2: return GarageInfo[pTemp[playerid][pFurniture]][gOutsideFurniture];
    }

    return -1;
}
	
this::ShowEditFurniture(playerid)
{
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) 	return 1;
	if (GetPVarInt(playerid, "chose_slot") < 0 || GetPVarInt(playerid, "chose_slot") > MAX_FURNITURE-1)					return 1;

	new name[64],
		type = pTemp[playerid][pFurnitureB],
		building = pTemp[playerid][pFurniture], 
		slot = GetPVarInt(playerid, "chose_slot");
		
	switch(type)
	{
		case 0: {
			if (HFurn[building][slot][fOn] == 0 || !IsValidDynamicObject(HFurn[building][slot][fObject]))	return pc_cmd_dekorasyon(playerid, "");
			format(name, sizeof(name), "%s", HFurn[building][slot][fName]);
		}
		case 1: {
			if (BFurn[building][slot][fOn] == 0 || !IsValidDynamicObject(BFurn[building][slot][fObject]))	return pc_cmd_dekorasyon(playerid, "");
			format(name, sizeof(name), "%s", BFurn[building][slot][fName]);
		}
		case 2: {
			if (GFurn[building][slot][fOn] == 0 || !IsValidDynamicObject(GFurn[building][slot][fObject]))	return pc_cmd_dekorasyon(playerid, "");
			format(name, sizeof(name), "%s", GFurn[building][slot][fName]);
		}
	}
	
 	Dialog_Show(playerid, EditFurniture, DIALOG_STYLE_LIST, name, "Bilgi\nPozisyon deðiþtir\nTexture düzenle\nSat\nÝsim deðiþtir\nKopyala", "Seç", "Geri Dön");
 	return 1;
}

ShowFurnitureList(playerid, list = 0)
{
	if (list == 0) pTemp[playerid][pDialogList] = 0;

    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) return 1;

	new type = pTemp[playerid][pFurnitureB], building = pTemp[playerid][pFurniture], furnitures = GetFurnitures(playerid);

	if (!furnitures)	return SendErrorMessage(playerid, "Mobilyanýz yok.");
	if (list < 0 || ((furnitures-1) / MAX_FURNITURE_LIST < list))	return 1;
	
	new start_itter = MAX_FURNITURE_LIST * list, count = 0, str[71 + (72 * MAX_FURNITURE_LIST)];

	if (list) strcat(str, "{bccd32}Önceki sayfa{FFFFFF}\n");
	    
	switch(type)
	{
		case 0: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!HFurn[building][i][fOn] || !IsValidDynamicObject(HFurn[building][i][fObject])) continue;

				if (count >= start_itter + MAX_FURNITURE_LIST)
				{
					strcat(str, "{bccd32}Sonraki sayfa");
					break;
				}
				
				if (count >= start_itter)	format(str, sizeof(str), "%s%s%i: %s\n", str, (HFurn[building][i][fInterior] != HouseInfo[building][hExitInt])?("{C3C3C3}"):(""), i+1, HFurn[building][i][fName]);
					
				count++;
			}
		} case 1: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!BFurn[building][i][fOn] || !IsValidDynamicObject(BFurn[building][i][fObject])) continue;

				if (count >= start_itter + MAX_FURNITURE_LIST)
				{
					strcat(str, "{bccd32}Sonraki sayfa");
					break;
				}
				
				if (count >= start_itter)	format(str, sizeof(str), "%s%s%i: %s\n", str, (BFurn[building][i][fInterior] != BizInfo[building][bizExitInt])?("{C3C3C3}"):(""), i+1, BFurn[building][i][fName]);
				
				count++;
			}
		} case 2: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!GFurn[building][i][fOn] || !IsValidDynamicObject(GFurn[building][i][fObject])) continue;

				if (count >= start_itter + MAX_FURNITURE_LIST)
				{
					strcat(str, "{bccd32}Sonraki sayfa");
					break;
				}
				
				if (count >= start_itter)	format(str, sizeof(str), "%s%s%i: %s\n", str, (GFurn[building][i][fInterior] != GarageInfo[building][garageExitInt])?("{C3C3C3}"):(""), i+1, GFurn[building][i][fName]);
					
				count++;
			}
		}
	}

	pTemp[playerid][pDialogList] = list;

	new title[64];
	format(title, sizeof(title), "{FFFFFF}Toplam: %i / %i. Dýþarýda: %i", furnitures, GetMaxPlayerFurniture(playerid), GetOutsideFurnitures(playerid));
	Dialog_Show(playerid, FurnitureList, DIALOG_STYLE_LIST, title, str, "Seç", "Kapat");
		
	return 1;
}

OnPlayerBuyFurniture(building, buildingID, type, interior, world, furnitureslot, model, price, name[], Float:x, Float:y, Float:z, category, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, texture_0= -1 ,texture_1= -1 ,texture_2= -1 ,texture_3= -1, texture_4= -1)
{
    new query[512];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `furnitures` (model,name,bType,building,interior,virworld,marketprice,posx,posy,posz,posrx,posry,posrz,category,texture_0,texture_1,texture_2,texture_3,texture_4,ChemIdx) VALUES (%i,'%e',%i,%i,%i,%i,%i, %f, %f, %f, %f, %f, %f,%i,%i,%i,%i,%i,%i,-1)", model, name, type, buildingID, interior, world, price, x, y, z, rx, ry, rz, category, texture_0, texture_1, texture_2, texture_3, texture_4);
	mysql_tquery(dbHandle, query, "OnFurnitureInsert", "iiiiiiisfffifffiiiii", type, building, interior, world, furnitureslot, model, price, name, x, y, z, category, rx, ry, rz, texture_0, texture_1, texture_2, texture_3, texture_4);
	return 1;
}

OnPlayerCallBuyFurniture(playerid, building, type, furnitureslot, model, f_category, f_index, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, texture_0 = -1, texture_1= -1 ,texture_2= -1 ,texture_3= -1, texture_4= -1)
{
	/*if (f_category == 29 && (model == REACTOR_OBJECT || model == DRYER_OBJECT || model == MIXER_OBJECT)) {
		if (GetClosestFurniture(playerid, 30.0, model, DRUG_LAB) != -1) return SendErrorMessage(playerid, "%s zaten bulunuyor.", furniture_list[f_category][f_index][frName]);
	}*/

	SetPVarInt(playerid, "furniture_index", f_index);
	SetPVarInt(playerid, "category_furniture", f_category);

	SetPVarInt(playerid, "edit_furniture", 1);
	SetPVarInt(playerid, "chose_slot", furnitureslot);

	SetPVarInt(playerid, #texture_0, texture_0);
	SetPVarInt(playerid, #texture_1, texture_1);
	SetPVarInt(playerid, #texture_2, texture_2);
	SetPVarInt(playerid, #texture_3, texture_3);
	SetPVarInt(playerid, #texture_4, texture_4);

	switch(type) {
		case 0: {
			HFurn[building][furnitureslot][fObject] = CreateDynamicObject(model, x, y, z, rx, ry, rz, GetWorld(playerid), GetInterior(playerid));
			
			if (texture_0 != -1) SetDynamicObjectMaterial(HFurn[building][furnitureslot][fObject], 0, ObjectTextures[texture_0][TModel], ObjectTextures[texture_0][TXDName], ObjectTextures[texture_0][TextureName], ObjectTextures[texture_0][MaterialColor]);
			if (texture_1 != -1) SetDynamicObjectMaterial(HFurn[building][furnitureslot][fObject], 1, ObjectTextures[texture_1][TModel], ObjectTextures[texture_1][TXDName], ObjectTextures[texture_1][TextureName], ObjectTextures[texture_1][MaterialColor]);
			if (texture_2 != -1) SetDynamicObjectMaterial(HFurn[building][furnitureslot][fObject], 2, ObjectTextures[texture_2][TModel], ObjectTextures[texture_2][TXDName], ObjectTextures[texture_2][TextureName], ObjectTextures[texture_2][MaterialColor]);
			if (texture_3 != -1) SetDynamicObjectMaterial(HFurn[building][furnitureslot][fObject], 3, ObjectTextures[texture_3][TModel], ObjectTextures[texture_3][TXDName], ObjectTextures[texture_3][TextureName], ObjectTextures[texture_3][MaterialColor]);
			if (texture_4 != -1) SetDynamicObjectMaterial(HFurn[building][furnitureslot][fObject], 4, ObjectTextures[texture_4][TModel], ObjectTextures[texture_4][TXDName], ObjectTextures[texture_4][TextureName], ObjectTextures[texture_4][MaterialColor]);
			
			EditDynamicObject(playerid, HFurn[building][furnitureslot][fObject]);
		}
		case 1: {
			BFurn[building][furnitureslot][fObject] = CreateDynamicObject(model, x, y, z, rx, ry, rz, GetWorld(playerid), GetInterior(playerid));
			
			if (texture_0 != -1) SetDynamicObjectMaterial(BFurn[building][furnitureslot][fObject], 0, ObjectTextures[texture_0][TModel], ObjectTextures[texture_0][TXDName], ObjectTextures[texture_0][TextureName], ObjectTextures[texture_0][MaterialColor]);
			if (texture_1 != -1) SetDynamicObjectMaterial(BFurn[building][furnitureslot][fObject], 1, ObjectTextures[texture_1][TModel], ObjectTextures[texture_1][TXDName], ObjectTextures[texture_1][TextureName], ObjectTextures[texture_1][MaterialColor]);
			if (texture_2 != -1) SetDynamicObjectMaterial(BFurn[building][furnitureslot][fObject], 2, ObjectTextures[texture_2][TModel], ObjectTextures[texture_2][TXDName], ObjectTextures[texture_2][TextureName], ObjectTextures[texture_2][MaterialColor]);
			if (texture_3 != -1) SetDynamicObjectMaterial(BFurn[building][furnitureslot][fObject], 3, ObjectTextures[texture_3][TModel], ObjectTextures[texture_3][TXDName], ObjectTextures[texture_3][TextureName], ObjectTextures[texture_3][MaterialColor]);
			if (texture_4 != -1) SetDynamicObjectMaterial(BFurn[building][furnitureslot][fObject], 4, ObjectTextures[texture_4][TModel], ObjectTextures[texture_4][TXDName], ObjectTextures[texture_4][TextureName], ObjectTextures[texture_4][MaterialColor]);
			
			EditDynamicObject(playerid, BFurn[building][furnitureslot][fObject]);
		}
		case 2: {
			GFurn[building][furnitureslot][fObject] = CreateDynamicObject(model, x, y, z, rx, ry, rz, GetWorld(playerid), GetInterior(playerid));
			
			if (texture_0 != -1) SetDynamicObjectMaterial(GFurn[building][furnitureslot][fObject], 0, ObjectTextures[texture_0][TModel], ObjectTextures[texture_0][TXDName], ObjectTextures[texture_0][TextureName], ObjectTextures[texture_0][MaterialColor]);
			if (texture_1 != -1) SetDynamicObjectMaterial(GFurn[building][furnitureslot][fObject], 1, ObjectTextures[texture_1][TModel], ObjectTextures[texture_1][TXDName], ObjectTextures[texture_1][TextureName], ObjectTextures[texture_1][MaterialColor]);
			if (texture_2 != -1) SetDynamicObjectMaterial(GFurn[building][furnitureslot][fObject], 2, ObjectTextures[texture_2][TModel], ObjectTextures[texture_2][TXDName], ObjectTextures[texture_2][TextureName], ObjectTextures[texture_2][MaterialColor]);
			if (texture_3 != -1) SetDynamicObjectMaterial(GFurn[building][furnitureslot][fObject], 3, ObjectTextures[texture_3][TModel], ObjectTextures[texture_3][TXDName], ObjectTextures[texture_3][TextureName], ObjectTextures[texture_3][MaterialColor]);
			if (texture_4 != -1) SetDynamicObjectMaterial(GFurn[building][furnitureslot][fObject], 4, ObjectTextures[texture_4][TModel], ObjectTextures[texture_4][TXDName], ObjectTextures[texture_4][TextureName], ObjectTextures[texture_4][MaterialColor]);
			
			EditDynamicObject(playerid, GFurn[building][furnitureslot][fObject]);
		}
	}

	InfoMSG(playerid, "Mobilyayý kendinize yaklastirmak icin \" ~y~SPACE ~w~\" ve \" ~y~MMB ~w~\" tuslarina basin. ~n~Islemi geri almak icin \" ~r~ESC ~w~\" tusuna basin", 5);
	return 1;
}

DelPVarText(playerid)
{
	DeletePVar(playerid, "edit_furniture");
	DeletePVar(playerid, "chose_slot");
	DeletePVar(playerid, "buy_furniture");
	DeletePVar(playerid, "category_furniture");
	DeletePVar(playerid, "furniture_index");

	DeletePVar(playerid, #texture_0);
	DeletePVar(playerid, #texture_1);
	DeletePVar(playerid, #texture_2);
	DeletePVar(playerid, #texture_3);
	DeletePVar(playerid, #texture_4);

	return 1;
}

OnPlayerEditedFurniture(type, building, furnitureslot, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new query[256];

	switch(type)
	{
		case 0: {
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `posx` = %f, `posy` = %f, `posz` = %f, `posrx` = %f, `posry` = %f, `posrz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, HFurn[building][furnitureslot][fID]);
			
			HFurn[building][furnitureslot][fPosX] = x;
			HFurn[building][furnitureslot][fPosY] = y;
			HFurn[building][furnitureslot][fPosZ] = z;
			HFurn[building][furnitureslot][fPosRX] = rx;
			HFurn[building][furnitureslot][fPosRY] = ry;
			HFurn[building][furnitureslot][fPosRZ] = rz;
		} case 1: {
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `posx` = %f, `posy` = %f, `posz` = %f, `posrx` = %f, `posry` = %f, `posrz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, BFurn[building][furnitureslot][fID]);
			
			BFurn[building][furnitureslot][fPosX] = x;
			BFurn[building][furnitureslot][fPosY] = y;
			BFurn[building][furnitureslot][fPosZ] = z;
			BFurn[building][furnitureslot][fPosRX] = rx;
			BFurn[building][furnitureslot][fPosRY] = ry;
			BFurn[building][furnitureslot][fPosRZ] = rz;
		} case 2: {
			mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `posx` = %f, `posy` = %f, `posz` = %f, `posrx` = %f, `posry` = %f, `posrz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, GFurn[building][furnitureslot][fID]);
			
			GFurn[building][furnitureslot][fPosX] = x;
			GFurn[building][furnitureslot][fPosY] = y;
			GFurn[building][furnitureslot][fPosZ] = z;
			GFurn[building][furnitureslot][fPosRX] = rx;
			GFurn[building][furnitureslot][fPosRY] = ry;
			GFurn[building][furnitureslot][fPosRZ] = rz;
		}
	}

	mysql_tquery(dbHandle, query);
	return 1;
}

OnPlayerSellFurniture(type, building, furnitureslot)
{
    new query[256];

	switch(type) {
		case 0: {
			mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `id` = %i", HFurn[building][furnitureslot][fID]);

			if (HFurn[building][furnitureslot][fVirtualWorld] != HouseInfo[building][hExitVW]) HouseInfo[building][hOutsideFurniture]--;

			DestroyDynamicObject(HFurn[building][furnitureslot][fObject]);
			HFurn[building][furnitureslot][fInterior] = 
			HFurn[building][furnitureslot][fVirtualWorld] =
			HFurn[building][furnitureslot][fMarketPrice] = 
			HFurn[building][furnitureslot][fModel] = 0;
			HFurn[building][furnitureslot][fPosX] = 
			HFurn[building][furnitureslot][fPosY] = 
			HFurn[building][furnitureslot][fPosZ] = 
			HFurn[building][furnitureslot][fPosRX] = 
			HFurn[building][furnitureslot][fPosRY] = 
			HFurn[building][furnitureslot][fPosRZ] = 0.0;
			format(HFurn[building][furnitureslot][fName], 64, "Yok");
			HFurn[building][furnitureslot][fOn] = 0;

			HouseInfo[building][hFurniture]--;
		} case 1: {
			mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `id` = %i", BFurn[building][furnitureslot][fID]);

			if (BFurn[building][furnitureslot][fVirtualWorld] != BizInfo[building][bizExitVW]) BizInfo[building][bOutsideFurniture]--;

			DestroyDynamicObject(BFurn[building][furnitureslot][fObject]);
			BFurn[building][furnitureslot][fInterior] = 
			BFurn[building][furnitureslot][fVirtualWorld] =
			BFurn[building][furnitureslot][fMarketPrice] = 
			BFurn[building][furnitureslot][fModel] = 0;
			BFurn[building][furnitureslot][fPosX] = 
			BFurn[building][furnitureslot][fPosY] = 
			BFurn[building][furnitureslot][fPosZ] = 
			BFurn[building][furnitureslot][fPosRX] = 
			BFurn[building][furnitureslot][fPosRY] = 
			BFurn[building][furnitureslot][fPosRZ] = 0.0;
			format(BFurn[building][furnitureslot][fName], 64, "Yok");
			BFurn[building][furnitureslot][fOn] = 0;

			BizInfo[building][bFurniture]--;
		} case 2: {
			mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `id` = %i", GFurn[building][furnitureslot][fID]);

			if (GFurn[building][furnitureslot][fVirtualWorld] != GarageInfo[building][garageExitVW]) GarageInfo[building][gOutsideFurniture]--;

			DestroyDynamicObject(GFurn[building][furnitureslot][fObject]);
			GFurn[building][furnitureslot][fInterior] = 
			GFurn[building][furnitureslot][fVirtualWorld] =
			GFurn[building][furnitureslot][fMarketPrice] = 
			GFurn[building][furnitureslot][fModel] = 0;
			GFurn[building][furnitureslot][fPosX] = 
			GFurn[building][furnitureslot][fPosY] = 
			GFurn[building][furnitureslot][fPosZ] = 
			GFurn[building][furnitureslot][fPosRX] = 
			GFurn[building][furnitureslot][fPosRY] = 
			GFurn[building][furnitureslot][fPosRZ] = 0.0;
			format(GFurn[building][furnitureslot][fName], 64, "Yok");
			GFurn[building][furnitureslot][fOn] = 0;

			GarageInfo[building][gFurniture]--;
		}
	}
	
	mysql_tquery(dbHandle, query);
	return 1;
}

GetMaxPlayerFurniture(playerid)
{
	switch(PlayerInfo[playerid][pPremium])
	{
	    case 0: return 70;
	    case 1: return 150;
	    case 2: return 250;
	    case 3: return 400;
	}
	return 70;
}


GetClosestFurniture(playerid, Float:fradius, furnmodelid, f_cat = 0)
{
	new building = GetNearBuilding(playerid);
	if (building == -1)	return -1;

    switch(building)
    {
        case 0: {
            building = GetNearOutsideHouse(playerid);
            if (building == -1)  building = GetNearInsideHouse(playerid);
			if (building == -1)	return 1;
			
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!HFurn[building][i][fOn])					        continue;
				if (HFurn[building][i][fModel] != furnmodelid)			continue;
				if (HFurn[building][i][fCategory] != f_cat)				continue;
				if (!IsValidDynamicObject(HFurn[building][i][fObject])) 	continue;

				if (IsPlayerInRangeOfPoint(playerid, fradius, HFurn[building][i][fPosX], HFurn[building][i][fPosY], HFurn[building][i][fPosZ]) && GetPlayerInterior(playerid) == HFurn[building][i][fInterior] && GetPlayerVirtualWorld(playerid) == HFurn[building][i][fVirtualWorld])
				{
					return i;
				}
			}
        } case 1: {
            building = GetNearOutsideGarage(playerid);
            if (building == -1)  building = GetNearInsideBiz(playerid);
			if (building == -1)	return 1;
			
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!BFurn[building][i][fOn])					        continue;
				if (BFurn[building][i][fModel] != furnmodelid)			continue;
				if (BFurn[building][i][fCategory] != f_cat)				continue;
				if (!IsValidDynamicObject(BFurn[building][i][fObject])) 	continue;	

				if (IsPlayerInRangeOfPoint(playerid, fradius, BFurn[building][i][fPosX], BFurn[building][i][fPosY], BFurn[building][i][fPosZ]) && GetPlayerInterior(playerid) == BFurn[building][i][fInterior] && GetPlayerVirtualWorld(playerid) == BFurn[building][i][fVirtualWorld])
				{
					return i;
				}
			}
        } case 2: {
            building = GetNearOutsideBiz(playerid);
            if (building == -1)  building = GetNearInsideGarage(playerid);
			if (building == -1)	return 1;
			
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!GFurn[building][i][fOn])					        continue;
				if (GFurn[building][i][fModel] != furnmodelid)			continue;
				if (GFurn[building][i][fCategory] != f_cat)				continue;
				if (!IsValidDynamicObject(GFurn[building][i][fObject])) 	continue;	

				if (IsPlayerInRangeOfPoint(playerid, fradius, GFurn[building][i][fPosX], GFurn[building][i][fPosY], GFurn[building][i][fPosZ]) && GetPlayerInterior(playerid) == GFurn[building][i][fInterior] && GetPlayerVirtualWorld(playerid) == GFurn[building][i][fVirtualWorld])
				{
					return i;
				}
			}
        }
    }
	
	return -1;
}


Bu_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if (GetPVarInt(playerid, "edit_furniture") == 1)
	{
		new building = pTemp[playerid][pFurniture], Float:Bx, Float:By, Float:Bz, Float:Brad, 
			f_cat = GetPVarInt(playerid, "category_furniture"), 
			f_index = GetPVarInt(playerid, "furniture_index"),
			name[64],
			f_slot = GetPVarInt(playerid, "chose_slot"),
			f_price = furniture_list[f_cat][f_index][frPrice];

		format(name, sizeof(name), furniture_list[f_cat][f_index][frName]);

		switch(pTemp[playerid][pFurnitureB])
		{
			case 0: {				
				Bx = HouseInfo[building][hPosX];
				By = HouseInfo[building][hPosY];
				Bz = HouseInfo[building][hPosZ];
				Brad = HouseInfo[building][hFurnitureRadius];
			} case 1: { 
				Bx = BizInfo[building][bizPosX];
				By = BizInfo[building][bizPosY];
				Bz = BizInfo[building][bizPosZ];
				Brad = BizInfo[building][bFurnitureRadius];
			} case 2: { 
				Bx = GarageInfo[building][garageVeh_Enter][0];
				By = GarageInfo[building][garageVeh_Enter][1];
				Bz = GarageInfo[building][garageVeh_Enter][2];
				Brad = GarageInfo[building][gFurnitureRadius];
			}
		}

		if (response == EDIT_RESPONSE_FINAL)
		{
		    if (f_cat == 28 && GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)
			{
			    EditDynamicObject(playerid, objectid);
				return SendErrorMessage(playerid, "Mobilyayý satýn almak / düzenlemek için dýþarýda olmalýsýnýz.");
			}

	    	else if (f_cat != 28 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)
			{
			    EditDynamicObject(playerid, objectid);
				return SendErrorMessage(playerid, "Mobilyayý satýn almak / düzenlemek için içeride olmalýsýnýz.");
		    }
		    
		    if (f_cat == 28 && GetDistanceBetweenPoints(x, y, z, Bx, By, Bz) > Brad)
		    {
		        EditDynamicObject(playerid, objectid);
		        return SendErrorMessage(playerid, "Mobilya kapýnýn 5 metre yakýnýnda olmalýdýr.");
		    }

			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);

		    if (GetPVarInt(playerid, "buy_furniture"))
			{
				switch(pTemp[playerid][pFurnitureB]) {
					case 0: OnPlayerBuyFurniture(building, HouseInfo[building][hID], 0, GetInterior(playerid), GetWorld(playerid), f_slot, furniture_list[f_cat][f_index][frModel], furniture_list[f_cat][f_index][frPrice], furniture_list[f_cat][f_index][frName], x, y, z, f_cat, rx, ry, rz, GetPVarInt(playerid, #texture_0), GetPVarInt(playerid, #texture_1), GetPVarInt(playerid, #texture_2), GetPVarInt(playerid, #texture_3), GetPVarInt(playerid, #texture_4));
					case 1: OnPlayerBuyFurniture(building, BizInfo[building][bizID], 1, GetInterior(playerid), GetWorld(playerid), f_slot, furniture_list[f_cat][f_index][frModel], furniture_list[f_cat][f_index][frPrice], furniture_list[f_cat][f_index][frName], x, y, z, f_cat, rx, ry, rz, GetPVarInt(playerid, #texture_0), GetPVarInt(playerid, #texture_1), GetPVarInt(playerid, #texture_2), GetPVarInt(playerid, #texture_3), GetPVarInt(playerid, #texture_4));
					case 2: OnPlayerBuyFurniture(building, GarageInfo[building][garageID], 2, GetInterior(playerid), GetWorld(playerid), f_slot, furniture_list[f_cat][f_index][frModel], furniture_list[f_cat][f_index][frPrice], furniture_list[f_cat][f_index][frName], x, y, z, f_cat, rx, ry, rz, GetPVarInt(playerid, #texture_0), GetPVarInt(playerid, #texture_1), GetPVarInt(playerid, #texture_2), GetPVarInt(playerid, #texture_3), GetPVarInt(playerid, #texture_4));
				}
				
				GiveCash(playerid, -f_price);			
				SendClientMessageEx(playerid, COLOR_YELLOWG, "[Dekorasyon] \"%s\" adlý mobilya $%s fiyatýna satýn alýndý.", name, FormatNumber(f_price));

                if (GetPVarInt(playerid, "buy_furniture") == 1) ShowFurnitureCategories(playerid);
				else                                           ShowFurnitureList(playerid);

				DelPVarText(playerid);
				return 1;
			}
			else SendSyntaxMessage(playerid, "Mobilyayý düzenlediniz: {C3C3C3}%s.", name);
			
			OnPlayerEditedFurniture(pTemp[playerid][pFurnitureB], building, f_slot, x, y, z, rx, ry, rz);
			DelPVarText(playerid);
		}

		else if (response == EDIT_RESPONSE_CANCEL)
		{
		    if (GetPVarInt(playerid, "buy_furniture"))
		    {
		        //OnPlayerSellFurniture(pTemp[playerid][pFurnitureB], building, GetPVarInt(playerid, "chose_slot")); - íå íóæíî
				
				switch(pTemp[playerid][pFurnitureB]) {
					case 0: DestroyDynamicObject(HFurn[building][f_slot][fObject]);
					case 1: DestroyDynamicObject(BFurn[building][f_slot][fObject]);
					case 2: DestroyDynamicObject(GFurn[building][f_slot][fObject]);
				}
				
		        if (GetPVarInt(playerid, "buy_furniture") == 1) FurnBuingDialog(playerid, f_cat);
				else                                           ShowFurnitureList(playerid);
				
				DelPVarText(playerid);
		        return 1;
		    }

			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
			DelPVarText(playerid);
		}

		else if (response == EDIT_RESPONSE_UPDATE)
		{
		    if (f_cat == 28 && GetDistanceBetweenPoints(x, y, z, Bx, By, Bz) > Brad)
			{
			    CancelEdit(playerid);
				DelPVarText(playerid);
				SendServerMessage(playerid, "Objeyi kapýdan çok uzaða koydun. %d metre civarýnda olmalý. Ýþlem iptal.", Brad);
				//ShowFurnitureList(playerid);
			}
        }
	}
    return 1;
}

Fu_OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT objectid)
{
    if (pTemp[playerid][pFurniture] != -1)
    {
        if (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1) return 1;
    	
    	new building = pTemp[playerid][pFurniture], name[64], slot = -1, type = pTemp[playerid][pFurnitureB];
		if(building == -1 || slot)

		switch(type)
		{
			case 0: {
				for(new i; i < MAX_FURNITURE; i++)
				{
					if (HFurn[building][i][fObject] != objectid || HFurn[building][i][fOn] != 1 || !IsValidDynamicObject(HFurn[building][i][fObject])) continue;
					slot = i;
					break;
				}
				if (slot == -1) return SendErrorMessage(playerid, "Bu mobilya ev için uygun deðil.");

				format(name, sizeof(name), "%s", HFurn[building][slot][fName]);
			} case 1: {
				for(new i; i < MAX_FURNITURE; i++)
				{
					if (BFurn[building][i][fObject] != objectid || BFurn[building][i][fOn] != 1 || !IsValidDynamicObject(BFurn[building][i][fObject])) continue;
					slot = i;
					break;
				}
				if (slot == -1) return SendErrorMessage(playerid, "Bu mobilya ev için uygun deðil.");

				format(name, sizeof(name), "%s", BFurn[building][slot][fName]);
			} case 2: {
				for(new i; i < MAX_FURNITURE; i++)
				{
					if (GFurn[building][i][fObject] != objectid || GFurn[building][i][fOn] != 1 || !IsValidDynamicObject(GFurn[building][i][fObject])) continue;
					slot = i;
					break;
				}
				if (slot == -1) return SendErrorMessage(playerid, "Bu mobilya ev için uygun deðil.");

				format(name, sizeof(name), "%s", GFurn[building][slot][fName]);
			}
		}

		CancelEdit(playerid);
		SetPVarInt(playerid, "chose_slot", slot);
        Dialog_Show(playerid, EditFurniture, DIALOG_STYLE_LIST, name, "Bilgi\nPozisyon deðiþtir\nTexture düzenle\nSat\nÝsim deðiþtir\nKopyala", "Seç", "Geri Dön");
	}
    return 1;
}

Furn_OnPlayerSelect3DMenuBox(playerid, MenuID, boxid, list, boxes)
{
    if (pTemp[playerid][p3DMenu] == MenuID)
    {
        if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) return 1;
    	
    	new building = pTemp[playerid][pFurniture], slot = GetPVarInt(playerid, "chose_slot"), texture = GetPVarInt(playerid, "chose_texture");

		new mes[56];
		format(mes, 56, "~w~Esyanin tasarimini ~g~degistirdin ~w~slot: %i", texture+1);
        InfoMSG(playerid, mes, 4);

     	new tid = (list * boxes) + boxid;

		new furn_type = GetNearBuilding(playerid);

		switch(furn_type) {
			case 0: {
				HFurn[building][slot][fTexture][texture] = tid;

				new query[256];
				mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = %i WHERE `id` = %i", texture, tid, HFurn[building][slot][fID]);
				mysql_tquery(dbHandle, query);

				SetDynamicObjectMaterial(HFurn[building][slot][fObject], texture, ObjectTextures[tid][TModel], ObjectTextures[tid][TXDName], ObjectTextures[tid][TextureName], ObjectTextures[tid][MaterialColor]);
			} case 1: {
				BFurn[building][slot][fTexture][texture] = tid;

				new query[256];
				mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = %i WHERE `id` = %i", texture, tid, BFurn[building][slot][fID]);
				mysql_tquery(dbHandle, query);

				SetDynamicObjectMaterial(BFurn[building][slot][fObject], texture, ObjectTextures[tid][TModel], ObjectTextures[tid][TXDName], ObjectTextures[tid][TextureName], ObjectTextures[tid][MaterialColor]);
			} case 2: {
				GFurn[building][slot][fTexture][texture] = tid;

				new query[256];
				mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = %i WHERE `id` = %i", texture, tid, GFurn[building][slot][fID]);
				mysql_tquery(dbHandle, query);

				SetDynamicObjectMaterial(GFurn[building][slot][fObject], texture, ObjectTextures[tid][TModel], ObjectTextures[tid][TXDName], ObjectTextures[tid][TextureName], ObjectTextures[tid][MaterialColor]);
			}
		}
			
	}
    return 1;
}

ShowFurnitureCategories(playerid)
{
    new str[571] = "1. Kanepeler\n2. Yataklar\n3. Koltuklar, Sandalyeler, Banklar\n4. Masalar\n5. Sehpalar\n6. Aydýnlatmalar\n7. Kulüp ekipmanlarý\n8. Komidin, gardrop, dolaplar\n9. Mutfak aletleri\n10. Ürünler\n11. Çöp\n12. Kýyafetler\n13. Bardaklar, þiþeler\n14. Dinamik kapýlar\n15. Ýç dekorasyon\n16. Silah\n17. Elektronik\n18. Banyo\n";
    strcat(str, "19. Resimler\n20. Bitkiler\n21. Kare duvar\n22. Büyük kare duvar\n23. Kapý giriþi\n24. Pencere açma\n25. Gözlük\n26. Dar duvar\n27. Geniþ duvar\n28. Sütunlar\n29. Sokak");
	
	if (PlayerInfo[playerid][pDrugLabAccess]) strcat(str, "\n30. Uyuþturucu laboratuvarý");

    Dialog_Show(playerid, FurnitureCategories, DIALOG_STYLE_LIST, "{FFFFFF}Liste", str, "Seç", "Ýptal");
	return 1;
}

GetFurnitureIndex(fcat, fid)
{
	for(new i = 0; i < MAX_F_SLOTS; i++) if (furniture_list[fcat][i][frModel] == fid) return i;
	return -1;
}

/*GetFurniturePrice(type, building)
{
	new paycheck;

	switch(type) {
		case 0: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!HFurn[building][i][fID] || !HFurn[building][i][fOn]) continue;
				paycheck += (HFurn[building][i][fMarketPrice] - (HFurn[building][i][fMarketPrice] & 2))  / 2;
			}
		} 
		case 1: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!BFurn[building][i][fID] || !BFurn[building][i][fOn]) continue;
				paycheck += (BFurn[building][i][fMarketPrice] - (BFurn[building][i][fMarketPrice] & 2))  / 2;
			}
		}
		case 2: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!GFurn[building][i][fID] || !GFurn[building][i][fOn]) continue;
				paycheck += (GFurn[building][i][fMarketPrice] - (GFurn[building][i][fMarketPrice] & 2))  / 2;
			}
		}
	}
	return paycheck;
}*/