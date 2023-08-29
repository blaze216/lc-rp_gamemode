CMD:taser(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	if (!pTemp[playerid][pTaser])
	{
		AC_RemovePlayerWeapon(playerid, PlayerInfo[playerid][pWeapons][2]);
		AC_GivePlayerWeapon(playerid, 23, 3);
		pTemp[playerid][pTaser] = 1;
		SetPlayerChatBubble(playerid, "teçhizat kemerinden taseri çýkartýr.", COLOR_PURPLE, 20.0, 4000);
		SM1(playerid, "Taseri çýkarttýnýz.");
	    return 1;
	}

	AC_RemovePlayerWeapon(playerid, 23);
	if(OlusumTipGetir(PlayerInfo[playerid][pFaction] != FACTION_CITY))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) AC_GivePlayerWeapon(playerid, 24, 100);
		else AC_GivePlayerWeapon(playerid, 22, 100); // pistol
	}

    pTemp[playerid][pTaser] = 0;
	SetPlayerChatBubble(playerid, "taseri teçhizat kemerine takar.", COLOR_PURPLE, 20.0, 4000);
	SM1(playerid, "Taseri geri koydunuz.");
	return 1;
}

CMD:beanbag(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (pTemp[playerid][pLTL])                                  return pc_cmd_ltl(playerid, "");

	if (!pTemp[playerid][pBeanbag])
	{
		AC_GivePlayerWeapon(playerid, 25, 50);
		pTemp[playerid][pBeanbag] = 1;
		SetPlayerChatBubble(playerid, "beanbag tüfeðini çýkarýr.", COLOR_PURPLE, 20.0, 4000);
		SM1(playerid, "Beanbag çýkardýnýz.");
	    return 1;
	}
	
	AC_RemovePlayerWeapon(playerid, 25);
    pTemp[playerid][pBeanbag] = 0;
	SetPlayerChatBubble(playerid, "beanbag tüfeðini sýrtýna asar.", COLOR_PURPLE, 20.0, 4000);
	SM1(playerid, "Beanbagi geri koydunuz.");
	return 1;
}

CMD:ltl(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (pTemp[playerid][pBeanbag])                              return pc_cmd_beanbag(playerid, "");	

	if (!pTemp[playerid][pLTL])
	{
		AC_GivePlayerWeapon(playerid, 33, 10);
		pTemp[playerid][pLTL] = 1;
		SetPlayerChatBubble(playerid, "LTL tüfeðini çýkarýr.", COLOR_PURPLE, 20.0, 4000);
		SM1(playerid, "LTL çýkardýnýz.");
	    return 1;
	}

	SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

	AC_RemovePlayerWeapon(playerid, 33); 
    pTemp[playerid][pLTL] = 0;
	SM1(playerid, "LTL'i geri koydunuz.");
	return 1;
}

