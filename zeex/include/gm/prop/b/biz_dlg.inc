Dialog:BusinessMenu(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	switch(listitem)
	{
		case 0: //Èíôîðìàöèÿ î áèçíåñå
		{
			new diatxt[400];
			format(diatxt, sizeof(diatxt), "{FFFFFF}Mekan ID:\t%d\nÝsim:\t%s\nMekan tipi:\t%s\nDurum:\t%s\n", BizInfo[bizid][bizID], BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]], (BizInfo[bizid][bizLocked]) ? ("Kapalý") : ("Açýk"));
			format(diatxt, sizeof(diatxt), "%sMekan kasasý:\t$%i\nGiriþ ücreti:\t$%i\n\nDepolama durumu: %i / 400\n", diatxt, BizInfo[bizid][bizCash], BizInfo[bizid][bizEntrance], BizInfo[bizid][bizProduct]);

			new id = biz_prod_types[BizInfo[bizid][bizType]];
            
			if(id != -1) format(diatxt, sizeof(diatxt), "%sSipariþ: %s $%i / 1 ürün", diatxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);

			Dialog_Show(playerid, BusinessMenuInfo, DIALOG_STYLE_MSGBOX, "Mekan Bilgisi", diatxt, "Geri Dön", "");
			return 1;
		}
		case 1: //Èíôîðìàöèþ î ñîòðóäíèêàõ
		{
			static dlgtxt[] = "Ýsim\tPozisyon\n\
					{FF6347}>{FFFFFF} Yeni bir iþçi al\n";

			new diatxt[sizeof(dlgtxt) + 10*(24+32)],
				count;

			format(diatxt, sizeof(diatxt), "%s", dlgtxt);
			for(new i = 0; i < MAX_WORK_SPACE; i++)
			{
				if (!BizWorkers[bizid][i][bizJobOn]) continue;

				count++;
				format(diatxt, sizeof(diatxt), "%s%i. %s\t%s\n", diatxt, i+1, BizWorkers[bizid][i][bizWorker], BizWorkers[bizid][i][bizPosition]);
			}		
			
			Dialog_Show(playerid, WorkerInfo, DIALOG_STYLE_TABLIST_HEADERS, "Çalýþan Bilgisi", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 2: //Êàññà - ïîëîæèòü / âçÿòü
		{
			static dlgtxt[] = "Kasada bulunan: $%i\n\
								{FF6347}>{FFFFFF} Para yatýr\n\
								{FF6347}>{FFFFFF} Para çek";

			new diatxt[sizeof(dlgtxt) + 11];		
			format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizCash]);

			Dialog_Show(playerid, TillOperations, DIALOG_STYLE_TABLIST, "Kasa", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 3: //Êîíôèãóðàöèÿ öåí
		{
			new diatxt[128];
			
			if (BizInfo[bizid][bizType] == BIZ_GAS_STATION)	format(diatxt, sizeof(diatxt), "{FFFFFF}Litre fiyatý: $%i", BizInfo[bizid][bizEntrance]);
			else 											format(diatxt, sizeof(diatxt), "{FFFFFF}Giriþ ücreti: $%i", BizInfo[bizid][bizEntrance]);

			new biz = BizInfo[bizid][bizType];
			if (biz == BIZ_STORE || 
				biz == BIZ_BAR ||
				biz == BIZ_PHARMACY || 
				biz == BIZ_PIZZA || 
				biz == BIZ_CLUCKIN || 
				biz == BIZ_BURGER || 
				biz == BIZ_DONUT) format(diatxt, sizeof(diatxt), "%s\n> Ürün fiyatý güncelleme", diatxt);
	
			Dialog_Show(playerid, ChooseConfigPrices, DIALOG_STYLE_TABLIST, "Ürün güncelleme", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 4: //Óëó÷øåíèÿ áèçíåñà
		{
			Dialog_Show(playerid, BizUpgrade, DIALOG_STYLE_TABLIST, "Mekan geliþimleri", "Ses sistemi al {33CC33}[$100]{FFFFFF}\nKapýyý tamir et {33CC33}[$1500]{FFFFFF}", "Seç", "Geri Dön");
			return 1;
		}
		case 5: pc_cmd_dekorasyon(playerid, "");
		case 6: //Çàêóïêà ïðîäóêòîâ
		{
			new id = biz_prod_types[BizInfo[bizid][bizType]];

			if(id == -1) pc_cmd_mekanmenu(playerid, "");
			
			static dlgtxt[] = "(%s) adlý ürünün 1 adetini $%i fiyatýndan satýyorsun.\nÜrünün yeni fiyatýný gir:";

			new diatxt[sizeof(dlgtxt) + 128];	

			format(diatxt, sizeof(diatxt), dlgtxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);
			Dialog_Show(playerid, ProductBuying, DIALOG_STYLE_INPUT, "Ürünler", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 7: //Èçìåíèòü íàçâàíèå
		{
			static dlgtxt[] = "Güncel isim: %s\nYeni isim giriniz:";

			new diatxt[sizeof(dlgtxt) + 24];

			format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizName]);
			Dialog_Show(playerid, ChangeBizName, DIALOG_STYLE_INPUT, "Ýsim deðiþimi", diatxt, "Seç", "Geri Dön");
			return 1;
		}
		case 8: //Èçìåíèòü íàäïèñü ïðè âõîäå
		{	
			Dialog_Show(playerid, DoorName, DIALOG_STYLE_LIST, "Giriþ yazýsýný deðiþtirme", "Düzenle\nKaldýr", "Seç", "Geri Dön");
			return 1;
		}
		case 9: //Ïðîäàòü áèçíåñ
		{
			Dialog_Show(playerid, SellBiz, DIALOG_STYLE_LIST, "Mekan satýþý", "Oyuncuya sat\nDevlete sat", "Seç", "Geri Dön");
			return 1;
		}
	}

	return 1;
}

Dialog:SellPawn(playerid, response, listitem, inputtext[])
{
	if (!response) return 0;
    
	switch(listitem)
	{
		case 0:
		{
			if(!PlayerInfo[playerid][pCalintiRadyo]) return SendErrorMessage(playerid, "Üzerinizde çalýntý radyo bulunmuyor.");

			PlayerInfo[playerid][pCalintiRadyo] = 0;
			SendServerMessage(playerid, "Pawnshop dükkaný, $%d karþýlýðýnda çalýntý radyoyu senden satýn aldý.", PRICE_RADIO);
			GiveCash(playerid, PRICE_RADIO);
		}
	}

	return 1;
}

Dialog:SellBiz(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_mekanmenu(playerid, "");

    new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan satýþý", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "Ýptal");
		}
		case 1:
		{
			static const str_size[] = "{FFFFFF}$%i karþýlýðýnda mekaný satmaktan emin misiniz?";
			new mes[sizeof(str_size) - 2 + 12];

			format(mes, sizeof(mes), str_size, BizInfo[bizid][bizPrice] / 2);
			Dialog_Show(playerid, SellBizState, DIALOG_STYLE_MSGBOX, "{FFFFFF}Mekan satýþý", mes, "Sat", "Ýptal");
		}
	}
	return 1;
}

