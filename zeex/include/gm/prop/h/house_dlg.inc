Dialog:HouseMenu(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new houseid;
	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yakýn deðilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	switch(listitem)
	{
	    case 0: pc_cmd_kilit(playerid, ""); // äâåðíîé çàìîê
		case 1: { //Óëó÷øåíèÿ äîìà
			static dlgtxt[] = "{FFFFFF}Kapýyý tamir et {33CC33} [$ 300] {FFFFFF}\n\
								Radyo satýn al {33CC33} [$ 500] {FFFFFF}\n\
								Kapýyý geliþtir\n\
								Kilidi geliþtir\n\
								Alarmý geliþtir\n\
								Gardrop satýn al {33CC33} [$ 600] {FFFFFF}\n\
								Ýlk yardým kiti satýn al";

			new diatxt[sizeof(dlgtxt) + 30], door[40];	

			if (!HouseInfo[houseid][hDDoor]) format(door, sizeof(door), "{9ACD32}Gerekli Deðil{FFFFFF}");
			else 							format(door, sizeof(door), "{FF6347}Gerekli{FFFFFF}");

			format(diatxt, sizeof(diatxt), dlgtxt, door);

			Dialog_Show(playerid, HouseUpgrade, DIALOG_STYLE_LIST, "Ev Geliþtirmeleri", diatxt, "Seç", "Geri Dön");
		}
		case 2: pc_cmd_dekorasyon(playerid, "");
		case 3:
		{
		    new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT `id`, `name` FROM `users` WHERE `rent_key` = %i LIMIT %i", HouseInfo[houseid][hID], MAX_TENAT_SPACE);
			mysql_tquery(dbHandle, query, "ShowTenantsAmount", "i", playerid);
		}
		case 4: //Èíâåíòàðü äîìà
		{
		    if (!IsPlayerInsideHouse(playerid, houseid))		return SendErrorMessage(playerid, "Evde olmalýsýnýz.");
		        
			PrintHouseInv(playerid, houseid);
		}
		case 5:
		{
			static dlgtxt[] = "Kasa: $%i\n\
								{FF6347}>{FFFFFF} Kasaya para koy\n\
								{FF6347}>{FFFFFF} Kasadan para al";

			new diatxt[sizeof(dlgtxt) + 11];		
			format(diatxt, sizeof(diatxt), dlgtxt, HouseInfo[houseid][hCash]);

			Dialog_Show(playerid, HouseSafeChoose, DIALOG_STYLE_TABLIST, "Kasa", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 6: pc_cmd_kiyafetlerim(playerid, "");
		case 7: Dialog_Show(playerid, SellHouseChoose, DIALOG_STYLE_LIST, "{FFFFFF}Satýlýk Ev", "Evi oyuncuya sat\nEvi sisteme sat", "Seç", "Geri Dön");
	}
	return 1;
}

Dialog:HouseUpgrade(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	switch(listitem)
	{
		case 0: {
			if (!HouseInfo[houseid][hDDoor])	return SendErrorMessage(playerid, "Evin kapýsý hasarlý deðil.");
			if (GetCash(playerid) < 300)		return SendErrorMessage(playerid, "Evin kapýsýný tamir ettirebilmek için yeterli paranýz bulunmuyor, fiyat: $300");

			HouseInfo[houseid][hDDoor] = 0;
			SQL_SetInteger("houses", "ddoor", HouseInfo[houseid][hDDoor], HouseInfo[houseid][hID]);
			UpdateHouseDoor(houseid);
			GiveCash(playerid, -300);
			SendSyntaxMessage(playerid, "$300 karþýlýðýnda evin kapýsýný tamir ettirdiniz.");
			return 1;
		}
		case 1: {
			if (HouseInfo[houseid][hRadio])	return SendErrorMessage(playerid, "Evde radyo bulunuyor.");
			if (GetCash(playerid) < 500)		return SendErrorMessage(playerid, "Radyo satýn alabilmek için yeterli paranýz bulunmuyor, fiyat: $500.");

			HouseInfo[houseid][hRadio] = 1;
			SQL_SetInteger("houses", "radio", HouseInfo[houseid][hRadio], HouseInfo[houseid][hID]);
			GiveCash(playerid, -500);
			SendSyntaxMessage(playerid, "$500 karþýlýðýnda radyo satýn aldýnýz, kullaným: /radyoayarla.");
			return 1;
		}
		case 2: {
			static dlgtxt[] = "Seviye\tKapý Tipi\tÖzellikler\tFiyat\n\
								{C3C3C3} 1 Seviye {FFFFFF}\t Ahþap\t + 5% hýrsýzlýða karþý koruma\t {33CC33} $750\n\
								{C3C3C3} 2 Seviye {FFFFFF}\t Demir\t + 15% hýrsýzlýða karþý koruma\t {33CC33} $1500";

			Dialog_Show(playerid, HouseUpgradeDoor, DIALOG_STYLE_TABLIST_HEADERS, "Kapý Geliþtirmesi", dlgtxt, "Satýn Al", "Geri Dön");
		}
		case 3: {
			static dlgtxt[] = "Seviye\tÖzellikler\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF}\t + 5% hýrsýzlýða karþý koruma\t {33CC33} $250\n\
							{C3C3C3} 2 Seviye {FFFFFF}\t + 10% hýrsýzlýða karþý koruma\t {33CC33} $500\n\
							{C3C3C3} 3 Seviye {FFFFFF}\t + 15% hýrsýzlýða karþý koruma\t {33CC33} $750\n\
							{C3C3C3} 4 Seviye {FFFFFF}\t + 20% hýrsýzlýða karþý koruma\t {33CC33} $1000\n\
							{C3C3C3} 5 Seviye {FFFFFF}\t + 25% hýrsýzlýða karþý koruma\t {33CC33} $1250";

			Dialog_Show(playerid, HouseUpgradeLock, DIALOG_STYLE_TABLIST_HEADERS, "Kilit Geliþtirmesi", dlgtxt, "Satýn Al", "Geri Dön");
		}
		case 4: {
			static dlgtxt[] = "Seviye\tÖzellikler\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF} \tStandart \t {33CC33} $500 \n\
							{C3C3C3} 2 Seviye {FFFFFF} \tOrta \t {33CC33} $1000 \n\
							{C3C3C3} 3 Seviye {FFFFFF} \tÝyi \t {33CC33} $1500";
			Dialog_Show(playerid, HouseUpgradeAlarm, DIALOG_STYLE_TABLIST_HEADERS, "Alarm Geliþtirmesi", dlgtxt, "Satýn Al", "Geri Dön");
		}
		case 5: {
			if (HouseInfo[houseid][hCupboard])	return SendErrorMessage(playerid, "Evinizde gardrop var.");
			if (GetCash(playerid) < 600)		return SendErrorMessage(playerid, "Gardrop almak için yeterli paranýz bulunmuyor, gereken ücret: $600");

			HouseInfo[houseid][hCupboard] = 1;
			SQL_SetInteger("houses", "cupboard", HouseInfo[houseid][hCupboard], HouseInfo[houseid][hID]);
			GiveCash(playerid, -600);
			SendSyntaxMessage(playerid, "600$ karþýlýðýnda gardrop satýn aldýnýz.");
			SendSyntaxMessage(playerid, "Kullanmak için /kiyafetlerim. ");
			return 1;
		}
		case 6: { // Êóïèòü àïòå÷êó
			static dlgtxt[] = "Seviye\tCan\tBekleme Süresi\tFiyat\n\
							{C3C3C3} 1 Seviye {FFFFFF} \t + 20 HP \t + 60 saniye \t {33CC33} $400 \n\
							{C3C3C3} 2 Seviye {FFFFFF} \t + 40 HP \t + 80 saniye \t {33CC33} $800 \n\
							{C3C3C3} 3 Seviye {FFFFFF} \t + 60 HP \t + 100 saniye \t {33CC33} $1200 \n\
							{C3C3C3} 4 Seviye {FFFFFF} \t + 80 HP \t + 120 saniye \t {33CC33} $1600 \n\
							{C3C3C3} 5 Seviye {FFFFFF} \t + 100 HP \t + 140 saniye \t {33CC33} $2000";

			Dialog_Show(playerid, HouseUpgradeHeal, DIALOG_STYLE_TABLIST_HEADERS, "Ýlk Yardým Kiti Geliþtirmesi", dlgtxt, "Satýn Al", "Geri Dön");	
		}
	}

	return 1;
}

Dialog:HouseUpgradeDoor(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	listitem += 1;

	if (HouseInfo[houseid][hDoor] >= listitem)	return SendErrorMessage(playerid, "Evinizin kapý seviyesi %i olduðu için iþlem gerçekleþtirilemedi.", HouseInfo[houseid][hDoor]);
	if (GetCash(playerid) < 750 * listitem)		return SendErrorMessage(playerid, "Bu iþlemi gerçekleþtirebilmek için yeterli paranýz bulunmuyor, gereken tutar: $%i.", listitem * 750);

	HouseInfo[houseid][hDoor] = listitem;
	SQL_SetInteger("houses", "door", HouseInfo[houseid][hDoor], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 750);
	SendSyntaxMessage(playerid, "$%i karþýlýðýnda evinizin kapýsýný %i seviyeye yükselttiniz.", listitem * 750, HouseInfo[houseid][hDoor]);
	return 1;
}

Dialog:HouseUpgradeLock(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	listitem += 1;

	if (HouseInfo[houseid][hLock] >= listitem)	return SendErrorMessage(playerid, "Evinizin kilit seviyesi %i olduðu için iþlem gerçekleþtirilemedi.", HouseInfo[houseid][hLock]);
	if (GetCash(playerid) < 250 * listitem)		return SendErrorMessage(playerid, "Bu iþlemi gerçekleþtirebilmek için yeterli paranýz bulunmuyor, gereken tutar: $%i.", listitem * 250);
	
	HouseInfo[houseid][hLock] = listitem;
	SQL_SetInteger("houses", "lock", HouseInfo[houseid][hLock], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 250);
	SendSyntaxMessage(playerid, "$%i karþýlýðýnda evinizin kilidini %i seviyeye yükselttiniz.", listitem * 250, HouseInfo[houseid][hLock]);
	return 1;
}

Dialog:HouseUpgradeAlarm(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	listitem += 1;

	if (HouseInfo[houseid][hAlarm] >= listitem)	return SendErrorMessage(playerid, "Evinizin alarm seviyesi %i olduðu için iþlem gerçekleþtirilemedi.", HouseInfo[houseid][hAlarm]);
	if (GetCash(playerid) < 500 * listitem)		return SendErrorMessage(playerid, "Bu iþlemi gerçekleþtirebilmek için yeterli paranýz bulunmuyor, gereken tutar: $%i.", listitem * 500);

	HouseInfo[houseid][hAlarm] = listitem;
	SQL_SetInteger("houses", "alarm", HouseInfo[houseid][hAlarm], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 500);
	SendSyntaxMessage(playerid, "$%i karþýlýðýnda evinizin alarmýný %i seviyeye yükselttiniz.", listitem * 500, HouseInfo[houseid][hAlarm]);
	return 1;
}

Dialog:HouseUpgradeHeal(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	listitem += 1;
	
	if (HouseInfo[houseid][hHeal] >= listitem)	return SendErrorMessage(playerid, "Evinizde ilk yardým kiti bulunuyor.");
	if (GetCash(playerid) < listitem * 400)		return SendErrorMessage(playerid, "Bu iþlemi gerçekleþtirebilmek için yeterli paranýz bulunmuyor, gereken tutar: $%i.", listitem * 400);

	HouseInfo[houseid][hHeal] = listitem;
	HouseInfo[houseid][hHealAmount] = 3;
	SQL_SetInteger("houses", "heal", HouseInfo[houseid][hHeal], HouseInfo[houseid][hID]);
	SQL_SetInteger("houses", "heal_amount", HouseInfo[houseid][hHealAmount], HouseInfo[houseid][hID]);
	GiveCash(playerid, -listitem * 400);
	SendSyntaxMessage(playerid, "$%i karþýlýðýnda evinize %i seviye ilk yardým kiti aldýnýz.", listitem * 400, HouseInfo[houseid][hHeal]);
	return 1;
}

Dialog:HouseSafeChoose(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_evmenu(playerid, "");
	if (!listitem)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz. ");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	if (listitem == 1)
	{
		Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "Kasaya koymak istediðiniz para miktarýný giriniz:\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");
	}
	
	if (listitem == 2)
	{
		static dlgtxt[] = "Kasadan almak istediðiniz para miktarý giriniz:\n\t\t(maksimum $%s)";

		new diatxt[sizeof(dlgtxt) + 10];

		format(diatxt, sizeof(diatxt), dlgtxt, FormatNumber(HouseInfo[houseid][hCash]));
		Dialog_Show(playerid, HouseWithDraw, DIALOG_STYLE_INPUT, "Kasadan Para Al", diatxt, "Seç", "Ýptal");
	}
	
	return 1;
}

Dialog:HouseDeposit(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	new amount;
	if (sscanf(inputtext, "i", amount))			 return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "Kasaya koymak istediðiniz para miktarýný giriniz:\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");
	if (amount > GetCash(playerid) || amount < 1) return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasaya Para Koy", "YETERLI PARAYA SAHIP DEGILSIN!\n\nKasaya koymak istediðiniz para miktarýný giriniz:\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");

	GiveCash(playerid, -amount);
	HouseInfo[houseid][hCash] += amount;
	SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
	SendSyntaxMessage(playerid, "Evin kasasýna $%i para yatýrdýnýz. Kasada Olan Para: $%i.", amount, HouseInfo[houseid][hCash]);
	return 1;
}

