CMD:kogusagonder(playerid, params[])
{
	new userid, time;

	if (!IsPlayerFactionDocs(playerid))									return SendErrorMessage(playerid,"Hapishane memuru olmalýsýn.");
	if (sscanf(params,"uI(0)", userid, time))							return SendHelpMessage(playerid, "/kogusagonder [ID / isim] [dakika]");
	if (!PlayerInfo[playerid][pOnDuty])									return SendErrorMessage(playerid, "Görev baþýnda olmalýsýn. ");
	if (!PlayerToPoint(50.0, playerid, -1774.4573,-488.8803,621.1163))	return SendErrorMessage(playerid, "Ýzolasyon koðuþunda olmalýsýnýz.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
	if (userid == playerid)												return 1;

	if (PlayerInfo[userid][pIsolateTime])
	{
	    SendSyntaxMessage(playerid, "%s tecrit koðuþundan taburcu oldunuz.", GetNameEx(userid));
		SendSyntaxMessage(userid, "Ýzolasyon koðuþundan taburcu edildin.");
		PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));

		new mes[5];

		format(mes, sizeof(mes), "A%i", PlayerInfo[userid][pPrisoned]+100);
        UpdateDynamic3DTextLabelText(PrisonLabel[userid], 0x00FF00FF, mes);
		SendSyntaxMessage(userid, "Mahkum numaranýz - A%i(/kogusnumaram).", PlayerInfo[userid][pPrisoned]+100);
        PlayerInfo[userid][pIsolateTime] = 0;
		
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PRISON_JAIL) continue;

			SendSyntaxMessage(i, "%s %s tecrit koðuþundan serbest býrakýldý %s", GetRankName(playerid), GetNameEx(playerid), GetNameEx(userid));
		}
	    return 1;
	}

	if (time < 1 || time > 360) return SendErrorMessage(playerid, "1'den 360 dakikaya kadar süre.");

    SendSyntaxMessage(playerid, "%s izolasyon koðuþuna koydunuz.", GetNameEx(userid));
	SendSyntaxMessage(userid, "Bir tecrit koðuþuna kondunuz.");
	PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));
	SendSyntaxMessage(userid, "Mahkum numaranýz - B%i(/kogusnumaram).", PlayerInfo[userid][pPrisoned]+100);
	PlayerInfo[userid][pIsolateTime] = 60 * time;
	PutPlayerInPrison(userid);

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PRISON_JAIL) continue;

		SendSyntaxMessage(i, "%s %s, %s adlý kiþiyi koðuþa aldý.", GetRankName(playerid), GetNameEx(playerid), GetNameEx(userid));
	}
	return 1;
}

CMD:serbestbirak(playerid, params[])
{
	new userid;

	if (!IsPlayerFactionDocs(playerid))									return SendErrorMessage(playerid, "Hapishane memuru olmalýsýn.");
	if (sscanf(params,"u", userid))                                 	return SendHelpMessage(playerid, "/serbestbirak [ID / isim]");
	if (!PlayerInfo[playerid][pOnDuty])                              	return SendErrorMessage(playerid, "Görev baþýnda olmalýsýn. ");
	if (!PlayerToPoint(30.0, playerid, 555.5505,-474.4340,915.6733)) 	return SendErrorMessage(playerid, "Hapishanede deðilsin. ");
	if (!IsPlayerLogged(userid))                                    	return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))                    	return SendNotNearPlayer(playerid);
	if (userid == playerid)                                          	return 1;
	if (PlayerInfo[userid][pJailed] != PRISON_JAIL)                  	return SendErrorMessage(playerid, "Oyuncu hapiste deðil.");
	if (PlayerInfo[playerid][pRank] < 6)                             	return SendErrorMessage(playerid, "Bir mahkumu hapisten çýkaramazsýnýz. ");

	SetPlayerPosEx(userid, 785.9385,-868.3475,35.3712);
	SetInterior(userid, 0);
	SetWorld(userid, 0);
	PlayerInfo[userid][pIsolateTime] = 0;
	PlayerInfo[userid][pJailTime] = 0;
	PlayerInfo[userid][pJailed] = 0;

	if (IsValidDynamic3DTextLabel(PrisonLabel[userid]))
	{
		DestroyDynamic3DTextLabel(PrisonLabel[userid]);
  		PrisonLabel[userid] = Text3D:INVALID_3DTEXT_ID;
	}

	GameTextForPlayer(userid,"~g~SERBEST BIRAKILDINIZ~n~~w~IYI BIRISI OLMAYA CALISIN",5000,1);
	SendSyntaxMessage(userid, "%s %s tarafýndan serbest býrakýldýnýz.", GetRankName(playerid), GetNameEx(playerid));
	return 1;
}