Dialog:SellBizTo(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (bizid < 0 || bizid >= MAX_BIZ || BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return 1;
	    
    new userid, price;

	if (sscanf(inputtext, "ui", userid, price))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan satýþý", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "Geçersiz bir giriþ yaptýnýz.");
	}
	
	if (!IsPlayerLogged(userid))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan satýþý", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "Ýptal");
		return SendNotConnected(playerid);
	}
	
	if (!PlayerNearPlayer(3.0, playerid, userid))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan satýþý", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "Ýptal");
		return SendNotNearPlayer(playerid);
	}
	
	if (price < 0 || price > 100000000)
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan satýþý", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "Ýptal");
	    return SendErrorMessage(playerid, "1 milyon dolarýn üzerinde fiyat belirleyemezsiniz.");
	}
	
	pTemp[userid][pBizPrice] = price;
	pTemp[userid][pBizPlayer] = playerid;
	pTemp[userid][pBizID] = bizid;

	SetPVarInt(userid, #accept_time, gettime() + 30);
	SendSyntaxMessage(playerid, "%s adlý kiþiye $%i karþýlýðýnda mekaný satma teklifi sundunuz.", GetNameEx(userid), price);
	SendSyntaxMessage(userid, "%s adlý kiþi size $%i karþýlýðýnda mekaný satma teklifi sundu. Y tuþu ile satýn alabilirsin.", GetNameEx(playerid), price);
	return 1;
}

