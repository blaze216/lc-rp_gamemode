Dialog:DutyMenu(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	    
    new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionLegal(faction)) return 1;
        
	switch(listitem)
	{
	    case 0://duty
	    {
			if (pTemp[playerid][pAdminDuty] > 0)	return SendErrorMessage(playerid, "Öncelikle yönetici görevini býrakmanýz gerekir.");
		    if (pTemp[playerid][pTaser])				return SendErrorMessage(playerid, "Ýlk önce þok ediciyi çýkarmanýz gerekir.");
		    if (pTemp[playerid][pPatrol])				return SendErrorMessage(playerid, "Öncelikle devriyeden çýkmanýz gerekir. (/mdc -> Birimler)");

           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");
    	
	        if (!PlayerInfo[playerid][pOnDuty])
			{				
				SetPVarInt(playerid, #pDelay, 1);
				SilahlariKaydet(playerid);

				if (IsFactionPolice(faction))
				{
					SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "%s dolabýndan rozetini alýr.", GetNameWithMask(playerid));
				}

				AC_ResetPlayerWeapons(playerid);
		        SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

				PlayerInfo[playerid][pOnDuty] = 1;
				pTemp[playerid][tempStatus] = 1;
		 		SetPlayerColor(playerid, RemoveAlpha(Factions[faction][fColor]));
		        SendFactionMessage(faction, IsFactionPolice(faction) ? COLOR_POLICECHAT : COLOR_LIGHTBLUE, "** HQ: %s %s iþbaþýna geçti. **", GetRankName(playerid), GetNameEx(playerid));
                GameTextForPlayer(playerid, "~g~ISBASINDASINIZ", 5000, 3);
				
				pc_cmd_isbasi(playerid, "");
				Save_User(playerid);

				SetPVarInt(playerid, #pDelay, 0);
				return 1;
			}
			else {

			AC_ResetPlayerWeapons(playerid);

			if (IsFactionPolice(faction))
			{
				SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "%s rozetini dolabýna koyar.", GetNameWithMask(playerid));
			}

			SendFactionMessage(faction, IsFactionPolice(faction) ? COLOR_POLICECHAT : COLOR_LIGHTBLUE, "** HQ: %s %s iþbaþýndan ayrýldý. **", GetRankName(playerid), GetNameEx(playerid));
			GameTextForPlayer(playerid, "~r~ISBASINDAN AYRILDIN", 5000, 3);
			
			SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);
			DestroyAllBort(playerid);
		    PlayerInfo[playerid][pChar] = 0;
			PlayerInfo[playerid][pSwatDuty] = 0;
			PlayerInfo[playerid][pOnDuty] = 0;
			pTemp[playerid][tempStatus] = 0;
			foreach(new p : Player) { if(pTemp[p][pSpecPlayer] == playerid) TogglePlayerSpectating(p, 0); }

			SetRadioChannel(playerid, 0);
			PlayerInfo[playerid][pAuthed] = 0;

			SetPlayerColor(playerid, TEAM_HIT_COLOR);
			SetPlayerArmour(playerid, 0);
			SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
			pc_cmd_isbasi(playerid, "");
			}
			return Save_User(playerid);
	    }
	    case 1:
		{
		    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid,"Ýlk önce iþbaþýnda olmalýsýnýz.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");
            //if (PlayerInfo[playerid][pSwatDuty])	return SendErrorMessage(playerid, "Üniformanýzý deðiþtirmeden önce S.W.A.T ekipmanlarýnýzý býrakýn.");
                
			mysql_tquery(dbHandle, GetFactionSkin("faction_skins.model_id", "", "", 1, -1, -1, faction), "DisplayFactionSkins", "d", playerid);
		}
		case 2:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "Ýlk önce iþbaþýnda olmalýsýnýz.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");
    			
			if (IsFactionPolice(faction))
			{
				return Dialog_Show(playerid, LSPDArmoury, DIALOG_STYLE_LIST, "Ekipman ve Silah", "Silahlar\nS.W.A.T ekipmaný", "Seç", "Geri Dön");
			}
			else if (IsFactionDocs(faction))
			{	
				return Dialog_Show(playerid, DOCSGUN, DIALOG_STYLE_LIST, "Silah", "Cudgel\nPepper Spray\nDesert Eagle (.50AE .ext)\n\t{ffc46a} - Ekstra þarjör al (.50AE .ext)\n{FFFFFF} MP5 (9x19mm .ext)\n\t{ffc46a} - Ekstra þarjör al (9x19mm .ext)\n{FFFFFF} Shotgun (12-G BIRDSHOT)\n\t{ffc46a} - Ekstra þarjör al (12-G BIRDSHOT)\n\t{ffc46a} - Plastik mermi þarjörü (12-G BEANBAG)\n{FFFFFF} M4 (5.56x45mm (drum))\n\t{ffc46a} - Ekstra þarjör al (5.56x45mm (drum))\n\t{ffc46a} - Plastik mermi þarjörü (5.56x45mm (plastik))\n{FFFFFF} Sniper Tüfeði (7.62x51mm)\n\t{ffc46a} - Ekstra þarjör al (7.62x51mm)\n{FFFFFF} Gaz bombasý\nKamera\n{FF6347} Tüm silahlarý teslim et", "Seç", "Kapat");
			}
			else if (IsFactionCity(faction))
			{
			    return Dialog_Show(playerid, CITYGUN, DIALOG_STYLE_LIST, "Silah", "Desert Eagle ( .50AE .ext )\n\t{ffc46a} - Ekstra þarjör al (.50AE .ext)\n{FFFFFF} MP5 (9x19mm .ext)\n\t{ffc46a} - Ekstra þarjör al (9x19mm .ext)\n{FFFFFF} M4 (5.56x45mm (drum))\n\t{ffc46a} - Ekstra þarjör al (5.56x45mm (drum))\n\t{ffc46a} - Plastik mermi (5.56x45mm (plastik))\n{FF6347} Tüm silahlarý teslim et", "Seç", "Kapat");
			}
			else if (IsFactionFire(faction) || IsFactionMedic(faction))
			{
		        return Dialog_Show(playerid, FDArmoury, DIALOG_STYLE_LIST, "Ekipman", "Elektrikli testere\nYangýn söndürücü\n{FF6347}Tüm ekipmanlarý al", "Seç", "Geri Dön");
			}		
	    }
	    case 3:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "Ýlk önce iþbaþýnda olmalýsýnýz.");
	        if (!IsFactionLegal(faction))											return SendErrorMessage(playerid, "Bir polis memuru / saðlýk görevlisi olmalýsýnýz.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");
    			
		    if (IsFactionMedic(faction) || IsFactionFire(faction)) SetPlayerArmour(playerid, 100.0);
			else				SetPlayerArmour(playerid, 100.0);

			SendSyntaxMessage(playerid, "Kurþun geçirmez yelek giyiyorsun. ");
            pc_cmd_isbasi(playerid, "");
	    }
	    case 4:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Bu fonksiyon için iþbaþýnda olmalýsýnýz. (/isbasi).");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");

		    PlayerInfo[playerid][pHealth] = 100.0;
		    
			SendSyntaxMessage(playerid, "Saðlýðýnýzý tazelediniz. ");
		    pc_cmd_isbasi(playerid, "");
	    }
	}
	return 1;
}

