Dialog:DutyMenu(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	    
    new faction = PlayerInfo[playerid][pFaction];
	if (!IsFactionLegal(faction)) return 1;
        
	switch(listitem)
	{
	    case 0://duty
	    {
			if (pTemp[playerid][pAdminDuty] > 0)	return SendErrorMessage(playerid, "�ncelikle y�netici g�revini b�rakman�z gerekir.");
		    if (pTemp[playerid][pTaser])				return SendErrorMessage(playerid, "�lk �nce �ok ediciyi ��karman�z gerekir.");
		    if (pTemp[playerid][pPatrol])				return SendErrorMessage(playerid, "�ncelikle devriyeden ��kman�z gerekir. (/mdc -> Birimler)");

           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
    	
	        if (!PlayerInfo[playerid][pOnDuty])
			{				
				SetPVarInt(playerid, #pDelay, 1);
				SilahlariKaydet(playerid);

				if (IsFactionPolice(faction))
				{
					SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "%s dolab�ndan rozetini al�r.", GetNameWithMask(playerid));
				}

				AC_ResetPlayerWeapons(playerid);
		        SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

				PlayerInfo[playerid][pOnDuty] = 1;
				pTemp[playerid][tempStatus] = 1;
		 		SetPlayerColor(playerid, RemoveAlpha(Factions[faction][fColor]));
		        SendFactionMessage(faction, IsFactionPolice(faction) ? COLOR_POLICECHAT : COLOR_LIGHTBLUE, "** HQ: %s %s i�ba��na ge�ti. **", GetRankName(playerid), GetNameEx(playerid));
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
				SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "%s rozetini dolab�na koyar.", GetNameWithMask(playerid));
			}

			SendFactionMessage(faction, IsFactionPolice(faction) ? COLOR_POLICECHAT : COLOR_LIGHTBLUE, "** HQ: %s %s i�ba��ndan ayr�ld�. **", GetRankName(playerid), GetNameEx(playerid));
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
		    if (!PlayerInfo[playerid][pOnDuty])		return SendErrorMessage(playerid,"�lk �nce i�ba��nda olmal�s�n�z.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
            //if (PlayerInfo[playerid][pSwatDuty])	return SendErrorMessage(playerid, "�niforman�z� de�i�tirmeden �nce S.W.A.T ekipmanlar�n�z� b�rak�n.");
                
			mysql_tquery(dbHandle, GetFactionSkin("faction_skins.model_id", "", "", 1, -1, -1, faction), "DisplayFactionSkins", "d", playerid);
		}
		case 2:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
    			
			if (IsFactionPolice(faction))
			{
				return Dialog_Show(playerid, LSPDArmoury, DIALOG_STYLE_LIST, "Ekipman ve Silah", "Silahlar\nS.W.A.T ekipman�", "Se�", "Geri D�n");
			}
			else if (IsFactionDocs(faction))
			{	
				return Dialog_Show(playerid, DOCSGUN, DIALOG_STYLE_LIST, "Silah", "Cudgel\nPepper Spray\nDesert Eagle (.50AE .ext)\n\t{ffc46a} - Ekstra �arj�r al (.50AE .ext)\n{FFFFFF} MP5 (9x19mm .ext)\n\t{ffc46a} - Ekstra �arj�r al (9x19mm .ext)\n{FFFFFF} Shotgun (12-G BIRDSHOT)\n\t{ffc46a} - Ekstra �arj�r al (12-G BIRDSHOT)\n\t{ffc46a} - Plastik mermi �arj�r� (12-G BEANBAG)\n{FFFFFF} M4 (5.56x45mm (drum))\n\t{ffc46a} - Ekstra �arj�r al (5.56x45mm (drum))\n\t{ffc46a} - Plastik mermi �arj�r� (5.56x45mm (plastik))\n{FFFFFF} Sniper T�fe�i (7.62x51mm)\n\t{ffc46a} - Ekstra �arj�r al (7.62x51mm)\n{FFFFFF} Gaz bombas�\nKamera\n{FF6347} T�m silahlar� teslim et", "Se�", "Kapat");
			}
			else if (IsFactionCity(faction))
			{
			    return Dialog_Show(playerid, CITYGUN, DIALOG_STYLE_LIST, "Silah", "Desert Eagle ( .50AE .ext )\n\t{ffc46a} - Ekstra �arj�r al (.50AE .ext)\n{FFFFFF} MP5 (9x19mm .ext)\n\t{ffc46a} - Ekstra �arj�r al (9x19mm .ext)\n{FFFFFF} M4 (5.56x45mm (drum))\n\t{ffc46a} - Ekstra �arj�r al (5.56x45mm (drum))\n\t{ffc46a} - Plastik mermi (5.56x45mm (plastik))\n{FF6347} T�m silahlar� teslim et", "Se�", "Kapat");
			}
			else if (IsFactionFire(faction) || IsFactionMedic(faction))
			{
		        return Dialog_Show(playerid, FDArmoury, DIALOG_STYLE_LIST, "Ekipman", "Elektrikli testere\nYang�n s�nd�r�c�\n{FF6347}T�m ekipmanlar� al", "Se�", "Geri D�n");
			}		
	    }
	    case 3:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z.");
	        if (!IsFactionLegal(faction))											return SendErrorMessage(playerid, "Bir polis memuru / sa�l�k g�revlisi olmal�s�n�z.");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
    			
		    if (IsFactionMedic(faction) || IsFactionFire(faction)) SetPlayerArmour(playerid, 100.0);
			else				SetPlayerArmour(playerid, 100.0);

			SendSyntaxMessage(playerid, "Kur�un ge�irmez yelek giyiyorsun. ");
            pc_cmd_isbasi(playerid, "");
	    }
	    case 4:
	    {
	        if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Bu fonksiyon i�in i�ba��nda olmal�s�n�z. (/isbasi).");
           	new locker_id = GetPlayerNearestLocker(playerid);
	        if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");

		    PlayerInfo[playerid][pHealth] = 100.0;
		    
			SendSyntaxMessage(playerid, "Sa�l���n�z� tazelediniz. ");
		    pc_cmd_isbasi(playerid, "");
	    }
	}
	return 1;
}

