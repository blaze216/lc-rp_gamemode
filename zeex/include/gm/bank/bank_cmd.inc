CMD:hesapdurumu(playerid, params[])
{
	if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada deðilsiniz.");

	SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Banka hesabýnýzda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
    SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Birikim Hesabý: $%i", PlayerInfo[playerid][pSavings]);
	SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Maaþ Hesabý: $%i", PlayerInfo[playerid][pPayCheckMoney]);
	return 1;
}

CMD:paratransferi(playerid, params[])
{
	new userid, amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada deðilsiniz.");
	if (sscanf(params, "ud", userid, amount))
	{
		SendHelpMessage(playerid, "/paratransferi [ID/Karakter Adý] [Tutar]");
		SendSyntaxMessage(playerid,"[BANKA] Banka hesabýnýzda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

	if (userid == playerid)								return SendErrorMessage (playerid, "Kendinize para transferi yapamazsýnýz.");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (GetBankCash(playerid) < amount || amount < 1)	return SendErrorMessage (playerid, "Girdiðiniz tutar banka hesabýnýzda yok veya geçersiz bir tutar girdiniz.");

	BankTransfer(playerid, userid, amount);
	return 1;
}

CMD:parayatir(playerid, params[])
{
	new amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada deðilsiniz.");

	if (sscanf(params, "d", amount))
	{
		SendHelpMessage(playerid, "/parayatir [Tutar]");
		SendSyntaxMessage(playerid, "[BANKA] Banka hesabýnýzda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

    if (amount > GetCash(playerid) || amount < 1) return SendErrorMessage(playerid, "Girdiðiniz tutar üzerinizde yok veya geçersiz bir tutar girdiniz.");
		
	BankDeposit(playerid, amount);
	return 1;
}

CMD:paracek(playerid, params[])
{
	new amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada deðilsiniz.");

	if (sscanf(params, "d", amount))
	{
		SendHelpMessage(playerid, "/paracek [Tutar]");
		SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Banka hesabýnýzda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

    if (amount > GetBankCash(playerid) || amount < 1)	return SendErrorMessage(playerid, "Girdiðiniz tutar banka hesabýnýzda yok veya geçersiz bir tutar girdiniz.");
    
	BankWithdraw(playerid, amount);
	return 1;
}

CMD:mevduat(playerid, params[])
{
	new amount;
	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada deðilsiniz.");

	if (PlayerInfo[playerid][pSavings] == 0)
	{
		if (sscanf(params, "d", amount))		return SendHelpMessage(playerid, "/mevduat [tutar]");
		if (amount < 50000 || amount > 150000)	return SendErrorMessage(playerid, "Mevduat tutarý 50000 ile 150000 arasýnda olmalýdýr.");
		if (GetCash(playerid) < amount) 		return SendNotCash(playerid);

		SendSyntaxMessage(playerid, "$%d tutarýný mevduat hesabýnýza yatýrdýnýz. Faiz oraný: 1%%", amount);
		GiveCash(playerid, -amount);
		PlayerInfo[playerid][pSavings] = amount;
		return 1;
	}
	else
	{
		SendSyntaxMessage(playerid, "Mevduatta bulunan paranýzý geri çektiniz: $%i.", PlayerInfo[playerid][pSavings]);
		GiveCash(playerid, PlayerInfo[playerid][pSavings]);
		PlayerInfo[playerid][pSavings] = 0;
	}
	return 1;
}

CMD:maascek(playerid, params[])
{
	if (!ATM_Nearest(playerid))					return SendErrorMessage(playerid, "Bankada deðilsiniz.");
	if (PlayerInfo[playerid][pPayCheckMoney] < 1)	return SendErrorMessage(playerid, "Maaþ hesabýndan çekebileceðiniz para bulunmuyor.");

	SendSyntaxMessage(playerid, "[MAAÞ HESABI] Hesabýnýzdan $%i tutarýnda para çektiniz.", PlayerInfo[playerid][pPayCheckMoney]);
	GiveCash(playerid, PlayerInfo[playerid][pPayCheckMoney]);
	PlayerInfo[playerid][pPayCheckMoney] = 0;
	return 1;
}

CMD:atm(playerid, params[])
{
    if (ATM_Nearest(playerid) == -1) return 1;
	
	Dialog_Show(playerid, ATMMenu, DIALOG_STYLE_LIST, "{FFFFFF}ATM", "- Bakiye\n- Para Çek\n- Para Yatýr\n- Para Transferi\n- Maaþ Çek", "Seç", "Ýptal");
	return 1;
}

CMD:banka(playerid, params[])
{
   if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada deðilsiniz.");
	
	Dialog_Show(playerid, BankMenu, DIALOG_STYLE_LIST, "{FFFFFF}Banka", "- Hesap Durumu\n- Para Çek\n- Para Yatýr\n- Para Transferi\n- Maaþ Çek\n- Mevduat", "Seç", "Ýptal");
	return 1;
}