Dialog:ScrapVehicleFaction(playerid, response, listitem, inputtext[])
{
	if (!response)											return 1;
    if (PlayerInfo[playerid][pFaction] == 0)				return SendErrorMessage(playerid, "Herhangi bir birliðe üye deðilsiniz.");
	if (!IsFactionLegal(PlayerInfo[playerid][pFaction]))	return SendErrorMessage(playerid, "Hükümet birliðinde olmalýsýn. ");

	new veh = PlayerInfo[playerid][pCarKey];

	if (!IsValidVehicle(veh))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý.");
	if (!IsPlayerInVehicle(playerid, veh))		return SendErrorMessage(playerid, "Bu aracýn sahibi deðilsiniz.");
	if (IsADonateModel(GetVehicleModel(veh)))	return SendErrorMessage(playerid, "Bu aracý transfer edemezsiniz.");
	if (VehicleInfo[veh][carComponent][5] != 0)	return SendErrorMessage(playerid, "Bu aracý üzerinde nitro varken transfer edemezsiniz.");
	    
    VehicleInfo[veh][carOwnerID] = INVALID_PLAYER_ID;
    VehicleInfo[veh][carFaction] = PlayerInfo[playerid][pFaction];
    StopCarBoomBox(veh);
    
	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `owner_id`=0, `faction`=%i WHERE `id`=%i", PlayerInfo[playerid][pFaction], VehicleInfo[veh][carID]);
	mysql_tquery(dbHandle, query);
    PlayerInfo[playerid][pCarKey] = 0;
    VehicleInfo[veh][carOwnerPlayer] = INVALID_PLAYER_ID;
    DeleteVehicleTickets(veh);
	SendSyntaxMessage(playerid, "%s aracýnýzý %s birliðine transfer ettiniz.", VehicleNames[VehicleInfo[veh][carModel]-400], Factions[PlayerInfo[playerid][pFaction]][fName]);
	return 1;
}

