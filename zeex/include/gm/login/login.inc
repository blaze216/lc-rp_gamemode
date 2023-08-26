/*Internal*/
static BWH_memset(variable[], cells, value) // Slice - http://forum.sa-mp.com/showpost.php?p=1974747
{
	new address;

	#emit LOAD.S.pri  variable
	#emit STOR.S.pri  address

	BWH_raw_memset(address, cells, value);
}

static BWH_raw_memset(address, cells, value) // Slice - http://forum.sa-mp.com/showpost.php?p=1974747
{
	new param_adr;

	#emit LCTRL       6
	#emit MOVE.alt
	#emit LCTRL       0
	#emit ADD
	#emit MOVE.alt
	#emit LCTRL       1
	#emit SUB.alt
	#emit ADD.C       92
	#emit STOR.S.pri  param_adr
	#emit LOAD.S.pri  cells
	#emit SHL.C.pri   2
	#emit SREF.S.pri  param_adr

	#emit LOAD.S.alt  address
	#emit LOAD.S.pri  value
	#emit FILL        0
}

Login_OnPlayerDisconnect(playerid, reason)
{
    if (IsPlayerNPC(playerid)) return 1;

	new reason_text[18];

	switch(reason)
	{
		case 0: reason_text = "Zaman aþýmý/Crash";
		case 1: reason_text = "Kendi isteðiyle";
		case 2: reason_text = "Kick/Ban";
	}

    SavePlayerPos(playerid);
    DisableWaypoint(playerid);
	UpdateInjured(playerid);
	ResetDamages(playerid);
	DestroyAllBort(playerid);
    Destroy_Boombox(playerid);
	ResetLoginScreenVariables(playerid);
	
	pc_cmd_raporiptal(playerid);

	if (GetPVarInt(playerid, #Chase_Timer)) KillTimer(GetPVarInt(playerid, #Chase_Timer));

	DeletePVar(playerid, "Admin:CodeInputted");

    if (IsAdminDuty(playerid)) server_admins--;

	if (TaxiMade[playerid])
	{
		GiveCash(playerid, TaxiMade[playerid]);
        TaxiMade[playerid] = 0;
	}

	if (IsValidVehicle(JackingVehicle[playerid]))
	{
		new Float:ccX, Float:ccY, Float:ccZ;
		GetVehiclePos(JackingVehicle[playerid], ccX, ccY, ccZ);

	    VehicleInfo[JackingVehicle[playerid]][ePhysicalAttack] = false;
	    DestroyDynamic3DTextLabel(VehicleInfo[JackingVehicle[playerid]][eVehicleLabel]);
	    VehicleInfo[JackingVehicle[playerid]][vCooldown] = false;
	    JackingVehicle[playerid] = 0;
	}

    pTemp[playerid][pRamType] = 0;
    pTemp[playerid][pRamTime] = 0;

    if (IsValidDynamicObject(pTemp[playerid][pRamObj]))
	{
		DestroyDynamicObject(pTemp[playerid][pRamObj]);
		pTemp[playerid][pRamObj] = INVALID_OBJECT_ID;
	}

	if (GetPVarInt(playerid, "3DLabel"))
    {
		DestroyDynamic3DTextLabel(Text3D:GetPVarInt(playerid, "3DLabel"));
		DeletePVar(playerid, "3DLabel");
    }

    if (pTemp[playerid][pPatrol])
	{
	    new id = pTemp[playerid][pPatrol]-1;
	    pTemp[playerid][pPatrol] = 0;

        if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == playerid) PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] = INVALID_PLAYER_ID;
        if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] == playerid) PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;
		if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID) PatrolInfo[GetPatrolID(playerid)][id][patrulExists] = 0;

	    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[Departman] %s %s devriyesini sonlandýrdý: %s%s.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][id][patrulName], reason_text);
	}

    if (IsPlayerPhoneCreated(playerid)) Phone_Destroy(playerid);

	if (pTemp[playerid][p3DMenu] != -1)
	{
    	Destroy3DMenu(pTemp[playerid][p3DMenu]);
		pTemp[playerid][p3DMenu] = -1;
	}

	if (pTemp[playerid][pTracePlayer] != INVALID_PLAYER_ID)
	{
	    pTemp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pTraceStage] = 0;
		if (pTemp[playerid][pTraceGZ] != -1) GangZoneDestroy(pTemp[playerid][pTraceGZ]);
		pTemp[playerid][pTraceGZ] = -1;
	}

	if (IsValidDynamic3DTextLabel(PrisonLabel[playerid]))
	{
		DestroyDynamic3DTextLabel(PrisonLabel[playerid]);
        PrisonLabel[playerid] = Text3D:INVALID_3DTEXT_ID;
	}

    if (pTemp[playerid][pInteriorBiz] != 0)
	{
		SetPlayerBuyInterior(playerid, 0);
        pTemp[playerid][pInteriorBiz] = 0;
	}
	
	if (pTemp[playerid][pZond] != 0)
	{
		SetPlayerZond(playerid, 0);
        pTemp[playerid][pZond] = 0;
	}

	if (PlayerInfo[playerid][pInjured] == 3 && IsValidDynamic3DTextLabel(status_upd[playerid])) 
	{
		DestroyDynamic3DTextLabel(status_upd[playerid]);
	}

    if (pTemp[playerid][pPayphone] != -1)
    {
		PayphoneInfo[pTemp[playerid][pPayphone]][phUsed] = INVALID_PLAYER_ID;
		pTemp[playerid][pPayphone] = -1;
	}
	
	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID)
	{
	    if (IsPlayerLogged(pTemp[playerid][pCallLine])) SendPhoneMessage(pTemp[playerid][pCallLine], "Telefon hattý meþgule düþtü.");
		HangupCall(playerid);
	}
	
	if (IsPlayerLogged(playerid))
	{
	    foreach(new i : Player)
		{
			if(pTemp[i][pSpecPlayer] == playerid) TogglePlayerSpectating(i, 0);

			if (!(PlayerInfo[i][pSettings] & togJoin))
			{
				if (IsAdminDuty(i))
					SendClientMessageEx(i, COLOR_GRAD2, "*** %s sunucudan ayrýldý. %s (nakit: $%s, banka: $%s)", GetNameEx(playerid), reason_text, FormatNumber(PlayerInfo[playerid][pCash]), FormatNumber(PlayerInfo[playerid][pBank]));

				else if (GetPlayerDistanceFromPlayer(playerid, i) < 15.0 && GetWorld(playerid) == GetWorld(i) && GetInterior(playerid) == GetInterior(i) && PlayerInfo[playerid][pAdmin] == 0)
                	SendClientMessageEx(i, COLOR_GRAD2, "* %s sunucudan ayrýldý. (%s)", GetNameEx(playerid), reason_text);
			}

			if(GetPVarInt(i, PVAR_LASTPM_ISACTIVE))
			{
				if(GetPVarInt(i, PVAR_LASTPM_ID) == playerid)
				{
					DeletePVar(i, PVAR_LASTPM_ISACTIVE);
					DeletePVar(i, PVAR_LASTPM_ID);
				}
			}			
		}

		if (pTemp[playerid][pRentveh] != 0)
		{
		    new vehicle = pTemp[playerid][pRentveh];

    		VehicleInfo[vehicle][carTerminate] = 300;
    		pTemp[playerid][pRentveh] = 0;
    	}
    
		if (PlayerInfo[playerid][pCarKey] != 0)
		{
			new vehicle = PlayerInfo[playerid][pCarKey];

		    Save_Car(vehicle);
			VehicleInfo[vehicle][carTerminateEx] = 600;
            VehicleInfo[vehicle][carOwnerPlayer] = INVALID_PLAYER_ID;
			PlayerInfo[playerid][pCarKey] = 0;
		}
		
		CheckPMBlockList(playerid);
		
		SQL_SetInteger("users", "online", 0, PlayerInfo[playerid][pID]);
		SQL_SetInteger("users", "last_login", gettime(), PlayerInfo[playerid][pID]);
    
		Save_User(playerid);
	}

	pTemp[playerid][pLogged] = 0;
	
	if(IsValidDynamicObject(sandalyeobje[playerid])){
		DestroyDynamicObject(sandalyeobje[playerid]);
		DestroyDynamic3DTextLabel(SandalyeLabel[playerid]);
	}
	if(IsValidDynamicObject(teksandalyeobje[playerid])){
		DestroyDynamicObject(teksandalyeobje[playerid]);
		DestroyDynamic3DTextLabel(TekSandalyeLabel[playerid]);
	}
	ResetPlayerVariables(playerid);

	Streamer_ToggleIdleUpdate(playerid, 0);
	return 1;
}

