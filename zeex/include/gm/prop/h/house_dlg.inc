Dialog:HouseMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new houseid;
	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yak�n de�ilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	switch(listitem)
	{
	    case 0: pc_cmd_kilit(playerid, ""); // ������� �����
		case 1: { //��������� ����
			static dlgtxt[] = "{FFFFFF}Kap�y� tamir et {33CC33} [$ 300] {FFFFFF}\n\
								Radyo sat�n al {33CC33} [$ 500] {FFFFFF}\n\
								Kap�y� geli�tir\n\
								Kilidi geli�tir\n\
								Alarm� geli�tir\n\
								Gardrop sat�n al {33CC33} [$ 600] {FFFFFF}\n\
								�lk yard�m kiti sat�n al";

			new diatxt[sizeof(dlgtxt) + 30], door[40];	

			if (!HouseInfo[houseid][hDDoor]) format(door, sizeof(door), "{9ACD32}Gerekli De�il{FFFFFF}");
			else 							format(door, sizeof(door), "{FF6347}Gerekli{FFFFFF}");

			format(diatxt, sizeof(diatxt), dlgtxt, door);

			Dialog_Show(playerid, HouseUpgrade, DIALOG_STYLE_LIST, "Ev Geli�tirmeleri", diatxt, "Se�", "Geri D�n");
		}
		case 2: pc_cmd_dekorasyon(playerid, "");
		case 3:
		{
		    new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT `id`, `name` FROM `users` WHERE `rent_key` = %i LIMIT %i", HouseInfo[houseid][hID], MAX_TENAT_SPACE);
			mysql_tquery(dbHandle, query, "ShowTenantsAmount", "i", playerid);
		}
		case 4: //��������� ����
		{
		    if (!IsPlayerInsideHouse(playerid, houseid))		return SendErrorMessage(playerid, "Evde olmal�s�n�z.");
		        
			PrintHouseInv(playerid, houseid);
		}
		case 5:
		{
			static dlgtxt[] = "Kasa: $%i\n\
								{FF6347}>{FFFFFF} Kasaya para koy\n\
								{FF6347}>{FFFFFF} Kasadan para al";

			new diatxt[sizeof(dlgtxt) + 11];		
			format(diatxt, sizeof(diatxt), dlgtxt, HouseInfo[houseid][hCash]);

			Dialog_Show(playerid, HouseSafeChoose, DIALOG_STYLE_TABLIST, "Kasa", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 6: pc_cmd_kiyafetlerim(playerid, "");
		case 7: Dialog_Show(playerid, SellHouseChoose, DIALOG_STYLE_LIST, "{FFFFFF}Sat�l�k Ev", "Evi oyuncuya sat\nEvi sisteme sat", "Se�", "Geri D�n");
	}
	return 1;
}

Dialog:HouseUpgrade(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	switch(listitem)
	{
		case 0: {
			if (!HouseInfo[houseid][hDDoor])	return SendErrorMessage(playerid, "Evin kap�s� hasarl� de�il.");
			if (GetCash(playerid) < 300)		return SendErrorMessage(playerid, "Evin kap�s�n� tamir ettirebilmek i�in yeterli paran�z bulunmuyor, fiyat: $300");

			HouseInfo[houseid][hDDoor] = 0;
			SQL_SetInteger("houses", "ddoor", HouseInfo[houseid][hDDoor], HouseInfo[houseid][hID]);
			UpdateHouseDoor(houseid);
			GiveCash(playerid, -300);
			SendSyntaxMessage(playerid, "$300 kar��l���nda evin kap�s�n� tamir ettirdiniz.");
			return 1;
		}
		case 1: {
			if (HouseInfo[houseid][hRadio])	return SendErrorMessage(playerid, "Evde radyo bulunuyor.");
			if (GetCash(playerid) < 500)		return SendErrorMessage(playerid, "Radyo sat�n alabilmek i�in yeterli paran�z bulunmuyor, fiyat: $500.");

			HouseInfo[houseid][hRadio] = 1;
			SQL_SetInteger("houses", "radio", HouseInfo[houseid][hRadio], HouseInfo[houseid][hID]);
			GiveCash(playerid, -500);
			SendSyntaxMessage(playerid, "$500 kar��l���nda radyo sat�n ald�n�z, kullan�m: /radyoayarla.");
			return 1;
		}
		case 2: {
			static dlgtxt[] = "Seviye\tKap� Tipi\t�zellikler\tFiyat\n\
								{C3C3C3} 1 Seviye {FFFFFF}\t Ah�ap\t + 5% h�rs�zl��a kar�� koruma\t {33CC33} $750\n\
								{C3C3C3} 2 Seviye {FFFFFF}\t Demir\t + 15% h�rs�zl��a kar�� koruma\t {33CC33} $1500";

			Dialog_Show(playerid, HouseUpgradeDoor, DIALOG_STYLE_TABLIST_HEADERS, "Kap� Geli�tirmesi", dlgtxt, "Sat�n Al", "Geri D�n");
		}
		case 3: {
			static dlgtxt[] = "Seviye\t�zellikler\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF}\t + 5% h�rs�zl��a kar�� koruma\t {33CC33} $250\n\
							{C3C3C3} 2 Seviye {FFFFFF}\t + 10% h�rs�zl��a kar�� koruma\t {33CC33} $500\n\
							{C3C3C3} 3 Seviye {FFFFFF}\t + 15% h�rs�zl��a kar�� koruma\t {33CC33} $750\n\
							{C3C3C3} 4 Seviye {FFFFFF}\t + 20% h�rs�zl��a kar�� koruma\t {33CC33} $1000\n\
							{C3C3C3} 5 Seviye {FFFFFF}\t + 25% h�rs�zl��a kar�� koruma\t {33CC33} $1250";

			Dialog_Show(playerid, HouseUpgradeLock, DIALOG_STYLE_TABLIST_HEADERS, "Kilit Geli�tirmesi", dlgtxt, "Sat�n Al", "Geri D�n");
		}
		case 4: {
			static dlgtxt[] = "Seviye\t�zellikler\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF} \tStandart \t {33CC33} $500 \n\
							{C3C3C3} 2 Seviye {FFFFFF} \tOrta \t {33CC33} $1000 \n\
							{C3C3C3} 3 Seviye {FFFFFF} \t�yi \t {33CC33} $1500";
			Dialog_Show(playerid, HouseUpgradeAlarm, DIALOG_STYLE_TABLIST_HEADERS, "Alarm Geli�tirmesi", dlgtxt, "Sat�n Al", "Geri D�n");
		}
		case 5: {
			if (HouseInfo[houseid][hCupboard])	return SendErrorMessage(playerid, "Evinizde gardrop var.");
			if (GetCash(playerid) < 600)		return SendErrorMessage(playerid, "Gardrop almak i�in yeterli paran�z bulunmuyor, gereken �cret: $600");

			HouseInfo[houseid][hCupboard] = 1;
			SQL_SetInteger("houses", "cupboard", HouseInfo[houseid][hCupboard], HouseInfo[houseid][hID]);
			GiveCash(playerid, -600);
			SendSyntaxMessage(playerid, "600$ kar��l���nda gardrop sat�n ald�n�z.");
			SendSyntaxMessage(playerid, "Kullanmak i�in /kiyafetlerim. ");
			return 1;
		}
		case 6: { // ������ �������
			static dlgtxt[] = "Seviye\tCan\tBekleme S�resi\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF} \t + 20 HP \t + 60 saniye \t {33CC33} $400 \n\
							{C3C3C3} 2 Seviye {FFFFFF} \t + 40 HP \t + 80 saniye \t {33CC33} $800 \n\
							{C3C3C3} 3 Seviye {FFFFFF} \t + 60 HP \t + 100 saniye \t {33CC33} $1200 \n\
							{C3C3C3} 4 Seviye {FFFFFF} \t + 80 HP \t + 120 saniye \t {33CC33} $1600 \n\
							{C3C3C3} 5 Seviye {FFFFFF} \t + 100 HP \t + 140 saniye \t {33CC33} $2000";

			Dialog_Show(playerid, HouseUpgradeHeal, DIALOG_STYLE_TABLIST_HEADERS, "�lk Yard�m Kiti Geli�tirmesi", dlgtxt, "Sat�n Al", "Geri D�n");	
		}
	}

	return 1;
}

Dialog:HouseUpgradeDoor(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	listitem += 1;

	if (HouseInfo[houseid][hDoor] >= listitem)	return SendErrorMessage(playerid, "Evinizin kap� seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hDoor]);
	if (GetCash(playerid) < 750 * listitem)		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $%i.", listitem * 750);

	HouseInfo[houseid][hDoor] = listitem;
	SQL_SetInteger("houses", "door", HouseInfo[houseid][hDoor], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 750);
	SendSyntaxMessage(playerid, "$%i kar��l���nda evinizin kap�s�n� %i seviyeye y�kselttiniz.", listitem * 750, HouseInfo[houseid][hDoor]);
	return 1;
}

Dialog:HouseUpgradeLock(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	listitem += 1;

	if (HouseInfo[houseid][hLock] >= listitem)	return SendErrorMessage(playerid, "Evinizin kilit seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hLock]);
	if (GetCash(playerid) < 250 * listitem)		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $%i.", listitem * 250);
	
	HouseInfo[houseid][hLock] = listitem;
	SQL_SetInteger("houses", "lock", HouseInfo[houseid][hLock], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 250);
	SendSyntaxMessage(playerid, "$%i kar��l���nda evinizin kilidini %i seviyeye y�kselttiniz.", listitem * 250, HouseInfo[houseid][hLock]);
	return 1;
}

Dialog:HouseUpgradeAlarm(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	listitem += 1;

	if (HouseInfo[houseid][hAlarm] >= listitem)	return SendErrorMessage(playerid, "Evinizin alarm seviyesi %i oldu�u i�in i�lem ger�ekle�tirilemedi.", HouseInfo[houseid][hAlarm]);
	if (GetCash(playerid) < 500 * listitem)		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $%i.", listitem * 500);

	HouseInfo[houseid][hAlarm] = listitem;
	SQL_SetInteger("houses", "alarm", HouseInfo[houseid][hAlarm], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 500);
	SendSyntaxMessage(playerid, "$%i kar��l���nda evinizin alarm�n� %i seviyeye y�kselttiniz.", listitem * 500, HouseInfo[houseid][hAlarm]);
	return 1;
}

Dialog:HouseUpgradeHeal(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	listitem += 1;
	
	if (HouseInfo[houseid][hHeal] >= listitem)	return SendErrorMessage(playerid, "Evinizde ilk yard�m kiti bulunuyor.");
	if (GetCash(playerid) < listitem * 400)		return SendErrorMessage(playerid, "Bu i�lemi ger�ekle�tirebilmek i�in yeterli paran�z bulunmuyor, gereken tutar: $%i.", listitem * 400);

	HouseInfo[houseid][hHeal] = listitem;
	HouseInfo[houseid][hHealAmount] = 3;
	SQL_SetInteger("houses", "heal", HouseInfo[houseid][hHeal], HouseInfo[houseid][hID]);
	SQL_SetInteger("houses", "heal_amount", HouseInfo[houseid][hHealAmount], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 400);
	SendSyntaxMessage(playerid, "$%i kar��l���nda evinize %i seviye ilk yard�m kiti ald�n�z.", listitem * 400, HouseInfo[houseid][hHeal]);
	return 1;
}

Dialog:HouseSafeChoose(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_evmenu(playerid, "");
	if (!listitem)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z. ");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	if (listitem == 1)
	{
		Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "Kasaya koymak istedi�iniz para miktar�n� giriniz:\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");
	}
	
	if (listitem == 2)
	{
		static dlgtxt[] = "Kasadan almak istedi�iniz para miktar� giriniz:\n\t\t(maksimum $%s)";

		new diatxt[sizeof(dlgtxt) + 10];

		format(diatxt, sizeof(diatxt), dlgtxt, FormatNumber(HouseInfo[houseid][hCash]));
		Dialog_Show(playerid, HouseWithDraw, DIALOG_STYLE_INPUT, "Kasadan Para Al", diatxt, "Se�", "�ptal");
	}
	
	return 1;
}

Dialog:HouseDeposit(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	new amount;
	if (sscanf(inputtext, "i", amount))			 return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "Kasaya koymak istedi�iniz para miktar�n� giriniz:\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");
	if (amount > GetCash(playerid) || amount < 1) return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "YETERLI PARAYA SAHIP DEGILSIN!\n\nKasaya koymak istedi�iniz para miktar�n� giriniz:\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");

	GiveCash(playerid, -amount);
	HouseInfo[houseid][hCash] += amount;
	SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
	SendSyntaxMessage(playerid, "Evin kasas�na $%i para yat�rd�n�z. Kasada Olan Para: $%i.", amount, HouseInfo[houseid][hCash]);
	return 1;
}