Dialog:BortListChoose(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_barikatliste(playerid, "");

    new bort = GetPVarInt(playerid, #select_bort)-1;

    DeletePVar(playerid, #select_bort);
	if (bort < 0)	return SendErrorMessage(playerid, "Barikat bulunamadý ");

	if (BortInfo[playerid][bort][bortUsing]) return SendErrorMessage(playerid, "Obje þu anda kullanýmda! ");

	if (listitem == 0)
	{
	    if (BortInfo[playerid][bort][bortOn] == 0)	return SendErrorMessage(playerid, "Obje bulunamadý. ");

		new Float: x, Float: y, Float: z;
		GetDynamicObjectPos(BortInfo[playerid][bort][bortObject], x, y, z);


		if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 10.0)	return SendErrorMessage(playerid, "Obje sizden çok uzakta.");
		if (IsPlayerInAnyVehicle(playerid))							return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýn.");
    	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýlk önce iþbaþýnda olmalýsýnýz. ");

		EditDynamicObject(playerid, BortInfo[playerid][bort][bortObject]);
		pTemp[playerid][pEditBort] = bort+1;
	    return 1;
	}

    if (!BortInfo[playerid][bort][bortOn]) 	return SendErrorMessage(playerid, "Obje bulunamadý. ");

	BortInfo[playerid][bort][bortOn] = 0;
	BortInfo[playerid][bort][bortUsing] = 0;

	if (IsValidDynamicObject(BortInfo[playerid][bort][bortObject]))
	{
		DestroyDynamicObject(BortInfo[playerid][bort][bortObject]);
 		BortInfo[playerid][bort][bortObject] = INVALID_OBJECT_ID;
	}

	SendSyntaxMessage(playerid, "'%s' barikatý kaldýrýldý.", BortInfo[playerid][bort][bortName]);

	for (new i = 0; i != MAX_BORTES; i ++)
	{
		if (BortInfo[playerid][i][bortOn] == 0) continue;
		pc_cmd_barikatliste(playerid, "");
		break;
	}

	return 1;
}

Dialog:BortList(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	if (listitem == 0)
	{
		SendSyntaxMessage(playerid, "Tüm barikatlar kaldýrýldý.");
	    DestroyAllBort(playerid);
	    return 1;
	}
	
	new count;

	for (new i = 0; i != MAX_BORTES; i ++)
	{
		if (BortInfo[playerid][i][bortOn] == 0) continue;
		
  		if (count == listitem-1)
      	{
       		Dialog_Show(playerid, BortListChoose, DIALOG_STYLE_LIST, BortInfo[playerid][i][bortName], "Barikatý düzenle\nBarikatý kaldýr", "Seç", "Geri Dön");
         	SetPVarInt(playerid, #select_bort, i+1);
			return 1;
   		}
    	count++;
	}
	SendErrorMessage(playerid, "Barikat bulunamdaý. ");
	return 1;
}

Dialog:FactionSettings(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	return ShowRightsForRank(playerid, listitem);
}

Dialog:FactionSettings_Set(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new faction = PlayerInfo[playerid][pFaction], rank = GetPVarInt(playerid, "Faction:RankEdit")-1;

	switch(listitem)
	{
		case 0:	FRank[faction][rank][rInvite] = !FRank[faction][rank][rInvite];
		case 1: FRank[faction][rank][rUninvite] = !FRank[faction][rank][rUninvite];
		case 2: FRank[faction][rank][rRank] = !FRank[faction][rank][rRank];
		case 3: FRank[faction][rank][r_eRank] = !FRank[faction][rank][r_eRank];
		case 4: FRank[faction][rank][rSpawn] = !FRank[faction][rank][rSpawn];
		case 5: FRank[faction][rank][rChat] = !FRank[faction][rank][rChat];
		case 6: FRank[faction][rank][rTow] = !FRank[faction][rank][rTow];
		case 7: FRank[faction][rank][rBodyCam] = !FRank[faction][rank][rBodyCam];
		case 8: FRank[faction][rank][r_eRights] = !FRank[faction][rank][r_eRights];
	}

	UpdateFactionRank(faction, rank+1);
	ShowRightsForRank(playerid, rank);
	DeletePVar(playerid, "Faction:EditRank");
	return 1;
}

Dialog:DialogOlusum(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(OlusumDialog[playerid][1])
		{
			case 0: // Oluþum kur
			{
				if(PlayerInfo[playerid][pFaction] != 0) return SendErrorMessage(playerid, "Birlikteyken bu komutu kullanamazsýn.");
				if(PlayerInfo[playerid][pLevel] < OLUSUM_BIRLIK_KUR_SEVIYE) return SendErrorMessage(playerid, "Birlik kurmak için "#OLUSUM_BIRLIK_KUR_SEVIYE" seviye olmalýsýn.");
				if(PlayerInfo[playerid][pCash] < OLUSUM_BIRLIK_KUR_PARA) return SendErrorMessage(playerid, "Birlik kurmak için yeterli paran yok.");
				new olusumadi[MAX_OLUSUM_ADI], kisadi[MAX_OLUSUM_KISADI], tip, kontrol;
				if(sscanf(inputtext, "p<,>s[40]s[10]d", olusumadi, kisadi, tip))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Girilen deðer 'Oluþum adý, kýsaltma, tip' þeklinde olmalýdýr.");
					return 1;
				}
				if(!(2 <= strlen(kisadi) < MAX_OLUSUM_KISADI))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Oluþum kýsaltmasý 2 ve 4 karakter arasý uzunlukta olmalýdýr.");
					return 1;
				}
				if(!(3 <= strlen(olusumadi) <= MAX_OLUSUM_ADI))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Oluþum adý 3 ve "#MAX_OLUSUM_ADI" karakter arasý uzunlukta olmalýdýr.");
					return 1;
				}
				for(new i; i < sizeof(OyuncuOlusumlar); i++) if(OyuncuOlusumlar[i] == tip) kontrol++;
				if(!kontrol)
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Hatalý oluþum tipi girdin, tekrar deneyin.");
					return 1;
				}
				OlusumYarat(playerid, tip, olusumadi, kisadi);
				GiveCash(playerid, -OLUSUM_BIRLIK_KUR_PARA);
				Log_Kaydet("birlik/genel.txt", sprintf("[%s] %s (C_ID: %d), %s adinda birlik kurdu.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], olusumadi));
				SendSyntaxMessage(playerid, "%s, %s (%s) birliðini oluþturdun ve hesabýndan $%d kesildi.", GetNameEx(playerid), olusumadi, OlusumTipleri[tip], OLUSUM_BIRLIK_KUR_PARA);
				SendSyntaxMessage(playerid, "144 saat içerisinde oluþum tanýtýmlarý kategorisinde bir tanýtým oluþturman gerekiyor, aksi taktirde birliðin siliniyor olacaktýr.");
			}
		}
	}
	return 1;
}			

