Dialog:BillboardList(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	if (BillboardInfo[listitem][bbRentDate]) {
		pc_cmd_panokirala(playerid, "");
		return SendErrorMessage(playerid, "Bu reklam panosu zaten kiralanmýþ!");
	}
	
	static const msg[] = "Kiralama Süresi Seçin:\n{FFFFFF}24 saat\t{FF6347}$%i\n{FFFFFF}48 saat\tFF6347$%i\n{FFFFFF}72 saat\t{FF6347}$%i";
	new string[sizeof(msg)+10];

	format(string, sizeof(string), msg, 
		BillboardInfo[listitem][bbRentCost], 
		floatround(BillboardInfo[listitem][bbRentCost]*2.2), 
		floatround(BillboardInfo[listitem][bbRentCost]*3.5)
	);

	SetPVarInt(playerid, #BB_SELECT_ID, listitem);
	Dialog_Show(playerid, BillboardRent, DIALOG_STYLE_TABLIST_HEADERS, "Reklam Panosu Kirala", string, ">>>", "Ýptal");
	return 1;
}

Dialog:BillboardRent(playerid, response, listitem, inputtext[])
{
	if (!response)	return DeletePVar(playerid, #BB_SELECT_ID);
	
	SetPVarInt(playerid, #BB_SELECT_HH, listitem);

	new id = GetPVarInt(playerid, #BB_SELECT_ID);
	
	static const msg[] = "{ffffff}Þimdi reklamýnýz için metni girin!\nMaksimum karakterleri göz önünde bulundurun: %i\n\n\n{c3c3c3}[ ! ] Yazdýklarýnýzý kaydetmeyi unutmayýn -> CTRL + C";
	new string[sizeof(msg)+1];

	new max_char;
	
	switch(BillboardInfo[id][bbModel]) {
		case 7302: max_char = 100;
		case 9314: max_char = 87;
	}

	format(string, sizeof(string), msg, max_char);

	Dialog_Show(playerid, BillboardRent2, DIALOG_STYLE_INPUT, "Reklam Panosu Kirala", string, ">>>", "Ýptal");
	return 1;
}

/*
bblen(str[]) {
    new stop = 0, count = 0;

    for(new i; i < strlen(str); i++) {
        if (str[i] = "{") stop = 1;
        if (str[i] = "}") stop = 0;

        if (!stop) count++;
    }
    return count++;
}*/

Dialog:BillboardRent2(playerid, response, listitem, inputtext[])
{
	if (!response) {
		DeletePVar(playerid, #BB_SELECT_ID);
		DeletePVar(playerid, #BB_SELECT_HH);
		return 1;
	}

	new id = GetPVarInt(playerid, #BB_SELECT_ID);

	if (CheckDialogString(inputtext)) {
		pc_cmd_panokirala(playerid, "");
		DeletePVar(playerid, #BB_SELECT_ID);
		DeletePVar(playerid, #BB_SELECT_HH);

		return SendErrorMessage(playerid, "Reklam metninde kullanýlamaz '\n'!");
	}

	if (1 < strlen(inputtext) < 100) {
		SetPVarString(playerid, #BB_SELECT_TEXT, TextTab(inputtext, 22, 35, 1, 0));

		static const msg[] = "• {ffffff}Billboard {c3c3c3}#%i\n{ffffff}• Kiralama Ücreti: {c3c3c3}$%i\n{ffffff}• Kiralama Süresi: {c3c3c3}%i saat\n{ffffff}• Reklam Metni:\n\n{c3c3c3}%s\n\n{ffffff}Her þeyin doðru olup olmadýðýný kontrol edin, eðer doðruysa 'Satýn Al' tuþuna týklayýn!";
		new string[sizeof(msg)+100+2];

		new hours, cost;
		switch(GetPVarInt(playerid, #BB_SELECT_HH)) {
			case 0: { hours = 24; cost = BillboardInfo[id][bbRentCost]; } // 24h 
			case 1: { hours = 48; cost = floatround(BillboardInfo[id][bbRentCost]*2.2); } // 48h
			case 2: { hours = 72; cost = floatround(BillboardInfo[id][bbRentCost]*3.5); } // 72h
		}

		format(string, sizeof(string), msg,
			id+1,
			cost,
			hours,
			TextTab(inputtext, 22, 35, 1, 0)
		);

		Dialog_Show(playerid, BillboardRentFinal, DIALOG_STYLE_MSGBOX, "Reklam Panosu Kirala", string, "Satýn Al", "Ýptal");
	} else {
		pc_cmd_panokirala(playerid, "");

		new max_char;
		switch(BillboardInfo[id][bbModel]) {
			case 7302: max_char = 100;
			case 9314: max_char = 87; 
		}
		
		DeletePVar(playerid, #BB_SELECT_ID);
		DeletePVar(playerid, #BB_SELECT_HH);

		return SendErrorMessage(playerid, "1 <= Reklam metni <= %i", max_char);
	}
	
	return 1;
}

Dialog:BillboardRentFinal(playerid, response, listitem, inputtext[])
{
	if (!response) {
		DeletePVar(playerid, #BB_SELECT_ID);
		DeletePVar(playerid, #BB_SELECT_HH);
		DeletePVar(playerid, #BB_SELECT_TEXT);
		return 1;
	}

	new mes[100], hours, cost, id = GetPVarInt(playerid, #BB_SELECT_ID);

	GetPVarString(playerid, #BB_SELECT_TEXT, mes, 100);

	switch(GetPVarInt(playerid, #BB_SELECT_HH)) {
		case 0: { hours = 24; cost = BillboardInfo[id][bbRentCost]; } // 24h 
		case 1: { hours = 48; cost = floatround(BillboardInfo[id][bbRentCost]*2.2); } // 48h
		case 2: { hours = 72; cost = floatround(BillboardInfo[id][bbRentCost]*3.5); } // 72h
	}

	GiveCash(playerid, -cost);

	BillboardInfo[id][bbRentDate] = gettime()+hours*60*60;
	BillboardInfo[id][bbRentBy] = PlayerInfo[playerid][pID];
	format(BillboardInfo[id][bbText], 100, "%s\n{595959}No: %i", mes, PlayerInfo[playerid][pNumber]);

	Save_BB(id);

	SendHelpMessage(playerid, "Baþarýlý þekilde reklam panosu kiraladýnýz [#%i] | {FF6347}%i saat{ffffff} | {FF6347}$%i{ffffff}.", id+1, hours, cost);
    SendHelpMessage(playerid, "/rp - reklam panolarýnýzý kontrol edebilirsiniz.");

	SetDynamicObjectMaterial(BillboardInfo[id][bbObject], 0, -1, "none", "none", 0xFFFFFFFF);
	SetDynamicObjectMaterialText(BillboardInfo[id][bbObject], 0, BillboardInfo[id][bbText], OBJECT_MATERIAL_SIZE_512x128,"Arial", 28, 0, 0xFF000000, 0x0FFFFFFF, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

	return 1;
}

Dialog:MyBillboards(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new id, count;

    for(new i; i < MAX_BILLBOARDS; i++) {
		if (BillboardInfo[i][bbRentBy] == PlayerInfo[playerid][pID]) {
			if (listitem == count) id = i;
			else count++;
		}
    }

    static const msg[] = "{FFFFFF}Reklam panosunun kiralamasýný iptal etmek istediðinize emin misiniz? [#%i], %s";
    new string[sizeof(msg)+1+MAX_ZONE_NAME];

    new location[MAX_ZONE_NAME];
	GetZone(BillboardInfo[id][bbPosX],BillboardInfo[id][bbPosY], location, MAX_ZONE_NAME);

    format(string, sizeof(string), msg,
        id,
        location
    );

	ConfirmDialog(playerid, "Onayla", string, "MyBillBoard_Unrent", id);
	return 1;
} //î
