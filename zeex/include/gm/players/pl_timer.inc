this::PlayerTimer()
{
    new string[164], cont;
	foreach(new i : Player)
	{
	    cont = Login_PlayerTimer(i);
		if (!cont) continue;

    	/*if (pTemp[i][pPayphone] && 0 == IsPlayerAtPayphone(i, pTemp[i][pPayphone]))
		{
			PayphoneInfo[pTemp[i][pPayphone]][phUsed] = INVALID_PLAYER_ID;
			pTemp[i][pPayphone] = -1;
        }*/

		Death_PlayerTimer(i);
		Graffity_PlayerTimer(i);
        House_PlayerTimer(i);
		CheckValidTextDraws(i);
		
		if (!(PlayerInfo[i][pSettings] & togHUD) && PlayerInfo[i][pSettings] & yesMHUD)	SyncHudTextDraw(i);
		else if (!(PlayerInfo[i][pSettings] & yesMHUD) && !(PlayerInfo[i][pSettings] & togHUD))	SyncHudTextDrawModern(i);		
		
		if (StaffInfo[i][sSpecID] != INVALID_PLAYER_ID) SyncSpectatingPanel(i);

		//if (!IsPlayerAFK(i)) Fire_Check(i);

/*
        if(IsPlayerFalling(i) && GetPlayerVirtualWorld(i) > 0 && GetNearHouse(i) != -1 || GetNearBiz(i) != -1)
		{
            new houseid = pTemp[i][pHouseEntered];
		    new bizid = pTemp[i][pBizEntered];

			if(bizid == -1 || houseid == -1) houseid = GetNearInsideHouse(i, 100.0), bizid = GetNearInsideBiz(i, 100.0);

			if(bizid == -1 || houseid == -1) return 0;

			if(GetPlayerDistanceToPointEx(i, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY], HouseInfo[houseid][hExitZ]) > 30.0)
                BugResolverFalling(i);			

			else if(GetPlayerDistanceToPointEx(i, BizInfo[bizid][bizExitX], BizInfo[bizid][bizExitY], BizInfo[bizid][bizExitZ]) > 30.0)
                BugResolverFalling(i);

			else return 0;	
		}
		else return 0;
*/	

        if(IsPlayerFalling(i) && GetPlayerVirtualWorld(i) == 0 && GetPlayerInterior(i) == 0)
		{
            new Float:oXa, Float:oYa, Float:oZa;
			GetPlayerPos(i, oXa, oYa, oZa);
			if(oZa < -20.0)
			{
		        new first_login = randomEx(1,5);

		        switch(first_login)
		        {
			        case 1:
			        {
                        SetWorld(i, 0);
				        SetInterior(i, 0);
				        SetPlayerPosEx(i,426.2177,-784.6637,43.9577);
			        }
			        case 2:
			        {
                        SetWorld(i, 0);
				        SetInterior(i, 0);
				        SetPlayerPosEx(i,681.7299,-669.9059,35.0301);
			        }
			        case 3:
			        {
                        SetWorld(i, 0);
				        SetInterior(i, 0);
				        SetPlayerPosEx(i,615.5635,-358.8992,25.0695);
			        } 
			        case 4:
			        {
                        SetWorld(i, 0);
				        SetInterior(i, 0);
				        SetPlayerPosEx(i,653.1493,-1083.1321,35.4389);
			        }
			        case 5:
			        {
                        SetWorld(i, 0);
				        SetInterior(i, 0);
				        SetPlayerPosEx(i,726.3694,-893.4230,35.0667);
			        }									
		       }
			   SendServerMessage(i, "Blaze Guard senin düþtüðünü anladý ve spawn bölgesine gönderdi.");				
			}
		}

		if (maskOn{i}) {
			new nametag[128], Float:armour;
            AntiCheatGetArmour(i, armour);

            if (armour > 1.0)
            {
                format(nametag, sizeof(nametag), "%s (%i)\n{FFFFFF}%s\n{FF0000}%s", PlayerInfo[i][pMaskname], i, GetArmorDots(i), GetHealthDots(i));
            }
            else
            {
                format(nametag, sizeof(nametag), "%s (%i)\n{FF0000}%s", PlayerInfo[i][pMaskname], i, GetHealthDots(i));
            }
            UpdateDynamic3DTextLabelText(cNametag[i], 0xFFFFFFFF, nametag);
		}

		if(Silah_Bilgi[i][sMermiTD_UpdateTime] < gettime()) {
			Silah_Bilgi[i][sMermiTD_UpdateTime] = gettime();
			new BWH_weaponid = GetPlayerWeapon(i);
			if(BWH_weaponid >= 0) {
				new slot = SilahSlotuBul[BWH_weaponid], BWH_ammo_str[7];
				format(BWH_ammo_str, sizeof(BWH_ammo_str), " ");
				if(Silah_Bilgi[i][sSilahID][slot] == BWH_weaponid) {
					if((BWH_weaponid > 21 && BWH_weaponid < 35) || BWH_weaponid == 38) {
						if(Silah_Bilgi[i][sMermi][slot] > 0) format(BWH_ammo_str, sizeof(BWH_ammo_str), "%d", Silah_Bilgi[i][sMermi][slot]);
					}
				}
				PlayerTextDrawSetString(i, Silah_Bilgi[i][MermiTD], BWH_ammo_str);
			}
		}

		if(GetTickCount() - PlayerInfo[i][pSilahTick] > 500 && PlayerInfo[i][pLevel] > 2 && !pTemp[i][pPizzaBoy] && !pTemp[i][pTruckerOn] && PlayerInfo[i][pSilahSistemi] == 1) {
			PlayerInfo[i][pUzerindekiSilah] = GetPlayerWeapon(i);
			new weaponid, ammo, objectslot, count, index;
			for(new ix = 3; ix < 7; ix++) {
				BWH_GetPlayerWeaponData(i, ix, weaponid, ammo);
				index = weaponid - 22;
				if(weaponid && ammo && !WeaponSettings[i][index][Hidden] && IsWeaponWearable(weaponid) && EditingWeapon[i] != weaponid) {
					objectslot = GetWeaponObjectSlot(weaponid);
					if(GetPlayerWeapon(i) != weaponid) SetPlayerAttachedObject(i, objectslot, GetWeaponModelEx(weaponid), WeaponSettings[i][index][Bone], WeaponSettings[i][index][Position][0], WeaponSettings[i][index][Position][1], WeaponSettings[i][index][Position][2], WeaponSettings[i][index][Position][3], WeaponSettings[i][index][Position][4], WeaponSettings[i][index][Position][5], 1.0, 1.0, 1.0);
					else if(IsPlayerAttachedObjectSlotUsed(i, objectslot)) RemovePlayerAttachedObject(i, objectslot);
				}
			}
			for (new ix = 6; ix <= 9; ix++) if(IsPlayerAttachedObjectSlotUsed(i, ix)) {
				count = 0;
				for (new j = 22; j <= 34; j++) if(AC_PlayerHasWeapon(i, j) && GetWeaponObjectSlot(j) == ix) count++;
				if(!count) RemovePlayerAttachedObject(i, ix);
			}
			PlayerInfo[i][pSilahTick] = GetTickCount();
		}

		if(GetPlayerMoney(i) != PlayerInfo[i][pCash]) 
		{
	        ResetPlayerMoney(i);
	        GivePlayerMoney(i, PlayerInfo[i][pCash]);			
		}

		if (GetPVarInt(i, #LableText) > 0)
		{
			SetPVarInt(i, #LableText, GetPVarInt(i, #LableText)-1);

			if (GetPVarInt(i, #LableText) == 0)
			{
				PlayerTextDrawHide(i, PlayerText:mulkbilgi[i]);
				PlayerTextDrawHide(i, PlayerText:mulktext[i][0]);
				PlayerTextDrawHide(i, PlayerText:mulktext[i][1]);
				DeletePVar(i, #LableText);
			}
		}

		//
        if (pTemp[i][pBoombox_house] != -1 && IsPlayerInsideHouse(i, pTemp[i][pBoombox_house], 25.0) == 0)
        {
            pTemp[i][pBoombox_house] = -1;
            StopAudioStreamForPlayer(i);
        }

        if (pTemp[i][pBoombox_biz] != -1 && IsPlayerBizInside(i, pTemp[i][pBoombox_biz], 25.0) == 0)
        {
            pTemp[i][pBoombox_biz] = -1;
            StopAudioStreamForPlayer(i);
        }
		
		if(!PlayerInfo[i][pAdmin] && IsPlayerInAnyVehicle(i) && IsPlayerLoggedIn(i)) {
			new vehicleid = GetPlayerVehicleID(i);
			if(vehicleid != pTemp[i][pCarWarpVehicleID] && pTemp[i][pCarWarpTime] > gettime()) 
			{
				SendClientMessageEx(i, COLOR_WHITE, "LIBERTY-AC tarafýndan kalýcý olarak yasaklandýn. Sebep: Vehicle-Hack (#2)");

	            new query[256];
	            mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `block_name`='Blaze Guard', `block_reason` ='Vehicle Troll', `status` = '3' WHERE `id` = '%i'", PlayerInfo[i][pID]);
	            mysql_tquery(dbHandle, query);

	            new mes[128];
                format(mes, sizeof(mes), "(( %s adlý karakter Blaze Guard tarafýndan yasaklandý. Sebep: Hile ))", GetNameEx(i));
	            SendClientMessageByAdmin(COLOUR_TOMATO, mes);

				KickEx(i);
				return 1;
			}
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER && pTemp[i][AntiHileSistemi] != -1 && pTemp[i][AntiHileSistemi] != vehicleid) {
				SendClientMessageEx(i, COLOR_WHITE, "LIBERTY-AC tarafýndan kalýcý olarak yasaklandýn. Sebep: Vehicle-Hack (#1)");

	            new query[256];
	            mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `block_name`='Blaze Guard', `block_reason` ='Vehicle Teleport', `status` = '3' WHERE `id` = '%i'", PlayerInfo[i][pID]);
	            mysql_tquery(dbHandle, query);

	            new mes[128];
                format(mes, sizeof(mes), "(( %s adlý karakter Blaze Guard tarafýndan yasaklandý. Sebep: Hile ))", GetNameEx(i));
	            SendClientMessageByAdmin(COLOUR_TOMATO, mes);

				KickEx(i);
			}

			if (!VehicleInfo[vehicleid][carEngineOn] && GetSpeed(i) > 30 && IsDriver(i))
			{
				SendAdmMessage("%s [/spec %d] adlý oyuncu %d ID'li aracý motoru kapalý sürüyor olabilir.", GetNameEx(i), i, vehicleid);
			}
	        
		}
		
        if (GetPVarInt(i, #try_engine))
		{
		    if (HoldingKey(i, KEY_SPRINT) == 0)
		    {
		        SetPVarInt(i, #try_engine, GetPVarInt(i, #try_engine)-1);
		        if (GetPVarInt(i, #try_engine) == 0)
		        {
		        	DeletePVar(i, #try_engine);
		        	GameTextForPlayer(i, "~r~CALISMIYOR! MOTOR COK HASARLI", 1000, 4);
				}
			}
		    else
		    {
		        PlaySound(i, 11200);
		        SetPVarInt(i, #try_engine, GetPVarInt(i, #try_engine)+1);
		        if (GetPVarInt(i, #try_engine) == 12)
		        {
		            DeletePVar(i, #try_engine);
		            VehicleEngine(GetPlayerVehicleID(i), true);
		            GameTextForPlayer(i, "~w~MOTOR ~g~CALISTI", 2500, 4);
		        }
		    }
		}

        if (pTemp[i][pFishTime])
		{
		    OnPlayAnim(i, "SWORD", "SWORD_IDLE", 4.1, 1, 0, 0, 1, 0);
		    pTemp[i][pFishTime]--;
		    if (pTemp[i][pFishTime] == 0)
		    {
		        StopPlayerAnims(i);
		        if (random(2) == 0)
				{
				    new randlb = randomEx(10, 30),
						rand = random(sizeof(fish_names));

					SM2(i, "%s aðýrlýðýna balýk yakaladýnýz: %i pound.", fish_names[rand], randlb);
					if (PlayerInfo[i][pFishCount] + randlb <= 1000)
						PlayerInfo[i][pFishCount] += randlb;
					else
					    PlayerInfo[i][pFishCount] = 1000;
				}
				else
					SM1(i, "Oltanýza hiçbir þey takýlmadý.");
		    }
		}

		Job_SecondTimer(i);

		if (pTemp[i][pTracePlayer] != INVALID_PLAYER_ID)	TracePlayer(i);


		for(new pp = 0; pp < MAX_PAYPHONES; pp++)
		{
			if (PayphoneInfo[pp][phState] == PAYPHONE_STATE_RINGING && PayphoneInfo[pp][phRing] < 59 && IsPlayerLogged(PayphoneInfo[pp][phCaller]))
			{
				PayphoneInfo[pp][phRing]++;
				if (PayphoneInfo[pp][phRing] % 5 == 0) Update_Payphone(pp);
			}
			else if (PayphoneInfo[pp][phState] == PAYPHONE_STATE_RINGING)
			{
				PayphoneInfo[pp][phState] = PAYPHONE_STATE_NONE;
				PayphoneInfo[pp][phRing] = 0;

				Update_Payphone(pp);

				PayphoneInfo[pp][phUsed] = INVALID_PLAYER_ID;
				PayphoneInfo[pp][phCaller] = INVALID_PLAYER_ID;
				PayphoneInfo[pp][phState] = PAYPHONE_STATE_NONE;

				if (IsPlayerLogged(PayphoneInfo[pp][phCaller]))
				{
					SendPhoneMessage(PayphoneInfo[pp][phCaller], "Kiþi cevap vermiyor.");
					HangupCall(PayphoneInfo[pp][phCaller]);
				}
			}
		}

		if (pTemp[i][pPayphone] != -1)
		{
			if (0 == IsPlayerAtPayphone(i, pTemp[i][pPayphone]))
			{
				SendWarningMessage(i, "Ankesörlü telefondan uzaklaþtýnýz.");
				cancelPayphone(i);
			}
        }

		if(0 != IsPlayerPhoneCreated(i))
			Update_Phone(i);

		if(pTemp[i][pCallStatus] == 2 && pTemp[i][pCallLine] != INVALID_PLAYER_ID)
		{
		    pTemp[i][pCallTime]++;
            if(0 != IsPlayerPhoneCreated(i))
            {
				new mes[52];
		    	format(mes, sizeof(mes), "%s~n~%s", pTemp[i][pCallName], ConvertSecond(pTemp[i][pCallTime]));

		    	PlayerTextDrawSetString(i, TD_iphone_name[i], mes);
		    	PlayerTextDrawShow(i, TD_iphone_name[i]);
			}
		}

		if (pTemp[i][pCallStatus] == 2 && (pTemp[i][pCallLine] != INVALID_PLAYER_ID || pTemp[i][pEmergency]))
		{
			if (PlayerInfo[i][pInjured] != 0)
			{
   				SendPhoneMessage(pTemp[i][pCallLine], "Hatta bulunduðunuz kiþi ile baðlantýnýz kesildi.");
   				SendPhoneMessage(i, "Hatta bulunduðunuz kiþi ile baðlantýnýz kesildi.");

				HangupCall(i);
				HangupCall(pTemp[i][pCallLine]);

				return 1;
			}
			if (Payphone_Nearest(i) == -1 && pTemp[i][pPayphone] != -1)
			{
				SendWarningMessage(i, "Ankesörlü telefondan uzaklaþtýnýz.");

				SendPhoneMessage(pTemp[i][pCallLine], "Hatta bulunduðunuz kiþi ile baðlantýnýz kesildi.");
   				SendPhoneMessage(i, "Hatta bulunduðunuz kiþi ile baðlantýnýz kesildi.");

				HangupCall(i);
				HangupCall(pTemp[i][pCallLine]);

				return 1;
			}


			new mes[52];

			if (pTemp[i][pPayphone] != -1)
			{
				format(mes, sizeof(mes), "%s", ConvertSecond(pTemp[i][pCallTime]));
				PlayerTextDrawSetString(i, PP_Btn[i][0], mes);
			}
		}

/*		if (GetPVarInt(i, #vehicle_info))
		{
		    SetPVarInt(i, #vehicle_info, GetPVarInt(i, #vehicle_info) - 1);
		    if (GetPVarInt(i, #vehicle_info) == 0)
		    {
        		TextDrawHideForPlayer(i, TD_vehicle_info[0]);
	    		TextDrawHideForPlayer(i, TD_vehicle_info[1]);
				PlayerTextDrawHide(i, TD_vehicle_name[i]);
				DeletePVar(i, #vehicle_info);
			}
		}*/

		if (pTemp[i][pFlashTime])
		{
		    pTemp[i][pFlashTime]--;
		    if (pTemp[i][pFlashTime] == 0)
		    {
		    	SetPlayerCurrentTimeAndWeather(i);
				StopPlayerAnims(i);
				UnFreezePlayer(i);
				SetPlayerDrunkLevel(i, 1999);
			}
		}

		if (pTemp[i][pFreezeTime])
		{
		    pTemp[i][pFreezeTime]--;
		    if (pTemp[i][pFreezeTime] == 0) UnFreezePlayer(i);
		}

		if (pTemp[i][pInjuredLegTime]) pTemp[i][pInjuredLegTime]--;

		if (pTemp[i][pTaserTime])
		{
		    if (!PlayerToPoint(1.5, i, PlayerInfo[i][pPosX], PlayerInfo[i][pPosY], PlayerInfo[i][pPosZ]))
		        SetPlayerPosEx(i, PlayerInfo[i][pPosX], PlayerInfo[i][pPosY], PlayerInfo[i][pPosZ]);

		    ApplyAnimation(i, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);

		    pTemp[i][pTaserTime]--;
		    if (0 == pTemp[i][pTaserTime]) SendSpecialMessage(i, "Artýk baygýn deðilsin."), StopPlayerAnims(i);
		}

		if (pTemp[i][pRamType] != 0 && pTemp[i][pRamTime] > 1)
		{
		    if (pTemp[i][pRamType] == 1
				&& ((pTemp[i][pRamHouse] != -1 && 0 == IsPlayerOutsideHouse(i, pTemp[i][pRamHouse], 1.5))
				|| (pTemp[i][pRamBiz] != -1 && 0 == IsPlayerBizOutside(i, pTemp[i][pRamBiz], 1.5))
				|| (pTemp[i][pRamGarage] != -1 && GetNearOutsideGarage(i, 5.0) != pTemp[i][pRamGarage])
				|| (pTemp[i][pRamVeh] != -1 && GetNearVehicle(i, 3.0) != pTemp[i][pRamVeh]))) {

		        SendErrorMessage(i, "Kapýdan çok uzaklaþtýnýz.");
		        pTemp[i][pRamType] = 0;
            	pTemp[i][pRamTime] = 0;
            	StopPlayerAnims(i);
		    }
		    else
	    	{
            	pTemp[i][pRamTime]--;
				format(string, sizeof(string), "KILIT KIRILIYOR ~w~SON ~g~%i ~w~SANIYE", pTemp[i][pRamTime]);
				InfoMSG(i, string, 1);
			}
		}
		else if (pTemp[i][pRamType] == 1 && pTemp[i][pRamTime] == 1)
		{
		    pTemp[i][pRamType] = 0;
            pTemp[i][pRamTime] = 0;

            new location[MAX_ZONE_NAME];
			GetPlayer2DZone(i, location, MAX_ZONE_NAME);

			if (pTemp[i][pRamHouse] != -1 && IsPlayerOutsideHouse(i, pTemp[i][pRamHouse]))
            {
                new houseid = pTemp[i][pRamHouse];
                HouseInfo[houseid][hLocked] = 0;
				GameTextForPlayer(i, "~w~Kapi ~g~acildi", 5000, 6);
				PlaySound(i, 1145);
				StopPlayerAnims(i);
                DestroyDynamicPickup(HouseInfo[houseid][hPickup]);
                HouseInfo[houseid][hPickup] = CreateDynamicPickup(1273, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] evin kapýsý açýldý (/ram) [H_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), HouseInfo[houseid][hID]);
			    insert_log(query, RAM_LOG, 1, PlayerInfo[i][pAccID]);
            }
            else if (pTemp[i][pRamBiz] != -1 && IsPlayerBizOutside(i, pTemp[i][pRamBiz]))
            {
                new bizid = pTemp[i][pRamBiz];
            	BizInfo[bizid][bizLocked] = 0;
				GameTextForPlayer(i, "~w~Kapi ~g~acildi", 5000, 6);
				PlaySound(i, 1145);
				StopPlayerAnims(i);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] iþletme kapýsý açýldý (/ram) [B_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), BizInfo[bizid][bizID]);
			    insert_log(query, RAM_LOG, 2, PlayerInfo[i][pAccID]);
            }
			else if (pTemp[i][pRamGarage] != -1 && GetNearOutsideGarage(i, 5.0) == pTemp[i][pRamGarage])
            {
                new garageid = pTemp[i][pRamGarage];
            	GarageInfo[garageid][garageLocked] = 0;
				GameTextForPlayer(i, "~w~Kapi ~g~acildi", 5000, 6);
				PlaySound(i, 1145);
				StopPlayerAnims(i);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] garaj kapýsý açýldý (/ram) [B_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), GarageInfo[garageid][garageID]);
			    insert_log(query, RAM_LOG, 3, PlayerInfo[i][pAccID]);
            }
			else if (pTemp[i][pRamVeh] != -1 && GetNearVehicle(i, 3.0) == pTemp[i][pRamVeh])
            {
                ToggleVehicleLock(pTemp[i][pRamVeh], false);
				GameTextForPlayer(i, "~w~Kapi ~g~acildi", 5000, 6);
				PlaySound(i, 1145);
				StopPlayerAnims(i);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] araç açýldý (/ram) [B_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), VehicleInfo[pTemp[i][pRamVeh]][carID]);
			    insert_log(query, RAM_LOG, 3, PlayerInfo[i][pAccID]);
            }
			TextDrawHideForPlayer(i, infotxt[i]);
		}
		else if (pTemp[i][pRamType] == 3 && pTemp[i][pRamTime] == 1)
		{
		    pTemp[i][pRamType] = 0;
            pTemp[i][pRamTime] = 0;

            new location[MAX_ZONE_NAME];
			GetPlayer2DZone(i, location, MAX_ZONE_NAME);
			if (pTemp[i][pRamHouse] != -1)
            {
                new houseid = pTemp[i][pRamHouse];
                CreateDynamicExplosion(HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], 12, 5.0, HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt]);
				if (IsValidDynamicObject(pTemp[i][pRamObj]))
				{
					DestroyDynamicObject(pTemp[i][pRamObj]);
					pTemp[i][pRamObj] = INVALID_OBJECT_ID;
				}
				HouseInfo[houseid][hLocked] = 0;
				HouseInfo[houseid][hDDoor] = 2;
                DestroyDynamicPickup(HouseInfo[houseid][hPickup]);
                HouseInfo[houseid][hPickup] = CreateDynamicPickup(1273, 1, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ], HouseInfo[houseid][hPosVW], HouseInfo[houseid][hPosInt], -1, 100.0);
				Save_House(houseid);
				UpdateHouseDoor(houseid);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] evin kapýsýný havaya uçurdu (/ram) [H_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), HouseInfo[houseid][hID]);
			    insert_log(query, RAM_LOG, 3, PlayerInfo[i][pAccID]);
            }
            else if (pTemp[i][pRamBiz] != -1)
            {
                new bizid = pTemp[i][pRamBiz];
            	CreateDynamicExplosion(BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ], 12, 5.0, BizInfo[bizid][bizPosVW], BizInfo[bizid][bizPosInt]);
                if (IsValidDynamicObject(pTemp[i][pRamObj]))
				{
					DestroyDynamicObject(pTemp[i][pRamObj]);
					pTemp[i][pRamObj] = INVALID_OBJECT_ID;
				}
				BizInfo[bizid][bizLocked] = 0;
				BizInfo[bizid][bizDDoor] = 2;
				Save_Business(bizid);
				UpdateBusinessDoor(bizid);

                new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] iþletmenin kapýsýný havaya uçurdu (/ram) [B_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), BizInfo[bizid][bizID]);
			    insert_log(query, RAM_LOG, 4, PlayerInfo[i][pAccID]);
            }
			else if (pTemp[i][pRamGarage] != -1)
            {
                new garageid = pTemp[i][pRamGarage];

            	CreateDynamicExplosion(GarageInfo[garageid][garagePlayer_Enter][0], GarageInfo[garageid][garagePlayer_Enter][1], GarageInfo[garageid][garagePlayer_Enter][2], 12, 5.0, GarageInfo[garageid][garageEnterVW], GarageInfo[garageid][garageEnterInt]);

                if (IsValidDynamicObject(pTemp[i][pRamObj]))
				{
					DestroyDynamicObject(pTemp[i][pRamObj]);
					pTemp[i][pRamObj] = INVALID_OBJECT_ID;
				}

				GarageInfo[garageid][garageLocked] = 0;
				GarageInfo[garageid][garageDDoor] = 2;

				Save_Garage(garageid);
				UpdateGarageDoor(garageid);

                new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] garajýn kapýsýný havaya uçurdu (/ram) [B_MYSQL: %i]",
				GetName(i), PlayerInfo[i][pID], q_GetPlayerIP(i), GarageInfo[garageid][garageID]);
			    insert_log(query, RAM_LOG, 5, PlayerInfo[i][pAccID]);
            }
		}
		//
		new vehicle = GetPlayerVehicleID(i), Float:health;
        AntiCheatGetVehicleHealth(vehicle, health);
		//Vehicle Milliage
		if (GetPlayerState(i) == PLAYER_STATE_DRIVER && VehicleInfo[vehicle][carOwnerID] > 0 && VehicleInfo[vehicle][carOwnerID] != INVALID_PLAYER_ID && !IsPlayerAFK(i) && GetVehicleSpeed(vehicle) > 0)
		    VehicleInfo[vehicle][carMilliage] += GetVehicleSpeed(vehicle)/1.6/1609.344;
  		//Vehicle Milliage
		//Engine off
		if (GetPlayerState(i) == PLAYER_STATE_DRIVER && IsABicycle(vehicle) == 0 && VehicleInfo[vehicle][carEngineOn] && health < 390.0 && random(20) == 0)
		{
			GameTextForPlayer(i, "~w~Arac Motoru ~r~Kapatildi", 2500, 4);
			SendNearbyMessage(Range_Normal, i, COLOR_PURPLE, "* Motor durdu. (( %s [%s] ))", VehicleNames[GetVehicleModel(vehicle)-400], VehicleInfo[vehicle][carPlate]);

			VehicleEngine(vehicle, false);
		}

		//Fire
		if (pTemp[i][pFireTime] > 0)
		{
			if (pTemp[i][pFireTime] == 1)
			{
				GameTextForPlayer(i, "~w~Ates ~r~yaktin~w~!", 1000, 4);
				CreatePlayersFire(i, GetPVarInt(i, #firetype), GetPVarInt(i, #firebuildID));
				StopCreatingPlayersFire(i);
			}
			else if (GetPlayerAnimationIndex(i) == 168)
			{
				pTemp[i][pFireTime]--;

				new mes[32];
				format(mes, sizeof(mes), "~y~Ates yakiliyor ... %i", pTemp[i][pFireTime]);
				GameTextForPlayer(i, mes, 1000, 4);
				ApplyAnimation(i,"BOMBER","BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0, 1);
			}
			else
			{
				StopCreatingPlayersFire(i);
				SendErrorMessage(i, "Ateþ yakýlamadý, tekrar deneyin! ");
			}
		}

		Mechanic_SecondTimer(i);

		//AFK Timer
		pTemp[i][pDarkAFK]++;
		//AFK Timer

		//Driving license exam
		/*if (pTemp[i][pLicenseExam]) {
			if (GetPVarInt(i, #exam_second) > 0 && IsPlayerInAnyVehicle(i))
			{
				UpdateIntVar(i, #exam_second, -1);
				format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~kalan sure: ~y~%i ~w~saniye", GetPVarInt(i, #exam_second));
				GameTextForPlayer(i, string, 1200, 3);
			} else {
				new vehicleid = GetPlayerVehicleID(i);
				SendSyntaxMessage(i, "Sýnavda baþarsýz oldunuz. ");
				pTemp[i][pLicenseExam] = 0;
				DeletePVar(i, #exam_second);
				TogglePlayerAllDynamicRaceCPs(i, false);
				RemovePlayerFromVehicle(i);
				RespawnVehicle(vehicleid);
			}
		}
		*/
		//Driving license exam
		//Gas Station Refueling
		/*if (GetPVarInt(i, "RefuelTime") != 0)
		{
			if (GetPVarInt(i, "RefuelTime") == 1)
			{
				new toFill = 100 - VehicleInfo[vehicle][carFuel];
				UnFreezePlayer(i);
				new toFill = 100 - VehicleInfo[vehicle][carFuel];
				VehicleInfo[vehicle][carFuel] += toFill;
				SM2(i,"ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ $%i.", GetPVarInt(i, "RefuelCost"));
				GiveCash(i, - GetPVarInt(i, "RefuelCost"));
				DeletePVar(i, "RefuelCost");
				DeletePVar(i, "RefuelTime");
			}
			else
			{
				UpdateIntVar(i, "RefuelTime", -1);
				format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~n~~w~Refueling ~b~%i", GetPVarInt(i, "RefuelTime"));
				GameTextForPlayer(i, string, 1050, 3);
			}
		}*/
		//ERROR Message refresher
		/*for(new a = 0; a < 3; a ++)
		{
			if (ErrorInfo[i][a][eExpire] > 1)
			{
				ErrorInfo[i][a][eExpire]--;
				if (ErrorInfo[i][a][eExpire] == 1)
				{
					ErrorInfo[i][a][eExpire] = 0;
					RefreshErrorMsg(i);
				}
			}
		}*/
		//ERROR Message refresher
		//------------------------------------------------------------------
		//Checking jail time
		if (PlayerInfo[i][pMutedTime] > 0)
		{
			PlayerInfo[i][pMutedTime]--;
			if (!PlayerInfo[i][pMutedTime]) SCM(i, COLOR_LIGHTRED, "Chat sizin için tekrar kullanýlabilir.");
		}

		if (PlayerInfo[i][pAJailTime] > 1 && PlayerInfo[i][pAJailed] == 1)
		{
			PlayerInfo[i][pAJailTime]--;
			new mes[56];
			format(mes,sizeof(mes),"~r~kalan sure: ~w~%i saniye",PlayerInfo[i][pAJailTime]);
			GameTextForPlayer(i, mes, 1200, 4);
		}

		else if (PlayerInfo[i][pAJailTime] < 3 && PlayerInfo[i][pAJailed] == 1)
		{
			PlayerInfo[i][pAJailTime] = 0;
			PlayerInfo[i][pAJailed] = 0;
			pTemp[i][pLastLogin] = 0;
			SetPlayerSpawn(i);
			GameTextForPlayer(i,"~w~Artik ~g~ozgursun~w~!",5000,1);
		}


		//Checking isolate time
		if (PlayerInfo[i][pIsolateTime] > 1) PlayerInfo[i][pIsolateTime]--;
		else if (PlayerInfo[i][pIsolateTime] == 1)
		{
		    PlayerInfo[i][pIsolateTime] = 0;
		    PutPlayerInPrison(i);
		}
		//Checking jail time
		if (PlayerInfo[i][pJailTime] > 1 && 0 == PlayerInfo[i][pIsolateTime] && 0 == PlayerInfo[i][pAJailTime]) PlayerInfo[i][pJailTime]--;
		else if (PlayerInfo[i][pJailTime] == 1)
		{
		    if (PlayerInfo[i][pJailed] == PALOMINO_JAIL)
		        SetPlayerPosEx(i, 785.9385,-868.3475,35.3712);
			/*else if (PlayerInfo[i][pJailed] == LSPD_JAIL)
				SetPlayerPosEx(i, 1552.4921,-1675.6072,16.1953);*/
			else if (PlayerInfo[i][pJailed] == PRISON_JAIL)
				SetPlayerPosEx(i, 785.9385,-868.3475,35.3712);
			/*else if (PlayerInfo[i][pJailed] == SASD_JAIL)
				SetPlayerPosEx(i, 631.0485,-571.7219,16.3359);*/

			SetWorld(i, 0);
			SetInterior(i, 0);

			PlayerInfo[i][pIsolateTime] = 0;
			PlayerInfo[i][pJailTime] = 0;
			PlayerInfo[i][pJailed] = 0;
			if (IsValidDynamic3DTextLabel(PrisonLabel[i]))
			{
				DestroyDynamic3DTextLabel(PrisonLabel[i]);
		        PrisonLabel[i] = Text3D:INVALID_3DTEXT_ID;
			}
			GameTextForPlayer(i,"~g~Hapis suren bitti~n~~w~Kanunlara uyman dilegiyle!",5000,1);
		}
		//Checking jail time
		if (pTemp[i][pInjuredTime])
		{
			pTemp[i][pInjuredTime]--;

			if (0 == pTemp[i][pInjuredTime])
			{
				if (PlayerInfo[i][pInjured] == 1) SendHelpMessage(i, "Yerden kalkmak için: \"/tedaviol\"");
				if (PlayerInfo[i][pInjured] == 2) SendHelpMessage(i, "Yerden kalkmak için: \"/tedaviol\"");
				if (PlayerInfo[i][pInjured] == 3) {
					PlayerInfo[i][pInjured] = 0;
					StopPlayerAnims(i);
					UnFreezePlayer(i);
					SM1(i, "Artýk yaralý deðilsiniz.");
				}
			}
		}

		//Info TextDraw Exire
		if (infotxt_expire{i} > 0)
		{
			infotxt_expire{i}--;
			if (infotxt_expire{i} == 1)
			{
				TextDrawHideForPlayer(i, infotxt[i]);
				infotxt_expire{i} = 0;
			}
		}
		//Info TextDraw Exire

		if (!IsPlayerInAnyVehicle(i)) {
			if (ATM_Nearest(i) != -1) {
				InfoMSG(i, "ATM kullanmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/atm~w~ komutunu kullanin.", 2);
			}
			/*else if (Payphone_Nearest(i) != -1) {
				InfoMSG(i, "Ankesorlu telefonu kullanmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/ankesorlutelefon~w~ komutunu kullanin.", 2);
			}*/
			else if (Trash_Nearest(i, 2.0) != -1 && PlayerInfo[i][pJob] == JOB_TRASHMASTER && pTemp[i][pJob] && !HasTrash[i]) {
				InfoMSG(i, "Coplugu kullanmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/copkutusu~w~ komutunu kullanin.", 2);
			}
		} else if (IsPlayerInAnyVehicle(i)) {
			if (Toll_Nearest(i) != -1) {
				InfoMSG(i, "Giseden gecmek icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/gise~w~ komutunu kullanin.", 2);
			}
			else if (GetNearGarage(i) != -1) {
				InfoMSG(i, "Garaja girmek icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/giris~w~ komutunu kullanin.", 2);
			}
			else if (ModShop_Nearest(i) != -1 || PAS_Nearest(i) != -1) {
				InfoMSG(i, "Menuyu acmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/giris~w~ komutunu kullanin", 2);
			}
			else if (AZC_Nearest(i) != -1) {
				if (!GetPVarInt(i, #UsePump)) InfoMSG(i, "Yakit doldurmayi baslatmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/benzin~w~ komutunu kullanin.", 2);
				else InfoMSG(i, "Yakit doldurmayi durdurmak icin ~y~'~k~~GROUP_CONTROL_BWD~'~w~ tusuna basin veya ~y~/benzin~w~ komutunu kullanin.", 1);
			}
		}



		if (JackingEngine[i] > 1)
		{
		    if (!IsPlayerInAnyVehicle(i) || VehicleInfo[GetPlayerVehicleID(i)][carEngineOn]) StopJackingEngine(i);
		    else
		    {
				JackingEngine[i]--;
				format(string, sizeof(string), "~y~/DUZKONTAK~w~ <SIFRELENMIS KELIME>~n~~r~SIFRELENMIS~w~ KOD: ~r~'~w~%s~r~'~n~~w~KALAN ~y~%i~w~ SANIYE", UnscrambleInfo[pTemp[i][pUnscrambleID]][eScrambledWord], JackingEngine[i]);
				InfoMSG(i, string, 2);
			}
		}
		else if (JackingEngine[i] == 1) pc_cmd_duzkontak(i, "");

		if (JackingLock[i] > 1)
		{
			if (pTemp[i][JackingType] == 1) {

				if (pTemp[i][JackingWarnings] >= 5)	return StopJackingLock(i);
				if (!CheckHanditem(i,18634))			return StopJackingLock(i);

				if (!IsPlayerInFrontVDoor(i, JackingVehicle[i])) {
					InfoMSG(i, "COK ~r~UZAKSIN~w~, GERI DON!", 3);
					return pTemp[i][JackingWarnings]++;
				}
			} else if (pTemp[i][JackingType] == 3 || pTemp[i][JackingType] == 4) {
				if (pTemp[i][JackingWarnings] >= 5)				 		  return StopBreakingLock(i);
				if (pTemp[i][JackingType] == 4 && !CheckHanditem(i,18634)) return StopBreakingLock(i);

				if (!IsPlayerOutsideHouse(i, BreakingHouse[i], 1.5)) {
					InfoMSG(i, "COK ~r~UZAKSIN~w~, GERI DON!", 3);
					return pTemp[i][JackingWarnings]++;
				}
			}
                else if (pTemp[i][JackingType] == 5 || pTemp[i][JackingType] == 6) {
				if (pTemp[i][JackingWarnings] >= 5)				 		  return StopStealing(i);
				if (pTemp[i][JackingType] == 6 && !CheckHanditem(i,18634)) return StopStealing(i);

				if (!IsPlayerInsideHouse(i, StealingHouse[i], 50.0)) {
					InfoMSG(i, "COK ~r~UZAKSIN~w~, GERI DON!", 3);
					return pTemp[i][JackingWarnings]++;
				}
			}			
			else return 1;

			if (IsPlayerCrouching(i) == false && pTemp[i][JackingType] != 5 && pTemp[i][JackingType] != 6){
				InfoMSG(i, "~r~EGILMEK~w~ ZORUNDASIN!", 2);
				return pTemp[i][JackingWarnings]++;
			}

		    if (!IsPlayerAFK(i))
		    {
				pTemp[i][JackingWarnings] = 0;
				JackingLock[i]--;

				if (pTemp[i][JackingType] == 2 || pTemp[i][JackingType] == 1)		   format(string, sizeof(string), "ARAC KAPISINI KIRIYORSUNUZ ~y~%i~w~ SANIYE", JackingLock[i]);
				else if (pTemp[i][JackingType] == 3 || pTemp[i][JackingType] == 4) format(string, sizeof(string), "EV KAPISINI KIRIYORSUNUZ ~y~%i~w~ SANIYE", JackingLock[i]);
				else if (pTemp[i][JackingType] == 5 || pTemp[i][JackingType] == 6) format(string, sizeof(string), "SOYGUN YAPILIYOR ~y~%i~w~ SANIYE", JackingLock[i]);
				InfoMSG(i, string, 2);
			}
		}
		else if (JackingLock[i] == 1)
		{
			if (pTemp[i][JackingType] == 2 || pTemp[i][JackingType] == 1)
			{
				if (IsValidVehicle(JackingVehicle[i])) {
					ToggleVehicleLock(JackingVehicle[i], false);
					PlaySound(i, 1145);
					InfoMSG(i, "ARAC KAPISI ~g~KIRILDI~w~!", 3);
					SendServerMessage(i, "Araç kapýsýný kýrdýnýz.");
					AlarmOn(JackingVehicle[i]);

					StopJackingLock(i, 0);
				}
			}
			else if (pTemp[i][JackingType] == 5 || pTemp[i][JackingType] == 6)
			{
				PlaySound(i, 1145);
				InfoMSG(i, "EV SOYGUNU ~g~SONA ERDI~w~!", 3);
				SendServerMessage(i, "Ev soygunu tamamlandý. Çuvalý araca /cuval ile býrakýn. Envanterinize eþyalar eklendi.");
				SendServerMessage(i, "Çalýntý ev eþyalarýný pawnshop aracýlýðýyla satabilirsin. (/gps)");
				HouseAlarm(StealingHouse[i], true);

				PlayerInfo[i][pCalintiEvEsya]++;

				pc_cmd_liftup(i, "");
                SetPlayerAttachedObject(i, ATTACH_HANDS, 2060, 5, 0.002953, 0.469660, -0.009797, 269.851104, 88.443557, 0.000000, 0.804894, 1.000000, 0.822361);
  	            SetPlayerSpecialAction(i, SPECIAL_ACTION_CARRY);

				JackingLock[i] = 0;
				StealingHouse[i] = 0;
				pTemp[i][JackingType] = 0;
				pTemp[i][JackingWarnings] = 0;				
			} 
			else {
				HouseInfo[BreakingHouse[i]][hLocked] = 0;
				PlaySound(i, 1145);
				InfoMSG(i, "EV KAPISI ~g~KIRILDI~w~!", 3);
				SendServerMessage(i, "Ev kapýsýný kýrdýnýz.");
				HouseAlarm(BreakingHouse[i], true);

				JackingLock[i] = 0;
				BreakingHouse[i] = 0;
				pTemp[i][JackingType] = 0;
				pTemp[i][JackingWarnings] = 0;
			}
		}

		if (VehicleInfo[JackingVehicle[i]][ePhysicalAttack] && GetPlayerState(i) == PLAYER_STATE_ONFOOT)
	    {
			if (!IsValidVehicle(JackingVehicle[i]))				 	return StopJackingLock(i);
			if (VehicleInfo[JackingVehicle[i]][carLocked] == 0)  	return StopJackingLock(i);
			if (IsPlayerInAnyVehicle(i))							return StopJackingLock(i);

			if (IsValidVehicle(JackingVehicle[i]))
			{
				new Float:ccX, Float:ccY, Float:ccZ;
				GetVehiclePos(JackingVehicle[i], ccX, ccY, ccZ);

				if (GetVehicleDriver(JackingVehicle[i]) != -1 || !IsPlayerInRangeOfPoint(i, 2.5, ccX, ccY, ccZ))
				{
					InfoMSG(i, "COK ~r~UZAKSIN~w~, GERI DON!", 3);
					pTemp[i][JackingWarnings]++;

					if (pTemp[i][JackingWarnings] >= 5) return StopJackingLock(i);
				} else pTemp[i][JackingWarnings] = 0;
			}
			else return StopJackingLock(i);
		}

		if (PlayerInfo[i][MissionTarget][0] != INVALID_VEHICLE_ID && PlayerInfo[i][InMission] == CARJACKER_DELIVER)
		{
			if (!IsValidVehicle(PlayerInfo[i][MissionTarget][0]))	return StopJackingLock(i);
		    PlayerInfo[i][MissionTime] --;

		    new time[64];
			format(time, sizeof(time), "~r~ARAC PARCALANIYOR~n~~w~KALAN ~y~%d~w~ SANIYE", PlayerInfo[i][MissionTime]);
			InfoMSG(i, time, 2);

			new lights, doors, panels, tires;

			GetVehicleDamageStatus(PlayerInfo[i][MissionTarget][0], panels, doors, lights, tires);
			if (PlayerInfo[i][MissionTime] <= 0)
			{
			    PlayerInfo[i][MissionReward] = CJ_MissionReward(PlayerInfo[i][MissionTarget][0]); // temp reward
			    UpdateVehicleDamageStatus(PlayerInfo[i][MissionTarget][0], 53674035, 33686020, 5, 15);
			    PlayerInfo[i][InMission] = CARJACKER_DROPOFF;
				PlayerInfo[i][MissionTime] = 0;

				new idx = PlayerInfo[i][MissionTarget][1],
					Float:persent = float(chopshop_data[idx][chopshop_procent])*float(PlayerInfo[i][MissionReward])/100.0;

				PlayerInfo[i][MissionReward] -= floatround(persent);

				chopshop_data[idx][chopshop_money] += floatround(persent);
				chopshop_data[idx][chopshop_vehs]++;

				SQL_SetInteger("chopshop", "money", chopshop_data[idx][chopshop_money], chopshop_data[idx][chopshop_id]);
				SQL_SetInteger("chopshop", "vehicles", chopshop_data[idx][chopshop_vehs], chopshop_data[idx][chopshop_id]);

			    InfoMSG(i, "SIMDI ~w~ARACTAN KURTULUN.~n~LUTFEN DIKKAT EDIN VE UZAK BIR YERDE ~y~GIZLENIN~w~, ARDINDAN ~y~/aracibirak ~w~KOMUTUNU KULLANIN ~n~~y~/gorevibitir ~w~- YAZARAK GOREVI DURDURUN, ~r~PARA ALMAZSINIZ~n~[[ARACI YOK EDERSENIZ CEZALANDIRILIRSINIZ]]", 15);

				new engine,alarm,bonnet,boot,objective;
				GetVehicleParamsEx(GetPlayerVehicleID(i), engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(GetPlayerVehicleID(i), VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);

				SendHelpMessage(i, "Araç parçalamasý bitti, arabadan kurtulmak için /aracibirak komutunu kullanýn. Görevi iptal etmek için: /gorevibitir");
			}
		}

	}
	return 1;
}