Dialog:ScrapVehicleFaction(playerid, response, listitem, inputtext[])
{
	if (!response)											return 1;
    if (PlayerInfo[playerid][pFaction] == 0)				return SendErrorMessage(playerid, "Herhangi bir birli�e �ye de�ilsiniz.");
	if (!IsFactionLegal(PlayerInfo[playerid][pFaction]))	return SendErrorMessage(playerid, "H�k�met birli�inde olmal�s�n. ");

	new veh = PlayerInfo[playerid][pCarKey];

	if (!IsValidVehicle(veh))					return SendErrorMessage(playerid, "Arac�n�z spawnlanmad�.");
	if (!IsPlayerInVehicle(playerid, veh))		return SendErrorMessage(playerid, "Bu arac�n sahibi de�ilsiniz.");
	if (IsADonateModel(GetVehicleModel(veh)))	return SendErrorMessage(playerid, "Bu arac� transfer edemezsiniz.");
	if (VehicleInfo[veh][carComponent][5] != 0)	return SendErrorMessage(playerid, "Bu arac� �zerinde nitro varken transfer edemezsiniz.");
	    
    VehicleInfo[veh][carOwnerID] = INVALID_PLAYER_ID;
    VehicleInfo[veh][carFaction] = PlayerInfo[playerid][pFaction];
    StopCarBoomBox(veh);
    
	new query[256];
    mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `owner_id`=0, `faction`=%i WHERE `id`=%i", PlayerInfo[playerid][pFaction], VehicleInfo[veh][carID]);
	mysql_tquery(dbHandle, query);
    PlayerInfo[playerid][pCarKey] = 0;
    VehicleInfo[veh][carOwnerPlayer] = INVALID_PLAYER_ID;
    DeleteVehicleTickets(veh);
	SendSyntaxMessage(playerid, "%s arac�n�z� %s birli�ine transfer ettiniz.", VehicleNames[VehicleInfo[veh][carModel]-400], Factions[PlayerInfo[playerid][pFaction]][fName]);
	return 1;
}