Dialog:Faction_Main(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strfind(inputtext, "Birlikten Ayrýl", true) != -1)
		{
			pc_cmd_birliktenayril(playerid, "");
		}

		if(strfind(inputtext, "Birliði Kapat", true) != -1)
		{
			new faction = PlayerInfo[playerid][pFaction];

			if (IsFactionLegal(faction)) return SendErrorMessage(playerid, "Devlet kurumlarý sadece geliþtiriciler tarafýndan kapatýlablilir.");

			if (!isLeader(playerid)) return SendErrorMessage(playerid, "Birliðin lideri olmalýsýnýz.");

			ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}\nBirliði silmek istediðinize emin misiniz?","FACTION_DELETE");	
		}		

		else if(strfind(inputtext, "Birlik Bilgileri", true) != -1)
		{
            new string[2068], birlikbilgileri[2068], factionid = PlayerInfo[playerid][pFaction];
           /* if(FactionData[factionid][factionSOnay]) format(silahonay, 24, "{00CC00}Var"); else format(silahonay, 24, "{CC0000}Yok");
            if(FactionData[factionid][factionUOnay]) format(uonay, 24, "{00CC00}Var"); else format(uonay, 24, "{CC0000}Yok");
            if(FactionData[factionid][factionOnay]) format(bonay, 24, "{00CC00}Var"); else format(bonay, 24, "{CC0000}Yok");*/
            format(birlikbilgileri, sizeof(birlikbilgileri), "{A9C4E4}Birlik Adý: {FFFFFF}%s\n{A9C4E4}Birlik Kasasý: {FFFFFF}Pasif\n{A9C4E4}Üye Sayýsý: {FFFFFF}%d\n{A9C4E4}Silah Onayý: {FF6347}Pasif\n{A9C4E4}Uyuþturucu Onayý: {FF6347}Pasif\n{A9C4E4}Sistem Onayý: {00CC00}Var", Factions[factionid][fName], Faction_MemberCount(factionid));
            strcat(string, birlikbilgileri);
            Dialog_Show(playerid, None, DIALOG_STYLE_LIST, "Birlik Bilgileri", string, "<< Geri", "");
		}

		else if(strfind(inputtext, "Birliðe Araç Ekle", true) != -1)
		{
			new vehicle = GetPlayerVehicleID(playerid);
			if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Herhangi bir araçta deðilsin.");
			if(VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Kendine ait bir araçta deðilsin.");

            static const msg[] = "{FFFFFF}Bu iþlem geri alýnamaz. Aracý birliðe ekleyecek misin? [#%i], %s";
            new string[sizeof(msg)+1+MAX_ZONE_NAME];

            format(string, sizeof(string), msg,
            VehicleInfo[vehicle][carID],
            GetVehicleModelName(GetVehicleModel(vehicle))
            );

	        ConfirmDialog(playerid, "Onayla", string, "Vehicle_AddToFaction", vehicle);
		}

		else if(strfind(inputtext, "Üye Davet Et", true) != -1)
		{
			Dialog_Show(playerid, Faction_Invite, DIALOG_STYLE_INPUT, "{FFFFFF}Davet", "{ffffff}Davet etmek istediðiniz kiþinin ID'sini giriniz.", ">>>", "Geri Dön");
		}

		else if(strfind(inputtext, "Üye Çýkar", true) != -1)
		{
			Dialog_Show(playerid, Faction_UnInvite, DIALOG_STYLE_INPUT, "{FFFFFF}Üye Çýkar", "{ffffff}Birlikten çýkarmak istediðiniz kiþinin ID'sini girin.\nEðer kiþi oyunda deðilse karakter adýný Ýsim_Soyisim formatýnda yazýn.", ">>>", "Geri Dön");
		}

		else if(strfind(inputtext, "Üye Listesi", true) != -1)
		{
			mysql_tquery(dbHandle, sprintf("SELECT * FROM users WHERE faction = %d", PlayerInfo[playerid][pFaction]), "FactionCharacterList", "d", playerid);
		}	

		else if(strfind(inputtext, "Rütbe Ýzinleri", true) != -1)
		{
			pc_cmd_editrights(playerid, "");
		}

		else if(strfind(inputtext, "Rütbe Deðiþtir", true) != -1)
		{
			Dialog_Show(playerid, Faction_ChangeRank, DIALOG_STYLE_INPUT, "{FFFFFF}Rütbe", "{ffffff}Rütbesini deðiþtirmek istediðiniz kiþinin ID'sini girin.", ">>>", "Geri Dön");
		}		

		else if(strfind(inputtext, "Rütbe Ýsimleri", true) != -1)
		{
	        new faction = PlayerInfo[playerid][pFaction];
	
	        new	faction_ranks[1024] = EOS;
	        for(new i = 0; i != Factions[faction][fRanks]; i++)
	        {
		        if (PlayerInfo[playerid][pRank] >= i && !isLeader(playerid))
		        {
			        format(faction_ranks, sizeof(faction_ranks), "%s%i\t%s\n", faction_ranks, i+1, FactionRanks[faction][i]);
		        }
		        else if (isLeader(playerid))
		        {
			        format(faction_ranks, sizeof(faction_ranks), "%s%i\t%s\n", faction_ranks, i+1, FactionRanks[faction][i]);
		        }
	        }
	        Dialog_Show(playerid, Faction_EditRank, DIALOG_STYLE_TABLIST, "{FFFFFF}Rütbe ayarlarý", faction_ranks, ">>>", "Ýptal");
		}				
	}
    else return 0;

	return 1;
}

