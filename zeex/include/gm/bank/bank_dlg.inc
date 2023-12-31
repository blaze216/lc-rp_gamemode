Dialog:ATMMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	    
	switch(listitem)
	{
	    case 0:
		{
		    static const str_size[] = "[BANKA] {"COL_GREEN"}$%i.\n[MEVDUAT] {"COL_GREEN"}$%i\n[MAA� HESABI] {"COL_GREEN"}$%i";
		    new mes[sizeof(str_size) - 4 + 24];
		    
			format(mes, sizeof(mes), str_size, PlayerInfo[playerid][pBank], PlayerInfo[playerid][pSavings], PlayerInfo[playerid][pPayCheckMoney]);
			Dialog_Show(playerid, ATMBack, DIALOG_STYLE_LIST, "{FFFFFF}Hesap Durumu", mes, "Geri D�n", "");
		}
		case 1: Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF} Para �ek", "{FFFFFF} Banka hesab�n�zdan �ekmek istedi�iniz tutar� giriniz:", "Para �ek", "Geri D�n");
		case 2: Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFF} Para Yat�r", "{FFFFFF} Banka hesab�n�za yat�rmak istedi�iniz tutar� giriniz:", "Para Yat�r", "Geri D�n");
		case 3: Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF} Para Transferi", "{FFFFFF}Transfer yapmak istedi�iniz ki�inin ad�n� veya ID'sini giriniz:", ">>>", "Geri D�n");
		case 4: pc_cmd_maascek(playerid, "");
	}
	return 1;
}//�

Dialog:BankMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	    
	switch(listitem)
	{
	    case 0:
		{
		    static const str_size[] = "[BANKA] {"COL_GREEN"}$%i.\n[MEVDUAT] {"COL_GREEN"}$%i\n[MAA� HESABI] {"COL_GREEN"}$%i";
		    new mes[sizeof(str_size) - 4 + 24];
		    
			format(mes, sizeof(mes), str_size, PlayerInfo[playerid][pBank], PlayerInfo[playerid][pSavings], PlayerInfo[playerid][pPayCheckMoney]);
			Dialog_Show(playerid, ATMBack, DIALOG_STYLE_LIST, "{FFFFFF}Hesap Durumu", mes, "Geri D�n", "");
		}
		case 1: Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF} Para �ek", "{FFFFFF} Banka hesab�n�zdan �ekmek istedi�iniz tutar� giriniz:", "Para �ek", "Geri D�n");
		case 2: Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFF} Para Yat�r", "{FFFFFF} Banka hesab�n�za yat�rmak istedi�iniz tutar� giriniz:", "Para Yat�r", "Geri D�n");
		case 3: Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF} Para Transferi", "{FFFFFF}Transfer yapmak istedi�iniz ki�inin ad�n� veya ID'sini giriniz:", ">>>", "Geri D�n");
		case 4: pc_cmd_maascek(playerid, "");
		case 5:	Dialog_Show(playerid, BankMevduat, DIALOG_STYLE_LIST, "{FFFFFF} Mevduat", "Para �ek(Hepsini)\nPara Yat�r", "Se�", "Geri D�n");
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
		SendSyntaxMessage(playerid, "Mevduatta bulunan paran�z� geri �ektiniz: $%i.", PlayerInfo[playerid][pSavings]);
		GiveCash(playerid, PlayerInfo[playerid][pSavings]);
		PlayerInfo[playerid][pSavings] = 0;
		}
		case 1: Dialog_Show(playerid, BankMevduatYatir, DIALOG_STYLE_INPUT, "{FFFFFF} Mevduat Yat�r", "{FFFFFF} Mevduat hesab�na yat�ralacak paray� yaz�n�z:\nMevduat tutar� 50000 ile 1000000 aras�nda olmal�d�r.", "Yat�r", "Geri D�n");
	}
return 1;
}

