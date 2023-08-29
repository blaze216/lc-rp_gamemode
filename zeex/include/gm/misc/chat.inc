alias:pm("om", "ozelmesaj");
CMD:pm(playerid, params[])
{
	new userid, text[128];

	if (PlayerInfo[playerid][pMutedTime] > 0)								return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
	if (sscanf(params, "us[128]", userid, text))							return SendHelpMessage(playerid, "/pm [ID / isim] [yazý]");
	if (!IsPlayerLogged(userid))											return SendNotConnected(playerid);
    if (userid == playerid)													return SendErrorMessage(playerid, "Kendinize PM gönderemezsiniz.");
	if (PlayerInfo[playerid][pSettings] & togPM)							return SendErrorMessage(playerid, "Mesaj atmak için mesaj almanýzý etkinleþtirin.");
	if (!IsAdminDuty(playerid) && !IsTesterDuty(playerid) && (PlayerInfo[userid][pSettings] & togPM))	return SendErrorMessage(playerid, "Bu oyuncu özel mesaj almayý kapatmýþ.");
	if (people_blocking[userid][playerid] == 1)							 	return SendErrorMessage(playerid, "Oyuncu sizi PM kara listesine eklemiþ, mesaj atamazsýnýz.");

	SendPMToPlayer(playerid, userid, text);

	SpectatorMessage(playerid, sprintf("(PM gönderdi) %s (%d): %s", GetNameEx(userid), userid, text));
	SpectatorMessage(userid, sprintf("(PM geldi) %s (%d): %s", GetNameEx(playerid), playerid, text));

    SetPVarInt(playerid, PVAR_LASTPM_ISACTIVE, 1);
    SetPVarInt(playerid, PVAR_LASTPM_ID, userid);	
	SetPVarInt(userid, PVAR_LASTPM_ID, playerid);	
	return 1;
}

alias:re("reply");
CMD:re(playerid, params[])
{
    if(!GetPVarInt(playerid, PVAR_LASTPM_ISACTIVE))
        return SendErrorMessage(playerid, "Henüz mesaj gönderdiðiniz birisi yok.");

    new message[144];

    if(sscanf(params, "s[144]", message))
        return SendHelpMessage(playerid, "/re [son mesaj gönderilen kiþiye gönderilecek mesaj]");

    SendPMToPlayer(playerid, GetPVarInt(playerid, PVAR_LASTPM_ID), message);

    return 1;
}

alias:ooc("o");
CMD:ooc(playerid, params[])
{
	if (PlayerInfo[playerid][pSettings] & togOOC)	return SendErrorMessage(playerid, "OOC sohbetinizi etkinleþtirmelisiniz.");
	if (PlayerInfo[playerid][pMutedTime] > 0)		return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
	if ((noooc) && !CheckAdmin(playerid, ADMIN_LEVEL_1))			return SendNotAdmin(playerid);
	if (isnull(params))								return SendHelpMessage(playerid, "/ooc [yazý]");

	new mes[128];

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(mes, sizeof(mes), "(( {a92626}%s{D6D6D6}: %.*s ... ))", GetAccName(playerid), pos, params);
		OOCMSG(COLOUR_ALTO,mes);
		format(mes, sizeof(mes), "(( ... %s ))", params[pos]);
		OOCMSG(COLOUR_ALTO,mes);
	}
	else
	{
		format(mes, sizeof(mes), "(( {a92626}%s{D6D6D6}: %s ))", GetAccName(playerid), params);
		OOCMSG(COLOUR_ALTO, mes);
	}
	return 1;
}

CMD:ame(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2) return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (isnull(params))						 return SendHelpMessage(playerid, "/ame [emote]");

	new mes[128];
	format(mes, sizeof(mes), "* %s %s", GetNameWithMask(playerid), params);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 10000);

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendClientMessageEx(playerid, COLOR_PURPLE, "> %s %.*s ...", GetNameWithMask(playerid), pos, params);
		SendClientMessageEx(playerid, COLOR_PURPLE, "... %s", params[pos]);
	}
	else
	{
  		SendClientMessageEx(playerid, COLOR_PURPLE, "> %s %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

CMD:ado(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2) return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (isnull(params))						 return SendHelpMessage(playerid, "/ado [durum]");
	
	new mes[128];
	format(mes, sizeof(mes), "* %s (( %s ))", params, GetNameWithMask(playerid));
	SetPlayerChatBubble(playerid, mes, COLOUR_VISTABLUE, 20.0, 10000);

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "> %.*s ...", pos, params);
		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "... %s (( %s ))", params[pos], GetNameWithMask(playerid));
	} else {
		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "> %s (( %s ))", params, GetNameWithMask(playerid));
	}
	return 1;
}

