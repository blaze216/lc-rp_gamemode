alias:kanal("telsizkanal");
CMD:kanal(playerid, params[])
{
	new option[16], secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendSyntaxMessage(playerid, "/kanal [ayarla / ayril / kirala / sat]");
		return 1;
	}

	if (CompareStrings(option, "ayarla"))
	{
		if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
		
		new channelid;

		if (sscanf(secoption, "i", channelid))						return SendHelpMessage(playerid, "/kanal ayarla [kanal]");
		if (!ChannelExists(channelid))								return SendErrorMessage(playerid, "Telsiz frekansý bulunamadý.");
		if (channelid == 911 && !IsPlayerFactionPolice(playerid))	return SendErrorMessage(playerid,"Bu telsiz frekansýný kullanamazsýnýz.");
		if (channelid == 912 && !IsPlayerFactionMedic(playerid))	return SendErrorMessage(playerid, "Bu telsiz frekansýný kullanamazsýnýz.");
		if (channelid == 998 && !IsPlayerFactionFire(playerid))		return SendErrorMessage(playerid, "Bu telsiz frekansýný kullanamazsýnýz.");
		if (channelid == GetPlayerChannel(playerid))				return SendErrorMessage(playerid, "Zaten bu telsiz frekansýna baðlýsýnýz.");
		
		if (channelid == 911 && IsPlayerFactionPolice(playerid))
		{
			SendRadioMsg(playerid, "Frekans deðiþtirildi [CH: %i]", channelid);
			PlayerInfo[playerid][pAuthed] = 1;
			SetRadioChannel(playerid, channelid);
			return 1;
		}

		else if (channelid == 912 && IsPlayerFactionMedic(playerid))
		{
			SendRadioMsg(playerid, "Frekans deðiþtirildi [CH: %i]", channelid);
			PlayerInfo[playerid][pAuthed] = 1;
			SetRadioChannel(playerid, channelid);
			return 1;
		}

		else if (channelid == 998 && IsPlayerFactionFire(playerid))
		{
			SendRadioMsg(playerid, "Frekans deðiþtirildi [CH: %i]", channelid);
			PlayerInfo[playerid][pAuthed] = 1;
			SetRadioChannel(playerid, channelid);
			return 1;
		}

		PlayerInfo[playerid][pAuthed] = 0;
		SetRadioChannel(playerid, channelid);
		SendRadioMsg(playerid, "Frekans deðiþtirildi [CH: %i]", channelid);
		SendHelpMessage(playerid, "Kanala giriþ için /auth komutunu kullanýn.");
		return 1;
	}

	else if (CompareStrings(option, "ayril"))
	{
		if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsiziniz yok.");
		if (!GetPlayerChannel(playerid))				return SendErrorMessage(playerid, "Herhangi bir frekansa baðlý deðilsiniz.");

		SendRadioMsg(playerid, "Telsiz kanalýndan ayrýldýnýz. [CH: %i]", GetPlayerChannel(playerid));
		SetRadioChannel(playerid, 0);
		PlaySound(playerid, 6400);
		return 1;
	}

	else if (CompareStrings(option, "kirala"))
	{
		if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2269.65, -74.306, 26.772))
		{
			Waypoint_Set(playerid, 2269.65, -74.306, 26.772);
			SendWarningMessage(playerid, "Þehir kütüphanesinin yakýnýnda olmalýsýnýz.");
			return 1;
		}

		new channel, pass[33];

		if (sscanf(secoption, "iS()[33]", channel, pass))	return SendHelpMessage(playerid, "/kanal kirala [kanal (1-9999)] [þifre | þifre belirlemek istemiyorsanýz boþ býrakýn]");
		if (strlen(pass) > 30)								return SendErrorMessage(playerid, "30 karakter kadar þifre koyabilirsiniz.");
		if (channel >= MAX_RADIOS || channel < 1)			return SendErrorMessage(playerid, "Frekans 1 ile  %i arasýnda olmalýdýr.", MAX_RADIOS - 1);
		if (PlayerInfo[playerid][pOwnedChannel])			return SendErrorMessage(playerid, "Zaten size ayrýlmýþ bir frekans var öncelikle ondan ayrýlýn.");
		if (ChannelExists(channel))							return SendErrorMessage(playerid, "Bu telsiz frekansýný kullanamazsýnýz. ");
		if (StringHasSymbols(pass))							return SendErrorMessage(playerid, "Þifre yalnýzca harf ve rakamlardan oluþabilir. ");
		
		new cost = 1500;

		if (GetCash(playerid) < cost)						return SendNotCash(playerid);

		new id = -1;

		for(new i = 0; i < MAX_RADIOS; i++)
		{
			if (RadiosInfo[i][radioOn]) continue;

			id = i;
			break;
		}

		if (id == -1)	return SendErrorMessage(playerid, "Bütün frekanslar meþgul, sonra tekrar deneyin.");

		GiveCash(playerid, -cost);
		SendRadioMsg(playerid, "$%i karþýlýðýnda [CH: %i] frekansýný kiraladýnýz.", channel, cost);
		SendHelpMessage(playerid, "/telsizyardim komutunu kullanarak komutlarý görebilirsiniz.");
		RadiosInfo[id][radioChannel] = channel;
		RadiosInfo[id][radioOwner] = PlayerInfo[playerid][pID];
		format(RadiosInfo[id][radioPass], 32, "%s", pass);
		AddChannelToFile(playerid, channel, pass, id);
		return 1;
	}

	else if (CompareStrings(option, "sat"))
	{
		if (!PlayerInfo[playerid][pOwnedChannel])	return SendErrorMessage(playerid, "Bu frekansý kiralayamazsýnýz.");
		
		new id = -1;

		if ((id = GetChannelID(PlayerInfo[playerid][pOwnedChannel])) == -1)
		{
			PlayerInfo[playerid][pOwnedChannel] = 0;
			SendWarningMessage(playerid, "Frekans bulunamadý");
			return 1;
		}

		new award = 750;

		GiveCash(playerid, award);
		SendRadioMsg(playerid, "[CH: %i] kanalýný $%i karþýlýðýnda sattýnýz.", RadiosInfo[id][radioChannel], award);

		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || GetPlayerChannel(i) != RadiosInfo[id][radioChannel] || i == playerid) continue;

			SendRadioMsg(i, "Baðlý olduðunuz frekans satýlmýþtýr.");
			SetRadioChannel(i, 0);
		}

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `channel` = 0, `authed` = 0 WHERE `channel` = %i", RadiosInfo[id][radioChannel]);
		mysql_tquery(dbHandle, query);
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `radios` WHERE `id` = %i", RadiosInfo[id][radioID]);
		mysql_tquery(dbHandle, query);

		RadiosInfo[id][radioOn] = 
		RadiosInfo[id][radioID] = 
		RadiosInfo[id][radioChannel] = 
		RadiosInfo[id][radioOwner] = 0;
		SetRadioChannel(playerid, 0);
		PlayerInfo[playerid][pOwnedChannel] = 0;
		return 1;
	}

	else 
	{
		SendHelpMessage(playerid, "/kanal [ayarla / ayril / kirala / sat]");
	}
	return 1;
}