Dialog:BortListChoose(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_barikatliste(playerid, "");

    new bort = GetPVarInt(playerid, #select_bort)-1;

    DeletePVar(playerid, #select_bort);
	if (bort < 0)	return SendErrorMessage(playerid, "Barikat bulunamad� ");

	if (BortInfo[playerid][bort][bortUsing]) return SendErrorMessage(playerid, "Obje �u anda kullan�mda! ");

	if (listitem == 0)
	{
	    if (BortInfo[playerid][bort][bortOn] == 0)	return SendErrorMessage(playerid, "Obje bulunamad�. ");

		new Float: x, Float: y, Float: z;
		GetDynamicObjectPos(BortInfo[playerid][bort][bortObject], x, y, z);


		if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 10.0)	return SendErrorMessage(playerid, "Obje sizden �ok uzakta.");
		if (IsPlayerInAnyVehicle(playerid))							return SendErrorMessage(playerid, "Bu i�lem i�in ara�ta olmamal�s�n.");
    	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "�lk �nce i�ba��nda olmal�s�n�z. ");

		EditDynamicObject(playerid, BortInfo[playerid][bort][bortObject]);
		pTemp[playerid][pEditBort] = bort+1;
	    return 1;
	}

    if (!BortInfo[playerid][bort][bortOn]) 	return SendErrorMessage(playerid, "Obje bulunamad�. ");

	BortInfo[playerid][bort][bortOn] = 0;
	BortInfo[playerid][bort][bortUsing] = 0;

	if (IsValidDynamicObject(BortInfo[playerid][bort][bortObject]))
	{
		DestroyDynamicObject(BortInfo[playerid][bort][bortObject]);
 		BortInfo[playerid][bort][bortObject] = INVALID_OBJECT_ID;
	}

	SendSyntaxMessage(playerid, "'%s' barikat� kald�r�ld�.", BortInfo[playerid][bort][bortName]);

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
		SendSyntaxMessage(playerid, "T�m barikatlar kald�r�ld�.");
	    DestroyAllBort(playerid);
	    return 1;
	}
	
	new count;

	for (new i = 0; i != MAX_BORTES; i ++)
	{
		if (BortInfo[playerid][i][bortOn] == 0) continue;
		
  		if (count == listitem-1)
      	{
       		Dialog_Show(playerid, BortListChoose, DIALOG_STYLE_LIST, BortInfo[playerid][i][bortName], "Barikat� d�zenle\nBarikat� kald�r", "Se�", "Geri D�n");
         	SetPVarInt(playerid, #select_bort, i+1);
			return 1;
   		}
    	count++;
	}
	SendErrorMessage(playerid, "Barikat bulunamda�. ");
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
			case 0: // Olu�um kur
			{
				if(PlayerInfo[playerid][pFaction] != 0) return SendErrorMessage(playerid, "Birlikteyken bu komutu kullanamazs�n.");
				if(PlayerInfo[playerid][pLevel] < OLUSUM_BIRLIK_KUR_SEVIYE) return SendErrorMessage(playerid, "Birlik kurmak i�in "#OLUSUM_BIRLIK_KUR_SEVIYE" seviye olmal�s�n.");
				if(PlayerInfo[playerid][pCash] < OLUSUM_BIRLIK_KUR_PARA) return SendErrorMessage(playerid, "Birlik kurmak i�in yeterli paran yok.");
				new olusumadi[MAX_OLUSUM_ADI], kisadi[MAX_OLUSUM_KISADI], tip, kontrol;
				if(sscanf(inputtext, "p<,>s[40]s[10]d", olusumadi, kisadi, tip))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Girilen de�er 'Olu�um ad�, k�saltma, tip' �eklinde olmal�d�r.");
					return 1;
				}
				if(!(2 <= strlen(kisadi) < MAX_OLUSUM_KISADI))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Olu�um k�saltmas� 2 ve 4 karakter aras� uzunlukta olmal�d�r.");
					return 1;
				}
				if(!(3 <= strlen(olusumadi) <= MAX_OLUSUM_ADI))
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Olu�um ad� 3 ve "#MAX_OLUSUM_ADI" karakter aras� uzunlukta olmal�d�r.");
					return 1;
				}
				for(new i; i < sizeof(OyuncuOlusumlar); i++) if(OyuncuOlusumlar[i] == tip) kontrol++;
				if(!kontrol)
				{
					OlusumKurDialog(playerid);
					SendErrorMessage(playerid, "Hatal� olu�um tipi girdin, tekrar deneyin.");
					return 1;
				}
				OlusumYarat(playerid, tip, olusumadi, kisadi);
				GiveCash(playerid, -OLUSUM_BIRLIK_KUR_PARA);
				Log_Kaydet("birlik/genel.txt", sprintf("[%s] %s (C_ID: %d), %s adinda birlik kurdu.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], olusumadi));
				SendSyntaxMessage(playerid, "%s, %s (%s) birli�ini olu�turdun ve hesab�ndan $%d kesildi.", GetNameEx(playerid), olusumadi, OlusumTipleri[tip], OLUSUM_BIRLIK_KUR_PARA);
				SendSyntaxMessage(playerid, "144 saat i�erisinde olu�um tan�t�mlar� kategorisinde bir tan�t�m olu�turman gerekiyor, aksi taktirde birli�in siliniyor olacakt�r.");
			}
		}
	}
	return 1;
}			