CMD:sme(playerid, params[])
{
	new seconds, emote[128];
	if (PlayerInfo[playerid][pInjured] == 2) return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (sscanf(params, "dS()[128]", seconds, emote)){
		return SendHelpMessage(playerid, "/sme [saniye %d-%d] [emote]", MIN_EMOTE_SECONDS, MAX_EMOTE_SECONDS);
	}
	if(seconds < MIN_EMOTE_SECONDS || seconds > MAX_EMOTE_SECONDS){
		return SendErrorMessage(playerid, "Geçersiz saniye girdiniz.");
	}
	if(seconds > MIN_EMOTE_SECONDS && !strlen(emote)){
		return SendHelpMessage(playerid, "/sme [saniye %d-%d] [emote]", MIN_EMOTE_SECONDS, MAX_EMOTE_SECONDS);
	}
	new bubblesecon = seconds * 1000;

	new mes[128];
	format(mes, sizeof(mes), "* %s %s", GetNameWithMask(playerid), emote);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, bubblesecon);

	if (strlen(emote) > MAXLEN){
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendClientMessageEx(playerid, COLOR_PURPLE, "> %s %.*s ...", GetNameWithMask(playerid), pos, emote);
		SendClientMessageEx(playerid, COLOR_PURPLE, "... %s", emote[pos]);
	} else {
		SendClientMessageEx(playerid, COLOR_PURPLE, "> %s %s", GetNameWithMask(playerid), emote);
	}
	return 1;
}

CMD:sdo(playerid, params[])
{
	new seconds, emote[128];
	if (PlayerInfo[playerid][pInjured] == 2) return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (sscanf(params, "dS()[128]", seconds, emote)){
		return SendHelpMessage(playerid, "/sdo [saniye %d-%d] [durum]", MIN_EMOTE_SECONDS, MAX_EMOTE_SECONDS);
	}
	if(seconds < MIN_EMOTE_SECONDS || seconds > MAX_EMOTE_SECONDS){
		return SendErrorMessage(playerid, "Geçersiz saniye girdiniz.");
	}
	if(seconds > MIN_EMOTE_SECONDS && !strlen(emote)){
		return SendHelpMessage(playerid, "/sdo [saniye %d-%d] [emote]", MIN_EMOTE_SECONDS, MAX_EMOTE_SECONDS);
	}
	new bubblesecon = seconds * 1000;

	new mes[128];
	format(mes, sizeof(mes), "* %s", emote);
	SetPlayerChatBubble(playerid, mes, COLOUR_VISTABLUE, 20.0, bubblesecon);

	if (strlen(emote) > MAXLEN){
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "> %.*s ...", pos, emote);
		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "... %s", emote[pos]);
	} else {
		SendClientMessageEx(playerid, COLOUR_VISTABLUE, "> %s", emote);
	}
	return 1;
}

CMD:server_ame(playerid, params[])
{
	new mes[128];
	format(mes, sizeof(mes), "* %s %s", GetNameWithMask(playerid), params);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 10000);

	return 1;
}

CMD:konus(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken konuþamazsýnýz.");
	if (isnull(params))							return SendHelpMessage(playerid, "/konus [yazý]");
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s: %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s: ... %s", GetNameWithMask(playerid), params[pos]);
	}
	else
	{
		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s: %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

CMD:uyruk(playerid){

	SendServerMessage(playerid, "%s, %i", GetOriginName(PlayerInfo[playerid][pOrigin]), PlayerInfo[playerid][pOrigin]);
	return 1;
}

CMD:e(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken konuþamazsýnýz.");
	if (isnull(params))							return SendHelpMessage(playerid, "/e [yazý]");
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

	new mes[128];
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1)	pos = MAXLEN;

		if (maskOn{playerid})	format(mes, sizeof(mes), "%s (%s): %.*s ...", GetNameWithMask(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin]), pos, params);
		else 					format(mes, sizeof(mes), "%s (%s): %.*s ...", GetNameEx(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin]), pos, params);

		ProxDetectorLanguage(Range_Normal, playerid, mes, COLOUR_ALTO, PlayerInfo[playerid][pOrigin]);

		if (maskOn{playerid})	format(mes, sizeof(mes), "... %s", params[pos]);
		else					format(mes, sizeof(mes), "... %s", params[pos]);

		ProxDetectorLanguage(Range_Normal, playerid, mes, COLOUR_ALTO, PlayerInfo[playerid][pOrigin]);
	}
	else 
	{
		if (maskOn{playerid})	format(mes, sizeof(mes), "%s (%s): %s", GetNameWithMask(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin]), params);
		else					format(mes, sizeof(mes), "%s (%s): %s", GetNameEx(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin]), params);

		ProxDetectorLanguage(Range_Normal, playerid, mes, COLOUR_ALTO, PlayerInfo[playerid][pOrigin]);
	}
	return 1;

}