alias:bagajdanal("pdsilah", "pdbagaj");
CMD:bagajdanal(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	new cid = Arac_Yakin(playerid, 4.0);
	if(cid == -1) return SendServerMessage(playerid, "Aracýn içinde veya yakýnýnda deðilsin.");
	if(PlayerInfo[playerid][pFaction] != VehicleInfo[cid][carFaction] && PlayerInfo[playerid][pOnDuty]) return SendClientMessageEx(playerid, COLOUR_TOMATO, "Araç: {FFFFFF}Bu aracýn bulunduðu oluþumda veya iþbaþýnda deðilsin.");
	new slot, string[128];
	if(!PlayerInfo[playerid][pOnDuty]) return SendClientMessageEx(playerid, COLOUR_TOMATO, "Araç: {FFFFFF}Bunu yapabilmek için iþ baþýnda olmalýsýn.");
//  if(VehicleInfo[cid][vOwner] != -1) return SendErrorMessage(playerid, "Sahibi olan araçlarda bunu yapamazsýn.");
	if(VehicleInfo[cid][carFaction] == -1 || (OlusumTipGetir(VehicleInfo[cid][carFaction]) != FACTION_POLICE && OlusumTipGetir(VehicleInfo[cid][carFaction]) != FACTION_CITY)) return SendClientMessageEx(playerid, COLOUR_TOMATO, "Araç: {FFFFFF}Oluþumlara atanmasý yapýlmamýþ araçlarda bu komut kullanýlamaz.");
	if(PlayerInfo[playerid][pFaction] != VehicleInfo[cid][carFaction]) return SendClientMessageEx(playerid, COLOUR_TOMATO, "Araç: {FFFFFF}Bulunduðun oluþum, aracýn ait olduðu oluþumla ayný deðil.");
	if(sscanf(params, "d", slot)) {
		static const allowedStatus[][10] = {"Evet", "Hayýr"};
		for(new j; j < MAX_CAR_WEAPONS; j++) if(OlusumTipGetir(VehicleInfo[cid][carFaction]) == CarFactionWeaponsInfo[j][weaponFaction] && VehicleInfo[cid][carSlotUsed][j] != 2)
			SendClientMessageEx(playerid, COLOR_GREY, "Slot %d: %s (Mermi: %d - Rezerve: %s)", j + 1, GetWeaponNameEx(CarFactionWeaponsInfo[j][weaponID]), CarFactionWeaponsInfo[j][weaponAmmo], allowedStatus[CarFactionWeaponsInfo[j][weaponAllowed]]);
		return SendSyntaxMessage(playerid, "/pdbagaj [slot]");
	}
	slot--;
	if(slot < 0 || slot >= MAX_CAR_WEAPONS || VehicleInfo[cid][carSlotUsed][slot] == 2) return SendErrorMessage(playerid, "Geçersiz veya boþ slot. (1 - %d)", MAX_CAR_WEAPONS);
	if(CarFactionWeaponsInfo[slot][weaponFaction] == FACTION_POLICE && !CarFactionWeaponsInfo[slot][weaponAllowed] && !PlayerInfo[playerid][pOlusumDivision][1]) return SendErrorMessage(playerid, "Bunu kullanabilecek birimde deðilsin.");
	if(OlusumTipGetir(VehicleInfo[cid][carFaction]) != CarFactionWeaponsInfo[slot][weaponFaction]) return SendErrorMessage(playerid, "Bu silahý kullanamazsýn.");
	// if(!PlayerInfo[playerid][pOlusumDivision][1] && CarFactionWeaponsInfo[slot][weaponID] == 31 && PlayerInfo[playerid][pm4UPR] == 0) return SendErrorMessage(playerid, "M4 UPR'ýn yok.");
	// if(!PlayerInfo[playerid][pOlusumDivision][1] && CarFactionWeaponsInfo[slot][weaponID] == 29 && PlayerInfo[playerid][pmp5UPR] == 0) return SendErrorMessage(playerid, "MP5 UPR'ýn yok.");
	if(CarFactionWeaponsInfo[slot][weaponID] == 25 && pTemp[playerid][pBeanbag]) pc_cmd_beanbag(playerid, "");
	if(CarFactionWeaponsInfo[slot][weaponID] == 23 && pTemp[playerid][pTaser]) pc_cmd_taser(playerid, "");
	if(CarFactionWeaponsInfo[slot][weaponID] == 24 && GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Araç içerisindeyken bagajdan Desert Eagle alamazsýn.");
	AC_GivePlayerWeapon(playerid, CarFactionWeaponsInfo[slot][weaponID], CarFactionWeaponsInfo[slot][weaponAmmo]);
	VehicleInfo[cid][carSlotUsed][slot]++;
	SendClientMessageEx(playerid, COLOR_GREY, "%s (%d mermi) silahýný aracýnýn içerisinden aldýn. /asilahbirak ile býrakabilirsin.", GetWeaponNameEx(CarFactionWeaponsInfo[slot][weaponID]), CarFactionWeaponsInfo[slot][weaponAmmo]);
	format(string, sizeof(string), "%s adlý silahý aracýn içerisinden çýkartýr.", GetWeaponNameEx(CarFactionWeaponsInfo[slot][weaponID]));
	PlayerAME2(playerid, string);
	return 1;
}

alias:asilahbirak("bagajakoy","bagajkoy");
CMD:asilahbirak(playerid, params[])
{
	new cid = Arac_Yakin(playerid, 4.0);
	if(cid == -1) return SendServerMessage(playerid, "Aracýn içinde veya yakýnýnda deðilsin.");
	new weaponid = AC_GetPlayerWeapon(playerid);
	new string[90];

	if(!PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Bunu yapabilmek için iþ baþýnda olmalýsýn.");
	//if(VehicleInfo[cid][vOwner] != -1) return SendErrorMessage(playerid, "Sahibi olan araçlarda bunu yapamazsýn.");
	if(PlayerInfo[playerid][pFaction] != VehicleInfo[cid][carFaction]) return SendErrorMessage(playerid, "Araç ile ayný oluþumda deðilsin.");
	if(VehicleInfo[cid][carFaction] == -1 || (OlusumTipGetir(VehicleInfo[cid][carFaction]) != FACTION_POLICE && OlusumTipGetir(VehicleInfo[cid][carFaction]) != FACTION_CITY)) return SendErrorMessage(playerid, "Bu komutu bu araçta kullanamazsýn.");
	new bool:depositGun = false;
	for(new j; j < MAX_CAR_WEAPONS; j++) if(CarFactionWeaponsInfo[j][weaponID] == weaponid || weaponid == WEAPON_SHOTGUN && !pTemp[playerid][pBeanbag]) {
		VehicleInfo[cid][carSlotUsed][j]--;
		if(VehicleInfo[cid][carSlotUsed][j] < 0) VehicleInfo[cid][carSlotUsed][j] = 0;
		depositGun = true; break;
	}
	if(!depositGun) return SendServerMessage(playerid, "Bu silahý oluþum aracýnýn bagajýna koyamazsýn.");
	AC_RemovePlayerWeapon(playerid, weaponid);
	SendClientMessageEx(playerid, COLOR_YELLOW, "%s silahýný aracýn bagajýna yerleþtirdin.", GetWeaponNameEx(weaponid));
	format(string, sizeof(string), "%s silahýný bagaja koyar.", GetWeaponNameEx(weaponid));
	pc_cmd_server_ame(playerid, string);
	SetPlayerArmedWeapon(playerid, 0);
	return 1;
}

CMD:tackle(playerid)
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if(IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araçta bu komutu kullanamazsýnýz.");

	pTemp[playerid][pTackleMode] = !pTemp[playerid][pTackleMode];
	SendClientMessageEx(playerid, COLOR_WHITE, (pTemp[playerid][pTackleMode]) ? ("Tackle modu {00ff00}AKTÝFLEÞTÝRÝLDÝ{ffffff}.") : ("Tackle modu {FF6347}KAPATILDI{ffffff}."));
	return 1;
}

CMD:takip(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))		return SendErrorMessage(playerid, "Bu komutu kullanabilmek için polis olmalýsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	new vehicle = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid))				return SendNotInVehicle(playerid);
	if (VehicleInfo[vehicle][carFaction] != faction)	return SendErrorMessage(playerid, "Polis aracýnda deðilsiniz.");

	new trace, targetid;

	if (sscanf(params,"d", trace))									return SendHelpMessage(playerid, "/takip [telefon numarasý]");
	if (pTemp[playerid][pTracePlayer] != INVALID_PLAYER_ID)			return SendErrorMessage(playerid, "Önce oturumu kapatýn. (/takipbirak)");
	//if (trace == PlayerInfo[playerid][pNumber])						return 1;
    if ((targetid = GetNumberOwner(trace)) == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Belirtilen numara veritabanýnda bulunamadý.");
    if (PlayerInfo[targetid][pJailed] != 0)							return SendErrorMessage(playerid, "Bu numaranýn sahibi gözaltýnda.");
	if (PlayerInfo[targetid][pBurnerTelefon] != 0)                  return SendErrorMessage(playerid, "Bu numara takip edilemez. (burner telefon)");

	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s telefon numarasýný takip ediyor: %i. **", GetRankName(playerid), GetNameEx(playerid), trace);

	Dialog_Show(playerid, ShowTrace, DIALOG_STYLE_MSGBOX, "Takip Sistemi", "{B4B5B7}Ýzleme baþlatýldý...", "Kapat", "");

	pTemp[playerid][pTracePlayer] = targetid;
	pTemp[playerid][pTraceStage] = 0;

	new Float:x, Float:y, Float:z;
	
	if (GetWorld(targetid) || GetInterior(targetid))
	{
		x = PlayerInfo[targetid][pLocationPos][0];
		y = PlayerInfo[targetid][pLocationPos][1];
		z = PlayerInfo[targetid][pLocationPos][2];
	}
	else GetPlayerPos(targetid, x, y, z);

	pTemp[playerid][pTraceDist][0] = GetDistanceBetweenPoints(x, y, z, 1459.3712, -783.0401, 93.6459);
	pTemp[playerid][pTraceDist][1] = GetDistanceBetweenPoints(x, y, z, 2667.2908, -1957.5245, 13.5469);
	pTemp[playerid][pTraceDist][2] = GetDistanceBetweenPoints(x, y, z, 923.6055, -1893.5146, 1.5319);
	return 1;
}

CMD:takipbirak(playerid, params[])
{
	if (pTemp[playerid][pTracePlayer] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Takip sisteminde deðilsiniz.");

	if (pTemp[playerid][pTraceGZ] != -1) GangZoneDestroy(pTemp[playerid][pTraceGZ]);
    
	pTemp[playerid][pTraceGZ] = -1;
    pTemp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
    pTemp[playerid][pTraceStage] = 0;
    SendSyntaxMessage(playerid, "Takip sisteminden çýkýþ yaptýnýz.");
	return 1;
}

alias:ceza("cezakes", "faturakes");
CMD:ceza(playerid, params[])
{
	new amount, reason[64], userid, faction = PlayerInfo[playerid][pFaction];

	if (sscanf(params,"uds[64]", userid, amount, reason))		return SendHelpMessage(playerid, "/ceza [ID/Ýsim] [ceza tutarý ($1-$50.000)] [sebep]");
	if (!IsPlayerLogged(userid))								return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (!IsFactionPolice(faction))								return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (strlen(reason) < 1 || strlen(reason) > 63)				return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
	if (amount < 1 || amount > 50000)							return SendErrorMessage(playerid, "Ceza tutarý minimum $1, maksimum $50000 dolar olmalýdýr.");
	if (!GivePlayerTicket(playerid, userid, amount, reason))	return SendErrorMessage(playerid,"Oyuncunun maksimum sayýda cezasý vardýr.");

	new mes[128];
	format(mes, sizeof(mes), "%s adlý kiþiye $%s tutarýnda ceza kesti. Sebep: \"%s\".", GetNameWithMask(userid), FormatNumber(amount), reason);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

	SM1(playerid, "%s adlý kiþiye \"%s\" sebebiyle $%s ceza kesildi.", GetNameWithMask(userid), reason, FormatNumber(amount));
	SendSpecialMessage(userid, "%s %s adlý kiþi $%s tutarýnda ceza kesti. Sebep: \"%s\".", GetRankName(playerid), GetNameWithMask(playerid), FormatNumber(amount), reason);
	SendHelpMessage(userid, "Cezalarýn listesini görüntülemek için: \"/cezalar\".");

	pTemp[playerid][pPoliceFines]++;
	return 1;
}

alias:araccezakes("aracacezakes");
CMD:araccezakes(playerid, params[])
{
	new amount, vehicle, vehiclenum[12], reason[64], faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))									return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (sscanf(params,"s[12]is[64]", vehiclenum, amount, reason))	return SendHelpMessage(playerid, "/aracceza [plaka (/plakakontrol)] [ceza tutarý ($1-$50.000)] [sebep]");
	if ((vehicle = FindVehicleByPlate(vehiclenum)) == -1)			return SendErrorMessage(playerid, "Araç bulunamadý. ");
	if (!PlayerInfo[playerid][pOnDuty])								return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz."); 
	if (GetNearVehicle(playerid, 10.0, vehicle) == 0)				return SendErrorMessage(playerid, "Araca yakýn durmalýsýnýz. ");
	if (VehicleInfo[vehicle][carRegistered] != 1)					return SendErrorMessage(playerid, "Bu araç kayýtlý deðil.");
	if (strlen(reason) < 1 || strlen(reason) > 63)					return SendErrorMessage(playerid, "Sebep maksimum 63 karakter olmalýdýr.");
	if (amount < 1 || amount > 50000)								return SendErrorMessage(playerid, "Ceza tutarý minimum $1, maksimum $50000 dolar olmalýdýr.");
	if (!GiveVehicleTicket(playerid, vehicle, amount, reason))		return SendErrorMessage(playerid, "Bu araç maksimum ceza sayýsýna sahiptir.");
	
	new mes[128];
	format(mes, sizeof(mes), "%s model araca $%s tutarýnda ceza kesti.", VehicleNames[GetVehicleModel(vehicle)-400], FormatNumber(amount));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

    new userid = GetVehicleOwner(vehicle);

    if (userid != INVALID_PLAYER_ID)
    {
	    SendSpecialMessage(userid, "%s %s, %s model aracýnýza $%s tutarýnda ceza kesti. Sebep: \"%s\".", GetRankName(playerid), GetNameEx(playerid), VehicleNames[GetVehicleModel(vehicle)-400], FormatNumber(amount), reason);
		SendHelpMessage(userid, "Bir araçtaki cezalarýn listesini görüntülemek için /araccezakontrol komutunu kullanýn.");
	}

	SM1(playerid, "%s model araca $%s tutarýnda ceza kestiniz. Sebep: %s.", VehicleNames[GetVehicleModel(vehicle)-400], FormatNumber(amount), reason);
	
	pTemp[playerid][pPoliceFines]++;
	return 1;
}

CMD:cezakontrol(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
		
    new userid;

	if (sscanf(params,"u",userid))						return SendHelpMessage(playerid, "/cezakontrol [ID/Ýsim]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);

	new query[255];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i AND `paid`=0 LIMIT %i", PlayerInfo[userid][pID], MAX_TICKETS);
	mysql_tquery(dbHandle, query, "ShowPlayersTickets", "ii", playerid, 0);

	SetPVarInt(playerid, #tickets_show, userid);
	SetPVarInt(playerid, #ticketsuse, 1);
	return 1;
}

alias:araccezakontrol("ack");
CMD:araccezakontrol(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanabilmek için Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	new vehicle;

    if (isnull(params))								  return SendHelpMessage(playerid, "/araccezakontrol - /ack [plaka (/plakakontrol)]");
	if (strlen(params) > 12)						  return SendErrorMessage(playerid, "Belirtilen plaka geçersiz.");
    if ((vehicle = FindVehicleByPlate(params)) == -1) return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

	new query[255];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `paid`=0 LIMIT %i", VehicleInfo[vehicle][carID], MAX_TICKETS);
	mysql_tquery(dbHandle, query, "ShowCarsTickets", "i", playerid);

	SetPVarInt(playerid, #tickets_show, vehicle);
	SetPVarInt(playerid, #ticketsuse, 1);
	return 1;
}

alias:kapikir("kapiyikir");
CMD:kapikir(playerid,params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	new building;
	switch(GetNearBuilding(playerid)) {
		case 0: {
			building = GetNearInsideHouse(playerid);
			if(building == -1)	return 1;

			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!IsPlayerInRangeOfPoint(playerid, 1.5, HFurn[building][i][fPosX], HFurn[building][i][fPosY], HFurn[building][i][fPosZ]) || !HFurn[building][i][fOn] || !isHouseDoor(HFurn[building][i][fModel]))
				{
					continue;
				}
				if (HFurn[building][i][fOpened])	return SendWarningMessage(playerid, "Kapý zaten açýk!");

				pc_cmd_server_ame(playerid,"kapýyý tekmeler.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);
				
				SetTimerEx("DoorRamEnd", 1000, false, "iiii", 0, building, i, playerid);
				break;
			}
		}
		case 1: {
			building = GetNearInsideBiz(playerid);
			if(building == -1)	return 1;
			
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!IsPlayerInRangeOfPoint(playerid, 1.5, BFurn[building][i][fPosX], BFurn[building][i][fPosY], BFurn[building][i][fPosZ]) || !BFurn[building][i][fOn] || !isHouseDoor(BFurn[building][i][fModel]))
				{
					continue;
				}
				if (BFurn[building][i][fOpened])	return SendWarningMessage(playerid, "Kapý zaten açýk!");

				pc_cmd_server_ame(playerid, "kapýyý tekmeler.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);

				SetTimerEx("DoorRamEnd", 1000, false, "iiii", 1, building, i, playerid);
				break;
			}
		}
		case 2: {
			building = GetNearInsideGarage(playerid);
			if(building == -1)	return 1;
			
			for(new i = 0; i < MAX_FURNITURE; i++)
			{
				if (!IsPlayerInRangeOfPoint(playerid, 1.5, GFurn[building][i][fPosX], GFurn[building][i][fPosY], GFurn[building][i][fPosZ]) || !GFurn[building][i][fOn] || !isHouseDoor(GFurn[building][i][fModel]))
				{
					continue;
				}
				if (GFurn[building][i][fOpened])	return SendWarningMessage(playerid, "Kapý zaten açýk!");

				pc_cmd_server_ame(playerid, "kapýyý tekmeler.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);

				SetTimerEx("DoorRamEnd", 1000, false, "iiii", 2, building, i, playerid);
				break;
			}
		}
	}	    
	return 1;
}

this::DoorRamEnd(type, building, i, playerid)
{
	switch(type)
	{
		case 0: {
			HFurn[building][i][fLocked] = 0;
			HFurn[building][i][fOpened] = 1;
				
			MoveDynamicObject(HFurn[building][i][fObject], HFurn[building][i][fPosX], HFurn[building][i][fPosY], HFurn[building][i][fPosZ], 1.5, HFurn[building][i][fPosRX], HFurn[building][i][fPosRY], HFurn[building][i][fPosRZ]-90.0);
				
		}
		case 1: {
			BFurn[building][i][fLocked] = 0;
			BFurn[building][i][fOpened] = 1;
				
			MoveDynamicObject(BFurn[building][i][fObject], BFurn[building][i][fPosX], BFurn[building][i][fPosY], BFurn[building][i][fPosZ], 1.5, BFurn[building][i][fPosRX], BFurn[building][i][fPosRY], BFurn[building][i][fPosRZ]-90.0);
		}
		case 2: {
			GFurn[building][i][fLocked] = 0;
			GFurn[building][i][fOpened] = 1;
				
			MoveDynamicObject(GFurn[building][i][fObject], GFurn[building][i][fPosX], GFurn[building][i][fPosY], GFurn[building][i][fPosZ], 1.5, GFurn[building][i][fPosRX], GFurn[building][i][fPosRY], GFurn[building][i][fPosRZ]-90.0);
		}
	}

	ClearAnimations(playerid);
	GameTextForPlayer(playerid, "~w~KAPIYI ~y~CALDIN", 1000, 1);
	return 1;
}

CMD:kilitkir(playerid,params[])
{
	if (!IsPlayerFactionPolice(playerid)) return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])	  return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
		    
	new slot;
	
	if (sscanf(params,"d", slot))
	{
		SendHelpMessage(playerid, "/kilitkir [ayar]");
		SendSyntaxMessage(playerid, "1 - Kilit Kýr | 2 - Kapýyý Kýr | 3 - C4 döþe | 4 - Aracýn kapýsýný kýr");
	}

	if (slot < 1 || slot > 4)						 return 1;
    if (slot < 4 && PlayerInfo[playerid][pRank] < 4) return SendErrorMessage(playerid, "Bu iþlemi yapabilmek için rütbeniz minimum 4 olmalýdýr.");
	if (pTemp[playerid][pRamType])					 return SendErrorMessage(playerid, "Zaten kapýyý kýrýyorsunuz");

    new location[MAX_ZONE_NAME];
	GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

	if (slot == 4) {
		new vehicle = GetNearVehicle(playerid, 2.0);
		if (!vehicle)							  return SendErrorMessage(playerid, "Yakýnda araç bulunmuyor.");

		if (VehicleInfo[vehicle][carLocked] == 0)  return SendErrorMessage(playerid, "Araç kilidi açýk.");
		if (VehicleInfo[vehicle][carOwnerID] == INVALID_PLAYER_ID) return SendErrorMessage(playerid, "Araç devlete aittir.");
		
		pc_cmd_server_ame(playerid, "kapý kilidini kýrar.");
		ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);

		pTemp[playerid][pRamType] = 1;
		pTemp[playerid][pRamTime] = 30;
		pTemp[playerid][pRamHouse] = -1;
		pTemp[playerid][pRamBiz] = -1;
		pTemp[playerid][pRamGarage] = -1;
		pTemp[playerid][pRamVeh] = vehicle;
		return 1;
	}

	new id = -1;
	if ((id = GetNearOutsideHouse(playerid)) != -1)
	{
	    if (!HouseInfo[id][hOwnerID])									return SendErrorMessage(playerid, "Ev devlete aittir.");
		if (!HouseInfo[id][hLocked] || HouseInfo[id][hDDoor])			return SendErrorMessage(playerid,"Kapý zaten açýk.");

		switch(slot)
		{
		    case 1:
		    {
				pc_cmd_server_ame(playerid, "kapý kilidini kýrar.");
				ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);

				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 30;
				pTemp[playerid][pRamHouse] = id;
				pTemp[playerid][pRamBiz] = -1;
				pTemp[playerid][pRamGarage] = -1;
				pTemp[playerid][pRamVeh] = -1;
			}
			case 2:
			{
			    pc_cmd_server_ame(playerid, "kapýya ayaðýyla vurur.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
				HouseInfo[id][hLocked] = 0;
				HouseInfo[id][hDDoor] = 1;
				Save_House(id);
				UpdateHouseDoor(id);
				GameTextForPlayer(playerid, "~w~KAPIYI ~y~KIRDINIZ", 1000, 1);
				InfoMSG(playerid, "GIRIS YAPMAK ICIN ~y~\"F\"~w~ TUSUNA BAS VEYA ~y~/GIRIS ~w~KOMUTUNU KULLAN", 2);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] evin kapýsýný çaldý (/ram) [H_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), HouseInfo[id][hID]);
			    insert_log(query, RAM_LOG, 5, PlayerInfo[playerid][pAccID], 0);
			}
			case 3:
			{
			    pc_cmd_server_ame(playerid, "kapýya C4 yerleþtirir.");
				OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                pTemp[playerid][pRamObj] = CreateDynamicObject(1654, HouseInfo[id][hPosX], HouseInfo[id][hPosY], HouseInfo[id][hPosZ]-0.8, 0.0, 0.0, 90.0, HouseInfo[id][hPosInt], HouseInfo[id][hPosVW]);
				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 10;
				pTemp[playerid][pRamHouse] = id;
				pTemp[playerid][pRamBiz] = -1;
				pTemp[playerid][pRamGarage] = -1;
				pTemp[playerid][pRamVeh] = -1;
			}
		}
		return 1;
	}
	
	else if ((id = GetNearOutsideBiz(playerid)) != -1)
	{
	    if (BizInfo[id][bizType] == BIZ_GAS_STATION || BizInfo[id][bizType] == BIZ_AUTOSALON || BizInfo[id][bizType] == BIZ_BOATSALON || BizInfo[id][bizType] == BIZ_FLYSALON || BizInfo[id][bizType] == BIZ_TUNING || BizInfo[id][bizType] == BIZ_ADVERT || BizInfo[id][bizType] == BIZ_LICENSE) return 1;
        if (!BizInfo[id][bizOwnerID])							return SendErrorMessage(playerid, "Ýþletme devlete aittir.");
		if (!BizInfo[id][bizLocked] || BizInfo[id][bizDDoor])	return SendErrorMessage(playerid, "Kapý zaten açýk!");

		switch(slot)
		{
		    case 1:
		    {
				pc_cmd_server_ame(playerid, "kapý kilidini kýrar.");
				ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);
				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 30;
				pTemp[playerid][pRamHouse] = -1;
				pTemp[playerid][pRamBiz] = id;
				pTemp[playerid][pRamGarage] = -1;
				pTemp[playerid][pRamVeh] = -1;
			}
			case 2:
			{
			    pc_cmd_server_ame(playerid, "kapýya ayaðýyla vurur.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
				BizInfo[id][bizLocked] = 0;
				BizInfo[id][bizDDoor] = 1;
				Save_Business(id);
				UpdateBusinessDoor(id);
				GameTextForPlayer(playerid, "~w~KAPIYI ~y~KIRDINIZ", 1000, 1);
				InfoMSG(playerid, "GIRIS YAPMAK ICIN ~y~\"F\"~w~ TUSUNA BAS VEYA ~y~/GIRIS ~w~KOMUTUNU KULLAN", 2);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] iþletmenin kapýsýný çaldý (/ram) [B_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), BizInfo[id][bizID]);
			    insert_log(query, RAM_LOG, 6, PlayerInfo[playerid][pAccID], 0);
			}
			case 3:
			{
			    pc_cmd_server_ame(playerid, "kapýya C4 yerleþtirir.");
				OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                pTemp[playerid][pRamObj] = CreateDynamicObject(1654, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]-0.8, 0.0, 0.0, 90.0, BizInfo[id][bizPosVW], BizInfo[id][bizPosInt]);
				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 10;
				pTemp[playerid][pRamHouse] = -1;
				pTemp[playerid][pRamBiz] = id;
				pTemp[playerid][pRamGarage] = -1;
				pTemp[playerid][pRamVeh] = -1;
			}
		}
		return 1;
	}

	else if ((id = GetNearOutsideGarage(playerid)) != -1)
	{
        if (!GarageInfo[id][garageOwner])									return SendErrorMessage(playerid, "Garaj devlete ait.");
		if (!GarageInfo[id][garageLocked] || GarageInfo[id][garageDDoor])	return SendErrorMessage(playerid, "Kapý zaten açýk.");

		switch(slot)
		{
		    case 1:
		    {
				pc_cmd_server_ame(playerid, "kapý kilidini kýrar.");
				ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);
				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 30;
				pTemp[playerid][pRamHouse] = -1;
				pTemp[playerid][pRamBiz] = -1;
				pTemp[playerid][pRamGarage] = id;
				pTemp[playerid][pRamVeh] = -1;
			}
			case 2:
			{
			    pc_cmd_server_ame(playerid, "kapýya ayaðýyla vurur.");
				ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
				GarageInfo[id][garageLocked] = 0;
				GarageInfo[id][garageDDoor] = 1;
				Save_Garage(id);
				UpdateGarageDoor(id);
				GameTextForPlayer(playerid, "~w~KAPIYI ~y~KIRDINIZ", 1000, 1);
				InfoMSG(playerid, "GIRIS YAPMAK ICIN ~y~\"F\"~w~ TUSUNA BAS VEYA ~y~/GIRIS ~w~KOMUTUNU KULLAN", 2);

				new query[256];
				format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] garajýn kapýsýný çaldý (/ram) [B_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), GarageInfo[id][garageID]);
			    insert_log(query, RAM_LOG, 6, PlayerInfo[playerid][pAccID], 0);
			}
			case 3:
			{
			    pc_cmd_server_ame(playerid, "kapýya C4 yerleþtirir.");
				OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                pTemp[playerid][pRamObj] = CreateDynamicObject(1654, GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2]-0.8, 0.0, 0.0, 90.0, GarageInfo[id][garageEnterVW], GarageInfo[id][garageEnterInt]);
				pTemp[playerid][pRamType] = slot;
				pTemp[playerid][pRamTime] = 10;
				pTemp[playerid][pRamHouse] = -1;
				pTemp[playerid][pRamBiz] = id;
				pTemp[playerid][pRamGarage] = id;
				pTemp[playerid][pRamVeh] = -1;
			}
		}		
		return 1;
	}
	else if (slot == 2) pc_cmd_kapikir(playerid, "");
	
	return 1;
}