Dialog:HouseWithDraw(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz. ");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	new amount;
	if (sscanf(inputtext, "i", amount))			 		 return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasadan Para Çek", "Kasadan almak istediðiniz para miktarý giriniz:\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");
	if (amount > HouseInfo[houseid][hCash] || amount < 1) return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "Kasadan Para Çek", "KASADA YETERLI PARA YOK!\n\nKasadan almak istediðiniz para miktarý giriniz::\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");

	HouseInfo[houseid][hCash] -= amount;
	SQL_SetInteger("houses", "cash", HouseInfo[houseid][hCash], HouseInfo[houseid][hID]);
	GiveCash(playerid, amount);
	SendSyntaxMessage(playerid, "Evin kasasýndan $%i para çektiniz. Kasada Kalan: $%i.", amount, HouseInfo[houseid][hCash]);

	return 1;
}

Dialog:SellHouseChoose(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");

	new houseid;

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yakýn deðilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	switch(listitem)
	{
		case 0:
		{
		    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev baþkasýna satýlýyor. {C3C3C3}[ID / isim] [satýþ deðeri]", "Sat", "Ýptal");
		}
		case 1:
		{
		    if (!IsPlayerOutsideHouse(playerid, houseid))	return SendErrorMessage(playerid, "Evin dýþýnda olmalýsýn.");
		        
		    static const str_size[] = "{FFFFFF}Evinizi $%i karþýlýðýnda sisteme satmak istediðinizden emin misiniz? ";
			new mes[sizeof(str_size) - 2 + 12];

		 	format(mes, sizeof(mes), str_size, HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/, '%');
			Dialog_Show(playerid, SellHouse, DIALOG_STYLE_MSGBOX, "Ev Satýþý", mes, "Sat", "Ýptal");
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
	    Dialog_Show(playerid, BuyInterior, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Dekor Sipariþi", "{FFFFFF}Dekorunu deðiþtirmek istediðiniz evin ID'sini giriniz:\nBu ev sana ait olmalý!", ">>>", "Kapat");
		return SendErrorMessage(playerid, "Ev bulunamadý.");
	}
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])
	{
	    Dialog_Show(playerid, BuyInterior, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Dekor Sipariþi", "{FFFFFF}Dekorunu deðiþtirmek istediðiniz evin ID'sini giriniz:\nBu ev sana ait olmalý!", ">>>", "Kapat");
		return SendErrorMessage(playerid, "Bu ev sana ait deðil.");
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
		return SendErrorMessage(playerid, "Bu ev sana ait deðil.");
	}
	if (GetCash(playerid) < 750)
	{
	    ShowMenuForPlayer(buy_interior, playerid);
	    return SendNotCash(playerid);
	}
	
	GiveCash(playerid, -750);
	SendSyntaxMessage(playerid, "Evinizin dekorunu $750 karþýlýðýnda deðiþtirdiniz: [ID: %i]", houseid);
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

	if ((houseid = GetNearHouse(playerid)) == -1)					return SendErrorMessage(playerid, "Eve yakýn deðilsin.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

	if (houseid < 0 || houseid >= MAX_HOUSES || HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return 1;
	    
    new userid, price;

	if (sscanf(inputtext, "ui", userid, price))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev Satýþý. {C3C3C3}[ID / isim] [tutar]", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "Geçersiz format.");
	}
	if (userid == playerid)
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev Satýþý. {C3C3C3}[ID / isim] [tutar]", "Sat", "Ýptal");
		return SendErrorMessage(playerid, "Evi kendinize satamazsýnýz.");
	}
	if (!IsPlayerLogged(userid))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev Satýþý. {C3C3C3}[ID / isim] [tutar]", "Sat", "Ýptal");
		return SendNotConnected(playerid);
	}
	
	if (!PlayerNearPlayer(3.0, playerid, userid))
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev Satýþý. {C3C3C3}[ID / isim] [tutar]", "Sat", "Ýptal");
		return SendNotNearPlayer(playerid);
	}
	
	if (price < 0 || price > 100000000)
	{
	    Dialog_Show(playerid, SellHouseTo, DIALOG_STYLE_INPUT, "{FFFFFF}Ev Satýþý", "{ffffff}Ev Satýþý. {C3C3C3}[ID / isim] [tutar]", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "Satýþ tutarý $0 ile $100,000,000 arasýnda olmalýdýr.");
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

	if ((houseid = GetNearOutsideHouse(playerid)) == -1)			return SendErrorMessage(playerid, "Yakýnýnýzda ev yok.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

    new money = PlayerInfo[playerid][pCash], cash;

	GiveCash(playerid, HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/);
	PlaySound(playerid, 1052);
	SendSyntaxMessage(playerid, "Evinizi baþarýlý bir þekilde sattýnýz. $%i.", HouseInfo[houseid][hPrice]/2/*+GetFurniturePrice(0, houseid)*/);

	if (HouseInfo[houseid][hCash] > 0) 
	{
		SendSyntaxMessage(playerid, "Ev kasanýzda bulunan $%i tutar hesabýnýza eklendi.", HouseInfo[houseid][hCash]);
		GiveCash(playerid, HouseInfo[houseid][hCash]);
		cash = HouseInfo[houseid][hCash];
	}

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money(ESKI): %i | Money(YENI): %i] ev satýldý [H_MYSQL: %i] for -- $%i + $%i", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), 
	HouseInfo[houseid][hID], HouseInfo[houseid][hPrice]/2, cash);
    insert_log(mes, PROPERTY_LOG, 1, PlayerInfo[playerid][pAccID]);

	Sell_House(houseid);
	return 1;
}