CMD:my(playerid, params[])
{
	if (isnull(params))	return SendHelpMessage(playerid, "/my [açýklama]");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-3-strlen(GetNameWithMask(playerid))) pos = MAXLEN;

		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s %.*s ...", GetNameWithMask(playerid), pos, params);
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* ... %s", GetNameWithMask(playerid), params[pos]);
	}
	else
	{
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s %s", GetNameWithMask(playerid), params);
	}
	return 1;
}

#define MAX_ACTION_LENGTH (144)
CMD:aksiyon(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");

    if (GetPVarInt(playerid, "3DLabel"))
    {
		SendSyntaxMessage(playerid, "Açýklamanýz kaldýrýldý.");
		DestroyDynamic3DTextLabel(Text3D:GetPVarInt(playerid, "3DLabel"));
		DeletePVar(playerid, "3DLabel");
		return 1;
    }

    if (sscanf(params, "s[144]", params[0])) 	return SendHelpMessage(playerid, "/aksiyon [yazý]");
    if (strlen(params[0]) > MAX_ACTION_LENGTH)	return SendErrorMessage(playerid, "Girilen yazý maksimum %s karakter olmalýdýr!", MAX_ACTION_LENGTH);

    new Float:p[3];    
	GetPlayerPos(playerid, p[0], p[1], p[2]);
    
	new string[MAX_PLAYER_NAME + MAX_ACTION_LENGTH + (13)];
	format(string, sizeof(string), "%s \n(( %s [ID:%i] ))", params[0], GetNameEx(playerid), playerid);
    SetPVarInt(playerid, "3DLabel", _:CreateDynamic3DTextLabel(string, 0xC2A2DAFF, p[0], p[1], p[2], 35.0));
    
	AMSG(COLOR_LIGHTRED, "[LOG] %s [ID:%i] adlý kullanýcý bir action oluþturdu: \"%s\".", GetNameEx(playerid), playerid, params[0]);
    return 1;
}

CMD:me(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (isnull(params))						return SendHelpMessage(playerid, "/me [emote]");
    
	new Float:range;
	if(GetPlayerVirtualWorld(playerid) > 0) range = 8.0;
	else range = 15.0;
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* %s %.*s ...", GetNameWithMask(playerid), pos, params);
		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* ... %s", params[pos], GetNameWithMask(playerid));
	}
	else
	{
		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* %s %s", GetNameWithMask(playerid), params);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) Emote Verdi: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

CMD:melow(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken herhangi bir iþlem yapamazsýnýz.");
	if (isnull(params))						return SendHelpMessage(playerid, "/melow [emote]");
    
	new Float:range;
	if(GetPlayerVirtualWorld(playerid) > 0) range = 4.0;
	else range = 7.5;
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* %s %.*s ...", GetNameWithMask(playerid), pos, params);
		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* ... %s", params[pos], GetNameWithMask(playerid));
	}
	else
	{
		SendNearbyMessage(range, playerid, COLOR_PURPLE, "* %s %s", GetNameWithMask(playerid), params);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) Emote-Low Verdi: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

CMD:dolow(playerid, params[])
{
	if (isnull(params))	return SendHelpMessage(playerid, "/dolow [durum]");

	new Float:range, message[144], message2[144];
	if(GetPlayerVirtualWorld(playerid) > 0) range = 4.0;
	else range = 7.5;
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(message,sizeof(message),"* %.*s ...", pos, params, GetNameWithMask(playerid));
        DO_Emote(range, playerid, message);
		format(message2,sizeof(message2),"... %s (( %s ))", params[pos], GetNameWithMask(playerid));
		DO_Emote(range, playerid, message2);
	}
	else
	{
		format(message,sizeof(message),"* %s (( %s ))", params, GetNameWithMask(playerid));
		DO_Emote(range, playerid, message);		
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) Do-Low Verdi: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

CMD:do(playerid, params[])
{
	if (isnull(params))	return SendHelpMessage(playerid, "/do [durum]");

	new Float:range, message[144], message2[144];
	if(GetPlayerVirtualWorld(playerid) > 0) range = 8.0;
	else range = 15.0;
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		format(message,sizeof(message),"* %.*s ...", pos, params, GetNameWithMask(playerid));
        DO_Emote(range, playerid, message);
		format(message2,sizeof(message2),"... %s (( %s ))", params[pos], GetNameWithMask(playerid));
		DO_Emote(range, playerid, message2);
	}
	else
	{
		format(message,sizeof(message),"* %s (( %s ))", params, GetNameWithMask(playerid));
		DO_Emote(range, playerid, message);		
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) Do Verdi: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

CMD:b(playerid,params[])
{
	if (isnull(params)) 						return SendHelpMessage(playerid, "/b [OOC sohbet yazýsý]");
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

	new mes[128];
	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		if (maskOn{playerid})			format(mes, sizeof(mes), "(( [OOC] %s: %.*s ... ))", GetNameWithMask(playerid), pos, params);
		else if (PlayerInfo[playerid][pAdmin] > 0 && IsAdminDuty(playerid)) 	format(mes, sizeof(mes), "(( [OOC] {a92626}%s{AFAFAF}: %.*s ... ))", GetPlayerNameEx(playerid), pos, params);
		else 							format(mes, sizeof(mes), "(( [OOC] %s: %.*s ... ))", GetNameEx(playerid), pos, params);

		ProxDetectorOutOfCharacter(20.0, playerid, mes, COLOUR_ALTO);

		if (maskOn{playerid}) 			format(mes, sizeof(mes), "(( ... %s ))", params[pos]);
		else if (PlayerInfo[playerid][pAdmin] > 0 && IsAdminDuty(playerid)) 	format(mes, sizeof(mes), "(( ... %s ))", params[pos]);
		else 							format(mes, sizeof(mes), "(( ... %s ))", params[pos]);

		ProxDetectorOutOfCharacter(20.0, playerid, mes, COLOUR_ALTO);
	}
	else
	{
		if (maskOn{playerid}) 			format(mes, sizeof(mes), "(( [OOC] %s: %s ))", GetNameWithMask(playerid), params);
		else if (PlayerInfo[playerid][pAdmin] > 0 && IsAdminDuty(playerid)) 	format(mes, sizeof(mes), "(( [OOC] {a92626}%s{AFAFAF}: %s ))", GetPlayerNameEx(playerid), params);
		else 							format(mes, sizeof(mes), "(( [OOC] %s: %s ))", GetNameEx(playerid), params);

		ProxDetectorOutOfCharacter(20.0, playerid, mes, COLOUR_ALTO);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) OOC Chat: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}


