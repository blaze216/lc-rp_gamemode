CMD:yayinbaslat(playerid,params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");
	if (PlayerInfo[playerid][pSettings] & togNews)	return SendErrorMessage(playerid, "Haber ak���n� devre d��� b�rakt�n�z. ");
	if (pTemp[playerid][pNews] != 0)				return SendErrorMessage(playerid, "Zaten yay�ndas�n. Yay�ndan ��kmak i�in /yayinbitir kullan�n. ");

	pTemp[playerid][pNews] = 1;
	SendSyntaxMessage(playerid,"Yay�n� ba�latt�n�z, art�k yaz�lar�n�z haber olarak gidecek. Kapatmak i�in: /yayinbitir");
	return 1;
}

CMD:yayinbitir(playerid,params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");
	if (pTemp[playerid][pNews] == 0)	return SendErrorMessage(playerid, "Yay�nda de�ilsin. Canl� yay�na ge�mek i�in /yyinbitir kullan�n. ");

	pTemp[playerid][pNews] = 0;
	SendSyntaxMessage(playerid, "Yay�n� bitirdiniz.");
	return 1;
}

CMD:yayindavet(playerid, params[])
{
    if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");

	new userid;
	
	if (sscanf(params,"u",userid))								return SendHelpMessage(playerid, "/yayindavet [ID / isim]");
	if (PlayerInfo[playerid][pSettings] & togNews)				return SendErrorMessage(playerid, "Haber ak���n� devre d��� b�rakt�n�z.");
	if (pTemp[playerid][pNews] == 0)							return SendErrorMessage(playerid, "Yay�nda de�ilsin. Canl� yay�na ge�mek i�in /yayinbaslat kullan�n. ");
	if (userid == playerid)										return SendErrorMessage(playerid, "Kendinizi bir r�portaj i�in davet edemezsiniz.");
	if (!PlayerNearPlayer(3.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (pTemp[playerid][pInterviewPlayer] != INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Yay�n i�in davet edildiniz, l�tfen biraz bekleyin veya daveti kabul edin.");
	if (pTemp[userid][pInterviewPlayer] != INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Oyuncuya bir r�portaj daveti zaten g�nderildi.");

    pTemp[userid][pInterviewPlayer] = playerid;
    SetPVarInt(userid, #accept_time, gettime() + 30);

    SendSyntaxMessage(playerid, "%s adl� ki�iyi yay�na davet ettiniz, l�tfen bekleyin.", GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s sizi bir yay�na davet etti.", GetNameWithMask(playerid));
	SendSyntaxMessage(userid, "Daveti kabul etmek i�in Y tu�una basabilirsiniz. ");
	return 1;
}

alias:yayindancikar("yayinayril", "yayindanayril");
CMD:yayindancikar(playerid, params[])
{
	if (pTemp[playerid][pInterview] != INVALID_PLAYER_ID)
	{
	    SendSyntaxMessage(playerid, "Yay�n� bitirdiniz. ");
	    pTemp[playerid][pInterview] = INVALID_PLAYER_ID;
	    return 1;
	}

    if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");

	new userid;

	if (sscanf(params,"u", userid))						return SendHelpMessage(playerid, "/yayindancikar [ID / isim]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (pTemp[userid][pInterview] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Bu oyuncuyla r�portaj yapm�yorsunuz. ");

    SendSyntaxMessage(playerid, "%s ile yay�n� bitirdiniz.", GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s sizinle yay�n� bitirdi.", GetNameWithMask(playerid));
	pTemp[userid][pInterview] = INVALID_PLAYER_ID;
	return 1;
}

CMD:basinkarti(playerid, params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))					return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");

	if(!pTemp[playerid][pSanDuty])
	{
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s bas�n kart�n� takar.", GetNameWithMask(playerid));
		//SetPlayerColor(playerid, COLOUR_YELLOW);
		pTemp[playerid][pSanDuty] = true;
	} else {
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s bas�n kart�n� ��kart�r.", GetNameWithMask(playerid));
		//SetPlayerColor(playerid, COLOUR_WHITE);
		pTemp[playerid][pSanDuty] = false;
	}
	return 1;
}

alias:basingoster("basinkartigoster");
CMD:basingoster(playerid, params[])
{
	new userid;
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))				return SendErrorMessage(playerid, "Herhangi bir haber �irketinde �al��m�yorsunuz.");
	if (sscanf(params, "u", userid))														return SendHelpMessage(playerid, "/basingoster [ID / isim]");
	if (!IsPlayerLogged(userid))															return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))											return SendNotNearPlayer(playerid);

	SCM(userid, COLOUR_YELLOW, "_______________________");
	SendClientMessageEx(userid, COLOR_WHITE, "�al��t��� �irket: %s", Factions[PlayerInfo[playerid][pFaction]][fName]);
	SendClientMessageEx(userid, COLOR_WHITE, "Pozisyon: %s | �sim: %s", GetRankName(playerid), GetNameWithMask(playerid));
	SCM(userid, COLOUR_YELLOW, "_______________________");

	SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s, %s adl� ki�iye bas�n kart�n� g�sterir.", GetNameWithMask(playerid), GetNameWithMask(userid));
	return 1;
}
