PlaceBoombox(playerid)
{
	if (BoomboxInfo[playerid][bUsed] != 0)				return SendErrorMessage(playerid, "Birden fazla boombox koyamazsýnýz.");
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)	return SendErrorMessage(playerid, "Boombox buraya yerleþtirilemez.");

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || !BoomboxInfo[i][bUsed]) 	continue;
		if (IsValidDynamicArea(BoomboxInfo[i][bArea]))		return SendErrorMessage(playerid, "Yakýn bir noktada boombox bulunuyor.");
	}

	new id = -1;
	if ((id = GetNearInsideHouse(playerid)) != -1 && HouseInfo[id][hRadioOn])	return SendErrorMessage(playerid, "Radyo zaten evde çalýyor.");
	else if ((id = GetNearInsideBiz(playerid)) != -1 && BizInfo[id][bizRadioOn])	return SendErrorMessage(playerid, "Radyo zaten iþletmede çalýyor.");

	SendSyntaxMessage(playerid, "Bir boombox yerleþtirdiniz, kontrol etmek için H tuþunu kullanýn.");

	GetXYInFrontOfPlayer(playerid, BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ], 1.0);
 	BoomboxInfo[playerid][bInt] = GetInterior(playerid);
  	BoomboxInfo[playerid][bVW] = GetWorld(playerid);
   	BoomboxInfo[playerid][bUsed] = 1;
   	BoomboxInfo[playerid][bUrl] = EOS;
	BoomboxInfo[playerid][bObject] = CreateDynamicObject(2226, BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ]-1.0, 0.0, 0.0, 0.0, BoomboxInfo[playerid][bVW], BoomboxInfo[playerid][bInt], -1, 300.0);
	BoomboxInfo[playerid][bArea] = CreateDynamicSphere(BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ], 50.0, BoomboxInfo[playerid][bVW], BoomboxInfo[playerid][bInt]);
	pTemp[playerid][pBoombox] = playerid;
	StopAudioStreamForPlayer(playerid);
	Iter_Add(boomboxIter, playerid);
	return 1;
}

ShowBoomboxMenu(playerid)
{
	if (BoomboxInfo[playerid][bUsed] == 0 || Boombox_Nearest(playerid) == 0)	return 1;

	Dialog_Show(playerid, BoomBox, DIALOG_STYLE_LIST, "{FFFFFF}Boombox", "Radyo istasyonu deðiþtir\nMüziklerim\nBoombox kapat\nBoombox kaldýrýn", "Seç", "Ýptal");
	return 1;
}

ChangeUrlBoombox(playerid, url[])
{
    if (BoomboxInfo[playerid][bUsed] != 0 && Boombox_Nearest(playerid) != 0)
	{
		format(BoomboxInfo[playerid][bUrl], 156, url);

		new Float:pXaz, Float:pYaz, Float:pZaz;
	    GetPlayerPos(playerid, pXaz, pYaz, pZaz);

		foreach (new i : Player) 
		{
			if (IsPlayerInRangeOfPoint(i, 50.0, pXaz, pXaz, pXaz), !IsPlayerInAnyVehicle(playerid))
			{
				pTemp[i][pBoombox] = playerid;
			    StopAudioStreamForPlayer(i);
			    PlayAudioStreamForPlayer(i, BoomboxInfo[playerid][bUrl], BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ], 50.0, 1);			
			}
		}
		/*
		if(IsPlayerInDynamicArea(i, BoomboxInfo[i][bArea]) && !IsPlayerInAnyVehicle(i))
		{
			pTemp[i][pBoombox] = playerid;
			StopAudioStreamForPlayer(i);
			PlayAudioStreamForPlayer(i, BoomboxInfo[playerid][bUrl], BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ], 50.0, 1);
		}	*/	
		SendServerMessage(playerid, "Müziði deðiþtirdiniz.");
		return 1;
	}
	
	new vehicle = GetPlayerVehicleID(playerid), id;

    if (IsDriver(playerid))
	{
		if (!VehicleInfo[vehicle][carRadio])	return SendErrorMessage(playerid, "Bu araçta radyo bulunmuyor.");

		VehicleInfo[vehicle][carRadioOn] = 1;
	    format(VehicleInfo[vehicle][carRadioURL], 156, url);
		SetPlayerChatBubble(playerid, "radyo istasyonunu deðiþtirir.", COLOR_PURPLE, 20.0, 4000);
	    foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || GetPlayerVehicleID(i) != vehicle) continue;

			StopAudioStreamForPlayer(i);
			PlayAudioStreamForPlayer(i, url);
		}
		return 1;
	}

	if ((id = GetNearInsideHouse(playerid)) != -1 && HouseInfo[id][hOwnerID] == PlayerInfo[playerid][pID])
	{
	    if (!HouseInfo[id][hRadio])	return SendErrorMessage(playerid, "Evinizde radyo bulunmuyor.");

		HouseInfo[id][hRadioOn] = 1;
		format(HouseInfo[id][hRadioURL], 156, url);
        SetPlayerChatBubble(playerid, "radyo istasyonunu deðiþtirir.", COLOR_PURPLE, 20.0, 4000);
	 	foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || GetNearInsideHouse(i) != id) continue;

            StopAudioStreamForPlayer(i);
			PlayAudioStreamForPlayer(i, url);
			pTemp[i][pBoombox_house] = id;
		}
	    return 1;
	}
	else if ((id = GetNearInsideBiz(playerid)) != -1 && BizInfo[id][bizOwnerID] == PlayerInfo[playerid][pID])
	{
	    if (BizInfo[id][bizRadio] == 0)	return SendErrorMessage(playerid, "Ýþletmenizde radyo bulunmuyor.");

		BizInfo[id][bizRadioOn] = 1;
		format(BizInfo[id][bizRadioURL], 156, url);
        SetPlayerChatBubble(playerid, "radyo istasyonunu deðiþtirir.", COLOR_PURPLE, 20.0, 4000);
	 	foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || GetNearInsideBiz(i) != id)	continue;

            StopAudioStreamForPlayer(i);
			PlayAudioStreamForPlayer(i, url);
			pTemp[i][pBoombox_biz] = id;
		}
	    return 1;
	}
	return 1;
}