CMD:bagajara(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid))	return 1;
	if (!PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	new vehicle = GetNearVehicle(playerid, 4.0);
	if (vehicle == 0)																															return SendErrorMessage(playerid, "Yakýnýnýzda araç bulunmuyor.");
	if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))	return SendErrorMessage(playerid, "Bu aracýn bagajý yok.");
    if (!IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carTrunkLock] == 0)																return SendErrorMessage(playerid, "Bu aracýn bagajý kapalý.");
	if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction]) 								return SendErrorMessage(playerid, "Bu aracý arayamazsýnýz.");
	
	if (!IsNearTrunk(vehicle, playerid, 2.0)) 	return SendErrorMessage(playerid, "Bagajýn yakýnýnda deðilsiniz! ");

	PrintVehInv(playerid, vehicle, 1);
	return 1;
}

CMD:torpidoara(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid)) return 1;
	if (!PlayerInfo[playerid][pOnDuty])	 return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	
	new vehicle = GetPlayerVehicleID(playerid);
	if (!vehicle && !IsPlayerInAnyVehicle(playerid))																									 return SendErrorMessage(playerid,"Araçta olmalýsýnýz.");
	if (VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction] && VehicleInfo[vehicle][carOwnerID] > 0 && VehicleInfo[vehicle][carOwnerID] != INVALID_PLAYER_ID) return SendErrorMessage(playerid, "Bu aracý arayamazsýnýz.");

	PrintGBInv(playerid, vehicle, 1);
	return 1;
}

CMD:mulkara(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid)) return 1;
	if (!PlayerInfo[playerid][pOnDuty])	 return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

	new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yakýn deðilsin.");
	if (HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait.");
	if (!IsPlayerInsideHouse(playerid, houseid))					return SendErrorMessage(playerid, "Evin içinde olmalýsýn.");

	PrintHouseInv(playerid, houseid, 1);
	return 1;
}

CMD:ustara(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	new userid;

	if (sscanf(params,"u", userid))										 return SendHelpMessage(playerid, "/ustara [ID/Ýsim]");
	if (!IsPlayerLogged(userid))										 return SendNotConnected(playerid);
	if (userid == playerid)												 return 1;
	if (!PlayerNearPlayer(3.0, playerid, userid))						 return SendNotNearPlayer(playerid);
	if (pTemp[userid][pFriskPlayer] == playerid)						 return SendErrorMessage(playerid, "Oyuncuyu aramayý zaten teklif ettiniz.");
	if (IsPlayerFactionPolice(playerid) && PlayerInfo[playerid][pOnDuty]) return PrintInvEx(userid, playerid), SilahKontrolEt(playerid, userid, 1);

    SendServerMessage(playerid,"Üst aramasý teklifi gönderdiniz.");
	SendServerMessage(userid, "%s adlý kiþi üstünüzü aramak istiyor.",GetNameEx(playerid));
	SendHelpMessage(userid, "Üst aramasýný onaylamak için: {ffc46a}/ustarakabul{FFFFFF}, reddetmek için: {ffc46a}/ustarared");
	
	pTemp[userid][pFriskPlayer] = playerid;
    SetPVarInt(userid, #accept_time, gettime() + 30);
	return 1;
}

CMD:ustarakabul(playerid, params[])
{
	if (pTemp[playerid][pFriskPlayer] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Üst arama teklifi bulunmuyor.");

	new userid = pTemp[playerid][pFriskPlayer];

	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);

	SendSyntaxMessage(playerid, "%s adlý kiþinin üstünüzü aramasýna izin verdiniz.",GetNameEx(userid));

	PrintInvEx(playerid, userid);
	pTemp[playerid][pFriskPlayer] = INVALID_PLAYER_ID;
	return 1;
}

CMD:ustarared(playerid, params[])
{
	if (pTemp[playerid][pFriskPlayer] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Üst arama teklifi bulunmuyor.");

	new userid = pTemp[playerid][pFriskPlayer];
	
	pTemp[playerid][pFriskPlayer] = INVALID_PLAYER_ID;
	SendSyntaxMessage(playerid, "%s adlý kiþinin üstünüzü aramasýna izin vermediniz.",GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s adlý kiþi üstünün aranmasýna izin vermedi.",GetNameWithMask(playerid));
	return 1;
}

CMD:plakabelirle(playerid, params[])
{
	if (!IsFactionCity(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanmak için yetkiniz yok.");

    new vehicleid = GetPlayerVehicleID(playerid);

    if (!vehicleid || VehicleInfo[vehicleid][carFaction] != PlayerInfo[playerid][pFaction])	
		return SendErrorMessage(playerid, "Birlik aracýnda deðilsiniz.");

    new plate[24];

    format(plate, sizeof(plate), "%s", GetVehicleNumber());

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `plate` FROM `cars` WHERE `plate` = '%e'", plate);
	mysql_tquery(dbHandle, query, "PoliceSetPlate", "iis", playerid, vehicleid, plate);
	return 1;
}

CMD:snakecam(playerid, params[])
{
	if (pTemp[playerid][pZond] != 0)		return SetPlayerZond(playerid, 0);
    if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid,"Bir polis memuru / hapishane memuru olmalýsýnýz.");
    if (!PlayerInfo[playerid][pSwatDuty])	return SendErrorMessage(playerid, "Bu komut SWAT tarafýndan kullanýlabilir.");
	
	new weapons[12];
	new ammo[12];

	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	{
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
	}

	SetPlayerZond(playerid, 1);
	return 1;
}

CMD:flashbang(playerid, params[])
{
    if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
    if (!PlayerInfo[playerid][pSwatDuty])	return SendErrorMessage(playerid, "Bu komut SWAT tarafýndan kullanýlabilir.");

    new id = -1;

	if ((id = GetNearOutsideBiz(playerid)) != -1 && (BizInfo[id][bizType] != BIZ_AUTOSALON && BizInfo[id][bizType] != BIZ_ADVERT && BizInfo[id][bizType] != BIZ_TUNING && BizInfo[id][bizType] != BIZ_LICENSE && BizInfo[id][bizType] != BIZ_BOATSALON && BizInfo[id][bizType] != BIZ_FLYSALON))
	{
	    if (BizInfo[id][bizLocked])	return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);

		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* %s %s flashbang kullandý.", GetRankName(playerid), GetNameEx(playerid));
		pc_cmd_me(playerid, "teçhizat kemerinden flashbang çýkartýr. Mandala basar ve pimini çekerek binanýn içine fýrlatýr.");
		
		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !IsPlayerBizInside(i, id)) continue;
		    
			SendSyntaxMessage(i, "Bir flaþ patlamasý sebebiyle geçici olarak kör oldun!");
			GameTextForPlayer(i, "~r~!!! FLASHBANG !!!~n~~n~~n~!!! FLASHBANG !!!~n~~n~~n~!!! FLASHBANG !!!", 12000, 3);
            SetPlayerWeather(i, 36);
			SetPlayerTime(i, 22, 0);
			StopPlayerAnims(i);
			FreezePlayer(i);
			SetPlayerDrunkLevel(i, 50000);
			pTemp[i][pFlashTime] = 15;
		}
		return 1;
	}
	if ((id = GetNearOutsideHouse(playerid)) != -1)
	{
	    if (HouseInfo[id][hLocked])	return GameTextForPlayer(playerid, "~r~KAPALI!", 2500, 1);

        SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* %s %s flashbang kullandý.", GetRankName(playerid), GetNameEx(playerid));
		pc_cmd_me(playerid, "teçhizat kemerinden flashbang çýkartýr. Mandala basar ve pimini çekerek binanýn içine fýrlatýr.");
		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !IsPlayerInsideHouse(i, id)) continue;
		    
			SendSyntaxMessage(i, "Bir flaþ patlamasý sebebiyle geçici olarak kör oldun!");
			GameTextForPlayer(i, "~r~!!! FLASHBANG !!!~n~~n~~n~!!! FLASHBANG !!!~n~~n~~n~!!! FLASHBANG !!!", 12000, 3);
            SetPlayerWeather(i, 36);
			SetPlayerTime(i, 22, 0);
			StopPlayerAnims(i);
			FreezePlayer(i);
			SetPlayerDrunkLevel(i, 50000);
			pTemp[i][pFlashTime] = 15;
		}
		return 1;
	}

	SendErrorMessage(playerid, "Ev/iþyeri giriþinde kullanýn.");
	return 1;
}

