Dialog:BusinessMenu(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	switch(listitem)
	{
		case 0: //���������� � �������
		{
			new diatxt[400];
			format(diatxt, sizeof(diatxt), "{FFFFFF}Mekan ID:\t%d\n�sim:\t%s\nMekan tipi:\t%s\nDurum:\t%s\n", BizInfo[bizid][bizID], BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]], (BizInfo[bizid][bizLocked]) ? ("Kapal�") : ("A��k"));
			format(diatxt, sizeof(diatxt), "%sMekan kasas�:\t$%i\nGiri� �creti:\t$%i\n\nDepolama durumu: %i / 400\n", diatxt, BizInfo[bizid][bizCash], BizInfo[bizid][bizEntrance], BizInfo[bizid][bizProduct]);

			new id = biz_prod_types[BizInfo[bizid][bizType]];
            
			if(id != -1) format(diatxt, sizeof(diatxt), "%sSipari�: %s $%i / 1 �r�n", diatxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);

			Dialog_Show(playerid, BusinessMenuInfo, DIALOG_STYLE_MSGBOX, "Mekan Bilgisi", diatxt, "Geri D�n", "");
			return 1;
		}
		case 1: //���������� � �����������
		{
			static dlgtxt[] = "�sim\tPozisyon\n\
					{FF6347}>{FFFFFF} Yeni bir i��i al\n";

			new diatxt[sizeof(dlgtxt) + 10*(24+32)],
				count;

			format(diatxt, sizeof(diatxt), "%s", dlgtxt);
			for(new i = 0; i < MAX_WORK_SPACE; i++)
			{
				if (!BizWorkers[bizid][i][bizJobOn]) continue;

				count++;
				format(diatxt, sizeof(diatxt), "%s%i. %s\t%s\n", diatxt, i+1, BizWorkers[bizid][i][bizWorker], BizWorkers[bizid][i][bizPosition]);
			}		
			
			Dialog_Show(playerid, WorkerInfo, DIALOG_STYLE_TABLIST_HEADERS, "�al��an Bilgisi", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 2: //����� - �������� / �����
		{
			static dlgtxt[] = "Kasada bulunan: $%i\n\
								{FF6347}>{FFFFFF} Para yat�r\n\
								{FF6347}>{FFFFFF} Para �ek";

			new diatxt[sizeof(dlgtxt) + 11];		
			format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizCash]);

			Dialog_Show(playerid, TillOperations, DIALOG_STYLE_TABLIST, "Kasa", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 3: //������������ ���
		{
			new diatxt[128];
			
			if (BizInfo[bizid][bizType] == BIZ_GAS_STATION)	format(diatxt, sizeof(diatxt), "{FFFFFF}Litre fiyat�: $%i", BizInfo[bizid][bizEntrance]);
			else 											format(diatxt, sizeof(diatxt), "{FFFFFF}Giri� �creti: $%i", BizInfo[bizid][bizEntrance]);

			new biz = BizInfo[bizid][bizType];
			if (biz == BIZ_STORE || 
				biz == BIZ_BAR ||
				biz == BIZ_PHARMACY || 
				biz == BIZ_PIZZA || 
				biz == BIZ_CLUCKIN || 
				biz == BIZ_BURGER || 
				biz == BIZ_DONUT) format(diatxt, sizeof(diatxt), "%s\n> �r�n fiyat� g�ncelleme", diatxt);
	
			Dialog_Show(playerid, ChooseConfigPrices, DIALOG_STYLE_TABLIST, "�r�n g�ncelleme", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 4: //��������� �������
		{
			Dialog_Show(playerid, BizUpgrade, DIALOG_STYLE_TABLIST, "Mekan geli�imleri", "Ses sistemi al {33CC33}[$100]{FFFFFF}\nKap�y� tamir et {33CC33}[$1500]{FFFFFF}", "Se�", "Geri D�n");
			return 1;
		}
		case 5: pc_cmd_dekorasyon(playerid, "");
		case 6: //������� ���������
		{
			new id = biz_prod_types[BizInfo[bizid][bizType]];

			if(id == -1) pc_cmd_mekanmenu(playerid, "");
			
			static dlgtxt[] = "(%s) adl� �r�n�n 1 adetini $%i fiyat�ndan sat�yorsun.\n�r�n�n yeni fiyat�n� gir:";

			new diatxt[sizeof(dlgtxt) + 128];	

			format(diatxt, sizeof(diatxt), dlgtxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);
			Dialog_Show(playerid, ProductBuying, DIALOG_STYLE_INPUT, "�r�nler", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 7: //�������� ��������
		{
			static dlgtxt[] = "G�ncel isim: %s\nYeni isim giriniz:";

			new diatxt[sizeof(dlgtxt) + 24];

			format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizName]);
			Dialog_Show(playerid, ChangeBizName, DIALOG_STYLE_INPUT, "�sim de�i�imi", diatxt, "Se�", "Geri D�n");
			return 1;
		}
		case 8: //�������� ������� ��� �����
		{	
			Dialog_Show(playerid, DoorName, DIALOG_STYLE_LIST, "Giri� yaz�s�n� de�i�tirme", "D�zenle\nKald�r", "Se�", "Geri D�n");
			return 1;
		}
		case 9: //������� ������
		{
			Dialog_Show(playerid, SellBiz, DIALOG_STYLE_LIST, "Mekan sat���", "Oyuncuya sat\nDevlete sat", "Se�", "Geri D�n");
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
			if(!PlayerInfo[playerid][pCalintiRadyo]) return SendErrorMessage(playerid, "�zerinizde �al�nt� radyo bulunmuyor.");

            new adet = PlayerInfo[playerid][pCalintiRadyo];
			SendServerMessage(playerid, "Pawnshop d�kkan�na $%d kar��l���nda %d adet �al�nt� radyo satt�n�z.", PRICE_RADIO * adet, adet);
			GiveCash(playerid, PRICE_RADIO * adet);

			PlayerInfo[playerid][pCalintiRadyo] = 0;
		}
		case 1:
		{
			if(!PlayerInfo[playerid][pCalintiEvEsya]) return SendErrorMessage(playerid, "�zerinizde �al�nt� ev e�yas� bulunmuyor.");
            
			new adet = PlayerInfo[playerid][pCalintiEvEsya];
			SendServerMessage(playerid, "Pawnshop d�kkan�na $%d kar��l���nda %d adet �al�nt� e�ya satt�n�z.", PRICE_EVHIRSIZLIK * adet, adet);
			GiveCash(playerid, PRICE_EVHIRSIZLIK * adet);
			PlayerInfo[playerid][pCalintiEvEsya] = 0;
		}		
	}

	return 1;
}

Dialog:SellBiz(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_mekanmenu(playerid, "");

    new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	switch(listitem)
	{
		case 0:
		{
			Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan sat���", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "�ptal");
		}
		case 1:
		{
			static const str_size[] = "{FFFFFF}$%i kar��l���nda mekan� satmaktan emin misiniz?";
			new mes[sizeof(str_size) - 2 + 12];

			format(mes, sizeof(mes), str_size, BizInfo[bizid][bizPrice] / 2);
			Dialog_Show(playerid, SellBizState, DIALOG_STYLE_MSGBOX, "{FFFFFF}Mekan sat���", mes, "Sat", "�ptal");
		}
	}
	return 1;
}

Dialog:SellBizTo(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (bizid < 0 || bizid >= MAX_BIZ || BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return 1;
	    
    new userid, price;

	if (sscanf(inputtext, "ui", userid, price))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan sat���", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "�ptal");
	    return SendErrorMessage(playerid, "Ge�ersiz bir giri� yapt�n�z.");
	}
	
	if (!IsPlayerLogged(userid))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan sat���", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "�ptal");
		return SendNotConnected(playerid);
	}
	
	if (!PlayerNearPlayer(3.0, playerid, userid))
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan sat���", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "�ptal");
		return SendNotNearPlayer(playerid);
	}
	
	if (price < 0 || price > 100000000)
	{
	    Dialog_Show(playerid, SellBizTo, DIALOG_STYLE_INPUT, "{FFFFFF}Mekan sat���", "{ffffff}Bilgileri giriniz {C3C3C3}[ID / isim] [fiyat]", "Sat", "�ptal");
	    return SendErrorMessage(playerid, "1 milyon dolar�n �zerinde fiyat belirleyemezsiniz.");
	}
	
	pTemp[userid][pBizPrice] = price;
	pTemp[userid][pBizPlayer] = playerid;
	pTemp[userid][pBizID] = bizid;

	SetPVarInt(userid, #accept_time, gettime() + 30);
	SendSyntaxMessage(playerid, "%s adl� ki�iye $%i kar��l���nda mekan� satma teklifi sundunuz.", GetNameEx(userid), price);
	SendSyntaxMessage(userid, "%s adl� ki�i size $%i kar��l���nda mekan� satma teklifi sundu. Y tu�u ile sat�n alabilirsin.", GetNameEx(playerid), price);
	return 1;
}

Dialog:SellBizState(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	PlaySound(playerid, 1052);

	new biz_cost = BizInfo[bizid][bizPrice] / 2, money = PlayerInfo[playerid][pCash], cash;

	GiveCash(playerid, biz_cost);
	SendSyntaxMessage(playerid, "Ba�ar�yla \"%s\" adl� mekan� $%i kar��l���nda satt�n�z.",BizInfo[bizid][bizName], biz_cost);

	if (BizInfo[bizid][bizCash] > 0)
	{
		SendSyntaxMessage(playerid,"Mekan sat�ld�ktan sonra kasada bulunan $%i, size geri verildi.", BizInfo[bizid][bizCash]);
		GiveCash(playerid, BizInfo[bizid][bizCash]);
		cash = BizInfo[bizid][bizCash];
	}

    new mes[256];
	format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Eski Para: %i | Yeni Para: %i SATILAN ��YER�: [B_MYSQL: %i] -- $%i + $%i",
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
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 0)
	{
		if (BizInfo[bizid][bizRadio] == 1)				return SendErrorMessage(playerid, "Mekan�n�zda zaten ses sistemi mevcut.");
		if (GetCash(playerid) < UPGRADE_PRICE_RADIO)	return SendErrorMessage(playerid, "Ses sistemi �creti $%i olarak belirlenmi�tir.", UPGRADE_PRICE_RADIO);

		BizInfo[bizid][bizRadio] = 1;
		SQL_SetInteger("business", "radio", BizInfo[bizid][bizRadio], BizInfo[bizid][bizID]);
		GiveCash(playerid, -UPGRADE_PRICE_RADIO);
		SendSyntaxMessage(playerid, "Mekan�n�z i�in ses sistemi sat�n ald�n�z. ");
		SendHelpMessage(playerid, "/radyoayarla komutu ile aray�ze eri�ebilirsiniz. ");
	}
	else
	{
		if (BizInfo[bizid][bizDDoor] == 0)			return SendErrorMessage(playerid, "Bu kap�n�n tamire ihtiyac� yok.");
		if (GetCash(playerid) < UPGRADE_PRICE_DOOR)	return SendErrorMessage(playerid, "Kap� tamir �creti $%i olarak belirlenmi�tir.", UPGRADE_PRICE_DOOR);

		BizInfo[bizid][bizDDoor] = 0;
		SQL_SetInteger("business", "ddoor", BizInfo[bizid][bizDDoor], BizInfo[bizid][bizID]);
		UpdateBusinessDoor(bizid);
		GiveCash(playerid, -UPGRADE_PRICE_DOOR);
		SendSyntaxMessage(playerid, "Kap�y� $%i kar��l���nda tamir ettiniz.", UPGRADE_PRICE_DOOR);
	}
	return 1;
}