alias:slotayarla("slotdegistir");
CMD:slotayarla(playerid, params[])
{
    if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");

	new slot;

	if (sscanf(params,"d",slot))			return SendHelpMessage(playerid, "/slotayarla [slot (0-100)]");
	if (slot < 0 || slot > 100)			return SendErrorMessage(playerid, "Slot 0 ile 100 arasýnda olmalýdýr");
	if (slot == GetPlayerSlot(playerid))	return SendErrorMessage(playerid, "Bu slotu zaten kullanýyorsunuz.");

	SetRadioSlot(playerid, slot);
	SendRadioMsg(playerid, "Frekans deðiþtirildi [SLOT: %i]", slot);
	return 1;
}

alias:telsizsifre("radyosifre");
CMD:telsizsifre(playerid, params[])
{
    if (!PlayerInfo[playerid][pTelsiz])		return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
	if (!GetPlayerChannel(playerid))				return SendErrorMessage(playerid, "Telsiziniz kapalý");
	if (PlayerInfo[playerid][pAuthed])				return SendErrorRadioMessage(playerid, "Bu frekansa zaten baðlanmýþsýnýz.");

	new id = -1;

	if ((id = ChannelExists(GetPlayerChannel(playerid))) == 0)	return SendErrorMessage(playerid, "Frekans bulunamadý.");

	if (CompareStrings(RadiosInfo[id][radioPass], ""))
	{
	    SendRadioMsg(playerid, "Kanala giriþ yaptýnýz %i.", GetPlayerChannel(playerid));
		PlayerInfo[playerid][pAuthed] = 1;
		PlaySound(playerid, 6400);
	    return 1;
	}

	if (isnull(params))										return SendHelpMessage(playerid, "/radyosifre [frekans þifresi]");
	if (CompareStrings(RadiosInfo[id][radioPass], params))	return SendErrorRadioMessage(playerid, "Yanlýþ þifre girdiniz.");

	SendRadioMsg(playerid, "Kanala giriþ yaptýnýz [CH: %i].", GetPlayerChannel(playerid));
	PlayerInfo[playerid][pAuthed] = 1;
	PlaySound(playerid, 6400);
	return 1;
}

