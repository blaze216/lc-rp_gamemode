CMD:arackirala(playerid, params[])
{
	if (pTemp[playerid][pRentveh])		return SendErrorMessage(playerid, "Zaten bir araç kiralamýþsýnýz, kiraladýðýnýz aracý iade etmek için /arackirabitir komutunu kullanýn.");
	if (GetCash(playerid) < 300)		return SendNotCash(playerid);
	if (Locker_RentalNearestType(playerid, 2) == -1) return SendErrorMessage(playerid, "Herhangi bir kiþisel araç kiralama noktasýna yakýn deðilsin.");

    Dialog_Show(playerid, Rent_Vehicle_Personal, DIALOG_STYLE_LIST, "Kiralýk Araç", "Elegant\nOceanic\nNebula\nPrimo\nTahoma\nVincent\nVirgo\nPrevion\nGreenwood\nGlendale", ">>", ""); 

	SendServerMessage(playerid, "Açýlan menüden kiralamak istediðiniz aracý seçiniz.");

/*
	GiveCash(playerid, -300);
	pTemp[playerid][pRentveh] = vehicle;
    VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	FixVehicle(vehicle);
	VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
	
	SendSyntaxMessage(playerid, "%s model aracý $300'a kiraladýnýz. Kullanabileceðiniz komutlar: /arackirabitir, /a kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	SendSyntaxMessage(playerid, "Dikkat! Aracý 10 dakika boyunca kullanmazsanýz araç spawnlanacaktýr!");*/
	return 1;
}

CMD:arackirabitir(playerid, params[])
{
    if (!pTemp[playerid][pRentveh]) return 1;

	new vehicle = pTemp[playerid][pRentveh];

    SendSyntaxMessage(playerid, "%s model aracýn kiralamasýný sonlandýrdýnýz.", VehicleNames[GetVehicleModel(vehicle)-400]);
	pTemp[playerid][pRentveh] = 0;
    VehicleInfo[vehicle][carRent] = 0;
	pTemp[playerid][pJob] = 0;
    AracKiraBitir(vehicle);
	return 1;
}

CMD:hacizdencikar(playerid, params[])
{
    new vehicle = GetPlayerVehicleID(playerid);

	if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
	if (!vehicle)														return SendNotInVehicle(playerid);
	if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
	if (!VehicleInfo[vehicle][Impounded])								return SendErrorMessage(playerid, "Aracanýza el konmamýþ.");
	if (GetCash(playerid) < IMPOUND_FEE) 								return SendErrorMessage(playerid, "Bu iþlemi tamamlamak için yetersiz paraya sahipsiniz. ($%i).", IMPOUND_FEE);

	GiveCash(playerid, -IMPOUND_FEE);
	VehicleInfo[vehicle][Impounded] = 0;
	Save_Car(vehicle);

    SendSyntaxMessage(playerid, "%s model aracýnýzý  $%i karþýlýðýnda otoparktan aldýnýz.", VehicleNames[GetVehicleModel(vehicle)-400], IMPOUND_FEE);
	SendHelpMessage(playerid, "Aracýnýzý daha sonra güvenli bir yere park etmeyi unutmayýn!(/park)");
	return 1;
}

