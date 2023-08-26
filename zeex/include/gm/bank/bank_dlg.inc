Dialog:ATMMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	    
	switch(listitem)
	{
	    case 0:
		{
		    static const str_size[] = "[BANKA] {"COL_GREEN"}$%i.\n[MEVDUAT] {"COL_GREEN"}$%i\n[MAAÞ HESABI] {"COL_GREEN"}$%i";
		    new mes[sizeof(str_size) - 4 + 24];
		    
			format(mes, sizeof(mes), str_size, PlayerInfo[playerid][pBank], PlayerInfo[playerid][pSavings], PlayerInfo[playerid][pPayCheckMoney]);
			Dialog_Show(playerid, ATMBack, DIALOG_STYLE_LIST, "{FFFFFF}Hesap Durumu", mes, "Geri Dön", "");
		}
		case 1: Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF} Para Çek", "{FFFFFF} Banka hesabýnýzdan çekmek istediðiniz tutarý giriniz:", "Para Çek", "Geri Dön");
		case 2: Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFF} Para Yatýr", "{FFFFFF} Banka hesabýnýza yatýrmak istediðiniz tutarý giriniz:", "Para Yatýr", "Geri Dön");
		case 3: Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF} Para Transferi", "{FFFFFF}Transfer yapmak istediðiniz kiþinin adýný veya ID'sini giriniz:", ">>>", "Geri Dön");
		case 4: pc_cmd_maascek(playerid, "");
	}
	return 1;
}//î

Dialog:BankMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	    
	switch(listitem)
	{
	    case 0:
		{
		    static const str_size[] = "[BANKA] {"COL_GREEN"}$%i.\n[MEVDUAT] {"COL_GREEN"}$%i\n[MAAÞ HESABI] {"COL_GREEN"}$%i";
		    new mes[sizeof(str_size) - 4 + 24];
		    
			format(mes, sizeof(mes), str_size, PlayerInfo[playerid][pBank], PlayerInfo[playerid][pSavings], PlayerInfo[playerid][pPayCheckMoney]);
			Dialog_Show(playerid, ATMBack, DIALOG_STYLE_LIST, "{FFFFFF}Hesap Durumu", mes, "Geri Dön", "");
		}
		case 1: Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF} Para Çek", "{FFFFFF} Banka hesabýnýzdan çekmek istediðiniz tutarý giriniz:", "Para Çek", "Geri Dön");
		case 2: Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFF} Para Yatýr", "{FFFFFF} Banka hesabýnýza yatýrmak istediðiniz tutarý giriniz:", "Para Yatýr", "Geri Dön");
		case 3: Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF} Para Transferi", "{FFFFFF}Transfer yapmak istediðiniz kiþinin adýný veya ID'sini giriniz:", ">>>", "Geri Dön");
		case 4: pc_cmd_maascek(playerid, "");
		case 5:	Dialog_Show(playerid, BankMevduat, DIALOG_STYLE_LIST, "{FFFFFF} Mevduat", "Para Çek(Hepsini)\nPara Yatýr", "Seç", "Geri Dön");
	}
	return 1;
}

Dialog:BankMevduat(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_banka(playerid, "");

	switch(listitem)
	{
	    case 0:
		{
		SendSyntaxMessage(playerid, "Mevduatta bulunan paranýzý geri çektiniz: $%i.", PlayerInfo[playerid][pSavings]);
		GiveCash(playerid, PlayerInfo[playerid][pSavings]);
		PlayerInfo[playerid][pSavings] = 0;
		}
		case 1: Dialog_Show(playerid, BankMevduatYatir, DIALOG_STYLE_INPUT, "{FFFFFF} Mevduat Yatýr", "{FFFFFF} Mevduat hesabýna yatýralacak parayý yazýnýz:\nMevduat tutarý 50000 ile 1000000 arasýnda olmalýdýr.", "Yatýr", "Geri Dön");
	}
return 1;
}

