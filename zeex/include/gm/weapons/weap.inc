Weapon_EditAttachedObject(playerid, response, index, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	new weaponid = EditingWeapon[playerid];
	if(weaponid)
	{
		if(response)
		{
			new enum_index = weaponid - 22, weaponname[18], name[MAX_PLAYER_NAME], string[340];

			GetWeaponName(weaponid, weaponname, sizeof(weaponname));
			GetPlayerName(playerid, name, MAX_PLAYER_NAME);

			WeaponSettings[playerid][enum_index][Position][0] = fOffsetX;
			WeaponSettings[playerid][enum_index][Position][1] = fOffsetY;
			WeaponSettings[playerid][enum_index][Position][2] = fOffsetZ;
			WeaponSettings[playerid][enum_index][Position][3] = fRotX;
			WeaponSettings[playerid][enum_index][Position][4] = fRotY;
			WeaponSettings[playerid][enum_index][Position][5] = fRotZ;
			new slot = GetWeaponObjectSlot(weaponid);
			if(slot != -1) SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModelEx(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
			else return SendErrorMessage(playerid, "Tüm aksesuar slotlarýný kullanýyorsunuz, bir aksesuar çýkartýp tekrar deneyin.");
			SendServerMessage(playerid, "%s isimli silahýnýzýn pozisyonunu baþarýyla deðiþtirdiniz.", weaponname);

			if(WeaponSettings[playerid][enum_index][duzenlendi])
			{
				mysql_format(dbHandle, string, sizeof(string), "DELETE FROM weaponsettings WHERE sOwner = '%d' AND WeaponID = '%d'", PlayerInfo[playerid][pID], weaponid);
				mysql_tquery(dbHandle, string);
				WeaponSettings[playerid][enum_index][duzenlendi] = 0;
			}

			if(!WeaponSettings[playerid][enum_index][duzenlendi])
			{
				WeaponSettings[playerid][enum_index][duzenlendi] = 1;
				mysql_format(dbHandle, string, sizeof(string), "INSERT INTO weaponsettings (sOwner, WeaponID, PosX, PosY, PosZ, RotX, RotY, RotZ, Bone, duzenlendi) VALUES (%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, 1, %d)", PlayerInfo[playerid][pID], weaponid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, WeaponSettings[playerid][enum_index][duzenlendi]);
				mysql_tquery(dbHandle, string);
			}
		}
		EditingWeapon[playerid] = 0;
		return 1;
	}
	return 1;
}

Weapon_OnPlayerDamage(&playerid, &Float:amount, &issuerid, &WEAPON:weapon, &bodypart)
{
	if (IsPlayerAFK(playerid))				   return 1;
	if (pTemp[playerid][pInvulnerable] != 0.0) return 1;
	
	if (issuerid != INVALID_PLAYER_ID)
	{		
		if (PlayerInfo[issuerid][pInjured] > 0) return 1;	
	    if (issuerid != INVALID_PLAYER_ID && weapon != 54 && IsPlayerAFK(issuerid))                 return 1; 

		new Float:health, Float:armour;

		health = PlayerInfo[playerid][pHealth];
		AntiCheatGetArmour(playerid, armour);
 
        pTemp[playerid][pInjureText] = 1;

		new Float:target_x, Float:target_y, Float:target_z, Float:distance;

		GetPlayerPos(playerid, target_x, target_y, target_z);
		distance = floatround(GetPlayerDistanceFromPoint(issuerid, target_x, target_y, target_z), floatround_round);	
		
	    if (PlayerInfo[playerid][pInjured] == 1 || PlayerInfo[playerid][pInjured] == 3)
		{
		    PlayerInfo[playerid][pHealth] = 100.0;

		    PlayerInfo[playerid][pInjured] = 2;
			PlayerInfo[issuerid][pDeathReason] = weapon;
			
			SQL_SetInteger("users", "deathreason", weapon, PlayerInfo[issuerid][pID]);

			AC_ResetPlayerWeapons(playerid);
			SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

			SM3(playerid, "Yaralýyken hasar aldýðýnýz için karakteriniz aðýr yaralý duruma geçti.");
			ApplyAnimation(playerid,"PARACHUTE","FALL_skyDive_DIE",3.5,0,0,0,1,0);
			return 1;
		}

		if (PlayerInfo[playerid][pInjured] == 2)
		{
		    PlayerInfo[playerid][pHealth] = 9999.0;
		    return 1;
		}

        if (weapon == 23 && pTemp[issuerid][pTaser])
		{
		    //health = health;
            SetPlayerArmour(playerid, armour);

            if (!PlayerNearPlayer(10.0, playerid, issuerid))	return SM1(issuerid, "Kiþinin mesafesi size çok uzak.");

            new vehicle = GetPlayerVehicleID(playerid);

			if (vehicle && !IsABiker(vehicle) && !IsABicycle(vehicle))	return 1;
            if (pTemp[playerid][pTaserTime])							return SM1(issuerid, "Bu kiþi zaten taser etkisinde.");
            if (vehicle)												RemovePlayerFromVehicle(playerid);

            PlayerPlaySound(playerid, 6003, 0.0, 0.0, 0.0);
            SavePlayerPos(playerid);
            ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);
            pTemp[playerid][pTaserTime] = 10;
			pc_cmd_me(playerid, "elektrik þokuyla birlikte yere yýðýlýr.");
			SetPlayerDrunkLevel(playerid, 2500);
		    return 1;
		}
		else if (weapon == 25 && pTemp[issuerid][pBeanbag])
		{
		    //SetPlayerHealth(playerid, health);
            SetPlayerArmour(playerid, armour);

            if (!PlayerNearPlayer(20.0, playerid, issuerid))	return SM1(issuerid, "Kiþinin mesafesi size çok uzak.");

            new vehicle = GetPlayerVehicleID(playerid);

			if (vehicle && !IsABiker(vehicle) && !IsABicycle(vehicle))	return 1;
            if (pTemp[playerid][pTaserTime])							return SM1(issuerid, "Bu kiþi zaten beanbag etkisinde.");
            if (vehicle)												RemovePlayerFromVehicle(playerid);

            SavePlayerPos(playerid);
            ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);
            pTemp[playerid][pTaserTime] = 15;
			pc_cmd_me(playerid, "plastik merminin etkisiyle yere yýðýlýr.");
			SetPlayerDrunkLevel(playerid, 2500);
		    return 1;			
		}
		else if (weapon == 33 && pTemp[issuerid][pLTL])
		{
		    //SetPlayerHealth(playerid, health);
            SetPlayerArmour(playerid, armour);

            if (!PlayerNearPlayer(30.0, playerid, issuerid))	return SM1(issuerid, "Kiþinin mesafesi size çok uzak.");

            new vehicle = GetPlayerVehicleID(playerid);

			if (vehicle && !IsABiker(vehicle) && !IsABicycle(vehicle))	return 1;
            if (pTemp[playerid][pTaserTime])							return SM1(issuerid, "Bu kiþi zaten beanbag etkisinde.");
            if (vehicle)												RemovePlayerFromVehicle(playerid);

            SavePlayerPos(playerid);
            ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);
            pTemp[playerid][pTaserTime] = 20;
			pc_cmd_me(playerid, "plastik kapsülün etkisiyle yere yýðýlýr.");
			SetPlayerDrunkLevel(playerid, 2500);
		    return 1;			
		}		
        else if ((weapon == 0 || weapon == 3) && pTemp[issuerid][pTackleMode])
		{
		    //SetPlayerHealth(playerid, health);
            SetPlayerArmour(playerid, armour);

            if (!PlayerNearPlayer(10.0, playerid, issuerid))	return SM1(issuerid, "Kiþinin mesafesi size çok uzak.");

            new vehicle = GetPlayerVehicleID(playerid);

			if (vehicle && !IsABiker(vehicle) && !IsABicycle(vehicle))	return 1;
            if (pTemp[playerid][pTaserTime])							return SM1(issuerid, "Bu kiþi zaten baygýnlýk etkisinde.");
            if (vehicle)												RemovePlayerFromVehicle(playerid);

            SavePlayerPos(playerid);
            ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 1, 0);
            pTemp[playerid][pTaserTime] = 10;

			pTemp[issuerid][pTackleMode] = !pTemp[issuerid][pTackleMode];
			
			pc_cmd_me(playerid, "üzerine yýðýlan polis memurunun etkisiyle yere düþer.");
			SetPlayerDrunkLevel(playerid, 2500);
		    return 1;
		}		

        if ((bodypart == 7 || bodypart == 8) && pTemp[playerid][pInjuredLegTime] == 0)
		{
		    SM3(playerid, "Bacaðýnýzdan hasar aldýnýz ve 30 saniye boyunca koþamayacaksýnýz.");
    		pTemp[playerid][pInjuredLegTime] = INJURED_LEG_TIME;
		}
		
		switch(weapon)
		{
		    case 0: amount = float(randomEx(15, 30))/10.0; // Fist
			case 1: amount = 5.0; // Brass Knuckles
			case 2: amount = 5.0; // Gîlf Club
			case 3: amount = 6.0; // Nightstick
			case 4: amount = 7.0; // Knife
			case 5: amount = 5.0; // Baseball Bat
			case 6: amount = 5.0; // Shovel
			case 7: amount = 5.0; // Pool Cue
			case 8: amount = 8.0; // Katana
			case 9: amount = 10.0; // Chainsaw
			case 14: amount = 2.0; // Flowers
			case 15: amount = 5.0; // Cane
			case 16: amount = 50.0; // Grenade
			case 18: amount = 20.0; // Molotov
			case 22: amount = float(randomEx(15, 20)); 				// M1911
			case 23, 28, 29, 32: amount = float(randomEx(17, 23)); 	// SD Pistol, UZI, MP5, Tec
			case 24: amount = float(randomEx(38, 43)); 				// Desert Eagle
			case 25, 26, 27: // Shotgun, Sawnoff Shotgun, CombatShotgun
			{
			    new Float: p_x, Float: p_y, Float: p_z;
			    GetPlayerPos(issuerid, p_x, p_y, p_z);
			    new Float: dist = GetPlayerDistanceFromPoint(playerid, p_x, p_y, p_z);

			    if (dist < 5.0)			amount = float(randomEx(50, 55));
				else if (dist < 10.0)	amount = float(randomEx(23, 35));
				else if (dist < 15.0)	amount = float(randomEx(15, 25));
				else if (dist < 20.0)	amount = float(randomEx(10, 15));
				else if (dist < 30.0)	amount = float(randomEx(5, 8));
			}
			case 30: amount = float(randomEx(20, 25)); // AK47
			case 31: amount = float(randomEx(20, 22)); // M4A1
			case 33, 34: amount = float(randomEx(70, 75)); // Country Rifle, Sniper Rifle
			case 35: amount = 0.0; // RPG
			case 36: amount = 0.0; // HS Rocket
			case 38: amount = 0.0; // Minigun
		}

		switch(bodypart)
        {
			case BODY_PART_HEAD: amount = amount * 1.2;
			case BODY_PART_LEFT_LEG, BODY_PART_RIGHT_LEG: amount = amount * 0.8;
		}	

		switch(distance)
		{
			case 46..70:
			{
				if(weapon != WEAPON_SNIPER && weapon != WEAPON_RIFLE) amount = amount * 0.74;
				else if(weapon == WEAPON_M4 || weapon == WEAPON_AK47 || weapon == WEAPON_SHOTGUN) amount = amount * 0.79;
			}
			case 71..200:
			{
				if(weapon != WEAPON_SNIPER && weapon != WEAPON_RIFLE) amount = amount * 0.70;
				else if(weapon == WEAPON_M4 || weapon == WEAPON_AK47 || weapon == WEAPON_SHOTGUN) amount = amount * 0.74;
			}
		}		

        if (bodypart == BODY_PART_TORSO && armour > 0.0 && (22 <= weapon <= 38))
		{
		    if (armour - amount <= 0.0)	SetPlayerArmour(playerid, 0.0);
	 		else						SetPlayerArmour(playerid, armour - (amount / 2));

            //SetPlayerHealth(playerid, health);
			RecordDamage(issuerid, playerid, weapon, bodypart, amount, 1);
		}
		else
		{
		    if (PlayerInfo[playerid][pHealth] - amount < 5.0)	
			{
				PlayerInfo[playerid][pHealth] = 30;
				SilahlariKaydet(playerid);
				InjuredPlayer(playerid, issuerid, weapon);
				RecordDamage(issuerid, playerid, weapon, bodypart, amount, 0);
				return 1;
			}
			else {
				new Float:hyperx;
				hyperx = PlayerInfo[playerid][pHealth];
				PlayerInfo[playerid][pHealth] = hyperx - amount;
			}
			if (armour) SetPlayerArmour(playerid, armour);

			if (pTemp[playerid][pInjureText] == 1  && health - amount <= 30.0 && health - amount >= 16.0)
			{
				SM3(playerid, "Canýnýz çok azaldý, silah yeteneðinin normal seviyeye düþtü.");
				SetPlayerSkill(playerid, 2);
				pTemp[playerid][pInjureText] = 2;
			}
			else if (pTemp[playerid][pInjureText] == 2 && health - amount < 16.0)
			{
				SM3(playerid, "Canýnýz çok azaldý, silah yeteneklerin en minimal hale getirildi.");
				SetPlayerSkill(playerid, 3);
				pTemp[playerid][pInjureText] = 3;
			}	

			RecordDamage(issuerid, playerid, weapon, bodypart, amount, 0);
		}
	}
    return 1;
}

