CMD:kilit(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");
    
    if (GetNearVehicle(playerid, 2.0) != 0) return pc_cmd_arac(playerid, "kilit");

	new bizid;
	if ((bizid = GetNearOutsideBiz(playerid, 1.5)) == -1) bizid = GetNearInsideBiz(playerid);
	if (bizid != -1)
	{
        if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID] && PlayerInfo[playerid][pWorkOn] != BizInfo[bizid][bizID])	return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);
		if (BizInfo[bizid][bizDDoor] > 0)																						return SendErrorMessage(playerid, "Kapý kýrýlmýþ.");

        if (BizInfo[bizid][bizLocked])
		{
			BizInfo[bizid][bizLocked] = 0;
			GameTextForPlayer(playerid, "~w~MEKAN ~g~ACILDI", 5000, 6);
			PlaySound(playerid, 1145);
			return 1;
		}

		else
		{
			BizInfo[bizid][bizLocked] = 1;
			GameTextForPlayer(playerid, "~w~MEKAN ~r~KILITLENDI", 5000, 6);
			PlaySound(playerid, 1145);
			return 1;
		}
	}

	new id = GetNearOutsideGarage(playerid, 1.5);
	if (id == -1) id = GetNearInsideGarage(playerid);
	if (id != -1)
	{
		if (GarageInfo[id][garageOwner] != PlayerInfo[playerid][pID]
		|| (GarageInfo[id][garageHouse] && HouseInfo[GarageInfo[id][garageHouse]][hID] != PlayerInfo[playerid][pRentKey])
		|| (GarageInfo[id][garageBiz] && BizInfo[GarageInfo[id][garageBiz]][bizID] != PlayerInfo[playerid][pWorkOn]))
			return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);

		GarageInfo[id][garageLocked] = GarageInfo[id][garageLocked]?0:1;

		if (GarageInfo[id][garageLocked]) 	GameTextForPlayer(playerid, "~w~GARAJ ~r~KILITLENDI", 3000, 4);
		else 								GameTextForPlayer(playerid, "~w~GARAJ ~g~ACILDI", 3000, 4);

		new query[60];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `garage` SET `locked`=%i WHERE `id`=%i", 1, GarageInfo[id][garageLocked], GarageInfo[id][garageID]);
		mysql_tquery(dbHandle, query);
		return 1;
	}

	for(new i = 0; i != MAX_ENTRANCE; i++)
	{
	    if (!EntranceInfo[i][eFaction] || !EntranceInfo[i][entranceOn] || !(IsPlayerEntranceOutside(playerid, i) && IsPlayerEntranceInside(playerid, i))) continue;

        if (PlayerInfo[playerid][pFaction] != EntranceInfo[i][eFaction])		return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);

        EntranceInfo[i][eLocked] = (EntranceInfo[i][eLocked]) ? (0) : (1);
        PlaySound(playerid, 1145);

        if (EntranceInfo[i][eLocked])	GameTextForPlayer(playerid, "~w~Kapi ~r~kapatildi", 5000, 6);
		else							GameTextForPlayer(playerid, "~w~Kapi ~g~acildi", 5000, 6);

		break;
	}

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) != -1 && (HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID] || HouseInfo[houseid][hID] == PlayerInfo[playerid][pRentKey]))
	{
	    for(new i = 0; i < MAX_FURNITURE; i++)
		{
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, HFurn[houseid][i][fPosX], HFurn[houseid][i][fPosY], HFurn[houseid][i][fPosZ]) || !HFurn[houseid][i][fOn] || !isHouseDoor(HFurn[houseid][i][fModel]))
   			{
				continue;
			}

			if (HFurn[houseid][i][fOpened])	return SendWarningMessage(playerid, "Ýlk önce kapýyý kapatýn.");

			if (!HFurn[houseid][i][fLocked])
			{
				InfoMSG(playerid, "Kapi ~r~kilitlendi", 3);
				HFurn[houseid][i][fLocked] = 1;
				return 1;
			}

			else
			{
				InfoMSG(playerid, "Kapi ~g~acildi", 3);
				HFurn[houseid][i][fLocked] = 0;
				return 1;
			}
		}
	}

	new biz_id;
	if ((biz_id = GetNearInsideBiz(playerid)) != -1 && (BizInfo[biz_id][bizOwnerID] == PlayerInfo[playerid][pID] || BizInfo[biz_id][bizID] == PlayerInfo[playerid][pWorkOn]))
	{
	    for(new i = 0; i < MAX_FURNITURE; i++)
		{
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, BFurn[biz_id][i][fPosX], BFurn[biz_id][i][fPosY], BFurn[biz_id][i][fPosZ]) || !BFurn[biz_id][i][fOn] || !BFurn[biz_id][i][fModel])
   			{
				continue;
			}

			if (BFurn[biz_id][i][fOpened])	return SendWarningMessage(playerid,"Ýlk önce kapýyý kapatýn.");

			if (!BFurn[biz_id][i][fLocked])
			{
				InfoMSG(playerid, "Kapý ~r~kilitlendi", 3);
				BFurn[biz_id][i][fLocked] = 1;
				return 1;
			}

			else
			{
				InfoMSG(playerid, "Kapi ~g~acildi", 3);
				BFurn[houseid][i][fLocked] = 0;
				return 1;
			}
		}
	}

	new garage = GetNearInsideGarage(playerid);
	if (garage != -1) {
		if (GarageInfo[garage][garageOwner] == PlayerInfo[playerid][pID]
		|| (GarageInfo[garage][garageHouse] && HouseInfo[GarageInfo[garage][garageHouse]][hID] == PlayerInfo[playerid][pRentKey])
		|| (GarageInfo[garage][garageBiz] && BizInfo[GarageInfo[garage][garageBiz]][bizID] == PlayerInfo[playerid][pWorkOn]))
		{
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!IsPlayerInRangeOfPoint(playerid, 2.0, GFurn[garage][i][fPosX], GFurn[garage][i][fPosY], GFurn[garage][i][fPosZ]) || !GFurn[garage][i][fOn] || !GFurn[garage][i][fModel])
				{
					continue;
				}

				if (GFurn[garage][i][fOpened])	return SendWarningMessage(playerid,"Ýlk önce kapýyý kapatýn.");

				if (!GFurn[garage][i][fLocked])
				{
					InfoMSG(playerid, "Kapi ~r~kilitlendi", 3);
					GFurn[garage][i][fLocked] = 1;
					return 1;
				}

				else
				{
					InfoMSG(playerid, "Kapi ~g~acildi", 3);
					GFurn[houseid][i][fLocked] = 0;
					return 1;
				}
			}
		}
	}

	if ((houseid = GetNearHouse(playerid, 15.0, 1.2)) != -1)
	{
		if (HouseInfo[houseid][hDDoor] > 0) return SendWarningMessage(playerid, "Kapý kýrýk.");

		if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID] && HouseInfo[houseid][hID] != PlayerInfo[playerid][pRentKey])
		    return GameTextForPlayer(playerid, "~r~ANAHTARINIZ BULUNMUYOR!", 5000, 6);

        if (HouseInfo[houseid][hLocked] == 1)
		{
			HouseInfo[houseid][hLocked] = 0;
			GameTextForPlayer(playerid, "~w~Kapi ~g~acildi", 5000, 3);
			PlaySound(playerid, 1145);
            DestroyDynamicPickup(HouseInfo[houseid][hPickup]);
            HouseInfo[houseid][hPickup] = CreateDynamicPickup(1273, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			return 1;
		}
		if (HouseInfo[houseid][hLocked] == 0)
		{
			HouseInfo[houseid][hLocked] = 1;
			GameTextForPlayer(playerid, "~w~Kapi ~r~kapatildi", 5000, 3);
			PlaySound(playerid, 1145);
            DestroyDynamicPickup(HouseInfo[houseid][hPickup]);
            HouseInfo[houseid][hPickup] = CreateDynamicPickup(19522, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
			return 1;
		}
	}

	return 1;
}

