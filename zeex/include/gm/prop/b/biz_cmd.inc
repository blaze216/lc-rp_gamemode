alias:mekan("isyeri");
CMD:mekan(playerid, params[])
{
	new option[16], secoption[129];
	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/mekan [satinal / aciklama / isim / bilgi / girisucreti]");
		SendSyntaxMessage(playerid, "bilgi | girisucresti | aciklama | isim | iscial | iscikov");
		SendSyntaxMessage(playerid, "kasayatir | kasacek | yukselt | urunal");
		SendSyntaxMessage(playerid, "satinal | sat | fiyatlar");		
		SendSyntaxMessage(playerid, "Di�er komutlar: /mekanmenu /dekorasyon /mekanreklam");
		return 1;
	}
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)													return SendErrorMessage(playerid, "Yak�n�n�zda bir mekan yok. ");

	if (CompareStrings(option, "bilgi"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])		return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");
		
		new diatxt[300];
		format(diatxt, sizeof(diatxt), "{FFFFFF}ID:\t\t%i\n�sim:\t\t %s\nMekan tipi:\t\t%s\nDurum:\t\t %s\n", BizInfo[bizid][bizID], BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]], (BizInfo[bizid][bizLocked]) ? ("Kapal�") : ("A��k"));
		format(diatxt, sizeof(diatxt), "%sKasa:\t\t $%i\nGiri� �creti:\t $%i\n\nDepo: %i / 400\n", diatxt, BizInfo[bizid][bizCash], BizInfo[bizid][bizEntrance], BizInfo[bizid][bizProduct]);

		new id = biz_prod_types[BizInfo[bizid][bizType]];

		if(id != -1) format(diatxt, sizeof(diatxt), "%sSipari�: %s - $%i / 1 �r�n", diatxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);

		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Mekan Bilgisi", diatxt, ">>", "");
		return 1;
	}

	else if (CompareStrings(option, "girisucreti"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new fee;

		if (sscanf(secoption, "i", fee)) return SendErrorMessage(playerid, "/mekan girisucreti [�cret (0-100)]");
		if (fee < 0 || fee > 100) 		 return SendErrorMessage(playerid, "Giri� �creti $0 ile $100 aras�nda olmal�d�r.");

		BizInfo[bizid][bizEntrance] = fee;
		SQL_SetInteger("business", "entrance", BizInfo[bizid][bizEntrance], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "��letmenin giri� �cretini $%i olarak belirlediniz. [ID: %d]", fee, bizid);
		return 1;
	}

	else if (CompareStrings(option, "aciklama"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new name[129];
		
		if (sscanf(secoption, "s[128]", name))
		{
			SendHelpMessage(playerid, "/mekan aciklama [yazi]");
			SendSyntaxMessage(playerid, "Yaz�y� kald�rmak i�in: {FFFF00}/mekan aciklama sil"); 
			SendSyntaxMessage(playerid, "Girilen yaz�da HTML renkleri kullan�labilir. Renk �rne�i: ~FFFF00~ - sar�");
			SendSyntaxMessage(playerid, "�rnek Kullan�m: \"~FFFF00~Ho� geldiniz\", bu kullan�m�n ��kt�s�: \"{FFFF00}Ho� geldiniz\""); //
			return 1;
		}
		if (CompareStrings(name, "sil"))
		{

		    format(BizInfo[bizid][bizMes], 128, "Mekana ho� geldiniz.");
		    place_color(BizInfo[bizid][bizMes]);
		    SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
		    SendSyntaxMessage(playerid, "Mekan a��klamas� s�f�rland�: %s", BizInfo[bizid][bizMes]);	

			return 1;
		}

		if (strlen(name) < 2 || strlen(name) > 127)	return SendErrorMessage(playerid, "Mekan a��klamas� en fazla 127 karakter olmal�d�r.");
		if (strfind(name, "\n", true) != -1) 		return SendErrorMessage(playerid, "Mekan a��klamas�n� alt sat�ra atamazs�n�z.");

		format(BizInfo[bizid][bizMes], 128, "%s", name);
		place_color(BizInfo[bizid][bizMes]);
		SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan a��klamas� ayarland�: %s", BizInfo[bizid][bizMes]);
		return 1;
	}

	else if (CompareStrings(option, "isim"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new name[32];
	
		if (sscanf(secoption, "s[32]", name)) 		return SendHelpMessage(playerid, "/mekan isim [isim]");
		if (strlen(name) > 30)						return SendErrorMessage(playerid, "Mekan isimi maksimum 30 karakter olmal�d�r.");
		if (strfind(name, "~n~", true) != -1)		return SendErrorMessage(playerid, "Mekan isminde alt sat�r komutlar� kullan�lmamal�d�r.");
		if (CheckTextDrawString(name))				return SendErrorMessage(playerid, "Mekan isimi ge�ersiz karakter i�ermektedir. '~'.");

		format(BizInfo[bizid][bizName], 32, "%s", name);
		SQL_SetString("business", "name", BizInfo[bizid][bizName], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan isimi de�i�tirildi: %s", BizInfo[bizid][bizName]);
		return 1;
	}
	
	else if (CompareStrings(option, "kasayatir"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new amount;

		if (sscanf(secoption, "d", amount))
		{
			SendHelpMessage(playerid, "/mekan kasayatir [para]");
			SendSyntaxMessage(playerid, "Mekan kasas�nda bulunan: $%i", BizInfo[bizid][bizCash]);
			return 1;
		}
		if (GetCash(playerid) < amount || amount < 1)		return SendNotCash(playerid);
		if (BizInfo[bizid][bizCash] + amount > 25000000)	return SendErrorMessage(playerid, "Mekan kasas�nda 25.000.000$'dan fazla para bulunamaz.");

		GiveCash(playerid, -amount);
		GiveBizCash(bizid, amount);
		//SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan kasas�na para koydunuz: $%i.", amount);
		return 1;
	}

	else if (CompareStrings(option, "kasacek"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");
		
		new amount;

		if (sscanf(secoption, "d", amount))
		{
			SendHelpMessage(playerid, "/mekan kasacek [para]");
			SendSyntaxMessage(playerid, "Mekan kasas�nda bulunan: $%i.", BizInfo[bizid][bizCash]);
			return 1;
		}
		if (BizInfo[bizid][bizCash] < amount) 	return SendErrorMessage(playerid, "Mekan kasas�nda yeterli miktarda para yok.");
		if (amount < 1 || amount > 25000000)	return SendErrorMessage(playerid, "Girilen de�er $1 ile $25.000.000 aras�nda olmal�d�r.");

		GiveCash(playerid, amount);
		GiveBizCash(bizid, -amount);
		//SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan kasas�ndan para �ektiniz: $%i.", amount);
		return 1;
	}

	else if (CompareStrings(option, "satinal"))
	{
		if (GetPlayerBizes(playerid) >= GetMaxPlayerBiz(playerid)) 		return SendErrorMessage(playerid, "Daha fazla mekan sat�n alamazs�n�z.");
		if (BizInfo[bizid][bizOwnerID] != 0) 							return SendErrorMessage(playerid, "Bu mekan sat�l�k de�il.");
		if (BizInfo[bizid][bizFreeze] != 0) 							return SendErrorMessage(playerid, "Bu mekan sat�n al�namaz.");
		if (PlayerInfo[playerid][pLevel] < BizInfo[bizid][bizLevelbuy])	return SendErrorMessage(playerid, "Bu mekan� sat�n almak i�in %i seviye olmal�s�n�z.", BizInfo[bizid][bizLevelbuy]);
		if (GetCash(playerid) < BizInfo[bizid][bizPrice])				return SendNotCash(playerid);

		BizInfo[bizid][bizOwnerID] = PlayerInfo[playerid][pID];
		BizInfo[bizid][bizLocked] = 0;
		BizInfo[bizid][bizProduct] = 150;
		BizInfo[bizid][bizBuyPrice] = 50;
		format(BizInfo[bizid][bizOwner], MAX_PLAYER_NAME, "%s", GetName(playerid));
		GiveCash(playerid, -BizInfo[bizid][bizPrice]);

        if (IsValidDynamicPickup(BizInfo[bizid][bizPickUp]))	DestroyDynamicPickup(BizInfo[bizid][bizPickUp]);

		new modelid;
		switch(BizInfo[bizid][bizType])
		{
			case BIZ_PIZZA:		modelid = 1582;
			case BIZ_BAR:       modelid = 1484;
			case BIZ_ATTACH:    modelid = 2710;
			case BIZ_PHARMACY:	modelid = 1241;
			case BIZ_CLOTHES:   modelid = 1275;
			case BIZ_LICENSE:   modelid = 1581;
			case BIZ_GAS_STATION: modelid = 1650;
			default:       modelid = 1272;
		}
		BizInfo[bizid][bizPickUp] = CreateDynamicPickup(modelid, 1, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ], BizInfo[bizid][bizPosVW], BizInfo[bizid][bizPosInt], -1, 100.0);

		Save_Business(bizid);
		SendSyntaxMessage(playerid, "%s adl� mekan� $%i kar��l���nda sat�n ald�n�z.", BizInfo[bizid][bizName], BizInfo[bizid][bizPrice]);

		for(new i = 0; i < MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageBiz] != BizInfo[bizid][bizID]) continue;
			
			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			SQL_SetInteger("garage", "owner", GarageInfo[i][garageOwner], GarageInfo[i][garageID]);
			SendSyntaxMessage(playerid, "Mekana ait bir garaj bulunuyor: [ID: %i]", i);
		}

		new mes[256];
		format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money (ONCEKI): %i | Money (SIMDIKI): %i] mekan sat�n ald� [B_MYSQL: %i] $%i.", 
		GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), PlayerInfo[playerid][pCash] + BizInfo[bizid][bizPrice], GetCash(playerid), BizInfo[bizid][bizID], BizInfo[bizid][bizPrice]);
		insert_log(mes, PROPERTY_LOG, 4, PlayerInfo[playerid][pAccID]);
		return 1;
	}

	else if (CompareStrings(option, "sat"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		Dialog_Show(playerid, SellBiz, DIALOG_STYLE_LIST, "Mekan sat���", "Oyuncuya sat\nDevlete sat", "Se�", "Geri D�n");
		return 1;
	}

	else if (CompareStrings(option, "urunal"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new price, id = biz_prod_types[BizInfo[bizid][bizType]];

		if (id == -1)						return SendErrorMessage(playerid, "Mekan�n�z�n bir �r�ne ihtiyac� yok.");
		if (sscanf(secoption, "i", price))	return SendHelpMessage(playerid, "/mekan urunal [�cret]");
		if (price > 50 && price < 1000) 		return SendErrorMessage(playerid, "Girilen �cret $50 ile $1000 aras�nda olmal�d�r.");

		BizInfo[bizid][bizBuyPrice] = price;
		SQL_SetInteger("business", "buy_price", price, BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "%s adl� yerden �r�n almak i�in $%i �deyeceksiniz.", truckcargo_product[id], price);
		return 1;
	}

	else if (CompareStrings(option, "yukselt"))
	{
		new opt[16];

		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");
		if (sscanf(secoption, "s[16]", opt)) 
		{
			SendHelpMessage(playerid, "/mekan yukselt [radyo | kapitamir]");
			return 1;
		}

		if (CompareStrings(opt, "radyo"))
		{
			if (BizInfo[bizid][bizRadio] == 1)				return SendErrorMessage(playerid, "Bu mekanda radyo bulunuyor.");
			if (GetCash(playerid) < UPGRADE_PRICE_RADIO)	return SendErrorMessage(playerid, "Radyo almak i�in yeterli paran�z bulunmuyor, gereken: $%i.", UPGRADE_PRICE_RADIO);

			BizInfo[bizid][bizRadio] = 1;
			SQL_SetInteger("business", "radio", BizInfo[bizid][bizRadio], BizInfo[bizid][bizID]);
			GiveCash(playerid, -UPGRADE_PRICE_RADIO);
			SendSyntaxMessage(playerid, "Mekan i�in bir radyo sat�n ald�n�z.");
			SendSyntaxMessage(playerid, "Radyo kullan�m� i�in: /radyoayarla");
			return 1;
		}

		else if (CompareStrings(opt, "kapitamir"))
		{
			if (BizInfo[bizid][bizDDoor] == 0)			return SendErrorMessage(playerid, "Bu kap�n�n tamire ihtiyac� yok.");
			if (GetCash(playerid) < UPGRADE_PRICE_DOOR)	return SendErrorMessage(playerid, "Kap�y� tamir ettirebilmek i�in yeterli paran�z bulunmuyor, gereken: $%i.", UPGRADE_PRICE_DOOR);

			BizInfo[bizid][bizDDoor] = 0;
			SQL_SetInteger("business", "ddoor", BizInfo[bizid][bizDDoor], BizInfo[bizid][bizID]);
			UpdateBusinessDoor(bizid);
			GiveCash(playerid, -UPGRADE_PRICE_DOOR);
			SendSyntaxMessage(playerid, "Kap� tamir ettirildi, �denen tutar: $%i.", UPGRADE_PRICE_DOOR);
			return 1;
		}
	}

	else if (CompareStrings(option, "iscial"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new userid;

		if (sscanf(secoption, "u", userid))				return SendHelpMessage(playerid, "/mekan iscial [ID / isim]");
		if (userid == playerid)							return SendErrorMessage(playerid, "Kendinizi i�e alamazs�n�z.");
		if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
		if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
		if (pTemp[userid][pHirePlayer] == playerid)		return SendErrorMessage(playerid, "Belirtilen oyuncu zaten mekan�n�zda �al���yor.");

		pTemp[userid][pHirePlayer] = playerid;
		SetPVarInt(userid, #accept_time, gettime() + 30);
		SendSyntaxMessage(userid, "%s adl� ki�i sizi mekan�na �al��an olarak davet etti.", GetNameWithMask(playerid));
		SendHelpMessage(userid, "Y tu�una basarak teklifi kabul edebilirsin.");
		SendSyntaxMessage(playerid, "%s adl� ki�iyi mekan�n�za �al��an olarak davet ettiniz.", GetNameWithMask(userid));
		return 1;
	}

	else if (CompareStrings(option, "iscikov"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");
	
		new userid;

		if (sscanf(secoption, "u", userid))							return SendHelpMessage(playerid, "/mekan iscikov [ID / isim]");
		if (userid == playerid)										return SendErrorMessage(playerid, "Kendinizi kovamazs�n�z.");
		if (!IsPlayerLogged(userid))								return SendNotConnected(playerid);
		if (PlayerInfo[userid][pWorkOn] != BizInfo[bizid][bizID])	return SendErrorMessage(playerid, "Belirtilen oyuncu mekan�n�zda �al��m�yor.");

		PlayerInfo[userid][pWorkOn] = 0;

		SendSyntaxMessage(userid, "%s adl� ki�i sizi i�ten kovdu.", GetNameWithMask(playerid));
		SendSyntaxMessage(playerid, "%s adl� ki�iyi i�ten ��kartt�n�z.", GetNameWithMask(userid));
		return 1;
	}

	else if (CompareStrings(option, "fiyatlar"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

		new biz = BizInfo[bizid][bizType];
		if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
			return SendErrorMessage(playerid, "Bu mekanda fiyat de�i�ikli�i yapamazs�n�z.");
		
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
			format(mes, sizeof(mes), "%s{FFFFFF}�r�n fiyat d�zenlemesi #%i {AFAFAF}[%s, $%i]\n", mes, i+1, name_order[type][i], BizInfo[bizid][bizProductPrice][i]);
		}

		Dialog_Show(playerid, ConfigPrices, DIALOG_STYLE_LIST, "{9ACD32}�r�n Ayarlar�", mes, "Se�", "Geri D�n");
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/mekan [se�enekler]");
		SendSyntaxMessage(playerid, "bilgi | girisucresti | aciklama | isim | iscial | iscikov");
		SendSyntaxMessage(playerid, "kasayatir | kasacek | yukselt | urunal");
		SendSyntaxMessage(playerid, "satinal | sat | fiyatlar");
	}
	return 1;
}

CMD:mekanmenu(playerid, params[])
{
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)													return SendErrorMessage(playerid, "Bir mekana yak�n de�ilsin. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])		return SendErrorMessage(playerid, "Bu mekan sana ait de�il.");

	static diastr[] = "Mekan Bilgisi\n\
					�al��an Bilgisi\n\
					Kasa\n\
					�cret Ayarlar�\n\
					Mekan Geli�tirmeleri\n\
					Mobilya D�zenleme\n\
					�r�n Sat���\n\
					�sim De�i�tir\n\
					A��klama De�i�tir\n\
					Mekan Sat";

	Dialog_Show(playerid, BusinessMenu, DIALOG_STYLE_LIST, "Mekan Men�", diastr, "Se�", "��k��");
	return 1;
}

CMD:yemek(playerid, params[])
{
	if (isnull(params))
	{
		SendHelpMessage(playerid, "/yemek [se�enekler]");
		SCM(playerid, COLOR_LIGHTRED,"/yemek siparis {FFFFFF}- yemek sipari� men�s�n� a�ar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsiyerlestir {FFFFFF}- yemek tepsisini yerle�tirmenizi sa�lar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsial {FFFFFF}- yemek tepsinizi elinize alman�z� sa�lar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek cop {FFFFFF}- yemek tepsinizi ��pe atman�z� sa�lar.");
		return 1;
	}

	if (CompareStrings(params, "siparis"))
	{
	    new bizid;

		if ((bizid = GetNearInsideBiz(playerid)) == -1)	return SendErrorMessage(playerid, "Herhangi bir mekan�n i�inde de�ilsiniz.");
		if (BizInfo[bizid][bizType] != BIZ_PIZZA && BizInfo[bizid][bizType] != BIZ_CLUCKIN && BizInfo[bizid][bizType] != BIZ_BURGER && BizInfo[bizid][bizType] != BIZ_DONUT)
		{
		    SendErrorMessage(playerid, "Restorantta de�ilsiniz.");
			return 1;
		}

		for(new i; i != 4; i++)
		{
		    TextDrawShowForPlayer(playerid, TD_restaurant[i]);
		}

		new mes[128], type = BizInfo[bizid][bizType] - BIZ_PIZZA;

		for(new i; i != max_product[type]; i++)
		{
		    format(mes, sizeof(mes), "%s~n~~r~Can: +%i~n~~r~Acligi Giderir~n~~p~Fiyat: $%i~n~", TurkishCharFix(name_order[type][i]), 30 + (i * 10), BizInfo[bizid][bizProductPrice][i]);
			PlayerTextDrawSetString(playerid, TD_restaurant_prod[playerid][i], mes);
			PlayerTextDrawShow(playerid, TD_restaurant_prod[playerid][i]);
            PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][i + 4], model_order[type][i]);
            PlayerTextDrawShow(playerid, TD_restaurant_prod[playerid][i + 4]);
		}

		SelectTextDraw(playerid, 0x00cb77FF);
		SetPVarInt(playerid, #restaurant, 1);
		return 1;
	}

	else if (CompareStrings(params, "tepsiyerlestir"))
	{
        if (!pTemp[playerid][pFoodStand]) return SendErrorMessage(playerid, "Elinizde tepsi yok.");

		new dropid = -1;
        for(new i; i != MAX_FOOD_DROPS; i++)
        {
            if (FoodDrop[i][foodDropped] != 0)	continue;

			dropid = i;
			break;
		}

		if (dropid == -1) return SendErrorMessage(playerid, "Maksimum tepsi say�s�na ula��ld�.");

        RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
        GetXYInFrontOfPlayer(playerid, FoodDrop[dropid][foodPosX], FoodDrop[dropid][foodPosY], FoodDrop[dropid][foodPosZ], 0.5);
		FoodDrop[dropid][foodPosZ] -= 0.1;
		FoodDrop[dropid][foodInt] = GetInterior(playerid);
		FoodDrop[dropid][foodVW] = GetWorld(playerid);
		FoodDrop[dropid][foodModel] = pTemp[playerid][pFoodStand];
  		FoodDrop[dropid][foodObject] = CreateDynamicObject(pTemp[playerid][pFoodStand], FoodDrop[dropid][foodPosX], FoodDrop[dropid][foodPosY], FoodDrop[dropid][foodPosZ], -25.300008, 23.200012, -16.699985, GetWorld(playerid), GetInterior(playerid));
		EditDynamicObject(playerid, FoodDrop[dropid][foodObject]);
		SetPVarInt(playerid, #edit_food, dropid+1);
        FoodDrop[dropid][foodDropped] = 1;
        FoodDrop[dropid][foodTime] = 15;
		OnPlayAnim(playerid,"CASINO","cards_win",4.1,0,0,0,0,0);
		pTemp[playerid][pFoodStand] = 0;
		SendSyntaxMessage(playerid, "Tepsinin konumunu d�zenliyorsunuz. Kameray� hareket ettirmek i�in \"SPACE\" tu�una bas�l� tutunuz.");
		return 1;
	}

	else if (CompareStrings(params, "tepsial"))
	{
	    if (pTemp[playerid][pFoodStand] != 0 || IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Elleriniz dolu.");

		new dropid = DropFood_Nearest(playerid);

		if (dropid == -1) return SendErrorMessage(playerid, "Yak�n�n�zda tepsi bulunmuyor.");

		OnPlayAnim(playerid,"CARRY","crry_prtial",4.1,1,1,1,1,1);
		SetPlayerAttachedObject(playerid, ATTACH_HANDS, FoodDrop[dropid][foodModel], 5, 0.091998, 0.021999, 0.409, -104.9, 27.6, 0, 1, 1, 1);
        pTemp[playerid][pFoodStand] = FoodDrop[dropid][foodModel];
        FoodDrop[dropid][foodModel] = 0;
        FoodDrop[dropid][foodDropped] = 0;
        if (IsValidDynamicObject(FoodDrop[dropid][foodObject])) DestroyDynamicObject(FoodDrop[dropid][foodObject]);

		return 1;
	}

	else if (CompareStrings(params, "cop"))
	{
		if (pTemp[playerid][pFoodStand] == 0) return SendErrorMessage(playerid, "Elinizde tepsi yok.");

		OnPlayAnim(playerid,"CASINO","cards_win",4.1,0,0,0,0,0);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		pTemp[playerid][pFoodStand] = 0;
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/yemek [se�enekler]");
		SCM(playerid, COLOR_LIGHTRED,"/yemek siparis {FFFFFF}- yemek sipari� men�s�n� a�ar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsiyerlestir {FFFFFF}- yemek tepsisini yerle�tirmenizi sa�lar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsial {FFFFFF}- yemek tepsinizi elinize alman�z� sa�lar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek cop {FFFFFF}- yemek tepsinizi ��pe atman�z� sa�lar.");
	}
	return 1;
}