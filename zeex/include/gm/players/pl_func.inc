this::KickPlayer(playerid)
{
    if (GetPVarInt(playerid,"kicked") != 1)	return 1;
	
    DeletePVar(playerid,"kicked");
	Kick(playerid);
	return 1;
}

this::Float:GetPlayerDistanceFromPlayer(playerid, targetid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	return GetPlayerDistanceFromPoint(playerid, x, y, z);
}

PlayerEnterFreeze(playerid)
{
	FreezePlayer(playerid);
	SetTimerEx("PlayerEnterUnFreeze", 5500, false, "i", playerid);
	return 1;
}

this::KillTimerSprung(playerid)
{
	InSprung[playerid] = 0;
	return 1;
}

this::FunktionInSprung(playerid)
{
	new animlib[32];
	new animname[32];
	new Float:vx,Float:vy,Float:vz;
	GetPlayerVelocity(playerid,vx,vy,vz);
	if(vz < -0.5)
	{
	    KillTimer(TimerIDSprung);
	    SetTimerEx("KillTimerSprung",1000,false,"i",playerid);
	    return 1;
	}
	GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
	if(!strcmp(animname,"JUMP_LAND") || !strcmp(animname,"FALL_LAND"))
	{
		KillTimer(TimerIDSprung);
		ClearAnimations(playerid,1);
		ApplyAnimation(playerid,"ped","FALL_COLLAPSE",4.1,0,1,1,0,0,1);
		SetTimerEx("KillTimerSprung",1000,false,"i",playerid);
	}
	return 1;
}

this::CBugFreezeOver(playerid)
{
	TogglePlayerControllable(playerid, true);

	pCBugging[playerid] = false;
	return 1;
}

this::PlayerEnterUnFreeze(playerid)
{
	UnFreezePlayer(playerid);
	return 1;
}

UnFreezePlayer(playerid)
{
	TogglePlayerControllable(playerid, 1);
	return 1;
}

FreezePlayer(playerid)
{
	TogglePlayerControllable(playerid, 0);
	return 1;
}

SetPlayerSkinEx(playerid, skinid)
{
	PlayerInfo[playerid][pSkin] = skinid;
	//SetSpawnInfoEx(playerid, 1642.2006, -2334.4751, -2.6797);
	return SetPlayerSkin(playerid, skinid);
}

Float:GetPlayerHealthEx(playerid)
{
	new Float:hp;
	AntiCheatGetHealth(playerid, hp);
	return hp;
}

SetPlayerSkill(playerid, type = 1)
{
	if (type == 1) { // ï¿½ï¿½
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 899);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 1);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
				
		SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
	} else if (type == 2) { // +-
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 200);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 0);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 0);
				
		SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 200);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 200);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 200);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 200);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 200);
	} else if (type == 3) { // ï¿½ï¿½ï¿½ï¿½ï¿½
		SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 100);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 0);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 0);
				
		SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 50);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 50);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 100);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 50);
		SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 50);
	}	
	return 1;
}

IsPlayerAFK(playerid)
{
	return (pTemp[playerid][pDarkAFK] > 5)?(1):(0);
}

/*IsPlayerInCube(playerid, Float:min_x, Float:min_y, Float:max_x, Float:max_y)
{
    new Float: x, Float: y, Float: z;

    GetPlayerPos(playerid, x, y, z);
    return ((x <= max_x && x >= min_x) && (y <= max_y && y >= min_y))?(1):(0);
}*/

IsValidPlayerName(const str[])
{
	if (!str[0] || str[0] == '\1') return 0;

	for (new i = 0, l = strlen(str); i != l; i ++) {
	    if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))	continue;
		if (str[i] == '_' || str[i] == '$' || str[i] == '@' || str[i] == '[' || str[i] == ']')	continue;
		else return 0;
	}
	return 1;
}

SendPlayerToPlayer(playerid, targetid)
{
	new Float:x, Float:y, Float:z;
	
	GetPlayerPos(targetid, x, y, z);

    if (GetInterior(targetid) || GetWorld(targetid))
	{
   		PlayerInfo[playerid][pLocationPos][0] = PlayerInfo[targetid][pLocationPos][0];
	    PlayerInfo[playerid][pLocationPos][1] = PlayerInfo[targetid][pLocationPos][0];
		PlayerInfo[playerid][pLocationPos][2] = PlayerInfo[targetid][pLocationPos][0];
	}

	if(IsPlayerInAnyVehicle(playerid))
    {
        SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
        LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
        SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), GetPlayerVirtualWorld(targetid));
		SetInterior(playerid, GetInterior(targetid));
		SetWorld(playerid, GetWorld(targetid));
    }
    else
	{
		SetPlayerPosEx(playerid, x + 1, y, z);
		SetInterior(playerid, GetInterior(targetid));
		SetWorld(playerid, GetWorld(targetid));
		pTemp[playerid][pHouseEntered] = pTemp[targetid][pHouseEntered];
		pTemp[playerid][pApartEntered] = pTemp[targetid][pApartEntered];
		pTemp[playerid][pBizEntered] = pTemp[targetid][pBizEntered];
	}
	return 1;
}

ShowSettings(playerid)
{
	new text[128], string[1024];
	    
	switch(PlayerInfo[playerid][pWalk])//0
	{
	    case 0: format(text, sizeof(text), "Yürüme Stili\t[Kapalý]\n");
		default: format(text, sizeof(text), "Yürüme Stili\t[%i]\n", PlayerInfo[playerid][pWalk]);
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pTalk])//1
	{
	    case 0: format(text, sizeof(text), "Konuþma Tarzý\t[Kapalý]\n");
		default: format(text, sizeof(text), "Konuþma Tarzý\t[%i]\n", PlayerInfo[playerid][pTalk]);
	}
	strcat(string, text);
	
    format(text, sizeof(text), "Dövüþ Tarzý\t[%s]\n", GetFightStyleName(playerid));//2
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togOOC)//4
	{
	    case 0: text = "OOC Duyuru Kanalý\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "OOC Duyuru Kanalý\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togName)//4
	{
	    case 0: text = "Oyuncu isimleri\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Oyuncu isimleri\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
    
    switch(PlayerInfo[playerid][pSettings] & togAdv)//5
	{
	    case 0: text = "Reklam metinleri\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Reklam metinleri\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togJoin)//6
	{
	    case 0: text = "Oyuncu giriþ/çýkýþ metinleri\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Oyuncu giriþ/çýkýþ metinleri\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togGov)//7
	{
	    case 0: text = "Hükümet Duyurularý (/gov)\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Hükümet Duyurularý (/gov)\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togPM)//8
	{
	    case 0: text = "Özel Mesajlar \t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Özel Mesajlar \t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togNews)//12
	{
	    case 0: text = "Haber metinleri\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Haber metinleri\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);

    switch(PlayerInfo[playerid][pSettings] & togAFK)//13
	{
	    case 0: text = "AFK geçirilen süreyi göster\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "AFK geçirilen süreyi göster\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);
	
	switch(PlayerInfo[playerid][pSettings] & togHUD)//14
	{
	    case 0: text = "Hud Göster\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Hud Göster\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);

	switch(PlayerInfo[playerid][pSettings] & yesMHUD)//15
	{
	    case 0: text = "Modern Hud Göster\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Modern Hud Göster\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);

	switch(PlayerInfo[playerid][pSettings] & togFaction)//16
	{
	    case 0: text = "Birlik Sohbeti\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Birlik Sohbeti\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);

	switch(PlayerInfo[playerid][pSettings] & togCustomBar)//17
	{
	    case 0: text = "Özel Can barý\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Özel Can Barý\t[{FF6347}Deaktif{FFFFFF}]\n";
	}	
	strcat(string, text);

	switch(PlayerInfo[playerid][pSettings] & togDoSetting)//18
	{
	    case 0: text = "/do Renk Ayarý\t[{79BFA3}Yeþil{FFFFFF}]\n";
		default: text = "/do Renk Ayarý\t[{C2A2DA}Mor{FFFFFF}]\n";
	}	
	strcat(string, text);

	switch(PlayerInfo[playerid][pSettings] & togEnter)//19
	{
	    case 0: text = "Giriþ/çýkýþ için Y tuþu kullanýmý\t[{90EE90}Aktif{FFFFFF}]\n";
		default: text = "Giriþ/çýkýþ için Y tuþu kullanýmý\t[{FF6347}Deaktif{FFFFFF}]\n";
	}
	strcat(string, text);		

	strcat(string, "Admin Yetkileri\tmenüye git\n"); // 20

	format(text, sizeof(text), "Harita Ayarlarý\tmenüye git\n");//21
	strcat(string, text);	
	
	strcat(string, "Þifre Deðiþtir");//22
	
	Dialog_Show(playerid, MainSettings, DIALOG_STYLE_TABLIST, "Ayarlar", string, "Seç", "Geri Dön");
	return 1;
}

PlayerNearPlayer(Float:radi, playerid, targetid)
{
	new Float:fX, Float:fY, Float:fZ;
	GetPlayerPos(targetid, fX, fY, fZ);
	return (GetInterior(playerid) == GetInterior(targetid) && GetWorld(playerid) == GetWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radi, fX, fY, fZ);
}

SavePlayerPos(playerid)
{
	GetPlayerPos(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pPosA]);
	PlayerInfo[playerid][pWorld] = GetWorld(playerid);
	PlayerInfo[playerid][pInt] = GetInterior(playerid);
	SetSpawnInfoEx(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	return 1;
}

GiveCash(playerid, cash)
{
 	PlayerInfo[playerid][pCash] += cash;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);

	new __cash = cash;

	if (cash < 0)	cash = -cash;

    new mes[19];
	format(mes, sizeof(mes), "%s$%i", (__cash < 0)?("~r~-"):("~g~+"), cash);
	GameTextForPlayer(playerid, mes, 1000, 1);

    SQL_SetInteger("users", "cash", PlayerInfo[playerid][pCash], PlayerInfo[playerid][pID]);	
	return 1;
}

SetCash(playerid, cash)
{
	PlayerInfo[playerid][pCash] = cash;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, cash);
	return 1;
}

GetCash(playerid)
{
	return PlayerInfo[playerid][pCash];
}

SendClientMessageEx(playerid, color, const str[], {Float,_}:...)
{
	static args, start, end, string[144];
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		SendClientMessage(playerid, color, string);

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN
	}
	return SendClientMessage(playerid, color, str);
}

stock SendClientMessageToAllEx(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.pri args
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format

        #emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) {
			SendClientMessage(i, color, string);
		}
		return 1;
	}
	return SendClientMessageToAll(color, str);
} 

SendNearbyMessage(Float:radius, playerid, color, const str[], {Float,_}:...)
{
	static args, start, end, string[144];
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
		    if (0 == IsPlayerLogged(i) || 0 == PlayerNearPlayer(radius, i, playerid)) continue;
			SendClientMessage(i, color, string);
		}
		return 1;
	}

	foreach (new i : Player)
	{
	    if (0 == IsPlayerLogged(i) || 0 == PlayerNearPlayer(radius, i, playerid)) continue;
		SendClientMessage(i, color, str);
	}
	return 1;
}

SendLocalMessage(Float:radius, playerid, col1, col2, col3, col4, col5, const str[], {Float,_}:...)
{
	static args, start, end, string[144];
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
		    if (0 == IsPlayerLogged(i)) 							continue;
			if (PlayerNearPlayer(radius/16, i, playerid))		SendClientMessage(i, col1, string);
            else if (PlayerNearPlayer(radius/8, i, playerid))	SendClientMessage(i, col2, string);
            else if (PlayerNearPlayer(radius/4, i, playerid))	SendClientMessage(i, col3, string);
            else if (PlayerNearPlayer(radius/2, i, playerid))	SendClientMessage(i, col4, string);
            else if (PlayerNearPlayer(radius, i, playerid))		SendClientMessage(i, col5, string);
			//SetPlayerChatBubble(i, string, col5, 5, 5000);
		}
		return 1;
	}

	foreach (new i : Player)
	{
	    if (0 == IsPlayerLogged(i))							continue;
	    if (PlayerNearPlayer(radius/16, i, playerid))		SendClientMessage(i, col1, string);
		else if (PlayerNearPlayer(radius/8, i, playerid))	SendClientMessage(i, col2, string);
		else if (PlayerNearPlayer(radius/4, i, playerid))	SendClientMessage(i, col3, string);
		else if (PlayerNearPlayer(radius/2, i, playerid))	SendClientMessage(i, col4, string);
		else if (PlayerNearPlayer(radius, i, playerid))		SendClientMessage(i, col5, string);
		//SetPlayerChatBubble(i, string, col5, 5, 5000);
	}
	return 1;
}