alias:tsdegistir("kanalsifredegis", "telsizsifredegis");
CMD:tsdegistir(playerid, params[])
{
	if (!PlayerInfo[playerid][pOwnedChannel])	return SendErrorMessage(playerid, "Bir kanal kiralamýyorsunuz.");

    new id = -1;

	if ((id = GetChannelID(PlayerInfo[playerid][pOwnedChannel])) == -1)				return SendErrorMessage(playerid, "Frekans bulanamadý."); 
	if (isnull(params))																return SendHelpMessage(playerid, "/telsizsifre [yeni þifre | þifreyi kaldýrmak istiyorsanýz, hiçbir þey girmeyin]");
	if (strlen(params) < 1 || strlen(params) > 32)									return SendErrorMessage(playerid, "Þifre 1 ile 32 karakter arasýnda olmalýdýr.");
	if (CompareStrings(RadiosInfo[id][radioPass], "") && CompareStrings(params, ""))	return SendErrorMessage(playerid, "Frekansýnýzýn þifresi yok.");
	if (!CompareStrings(params, "") && StringHasSymbols(params))						return SendErrorMessage(playerid, "Þifrede sadece harf ve rakamlar kullanýlabilir.");

	if (CompareStrings(params, ""))	SendRadioMsg(playerid, "Frekansýnýzýn artýk bir þifresi yok.");
	else							SendRadioMsg(playerid, "Frekans þifrenizi \"%s\" olarak deðiþtirdiniz", params);

	format(RadiosInfo[id][radioPass], 33, "%s", params);
	SQL_SetString("radios", "pass", RadiosInfo[id][radioPass], RadiosInfo[id][radioID]);
	return 1;
}

alias:telsizliste("telsizuyeler", "radyouyeler");
CMD:telsizliste(playerid, params[])
{
    if (!PlayerInfo[playerid][pOwnedChannel])	return SendErrorMessage(playerid, "Bir kanal kiralamýyorsunuz.");

    new id = -1;

	if ((id = GetChannelID(PlayerInfo[playerid][pOwnedChannel])) == -1)	return SendErrorMessage(playerid, "Frekans bulunamadý");

	new dialog_header[64] = "{FFFFFF}Ýsim\t{FFFFFF}ID\n", dialog_body[2048];

	format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || GetPlayerChannel(i) != RadiosInfo[id][radioChannel]) continue;

	    format(dialog_body, sizeof(dialog_body), "%s%s\t%i\n", GetNameEx(i), i);
	}
	
	Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Frekansa baðlanan oyuncularýn listesi", dialog_body, "Kapat", "");
	return 1;
}

CMD:kanaldanat(playerid, params[])
{
    if (!PlayerInfo[playerid][pOwnedChannel])	return SendErrorMessage(playerid, "Herhangi bir kanalda deðilsiniz.");

	new userid;

	if (sscanf(params,"u", userid))	return SendHelpMessage(playerid, "/kanaldanat [ID / isim]");
	if (!IsPlayerLogged(userid))		return SendNotConnected(playerid);
	if (userid == playerid)			return SendErrorMessage(playerid, "Kendinizi frekanstan atamazsýnýz.");

    new id = -1;

	if ((id = GetChannelID(PlayerInfo[playerid][pOwnedChannel])) == -1)	return SendErrorMessage(playerid, "Frekans bulunamadý.");
	if (RadiosInfo[id][radioChannel] != GetPlayerChannel(playerid))		return SendErrorMessage(playerid, "[CH: %i] kanalýnda olmalýsýnýz.", RadiosInfo[id][radioChannel]);
	if (GetPlayerChannel(userid) != GetPlayerChannel(playerid))			return SendErrorMessage(playerid, "Belirttiðiniz oyuncu bu frekansa baðlý deðil. ");

	SendRadioMsg(playerid, "%s adlý kiþiyi kanaldan attýnýz.", GetNameEx(id));
	SendRadioMsg(userid, "Kanaldan atýldýnýz.");
	SetRadioChannel(userid, 0);
	return 1;
}

