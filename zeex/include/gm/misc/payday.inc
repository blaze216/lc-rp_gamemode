#define MEVDUAT_FAIZ_ORAN (1)

PayDay(i)
{
	if (!IsPlayerLogged(i)) return 1;

	new oldbank = PlayerInfo[i][pBank], faction = PlayerInfo[i][pFaction], savings, tax_house, rent_house, debt, checks;

	if(ServerInfo[sDoublePayday]) checks = ServerInfo[sPricePayday] * 2;
	else checks = ServerInfo[sPricePayday];

	if (IsFactionLegal(faction)) checks += 150 + (PlayerInfo[i][pRank] * 50);  

	if (PlayerInfo[i][pJob] == JOB_MECHANIC)		checks += 100;	
	else if (PlayerInfo[i][pJob] == JOB_TAXI) 	checks += 100;
	
	if (PlayerInfo[i][pSavings] >= 50000 && PlayerInfo[i][pSavings] < 300000) savings = PlayerInfo[i][pSavings]*MEVDUAT_FAIZ_ORAN/100;
    PlayerInfo[i][pSavings] += savings;

	if (PlayerInfo[i][pBank] < 0)
	{
	    debt = floatround(float(checks) * 0.8);
	    PlayerInfo[i][pBank] += debt,
		checks -= debt;
	}

	new houses_tax[4] = {50, 100, 200, 400};

	for(new h; h != MAX_HOUSES; h++)
	{
	    if (HouseInfo[h][hID] == 0 || HouseInfo[h][hOwnerID] != PlayerInfo[i][pID])	continue;
		
		tax_house += houses_tax[HouseInfo[h][hClass]];
	}

	new houseid = -1;
    if (PlayerInfo[i][pRentPrice] != 0 && PlayerInfo[i][pRentKey] != 0 && (houseid = GetHouseIDByMysql(PlayerInfo[i][pRentKey])) != -1)
	{
	    rent_house += PlayerInfo[i][pRentPrice];
		HouseInfo[houseid][hCash] += PlayerInfo[i][pRentPrice];
	}
	PlayerInfo[i][pBank] -= tax_house + rent_house;

	DeletePVar(i, "BugKurtar");

	new msg[256];

    SendClientMessageEx(i, COLOR_SERVER2, "|______________LIBERTY BANK______________|");
	SendClientMessageEx(i, COLOUR_ALTO, "Hesap durumu: $%i, Ald���n�z maa�: $%i", oldbank, checks);
	if (savings) SendClientMessageEx(i, COLOUR_ALTO, "Mevduat hesab�: $%i, gelen faiz: $%i", PlayerInfo[i][pSavings], savings);
	if (rent_house) SendClientMessageEx(i, COLOUR_ALTO, "Ev kiras�: -$%i", rent_house);
	if (tax_house) SendClientMessageEx(i, COLOUR_ALTO, "Emlak vergisi: -$%i", tax_house);
	SendClientMessageEx(i, COLOUR_ALTO, "Yeni maa� hesab� bakiyeniz: $%i", PlayerInfo[i][pPayCheckMoney] + checks);
	SendClientMessageEx(i, COLOR_SERVER2, "|______________LIBERTY BANK______________|");

	SendSyntaxMessage(i, "Maa��n�z� en yak�n ATM'den �ekebilirsiniz.");

	if (debt) SendSyntaxMessage(i, "Bir miktar borcun var. Banka, borcunu �demek i�in maa��ndan kesti.");

	PlayerInfo[i][pPayDayTime] = 0;
	PlayerInfo[i][pPayCheckMoney] += checks;
	PlayerInfo[i][pHours]++;
	PlayerInfo[i][pCareer]++;

	if (PlayerInfo[i][pWepLic] && PlayerInfo[i][pWepCount] > 0) {
		PlayerInfo[i][pWepCount]--;
		if (!PlayerInfo[i][pWepCount]) SendHelpMessage(i, "Tekrar silah sat�n alabilirsiniz! (/gps)");
	}
	
	PlayerInfo[i][pExp]++;
	new expamount = (PlayerInfo[i][pLevel]+1) * LEVEL_EXP;

	if (PlayerInfo[i][pExp] >= expamount)
	{
		PlayerInfo[i][pLevel]++;
		PlaySound(i, 1052);

		format(msg, sizeof(msg), "~y~SEVIYE ATLADIN~n~~w~Yeni seviyen %i", PlayerInfo[i][pLevel]);
		GameTextForPlayer(i, msg, 5000, 1);

		SendServerMessage(i, "Seviye atlad�n�z!");

		PlayerInfo[i][pExp] = 0;
		SetPlayerScore(i, PlayerInfo[i][pLevel]);
		
	}
	if (PlayerInfo[i][pHours] == 8)
	{
		PlaySound(i, 1052);

		SendServerMessage(i, "Art�k '�aylak' de�ilsiniz, t�m i�levlerinizi kullanabilirsiniz. ");
		SendServerMessage(i, "Hesab�n�za eklenen para: $%i, maa��n�zla beraber bankadan �ekebilirsiniz.", SERVER_BONUS);

		PlayerInfo[i][pPayCheckMoney] += SERVER_BONUS;
	}

	if (PlayerInfo[i][pForbid] > 0) 
	{
		PlayerInfo[i][pForbid]--;
		SQL_SetInteger("users", "Forbid", PlayerInfo[i][pForbid], PlayerInfo[i][pID]);

		if (PlayerInfo[i][pForbid] == 0)
			SendClientMessage(i, COLOR_ORANGE, "[ ! ] {FFFFFF}Silah kullanma yasa�� sona erdi, �imdi tekrar kullanabilirsiniz.");

		Save_User(i);
	}
	return 1;
}