SendPMToPlayer(playerid, targetid, text[])
{
    new pos = MAXLEN;
	if (pos < MAXLEN-1) pos = MAXLEN;

	if (strlen(text) > MAXLEN)
	{
		if (IsAdminDuty(playerid))	SendClientMessageEx(targetid, COLOUR_TURBO, ">> {a92626}%s {F0F000}(%i): %.*s ...", GetNameEx(playerid), playerid, pos, (text));
		else						SendClientMessageEx(targetid, COLOUR_TURBO, ">> %s (%i): %.*s ...", GetNameEx(playerid), playerid, pos, (text));
		SendClientMessageEx(targetid, COLOUR_TURBO, ">> ... %s", (text)[pos]);
		
		if (IsAdminDuty(targetid))	SendClientMessageEx(playerid, COLOUR_TULIPTREE, "<< {a92626}%s (%i){E5C43E}: %.*s ...", GetNameEx(targetid), targetid, pos, (text));
		else						SendClientMessageEx(playerid, COLOUR_TULIPTREE, "<< %s (%i): %.*s ...", GetNameEx(targetid), targetid, pos, (text));
		SendClientMessageEx(playerid, COLOUR_TULIPTREE, ">> ... %s", (text)[pos]);
	}
	else
	{
	    if (IsAdminDuty(playerid)) 	SendClientMessageEx(targetid, COLOUR_TURBO, ">> {a92626}%s {F0F000}(%i): %s", GetNameEx(playerid), playerid, (text));
		else						SendClientMessageEx(targetid, COLOUR_TURBO, ">> %s (%i): %s", GetNameEx(playerid), playerid, (text));
		if (IsAdminDuty(targetid))	SendClientMessageEx(playerid, COLOUR_TULIPTREE, "<< {a92626}%s (%i){E5C43E}: %s", GetNameEx(targetid), targetid, (text));
		else						SendClientMessageEx(playerid, COLOUR_TULIPTREE, "<< %s (%i): %s", GetNameEx(targetid), targetid, (text));
	}

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !IsAdminDuty(i) || (pTemp[i][pPMPlayer] != playerid && GetPVarInt(i, #spypm_all) != 1)) continue;

        if (strlen(text) > MAXLEN)
		{
			SendClientMessageEx(i, COLOUR_TURBO, "[ELF GÖZÜ PM] >> %s > %s (%i): %.*s ...", GetNameEx(playerid), GetName(targetid), targetid, pos, (text));
			SendClientMessageEx(i, COLOUR_TURBO, "... %s", (text)[pos]);
		}
		else
		{
			SendClientMessageEx(i, COLOUR_TURBO, "[ELF GÖZÜ PM] >> %s > %s (%i): %s", GetNameEx(playerid), GetName(targetid), targetid, text);
		}
	}
	return 1;
}

GetPlayer2DZone(playerid, zone[], len)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	if (GetWorld(playerid) || GetInterior(playerid))
	{
		x = PlayerInfo[playerid][pLocationPos][0];
		y = PlayerInfo[playerid][pLocationPos][1];
		z = PlayerInfo[playerid][pLocationPos][2];
	}

	for(new i = 0; i != sizeof(gSAZones); i++)
	{
		if (x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
	}
	return 0;
}

GetZone(Float:x, Float:y, zone[], len)
{
	for(new i = 0; i != sizeof(gSAZones); i++)
	{
		if (x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
	}
	return format(zone, len, "Bilinmiyor");
}



ResetPlayerVariables(playerid)
{
	MDC_Hide(playerid);
    ResetDamages(playerid);
	for(new i = 0; i != MAX_CHARACTERS; i++)
	{
	    login_char_id[playerid][i] = 0;
	    format(login_char_name[playerid][i], MAX_PLAYER_NAME, "Boþ slot");
	}

    RadarHud_Sil(playerid);

    RemovePlayerMask(playerid);
	maskOn{playerid} = false;
	DeletePVar(playerid, "BugKurtar");

	new reportid;
	reportid = GetPVarInt(playerid, "reportidm");
	pTemp[playerid][pSendReport] = false;
	pTemp[playerid][pDestekTakip] = 0;
	
	if(reportid >= 0)
	{
        ReportInfo[reportid][rReportExists] = false;
	    ReportInfo[reportid][rReportBy] = INVALID_PLAYER_ID;
	}	
	DeletePVar(playerid, "reportidm");

	new reportidx;
	reportidx = GetPVarInt(playerid, "questidm");
	pTemp[playerid][pSendQuest] = false;
	if(reportidx >= 0)
	{
	    QuestInfo[reportidx][qQuestExists] = false;
	    QuestInfo[reportidx][qQuestBy] = INVALID_PLAYER_ID;
	}	
	DeletePVar(playerid, "questidm");
	DeletePVar(playerid, PVAR_DARKSCREEN_ISACTIVE);	

    pTemp[playerid][pTruckerTime] = 0;
    pTemp[playerid][pTruckerPrice] = 0;
    pTemp[playerid][pTruckerOn] = 0;
	pTemp[playerid][pColorPage] = 0;
	pTemp[playerid][pTackleMode] = false;
	pTemp[playerid][pLastLogin] = 0;

	pTemp[playerid][pAdvertTime] = 0;
	pTemp[playerid][pDebugMode] = 0;

	// Uyuþturucu Baðýmlýlýðý
	PlayerInfo[playerid][pBagimlilikEXP] = PlayerInfo[playerid][pBagimlilikSeviye] = PlayerInfo[playerid][pUTedaviEXP] = PlayerInfo[playerid][pUTedaviSure] = PlayerInfo[playerid][pKrizSure] = PlayerInfo[playerid][UyusKullan] = 0;	

	KillTimer(YuruyusTimer[playerid]);

	for(new j; j < 5; j++)
		PlayerInfo[playerid][pOlusumDivision][j] = -1;	

    cameraSession[playerid] = 
	JackingEngine[playerid] =
	JackingLock[playerid] = 
	BreakingHouse[playerid] = 
	JackingVehicle[playerid] = 0;

    ResetSpectateVariables(playerid);

	OnAnim{playerid} = false;

	Job_OnPlayerDisconnect(playerid);

	for(new i; i != MAX_PLAYERS; i++)
		people_blocking[playerid][i] = 0;

	for(new i = 0; i < MAX_PLAYER_CONTACTS; i++)
		PlayerContacts[playerid][i][contactOn] = 0;

	for(new i = 0; i < MAX_PLAYER_NOTES; i++)
		PlayerNotes[playerid][i][noteOn] = 0;

	for(new i; i != 30; i++)
		pTemp[playerid][pWeaponListed][i] = 0;

    for(new i; i != 5; i++)
		pTemp[playerid][pListed][i] = 0;
		
	for(new i = 0; i < MAX_INV_SLOTS; i++)
	{
		Inventory[playerid][i][pInvItem] = 0;
		Inventory[playerid][i][pInvItem] = 0;
		Inventory[playerid][i][pInvEx] = 0;
		Inventory[playerid][i][pInvQFloat] = 0;
		Inventory[playerid][i][pInvQ] = 0;
		Inventory[playerid][i][pInvName] = EOS;
	}

	for(new x; x < 12; x++)
	{
		PlayerInfo[playerid][pWeapons][x] = 0;
		PlayerInfo[playerid][pAmmo][x] = 0;
	}	

    PlayerInfo[playerid][pUzerindekiSilah] = PlayerInfo[playerid][pSilahTick] = PlayerInfo[playerid][SilahTick] = 0;

    pTemp[playerid][pRentveh] = 0;
	PlayerInfo[playerid][pCarKey] = 0;

	PlayerInfo[playerid][pCicek] = PlayerInfo[playerid][pKamera] = PlayerInfo[playerid][pBoombox] = PlayerInfo[playerid][pMaske] = PlayerInfo[playerid][pSigara] = 0;
	PlayerInfo[playerid][pKalem] = PlayerInfo[playerid][pTelsiz] = PlayerInfo[playerid][pBenzinBidonu] = PlayerInfo[playerid][pZar] = PlayerInfo[playerid][pCakmak] = 0;

    pTemp[playerid][AntiHileSistemi] = -1;
	// Anti-Hile
	pTemp[playerid][OlumSayisi] = pTemp[playerid][OlumSuresi] = pTemp[playerid][pCarTick] = pTemp[playerid][pCarWarpTime] = pTemp[playerid][pCarWarpVehicleID] = 0;
	pTemp[playerid][HileKontrol] = gettime();

	// Specmode
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	noclipdata[playerid][lrold]	= 0;
	noclipdata[playerid][udold] = 0;
	noclipdata[playerid][mode] = 0;
	noclipdata[playerid][lastmove] = 0;
	noclipdata[playerid][accelmul] = 0.0;	

	pTemp[playerid][pChangeNick] = EOS;
	pTemp[playerid][pCallName] = EOS;
	pTemp[playerid][pCallKeypad] = EOS;

	pTemp[playerid][pPayphone] = -1;
	
	//pTemp[playerid][JackingVehID] = 
	pTemp[playerid][pUnscrambleID] =
	//pTemp[playerid][pPunctePremium] =  
	pTemp[playerid][pScrambleFailed] = 
	pTemp[playerid][pScrambleSuccess] = 
	//pTemp[playerid][JackingCP] = 
	pTemp[playerid][JackingType] = 
	pTemp[playerid][JackingWarnings] = 
	pTemp[playerid][pPizzaBoy] = 
    pTemp[playerid][pDemolitionTime] = 
	pTemp[playerid][pDrugUse] = 
	pTemp[playerid][pDrugTime] = 
	pTemp[playerid][pDrugChgWeather] =
	pTemp[playerid][pMicPerm] = false;
	pTemp[playerid][tempItem] = 
	pTemp[playerid][tempEx] = 
	pTemp[playerid][tempQ] = 	
	pTemp[playerid][pLicenseExam] = 
	pTemp[playerid][pTesterDuty] = 
    pTemp[playerid][pAdminDuty] = 
	pTemp[playerid][pServeType] = 
	pTemp[playerid][pGreetType] = 
	pTemp[playerid][pFoodStand] = 
	pTemp[playerid][pDMLog] = 
	pTemp[playerid][pSpawned] =
	pTemp[playerid][pNews] = 
	pTemp[playerid][pDarkAFK] = 
	pTemp[playerid][pCuffed] = 
	pTemp[playerid][pFireTime] =
	pTemp[playerid][pPlantTime] =
	pTemp[playerid][pPlantType] =
    pTemp[playerid][pFishTime] =
	pTemp[playerid][pPatrol] =
    pTemp[playerid][pReportTime] =
	pTemp[playerid][pLogged] = 
	pTemp[playerid][pLoggedTime] =
	pTemp[playerid][pLoggedTry] = 
	pTemp[playerid][pJob] = 
	pTemp[playerid][pJobTime] = 
	pTemp[playerid][pRentPrice] =
	pTemp[playerid][pHousePrice] = 
	pTemp[playerid][pCarPrice] = 
	pTemp[playerid][pTaser] = 
	pTemp[playerid][pBeanbag] =
	pTemp[playerid][pLTL] =
	pTemp[playerid][pTaserTime] = 
	pTemp[playerid][pFreezeTime] =
	pTemp[playerid][pEditBort] = 
    pTemp[playerid][pCCTV] = 
	pTemp[playerid][pZond] = 
	pTemp[playerid][pDamagesCount] = 
	pTemp[playerid][pInjuredTime] = 
	pTemp[playerid][pInjuredLegTime] = 
	pTemp[playerid][pHelpUp3dText] = 
	pTemp[playerid][pFlashTime] =
	pTemp[playerid][pHealTime] = 
	pTemp[playerid][pBuildHouse] = 
	pTemp[playerid][pRamType] = 
    pTemp[playerid][pRamTime] = 
	pTemp[playerid][pCallStatus] = 
	pTemp[playerid][pCallIncoming] = 
	pTemp[playerid][pCallTime] = 
	pTemp[playerid][pWepPrice] = 
	PlayerInfo[playerid][pGanjaTime] = 
	PlayerInfo[playerid][pPrescribe] = 
	PlayerInfo[playerid][pDependence] =
	PlayerInfo[playerid][pDemolition] = 
	PlayerInfo[playerid][pID] = 
	PlayerInfo[playerid][pAccID] = 
	pTemp[playerid][pInteriorHouse] = 
	pTemp[playerid][pInteriorBiz] =
	pTemp[playerid][pInteriorID] = 
	pTemp[playerid][pCargoID] = 
	pTemp[playerid][pCallOn] = 
	pTemp[playerid][pEmergency] = 
	pTemp[playerid][pPoliceCalls] = 
	pTemp[playerid][pPoliceJails] = 
	pTemp[playerid][pPoliceFines] = 
	pTemp[playerid][UsingBort] = 
	pTemp[playerid][UsingCorpse] =
	pTemp[playerid][tempStatus] =
	pTemp[playerid][pTraceStage] = 0;

	pTemp[playerid][pBoombox_house] = 
	pTemp[playerid][pBoombox_biz] = 
	pTemp[playerid][pBizEntered] = 
	pTemp[playerid][pApartEntered] = 
	pTemp[playerid][pHouseEntered] = 
	pTemp[playerid][pHouseHouse] = 
	pTemp[playerid][pFurniture] = 
	pTemp[playerid][pFurnitureB] = 
	pTemp[playerid][p3DMenu] = -1;
    pTemp[playerid][pRamHouse] = 
	pTemp[playerid][pRamVeh] = 
    pTemp[playerid][pRamGarage] = 
    pTemp[playerid][pRamBiz] = 
	pTemp[playerid][pTraceGZ] = -1;

	pTemp[playerid][pBizPrice] = 0;
	pTemp[playerid][pBizID] = INVALID_PLAYER_ID;

	pTemp[playerid][pBoombox] = 
	pTemp[playerid][pServePlayer] = 
	pTemp[playerid][pGreetPlayer] = 
	pTemp[playerid][pMDCPlayer] = 
	pTemp[playerid][pWepPlayer] = 
	pTemp[playerid][pRentPlayer] = 
	pTemp[playerid][pPMPlayer] = 
	pTemp[playerid][pHousePlayer] = 
	pTemp[playerid][pInterview] = 
	pTemp[playerid][pBizPlayer] = 
	pTemp[playerid][pInterviewPlayer] = 
	pTemp[playerid][pGozAlti] =
	pTemp[playerid][pHealPlayer] = 
	pTemp[playerid][pFactionPlayer] = 
	pTemp[playerid][pFriskPlayer] = 
	pTemp[playerid][pSpecPlayer] = 
	pTemp[playerid][pHirePlayer] = 
	pTemp[playerid][pCarPlayer] = 
	pTemp[playerid][pCallLine] = 
	pTemp[playerid][pInjureText] =
	pTemp[playerid][pTracePlayer] = INVALID_PLAYER_ID;

	pTemp[playerid][pDriver] = INVALID_VEHICLE_ID;
	pTemp[playerid][pZondActor] = INVALID_ACTOR_ID;
    pTemp[playerid][pRamObj] = INVALID_OBJECT_ID;

	for(new c = 0; c < 5; c++)
	{
		pTemp[playerid][MyCarSpawn][c] = 0;
		pTemp[playerid][MyCarSpawn][c] = 0;
	}

	for(new i = 0; i < MAX_WEAP-1; i++)	PlayerInfo[playerid][pHideWeap][i] = 0;

	PlayerInfo[playerid][pAccname] = EOS;
	PlayerInfo[playerid][pBirthdate] = 
	PlayerInfo[playerid][pReportMute] =

	PlayerInfo[playerid][pFishTime] = 
	PlayerInfo[playerid][pCarKey] =
	PlayerInfo[playerid][pTog][0] =
	PlayerInfo[playerid][pTog][1] = 
	PlayerInfo[playerid][pTog][2] = 
	PlayerInfo[playerid][pSwatDuty] = 
	PlayerInfo[playerid][pOnDuty] = 
	PlayerInfo[playerid][pCash] = 
	PlayerInfo[playerid][pBank] = 
	PlayerInfo[playerid][pSkin] = 
	PlayerInfo[playerid][pSex] = 
	PlayerInfo[playerid][pAge] = 
	PlayerInfo[playerid][pRace] = 
	PlayerInfo[playerid][pOrigin] = 
	PlayerInfo[playerid][pLevel] =
	PlayerInfo[playerid][pExp] = 
	PlayerInfo[playerid][pHours] =
	PlayerInfo[playerid][pMinutes] = 
	PlayerInfo[playerid][pAdmin] = 
	PlayerInfo[playerid][pAdminHide] = 
	PlayerInfo[playerid][pHelper] =
	PlayerInfo[playerid][pHelperLead] =  
	PlayerInfo[playerid][pFMAdmin] =  
	PlayerInfo[playerid][pMapper] =  
	PlayerInfo[playerid][pEbc] =  
	PlayerInfo[playerid][pSkinYetki] =
	PlayerInfo[playerid][pRdscripter] =
	PlayerInfo[playerid][pInt] = 
	PlayerInfo[playerid][pWorld] =
	PlayerInfo[playerid][pJailed] = 
	PlayerInfo[playerid][pIsolateTime] = 
	PlayerInfo[playerid][pJailTime] = 
	PlayerInfo[playerid][pWarns] = 
	PlayerInfo[playerid][pPremium] = 
	PlayerInfo[playerid][pPremiumTime] = 
	PlayerInfo[playerid][pNameChanges] = 
	PlayerInfo[playerid][pNumberChanges] = 
	PlayerInfo[playerid][pCarLic] = 
	PlayerInfo[playerid][pWepLic] = 
	PlayerInfo[playerid][pFlyLic] = 
	PlayerInfo[playerid][pTaxiLic] = 
	PlayerInfo[playerid][pInjured] = 
	PlayerInfo[playerid][pDeathReason] = 
	PlayerInfo[playerid][pFightStyle] = 
	PlayerInfo[playerid][pPayCheckMoney] = 
	PlayerInfo[playerid][pPayDayTime] = 
	PlayerInfo[playerid][pNumber] = 
	PlayerInfo[playerid][pSavings] = 
	PlayerInfo[playerid][pRentKey] = 
	PlayerInfo[playerid][pRentPrice] = 
	PlayerInfo[playerid][pChannel] = 
	PlayerInfo[playerid][pOwnedChannel] = 
	PlayerInfo[playerid][pAuthed] = 
	PlayerInfo[playerid][pSpareKey] =
	PlayerInfo[playerid][pWorkOn] = 
	PlayerInfo[playerid][pWalk] = 
	PlayerInfo[playerid][pFaction] = 
	PlayerInfo[playerid][pJob] = 
	PlayerInfo[playerid][pCareer] = 
	PlayerInfo[playerid][pRank] = 
	PlayerInfo[playerid][pBadgeNumber] = 
	PlayerInfo[playerid][pDriveWarns] = 
	PlayerInfo[playerid][pWepWarns] = 
	PlayerInfo[playerid][pWepCount] = 
	PlayerInfo[playerid][pArrested] = 
	PlayerInfo[playerid][pTalk] = 
	PlayerInfo[playerid][pSwat] = 
	PlayerInfo[playerid][pLawyer] =
	PlayerInfo[playerid][pAuthwep] = 
	PlayerInfo[playerid][pPrisoned] = 
	PlayerInfo[playerid][pHud] = 0;

	pTemp[playerid][pInvulnerable] = 
	PlayerInfo[playerid][pPosX] =
	PlayerInfo[playerid][pPosY] = 
	PlayerInfo[playerid][pPosZ] = 
	PlayerInfo[playerid][pPosA] = 
	PlayerInfo[playerid][pArmour] = 0.0;

	PlayerInfo[playerid][pSlot] = 1;
    
	if(IsValidDynamicObject(sandalyeobje[playerid])) DestroyDynamicObject(sandalyeobje[playerid]);
	if(IsValidDynamicObject(teksandalyeobje[playerid])) DestroyDynamicObject(teksandalyeobje[playerid]);

	sandalyeobje[playerid] = INVALID_OBJECT_ID;
	teksandalyeobje[playerid] = INVALID_OBJECT_ID;

	//Tog
	PlayerInfo[playerid][pSettings] &= ~togService;
	PlayerInfo[playerid][pSettings] &= ~togName;
	PlayerInfo[playerid][pSettings] &= ~togOOC;
	PlayerInfo[playerid][pSettings] &= ~togJoin;
	PlayerInfo[playerid][pSettings] &= ~togAdv;
	PlayerInfo[playerid][pSettings] &= ~togGov;
	PlayerInfo[playerid][pSettings] &= ~togPM;
    PlayerInfo[playerid][pSettings] &= ~togAdmCmds;
	PlayerInfo[playerid][pSettings] &= ~togAdmChat;
	PlayerInfo[playerid][pSettings] &= ~togHelperChat;
    PlayerInfo[playerid][pSettings] &= ~togNews;
    PlayerInfo[playerid][pSettings] &= ~togAFK;
    PlayerInfo[playerid][pSettings] &= ~togHUD;
	PlayerInfo[playerid][pSettings] &= ~yesMHUD;
    PlayerInfo[playerid][pSettings] &= ~togFaction;
    PlayerInfo[playerid][pSettings] &= ~togTester;
	PlayerInfo[playerid][pSettings] &= ~togCustomBar;
	PlayerInfo[playerid][pSettings] &= ~togDoSetting;
	PlayerInfo[playerid][pSettings] &= ~togEnter;
	

    DeletePVar(playerid, PVAR_LASTENTEREDVEH_SEAT);
	DeletePVar(playerid, PVAR_LASTENTEREDVEH_ID);
    DeletePVar(playerid, PVAR_LASTPM_ISACTIVE);
    DeletePVar(playerid, PVAR_LASTPM_ID);	

	HUD_Created{playerid} = false;

	for(new i = 0; i < MAX_PLAYER_MARKS; i++)
	{
		PlayerInfo[playerid][pMark][i] = -1;
	}

	for(new i = 0; i < MAX_CCTV; i++)
	{
		PCamera[playerid][i][pc_used] =
		PCamera[playerid][i][pc_time] = 0;
	}
    
	/// silah
	for (new i; i < 17; i++)
	{
		WeaponSettings[playerid][i][Position][0] = -0.116;
		WeaponSettings[playerid][i][Position][1] = 0.189;
		WeaponSettings[playerid][i][Position][2] = 0.088;
		WeaponSettings[playerid][i][Position][3] = 0.0;
		WeaponSettings[playerid][i][Position][4] = 44.5;
		WeaponSettings[playerid][i][Position][5] = 0.0;
		WeaponSettings[playerid][i][Bone] = 1;
		WeaponSettings[playerid][i][Hidden] = false;
		WeaponSettings[playerid][i][duzenlendi] = 0;
	}
	WeaponTick[playerid] = 0;
	EditingWeapon[playerid] = 0;
	PlayerInfo[playerid][pSilahSistemi] = 0;
	/// silah

	Fuel_ResetPlayer(playerid);

	InSprung[playerid] = 0;

	pCBugging[playerid] = false;
	KillTimer(ptmCBugFreezeOver[playerid]);
	ptsLastFiredWeapon[playerid] = 0;	
	return 1;
}

RemovePlayerMask(playerid)
{
	if (IsValidDynamic3DTextLabel(cNametag[playerid])) DestroyDynamic3DTextLabel(cNametag[playerid]);
	maskOn{playerid} = false;
	ShowPlayerName(playerid, true);
	format(PlayerInfo[playerid][pMaskname], 32, PlayerInfo[playerid][pUsername_]);
	
	return 1;
}

stock IsPlayerLogged(playerid)
{
    new bool:result = false;

    if(playerid != INVALID_PLAYER_ID && IsPlayerConnected(playerid) && pTemp[playerid][pSpawned] == 1)
        result = true;

    return result;
}

BugResolverFalling(playerid)
{
	SendWarningMessage(playerid, "Blaze Guard olarak bir mekanda buga girdiðinizi tespit ettik. Seni kurtarmak için hazýrlanýyorum!");
	FreezePlayer(playerid);

    Dialog_Show(playerid, Bug_Resolver_Falling, DIALOG_STYLE_MSGBOX, "{FFFFFF}Blaze Guard", "{FFFFFF}Bulunduðunuz konumdan aþaðý düþtüðünüzü tespit ettik.\nSizi nereye ýþýnlamamý istersiniz?", "Mekan Ýçi", "Mekan Dýþý");	
	return 1;
}

Dialog:Bug_Resolver_Falling(playerid, response, listitem, inputtext[])
{
    new houseid = GetNearInsideHouse(playerid, 100.0);
	new bizid = GetNearInsideBiz(playerid, 100.0);

	if (!response)
	{
	    if(houseid != -1)
		{ 
		    SetPlayerPosEx(playerid,HouseInfo[houseid][hPosX],HouseInfo[houseid][hPosY],HouseInfo[houseid][hPosZ] + 1.0);
			SetWorld(playerid, HouseInfo[houseid][hPosVW]);
			SetInterior(playerid, HouseInfo[houseid][hPosInt]);
		}
	
	    if(bizid != -1) 
		{
			SetPlayerPosEx(playerid,BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ] + 1.0);
			SetWorld(playerid, BizInfo[bizid][bizPosVW]);
			SetInterior(playerid, BizInfo[bizid][bizPosInt]);
		}			
	}
	else
	{
	if(houseid != -1) SetPlayerPosEx(playerid,HouseInfo[houseid][hExitX],HouseInfo[houseid][hExitY],HouseInfo[houseid][hExitZ] + 1.0);
	
	if(bizid != -1) SetPlayerPosEx(playerid,BizInfo[bizid][bizExitX], BizInfo[bizid][bizExitY], BizInfo[bizid][bizExitZ] + 1.0);
	}

	SM1(playerid, "Blaze Guard seni bulunduðun durumdan kurtardý. Ýyi eðlenceler dileriz!");
	UnFreezePlayer(playerid);
	return 1;
}

ShowPlayerName(playerid, bool:show)
{
	if (show)
	{
		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, 1);
		}
	}
	else
	{
		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, 0);
		}
	}
	return 1;
}