Dialog:SellBizState(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	PlaySound(playerid, 1052);

	new biz_cost = BizInfo[bizid][bizPrice] / 2, money = PlayerInfo[playerid][pCash], cash;

	GiveCash(playerid, biz_cost);
	SendSyntaxMessage(playerid, "Baþarýyla \"%s\" adlý mekaný $%i karþýlýðýnda sattýnýz.",BizInfo[bizid][bizName], biz_cost);

	if (BizInfo[bizid][bizCash] > 0)
	{
		SendSyntaxMessage(playerid,"Mekan satýldýktan sonra kasada bulunan $%i, size geri verildi.", BizInfo[bizid][bizCash]);
		GiveCash(playerid, BizInfo[bizid][bizCash]);
		cash = BizInfo[bizid][bizCash];
	}

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Eski Para: %i | Yeni Para: %i SATILAN ÝÞYERÝ: [B_MYSQL: %i] -- $%i + $%i",
	GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), money, GetCash(playerid), BizInfo[bizid][bizID], biz_cost, cash);
    insert_log(mes, PROPERTY_LOG, 2, PlayerInfo[playerid][pAccID]);

	RemoveAllWorkers(bizid);
    Sell_Business(bizid);

	return 1;
}

Dialog:BizUpgrade(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 0)
	{
		if (BizInfo[bizid][bizRadio] == 1)				return SendErrorMessage(playerid, "Mekanýnýzda zaten ses sistemi mevcut.");
		if (GetCash(playerid) < UPGRADE_PRICE_RADIO)	return SendErrorMessage(playerid, "Ses sistemi ücreti $%i olarak belirlenmiþtir.", UPGRADE_PRICE_RADIO);

		BizInfo[bizid][bizRadio] = 1;
		SQL_SetInteger("business", "radio", BizInfo[bizid][bizRadio], BizInfo[bizid][bizID]);
		GiveCash(playerid, -UPGRADE_PRICE_RADIO);
		SendSyntaxMessage(playerid, "Mekanýnýz için ses sistemi satýn aldýnýz. ");
		SendHelpMessage(playerid, "/radyoayarla komutu ile arayüze eriþebilirsiniz. ");
	}
	else
	{
		if (BizInfo[bizid][bizDDoor] == 0)			return SendErrorMessage(playerid, "Bu kapýnýn tamire ihtiyacý yok.");
		if (GetCash(playerid) < UPGRADE_PRICE_DOOR)	return SendErrorMessage(playerid, "Kapý tamir ücreti $%i olarak belirlenmiþtir.", UPGRADE_PRICE_DOOR);

		BizInfo[bizid][bizDDoor] = 0;
		SQL_SetInteger("business", "ddoor", BizInfo[bizid][bizDDoor], BizInfo[bizid][bizID]);
		UpdateBusinessDoor(bizid);
		GiveCash(playerid, -UPGRADE_PRICE_DOOR);
		SendSyntaxMessage(playerid, "Kapýyý $%i karþýlýðýnda tamir ettiniz.", UPGRADE_PRICE_DOOR);
	}
	return 1;
}

Dialog:ProductBuying(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new price = strval(inputtext), 
		id = biz_prod_types[BizInfo[bizid][bizType]];

	if (id == -1)					return SendErrorMessage(playerid, "Mekanýn bir ürüne ihtiyacý yok.");
	if (price < 50 && price > 1000)	return SendErrorMessage(playerid, "Fiyat 50 ve 1000 dolar arasýnda olmalý.");

	BizInfo[bizid][bizBuyPrice] = price;
	SQL_SetInteger("business", "buy_price", price, BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "%s adlý üründen $%i adet satýn aldýn.", truckcargo_product[id], price);
	return 1;
}

Dialog:ChangeBizName(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new name[32];
	
	if (sscanf(inputtext, "s[32]", name)) return 1;
	if (strlen(name) > 30)				 	return SendErrorMessage(playerid, "Mekan adý 30 karakterden fazla olamaz.");
	if (strfind(name, "~n~", true) != -1) 	return SendErrorMessage(playerid, "Mekan adýnda satýr atlayamazsýn.");
	if (strfind(name, "\n", true) != -1)	return SendErrorMessage(playerid, "Mekan adýnda satýr atlayamasýn.");
	if (strfind(name, "'", true) != -1) 	return SendErrorMessage(playerid, "Mekan adýnda týrnak iþareti kullanamazsýn.");
	if (CheckTextDrawString(name))			return SendErrorMessage(playerid, "Mekan adýnda '~' ifadesi barýnamaz.");

	format(BizInfo[bizid][bizName], 32, "%s", name);
	SQL_SetString("business", "name", BizInfo[bizid][bizName], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Mekanýn adýný güncelledin: %s", BizInfo[bizid][bizName]);

	return 1;
}

Dialog:TillOperations(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");
	if (!listitem)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 1)
	{
		Dialog_Show(playerid, TillDeposit, DIALOG_STYLE_INPUT, "Kasaya para yatýrma", "Mekanýn kasasýna para yatýrmak mý istiyorsun?\nKasaya ne kadar para yatýrmak istediðini kutucuða yaz:\n\t\t(maksimum $25.000.000)", "Seç", "Ýptal");
	}
	
	if (listitem == 2)
	{
		static dlgtxt[] = "Mekanýn kasasýndan çekmek mi istiyorsun?\nÇekmek istediðin miktarý kasaya gir:\n\t\t(maksimum $%s)";

		new diatxt[sizeof(dlgtxt) + 10];

		format(diatxt, sizeof(diatxt), dlgtxt, FormatNumber(BizInfo[bizid][bizCash]));
		Dialog_Show(playerid, TillWithDraw, DIALOG_STYLE_INPUT, "Kasadan para çekme", diatxt, "Seç", "Ýptal");
	}
	
	return 1;
}