Dialog:HouseWithDraw(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z. ");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	new amount;
	if (sscanf(inputtext, "i", amount))			 		 return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasadan Para �ek", "Kasadan almak istedi�iniz para miktar� giriniz:\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");
	if (amount > HouseInfo[houseid][hCash] || amount < 1) return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasadan Para �ek", "KASADA YETERLI PARA YOK!\n\nKasadan almak istedi�iniz para miktar� giriniz::\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");

	HouseInfo[houseid][hCash] -= amount;
	SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
	GiveCash(playerid, amount);
	SendSyntaxMessage(playerid, "Evin kasas�ndan $%i para �ektiniz. Kasada Kalan: $%i.", amount, HouseInfo[houseid][hCash]);

	return 1;
}

Dialog:SellHouseChoose(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yak�n de�ilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	switch(listitem)
	{
		case 0:
		{
		    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev ba�kas�na sat�l�yor. {C3C3C3}[ID / isim] [sat�� de�eri]", "Sat", "�ptal");
		}
		case 1:
		{
		    if (!IsPlayerOutsideHouse(playerid, houseid))	return SendErrorMessage(playerid, "Evin d���nda olmal�s�n.");
		        
		    static const str_size[] = "{FFFFFF}Evinizi $%i kar��l���nda sisteme satmak istedi�inizden emin misiniz? ";
			new mes[sizeof(str_size) - 2 + 12];

		 	format(mes, sizeof(mes), str_size, HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/, '%');
			Dialog_Show(playerid, SellHouse, DIALOG_STYLE_MSGBOX, "Ev Sat���", mes, "Sat", "�ptal");
		}
	}

	return 1;
}

