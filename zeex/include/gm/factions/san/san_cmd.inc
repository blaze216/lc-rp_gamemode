CMD:yayinbaslat(playerid,params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");
	if (PlayerInfo[playerid][pSettings] & togNews)	return SendErrorMessage(playerid, "Haber akýþýný devre dýþý býraktýnýz. ");
	if (pTemp[playerid][pNews] != 0)				return SendErrorMessage(playerid, "Zaten yayýndasýn. Yayýndan çýkmak için /yayinbitir kullanýn. ");

	pTemp[playerid][pNews] = 1;
	SendSyntaxMessage(playerid,"Yayýný baþlattýnýz, artýk yazýlarýnýz haber olarak gidecek. Kapatmak için: /yayinbitir");
	return 1;
}

CMD:yayinbitir(playerid,params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");
	if (pTemp[playerid][pNews] == 0)	return SendErrorMessage(playerid, "Yayýnda deðilsin. Canlý yayýna geçmek için /yyinbitir kullanýn. ");

	pTemp[playerid][pNews] = 0;
	SendSyntaxMessage(playerid, "Yayýný bitirdiniz.");
	return 1;
}

CMD:yayindavet(playerid, params[])
{
    if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");

	new userid;
	
	if (sscanf(params,"u",userid))								return SendHelpMessage(playerid, "/yayindavet [ID / isim]");
	if (PlayerInfo[playerid][pSettings] & togNews)				return SendErrorMessage(playerid, "Haber akýþýný devre dýþý býraktýnýz.");
	if (pTemp[playerid][pNews] == 0)							return SendErrorMessage(playerid, "Yayýnda deðilsin. Canlý yayýna geçmek için /yayinbaslat kullanýn. ");
	if (userid == playerid)										return SendErrorMessage(playerid, "Kendinizi bir röportaj için davet edemezsiniz.");
	if (!PlayerNearPlayer(3.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (pTemp[playerid][pInterviewPlayer] != INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Yayýn için davet edildiniz, lütfen biraz bekleyin veya daveti kabul edin.");
	if (pTemp[userid][pInterviewPlayer] != INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Oyuncuya bir röportaj daveti zaten gönderildi.");

    pTemp[userid][pInterviewPlayer] = playerid;
    SetPVarInt(userid, #accept_time, gettime() + 30);

    SendSyntaxMessage(playerid, "%s adlý kiþiyi yayýna davet ettiniz, lütfen bekleyin.", GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s sizi bir yayýna davet etti.", GetNameWithMask(playerid));
	SendSyntaxMessage(userid, "Daveti kabul etmek için Y tuþuna basabilirsiniz. ");
	return 1;
}

alias:yayindancikar("yayinayril", "yayindanayril");
CMD:yayindancikar(playerid, params[])
{
	if (pTemp[playerid][pInterview] != INVALID_PLAYER_ID)
	{
	    SendSyntaxMessage(playerid, "Yayýný bitirdiniz. ");
	    pTemp[playerid][pInterview] = INVALID_PLAYER_ID;
	    return 1;
	}

    if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))	return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");

	new userid;

	if (sscanf(params,"u", userid))						return SendHelpMessage(playerid, "/yayindancikar [ID / isim]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);
	if (pTemp[userid][pInterview] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Bu oyuncuyla röportaj yapmýyorsunuz. ");

    SendSyntaxMessage(playerid, "%s ile yayýný bitirdiniz.", GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s sizinle yayýný bitirdi.", GetNameWithMask(playerid));
	pTemp[userid][pInterview] = INVALID_PLAYER_ID;
	return 1;
}

CMD:basinkarti(playerid, params[])
{
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))					return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");

	if(!pTemp[playerid][pSanDuty])
	{
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s basýn kartýný takar.", GetNameWithMask(playerid));
		//SetPlayerColor(playerid, COLOUR_YELLOW);
		pTemp[playerid][pSanDuty] = true;
	} else {
		SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s basýn kartýný çýkartýr.", GetNameWithMask(playerid));
		//SetPlayerColor(playerid, COLOUR_WHITE);
		pTemp[playerid][pSanDuty] = false;
	}
	return 1;
}

alias:basingoster("basinkartigoster");
CMD:basingoster(playerid, params[])
{
	new userid;
	if (!IsPlayerFactionNews(playerid) && !IsPlayerFactionNewsOff(playerid))				return SendErrorMessage(playerid, "Herhangi bir haber þirketinde çalýþmýyorsunuz.");
	if (sscanf(params, "u", userid))														return SendHelpMessage(playerid, "/basingoster [ID / isim]");
	if (!IsPlayerLogged(userid))															return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))											return SendNotNearPlayer(playerid);

	SCM(userid, COLOUR_YELLOW, "_______________________");
	SendClientMessageEx(userid, COLOR_WHITE, "Çalýþtýðý Þirket: %s", Factions[PlayerInfo[playerid][pFaction]][fName]);
	SendClientMessageEx(userid, COLOR_WHITE, "Pozisyon: %s | Ýsim: %s", GetRankName(playerid), GetNameWithMask(playerid));
	SCM(userid, COLOUR_YELLOW, "_______________________");

	SendNearbyMessage(Range_Normal, playerid, COLOR_PURPLE, "* %s, %s adlý kiþiye basýn kartýný gösterir.", GetNameWithMask(playerid), GetNameWithMask(userid));
	return 1;
}
