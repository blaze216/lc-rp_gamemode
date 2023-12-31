CMD:hesapdurumu(playerid, params[])
{
	if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada de�ilsiniz.");

	SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Banka hesab�n�zda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
    SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Birikim Hesab�: $%i", PlayerInfo[playerid][pSavings]);
	SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Maa� Hesab�: $%i", PlayerInfo[playerid][pPayCheckMoney]);
	return 1;
}

CMD:paratransferi(playerid, params[])
{
	new userid, amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada de�ilsiniz.");
	if (sscanf(params, "ud", userid, amount))
	{
		SendHelpMessage(playerid, "/paratransferi [ID/Karakter Ad�] [Tutar]");
		SendSyntaxMessage(playerid,"[BANKA] Banka hesab�n�zda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

	if (userid == playerid)								return SendErrorMessage (playerid, "Kendinize para transferi yapamazs�n�z.");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (GetBankCash(playerid) < amount || amount < 1)	return SendErrorMessage (playerid, "Girdi�iniz tutar banka hesab�n�zda yok veya ge�ersiz bir tutar girdiniz.");

	BankTransfer(playerid, userid, amount);
	return 1;
}

CMD:parayatir(playerid, params[])
{
	new amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada de�ilsiniz.");

	if (sscanf(params, "d", amount))
	{
		SendHelpMessage(playerid, "/parayatir [Tutar]");
		SendSyntaxMessage(playerid, "[BANKA] Banka hesab�n�zda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

    if (amount > GetCash(playerid) || amount < 1) return SendErrorMessage(playerid, "Girdi�iniz tutar �zerinizde yok veya ge�ersiz bir tutar girdiniz.");
		
	BankDeposit(playerid, amount);
	return 1;
}

CMD:paracek(playerid, params[])
{
	new amount;

	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada de�ilsiniz.");

	if (sscanf(params, "d", amount))
	{
		SendHelpMessage(playerid, "/paracek [Tutar]");
		SendClientMessageEx(playerid, COLOR_FADE1, "[BANKA] Banka hesab�n�zda $%i bulunuyor.", PlayerInfo[playerid][pBank]);
		return 1;
	}

    if (amount > GetBankCash(playerid) || amount < 1)	return SendErrorMessage(playerid, "Girdi�iniz tutar banka hesab�n�zda yok veya ge�ersiz bir tutar girdiniz.");
    
	BankWithdraw(playerid, amount);
	return 1;
}

CMD:mevduat(playerid, params[])
{
	new amount;
	if (!Bank_Nearest(playerid)) return SendErrorMessage(playerid, "Bankada de�ilsiniz.");

	if (PlayerInfo[playerid][pSavings] == 0)
	{
		if (sscanf(params, "d", amount))		return SendHelpMessage(playerid, "/mevduat [tutar]");
		if (amount < 50000 || amount > 150000)	return SendErrorMessage(playerid, "Mevduat tutar� 50000 ile 150000 aras�nda olmal�d�r.");
		if (GetCash(playerid) < amount) 		return SendNotCash(playerid);

		SendSyntaxMessage(playerid, "$%d tutar�n� mevduat hesab�n�za yat�rd�n�z. Faiz oran�: 1%%", amount);
		GiveCash(playerid, -amount);
		PlayerInfo[playerid][pSavings] = amount;
		return 1;
	}
	else
	{
		SendSyntaxMessage(playerid, "Mevduatta bulunan paran�z� geri �ektiniz: $%i.", PlayerInfo[playerid][pSavings]);
		GiveCash(playerid, PlayerInfo[playerid][pSavings]);
		PlayerInfo[playerid][pSavings] = 0;
	}
	return 1;
}

CMD:maascek(playerid, params[])
{
	if (!ATM_Nearest(playerid))					return SendErrorMessage(playerid, "Bankada de�ilsiniz.");
	if (PlayerInfo[playerid][pPayCheckMoney] < 1)	return SendErrorMessage(playerid, "Maa� hesab�ndan �ekebilece�iniz para bulunmuyor.");

	SendSyntaxMessage(playerid, "[MAA� HESABI] Hesab�n�zdan $%i tutar�nda para �ektiniz.", PlayerInfo[playerid][pPayCheckMoney]);
	GiveCash(playerid, PlayerInfo[playerid][pPayCheckMoney]);
	PlayerInfo[playerid][pPayCheckMoney] = 0;
	return 1;
}

CMD:atm(playerid, params[])
{
    if (ATM_Nearest(playerid) == -1) return 1;
	
	Dialog_Show(playerid, ATMMenu, DIALOG_STYLE_LIST, "{FFFFFF}ATM", "- Bakiye\n- Para �ek\n- Para Yat�r\n- Para Transferi\n- Maa� �ek", "Se�", "�ptal");
	return 1;
}

CMD:banka(playerid, params[])
{
   if (!Bank_Nearest(playerid)) return SendErrorMessage (playerid, "Bankada de�ilsiniz.");
	
	Dialog_Show(playerid, BankMenu, DIALOG_STYLE_LIST, "{FFFFFF}Banka", "- Hesap Durumu\n- Para �ek\n- Para Yat�r\n- Para Transferi\n- Maa� �ek\n- Mevduat", "Se�", "�ptal");
	return 1;
}