Dialog:Faction_Main(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strfind(inputtext, "Birlikten Ayr�l", true) != -1)
		{
			pc_cmd_birliktenayril(playerid, "");
		}

		if(strfind(inputtext, "Birli�i Kapat", true) != -1)
		{
			new faction = PlayerInfo[playerid][pFaction];

			if (IsFactionLegal(faction)) return SendErrorMessage(playerid, "Devlet kurumlar� sadece geli�tiriciler taraf�ndan kapat�lablilir.");

			if (!isLeader(playerid)) return SendErrorMessage(playerid, "Birli�in lideri olmal�s�n�z.");

			ConfirmDialog(playerid, "Do�rulama", "{FFFFFF}\nBirli�i silmek istedi�inize emin misiniz?","FACTION_DELETE");	
		}		

		else if(strfind(inputtext, "Birlik Bilgileri", true) != -1)
		{
            new string[2068], birlikbilgileri[2068], factionid = PlayerInfo[playerid][pFaction];
           /* if(FactionData[factionid][factionSOnay]) format(silahonay, 24, "{00CC00}Var"); else format(silahonay, 24, "{CC0000}Yok");
            if(FactionData[factionid][factionUOnay]) format(uonay, 24, "{00CC00}Var"); else format(uonay, 24, "{CC0000}Yok");
            if(FactionData[factionid][factionOnay]) format(bonay, 24, "{00CC00}Var"); else format(bonay, 24, "{CC0000}Yok");*/
            format(birlikbilgileri, sizeof(birlikbilgileri), "{A9C4E4}Birlik Ad�: {FFFFFF}%s\n{A9C4E4}Birlik Kasas�: {FFFFFF}Pasif\n{A9C4E4}�ye Say�s�: {FFFFFF}%d\n{A9C4E4}Silah Onay�: {FF6347}Pasif\n{A9C4E4}Uyu�turucu Onay�: {FF6347}Pasif\n{A9C4E4}Sistem Onay�: {00CC00}Var", Factions[factionid][fName], Faction_MemberCount(factionid));
            strcat(string, birlikbilgileri);
            Dialog_Show(playerid, None, DIALOG_STYLE_LIST, "Birlik Bilgileri", string, "<< Geri", "");
		}

		else if(strfind(inputtext, "Birli�e Ara� Ekle", true) != -1)
		{
			new vehicle = GetPlayerVehicleID(playerid);
			if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Herhangi bir ara�ta de�ilsin.");
			if(VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Kendine ait bir ara�ta de�ilsin.");

            static const msg[] = "{FFFFFF}Bu i�lem geri al�namaz. Arac� birli�e ekleyecek misin? [#%i], %s";
            new string[sizeof(msg)+1+MAX_ZONE_NAME];

            format(string, sizeof(string), msg,
            VehicleInfo[vehicle][carID],
            GetVehicleModelName(GetVehicleModel(vehicle))
            );

	        ConfirmDialog(playerid, "Onayla", string, "Vehicle_AddToFaction", vehicle);
		}

		else if(strfind(inputtext, "�ye Davet Et", true) != -1)
		{
			Dialog_Show(playerid, Faction_Invite, DIALOG_STYLE_INPUT, "{FFFFFF}Davet", "{ffffff}Davet etmek istedi�iniz ki�inin ID'sini giriniz.", ">>>", "Geri D�n");
		}

		else if(strfind(inputtext, "�ye ��kar", true) != -1)
		{
			Dialog_Show(playerid, Faction_UnInvite, DIALOG_STYLE_INPUT, "{FFFFFF}�ye ��kar", "{ffffff}Birlikten ��karmak istedi�iniz ki�inin ID'sini girin.\nE�er ki�i oyunda de�ilse karakter ad�n� �sim_Soyisim format�nda yaz�n.", ">>>", "Geri D�n");
		}

		else if(strfind(inputtext, "�ye Listesi", true) != -1)
		{
			mysql_tquery(dbHandle, sprintf("SELECT * FROM users WHERE faction = %d", PlayerInfo[playerid][pFaction]), "FactionCharacterList", "d", playerid);
		}	

		else if(strfind(inputtext, "R�tbe �zinleri", true) != -1)
		{
			pc_cmd_editrights(playerid, "");
		}

		else if(strfind(inputtext, "R�tbe De�i�tir", true) != -1)
		{
			Dialog_Show(playerid, Faction_ChangeRank, DIALOG_STYLE_INPUT, "{FFFFFF}R�tbe", "{ffffff}R�tbesini de�i�tirmek istedi�iniz ki�inin ID'sini girin.", ">>>", "Geri D�n");
		}		

		else if(strfind(inputtext, "R�tbe �simleri", true) != -1)
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
	        Dialog_Show(playerid, Faction_EditRank, DIALOG_STYLE_TABLIST, "{FFFFFF}R�tbe ayarlar�", faction_ranks, ">>>", "�ptal");
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
        if(faction != PlayerInfo[userid][pFaction]) return SendErrorMessage(playerid, "Bu ki�i sizin birli�inizde de�il.");

		SetPVarInt(playerid, "Faction_RankChange", strval(inputtext));

		Dialog_Show(playerid, Faction_ChangeRankF, DIALOG_STYLE_INPUT, "{FFFFFF}R�tbe", "{ffffff}�yenin r�tbesini ne olarak de�i�tirmek istersin? (1 ile 20 aras�nda olmal�d�r)", ">>>", "Geri D�n");
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
	format(title, sizeof(title), "R�tbe �simleri: {9189EF}%s", FactionRanks[faction][listitem]);
	SetPVarInt(playerid, "Faction:RankEditName", listitem+1);

	Dialog_Show(playerid, Faction_EditRankSet, DIALOG_STYLE_INPUT, title, "Bu r�tbenin ad�n� ne olarak de�i�tirmek istersiniz?", "De�i�tir", "Geri D�n");	
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