this::CheckAccount(playerid)
{
    if (!IsPlayerConnected(playerid))	return 1;

    SetSpawnInfo(playerid, NO_TEAM, 252, 1039.732055, 2.433174, 1005.315917, 0.0, 0, 0, 0, 0, 0, 0);

    TogglePlayerSpectating(playerid, true);

    SetPlayerColor(playerid, TEAM_HIT_COLOR);
	PlayerPlaySound(playerid, 175, 0.0, 0.0, 0.0);

    InterpolateCameraPos(playerid, 1987.575683, 1192.000732, 27.456075, 1980.587280, 1191.452270, 28.105039, 1500);
    InterpolateCameraLookAt(playerid, 1991.259033, 1195.381835, 27.420658, 1984.578735, 1194.427490, 27.640491, 1500);
	SetWorld(playerid, playerid + 100);
	
	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof(name));

	new query[3096];
	
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts`, `users` WHERE accounts.forum_id = '%s' OR (users.name = '%e' AND accounts.forum_id = users.accountid) LIMIT 1", name, name); 
	mysql_tquery(dbHandle, query, "OnAccountCheck", "d", playerid);
	return 1;
}

this::LoadCharacter(playerid)
{
	if (cache_num_rows())
	{
	    new status;
		cache_get_value_int(0, "status", status);

	    switch(status)
		{
		    case 0:
			{
				SendErrorMessage(playerid, "Karakteriniz þu an pasif halde, bilgi için: %s", WeburlName);
				ShowCharacterMenu(playerid);
				return 1;
			}
      		case 2:
			{
				SM1(playerid, "Karakterinizin detaylarýný düzenleyebilirsiniz.");
				CustomizeCharacter(playerid, CUSTOMIZATION_BACK + 1);
				return 1;
			}
			case 3:
			{
			    new admin_name[MAX_PLAYER_NAME + 1];
			    cache_get_value(0, "block_name", admin_name);
			    
				new reason[65];
			    cache_get_value(0, "block_reason", reason);
			    
				static const str_size[] = "Bu karakter %s adlý yönetici tarafýndan kilitlendi.\nSebep: %s";
			    new str[sizeof(str_size) - 4 + MAX_PLAYER_NAME + 64];
			    format(str, sizeof(str), str_size, admin_name, reason);
			    Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Liberty", str, "Kapat", "");
				return KickEx(playerid);
			}
			case 4: return Kick(playerid);
		}
		
	    foreach (new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[playerid][pAccID] != PlayerInfo[i][pAccID]) continue;

			SendErrorMessage(playerid, "Hesap zaten açýk. #2");
			KickEx(playerid);
			return 1;
		}

		new name[MAX_PLAYER_NAME+1];

		cache_get_value(0, "name", name);

  		if (!CompareStrings(PlayerInfo[playerid][pUsername], name) && SetPlayerName(playerid, name) != 1)
		{
		    SendErrorMessage(playerid,"Hesap zaten açýk. #1");   
		    KickEx(playerid);
		    return 1;
		}
	    GetNameForPlayer(playerid);

		cache_get_value_int(0, "id", PlayerInfo[playerid][pID]);

		SQL_SetInteger("users", "online", 1, PlayerInfo[playerid][pID]);

		//Load database
		cache_get_value_int(0, "cash", PlayerInfo[playerid][pCash]);
		cache_get_value_int(0, "bank", PlayerInfo[playerid][pBank]);
		cache_get_value_int(0, "skin", PlayerInfo[playerid][pSkin]);
		cache_get_value_int(0, "sex", PlayerInfo[playerid][pSex]);
		cache_get_value_int(0, "age", PlayerInfo[playerid][pAge]);
		cache_get_value_int(0, "origin", PlayerInfo[playerid][pOrigin]);
		cache_get_value_int(0, "race", PlayerInfo[playerid][pRace]);		
	 	cache_get_value(0, "birthdate", PlayerInfo[playerid][pBirthdate], 24);
		cache_get_value_int(0, "level", PlayerInfo[playerid][pLevel]);
		cache_get_value_int(0, "exp", PlayerInfo[playerid][pExp]);
		cache_get_value_int(0, "hours", PlayerInfo[playerid][pHours]);
		cache_get_value_int(0, "admin_hide", PlayerInfo[playerid][pAdminHide]);

		cache_get_value_int(0, "donate", PlayerInfo[playerid][pDonate]);
        cache_get_value_int(0, "name_changes", PlayerInfo[playerid][pNameChanges]);
        cache_get_value_int(0, "number_changes", PlayerInfo[playerid][pNumberChanges]);
		
		cache_get_value_int(0, "int", PlayerInfo[playerid][pInt]);
		cache_get_value_int(0, "world", PlayerInfo[playerid][pWorld]);
		cache_get_value_int(0, "ajailed", PlayerInfo[playerid][pAJailed]);
		cache_get_value_int(0, "ajailtime", PlayerInfo[playerid][pAJailTime]);
		cache_get_value_int(0, "jailed", PlayerInfo[playerid][pJailed]);
		cache_get_value_int(0, "isolatetime", PlayerInfo[playerid][pIsolateTime]);
		cache_get_value_int(0, "vip", PlayerInfo[playerid][pPremium]);
		cache_get_value_int(0, "vip_time", PlayerInfo[playerid][pPremiumTime]);
		cache_get_value_int(0, "carlic", PlayerInfo[playerid][pCarLic]);
		cache_get_value_int(0, "weplic", PlayerInfo[playerid][pWepLic]);
		cache_get_value_int(0, "flylic", PlayerInfo[playerid][pFlyLic]);
		cache_get_value_int(0, "taxilic", PlayerInfo[playerid][pTaxiLic]);
		cache_get_value_int(0, "injured", PlayerInfo[playerid][pInjured]);
		cache_get_value_int(0, "deathreason", PlayerInfo[playerid][pDeathReason]);
		cache_get_value_int(0, "paycheck", PlayerInfo[playerid][pPayCheckMoney]);
		cache_get_value_int(0, "paydaytime", PlayerInfo[playerid][pPayDayTime]);
		cache_get_value_int(0, "number", PlayerInfo[playerid][pNumber]);
		cache_get_value_int(0, "savings", PlayerInfo[playerid][pSavings]);
		cache_get_value_int(0, "mutetime", PlayerInfo[playerid][pMutedTime]);
		cache_get_value_int(0, "rent_key", PlayerInfo[playerid][pRentKey]);
		cache_get_value_int(0, "rent_price", PlayerInfo[playerid][pRentPrice]);

		cache_get_value_int(0, "weaphide0", PlayerInfo[playerid][pHideWeap][0]);
		cache_get_value_int(0, "weaphide1", PlayerInfo[playerid][pHideWeap][1]);
		cache_get_value_int(0, "weaphide2", PlayerInfo[playerid][pHideWeap][2]);

		cache_get_value_int(0, "channel", PlayerInfo[playerid][pChannel]);
		cache_get_value_int(0, "owned_channel", PlayerInfo[playerid][pOwnedChannel]);
		cache_get_value_int(0, "authed", PlayerInfo[playerid][pAuthed]);
		cache_get_value_int(0, "sparekey", PlayerInfo[playerid][pSpareKey]);
		cache_get_value_int(0, "workon", PlayerInfo[playerid][pWorkOn]);
		cache_get_value_int(0, "walk", PlayerInfo[playerid][pWalk]);
		cache_get_value_int(0, "faction", PlayerInfo[playerid][pFaction]);
		cache_get_value_int(0, "rank", PlayerInfo[playerid][pRank]);
		cache_get_value_int(0, "badgenumber", PlayerInfo[playerid][pBadgeNumber]);
		cache_get_value_int(0, "drivewarns", PlayerInfo[playerid][pDriveWarns]);
		cache_get_value_int(0, "wepwarns", PlayerInfo[playerid][pWepWarns]);
		cache_get_value_int(0, "wep_count", PlayerInfo[playerid][pWepCount]);
		cache_get_value_int(0, "jailtime", PlayerInfo[playerid][pJailTime]);
		cache_get_value_int(0, "arrested", PlayerInfo[playerid][pArrested]);
		cache_get_value_int(0, "chat", PlayerInfo[playerid][pTalk]);
		cache_get_value_int(0, "authwep", PlayerInfo[playerid][pAuthwep]);
  		cache_get_value_int(0, "swat", PlayerInfo[playerid][pSwat]);
		cache_get_value_int(0, "swat_duty", PlayerInfo[playerid][pSwatDuty]);
		cache_get_value_int(0, "fishcount", PlayerInfo[playerid][pFishCount]);
		cache_get_value_int(0, "slot", PlayerInfo[playerid][pSlot]);
		cache_get_value_int(0, "job", PlayerInfo[playerid][pJob]);
		cache_get_value_int(0, "sidejob", PlayerInfo[playerid][pSideJob]);
		cache_get_value_int(0, "prescribe", PlayerInfo[playerid][pPrescribe]);
		cache_get_value_int(0, "ganja_time", PlayerInfo[playerid][pGanjaTime]);
		cache_get_value_int(0, "career", PlayerInfo[playerid][pCareer]);
		cache_get_value_float(0, "pos_X", PlayerInfo[playerid][pPosX]);
		cache_get_value_float(0, "pos_Y", PlayerInfo[playerid][pPosY]);
		cache_get_value_float(0, "pos_Z", PlayerInfo[playerid][pPosZ]);
		cache_get_value_float(0, "pos_A", PlayerInfo[playerid][pPosA]);
		cache_get_value_int(0, "prisoned", PlayerInfo[playerid][pPrisoned]);
		cache_get_value_int(0, "duty", PlayerInfo[playerid][pOnDuty]);
		cache_get_value_int(0, "char", PlayerInfo[playerid][pChar]);
		cache_get_value_int(0, "hud", PlayerInfo[playerid][pHud]);
		
		cache_get_value_int(0, "drugaccess", PlayerInfo[playerid][pDrugLabAccess]);

		cache_get_value_int(0, "weap_0_bone", PlayerInfo[playerid][pWeaponBone][0]);
		cache_get_value_float(0, "weap_0_x", PlayerInfo[playerid][pWeaponX][0]);
		cache_get_value_float(0, "weap_0_y", PlayerInfo[playerid][pWeaponY][0]);
		cache_get_value_float(0, "weap_0_z", PlayerInfo[playerid][pWeaponZ][0]);
		cache_get_value_float(0, "weap_0_rx", PlayerInfo[playerid][pWeaponRX][0]);
		cache_get_value_float(0, "weap_0_ry", PlayerInfo[playerid][pWeaponRY][0]);
		cache_get_value_float(0, "weap_0_rz", PlayerInfo[playerid][pWeaponRZ][0]);

		cache_get_value_int(0, "weap_1_bone", PlayerInfo[playerid][pWeaponBone][1]);
		cache_get_value_float(0, "weap_1_x", PlayerInfo[playerid][pWeaponX][1]);
		cache_get_value_float(0, "weap_1_y", PlayerInfo[playerid][pWeaponY][1]);
		cache_get_value_float(0, "weap_1_z", PlayerInfo[playerid][pWeaponZ][1]);
		cache_get_value_float(0, "weap_1_rx", PlayerInfo[playerid][pWeaponRX][1]);
		cache_get_value_float(0, "weap_1_ry", PlayerInfo[playerid][pWeaponRY][1]);
		cache_get_value_float(0, "weap_1_rz", PlayerInfo[playerid][pWeaponRZ][1]);

		cache_get_value_int(0, "weap_2_bone", PlayerInfo[playerid][pWeaponBone][2]);
		cache_get_value_float(0, "weap_2_x", PlayerInfo[playerid][pWeaponX][2]);
		cache_get_value_float(0, "weap_2_y", PlayerInfo[playerid][pWeaponY][2]);
		cache_get_value_float(0, "weap_2_z", PlayerInfo[playerid][pWeaponZ][2]);
		cache_get_value_float(0, "weap_2_rx", PlayerInfo[playerid][pWeaponRX][2]);
		cache_get_value_float(0, "weap_2_ry", PlayerInfo[playerid][pWeaponRY][2]);
		cache_get_value_float(0, "weap_2_rz", PlayerInfo[playerid][pWeaponRZ][2]);

		cache_get_value_int(0, "fightstyle", PlayerInfo[playerid][pFightStyle]);

		cache_get_value_int(0, "tog_0", PlayerInfo[playerid][pTog][0]);
		cache_get_value_int(0, "tog_1", PlayerInfo[playerid][pTog][1]);
		cache_get_value_int(0, "tog_2", PlayerInfo[playerid][pTog][2]);

		cache_get_value_int(0, "phone_off", PlayerInfo[playerid][pPhoneOff]);
		cache_get_value_int(0, "phone_airplane", PlayerInfo[playerid][pPhoneAirplane]);
		cache_get_value_int(0, "phone_sound", PlayerInfo[playerid][pPhoneSound]);
		cache_get_value_int(0, "phone_model", PlayerInfo[playerid][pPhoneModel]);
		cache_get_value_int(0, "phone_ringtone", PlayerInfo[playerid][pPhoneRingtone]);
        cache_get_value_int(0, "phone_style", PlayerInfo[playerid][pPhoneStyle]);
        cache_get_value_int(0, "settings", PlayerInfo[playerid][pSettings]);

		cache_get_value_int(0, "bitcoin", PlayerInfo[playerid][pBitcoin]);
		cache_get_value_int(0, "etherium", PlayerInfo[playerid][pEtherium]);

		cache_get_value_int(0, "warns", PlayerInfo[playerid][pWarns]);

		cache_get_value_int(0, "PlayerSerial", PlayerInfo[playerid][pPlayerSerial]);
		if (!PlayerInfo[playerid][pPlayerSerial]) PlayerInfo[playerid][pPlayerSerial] = PlayerInfo[playerid][pID]*100 + 99999 + random(99);
        
		new string2[256], string3[256];
	    cache_get_value(0, "division", string2, 256);
	    sscanf(string2, "p<|>ddddd", PlayerInfo[playerid][pOlusumDivision][0], PlayerInfo[playerid][pOlusumDivision][1], PlayerInfo[playerid][pOlusumDivision][2],
	    PlayerInfo[playerid][pOlusumDivision][3], PlayerInfo[playerid][pOlusumDivision][4]);		

		cache_get_value_int(0, "LastPrim", PlayerInfo[playerid][pLastPrim]);
		cache_get_value_int(0, "LastSec", PlayerInfo[playerid][pLastSec]);
		cache_get_value_int(0, "LastMelee", PlayerInfo[playerid][pLastMelee]);

		cache_get_value_int(0, "Forbid", PlayerInfo[playerid][pForbid]);
		cache_get_value_int(0, "last_login", pTemp[playerid][pLastLogin]);

		cache_get_value(0, "Desc1", PlayerInfo[playerid][pDescribe], PAME_MAX_LEN);
		cache_get_value(0, "Desc2", PlayerInfo[playerid][pDescribe2], PAME_MAX_LEN);

        cache_get_value_int(0, "dependence", PlayerInfo[playerid][pDependence]);
        cache_get_value_int(0, "demolition", PlayerInfo[playerid][pDemolition]);
        cache_get_value_int(0, "fish_time", PlayerInfo[playerid][pFishTime]);

		cache_get_value_int(0, "boombox", PlayerInfo[playerid][pBoombox]);
		cache_get_value_int(0, "maske", PlayerInfo[playerid][pMaske]);
		cache_get_value_int(0, "sigara", PlayerInfo[playerid][pSigara]);
		cache_get_value_int(0, "cakmak", PlayerInfo[playerid][pCakmak]);	
		cache_get_value_int(0, "kalem", PlayerInfo[playerid][pKalem]);
		cache_get_value_int(0, "telsiz", PlayerInfo[playerid][pTelsiz]);
		cache_get_value_int(0, "benzinbidonu", PlayerInfo[playerid][pBenzinBidonu]);	
		cache_get_value_int(0, "zar", PlayerInfo[playerid][pZar]);		
		cache_get_value_int(0, "oyunkarti", PlayerInfo[playerid][pOyunKarti]);	
		cache_get_value_int(0, "calintiradyo", PlayerInfo[playerid][pCalintiRadyo]);
		cache_get_value_int(0, "burnertelefon", PlayerInfo[playerid][pBurnerTelefon]);	

		cache_get_value_int(0, "uyusgettime", PlayerInfo[playerid][UyusKullan]);
	    cache_get_value_int(0, "bagimlilik_exp", PlayerInfo[playerid][pBagimlilikEXP]);
	    cache_get_value_int(0, "bagimlilik_seviye", PlayerInfo[playerid][pBagimlilikSeviye]);
	    cache_get_value_int(0, "kriz_sure", PlayerInfo[playerid][pKrizSure]);
	    cache_get_value_int(0, "tedavi_exp", PlayerInfo[playerid][pUTedaviEXP]);
	    cache_get_value_int(0, "tedavi_sure", PlayerInfo[playerid][pUTedaviSure]);				
		
	    if(PlayerInfo[playerid][pOnDuty])
	    {
		    cache_get_value(0, "string_weapons", string3, 256);
		    sscanf(string3, "p<|>dddddddddddddddddddddddd",
		    PlayerInfo[playerid][pWeapons][0], PlayerInfo[playerid][pAmmo][0],
		    PlayerInfo[playerid][pWeapons][1], PlayerInfo[playerid][pAmmo][1],
		    PlayerInfo[playerid][pWeapons][2], PlayerInfo[playerid][pAmmo][2],
		    PlayerInfo[playerid][pWeapons][3], PlayerInfo[playerid][pAmmo][3],
		    PlayerInfo[playerid][pWeapons][4], PlayerInfo[playerid][pAmmo][4],
		    PlayerInfo[playerid][pWeapons][5], PlayerInfo[playerid][pAmmo][5],
		    PlayerInfo[playerid][pWeapons][6], PlayerInfo[playerid][pAmmo][6],
		    PlayerInfo[playerid][pWeapons][7], PlayerInfo[playerid][pAmmo][7],
		    PlayerInfo[playerid][pWeapons][8], PlayerInfo[playerid][pAmmo][8],
		    PlayerInfo[playerid][pWeapons][9], PlayerInfo[playerid][pAmmo][9],
		    PlayerInfo[playerid][pWeapons][10], PlayerInfo[playerid][pAmmo][10],
		    PlayerInfo[playerid][pWeapons][11], PlayerInfo[playerid][pAmmo][11]);
	    }		
	    else
	     {
		    cache_get_value_int(0, "kamera", PlayerInfo[playerid][pKamera]);
		    cache_get_value_int(0, "cicek", PlayerInfo[playerid][pCicek]);
	    }			
        //PlayerHealth[playerid] = PlayerInfo[playerid][pHealth];

        //SetPlayerHealth(playerid, PlayerHealth[playerid]);

		pTemp[playerid][pPayphone] = -1;
		pTemp[playerid][pPayphoneNumStr] = EOS;
		
		pTemp[playerid][pCallLine] = INVALID_PLAYER_ID;
		pTemp[playerid][pCallStatus] = 0;
		pTemp[playerid][pCallIncoming] = 0;
		pTemp[playerid][pCallTime] = 0;
		format(pTemp[playerid][pCallName], 25, "");

		for(new i; i<6; i++) pTemp[playerid][editPos][i] = 0.0;

		LoadPlayerAttach(playerid);
		LoadPlayerMusic(playerid);
		LoadPlayerNotes(playerid);
		LoadPlayerContacts(playerid);
		LoadPlayerMarks(playerid);
		
		LoadPayPhoneBtnTD(playerid);
		LoadNumPayPhoneTD(playerid);
		CreateVehicleMenu(playerid);

		GiveAdminRights(playerid);

		printf("%f %f", PlayerInfo[playerid][pHealth], PlayerInfo[playerid][pArmour]);

		SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);	

		foreach(new i:Vehicle)
		{
		    if (VehicleInfo[i][carOwnerID] == PlayerInfo[playerid][pID])
			{
            	PlayerInfo[playerid][pCarKey] = i;
            	VehicleInfo[i][carOwnerPlayer] = playerid;
            }
			else if (VehicleInfo[i][carRent] == PlayerInfo[playerid][pID])
			{
				if (VehicleInfo[i][carType] > 5 && VehicleInfo[i][carType] < 10) {
					pTemp[playerid][pJob] = 1;
					pTemp[playerid][pJobTime] = gettime();
				}

			    pTemp[playerid][pRentveh] = i;
			    VehicleInfo[i][carTerminate] = 0;
			}
		}
		
		ResetLoginScreenVariables(playerid);
		ToggleCharacterSelectionScreen(playerid, false);
        ClearChatbox(playerid, 50);
		new gametext[48];

		format(gametext, sizeof(gametext), "~w~hos geldiniz ~n~~h~~y~   %s", GetNameEx(playerid));
		GameTextForPlayer(playerid, gametext, 2500, 1);

		if(PlayerInfo[playerid][pTaxiLic] == 0) PlayerInfo[playerid][pTaxiLic] = 1;
		if(PlayerInfo[playerid][pCarLic] == 0) PlayerInfo[playerid][pCarLic] = 1;

		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 2000, playerid);
		Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 5.0, playerid);

		SendServerMessage(playerid, "Sunucuya hoþ geldin, {c7c3c3}%s!", GetNameEx(playerid));
		SendServerMessage(playerid, "Ýhtiyacýn olursa: {c7c3c3}/soru, /yardim, /menu");
		SendServerMessage(playerid, "Harita ayarlarý için: {c7c3c3}/ayarlar -> Harita");
		
		SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

        SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pWorld]);

		TogglePlayerSpectating(playerid, false);
		
        new premium_info[4][32] = {"Bulunmuyor", "{CC6633}Bronz{FFFFFF}", "{C0C0C0}Gümüþ{FFFFFF}", "{FFD700}Altýn{FFFFFF}"};
				
		if (PlayerInfo[playerid][pPremium] && PlayerInfo[playerid][pPremiumTime] > gettime())
		{
			new Float:days = float(PlayerInfo[playerid][pPremiumTime] - gettime()) / 86400.0;

		    SendServerMessage(playerid, "Baðýþçý durumu: %s. %i gün sonra sona erecek.", premium_info[PlayerInfo[playerid][pPremium]], floatround(days));
		}
		else if (PlayerInfo[playerid][pPremium] && PlayerInfo[playerid][pPremiumTime] < gettime())
		{
		    SendServerMessage(playerid, "Baðýþçý durumunuz (%s) sona erdi. Bizi desteklediðiniz için teþekkürler!", premium_info[PlayerInfo[playerid][pPremium]]);

            PlayerInfo[playerid][pPremium] = 0;
            PlayerInfo[playerid][pPremiumTime] = 0;
			PlayerInfo[playerid][pHud] = 0;
			PlayerInfo[playerid][pFightStyle] = 4;
			SQL_SetFloat("users", "spawnhealth", 75.0, PlayerInfo[playerid][pID]);
			Save_User(playerid);			
		}

		if (PlayerInfo[playerid][pInjured])
		{
			if (PlayerInfo[playerid][pInjured] == 3) pTemp[playerid][pInjuredTime] = 120;
			else									pTemp[playerid][pInjuredTime] = 60;
		}

		if (PlayerInfo[playerid][pAdmin] > 0)		SendServerMessage(playerid, "%i seviye Administrator olarak giriþ yaptýnýz. (/ah)", PlayerInfo[playerid][pAdmin]);
		else if (PlayerInfo[playerid][pHelper] > 0)	SendServerMessage(playerid, "%i seviye Supporter olarak giriþ yaptýnýz. (/helperyardim)", PlayerInfo[playerid][pHelper]);	

        PlayerTextDrawShow(playerid, Silah_Bilgi[playerid][MermiTD]);
		SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pWorld]);
		
		foreach(new i : Player)
		{
			if (!(PlayerInfo[i][pSettings] & togJoin))
			{
				if (IsAdminDuty(i)) 
				{
					SendClientMessageEx(i, COLOR_GRAD2, "*** %s (ID: %i) sunucuya giriþ yaptý (IP: %s, nakit: $%s, banka: $%s)", GetNameEx(playerid),playerid, q_GetPlayerIP(playerid), FormatNumber(PlayerInfo[playerid][pCash]), FormatNumber(PlayerInfo[playerid][pBank]));
				}
			}
		}

	    if (PlayerInfo[playerid][pOnDuty] && PlayerInfo[playerid][pFaction] && IsFactionLegal(PlayerInfo[playerid][pFaction]))
		{
		    SetPlayerColor(playerid, RemoveAlpha(Factions[PlayerInfo[playerid][pFaction]][fColor]));
		    SendClientMessageEx(playerid, COLOR_GRAD2, "{%06x}[%s]{FFFFFF} Tekrar iþbaþýna döndünüz. %s", Factions[PlayerInfo[playerid][pFaction]][fColor] >>> 8, Factions[PlayerInfo[playerid][pFaction]][fShortName], IsFactionPolice(PlayerInfo[playerid][pFaction]) ? " (Durum: 10-7 ÝÞBAÞI)" : "");
			if(IsFactionPolice(PlayerInfo[playerid][pFaction])) pTemp[playerid][tempStatus] = 1;
		}

        PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);

		new count = CountPlayerTickets(playerid);
		if (count)	SendSyntaxMessage(playerid, "Ödenmemiþ %i cezanýz var.", count);

		if (!PlayerInfo[playerid][pNumber])	{
			SetPlayerNumber(playerid);
		}

		SQL_SetInteger("users", "last_login", gettime(), PlayerInfo[playerid][pID]);
		SQL_SetString("users", "last_ip", q_GetPlayerIP(playerid), PlayerInfo[playerid][pID]);

		pTemp[playerid][pSpawned] = 1;
		
		if (PlayerInfo[playerid][pHours] < 8) SendHelpMessage(playerid, "8 oyun saatine ulaþtýðýnýzda $%i bonus kazanacaksýnýz.", SERVER_BONUS);

		SetCash(playerid, PlayerInfo[playerid][pCash]);

		//pTemp[playerid][pLogged] = 2;

        PlayerEnterFreeze(playerid);

		pTemp[playerid][pLogged] = 2;	

		//SetSpawnInfoEx(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
		SetPlayerPosEx(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);

		//SpawnPlayer(playerid);

	}
	else
	{
	    SendErrorMessage(playerid, "Karakter verileriniz alýnýrken bir hata oluþtu. Forum üzerinden ticket açýn.");
	    KickEx(playerid);
	}
	return 1;
}

this::OnAccountCheck(playerid)
{
    if (IsPlayerNPC(playerid))	return 1;

	if (!cache_num_rows())
	{
		SendErrorMessage(playerid, "Üzgünüz, veritabaný kontrol edildi ve hesabýnýz bulunamadý.");
		SendServerMessage(playerid, "Kayýtlar forum adresi üzerinde bulunan UCP kýsmýndan yapýlmaktadýr.");
		SendServerMessage(playerid, "UCP bölümüne eriþmek için: "WeburlName"");
		KickEx(playerid);
	    return 1;
	}

	new last_ip[24];

	cache_get_value_int(0, "forum_id", PlayerInfo[playerid][pAccID]);	
	
	cache_get_value(0, "login", PlayerInfo[playerid][pAccname], MAX_PLAYER_NAME+1);

	cache_get_value_int(0, "talepsayi", PlayerInfo[playerid][pTalepSayi]);
	cache_get_value_int(0, "raporsayi", PlayerInfo[playerid][pRaporSayi]);
	
	cache_get_value(0, "last_game_ip", last_ip);
		
	if(IsPlayerLoggedIn(GetPlayerIDByAccountSqlID(PlayerInfo[playerid][pAccID])))
		return KickLine(playerid, "Bu karakterin baðlý olduðu hesap zaten oyunda olduðu için uzaklaþtýrýlýyorsunuz.");
	
	new query[170], sub[8];

	GetPlayerIp(playerid, sub, sizeof(sub));

	new pos;

	for(new i; i < 2; i++)
	{
	    pos = strfind(sub, ".", true, pos+1);
	}

	if (pos != -1) strdel(sub, pos, 24);
	

	new pip[24];

    GetPlayerIp(playerid, pip, sizeof(pip));

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `bans` WHERE `name` = '%e' OR `ip`='%s' OR `ip`='%s'", PlayerInfo[playerid][pAccname], sub, pip);
	mysql_tquery(dbHandle, query, "OnPlayerAttemptLogin", "is", playerid, last_ip);
	return 1;
}

this::LoginPlayer(playerid)
{
	if (cache_num_rows() == 0)
	{
    	if (pTemp[playerid][pLoggedTry]++ == 3) return KickEx(playerid);
		
		static const str_size[] = "{c7c3c3}LIBERTY:\t{FFFFFF}Giriþ yapmak için 5 dakikanýz var.\n\
								   {c7c3c3}ÝPUCU:\t\t{FFFFFF}Hesap þifrenizi forumdan deðiþtirebilirsiniz.\n\
								   \t\tForum: {c7c3c3}"WeburlName"\n\
								   \t\t{FFFFFF}Forum üzerinden UCP bölümüne eriþebilirsin\n\n\
								   Þifrenizi girin:"; 
		new mes[sizeof(str_size)+103];

		format(mes, sizeof(mes), "{FF6347}[ ! ] {FFFFFF}Yanlýþ þifre girdiniz!\n{FF6347}[ ! ] {FFFFFF}Kalan deneme sayýsý: {FF6347}%d\n\n%s", 3-pTemp[playerid][pLoggedTry], str_size);	
		Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, ""ProjectName"", mes, "Giriþ Yap", "Ýptal");
		SendWarningMessage(playerid, "Yanlýþ þifre girdiniz.");
		return 1;
	}

    pTemp[playerid][pLoggedTime] = 0;
	
	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `loginlog` (accountid, ip, method, date) VALUES (%i, '%e', 'Giris', '%e')", PlayerInfo[playerid][pAccID], q_GetPlayerIP(playerid), GetFullDate());
	mysql_tquery(dbHandle, query);
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `last_game_ip` = '%e', `last_game_login` = '%e' WHERE `forum_id` = %i", q_GetPlayerIP(playerid), GetFullDate(), PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);

	ShowCharacterMenu(playerid);
	return 1;
}

this::SearchCharacters(playerid)
{
	if (!cache_num_rows())
	{
		SendErrorMessage(playerid, "Bu hesapta aktif karakter bulunmuyor.");
		KickEx(playerid);
		return 1;
	}

	mysql_tquery(dbHandle, sprintf("SELECT id FROM users WHERE accountid = '%d' AND (status = 1 or status = 2)", PlayerInfo[playerid][pAccID]), "OnPlayerCharactersLoaded", "d", playerid);	
	//Dialog_Show(playerid, SelectChar, DIALOG_STYLE_TABLIST_HEADERS, "Karakter seçimi:", mes, "Seç", "Ýptal");
	return 1;
}

this::OnPlayerCharactersLoaded(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        CharacterSelection[playerid][sCharactersCount] = rows;

        LoginScreenDisplayCharacter(playerid, 1, 1);
    }

    else KickEx(playerid);

    return 1;
}

this::OnPlayerAttemptLogin(playerid, last_ip[])
{
	if (cache_num_rows() != 0) {
		new reason[64], ip[24], date[24], name[24], admin[MAX_PLAYER_NAME], time;
		
		cache_get_value(0, "reason", reason);
		cache_get_value(0, "date", date);
		cache_get_value(0, "ip", ip);
		cache_get_value(0, "admin", admin);
		cache_get_value(0, "name", name);
		
		cache_get_value_int(0, "time", time);

		if (gettime() < time) 
		{
			new mes[512];
			if (CompareStrings(ip, "-") != 0)
			{
				format(mes, sizeof(mes), "{FFFFFF}Hesabýnýz bir yönetici tarafýndan yasaklanmýþ: {B5B5B5}%s.\n{FFFFFF}Yasaklanma tarihi: {B5B5B5}%s\n{FFFFFF}Sebep: {B5B5B5}%s\n\nHatalý yasaklanma için lütfen forumdan ticket açýn.\n\
				Çýkýþ yapmak için /q", admin, date, reason);
			}
			else
			{
				format(mes, sizeof(mes), "{FFFFFF}IP adresiniz (%s) yönetici tarafýndan yasaklanmýþ: {B5B5B5}%s.\n{FFFFFF}Yasaklanma tarihi: {B5B5B5}%s\n{FFFFFF}Sebep: {B5B5B5}%s\n\nHatalý yasaklanma için lütfen forumdan ticket açýn.\n\
				Çýkýþ yapmak için /q", ip, admin, date, reason);
			}
			
			Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Yasaklý Oyuncu", mes, "/q", "");
			KickEx(playerid);
			return 1;
		} 
		else 
		{
			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `bans` WHERE `name` = '%e'", name);
			mysql_tquery(dbHandle, query);
		}
	}

	new ip[24];

	GetPlayerIp(playerid, ip, sizeof(ip));

	pTemp[playerid][pLogged] = 1;
	ClearChatbox(playerid, 50);
	SendServerMessage(playerid,"Oyun servisi sürümü: {c7c3c3}"GameModeVersion"");
	SendServerMessage(playerid,"Son güncelleme: {c7c3c3}"GameModeUpdate"");

	static const str_size[] = "{c7c3c3}LIBERTY:\t{FFFFFF}Giriþ yapmak için 5 dakikanýz var.\n\
								   {c7c3c3}ÝPUCU:\t\t{FFFFFF}Hesap þifrenizi forumdan deðiþtirebilirsiniz.\n\
								   \t\tForum: {c7c3c3}"WeburlName"\n\
								   \t\t{FFFFFF}Forum üzerinden UCP bölümüne eriþebilirsin\n\n\
								   Þifrenizi girin:"; 

	new mes[sizeof(str_size)];

	format(mes, sizeof(mes), str_size);
	Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, ""ProjectName"", mes, "Giriþ Yap", "Ýptal");
	return 1;
}

ShowCharacterMenu(playerid)
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `accountid` = %i AND (status = 1 or status = 2)", PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query, "SearchCharacters", "i", playerid);
	return 1;
}

SetPlayerSpawn(playerid)
{
	if (IsPlayerNPC(playerid)) return 1;

    TogglePlayerSpectating(playerid, 0);	

    if (pTemp[playerid][pLastLogin] == 0)
	{
		new first_login = randomEx(1,5);

		switch(first_login)
		{
			case 1:
			{
                SetWorld(playerid, 0);
				SetInterior(playerid, 0);
				SetPlayerPosEx(playerid,426.2177,-784.6637,43.9577);
			}
			case 2:
			{
                SetWorld(playerid, 0);
				SetInterior(playerid, 0);
				SetPlayerPosEx(playerid,681.7299,-669.9059,35.0301);
			}
			case 3:
			{
                SetWorld(playerid, 0);
				SetInterior(playerid, 0);
				SetPlayerPosEx(playerid,615.5635,-358.8992,25.0695);
			}
			case 4:
			{
                SetWorld(playerid, 0);
				SetInterior(playerid, 0);
				SetPlayerPosEx(playerid,653.1493,-1083.1321,35.4389);
			}
			case 5:
			{
                SetWorld(playerid, 0);
				SetInterior(playerid, 0);
				SetPlayerPosEx(playerid,726.3694,-893.4230,35.0667);
			}									
		}
		SendServerMessage(playerid, "%d numaralý spawn bölgesine gönderildiniz.", first_login);
		pTemp[playerid][pLastLogin] = gettime();
		return 1;
	}

	if (pTemp[playerid][pSpecPlayer] != INVALID_PLAYER_ID)
	{
	    pTemp[playerid][pSpecPlayer] = INVALID_PLAYER_ID;
		SetInterior(playerid,PlayerInfo[playerid][pInt]);
		SetWorld(playerid, PlayerInfo[playerid][pWorld]);
		SetPlayerPosEx(playerid,PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
		PlayerTextDrawHide(playerid, spectate_TD[playerid][0]);
		PlayerTextDrawHide(playerid, spectate_TD[playerid][1]);
		return 1;
	}

    else if (pTemp[playerid][pCCTV])
	{
	    pTemp[playerid][pCCTV] = 0;
        DeletePVar(playerid, "CCTV:ID");

		SetInterior(playerid,PlayerInfo[playerid][pInt]);
		SetWorld(playerid, PlayerInfo[playerid][pWorld]);
		SetPlayerPosEx(playerid,PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	    return 1;
	}

	else if (pTemp[playerid][pInteriorBiz])
	{
	    new bizid = pTemp[playerid][pInteriorBiz]-1;

		SetPlayerPosEx(playerid,BizInfo[bizid][bizExitX], BizInfo[bizid][bizExitY], BizInfo[bizid][bizExitZ]);
		SetInterior(playerid,BizInfo[bizid][bizExitInt]);
		SetWorld(playerid,BizInfo[bizid][bizExitVW]);

        pTemp[playerid][pInteriorBiz] = 0;
        pTemp[playerid][pInteriorID] = 0;
        pTemp[playerid][pInteriorHouse] = 0;
	    return 1;
	}
	
	else if (pTemp[playerid][pZond])
	{
	    pTemp[playerid][pZond] = 0;
		SetInterior(playerid,PlayerInfo[playerid][pInt]);
		SetWorld(playerid, PlayerInfo[playerid][pWorld]);
		SetPlayerPosEx(playerid,PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	    return 1;
	}

	// ï¿½ï¿½ï¿½ï¿½ ï¿½ ï¿½ï¿½ï¿½ï¿½

	if (PlayerInfo[playerid][pAJailed] != 0)
	{
		SetInterior(playerid, 18);
		SetWorld(playerid, playerid + 100);
		SetPlayerPosEx(playerid, 1017.3297,-807.2664,2003.0758);
		SendSyntaxMessage(playerid, "OOC hapis cezasýna geri döndünüz. Kalan süre: %i dakika", PlayerInfo[playerid][pAJailTime]/60);
		return 1;
	}
	else if (PlayerInfo[playerid][pJailed]) return PutPlayerInPrison(playerid);

	//SPAWN TYPES
	/*if (PlayerInfo[playerid][pInjured] || GetPVarInt(playerid, #last_login) || PlayerInfo[playerid][pSpawnType] == 3)
	{*/

	if (pTemp[playerid][pLastLogin] != 0)
	{
	    SetPlayerPosEx(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
	    SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pPosA]);
	    SetInterior(playerid, PlayerInfo[playerid][pInt]);
	    SetWorld(playerid, PlayerInfo[playerid][pWorld]);
	}	
		
	/*	DeletePVar(playerid, #last_login);
		return 1;
	}

	else if (PlayerInfo[playerid][pSpawnType] == 1)
	{
	    new houseid = GetHouseIDByMysql(PlayerInfo[playerid][pSpawnPoint]);
	    if (houseid == -1 || (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID] && PlayerInfo[playerid][pRentKey] != PlayerInfo[playerid][pSpawnPoint]))
		{
			SendSyntaxMessage(playerid, "Evinizin kira süresi bitti veya anahtarý sizden alýndý. ");
			PlayerInfo[playerid][pSpawnType] = 0;
			PlayerInfo[playerid][pSpawnPoint] = 1;
			SendHelpMessage(playerid, "Spawn lokasyonunuz tekrardan deðiþtirildi. (/settings)");
		}
		else
		{
			SetPlayerPos(playerid, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY],HouseInfo[houseid][hExitZ]);
			SetInterior(playerid,HouseInfo[houseid][hExitInt]);
			SetWorld(playerid,HouseInfo[houseid][hExitVW]);
			pTemp[playerid][pHouseEntered] = houseid;
			return 1;
		}
	}

	else if (PlayerInfo[playerid][pSpawnType] == 2)
	{
		if (PlayerInfo[playerid][pFaction] == 0)
		{
			SendSyntaxMessage(playerid, "Artýk herhangi bir birlikte deðilsiniz.");
			PlayerInfo[playerid][pSpawnType] = 0;
			PlayerInfo[playerid][pSpawnPoint] = 1;
			SendHelpMessage(playerid, "Spawn lokasyonunuz tekrardan deðiþtirildi. (/settings)");
		}
		else
		{
			SetPlayerPos(playerid,Factions[PlayerInfo[playerid][pFaction]][fPosX],Factions[PlayerInfo[playerid][pFaction]][fPosY],Factions[PlayerInfo[playerid][pFaction]][fPosZ]);
			SetInterior(playerid, Factions[PlayerInfo[playerid][pFaction]][fSpawnInt]);
			SetWorld(playerid, Factions[PlayerInfo[playerid][pFaction]][fSpawnVW]);
			return 1;
		}
	}

	else if (PlayerInfo[playerid][pSpawnType] == 0)
	{		        
	   	SetPlayerPos(playerid, first_spawn[PlayerInfo[playerid][pSpawnPoint]-1][0], first_spawn[PlayerInfo[playerid][pSpawnPoint]-1][1], first_spawn[PlayerInfo[playerid][pSpawnPoint]-1][2]);
	    SetPlayerFacingAngle(playerid, first_spawn[PlayerInfo[playerid][pSpawnPoint]-1][3]);
		SetInterior(playerid,0);
		SetWorld(playerid, 0);
		return 1;
	}*/
	return 1;
}

stock RPnamecheck(pname[])
{
	if(strfind(pname,"[",true) != (-1)) return 0;
    else if(strfind(pname,"]",true) != (-1)) return 0;
    else if(strfind(pname,"$",true) != (-1)) return 0;
    else if(strfind(pname,"(",true) != (-1)) return 0;
    else if(strfind(pname,")",true) != (-1)) return 0;
    else if(strfind(pname,"=",true) != (-1)) return 0;
    else if(strfind(pname,"@",true) != (-1)) return 0;
    else if(strfind(pname,"1",true) != (-1)) return 0;
    else if(strfind(pname,"2",true) != (-1)) return 0;
    else if(strfind(pname,"3",true) != (-1)) return 0;
    else if(strfind(pname,"4",true) != (-1)) return 0;
    else if(strfind(pname,"5",true) != (-1)) return 0;
    else if(strfind(pname,"6",true) != (-1)) return 0;
    else if(strfind(pname,"7",true) != (-1)) return 0;
    else if(strfind(pname,"8",true) != (-1)) return 0;
    else if(strfind(pname,"9",true) != (-1)) return 0;
    else if(strfind(pname,"fuck",true) != (-1)) return 0;
    else if(strfind(pname,"FUCK",true) != (-1)) return 0;
    else if(strfind(pname,"Boobies",true) != (-1)) return 0;
    else if(strfind(pname,"Tupac_Shakur",true) != (-1)) return 0;
    else if(strfind(pname,"Pussy",true) != (-1)) return 0;
    else if(strfind(pname,"Rape",true) != (-1)) return 0;
    else if(strfind(pname,"kill",true) != (-1)) return 0;
    else if(strfind(pname,"shit",true) != (-1)) return 0;
    else if(strfind(pname,"ass",true) != (-1)) return 0;
    else if(strfind(pname,"Jack_Black",true) != (-1)) return 0;
    else if(strfind(pname,"Max_Kenton",true) != (-1)) return 0;
    else if(strfind(pname,"Will_Smith",true) != (-1)) return 0;
    else if(strfind(pname,"Jaden_Smith",true) != (-1)) return 0;
    else if(strfind(pname,"Megan_Fox",true) != (-1)) return 0;
    else if(strfind(pname,"Charlie_Kenton",true) != (-1)) return 0;
    else if(strfind(pname,"Hugh_Hefner",true) != (-1)) return 0;
    else if(strfind(pname,"Paris_Hilton",true) != (-1)) return 0;
    else if(strfind(pname,"Marshall_Mathers",true) != (-1)) return 0;
    else if(strfind(pname,"Sheldon_Cooper",true) != (-1)) return 0;
    else if(strfind(pname,"Jet_Lee",true) != (-1)) return 0;
    else if(strfind(pname,"Jackie_Chan",true) != (-1)) return 0;
    else if(strfind(pname,"Chuck_Norris",true) != (-1)) return 0;
    else if(strfind(pname,"Peter_Parker",true) != (-1)) return 0;
    else if(strfind(pname,"Spider_Man",true) != (-1)) return 0;
    else if(strfind(pname,"Bat_Man",true) != (-1)) return 0;
    else if(strfind(pname,"Emma_Stone",true) != (-1)) return 0;
    else if(strfind(pname,"whore",true) != (-1)) return 0;
    else if(strfind(pname,"Hugh_Jackman",true) != (-1)) return 0;
    else if(strfind(pname,"Charles_Kenton",true) != (-1)) return 0;
    else if(strfind(pname,"Harry_Potter",true) != (-1)) return 0;
    else if(strfind(pname,"Chris_Hemsworth",true) != (-1)) return 0;
    else if(strfind(pname,"Penis",true) != (-1)) return 0;
    else if(strfind(pname,"_Dick",true) != (-1)) return 0;
    else if(strfind(pname,"Vagina",true) != (-1)) return 0;
    else if(strfind(pname,"Cock",true) != (-1)) return 0;
    else if(strfind(pname,"Rectum",true) != (-1)) return 0;
    else if(strfind(pname,"Sperm",true) != (-1)) return 0;
    else if(strfind(pname,"Rektum",true) != (-1)) return 0;
    else if(strfind(pname,"Pistol",true) != (-1)) return 0;
    else if(strfind(pname,"AK47",true) != (-1)) return 0;
    else if(strfind(pname,"Shotgun",true) != (-1)) return 0;
    else if(strfind(pname,"Cum",true) != (-1)) return 0;
    else if(strfind(pname,"Hitler",true) != (-1)) return 0;
    else if(strfind(pname,"Jesus",true) != (-1)) return 0;
    else if(strfind(pname,"God",true) != (-1)) return 0;
    else if(strfind(pname,"Shotgun",true) != (-1)) return 0;
    else if(strfind(pname,"Desert_Eagle",true) != (-1)) return 0;
    else if(strfind(pname,"fucker",true) != (-1)) return 0;
    else if(strfind(pname,"Retard",true) != (-1)) return 0;
    else if(strfind(pname,"Tarded",true) != (-1)) return 0;
    else if(strfind(pname,"fanny",true) != (-1)) return 0;
    else if(strfind(pname,"Daniel_Hardy",true) != (-1)) return 0;
    else if(strfind(pname,"abcdefghijklmnopqrstuvwxyz",true) != (-1)) return 0;
   
    return 1;
}

stock LoginScreenDisplayCharacter(playerid, slot, isFirstLogin = 0)
{
    if(slot < 1)
        slot = 1;

    else if(slot > CharacterSelection[playerid][sCharactersCount])
        slot = CharacterSelection[playerid][sCharactersCount];

    if(slot != CharacterSelection[playerid][sCurrentSlotID])
    {
        new query[177 + (11 * 4) + 1];

        mysql_format(dbHandle, query, sizeof(query), "SELECT id, name, level, skin, world, pos_X, pos_Y, pos_Z FROM users WHERE accountid = '%d' AND (status = 1 or status = 2) LIMIT %d, %d", PlayerInfo[playerid][pAccID], slot-1, slot);
        mysql_tquery(dbHandle, query, "LoadCharacterDetailsOnSelection", "dd", playerid, isFirstLogin);

        PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], sprintf("%d/%d", slot, CharacterSelection[playerid][sCharactersCount]));

        CharacterSelection[playerid][sIsSelecting] = true;
        CharacterSelection[playerid][sCurrentSlotID] = slot;
    }
	//SendClientMessageEx(playerid, 0xFFFFFFFF, "%d, %d", GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID), slot);

	SelectTextDraw(playerid, COLOUR_DANDELION);

	return 1;
}

this::LoadCharacterDetailsOnSelection(playerid, isFirstLogin)
{
	new rows = cache_num_rows();
	if(rows)
	{
		new id, name[MAX_PLAYER_NAME], level, skin, world, Float:x, Float:y, Float:z; //world
		cache_get_value_int(0, "id", id);
		cache_get_value(0, "name", name);
		cache_get_value_int(0, "level", level);
		cache_get_value_int(0, "skin", skin);
		//world = cache_get_field_content_int (0, "world");
		cache_get_value_float(0, "pos_X", x);
		cache_get_value_float(0, "pos_Y", y);
		cache_get_value_float(0, "pos_Z", z);
		cache_get_value_int(0, "world", world);

		SetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID, id);

		if(x != 0.0 && y != 0.0 && z != 0.0)
		{
			new location[128];
			
			if(world > 0) location = "Bir Mekanin Icinde";
			else format(location, sizeof(location), GetLocationZone(x, y, z));

			PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], sprintf("~y~%s (Lvl: ~w~%d~y~)~n~%s ~w~bolgesinde.", name, level, location));
		}

		else PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], sprintf("~y~%s (Lvl: ~w~%d~y~)~n~Mekan ~w~icinde.", name, level));

		if(isFirstLogin)
		{	
			ToggleCharacterSelectionScreen(playerid, true);
		}

		new actorid = CharacterSelection[playerid][sActorID];

		if(actorid != INVALID_ACTOR_ID)
		{
			DestroyDynamicActor(actorid);
		}

        SetPlayerVirtualWorld(playerid, playerid+100);
		actorid = CreateDynamicActor(skin, 1984.1781,1196.9385,26.8855,137.1539, 1, 100.0, playerid+100, 0);
		Streamer_Update(playerid);

		CharacterSelection[playerid][sActorID] = actorid;
	}

	else if(isFirstLogin && !rows)
	{
		SendErrorMessage(playerid, "Karakter detaylarý alýnýrken bir sorun meydana geldi. Sorun devam ederse yöneticilerle iletiþime geçiniz. (Hata kodu: #3)");
		//AdminWarn(DEV, sprintf("%s (ID: %d / Hesap: %d) - (LoadCharacterDetailsOnSelection) hatasý aldý. (#3)", GetName(playerid, 0), playerid, PlayerInfo[playerid][pID]));
	}

	else
	{
		SendErrorMessage(playerid, "Karakter detaylarý alýnýrken bir sorun meydana geldi. Sorun devam ederse yöneticilerle iletiþime geçiniz. (Hata kodu: #4)");
		//AdminWarn(DEV, sprintf("%s (ID: %d / Hesap: %d) - (LoadCharacterDetailsOnSelection) hatasý aldý. (#4)", GetName(playerid, 0), playerid, PlayerInfo[playerid][pID]));
	}

	return 1;
}

stock ToggleCharacterSelectionScreen(playerid, bool:status)
{
    switch(status)
    {
        case false:
        {
            for(new i = 0; i < 5; i++)
            {
			    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][LoginCharacterTD][i]);
            }

            ResetLoginScreenVariables(playerid);

            ClearChatbox(playerid, 20);
            CancelSelectTextDraw(playerid);
        }

        case true:
        {
            SendClientMessageEx(playerid, COLOUR_ALTO, "Ýmleci aktifleþtirmek için: /fare veya /imlec");

            for(new i = 0; i < 5; i++)
            {
			    PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][i]);
            }

            InterpolateCameraPos(playerid, 1980.587280, 1191.452270, 28.105039, 1982.342407, 1192.793579, 27.254293, 1500);
            InterpolateCameraLookAt(playerid, 1984.578735, 1194.427490, 27.640491, 1985.426635, 1196.728149, 27.171886, 1500);

            SyncCharacterSelectionButtons(playerid);
        }
    }

    return 1;
}

stock ResetLoginScreenVariables(playerid)
{
    CharacterSelection[playerid][sIsSelecting] = false;
    CharacterSelection[playerid][sCurrentSlotID] = 0;
    CharacterSelection[playerid][sCharactersCount] = 0;

	DeletePVar(playerid, PVAR_LISTCHARS_CDETAILS_CID);

    new actorid = CharacterSelection[playerid][sActorID];

    if(IsValidDynamicActor(actorid))
    {
        DestroyDynamicActor(actorid);
    }

    CharacterSelection[playerid][sActorID] = INVALID_ACTOR_ID;

    return 1;
}

stock SyncCharacterSelectionButtons(playerid)
{
	if(CharacterSelection[playerid][sCurrentSlotID] <= 1)
	{
		PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], false);
		PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], sprintf("~w~Geri"));
	}

	else
	{
		PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], true);
		PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], sprintf("Geri"));
	}

	if(CharacterSelection[playerid][sCurrentSlotID] >= CharacterSelection[playerid][sCharactersCount])
	{
		PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], false);
		PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], sprintf("~w~Ileri"));
	}

	else
	{
		PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], true);
		PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], sprintf("Ileri"));
	}

    return 1;
}

stock CustomizeCharacter(playerid, step)
{
    if(step == CUSTOMIZATION_SKIN)
    {
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0]);
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1]);
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2]);
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3]);
    }

    else
    {
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0]);
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1]);
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2]);
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3]);
    }

    switch(step)
    {
        // case CUSTOMIZATION_BACK: DisplayCharacterList(playerid);
        case CUSTOMIZATION_AGE: Dialog_Show(playerid, CustomizationAge, DIALOG_STYLE_INPUT, "Yaþ Seçimi", EMBED_WHITE "Karakteriniz için lütfen yaþ belirleyiniz.\n" DIALOG_EX "17 - 98", "Ýleri", "Geri");
        case CUSTOMIZATION_GENDER: Dialog_Show(playerid, CustomizationGender, DIALOG_STYLE_LIST, "Cinsiyet Seçimi", EMBED_WHITE "Karakteriniz için lütfen cinsiyet belirleyiniz.\n" EMBED_BLACK ".\nErkek\nKadýn\n", "Ýleri", "Geri"); 
        case CUSTOMIZATION_RACE: Dialog_Show(playerid, CustomizationRace, DIALOG_STYLE_LIST, "Ten Rengi Seçimi", EMBED_WHITE "Karakteriniz için lütfen ten rengi belirleyiniz.\n" EMBED_BLACK ".\nBeyaz\nSiyah\n", "Ýleri", "Geri"); 
        case CUSTOMIZATION_ORIGIN: mysql_tquery(dbHandle, "SELECT origin FROM origins", "CustomizationOrigin", "d", playerid);
        case CUSTOMIZATION_SKIN: mysql_tquery(dbHandle, GetSkin("game_skins.model_id, game_skins.price", "", "", 1, -1, -1, -1, PlayerInfo[playerid][pSex], PlayerInfo[playerid][pRace]), "CustomizationSkin", "d", playerid);
        case CUSTOMIZATION_VERIFY: Dialog_Show(playerid, CustomizationVerify, DIALOG_STYLE_LIST, "Özelleþtirme Onaylamasý", EMBED_WHITE "Karakter detaylarýný belirlediniz. Þimdi onu kaydetmek ister misiniz?\n" EMBED_BLACK ".\n" EMBED_PASTELGREEN "Evet, devam et.\n" EMBED_TOMATO "Hayýr, geri dön.", "Ýleri", "Geri");
        // case CUSTOMIZATION_DONE: DisplayCharacterList(playerid);
    }

    return 1;
}

stock LoadCharacterSkinPrices(playerid)
{
	if (PlayerInfo[playerid][pSex] == 1)
    {
        new mes[sizeof(male_skins)*16];
        for(new i = 0; i < sizeof(male_skins); i++)
        {
            format(mes, sizeof(mes), "%s%i\tID: %i\n", mes, male_skins[i], male_skins[i]); 
        }
        Dialog_Show(playerid, CustomizationSkin, DIALOG_STYLE_PREVIEW_MODEL, "Kiyafet Secimi", mes, "Sec", "Ýptal");
    }
    else
    {
        new mes[sizeof(female_skins)*16];
        for(new i = 0; i < sizeof(female_skins); i++)
        {
            format(mes, sizeof(mes), "%s%i\tID: %i\n", mes, female_skins[i], female_skins[i]); 
        }
        Dialog_Show(playerid, CustomizationSkin, DIALOG_STYLE_PREVIEW_MODEL, "Kiyafet Secimi", mes, "Sec", "Ýptal");
	}
}

stock GetOriginID(name[])
{
    new sqlid = 0, query[43 + MAX_PLAYER_NAME + 1], Cache:search;

    mysql_format(dbHandle, query, sizeof(query), "SELECT id FROM origins WHERE origin = '%e'", name);
    search = mysql_query(dbHandle, query);

    if(cache_num_rows())
    {
        cache_get_value_int(0, "id", sqlid);
    }

    cache_delete(search);
	search = MYSQL_INVALID_CACHE;
    return sqlid;
}

stock GiveAdminRights(playerid)
{
    new admin = 0, helper = 0, helperlead = 0, fmadmin = 0, mapper = 0, rdscripter = 0, query[86 + MAX_PLAYER_NAME + 1], Cache:search;

    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM accounts WHERE forum_id = '%d'", PlayerInfo[playerid][pAccID]);
    search = mysql_query(dbHandle, query);

    if(cache_num_rows())
    {
        cache_get_value_int(0, "admin", admin);
		cache_get_value_int(0, "helper", helper);
		cache_get_value_int(0, "helperlead", helperlead);
		cache_get_value_int(0, "fmadmin", fmadmin);
		cache_get_value_int(0, "mapper", mapper);
		cache_get_value_int(0, "rdscripter", rdscripter);
    }

    PlayerInfo[playerid][pAdmin] = admin;
	PlayerInfo[playerid][pHelper] = helper;
	PlayerInfo[playerid][pHelperLead] = helperlead;
	PlayerInfo[playerid][pFMAdmin] = fmadmin;
	PlayerInfo[playerid][pMapper] = mapper;
	PlayerInfo[playerid][pRdscripter] = rdscripter;

	cache_delete(search);
	search = MYSQL_INVALID_CACHE;
    return 1;
}

stock GetAccountByName(name[])
{
    new query[256], Cache:search, accountid = -1;

    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM users WHERE name = '%e'", name);
    search = mysql_query(dbHandle, query);

    if(cache_num_rows())
    {
        cache_get_value_int(0, "accountid", accountid);
    }

    cache_delete(search);
	search = MYSQL_INVALID_CACHE;
    return accountid;
}

this::CustomizationSkin(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new str[512], skin_id;

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_int(i, "model_id", skin_id);

            format(str, sizeof(str), "%s%d\n", str, skin_id);
        }

        Dialog_Show(playerid, CustomizationSkinSelect, DIALOG_STYLE_PREVIEW_MODEL, "Kiyafetler", str, "Satin Al", "Kapat");

    }

    else CustomizeCharacter(playerid, CUSTOMIZATION_SKIN + 1);

    return 1;
}

this::CustomizationOrigin(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new str[1024];
        new origin[90];

        for(new i = 0; i < rows; i++)
        {
            cache_get_value(i, "origin", origin, 90);

            if(!(i % 2))
                format(str, sizeof(str), "%s" EMBED_ALTO "%s\n", str, origin);

            else format(str, sizeof(str), "%s" EMBED_WHITE "%s\n", str, origin);
        }

        Dialog_Show(playerid, CustomizationOrigin, DIALOG_STYLE_LIST, "Uyruklar", str, "Ýleri", "Geri");
    }

    else CustomizeCharacter(playerid, CUSTOMIZATION_ORIGIN + 1);

    return 1;
}

this::CharacterOriginSelected(playerid, origin[])
{
    new rows = cache_num_rows();

    if(rows)
    {
        mysql_tquery(dbHandle, sprintf("UPDATE users SET origin = '%d' WHERE id = '%d'", GetOriginID(origin), GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));
        PlayerInfo[playerid][pOrigin] = GetOriginID(origin);

        SM1(playerid, "Uyruðunuz %s olarak belirlendi.", origin);
        CustomizeCharacter(playerid, CUSTOMIZATION_ORIGIN + 1);
    }

    else CustomizeCharacter(playerid, CUSTOMIZATION_ORIGIN + 1);

    return 1;
}

this::FixHealthArm(playerid)
{
	PlayerInfo[playerid][pHealth] = GetSQLHealth(playerid);
	SetPlayerHealth(playerid, GetSQLHealth(playerid));
	PlayerInfo[playerid][pArmour] = GetSQLArmor(playerid);
	SetPlayerArmour(playerid, GetSQLArmor(playerid));
	return 1;	
}