alias:arac("a");
CMD:arac(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	new parametrs[13], arg[128], vehicle = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehicle);

	if (sscanf(params, "s[13]S()[128]", parametrs, arg))
	{
		SendHelpMessage(playerid, "/(a)rac [seçenekler]");
		SendSyntaxMessage(playerid, "liste | getir | park | bul/gps | kilit | plakagizle | sahteplaka | ilan | anahtar");
		SendSyntaxMessage(playerid, "ceset | cek | bilgi | cezalar | sistemesat | sat | dmvkayit | ilankaldir | kirala");
		SendClientMessageEx(playerid, COLOR_GRAD2, "[EKSTRA]{FFFFFF} /aracmenu /araclarim /ahe /motor /farlar /bagaj /kaput /radyoayarla /cam /hacizdencikar");
		return 1;
	}

    if(!strcmp(parametrs, "ilan",  true))
	{
		pc_cmd_aracilan(playerid, arg);
	}

    else if(!strcmp(parametrs, "ilankaldir",  true))
	{
		pc_cmd_ilankaldir(playerid, "");
	}

	else if(!strcmp(parametrs, "kirala", true))
	{
		pc_cmd_arackirala(playerid, "");
	}

	else if(!strcmp(parametrs, "anahtar", true))
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnz spawnlanmamýþ.");

		static const str_size[] = "{ffffff}%s için kopyala. {C3C3C3}[ID / isim] {ffffff}anahtarlarý kime vermek istiyorsunuz:";
		new mes[sizeof(str_size) - 2 + 1 + 32];

		format(mes, sizeof(mes), str_size, VehicleNames[GetVehicleModel(PlayerInfo[playerid][pCarKey])-400]);
	    Dialog_Show(playerid, DuplicateKey, DIALOG_STYLE_INPUT, "Kopyala", mes, "Satýn Al", "Ýptal");
	    return 1;
	}

    else if(!strcmp(parametrs, "motor", true))
	{
		pc_cmd_motor(playerid, "");
	}

	else if(!strcmp(parametrs, "dmvkayit", true))
	{
        if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

	    vehicle = PlayerInfo[playerid][pCarKey];

	    if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
	    if (IsABicycle(vehicle))												return SendErrorMessage(playerid, "Bisikleti sisteme kayýt ettiremezsiniz.");
	    if (VehicleInfo[vehicle][carEngineOn])								return SendErrorMessage(playerid, "Aracýnýzda deðiþiklik yapmadan önce motoru durdurun!");
	    if (VehicleInfo[vehicle][carRegistered])								return SendErrorMessage(playerid, "Bu araç zaten DMV kayýtlý.");
	    if (GetCash(playerid) < 300)											return SendNotCash(playerid);

	    StartVehicleUpgrade(playerid, vehicle, 7, 300);
	    SendSyntaxMessage(playerid, "Sisteme kayýt iþlemi baþladý, biraz zaman alabilir.");
	}

	else if (!strcmp(parametrs, "plakagizle", true))
	{
		vehicle = GetNearVehicle(playerid, 4.0);

		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
		if (!vehicle)														return SendErrorMessage(playerid, "Aracýnýzýn yakýnýnda deðilsiniz.");
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
		if (VehicleInfo[vehicle][carFakePlate])								return SendErrorMessage(playerid, "Öncelikle sahte plakayý kaldýrmanýz gerekmektedir.");
		if (!IsPlayerHasItem(playerid, INV_TOOLS)) 							return SendErrorMessage(playerid, "Bunun için alet çantasýna ihtiyacýn var!");
		if (VehicleInfo[vehicle][carPlate] == '_') 							return SendErrorMessage(playerid, "Arabanýzýn plakasý bulunmamakta!");

		if (VehicleInfo[vehicle][carHidedPlate])
		{
			VehicleInfo[vehicle][carHidedPlate] = 0;
			SQL_SetInteger("cars", "hidednum", VehicleInfo[vehicle][carHidedPlate], VehicleInfo[vehicle][carID]);
			SetVehicleNumberPlate(vehicle, VehicleInfo[vehicle][carPlate]);
			SetVehicleToRespawn(vehicle);
			SendSyntaxMessage(playerid, "Aracýn plakasýný tekrardan taktýn. Araç park yerine gönderildi.");
		}
		else
		{
			VehicleInfo[vehicle][carHidedPlate] = 1;
			SQL_SetInteger("cars", "hidednum", VehicleInfo[vehicle][carHidedPlate], VehicleInfo[vehicle][carID]);
			SetVehicleNumberPlate(vehicle, "_");
			SetVehicleToRespawn(vehicle);
			SendSyntaxMessage(playerid, "Araçtan plakayý kaldýrdýn. Araç park yerine gönderildi.");
		}
		return 1;
	}

	else if (!strcmp(parametrs, "sahteplaka", true))
	{
		vehicle = GetNearVehicle(playerid, 4.0);

		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
		if (!vehicle)														return SendErrorMessage(playerid, "Aracýnýzýn yakýnýnda deðilsiniz..");
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
		if (!IsPlayerHasItem(playerid, INV_FAKENUM)) 						return SendWarningMessage(playerid, "Sahte plakalýðýn yok.");
		if (VehicleInfo[vehicle][carHidedPlate])							return SendErrorMessage(playerid, "Plakaný gizlemiþsin. (/a plakagizle)");

		if (VehicleInfo[vehicle][carFakePlate])
		{
			VehicleInfo[vehicle][carFakePlate] = 0;
			SQL_SetInteger("cars", "fakenum", VehicleInfo[vehicle][carFakePlate], VehicleInfo[vehicle][carID]);
			SetVehicleNumberPlate(vehicle, VehicleInfo[vehicle][carPlate]);
			SetVehicleToRespawn(vehicle);
			SendSyntaxMessage(playerid, "Sahte plakayý araçtan söktün. Araç park yerine gönderildi.");
		}
		else
		{
			VehicleInfo[vehicle][carFakePlate] = 1;
			SQL_SetInteger("cars", "fakenum", VehicleInfo[vehicle][carFakePlate], VehicleInfo[vehicle][carID]);

			if (isempty(VehicleInfo[vehicle][carFakePlateS]))
			{
				format(VehicleInfo[vehicle][carFakePlateS], 24, "%s", GetVehicleNumber());
				SQL_SetString("cars", "fakenum_str", VehicleInfo[vehicle][carFakePlateS], VehicleInfo[vehicle][carID]);
			}

			SetVehicleNumberPlate(vehicle, VehicleInfo[vehicle][carFakePlateS]);
			SetVehicleToRespawn(vehicle);
			SendSyntaxMessage(playerid, "Sahte plakayý araca taktýn. Araç park yerine gönderildi.");
		}
		return 1;
	}

	else if (!strcmp(parametrs, "menu", true))
	{
		pc_cmd_aracmenu(playerid, "");
	}

	else if (!strcmp(parametrs, "cezalar", true))
	{
		pc_cmd_aracceza(playerid, "");
	}

	else if (!strcmp(parametrs, "getir", true))
	{
		if (IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Zaten spawnlanmýþ bir aracýnýz var.");

		pc_cmd_araclarim(playerid, "");
	}

	else if (!strcmp(parametrs, "park", true))
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
		if (vehicle == 0)													return SendNotInVehicle(playerid);
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
		if (VehicleInfo[vehicle][Impounded])								return SendErrorMessage(playerid, "Bu araç haciz alanýda, çýkartmak için (/hacizdencikar) komutunu kullanabilirsiniz.");

	    for(new i; i != MAX_TRUCK_PRODUCT; i++)
	    {
			if (IsValidDynamicObject(VehicleInfo[vehicle][carCargoObj][i])) return SendErrorMessage(playerid, "Aracýnýzýn bagajýnda koliler varken park edemezsiniz.");
		    break;
	    }

		new Float:hp;
		AntiCheatGetVehicleHealth(vehicle, hp);

		if (hp < 250.0)									return SendErrorMessage(playerid, "Aracýnýz aðýr hasarlý olduðu için bu aracý park edemezsiniz.");

		GetVehiclePos(vehicle, VehicleInfo[vehicle][carParkX], VehicleInfo[vehicle][carParkY], VehicleInfo[vehicle][carParkZ]);
		GetVehicleZAngle(vehicle, VehicleInfo[vehicle][carParkA]);

		SendSyntaxMessage(playerid, "\"%s\" model aracýnýz park edildi.", VehicleNames[model-400]);
		ResetVehicleStuff(vehicle, 1);
		DestroyVehicleEx(vehicle, 1);
		PlayerInfo[playerid][pCarKey] = 0;
		VehicleInfo[vehicle][carOwnerPlayer] = INVALID_PLAYER_ID;
		return 1;
	}

	else if (!strcmp(parametrs, "sat", true))
	{
		new userid, price;

		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))									return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
		if (!vehicle)																		return SendNotInVehicle(playerid);
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])					return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
		if (sscanf(arg, "ui", userid, price))												return SendHelpMessage(playerid, "/a sat [ID / isim] [ücret]");
        if (!IsPlayerLogged(userid))														return SendNotConnected(playerid);
		if (IsADonateModel(GetVehicleModel(vehicle)))										return SendErrorMessage(playerid,"Baðýþcý araçlarýný satamazsýnýz!");
        if (PlayerInfo[userid][pPremium] < 2 && VehicleInfo[vehicle][carComponent][5] != 0)	return SendErrorMessage(playerid, "Bu kiþi nitrolu bir aracý kullanamaz!");
		if (userid == playerid)																return 1;
		if (!IsABicycle(vehicle) && !VehicleInfo[vehicle][carRegistered])					return SendErrorMessage(playerid, "Bu araç sisteme kayýtlý deðil!");
		if (!PlayerNearPlayer(3.0, playerid, userid))										return SendNotNearPlayer(playerid);
		if (IsValidVehicle(PlayerInfo[userid][pCarKey]))									return SendErrorMessage(playerid, "Oyuncunun zaten spawnlanmýþ bir aracý var.");
		if (price < 0 || price > 10000000)													return SendErrorMessage(playerid, "Fiyat $0 ve $10,000,000. aralýðýnda olmalýdýr");

		SendSyntaxMessage(userid, "%s size %s model aracý  $%i karþýlýðýnda satmak istiyor. (Satýn almak için {33AA33}Y{FFFFFF} týklayýn.)", GetNameEx(playerid), VehicleNames[GetVehicleModel(vehicle)-400], price);
		if (IsABicycle(vehicle))
		{
			SendSyntaxMessage(userid, "Güvenlik: Kilit Seviyesi[%i]", VehicleInfo[vehicle][carLock]);
			SendSyntaxMessage(userid, "Diðer: Birincil Renk[{%06x}#%i{FFFFFF}], Ýkincil Renk[{%06x}#%i{FFFFFF}]", VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor1]] >>> 8, VehicleInfo[vehicle][carColor1], VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor2]] >>> 8, VehicleInfo[vehicle][carColor2]);
		}
		else
		{
			SendSyntaxMessage(userid, "Kondisyon: Motor Ömrü[%.2f], Akü Durumu[%.2f], Kilometre[%.2f]",VehicleInfo[vehicle][carEngine], VehicleInfo[vehicle][carBattery], VehicleInfo[vehicle][carMilliage]);
			SendSyntaxMessage(userid, "Güvenlik: Kilit Seviyesi[%i], Alarm Seviyesi[%i], Immobilizer[%i], Sigorta[%i]", VehicleInfo[vehicle][carLock], VehicleInfo[vehicle][carAlarm], VehicleInfo[vehicle][carImmob], VehicleInfo[vehicle][carInsurance]);

			if (VehicleInfo[vehicle][carArmour] > 0.0)	SendSyntaxMessage(userid, "Diðer: Birincil Renk[{%06x}#%i{FFFFFF}], Ýkincil Renk[{%06x}#%i{FFFFFF}], Plaka[%s], Zýrh[%.2f], Radyo[%i]", VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor1]] >>> 8, VehicleInfo[vehicle][carColor1], VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor2]] >>> 8, VehicleInfo[vehicle][carColor2], VehicleInfo[vehicle][carPlate], VehicleInfo[vehicle][carArmour], VehicleInfo[vehicle][carRadio]);
			else										SendSyntaxMessage(userid, "Diðer: Birincil Renk[{%06x}#%i{FFFFFF}], Ýkincil Renk[{%06x}#%i{FFFFFF}], Plaka[%s], Radyo[%i]", VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor1]] >>> 8, VehicleInfo[vehicle][carColor1], VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor2]] >>> 8, VehicleInfo[vehicle][carColor2], VehicleInfo[vehicle][carPlate], VehicleInfo[vehicle][carRadio]);
		}

		SendSyntaxMessage(playerid, "\"%s\" model aracýnýzý %s adlý kiþiye $%i karþýlýðýnda satmak için teklif gönderdiniz.", VehicleNames[GetVehicleModel(vehicle)-400], GetNameWithMask(userid), price);

		pTemp[userid][pCarPlayer] = playerid;
		pTemp[userid][pCarPrice] = price;
		SetPVarInt(userid, #accept_time, gettime() + 30);
		return 1;
	}

	else if (!strcmp(parametrs, "kilitid", true))
	{
		new vehicleid;
		if (sscanf(arg, "i", vehicleid))												return SendHelpMessage(playerid, "/arac kilitid [aracid]");
	    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	    vehicle = vehicleid;
		if (GetNearVehicle(playerid, 4.2, vehicle) == 0) return SendErrorMessage(playerid, "Aracýn yakýnýnda olmalýsýn.");
		if (!IsValidVehicle(vehicle))                    return SendErrorMessage(playerid, "Geçersiz araç ID girdiniz.");
		if (vehicle > 0)
		{
		    if ((VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction])
			 || pTemp[playerid][pRentveh] == vehicle
			 || PlayerInfo[playerid][pCarKey] == vehicle
			 || (PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehicle][carID] && PlayerInfo[playerid][pSpareKey] != 0))
			{
			    PlaySound(playerid, 1145);

				new mes[128];

			    if (VehicleInfo[vehicle][carLocked]) format(mes, sizeof(mes), "KILIT ~g~ACILDI");
				else format(mes, sizeof(mes), "ARAC ~r~KILITLENDI");
				GameTextForPlayer(playerid, mes, 2500, 4);

			    if (VehicleInfo[vehicle][carLocked])	format(mes, sizeof(mes), "%s model aracýn kilidini açtý.", VehicleNames[GetVehicleModel(vehicle)-400]);
				else								format(mes, sizeof(mes), "%s model aracý kilitledi.", VehicleNames[GetVehicleModel(vehicle)-400]);
				SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

			    ToggleVehicleLock(vehicle, (VehicleInfo[vehicle][carLocked]) ? (false): (true));
				return 1;
			}
			else {
				SendErrorMessage(playerid, "Aracýn anahtarý sizde yok!");
				SendHelpMessage(playerid, "Aracýn kilidini kýrmak için /arackilitkir (/akk) komutunu kullanabilirsiniz.");
			}
		}
		return 1;
	}	

	else if (!strcmp(parametrs, "kilit", true))
	{
	    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])	return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	    vehicle = Arac_Yakin(playerid, 4.0);
		if (!vehicle) return SendErrorMessage(playerid, "Yakýnýnýzda araç yok.");
		if (!AracSayiKontrol(playerid)) return SendErrorMessage(playerid, "Etrafýnýzda çok araç var. /arac kilitid komutunu kullanýn.");
		if (vehicle > 0)
		{
		    if ((VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction])
			 || pTemp[playerid][pRentveh] == vehicle
			 || PlayerInfo[playerid][pCarKey] == vehicle
			 || (PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehicle][carID] && PlayerInfo[playerid][pSpareKey] != 0))
			{
			    PlaySound(playerid, 1145);

				new mes[128];

			    if (VehicleInfo[vehicle][carLocked]) format(mes, sizeof(mes), "KILIT ~g~ACILDI");
				else format(mes, sizeof(mes), "ARAC ~r~KILITLENDI");
				GameTextForPlayer(playerid, mes, 2500, 4);

			    if (VehicleInfo[vehicle][carLocked])	format(mes, sizeof(mes), "%s model aracýn kilidini açtý.", VehicleNames[GetVehicleModel(vehicle)-400]);
				else								format(mes, sizeof(mes), "%s model aracý kilitledi.", VehicleNames[GetVehicleModel(vehicle)-400]);
				SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

			    ToggleVehicleLock(vehicle, (VehicleInfo[vehicle][carLocked]) ? (false): (true));
				return 1;
			}
			else {
				SendErrorMessage(playerid, "Aracýn anahtarý sizde yok!");
				SendHelpMessage(playerid, "Aracýn kilidini kýrmak için /arackilitkir (/akk) komutunu kullanabilirsiniz.");
			}
		}
	    return 1;
	}

	else if (!strcmp(parametrs, "bul", true) || !strcmp(parametrs, "gps", true))
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

		vehicle = PlayerInfo[playerid][pCarKey];

		if (!VehicleInfo[vehicle][carGps])			return SendErrorMessage(playerid, "Aracýnýzda GPS yok!");
        if (IsPlayerInVehicle(playerid, vehicle))	return SendErrorMessage(playerid, "Aracýnýzý zaten þu an kullanýyorsunuz.");
		if (!VehicleEmpty(vehicle))					return SendErrorMessage(playerid, "Birisi þu anda aracýnýzý kullanýyor.");
		if (GetVehicleInteriorEx(vehicle))			return SendErrorMessage(playerid, "Aracýnýz bulunamýyor. (interior içinde)");

		new Float:x, Float:y, Float:z;
		GetVehiclePos(vehicle, x, y, z);

		SendSyntaxMessage(playerid, "Aracýnýz \"%s\", \"%s\" alanýnda bulunuyor.", VehicleNames[GetVehicleModel(vehicle)-400], GetVehicleZone(vehicle));
		SendSyntaxMessage(playerid, "Aracýnýzýn konumu haritada iþaretlenmiþtir. (/cpsifirla) komutu ile checkpointi kaldýrabilirsiniz.");
		Waypoint_Set(playerid, x, y, z);
		return 1;
	}

	else if (!strcmp(parametrs, "cek", true))
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

		vehicle = PlayerInfo[playerid][pCarKey];

		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
		if (IsPlayerInVehicle(playerid, vehicle))							return SendErrorMessage(playerid, "Aracýnýzý zaten þu an kullanýyorsunuz.");
		if (!VehicleEmpty(vehicle))											return SendErrorMessage(playerid, "Birisi þu anda aracýnýzý kullanýyor.");
		if (!IsABicycle(vehicle) && !VehicleInfo[vehicle][carRegistered])	return SendErrorMessage(playerid, "Bu araç DMV kayýtlý deðil.");
		if (VehicleInfo[vehicle][Impounded])								return SendErrorMessage(playerid, "Aracýnýz park halinde iken bu komutu kullanamazsýnýz.(/hacizdencikar)");
		if (GetCash(playerid) < 200)										return SendNotCash(playerid);

		SendSyntaxMessage(playerid, "Aracýnýz 10 saniye içinde park yerine çekilecektir.");
        StartVehicleUpgrade(playerid, vehicle, 1, 200);
		return 1;
	}

	else if (!strcmp(parametrs, "bilgi", true))
	{
		if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

  		vehicle = PlayerInfo[playerid][pCarKey];

		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");

		new title[24], diatxt[512];
		format(title, sizeof(title), "%s", VehicleNames[GetVehicleModel(vehicle)-400]);

		if (IsABicycle(vehicle))
		{
			format(diatxt, sizeof(diatxt), "Güvenlik:\n- Kilit\t[%i]\n", VehicleInfo[vehicle][carLock]);
			format(diatxt, sizeof(diatxt), "%sDiðer:\n- Birincil Renk\t[{%06x}#%i{FFFFFF}]\n- Ýkincil Renk\t[{%06x}#%i{FFFFFF}]", diatxt, VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor1]] >>> 8, VehicleInfo[vehicle][carColor1], VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor2]] >>> 8, VehicleInfo[vehicle][carColor2]);
			Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, title, diatxt, ">>", "");
			return 1;
		}

		format(diatxt, sizeof(diatxt), "{ecc317}Legal Kayýt:{FFFFFF}\n");

		if (VehicleInfo[vehicle][carRegistered]) format(diatxt, sizeof(diatxt), "%s{FFFFFF}Plaka - %s\n", diatxt, VehicleInfo[vehicle][carPlate]);
		else 									format(diatxt, sizeof(diatxt), "%s{FF6347}KAYITLI DEÐÝL{FFFFFF}\n", diatxt, VehicleInfo[vehicle][carPlate]);

		if (VehicleInfo[vehicle][carHidedPlate]) format(diatxt, sizeof(diatxt), "%s{FF6347}PLAKA GÝZLENMÝÞ{FFFFFF}\n", diatxt, VehicleInfo[vehicle][carPlate]);
		if (VehicleInfo[vehicle][carFakePlate])	format(diatxt, sizeof(diatxt), "%s{FF6347}SAHTE PLAKA TAKILI\n\t\t[%s]\n", diatxt, VehicleInfo[vehicle][carFakePlateS]);

		format(diatxt, sizeof(diatxt), "%s\n{ecc317}Genel:{FFFFFF}\n- Motor Ömrü\t\t[%.2f]\n- Akü Durumu\t\t[%.2f]\n- Yakýt\t\t[%.1f / %.0f]\n- Kilometre\t\t[%.2f]\n\n", diatxt, VehicleInfo[vehicle][carEngine], VehicleInfo[vehicle][carBattery], VehicleInfo[vehicle][carFuel], GetVehicleFuelCapacity(GetVehicleModel(vehicle)), VehicleInfo[vehicle][carMilliage]);
		format(diatxt, sizeof(diatxt), "%s{ecc317}Güvenlik:{FFFFFF}\n- Kilit Seviyesi\t\t\t[%i]\n- Alarm\t[%i]\n- Immobilizer\t[%i]\n- Sigorta\t\t[%i]\n", diatxt, VehicleInfo[vehicle][carLock], VehicleInfo[vehicle][carAlarm], VehicleInfo[vehicle][carImmob], VehicleInfo[vehicle][carInsurance]);

		if (VehicleInfo[vehicle][carArmour] > 0.0) format(diatxt, sizeof(diatxt), "%sArmor\t[%.2f]\n", diatxt, VehicleInfo[vehicle][carArmour]);

		format(diatxt, sizeof(diatxt), "%s\n{ecc317}Diðer:{FFFFFF}\n- Radyo\t\t%s\n- Birincil Renk\t\t\t[{%06x}#%i{FFFFFF}]\n- Ýkincil Renk\t\t\t[{%06x}#%i{FFFFFF}]", diatxt, (VehicleInfo[vehicle][carRadio])?("{33AA33}Bulunuyor{FFFFFF}"):("{FF6347}Bulunmuyor{FFFFFF}"), VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor1]] >>> 8, VehicleInfo[vehicle][carColor1], VehicleColoursTableRGBA[VehicleInfo[vehicle][carColor2]] >>> 8, VehicleInfo[vehicle][carColor2]);

		Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, title, diatxt, ">>", "");
		return 1;
	}

	else if (!strcmp(parametrs, "liste", true))
	{
	    new query[256];
	    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `owner` = %i", PlayerInfo[playerid][pID]);
		mysql_tquery(dbHandle, query, "ShowCarsForPlayer", "ii", playerid, playerid);
	    return 1;
	}
	else if (!strcmp(parametrs, "ceset", true))
	{
		vehicle = GetNearVehicle(playerid, 4.0);
        if (vehicle == -1)							return SendErrorMessage(playerid, "Aracýn yakýnýnda deðilsiniz.");
 		if (!IsNearTrunk(vehicle, playerid, 2.0)) 	return SendErrorMessage(playerid, "Bagajýn yakýnýnda deðilsiniz! ");
		if (!VehicleInfo[vehicle][carTrunkLock])	return SendErrorMessage(playerid, "Bagaj açýk olmalý.");
		if (!VehicleInfo[vehicle][vCorp] && !CorpInfo[VehicleInfo[vehicle][vCorp]][cUsed]) return SendErrorMessage(playerid, "Bagajda ceset yok!");

		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		DestroyDynamic3DTextLabel(CorpInfo[VehicleInfo[vehicle][vCorp]-1][cText]);

	    CorpInfo[VehicleInfo[vehicle][vCorp]-1][cText]=CreateDynamic3DTextLabel("(( ÖLÜ CESET ))\n'~k~~GROUP_CONTROL_BWD~' tuþuna basýn", COLOR_LIGHTRED, pos[0]+0.75, pos[1], pos[2]-0.4, 50.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 50.0);
		CorpInfo[VehicleInfo[vehicle][vCorp]-1][cX] = pos[0]+0.75;
	    CorpInfo[VehicleInfo[vehicle][vCorp]-1][cY] = pos[1];
	    CorpInfo[VehicleInfo[vehicle][vCorp]-1][cZ] = pos[2];
	    CorpInfo[VehicleInfo[vehicle][vCorp]-1][cVeh] = 0;
		CorpInfo[VehicleInfo[vehicle][vCorp]-1][cTime] = gettime();
		if (CorpInfo[VehicleInfo[vehicle][vCorp]-1][cType] == 0) {
			CorpInfo[VehicleInfo[vehicle][vCorp]-1][cBody]=CreateDynamicActor(CorpInfo[VehicleInfo[vehicle][vCorp]-1][cSkin], pos[0]+0.75, pos[1], pos[2], 0.0);
			SetActorInvulnerable(CorpInfo[VehicleInfo[vehicle][vCorp]-1][cBody], true);
			ApplyActorAnimation(CorpInfo[VehicleInfo[vehicle][vCorp]-1][cBody], "PED", "KO_shot_stom", 4.0, 0, 0, 0, 1, 0);
		} else {
			CorpInfo[VehicleInfo[vehicle][vCorp]-1][cBody]=CreateDynamicObject(19944, pos[0]+0.75, pos[1], pos[2]-0.5, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		}

	    VehicleInfo[vehicle][vCorp]=0;
		SM2(playerid, "Bagajdan ceseti çýkardýnýz.");
		return 1;
	}
	else if (!strcmp(parametrs, "sistemesat", true))
	{
		new veh = PlayerInfo[playerid][pCarKey], lockuse[200], alarmuse[300], immobuse[300], insuranceuse[350], xmradiouse[50], gpsuse[50], string1[1250];

		if (!IsValidVehicle(veh))											return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
		if (!IsPlayerInAnyVehicle(playerid))								return SendNotInVehicle(playerid);
		if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");

		if (VehicleInfo[veh][carLock] == 1) 	 lockuse = "{a9c4e4}Kilit: \t{bab9ba}1 seviye\t{e2bd63}$3.500\n{4af085}+{e2bd63}120 saniye içerisinde kýrýlabilir.\n\n";
		else if (VehicleInfo[veh][carLock] == 2) lockuse = "{a9c4e4}Kilit: \t{bab9ba}2 seviye\t{e2bd63}$5.500\n{4af085}+{e2bd63}180 saniye içerisinde kýrýlabilir.\n\n";
		else if (VehicleInfo[veh][carLock] == 3) lockuse = "{a9c4e4}Kilit: \t{bab9ba}3 seviye\t{e2bd63}$7.500\n{4af085}+{e2bd63}240 saniye içerisinde kýrýlabilir.\n\n";
		else if (VehicleInfo[veh][carLock] == 4) lockuse = "{a9c4e4}Kilit: \t{bab9ba}4 seviye\t{e2bd63}$10.500\n{4af085}+{e2bd63}300 saniye içerisinde kýrýlabilir.\n\n";
		else if (VehicleInfo[veh][carLock] == 5) lockuse = "{a9c4e4}Kilit: \t{bab9ba}5 seviye\t{e2bd63}$13.500\n{4af085}+{e2bd63}360 saniye içerisinde kýrýlabilir.\n\n";

		if (VehicleInfo[veh][carAlarm] == 1) 		alarmuse = "{a9c4e4}Alarm: \t{bab9ba}1 seviye\t{e2bd63}$2.600\n{f0634a}+{e2bd63}Yüksek sesli araç alarmý.\n";
		else if (VehicleInfo[veh][carAlarm] == 2) 	alarmuse = "{a9c4e4}Alarm: \t{bab9ba}2 seviye\t{e2bd63}$5.500\n{f0634a}+{e2bd63}Yüksek sesli araç alarmý\n{f0634a}+{e2bd63}Alarm çalmasý durumunda polis departmanýna haber verilir.\n\n";
		else if (VehicleInfo[veh][carAlarm] == 3) 	alarmuse = "{a9c4e4}Alarm: \t{bab9ba}3 seviye\t{e2bd63}$8.000\n{f0634a}+{e2bd63}Yüksek sesli araç alarmý.\n{f0634a}+{e2bd63}Alarm çalmasý durumunda polis departmanýna haber verilir.\n{f0634a}+{e2bd63}SMS ile bildirim\n\n";
		else if (VehicleInfo[veh][carAlarm] == 4) 	alarmuse = "{a9c4e4}Alarm: \t{bab9ba}4 seviye\t{e2bd63}$10.500\n{f0634a}+{e2bd63}Yüksek sesli araç alarmý.\n{f0634a}+{e2bd63}Alarm çalmasý durumunda polis departmanýna haber verilir.\n{f0634a}+{e2bd63}SMS ile bildirim\n{f0634a}+{e2bd63}Araç bilgisi gpsiniz üzerinde iþaretlenir.\n\n";

		if (VehicleInfo[veh][carImmob] == 1) 		immobuse = "{a9c4e4}Immobilizer: \t{bab9ba}1 seviye\t{e2bd63}$5.600\n{feff00}+{e2bd63}25 saniye düz kontak uygulama süresini arttýrýr.\n\n";
		else if (VehicleInfo[veh][carImmob] == 2) 	immobuse = "{a9c4e4}Immobilizer: \t{bab9ba}2 seviye\t{e2bd63}$11.300\n{feff00}+{e2bd63}50 saniye düz kontak uygulama süresini arttýrýr.\n\n";
		else if (VehicleInfo[veh][carImmob] == 3) 	immobuse = "{a9c4e4}Immobilizer: \t{bab9ba}3 seviye\t{e2bd63}$17.000\n{feff00}+{e2bd63}75 saniye düz kontak uygulama süresini arttýrýr.\n\n";
		else if (VehicleInfo[veh][carImmob] == 4) 	immobuse = "{a9c4e4}Immobilizer: \t{bab9ba}4 seviye\t{e2bd63}$22.600\n{feff00}+{e2bd63}100 saniye düz kontak uygulama süresini arttýrýr.\n\n";

		if (VehicleInfo[veh][carInsurance] == 1) 		insuranceuse = "{a9c4e4}Sigorta: \t{bab9ba}1 seviye\t{e2bd63}$5.600\n{4a90f0}+{e2bd63}Aracýnýz her zaman tamir edilmiþ þekilde býrakýlýr.\n\n";
		else if (VehicleInfo[veh][carInsurance] == 2) 	insuranceuse = "{a9c4e4}Sigorta: \t{bab9ba}2 seviye\t{e2bd63}$11.300\n{4a90f0}+{e2bd63}Aracýnýz her zaman tamir edilmiþ þekilde býrakýlýr..\n{4a90f0}+{e2bd63}Araç hasarýna karþý koruma, aracýnýz sigorta sayesinde yeni gibi duracak.\n\n";
		else if (VehicleInfo[veh][carInsurance] == 3)	insuranceuse = "{a9c4e4}Sigorta: \t{bab9ba}3 seviye\t{e2bd63}$17.000\n{4a90f0}+{e2bd63}Aracýnýz her zaman tamir edilmiþ þekilde býrakýlýr..\n{4a90f0}+{e2bd63}Araç hasarýna karþý koruma, aracýnýz sigorta sayesinde yeni gibi duracak.\n{4a90f0}+{e2bd63}Araç modifikasyonlarý korunur.\n\n";

		if (VehicleInfo[veh][carRadio] == 1) xmradiouse = "{a9c4e4}Radyo:\t{e2bd63}$7.500\n";
		if (VehicleInfo[veh][carGps] == 1) gpsuse = "{a9c4e4}GPS:\t{e2bd63}$3.500\n";

		new mes[56];

		if (IsABicycle(veh))	format(mes, sizeof(mes), "{33AA33}%s", VehicleNames[VehicleInfo[veh][carModel]-400]);
		else
		{
			if (VehicleInfo[veh][carRegistered])	format(mes, sizeof(mes), "{FFFFFF}%s [%s]", VehicleNames[VehicleInfo[veh][carModel]-400], VehicleInfo[veh][carPlate]);
			else								format(mes, sizeof(mes), "{FFFFFF}%s", VehicleNames[VehicleInfo[veh][carModel]-400]);
		}

		format(string1, sizeof(string1), "{ffffff}Satýþ fiyatý:\t\t{e2bd63}$%i\n{ffffff}Maksimum can:\t{e2bd63}%.2f\n\n%s%s%s%s%s%s", GetVehiclePrice(VehicleInfo[veh][carModel])/2, GetVehicleMaxHealth(GetVehicleModel(veh)), lockuse, alarmuse, immobuse, insuranceuse, xmradiouse, gpsuse);
		Dialog_Show(playerid, ScrapSell, DIALOG_STYLE_MSGBOX, mes, string1, "Kabul", "Ýptal");
		return 1;
	}
	else
	{
		SendHelpMessage(playerid, "/(a)rac [seçenekler]");
		SendSyntaxMessage(playerid, "liste | getir | park | bul/gps | kilit | plakagizle | sahteplaka");
		SendSyntaxMessage(playerid, "ceset | cek | bilgi | cezalar | sistemesat | sat | dmvkayit");
		SendClientMessageEx(playerid, COLOR_GRAD2, "[EKSTRA]{FFFFFF} /aracmenu /araclarim /ahe /motor /farlar /bagaj /kaput /radyoayarla /cam /hacizdencikar");
	}
	return 1;
}