SetPlayerBuyInterior(playerid, step, houseid = 0)
{
	if (!step)
	{
	    if (pTemp[playerid][pInteriorBiz] == 0) return 1;
        
	    TogglePlayerSpectating(playerid, 0);
		DestroyPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
  		HideMenuForPlayer(buy_interior, playerid);
		return 1;
	}

    new bizid = -1;

	if ((bizid = GetNearInsideBiz(playerid)) == -1 || BizInfo[bizid][bizType] != BIZ_BUILD)	return SendErrorMessage(playerid, "Bir mimarlýk ofisinde olmalýsýnýz.");
	    
	new start = -1;

    for(new i = 0; i < MAX_INTERIORS; i++)
	{
		if (!AdminTeles[i][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[i][telesType]) continue;

		start = i;
		break;
	}
	
	if (start == -1)	 return SendErrorMessage(playerid, "Eviniz için uygun interior bulunamadý.");
	    
	SavePlayerPos(playerid);
    GameTextForPlayer(playerid, "_", 1, 4);
	TogglePlayerSpectating(playerid, 1);
    pTemp[playerid][pInteriorBiz] = bizid+1;
    pTemp[playerid][pInteriorHouse] = houseid+1;
    pTemp[playerid][pInteriorID] = start;
    pTemp[playerid][pInteriorObj] = CreatePlayerObject(playerid, 19300, AdminTeles[start][telesPosX], AdminTeles[start][telesPosY], AdminTeles[start][telesPosZ], 0.0, 0.0, 0.0);
	AttachCameraToPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
	SetInterior(playerid, AdminTeles[start][telesInt]);
	SetWorld(playerid, 5000 + playerid);
	ShowMenuForPlayer(buy_interior, playerid);
	SendServerMessage(playerid, "Butonlar arasýnda geçiþi ok tuþlarýyla yapýp, SPACE tuþuna basarak seçimleri gerçekleþtir.");
	return 1;
}

IsPlayerAtCarfix(playerid)
{
    if (PlayerInfo[playerid][pFaction] == 0) return 0;
    
	new i = PlayerInfo[playerid][pFaction];
	
	if (GetWorld(playerid) != Factions[i][Carfix][fixVW] || GetInterior(playerid) != Factions[i][Carfix][fixInt]) return 0;

	if (PlayerToPoint(15.0, playerid, Factions[i][Carfix][fixX], Factions[i][Carfix][fixY], Factions[i][Carfix][fixZ]) != 0) return 1;
	
	return 0;
}

PlaySoundEx(soundid, Float:x, Float:y, Float:z, range)
{
	foreach(new i : Player)
	{
		if(!IsPlayerInRangeOfPoint(i, range, x, y, z)) continue;
		PlayerPlaySound(i, soundid, 0, 0, 0);
	}
}

PlaySound(playerid, soundid)
{
	PlayerPlaySound(playerid, soundid, 0.0, 0.0, 0.0);
}

PlayerPlaySoundEx(playerid, sound)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	foreach (new i : Player)
	{
	    if (!IsPlayerLogged(i) && IsPlayerInRangeOfPoint(i, 20.0, x, y, z) && GetWorld(i) != GetWorld(playerid) && GetInterior(playerid) != GetInterior(i)) continue;

	    PlayerPlaySound(i, sound, 0.0, 0.0, 0.0);
	}
	return 1;
}