CMD:yt(playerid, params[])
{
	if (PlayerInfo[playerid][pMutedTime] > 0)		return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
	if(isnull(params)) return SendSyntaxMessage(playerid, "/yt [yazý]");
	new Float:ppos[3];
	GetPlayerPos(playerid, ppos[0], ppos[1], ppos[2]);
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pFaction] == 0) continue;
		if(!PlayerInfo[i][pOnDuty]) continue;
		if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
		if(!IsPlayerInRangeOfPoint(i, 100.0, ppos[0], ppos[1], ppos[2])) continue;
		if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(i)) continue;
	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_RADIO, "** [CH: BASE, S: 931] %s: %.*s ...", GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_RADIO, "** [CH: BASE, S: 931] %s: %s", GetNameEx(playerid), params);
	    }	
	}
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;             

		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	}
	else
	{
		SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
	}		
	printf("[YT] %s: %s", GetNameEx(playerid), params);
	return 1;
}

alias:r("telsiz", "t");
CMD:r(playerid, params[])
{
    if (PlayerInfo[playerid][pMutedTime] > 0)		return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
    if (sscanf(params, "s[144]", params)) 		return SendHelpMessage(playerid, "/r [yazý]");

	new olusumID = PlayerInfo[playerid][pFaction];

	if(OlusumTipGetir(olusumID) == FACTION_POLICE)
	{
		new tag[6], arg[25];
		if (!sscanf(params, "s[6]s[24]", tag, arg)) { 
			if (CompareStrings(tag, "10-27")) {
				new userid;
				if (sscanf(arg, "u", userid)) return SendErrorMessage(playerid, "/r 10-27 [ID / isim]");
				if (!IsPlayerLogged(userid))	 return SendClientMessageEx(playerid, COLOR_POLICECHAT, "* HQ: Sonuç bulunamadý.");

				SendClientMessageEx(playerid, COLOR_POLICECHAT, "* HQ: %s, cinsiyet: %s, yaþ: %i, ödenmemiþ cezalar: %s, aranma durumu: %s.", GetNameEx(userid), (PlayerInfo[userid][pSex]==1)?("erkek"):("kadýn"), PlayerInfo[userid][pAge], (CountPlayerTickets(userid))?("{FF6347}%i{9189EF}"):("Hayýr"), (IsPlayerWanted(userid))?("Evet"):("Hayýr"));
				SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: Dispatcher, 10-27 %s.", GetNameWithMask(playerid), GetNameEx(userid));
				return 1;
			} else if (CompareStrings(tag, "10-28")) {
				new plates[12], vehicle;
				if (sscanf(arg, "s[102]", plates))				 return SendErrorMessage(playerid, "/r 10-28 [plaka]");
				if ((vehicle = FindVehicleByPlate(plates)) == -1) return SendClientMessageEx(playerid, COLOR_POLICECHAT, "* HQ: Sonuç bulunamadý.");
				
				PlayCrimeReportForPlayer(playerid, playerid, 13);
				
				SendClientMessageEx(playerid, COLOR_POLICECHAT, "* HQ: %s [%s], sahip: %s, ödenmemiþ cezalar: %s, aranma durumu: %s.", VehicleNames[GetVehicleModel(vehicle)-400], VehicleInfo[vehicle][carPlate], VehicleInfo[vehicle][carOwner], (CountVehicleTickets(vehicle))?("%i"):("Hayýr"), (VehicleInfo[vehicle][carWanted])?("Evet"):("Hayýr"));
				SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: Dispatcher, 10-28 %s.", GetNameWithMask(playerid), VehicleInfo[vehicle][carPlate]);
				return 1;
			}
		}		
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pFaction] == 0) continue;
			if(!PlayerInfo[i][pOnDuty]) continue;
			if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;

	        if (strlen(params) > MAXLEN)
	        {
		        new pos = MAXLEN;

		        if (pos < MAXLEN-1) pos = MAXLEN;
                
				SendClientMessageEx(i, COLOR_RADIO, "** [CH: BASE, S: 911] %s: %.*s ...", GetNameEx(playerid), pos, params);
				SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);
	        }
	        else
	        {
  		        SendClientMessageEx(i, COLOR_RADIO, "** [CH: BASE, S: 911] %s: %s", GetNameEx(playerid), params);
	        }		
	    }
	    if (strlen(params) > MAXLEN)
	    {
		     new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;             

			SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		    SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	    }
	    else
	    {
			SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
	    }			
		return 1;
	}
	else if(OlusumTipGetir(olusumID) == FACTION_MEDICS || OlusumTipGetir(olusumID) == FACTION_FIRE)
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pFaction] == 0) continue;
			if(!PlayerInfo[i][pOnDuty]) continue;
			if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
			
	        if (strlen(params) > MAXLEN)
	        {
		        new pos = MAXLEN;

		        if (pos < MAXLEN-1) pos = MAXLEN;
                
				SendClientMessageEx(i, COLOR_RADIO, "** [CH: FDMD, S: 911] %s: %.*s ...", GetNameEx(playerid), pos, params);
				SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);				
	        }
	        else
	        {
  		        SendClientMessageEx(i, COLOR_RADIO, "** [CH: FDMD, S: 911] %s: %s", GetNameEx(playerid), params);
	        }
		}
	    if (strlen(params) > MAXLEN)
	    {
		     new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;             

			SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		    SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	    }
	    else
	    {
			SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
	    }					
		return 1;
	}
	else if(OlusumTipGetir(olusumID) == FACTION_CITY)
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pFaction] == 0) continue;
			if(!PlayerInfo[i][pOnDuty]) continue;
			if(PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction]) continue;
			
	        if (strlen(params) > MAXLEN)
	        {
		        new pos = MAXLEN;

		        if (pos < MAXLEN-1) pos = MAXLEN;
                
				SendClientMessageEx(i, COLOR_RADIO, "** [CH: CITY, S: 333] %s: %.*s ...", GetNameEx(playerid), pos, params);
				SendClientMessageEx(i, COLOR_RADIO, "... %s", params[pos]);			
	        }
	        else
	        {
  		        SendClientMessageEx(i, COLOR_RADIO, "** [CH: CITY, S: 333] %s: %s", GetNameEx(playerid), params);
	        }
		}
	    if (strlen(params) > MAXLEN)
	    {
		     new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;             

			SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		    SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	    }
	    else
	    {
			SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "(Telsiz) %s: %s", GetNameEx(playerid), params);
	    }					
		return 1;
	}

    new channel = GetPlayerChannel(playerid);

	if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
	if (channel == 0)							return SendErrorMessage(playerid, "Frekansta deðilsin.");
	if (!PlayerInfo[playerid][pAuthed])			return SendErrorMessage(playerid, "Frekansa giriþ yapmadýnýz.");
	
	if (sscanf(params, "s[144]", params)) 		return SendHelpMessage(playerid, "/r [yazý]");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;
		
		if (pTemp[playerid][pPatrol] && channel == 911) {
			format(mes, sizeof(mes), "** [CH: %i, S: 0] [%s] %s: %.*s ...", channel, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), pos, params);
		} else {
			format(mes, sizeof(mes), "** [CH: %i, S: 0] %s: %.*s ...", channel, GetNameEx(playerid), pos, params);
		}

		SendRadioMessage(channel, COLOR_RADIO, mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SendRadioMessage(channel, COLOR_RADIO, mes);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	}
	else
	{
	    if (pTemp[playerid][pPatrol] && channel == 911) {
			format(mes, sizeof(mes), "** [CH: %i, S: 0] [%s] %s: %s", channel, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), params);
		} else {
			format(mes, sizeof(mes), "** [CH: %i, S: 0] %s: %s", channel, GetNameEx(playerid), params);
		}
			
		SendRadioMessage(channel, COLOR_RADIO, mes);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