CMD:dmvkayit(playerid, params[])
{
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

	new vehicle = PlayerInfo[playerid][pCarKey];

	if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
	if (IsABicycle(vehicle))												return SendErrorMessage(playerid, "Bisikleti sisteme kayýt ettiremezsiniz.");
	if (VehicleInfo[vehicle][carEngineOn])								return SendErrorMessage(playerid, "Aracýnýzda deðiþiklik yapmadan önce motoru durdurun!");
	if (VehicleInfo[vehicle][carRegistered])								return SendErrorMessage(playerid, "Bu araç zaten sisteme kayýtlý.");
	if (GetCash(playerid) < 300)											return SendNotCash(playerid);

	StartVehicleUpgrade(playerid, vehicle, 7, 300);
	SendSyntaxMessage(playerid, "Sisteme kayýt iþlemi baþladý, biraz zaman alabilir.");
	return 1;
}

CMD:dmvkayitsil(playerid, params[])
{
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))					return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");

	new vehicle = PlayerInfo[playerid][pCarKey];

	if (VehicleInfo[vehicle][carOwnerID] != PlayerInfo[playerid][pID])	return SendErrorMessage(playerid, "Aracýn sahibi siz deðilsiniz!");
	if (IsABicycle(vehicle))												return SendErrorMessage(playerid, "Bisikleti sisteme kayýt ettiremezsiniz.");
	if (VehicleInfo[vehicle][carEngineOn])								return SendErrorMessage(playerid, "Aracýnýzda deðiþiklik yapmadan önce motoru durdurun!");
	if (!VehicleInfo[vehicle][carRegistered])							return SendErrorMessage(playerid, "Bu araç sisteme kayýtlý deðil.");
	if (GetCash(playerid) < 300)											return SendNotCash(playerid);

	StartVehicleUpgrade(playerid, vehicle, 8, 300);
	SendSyntaxMessage(playerid, "Sistemden kayýt silme iþlemi baþladý, biraz zamana alabilir.");
	return 1;
}