q_GetPlayerIP(playerid)
{
	new IP[24];

	GetPlayerIp(playerid, IP, sizeof(IP));
	return IP;
}

Save_User(playerid)
{	
	if (!IsPlayerLogged(playerid))	return 1;

    if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
    {
		SavePlayerPos(playerid);
	}

	new Float:health, Float:armour;
	GetPlayerArmour(playerid, armour);
	GetPlayerHealth(playerid, health);
	
	SilahlariKaydet(playerid);
    new division_string[256];

	for(new j; j < 5; j++)
		format(division_string, sizeof(division_string), "%s%d|", division_string, PlayerInfo[playerid][pOlusumDivision][j]);

	new weapons[24];
	new ammo[24];
	new weapons_string[256];
	for(new x; x < 12; x++)
	{
		BWH_GetPlayerWeaponData(playerid, x, weapons[x], ammo[x]);
		if(!AC_PlayerHasWeapon(playerid, weapons[x]) || !ammo[x])
		{
			weapons[x] = 0;
			ammo[x] = 0;
		}

		if(PlayerInfo[playerid][pOnDuty])
			format(weapons_string, sizeof(weapons_string), "%s%d|%d|", weapons_string, weapons[x], ammo[x]);

		else
			format(weapons_string, sizeof(weapons_string), "%s%d|%d|", weapons_string, 0, 0);
	}		

	new query[9096];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `health`=%f,`armour`=%f,`cash`=%i,`bank`=%i,`skin`=%i,`sex`=%i,`age` = %i, `origin` = %i, `race` = %i, `level`=%i,`exp`=%i, `birthdate` = %i, `hours`=%i,`minutes`=%i,`admin_hide`=%i,`int`=%i,`world`=%i,`channel`=%i,`owned_channel`=%i,`authed`=%i,`paydaytime`=%i,`number`=%i, `puncte`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pHealth], armour, PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], 
		PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pSex], PlayerInfo[playerid][pAge], PlayerInfo[playerid][pOrigin], PlayerInfo[playerid][pRace], PlayerInfo[playerid][pLevel],
		PlayerInfo[playerid][pExp], PlayerInfo[playerid][pBirthdate], PlayerInfo[playerid][pHours], PlayerInfo[playerid][pMinutes], PlayerInfo[playerid][pAdminHide], PlayerInfo[playerid][pInt], 
		PlayerInfo[playerid][pWorld], PlayerInfo[playerid][pChannel], PlayerInfo[playerid][pOwnedChannel], 
		PlayerInfo[playerid][pAuthed], PlayerInfo[playerid][pPayDayTime], PlayerInfo[playerid][pNumber], PlayerInfo[playerid][pPunctePremium], PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `ajailed`=%i,`ajailtime`=%i,`jailed`=%i,`isolatetime`=%i,`warns`=%i,`vip`=%i,`carlic`=%i,`weplic`=%i,`flylic`=%i,`savings`=%i,`rent_key`=%i,`rent_price`=%i,`taxilic`=%i,`dependence`=%i,`demolition`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pAJailed], PlayerInfo[playerid][pAJailTime], PlayerInfo[playerid][pJailed], 
		PlayerInfo[playerid][pIsolateTime], PlayerInfo[playerid][pWarns], PlayerInfo[playerid][pPremium], 
		PlayerInfo[playerid][pCarLic], PlayerInfo[playerid][pWepLic], PlayerInfo[playerid][pFlyLic],
		PlayerInfo[playerid][pSavings], PlayerInfo[playerid][pRentKey], PlayerInfo[playerid][pRentPrice],
		PlayerInfo[playerid][pTaxiLic], PlayerInfo[playerid][pDependence], PlayerInfo[playerid][pDemolition],PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `arrested`=%i,`chat`=%i,`authwep`=%i,`swat`=%i,`swat_duty`=%i,`lawyer`=%i,`job`=%i,`career`=%i,`fightstyle`=%i,`hud`=%i,`mutetime`=%i,`phone_off`=%i,`phone_airplane`=%i,`paycheck`=%i,`fishcount`=%i,`fish_time`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pArrested], PlayerInfo[playerid][pTalk], PlayerInfo[playerid][pAuthwep], 
		PlayerInfo[playerid][pSwat], PlayerInfo[playerid][pSwatDuty], PlayerInfo[playerid][pLawyer], PlayerInfo[playerid][pJob], 
		PlayerInfo[playerid][pCareer], PlayerInfo[playerid][pFightStyle], PlayerInfo[playerid][pHud], 
		PlayerInfo[playerid][pMutedTime], PlayerInfo[playerid][pPhoneOff], PlayerInfo[playerid][pPhoneAirplane],
		PlayerInfo[playerid][pPayCheckMoney], PlayerInfo[playerid][pFishCount], PlayerInfo[playerid][pFishTime],PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `walk`=%i,`faction`=%i, `rank`=%i,`phone_sound`=%i,`phone_model`=%i,`phone_ringtone`=%i,`badgenumber`=%i,`drivewarns`=%i,`wepwarns`=%i,`wep_count`=%i,`jailtime`=%i,`slot`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pWalk], PlayerInfo[playerid][pFaction], PlayerInfo[playerid][pRank],
		PlayerInfo[playerid][pPhoneSound], PlayerInfo[playerid][pPhoneModel], PlayerInfo[playerid][pPhoneRingtone],
		PlayerInfo[playerid][pBadgeNumber], PlayerInfo[playerid][pDriveWarns], PlayerInfo[playerid][pWepWarns], 
		PlayerInfo[playerid][pWepCount],PlayerInfo[playerid][pJailTime],PlayerInfo[playerid][pSlot], PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `sidejob`=%i,`prescribe`=%i,`ganja_time`=%i,`phone_style`=%i,`sparekey`=%i,`workon`=%i,`pos_X`=%f,`pos_Y`=%f,`pos_Z`=%f,`pos_A`=%f,`prisoned`=%i WHERE `id`=%i",
    	PlayerInfo[playerid][pSideJob], PlayerInfo[playerid][pPrescribe], PlayerInfo[playerid][pGanjaTime], 
		PlayerInfo[playerid][pPhoneStyle], PlayerInfo[playerid][pSpareKey], PlayerInfo[playerid][pWorkOn],
		PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ], 
		PlayerInfo[playerid][pPosA], PlayerInfo[playerid][pPrisoned],PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

    mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `weaphide0`=%i,`weaphide1`=%i,`weaphide2`=%i,`duty`=%i,`char`=%i,`drugaccess`=%i,`tog_0`=%i,`tog_1`=%i,`tog_2`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pHideWeap][0], PlayerInfo[playerid][pHideWeap][1], PlayerInfo[playerid][pHideWeap][2],
		PlayerInfo[playerid][pOnDuty], PlayerInfo[playerid][pChar], PlayerInfo[playerid][pDrugLabAccess],
		PlayerInfo[playerid][pTog][0], PlayerInfo[playerid][pTog][1], PlayerInfo[playerid][pTog][2], PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

   	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET zar = %d, oyunkarti = %d, benzinbidonu = %d, telsiz = %d, kalem = %d, sigara = %d, cakmak = %d, bagimlilik_exp = '%d', bagimlilik_seviye = '%d', tedavi_exp = '%d', tedavi_sure = '%d', kriz_sure = '%d' WHERE `id`=%i",
		PlayerInfo[playerid][pZar], PlayerInfo[playerid][pOyunKarti], PlayerInfo[playerid][pBenzinBidonu], 
		PlayerInfo[playerid][pTelsiz], PlayerInfo[playerid][pKalem], PlayerInfo[playerid][pSigara], PlayerInfo[playerid][pCakmak],
		PlayerInfo[playerid][pBagimlilikEXP],
		PlayerInfo[playerid][pBagimlilikSeviye],
		PlayerInfo[playerid][pUTedaviEXP],
		PlayerInfo[playerid][pUTedaviSure],
		PlayerInfo[playerid][pKrizSure],  
		PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

   	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET maske = %d, boombox = %d, kamera = %d, cicek = %d, string_weapons = '%e', `division`='%e',`ReportMute`=%d,`PlayerSerial`=%i,`LastPrim`=%i,`LastSec`=%i,`LastMelee`=%i,`Forbid`=%i,`char`=%i WHERE `id`=%i",
		PlayerInfo[playerid][pMaske], PlayerInfo[playerid][pBoombox], PlayerInfo[playerid][pCicek], PlayerInfo[playerid][pKamera], weapons_string, division_string, PlayerInfo[playerid][pReportMute], PlayerInfo[playerid][pPlayerSerial], PlayerInfo[playerid][pLastPrim], 
		PlayerInfo[playerid][pLastSec], PlayerInfo[playerid][pLastMelee], PlayerInfo[playerid][pForbid], PlayerInfo[playerid][pChar], PlayerInfo[playerid][pID]
	);
	mysql_tquery(dbHandle, query);

	//printf(playerid, "%s", query);
	return 1;
}

