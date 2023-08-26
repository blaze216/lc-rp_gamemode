alias:panokirala("reklampanokira");
CMD:panokirala(playerid, params[]) 
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (!PlayerInfo[playerid][pNumber]) return SendErrorMessage(playerid, "Ýlan gönderebilmek için telefona ihtiyacýnýz var.");

    new bizid = -1;
    if ((bizid = Advertisement_Nearest(playerid)) == -1) return SendErrorMessage(playerid, "Bir reklam ajansýnda deðilsiniz.");
	if (BizInfo[bizid][bizLocked] == 1)					 return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

	new str[128], mes[(13+MAX_ZONE_NAME+60)*MAX_BILLBOARDS+27] = "Lokasyon\tÝsim\tDurum\n";

	new count;
	for(new i; i < MAX_BILLBOARDS; i++) if (BillboardInfo[i][bbRentBy] == PlayerInfo[playerid][pID]) count++;
	if (count >= 3) return SendErrorMessage(playerid, "Kiralayabileceðiniz maksimum sayýda reklam panosu kiralamýþsýnýz! /rp komutuyla reklamlarýnýzý yönetebilirsiniz.");

	new location[MAX_ZONE_NAME];
	count = 0;

	for(new i; i < MAX_BILLBOARDS; i++) {
		if (!BillboardInfo[i][bbActive]) continue;
		GetZone(BillboardInfo[i][bbPosX],BillboardInfo[i][bbPosY], location, MAX_ZONE_NAME);

		if (!BillboardInfo[i][bbRentDate]) 	format(str, sizeof(str), "%s\t[Reklam Panosu #%i]\t{16b819}Boþta{FFFFFF}", location, i+1);
		else								format(str, sizeof(str), "%s\t[Reklam Panosu #%i]\t{FF6347}%s {FFFFFF}tarafýndan {FF6347}%s{FFFFFF} tarihine kadar kiralanmýþ.", location, i+1, GetPlayerNameBySqlID(BillboardInfo[i][bbRentBy]), get_date("%dd.%mm.%yy", BillboardInfo[i][bbRentDate]));

		format(mes, sizeof(mes), "%s\n%s", mes, str);
		count++;
	}

	if (!count) return SendErrorMessage(playerid, "Sunucuda reklam panosu bulunmuyor!");

	Dialog_Show(playerid, BillboardList, DIALOG_STYLE_TABLIST_HEADERS, "Reklam Panosu Kirala", mes, "Kirala", "Ýptal");
	return 1;
}

alias:reklampanolarim("rp");
CMD:reklampanolarim(playerid , params[]) 
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (!PlayerInfo[playerid][pNumber])				return SendErrorMessage(playerid, "Ýlan gönderebilmek için telefona ihtiyacýnýz var.");

    new bizid = -1;
    if ((bizid = Advertisement_Nearest(playerid)) == -1)	return SendErrorMessage(playerid, "Bir reklam ajansýnda deðilsiniz.");
	if (BizInfo[bizid][bizLocked] == 1)						return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);

	new count, str[90], mes[(60+MAX_ZONE_NAME+13)*3+27] = "Lokasyon\tÝsim\tDurum\n", location[MAX_ZONE_NAME];
	
	for(new i; i < MAX_BILLBOARDS; i++) {
		if (BillboardInfo[i][bbRentBy] == PlayerInfo[playerid][pID]) 
		{
			GetZone(BillboardInfo[i][bbPosX],BillboardInfo[i][bbPosY], location, MAX_ZONE_NAME);
			format(str, sizeof(str), "%s\t[Reklam Panosu #%i]\t%s{FFFFFF} tarihine kadar kiralanmýþ.", location, i+1, get_date("%dd.%mm.%yy", BillboardInfo[i][bbRentDate]));

			format(mes, sizeof(mes), "%s\n%s", mes, str);
			count++;

			if (count == 3) break;
		}
	}

	if (!count) return SendErrorMessage(playerid, "Kiralýk reklam panonuz yok!");
	
	Dialog_Show(playerid, MyBillboards, DIALOG_STYLE_TABLIST_HEADERS, "Reklam Panolarýnýz", mes, "Kaldýr", "Ýptal");
	return 1;
}