Dialog:ProductBuying(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new price = strval(inputtext), 
		id = biz_prod_types[BizInfo[bizid][bizType]];

	if (id == -1)					return SendErrorMessage(playerid, "Mekan�n bir �r�ne ihtiyac� yok.");
	if (price < 50 && price > 1000)	return SendErrorMessage(playerid, "Fiyat 50 ve 1000 dolar aras�nda olmal�.");

	BizInfo[bizid][bizBuyPrice] = price;
	SQL_SetInteger("business", "buy_price", price, BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "%s adl� �r�nden $%i adet sat�n ald�n.", truckcargo_product[id], price);
	return 1;
}

Dialog:ChangeBizName(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new name[32];
	
	if (sscanf(inputtext, "s[32]", name)) return 1;
	if (strlen(name) > 30)				 	return SendErrorMessage(playerid, "Mekan ad� 30 karakterden fazla olamaz.");
	if (strfind(name, "~n~", true) != -1) 	return SendErrorMessage(playerid, "Mekan ad�nda sat�r atlayamazs�n.");
	if (strfind(name, "\n", true) != -1)	return SendErrorMessage(playerid, "Mekan ad�nda sat�r atlayamas�n.");
	if (strfind(name, "'", true) != -1) 	return SendErrorMessage(playerid, "Mekan ad�nda t�rnak i�areti kullanamazs�n.");
	if (CheckTextDrawString(name))			return SendErrorMessage(playerid, "Mekan ad�nda '~' ifadesi bar�namaz.");

	format(BizInfo[bizid][bizName], 32, "%s", name);
	SQL_SetString("business", "name", BizInfo[bizid][bizName], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Mekan�n ad�n� g�ncelledin: %s", BizInfo[bizid][bizName]);

	return 1;
}

Dialog:TillOperations(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");
	if (!listitem)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 1)
	{
		Dialog_Show(playerid, TillDeposit, DIALOG_STYLE_INPUT, "Kasaya para yat�rma", "Mekan�n kasas�na para yat�rmak m� istiyorsun?\nKasaya ne kadar para yat�rmak istedi�ini kutucu�a yaz:\n\t\t(maksimum $25.000.000)", "Se�", "�ptal");
	}
	
	if (listitem == 2)
	{
		static dlgtxt[] = "Mekan�n kasas�ndan �ekmek mi istiyorsun?\n�ekmek istedi�in miktar� kasaya gir:\n\t\t(maksimum $%s)";

		new diatxt[sizeof(dlgtxt) + 10];

		format(diatxt, sizeof(diatxt), dlgtxt, FormatNumber(BizInfo[bizid][bizCash]));
		Dialog_Show(playerid, TillWithDraw, DIALOG_STYLE_INPUT, "Kasadan para �ekme", diatxt, "Se�", "�ptal");
	}
	
	return 1;
}