Dialog:BuyInterior(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	    
	new houseid = strval(inputtext);

    if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID])
	{
	    Dialog_Show(playerid, BuyInterior, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Dekor Sipari�i", "{FFFFFF}Dekorunu de�i�tirmek istedi�iniz evin ID'sini giriniz:\nBu ev sana ait olmal�!", ">>>", "Kapat");
		return SendErrorMessage(playerid, "Ev bulunamad�.");
	}
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])
	{
	    Dialog_Show(playerid, BuyInterior, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Dekor Sipari�i", "{FFFFFF}Dekorunu de�i�tirmek istedi�iniz evin ID'sini giriniz:\nBu ev sana ait olmal�!", ">>>", "Kapat");
		return SendErrorMessage(playerid, "Bu ev sana ait de�il.");
	}
	
	SetPlayerBuyInterior(playerid, 1, houseid);
	return 1;
}

Dialog:BuyInteriorAccept(playerid, response, listitem, inputtext[])
{
	if (!response)	return ShowMenuForPlayer(buy_interior, playerid);

	new houseid = pTemp[playerid][pInteriorHouse]-1;

    if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID])	return SetPlayerBuyInterior(playerid, 0);
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])
	{
	    SetPlayerBuyInterior(playerid, 0);
		return SendErrorMessage(playerid, "Bu ev sana ait de�il.");
	}
	if (GetCash(playerid) < 750)
	{
	    ShowMenuForPlayer(buy_interior, playerid);
	    return SendNotCash(playerid);
	}
	
	GiveCash(playerid, -750);
	SendSyntaxMessage(playerid, "Evinizin dekorunu $750 kar��l���nda de�i�tirdiniz: [ID: %i]", houseid);
    SetHouseInterior(houseid, pTemp[playerid][pInteriorID]);
	SetPlayerBuyInterior(playerid, 0);
	
	new paycheck;

	for(new i; i < MAX_FURNITURE; i++)
	{
	    if (!HFurn[houseid][i][fID] || !HFurn[houseid][i][fOn]) continue;
	    paycheck += (HFurn[houseid][i][fMarketPrice] - (HFurn[houseid][i][fMarketPrice] & 2))  / 2;
	    HFurn[houseid][i][fID] =
	    HFurn[houseid][i][fOn] = 0;
	    DestroyDynamicObject(HFurn[houseid][i][fObject]);
	}

    HouseInfo[houseid][hFurniture] =
    HouseInfo[houseid][hOutsideFurniture] = 0;
    GiveCash(playerid, paycheck);

   	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `furnitures` WHERE `building` = %i AND `bType` = 0", HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query);
	return 1;
}