alias:low("l", "c");
CMD:low(playerid,params[])
{
    if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid,"Yaralýyken konuþamazsýnýz.");
	if (isnull(params))							return SendHelpMessage(playerid, "/low [yazý]");
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

    if (IsPlayerInAnyVehicle(playerid) && !IsADontWindow(GetPlayerVehicleID(playerid)) && IsWindowsClose(GetPlayerVehicleID(playerid)))	
		return SendErrorMessage(playerid, "Normal chati kullanýn, sizi kimse duyamaz.");

	if (strlen(params) > MAXLEN)
 	{
  		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2)
    	{
			SendLocalMessage(4.5, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "%s kýsýk ses (telefon): %.*s ...", GetNameWithMask(playerid), MAXLEN, params);
			SendPhoneMessageEx(pTemp[playerid][pCallLine], COLOR_YELLOWG, "%s kýsýk ses (telefon): %.*s ...", GetNameWithMask(playerid), MAXLEN, params);
			SendLocalMessage(4.5, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "... %s", params[MAXLEN]);
			SendPhoneMessageEx(pTemp[playerid][pCallLine], COLOR_YELLOWG, "... %s", params[MAXLEN]);
   		}
     	else
      	{
			SendLocalMessage(4.5, playerid,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "%s (kýsýk ses): %.*s ...", GetNameWithMask(playerid), MAXLEN, params);
			SendLocalMessage(4.5, playerid,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3, "... %s", params[MAXLEN]);
		}
	}

	else
	{
	    if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) 
     	{
			SendLocalMessage(4.5, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s kýsýk ses (telefon): %s", GetNameWithMask(playerid), params);
            SendPhoneMessageEx(pTemp[playerid][pCallLine], COLOR_YELLOWG, "%s kýsýk ses (telefon): %s", GetNameWithMask(playerid), params);
	   	}
     	else
		{
			SendLocalMessage(4.5, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (kýsýk ses): %s", GetNameWithMask(playerid), params);
		}
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) kýsýk sesle konuþtu: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

alias:whisper("w", "fisilda");
CMD:whisper(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] == 2)	return SCM(playerid, COLOR_GREY, "Yaralýyken konuþamazsýnýz.");

	new userid, text[128];

	if (sscanf(params,"us[128]", userid, text))		return SendHelpMessage(playerid, "(/w)hisper [ID / isim] [yazý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (PlayerInfo[playerid][pMutedTime] > 0)		return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
    if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (userid == playerid)							return SendErrorMessage(playerid, "Kendinize fýsýldayamazsýnýz.");

	new mes[128];

	format(mes, sizeof(mes), "%s, %s adlý kiþinin kulaðýna bir þeyler fýsýldar.", GetNameWithMask(playerid), GetNameWithMask(userid));
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 15.0, 10000);
	
	SendClientMessageEx(userid, COLOUR_TURBO, "%s kiþisi fýsýldadý: %s", GetNameWithMask(playerid), text);
	SendClientMessageEx(playerid,  COLOUR_TURBO, "%s kiþisine fýsýldadý: %s", GetNameWithMask(userid), text);

	SpectatorMessage(playerid, sprintf("%s kiþisine fýsýladý: %s", GetNameEx(userid), text));
	SpectatorMessage(userid, sprintf("%s kiþisi fýsýladý: %s", GetNameEx(playerid), text));	
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) fýsýldadý: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