CMD:ekip(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction];
	
	if (!IsFactionPolice(faction))	return SendErrorMessage(playerid, "Bu komutu kullanabilmek için Bu komutu kullanamazsýnýz.");

	if (pTemp[playerid][pPatrol])
	{
	    new id = pTemp[playerid][pPatrol]-1;

	    pTemp[playerid][pPatrol] = 0;

	    if (id < 0 || id >= MAX_PATROL || !PatrolInfo[GetPatrolID(playerid)][id][patrulExists])	return 1;

        if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == playerid) 																							PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] = INVALID_PLAYER_ID;
        if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] == playerid) 																							PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;
		if (PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID)	PatrolInfo[GetPatrolID(playerid)][id][patrulExists] = 0;

	    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[LSPD] %s %s ekibi sildi: %s", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][id][patrulName]);
		return 1;
	}

    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (isnull(params))					return SendHelpMessage(playerid, "/callsign [ekip kodu]");

	for(new i; i != MAX_PATROL; i++)
	{
	    if (!PatrolInfo[GetPatrolID(playerid)][i][patrulExists] || !CompareStrings(params, PatrolInfo[GetPatrolID(playerid)][i][patrulName]))	 continue;

		if (PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] != INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][1] != INVALID_PLAYER_ID)	
			return SendErrorMessage(playerid, "Bu devriye zaten tamamlandý.");

        if (PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] == INVALID_PLAYER_ID) PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] = playerid;
        else 																			PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][1] = playerid;

		pTemp[playerid][pPatrol] = i+1;
		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[LSPD] %s %s, %s ekibine katýldý.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][i][patrulName]);
		return 1;
	}

	new id = -1;
	for(new i; i != MAX_PATROL; i++)
	{
	    if (PatrolInfo[GetPatrolID(playerid)][i][patrulExists]) continue;

		id = i;
		break;
	}

	if (id == -1)	return SendErrorMessage(playerid, "Maksimum ekip sayýsýna ulaþýldý.");

    pTemp[playerid][pPatrol] = id+1;
    PatrolInfo[GetPatrolID(playerid)][id][patrulExists] = 1;
    format(PatrolInfo[GetPatrolID(playerid)][id][patrulName], 32, "%s", params);
    PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] = playerid;
    PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;
    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[LSPD] %s %s, %s ekip koduyla sahaya çýktý.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][id][patrulName]);
	return 1;
}

alias:ekipliste("ekiplistesi");
CMD:ekipliste(playerid, params)
{
	new faction = PlayerInfo[playerid][pFaction], string[256], f = GetPatrolID(playerid), count;
	if (!IsFactionPolice(faction))						return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

    for(new i = 0; i != MAX_PATROL; i++)
    {
        if (!PatrolInfo[f][i][patrulExists])  continue;

        format(string, sizeof(string), "Ekip adý: %s", PatrolInfo[f][i][patrulName]);

        if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][0]))
        {
            format(string, sizeof(string), "%s Memurlar: %s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][0]));
        }
        if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][1]))
        {
            if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][1])) {
                format(string, sizeof(string), "%s, %s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][1]));
            } else {
                format(string, sizeof(string), "%s%s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][1]));
            }
        }
                
        SendClientMessageEx(playerid, COLOUR_ALTO, string);

        count++;
        break;
    }
	if(!count) SendErrorMessage(playerid, "Aktif ekip bulunamadý.");
	return 1;	
}

CMD:elkoy(playerid, params[])
{
	new userid, type[24], faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))						return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (sscanf(params,"us[24]", userid, type))			return SendHelpMessage(playerid, "/elkoy [ID / Karakter Adý] [suruculisansi | ucuslisansi | silah | esyalar(maske, kalem vb.)]");
	if (userid == playerid)								return 1;
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(4.0, playerid, userid))		return SendNotNearPlayer(playerid);

	if (CompareStrings(type, "suruculisansi"))
	{
	    if (!PlayerInfo[userid][pCarLic])	return SendErrorMessage(playerid, "Oyuncunun ehliyeti bulunmuyor.");

		new mes[128];
		format(mes, sizeof(mes), "%s adlý kiþinin ehliyetine el koyar.", GetNameWithMask(userid));
		pc_cmd_me(playerid, mes);

		SendSyntaxMessage(userid, "%s adlý memur ehliyete el koyar.", GetNameWithMask(playerid));
		PlayerInfo[userid][pCarLic] = 0;
		SQL_SetInteger("users", "carlic", 0, PlayerInfo[userid][pID]);
		return 1;
	}

	else if (CompareStrings(type, "ucuslisansi"))
	{
	    if (!PlayerInfo[userid][pFlyLic])	return SendErrorMessage(playerid, "Oyuncunun uçuþ lisansý bulunmuyor.");

	    new mes[128];
		format(mes, sizeof(mes), "%s adlý kiþinin uçuþ lisansýna el koyar.", GetNameWithMask(userid));
		pc_cmd_me(playerid, mes);

		SendSyntaxMessage(userid, "%s adlý memur uçuþ lisansýnýza el koydu.", GetNameWithMask(playerid));
		PlayerInfo[userid][pFlyLic] = 0;
		SQL_SetInteger("users", "flylic", 0, PlayerInfo[userid][pID]);
		return 1;
	}

	else if (CompareStrings(type, "ucuslisansi"))
	{
	    new mes[128];
		format(mes, sizeof(mes), "%s adlý kiþinin eþyalarýna el koyar.", GetNameWithMask(userid));
		pc_cmd_me(playerid, mes);

		SendSyntaxMessage(userid, "%s adlý memur tüm eþyalarýnýza el koydu.", GetNameWithMask(playerid));
		ClearTextInventory(userid);
		return 1;
	}


	else if (CompareStrings(type, "silah"))
	{
		SilahElkoyFonksiyon(playerid, userid, 1);

	    new mes[128];
		format(mes, sizeof(mes), "%s adlý kiþinin silahýna el koyar.", GetNameWithMask(userid));
		pc_cmd_me(playerid, mes);

		SendWarningMessage(userid, "%s adlý memur silahýnýza el koydu.", GetNameWithMask(playerid));
		AC_ResetPlayerWeapons(userid);
		return 1;
	}
	else 
	{
		SendHelpMessage(playerid, "/elkoy [ID / Karakter Adý] [suruculisansi | ucuslisansi | silah]");
	}
	return 1;
}

CMD:gozalti(playerid, params[])
{
	new userid, faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))		return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (sscanf(params,"u", userid))									return SendHelpMessage(playerid, "/gozalti [ID / Karakter Adý]");
	if (userid == playerid)											return 1;
	if (!PlayerInfo[playerid][pOnDuty])								return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (!IsPlayerInAnyVehicle(playerid))							return SendNotInVehicle(playerid);
	if (!IsPlayerLogged(userid))									return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);

	new mes[128];

	if (pTemp[userid][pGozAlti] == 0)
	{
		format(mes, sizeof(mes), "%s adlý kiþiyi gözaltýna alýr.", GetNameWithMask(userid));
		FreezePlayer(userid);
		pTemp[userid][pGozAlti] = 1;
	}
	else
	{
		format(mes, sizeof(mes), "%s adlý kiþiyi gözaltýndan çýkarýr.", GetNameWithMask(userid));
		UnFreezePlayer(userid);
		pTemp[userid][pGozAlti] = 0;
	}
	pc_cmd_me(playerid, mes);
	return 1;
}

alias:tutukla("hapis");
CMD:tutukla(playerid, params[])
{
	new userid, time, info[128], faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))						return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (sscanf(params,"uds[128]", userid, time, info))	return SendHelpMessage(playerid, "/tutukla [ID / Karakter Adý] [zaman (dakika)] [sebep]");
	if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýn.");

    new arrestpoint_id = GetPlayerNearestArrestPoint(playerid);

    if(arrestpoint_id < 1)
        return SendErrorMessage(playerid, "Hapis iþlemini sadece iþlem noktalarýnda uygulayabilirsiniz.");

	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);
    if (userid == playerid)								return SendErrorMessage(playerid, "Bu komutu kendi üzerinde kullanamazsýn.");
    if (PlayerInfo[userid][pJailed])					return SendErrorMessage(playerid, "Oyuncu zaten tutuklu.");
	if (time < 1 || time > 1000)						return SendErrorMessage(playerid, "Tutuklama süresi 1 dakika ile 1000 dakika arasýnda olmalýdýr.");

    Add_Arrest(playerid, userid, time);
	PlayerInfo[userid][pJailed] = PALOMINO_JAIL;
	PlayerInfo[userid][pJailTime] = time * 60;
	PlayerInfo[userid][pArrested]++;
	SQL_SetInteger("users", "arrested", PlayerInfo[userid][pArrested], PlayerInfo[userid][pID]);
	AddCriminalRecord(userid, info, PlayerInfo[playerid][pUsername], PlayerInfo[playerid][pFaction], 1);

	SilahElkoyFonksiyon(playerid, userid, 1);

	PutPlayerInPrison(userid);
	SendServerMessage(userid, "%s adlý polis memuru tarafýndan %i dakika tutuklandýnýz. Sebep: %s", GetNameWithMask(playerid), time, info);
	pTemp[playerid][pPoliceJails]++;
	return 1;
}
/*
CMD:prison(playerid, params[])
{
	new userid, time, info[128], faction = PlayerInfo[playerid][pFaction];

    new arrestid = ArrestNearest(playerid);

	if (!IsFactionPolice(faction) && !IsFactionDocs(faction))		return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (sscanf(params,"uds[128]", userid, time, info))				return SendHelpMessage(playerid, "/prison [ID / Karakter Adý] [dakika] [sebep]");
	if (!PlayerInfo[playerid][pOnDuty])								return SendErrorMessage(playerid, "Ýþbaþýnda olmadan bu komutu kullanamazsýnýz.");
	if ((arrestid == -1))											return SendErrorMessage(playerid, "Hapis bölgesine yakýn olmalýsýn!");
	if (!IsPlayerLogged(userid))									return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))					return SendNotNearPlayer(playerid);
	if (time < 1 || time > 10000)									return SendErrorMessage(playerid, "Zaman 1 ile 10000 dakika arasý olabilir.");
	if (userid == playerid)											return 1;

	PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));
	PlayerInfo[userid][pJailed] = PRISON_JAIL;
	PlayerInfo[userid][pJailTime] = time * 60;
	PlayerInfo[userid][pIsolateTime] = 0;
	PutPlayerInPrison(userid);
	
	SendSyntaxMessage(userid, "%s dakika hapise gönderildiniz.", FormatNumber(time));
	SendSyntaxMessage(userid, "SADoC kaydýn yapýldý. %i - Numaraný öðrenmek için: (/kogusnumaram).", PlayerInfo[userid][pPrisoned]+100);
	return 1;
}*/

CMD:plakakontrol(playerid, params[])
{
	new vehicle;
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/plakakontrol [Araç ID]");
    if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
	if (!VehicleEmpty(vehicle))					return SendErrorMessage(playerid, "Bu araç þu an kullanýlýyor.");	
	if (GetNearVehicle(playerid, 12.0, vehicle) == 0) return SendErrorMessage(playerid, "Araca yakýn deðilsiniz.");


	if (VehicleInfo[vehicle][carRegistered] == 0 && VehicleInfo[vehicle][carHidedPlate] == 1)	SendSyntaxMessage(playerid, "%s model aracýn plakasý bulunmuyor.", VehicleNames[GetVehicleModel(vehicle)-400]);
	else											SendSyntaxMessage(playerid, "%s model aracýn plakasý: %s", VehicleNames[GetVehicleModel(vehicle)-400], VehicleInfo[vehicle][carPlate]);
	
	return 1;
}

CMD:kelepce(playerid, params[])
{
	new userid, faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))					return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (sscanf(params,"u",userid))					return SendHelpMessage(playerid, "/kelepce [ID / Karakter Adý]");
	if (!PlayerInfo[playerid][pOnDuty])				return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (userid == playerid)							return 1;
	if (pTemp[userid][pCuffed])						return SendErrorMessage(playerid, "Kiþi zaten kelepçeli.");

    new mes[128];
    format(mes, sizeof(mes), "%s adlý kiþiyi kelepçeler.", GetNameWithMask(userid));
    pc_cmd_me(playerid, mes);

	GameTextForPlayer(userid, "~r~KELEPCELENDINIZ", 2500, 3);
	pTemp[userid][pCuffed] = 1;
	SendSyntaxMessage(userid, "%s seni kelepçeledi.", GetNameWithMask(playerid));
	SendSyntaxMessage(playerid, "%s adlý kiþiyi kelepçelediniz.", GetNameWithMask(userid));
	SetPlayerAttachedObject(userid, ATTACH_HANDS, 19418,6,0.003999,0.028000,-0.018000,-12.900005,0.000000,-65.100006,0.878000,1.890999,1.652001);
	SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);
	UnFreezePlayer(userid);
	return 1;
}

