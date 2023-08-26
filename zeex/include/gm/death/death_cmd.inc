alias:hasarlar("dmg", "hsrlr");
CMD:hasarlar(playerid, params[])
{
	new userid;

	if (!IsPlayerLogged(playerid))															return SendNotConnected(playerid);
	if (sscanf(params, "u", userid))														return SendHelpMessage(playerid,"/hasarlar [ID/Ad ve Soyad]");
	if (!IsPlayerConnected(userid))                 										return SendErrorMessage(playerid, "Karakter çevrimdýþý.");
	if (!PlayerNearPlayer(3.0, playerid, userid) && !CheckAdmin(playerid, ADMIN_LEVEL_1))	return SendNotNearPlayer(playerid);

	pTemp[playerid][pDialogList] = 0;

	DisplayDamages(playerid, userid);
	return 1;
}
/*
CMD:yardimet(playerid, params[])
{
	new userid;

	if (!IsPlayerLogged(playerid))				 	return SendNotConnected(playerid);
	if (sscanf(params, "u", userid))			 	return SendHelpMessage(playerid,"/yardimet [ID/Ad ve Soyad]");
	if (userid == playerid)						 	return 1;
	if (!IsPlayerConnected(userid))            	 	return SendErrorMessage(playerid, "Karakter çevrimdýþý."); //îôëàéí
	if (!PlayerNearPlayer(2.0, playerid, userid)) 	return SendNotNearPlayer(playerid);
	if (pTemp[userid][pInjuredTime]-40 > 0)		 	return SendErrorMessage(playerid, "%i saniye daha beklemelisin", pTemp[userid][pInjuredTime]-40); 
	
	StartProgress(userid, playerid, 1, 839);
	return 1;
}*/

/*
CMD:kabulolum(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] == 0) return SendErrorMessage(playerid, "Yaralý deðilsin.");

	new count = 0;
	foreach(new i : Player)
	{
		if (i == playerid) continue;
		if (GetPlayerDistanceFromPlayer(playerid, i) < 11.0) count++;
	}

	if (pTemp[playerid][pInjuredTime])
	{
		if (count) {
			SendWarningMessage(playerid, "Yakýnýnda oyuncular varsa ölümü hemen kabul edemezsin. Biraz daha beklemen gerekiyor. %i saniye.", pTemp[playerid][pInjuredTime]);
			return 1;
		}
	}

	SendSpecialMessage(playerid, "Karakteriniz öldü, yeniden doðmak için \"/tedaviol\"."); 
	PlayerInfo[playerid][pInjured] = 2;
	pTemp[playerid][pInjuredTime] = 60;
	pTemp[playerid][pInjureText] = 0;
	return 1;
}*/

CMD:tedaviol(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] == 0) return SendErrorMessage(playerid, "Henüz yaralý deðilsiniz.");
	if (pTemp[playerid][pInjuredTime]) 		return SendSpecialMessage(playerid, "Sadece %i saniye beklediniz. /tedaviol komutunu kullanabilmek için 60 saniye beklemiþ olmalýsýnýz.", 60 - pTemp[playerid][pInjuredTime]);
 
	PlayerInfo[playerid][pDeathReason] = 0;
	SQL_SetInteger("users", "deathreason", 0, PlayerInfo[playerid][pID]);
	
	if (!PlayerInfo[playerid][pPremium]) PlayerInfo[playerid][pHealth] = 50.0;
	else							  	PlayerInfo[playerid][pHealth] = 100.0;

	ResetDamages(playerid);
	StopPlayerAnims(playerid);
	UnFreezePlayer(playerid);
	SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);

	SM1(playerid, "Tedavi oldunuz ve ayaða kalktýnýz.");

	SetPlayerSkill(playerid);
	return 1;
}