stock Fuel_ResetPlayer(playerid) 
{
    if (RefuelTimer[playerid] != -1)
    {
        KillTimer(RefuelTimer[playerid]);
        RefuelTimer[playerid] = -1;
        PlayerTextDrawHide(playerid, FuelText[playerid]);
    }
 
    DeletePVar(playerid, #UsePump);
    DeletePVar(playerid, #FuelBought);
    return 1;
}

ResetVariables(playerid)
{
    pTemp[playerid][pPizzaBoy] = 
    pTemp[playerid][pDemolitionTime] =
	pTemp[playerid][pDrugUse] =
	pTemp[playerid][pDrugTime] =
	pTemp[playerid][pDrugChgWeather] =
    pTemp[playerid][pLicenseExam] =
	pTemp[playerid][pWaypoint] = 
    pTemp[playerid][pWaypoint] = 
	pTemp[playerid][pWepPrice] =
	pTemp[playerid][pRentPrice] = 
	pTemp[playerid][pHousePrice] =
    pTemp[playerid][pRentveh] = 
	pTemp[playerid][pServeType] = 
	pTemp[playerid][pGreetType] =
    pTemp[playerid][pNews] = 
	pTemp[playerid][pCallOn] =
	pTemp[playerid][pFishTime] =
    pTemp[playerid][pEditBort] = 
	pTemp[playerid][pCarPrice] = 
	pTemp[playerid][tempItem] = 
	pTemp[playerid][tempEx] = 
	pTemp[playerid][tempQ] = 	
    pTemp[playerid][pHealTime] = 
    pTemp[playerid][pRamType] =
	pTemp[playerid][UsingBort] = 
	pTemp[playerid][UsingCorpse] =
	pTemp[playerid][tempStatus] =
    pTemp[playerid][pRamTime] = 0;

	pTemp[playerid][pHouseHouse] = -1;

	pTemp[playerid][pBizPrice] = 0;
	pTemp[playerid][pBizID] = INVALID_PLAYER_ID;

    pTemp[playerid][pInterview] = 
	pTemp[playerid][pInterviewPlayer] =
	pTemp[playerid][pHealPlayer] = 
    pTemp[playerid][pFactionPlayer] = 
	pTemp[playerid][pBizPlayer] = 
    pTemp[playerid][pFriskPlayer] = 
	pTemp[playerid][pSpecPlayer] = 
	pTemp[playerid][pHirePlayer] = 
	pTemp[playerid][pCarPlayer] = 
	pTemp[playerid][pWepPlayer] = 
	pTemp[playerid][pRentPlayer] = 
	pTemp[playerid][pHousePlayer] =
	pTemp[playerid][pServePlayer] = 
	pTemp[playerid][pGreetPlayer] = INVALID_PLAYER_ID;

	for(new c = 0; c < 5; c++)
	{
		pTemp[playerid][MyCarSpawn][c] = 0;
		pTemp[playerid][MyCarSpawn][c] = 0;
	}

	SetPVarInt(playerid, #attach_item, 0);

	if(IsPlayerPhoneCreated(playerid))
		Phone_Destroy(playerid);

	if (IsPlayerUseMDC(playerid))		MDC_Hide(playerid);

    if (IsValidDynamicObject(pTemp[playerid][pRamObj]))
	{
		DestroyDynamicObject(pTemp[playerid][pRamObj]);
		pTemp[playerid][pRamObj] = INVALID_OBJECT_ID;
	}

	PlayerInfo[playerid][pArmour] = 0.0;

	if (pTemp[playerid][pFlashTime]) pTemp[playerid][pFlashTime] = 1;

	if (pTemp[playerid][p3DMenu] != -1)
	{
    	Destroy3DMenu(pTemp[playerid][p3DMenu]);
		pTemp[playerid][p3DMenu] = -1;
	}

	if (IsPlayerPhoneCreated(playerid)) Phone_Destroy(playerid);

	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID)
	{
	    SendPhoneMessage(pTemp[playerid][pCallLine], "Baðlantý kesildi ...");
	    pc_cmd_telefonkapat(playerid, "");
		
	}
	pTemp[playerid][pEmergency] = 0;

	if (GetPVarInt(playerid, #selfie)) DeletePVar(playerid, #selfie);

    if (pTemp[playerid][pTracePlayer] != INVALID_PLAYER_ID)
	{
	    pTemp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
		pTemp[playerid][pTraceStage] = 0;

		if (pTemp[playerid][pTraceGZ] != -1) GangZoneDestroy(pTemp[playerid][pTraceGZ]);

		pTemp[playerid][pTraceGZ] = -1;
	}

	if (pTemp[playerid][pCargoID]) pTemp[playerid][pCargoID] = 0;
	
	RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
	TogglePlayerAllDynamicRaceCPs(playerid, false);
	TogglePlayerAllDynamicCPs(playerid, false);
	EndJob(playerid);
	Fuel_ResetPlayer(playerid);
	return 1;
}

KickEx(playerid)
{
	if (GetPVarInt(playerid,"kicked")) return 1;

    SendServerMessage(playerid, "Sistem tarafýndan oyundan atýldýnýz.");
    SetPVarInt(playerid,"kicked", 1);
    SetTimerEx("KickPlayer", 200, false, "d", playerid);
    return 1;
}

ShowStats(playerid, id)
{
	new nums[32], works[64], donate[50], fname[50], rname[50];
	new year, month, day, hour, minute, second;

	if (PlayerInfo[id][pNumber] == 0) 	nums = "Bulunamadý";
	else								format(nums, sizeof(nums), "%i", PlayerInfo[id][pNumber]);

	if (PlayerInfo[id][pWorkOn] == 0)	works = "Bulunamadý";
	else								format(works, sizeof(works), "%i", PlayerInfo[id][pWorkOn]);

	if (PlayerInfo[id][pFaction] == 0)	fname = "Bulunamadý";
	else								format(fname, 32, "%s", Factions[PlayerInfo[id][pFaction]][fName]);

	if (PlayerInfo[id][pRank] == 0)		rname = "Bulunamadý";
	else								format(rname, 32, "%s", GetRankName(id));

	switch(PlayerInfo[id][pPremium])
	{
	    case 1: donate = "BRONZ";
	    case 2: donate = "SILVER";
	    case 3: donate = "GOLD";
		default: donate = "Yok";
	}

	getdate(year, month, day);
	gettime(hour, minute, second);

	new expamount = (PlayerInfo[id][pLevel]+1) * LEVEL_EXP;

	SendClientMessageEx(playerid, COLOR_SERVER2,"[%s (%i) | %02d %s %i, %02d:%02d:%02d]", GetNameEx(id), id, day, GetMonthName(month), year, hour, minute, second);
	SendClientMessageEx(playerid, COLOUR_ALTO,  "Forum Adý: [%s] Birlik: [%s] Rütbe: [%s]", GetAccName(id), fname, rname);
	SendClientMessageEx(playerid, COLOUR_WHITE, "Nakit: [$%i] Banka: [$%i] Maaþ Hesabý: [$%i] Mevduat Hesabý: [$%i]", GetCash(id), PlayerInfo[id][pBank], PlayerInfo[id][pPayCheckMoney], PlayerInfo[id][pSavings]);
	SendClientMessageEx(playerid, COLOUR_ALTO,  "Seviye: [%i] EXP: [%i / %i] Maaþa kalan süre: [%i dakika] ", PlayerInfo[id][pLevel], PlayerInfo[id][pExp], expamount, 60 - PlayerInfo[id][pPayDayTime]);
	SendClientMessageEx(playerid, COLOUR_WHITE, "Telefon Numarasý: [%s] Dövüþ Stili: [%s] Baðýþçý: [Yok]", nums, GetFightStyleName(id));
	SendClientMessageEx(playerid, COLOUR_ALTO, "Çalýþýlan Ýþletme: [%s] Ana Meslek: [%s] Ýkinci Meslek: [%s]", works, GetJobName(PlayerInfo[id][pJob]), GetJobName(PlayerInfo[id][pSideJob]));
	SendClientMessageEx(playerid, COLOUR_WHITE,  "Uyarýlar: [%i] IP: [%s] Admin: [%s] Supporter: [%s]", PlayerInfo[id][pWarns], q_GetPlayerIP(id), (PlayerInfo[id][pAdmin] != 0)?("Yönetici"):("Yönetici Deðil"), (PlayerInfo[id][pHelper] != 0)?("Supporter"):("Supporter Deðil"));
	if(PlayerInfo[id][pBagimlilikEXP] > 0 || PlayerInfo[id][pBagimlilikSeviye] > 0) SendClientMessageEx(playerid, COLOUR_ALTO, "Baðýmlýlýk EXP: %d/3 | Baðýmlýlýk Seviyesi: %d | Tedavi EXP: %d/10 | Tedaviye Kalan Süre: %d dakika | Krize Kalan Süre: %d dakika", PlayerInfo[id][pBagimlilikEXP], PlayerInfo[id][pBagimlilikSeviye], PlayerInfo[id][pUTedaviEXP], PlayerInfo[playerid][pUTedaviSure], PlayerInfo[id][pKrizSure]);
	if (CheckAdmin(playerid, ADMIN_LEVEL_1))
	{
		if (PlayerInfo[id][pJailed] != 0)		SendClientMessageEx(playerid, COLOUR_WHITE, "IC Hapis: [%i dakika]", PlayerInfo[id][pJailTime]);
    	if (PlayerInfo[id][pMutedTime] > 0)		SendClientMessageEx(playerid, COLOUR_WHITE, "Susturulma: [%i dakika]", PlayerInfo[id][pMutedTime]);
		if (PlayerInfo[id][pForbid] != 0)		SendClientMessageEx(playerid, COLOUR_WHITE, "Silah Yasaðý: [%i saat]", PlayerInfo[id][pForbid]);
		if (id != playerid)						SendHelpMessage(playerid,"Envanter kontrolü için {ffc46a}/check %i", id);
		SendClientMessageEx(playerid, COLOUR_WHITE, "Virtual World: [%d], Interior: [%d]", GetPlayerVirtualWorld(id), GetPlayerInterior(id));
	}

	SendClientMessageEx(playerid, COLOR_SERVER2,"[%s (%i) | %02d %s %i, %02d:%02d:%02d]", GetNameEx(id), id, day, GetMonthName(month), year, hour, minute, second);
	return 1;
}

SetSpawnInfoEx(playerid, Float:x, Float:y, Float:z, Float:Angle = 0.0)
{
    if (PlayerInfo[playerid][pChar] > 0)	SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pChar], x, y, z, Angle, 0, 0, 0, 0, 0, 0);
	else									SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pSkin], x, y, z, Angle, 0, 0, 0, 0, 0, 0);
	return 1;
}