CMD:to(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] == 2)	return SCM(playerid, COLOR_GREY, "Yaralýyken konuþamazsýnýz.");

	new userid, text[128];

	if (sscanf(params,"us[128]", userid, text))		return SendHelpMessage(playerid, "/to [ID / isim] [yazý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (PlayerInfo[playerid][pMutedTime] > 0)		return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
    if (!PlayerNearPlayer(10.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (userid == playerid)							return SendErrorMessage(playerid, "Kendinize mesaj gönderemezsiniz.");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s seslenir (%s): %.*s ...", GetNameWithMask(playerid), GetNameWithMask(userid), pos, text);
		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s seslenir (%s): ... %s", GetNameWithMask(playerid), GetNameWithMask(userid), text[pos]);
	}
	else
	{
		SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s seslenir (%s): %s", GetNameWithMask(playerid), GetNameWithMask(userid), text);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) PM'e karþýlýk verdi: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

alias:cw("carwhisper");
CMD:cw(playerid, params[])
{
	if (isnull(params))							return SendHelpMessage(playerid, "/cw [yazý]");
	if (!IsPlayerInAnyVehicle(playerid))			return SendNotInVehicle(playerid);
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

	new vehicle = GetPlayerVehicleID(playerid);

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicle)) continue;

		if (strlen(params) > MAXLEN)
		{
		    new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendClientMessageEx(i,  COLOR_YELLOWG, "%s (araç içi): %.*s ...", GetNameWithMask(playerid), pos, params);
			SendClientMessageEx(i,  COLOR_YELLOWG, "... %s", params[pos]);
		}
		else 
		{
			SendClientMessageEx(i,  COLOR_YELLOWG, "%s (araç içi): %s", GetNameWithMask(playerid), params);
		}

		SpectatorMessage(i, sprintf("%s (araç içi): %s", GetNameEx(playerid)));
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) araçta fýsýldadý: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}
CMD:carblow(playerid, params[])
{
	if (isnull(params))							return SendHelpMessage(playerid, "/carblow [yazý]");
	if (!IsPlayerInAnyVehicle(playerid))		return SendNotInVehicle(playerid);
	if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");

	new vehicleid = GetPlayerVehicleID(playerid);

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicleid)) continue;

		if (strlen(params) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			SendClientMessageEx(i, COLOUR_ALTO, "[OOC] %s (araç içi): %.*s ...", GetNameWithMask(playerid), pos, params);
			SendClientMessageEx(i, COLOUR_ALTO, "... %s", params[pos]);
		} else {
			SendClientMessageEx(i, COLOUR_ALTO, "[OOC] %s (araç içi): %s", GetNameWithMask(playerid), params);
		}
	}
	return 1;
}