Dialog:TillWithDraw(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new amount = strval(inputtext);

	if (BizInfo[bizid][bizCash] < amount) 	return SendErrorMessage(playerid, "Kasada belirtti�in miktarda bir para bulunmuyor.");
	if (amount < 1 || amount > 25000000)	return SendErrorMessage(playerid, "$1 ile $25.000.000 aras�nda bir miktar girmelisin.");

	GiveCash(playerid, amount);
	GiveBizCash(bizid, -amount);
	SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Kasadan $%i de�erinde para ald�n.", amount);
	return 1;
}

Dialog:TillDeposit(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new amount = strval(inputtext);

	if (GetCash(playerid) < amount || amount < 1)	return SendNotCash(playerid);
	if (BizInfo[bizid][bizCash] + amount > 25000000)	return SendErrorMessage(playerid, "$25.000.000 �zerinde bir miktar yat�r�lamaz.");

	GiveCash(playerid, -amount);
	GiveBizCash(bizid, amount);
	SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "$%i de�erinde paray� kasaya koydun.", amount);
	
	return 1;
}

Dialog:DoorName(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 0)
	{
		static dlgtxt[] = "%s\n\
						{FFFFFF}HTML renkler yaz� i�erisinde kullanabilir. �rne�in: ~FFFF00~ - sar� rengidir.\n\
						�rnek yaz�: \"~FFFF00~Ho� geldin\" yaz�s� �u �ekilde g�z�kecek: - \"{FFFF00}Ho� geldin{FFFFFF}\" \n\n\
						L�tfen yaz�y� giriniz:";

		new diatxt[sizeof(dlgtxt) + 128];

		format(diatxt, sizeof(diatxt), dlgtxt, BizInfo[bizid][bizMes]);
		Dialog_Show(playerid, ChangeDoorName, DIALOG_STYLE_INPUT, "Mekan giri�inde ��kacak yaz�", diatxt, "Se�", "�ptal");
	}
	else 
	{
		format(BizInfo[bizid][bizMes], 128, "!");
		SQL_SetString("business", "entermsg", "!", BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Art�k giri�te herhangi bir yaz� yazmayacak. ");
	}

	return 1;
}