Dialog:TillWithDraw(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new amount = strval(inputtext);

	if (BizInfo[bizid][bizCash] < amount) 	return SendErrorMessage(playerid, "Kasada belirttiðin miktarda bir para bulunmuyor.");
	if (amount < 1 || amount > 25000000)	return SendErrorMessage(playerid, "$1 ile $25.000.000 arasýnda bir miktar girmelisin.");

	GiveCash(playerid, amount);
	GiveBizCash(bizid, -amount);
	SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Kasadan $%i deðerinde para aldýn.", amount);
	return 1;
}

Dialog:TillDeposit(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new amount = strval(inputtext);

	if (GetCash(playerid) < amount || amount < 1)	return SendNotCash(playerid);
	if (BizInfo[bizid][bizCash] + amount > 25000000)	return SendErrorMessage(playerid, "$25.000.000 üzerinde bir miktar yatýrýlamaz.");

	GiveCash(playerid, -amount);
	GiveBizCash(bizid, amount);
	SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "$%i deðerinde parayý kasaya koydun.", amount);
	
	return 1;
}

Dialog:DoorName(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 0)
	{
		static dlgtxt[] = "%s\n\
						{FFFFFF}HTML renkler yazý içerisinde kullanabilir. Örneðin: ~FFFF00~ - sarý rengidir.\n\
						Örnek yazý: \"~FFFF00~Hoþ geldin\" yazýsý þu þekilde gözükecek: - \"{FFFF00}Hoþ geldin{FFFFFF}\" \n\n\
						Lütfen yazýyý giriniz:";

		new diatxt[sizeof(dlgtxt) + 128];

		format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizMes]);
		Dialog_Show(playerid, ChangeDoorName, DIALOG_STYLE_INPUT, "Mekan giriþinde çýkacak yazý", diatxt, "Seç", "Ýptal");
	}
	else 
	{
		format(BizInfo[bizid][bizMes], 128, "!");
		SQL_SetString("business", "entermsg", "!", BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Artýk giriþte herhangi bir yazý yazmayacak. ");
	}

	return 1;
}

Dialog:ChangeDoorName(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (strlen(inputtext) < 2 || strlen(inputtext) > 127) return SendErrorMessage(playerid, "Mekan giriþ yazýsý 127 karakterden fazla olamaz. ");
	if (strfind(inputtext, "\n", true) != -1) 			 return SendErrorMessage(playerid, "Mekan giriþ yazýsýnda satýrý aþaðý atlatamazsýn.");

	format(BizInfo[bizid][bizMes], 128, "%s", inputtext);
	place_color(BizInfo[bizid][bizMes]);
	SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Mekan giriþi için yeni yazý belirledin: %s", BizInfo[bizid][bizMes]);

	return 1;
}