Dialog:BankMevduatYatir(playerid, listitem, response, inputtext[])
{
	if (!response) return pc_cmd_banka(playerid, "");
	new amount = strval(inputtext);
    if (amount < 50000 || amount > 150000)	return SendErrorMessage(playerid, "Mevduat tutar� 50000 ile 150000 aras�nda olmal�d�r.");
	if (GetCash(playerid) < amount) 		return SendNotCash(playerid);
	if (amount + PlayerInfo[playerid][pSavings] > 150000)    return SendErrorMessage(playerid, "Mevduat tutar� 50000 ile 150000 aras�nda olmal�d�r.");
	SendSyntaxMessage(playerid, "$%d tutar�n� mevduat hesab�n�za yat�rd�n�z. Faiz oran�: 1%%", amount);
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
	    Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF}Para Transferi", "{FFFFFF}Transfer yapmak istedi�iniz ki�inin ad�n� veya ID'sini giriniz:", ">>>", "Geri D�n");
	    return SendErrorMessage(playerid, "Al�c� bulunamad�.");
	}

	static const str_size[] = "{FFFFFF}Para Transferi - {FFFF00}%s";
	new mes[sizeof(str_size) - 2 + MAX_PLAYER_NAME + 1];

	format(mes, sizeof(mes), str_size, GetNameEx(userid));
	SetPVarInt(playerid, #transfer_player, userid);
	Dialog_Show(playerid, ATMTransfer2, DIALOG_STYLE_INPUT, mes, "{FFFFFF}Transfer yapmak istedi�iniz tutar� giriniz:", "Transfer Yap", "�ptal");
	return 1;
}

Dialog:ATMTransfer2(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_atm(playerid, "");

	new userid = GetPVarInt(playerid, #transfer_player), amount = strval(inputtext);

	DeletePVar(playerid, #transfer_player);

	if (!IsPlayerLogged(userid) || userid == playerid)
	{
	    Dialog_Show(playerid, ATMTransfer, DIALOG_STYLE_INPUT, "{FFFFFF}Para Transferi", "{FFFFFF}Transfer yapmak istedi�iniz ki�inin ad�n� veya ID'sini giriniz:", ">>>", "Geri D�n");
	    return SendErrorMessage(playerid, "Al�c� bulunamad�.");
	}
	if (GetBankCash(playerid) < amount || amount < 1)
	{
	    static const str_size[] = "{FFFFFF}Para Transferi - {FFFF00}%s";
		new mes[sizeof(str_size) - 2 + MAX_PLAYER_NAME + 1];

		format(mes, sizeof(mes), str_size, GetNameEx(userid));
		SetPVarInt(playerid, #transfer_player, userid);
		Dialog_Show(playerid, ATMTransfer2, DIALOG_STYLE_INPUT, mes, "{FFFFFF}Transfer yapmak istedi�iniz tutar� giriniz:", "Transfer Yap", "�ptal");
 		return SendErrorMessage(playerid, "Girdi�iniz tutar banka hesab�n�zda bulunmuyor veya ge�ersiz bir tutar girdiniz.");
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
        Dialog_Show(playerid, ATMWithdraw, DIALOG_STYLE_INPUT, "{FFFFFF}Para �ek", "{FFFFFF}Banka hesab�n�zdan �ekmek istedi�iniz tutar� giriniz:", "Para �ek", "Geri D�n");
		return SendErrorMessage(playerid, "Girdi�iniz tutar banka hesab�n�zda bulunmuyor veya ge�ersiz bir tutar girdiniz.");
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
        Dialog_Show(playerid, ATMDeposit, DIALOG_STYLE_INPUT, "{FFFFFFF}Para Yat�r", "Banka hesab�n�za yat�rmak istedi�iniz tutar� giriniz:", "Para Yat�r", "Geri D�n");
		return SendErrorMessage(playerid, "Girdi�iniz tutar �zerinizde bulunmuyor veya ge�ersiz bir tutar girdiniz.");
	}

	BankDeposit(playerid, amount);
	pc_cmd_atm(playerid, "");
	return 1;
}