alias:kelepcecikar("kelepcecoz");
CMD:kelepcecikar(playerid, params[])
{
	new userid, faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))					return SendErrorMessage(playerid, "Bir polis memuru / hapishane memuru olmalýsýnýz.");
	if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/kelepcecikar [ID]");
	if (!PlayerInfo[playerid][pOnDuty])				return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (userid == playerid)							return 1;
	if (!pTemp[userid][pCuffed])					return SendErrorMessage(playerid,"Oyuncunun elleri kelepçeli deðil.");

	new mes[128];
    format(mes, sizeof(mes), "%s adlý kiþinin kelepçesini çýkartýr.", GetNameWithMask(userid));
    pc_cmd_me(playerid, mes);

	pTemp[userid][pCuffed] = 0;
	SendSyntaxMessage(userid, "%s kelepçelerini çýkardý.", GetNameWithMask(playerid));
	SendSyntaxMessage(playerid, "%s adlý kiþinin kelepçesini çözdünüz.", GetNameWithMask(userid));
	RemovePlayerAttachedObject(userid, ATTACH_HANDS);
	SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
	return 1;
}

alias:destekiste("destek");
CMD:destekiste(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionPolice(faction))		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (GetPVarInt(playerid, #Chase_Time) > 1)		return StopChase(playerid);

	new location[MAX_ZONE_NAME];
	GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
    foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || !IsPlayerFactionPolice(i) || (PlayerInfo[i][pSettings] & togFaction))
			continue;

		SendClientMessage(i, COLOR_POLICECHAT, "|____________ Acil Destek Çaðrýsý ____________|");

		SendClientMessageEx(i, COLOR_POLICECHAT, "Memur: %s, No: %i", GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);
		SendClientMessageEx(i, COLOR_POLICECHAT, "Konum: %s", location);
	}

	GetPlayerPos(playerid, pTemp[playerid][pCallPosX], pTemp[playerid][pCallPosY], pTemp[playerid][pCallPosZ]);
	pTemp[playerid][pCallOn] = 1;

	SendServerMessage(playerid, "Baþarýyla destek talebi gönderdiniz. Ýptal etmek için tekrar /destek yazýn.");

	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "ÝPUCU:{FFFFFF} Destek çaðrýsýný yanýtlamak için: /dk %i", playerid);	
	StartChase(playerid);
	return 1;
}
/*
alias:kovalamaca("pursuit");
CMD:kovalamaca(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionPolice(faction))		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	
	new userid;
	if (sscanf(params,"u", userid))					return SendHelpMessage(playerid, "/pursuit [ID / Karakter Adý]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (userid == playerid)							return 1;
	if (GetPVarInt(playerid, #Chase_Time) > 1)		return SendErrorMessage(playerid, "%s [ID:%i] kovalamacaya takip ediliyor.", GetNameWithMask(userid), userid);
	if (!PlayerNearPlayer(15.0, playerid, userid))	return SendNotNearPlayer(playerid);

	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "(( HQ: %s %s adlý memur %s adlý kiþiyi kovalýyor. [ID:%i] ))", GetRankName(playerid), GetNameEx(playerid), GetNameWithMask(userid), userid);

	StartChase(userid);	
	return 1;
}*/

CMD:siren(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction], vehicle = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehicle), siren_id;

	if (!IsFactionLegal(faction))											return SendErrorMessage(playerid, "Bir devlet personeli olmalýsýnýz.");
    if (VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Resmi bir araç deðil.");
	if (sscanf(params, "i", siren_id))										return SendHelpMessage(playerid, "/siren [1-3]");
	if (siren_id < 1 || siren_id > 3)										return SendErrorMessage(playerid, "Geçersiz siren ID: 1-3.");

	if (siren_id == 1)
	{
		if (IsValidDynamicObject(VehicleInfo[vehicle][carSiren][0]))
		{
		    SendSyntaxMessage(playerid, "Siren kapatýldý.");
			DestroyDynamicObject(VehicleInfo[vehicle][carSiren][0]);
			VehicleInfo[vehicle][carSiren][0] = INVALID_OBJECT_ID;
		    return 1;
		}

		if (model != 560 && model != 541 && model != 525 && model != 426 && model != 579 && model != 415 && model != 554 && model != 546 && model != 566 && model != 561 && model != 547 && model != 482)
		{
			return SendErrorMessage(playerid, "Sultan/Bullet/Towtruck/Premier/Huntley/Cheetah/Yosemite/Intruder/Tahoma/Stratum/Primo/Burrito model araçlara takýlabilir");
		}

	    VehicleInfo[vehicle][carSiren][0] = CreateDynamicObject((model != 525)?(18646):(19419), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
		switch(model)
	    {
	        case 560: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.571924, 0.068632, 0.860007, 0.000000, 0.000000, -181.148086);
	        case 541: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.442310, -0.091429, 0.670001, 0.000000, -2.299999, -178.874786);
	        case 426: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.570416, -0.012622, 0.890005, 0.000000, 0.000000, -91.267646);
	        case 525: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.0, -0.485, 1.36, 0.000000, 0.000000, 180.0);
	        case 579: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.640568, -0.021741, 1.260003, 0.000000, 0.000000, -90.153976);
	        case 415: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.424245, -0.241412, 0.640021, 3.000001, -3.499999, -181.499969);
	        case 554: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.734659, 0.117240, 1.059349, -4.199999, 0.000000, -87.859664);
	        case 546: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.591740, -0.153342, 0.870005, 0.000000, 0.000000, -269.351074);
	        case 566: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.660138, 0.024635, 0.869999, 0.000000, 0.000000, -88.731002);
	        case 561: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.428671, 0.080074, 0.850004, -2.799999, 0.000000, -88.665367);
	        case 547: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.530513, 0.002143, 0.916606, -3.899999, 0.000000, -89.768531);
	        case 482: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.515804, 0.702674, 0.950006, 0.000000, 0.000000, -92.038864);
	    }

	    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	    return SendSyntaxMessage(playerid, "Siren aktif.");
	}

	else if (siren_id == 2)
	{
	    if (IsValidDynamicObject(VehicleInfo[vehicle][carSiren][1]))
		{
		    SendSyntaxMessage(playerid, "Siren kapatýldý.");
			DestroyDynamicObject(VehicleInfo[vehicle][carSiren][1]);
			VehicleInfo[vehicle][carSiren][1] = INVALID_OBJECT_ID;
		    return 1;
		}

	    if (model != 560 && model != 426 && model != 579 && model != 566 && model != 561 && model != 547 && model != 546)
		{
			return SendErrorMessage(playerid, "Sultan/Bullet/Towtruck/Premier/Huntley/Cheetah/Yosemite/Intruder/Tahoma/Stratum/Primo/Burrito model araçlara takýlabilir.");
		}

        VehicleInfo[vehicle][carSiren][1] = CreateDynamicObject(19419, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
        switch(model)
	    {
	        case 560: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.000000, -1.289999, 0.394999, 0.000000, 0.000000, 0.000000);
	        case 426: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.000000, -1.669998, 0.349999, 0.000000, 0.000000, 0.000000);
	        case 579: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.005192, -2.445963, 0.521951, 0.000000, 0.000000, -359.884796);
	        case 566: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.009878, -1.681756, 0.400007, 0.000000, 0.000000, -0.010757);
	        case 561: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, -0.004864, -2.317730, 0.249995, 0.000000, 0.000000, -0.192703);
	        case 547: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, -0.001344, -1.571307, 0.400003, 0.000000, 0.000000, -0.468620);
	        case 546: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.014445, -1.771190, 0.340004, 0.000000, 0.000000, -359.851013);
	    }
	    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
		return SendSyntaxMessage(playerid,"Siren aktif.");
	}

	else if (siren_id == 3)
	{
	    if (IsValidDynamicObject(VehicleInfo[vehicle][carSiren][2]))
		{
		    SendSyntaxMessage(playerid, "Siren kapatýldý.");
			DestroyDynamicObject(VehicleInfo[vehicle][carSiren][2]);
			VehicleInfo[vehicle][carSiren][2] = INVALID_OBJECT_ID;
			DestroyDynamicObject(VehicleInfo[vehicle][carSiren][3]);
			VehicleInfo[vehicle][carSiren][3] = INVALID_OBJECT_ID;
			DestroyDynamicObject(VehicleInfo[vehicle][carSiren][4]);
			VehicleInfo[vehicle][carSiren][4] = INVALID_OBJECT_ID;
		    return 1;
		}

	    if (model != 541 && model != 415 && model != 560)	return SendErrorMessage(playerid, "Bu siren yalnýzca Bullet/Cheetah/Sultan model araçlara yerleþtirilebilir.");

        if (model == 541)
		{
			VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, 0.000000, 0.000000, 0.659999, 0.000000, 0.000000, -359.823394);
			VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, 0.006984, -2.280384, -0.190001, 0.000000, 0.000000, -359.824523);
			VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, -0.007443, 2.430286, -0.070001, 0.000000, 0.000000, -180.024566);
		}
		if (model == 415)
		{
			VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, 0.000475, -0.270263, 0.630008, 0.000000, 0.000000, -359.899139);
			VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, -0.005538, 2.660761, -0.210004, 0.000000, 0.000000, -180.099121);
			VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, 0.003255, -2.460503, -0.140003, 0.000000, 0.000000, 0.266403);
		}
		if (model == 560)
		{
			VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, -0.000927, 0.110103, 0.870014, 0.000000, 0.000000, -359.517333);
			VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, 0.004800, -2.370894, 0.105430, 0.000000, 0.000000, -359.912292);
			VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, -0.003252, 2.561954, 0.050001, 0.000000, 0.000000, -179.912200);
		}

		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
		return SendSyntaxMessage(playerid,"Siren aktif.");
	}
	return 1;
}

CMD:silahruhsati(playerid, params[])
{
    new userid, price;
		
	if (sscanf(params,"ui",userid, price))			return SendHelpMessage(playerid, "/silahruhsati [ID / Karakter Adý] [ücret]");
	if (IsPlayerFactionPolice(playerid))			return SendErrorMessage(playerid, "LSPD birliðinde olmalýsýnýz.");
	if (PlayerInfo[playerid][pAuthwep] != 1)		return SendErrorMessage(playerid, "Silah ruhsatý verme yetkiniz yok.");
	if (price < 1 || price > 10000)					return SendErrorMessage(playerid, "Deðer 1-10,000. arasýnda olmalýdýr.");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
    if (PlayerInfo[userid][pWepLic] != 0)			return SendErrorMessage(playerid, "Oyuncunun zaten ruhsatý var.");
	if (pTemp[userid][pWepPlayer] == playerid)		return SendErrorMessage(playerid, "Oyuncuya zaten bir lisans satýn almasýný teklif ettiniz.");
	    
	pTemp[userid][pWepPlayer] = playerid;
	pTemp[userid][pWepPrice] = price;
	SetPVarInt(userid, #accept_time, gettime() + 30);
	SendSyntaxMessage(userid, "%s %s adlý memur sana silah lisansý teklifi verdi. Ücret: $%i. (Lisansý almak için Y tuþuna basýn.)", GetRankName(playerid), GetNameEx(playerid), price);
	SendSyntaxMessage(playerid, "%s isimli oyuncuya silah lisansý almayý teklif ettiniz. $%i.", GetNameEx(userid), price);
	return 1;
}

CMD:ruhsatyetki(playerid, params[])
{
    new userid;

	if (sscanf(params,"u",userid))										return SendHelpMessage(playerid, "/ruhsatyetki [ID / Karakter Adý]");
	if (IsPlayerFactionPolice(playerid))								return SendErrorMessage(playerid, "LSPD birliðinde olmalýsýnýz.");
	if (!isLeader(playerid))											return SendErrorMessage(playerid, "Birlik yetkilisi deðilsiniz..");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Oyuncu birliðinize üye deðil.");

	if (PlayerInfo[userid][pAuthwep] == 0)
	{
		PlayerInfo[userid][pAuthwep] = 1;
		SendSyntaxMessage(userid, "%s %s sizi lisanslandýrma birimine aldý.", GetRankName(playerid), GetNameEx(playerid));
		SendSyntaxMessage(playerid, "Lisanslandýrma birimine dahil ettiniz: %s.", GetNameEx(userid));
		return 1;
	}

	PlayerInfo[userid][pAuthwep] = 0;
	SendSyntaxMessage(userid, "%s %s sizi lisanslandýrma biriminden çýkarttý.", GetRankName(playerid), GetNameEx(playerid));
	SendSyntaxMessage(playerid, "Lisanslandýrma biriminden çýkarttýnýz: %s.", GetNameEx(userid));
	return 1;
}

CMD:swatyetki(playerid, params[])
{
	new userid;

	if (sscanf(params,"u",userid))										return SendHelpMessage(playerid, "/swatyetki [ID / Karakter Adý]"); //Komut
	if (!IsPlayerFactionPolice(playerid))								return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!isLeader(playerid))											return SendErrorMessage(playerid, "Birlik yetkilisi deðilsiniz.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Oyuncu birliðinize üye deðil.");

	if (PlayerInfo[userid][pSwat] == 0)
	{
		PlayerInfo[userid][pSwat] = 1;
		SendSyntaxMessage(userid, "%s %s adlý memur sizi SWAT birimine dahil etti.", GetRankName(playerid), GetNameEx(playerid));
		SendSyntaxMessage(playerid, "%s adlý kiþiyi SWAT birimine dahil etti.", GetNameEx(userid));
		return 1;
	}

	PlayerInfo[userid][pSwat] = 0;
	SendSyntaxMessage(userid, "%s %s adlý memur sizi SWAT birimine dahil etti.", GetRankName(playerid), GetNameEx(playerid));
	SendSyntaxMessage(playerid, "%s adlý kiþiyi SWAT biriminden çýkarttýnýz.", GetNameEx(userid));
	return 1;
}

