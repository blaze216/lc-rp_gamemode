alias:parabirak("paraat");
CMD:parabirak(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])   
		return SendErrorMessage(playerid, "Bu �zelli�i �u anda kullanamazs�n�z.");
	if (IsAdminDuty(playerid))                                                         return SendErrorMessage(playerid, "�nce admin i�ba��ndan ��kman�z laz�m..");
    if (IsPlayerInAnyVehicle(playerid))                                                              return SendErrorMessage(playerid, "Ara�ta olmaman�z gerekmektedir.");
    if (PlayerInfo[playerid][pHours] < 2)                                                            return SendErrorMessage(playerid, "�nce 2 level olmal�s�n�z..");

    new amount;

    if (sscanf(params, "i", amount))                                                                 return SendHelpMessage(playerid, "/parabirak [miktar]");
	if (amount < 1 || amount > 3000)                                                                 return SendErrorMessage(playerid, "Yanl�� bir tutar girdiniz. ($1 - $3000).");
	if (amount > GetCash(playerid))                                                                  return SendNotCash(playerid);
	if (ItemDrop_Drop(playerid, 9999, amount) == -1)                                                 return SendErrorMessage(playerid, "D��en maksimum ��e say�s�na ula��ld�.");
    SendAdmMessage("%s [ID: %i] $%i yere att�.", GetNameEx(playerid), playerid, amount);
	GiveCash(playerid, -amount);

    SendSyntaxMessage(playerid, "$%i paray� yere b�rakt�n�z. Almak i�in {ffc46a}/yerdenal{FFFFFF} veya oturun ve {ffc46a}H{FFFFFF} tu�una bas�n.", amount);
	return 1;
}

CMD:yerebirak(playerid, params[])
{
    if (!GetPVarInt(playerid, #attach_item))  return 1;
    if (ItemDrop_Drop(playerid, pTemp[playerid][tempItem], pTemp[playerid][tempQ], pTemp[playerid][tempEx]) == -1)
	return SendErrorMessage(playerid, "Yere e�ya b�rakma s�n�r�n� a�t�n�z.");
	if (IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Ara� i�indeyken yere e�ya b�rakamazs�n.");

    SendSyntaxMessage(playerid, "$%i paray� yere b�rakt�n�z. Almak i�in {ffc46a}/yerdenal{FFFFFF} veya oturun ve {ffc46a}H{FFFFFF} tu�una bas�n.", inventory_items[pTemp[playerid][tempItem]][itemName], pTemp[playerid][tempQ]);			
    		
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
		return SendErrorMessage(playerid, "Bu �zelli�i �u anda kullanamazs�n�z.");
	new dropid = -1;
	if ((dropid = ItemDrop_Nearest(playerid)) == -1) return OyuncuYerdenPaketAl(playerid);

	if (IsPlayerCrouching(playerid)) ItemDrop_Pickup(playerid, dropid);
	else 							InfoMSG(playerid, "Bir nesneyi almak icin ~y~ oturmaniz ~w~gerekmektedir ~w~~y~", 3);
	
	return 1;
}