Dialog:ChangeHouseInterior(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new index, houseid = GetPVarInt(playerid, "house_change");

    if (houseid < 0 || houseid >= MAX_HOUSES || !HouseInfo[houseid][hID])	return SendErrorMessage(playerid, "Ev bulunamadý.");

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

	if(strfind(inputtext, "Yeni bir kiracý al", true) != -1) return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FFFFFF}Evinizi kiralamak istediðiniz kiþinin ID/Ýsmini giriniz.", ">>>", "Geri Dön");
	else 		  listitem--;

	SetPVarInt(playerid, #Temp, listitem);

	format(name, sizeof(name), "%s", GetPlayerNameBySqlID(pTemp[playerid][pListed][listitem]));		
	format(dlgmes, sizeof(dlgmes), "{FFFFFF}%s adlý kiþiyi gerçekten kiracýlardan çýkarmak istiyor musunuz?", name);
	
	ConfirmDialog(playerid, "Onayla", dlgmes, "EvictTenantConfirm");
	return 1;
}

Dialog:HouseRequestRent(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_evmenu(playerid, "");
	
	new userid;
	if (sscanf(inputtext,"u", userid)) 								return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FFFFFF}Evinizi kiralamak istediðiniz kiþinin ID/Ýsmini giriniz.", ">>>", "Geri Dön");
    if (userid == playerid) 			  							return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FF6347}OYUNCU BULUNAMADI!\n{FFFFFF}Evinizi kiralamak istediðiniz kiþinin ID/Ýsmini giriniz.", ">>>", "Geri Dön");
	if (!IsPlayerLogged(userid))		  							return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FF6347}OYUNCU BULUNAMADI!\n{FFFFFF}Evinizi kiralamak istediðiniz kiþinin ID/Ýsmini giriniz.", ">>>", "Geri Dön");
    if (!PlayerNearPlayer(3.0, playerid, userid))					return Dialog_Show(playerid, HouseRequestRent, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FF6347}OYUNCU YAKININIZDA DEGIL!\n{FFFFFF}Evinizi kiralamak istediðiniz kiþinin ID/Ýsmini giriniz.", ">>>", "Geri Dön");
    if (GetPlayerHouses(userid) || PlayerInfo[userid][pRentKey])	return SendErrorMessage(playerid, "Belirtilen oyuncunun evi var veya baþka evde kiracý.");

	SetPVarInt(playerid, #RentUserid, userid);
	Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FFFFFF}Kira Ücreti:", ">>>", "Geri Dön");
	return 1;
}