Dialog:SellHouseTo(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yak�n de�ilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	if (houseid < 0 || houseid >= MAX_HOUSES || HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return 1;
	    
    new userid, price;

	if (sscanf(inputtext, "ui", userid, price))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev Sat���. {C3C3C3}[ID / isim] [tutar]", "Sat", "�ptal");
	    return SendErrorMessage(playerid, "Ge�ersiz format.");
	}
	if (userid == playerid)
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev Sat���. {C3C3C3}[ID / isim] [tutar]", "Sat", "�ptal");
		return SendErrorMessage(playerid, "Evi kendinize satamazs�n�z.");
	}
	if (!IsPlayerLogged(userid))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev Sat���. {C3C3C3}[ID / isim] [tutar]", "Sat", "�ptal");
		return SendNotConnected(playerid);
	}
	
	if (!PlayerNearPlayer(3.0, playerid, userid))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev Sat���. {C3C3C3}[ID / isim] [tutar]", "Sat", "�ptal");
		return SendNotNearPlayer(playerid);
	}
	
	if (price < 0 || price > 100000000)
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Sat���", "{ffffff}Ev Sat���. {C3C3C3}[ID / isim] [tutar]", "Sat", "�ptal");
	    return SendErrorMessage(playerid, "Sat�� tutar� $0 ile $100,000,000 aras�nda olmal�d�r.");
	}
	
	new mes[64];
	format(mes, sizeof(mes), "sat %s", inputtext);
	pc_cmd_ev(playerid, mes);
	return 1;
}

