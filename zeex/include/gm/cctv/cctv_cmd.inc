CMD:cctv(playerid, params[])
{
	new id;

	if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Polis memuru olmalýsýnýz.");

	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/cctv [goruntule / ayril / liste]");
		return 1;
	}

	if (CompareStrings(option, "goruntule"))
	{
		new factionid = PlayerInfo[playerid][pFaction];
		if (!IsPlayerInRangeOfPoint(playerid, 30.0, Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ])) {	
			return SendErrorMessage(playerid, "Bu özellik yalnýzca HQ'da mevcuttur.");
		}

		if (sscanf(secoption,"d", id))								return SendHelpMessage(playerid, "/cctv goruntule [ID]");
		if (id < 0 || id > MAX_CCTV-1 || !CCTVInfo[id][tvObjectOn])	return SendErrorMessage(playerid, "CCTV bulunamadý.");
		if (CCTVInfo[id][tvBreak])	{
			Waypoint_Set(playerid, CCTVInfo[id][tvPosX],CCTVInfo[id][tvPosY],CCTVInfo[id][tvPosZ], 3.0);
			return SendErrorMessage(playerid, "CCTV arýzalý.");
		}

    	if (!pTemp[playerid][pCCTV])
		{
			SavePlayerPos(playerid);
			pTemp[playerid][pCCTV] = 1;
            SetPVarInt(playerid, "CCTV:ID", id + 1);

			if (IsPlayerInAnyVehicle(playerid)) {
				SetPVarInt(playerid, #CCTV_VEH, GetPlayerVehicleID(playerid));
				SetPVarInt(playerid, #CCTV_VEH_SEAT, GetPlayerVehicleSeat(playerid));
				RemovePlayerFromVehicle(playerid);
			}
			
			SetInterior(playerid, CCTVInfo[id][tvInt]);
			SetWorld(playerid, CCTVInfo[id][tvVW]);
			for(new i; i < 12; i++) GetPlayerWeaponData(playerid, i, PlayerInfo[playerid][pScriptedGun][i], PlayerInfo[playerid][pScriptedAmmo][i]);

			if (MdcInfo[playerid][mdcCreated]) {
				MDC_Hide(playerid);
				SetPVarInt(playerid, #CCTV_MDC_USE, 1);
			}

			for(new i; i < 11;i++) TextDrawShowForPlayer(playerid, zond_cam[i]);

			SetTimerEx("CCTV_PLA_TIMER", 1000, false, "ii", playerid, id);
		}
	}

	else if (CompareStrings(option, "liste"))
	{
		new dialog_header[96] = "{FFFFFF}CCTV\t{FFFFFF}CCTV ID\t{FFFFFF}Durum\n", dialog_body[3072];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

		new count;
		for(new i = 0; i < MAX_CCTV; i++)
		{
			if (CCTVInfo[i][tvObjectOn])
			{
                new break_str[24];
				count++;

                if (CCTVInfo[i][tvBreak])    format(break_str, sizeof(break_str), "{CC0000}Deaktif");
                else                        format(break_str, sizeof(break_str), "{00B200}Aktif");

				format(dialog_body, sizeof(dialog_body), "%s%s\t%i\t%s\n", dialog_body, CCTVInfo[i][tvName], i, break_str);
			}
		}
		if (!count)	dialog_body = "CCTV yok.";
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}CCTV Listesi", dialog_body, "Kapat", "");
		return 1;
	}

	else if (CompareStrings(option, "ayril"))
	{
		if (!pTemp[playerid][pCCTV]) return SendErrorMessage(playerid, "CCTV izlemiyorsunuz.");

		TogglePlayerSpectating(playerid, 0);		

		SetInterior(playerid, PlayerInfo[playerid][pInt]);
		SetWorld(playerid, PlayerInfo[playerid][pWorld]);

		for(new i; i < 11; i++) TextDrawHideForPlayer(playerid, zond_cam[i]);

		for(new i; i < 12; i++) GivePlayerWeapon(playerid, PlayerInfo[playerid][pScriptedGun][i], PlayerInfo[playerid][pScriptedAmmo][i]);

		if (GetPVarInt(playerid, #CCTV_MDC_USE) && !MdcInfo[playerid][mdcCreated]) {
			MDC_Show(playerid, PAGE_CCTV);
			DeletePVar(playerid, #CCTV_MDC_USE);
		}

		if (GetPVarInt(playerid, #CCTV_VEH)) SetTimerEx("CCTV_VEH_TIMER", 1000, false, "i", playerid); 
	}

	else 
	{
		SendHelpMessage(playerid, "/cctv [ayarlar]");
		SendSyntaxMessage(playerid, "goster/ayril/liste");
	}
	return 1;
}

this::CCTV_VEH_TIMER(playerid) {
	PutPlayerInVeh(playerid, GetPVarInt(playerid, #CCTV_VEH), GetPVarInt(playerid, #CCTV_VEH_SEAT));
	DeletePVar(playerid, #CCTV_VEH);
	DeletePVar(playerid, #CCTV_VEH_SEAT);
	return 1;
}

this::CCTV_PLA_TIMER(playerid, id) {
	TogglePlayerSpectating(playerid, 1);
	AttachCameraToDynamicObject(playerid, CCTVInfo[id][tvObject]);
	SendHelpMessage(playerid, "CCTV'yi kontrol etmek için farenizi kullanabilirsiniz. CCTV modundan çýkmak için: {DABB3E}/cctv ayril");
	return 1;
}//î