CMD:masasandalye(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");
			
	if(IsPlayerConnected(playerid))
	{
	    new mstring[64];

		if(sscanf(params, "s[64]", mstring)){
			SendHelpMessage(playerid, "/masasandalye [fonksiyon]");
			SendHelpMessage(playerid, "Geçerli fonksiyonlar: kur, kaldir");

			return 1;
		}
		if(!strcmp(mstring, "kur", true))
    	{
			if(IsPlayerInAnyVehicle(playerid))					return SendErrorMessage(playerid, "Bu komutu araç içerisinde kullanamazsýnýz.");
			if(IsValidDynamicObject(sandalyeobje[playerid]))	return SendErrorMessage(playerid, "Kurulu masa sandalyeniz bulunuyor.");

			new Float:px, Float:py, Float:pz, Float:pangle;

			GetPlayerPos(playerid, px, py, pz);
			GetPlayerFacingAngle(playerid, pangle);

			sandalyeobje[playerid] = CreateDynamicObject(1825, px, py, pz-1, 0, 0, pangle, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			SendServerMessage(playerid, "Masa sandalye kurdunuz.");

			new string[128];
			format(string, sizeof(string), "(%d)", playerid);
			SandalyeLabel[playerid] = CreateDynamic3DTextLabel(string, -1, px, py, pz-0.4, 10, .worldid=GetPlayerVirtualWorld(playerid),.interiorid=GetPlayerInterior(playerid));

			Streamer_Update(playerid);
		} else if(!strcmp(mstring, "kaldir", true)){
			if(IsValidDynamicObject(sandalyeobje[playerid])){
				DestroyDynamicObject(sandalyeobje[playerid]);
				DestroyDynamic3DTextLabel(SandalyeLabel[playerid]);
				Streamer_Update(playerid);
				SendServerMessage(playerid, "Masa sandalyeyi kaldýrdýnýz.");
			} else {
				SendErrorMessage(playerid, "Kurulu masa sandalyeniz yok.");
			}
		}
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) masa sandalye oluþturdu. %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
	return 1;
}

CMD:sandalye(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	if(IsPlayerConnected(playerid))
	{
	    new mstring[64];

		if(sscanf(params, "s[64]", mstring)){
			SendHelpMessage(playerid, "/sandalye [fonksiyon]");
			SendHelpMessage(playerid, "Geçerli fonksiyonlar: kur, kaldir");

			return 1;
		}
		if(!strcmp(mstring, "kur", true))
    	{
			if(IsPlayerInAnyVehicle(playerid))					return SendErrorMessage(playerid, "Bu komutu araç içerisinde kullanamazsýnýz.");
			if(IsValidDynamicObject(teksandalyeobje[playerid]))	return SendErrorMessage(playerid, "Kurulu sandalyeniz bulunuyor.");

			new Float:px, Float:py, Float:pz, Float:pangle;

			GetPlayerPos(playerid, px, py, pz);
			GetPlayerFacingAngle(playerid, pangle);

			teksandalyeobje[playerid] = CreateDynamicObject(1720, px, py, pz-1, 0, 0, pangle, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			SendServerMessage(playerid, "Sandalye kurdunuz.");

			new string[128];
			format(string, sizeof(string), "%d", playerid);
			TekSandalyeLabel[playerid] = CreateDynamic3DTextLabel(string, -1, px, py, pz-0.4, 10, .worldid=GetPlayerVirtualWorld(playerid),.interiorid=GetPlayerInterior(playerid));

			Streamer_Update(playerid);
		} else if(!strcmp(mstring, "kaldir", true)){
			if(IsValidDynamicObject(teksandalyeobje[playerid])){
				DestroyDynamicObject(teksandalyeobje[playerid]);
				DestroyDynamic3DTextLabel(TekSandalyeLabel[playerid]);
				Streamer_Update(playerid);
				SendServerMessage(playerid, "Sandalyeyi kaldýrdýnýz.");
			} else {
				SendErrorMessage(playerid, "Sandalyeniz yok.");
			}
		}
	}
	return 1;
}

alias:dshout("ds");
CMD:dshout(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken konuþamazsýnýz.");

	new text[128];

	if (sscanf(params,"s[128]",text)) 		return SendHelpMessage(playerid, "(/ds)hout [yazý]");

	for(new i = 0; i < MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0) continue;

		if (IsPlayerOutsideHouse(playerid, i, 2.0))
		{
		    SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn içine doðru baðýrýr): %s!", GetNameWithMask(playerid), text);

   			foreach(new p : Player)
			{
				if (!IsPlayerInsideHouse(p, i)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn dýþýndan baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}

		else if (IsPlayerInsideHouse(playerid, i, 3.0))
		{
		    SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn dýþýna doðru baðýrýr): %s!", GetNameWithMask(playerid), text);

			foreach(new p : Player)
			{
				if (!IsPlayerOutsideHouse(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn içinden baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}
	}

	for(new i = 0; i < MAX_APART; i++)
	{
	    if (ApartInfo[i][aApartOn] == 0) continue;

		if (IsPlayerApartmentOutside(playerid, i, 2.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn içine doðru baðýrýr): %s!", GetNameWithMask(playerid), text);

   			foreach(new p : Player)
			{
				if (!IsPlayerApartmentInside(p, i)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn dýþýndan baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}

		else if (IsPlayerApartmentInside(playerid, i, 3.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn içine doðru baðýrýr): %s!", GetNameWithMask(playerid), text);

			foreach(new p : Player)
			{
				if (!IsPlayerApartmentOutside(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn dýþýndan baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}
	}

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0) continue;

		if (IsPlayerBizOutside(playerid, i, 2.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn içine doðru baðýrýr): %s!", GetNameWithMask(playerid), text);

   			foreach(new p : Player)
			{
				if (!IsPlayerBizInside(p, i)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn dýþýndan baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}

		else if (IsPlayerBizInside(playerid, i, 3.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOR_WHITE, "* %s (mekanýn içine doðru baðýrýrr): %s!", GetNameWithMask(playerid), text);

			foreach(new p : Player)
			{
				if (!IsPlayerBizOutside(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOR_WHITE, "* %s (mekanýn dýþýndan baðýrýr): %s!", GetNameWithMask(playerid), text);
			}
			return 1;
		}	
	}
	return 1;
}

CMD:ddo(playerid, params[])
{
	new text[128];

	if (sscanf(params,"s[128]",text)) return SendHelpMessage(playerid, "/ddo [durum] (kapý yakýnýnda olmalýsýn)");

	for(new i = 0; i < MAX_HOUSES; i++)
	{
		if (!HouseInfo[i][hID]) continue;

		if (IsPlayerOutsideHouse(playerid, i, 2.0))
		{
		    SendNearbyMessage(Range_Long, playerid, COLOR_PURPLE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			
			foreach(new p : Player)
			{
				if (!IsPlayerInsideHouse(p, i)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}

		else if (IsPlayerInsideHouse(playerid, i, 3.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			foreach(new p : Player)
			{
				if (!IsPlayerOutsideHouse(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}
	}

	for(new i = 0; i < MAX_APART; i++)
	{
		if (!ApartInfo[i][aApartOn]) continue;

		if (IsPlayerApartmentOutside(playerid, i, 2.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));

			foreach(new p : Player)
			{
				if (!IsPlayerApartmentInside(p, i)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}

		else if (IsPlayerApartmentInside(playerid, i, 3.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));

			foreach(new p : Player)
			{
				if (!IsPlayerApartmentOutside(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}
	}

	for(new i = 0; i < MAX_BIZ; i++)
	{
		if (!BizInfo[i][bizID]) continue;

		if (IsPlayerBizOutside(playerid, i, 2.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));

			foreach(new p : Player)
			{
				if (!IsPlayerBizInside(p, i)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}

		else if (IsPlayerBizInside(playerid, i, 3.0))
		{
			SendNearbyMessage(Range_Long, playerid, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));

			foreach(new p : Player)
			{
				if (!IsPlayerBizOutside(p, i, 6.0)) continue;

				SendClientMessageEx(p, COLOUR_VISTABLUE, "[KAPI] * %s (( %s ))", text,GetNameWithMask(playerid));
			}
			return 1;
		}
	}
	return 1;
}

CMD:aciklama(playerid, params[])
{
	new text[64], line;

	if (sscanf(params,"iS()[128]",line,text)) return SendHelpMessage(playerid, "/aciklama [satýr (1-2)] [yazý]");

	if (strlen(text) > PAME_MAX_LEN) return SendErrorMessage(playerid, "Karakter açýklamanýz çok fazla. (Max %i karakter)", PAME_MAX_LEN);
	if (line < 1 || line > 2) 		return SendErrorMessage(playerid, "1 =< Satýr =< 2.");

	SendHelpMessage(playerid, "/aciklama [1/2] - açýklama satýrýný kaldýrmak için (metin parametresi yok.).");
	SendHelpMessage(playerid, "/ozellik [id] - sohbette baþka bir karakterin açýklamasýný göster.");
	SendHelpMessage(playerid, "/ozellik %i - açýklamanýzý sohbette görüntüleyebilirsiniz.", playerid);

	switch(line) {
		case 1: {
			if (!strlen(text)) {
				SM1(playerid, "Satýr (1) karakter açýklamanýz kaldýrýldý.");
				format(PlayerInfo[playerid][pDescribe], PAME_MAX_LEN, "NULL");
			} else {
				SM2(playerid, "Karakter açýklama satýrý (1) deðiþtirildi. ");
				format(PlayerInfo[playerid][pDescribe], PAME_MAX_LEN, "%s", text);
			}
			SQL_SetString("users", "Desc1", PlayerInfo[playerid][pDescribe], PlayerInfo[playerid][pID]);
		}
        case 2: {
			if (!strlen(text)) {
				SM1(playerid, "Karakter açýklama satýrý (2) kaldýrýldý. ");
				format(PlayerInfo[playerid][pDescribe2], PAME_MAX_LEN, "NULL");
			} else {
				if (CompareStrings(PlayerInfo[playerid][pDescribe], "NULL")) {
					return SendErrorMessage(playerid, "1. satýrýn karakter açýklamasýný doldurmalýsýnýz.");
				}

				SM2(playerid, "2. satýrda olan karakter açýklamanýz deðiþtirildi.");
				format(PlayerInfo[playerid][pDescribe2], PAME_MAX_LEN, "%s", text);
			}
			SQL_SetString("users", "Desc2", PlayerInfo[playerid][pDescribe2], PlayerInfo[playerid][pID]);
		}
	}

	return 1;
}

CMD:ozellik(playerid, params[])
{
	new userid;

	if (sscanf(params, "u", userid))				  			return SendHelpMessage(playerid, "/ozellik [ID / isim]");
	if (!IsPlayerLogged(userid))					  			return SendNotConnected(playerid);
	if (!PlayerNearPlayer(15.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (CompareStrings(PlayerInfo[userid][pDescribe], "NULL")) 	return SendErrorMessage(playerid, "Oyuncunun açýklamasý yok!");

	if (playerid == userid) {
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "** %s %s", GetNameWithMask(userid), PlayerInfo[userid][pDescribe]);
		if (!CompareStrings(PlayerInfo[userid][pDescribe2], "NULL")) {
			SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, ".. %s **", PlayerInfo[userid][pDescribe2]);
		}
	} else {
		SendClientMessageEx(playerid, COLOR_PURPLE, "** %s %s", GetNameWithMask(userid), PlayerInfo[userid][pDescribe]);
		if (!CompareStrings(PlayerInfo[userid][pDescribe2], "NULL")) {
			SendClientMessageEx(playerid, COLOR_PURPLE, ".. %s **", PlayerInfo[userid][pDescribe2]);
		}
	}
	
	return 1;
}

alias:shout("s", "bagir");
CMD:shout(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken baðýramazsýnýz.");
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
	if (isnull(params))							return SendHelpMessage(playerid, "(/s)hout [yazý]");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendLocalMessage(Range_Long, playerid, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, "%s (baðýrýr): %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(Range_Long, playerid, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, "... %s!", params[pos]);
	}
	else
	{
		SendLocalMessage(Range_Long, playerid, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, "%s (baðýrýr): %s!", GetNameWithMask(playerid), params);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) baðýrdý: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

alias:mikrofon("mic", "mi");
CMD:mikrofon(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 2)	return SendErrorMessage(playerid, "Yaralýyken baðýramazsýnýz.");
    if (PlayerInfo[playerid][pMutedTime] > 0)	return SendErrorMessage(playerid, "Sohbetiniz sistem tarafýndan engellendi.");
	if (!pTemp[playerid][pMicPerm])        		return SendErrorMessage(playerid, "Mikrofon izniniz bulunmuyor. Helperlardan talepte bulunabilirsiniz.");
	if (isnull(params))							return SendHelpMessage(playerid, "(/mic)ikrofon [yazý]");

	if (strlen(params) > MAXLEN)
	{
		new pos = MAXLEN;

		if (pos < MAXLEN-1) pos = MAXLEN;

		SendLocalMessage(75.0, playerid, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, "%s (mikrofon): %.*s ...", GetNameWithMask(playerid), pos, params);
		SendLocalMessage(75.0, playerid, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, "... %s", params[pos]);
	}
	else
	{
		SendLocalMessage(75.0, playerid, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, COLOUR_ATLANTIS, "%s (mikrofon): %s", GetNameWithMask(playerid), params);
	}
	Log_Kaydet("loglar/roleplay.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d) mikrofondan konuþtu: %s", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], params));
	return 1;
}

OOCMSG(color,string[])
{
	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togOOC)) continue;

		SCM(i, color, string);
	}
	return 1;
}

NewsChat(color,string[])
{
	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togNews)) continue;

		SCM(i, color, string);
	}
	return 1;
}

ProxDetectorOutOfCharacter(Float:radi, playerid, string[], color)
{
	foreach(new i : Player)
	{
		if (IsPlayerLogged(i) == 0 || 0 == PlayerNearPlayer(radi, playerid, i)) continue;

		SCM(i,color,string);
	}
	return 1;
}

ProxDetectorLanguage(Float:radi, playerid, string[], color, originid)
{
	foreach(new i : Player)
	{
		if (IsPlayerLogged(i) == 0 || 0 == PlayerNearPlayer(radi, playerid, i)) continue;
		if (originid != PlayerInfo[i][pOrigin] && maskOn{playerid} && originid != 1) return SCM(i, color, sprintf("%s (%s): [? ? ? ? ?]", GetNameWithMask(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin])));
		if (originid != PlayerInfo[i][pOrigin] && !maskOn{playerid} && originid != 1) return SCM(i, color, sprintf("%s (%s): [? ? ? ? ?]", GetNameEx(playerid), GetOriginLangName(PlayerInfo[playerid][pOrigin])));

		SCM(i,color,string);
	}
	return 1;
}