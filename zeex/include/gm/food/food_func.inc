Fo_OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	for(new i; i < MAX_FOOD_STAND; i++)
	{
		if (FoodStand[i][fPickUp] == pickupid)
		{
			CreateLableText(playerid,"~h~~p~TEZGAH~n~~y~\"Cluckin' Bell\"", "~w~~h~Yemek icin ~h~/yemekal~h~~w~ komutunu kullan");
			break;
		}
	}
	return 1;
}

this::LoadDynamicStands()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)
	{
	    print("[Tezgah] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", FoodStand[i][fID]);
	    cache_get_value_int(i, "type", FoodStand[i][fType]);
	    cache_get_value_float(i, "posx", FoodStand[i][fPosX]);
	    cache_get_value_float(i, "posy", FoodStand[i][fPosY]);
	    cache_get_value_float(i, "posz", FoodStand[i][fPosZ]);
	    cache_get_value_float(i, "posrx", FoodStand[i][fPosRX]);
	    cache_get_value_float(i, "posry", FoodStand[i][fPosRY]);
	    cache_get_value_float(i, "posrz", FoodStand[i][fPosRZ]);

	    cache_get_value_int(i, "vw", FoodStand[i][fVW]);
	    cache_get_value_int(i, "interior", FoodStand[i][fInt]);

	    if (FoodStand[i][fType] == 1)
	    {
		    FoodStand[i][fObject] =	CreateDynamicObject(1340, FoodStand[i][fPosX], FoodStand[i][fPosY], FoodStand[i][fPosZ], FoodStand[i][fPosRX], FoodStand[i][fPosRY], FoodStand[i][fPosRZ], FoodStand[i][fVW], FoodStand[i][fInt], -1, 200.0);

		    if (FoodStand[i][fPosRZ] < -50.0)	FoodStand[i][fPosY] += (1.2 * floatcos((-FoodStand[i][fPosRZ]+90), degrees));
			if (FoodStand[i][fPosRZ] < -150.0) 	FoodStand[i][fPosX] += (1.2 * floatsin((-FoodStand[i][fPosRZ]+90), degrees));
			if (FoodStand[i][fPosRZ] >= 0.0) 	FoodStand[i][fPosX] += (1.2 * floatsin((-FoodStand[i][fPosRZ]+90), degrees));
			if (FoodStand[i][fPosRZ] > 50.0) 	FoodStand[i][fPosY] += (1.2 * floatcos((-FoodStand[i][fPosRZ]+90), degrees));
	    }

	    //FoodStand[i][fLabel] = CreateDynamic3DTextLabel(""EMBED_RED"["EMBED_WHITE"Палатка с едой"EMBED_RED"]\n"EMBED_CYAN"/yemekal.", -1, FoodStand[i][fPosX], FoodStand[i][fPosY], FoodStand[i][fPosZ], 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FoodStand[i][fVW], FoodStand[i][fInt], -1, 100.0);
		FoodStand[i][fPickUp] =	CreateDynamicPickup(1239, 1, FoodStand[i][fPosX], FoodStand[i][fPosY], FoodStand[i][fPosZ], FoodStand[i][fVW], FoodStand[i][fInt], -1, 100.0);
	    FoodStand[i][fStandOn] = 1;

	    total++;
	}
	printf("[Tezgah] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

this::OnFoodStandInsert(StandID)
{
	return FoodStand[StandID][fID] = cache_insert_id();
}

AddFoodStandToFile(standid, type, Float:x, Float:y, Float:z, vw, interior)
{
    new query[128 + 128];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `foodstand` (type, posx, posy, posz, vw, interior) VALUES (%i, %f, %f, %f, %i, %i)", type, x, y, z, vw, interior);
	mysql_tquery(dbHandle, query, "OnFoodStandInsert", "d", standid);
	return 1;
}