CMD:farlar(playerid, params[])
{
	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);

	new vehicleid = GetPlayerVehicleID(playerid), mes[128];
	new engine,lights,alarm,doors,bonnet,boot,objective;
	if (PlayerInfo[playerid][pInjured])  return SendErrorMessage(playerid, "Yaralýyken bu komutu kullanamazsýn.");

    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);

	if (lights)
	{
		format(mes, sizeof(mes), "%s model aracýn farlarýný kapatýr.", VehicleNames[GetVehicleModel(vehicleid)-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
		format(mes, sizeof(mes), "~w~%s farlari ~r~kapandi", VehicleNames[GetVehicleModel(vehicleid)-400]);
		GameTextForPlayer(playerid, mes, 2500, 4);
		VehicleInfo[vehicleid][carLights] = 0;
		VehicleLight(vehicleid, false);
		return 1;
	}

	format(mes, sizeof(mes), "%s model aracýn farlarýný açar.", VehicleNames[GetVehicleModel(vehicleid)-400]);
	SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

	format(mes, sizeof(mes), "~w~%s farlari ~g~acildi", VehicleNames[GetVehicleModel(vehicleid)-400]);
	GameTextForPlayer(playerid, mes, 2500, 4);
    VehicleInfo[vehicleid][carLights] = 1;
	VehicleLight(vehicleid, true);
	return 1;
}

CMD:alarmkapat(playerid, params[])
{
    if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))						return SendErrorMessage(playerid, "Aracýnýz spawnlanmadý!");
	if (!GetNearVehicle(playerid, 10.0, PlayerInfo[playerid][pCarKey]))		return SendErrorMessage(playerid, "Aracanýza yakýn olmalýsýnýz.");

    new engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(PlayerInfo[playerid][pCarKey],engine,lights,alarm,doors,bonnet,boot,objective);

	if (alarm < 1)	return SendErrorMessage(playerid, "Alarm çalýþmýyor.");

	AlarmOff(PlayerInfo[playerid][pCarKey]);
	SendWarningMessage(playerid, "Alarmý devre dýþý býraktýnýz.");
	return 1;
}