Dialog:Faction_Invite(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_birlik(playerid, "");
	if(response)
	{
		pc_cmd_birlikdavet(playerid, inputtext);
	}
	return 1;
}

Dialog:Faction_UnInvite(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_birlik(playerid, "");
	if(response)
	{
		if(strlen(inputtext) > 3)
		{
			new name[MAX_PLAYER_NAME];
			format(name, sizeof(name), "%s", inputtext);
            foreach(new i : Player)
	        {
	            if(!IsPlayerLogged(i) || !CompareStrings(GetNameEx(i), inputtext))	continue;

		        pc_cmd_birliktenat(playerid, inputtext);
		        return 1;
	        }			
			new query[256];
	        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%e'", name);
	        mysql_tquery(dbHandle, query, "OfflineFactionKick", "is", playerid, name);
		}
		else pc_cmd_birliktenat(playerid, inputtext);
	}
	return 1;
}

Dialog:Faction_ChangeRank(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_birlik(playerid, "");
	if(response)
	{
		new faction = PlayerInfo[playerid][pFaction];
		new userid = strval(inputtext);
		if(!IsPlayerLogged(strval(inputtext))) return SendNotConnected(playerid);
        if(faction != PlayerInfo[userid][pFaction]) return SendErrorMessage(playerid, "Bu kiþi sizin birliðinizde deðil.");

		SetPVarInt(playerid, "Faction_RankChange", strval(inputtext));

		Dialog_Show(playerid, Faction_ChangeRankF, DIALOG_STYLE_INPUT, "{FFFFFF}Rütbe", "{ffffff}Üyenin rütbesini ne olarak deðiþtirmek istersin? (1 ile 20 arasýnda olmalýdýr)", ">>>", "Geri Dön");
	}
	return 1;
}

