forward LoadDynamicBanks();
forward LoadDynamicATMS();
forward OnATMInsert(AtmID);

public LoadDynamicATMS()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)	return print("[ATM] Kayit bulunamadi.");
	 

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", ATMInfo[i][atmID]);
		cache_get_value_float(i, "posx", ATMInfo[i][atmPosX]);
		cache_get_value_float(i, "posy", ATMInfo[i][atmPosY]);
		cache_get_value_float(i, "posz", ATMInfo[i][atmPosZ]);
		cache_get_value_float(i, "posrz", ATMInfo[i][atmPosRZ]);
		cache_get_value_int(i, "interior", ATMInfo[i][atmInt]);
	    cache_get_value_int(i, "vw", ATMInfo[i][atmVW]);
		ATMInfo[i][atmObject] = CreateDynamicObject(19324, ATMInfo[i][atmPosX], ATMInfo[i][atmPosY], ATMInfo[i][atmPosZ], 0.0, 0.0, ATMInfo[i][atmPosRZ], ATMInfo[i][atmVW], ATMInfo[i][atmInt]);
		total++;
	}
	printf("[ATM] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

public OnATMInsert(AtmID)
{
	return ATMInfo[AtmID][atmID] = cache_insert_id();
}

GiveBankCash(playerid, cash)
{
	return PlayerInfo[playerid][pBank] = PlayerInfo[playerid][pBank] + cash;
}

GetBankCash(playerid)
{
	return PlayerInfo[playerid][pBank];
}


BankTransfer(playerid, userid, amount)
{
    if (GetPVarInt(playerid, #just_transfer) > gettime())	return SendErrorMessage(playerid, "25 saniye bekleyiniz.");
    if (userid == playerid)									return 1;
	if (!IsPlayerLogged(userid))							return SendNotConnected(playerid);
	if (GetBankCash(playerid) < amount || amount < 1)		return SendNotCash(playerid);

    new money1 = PlayerInfo[playerid][pBank], money2 = PlayerInfo[userid][pBank];

	GiveBankCash(playerid, -amount);
	GiveBankCash(userid, amount);
	SendClientMessageEx(playerid, COLOR_YELLOWG, "[ATM] {FFFFFF}%s adlý kiþiye $%i transfer ettiniz.", GetNameEx(userid), amount);
	SendClientMessageEx(userid, COLOR_YELLOWG, "[ATM] {FFFFFF}%s adlý kiþi size $%i transfer etti", GetNameEx(playerid), amount);

	new mes[256];
    format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Bank(ONCEKI): %i | Bank(SUANKI): %i] adlý kiþi %s adlý kiþiye banka transferi yaptý. [MYSQL: %i | IP: %s | Bank(ONCEKI): %i | Bank(SUANKI): %i] -- $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money1, PlayerInfo[playerid][pBank], GetName(userid), PlayerInfo[userid][pID], q_GetPlayerIP(userid), money2, PlayerInfo[userid][pBank], amount);
    insert_log(mes, MONEY_LOG, 2, PlayerInfo[playerid][pAccID], PlayerInfo[userid][pAccID]);
    
    SetPVarInt(playerid, #just_transfer, gettime() + 25);
    SendAdmMessage("%s [ID: %i] adlý oyuncu %s [ID: %i] adlý oyuncuya banka transferi yaptý | Tutar: $%i", GetNameEx(playerid), playerid, GetNameEx(userid), userid, amount);
	return 1;
}

BankDeposit(playerid, amount)
{
    if (amount > GetCash(playerid) || amount < 1) return 1;
		
    new money = PlayerInfo[playerid][pCash], bank = PlayerInfo[playerid][pBank];

	GiveCash(playerid,-amount);
	GiveBankCash(playerid, amount);
	SendClientMessageEx(playerid, COLOR_YELLOWG, "[ATM] {FFFFFF}Banka hesabýnýza $%i para yatýrdýnýz. Yeni bakiye: $%i.", amount, GetBankCash(playerid));

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SIMDIKI): %i | Bank(ONCEKI): %i | Bank(SIMDIKI): %i] bankaya para yatýrdý -- $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), bank, PlayerInfo[playerid][pBank], amount);
    insert_log(mes, MONEY_LOG, 3, PlayerInfo[playerid][pAccID], 0);
	return 1;
}

BankWithdraw(playerid, amount)
{
    if (amount > GetBankCash(playerid) || amount < 1) return 1;
		
    new money = PlayerInfo[playerid][pCash], bank = PlayerInfo[playerid][pBank];
	
	GiveCash(playerid,amount);
	GiveBankCash(playerid, -amount);
	SendClientMessageEx(playerid, COLOR_YELLOWG, "[ATM] {FFFFFF}Banka hesabýnýzdan $%i tutarýnda para çektiniz. Yeni bakiye: $%i.", amount,GetBankCash(playerid));

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ONCEKI): %i | Money(SIMDIKI): %i | Bank(ONCEKI): %i | Bank(SIMDIKI): %i] bankadan para çekti -- $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), bank, PlayerInfo[playerid][pBank], amount);
    insert_log(mes, MONEY_LOG, 4, PlayerInfo[playerid][pAccID], 0);
	return 1;
}

Bank_Nearest(playerid)
{
 	if (!IsPlayerLogged(playerid)) return 0;

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0 || BizInfo[i][bizType] != BIZ_BANK)	continue;

		if (PlayerToPoint(20.0,playerid,BizInfo[i][bizExitX], BizInfo[i][bizExitY], BizInfo[i][bizExitZ]) && GetWorld(playerid) == BizInfo[i][bizExitVW] && GetInterior(playerid) == BizInfo[i][bizExitInt])	return 1;
	}
	return 0;
}

AddATMToFile(atmid, Float:x, Float:y, Float:z, Float: rz, interior, vw)
{
    new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `atms` (posx, posy, posz, posrz, interior, vw) VALUES (%f, %f, %f, %f, %i, %i)", x, y, z, rz, interior, vw);
	mysql_tquery(dbHandle, query, "OnATMInsert", "d", atmid);
	return 1;
}

ATM_Nearest(playerid)
{
	for(new i; i != MAX_ATMS; i++)
	{
	    if (ATMInfo[i][atmID] == 0) continue;

        if (IsPlayerInRangeOfPoint(playerid, 2.0, ATMInfo[i][atmPosX], ATMInfo[i][atmPosY], ATMInfo[i][atmPosZ]) && ATMInfo[i][atmInt] == GetInterior(playerid) && ATMInfo[i][atmVW] == GetWorld(playerid)) return i;
	}
	return -1;
}