alias:camlar("cam");
CMD:camlar(playerid, params[])
{
    if (!IsPlayerInAnyVehicle(playerid))				return SendNotInVehicle(playerid);

	new vehicle = GetPlayerVehicleID(playerid), seat = AntiCheatGetVehicleSeat(playerid), model = GetVehicleModel(vehicle), wi;

    if (IsADontWindow(vehicle))						return SendErrorMessage(playerid, "Bu aracýn penceresi yoktur.");

	new mes[128];

    new driver, passenger, backleft, backright;
	GetVehicleParamsCarWindows(vehicle, driver, passenger, backleft, backright);

    if (driver == 0)
	{
		format(mes, sizeof(mes), "tüm pencereleri kapattý. (%s)",VehicleNames[model-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

		GameTextForPlayer(playerid, "~w~pencere ~g~kapandi", 2500, 4);
		SetVehicleParamsCarWindows(vehicle, 1, 1, 1, 1);	
	}
	else
	{
		format(mes, sizeof(mes), "tüm pencereleri açtý. (%s)",VehicleNames[model-400]);
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);

		GameTextForPlayer(playerid, "~w~pencere ~g~acildi", 2500, 4);
		SetVehicleParamsCarWindows(vehicle, 0, 0, 0, 0);	
	}
	return 1;	
}

CMD:araclarim(playerid, params[])
{
	new query[64 + 64];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `owner`=%d", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "ShowListVeh", "i", playerid);
	return 1;
}

alias:ahe("arachizlierisim");
CMD:ahe(playerid, params[])
{
	new vehicle;
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Bir araç kullanýyor olmalýsýnýz.");
	if (!(vehicle = GetPlayerVehicleID(playerid))) 		 return SendErrorMessage(playerid, "Bir araç kullanýyor olmalýsýnýz.");

	new engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(vehicle,engine,lights,alarm,doors,bonnet,boot,objective);

	static mestxt[] = "{FFFFFF}• Motoru %s\t{C7C7C7}/motor\n\
					{FFFFFF}• Kapýlarý %s\t{C7C7C7}/kilit\n\
					{FFFFFF}• Farlarý %s\t{C7C7C7}/farlar\n\
					{FFFFFF}• Bagajý %s\t{C7C7C7}/bagaj\n\
					{FFFFFF}• Kaputu %s\t{C7C7C7}/kaput\n\
					{FFFFFF}• Sürücü penceresi\t{C7C7C7}/camlar\n\
					{FFFFFF}• Radyo\t{C7C7C7}/radyoayarla%s";

	new mes[sizeof(mestxt) + 90];

	format(mes, sizeof(mes), mestxt,
		(!engine)?("çalýþtýr"):("durdur"),
		(doors)?("aç"):("kilitle"),
		(!lights)?("aç"):("kapat"),
		(!boot)?("aç"):("kapat"),
		(!bonnet)?("aç"):("kapat"),
		(PlayerInfo[playerid][pCarKey] == vehicle)?("\n	\n{FF6347}> Araç paneli <"):("")
	);

	new title[39];
	format(title, sizeof(title), "{FFFFFF}%s", VehicleNames[GetVehicleModel(vehicle)-400]);

	Dialog_Show(playerid, VehFastAccess, DIALOG_STYLE_TABLIST, title, mes, "Seç", "Ýptal");
	return 1;
}

CMD:aracmenu(playerid, params[])
{
	if (!IsValidVehicle(PlayerInfo[playerid][pCarKey]))	return SendErrorMessage(playerid,"Aracýnýz spawnlanmadý!");

	new vehicle = PlayerInfo[playerid][pCarKey];
	if (!vehicle) return 1;

	static mestxt[] = ""EMBED_SERVER2"• Araç istatistikleri\n\
					• Ödenmemiþ cezalar\n\
					• Aracý park et\n\
					• GPS ile aracý bul\n\
					• Alarmý devre dýþý býrak[ %s{FFFFFF} ]\n\
					• Aracý sisteme sat\n\
					• Aracý kiþiye sat";
	new mes[sizeof(mestxt)+12],engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(PlayerInfo[playerid][pCarKey],engine,lights,alarm,doors,bonnet,boot,objective);

	format(mes, sizeof(mes), mestxt, (alarm)?("{00E100}AÇIK"):("{FF6347}KAPALI"));

	new title[39];
	format(title, sizeof(title), "{FFFFFF}%s", VehicleNames[GetVehicleModel(vehicle)-400]);
	Dialog_Show(playerid, VehMenu, DIALOG_STYLE_LIST, title, mes, "Seç", "Ýptal");
	return 1;
}

CMD:benzin(playerid, params[])
{
	new vehicle = GetPlayerVehicleID(playerid);

	if (!GetPVarInt(playerid, #UsePump)) {
		new price, Float: f_price, bizid;
		if (!IsDriver(playerid))					return SendNotInVehicle(playerid);
		if ((bizid = AZC_Nearest(playerid)) == -1)	return SendErrorMessage(playerid, "Yakýnýzda benzin alabileceðin bir istasyon yok.");
		if (BizInfo[bizid][bizLocked])				return GameTextForPlayer(playerid, "~r~BENZIN ISTASYONU KAPALI!", 2500, 1);
		if (VehicleInfo[vehicle][carEngineOn]) 		return SendErrorMessage(playerid, "Aracýn motorunu durdurun.");

		new modelid = GetVehicleModel(vehicle);

		if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'P') 	  f_price = float(BizInfo[bizid][bizEntrance]) * 1.2;
		else if (GetVehicleModelInfoAsInt(modelid, "TransmissionData_nEngineType") == 'E') f_price = float(BizInfo[bizid][bizEntrance]) * 0.8;
		else f_price = float(BizInfo[bizid][bizEntrance]);

		price = floatround(f_price, floatround_ceil);
		if (GetCash(playerid) < price) return SendNotCash(playerid);

		new str[128];
		format(str, sizeof(str), "$%i/L karþýlýðýnda yakýt almak istiyor musunuz?", price);
 		ConfirmDialog(playerid, "Araç yakýt", str, "ConfirmFilling");
	} else {
		Fuel_ResetPlayer(playerid);
		ToggleVehicleEngine(vehicle, playerid);
	}
	return 1;
}

alias:motor("aracmotor");
CMD:motor(playerid, params[])
{
	if (!IsDriver(playerid)) return 1;

	new vehicle = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][MissionTime])											 return 1;
	if (pTemp[playerid][pCuffed])     											     return SendCuffedMessage(playerid);
	if (PlayerInfo[playerid][pInjured])                                              return SendErrorMessage(playerid, "Yaralýyken bu komutu kullanamazsýn.");
	if (IsADMVCar(vehicle) || IsADMVHeli(vehicle) || IsABicycle(vehicle))			 return SendErrorMessage(playerid, "Bu aracýn motorunu çalýþtýramazsýnýz.");
	if (VehicleInfo[vehicle][carFuel] == 0.0)										 return SendErrorMessage(playerid, "Araçta benzin bulunmamakta.");
	if (GetPVarInt(playerid, #UsePump))												 return pc_cmd_benzin(playerid, "");
    if (VehicleInfo[vehicle][carOwnerID] && VehicleInfo[vehicle][carEngine] <= 0.0)	 return SendErrorMessage(playerid, "Aracýn motoru çalýþmýyor.");
    if (VehicleInfo[vehicle][carOwnerID] && VehicleInfo[vehicle][carBattery] <= 0.0) return SendErrorMessage(playerid, "Aracýn aküsü çalýþmýyor.");
	if (IsRentCar(vehicle) && pTemp[playerid][pRentveh] != vehicle) 				 return SendErrorMessage(playerid, "Önce aracý kiralamalýsýnýz.");
	if (VehicleInfo[vehicle][Impounded])											 return SendErrorMessage(playerid, "Araç park halindeyken bu komutu kullanamazsýnýz. (/hacizdencikar) komutunu kullanabilirsiniz.");

	if (VehicleInfo[vehicle][carFaction] &&
		VehicleInfo[vehicle][carFaction] != PlayerInfo[playerid][pFaction])			return 1;

	if (	VehicleInfo[vehicle][carType] >= RENT_CAR &&
		VehicleInfo[vehicle][carType] <= MINER_CAR &&
		pTemp[playerid][pRentveh] != vehicle)	return SendErrorMessage(playerid, "Önce aracý kiralayýn /meslekarackirala(/mak).");
    
    if(pTemp[playerid][pRentveh] == vehicle) return ToggleVehicleEngine(vehicle, playerid);

	if ((VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction])
		|| pTemp[playerid][pRentveh] == vehicle
		|| PlayerInfo[playerid][pCarKey] == vehicle
		|| (PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehicle][carID] && PlayerInfo[playerid][pSpareKey] != 0))
	{
		ToggleVehicleEngine(vehicle, playerid);
	}
	else
	{
		if (!VehicleInfo[vehicle][carEngineOn])
		{

			if (!IsPlayerHasItem(playerid, INV_TOOLS)) 	 return SendErrorMessage(playerid, "Motoru düzkontak yoluyla çalýþtýrmak için gerekli araçlara sahip deðilsin.");

			if (!PoliceOnline())						 return SendErrorMessage(playerid, "Oyunda en az %i polis memuru olmalý.", NEED_COPS_TO_CRIME);
			if (VehicleInfo[vehicle][carOwnerID] == INVALID_PLAYER_ID)   return SendErrorMessage(playerid, "Sadece oyuncularýn aldýðý araçlar düzkontaklanabilir.");
			if (JackingEngine[playerid] != 0)            return SendErrorMessage(playerid, "Zaten motoru çalýþtýrmaya çalýþýyorsun!");

			static const str_size[] = "{"COL_GREY"} %s model aracýn motorunu düzkontak yapmaya baþlamak ister misin?";
			new mes[sizeof(str_size) - 4 + 1 + 31 + 7];
			format(mes, sizeof(mes), str_size, VehicleNames[GetVehicleModel(vehicle)-400]); //(VehicleInfo[vehicle][carImmob]+1) * 20
			Dialog_Show(playerid, StartJackingEngine, DIALOG_STYLE_MSGBOX, "{FFFFFF}Düz kontak iþlemi uyguluyorsun", mes, ">>>", "Ýptal");
			return 1;
		}		
	}	
	return 1;
}

