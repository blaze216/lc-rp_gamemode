CMD:kogusagonder(playerid, params[])
{
	new userid, time;

	if (!IsPlayerFactionDocs(playerid))									return SendErrorMessage(playerid,"Hapishane memuru olmal�s�n.");
	if (sscanf(params,"uI(0)", userid, time))							return SendHelpMessage(playerid, "/kogusagonder [ID / isim] [dakika]");
	if (!PlayerInfo[playerid][pOnDuty])									return SendErrorMessage(playerid, "G�rev ba��nda olmal�s�n. ");
	if (!PlayerToPoint(50.0, playerid, -1774.4573,-488.8803,621.1163))	return SendErrorMessage(playerid, "�zolasyon ko�u�unda olmal�s�n�z.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
	if (userid == playerid)												return 1;

	if (PlayerInfo[userid][pIsolateTime])
	{
	    SendSyntaxMessage(playerid, "%s tecrit ko�u�undan taburcu oldunuz.", GetNameEx(userid));
		SendSyntaxMessage(userid, "�zolasyon ko�u�undan taburcu edildin.");
		PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));

		new mes[5];

		format(mes, sizeof(mes), "A%i", PlayerInfo[userid][pPrisoned]+100);
        UpdateDynamic3DTextLabelText(PrisonLabel[userid], 0x00FF00FF, mes);
		SendSyntaxMessage(userid, "Mahkum numaran�z - A%i(/kogusnumaram).", PlayerInfo[userid][pPrisoned]+100);
        PlayerInfo[userid][pIsolateTime] = 0;
		
		foreach(new i : Player)
		{
			if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PRISON_JAIL) continue;

			SendSyntaxMessage(i, "%s %s tecrit ko�u�undan serbest b�rak�ld� %s", GetRankName(playerid), GetNameEx(playerid), GetNameEx(userid));
		}
	    return 1;
	}

	if (time < 1 || time > 360) return SendErrorMessage(playerid, "1'den 360 dakikaya kadar s�re.");

    SendSyntaxMessage(playerid, "%s izolasyon ko�u�una koydunuz.", GetNameEx(userid));
	SendSyntaxMessage(userid, "Bir tecrit ko�u�una kondunuz.");
	PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));
	SendSyntaxMessage(userid, "Mahkum numaran�z - B%i(/kogusnumaram).", PlayerInfo[userid][pPrisoned]+100);
	PlayerInfo[userid][pIsolateTime] = 60 * time;
	PutPlayerInPrison(userid);

	foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PRISON_JAIL) continue;

		SendSyntaxMessage(i, "%s %s, %s adl� ki�iyi ko�u�a ald�.", GetRankName(playerid), GetNameEx(playerid), GetNameEx(userid));
	}
	return 1;
}

CMD:serbestbirak(playerid, params[])
{
	new userid;

	if (!IsPlayerFactionDocs(playerid))									return SendErrorMessage(playerid, "Hapishane memuru olmal�s�n.");
	if (sscanf(params,"u", userid))                                 	return SendHelpMessage(playerid, "/serbestbirak [ID / isim]");
	if (!PlayerInfo[playerid][pOnDuty])                              	return SendErrorMessage(playerid, "G�rev ba��nda olmal�s�n. ");
	if (!PlayerToPoint(30.0, playerid, 555.5505,-474.4340,915.6733)) 	return SendErrorMessage(playerid, "Hapishanede de�ilsin. ");
	if (!IsPlayerLogged(userid))                                    	return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))                    	return SendNotNearPlayer(playerid);
	if (userid == playerid)                                          	return 1;
	if (PlayerInfo[userid][pJailed] != PRISON_JAIL)                  	return SendErrorMessage(playerid, "Oyuncu hapiste de�il.");
	if (PlayerInfo[playerid][pRank] < 6)                             	return SendErrorMessage(playerid, "Bir mahkumu hapisten ��karamazs�n�z. ");

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
	SendSyntaxMessage(userid, "%s %s taraf�ndan serbest b�rak�ld�n�z.", GetRankName(playerid), GetNameEx(playerid));
	return 1;
}