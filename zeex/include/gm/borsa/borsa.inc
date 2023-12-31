
CMD:sadrazaminsoltas(playerid, listitem){
    new string[128];
    if (PlayerInfo[playerid][pInjured] == 2) return SendErrorMessage(playerid, "Yaral�yken herhangi bir i�lem yapamazs�n�z.");
    format(string, sizeof(string), "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice]);
    Dialog_Show(playerid, BorsaDialog, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", string, "Se�", "Iptal");
    return 1;
}


Dialog:BorsaDialog(playerid, response, listitem){

    if(!response) return 1;

     if(listitem == 0) return Dialog_Show(playerid, BorsaDialogBitcoinInfo, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", "Bitcoin Fiyat: %d\nElinizde bulunan %d adet\n Sat�n Al\nSat", "Se�", "Iptal", Borsa[0][bPrice], PlayerInfo[playerid][pBitcoin]);
    //if(listitem == 1) return  Dialog_Show(playerid, BorsaDialogEtherium, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", string, "Se�", "Iptal");
    return 1;
}

Dialog:BorsaDialogBitcoinInfo(playerid, response, listitem)
{
    if(!response) return 1;
    
     if(listitem == 2) Dialog_Show(playerid, BorsaDialogBitcoinBuy, DIALOG_STYLE_INPUT, "{FFFFFF}Borsa", "Ka� tane sat�n alacaks�n�z?", "Sat�n Al", "Iptal");
     else if(listitem == 3) Dialog_Show(playerid, BorsaDialogBitcoinSell, DIALOG_STYLE_INPUT, "{FFFFFF}Borsa", "Ka� tane satacaks�n�z?", "Sat�n Al", "Iptal");
//return Dialog_Show(playerid, BorsaDialog, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice], "Sat�n Al", "Iptal");
return 1;
}

Dialog:BorsaDialogBitcoinBuy(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    
    new string[128], amount;
    format(string, sizeof(string), "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice]);
    amount = strval(inputtext);
    if(amount <= 0) return Dialog_Show(playerid, BorsaDialogBitcoinBuy, DIALOG_STYLE_INPUT, "{FFFFFF}Borsa", "L�tfen ge�erli miktar giriniz!\nKa� tane sat�n alacaks�n�z?", "Sat�n Al", "Iptal");

    new totalCost = amount * Borsa[0][bPrice]; 

    if(PlayerInfo[playerid][pBank] < totalCost) 
    {
        SendErrorMessage(playerid, "Yetersiz bakiye.");
        format(string, sizeof(string), "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice]);
        return Dialog_Show(playerid, BorsaDialog, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", string, "Sat�n Al", "Iptal");
    }

    
    new oldBitcoin = PlayerInfo[playerid][pBitcoin];
    PlayerInfo[playerid][pBitcoin] += amount;

    
    GiveCash(playerid, -totalCost);
    

    
    new query[256];
    format(query, sizeof(query), "UPDATE users SET bitcoin = bitcoin + %d WHERE accountid = %d", amount,  PlayerInfo[playerid][pAccID]);
    mysql_tquery(dbHandle, query);

    SendServerMessage(playerid, "%d adet Bitcoin sat�n al�nd�. Yeni Bitcoin miktar�n�z: %d", amount, PlayerInfo[playerid][pBitcoin]);
    format(string, sizeof(string), "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice]);
    return 1;
}


Dialog:BorsaDialogBitcoinSell(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    new string[128], amount;
    format(string, sizeof(string), "Bitcoin %d$\nEtherium%d$", Borsa[0][bPrice], Borsa[1][bPrice]);
    amount = strval(inputtext);
    if (amount <= 0) return Dialog_Show(playerid, BorsaDialogBitcoinSell, DIALOG_STYLE_INPUT, "{FFFFFF}Borsa", "L�tfen ge�erli miktar giriniz!\nKa� tane satacaks�n�z?", "Sat", "Iptal");

    
    if (PlayerInfo[playerid][pBitcoin] < amount)
    {
        SendErrorMessage(playerid, "Yetersiz Bitcoin miktar�.");
        return Dialog_Show(playerid, BorsaDialog, DIALOG_STYLE_LIST, "{FFFFFF}Borsa", string, "Se�", "Iptal");
    }

    
    GiveCash(playerid, amount * Borsa[0][bPrice]);
    PlayerInfo[playerid][pBitcoin] -= amount;

    
    new query[256];
    format(query, sizeof(query), "UPDATE users SET bitcoin = bitcoin - %d WHERE accountid = %d", amount, PlayerInfo[playerid][pAccID]);
    mysql_tquery(dbHandle, query);

    SendServerMessage(playerid, "%d adet Bitcoin sat�ld�.", amount);
    return 1;
}