Dialog:BankMevduatYatir(playerid, listitem, response, inputtext[])
{
	if (!response) return pc_cmd_banka(playerid, "");
	new amount = strval(inputtext);
    if (amount < 50000 || amount > 1000000)	return SendErrorMessage(playerid, "Mevduat tutarý 50000 ile 1000000 arasýnda olmalýdýr.");
	if (GetCash(playerid) < amount) 		return SendNotCash(playerid);
	if (amount + PlayerInfo[playerid][pSavings] > 1000000)    return SendErrorMessage(playerid, "Mevduat tutarý 50000 ile 1000000 arasýnda olmalýdýr.");
	SendSyntaxMessage(playerid, "$%d tutarýný mevduat hesabýnýza yatýrdýnýz. Faiz oraný: 1%%", amount);
	GiveCash(playerid, -amount);
	PlayerInfo[playerid][pSavings] += amount;
	pc_cmd_banka(playerid, "");
return 1;
}

Dialog:ATMBack(playerid, response, listitem, inputtext[])
{
	if (response)	pc_cmd_atm(playerid, "");
	
	return 1;
}

Dialog:ATMTransfer(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_atm(playerid, "");

	new userid;

	sscanf(inputtext, "u", userid);

	if (!IsPlayerLogged(userid) || userid == playerid)
	{
	    Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF}Para Transferi", "{FFFFFF}Transfer yapmak istediðiniz kiþinin adýný veya ID'sini giriniz:", ">>>", "Geri Dön");
	    return SendErrorMessage(playerid, "Alýcý bulunamadý.");
	}

	static const str_size[] = "{FFFFFF}Para Transferi - {FFFF00}%s";
	new mes[sizeof(str_size) - 2 + MAX_PLAYER_NAME + 1];

	format(mes, sizeof(mes), str_size, GetNameEx(userid));
	SetPVarInt(playerid, #transfer_player, userid);
	Dialog_Show(playerid, ATMTransfer2, DIALOG_STYLE_INPUT, mes, "{FFFFFF}Transfer yapmak istediðiniz tutarý giriniz:", "Transfer Yap", "Ýptal");
	return 1;
}

Dialog:ATMTransfer2(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_atm(playerid, "");

	new userid = GetPVarInt(playerid, #transfer_player), amount = strval(inputtext);

	DeletePVar(playerid, #transfer_player);

	if (!IsPlayerLogged(userid) || userid == playerid)
	{
	    Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF}Para Transferi", "{FFFFFF}Transfer yapmak istediðiniz kiþinin adýný veya ID'sini giriniz:", ">>>", "Geri Dön");
	    return SendErrorMessage(playerid, "Alýcý bulunamadý.");
	}
	if (GetBankCash(playerid) < amount || amount < 1)
	{
	    static const str_size[] = "{FFFFFF}Para Transferi - {FFFF00}%s";
		new mes[sizeof(str_size) - 2 + MAX_PLAYER_NAME + 1];

		format(mes, sizeof(mes), str_size, GetNameEx(userid));
		SetPVarInt(playerid, #transfer_player, userid);
		Dialog_Show(playerid, ATMTransfer2, DIALOG_STYLE_INPUT, mes, "{FFFFFF}Transfer yapmak istediðiniz tutarý giriniz:", "Transfer Yap", "Ýptal");
 		return SendErrorMessage(playerid, "Girdiðiniz tutar banka hesabýnýzda bulunmuyor veya geçersiz bir tutar girdiniz.");
	}
	
	BankTransfer(playerid, userid, amount);
	pc_cmd_atm(playerid, "");
	return 1;
}

Dialog:ATMWithdraw(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_atm(playerid, "");
	    
	new amount = strval(inputtext);

    if (amount > GetBankCash(playerid) || amount < 1)
	{
        Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF}Para Çek", "{FFFFFF}Banka hesabýnýzdan çekmek istediðiniz tutarý giriniz:", "Para Çek", "Geri Dön");
		return SendErrorMessage(playerid, "Girdiðiniz tutar banka hesabýnýzda bulunmuyor veya geçersiz bir tutar girdiniz.");
	}
	
	BankWithdraw(playerid, amount);
	pc_cmd_atm(playerid, "");
	return 1;
}

Dialog:ATMDeposit(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_atm(playerid, "");

	new amount = strval(inputtext);

    if (amount > GetCash(playerid) || amount < 1)
	{
        Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFFF}Para Yatýr", "Banka hesabýnýza yatýrmak istediðiniz tutarý giriniz:", "Para Yatýr", "Geri Dön");
		return SendErrorMessage(playerid, "Girdiðiniz tutar üzerinizde bulunmuyor veya geçersiz bir tutar girdiniz.");
	}

	BankDeposit(playerid, amount);
	pc_cmd_atm(playerid, "");
	return 1;
}