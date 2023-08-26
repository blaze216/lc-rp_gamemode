Death_PlayerTimer(playerid)
{
    if (PlayerInfo[playerid][pInjured] == 1)
	{
		if (IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PED", "CAR_DEAD_LHS", 4.0, 1, 0, 0, 0, 0, 1);	
		else
		{							
			if (!PlayerToPoint(2.0, playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]))
			{
				SetPlayerPosFindZ(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
			}
			ApplyAnimation(playerid, "WUZI",  "CS_Dead_Guy", 4.1, 1, 0, 0, 1, 0, 1);
		}
		
		static const str_damage[] = "(( Bu kiþi %i kez hasar aldý, /hasarlar %i ile hasarlarý görebilirsin ))"; // 0xFF6347FF
    	new mes_damage[sizeof(str_damage) + 4 + 4];
   		format(mes_damage, sizeof(mes_damage), str_damage, pTemp[playerid][pDamagesCount], playerid);
    	SetPlayerChatBubble(playerid, mes_damage, 0xFF6347FF, 10.0, 1500);
    }

	else if (PlayerInfo[playerid][pInjured] == 2)
	{
		if (IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PED", "CAR_DEAD_LHS", 4.0, 1, 0, 0, 0, 0, 1);	
		else
		{
			if (!PlayerToPoint(2.0, playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]))
			{
				SetPlayerPosFindZ(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
			} 
			ApplyAnimation(playerid, "WUZI",  "CS_Dead_Guy", 4.1, 1, 0, 0, 1, 0, 1);
		}
		 
		SetPlayerChatBubble(playerid, "(( Bu karakter artýk aðýr yaralý ))", 0xFF6347FF, 10.0, 1500); // // 0xFF6347FF
    }
	
	else if (PlayerInfo[playerid][pInjured] == 3)
	{
		if (!PlayerToPoint(2.0, playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]))
		{
			SetPlayerPosFindZ(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
		}

		ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.1, 1, 0, 0, 1, 0, 1);
		
		static const str_damage[] = "(( %i saniye önce yaralandý. ))"; // 0xFF6347FF
    	new mes_damage[sizeof(str_damage) + 4 + 4];
   		format(mes_damage, sizeof(mes_damage), str_damage, pTemp[playerid][pDamagesCount]);
    	SetPlayerChatBubble(playerid, mes_damage, 0xFF6347FF, 10.0, 1500);
    }
    return 1;
}

Death_OnPlayerDeath(playerid, killerid, reason)
{
	if(gettime() - pTemp[playerid][OlumSuresi] < 5)
	{
		pTemp[playerid][OlumSayisi]++;
		if(pTemp[playerid][OlumSayisi] > 2)
		{
			SendAdmMessage("[Anti-Cheat] %s (%s), Fake-Kill radarýna takýldý. Ýzle! Saldýrý yapýyor olabilir!", GetNameEx(playerid), PlayerInfo[playerid][pAccname]);		
		}
	}
	else pTemp[playerid][OlumSayisi] = 0;

	pTemp[playerid][OlumSuresi] = gettime();

    ResetVariables(playerid);
	ResetPlayerWeapons(playerid);
	RemovePlayerMask(playerid);
	SilahlariKaydet(playerid);

	if ((reason == WEAPON_VEHICLE || reason == WEAPON_COLLISION) && PlayerInfo[playerid][pInjured] == 0) 
		SetTimerEx("InjuredPlayer", 1200, 0, "iii", playerid, killerid, reason);

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || pTemp[i][pDMLog] != 1) continue;
        
		SendDeathMessageToPlayer(i, killerid, playerid, reason);
	}
    return 1;
}

StartProgress(playerid, userid, type, animation)
{
	if (pTemp[playerid][pHelpUp3dText] != 0) return SendErrorMessage(playerid,"Bu komut þu anda kullanýlamaz.");

	pTemp[playerid][pHelpUp3dText] = type;
	SetPVarInt(playerid, #player_upgrade_timer, 0);
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	ApplyAnimation(userid,"MEDIC","CPR",4.0,0,0,0,0,0);

	if (IsValidDynamic3DTextLabel(status_upd[playerid])) DestroyDynamic3DTextLabel(status_upd[playerid]);
	status_upd[playerid] = CreateDynamic3DTextLabel("(( ---------- ))", 0x33AA33FF, x, y, z-0.5, 15.0, playerid, INVALID_VEHICLE_ID, 1, GetWorld(playerid), GetInterior(playerid));

	SetTimerEx("PlayerUpgrade", 1, 0, "iii", userid, playerid, animation);
	return 1;
}

this::PlayerUpgrade(playerid, userid, animation)
{
	if (!PlayerInfo[playerid][pInjured] || GetPlayerAnimationIndex(userid) != animation || !PlayerNearPlayer(3.0, playerid, userid))
	{
	    DeletePVar(playerid, #player_upgrade_timer);
		if (IsValidDynamic3DTextLabel(status_upd[playerid])) DestroyDynamic3DTextLabel(status_upd[playerid]);
		pTemp[playerid][pHelpUp3dText] = 0;
		return 1;
	}
	/*if (!PlayerInfo[playerid][pInjured])					SM1(playerid, "1");
	if (GetPlayerAnimationIndex(userid) != animation)	SM1(playerid, "2");
	if (!PlayerNearPlayer(3.0, playerid, userid))		SM1(playerid, "3");*/

	new upgrade_name[2][32] = {
		"YARDIM EDÝYOR", "TEDAVÝ EDÝYOR"
	};

	new string[128] = "(( ", 
		uptime = 1000,
		upgrade = 0;


	for(new i; i != 10; i++)
	{
	    if (GetPVarInt(playerid, #player_upgrade_timer) >= i)	strcat(string, "I");
		else													strcat(string, "-");
	}

	format(string, sizeof(string), "%s ))\n%s", string, upgrade_name[pTemp[playerid][pHelpUp3dText]-1]);
	UpdateDynamic3DTextLabelText(status_upd[playerid], 0x33AA33FF, string);
	SetPVarInt(playerid, #player_upgrade_timer, GetPVarInt(playerid, #player_upgrade_timer) + 1);

	if (GetPVarInt(playerid, #player_upgrade_timer) == 11)
	{
	    upgrade = pTemp[playerid][pHelpUp3dText];
	    DeletePVar(playerid, #player_upgrade_timer);
		if (IsValidDynamic3DTextLabel(status_upd[playerid])) DestroyDynamic3DTextLabel(status_upd[playerid]);
		pTemp[playerid][pHelpUp3dText] = 0;
	}
	else SetTimerEx("PlayerUpgrade", uptime, 0, "iii", playerid, userid, animation);
	
	if (upgrade == 0) 
	{
		return 1;
	}
	else if (upgrade == 1)
	{	
		PlayerInfo[playerid][pInjured] = 0;
		PlayerInfo[playerid][pHealth] = 30.0;
		StopPlayerAnims(playerid);
		StopPlayerAnims(userid);
		UnFreezePlayer(playerid);
		
		SM1(playerid, "%s kalkmana yardým etti.", GetNameWithMask(userid));
		SM1(userid, "%s adlý kiþinin yerden kalkmasýna yardým ettin. ", GetNameWithMask(playerid));
		return 1;
	}
	else if (upgrade == 2)
	{
		return 1;
	}

	return 1;
}