Dialog:SellHouse(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    new houseid;

	if ((houseid = GetNearOutsideHouse(playerid)) == -1)			return SendErrorMessage(playerid, "Yak�n�n�zda ev yok.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

    new money = PlayerInfo[playerid][pCash], cash;

	GiveCash(playerid, HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/);
	PlaySound(playerid, 1052);
	SendSyntaxMessage(playerid, "Evinizi ba�ar�l� bir �ekilde satt�n�z. $%i.", HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/);

	if (HouseInfo[houseid][hCash] > 0) 
	{
		SendSyntaxMessage(playerid, "Ev kasan�zda bulunan $%i tutar hesab�n�za eklendi.", HouseInfo[houseid][hCash]);
		GiveCash(playerid, HouseInfo[houseid][hCash]);
		cash = HouseInfo[houseid][hCash];
	}

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ESKI): %i | Money(YENI): %i] ev sat�ld� [H_MYSQL: %i] for -- $%i + $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), 
	HouseInfo[houseid][hID], HouseInfo[houseid][hPrice]/2, cash);
    insert_log(mes, PROPERTY_LOG, 1, PlayerInfo[playerid][pAccID]);

	Sell_House(houseid);
	return 1;
}

Dialog:ChangeHouseInterior(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new index, houseid = GetPVarInt(playerid, "house_change");

    if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID])	return SendErrorMessage(playerid, "Ev bulunamad�.");

	for(new i = 0; i < MAX_INTERIORS; i++)
	{
		if (!AdminTeles[i][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[i][telesType]) continue;

		if (index == listitem)
		{
		    index = i;
		    break;
		}
		index++;
	}

	SetHouseInterior(houseid, index);
	SendAdmMessageToPlayer(playerid, "Ev [ID: %i | INT: %s].", houseid, AdminTeles[index][telesMapName]);
	return 1;
}