alias:aracbagla("haciz", "arachaciz");
CMD:aracbagla(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction], vehicle = GetPlayerVehicleID(playerid);

	if (!IsFactionPolice(faction) && !IsFactionCity(faction))				return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])			return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (!IsATowTruck(vehicle))					return SendErrorMessage(playerid, "Bir çekicide olmalýsýn. ");
    if (!IsTrailerAttachedToVehicle(vehicle))	return SendErrorMessage(playerid, "Çekiciye bir araç baðlý deðil.");
	
	new trailer = GetVehicleTrailer(vehicle);

	if (!VehicleInfo[trailer][carOwnerID])								return SendErrorMessage(playerid, "Sadece kiþisel araçlar haczedilebilir.");
	//if (!PlayerToPoint(10.0, playerid, IMPOUNDX, IMPOUNDY, IMPOUNDZ))	return SendErrorMessage(playerid, "Park yeri bulunamadý.");

	DetachTrailerFromVehicle(vehicle);
	GetVehiclePos(trailer, VehicleInfo[trailer][carParkX], VehicleInfo[trailer][carParkY], VehicleInfo[trailer][carParkZ]);
    GetVehicleZAngle(trailer, VehicleInfo[trailer][carParkA]);

	SendSyntaxMessage(playerid, "%s model aracý haciz alanýna gönderdiniz.", VehicleNames[GetVehicleModel(trailer)-400]);
	VehicleEngine(trailer, false);
	
	VehicleInfo[trailer][Impounded] = 1;

	Save_Car(trailer);
	
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || PlayerInfo[i][pCarKey] != trailer) continue;

		SendSyntaxMessage(i, "%s %s tarafýndan %s model aracýnýza ceza kesildi ve hacize gönderildi", GetRankName(playerid), GetNameEx(playerid), VehicleNames[GetVehicleModel(trailer)-400]);
		break;
	}
	return 1;
}
/*
alias:swatip("sr");
CMD:swatip(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], vehicle = GetPlayerVehicleID(playerid);

	if (!IsFactionPolice(faction))			return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (!PlayerInfo[playerid][pSwatDuty])	return SendErrorMessage(playerid, "S.W.A.T. biriminde olmalýsýnýz.");
	if (GetPVarInt(playerid, #SWATROPE))	return 1;
	if (IsPlayerInAnyVehicle(playerid))		return SendErrorMessage(playerid,"Helikopterde olmalýsýnýz..");
	if (IsAHelicopter(vehicle))				return SendErrorMessage(playerid,"Helikopterde olmalýsýnýz..");
	if (!GetPlayerVehicleSeat(playerid))	return SendErrorMessage(playerid, "Yolcu koltuðunda olmalýsýnýz.");

	OnPlayerCallRappelling(playerid);
	return 1;
}*/

CMD:araccek(playerid, params[])
{
	/*new faction = PlayerInfo[playerid][pFaction], */ new vehicle = GetPlayerVehicleID(playerid);

	/*if (!IsFactionPolice(faction))			return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");*/
	if (!IsATowTruck(vehicle))				return SendErrorMessage(playerid, "Çekicinin içerisinde olmalýsýnýz.");
    if (IsTrailerAttachedToVehicle(vehicle))
	{
		DetachTrailerFromVehicle(vehicle);
		return SendErrorMessage(playerid, "Araç kancadan çýkarýldý.");
	}

	new vehid;

    if (sscanf(params,"i", vehid))														return SendHelpMessage(playerid, "/araccek [araç ID]");
	if (vehid < 1 || vehid >= MAX_VEHICLES)												return 1;
    if (GetNearVehicle(playerid, 14.0, vehid) == 0)										return SendErrorMessage(playerid, "Aracýn yakýnýnda deðilsiniz.");
    if (IsABoat(vehid) || IsAPlane(vehid) || IsAHelicopter(vehid) || IsABiker(vehid))	return SendErrorMessage(playerid, "Bu araç çekilemez.");
		
    AttachTrailerToVehicle(vehid, vehicle);
	SendSyntaxMessage(playerid, "%s model aracý çekiyorsun. Komutu tekrar kullanarak kancayý kaldýrabilirsin.", VehicleNames[GetVehicleModel(vehid)-400]);
	return 1;
}

CMD:apb(playerid, params[])
{
	new action[24], secoption[153], tmp[2][128], faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction))		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");

    if (sscanf(params, "s[24]S()[153]", action, secoption))
	{
		SendHelpMessage(playerid, "/apb [seçenek]");
		SendSyntaxMessage(playerid, "olustur / temizle / goster / duzenle / liste");
		return 1;
	}

	if (CompareStrings(action, "liste"))
	{
	    new count;
	   
		for(new i = 0; i != MAX_APBS; i++)
	    {
	        if (ApbInfo[i][apbOn] == 0) continue;

	        if (strlen(ApbInfo[i][apbCharge]) > 64)	SendClientMessageEx(playerid, COLOR_LIGHTRED, "APB %i:{FFFFFF} %.64s ... (%s)", i, ApbInfo[i][apbCharge], ApbInfo[i][apbSuspect]);
	        else									SendClientMessageEx(playerid, COLOR_LIGHTRED, "APB %i:{FFFFFF} %s (%s)", i, ApbInfo[i][apbCharge], ApbInfo[i][apbSuspect]);

			count++;
	    }

	    if (!count)	return SendErrorMessage(playerid,"APB notlarý bulunamadý.");

		return 1;
	}
	else if (CompareStrings(action, "goster"))
	{
		new number;

		if (sscanf(secoption,"i", number))	return SendHelpMessage(playerid, "/apb goster [APB Numarasý]");
		if (!ApbInfo[number][apbOn])			return SendErrorMessage(playerid, "APB notu bulunamadý.");

		SCM(playerid, -1, "____________________________________");
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "Þüpheli:{FFFFFF} %s", ApbInfo[number][apbSuspect]);
		
		if (strlen(ApbInfo[number][apbCharge]) > 64)
		{
		    SendClientMessageEx(playerid, COLOR_LIGHTRED, "Taným:{FFFFFF} %.64s ...", ApbInfo[number][apbCharge]);
		    SendClientMessageEx(playerid, -1, "... %s", ApbInfo[number][apbCharge][64]);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_LIGHTRED, "Taným:{FFFFFF} %s", ApbInfo[number][apbCharge]);
		}

        SendClientMessageEx(playerid, COLOR_LIGHTRED, "Düzenleyen:{FFFFFF} %s, %s.", ApbInfo[number][apbOfficer], Factions[ApbInfo[number][apbFaction]][fShortName]);
		SCM(playerid, -1, "____________________________________");
	}
	else if (CompareStrings(action, "temizle"))
	{
		new number;

		if (sscanf(secoption,"i", number))	return SendHelpMessage(playerid, "/apb temizle [APB Numarasý]");
		if (!ApbInfo[number][apbOn])		return SendErrorMessage(playerid, "APB notu bulunamadý.");

		SendSyntaxMessage(playerid, "ABP notunu temizlediniz %i.", number);
		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s ABP notunu temizledi %i.", GetRankName(playerid), GetNameEx(playerid), number);

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `apbs` WHERE `id` = %i", ApbInfo[number][apbID]);
		mysql_tquery(dbHandle, query);

		ApbInfo[number][apbOn] =
		ApbInfo[number][apbID] = 0;
	}
	else if (CompareStrings(action, "duzenle"))
	{
		new number, info[153];

		if (sscanf(secoption,"is[153]", number, info))	return SendHelpMessage(playerid, "/apb duzenle [APB numarasý] [þüpheli / taným]");
		if (!ApbInfo[number][apbOn])					return SendErrorMessage(playerid, "APB notu bulunamadý.");
        if (strfind(info, "/", true) == -1)				return SendErrorMessage(playerid, "Sembol bulunamadý \"/\".");
		
		SendSyntaxMessage(playerid, "APB notunu düzenlediniz. [NUM: %i].", number);
		strexplode(tmp, info, "/");
		format(ApbInfo[number][apbSuspect], MAX_PLAYER_NAME, "%s", tmp[0]);
		format(ApbInfo[number][apbCharge], 128, "%s", tmp[1]);
		ApbInfo[number][apbFaction] = faction;

		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s APB numarasý deðiþtirildi %i.", GetRankName(playerid), GetNameEx(playerid), number);
		
		new query[128 + 128];
		mysql_format(dbHandle,query, sizeof(query), "UPDATE `apbs` SET `charge` = '%s', `suspect` = '%e' WHERE `id` = %i", SQL_ReturnEscaped(tmp[1]), SQL_ReturnEscaped(tmp[0]), ApbInfo[number][apbID]);
		mysql_tquery(dbHandle, query);
		return 1;
	}
	else if (CompareStrings(action, "olustur"))
	{
		new info[153];

		if (sscanf(secoption,"s[153]", info))	return SendHelpMessage(playerid, "/apb olustur [süpheli / taným]");
        if (strfind(info, "/", true) == -1)		return SendErrorMessage(playerid, "\"/\" ile ayýrarak yazmalýsýnýz.");

		new apb = -1;

		for(new i = 0; i != MAX_APBS; i++)
		{
			if (ApbInfo[i][apbOn] != 0) continue;

			apb = i;
			break;
		}

		if (apb == -1)	return SendErrorMessage(playerid, "APB notu oluþturmak için yer kalmamýþ.");

		SendSyntaxMessage(playerid, "Bir APB notu oluþturdunuz [Numara: %i].", apb);
		strexplode(tmp, info, "/");
		format(ApbInfo[apb][apbOfficer], MAX_PLAYER_NAME, "%s", GetNameEx(playerid));
		format(ApbInfo[apb][apbSuspect], MAX_PLAYER_NAME, "%s", tmp[0]);
		format(ApbInfo[apb][apbCharge], 128, "%s", tmp[1]);
		format(ApbInfo[apb][apbDate], 32, "%s", GetFullDate());

		ApbInfo[apb][apbFaction] = faction;

		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s yeni bir APB notu eklendi. Numara: %i.", GetRankName(playerid), GetNameEx(playerid), apb);
		
        new query[128 + 128];
		mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `apbs` (faction, charge, suspect, officer, date) VALUES (%i, '%s', '%s', '%s', '%s')", faction, SQL_ReturnEscaped(tmp[1]), SQL_ReturnEscaped(tmp[0]), GetNameEx(playerid), GetFullDate());
		mysql_tquery(dbHandle, query, "ApbCreate", "i", apb);
		return 1;
	}
	return 1;
}

CMD:gisedurum(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
		
	if (isnull(params))
	{
	    SendHelpMessage(playerid, "/gisedurum [seçenekler]");
	    SCM(playerid, COLOR_GRAD2, "kapat / ac ile giþeleri kontrol edebilirsin. ");
		SCM(playerid, COLOR_GRAD2, "0 - Las Venturas giþelerini açýp kapatýr. ");
		SCM(playerid, COLOR_GRAD2, "1 - Blueberry (sað köprü) - açýp kapatýr. ");
		SCM(playerid, COLOR_GRAD2, "2 - Blueberry (sol köprü) - açýp kapatýr. ");
		return 1;
	}
	
	if (L_a_RequestAllowedCop > gettime())	return SendErrorMessage(playerid, "%i saniye beklemelisin.", L_a_RequestAllowedCop - gettime());
	    
    if (CompareStrings(params, "ac"))
	{
	    if (PlayerInfo[playerid][pRank] < 10)	return SendErrorMessage(playerid, "Bu fonksiyonu kullanmak için yetkili deðilsiniz.");
		
	    for(new i; i != MAX_TOLLS; i++)
		{
			aTolls[i][E_tLocked] = 0;
		}
		
        SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s adlý memur giþe giriþ çýkýþlarýný açtý. **", GetRankName(playerid), GetNameEx(playerid));
		L_a_RequestAllowedCop = gettime() + TOLL_DELAY_COP;
		return 1;
	}
	else if (CompareStrings(params, "kapat"))
	{
	    if (PlayerInfo[playerid][pRank] < 10)	return SendErrorMessage(playerid, "Bu fonksiyonu kullanmak için yetkili deðilsiniz. ");
			
		for(new i; i != MAX_TOLLS; i++)
		{
		    aTolls[i][E_tLocked] = 1;
		    Toll_CloseToll(i);
		}
		
		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s giþe giriþ çýkýþlarýný kapattý. **", GetRankName(playerid), GetNameEx(playerid));
        L_a_RequestAllowedCop = gettime() + TOLL_DELAY_COP;
		return 1;
	}
	
	new id = strval(params);
	
	if (id < 0 || id > 4)				return SendHelpMessage(playerid, "/gisedurum [giþe numarasý]");
    if (PlayerInfo[playerid][pRank] < 4)	return SendErrorMessage(playerid, "Bu komutu kullanabilmek için 4. rütbede olmalýsýnýz.");
		
    if (!IsPlayerInRangeOfPoint(playerid, TOLL_OPEN_DISTANCE, toll_gate_pos[id][0], toll_gate_pos[id][1], toll_gate_pos[id][2]) && !IsPlayerInRangeOfPoint(playerid, TOLL_OPEN_DISTANCE, toll_gate_pos[id+1][0], toll_gate_pos[id+1][1], toll_gate_pos[id+1][2]))
	{
		return SendErrorMessage(playerid, "Yakýnýnýzda giþe yok.");
	}
	        
	new toll_name[3][35] = /*{"òîííåëü Richman", "Flint County", */{"Las Venturas motorways", "Blueberry köprüsü", "Blueberry köprüsü"};

	if (aTolls[id][E_tLocked] == 0)
	{
		aTolls[id][E_tLocked] = 1;
		Toll_CloseToll(id);
		aTolls[id+1][E_tLocked] = 1;
		Toll_CloseToll(id+1);
		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s, %s adlý giþenin giriþ çýkýþýný açtý. **", GetRankName(playerid), GetNameEx(playerid), toll_name[id]);
	}
	else
	{
		aTolls[id][E_tLocked] = 0;
		aTolls[id+1][E_tLocked] = 0;
		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s, %s adlý giþenin giriþ çýkýþýný kapattý. **", GetRankName(playerid), GetNameEx(playerid), toll_name[id]);
	}

	L_a_RequestAllowedCop = gettime() + TOLL_DELAY_COP;
	return 1;
}

