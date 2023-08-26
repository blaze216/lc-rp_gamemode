alias:parabirak("paraat");
CMD:parabirak(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])   
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");
	if (IsAdminDuty(playerid))                                                         return SendErrorMessage(playerid, "Önce admin iþbaþýndan çýkmanýz lazým..");
    if (IsPlayerInAnyVehicle(playerid))                                                              return SendErrorMessage(playerid, "Araçta olmamanýz gerekmektedir.");
    if (PlayerInfo[playerid][pHours] < 2)                                                            return SendErrorMessage(playerid, "Önce 2 level olmalýsýnýz..");

    new amount;

    if (sscanf(params, "i", amount))                                                                 return SendHelpMessage(playerid, "/parabirak [miktar]");
	if (amount < 1 || amount > 3000)                                                                 return SendErrorMessage(playerid, "Yanlýþ bir tutar girdiniz. ($1 - $3000).");
	if (amount > GetCash(playerid))                                                                  return SendNotCash(playerid);
	if (ItemDrop_Drop(playerid, 9999, amount) == -1)                                                 return SendErrorMessage(playerid, "Düþen maksimum öðe sayýsýna ulaþýldý.");
    SendAdmMessage("%s [ID: %i] $%i yere attý.", GetNameEx(playerid), playerid, amount);
	GiveCash(playerid, -amount);

    SendSyntaxMessage(playerid, "$%i parayý yere býraktýnýz. Almak için {ffc46a}/yerdenal{FFFFFF} veya oturun ve {ffc46a}H{FFFFFF} tuþuna basýn.", amount);
	return 1;
}

CMD:yerebirak(playerid, params[])
{
    if (!GetPVarInt(playerid, #attach_item))  return 1;
    if (ItemDrop_Drop(playerid, pTemp[playerid][tempItem], pTemp[playerid][tempQ], pTemp[playerid][tempEx]) == -1)
	return SendErrorMessage(playerid, "Yere eþya býrakma sýnýrýný aþtýnýz.");
	if (IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araç içindeyken yere eþya býrakamazsýn.");

    SendSyntaxMessage(playerid, "$%i parayý yere býraktýnýz. Almak için {ffc46a}/yerdenal{FFFFFF} veya oturun ve {ffc46a}H{FFFFFF} tuþuna basýn.", inventory_items[pTemp[playerid][tempItem]][itemName], pTemp[playerid][tempQ]);			
    		
    RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    SetPVarInt(playerid, #attach_item, 0);

    pTemp[playerid][tempItem] = 0;
    pTemp[playerid][tempEx] = 0;
    pTemp[playerid][tempQ] = 0;
    return 1;
}

alias:yerdenal("esyaal");
CMD:yerdenal(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) 
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");
	new dropid = -1;
	if ((dropid = ItemDrop_Nearest(playerid)) == -1) return OyuncuYerdenPaketAl(playerid);

	if (IsPlayerCrouching(playerid)) ItemDrop_Pickup(playerid, dropid);
	else 							InfoMSG(playerid, "Bir nesneyi almak icin ~y~ oturmaniz ~w~gerekmektedir ~w~~y~", 3);
	
	return 1;
}