CMD:anahtarat(playerid, params[])
{
	if (!PlayerInfo[playerid][pSpareKey])	return SendErrorMessage(playerid, "Anahtarýnýz yok.");

	PlayerInfo[playerid][pSpareKey] = 0;
	SendSyntaxMessage(playerid, "Anahtarlarý yere attýnýz.");
	return 1;
}

CMD:callsign(playerid, params[])
{
	new vehicle = GetPlayerVehicleID(playerid), string[128];

	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);
	if (isnull(params))			return SendHelpMessage(playerid, "/callsign [yazý]");
	if (strlen(params) > 84)	return SendErrorMessage(playerid, "Girilen deðer maksimum 84 karakter olmalýdýr.");

	if (strlen(params) > 28)
	{
		new pos = 28, string1[30], string2[30], string3[30];

		if (pos < 28-1) pos = 28;

		if (strlen(params[pos]) > 28)
		{
			format(string1, sizeof(string1), "%.*s", pos, params);
			format(string2, sizeof(string2), "%.*s", pos, params[pos]);
			format(string3, sizeof(string3), "%.*s", pos, params[pos+pos]);
			format(string, sizeof(string), "%s\n%s\n%s", string1, string2, string3);
		}
		else
		{
			format(string1, sizeof(string1), "%.*s", pos, params);
			format(string2, sizeof(string2), "%s", params[pos]);
			format(string, sizeof(string), "%s\n%s", string1, string2);
		}
	}
	else
	{
		format(string, sizeof(string), "%s",params);
	}

	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))
		return SCM(playerid, COLOR_LIGHTRED, "Sadece polis ve paramedikler kendine ait olmayan birlik araçlarýna etiket yerleþtirebilir.");

	if (!PlayerInfo[playerid][pOnDuty])
		return SCM(playerid, COLOR_LIGHTRED, "Görev baþýnda olmalýsýnýz. (/isbasi).");

	if (VehicleInfo[vehicle][carFaction] != faction)
	    return SendErrorMessage(playerid, "Bu araç birliðinize ait deðildir.");

	SendHelpMessage(playerid, "Tekrar /callsign yazarak kaldýrabilirsiniz.");
	if (!IsValidDynamic3DTextLabel(veicolo_callsign_testo[vehicle]))
	{
	    new Float: x,
	        Float: y,
	        Float: z;
        GetCarsignPosition(vehicle, x, y, z);
		veicolo_callsign_testo[vehicle] = CreateDynamic3DTextLabel(string, 0xFFFFFFFF, -x, y, z, 40.0, INVALID_PLAYER_ID, vehicle, 1, -1, 0);
		SendServerMessage(playerid, "%s isimli callsign eklendi.", string);
	}
    else if (IsValidDynamic3DTextLabel(veicolo_callsign_testo[vehicle]))
	{
		DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicle]);
        veicolo_callsign_testo[vehicle] = Text3D:INVALID_3DTEXT_ID;
		SendServerMessage(playerid, "Callsign kaldýrýldý.");
	}
	return 1;	
}

CMD:aracilan(playerid,params[])
{
	new vehicle = GetPlayerVehicleID(playerid), string[128];

	if (!IsDriver(playerid))	return SendNotInVehicle(playerid);
	if (isnull(params))			return SendHelpMessage(playerid, "/aracilan [yazý]");
	if (IsABicycle(vehicle))	return SendErrorMessage(playerid,"Bu araca etiket belirleyemezsiniz.");
	if (strlen(params) > 84)	return SendErrorMessage(playerid, "Girilen deðer maksimum 84 karakter olmalýdýr..");

	if (strlen(params) > 28)
	{
		new pos = 28, string1[30], string2[30], string3[30];

		if (pos < 28-1) pos = 28;

		if (strlen(params[pos]) > 28)
		{
			format(string1, sizeof(string1), "%.*s", pos, params);
			format(string2, sizeof(string2), "%.*s", pos, params[pos]);
			format(string3, sizeof(string3), "%.*s", pos, params[pos+pos]);
			format(string, sizeof(string), "%s\n%s\n%s", string1, string2, string3);
		}
		else
		{
			format(string1, sizeof(string1), "%.*s", pos, params);
			format(string2, sizeof(string2), "%s", params[pos]);
			format(string, sizeof(string), "%s\n%s", string1, string2);
		}
	}
	else
	{
		format(string, sizeof(string), "%s",params);
	}

	if (PlayerInfo[playerid][pCarKey] == vehicle)
	{
		if (!IsPlayerHasItem(playerid, INV_SIGN))		return SendErrorMessage(playerid, "Araba etiketiniz yok. Marketten alabilirsiniz.");
		if (PlayerInfo[playerid][pCarKey] != vehicle)	return SendErrorMessage(playerid, "Etiketler yalnýzca kiþisel araçlara takýlabilir.");

		SendHelpMessage(playerid, "/arac ilankaldir - etiketi geri kaldýrýrsýnýz.");
		if (!IsValidDynamic3DTextLabel(veicolo_callsign_testo[vehicle]))
		{
		    new Float: x, Float: y, Float: z;
        	GetCarsignPosition(vehicle, x, y, z);
			veicolo_callsign_testo[vehicle] = CreateDynamic3DTextLabel(string,0x33AA33FF, -x, y, z, 20.0, INVALID_PLAYER_ID, vehicle, 1, -1, 0);
		}
		else	UpdateDynamic3DTextLabelText(veicolo_callsign_testo[vehicle], 0x33AA33FF, string);

		RemovePlayerItem(playerid, INV_SIGN, 1);

		return 1;
	}

	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionLegal(faction))
		return SCM(playerid, COLOR_LIGHTRED, "Sadece polis ve paramedikler kendine ait olmayan birlik araçlarýna etiket yerleþtirebilir.");

	if (!PlayerInfo[playerid][pOnDuty])
		return SCM(playerid, COLOR_LIGHTRED, "Görev baþýnda olmalýsýnýz. (/isbasi).");

	if (VehicleInfo[vehicle][carFaction] != faction)
	    return SendErrorMessage(playerid, "Bu araç birliðinize ait deðildir.");

	SendHelpMessage(playerid, "/arac ilankaldir - araba etiketini kaldýrma.");
	if (!IsValidDynamic3DTextLabel(veicolo_callsign_testo[vehicle]))
	{
	    new Float: x,
	        Float: y,
	        Float: z;
        GetCarsignPosition(vehicle, x, y, z);
		veicolo_callsign_testo[vehicle] = CreateDynamic3DTextLabel(string,0xFFFFFFFF, -x, y, z, 40.0, INVALID_PLAYER_ID, vehicle, 1, -1, 0);
	}
	else
		UpdateDynamic3DTextLabelText(veicolo_callsign_testo[vehicle], 0xFFFFFFFF, string);
	return 1;
}

CMD:ilankaldir(playerid,params[])
{
    if (!IsDriver(playerid))	return SendNotInVehicle(playerid);

	new vehicle = GetPlayerVehicleID(playerid);
    if (PlayerInfo[playerid][pCarKey] != vehicle)	return SendErrorMessage(playerid, "Bu komutu kullanmaya yetkiniz yok.");

    if (IsValidDynamic3DTextLabel(veicolo_callsign_testo[vehicle]))
	{
		DestroyDynamic3DTextLabel(veicolo_callsign_testo[vehicle]);
        veicolo_callsign_testo[vehicle] = Text3D:INVALID_3DTEXT_ID;
	}
	return 1;
}