Login_OnPlayerConnect(playerid)
{
    if (IsPlayerNPC(playerid)) return 1;
		
	for(new i = 0; i < 10; i++)
	{
		RemovePlayerAttachedObject(playerid, i);
	}
	
	BWH_memset(Silah_Bilgi[playerid][sSilahID], 13, 0);
	BWH_memset(Silah_Bilgi[playerid][sMermi], 13, 0);

	PreloadAnimations(playerid);
	//StopAudioStreamForPlayer(playerid);
	ResetPlayerVariables(playerid);
	TDraw_OnPlayerConnect(playerid);
    TogglePlayerAllDynamicRaceCPs(playerid, false);
    SetPlayerColor(playerid, TEAM_HIT_COLOR);
	GetNameForPlayer(playerid);
	Streamer_ToggleIdleUpdate(playerid, 1);

	RemoveBuildingForPlayer(playerid, -1, 0.0, 0.0, 0.0, 6000.0);

    return 1;
}

Login_OnPlayerSpawn(playerid)
{
    if (!IsPlayerLogged(playerid))
	{
	    SendErrorMessage(playerid, "Giriþ yapmadýðýnýz için atýldýnýz.");
		KickEx(playerid);
		return 1;
	}

	SetPlayerFightingStyle(playerid, PlayerInfo[playerid][pFightStyle]);
	SetPlayerSkill(playerid);

	for(new i = 0; i < MAX_PLAYER_ATTACH; i++)
	{
	    RemovePlayerAttachedObject(playerid, i);
		
		if (!AttachInfo[playerid][i][aID] || !AttachInfo[playerid][i][aUsed]) continue;

		SetPlayerAttachedObject(playerid, i, AttachInfo[playerid][i][aModel], AttachInfo[playerid][i][aBone], AttachInfo[playerid][i][aOffsetX], AttachInfo[playerid][i][aOffsetY], AttachInfo[playerid][i][aOffsetZ], AttachInfo[playerid][i][aRotX], AttachInfo[playerid][i][aRotY], AttachInfo[playerid][i][aRotZ], AttachInfo[playerid][i][aScaleX], AttachInfo[playerid][i][aScaleY], AttachInfo[playerid][i][aScaleZ]);
	}
	
    SetPlayerCurrentTimeAndWeather(playerid);
    SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);
 	SetPlayerSpawn(playerid);

	if(PlayerInfo[playerid][pInjured] > 0)
	{
		new reason = PlayerInfo[playerid][pDeathReason];
		new killerid = 499;
		SetTimerEx("InjuredPlayer", 2000, 0, "iii", playerid, killerid, reason);
	}
	
	// Reset weapons and ammo
	BWH_memset(Silah_Bilgi[playerid][sSilahID], 13, 0);
	BWH_memset(Silah_Bilgi[playerid][sMermi], 13, 0);

	PlayerTextDrawShow(playerid, Silah_Bilgi[playerid][MermiTD]);

	if (!(PlayerInfo[playerid][pSettings] & togHUD))
	{
		if(!(PlayerInfo[playerid][pSettings] & yesMHUD)){
				ShowHudTextDrawModern(playerid);
		} else ShowHudTextDraw(playerid);
	}

	if (PlayerInfo[playerid][pSettings] & togCustomBar) EnableHealthBarForPlayer(playerid, false);

	SetTimerEx("FixHealthArm", 1000, false, "d", playerid);

	new ora,minut,sec;
	gettime(ora,minut,sec);
	if(ora == 19 && minut == 0 || ora == 20 && minut == 0 || ora == 21 && minut == 0 || ora == 22 && minut == 0)
	{
    	SendSyntaxMessage(playerid, "Happy hour sistemi aktif."); // mesajul trimis player-ului la acea ora
    	return 1;
	}
	
	return 1;
}

Login_PlayerTimer(playerid)
{
	if (pTemp[playerid][pLogged] == 1 && pTemp[playerid][pLoggedTime]++ >= AUTH_TIME)
	{
	    SendErrorMessage(playerid, "%i saniye boyunca þifrenizi girmediniz.", AUTH_TIME); //êèê
		KickEx(playerid);
		return 0;
	}

	if (pTemp[playerid][pLogged] != 2) return 0;
	
	return 1;
}