CMD:rr(playerid, params[])
{
	if (isnull(params))							return SendHelpMessage(playerid, "/rr [yazý]");
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

    new channel = GetPlayerChannel(playerid),
		slot = GetPlayerSlot(playerid);

	if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
	if (channel == 0)							return SendErrorRadioMessage(playerid, "Frekansta deðilsin.");
	if (PlayerInfo[playerid][pAuthed] == 0)		return SendErrorRadioMessage(playerid, "Frekansa giriþ yapmadýnýz.");

	new mes[128];
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;
		if (pos < MAXLEN-1) pos = MAXLEN;
		if (pTemp[playerid][pPatrol])
		    format(mes, sizeof(mes), "** [CH: %i, S: %i] [%s] %s: %.*s ...", channel, slot, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), pos, params);
		else
			format(mes, sizeof(mes), "** [CH: %i, S: %i] %s: %.*s ...", channel, slot, GetNameEx(playerid), pos, params);

		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);

		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	}
	else
	{
	    if (pTemp[playerid][pPatrol])
			format(mes, sizeof(mes), "** [CH: %i, S: %i] [%s] %s: %s", channel, slot, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), params);
		else
			format(mes, sizeof(mes), "** [CH: %i, S: %i] %s: %s", channel, slot, GetNameEx(playerid), params);

		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);
		SendLocalMessage(5.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s: %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

alias:rlow("rl");
CMD:rlow(playerid, params[])
{
	if (isnull(params))							return SendHelpMessage(playerid, "/rlow [text]");
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

    new channel = GetPlayerChannel(playerid);

	if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
	if (!channel)								return SendErrorMessage(playerid, "Frekansta deðilsiniz.");
	if (!PlayerInfo[playerid][pAuthed])			return SendErrorMessage(playerid, "Frekansa giriþ yapmadýnýz.");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;
		
		if (pTemp[playerid][pPatrol])	format(mes, sizeof(mes), "**[CH: %i, S: 0] [%s] %s (kýsýk ses): %.*s ...", channel, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), pos, params);
		else							format(mes, sizeof(mes), "**[CH: %i, S: 0] %s (kýsýk ses): %.*s ...", channel, GetNameEx(playerid), pos, params);

		SendRadioMessage(channel, COLOR_RADIO, mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SendRadioMessage(channel, COLOR_RADIO, mes);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s (kýsýk ses): %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	}
	else
	{
	    if (pTemp[playerid][pPatrol])	format(mes, sizeof(mes), "**[CH: %i, S: 0] [%s] %s (kýsýk ses): %s", channel, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), params);
		else							format(mes, sizeof(mes), "**[CH: %i, S: 0] %s (kýsýk ses): %s", channel, GetNameEx(playerid), params);

		SendRadioMessage(channel, COLOR_RADIO, mes);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s (kýsýk ses): %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

alias:rrlow("rrl");
CMD:rrlow(playerid, params[])
{
	if (isnull(params))							return SendHelpMessage(playerid, "/rrlow [yazý]");
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid,"Sohbetiniz sistem tarafýndan engellendi.");

    new channel = GetPlayerChannel(playerid), slot = GetPlayerSlot(playerid);

	if (!PlayerInfo[playerid][pTelsiz])	return SendErrorMessage(playerid, "Telsize sahip deðilsiniz.");
	if (!channel)								return SendErrorRadioMessage(playerid, "Frekansta deðilsiniz.");
	if (!PlayerInfo[playerid][pAuthed])			return SendErrorRadioMessage(playerid, "Frekansa giriþ yapmadýnýz.");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;
		
		if (pTemp[playerid][pPatrol])	format(mes, sizeof(mes), "**[CH: %i, S: %i] [%s] %s (kýsýk ses): %.*s ...", channel, slot, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), pos, params);
		else							format(mes, sizeof(mes), "**[CH: %i, S: %i] %s (kýsýk ses): %.*s ...", channel, slot, GetNameEx(playerid), pos, params);

		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);
		format(mes, sizeof(mes), "... %s", params[pos]);
		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s (kýsýk ses): %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", params[pos]);
	}
	else
	{
	    if (pTemp[playerid][pPatrol])	format(mes, sizeof(mes), "**[CH: %i, S: %i] [%s] %s (kýsýk ses): %s", channel, slot, PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], GetNameEx(playerid), params);
		else							format(mes, sizeof(mes), "**[CH: %i, S: %i] %s (kýsýk ses): %s", channel, slot, GetNameEx(playerid), params);

		SendSlotRadioMessage(channel, slot, COLOR_RADIO, mes);
		SendLocalMessage(2.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "(Telsiz) %s (kýsýk ses): %s", GetNameWithMask(playerid), params);
	}
	return 1;
} //î