Dialog:Faction_ChangeRankF(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_birlik(playerid, "");
	if(response)
	{
		if (strval(inputtext) < 0 || strval(inputtext) > 20) return pc_cmd_birlik(playerid, "");

		new userid = GetPVarInt(playerid, "Faction_RankChange");

		pc_cmd_rutbedegistir(playerid, sprintf("%d %d", userid, strval(inputtext)));

		DeletePVar(playerid, "Faction_RankChange");
	}
	return 1;
}

Dialog:Faction_EditRank(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	return EditRankName(playerid, listitem);
}

EditRankName(playerid, listitem)
{
    new title[32], faction = PlayerInfo[playerid][pFaction];
	format(title, sizeof(title), "Rütbe Ýsimleri: {9189EF}%s", FactionRanks[faction][listitem]);
	SetPVarInt(playerid, "Faction:RankEditName", listitem+1);

	Dialog_Show(playerid, Faction_EditRankSet, DIALOG_STYLE_INPUT, title, "Bu rütbenin adýný ne olarak deðiþtirmek istersiniz?", "Deðiþtir", "Geri Dön");	
	return 1;
}

Dialog:Faction_EditRankSet(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_birlik(playerid, "");

	new rank = GetPVarInt(playerid, "Faction:RankEditName");

	pc_cmd_rutbeisim(playerid, sprintf("%d %s", rank, inputtext));
	DeletePVar(playerid, "Faction:RankEditName");
	return 1;
}