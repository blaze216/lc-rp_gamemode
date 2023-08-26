ResetDamages(playerid)
{
	for(new i = 0; i != MAX_DAMAGES; i++)
	{
	    if (DamageInfo[playerid][i][damageOn] == 0) continue;

		DamageInfo[playerid][i][damageBy] = EOS;
        DamageInfo[playerid][i][damageOn] = 0;
        DamageInfo[playerid][i][damageWeapon] = 0;
        DamageInfo[playerid][i][damageAmount] = 0.0;
        DamageInfo[playerid][i][damageArmour] = 0;
		DamageInfo[playerid][i][damageTime] = 0;
	}

	pTemp[playerid][pDamagesCount] = 0;
	pTemp[playerid][pInjuredTime] = 0;
    pTemp[playerid][pInjuredLegTime] = 0;
	PlayerInfo[playerid][pInjured] = 0;
	PlayerInfo[playerid][pDeathReason] = 0;
	pTemp[playerid][pInjureText] = 0;
	return 1;
}

ResetDamage(playerid, i)
{
	if (!DamageInfo[playerid][i][damageOn])	return 1;

	DamageInfo[playerid][i][damageBy] = EOS;
	DamageInfo[playerid][i][damageOn] = 0;
	DamageInfo[playerid][i][damageWeapon] = 0;
	DamageInfo[playerid][i][damageAmount] = 0.0;
	DamageInfo[playerid][i][damageArmour] = 0;
	DamageInfo[playerid][i][damageTime] = 0;
	
	return 1;
}

UpdateInjured(playerid)
{
	SQL_SetInteger("users", "injured", PlayerInfo[playerid][pInjured], PlayerInfo[playerid][pID]);
	SQL_SetInteger("users", "deathreason", PlayerInfo[playerid][pDeathReason], PlayerInfo[playerid][pID]);	
	return 1;
}

GetBodyPartName(bodypart)
{
	new part[15];
	switch(bodypart)
	{
		case BODY_PART_TORSO: 		part = "Gövde";		
		case BODY_PART_GROIN: 		part = "Kasýk";			
		case BODY_PART_LEFT_ARM: 	part = "Sol Kol";	
		case BODY_PART_RIGHT_ARM: 	part = "Sað Kol";	
		case BODY_PART_LEFT_LEG: 	part = "Sol Bacak";	
		case BODY_PART_RIGHT_LEG: 	part = "Sað Bacak";	
		case BODY_PART_HEAD: 		part = "Kafa";		
		default: 					part = "Belirsiz";	
	}
	return part;
}