Weapon_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if (IsPlayerAFK(playerid))	return 0;

	if(!Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]]) // Not given by the server or removed? Don't sync the bullets.
	{
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] <= 0)
			PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");

		return 0;
	}
	else // Otherwise...
	{
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] > 1) // The idea here is to remove the weapon if there is no server ammo, so bullets won't be synced.
		{
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]]--;
			if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] <= 0) PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");

			if(PlayerInfo[playerid][pOnDuty] == 0)
			{
				new omur_kontrol[200];
				mysql_format(dbHandle, omur_kontrol, sizeof(omur_kontrol), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0' AND omur < 6", PlayerInfo[playerid][pID]);
				new Cache:veri = mysql_query(dbHandle, omur_kontrol, true);
				new rows;
				cache_get_row_count(rows);
				if(rows)
				{
					SetPlayerAmmo(playerid, weaponid, 0);
					Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]] = false;
					PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
					if(!PlayerInfo[playerid][pOnDuty] && SilahSlotBul(weaponid) > 1 && PlayerInfo[playerid][pSilahSistemi])
					{
						new sorgu[250];
						mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE weapons SET status = '10', omur = '0' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", weaponid, PlayerInfo[playerid][pID]);
						mysql_tquery(dbHandle, sorgu);
						SendClientMessageEx(playerid, COLOUR_TOMATO, "%s model silahýnýzýn ömrü tükendi ve kullanýlmaz hale geldi.", GetWeaponNameEx(weaponid));
					}		
				}
				cache_delete(veri);
			}


			if(!PlayerInfo[playerid][pOnDuty] && SilahSlotBul(weaponid) > 1 && PlayerInfo[playerid][pSilahSistemi])
			{
				new sorgu[100];
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE weapons SET ammo = ammo - 1 WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", weaponid, PlayerInfo[playerid][pID]);
				mysql_tquery(dbHandle, sorgu);
				if(weaponid == 22 || weaponid == 23 || weaponid == 24 || weaponid == 25 || weaponid == 26 || weaponid == 27 || weaponid == 33 || weaponid == 34)
				{
					new sorgu_omur[150];
					mysql_format(dbHandle, sorgu_omur, sizeof(sorgu_omur), "UPDATE weapons SET omur = omur - %d WHERE weaponid = '%d' AND owner = '%d' AND status = '0' AND lisans = '0'", randomEx(7, 18), weaponid, PlayerInfo[playerid][pID]);
					mysql_tquery(dbHandle, sorgu_omur);
				}
				else if(weaponid == 28 || weaponid == 29 || weaponid == 30 || weaponid == 31 || weaponid == 32)
				{
					new sorgu_omur[150];
					mysql_format(dbHandle, sorgu_omur, sizeof(sorgu_omur), "UPDATE weapons SET omur = omur - %d WHERE weaponid = '%d' AND owner = '%d' AND status = '0' AND lisans = '0'", randomEx(3, 9), weaponid, PlayerInfo[playerid][pID]);
					mysql_tquery(dbHandle, sorgu_omur);
				}
			}
		}
		else
		{
			PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
			Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]] = false;
			SetPlayerAmmo(playerid, weaponid, 0); // To ensure it is removed.
			if(!PlayerInfo[playerid][pOnDuty] && SilahSlotBul(weaponid) != 0 && PlayerInfo[playerid][pSilahSistemi])
			{
				new sorgu[100];
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE weapons SET ammo = '0' WHERE weaponid = '%d' and owner = '%d' and status = '0'", weaponid, PlayerInfo[playerid][pID]);
				mysql_tquery(dbHandle, sorgu);
			}
		}

		if(weaponid == 25 && Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] <= 1 || weaponid == 26 && Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] <= 1)
		{
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] = 0;
			PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
			Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]] = false;
			SetPlayerAmmo(playerid, weaponid, 0); // To ensure it is removed.
			if(!PlayerInfo[playerid][pOnDuty] && SilahSlotBul(weaponid) != 0 && PlayerInfo[playerid][pSilahSistemi])
			{
				new sorgu[100];
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE weapons SET ammo = '0' WHERE weaponid = '%d' and owner = '%d' and status = '0'", weaponid, PlayerInfo[playerid][pID]);
				mysql_tquery(dbHandle, sorgu);
			}
		}
	}

    if (hittype == BULLET_HIT_TYPE_PLAYER)
    {
        if ((floatcmp(floatabs(fX), 20.0) == 1) || (floatcmp(floatabs(fY), 20.0) == 1) || (floatcmp(floatabs(fZ), 20.0) == 1)) return KickEx(playerid), 0;
    }
    
	if (weaponid < 22 || weaponid > 38) return 0;
	
	if(!IsPlayerInAnyVehicle(playerid) && hittype == BULLET_HIT_TYPE_PLAYER && !IsPlayerInAnyVehicle(hitid) && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && GetPlayerSurfingVehicleID(hitid) == INVALID_VEHICLE_ID && NetStats_PacketLossPercent(hitid) < 0.7 && NetStats_PacketLossPercent(playerid) < 0.7)
	{
		new Float:g_fOriginX, Float:g_fOriginY, Float:g_fOriginZ;
		new Float:g_fHitPosX, Float:g_fHitPosY, Float:g_fHitPosZ;

		GetPlayerLastShotVectors(playerid, g_fOriginX, g_fOriginY, g_fOriginZ, g_fHitPosX, g_fHitPosY, g_fHitPosZ);

		if(IsPlayerInRangeOfPoint(hitid, 3.0, g_fHitPosX, g_fHitPosY, g_fHitPosZ) == 0)
			SendAdmMessage("%s adlý kiþi silent-aim olabilir.", GetNameEx(playerid));
	}

	if (weaponid == 23 && pTemp[playerid][pTaser])
	{
	    PlayerPlaySound(playerid, 6003, 0.0, 0.0, 0.0);
	    ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0, 1);
	}

	if (PlayerInfo[playerid][pInjured] != 0)
	{
	    if (!PlayerToPoint(2.0, playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ])) SetPlayerPosEx(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
	    
		//ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 1, 1, 1, 1, 0, 1);
	    return 0;
	}

	if (hittype == BULLET_HIT_TYPE_VEHICLE && hitid != INVALID_VEHICLE_ID)
	{
	    new Float: health;

	    AntiCheatGetVehicleHealth(hitid, health);
		
	    return (health < 350.0)?(0):(1);
	}

	if(GetPlayerVehicleSeat(playerid) == 0)
	{
		SendAdmMessage("%s [%d] adlý oyuncu þoför koltuðunda drive bya kalktý. (/spec %d)", GetNameEx(playerid), playerid, playerid);
    	KickEx(playerid);
		return 0;
	}


    return 1;
}

Weapon_OnPlayerStateChange(playerid, newstate)
{
    if (newstate == PLAYER_STATE_DRIVER)
    {
        if (GetPlayerWeapon(playerid) == 24) SetPlayerArmedWeapon(playerid, 0);
    }
    return 1;
}

Weapon_OnPlayerExitVehicle(playerid, vehicleid)
{
    if (IsAPlane(vehicleid) || IsAHelicopter(vehicleid)) ResetPlayerWeapons(playerid);
	
    return 1;
} 