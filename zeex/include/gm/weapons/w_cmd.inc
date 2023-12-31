CMD:silahlarim(playerid)
{
	pc_cmd_silah(playerid, "liste");
	return 1;
}

CMD:silah(playerid, params[]) // Loglanacak
{
	new opsiyon[32];
	if(PlayerInfo[playerid][pLevel] < 3) return SendErrorMessage(playerid, "Bu sistemden sadece 3. seviye ve �st� kullan�c�lar yararlanabilir.");

	if(sscanf(params, "s[32]", opsiyon)){
        SendSyntaxMessage(playerid, "/silah [fonksiyon]");
		SendClientMessageEx(playerid, COLOR_GREY, "{9FA8C7}Temel fonksiyonlar: {C8C8C8}liste/birak/envanter/ver/pozisyon/sistemesat");	
        SendClientMessageEx(playerid, COLOR_GREY, "siparis: �llegal birlik �yelerinin sipari� verebilece�i komut.");
        SendClientMessageEx(playerid, COLOR_GREY, "siparisdurum: Sipari�leri kontrol etmeye yarayan komut.");
        SendClientMessageEx(playerid, COLOR_GREY, "teslimal: Sipari�i teslim alman�za yarayan komut.");
        return 0;	
	} 

	SilahlariKaydet(playerid);
	if(!strcmp(opsiyon, "liste", true)) Dialog_Show(playerid, SilahListeGoruntule, DIALOG_STYLE_INPUT, "Silah Sistemi", "Bu karaktere kay�tl� t�m silahlar� listelemek istedi�inize emin misiniz?\nEminseniz a�a��daki kutucu�a onay i�in 'EVET' yazmal�s�n�z.", "Evet", "Hay�r");
	else if(!strcmp(opsiyon, "pozisyon", true))
	{
		new weaponid = AC_GetPlayerWeapon(playerid);
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(!weaponid) return SendErrorMessage(playerid, "Elinizde silah yokken pozisyon d�zenleyemezsiniz.");
		if(!IsWeaponWearable(weaponid)) return SendErrorMessage(playerid, "Elinizde bulunan silah pozisyon sistemine dahil de�il.");

		Dialog_Show(playerid, DialogSilahPozisyon, DIALOG_STYLE_LIST, "Silah Pozisyon Sistemi", "Silah� Gizle / G�ster\nKemik Ayarla\nPozisyon D�zenle\nPozisyon S�f�rla", "OK", "<<");
	}
	else if(!strcmp(opsiyon, "birak", true) || !strcmp(opsiyon, "yerlestir", true))
	{
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "��ba��nda bu sistemden yararlanamazs�n�z.");

		new bweaponid = AC_GetPlayerWeapon(playerid), rows, tempwid, tempsqlid, vid = Arac_Yakin(playerid, 5.0), h = GetNearInsideHouse(playerid);

		if(!bweaponid)
		{
			Dialog_Show(playerid, MermisizSilahlar, DIALOG_STYLE_INPUT, "Alternatif Silah Yerle�tirme", "E�er mermisi olmayan bir silaha sahipseniz ve m�lk�n�ze bu silah� yerle�tirmek istiyorsan�z bu fonksiyondan yararlanabilirsiniz.\nA�a��daki kutucu�a onay i�in 'EVET' yazmal�s�n�z.", "Evet", "Hay�r");
			return SendErrorMessage(playerid, "Elinizde silah yokken bu i�lemi yapamazs�n�z.");
		}

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0' AND weaponid = '%d'", PlayerInfo[playerid][pID], bweaponid);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		cache_get_row_count(rows);
		if(!rows) return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazs�n�z."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", tempsqlid);
				cache_get_value_int(j, "weaponid", tempwid);

				if(tempwid == bweaponid)break;
			}
		}
		cache_delete(veri);

		if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
		{
			if(HouseInfo[h][hLocked] == 1 && PlayerInfo[playerid][pID] != HouseInfo[h][hOwner]) return SendErrorMessage(playerid, "Kap�s� kilitli evlere silah koyamazs�n�z.");
			if(Silah_SayiKontrol(1, h) >= MAX_WEAPON_HOUSE) return SendErrorMessage(playerid, "Bu eve daha fazla silah yerle�tiremezsiniz.");

			new ammo = Silah_Bilgi[playerid][sMermi][SilahSlotuBul[bweaponid]];

			PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[bweaponid]] = 0;
			Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[bweaponid]] = false;
			SetPlayerAmmo(playerid, bweaponid, 0);
			AC_RemovePlayerWeapon(playerid, bweaponid);

			new string[150];
			format(string, 150, "elindeki %s model silah� evin kasas�na koydu.", GetWeaponNameEx(bweaponid));
			PlayerAME(playerid, string);
			
			SendClientMessageEx(playerid, COLOR_GREY, "%s model silah�n�z� %d (SQL ID: %d) ID'li eve yerle�tirdiniz.", GetWeaponNameEx(bweaponid), h, HouseInfo[h][hID]);

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d', status = '1', house = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", ammo, HouseInfo[h][hID], bweaponid, PlayerInfo[playerid][pID]);
			mysql_query(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", tempsqlid, PlayerInfo[playerid][pID], HouseInfo[h][hID], "silah eve yerle�tirildi");
			mysql_tquery(dbHandle, queryx);

			Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %d ID'li %s model silahini %d ID'li eve yerlestirdi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], tempsqlid, GetWeaponNameEx(bweaponid), HouseInfo[h][hID]);
		}
		else if(vid != -1)
		{
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE) return SendErrorMessage(playerid, "Bisiklete silah yerle�tiremezsiniz.");
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carTrunkLock] || Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu i�lem i�in ara� kilitsiz ve bagaj� a��k olmal�d�r.");
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carEngineOn] || Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu i�lem i�in arac�n motoru a��k ve ara� kilitsiz olmal�.");

			new Float:tX, Float:tY, Float:tZ;
			GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !IsPlayerInRangeOfPoint(playerid, 2.5, tX, tY, tZ)) return SendErrorMessage(playerid, "Arac�n bagaj�na yak�n de�ilsin.");

			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Silah yerle�tirmek i�in motorda s�r�c� olmal�s�n.");

			if(Silah_SayiKontrol(2, VehicleInfo[vid][carID]) >= AracSilahLimiti(VehicleInfo[vid][carModel])) return SendErrorMessage(playerid, "Bu araca daha fazla silah yerle�tiremezsiniz.");

			new ammo = Silah_Bilgi[playerid][sMermi][SilahSlotuBul[bweaponid]];

			PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[bweaponid]] = 0;
			Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[bweaponid]] = false;
			SetPlayerAmmo(playerid, bweaponid, 0);
			AC_RemovePlayerWeapon(playerid, bweaponid);
	
			SendClientMessageEx(playerid, COLOR_GREY, "%s model silah�n�z� %d (SQL ID: %d) ID'li araca yerle�tirdiniz.", GetWeaponNameEx(bweaponid), vid, VehicleInfo[vid][carID]);

			PlayerAME(playerid, "arac�n�n i�erisine bir �ey b�rak�r.");

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d', status = '2', vehicle = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", ammo, VehicleInfo[vid][carID], bweaponid, PlayerInfo[playerid][pID]);
			mysql_query(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", tempsqlid, PlayerInfo[playerid][pID], VehicleInfo[vid][carID], "silah araca yerle�tirildi");
			mysql_tquery(dbHandle, queryx);

			Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %d ID'li %s model silahini %d ID'li araca yerlestirdi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], tempsqlid, GetWeaponNameEx(bweaponid), VehicleInfo[vid][carID]);
		}
		else SendErrorMessage(playerid, "Bu i�lemi yapamazs�n�z. Silahlar ev, ara� veya kasalara konabilir.");
	}
	else if(!strcmp(opsiyon, "envanter", true) || !strcmp(opsiyon, "env", true) || !strcmp(opsiyon, "al", true) || !strcmp(opsiyon, "cal", true))
	{
		new vid = Arac_Yakin(playerid, 5.0);
		new h = GetNearInsideHouse(playerid);

		if(!PlayerInfo[playerid][pOnDuty]) // Envanterden (C)alma
		{
			if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
			{
				if(HouseInfo[h][hOwner] <= 0 && PlayerInfo[playerid][pAdmin] < 4) return SendErrorMessage(playerid, "Sisteme ait evlerden silah alamazs�n�z.");
				if(HouseInfo[h][hLocked] == 1 && PlayerInfo[playerid][pID] != HouseInfo[h][hOwner]) return SendErrorMessage(playerid, "Kap�s� kilitli evlerden silah alamazs�n�z.");
			
				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE house = '%d' AND status = '1'", HouseInfo[h][hID]);
				new Cache:veri = mysql_query(dbHandle, queryx, true);
				new rows, string[1599];
				cache_get_row_count(rows);

				if(rows)
				{
					new xid, xweaponid, xammo, xstatus;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "id", xid);
						cache_get_value_int(j, "weaponid", xweaponid);
						cache_get_value_int(j, "ammo", xammo);
						cache_get_value_int(j, "status", xstatus);

						if(xstatus == 1) format(string, 1599, "%s%s (Ammo: %d - ID: %d)\n", string, GetWeaponNameEx(xweaponid), xammo, xid);
					}
					Dialog_Show(playerid, SilahEvEnvanter, DIALOG_STYLE_LIST, "Liberty City - Silah Sistemi", string, "Al", "Iptal"), cache_delete(veri);
				}
				else SendErrorMessage(playerid, "Ev silah envanteri bo�."), cache_delete(veri);
			}
			else if(vid != -1)
			{			
				if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE) return SendErrorMessage(playerid, "Bisikletlere silah yerle�tirilemedi�i i�in bu i�lemi yapamazs�n�z.");

				if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carTrunkLock] || Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bir arabadan silah almak i�in, o arac�n bagaj� ve kilidi a��k olmal�d�r.");
				if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carEngineOn] || Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked])
					return SendErrorMessage(playerid, "Bu i�lem i�in arac�n motoru a��k ve ara� kilitsiz olmal�.");

				new Float:tX, Float:tY, Float:tZ;
				GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
				if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !IsPlayerInRangeOfPoint(playerid, 2.2, tX, tY, tZ)) return SendErrorMessage(playerid, "Arac�n bagaj�na yak�n de�ilsin.");
				else if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Silah� ara�tan almak i�in motorda s�r�c� olmal�s�n.");

				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE vehicle = '%d' AND status = '2'", VehicleInfo[vid][carID]);
				new Cache:veri = mysql_query(dbHandle, queryx, true);
				new rows, string[1599];
				cache_get_row_count(rows);

				if(rows)
				{
					new xid, xweaponid, xammo, xstatus;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "id", xid);
						cache_get_value_int(j, "weaponid", xweaponid);
						cache_get_value_int(j, "ammo", xammo);
						cache_get_value_int(j, "status", xstatus);

						if(xstatus == 2)
							format(string, 1599, "%s%s (Mermi: %d - SQLID: %d)\n", string, GetWeaponNameEx(xweaponid), xammo, xid);
					}
					Dialog_Show(playerid, SilahAracEnvanter, DIALOG_STYLE_LIST, "Liberty City - Silah Sistemi", string, "Al", "Iptal"), cache_delete(veri);
				}
				else SendErrorMessage(playerid, "Ara� silah envanteri bo�."), cache_delete(veri);
			}
			else SendErrorMessage(playerid, "Bu i�lemi yapamazs�n�z.");

		}
		else if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE) // El koyma
		{
			if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
			{
				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE house = '%d'", HouseInfo[h][hID]);
				new Cache:veri = mysql_query(dbHandle, queryx, true);
				new rows, string[1599];
				cache_get_row_count(rows);

				if(rows)
				{
					new xid, xweaponid, xammo, xstatus;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "id", xid);
						cache_get_value_int(j, "weaponid", xweaponid);
						cache_get_value_int(j, "ammo", xammo);
						cache_get_value_int(j, "status", xstatus);

						if(xstatus == 1)
							format(string, 1599, "%s%s (Mermi: %d - SQLID: %d)\n", string, GetWeaponNameEx(xweaponid), xammo, xid);
					}
					Dialog_Show(playerid, SilahEvEnvanterPD, DIALOG_STYLE_LIST, "Liberty City - Silah Sistemi", string, "Al", "Iptal"), cache_delete(veri);
				}
				else SendErrorMessage(playerid, "Ev silah envanteri bo�."), cache_delete(veri);
			}
			else if(vid != -1)
			{
				new Float:tX, Float:tY, Float:tZ;
				GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
				if(!IsPlayerInRangeOfPoint(playerid, 2.2, tX, tY, tZ))
					return SendErrorMessage(playerid, "Araca yak�n de�ilsin.");

				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE vehicle = '%d'", VehicleInfo[vid][carID]);
				new Cache:veri = mysql_query(dbHandle, queryx, true);
				new rows, string[1599];
				cache_get_row_count(rows);

				if(rows)
				{
					new xid, xweaponid, xammo, xstatus;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "id", xid);
						cache_get_value_int(j, "weaponid", xweaponid);
						cache_get_value_int(j, "ammo", xammo);
						cache_get_value_int(j, "status", xstatus);

						if(xstatus == 2)
							format(string, 1599, "%s%s (Mermi: %d - SQLID: %d)\n", string, GetWeaponNameEx(xweaponid), xammo, xid);
					}
					Dialog_Show(playerid, SilahAracEnvanterPD, DIALOG_STYLE_LIST, "Liberty City - Silah Sistemi", string, "Al", "Iptal"), cache_delete(veri);
				}
				else SendErrorMessage(playerid, "Ara� silah envanteri bo�."), cache_delete(veri);
			}
			else SendErrorMessage(playerid, "Bu i�lemi yapamazs�n�z.");
		}
		else SendErrorMessage(playerid, "Bu i�lemi yapamazs�n�z.");
	}
	else if(!strcmp(opsiyon, "ver", true))
	{
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Olu�um i�ba��nda olan kullan�c�lar bu sistemden yararlanamaz.");
		new vweaponid = AC_GetPlayerWeapon(playerid);
		if(!vweaponid) return SendErrorMessage(playerid, "Elinizde silah yokken bu i�lemi yapamazs�n�z.");
		
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0' AND weaponid = '%d'", PlayerInfo[playerid][pID], vweaponid);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazs�n�z."),  PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new twidc, statuc, lisansc;

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", twidc);
				cache_get_value_int(j, "lisans", lisansc);
				cache_get_value_int(j, "status", statuc);
				cache_get_value_int(j, "id", PlayerInfo[playerid][SilahVerDialogID]);

				if(twidc == vweaponid && statuc == 0 && lisansc == 1)break;
			}
			cache_delete(veri);
		}

		if(lisansc == 0) Dialog_Show(playerid, SilahVer, DIALOG_STYLE_INPUT, "Liberty City - Silah Sistemi", "%s silah�n� vermek istedi�iniz ki�inin ad�n� ya da ID bilgisini girin:", "Ver", "Iptal", GetWeaponNameEx(vweaponid));
		else SendErrorMessage(playerid, "Bu silah� veremezsiniz.");
	}
	else if(!strcmp(opsiyon, "sistemesat", true))
	{
		if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2260.4148, 63.1703, 26.4844) && !IsPlayerInRangeOfPoint(playerid, 5.0, 1248.9823, 365.7434, 19.5547)) return SendErrorMessage(playerid, "Silah satma noktas�nda de�ilsiniz.");
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Olu�um i�ba��nda olan kullan�c�lar bu sistemden yararlanamaz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazs�n�z."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new weaponid, ammo, fiyat, string[1024];
		format(string, sizeof(string), "Silah\tMermi Say�s�\tFiyat\n");

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);

				switch(weaponid)
				{
					case 22: fiyat = 6000;
					case 23: fiyat = 8000;
					case 24: fiyat = 12000;
					case 25: fiyat = 10000;
					case 28: fiyat = 13000;
					case 30: fiyat = 17000;
					case 32: fiyat = 13000;
					default: fiyat = 0;
				}

				format(string, sizeof(string), "%s%s\t%d adet\t$%d\n", string, GetWeaponNameEx(weaponid), ammo, fiyat);
			}
			Dialog_Show(playerid, SilahSistemeSat, DIALOG_STYLE_TABLIST_HEADERS, "Silah Sisteme Sat", string, "Sat", "�ptal");
			cache_delete(veri);
		}
	}
	/*
	else if(!strcmp(opsiyon, "siparis", true))
	{
		if(SunucuBilgi[SilahSatisDurum]) return SendErrorMessage(playerid, "IFM taraf�ndan silah sat��lar� pasife �ekilmi�tir.");
	    new olusum = PlayerInfo[playerid][pFaction], string[256], aktor = Get_Nearest_Weapon_Actor(playerid);

	    if(olusum < 1) return SendErrorMessage(playerid, "Bu komutu sadece birlik �yeleri kullanabilir.");
		if(aktor == -1) return SendErrorMessage(playerid, "Silah sat��� yapan bir akt�re yak�n olmal�s�n.");
	    if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "�u an bu komutu kullanamazs�n�z.");
		if(!Olusum[olusum][oSilahIzin]) return SendErrorMessage(playerid, "Bu birli�in silah sat�n alma izni bulunmuyor.");
		if(PlayerInfo[playerid][pOlusumRutbe] > 3) return SendErrorMessage(playerid, "Bu opsiyondan sadece birlikteki ilk 3 r�tbe faydalanabilir, di�er �yeler faydalanamazlar.");
		if(GetFactionWeaponStock(olusum) < 1) return SendErrorMessage(playerid, "Bulundu�unuz birlik IFM taraf�ndan tan�mlanan silah hakk�n� doldurmu�.");

        if(AktorBilgi[aktor][aktorTip] != AKTOR_TIP_SILAH) return SendErrorMessage(playerid, "Bu akt�r silah sat��� yapm�yor.");

	    if(Siparis_Kontrol(playerid)) return SendErrorMessage(playerid, "Zaten bir silah sipari� etmi�siniz. /silah siparisdurum ile durumunu ��renebilirsiniz.");

        if(olusum > 0 && IllegalOlusumUyesi(playerid) && Olusum[olusum][oDurum] > 0)
	    {
	        for(new i; i < 2; i++)
	        {
	            format(string, sizeof(string), "%s%s\t%d adet\t$%d\t%d Payday\n", string, GetWeaponNameEx(silahlar[i]), mermiler[i], lvl3fiyatlar[i], lvl3sureler[i]);
			    Dialog_Show(playerid, SilahSiparisi, DIALOG_STYLE_TABLIST_HEADERS, "Silah Sipari� Sistemi", "Silah ad�\tMermi miktar�\tFiyat\tTeslim s�resi(PayDay)\n%s", "Sipari�", "Geri", string);
	        }
	    }
	    else SendErrorMessage(playerid, "Bu sistemden sadece tan�t�m onayl� illegal birlikler yararlanabilir.");		
	}
	else if(!strcmp(opsiyon, "siparisdurum", true))
	{
	    new olusum = PlayerInfo[playerid][pFaction], string[3500], siparisdurum[128];

	    if(olusum < 1) return SendErrorMessage(playerid, "Bu komutu sadece birlik �yeleri kullanabilir.");
	    if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "�u an bu komutu kullanamazs�n�z.");
	    if(!Siparis_Durum(playerid)) return SendErrorMessage(playerid, "Herhangi bir silah sipari�iniz yok.");

        if(olusum > 0 && IllegalOlusumUyesi(playerid) && Olusum[olusum][oDurum] > 0)
	    {
	        foreach(new si : Siparisler)
	        {
				if(SilahSiparisi[si][siparisSahip] == PlayerInfo[playerid][pID] && SilahSiparisi[si][siparisDurum] == 0)

                switch(SilahSiparisi[si][siparisDurum])
				{
					case 0: siparisdurum = sprintf("%d PayDay", SilahSiparisi[si][siparisKalan]);
					case 1: siparisdurum = sprintf("Sipari� Haz�r");
					case 2: siparisdurum = sprintf("Teslim Al�nm��");
				}

	            format(string, sizeof(string), "%s%s\t%d adet\t$%d (�denmi�)\t%s\n", string, GetWeaponNameEx(SilahSiparisi[si][siparisSilah]), SilahSiparisi[si][siparisMermi], SilahSiparisi[si][siparisFiyat], siparisdurum);
			    Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "Sipari� Durumu", "Silah ad�\tMermi miktar�\tFiyat\tSipari� Durumu\n%s", ">>", "Kapat", string);
				break;
	        }
			SunucuMesaji(playerid, "Sokaklar aras�ndan bir f�s�lt� kula��na geldi ve sipari�inin durumunu ��rendin.");
	    }
	    else SendErrorMessage(playerid, "Bu sistemden sadece tan�t�m onayl� illegal birlikler yararlanabilir.");		
	}	
	else if(!strcmp(opsiyon, "teslimal", true))
	{
	    new olusum = PlayerInfo[playerid][pFaction], aktor = Get_Nearest_Weapon_Actor(playerid);

	    if(olusum < 1) return SendErrorMessage(playerid, "Bu komutu sadece birlik �yeleri kullanabilir.");
		if(aktor == -1) return SendErrorMessage(playerid, "Silah sat��� yapan bir akt�re yak�n olmal�s�n.");
	    if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "�u an bu komutu kullanamazs�n�z.");

        if(AktorBilgi[aktor][aktorTip] != AKTOR_TIP_SILAH) return SendErrorMessage(playerid, "Bu akt�r silah sat��� yapm�yor.");

	    if(!Siparis_Durum(playerid)) return SendErrorMessage(playerid, "Teslim edilmeye haz�r bir sipari�iniz yok.");

        if(olusum > 0 && IllegalOlusumUyesi(playerid))
	    {
	        foreach(new sipo : Siparisler)
	        {
	            if(SilahSiparisi[sipo][siparisSahip] == PlayerInfo[playerid][pID] && SilahSiparisi[sipo][siparisDurum] == 1)
				{
                    mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
                    new Cache:veri = mysql_query(dbHandle, queryx, true);
                    new rows;
                    cache_get_row_count(rows);

                    if(rows)
                    {
                        new xweaponid;

                        for(new j; j < rows; j++)
                        {
                            cache_get_value_int(j, "weaponid", xweaponid);
                            if(SilahSiparisi[sipo][siparisSilah] == xweaponid)break;
                        }
                    
					    if(SilahSiparisi[sipo][siparisSilah] == xweaponid) return SendClientMessageEx(playerid, COLOR_GREY, "�zerinizde ayn� silahtan bulunuyor, bu sebepten �t�r� silah alamazs�n�z."), cache_delete(veri);
                        if(SilahSlotBul(SilahSiparisi[sipo][siparisSilah]) == SilahSlotBul(xweaponid)) return SendClientMessageEx(playerid, COLOR_GREY, "�zerinizde ayn� tip silahtan bulunuyor, bu sebepten �t�r� silah� alamazs�n�z."), cache_delete(veri);            
                   }

					Silah_Ver(playerid, SilahSiparisi[sipo][siparisSilah], SilahSiparisi[sipo][siparisMermi]);
					SilahSiparisi[sipo][siparisDurum] = 2;	
				}
				break;
	        }
	    }
	    else SendErrorMessage(playerid, "Bu sistemden sadece tan�t�m onayl� illegal birlikler yararlanabilir.");		
	}*/
	else SendErrorMessage(playerid, "Hatal� parametre giri�i tespit edildi.");
	return 1;
}