GetNameForPlayer(playerid)
{
    GetPlayerName(playerid, PlayerInfo[playerid][pUsername], MAX_PLAYER_NAME+1);
    GetPlayerName(playerid, PlayerInfo[playerid][pUsername_], MAX_PLAYER_NAME+1);
    strreplace(PlayerInfo[playerid][pUsername_], '_', ' ');
    format(PlayerInfo[playerid][pMaskname], 32, PlayerInfo[playerid][pUsername_]);
    return 1;
}

GetIDByID(databaseid)
{
	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i)) 												continue;
		if (PlayerInfo[i][pID] == databaseid)								return i;
	}
	return INVALID_PLAYER_ID;
}

stock IsPlayerLoggedIn(playerid)
{
    new bool:result = false;

    if(playerid != INVALID_PLAYER_ID && IsPlayerConnected(playerid) && pTemp[playerid][pSpawned] == 1 && PlayerInfo[playerid][pID] >= 0 && PlayerInfo[playerid][pAccID] > 0)
        result = true;

    return result;
}

stock GetPlayerIDByAccountSqlID(sqlid)
{
    new id = INVALID_PLAYER_ID;

    foreach(new i : Player)
    {
        if(!IsPlayerLogged(i))
            continue;

        if(PlayerInfo[i][pAccID] != sqlid)
            continue;

        id = i;
        break;
    }

    return id;
}

this::KickTimerLine(playerid)
{
	Kick(playerid);
	return 1;
}

stock KickLine(playerid, reason[] = "")
{
    if(strlen(reason) > 3)
    {
        SCM(playerid, COLOUR_TOMATO, sprintf("%s", reason));
    }

    SetTimerEx("KickTimerLine", 1500, false, "d", playerid);
    return 1;
}

CheckPMBlockList(playerid)
{
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || people_blocking[i][playerid] != 1)			continue;

        SendSyntaxMessage(i, "%s sunucuyla baðlantýsý kesildi ve PM blok listenizden kaldýrýldý.", GetNameEx(playerid), playerid);
		people_blocking[i][playerid] = 0;
	}
	return 1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, &Float:Z, Float:distance)
{
	new Float:A;
	GetPlayerPos(playerid, X, Y, Z);

	if (GetPlayerVehicleID(playerid))	GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
	else								GetPlayerFacingAngle(playerid, A);

	X += (distance * floatsin(-A, degrees));
	Y += (distance * floatcos(-A, degrees));
}