Dialog:HouseRequestRent2(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	
	new price, userid = GetPVarInt(playerid, #RentUserid);
	if (sscanf(inputtext,"i", price)) 	return Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FFFFFF}Kira Ücreti:", ">>>", "Geri Dön");
	if (price < 0 || price > 500) 		return Dialog_Show(playerid, HouseRequestRent2, DIALOG_STYLE_INPUT, "Yeni Kiracý", "{FF6347}Kira ücreti $0 ile $500 arasýnda olmalýdýr!\n{FFFFFF}Kira Ücreti:", ">>>", "Geri Dön");
	if (GetCash(userid) < price)		return SendErrorMessage(playerid, "Belirtilen oyuncunun yeterli parasý bulunmuyor.");

	new houseid;
	if ((houseid = GetNearInsideHouse(playerid)) == -1)				return SendErrorMessage(playerid, "Evin içinde olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu ev sana ait deðil.");

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
	if (!IsPlayerOutsideHouse(playerid, houseid, 3.0)) return SendErrorMessage(playerid, "Evin giriþine yakýn olmalýsýnýz.");
	if (HouseInfo[houseid][hOwnerID] == 0)   		  return SendErrorMessage(playerid, "Yalnýzca satýn alýnan evlerde hýrsýzlýk yapýlabilir.");
	if (HouseInfo[houseid][hLocked] == 0)   			  return SendErrorMessage(playerid, "Bu evin kapýsý kilitli deðil.");
	if (IsPlayerCrouching(playerid) == false)		  return SendErrorMessage(playerid, "Eðilmek zorundasýn.");
 
	if (pTemp[playerid][JackingType] == 3) {
		if (!IsPlayerHasItem(playerid, INV_PICKLOCK)) return SendErrorMessage(playerid, "Aracýn kilidini kýrmak için maymuncuða ihtiyacýnýz var.");
		
		new htime;
		
		switch(HouseInfo[houseid][hDoor]) {
			case 0: htime = 250+HouseInfo[houseid][hLock]*250;
			case 1: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.05);
			case 2: htime = 250+HouseInfo[houseid][hLock]*250 + floatround((250+HouseInfo[houseid][hLock]*250) * 0.15);
		}

		JackingLock[playerid] = htime;	
		RemovePlayerItem(playerid, INV_PICKLOCK, 1);

	} else if (pTemp[playerid][JackingType] == 4) {
		if (!CheckHanditem(playerid,18634)) return SendErrorMessage(playerid, "Elinizde bir levye olmalý.");
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
	pc_cmd_me(playerid, "bir þey çýkartýr ve ön kapýnýn kilidiyle oynamaya baþlar.");
	return 1;
}