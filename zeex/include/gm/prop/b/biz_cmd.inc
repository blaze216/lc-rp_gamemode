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
		SendSyntaxMessage(playerid, "Diðer komutlar: /mekanmenu /dekorasyon /mekanreklam");
		return 1;
	}
	
	new bizid;

	if ((bizid = GetNearOutsideBiz(playerid)) == -1) 				bizid = GetNearInsideBiz(playerid);
	if (bizid == -1)													return SendErrorMessage(playerid, "Yakýnýnýzda bir mekan yok. ");

	if (CompareStrings(option, "bilgi"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])		return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");
		
		new diatxt[300];
		format(diatxt, sizeof(diatxt), "{FFFFFF}ID:\t\t%i\nÝsim:\t\t %s\nMekan tipi:\t\t%s\nDurum:\t\t %s\n", BizInfo[bizid][bizID], BizInfo[bizid][bizName], biz_types[BizInfo[bizid][bizType]], (BizInfo[bizid][bizLocked]) ? ("Kapalý") : ("Açýk"));
		format(diatxt, sizeof(diatxt), "%sKasa:\t\t $%i\nGiriþ ücreti:\t $%i\n\nDepo: %i / 400\n", diatxt, BizInfo[bizid][bizCash], BizInfo[bizid][bizEntrance], BizInfo[bizid][bizProduct]);

		new id = biz_prod_types[BizInfo[bizid][bizType]];

		if(id != -1) format(diatxt, sizeof(diatxt), "%sSipariþ: %s - $%i / 1 ürün", diatxt, truckcargo_product[id], BizInfo[bizid][bizBuyPrice]);

		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Mekan Bilgisi", diatxt, ">>", "");
		return 1;
	}

	else if (CompareStrings(option, "girisucreti"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new fee;

		if (sscanf(secoption, "i", fee)) return SendErrorMessage(playerid, "/mekan girisucreti [ücret (0-100)]");
		if (fee < 0 || fee > 100) 		 return SendErrorMessage(playerid, "Giriþ ücreti $0 ile $100 arasýnda olmalýdýr.");

		BizInfo[bizid][bizEntrance] = fee;
		SQL_SetInteger("business", "entrance", BizInfo[bizid][bizEntrance], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Ýþletmenin giriþ ücretini $%i olarak belirlediniz. [ID: %d]", fee, bizid);
		return 1;
	}

	else if (CompareStrings(option, "aciklama"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new name[129];
		
		if (sscanf(secoption, "s[128]", name))
		{
			SendHelpMessage(playerid, "/mekan aciklama [yazi]");
			SendSyntaxMessage(playerid, "Yazýyý kaldýrmak için: {FFFF00}/mekan aciklama sil"); 
			SendSyntaxMessage(playerid, "Girilen yazýda HTML renkleri kullanýlabilir. Renk örneði: ~FFFF00~ - sarý");
			SendSyntaxMessage(playerid, "Örnek Kullaným: \"~FFFF00~Hoþ geldiniz\", bu kullanýmýn çýktýsý: \"{FFFF00}Hoþ geldiniz\""); //
			return 1;
		}
		if (CompareStrings(name, "sil"))
		{

		    format(BizInfo[bizid][bizMes], 128, "Mekana hoþ geldiniz.");
		    place_color(BizInfo[bizid][bizMes]);
		    SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
		    SendSyntaxMessage(playerid, "Mekan açýklamasý sýfýrlandý: %s", BizInfo[bizid][bizMes]);	

			return 1;
		}

		if (strlen(name) < 2 || strlen(name) > 127)	return SendErrorMessage(playerid, "Mekan açýklamasý en fazla 127 karakter olmalýdýr.");
		if (strfind(name, "\n", true) != -1) 		return SendErrorMessage(playerid, "Mekan açýklamasýný alt satýra atamazsýnýz.");

		format(BizInfo[bizid][bizMes], 128, "%s", name);
		place_color(BizInfo[bizid][bizMes]);
		SQL_SetString("business", "entermsg", BizInfo[bizid][bizMes], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan açýklamasý ayarlandý: %s", BizInfo[bizid][bizMes]);
		return 1;
	}

	else if (CompareStrings(option, "isim"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new name[32];
	
		if (sscanf(secoption, "s[32]", name)) 		return SendHelpMessage(playerid, "/mekan isim [isim]");
		if (strlen(name) > 30)						return SendErrorMessage(playerid, "Mekan isimi maksimum 30 karakter olmalýdýr.");
		if (strfind(name, "~n~", true) != -1)		return SendErrorMessage(playerid, "Mekan isminde alt satýr komutlarý kullanýlmamalýdýr.");
		if (CheckTextDrawString(name))				return SendErrorMessage(playerid, "Mekan isimi geçersiz karakter içermektedir. '~'.");

		format(BizInfo[bizid][bizName], 32, "%s", name);
		SQL_SetString("business", "name", BizInfo[bizid][bizName], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan isimi deðiþtirildi: %s", BizInfo[bizid][bizName]);
		return 1;
	}
	
	else if (CompareStrings(option, "kasayatir"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new amount;

		if (sscanf(secoption, "d", amount))
		{
			SendHelpMessage(playerid, "/mekan kasayatir [para]");
			SendSyntaxMessage(playerid, "Mekan kasasýnda bulunan: $%i", BizInfo[bizid][bizCash]);
			return 1;
		}
		if (GetCash(playerid) < amount || amount < 1)		return SendNotCash(playerid);
		if (BizInfo[bizid][bizCash] + amount > 25000000)	return SendErrorMessage(playerid, "Mekan kasasýnda 25.000.000$'dan fazla para bulunamaz.");

		GiveCash(playerid, -amount);
		GiveBizCash(bizid, amount);
		//SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan kasasýna para koydunuz: $%i.", amount);
		return 1;
	}

	else if (CompareStrings(option, "kasacek"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");
		
		new amount;

		if (sscanf(secoption, "d", amount))
		{
			SendHelpMessage(playerid, "/mekan kasacek [para]");
			SendSyntaxMessage(playerid, "Mekan kasasýnda bulunan: $%i.", BizInfo[bizid][bizCash]);
			return 1;
		}
		if (BizInfo[bizid][bizCash] < amount) 	return SendErrorMessage(playerid, "Mekan kasasýnda yeterli miktarda para yok.");
		if (amount < 1 || amount > 25000000)	return SendErrorMessage(playerid, "Girilen deðer $1 ile $25.000.000 arasýnda olmalýdýr.");

		GiveCash(playerid, amount);
		GiveBizCash(bizid, -amount);
		//SQL_SetInteger("business", "cash", BizInfo[bizid][bizCash], BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "Mekan kasasýndan para çektiniz: $%i.", amount);
		return 1;
	}

	else if (CompareStrings(option, "satinal"))
	{
		if (GetPlayerBizes(playerid) >= GetMaxPlayerBiz(playerid)) 		return SendErrorMessage(playerid, "Daha fazla mekan satýn alamazsýnýz.");
		if (BizInfo[bizid][bizOwnerID] != 0) 							return SendErrorMessage(playerid, "Bu mekan satýlýk deðil.");
		if (BizInfo[bizid][bizFreeze] != 0) 							return SendErrorMessage(playerid, "Bu mekan satýn alýnamaz.");
		if (PlayerInfo[playerid][pLevel] < BizInfo[bizid][bizLevelbuy])	return SendErrorMessage(playerid, "Bu mekaný satýn almak için %i seviye olmalýsýnýz.", BizInfo[bizid][bizLevelbuy]);
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
		SendSyntaxMessage(playerid, "%s adlý mekaný $%i karþýlýðýnda satýn aldýnýz.", BizInfo[bizid][bizName], BizInfo[bizid][bizPrice]);

		for(new i = 0; i < MAX_GARAGES; i++)
		{
			if (!GarageInfo[i][garageID] || GarageInfo[i][garageBiz] != BizInfo[bizid][bizID]) continue;
			
			GarageInfo[i][garageOwner] = PlayerInfo[playerid][pID];
			SQL_SetInteger("garage", "owner", GarageInfo[i][garageOwner], GarageInfo[i][garageID]);
			SendSyntaxMessage(playerid, "Mekana ait bir garaj bulunuyor: [ID: %i]", i);
		}

		new mes[256];
		format(mes, sizeof(mes), "%s [MYSQL: %i | IP: %s | Money (ONCEKI): %i | Money (SIMDIKI): %i] mekan satýn aldý [B_MYSQL: %i] $%i.", 
		GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), PlayerInfo[playerid][pCash] + BizInfo[bizid][bizPrice], GetCash(playerid), BizInfo[bizid][bizID], BizInfo[bizid][bizPrice]);
		insert_log(mes, PROPERTY_LOG, 4, PlayerInfo[playerid][pAccID]);
		return 1;
	}

	else if (CompareStrings(option, "sat"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		Dialog_Show(playerid, SellBiz, DIALOG_STYLE_LIST, "Mekan satýþý", "Oyuncuya sat\nDevlete sat", "Seç", "Geri Dön");
		return 1;
	}

	else if (CompareStrings(option, "urunal"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new price, id = biz_prod_types[BizInfo[bizid][bizType]];

		if (id == -1)						return SendErrorMessage(playerid, "Mekanýnýzýn bir ürüne ihtiyacý yok.");
		if (sscanf(secoption, "i", price))	return SendHelpMessage(playerid, "/mekan urunal [ücret]");
		if (price > 50 && price < 1000) 		return SendErrorMessage(playerid, "Girilen ücret $50 ile $1000 arasýnda olmalýdýr.");

		BizInfo[bizid][bizBuyPrice] = price;
		SQL_SetInteger("business", "buy_price", price, BizInfo[bizid][bizID]);
		SendSyntaxMessage(playerid, "%s adlý yerden ürün almak için $%i ödeyeceksiniz.", truckcargo_product[id], price);
		return 1;
	}

	else if (CompareStrings(option, "yukselt"))
	{
		new opt[16];

		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");
		if (sscanf(secoption, "s[16]", opt)) 
		{
			SendHelpMessage(playerid, "/mekan yukselt [radyo | kapitamir]");
			return 1;
		}

		if (CompareStrings(opt, "radyo"))
		{
			if (BizInfo[bizid][bizRadio] == 1)				return SendErrorMessage(playerid, "Bu mekanda radyo bulunuyor.");
			if (GetCash(playerid) < UPGRADE_PRICE_RADIO)	return SendErrorMessage(playerid, "Radyo almak için yeterli paranýz bulunmuyor, gereken: $%i.", UPGRADE_PRICE_RADIO);

			BizInfo[bizid][bizRadio] = 1;
			SQL_SetInteger("business", "radio", BizInfo[bizid][bizRadio], BizInfo[bizid][bizID]);
			GiveCash(playerid, -UPGRADE_PRICE_RADIO);
			SendSyntaxMessage(playerid, "Mekan için bir radyo satýn aldýnýz.");
			SendSyntaxMessage(playerid, "Radyo kullanýmý için: /radyoayarla");
			return 1;
		}

		else if (CompareStrings(opt, "kapitamir"))
		{
			if (BizInfo[bizid][bizDDoor] == 0)			return SendErrorMessage(playerid, "Bu kapýnýn tamire ihtiyacý yok.");
			if (GetCash(playerid) < UPGRADE_PRICE_DOOR)	return SendErrorMessage(playerid, "Kapýyý tamir ettirebilmek için yeterli paranýz bulunmuyor, gereken: $%i.", UPGRADE_PRICE_DOOR);

			BizInfo[bizid][bizDDoor] = 0;
			SQL_SetInteger("business", "ddoor", BizInfo[bizid][bizDDoor], BizInfo[bizid][bizID]);
			UpdateBusinessDoor(bizid);
			GiveCash(playerid, -UPGRADE_PRICE_DOOR);
			SendSyntaxMessage(playerid, "Kapý tamir ettirildi, ödenen tutar: $%i.", UPGRADE_PRICE_DOOR);
			return 1;
		}
	}

	else if (CompareStrings(option, "iscial"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new userid;

		if (sscanf(secoption, "u", userid))				return SendHelpMessage(playerid, "/mekan iscial [ID / isim]");
		if (userid == playerid)							return SendErrorMessage(playerid, "Kendinizi iþe alamazsýnýz.");
		if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
		if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
		if (pTemp[userid][pHirePlayer] == playerid)		return SendErrorMessage(playerid, "Belirtilen oyuncu zaten mekanýnýzda çalýþýyor.");

		pTemp[userid][pHirePlayer] = playerid;
		SetPVarInt(userid, #accept_time, gettime() + 30);
		SendSyntaxMessage(userid, "%s adlý kiþi sizi mekanýna çalýþan olarak davet etti.", GetNameWithMask(playerid));
		SendHelpMessage(userid, "Y tuþuna basarak teklifi kabul edebilirsin.");
		SendSyntaxMessage(playerid, "%s adlý kiþiyi mekanýnýza çalýþan olarak davet ettiniz.", GetNameWithMask(userid));
		return 1;
	}

	else if (CompareStrings(option, "iscikov"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");
	
		new userid;

		if (sscanf(secoption, "u", userid))							return SendHelpMessage(playerid, "/mekan iscikov [ID / isim]");
		if (userid == playerid)										return SendErrorMessage(playerid, "Kendinizi kovamazsýnýz.");
		if (!IsPlayerLogged(userid))								return SendNotConnected(playerid);
		if (PlayerInfo[userid][pWorkOn] != BizInfo[bizid][bizID])	return SendErrorMessage(playerid, "Belirtilen oyuncu mekanýnýzda çalýþmýyor.");

		PlayerInfo[userid][pWorkOn] = 0;

		SendSyntaxMessage(userid, "%s adlý kiþi sizi iþten kovdu.", GetNameWithMask(playerid));
		SendSyntaxMessage(playerid, "%s adlý kiþiyi iþten çýkarttýnýz.", GetNameWithMask(userid));
		return 1;
	}

	else if (CompareStrings(option, "fiyatlar"))
	{
		if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

		new biz = BizInfo[bizid][bizType];
		if (biz != BIZ_STORE && biz != BIZ_BAR && biz != BIZ_PHARMACY && biz != BIZ_PIZZA && biz != BIZ_CLUCKIN && biz != BIZ_BURGER && biz != BIZ_DONUT)	
			return SendErrorMessage(playerid, "Bu mekanda fiyat deðiþikliði yapamazsýnýz.");
		
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
			format(mes, sizeof(mes), "%s{FFFFFF}Ürün fiyat düzenlemesi #%i {AFAFAF}[%s, $%i]\n", mes, i+1, name_order[type][i], BizInfo[bizid][bizProductPrice][i]);
		}

		Dialog_Show(playerid, ConfigPrices, DIALOG_STYLE_LIST, "{9ACD32}Ürün Ayarlarý", mes, "Seç", "Geri Dön");
		return 1;
	}

	else
	{
		SendHelpMessage(playerid, "/mekan [seçenekler]");
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
	if (bizid == -1)													return SendErrorMessage(playerid, "Bir mekana yakýn deðilsin. ");
	if (BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID])		return SendErrorMessage(playerid, "Bu mekan sana ait deðil.");

	static diastr[] = "Mekan Bilgisi\n\
					Çalýþan Bilgisi\n\
					Kasa\n\
					Ücret Ayarlarý\n\
					Mekan Geliþtirmeleri\n\
					Mobilya Düzenleme\n\
					Ürün Satýþý\n\
					Ýsim Deðiþtir\n\
					Açýklama Deðiþtir\n\
					Mekan Sat";

	Dialog_Show(playerid, BusinessMenu, DIALOG_STYLE_LIST, "Mekan Menü", diastr, "Seç", "Çýkýþ");
	return 1;
}

CMD:yemek(playerid, params[])
{
	if (isnull(params))
	{
		SendHelpMessage(playerid, "/yemek [seçenekler]");
		SCM(playerid, COLOR_LIGHTRED,"/yemek siparis {FFFFFF}- yemek sipariþ menüsünü açar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsiyerlestir {FFFFFF}- yemek tepsisini yerleþtirmenizi saðlar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsial {FFFFFF}- yemek tepsinizi elinize almanýzý saðlar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek cop {FFFFFF}- yemek tepsinizi çöpe atmanýzý saðlar.");
		return 1;
	}

	if (CompareStrings(params, "siparis"))
	{
	    new bizid;

		if ((bizid = GetNearInsideBiz(playerid)) == -1)	return SendErrorMessage(playerid, "Herhangi bir mekanýn içinde deðilsiniz.");
		if (BizInfo[bizid][bizType] != BIZ_PIZZA && BizInfo[bizid][bizType] != BIZ_CLUCKIN && BizInfo[bizid][bizType] != BIZ_BURGER && BizInfo[bizid][bizType] != BIZ_DONUT)
		{
		    SendErrorMessage(playerid, "Restorantta deðilsiniz.");
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

		if (dropid == -1) return SendErrorMessage(playerid, "Maksimum tepsi sayýsýna ulaþýldý.");

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
		SendSyntaxMessage(playerid, "Tepsinin konumunu düzenliyorsunuz. Kamerayý hareket ettirmek için \"SPACE\" tuþuna basýlý tutunuz.");
		return 1;
	}

	else if (CompareStrings(params, "tepsial"))
	{
	    if (pTemp[playerid][pFoodStand] != 0 || IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS)) return SendWarningMessage(playerid, "Elleriniz dolu.");

		new dropid = DropFood_Nearest(playerid);

		if (dropid == -1) return SendErrorMessage(playerid, "Yakýnýnýzda tepsi bulunmuyor.");

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
		SendHelpMessage(playerid, "/yemek [seçenekler]");
		SCM(playerid, COLOR_LIGHTRED,"/yemek siparis {FFFFFF}- yemek sipariþ menüsünü açar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsiyerlestir {FFFFFF}- yemek tepsisini yerleþtirmenizi saðlar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek tepsial {FFFFFF}- yemek tepsinizi elinize almanýzý saðlar.");
		SCM(playerid, COLOR_LIGHTRED,"/yemek cop {FFFFFF}- yemek tepsinizi çöpe atmanýzý saðlar.");
	}
	return 1;
}