CMD:durdur(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured]) return 1;

	/*if (JackingEngine[playerid] != 0)
	{
		JackingEngine[playerid] = 0;
		UnFreezePlayer(playerid);
		SendSyntaxMessage(playerid, "Âû îñòàíîâor âçëîì äâèãàòåëÿ.");
	}

	if (JackingLock[playerid] != 0)
	{
		JackingLock[playerid] = 0;
		JackingVehicle[playerid] = 0;
		UnFreezePlayer(playerid);
		SendSyntaxMessage(playerid, "Âû îñòàíîâor âçëîì äâåðåé.");
	}*/

	if (pTemp[playerid][pPlantTime] != 0)
	{
		UnFreezePlayer(playerid);
		StopPlayerAnims(playerid);
		pTemp[playerid][pPlantTime] = 0;
		pTemp[playerid][pPlantType] = 0;
		SendSyntaxMessage(playerid, "Tohum ekmeyi býraktýn.");
	}

	if (pTemp[playerid][pFireTime] != 0)
	{
		StopCreatingPlayersFire(playerid);
		SendSyntaxMessage(playerid, "Ateþ yakmayý býraktýn.");
	}
	return 1;
}

CMD:bagaj(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    new vehicle = GetPlayerVehicleID(playerid);

	    if (IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))	return SendErrorMessage(playerid, "Bu aracýn bagajý bulunmuyor.");
		if (VehicleInfo[vehicle][carLocked] || (IsRentCar(vehicle) && !VehicleInfo[vehicle][carRent]))												return SendErrorMessage(playerid, "Bu araç kilitli. ");
        if (!GetPlayerHasRightTrunk(playerid, vehicle)) return SendErrorMessage(playerid, "Bu aracýn bagajýný açamazsýnýz.");
 
		if (VehicleInfo[vehicle][carTrunkLock] == 1)
		{
		    new mes[56];
			format(mes, sizeof(mes), "~w~BAGAJ %s ~r~KAPANDI", VehicleNames[GetVehicleModel(vehicle)-400]);
			GameTextForPlayer(playerid, mes, 3000, 3);

			VehicleTrunk(vehicle, false);
			SendSyntaxMessage(playerid, "Aracýn bagajýný kapattýnýz.");
			return 1;
		}
		else
		{
			new mes[56];
	        format(mes, sizeof(mes), "~w~BAGAJ %s ~g~ACILDI", VehicleNames[GetVehicleModel(vehicle)-400]);
			GameTextForPlayer(playerid, mes, 3000, 3);

			VehicleTrunk(vehicle, true);
			SendSyntaxMessage(playerid, "Aracýn bagajýný açtýnýz.");
			SendHelpMessage(playerid, "Etkileþime girmek için N tuþuna basýn.");

			if (vehicle != 0 && (!IsADontTrunk(vehicle) || !IsAPlane(vehicle) || !IsABiker(vehicle) || !IsAHelicopter(vehicle) || !IsABoat(vehicle) || !IsABicycle(vehicle)))
			{
				if ((VehicleInfo[vehicle][carTrunkLock] && !IsPlayerInAnyVehicle(playerid)) || (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]))
				{
					PrintVehInv(playerid, vehicle);
				}
			}

		}
		return 1;
	}

	new vehicle = GetNearVehicle(playerid, 4.0);
	if (vehicle == -1)							return SendErrorMessage(playerid, "Aracýn yakýnýnda deðilsiniz.");
    if (!IsNearTrunk(vehicle, playerid, 5.0)) 	return SendErrorMessage(playerid, "Bagajýn yakýnýnda deðilsiniz! ");

	if (VehicleInfo[vehicle][carOwnerID] && PlayerInfo[playerid][pCarKey] != vehicle)							return SendErrorMessage(playerid, "Bu araç size ait deðil.");
    if (VehicleInfo[vehicle][carFaction] && PlayerInfo[playerid][pFaction] != VehicleInfo[vehicle][carFaction])	return SendErrorMessage(playerid, "Bu araç baþka bir birliðe ait.");
    if (VehicleInfo[vehicle][carLocked] || (IsRentCar(vehicle) && VehicleInfo[vehicle][carRent]))				return SendErrorMessage(playerid, "Araç kilitli.");

    if (VehicleInfo[vehicle][carTrunkLock] == 1)
	{
	    new mes[56];
		format(mes, sizeof(mes), "~w~BAGAJ %s ~r~KAPANDI", VehicleNames[GetVehicleModel(vehicle)-400]);
		GameTextForPlayer(playerid, mes, 3000, 3);

		VehicleTrunk(vehicle, false);
		SendSyntaxMessage(playerid, "Aracýn bagajýný kapattýnýz.");
		return 1;
	}
	else
	{
		new mes[56];
        format(mes, sizeof(mes), "~w~BAGAJ %s ~g~ACILDI", VehicleNames[GetVehicleModel(vehicle)-400]);
		GameTextForPlayer(playerid, mes, 3000, 3);


		if (vehicle != 0 && (!IsADontTrunk(vehicle) || !IsAPlane(vehicle) || !IsABiker(vehicle) || !IsAHelicopter(vehicle) || !IsABoat(vehicle) || !IsABicycle(vehicle)))
		{
			if ((VehicleInfo[vehicle][carTrunkLock] && !IsPlayerInAnyVehicle(playerid)) || (IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carFaction] && VehicleInfo[vehicle][carFaction] == PlayerInfo[playerid][pFaction]))
			{
				PrintVehInv(playerid, vehicle);
			}
		}

		VehicleTrunk(vehicle, true);
		SendSyntaxMessage(playerid, "Aracýn bagajýný açtýnýz.");
	}
	return 1;
}

CMD:kaput(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    new vehicle = GetPlayerVehicleID(playerid);

		if (IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))	return SendErrorMessage(playerid, "Bu aracýn kaputu yok");
		if (VehicleInfo[vehicle][carLocked])																				return SendErrorMessage(playerid, "Kilitli aracýn kaputunu açamazsýn.");

		if (VehicleInfo[vehicle][carHoodLock] == 1)
		{
		    new mes[56];
			format(mes, sizeof(mes), "~w~%s KAPUT ~r~KAPANDI", VehicleNames[GetVehicleModel(vehicle)-400]);
			GameTextForPlayer(playerid, mes, 3000, 3);

			VehicleHood(vehicle, false);
			SendSyntaxMessage(playerid, "Aracýn kaputunu kapattýnýz.");
			return 1;
		}
		else
		{
			new mes[56];
	        format(mes, sizeof(mes), "~w~%s KAPUT ~g~ACILDI", VehicleNames[GetVehicleModel(vehicle)-400]);
			GameTextForPlayer(playerid, mes, 3000, 3);

			VehicleHood(vehicle, true);
			SendSyntaxMessage(playerid, "Aracýn kaputunu açtýnýz.");
		}
		return 1;
	}

	new vehicle = 0;

	foreach(new i : Vehicle)
	{
	    if (IsAPlane(i) || IsABiker(i) || IsAHelicopter(i) || IsABoat(i) || IsABicycle(i) || !IsOnHoodVehicle(playerid, i)) continue;

	    vehicle = i;
		break;
	}

	if (!vehicle)							return SendErrorMessage(playerid, "Yakýnýnýzda kaputlu bir araç yok.");
    if (VehicleInfo[vehicle][carLocked])	return SendErrorMessage(playerid, "Araç kilitli.");
    if (VehicleInfo[vehicle][carHoodLock] == 1)
	{
	    new mes[56];
		format(mes, sizeof(mes), "~w~%s KAPUT ~r~KAPANDI", VehicleNames[GetVehicleModel(vehicle)-400]);
		GameTextForPlayer(playerid, mes, 3000, 3);

		VehicleHood(vehicle, false);
		SendSyntaxMessage(playerid, "Aracýn kaputunu kapattýnýz.");
		return 1;
	}
	else
	{
		new mes[56];
        format(mes, sizeof(mes), "~w~%s KAPUT ~g~ACILDI", VehicleNames[GetVehicleModel(vehicle)-400]);
		GameTextForPlayer(playerid, mes, 3000, 3);

		VehicleHood(vehicle, true);
		SendSyntaxMessage(playerid, "Aracýn kaputunu açtýnýz.");
	}
	return 1;
}