Dialog:ChangeDoorName(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (strlen(inputtext) < 2 || strlen(inputtext) > 127) return SendErrorMessage(playerid, "Mekan giri� yaz�s� 127 karakterden fazla olamaz. ");
	if (strfind(inputtext, "\n", true) != -1) 			 return SendErrorMessage(playerid, "Mekan giri� yaz�s�nda sat�r� a�a�� atlatamazs�n.");

	format(BizInfo[bizid][bizMes], 128, "%s", inputtext);
	place_color(BizInfo[bizid][bizMes]);
	SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
	SendSyntaxMessage(playerid, "Mekan giri�i i�in yeni yaz� belirledin: %s", BizInfo[bizid][bizMes]);

	return 1;
}

Dialog:WorkerInfo(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 0) return Dialog_Show(playerid, WorkerInvite, DIALOG_STYLE_INPUT, "���i alma", "{FFFFFF}���i olarak almak istedi�iniz oyuncunun ID veya ad�n� giriniz:", ">>>", "Geri D�n");
	
	listitem -= 1;
	SetPVarInt(playerid, #WorkerID, listitem);

	static dlgtxt[] = "{FFFFFF}�S�M:\t\t %s\n\
					POZ�SYON:\t %s\n\
					{FF6347}>{FFFFFF} Pozisyon de�i�tir\n\
					{FF6347}>{FFFFFF} ��ten ��kar";
	
	new diatxt[sizeof(dlgtxt) + 24 + 32];

	format(diatxt, sizeof(diatxt), dlgtxt, BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

	Dialog_Show(playerid, WorkerEdit, DIALOG_STYLE_TABLIST_HEADERS, "�al��an Bilgisi", diatxt, "Se�", "Geri D�n");
	return 1;
}

Dialog:WorkerEdit(playerid, response, listitem, inputtext[])
{
    if (!response)	return pc_cmd_mekanmenu(playerid, "");

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 1) return Dialog_Show(playerid, WorkerEditPos, DIALOG_STYLE_INPUT, "Pozisyon de�i�tirme", "{FFFFFF}�al��an�n yeni pozisyonunu giriniz:", "Se�", "�ptal");
	if (listitem == 2)
	{
		listitem = GetPVarInt(playerid, #WorkerID);
		static dlgtxt[] = "{FFFFFF}%s (%s) adl� i��iyi kovmak istedi�inize emin misiniz?";
		new diatxt[sizeof(dlgtxt) + 24 + 32];

		format(diatxt, sizeof(diatxt), dlgtxt, BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);
		Dialog_Show(playerid, WorkerFire, DIALOG_STYLE_INPUT, "���i kovma", diatxt, "Kabul", "�ptal");
	}
	return 1;
}

Dialog:WorkerInvite(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

	new bizid, userid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (WorkSpace(bizid) == -1)						return SendErrorMessage(playerid, "�al��an s�n�r�na ula�t�n�z. ");

	if (sscanf(inputtext, "u", userid))				return 1;
	if (userid == playerid)							return SendErrorMessage(playerid, "Kendini i�e alamazs�n. ");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (pTemp[userid][pHirePlayer] == playerid)		return SendErrorMessage(playerid, "Zaten ki�iyi mekana davet etmi�sin. ");

	pTemp[userid][pHirePlayer] = playerid;
	SetPVarInt(userid, #accept_time, gettime() + 30);

	SendSyntaxMessage(userid, "%s seni mekan�nda �al��maya davet etti.", GetNameWithMask(playerid));
	SendHelpMessage(userid, "Y tu�una basarak teklifi kabul edebilirsin.");
	SendSyntaxMessage(playerid, "%s adl� ki�iyi mekan�na davet ettin.", GetNameWithMask(userid));

	return 1;
}

Dialog:WorkerEditPos(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	listitem = GetPVarInt(playerid, #WorkerID);

	format(BizWorkers[bizid][listitem][bizPosition], 24, "%s", inputtext);

	SQL_SetString("users", "position", BizWorkers[bizid][listitem][bizPosition], BizWorkers[bizid][listitem][bizJobOn]);

	SendSyntaxMessage(playerid, "%s adl� ki�inin pozisyonunu %s olarak g�ncelledin.", BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

	for(new i; i < GetPlayerPoolSize(); i++)
	{
		if (PlayerInfo[i][pID] == BizWorkers[bizid][listitem][bizJobOn])
		{
			SendSyntaxMessage(i, "%s pozisyonunuzu %s olarak d�zenledi.", GetNameEx(playerid), BizWorkers[bizid][listitem][bizPosition]);
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
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

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

	SendSyntaxMessage(playerid, "%s (%s) adl� ki�iyi i�ten kovdun.", BizWorkers[bizid][listitem][bizWorker], BizWorkers[bizid][listitem][bizPosition]);

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
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	if (listitem == 0)
	{
		Dialog_Show(playerid, ConfigEntranceFee, DIALOG_STYLE_INPUT, "�r�n g�ncelleme", "Yeni bir de�er girin:", "Se�", "�ptal");
	}
	else 
	{
		new biz = BizInfo[bizid][bizType];
		if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
			return SendErrorMessage(playerid,"Bu mekan�n fiyatlar�n� de�i�tiremezsin.");
		
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
			format(mes, sizeof(mes), "%s{FFFFFF}�r�n fiyat� de�i�imi -> #%i {AFAFAF}[%s, $%i]\n", mes, i+1, name_order[type][i], BizInfo[bizid][bizProductPrice][i]);
		}

		Dialog_Show(playerid, ConfigPrices, DIALOG_STYLE_LIST, "�r�n g�ncelleme", mes, "Se�", "Geri D�n");
		return 1;
	}

	return 1;
}

Dialog:ConfigEntranceFee(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 			bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)												return SendErrorMessage(playerid, "Herhangi bir mekana yak�n de�ilsiniz. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new fee = strval(inputtext);

	if (fee < 0 || fee > 100) 
	{
		Dialog_Show(playerid, ConfigEntranceFee, DIALOG_STYLE_INPUT, "�r�n g�ncelleme", "Yeni fiyat girin:", "Se�", "�ptal");
		return SendErrorMessage(playerid, "Giri� fiyat� 0 veya 100 dolar aras�nda olmal�d�r.");
	}

	BizInfo[bizid][bizEntrance] = fee;
	SQL_SetInteger("business", "entrance", BizInfo[bizid][bizEntrance], BizInfo[bizid][bizID]);
	
	if (BizInfo[bizid][bizType] == BIZ_GAS_STATION)	SendSyntaxMessage(playerid, "Mekan�n yak�t fiyat�n� g�ncelledin [ID: %d] - $%i/Litre.", bizid, fee);
	else 											SendSyntaxMessage(playerid, "Mekan�n giri� �cretini g�ncelledin [ID: %d] $%i.", bizid, fee);
	
	return 1;
}


Dialog:ConfigPrices(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearInsideBiz(playerid)) == -1)				return SendErrorMessage(playerid, "��yerinin i�erisinde olmal�s�n�z.");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");
	
	new biz = BizInfo[bizid][bizType];
	if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
		return SendErrorMessage(playerid, "Bu mekanda bulunan �eylerin �cretini de�i�tiremezsiniz.");
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

	format(mes, sizeof(mes), "{FFFFFF}�r�n fiyat de�i�imi: #%i {AFAFAF}[%s, $%i]", listitem+1, name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
	Dialog_Show(playerid, ConfigPricesEnd, DIALOG_STYLE_INPUT, "�r�n g�ncelleme", mes, "Tamam", "Kapat");
	SetPVarInt(playerid, "ConfigPrices", listitem);
	return 1;
}

Dialog:ConfigPricesEnd(playerid, response, listitem, inputtext[])
{
    if (!response)	return 1;

    new bizid;

	if ((bizid = GetNearInsideBiz(playerid)) == -1)					return SendErrorMessage(playerid, "��yerinin i�erisinde olmal�s�n�z.");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan size ait de�il.");

	new money = strval(inputtext);
	listitem = GetPVarInt(playerid, "ConfigPrices");

	new biz = BizInfo[bizid][bizType];
	if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	return SendErrorMessage(playerid,"Bu mekan�n fiyatlar�n� de�i�tiremezsin.");
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
		format(mes, sizeof(mes), ""EMBED_RED"Girilen miktar $%i ile $%i aras�nda olmal�d�r!\n{FFFFFF}�r�n�n fiyat�n� �u �ekilde belirleyebilirsiniz: #%i {AFAFAF}[%s, $%i]", biz_prices[type][listitem]/2, biz_prices[type][listitem]*2, listitem+1, name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
		Dialog_Show(playerid, ConfigPricesEnd, DIALOG_STYLE_INPUT, "�r�n g�ncelleme", mes, "Tamam", "Kapat");
		return 1;
	}

	BizInfo[bizid][bizProductPrice][listitem] = money;
	SendSyntaxMessage(playerid,"{FF6347}%s {FFFFFF}adl� e�yan�n fiyat�n� {FF6347}$%i{FFFFFF} olarak belirledin.", name_order[type][listitem], BizInfo[bizid][bizProductPrice][listitem]);
	
	Save_Business(bizid);
	DeletePVar(playerid,"ConfigPrices");
	return 1;
}

Dialog:StoreDialog(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

	new bizid = GetNearInsideBiz(playerid);

	if (bizid == -1)														return 1;
    if (BizInfo[bizid][bizOwnerID] != 0 && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid,"Bu mekanda yeterince �r�n yok.");
    if (GetCash(playerid) < BizInfo[bizid][bizProductPrice][listitem])	return SendNotCash(playerid);
	
	if (BizInfo[bizid][bizType] == BIZ_STORE)
	{
		switch(listitem)
		{
			case 0:
			{
				SetPlayerNumber(playerid);
				SendSyntaxMessage(playerid,"$%i �deyerek SIM kart� sat�n ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 1:
			{
				if (PlayerInfo[playerid][pTelsiz] == 1)	return SendErrorMessage(playerid, "Zaten telsiziniz var.");

				SendSyntaxMessage(playerid, "$%i �deyerek telsiz ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
				SendSyntaxMessage(playerid, "/telsizyardim ile detaylara eri�ebilirsin. ");
				PlayerInfo[playerid][pTelsiz] = 1;
			}
			case 2:
			{
				if (PlayerInfo[playerid][pLevel] < 2)			return SendErrorMessage(playerid, "Maske sat�n alabilmek i�in en az 2 seviye olmal�s�n�z.");
				if (PlayerInfo[playerid][pMaske] == 1)	return SendErrorMessage(playerid, "Zaten maskeniz var.");
				
				PlayerInfo[playerid][pMaske] = 1;
				SendSyntaxMessage(playerid, "$%i �deyerek maske sat�n ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/maske ile takabilirsin. ");
			}
			case 3:
			{
				if (PlayerInfo[playerid][pCakmak] == 1)	return SendErrorMessage(playerid, "Zaten �akma��n�z var.");

				SendSyntaxMessage(playerid, "$%i �deyerek �akmak ald�n.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pCakmak] = 1;
			}
			case 4:
			{
				if (PlayerInfo[playerid][pSigara])	return SendErrorMessage(playerid, "Zaten sigaran�z var.");

				SendSyntaxMessage(playerid, "$%i �deyerek sigara ald�n.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pSigara] = 20;
			}
			case 5:
			{
				if (PlayerInfo[playerid][pZar] == 1)		return SendErrorMessage(playerid, "Zaten zar�n�z var.");
				
				SendSyntaxMessage(playerid, "$%i �deyerek zar ald�n.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/zar ile kullanabilirsin. ");
				PlayerInfo[playerid][pZar] = 1;
			}
			case 6:
			{
				if (PlayerInfo[playerid][pBenzinBidonu] == 1)	return SendErrorMessage(playerid, "Zaten benzin bidonunuz var.");

				SendSyntaxMessage(playerid, "$%i �deyerek benzin bidonu ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pBenzinBidonu] = 1;
			}
			case 7:
			{
				if (PlayerInfo[playerid][pKalem] == 1)		return SendErrorMessage(playerid, "Zaten kaleminiz var.");

				SendSyntaxMessage(playerid, "$%i �deyerek kalem ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/not ile defterine bir �eyler karalayabilirsin. ");
				PlayerInfo[playerid][pKalem] = 1;
			}
			case 8:
			{
				if (PlayerInfo[playerid][pOyunKarti] == 1)	return SendErrorMessage(playerid, "Zaten oyun kart�n�z var.");

				SendSyntaxMessage(playerid, "$%i �deyerek oyun kart� ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
				SendHelpMessage(playerid, "/kartver ile oyun ba�latabilirsin.");
				PlayerInfo[playerid][pOyunKarti] = 1;
			}
			case 9:
			{
				if (PlayerInfo[playerid][pKamera])		return SendErrorMessage(playerid, "Kameran�z zaten var.");
				SendClientMessageEx(playerid, COLOR_WHITE, "$%i �deyerek kamera sat�n al�dn�z.", BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pKamera] = 1, AC_GivePlayerWeapon(playerid, 43, 100);
			}
			case 10:
			{
				if (PlayerInfo[playerid][pBoombox] == 1)	return SendErrorMessage(playerid, "Zaten boombox�n�z var.");
				SendSyntaxMessage(playerid, "$%i �deyerek boombox ald�n�z.",  BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pBoombox] = 1;
			}
			case 11:
			{
				if (PlayerInfo[playerid][pCicek])	return SendErrorMessage(playerid, "Zaten �i�e�iniz var.");
				SendSyntaxMessage(playerid, "$%i �deyerek �i�ek ald�n�z.",  BizInfo[bizid][bizProductPrice][listitem]);
				PlayerInfo[playerid][pCicek] = 1, AC_GivePlayerWeapon(playerid, 14, 1);
			}
		}
	}
	else if (BizInfo[bizid][bizType] == BIZ_BAR)
	{
		new name_drink[8][8] = {"bira", "votka", "kola", "su", "viski", "lik�r", "gazoz", "�arap"};

		switch(listitem)
		{
             case 0:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
                pc_cmd_server_ame(playerid, "bira i�er.");
            }
            case 2, 3, 6:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

                if (listitem == 2)         pc_cmd_server_ame(playerid, "kola i�er.");
                else if (listitem == 3)  pc_cmd_server_ame(playerid, "su i�er.");
                else                             pc_cmd_server_ame(playerid, "gazoz i�er.");
            }				
            case 1, 4, 5, 7:
            {
                if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Eliniz zaten dolu.");

                InfoMSG(playerid, "Icmek icin \" ~g~LKM ~w~\" tusuna basin ~n~Iptal etmek icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);

                if (listitem == 1)         pc_cmd_server_ame(playerid, "votka i�er.");
                else if (listitem == 4)  pc_cmd_server_ame(playerid, "viski i�er.");
                else if (listitem == 5)   pc_cmd_server_ame(playerid, "brendi i�er.");
                else                             pc_cmd_server_ame(playerid, "�arap i�er.");
            }			
		}

		SendSyntaxMessage(playerid, "$%i �deyerek %s adl� i�ece�i ald�n�z.", name_drink[listitem], BizInfo[bizid][bizProductPrice][listitem]);
	}
	else if (BizInfo[bizid][bizType] == BIZ_PAWN)
	{
		switch(listitem)
		{
            case 0:
            {
                if (PlayerInfo[playerid][pBurnerTelefon]) return SendErrorMessage(playerid, "Zaten bir burner telefona sahipsin.");

                SendServerMessage(playerid, "Tek kullan�ml�k olan burner telefonu sat�n ald�n�z.");
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
				if (PlayerInfo[playerid][pPrescribe] < gettime())		return SendErrorMessage(playerid, "Re�eteniz bulunmuyor.");
				if (PlayerInfo[playerid][pGanjaTime] > gettime())		return SendErrorMessage(playerid, "Re�etenin s�resi bitmi�: %s.", ConvertSecond(PlayerInfo[playerid][pGanjaTime] - gettime()));
				if (GiveInvItem(playerid, INV_MED_GANJA, 2) == -1)		return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

				PlayerInfo[playerid][pGanjaTime] = gettime() + 86400;
				SendSyntaxMessage(playerid, "$%i �deyerek medikal esrar sat�n ald�n.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 1:
			{
				if (IsPlayerHasItem(playerid, INV_HEAL))	  return SendErrorMessage(playerid,"Zaten ilk yard�m kitiniz mevcut.");
				if (GiveInvItem(playerid, INV_HEAL, 1) == -1) return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
					
				SendSyntaxMessage(playerid, "$%i �deyerek ilk yard�m kiti ald�n�z.", BizInfo[bizid][bizProductPrice][listitem]);
			}
			case 2..11: //103..112 
			{
				if (GiveFloatInvItem(playerid, 101+listitem, 100.0) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
				SendSyntaxMessage(playerid, "$%i �deyerek %s adl� e�yay� sat�n ald�n.", name_order[6][listitem], BizInfo[bizid][bizProductPrice][listitem]);
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

    if (bizid < 0 || bizid > MAX_BIZ-1 || !BizInfo[bizid][bizID])	return SendErrorMessage(playerid,"Belirtilen mekan bulunamad�, ge�ersiz ID.");

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