#define GetVectorSpeed(%0,%1,%2) floatround(VectorSize(%0, %1, %2) * 179.28625)
SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, freeze = 1)
{
	SetPVarInt(playerid, "tpOnlem", 1);
	pTemp[playerid][HileKontrol] = gettime() + 4;
	SetPlayerPos(playerid, x, y, z + 0.6);
 	SetCameraBehindPlayer(playerid);
	PlayerEnterFreeze(playerid);
	if (freeze != 0)
	{
 		FreezePlayer(playerid);
 		pTemp[playerid][pFreezeTime] = 2;
	}
	if(FlyMode[playerid]) SetPlayerObjectPos(playerid, noclipdata[playerid][flyobject], x, y, z);
	return 1;
}

SetPlayerCurrentTimeAndWeather(playerid)
{
	SetPlayerTime(playerid, server_hour, 0);
	SetPlayerWeather(playerid, server_weather);
	return 1;
}

GetFightStyleName(playerid)
{
	new style[9];
	switch(PlayerInfo[playerid][pFightStyle])
	{
		case FIGHT_STYLE_BOXING: format(style, sizeof(style), "Boxing");
		case FIGHT_STYLE_KUNGFU: format(style, sizeof(style), "Kungfu");
		case FIGHT_STYLE_GRABKICK: format(style, sizeof(style), "Grabkick");
		case FIGHT_STYLE_KNEEHEAD: format(style, sizeof(style), "Kneehead");
		case FIGHT_STYLE_NORMAL: format(style, sizeof(style), "Standart");
	}
	return style;
}

Dialog:MODEL_SEL_BUYCLOTHES(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new modelid = strval(inputtext);

	if (GetCash(playerid) < 100)	return SendNotCash(playerid);
	if (GetPlayerSkin(playerid) == modelid || PlayerInfo[playerid][pTog][0] == modelid || PlayerInfo[playerid][pTog][1] == modelid || PlayerInfo[playerid][pTog][2] == modelid) 
	{
		return SendErrorMessage(playerid, "Bu kýyafeti zaten satýn almýþsýnýz.");
	}

	new mes[128];

	for(new i; i != 3; i++)
	{
		if (PlayerInfo[playerid][pTog][i] == 0)	strcat(mes, "\n[Boþ Slot]");
		else									format(mes, sizeof(mes), "%s\n[Skin #%i]", mes, PlayerInfo[playerid][pTog][i]);
	}

	Dialog_Show(playerid, BuyClothes, DIALOG_STYLE_LIST, "Kýyafet Dolabý", mes, "Deðiþtir", "X");
	SetPVarInt(playerid, "clothes_model", modelid);
	return 1;
}

CreateDynamicExplosion(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,playerid = -1,Float:distance = 200.0){
	if (playerid == -1){
		foreach(new i : Player){
			new Float:px, Float:py, Float:pz;
			if (IsPlayerInAnyVehicle(i)){
				GetVehiclePos(GetPlayerVehicleID(i),px,py,pz);
			} else {
				GetPlayerPos(i,px,py,pz);
			}
			if ((GetPlayerInterior(i) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(i) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(i,x,y,z,type,radius);
			}
		}
	} else {
		if (IsPlayerConnected(playerid)){
			new Float:px, Float:py, Float:pz;
			if (IsPlayerInAnyVehicle(playerid)){
				GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			} else {
				GetPlayerPos(playerid,px,py,pz);
			}
			if ((GetPlayerInterior(playerid) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(playerid) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(playerid,x,y,z,type,radius);
			}
		}
	}
} 

GetLocationZone(Float:x, Float:y, Float:z)
{
	new string[128], zone[28];

	GetZone(x, y, zone, sizeof(zone));
	
	if (IsPointInAnyDynamicArea(x, y, z)) {
		new areas[10], street_area[2], j = GetNumberDynamicAreasForPoint(x,y,z);
		GetDynamicAreasForPoint(x, y, z, areas, sizeof(areas));

		if (GetStreet(areas, j, street_area)) {
			if (street_area[1] == -1) format(string, sizeof(string), "%s, %s", zone, street_names[street_area[0]]); 
			else					 format(string, sizeof(string), "%s, %s ve %s", zone, street_names[street_area[0]],street_names[street_area[1]]);
		}
	}
	format(string, sizeof(string), "%s", zone);

	return string;
}

stock bool:IsPlayerCrouching(playerid)
{
    if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) return false;
	return true;
}

CheckHanditem(playerid, model) {
	new result = 0;
	for(new i = 0; i < MAX_PLAYER_ATTACH; i++)
	{
		if (!AttachInfo[playerid][i][aUsed]) 										   continue;
		if (AttachInfo[playerid][i][aModel] != model)								   continue;
		if (AttachInfo[playerid][i][aBone] != 5 && AttachInfo[playerid][i][aBone] != 6) continue;
		return 1;
	}
	
	return result;
}

stock PlaySoundInArea(soundid,Float:x,Float:y,Float:z,Float:radi)
{
    foreach(new i : Player)
	{
        if (!IsPlayerLogged(i)) continue;
	    if (IsPlayerInRangeOfPoint(i,radi,x,y,z)) PlayerPlaySound(i, soundid, x, y, z);
	}
	return 1;
}

Float:XB_GetDistanceBetweenTPoints(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz)
{
	new Float:temp1, Float:temp2 , Float:temp3;
	temp1 = x-tx;temp2 = y-ty;
	temp3 = z-tz;
	return floatsqroot(temp1*temp1+temp2*temp2+temp3*temp3);
}

CheckNumberAvailable(number)
{
	new
		query[64]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) as total FROM `users` WHERE `number`=%i", number);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
	cache_get_value_int(0, "total", count);

	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return count;
}

SetPlayerNumber(playerid) {	
	mysql_tquery(dbHandle, "SELECT FLOOR(RAND()*(999999-100100)+100100) as randNumber \
							FROM `users` \
							HAVING (SELECT COUNT(*) FROM `users` WHERE number = randNumber) < 1 \
							LIMIT 1", 
				"GetPlayerNumber", "i", playerid
	);
	return 1;
}

this::GetPlayerNumber(playerid) {
	if (!cache_num_rows()) return SetPlayerNumber(playerid);

	cache_get_value_int(0, "randNumber", PlayerInfo[playerid][pNumber]);
	SQL_SetInteger("users", "number", PlayerInfo[playerid][pNumber], PlayerInfo[playerid][pID]);

	SendSyntaxMessage(playerid, "Yeni bir telefon numarasý atandý: %i (/telefon)", PlayerInfo[playerid][pNumber]);
	return 1;
}

CreatePlayersFire(playerid, type, building)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	if (GetDistanceBetweenPoints(x,y,z,PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]) > 1.5 
		&& PlayerInfo[playerid][pWorld] != GetWorld(playerid) 
		&& PlayerInfo[playerid][pInt] != GetInterior(playerid)
	) {
		StopCreatingPlayersFire(playerid);
		return SendErrorMessage(playerid, "Ateþ yakýlamadý, tekrar deneyin!");
	}
	
	new 
		location[128], 
		where[12], 
		Float:ExpPos[3]
	;

	switch(type) {
		case 0: {
			CreateFireInHouse(building);

			if (HouseInfo[building][hApart]) {
				ExpPos[0] = ApartInfo[HouseInfo[building][hApart]][aPosX];
				ExpPos[1] = ApartInfo[HouseInfo[building][hApart]][aPosY];
				ExpPos[2] = ApartInfo[HouseInfo[building][hApart]][aPosZ];

				where = "bina";
			} else {
				ExpPos[0] = HouseInfo[building][hPosX]; 
				ExpPos[1] = HouseInfo[building][hPosY];
				ExpPos[2] = HouseInfo[building][hPosZ];

				where = "ev";
			}
		}
		case 1: {
			CreateFireInBiz(building);

			ExpPos[0] = BizInfo[building][bizPosX]; 
			ExpPos[1] = BizInfo[building][bizPosY];
			ExpPos[2] = BizInfo[building][bizPosZ];

			where = "iþyeri";
		} 
		case 2: {
			CreateFireInGarage(building);

			ExpPos[0] = GarageInfo[building][garageVeh_Enter][0]; 
			ExpPos[1] = GarageInfo[building][garageVeh_Enter][1];
			ExpPos[2] = GarageInfo[building][garageVeh_Enter][2];

			where = "garaj";
		}
	}

	format(location, sizeof(location), "%s", GetLocationZone(x,y,z));

	for(new i = FACTION_POLICE; i <= FACTION_FIRE; i++)
	{
		SendFactionMessage(i, COLOR_LIGHTBLUE, "|__________Acil Çaðrý__________|");
		SendFactionMessage(i, COLOR_LIGHTBLUE, "Aranma Yeri: Ankesörlü Telefon");
		SendFactionMessage(i, COLOR_LIGHTBLUE, "Talep: Polis, Ambulans / Ýtfaiye");
		SendFactionMessage(i, COLOR_LIGHTBLUE, "Lokasyon: %s %i", location, building);
		SendFactionMessage(i, COLOR_LIGHTBLUE, "Durum: Yangýn çýktý %s!", where);			
	}

	for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
	{
	    if (CallInfo[i][callExists] != 0) continue;

       	CallInfo[i][callPosX] = ExpPos[0];
		CallInfo[i][callPosY] = ExpPos[1];
		CallInfo[i][callPosZ] = ExpPos[2];

        CallInfo[i][callType] = 3;
		CallInfo[i][callPhone] = 0;

		format(CallInfo[i][callText], 128, "Yangýn çýktý: %s!", where);
		format(CallInfo[i][callName], MAX_PLAYER_NAME, "Ankesörlü Telefon");
        format(CallInfo[i][callDate], 32, "%s", GetFullDate());
        format(CallInfo[i][callLocation], MAX_ZONE_NAME, "%s %i", location, building);
        
        CallInfo[i][callDelete] = gettime() + 1200;
        CallInfo[i][callExists] = 1;
        break;
	}

	return 1;
}