alias:government("gov");
CMD:government(playerid, params[])
{
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndna engellendi.");
	if (isnull(params))							return SendHelpMessage(playerid, "(/gov) [mesaj]");            

	new faction = PlayerInfo[playerid][pFaction], rank = PlayerInfo[playerid][pRank];

    if (!faction || IsFactionLegal(faction))						return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
	if (!isLeader(playerid))	                                    return SendErrorMessage(playerid, "Sadece birlik yetkilisi kullanabilir.");
	if (PlayerInfo[playerid][pSettings] & togGov)					return SendErrorMessage(playerid, "Önce hükümet haberlerini yayýnla. ");

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togGov))	continue;

		if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendClientMessageEx(i, COLOR_LSPD, "[Hükümet Duyurusu] %.*s ...", pos, params);
			SendClientMessageEx(i, COLOR_LSPD, "[Hükümet Duyurusu] ... %s", params[pos]);
		}
		else
		{
			SendClientMessageEx(i, COLOR_LSPD, "[Hükümet Duyurusu] %s", params);
		}
	}
	return 1;
}

alias:isbasi("uniforma", "ekipman");
CMD:isbasi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!faction || !IsFactionLegal(faction))								return 1;

    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");

    Dialog_Show(playerid, DutyMenu, DIALOG_STYLE_LIST, "{FFFFFF}Ýþbaþý", "- Ýþbaþý\n- Üniformalar\n- Ekipmanlar\n- Çelik Yelek\n- Tedavi Ol", "Seç", "Ýptal");
	return 1;
}

alias:birliktag("pdtag", "/fdtag");
CMD:birliktag(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsPlayerFactionPolice(playerid) && !IsPlayerFactionFire(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	if (PlayerInfo[playerid][pRank] < 2)	return SendErrorMessage(playerid, "Bu iþlev sizin için mevcut deðil.");

    if (GetPlayerColor(playerid) != RemoveAlpha(Factions[faction][fColor]))
	{
		SetPlayerColor(playerid, RemoveAlpha(Factions[faction][fColor]));
        SendSyntaxMessage(playerid, "Adýnýzýn rengini deðiþtirdiniz. ");
	}
	else
	{
		SetPlayerColor(playerid, TEAM_HIT_COLOR);
        SendSyntaxMessage(playerid, "Adýnýzýn rengini deðiþtirdiniz.");
	}
	return 1;
}

/*
CMD:lift(playerid, params[])
{
	if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2268.0640,2448.2449,3.5313) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2781.0559,-1056.2823,1028.4969) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2874.6665,-940.6707,1035.9259) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2872.8813,-1072.9934,1037.1782)) return 1;

	Dialog_Show(playerid, LSPDElevator, DIALOG_STYLE_LIST, "{FFFFFF}Elevator", "[0] Garage\n[1] Ïåðâûé ýòàæ\n[2] Âòîðîé ýòàæ\n[3] Ñïîðòèâíûé çàë", "Seç", "Ýptal");
	return 1;
}*/

alias:destekkabul("dk");
CMD:destekkabul(playerid, params[])
{
    new
		userid;

	if (!IsFactionLegal(PlayerInfo[playerid][pFaction]))												
		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	
	new id = PlayerInfo[playerid][pFaction];

	if (sscanf(params, "u", userid))																										
		return SendHelpMessage(playerid, "/destekkabul [destek talebi veren kiþi ID veya isim]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "Kiþi oyunda deðil.");	

	if (!IsPlayerLogged(userid) && pTemp[userid][pCallOn] == 0)																											
		return SendErrorMessage(playerid, "Kabul ettiðiniz çaðrý kodu sonlanmýþ veya hatalý.");

	if (pTemp[playerid][pPatrol])	SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s [%s] çaðrýya katýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], userid);
	else							SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s çaðrýya katýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), userid);	

    SendServerMessage(playerid, "Bir destek çaðrýsýna katýldýn. /destekbitir ile ayrýlabilirsin.");

	Waypoint_Set(playerid, pTemp[userid][pCallPosX], pTemp[userid][pCallPosY], pTemp[userid][pCallPosZ], 3.0);
	pTemp[playerid][pDestekTakip] = userid;
	return 1;
}

CMD:destekbitir(playerid, params[])
{
    new
		userid;

	if (!IsFactionLegal(PlayerInfo[playerid][pFaction]))												
		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	
	new id = PlayerInfo[playerid][pFaction];

	if (!IsPlayerLogged(playerid) && pTemp[userid][pDestekTakip] == 0)																											
		return SendErrorMessage(playerid, "Bir destek çaðrýsýna katýlmamýþsýn.");

	if (pTemp[playerid][pPatrol])	SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s [%s] çaðrýdan ayrýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], pTemp[playerid][pDestekTakip]);
	else							SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s çaðrýdan ayrýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), pTemp[playerid][pDestekTakip]);	

	pTemp[playerid][pDestekTakip] = 0;
	pc_cmd_cpsifirla(playerid, "");
	return 1;
}


alias:ihbarkabul("ik");
CMD:ihbarkabul(playerid, params[])
{
    new
		vehicle = GetPlayerVehicleID(playerid), 
		userid
	;

	if (!IsPlayerFactionPolice(playerid))												
		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	
	new id = PlayerInfo[playerid][pFaction];

	if (VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction] && !PlayerToPoint(30.0, playerid, Factions[id][fPosX], Factions[id][fPosY], Factions[id][fPosZ]))	
		return SendErrorMessage(playerid, "Bu komut sadece departmanda ve polis araçlarýnda kullanýlabilir.");

	if (sscanf(params, "u", userid))																										
		return SendHelpMessage(playerid, "/ihbarkabul [ihbar eden kiþi ID veya isim]");

	if (!IsPlayerLogged(userid) && pTemp[userid][pCallOn] == 0)																											
		return SendErrorMessage(playerid, "Kabul ettiðiniz çaðrý kodu sonlanmýþ veya hatalý. ");

	if (pTemp[playerid][pPatrol])	SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s [%s] çaðrýya katýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], userid);
	else							SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* %s %s çaðrýya katýldý. #%i.", GetRankName(playerid), GetNameEx(playerid), userid);	

	Waypoint_Set(playerid, pTemp[userid][pCallPosX], pTemp[userid][pCallPosY], pTemp[userid][pCallPosZ], 3.0);
	pTemp[userid][pCallOn] = 0;

	pTemp[playerid][pPoliceCalls]++;
	return 1;
}

alias:spike("sp");
CMD:spike(playerid, params[])
{
	if (!IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	
	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/spike [yerlestir / kaldir / tumunukaldir]"); //Komut
		return 1;
	}

	if (CompareStrings(option, "yerlestir"))
	{
		if (GetWorld(playerid) != 0 || GetInterior(playerid) != 0)	return SendErrorMessage(playerid, "Bu komutu araç içerisinde kullanamazsýnýz.");
		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)		return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýn. ");
		new size, model;
		if (sscanf(secoption,"i", size))	return SendHelpMessage(playerid, "/spike yerlestir [1 = büyük, 2 = küçük]");
		if (size < 1 || size > 2)           return SendHelpMessage(playerid, "/spike yerlestir [1 = büyük, 2 = küçük]");

		new Float:x, Float:y, Float:z, Float:a, location[MAX_ZONE_NAME];

		GetPlayerFacingAngle(playerid, a);

		GetXYInFrontOfPlayer(playerid, x, y, z, 4.5);

		if (size == 1) {
			model = 2892;
		}
		else model = 2899;

		if (CreateStrip(x, y, z, a, model) == -1)	return SendErrorMessage(playerid, "Maksimum çivi sayýsýna ulaþýldý.");

		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

		OnPlayAnim(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0);

		SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* HQ: %s %s adlý memur %s lokasyonuna çivi yerleþtirdi.", GetRankName(playerid), GetNameEx(playerid), location);
		return 1;
	}

	if (CompareStrings(option, "kaldir"))
	{
		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)	return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýn. ");

		for(new i = 0; i < MAX_SPIKE; i++)
		{
			if (!SpikeInfo[i][sCreated] && !IsPlayerInRangeOfPoint(playerid, 4.0, SpikeInfo[i][sX], SpikeInfo[i][sY], SpikeInfo[i][sZ])) continue;

			SpikeInfo[i][sCreated] = 0;
			SpikeInfo[i][sX] = 
			SpikeInfo[i][sY] = 
			SpikeInfo[i][sZ] = 0.0;
			
			if (IsValidDynamicObject(SpikeInfo[i][sObject]))
			{
				DestroyDynamicObject(SpikeInfo[i][sObject]);
				SpikeInfo[i][sObject] = INVALID_OBJECT_ID;	
			}

			SendSyntaxMessage(playerid, "Çivileri kaldýrdýn [ID: %i].", i);
			break;
		}
		return 1;
	}

	else if (CompareStrings(option, "tumunukaldir"))
	{
		for(new i = 0; i < MAX_SPIKE; i++)
		{
			if (!SpikeInfo[i][sCreated]) continue;

			SpikeInfo[i][sCreated] = 0;
			SpikeInfo[i][sX] = 
			SpikeInfo[i][sY] = 
			SpikeInfo[i][sZ] = 0.0;

			if (IsValidDynamicObject(SpikeInfo[i][sObject]))
			{
				DestroyDynamicObject(SpikeInfo[i][sObject]);
				SpikeInfo[i][sObject] = INVALID_OBJECT_ID;
			}
		}

		SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* HQ: %s %s adlý memur tüm çivileri kaldýrdý.", GetRankName(playerid), GetNameEx(playerid));
		return 1;
	}

	else 
	{
		SendHelpMessage(playerid, "/spike [yerlestir / kaldir / tumunukaldir]");  //KOMUTU DEÐÝÞTÝRÝLECEK
	}
	return 1;
}

CMD:tutuklulistesi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionPolice(faction) || !IsFactionDocs(faction))	return SendErrorMessage(playerid,"Bir polis memuru / hapishane memuru olmalýsýnýz.");
	
	/*if (faction == DOCS)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Ñïèñîê çàêëþ÷¸ííûõ â òþðüìå:");
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PRISON_JAIL) continue;

			SendClientMessageEx(playerid, COLOR_GRAD2, "%s%i %s | Âðåìÿ çàêëþ÷åíèÿ: %s ñåê.", (PlayerInfo[i][pIsolateTime] != 0)?("B"):("A"),PlayerInfo[i][pPrisoned]+100, GetNameEx(i), FormatNumber(PlayerInfo[i][pJailTime]));
		}
		return 1;
	}*/
	
	if (IsFactionPolice(faction))
	{
		SendClientMessage(playerid, COLOR_SERVER2, "TUTUKLU LÝSTESÝ:");

		foreach(new i : Player)
		{		//(PlayerInfo[i][pJailed] != LSPD_JAIL && PlayerInfo[i][pJailed] != PALOMINO_JAIL)
			if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PALOMINO_JAIL) continue; 

			SendClientMessageEx(playerid, COLOR_GRAD2, "%s | Hapis süresi: %s saniye.", GetNameEx(i), FormatNumber(PlayerInfo[i][pJailTime]));
		}
		return 1;
	}
	
	/*else if (faction == SASD)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Ñïèñîê çàêëþ÷¸ííûõ â ó÷àñòêå San Andreas Sheriff's Department:");
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != SASD_JAIL) continue;

			SendClientMessageEx(playerid, COLOR_GRAD2, "%s | Âðåìÿ çàêëþ÷åíèÿ: %s ñåê.", GetNameEx(i), FormatNumber(PlayerInfo[i][pJailTime]));
		}
		return 1;
	}*/
	return 1;
}