alias:asilah("aweapon");
CMD:asilah(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 3) return SendErrorMessage(playerid, "Bu komut sadece Game Admin 3 ve �st� yetkililer taraf�ndan kullan�labilir.");             
	new option[20], id, weaponid, ammo;
	if(sscanf(params, "S[20]D(-1)D(-1)D(-1)", option, id, weaponid, ammo))
	{
		SendClientMessageEx(playerid, COLOR_YELLOW, "[GA1+] {FFFFFF}sil | temizle | kontrol | id | sifirla");
		SendClientMessageEx(playerid, COLOR_YELLOW, "[GA5+] {FFFFFF}ver | duzenle");
		SendClientMessageEx(playerid, COLOR_GREEN, "[!] {AFAFAF}/asilah [Se�enek Ad�] �eklinde komutu kullanabilir, kalan bo�luklar� doldurarak i�leminizi ger�ekle�tirebilirsiniz.");
		return 1;
	}
		
	if(!strcmp(option, "ver", true))
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return SendErrorMessage(playerid, "Bu komut sadece Game Admin 5 ve �st� yetkililer taraf�ndan kullan�labilir.");      
		if(id < 0) return SendSyntaxMessage(playerid, "/asilah ver (Oyuncu ID) (Silah ID) (Mermi Miktar)");
		
		if(!IsPlayerConnected(id) || !pTemp[id][pLogged]) return SendSyntaxMessage(playerid, "Ge�ersiz ID giri�i tespit edildi.");
		if(weaponid <= 0) return SendSyntaxMessage(playerid, "/asilah ver %d (Silah ID) (Mermi Miktar)", id);
			
		if(ammo < 1) return SendErrorMessage(playerid, "1'den az mermili bir silah veremezsin.");
		if(weaponid == 24 && ammo > 50) return SendErrorMessage(playerid, "Desert Eagle silah� maksimum 50 mermi alabilir.");
		if(weaponid == 30 && ammo > 90)return SendErrorMessage(playerid, "AK-47 silah� maksimum 90 mermi alabilir.");
		if(weaponid == 31 && ammo > 150) return SendErrorMessage(playerid, "M4 silah� maksimum 150 mermi alabilir.");
		if(weaponid == 25 && ammo > 35) return SendErrorMessage(playerid, "Shotgun silah� maksimum 35 mermi alabilir.");
		if(weaponid == 22 && ammo > 68) return SendErrorMessage(playerid, "Pistol silah� maksimum 68 mermi alabilir.");
		if(weaponid == 23 && ammo > 68) return SendErrorMessage(playerid, "Silenced Pistol silah� maksimum 68 mermi alabilir.");
		if(weaponid == 32 && ammo > 150) return SendErrorMessage(playerid, "Tec-9 silah� maksimum 150 mermi alabilir.");
		if(weaponid == 28 && ammo > 150) return SendErrorMessage(playerid, "Uzi silah� maksimum 150 mermi alabilir.");
		if(weaponid == 33 && ammo > 30) return SendErrorMessage(playerid, "County Rifle silah� maksimum 30 mermi alabilir.");
		if(weaponid == 34 && ammo > 30) return SendErrorMessage(playerid, "Sniper silah� maksimum 30 mermi alabilir.");
		if(weaponid == 26 && ammo > 40) return SendErrorMessage(playerid, "Sawnoff Shotgun silah� maksimum 40 mermi alabilir.");

		Silah_Ver(id, weaponid, ammo, playerid, PlayerInfo[playerid][pAccID]);
		// mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[id][pID]);
		// new Cache:veri = mysql_query(dbHandle, queryx, true);
		// new rows;
		// cache_get_row_count(rows);

		// if(!rows)
		// {
		// 	mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin) VALUES ('%d', '%d', '%d', '%d', '%d')", PlayerInfo[id][pID], weaponid, ammo, 0, PlayerInfo[playerid][pID]);
		// 	mysql_query(dbHandle, queryx);
		// 	SendClientMessageEx(playerid, COLOR_WHITE, "%s adl� oyuncuya {80F5B1}%s (Mermi: %d){FFFFFF} verdin.", GetNameEx(id), SilahAdi(weaponid), ammo);
		// 	SendClientMessageEx(id, COLOR_WHITE, "%s adl� yetkili sana {80F5B1}%s (Mermi: %d){FFFFFF} verdi.", GetNameEx(id), SilahAdi(weaponid), ammo);
		// 	Log_Kaydet("adminLog.txt", "[/asilah ver] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli oyuncuya %s (Mermi: %d) verdi. [Tarih: %s]", PlayerInfo[playerid][pUsername], PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pAccID], SilahAdi(weaponid), ammo, ReturnDate());
		// 	PlayerInfo[id][pSilahSistemi] = 1;
		// 	AC_GivePlayerWeapon(id, weaponid, ammo);
		// }
		// else
		// {
		// 	new xweaponid;

		// 	for(new j; j < rows; j++)
		// 	{
		// 		cache_get_value_int(j, "weaponid", xweaponid);
		// 		if(weaponid == xweaponid)break;
		// 	}

		// 	if(weaponid == xweaponid) return SendErrorMessage(playerid, "Kar��daki kullan�c�n�n �zerinde ayn� silahtan var, bunu yapamazs�n�z."), cache_delete(veri);
		// 	if(SilahSlotBul(weaponid) == SilahSlotBul(xweaponid)) return SendErrorMessage(playerid, "Kar��daki kullan�c�n�n �zerinde ayn� tip silahtan var, bunu yapamazs�n�z."), cache_delete(veri);

		// 	mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin) VALUES ('%d', '%d', '%d', '%d', '%d')", PlayerInfo[id][pID], weaponid, ammo, 0, PlayerInfo[playerid][pID]);
		// 	mysql_query(dbHandle, queryx);

		// 	PlayerInfo[id][pSilahSistemi] = 1;
		// 	AC_GivePlayerWeapon(id, weaponid, ammo);
		// 	SendClientMessageEx(playerid, COLOR_WHITE, "%s adl� oyuncuya {80F5B1}%s (Mermi: %d){FFFFFF} verdin.", GetNameEx(id), SilahAdi(weaponid), ammo);
		// 	SendClientMessageEx(id, COLOR_WHITE, "%s adl� yetkili sana {80F5B1}%s (Mermi: %d){FFFFFF} verdi.", GetNameEx(id), SilahAdi(weaponid), ammo);
		// 	Log_Kaydet("adminLog.txt", "[/asilah ver] %s (C_ID: %d | A_ID: %d), %s (C_ID: %d | A_ID: %d) adli oyuncuya %s (Mermi: %d) verdi. [Tarih: %s]", PlayerInfo[playerid][pUsername], PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetNameEx(id), PlayerInfo[id][pID], PlayerInfo[id][pAccID], SilahAdi(weaponid), ammo, ReturnDate());
		// }
		// cache_delete(veri);
	}
	else if(!strcmp(option, "temizle", true))
	{
		if(id < 0) return SendSyntaxMessage(playerid, "/asilah temizle (Oyuncu ID)");
		if(IsPlayerConnected(id) && pTemp[id][pLogged]) SilahElkoyFonksiyon(playerid, id, 2);
		else SendErrorMessage(playerid, "Hatal� ID girdiniz.");
	}
	else if(!strcmp(option, "sil", true))
	{
		if(id <= 0) return SendSyntaxMessage(playerid, "/asilah sil (Silah SQLID)");
			
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE id = '%d'", id);
		new Cache:veri = mysql_query(dbHandle, queryx, true);

		new rows;
		cache_get_row_count(rows);

		if(!rows) SendErrorMessage(playerid, "%d nolu silah veritaban�nda bulunamad�.", id);
		else
		{
			new status, owner, weapontype;
			cache_get_value_name_int(0, "status", status);
			cache_get_value_name_int(0, "owner", owner);
			cache_get_value_name_int(0, "weaponid", weapontype);

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '5' WHERE id = '%d'", id);
			mysql_query(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", id, PlayerInfo[playerid][pID], -1, "silaha el koyuldu");
			mysql_tquery(dbHandle, queryx);
			
			SendServerMessage(playerid, "%d nolu silaha y�netici m�dahalesi uygulad�n�z.", id);
			Log_Kaydet("adminLog.txt", "[/asilah sil] %s, %d ID'li silaha yonetici mudahalesi uyguladi. [Tarih: %s]", PlayerInfo[playerid][pUsername], id, ReturnDate());

			if(status == 0) 
			{
				foreach(new i : Player) if(pTemp[i][pLogged] && PlayerInfo[i][pID] == owner)
				 {
					AC_ResetPlayerWeapons(i);
					SetTimerEx("OnPlayerSetData", 1000, false, "d", i);
					SendErrorMessage(i, "%s silah�n %s adl� yetkili taraf�ndan silindi.", GetWeaponNameEx(weapontype), PlayerInfo[playerid][pUsername]);
					SendAdmMessage("AdmCmd: %s %s isimli oyuncunun %s(%d) silah�n� sildi.", PlayerInfo[playerid][pUsername], GetNameEx(i), GetWeaponNameEx(weapontype), id);
					break;
				}
			}
		}
		cache_delete(veri);
	}
	else if(!strcmp(option, "duzenle", true))
	{
		if(PlayerInfo[playerid][pAdmin] < 3) return SendErrorMessage(playerid, "Bu komut sadece Game Admin 5 ve �st� yetkililer taraf�ndan kullan�labilir.");  
		if(id <= 0)return SendSyntaxMessage(playerid, "/asilah duzenle (Silah SQLID)");
			
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE id = '%d'", id);
		new Cache:veri = mysql_query(dbHandle, queryx, true);

		new rows;
		cache_get_row_count(rows);

		if(!rows) SendErrorMessage(playerid, "%d nolu silah veritaban�nda bulunamad�.", id);
		else
		{
			new ownerid, xweaponid, xammo, status, omur;
			cache_get_value_int(0, "owner", ownerid);
			cache_get_value_int(0, "weaponid", xweaponid);
			cache_get_value_int(0, "ammo", xammo);
			cache_get_value_int(0, "status", status);
			cache_get_value_int(0, "omur", omur);

			SetPVarInt(playerid, "aSilahSQLID", id);
			SetPVarInt(playerid, "aSilahSahip", ownerid);
			SetPVarInt(playerid, "aSilahID", xweaponid);
			SetPVarInt(playerid, "aSilahMermi", xammo);
			SetPVarInt(playerid, "aSilahDurum", status);
			SetPVarInt(playerid, "aSilahOmur", omur);

			Dialog_Show(playerid, aSilahDuzenle, DIALOG_STYLE_LIST, "Silah D�zenleme Men�s�", "Mermi Say�s�n� D�zenle\nSahibi D�zenle\nDurumu D�zenle\nSilah �mr�n� D�zenle", ">>", "<<");
		}
		cache_delete(veri);
	}
	else if(!strcmp(option, "kontrol", true))
	{
		if(id < 0) return SendSyntaxMessage(playerid, "/asilah kontrol (Oyuncu ID) || //osilahkontrol (Karakter ad�)");
			
		if(IsPlayerConnected(id) && pTemp[id][pLogged])
			SilahKontrolEt(playerid, id, 0);
	}
	else if(!strcmp(option, "id", true))
	{
		if(id <= 0) return SendSyntaxMessage(playerid, "/asilah id (Silah SQLID)");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE id = '%d'", id);
		new Cache:veri = mysql_query(dbHandle, queryx, true);

		new rows;
		cache_get_row_count(rows);

		if(!rows) SendErrorMessage(playerid, "%d nolu silah veritaban�nda bulunamad�.", id);
		else
		{
			new ownerid, mweaponid, mammo, status, house, vehicle, biz, olusumid, idstr[6], statusstr[24], bm, sistemdenalan, admin;

			cache_get_value_int(0, "owner", ownerid);
			cache_get_value_int(0, "weaponid", mweaponid);
			cache_get_value_int(0, "ammo", mammo);
			cache_get_value_int(0, "status", status);
			cache_get_value_int(0, "house", house);
			cache_get_value_int(0, "vehicle", vehicle);
			cache_get_value_int(0, "biz", biz);
			cache_get_value_int(0, "faction_id", olusumid);
			cache_get_value_int(0, "bm", bm);
			cache_get_value_int(0, "sistemdenalan", sistemdenalan);
			cache_get_value_int(0, "admin", admin);

			if(id < 1000) format(idstr, 6, "0%d", id);
			else if(id < 100) format(idstr, 6, "00%d", id);
			else if(id < 10) format(idstr, 6, "000%d", id);

			switch(status)
			{
				case 0: format(statusstr, 24, "�zerinde");
				case 1: format(statusstr, 24, "Evde (%d)", house);
				case 2: format(statusstr, 24, "Ara�ta (%d)", vehicle);
				case 3: format(statusstr, 24, "��letmede (%d)", biz);
				case 4: format(statusstr, 24, "Polis Zimmeti");
				case 5: format(statusstr, 24, "Y�netici M�dahalesi");
				case 6: format(statusstr, 24, "Geri �deme Yap�lm��");
				case 7: format(statusstr, 24, "Birlik kasas�nda (%d)", olusumid);
			}

			SendClientMessageEx(playerid, COLOR_GREY, "Sistemden Alan: %s, Blackmarket ID: %d, Olu�turan Admin: %s", GetNameEx(sistemdenalan), bm, GetNameEx(admin));

			SendClientMessageEx(playerid, COLOR_GREY, "ID[%s] - Sahip[%s] - Silah[%s] - Mermi[%d] - Durum[%s] - Ev[%d] - Ara�[%d]", idstr, GetNameEx(ownerid), GetWeaponNameEx(mweaponid), mammo, statusstr, house, vehicle);
		}
		cache_delete(veri);
	}
	else SendSyntaxMessage(playerid, "/asilah <ver/sil/temizle/duzenle/kontrol/id/sifirla> || /osilahkontrol (Karakter ad�)");
	return 1;
}