StopCreatingPlayersFire(playerid)
{
	UnFreezePlayer(playerid);
	StopPlayerAnims(playerid);
	pTemp[playerid][pFireTime] = 0;
	DeletePVar(playerid, #firetype);
	DeletePVar(playerid, #firebuildID);
	return 1;
}

GetHealthDots(playerid)
{
    new
        dots[64], Float: HP;
 
    AntiCheatGetHealth(playerid, HP);
 
	if (HP >= 100)
        dots = "IIIIIIIIII";
    else if (HP >= 90)
        dots = "IIIIIIIII{660000}I";
    else if (HP >= 80)
        dots = "IIIIIIII{660000}II";
    else if (HP >= 70)
        dots = "IIIIIII{660000}III";
    else if (HP >= 60)
        dots = "IIIIII{660000}IIII";
    else if (HP >= 50)
        dots = "IIIII{660000}IIIII";
    else if (HP >= 40)
        dots = "IIII{660000}IIIIII";
    else if (HP >= 30)
        dots = "III{660000}IIIIIII";
    else if (HP >= 20)
        dots = "II{660000}IIIIIIII";
    else if (HP >= 10)
        dots = "I{660000}IIIIIIIII";
    else if (HP >= 0)
        dots = "{660000}IIIIIIIIII";

    /*if (HP >= 100)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 90)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{660000}ï¿½";
    else if (HP >= 80)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{660000}ï¿½ï¿½";
    else if (HP >= 70)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{660000}ï¿½ï¿½ï¿½";
    else if (HP >= 60)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{660000}ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 50)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½{660000}ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 40)
        dots = "ï¿½ï¿½ï¿½ï¿½{660000}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 30)
        dots = "ï¿½ï¿½ï¿½{660000}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 20)
        dots = "ï¿½ï¿½{660000}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 10)
        dots = "ï¿½{660000}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (HP >= 0)
        dots = "{660000}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";*/
 
    return dots;
}
 
GetArmorDots(playerid)
{
    new
        dots[64], Float: AR;
 
    AntiCheatGetArmour(playerid, AR);
	
	if (AR >= 100)
        dots = "IIIIIIIIII";
    else if (AR >= 90)
        dots = "IIIIIIIII{666666}I";
    else if (AR >= 80)
        dots = "IIIIIIII{666666}II";
    else if (AR >= 70)
        dots = "IIIIIII{666666}III";
    else if (AR >= 60)
        dots = "IIIIII{666666}IIII";
    else if (AR >= 50)
        dots = "IIIII{666666}IIIII";
    else if (AR >= 40)
        dots = "IIII{666666}IIIIII";
    else if (AR >= 30)
        dots = "III{666666}IIIIIII";
    else if (AR >= 20)
        dots = "II{666666}IIIIIIII";
    else if (AR >= 10)
        dots = "I{666666}IIIIIIIII";
    else if (AR >= 0)
        dots = "{666666}IIIIIIIIII";

    /*if (AR >= 100)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 90)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{666666}ï¿½";
    else if (AR >= 80)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{666666}ï¿½ï¿½";
    else if (AR >= 70)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{666666}ï¿½ï¿½ï¿½";
    else if (AR >= 60)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½{666666}ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 50)
        dots = "ï¿½ï¿½ï¿½ï¿½ï¿½{666666}ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 40)
        dots = "ï¿½ï¿½ï¿½ï¿½{666666}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 30)
        dots = "ï¿½ï¿½ï¿½{666666}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 20)
        dots = "ï¿½ï¿½{666666}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 10)
        dots = "ï¿½{666666}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";
    else if (AR >= 0)
        dots = "{666666}ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½";*/
 
    return dots;
}

this::Invulnerable(playerid)
{
	if (pTemp[playerid][pInvulnerable] == 0.0) {
		pTemp[playerid][pInvulnerable] = 30.0;
	}

	PlayerInfo[playerid][pHealth] = pTemp[playerid][pInvulnerable];
	pTemp[playerid][pInvulnerable] = 0.0;
	return 1;
}

stock to_date( timestamp, _form=0 )
{
    /*
        ~ convert a Timestamp to a Date.
        ~ 10.07.2009

        date( 1247182451 )  will print >> 09.07.2009-23:34:11
        date( 1247182451, 1) will print >> 09/07/2009, 23:34
        date( 1247182451, 2) will print >> July 09, 2009, 23:34:11
        date( 1247182451, 3) will print >> 9 Jul 2009, 23:34
    */
    new year=1970, day=0, month=0, hour=0, mins=0, sec=0;

    new days_of_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    new names_of_month[12][10] = {"Oca","Sub","Mar","Nis","May","Haz","Tem","Agu","Eyl","Eki","Kas","Ara"};
    new returnstring[32];

    while(timestamp>31622400){
        timestamp -= 31536000;
        if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) ) timestamp -= 86400;
        year++;
    }

    if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) )
        days_of_month[1] = 29;
    else
        days_of_month[1] = 28;


    while(timestamp>86400){
        timestamp -= 86400, day++;
        if (day==days_of_month[month]) day=0, month++;
    }

    while(timestamp>60){
        timestamp -= 60, mins++;
        if ( mins == 60) mins=0, hour++;
    }

    sec=timestamp;

    switch( _form ){
        case 1: format(returnstring, 31, "%02d/%02d/%d %02d:%02d", day+1, month+1, year, hour, mins);
        case 2: format(returnstring, 31, "%s %02d, %d, %02d:%02d:%02d", names_of_month[month],day+1,year, hour, mins, sec);
        case 3: format(returnstring, 31, "%d %c%c%c %d, %02d:%02d", day+1,names_of_month[month][0],names_of_month[month][1],names_of_month[month][2], year,hour,mins);

        default: format(returnstring, 31, "%02d.%02d.%d-%02d:%02d:%02d", day+1, month+1, year, hour, mins, sec);
    }

    return returnstring;
}

stock GetSkin(const fields[] = "game_skins.*", const joins[] = "", const wheres[] = "", page = 1, limit = -1, sqlid = -1, model_id = -1, gender = -1, race = -1)
{
    new query[1024];

    format(query, sizeof(query), "SELECT %s FROM game_skins", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(sqlid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_skins.id = '%d'", query, sqlid);
    }

    if(model_id != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_skins.model_id = '%d'", query, model_id);
    }

    if(gender != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_skins.gender = '%d'", query, gender);
    }

    if(race != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND game_skins.race = '%d'", query, race);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY game_skins.id DESC", query);

    if(limit == -1)
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 10000", query, ((page - 1) * ITEM_PER_PAGE));
    else
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 1", query, ((page - 1) * ITEM_PER_PAGE) + limit);

    return query;
}

this::LoadModels()
{
	new rows = cache_num_rows();
	if(cache_num_rows())
	{
		new ozelmodel;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_int(i, "id", ozelmodel);

			RefreshModel(ozelmodel);
		}

		printf("[!] Sunucudan %d model verisi alindi.", rows);
	}

	else printf("[!] Sunucudan model verisi alinamadi.");

	return 1;
}

stock GetModel(const fields[] = "ozel_modeller.*", const joins[] = "", const wheres[] = "", page = 1, limit = -1, sqlid = -1, type = -1, baseid = -1, newid = -1)
{
    new query[512];

    format(query, sizeof(query), "SELECT %s FROM ozel_modeller", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(sqlid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND ozel_modeller.id = '%d'", query, sqlid);
    }

    if(type != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND ozel_modeller.type = '%d'", query, type);
    }

    if(baseid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND ozel_modeller.baseid = '%d'", query, baseid);
    }

    if(newid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND ozel_modeller.newid = '%d'", query, newid);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY ozel_modeller.id DESC", query);

    if(limit == -1)
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 10000", query, ((page - 1) * ITEM_PER_PAGE));
    else
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 1", query, ((page - 1) * ITEM_PER_PAGE) + limit);

    return query;
}

stock RefreshModel(ozelmodel)
{
    mysql_tquery(dbHandle, GetModel("ozel_modeller.type, ozel_modeller.baseid, ozel_modeller.newid", "", "", 1, -1, ozelmodel), "OnModelRefreshed", "d", ozelmodel);
    return 1;
}

this::OnModelRefreshed(ozelmodel)
{
    if(cache_num_rows())
    {
		new type, baseid, newid;
		cache_get_value_int(0, "type", type);
		cache_get_value_int(0, "baseid", baseid);
		cache_get_value_int(0, "newid", newid);

        new dff[90], txd[90];

        format(dff, sizeof(dff), "ozel_model/%s.dff", valstrEx(newid));
        format(txd, sizeof(txd), "ozel_model/%s.txd", valstrEx(newid));

        switch(type)
        {
            case 1: AddCharModel(baseid, newid, dff, txd);
            case 2: AddSimpleModel(-1, baseid, newid, dff, txd);
        }
    }

    else printf("(OnModelRefreshed) %d numarali model icin calismadi.", ozelmodel);

    return 1;
}

stock GetPlayerDistanceToObject(playerid, objectid) // by blaze
{
	new Float:tmpdis;
    new Float:player_pos[3], Float:object_pos[3];
    GetPlayerPos(playerid, player_pos[0], player_pos[1], player_pos[2]);
    GetDynamicObjectPos(objectid, object_pos[0], object_pos[1], object_pos[2]);

	tmpdis = floatsqroot(floatpower(floatabs(floatsub(object_pos[0],player_pos[0])),2)+floatpower(floatabs(floatsub(object_pos[1],player_pos[1])),2)+floatpower(floatabs(floatsub(object_pos[2],player_pos[2])),2));
	return floatround(tmpdis);
}

forward YuruyusAnim(playerid);
public YuruyusAnim(playerid)
{
	new keys, updown, leftright;
	GetPlayerKeys(playerid, keys, updown, leftright);
	if(PlayerInfo[playerid][pWalk] == YURUYUS_NORMAL)
	{
		if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_player",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_PED)
	{
		if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_civi",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if (PlayerInfo[playerid][pWalk] == YURUYUS_GANGSTER)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_gang1",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_GANGSTER2)
	{
		if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_gang2",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_YASLI)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_old",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_SISKO_YASLI)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_fatold",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_SISKO)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_fat",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_fat",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_KADIN)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_KADIN2)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_FAHISE)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_FAHISE2)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_SARHOS)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_drunk",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_KOR)
	{
		if((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","Walk_Wuzi",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	else if(PlayerInfo[playerid][pWalk] == YURUYUS_ARMED)
	{
		if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
		{
			KillTimer(YuruyusTimer[playerid]);
			ApplyAnimation(playerid,"PED","WALK_armed",4.1,1,1,1,1,1);
			YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
		}
		else ApplyAnimation(playerid,"PED","WALK_armed",4.0,0,0,0,0,1), KillTimer(YuruyusTimer[playerid]);
	}
	return true;
}

stock AntiCheatGetHealth(playerid, &Float:health)
{
	if(!IsPlayerConnected(playerid)) return 0;
	health = PlayerInfo[playerid][pHealth];
	return 1;
}

stock ClearTextInventory(playerid)
{
	PlayerInfo[playerid][pCicek] = PlayerInfo[playerid][pKamera] = PlayerInfo[playerid][pBoombox] = PlayerInfo[playerid][pMaske] = PlayerInfo[playerid][pSigara] = 0;
	PlayerInfo[playerid][pKalem] = PlayerInfo[playerid][pTelsiz] = PlayerInfo[playerid][pBenzinBidonu] = PlayerInfo[playerid][pZar] = PlayerInfo[playerid][pCakmak] = 0;
    return 1;
}