alias:arackilitkir("akk");
CMD:arackilitkir(playerid, params[])
{
	if (!PoliceOnline())	return SendErrorMessage(playerid, "Oyunda en az %i polis memuru olmalý.", NEED_COPS_TO_CRIME);

	new vehid = Arac_Yakin(playerid, 3.0);
	if (!vehid)	return SendErrorMessage(playerid, "Yakýnýnýzda araç yok.");

	if (VehicleInfo[vehid][carOwnerID] == PlayerInfo[playerid][pID] || PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehid][carOwnerID])
		return SendErrorMessage(playerid, "Kendi aracýnýzý çalamazsýnýz!");

	if (VehicleInfo[vehid][carType])			return SendErrorMessage(playerid, "Yalnýzca oyuncu araçlarý çalýnabilir.");
	if (VehicleInfo[vehid][carOwnerID] == INVALID_PLAYER_ID)    return SendErrorMessage(playerid, "Yalnýzca oyuncu araçlarý çalýnabilir.");
	if (VehicleInfo[vehid][carLocked] == 0)     return SendErrorMessage(playerid, "Araç kapýlarý açýk.");
	if (JackingLock[playerid] != 0)             return SendErrorMessage(playerid, "Zaten kapýlarý kýrýyorsun!");
	if (!IsPlayerInFrontVDoor(playerid, vehid)) return SendErrorMessage(playerid, "Sürücü kapýsýnýn yanýnda olmalýsýn.");

	foreach(new i : Player) {
		if (JackingVehicle[i] == vehid) return SendErrorMessage(playerid, "Birisi zaten bu aracýn kapýlarýný kýrmýþ veya kýrmaya çalýþýyor.");
	}

	new param[10];
	if (sscanf(params, "s[10]", param)) {
		SendHelpMessage(playerid, "/akk [tür] veya /arackilitkir [tür]");
		SendSyntaxMessage(playerid, "sessiz - levye ile araç kapýsýný sessizce kýrabilirsiniz. (Aksesuarcýdan levye almalýsýn)");
		SendSyntaxMessage(playerid, "sesli - aracýn kapýlarýnýn yüksek sesle kýrýlmasý, araç alarmýný etkinleþtirir.");
		return 1;
	}

	if (CompareStrings(param, "s") || CompareStrings(param, "sessiz"))
	{
		//if (!IsPlayerHasItem(playerid, INV_PICKLOCK)) return SendErrorMessage(playerid, "Ó âàñ äîëæíà áûòü îòìû÷êà, ÷òîáû âçëàìûâàòü çàìîê òðàíñïîðòà.");
		if (!CheckHanditem(playerid,18634))		 return SendErrorMessage(playerid, "Elinizde bir levye olmalý. (/aksesuar)");
		if (IsPlayerCrouching(playerid) == false) return SendErrorMessage(playerid, "Eðilmelisiniz.");

		SetPVarInt(playerid, #JackingVehicle, vehid);
		pTemp[playerid][JackingType] = 1;

		static const str_size[] = "{"COL_GREY"}%s kapýlarýný kýrmaya baþlamak istiyor musunuz? %i saniyeye ihtiyacýn var.";
		new mes[sizeof(str_size) - 4 + 1 + 31 + 7];
		format(mes, sizeof(mes), str_size, VehicleNames[GetVehicleModel(vehid)-400], 250+VehicleInfo[vehid][carLock]*250);
        Dialog_Show(playerid, StartJackingLock, DIALOG_STYLE_MSGBOX, "{FFFFFF}Kilit Kýrma", mes, ">>>", "Ýptal");
	}
	else if (CompareStrings(param, "se") || CompareStrings(param, "sesli"))
	{
		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Ayakta olmalýsýn.");

		SetPVarInt(playerid, #JackingVehicle, vehid);
		pTemp[playerid][JackingType] = 2;

		static const str_size[] = "{"COL_GREY"}%s kapýlarýný kýrmaya baþlamak istiyor musunuz?";
		new mes[sizeof(str_size) - 4 + 1 + 31 + 7];
		format(mes, sizeof(mes), str_size, VehicleNames[GetVehicleModel(vehid)-400]);
        Dialog_Show(playerid, StartJackingLock, DIALOG_STYLE_MSGBOX, "{FFFFFF}Kilit Kýrma", mes, ">>>", "Ýptal");
	}
	else {
		SendHelpMessage(playerid, "/akk [tür] veya /arackilitkir [tür]");
		SendSyntaxMessage(playerid, "sessiz - levye ile araç kapýsýný sessizce kýrabilirsiniz.");
		SendSyntaxMessage(playerid, "sesli - aracýn kapýlarýnýn yüksek sesle kýrýlmasý, araç alarmýný etkinleþtirir.");
		return 1;
	}



	return 1;
}

alias:duzkontak("dkk");
CMD:duzkontak(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid) || !JackingEngine[playerid]) return SendErrorMessage(playerid, "Bu komutu þu anda kullanamazsýnýz!");

	new unword[64];
	if (sscanf(params, "s[64]", unword))	return SendHelpMessage(playerid, "/duzkontak [þifreli kelime]");

	new vehid = GetPlayerVehicleID(playerid);
	if (!isnull(unword) && CompareStrings(unword, UnscrambleInfo[pTemp[playerid][pUnscrambleID]][eUnscrambledWord]))
	{
		pTemp[playerid][pScrambleSuccess]++;
		PlaySound(playerid, 1052);

		switch(VehicleInfo[vehid][carImmob])
		{
			case 0: if (pTemp[playerid][pScrambleSuccess] < 3) return NewScrambleWord(playerid);
			case 1: if (pTemp[playerid][pScrambleSuccess] < 4) return NewScrambleWord(playerid);
			case 2: if (pTemp[playerid][pScrambleSuccess] < 5) return NewScrambleWord(playerid);
			case 3: if (pTemp[playerid][pScrambleSuccess] < 6) return NewScrambleWord(playerid);
			case 4: if (pTemp[playerid][pScrambleSuccess] < 7) return NewScrambleWord(playerid);
		}

		JackingEngine[playerid] = 0;
		pTemp[playerid][pUnscrambleID] = 0;
		pTemp[playerid][pScrambleFailed] = 0;
		pTemp[playerid][pScrambleSuccess] = 0;

		if (IsValidVehicle(GetPlayerVehicleID(playerid))) {
			ToggleVehicleEngine(GetPlayerVehicleID(playerid), playerid);
			PlaySound(playerid, 1145);
			AlarmOff(vehid);
			InfoMSG(playerid, "MOTOR ~g~BASARIYLA ~w~CALISTIRILDI!", 3);
		}
	}
	else {
		pTemp[playerid][pScrambleFailed]++;
		PlaySound(playerid,1085);

		switch(VehicleInfo[vehid][carImmob])
		{
			case 0: if (pTemp[playerid][pScrambleFailed] == 3) return StopJackingEngine(playerid);
			case 1: {
				if (pTemp[playerid][pScrambleFailed] >= 2){
					PlaySound(playerid, 1138);
					AlarmOn(vehid);

					if (pTemp[playerid][pScrambleFailed] == 3) return StopJackingEngine(playerid);
				}
			}
			case 2: {
				if (pTemp[playerid][pScrambleFailed] >= 2){
					PlaySound(playerid, 1138);
					AlarmOn(vehid);
					return StopJackingEngine(playerid);
				}
			}
			case 3: {
				PlaySound(playerid, 1138);
				AlarmOn(vehid);

				if (pTemp[playerid][pScrambleFailed] == 2) return StopJackingEngine(playerid);
			}
			case 4: {
				PlaySound(playerid, 1138);
				AlarmOn(vehid);
				return StopJackingEngine(playerid);
			}
		}

		NewScrambleWord(playerid);
	}

	return 1;
}

/*
alias:jackingvehicle("jackv");
CMD:jackingvehicle(playerid, params[])
{
	//new vehicle = GetPlayerVehicleID(playerid);

	if (!VehicleInfo[vehicle][carOwnerID]) 									return SendErrorMessage(playerid, "Âû íå ìîæåòå óãíàòü ãîñóäàðñòâåííûé òðàíñïîðò.")
	if (!VehicleInfo[vehicle][carEngineOn]) 									return SendErrorMessage(playerid, "Âû íå ìîæåòå óãíàòü çàãëóøåííûé òðàíñïîðò.")
	if (PlayerInfo[playerid][pCarKey] == vehicle
		|| PlayerInfo[playerid][pSpareKey] == VehicleInfo[vehicle][carID])  return SendErrorMessage(playerid, "Âû íå ìîæåòå óãíàòü ñâîé òðàíñïîðò, à òàêæå òðàíñïîðò, îò êîòîðîãî ó âàñ åñòü êëþ÷è.")

	if (!PoliceOnline())	return SendErrorMessage(playerid, "Â èãðå äîæíî áûòü õîòÿ áû %i ïîëèöåéñêèõ.", NEED_COPS_TO_CRIME);

	new jtime = pTemp[playerid][JackingTime]-gettime();

	if (GetPVarInt(playerid, #JACKING_PROCESS))						  return SendErrorMessage(playerid, "Âû óæå óãîíÿåòå òðàíñïîðò.");
	if (pTemp[playerid][JackingTime] == 0) 							  return SendErrorMessage(playerid, "Âû íå óãîíÿëè íèêàêîé òðàíñïîðò.");
	if (jtime > 0) 													  return SendErrorMessage(playerid, "Âû íå ìîæåòå óãíàòü ýòîò òðàíñïîðò åù¸ %i ñåêóíä.", jtime);
	if (GetPlayerVehicleID(playerid) != pTemp[playerid][JackingVehID]) return SendErrorMessage(playerid, "Âû íå óãîíÿëè ýòîò òðàíñïîðò.");

	if (IsPoliceNear(playerid)) return SendErrorMessage(playerid, "Âû íå ìîæåòå óãíàòü òðàíñïîðò, òàê êàê ðÿäîì ñ âàìè åñòü ïîëèöåéñêèå.");

	pTemp[playerid][JackingTime] = 0;
	SetPVarInt(playerid, #JACKING_PROCESS, 1);
	//pTemp[playerid][JackingVehID] = 0;

	DisableWaypoint(playerid);
	if (IsValidDynamicCP(pTemp[playerid][JackingCP])) DestroyDynamicCP(pTemp[playerid][JackingCP]);
	pTemp[playerid][JackingCP] = 0;

	new randomCP = random(sizeof(Jacking_CP));
	pTemp[playerid][JackingCP] = CreateDynamicCP(Jacking_CP[randomCP][0], Jacking_CP[randomCP][1], Jacking_CP[randomCP][2], 1.5, 0, 0, playerid, 15000.0);
	TogglePlayerDynamicCP(playerid, pTemp[playerid][JackingCP], true);
    Streamer_Update(playerid, STREAMER_TYPE_CP);

	InfoMSG(playerid, "ÄÎÑÒÀÂÜÒÅ ÒÐÀÍÑÏÎÐÒ ÍÀ ~r~×ÅÊÏÎÈÍÒ~w~, ×ÒÎÁÛ ÏÎËÓ×ÈÒÜ ÇÀ ÍÅÃÎ ~g~ÄÅÍÜÃÈ~w~~n~ÅÑËÈ ÏÎ ~y~ÏÐÈÁÛÒÈÞ~w~ ÇÀ ÂÀÌÈ ÁÓÄÅÒ ~y~ÕÂÎÑÒ~w~, Â ÒÀÊÎÌ ÑËÓ×ÀÅ ~r~×ÅÊÏÎÈÍÒ~w~~n~ÁÓÄÅÒ ~y~ÑÎÇÄÀÍ ÅÙ¨ ÐÀÇ!", 8);
	return 1;
}*/

alias:deletejackvehicles("deljackveh");
CMD:deletejackvehicles(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 5) return 0;
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM cars WHERE owner = %i AND jacking = 1", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "Remove_ShowVehicleList", "i", playerid);

	return 1;
}