alias:mulklerim("evlerim", "isyerlerim", "mekanlarim");
CMD:mulklerim(playerid, params[])
{
	return ShowProperty(playerid, playerid);
}

alias:ozelmodel("ozelskin", "donatorskin");
CMD:ozelmodel(playerid)
{

	new sorgu[65];
	if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) return SendErrorMessage(playerid, "Kýyafet giymek için uygun noktada deðilsin. (Interiorlarda giyebilirsin)");
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT * FROM donator_skinler WHERE sahip = '%d'", PlayerInfo[playerid][pAccID]);
	mysql_query(dbHandle, sorgu);
	if(!cache_num_rows()) return SendErrorMessage(playerid, "Herhangi bir kýyafetiniz bulunmuyor.");
	new string[1000], skinid;
	for(new i = 0; i < cache_num_rows(); i++) cache_get_value_int(i, "skinid", skinid), format(string, sizeof string, "%s%d\t\n", string, skinid);
	Dialog_Show(playerid, DIALOG_KIYAFETDOLAP, DIALOG_STYLE_PREVIEW_MODEL, "> Ozel Modellerim", string, "Sec", "Kapat");
	return 1;
}

CMD:kiyafetlerim(playerid, params[])
{
    if (PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Bu komutu iþbaþýndayken kullanamazsýn.");

    new id, used;

	if ((id = GetNearInsideHouse(playerid)) != -1)
	{
		if (HouseInfo[id][hOwnerID] != PlayerInfo[playerid][pID] && PlayerInfo[playerid][pRentKey] != HouseInfo[id][hID])	return SendErrorMessage(playerid, "Bu ev size ait deðil veya kiracýsý deðilsiniz.");
		if (!HouseInfo[id][hCupboard])																						return SendErrorMessage(playerid, "Bu evde gardrop bulunmuyor.");

		used = 1;
	}

	if (!used && (id = GetNearInsideBiz(playerid)) != -1)
	{
		if (BizInfo[id][bizType] != BIZ_CLOTHES)	return SendErrorMessage(playerid, "Herhangi bir kýyafet dükkanýnda deðilsiniz.");

		used = 1;
	}

	if (!used) return SendErrorMessage(playerid, "Bu komutu kullanmak için kýyafet maðazasýnda veya evinizde olmalýsýnýz.");

	new mes[128];

	for(new i; i != 3; i++)
	{
 		if (!PlayerInfo[playerid][pTog][i])	strcat(mes, "\n[Yerleþtir]");
   		else								format(mes, sizeof(mes), "%s\n[Kýyafet seçimi #%i]", mes, PlayerInfo[playerid][pTog][i]);
	}

	Dialog_Show(playerid, EditClothes, DIALOG_STYLE_LIST, "Slot seçiniz...", mes, "Seç", "Ýptal");
	return 1;
}

alias:kapitikla("kapical", "kapiyatikla", "kapiyavur");
CMD:kapitikla(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken kapýya vuramazsýn.");

	for(new i = 0; i < MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID] || !IsPlayerOutsideHouse(playerid, i, 2.0)) continue;

		foreach(new p : Player)
		{
		    if (!IsPlayerInsideHouse(p, i)) continue;

  			SendClientMessageEx(p, COLOR_PURPLE, "* [Kapý] Birisi kapýyý týklatýyor! (( %s ))", GetNameWithMask(playerid));
		}

		pc_cmd_me(playerid, "evin kapýsýný çalar.");
		return 1;
	}

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (!BizInfo[i][bizID] || !IsPlayerBizOutside(playerid, i, 2.0)) continue;

		foreach(new p : Player)
		{
		    if (!IsPlayerBizInside(p, i)) continue;

			SendClientMessageEx(p, COLOR_PURPLE, "* [Kapý] Birisi kapýyý týklatýyor! (( %s ))", GetNameWithMask(playerid));
		}

		pc_cmd_me(playerid, "mekanýn kapýsýný çalar.");
		return 1;
	}
	return 1;
}