Dialog:EvictTenant(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new 
		dlgmes[128],
		name[MAX_PLAYER_NAME]
	;

	if(strfind(inputtext, "Yeni bir kirac� al", true) != -1) return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FFFFFF}Evinizi kiralamak istedi�iniz ki�inin ID/�smini giriniz.", ">>>", "Geri D�n");
	else 		  listitem--;

	SetPVarInt(playerid, #Temp, listitem);

	format(name, sizeof(name), "%s", GetPlayerNameBySqlID(pTemp[playerid][pListed][listitem]));		
	format(dlgmes, sizeof(dlgmes), "{FFFFFF}%s adl� ki�iyi ger�ekten kirac�lardan ��karmak istiyor musunuz?", name);
	
	ConfirmDialog(playerid, "Onayla", dlgmes, "EvictTenantConfirm");
	return 1;
}

Dialog:HouseRequestRent(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");
	
	new userid;
	if (sscanf(inputtext,"u", userid)) 								return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FFFFFF}Evinizi kiralamak istedi�iniz ki�inin ID/�smini giriniz.", ">>>", "Geri D�n");
    if (userid == playerid) 			  							return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FF6347}OYUNCU BULUNAMADI!\n{FFFFFF}Evinizi kiralamak istedi�iniz ki�inin ID/�smini giriniz.", ">>>", "Geri D�n");
	if (!IsPlayerLogged(userid))		  							return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FF6347}OYUNCU BULUNAMADI!\n{FFFFFF}Evinizi kiralamak istedi�iniz ki�inin ID/�smini giriniz.", ">>>", "Geri D�n");
    if (!PlayerNearPlayer(3.0, playerid, userid))					return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FF6347}OYUNCU YAKININIZDA DEGIL!\n{FFFFFF}Evinizi kiralamak istedi�iniz ki�inin ID/�smini giriniz.", ">>>", "Geri D�n");
    if (GetPlayerHouses(userid) || PlayerInfo[userid][pRentKey])	return SendErrorMessage(playerid, "Belirtilen oyuncunun evi var veya ba�ka evde kirac�.");

	SetPVarInt(playerid, #RentUserid, userid);
	Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FFFFFF}Kira �creti:", ">>>", "Geri D�n");
	return 1;
}

Dialog:HouseRequestRent2(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	
	new price, userid = GetPVarInt(playerid, #RentUserid);
	if (sscanf(inputtext,"i", price)) 	return Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FFFFFF}Kira �creti:", ">>>", "Geri D�n");
	if (price < 0 || price > 500) 		return Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kirac�", "{FF6347}Kira �creti $0 ile $500 aras�nda olmal�d�r!\n{FFFFFF}Kira �creti:", ">>>", "Geri D�n");
	if (GetCash(userid) < price)		return SendErrorMessage(playerid, "Belirtilen oyuncunun yeterli paras� bulunmuyor.");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin i�inde olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait de�il.");

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `users` WHERE `rent_key`=%i", HouseInfo[houseid][hID]);
	mysql_tquery(dbHandle, query, "OfferRentRoom", "iii", playerid, userid, price);

	return 1;
}