alias:cctvtamir("kameratamir");
CMD:cctvtamir(playerid)
{
	new faction = PlayerInfo[playerid][pFaction]; 

	if (!IsFactionPolice(faction) && !IsFactionCity(faction)) 				return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz."); 

	new camid = GetNearestCamera(playerid, 10.0); 

	if (camid == -1) 				return SendErrorMessage(playerid, "CCTV kamerasýna yakýn olmalýsýnýz.");
	if (!CCTVInfo[camid][tvBreak]) 	return SendErrorMessage(playerid, "Bu CCTV kamerasý çalýþýyor.");

	SetCameraBreakState(camid, 0); 
	SendSyntaxMessage(playerid, "CCTV kamerasýný tamir ettiniz. [ID: %i | %s].", camid, CCTVInfo[camid][tvName]);
	return 1; 
}

/*
CMD:rgun(playerid)
{
	if (IsPlayerFactionPolice(playerid))		return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz."); 
	
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");
	
	new dropid = -1;
	if ((dropid = ItemDrop_Nearest(playerid)) == -1) return SendErrorMessage(playerid, "Íà ïîëó îêîëî Âàñ íåò îðóæèÿ.");
	if (ItemDrop[dropid][dropID] == 0) 				return SendErrorMessage(playerid, "Íà ïîëó îêîëî Âàñ íåò îðóæèÿ.");
	
	if (inventory_items[ItemDrop[dropid][dropID]][itemType] == ITEM_TYPE_WEAPON)	
		return SendErrorMessage(playerid, "Íà ïîëó îêîëî Âàñ íåò îðóæèÿ.");

	ItemDrop_Delete(dropid);
	return 1;
}*/


/*
#define MAX_HELP_LIST (50)

enum HELP_LIST_ENUM
{
	bool:hlExist,
    Float:hlX,
    Float:hlY,
    Float:hlZ,
	hlOfficer[MAX_PLAYER_NAME*2],
	hlTime,
	hlResponded //Ñêîëüêî ðàç îòêëèêíóëèñü
};
new HelpList[MAX_HELP_LIST][HELP_LIST_ENUM];

GetFreeHelpListSlot() {

	return 1;
}

Dialog:HelpList(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new string[MAX_PLAYER_NAME*2 + ] = "";

	for (new i; i < MAX_HELP_LIST; i++) {
		new location[MAX_ZONE_NAME];
		GetZone(HelpList[i][hlX], HelpList[i][hlY], location, MAX_ZONE_NAME);

		format(string, sizeof(string), "Çàïðîñ îò %s ~%i ñåêóíä íàçàä â ðàéîíå %s", );
	}
	Show_Dialog(playerid, "Çàïðàøèâàþò ïîìîùü:", string, "Accept", Kapat)
	return 1;
}


alias:panicbutton("pb");
CMD:panicbutton(playerid)
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	if (IsPlayerFactionPolice(playerid)) 	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz."); 
	if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	
	new id = GetFreeHelpListSlot();

	if () { // in da interior
		
	}
	else GetPlayerPos(playerid, HelpList[id][hlX], HelpList[id][hlY], HelpList[id][hlZ]);

	HelpList[id][hlExist] = true;
	HelpList[id][hlResponded] = 0;
	HelpList[id][hlTime] = gettime(); 
	

	format(HelpList[id][hlOfficer], MAX_PLAYER_NAME*2, "%s %s", GetRankName(playerid), GetOfficerName(playerid));

	Waypoint_Set(playerid, HelpList[id][hlX], HelpList[id][hlY], HelpList[id][hlZ], 3.0);

	new location[MAX_ZONE_NAME];
	GetZone(HelpList[id][hlX], HelpList[id][hlY], location, MAX_ZONE_NAME);

	SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s çàïðàøèâàåò ïîìîùü â ðàéîíå %s.", HelpList[id][hlOfficer], location);
	return 1;
}

alias:pblist("helplist");
CMD:pblist(playerid)
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	if (IsPlayerFactionPolice(playerid)) 	return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz."); 
	if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid, "Ýþbaþýnda olmalýsýnýz.");
	
	
	return 1;
}*/

CMD:fbirim(playerid, params[]) // Log: Evet
{
	new olusumid = PlayerInfo[playerid][pFaction], id, division;
	if(olusumid == 0) return SendErrorMessage(playerid, "Birlikte deðilsin.");
	if(PlayerInfo[playerid][pRank] < 17) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
	if(OlusumTipGetir(olusumid) == FACTION_POLICE) 
	{
		static const divisionsName[5][32] = {"Dedektif Büro", "SEB/SWAT", "FLD", "ASD", "Trafik"};
		if(!sscanf(params, "ud", id, division))
		{
			if(PlayerInfo[id][pFaction] != olusumid) return SendServerMessage(playerid, "Bu kiþi sizin oluþumunuzda deðil.");
			if(division < 1 || division > 5) return SendServerMessage(playerid, "Birim bulunamadý. (1 - 3)");
			division--;
			PlayerInfo[id][pOlusumDivision][division] = !PlayerInfo[id][pOlusumDivision][division];
			if(PlayerInfo[id][pOlusumDivision][division])
			{
				SendServerMessage(playerid, "%s kiþisini %s birimine aldýn.", GetNameEx(id), divisionsName[division]);
				SendServerMessage(id, "%s kiþisi seni %s birimine aldý.", GetNameEx(playerid), divisionsName[division]);
				Log_Kaydet("resmibirlikLog.txt", "[/fbirim] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli kullaniciyi %s birimine aldi. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pID], divisionsName[division], GetFullDate());
			}
			else
			{
				SendServerMessage(playerid, "%s kiþisini %s biriminden çýkarttýn.", GetNameEx(id), divisionsName[division]);
				SendServerMessage(id, "%s kiþisi seni %s biriminden çýkarttý.", GetNameEx(playerid), divisionsName[division]);
				Log_Kaydet("resmibirlikLog.txt", "[/fbirim] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli kullaniciyi %s biriminden atti. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pID], divisionsName[division], GetFullDate());
			}
		}
		else return SendSyntaxMessage(playerid, "/fbirim [id/isim] [1: DB - 2: SWAT - 3: Lisans - 4: ASD - 5: Trafik]");
	}
	else if(OlusumTipGetir(olusumid) == FACTION_FIRE)
	{
		static const divisionsName[5][32] = {"TSB", "SFM", "ARSON", "AIR", "LSL"};
		if(!sscanf(params, "ud", id, division))
		{
			if(PlayerInfo[id][pFaction] != olusumid) return SendServerMessage(playerid, "Bu kiþi sizin oluþumunuzda deðil.");
			if(division < 1 || division > 5) return SendServerMessage(playerid, "Birim bulunamadý. (1 - 5)");
			division--;
			PlayerInfo[id][pOlusumDivision][division] = !PlayerInfo[id][pOlusumDivision][division];
			if(PlayerInfo[id][pOlusumDivision][division])
			{
				SendServerMessage(playerid, "%s kiþisini %s birimine aldýn.", GetNameEx(id), divisionsName[division]);
				SendServerMessage(id, "%s kiþisi seni %s birimine aldý.", GetNameEx(playerid), divisionsName[division]);
				Log_Kaydet("resmibirlikLog.txt", "[/fbirim] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli kullaniciyi %s birimine aldi. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pID], divisionsName[division], GetFullDate());
			}
			else
			{
				SendServerMessage(playerid, "%s kiþisini %s biriminden çýkarttýn.", GetNameEx(id), divisionsName[division]);
				SendServerMessage(id, "%s kiþisi seni %s biriminden çýkarttý.", GetNameEx(playerid), divisionsName[division]);
				Log_Kaydet("resmibirlikLog.txt", "[/fbirim] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli kullaniciyi %s biriminden atti. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pID], divisionsName[division], GetFullDate());

			}
		}
		else return SendSyntaxMessage(playerid, "/fbirim [id/isim] [1: TSB - 2: SFM - 3: ARSON - 4: AIR - 5: LSL]");
	}
	else 
	{
		static const divisionsName[84] = {"Lisans"};
		if(!sscanf(params, "ud", id, division))
		{
			if(PlayerInfo[id][pFaction] != olusumid) return SendServerMessage(playerid, "Bu kiþi sizin oluþumunuzda deðil.");
			if(division != 1) return SendServerMessage(playerid, "Birim bulunamadý. (Sadece 1 yazabilirsiniz)");
			division--;
			PlayerInfo[id][pOlusumDivision][division] = !PlayerInfo[id][pOlusumDivision][division];
			if(PlayerInfo[id][pOlusumDivision][division])
			{
				SendServerMessage(playerid, "%s kiþisini %s birimine aldýn.", GetNameEx(id), divisionsName);
				SendServerMessage(id, "%s kiþisi seni %s birimine aldý.", GetNameEx(playerid), divisionsName);
			}
			else
			{
				SendServerMessage(playerid, "%s kiþisini %s biriminden çýkarttýn.", GetNameEx(id), divisionsName);
				SendServerMessage(id, "%s kiþisi seni %s biriminden çýkarttý.", GetNameEx(playerid), divisionsName);
			}
		}
		else return SendSyntaxMessage(playerid, "/fbirim [id/isim] [1: Lisans]");
	}
	return 1;
}

CMD:r2(playerid, params[]) 
{
    new faction = PlayerInfo[playerid][pFaction];
	if(!IsFactionLegal(faction)) return SendErrorMessage(playerid, "Hükümet oluþumunda olmalýsýn.");
		
    new message[256];
    if(sscanf(params, "s[256]", message) || strlen(message) > 256) return SendSyntaxMessage(playerid, "/r [yazý]");
    SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFaction] == 0) continue;
		if(!PlayerInfo[i][pOnDuty]) continue;
        if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
        
	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_RADIO, "** [CH: CW-TAC, S: 913] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_RADIO, "** [CH: CW-TAC, S: 913] %s: %s", GetNameEx(playerid), params);
	    }	
    }
    printf("[R] %s: %s", GetNameEx(playerid), params);
    return 1;
}

CMD:r3(playerid, params[]) 
{
    new faction = PlayerInfo[playerid][pFaction];
	if(!IsFactionLegal(faction)) return SendErrorMessage(playerid, "Hükümet oluþumunda olmalýsýn.");

    if(PlayerInfo[playerid][pOlusumDivision][4] != 1) return SendErrorMessage(playerid, "Bu komutu sadece Trafik Büro üyeleri kullanabilir.");
    new message[256];
    if(sscanf(params, "s[256]", message) || strlen(message) > 256) return SendSyntaxMessage(playerid, "/r [yazý]");
    SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFaction] == 0) continue;
		if(!PlayerInfo[i][pOnDuty]) continue;
        if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
        
        if(PlayerInfo[i][pOlusumDivision][4] != 1) continue;
	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_RADIO, "** [CH: TRAFFIC, S: 913] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_RADIO, "** [CH: TRAFFIC, S: 913] %s: %s", GetNameEx(playerid), params);
	    }
    }
    printf("[R] %s: %s", GetNameEx(playerid), params);
    return 1;
}

CMD:r4(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction];
	if(!IsFactionLegal(faction)) return SendErrorMessage(playerid, "Hükümet oluþumunda olmalýsýn.");

    if(PlayerInfo[playerid][pOlusumDivision][1] != 1) return SendErrorMessage(playerid, "Bu komutu sadece SWAT üyeleri kullanabilir.");
    new message[256];
    if(sscanf(params, "s[256]", message) || strlen(message) > 256) return SendSyntaxMessage(playerid, "/r [yazý]");
    SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFaction] == 0) continue;
		if(!PlayerInfo[i][pOnDuty]) continue;
        if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
        
        if(PlayerInfo[i][pOlusumDivision][1] != 1) continue;
	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_RADIO, "** [CH: METRO, S: 914] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_RADIO, "** [CH: METRO, S: 914] %s: %s", GetNameEx(playerid), params);
	    }
    }
    printf("[R] %s: %s", GetNameEx(playerid), params);
    return 1;
}

CMD:r5(playerid, params[])
{
    new faction = PlayerInfo[playerid][pFaction];
	if(!IsFactionLegal(faction)) return SendErrorMessage(playerid, "Hükümet oluþumunda olmalýsýn.");

    if(PlayerInfo[playerid][pOlusumDivision][0] != 1) return SendErrorMessage(playerid, "Bu komutu sadece DET üyeleri kullanabilir.");
    new message[256];
    if(sscanf(params, "s[256]", message) || strlen(message) > 256) return SendSyntaxMessage(playerid, "/r [yazý]");
    SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
    foreach(new i : Player)
    {
        if(PlayerInfo[i][pFaction] == 0) continue;
		if(!PlayerInfo[i][pOnDuty]) continue;
        if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
        
        if(PlayerInfo[i][pOlusumDivision][0] != 1) continue;
	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_RADIO, "** [CH: DETECTIVE, S: 915] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_RADIO, "** [CH: DETECTIVE, S: 915] %s: %s", GetNameEx(playerid), params);
	    }
    }
    printf("[R] %s: %s", GetNameEx(playerid), params);
    return 1;
}