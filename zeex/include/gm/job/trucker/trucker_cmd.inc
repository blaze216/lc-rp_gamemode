alias:tasimacilik("teslimat");
CMD:tasimacilik(playerid, params[])
{
	if(!MeslekSistemleri) return SendErrorMessage(playerid, "Meslek sistemleri pasife çekildi. Rol modu aktif edildi. (PayDay yükseltildi)");
	if (pTemp[playerid][pTruckerOn])
	{
	    pTemp[playerid][pTruckerOn] = 0;
	    SendSyntaxMessage(playerid, "Teslimatý reddettiniz. Yeni teslimat iki dakika sonra hazýr olacak.");
	    DisableWaypoint(playerid);
	    SetPVarInt(playerid, #pizza_time, gettime() + 120);
	    return 1;
	}

	if (GetPVarInt(playerid, #pizza_time) > gettime())	return SendErrorMessage(playerid, "Sipariþ yok, lütfen daha sonra iletiþime geçin.");
    if (PlayerInfo[playerid][pJob] != JOB_TRUCKER) 	    return 1;
	if (!IsPlayerInAnyVehicle(playerid))		        return SendErrorMessage(playerid, "Araçta olmalýsýnýz.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Sürücü olmalýsýnýz.");
	
	new vehicle = GetPlayerVehicleID(playerid);
	if (!GetAvailableTruck(playerid, GetVehicleModel(vehicle))) return SendErrorMessage(playerid, "Bu araç bu mesleðe uygun deðil.");

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

            SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("Liberty Taþýmacýlýk Þirketi " EMBED_ALTO "sana yeni bir " EMBED_SERVER2 "%s teslimatý " EMBED_ALTO "iþi verdi.", trucker_teslimat[BizInfo[bizid][bizType]]));
            SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("Bölge: " EMBED_ALTO "%s " EMBED_SERVER2 "Mekan: " EMBED_ALTO "%s " EMBED_SERVER2 "Açýklama: " EMBED_ALTO "%s", location, BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]])); 
			SendClientMessageEx(playerid, COLOR_SERVER2, sprintf("Ýpucu: " EMBED_ALTO "Teslimat noktasýna gittikten sonra /koli yazarak koliyi elinize alýn. ")); 

			Waypoint_Set(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
		    return 1;
		}
	}

	//Dialog_Show(playerid, PDAMenu, DIALOG_STYLE_LIST, "{FFFFFF}Taþýmacýlýk Menüsü", "{FFFFFF}Ýþletmeleri görüntüle\nTüm iþletme sipariþlerini görüntüle\nGemi hakkýnda bilgi göster", "Seç", "Ýptal");
	return 1;
}

CMD:koli(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	if (!pTemp[playerid][pTruckerOn])								return SendErrorMessage(playerid, "Þu an teslimat sürecinde deðilsiniz. (/tasimacilik)");
	if (IsPlayerInAnyVehicle(playerid))                             return SendWarningMessage(playerid, "Araçta bu iþlemi yapamazsýn.");      
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))		return SendWarningMessage(playerid, "Elleriniz zaten dolu.");

	new vehicle;    
    if ((vehicle = Arac_Yakin(playerid, 5.0)) == -1 || !GetAvailableTruck(playerid, GetVehicleModel(vehicle)))	return SendErrorMessage(playerid, "Kamyonun yanýnda olmalýsýnýz.");
    
	pc_cmd_liftup(playerid, "");
    SetPlayerAttachedObject(playerid, ATTACH_HANDS, 2912, 5, 0.102000, 0.306000, -0.228999, -1.100001, 14.499999, -1.300000, 1.000000, 1.000000, 1.000000);
  	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
  	InfoMSG(playerid, "Belirlenen noktaya ilerleyin.", 5);
	return 1;
}