Dialog:StartBreakingLock(playerid, response, listitem, inputtext[])
{
	new houseid = BreakingHouse[playerid];
    
	BreakingHouse[playerid] = 0;
	
	if (!response)									  return 1;
	if (!IsPlayerOutsideHouse(playerid, houseid, 3.0)) return SendErrorMessage(playerid, "Evin giri�ine yak�n olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] == 0)   		  return SendErrorMessage(playerid, "Yaln�zca sat�n al�nan evlerde h�rs�zl�k yap�labilir.");
	if (HouseInfo[houseid][hLocked] == 0)   			  return SendErrorMessage(playerid, "Bu evin kap�s� kilitli de�il.");
	if (IsPlayerCrouching(playerid) == false)		  return SendErrorMessage(playerid, "E�ilmek zorundas�n.");
 
	if (pTemp[playerid][JackingType] == 3) {
		
		new htime;
		
		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		JackingLock[playerid] = htime;	

	} else if (pTemp[playerid][JackingType] == 4) {
		if (!CheckHanditem(playerid,18634)) return SendErrorMessage(playerid, "Elinizde bir levye olmal�. /aksesuar");
		PlaySound(playerid, 1138);
		HouseAlarm(houseid, true);

		new htime;
		
		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		JackingLock[playerid] = htime;	

	} else return 1;
	
	BreakingHouse[playerid] = houseid;
	pc_cmd_me(playerid, "bir �ey ��kart�r ve �n kap�n�n kilidiyle oynamaya ba�lar.");
	return 1;
}

Dialog:StartStealingHouse(playerid, response, listitem, inputtext[])
{
	new houseid = StealingHouse[playerid];
    
	StealingHouse[playerid] = 0;
	
	if (!response)									  return 1;
	if (!IsPlayerInsideHouse(playerid, houseid, 50.0)) return SendErrorMessage(playerid, "Evin giri�ine yak�n olmal�s�n�z.");
	if (HouseInfo[houseid][hOwnerID] == 0)   		  return SendErrorMessage(playerid, "Yaln�zca sat�n al�nan evlerde h�rs�zl�k yap�labilir.");
 
	if (pTemp[playerid][JackingType] == 5) {	
		new htime;
		
		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		JackingLock[playerid] = htime;	

	} else if (pTemp[playerid][JackingType] == 6) {
		if (!CheckHanditem(playerid,18634)) return SendErrorMessage(playerid, "Elinizde bir levye olmal�. /aksesuar");
		PlaySound(playerid, 1138);
		HouseAlarm(houseid, true);


        ApplyAnimation(playerid, "COP_AMBIENT", "COPBROWSE_LOOP", 4.0, 1, 0, 0, 0, 0);
	    new Float: x, Float: y, Float: z, Float: a;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);
			
		x += (1.25 * floatsin(-a, degrees));
		y += (1.25 * floatcos(-a, degrees));
		PlayerInfo[playerid][SafeObject][0] = CreateDynamicObject(19618, x, y, z-0.55, 0.0, 0.0, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

        a += 90.0;
		x += (0.42 * floatsin(-a, degrees)) + (-0.22 * floatsin(-(a - 90.0), degrees));
		y += (0.42 * floatcos(-a, degrees)) + (-0.22 * floatcos(-(a - 90.0), degrees));
		PlayerInfo[playerid][SafeObject][1] = CreateDynamicObject(19619, x, y, z-0.55, 0.0, 0.0, a + 270.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
					
        Streamer_Update(playerid);

		new htime;
		
		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		JackingLock[playerid] = htime;	

	} else return 1;
	
	StealingHouse[playerid] = houseid;
	pc_cmd_me(playerid, "levye ile evde bulunan kasay� par�alamaya ba�lar.");
	return 1;
}