Destroy_Boombox(playerid)
{
    if (BoomboxInfo[playerid][bUsed] == 0) 			return 1;
	
    BoomboxInfo[playerid][bUsed] = 0;
    
    foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || pTemp[i][pBoombox] != playerid) continue;

		StopAudioStreamForPlayer(i);
	}
    
	if (IsValidDynamicArea(BoomboxInfo[playerid][bArea]))		DestroyDynamicArea(BoomboxInfo[playerid][bArea]);
    if (IsValidDynamicObject(BoomboxInfo[playerid][bObject]))	DestroyDynamicObject(BoomboxInfo[playerid][bObject]);

	Iter_Remove(boomboxIter, playerid);
        
	return 1;
}

Boombox_Nearest(playerid)
{
	return (BoomboxInfo[playerid][bUsed] == 0 || !IsPlayerInRangeOfPoint(playerid, 2.0, BoomboxInfo[playerid][bPosX], BoomboxInfo[playerid][bPosY], BoomboxInfo[playerid][bPosZ]) || GetWorld(playerid) != BoomboxInfo[playerid][bVW] || GetInterior(playerid) != BoomboxInfo[playerid][bInt])?(0):(1);
}

ShowBoomBoxStations(playerid)
{
	return Dialog_Show(playerid, RadioStations, DIALOG_STYLE_LIST, "Tür Seçin", "Pop/Dance/Dubstep\nJazz/Country/Rock\nHip-hop/RnB/Reggae\nMüziklerim\nRadyoyu kapat", "Seç", "Kapat");
}

StopCarBoomBox(vehicle)
{
	if (VehicleInfo[vehicle][carRadioOn] != 1)	return 1;

    VehicleInfo[vehicle][carRadioOn] = 0;

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || GetPlayerVehicleID(i) != vehicle)	continue;

		StopAudioStreamForPlayer(i);
	}
	return 1;
}

StopHouseBoomBox(houseid)
{
	if (HouseInfo[houseid][hRadioOn] != 1)	return 1;

	HouseInfo[houseid][hRadioOn] = 0;
	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || pTemp[i][pBoombox_house] != houseid) continue;

	 	StopAudioStreamForPlayer(i);
		pTemp[i][pBoombox_house] = -1;
	}
	return 1;
}

StopBusinessBoomBox(biz)
{
	if (BizInfo[biz][bizRadioOn] != 1)	return 1;

	BizInfo[biz][bizRadioOn] = 0;

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || pTemp[i][pBoombox_biz] != biz)	continue;

		StopAudioStreamForPlayer(i);
		pTemp[i][pBoombox_biz] = -1;
	}
	return 1;
}