Dialog:WorkerInfo(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 0) return Dialog_Show(playerid, WorkerInvite, DIALOG_STYLE_INPUT, "Ýþçi alma", "{FFFFFF}Ýþçi olarak almak istediðiniz oyuncunun ID veya adýný giriniz:", ">>>", "Geri Dön");
	
	listitem -= 1;
	SetPVarInt(playerid, #WorkerID, listitem);

	static dlgtxt[] = "{FFFFFF}ÝSÝM:\t\t %s\n\
					POZÝSYON:\t %s\n\
					{FF6347}>{FFFFFF} Pozisyon deðiþtir\n\
					{FF6347}>{FFFFFF} Ýþten Çýkar";
	
	new diatxt[sizeof(dlgtxt) + 24 + 32];

	format(diatxt, sizeof(diatxt), dlgtxt, BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

	Dialog_Show(playerid, WorkerEdit, DIALOG_STYLE_TABLIST_HEADERS, "Çalýþan Bilgisi", diatxt, "Seç", "Geri Dön");
	return 1;
}

Dialog:WorkerEdit(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 1) return Dialog_Show(playerid, WorkerEditPos, DIALOG_STYLE_INPUT, "Pozisyon deðiþtirme", "{FFFFFF}Çalýþanýn yeni pozisyonunu giriniz:", "Seç", "Ýptal");
	if (listitem == 2)
	{
		listitem = GetPVarInt(playerid, #WorkerID);
		static dlgtxt[] = "{FFFFFF}%s (%s) adlý iþçiyi kovmak istediðinize emin misiniz?";
		new diatxt[sizeof(dlgtxt) + 24 + 32];

		format(diatxt, sizeof(diatxt), dlgtxt, BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);
		Dialog_Show(playerid, WorkerFire, DIALOG_STYLE_INPUT, "Ýþçi kovma", diatxt, "Kabul", "Ýptal");
	}
	return 1;
}

Dialog:WorkerInvite(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid, userid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (WorkSpace(bizid) == -1)						return SendErrorMessage(playerid, "Çalýþan sýnýrýna ulaþtýnýz. ");

	if (sscanf(inputtext, "u", userid))				return 1;
	if (userid == playerid)							return SendErrorMessage(playerid, "Kendini iþe alamazsýn. ");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (pTemp[userid][pHirePlayer] == playerid)		return SendErrorMessage(playerid, "Zaten kiþiyi mekana davet etmiþsin. ");

	pTemp[userid][pHirePlayer] = playerid;
	SetPVarInt(userid, #accept_time, gettime() + 30);

	SendSyntaxMessage(userid, "%s seni mekanýnda çalýþmaya davet etti.", GetNameWithMask(playerid));
	SendHelpMessage(userid, "Y tuþuna basarak teklifi kabul edebilirsin.");
	SendSyntaxMessage(playerid, "%s adlý kiþiyi mekanýna davet ettin.", GetNameWithMask(userid));

	return 1;
}

Dialog:WorkerEditPos(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	listitem = GetPVarInt(playerid, #WorkerID);

	format(BizWorkers[bizid][listitem][bizPosition], 24, "%s", inputtext);

	SQL_SetString("users", "position", BizWorkers[bizid][listitem][bizPosition], BizWorkers[bizid][listitem][bizJobOn]);

	SendSyntaxMessage(playerid, "%s adlý kiþinin pozisyonunu %s olarak güncelledin.", BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

	for(new i; i < GetPlayerPoolSize(); i++)
	{
		if (PlayerInfo[i][pID] == BizWorkers[bizid][listitem][bizJobOn])
		{
			SendSyntaxMessage(i, "%s pozisyonunuzu %s olarak düzenledi.", GetNameEx(playerid), BizWorkers[bizid][listitem][bizPosition]);
			break;
		}
	}
	
	return 1;
}

Dialog:WorkerFire(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	listitem = GetPVarInt(playerid, #WorkerID);

	SQL_SetString("users", "position", "-", BizWorkers[bizid][listitem][bizJobOn]);
	SQL_SetInteger("users", "workon", 0, BizWorkers[bizid][listitem][bizJobOn]);
	
	for(new i; i < GetPlayerPoolSize(); i++)
	{
		if (PlayerInfo[i][pID] == BizWorkers[bizid][listitem][bizJobOn])
		{
			SendSyntaxMessage(i, "%s sizi mekandan kovdu.", GetNameEx(playerid));
			PlayerInfo[i][pWorkOn] = 0;
			break;
		}
	}

	SendSyntaxMessage(playerid, "%s (%s) adlý kiþiyi iþten kovdun.", BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

	BizWorkers[bizid][listitem][bizWorker] = EOS;
	BizWorkers[bizid][listitem][bizPosition] = EOS;
	BizWorkers[bizid][listitem][bizJobOn] = 0;
	return 1;
}

Dialog:BusinessMenuInfo(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");
	return 	pc_cmd_mekanmenu(playerid, "");
}

Dialog:ChooseConfigPrices(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	if (listitem == 0)
	{
		Dialog_Show(playerid, ConfigEntranceFee, DIALOG_STYLE_INPUT, "Ürün güncelleme", "Yeni bir deðer girin:", "Seç", "Ýptal");
	}
	else 
	{
		new biz = BizInfo[bizid][bizType];
		if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
			return SendErrorMessage(playerid,"Bu mekanýn fiyatlarýný deðiþtiremezsin.");
		
		new type;
		switch(biz)
		{
			case BIZ_PIZZA:		type = 0;
			case BIZ_CLUCKIN:	type = 1;
			case BIZ_BURGER:	type = 2;
			case BIZ_DONUT:		type = 3;
			case BIZ_STORE:		type = 4;
			case BIZ_BAR:		type = 5;
			case BIZ_PHARMACY:	type = 6;
		}
		
		new mes[LIMIT_MAX_PRODUCTS*128];

		for(new i = 0; i < max_product[type]; i++)
		{
			format(mes, sizeof(mes), "%s{FFFFFF}Ürün fiyatý deðiþimi -> #%i {AFAFAF}[%s, $%i]\n", mes, i+1, name_order[type][i], BizInfo[bizid][bizProductPrice][i]);
		}

		Dialog_Show(playerid, ConfigPrices, DIALOG_STYLE_LIST, "Ürün güncelleme", mes, "Seç", "Geri Dön");
		return 1;
	}

	return 1;
}

Dialog:ConfigEntranceFee(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yakýn deðilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new fee = strval(inputtext);

	if (fee < 0 || fee > 100) 
	{
		Dialog_Show(playerid, ConfigEntranceFee, DIALOG_STYLE_INPUT, "Ürün güncelleme", "Yeni fiyat girin:", "Seç", "Ýptal");
		return SendErrorMessage(playerid, "Giriþ fiyatý 0 veya 100 dolar arasýnda olmalýdýr.");
	}

	BizInfo[bizid][bizEntrance] = fee;
	SQL_SetInteger("business", "entrance", BizInfo[bizid][bizEntrance], BizInfo[bizid][bizID]);
	
	if (BizInfo[bizid][bizType] == BIZ_GAS_STATION)	SendSyntaxMessage(playerid, "Mekanýn yakýt fiyatýný güncelledin [ID: %d] - $%i/Litre.", bizid, fee);
	else 											SendSyntaxMessage(playerid, "Mekanýn giriþ ücretini güncelledin [ID: %d] $%i.", bizid, fee);
	
	return 1;
}


Dialog:ConfigPrices(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearInsideBiz(playerid)) == -1)				return SendErrorMessage(playerid, "Ýþyerinin içerisinde olmalýsýnýz.");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");
	
	new biz = BizInfo[bizid][bizType];
	if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
		return SendErrorMessage(playerid, "Bu mekanda bulunan þeylerin ücretini deðiþtiremezsiniz.");
	new type;
	switch(biz)
	{
		case BIZ_PIZZA:		type = 0;
		case BIZ_CLUCKIN:	type = 1;
		case BIZ_BURGER:	type = 2;
		case BIZ_DONUT:		type = 3;
		case BIZ_STORE:		type = 4;
		case BIZ_BAR:		type = 5;
		case BIZ_PHARMACY:	type = 6;
	}

	new mes[128];

	format(mes, sizeof(mes), "{FFFFFF}Ürün fiyat deðiþimi: #%i {AFAFAF}[%s, $%i]", listitem+1, name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
	Dialog_Show(playerid, ConfigPricesEnd, DIALOG_STYLE_INPUT, "Ürün güncelleme", mes, "Tamam", "Kapat");
	SetPVarInt(playerid, "ConfigPrices", listitem);
	return 1;
}

Dialog:ConfigPricesEnd(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearInsideBiz(playerid)) == -1)					return SendErrorMessage(playerid, "Ýþyerinin içerisinde olmalýsýnýz.");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait deðil.");

	new money = strval(inputtext);
	listitem = GetPVarInt(playerid, "ConfigPrices");

	new biz = BizInfo[bizid][bizType];
	if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	return SendErrorMessage(playerid,"Bu mekanýn fiyatlarýný deðiþtiremezsin.");
	new type;
	switch(biz)
	{
		case BIZ_PIZZA:		type = 0;
		case BIZ_CLUCKIN:	type = 1;
		case BIZ_BURGER:	type = 2;
		case BIZ_DONUT:		type = 3;
		case BIZ_STORE:		type = 4;
		case BIZ_BAR:		type = 5;
		case BIZ_PHARMACY:	type = 6;
	}

	if (money < biz_prices[type][listitem]/2 || money > biz_prices[type][listitem]*2)
	{
	    new mes[256];
		format(mes, sizeof(mes), ""EMBED_RED"Girilen miktar $%i ile $%i arasýnda olmalýdýr!\n{FFFFFF}Ürünün fiyatýný þu þekilde belirleyebilirsiniz: #%i {AFAFAF}[%s, $%i]", biz_prices[type][listitem]/2, biz_prices[type][listitem]*2, listitem+1, name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
		Dialog_Show(playerid, ConfigPricesEnd, DIALOG_STYLE_INPUT, "Ürün güncelleme", mes, "Tamam", "Kapat");
		return 1;
	}

	BizInfo[bizid][bizProductPrice][listitem] = money;
	SendSyntaxMessage(playerid,"{FF6347}%s {FFFFFF}adlý eþyanýn fiyatýný {FF6347}$%i{FFFFFF} olarak belirledin.", name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
	
	Save_Business(bizid);
	DeletePVar(playerid,"ConfigPrices");
	return 1;
}

Dialog:StoreDialog(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new bizid = GetNearInsideBiz(playerid);

	if (bizid == -1)														return 1;
    if (BizInfo[bizid][bizOwnerID] != 0 && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid,"Bu mekanda yeterince ürün yok.");
    if (GetCash(playerid) < BizInfo[bizid][bizProductPrice][listitem])	return SendNotCash(playerid);
	
	if (BizInfo[bizid][bizType] == BIZ_STORE)
	{
		switch(listitem)
		{
			case 0:
			{
				SetPlayerNumber(playerid);
				SendSyntaxMessage(playerid,"$%i ödeyerek SIM kartý satýn aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 1:
			{
				if (PlayerInfo[playerid][pTelsiz] == 1)	return SendErrorMessage(playerid, "Zaten telsiziniz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek telsiz aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				SendSyntaxMessage(playerid, "/telsizyardim ile detaylara eriþebilirsin. ");
				PlayerInfo[playerid][pTelsiz] = 1;
			}
			case 2:
			{
				if (PlayerInfo[playerid][pLevel] < 2)			return SendErrorMessage(playerid, "Maske satýn alabilmek için en az 2 seviye olmalýsýnýz.");
				if (PlayerInfo[playerid][pMaske] == 1)	return SendErrorMessage(playerid, "Zaten maskeniz var.");
				
				PlayerInfo[playerid][pMaske] = 1;
				SendSyntaxMessage(playerid, "$%i ödeyerek maske satýn aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/maske ile takabilirsin. ");
			}
			case 3:
			{
				if (PlayerInfo[playerid][pCakmak] == 1)	return SendErrorMessage(playerid, "Zaten çakmaðýnýz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek çakmak aldýn.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pCakmak] = 1;
			}
			case 4:
			{
				if (PlayerInfo[playerid][pSigara])	return SendErrorMessage(playerid, "Zaten sigaranýz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek sigara aldýn.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pSigara] = 20;
			}
			case 5:
			{
				if (PlayerInfo[playerid][pZar] == 1)		return SendErrorMessage(playerid, "Zaten zarýnýz var.");
				
				SendSyntaxMessage(playerid, "$%i ödeyerek zar aldýn.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/zar ile kullanabilirsin. ");
				PlayerInfo[playerid][pZar] = 1;
			}
			case 6:
			{
				if (PlayerInfo[playerid][pBenzinBidonu] == 1)	return SendErrorMessage(playerid, "Zaten benzin bidonunuz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek benzin bidonu aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pBenzinBidonu] = 1;
			}
			case 7:
			{
				if (PlayerInfo[playerid][pKalem] == 1)		return SendErrorMessage(playerid, "Zaten kaleminiz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek kalem aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/not ile defterine bir þeyler karalayabilirsin. ");
				PlayerInfo[playerid][pKalem] = 1;
			}
			case 8:
			{
				if (PlayerInfo[playerid][pOyunKarti] == 1)	return SendErrorMessage(playerid, "Zaten oyun kartýnýz var.");

				SendSyntaxMessage(playerid, "$%i ödeyerek oyun kartý aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/kartver ile oyun baþlatabilirsin.");
				PlayerInfo[playerid][pOyunKarti] = 1;
			}
			case 9:
			{
				if (PlayerInfo[playerid][pKamera])		return SendErrorMessage(playerid, "Kameranýz zaten var.");
				SendClientMessageEx(playerid, COLOR_WHITE, "$%i ödeyerek kamera satýn alýdnýz.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pKamera] = 1, AC_GivePlayerWeapon(playerid, 43, 100);
			}
			case 10:
			{
				if (PlayerInfo[playerid][pBoombox] == 1)	return SendErrorMessage(playerid, "Zaten boomboxýnýz var.");
				SendSyntaxMessage(playerid, "$%i ödeyerek boombox aldýnýz.",  BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pBoombox] = 1;
			}
			case 11:
			{
				if (PlayerInfo[playerid][pCicek])	return SendErrorMessage(playerid, "Zaten çiçeðiniz var.");
				SendSyntaxMessage(playerid, "$%i ödeyerek çiçek aldýnýz.",  BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pCicek] = 1, AC_GivePlayerWeapon(playerid, 14, 1);
			}
		}
	}
	else if (BizInfo[bizid][bizType] == BIZ_BAR)
	{
		new name_drink[8][8] = {"bira", "votka", "kola", "su", "viski", "likör", "gazoz", "þarap"};

		switch(listitem)
		{
             case 0:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
                pc_cmd_server_ame(playerid, "bira içer.");
            }
            case 2, 3, 6:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

                if (listitem == 2)         pc_cmd_server_ame(playerid, "kola içer.");
                else if (listitem == 3)  pc_cmd_server_ame(playerid, "su içer.");
                else                             pc_cmd_server_ame(playerid, "gazoz içer.");
            }				
            case 1, 4, 5, 7:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

                if (listitem == 1)         pc_cmd_server_ame(playerid, "votka içer.");
                else if (listitem == 4)  pc_cmd_server_ame(playerid, "viski içer.");
                else if (listitem == 5)   pc_cmd_server_ame(playerid, "brendi içer.");
                else                             pc_cmd_server_ame(playerid, "þarap içer.");
            }			
		}

		SendSyntaxMessage(playerid, "$%i ödeyerek %s adlý içeceði aldýnýz.", name_drink[listitem], BizInfo[bizid][bizProductPrice][listitem]);
	}
	else if (BizInfo[bizid][bizType] == BIZ_PAWN)
	{
		switch(listitem)
		{
            case 0:
            {
                if (PlayerInfo[playerid][pBurnerTelefon]) return SendErrorMessage(playerid, "Zaten bir burner telefona sahipsin.");

                SendServerMessage(playerid, "Tek kullanýmlýk olan burner telefonu satýn aldýnýz.");
			    PlayerInfo[playerid][pBurnerTelefon] = 1;
            }
		}
	}
	else if (BizInfo[bizid][bizType] == BIZ_PHARMACY)
	{
		switch(listitem)
		{
			case 0:
			{
				if (PlayerInfo[playerid][pPrescribe] < gettime())		return SendErrorMessage(playerid, "Reçeteniz bulunmuyor.");
				if (PlayerInfo[playerid][pGanjaTime] > gettime())		return SendErrorMessage(playerid, "Reçetenin süresi bitmiþ: %s.", ConvertSecond(PlayerInfo[playerid][pGanjaTime] - gettime()));
				if (GiveInvItem(playerid, INV_MED_GANJA, 2) == -1)		return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

				PlayerInfo[playerid][pGanjaTime] = gettime() + 86400;
				SendSyntaxMessage(playerid, "$%i ödeyerek medikal esrar satýn aldýn.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 1:
			{
				if (IsPlayerHasItem(playerid, INV_HEAL))	  return SendErrorMessage(playerid,"Zaten ilk yardým kitiniz mevcut.");
				if (GiveInvItem(playerid, INV_HEAL, 1) == -1) return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
					
				SendSyntaxMessage(playerid, "$%i ödeyerek ilk yardým kiti aldýnýz.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 2..11: //103..112 
			{
				if (GiveFloatInvItem(playerid, 101+listitem, 100.0) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
				SendSyntaxMessage(playerid, "$%i ödeyerek %s adlý eþyayý satýn aldýn.", name_order[6][listitem], BizInfo[bizid][bizProductPrice][listitem]);
			}
		}
	}
	else return 1;

	if (BizInfo[bizid][bizOwnerID] != 0)
 	{
 		BizInfo[bizid][bizProduct]--;
		GiveBizCash(bizid, BizInfo[bizid][bizProductPrice][listitem]);
	}

	GiveCash(playerid, -BizInfo[bizid][bizProductPrice][listitem]);
	return 1;
}

Dialog:ChangeBizInterior(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new index, bizid = GetPVarInt(playerid, "biz_change");

    if (bizid < 0 || bizid > MAX_BIZ-1 || !BizInfo[bizid][bizID])	return SendErrorMessage(playerid,"Belirtilen mekan bulunamadý, geçersiz ID.");

    for(new i = 0; i < MAX_INTERIORS; i++)
	{
		if (!AdminTeles[i][telesOn] || BUSSINESS_INT_TYPE != AdminTeles[i][telesType]) continue;

		if (index == listitem)
		{
		    index = i;
		    break;
		}
		index++;
	}

	SetBizInterior(playerid, bizid, index);
	return 1;
}
