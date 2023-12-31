alias:tasimacilik("teslimat");
CMD:tasimacilik(playerid, params[])
{
	if(!MeslekSistemleri) return SendErrorMessage(playerid, "Meslek sistemleri pasife �ekildi. Rol modu aktif edildi. (PayDay y�kseltildi)");
	if (pTemp[playerid][pTruckerOn])
	{
	    pTemp[playerid][pTruckerOn] = 0;
	    SendSyntaxMessage(playerid, "Teslimat� reddettiniz. Yeni teslimat iki dakika sonra haz�r olacak.");
	    DisableWaypoint(playerid);
	    SetPVarInt(playerid, #pizza_time, gettime() + 120);
	    return 1;
	}

	if (GetPVarInt(playerid, #pizza_time) > gettime())	return SendErrorMessage(playerid, "Sipari� yok, l�tfen daha sonra ileti�ime ge�in.");
    if (PlayerInfo[playerid][pJob] != JOB_TRUCKER) 	    return 1;
	if (!IsPlayerInAnyVehicle(playerid))		        return SendErrorMessage(playerid, "Ara�ta olmal�s�n�z.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "S�r�c� olmal�s�n�z.");
	
	new vehicle = GetPlayerVehicleID(playerid);
	if (!GetAvailableTruck(playerid, GetVehicleModel(vehicle))) return SendErrorMessage(playerid, "Bu ara� bu mesle�e uygun de�il.");

	new i, bizid = randomEx(1, 150), location[MAX_ZONE_NAME];
		
	while(i == 0)
	{
	    if (!BizInfo[bizid][bizID])
		{
			bizid = randomEx(1, 150);
		}
		else
		{
			GetZone(BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], location, MAX_ZONE_NAME);
			new deliveryPrice = floatround(GetPlayerDistanceFromPoint(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]) * 0.16);
		    i = 1;
		    pTemp[playerid][pTruckerOn] = bizid+1;
			pTemp[playerid][pTruckerPrice] = deliveryPrice;
			pTemp[playerid][pTruckerTime] = gettime();

            SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("Liberty Ta��mac�l�k �irketi " EMBED_ALTO "sana yeni bir " EMBED_SERVER2 "%s teslimat� " EMBED_ALTO "i�i verdi.", trucker_teslimat[BizInfo[bizid][bizType]]));
            SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("B�lge: " EMBED_ALTO "%s " EMBED_SERVER2 "Mekan: " EMBED_ALTO "%s " EMBED_SERVER2 "A��klama: " EMBED_ALTO "%s", location, BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]])); 
			SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("�pucu: " EMBED_ALTO "Teslimat noktas�na gittikten sonra /koli yazarak koliyi elinize al�n. ")); 

			Waypoint_Set(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
		    return 1;
		}
	}

	//Dialog_Show(playerid, PDAMenu, DIALOG_STYLE_LIST, "{FFFFFF}Ta��mac�l�k Men�s�", "{FFFFFF}��letmeleri g�r�nt�le\nT�m i�letme sipari�lerini g�r�nt�le\nGemi hakk�nda bilgi g�ster", "Se�", "�ptal");
	return 1;
}

alias:koli("cuval");
CMD:koli(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");

	if (!pTemp[playerid][pTruckerOn])								return SendErrorMessage(playerid, "�u an teslimat s�recinde de�ilsiniz veya elinizde koli yok. (/tasimacilik)");
	if (IsPlayerInAnyVehicle(playerid))                             return SendWarningMessage(playerid, "Ara�ta bu i�lemi yapamazs�n.");      
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))		return RemovePlayerAttachedObject(playerid, ATTACH_HANDS), SendServerMessage(playerid, "Koliyi/�uval� araca b�rakt�n�z.");

	new vehicle;    
    if ((vehicle = Arac_Yakin(playerid, 5.0)) == -1 || !GetAvailableTruck(playerid, GetVehicleModel(vehicle)))	return SendErrorMessage(playerid, "Kamyonun yan�nda olmal�s�n�z.");
    
	pc_cmd_liftup(playerid, "");
    SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2912, 5, 0.102000, 0.306000, -0.228999, -1.100001, 14.499999, -1.300000, 1.000000, 1.000000, 1.000000);
  	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
  	InfoMSG(playerid, "Belirlenen noktaya ilerleyin.", 5);
	return 1;
}