DisplayDamages(toplayer, playerid)
{
	new maxpages = floatround(MAX_DAMAGES/MAX_DIALOG_LIST,floatround_ceil);
	if (pTemp[toplayer][pDialogList] < 0 || (maxpages < pTemp[toplayer][pDialogList]+1)) return 1;
	
	new 
		title[256], 
		start_itter = MAX_DIALOG_LIST * pTemp[playerid][pDialogList],
		end_itter = (maxpages == pTemp[playerid][pDialogList]+1) ? (MAX_DAMAGES) : (start_itter+MAX_DIALOG_LIST+1),
		count, 
		str[(MAX_PLAYER_NAME + 65) * MAX_DIALOG_LIST + 71 + 1555] = "Hasar\tBölge\tSilah\tHasar Veren\t.\n",
		weaponname[64]
	;

	format(title, sizeof(title), "{FFFFFF}%s - Son 10 hasar", GetNameEx(playerid));

	if (pTemp[toplayer][pDialogList]) format(str, sizeof(str), "%s{bccd32}Önceki sayfa{FFFFFF}\n", str);

	for(new i =0; i < 10; i++)
	{
	    if (DamageInfo[playerid][i][damageOn] != 1) continue;

		if (gettime()-DamageInfo[playerid][i][damageTime] > 3600) ResetDamage(playerid, i);
		else
		{
			if (count == MAX_DIALOG_LIST) {
				strcat(str, "{bccd32}Sonraki sayfa");
			} else {
				new weaponid = DamageInfo[playerid][i][damageWeapon];

				if (weaponid == 0) format(weaponname, sizeof(weaponname), "Yumruk");
				else format(weaponname, sizeof(weaponname), "%s", GetWeaponNameEx(weaponid));
				
				new stradmin[3 + MAX_PLAYER_NAME] = EOS;
				if (CheckAdmin(toplayer, 1))  format(stradmin, sizeof(stradmin), "[%s]", DamageInfo[playerid][i][damageBy]);
				if (DamageInfo[playerid][i][damageWeapon] == 51)	format(str, sizeof(str), "%s\t%.0f\t%s\tYanma - %d saniye önce\t%s\n", str, DamageInfo[playerid][i][damageAmount], GetBodyPartName(DamageInfo[playerid][i][damageBodypart]), gettime()-DamageInfo[playerid][i][damageTime], stradmin);
				else if (!DamageInfo[playerid][i][damageArmour])	format(str, sizeof(str), "%s\t%.0f\t%s\t%s - %d saniye önce\t%s\n", str, DamageInfo[playerid][i][damageAmount], GetBodyPartName(DamageInfo[playerid][i][damageBodypart]), weaponname, gettime()-DamageInfo[playerid][i][damageTime], stradmin);
				else 											format(str, sizeof(str), "%s\t%.0f\t%s\t%s - %d saniye önce\t%s\n", str, DamageInfo[playerid][i][damageAmount], GetBodyPartName(DamageInfo[playerid][i][damageBodypart]), weaponname, gettime()-DamageInfo[playerid][i][damageTime], stradmin);
				
				count++;
			}
		}
	}

	if (!count) return Dialog_Show(toplayer, None, DIALOG_STYLE_LIST, title, "Herhangi bir hasar mevcut deðil...", ">>>", "");

	SetPVarInt(toplayer, #userid, playerid);
    Dialog_Show(toplayer, DamageDialog, DIALOG_STYLE_TABLIST_HEADERS, title, str, ">>>", "");
	return 1;
}

Dialog:DamageDialog(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	if (pTemp[playerid][pDialogList]) {			//if not first page
		if (listitem == 0) {
			pTemp[playerid][pDialogList]--;
			return DisplayDamages(playerid, GetPVarInt(playerid, #userid));
		} else if (listitem == MAX_DIALOG_LIST+1) {
			pTemp[playerid][pDialogList]++;
			return DisplayDamages(playerid, GetPVarInt(playerid, #userid));
		}
	} else { 									//if it's a first page
		if (listitem == MAX_DIALOG_LIST) {
			pTemp[playerid][pDialogList]++;
			return DisplayDamages(playerid, GetPVarInt(playerid, #userid));
		}
	}

	return 1;
}

CountDamageRecord(playerid)
{
	new count = 0;
	for(new i = 0; i != MAX_DAMAGES; i++)
	{
		if (DamageInfo[playerid][i][damageOn] == 1)  count++;
	}
	return count;
}

RecordDamage(userid, playerid, weaponid, bodypart, Float: amount, armour)
{
	for(new i = 0; i != MAX_DAMAGES; i++)
	{
		if (DamageInfo[playerid][i][damageOn] == 1 && gettime()-DamageInfo[playerid][i][damageTime] > 3600) ResetDamage(playerid, i);

	    if (DamageInfo[playerid][i][damageOn] == 1)  continue;

        DamageInfo[playerid][i][damageOn] = 1;
		
		if (userid != -1) format(DamageInfo[playerid][i][damageBy], MAX_PLAYER_NAME, "%s",  GetNameEx(userid));
		else 			 format(DamageInfo[playerid][i][damageBy], MAX_PLAYER_NAME, "yanarak");

		DamageInfo[playerid][i][damageWeapon] = weaponid;
		DamageInfo[playerid][i][damageBodypart] = bodypart;
		DamageInfo[playerid][i][damageAmount] = amount;
		DamageInfo[playerid][i][damageArmour] = armour;
		DamageInfo[playerid][i][damageTime] = gettime();
		pTemp[playerid][pDamagesCount]++;
		return 1;
    }
	
    return 1;
}

Death_OnPlayerExitVehicle(playerid, vehicleid)
{
	if (PlayerInfo[playerid][pInjured]) {
		UnFreezePlayer(playerid);

		new Float:ccX, Float:ccY, Float:ccZ;
		new Float:dX, Float:dY, Float:dZ;
		
		GetVehicleModelInfo(VehicleInfo[vehicleid][carModel], VEHICLE_MODEL_INFO_FRONTSEAT, ccX, ccY, ccZ);
		GetVehicleRelativePos(vehicleid, dX, dY, dZ, -ccX - 1, ccY, ccZ);
		
		SetPlayerPosEx(playerid, dX, dY, dZ);
		//SetPlayerPosFindZ(playerid, 1234.5, 1234.5, 1000.0);
		
		ApplyAnimation(playerid, "PED", "KO_SHOT_STOM", 4.0, 1, 0, 0, 0, 0, 1);

		SavePlayerPos(playerid);
	}
	return 1;
}

this::InjuredPlayer(playerid, killerid, weaponid)
{
	if (!IsPlayerLogged(playerid)) return 1;
	if (IsValidVehicle(JackingVehicle[playerid])) StopJackingLock(playerid);

	pTemp[playerid][AntiHileSistemi] = -1;

	ResetVariables(playerid);
	RemovePlayerMask(playerid);
	
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || pTemp[i][pDMLog] != 1) continue;
		SendDeathMessageToPlayer(i, killerid, playerid, weaponid);
	}

	SavePlayerPos(playerid);
	PlayerInfo[playerid][pDeathReason] = weaponid;
	SQL_SetInteger("users", "deathreason", weaponid, PlayerInfo[playerid][pID]);

	new weapons[12], ammo[12];
	for(new x; x < 12; x++)
	{
		BWH_GetPlayerWeaponData(playerid, x, weapons[x], ammo[x]);
		if(!AC_PlayerHasWeapon(playerid, weapons[x]) || !ammo[x])
		{
			weapons[x] = 0;
			ammo[x] = 0;
		}
		PlayerInfo[playerid][pWeapons][x] = weapons[x];
		PlayerInfo[playerid][pAmmo][x] = ammo[x];
	}

	if (Check_KO(playerid)) {
		GameTextForPlayer(playerid, "~r~NAKAVT OLDUN", 5000, 3);

		ApplyAnimation(playerid,"SWEET", "Sweet_injuredloop",4.0,0,1,1,1,0);

		pTemp[playerid][pInvulnerable] = 15.0;
		PlayerInfo[playerid][pInjured] = 3;
		pTemp[playerid][pInjuredTime] = 60;
		SetCameraBehindPlayer(playerid);

		pTemp[playerid][pInjureText] = 0;
		SendClientMessageEx(playerid, COLOR_LIGHTRED,"[ ! ] >> {FFFFFF}Nakavt oldun, 60 saniye sonra kalkabilirsin veya biri sana yardým edebilir");
		SendClientMessageEx(playerid, COLOR_LIGHTRED,"[ ! ] >> {FFFFFF}%i kez hasar alarak yaralandýnýz, detaylý bilgi için /hasarlar %i kullanýn", pTemp[playerid][pDamagesCount], playerid);
	} else {
		GameTextForPlayer(playerid, "~b~YARALANDIN", 5000, 3); //ñìýðòü

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && GetPlayerState(playerid) != PLAYER_STATE_PASSENGER) ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 0, 1);
        else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)  ApplyAnimation(playerid, "PED", "CAR_dead_RHS", 4.1, 1, 1, 1, 1, 0, 1);    
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
		{
            new aracid = GetPlayerVehicleID(playerid);
            if (VehicleInfo[aracid][carEngineOn]) ToggleVehicleEngine(aracid, playerid);
            if(Arac_Model(VehicleInfo[aracid][carModel]) == VEHICLE_TYPE_BIKE || Arac_Model(VehicleInfo[aracid][carModel]) == VEHICLE_TYPE_MBIKE) ClearAnimations(playerid, 1), ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 0, 1);
        }	
		
		pTemp[playerid][pInvulnerable] = 100.0;
		PlayerInfo[playerid][pInjured] = 1;
		pTemp[playerid][pInjuredTime] = 60;
		SetCameraBehindPlayer(playerid);

		SendClientMessageEx(playerid, COLOR_LIGHTRED,"[ ! ] >> {FFFFFF}Yaralandýn ve yere yýðýldýn. Bir ambulans bekleyebilirsiniz veya \"/tedaviol\".");
		SendClientMessageEx(playerid, COLOR_LIGHTRED,"[ ! ] >> {FFFFFF}%i kez hasar alarak yaralandýnýz, detaylý bilgi için /hasarlar %i kullanýn", pTemp[playerid][pDamagesCount], playerid);
	}

	if(PlayerInfo[playerid][pChar] > 0 && PlayerInfo[playerid][pOnDuty]) SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	else SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	
    pTemp[playerid][pInjuredLegTime] = 0;
	TogglePlayerControllable(playerid, false);

	pTemp[playerid][OlumSuresi] = gettime();
	
	PlayerInfo[playerid][pHealth] = 100;
	SetPlayerHealth(playerid, 100);
	SetTimerEx("Invulnerable", 4000, false, "i", playerid);
	return 1;
}

Check_KO(playerid)
{
	if (PlayerInfo[playerid][pInjured])	return 0;
	if (IsPlayerInAnyVehicle(playerid))	return 0;

	new Float:m_damage, Float:a_damage;

	for(new i = CountDamageRecord(playerid)-1; i >= 0; i--)
	{
		if (DamageInfo[playerid][i][damageOn] != 1) continue;
		if (gettime()-DamageInfo[playerid][i][damageTime] > 5*60) continue;
		
		switch(DamageInfo[playerid][i][damageWeapon]) {
			case 0 .. 9: 	m_damage += DamageInfo[playerid][i][damageAmount];
			default:		a_damage += DamageInfo[playerid][i][damageAmount];
		}
	}

	if (m_damage > 20.0 && m_damage > a_damage) return 1;
	return 0;
}