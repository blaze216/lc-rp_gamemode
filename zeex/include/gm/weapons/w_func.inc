Dialog:SilahSistemeSat(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2260.4148, 63.1703, 26.4844) && !IsPlayerInRangeOfPoint(playerid, 5.0, 1248.9823, 365.7434, 19.5547)) return SendErrorMessage(playerid, "Silah satma noktasýnda deðilsiniz.");
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new xid, weaponid, ammo, fiyat, count = -1;

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", xid);
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
				count++;
				if(listitem == count)break;
			}

			if(ammo != 0) return SendErrorMessage(playerid, "Þarjörü dolu olan bir silahý ya da yakýn dövüþ silahýný sisteme satamazsýn."), cache_delete(veri);
			if(fiyat < 0) return SendErrorMessage(playerid, "Negatif deðer oluþturuldu, gerekli ekran görüntüleriyle Bug Bildirimi oluþturun."), cache_delete(veri);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e%d', NOW())", xid, PlayerInfo[playerid][pID], -1, "silah sisteme satýldý ", fiyat);
			mysql_tquery(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '6' WHERE id = '%d'", xid);
			mysql_query(dbHandle, queryx);

			GiveCash(playerid, fiyat);
			SendClientMessageEx(playerid, COLOUR_TOMATO, "Silah Satýcýsý: {AFAFAF}Ticaretten memnun kaldým, tekrar bir þeyler satacak olursan buralardayým.");
			SendServerMessage(playerid, "Silah tüccarýna %s model silahýný verdin ve karþýlýðýnda sana $%d verdi.", GetWeaponNameEx(weaponid), fiyat);
			Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %s model (%d SQL ID) silahini sisteme satti ve $%d kazandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], GetWeaponNameEx(weaponid), xid, fiyat);
			cache_delete(veri);
		}
	}
	return 1;
}

Dialog:MermisizSilahlar(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;

	if(isnull(inputtext)) return SendErrorMessage(playerid, "Hatalý onay kodu giriþi, iþlem baþarýsýz.");

	if(!strcmp("EVET", inputtext, true))
	{
		if(PlayerInfo[playerid][pOnDuty])
			return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		if(GetTickCount() - PlayerInfo[playerid][SilahTick] > 10000)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND ammo = '0' AND status = '0'", PlayerInfo[playerid][pID]);
			new Cache:veri = mysql_query(dbHandle, queryx, true);
			new rows;
			cache_get_row_count(rows);

			if(!rows)
			{
				PlayerInfo[playerid][pSilahSistemi] = 0;
				SendErrorMessage(playerid, "Üzerinize kayýtlý mermisiz silah bulunamadý. (%s)", GetFullDate());
			}
			else
			{
				new id, weaponid, idstr[6], string[512];

				for(new j; j < rows; j++)
				{
					cache_get_value_int(j, "id", id);
					cache_get_value_int(j, "weaponid", weaponid);
					format(idstr, 6, "%d", id);

					if(id < 1000) format(idstr, 6, "0%d", id);
					else if(id < 100) format(idstr, 6, "00%d", id);
					else if(id < 10) format(idstr, 6, "000%d", id);

					format(string, sizeof(string), "%s%d) %s(%s)", string, j+1, GetWeaponNameEx(weaponid), idstr);
				}
				Dialog_Show(playerid, MermisizSilahYerlestir, DIALOG_STYLE_LIST, "Alternatif Silah Yerleþtirme", string, "Býrak", "Ýptal");
			}
			cache_delete(veri);
			PlayerInfo[playerid][SilahTick] = GetTickCount();
		}
		else SendErrorMessage(playerid, "Bu komutu bu kadar sýk kullanmayýn.");
	}
	else SendErrorMessage(playerid, "Hatalý onay kodu giriþi, iþlem baþarýsýz.");
	return 1;
}

Dialog:MermisizSilahYerlestir(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;

	mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND ammo = '0' AND status = '0'", PlayerInfo[playerid][pID]);
	new Cache:veri = mysql_query(dbHandle, queryx, true);
	new rows, islem = 0;
	cache_get_row_count(rows);

	new id, weaponid;
	if(!rows)
	{
		PlayerInfo[playerid][pSilahSistemi] = 0;
		SendErrorMessage(playerid, "Üzerinize kayýtlý mermisiz silah bulunamadý. (%s)", GetFullDate());
	}
	else
	{
		for(new j; j < rows; j++)
		{
			cache_get_value_int(j, "id", id);
			cache_get_value_int(j, "weaponid", weaponid);
			if(listitem == j) islem = 1; break;
		}
	}
	cache_delete(veri);
	if(islem == 1)
	{
		new vid = Arac_Yakin(playerid, 5.0);
		new h = GetNearInsideHouse(playerid);

		if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
		{
			if(Silah_SayiKontrol(1, h) >= MAX_WEAPON_HOUSE) return SendErrorMessage(playerid, "Bu eve daha fazla silah yerleþtiremezsiniz.");

			SendClientMessageEx(playerid, COLOR_GREY, "%s model silahýnýzý %d (SQL ID: %d) ID'li eve yerleþtirdiniz.", GetWeaponNameEx(weaponid), h, HouseInfo[h][hID]);
			Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %d ID'li %s model silahini %d ID'li eve yerlestirdi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], id, GetWeaponNameEx(weaponid), HouseInfo[h][hID]);

			new string[150];
			format(string, 150, "elindeki %s model silahý evin kasasýna koydu.", GetWeaponNameEx(weaponid));
			PlayerAME(playerid, string);

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '1', house = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", HouseInfo[h][hID], weaponid, PlayerInfo[playerid][pID]);
			mysql_query(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", id, PlayerInfo[playerid][pID], HouseInfo[h][hID], "silah eve yerleþtirildi");
			mysql_tquery(dbHandle, queryx);
		}
		else if(vid != -1)
		{
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE) return SendErrorMessage(playerid, "Bisiklete silah yerleþtiremezsiniz.");

			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carTrunkLock] || Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu iþlem için araç kilitsiz ve bagajý açýk olmalýdýr.");

			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carEngineOn] || Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu iþlem için aracýn motoru açýk ve araç kilitsiz olmalý.");

			new Float:tX, Float:tY, Float:tZ;
			GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !IsPlayerInRangeOfPoint(playerid, 2.5, tX, tY, tZ)) return SendErrorMessage(playerid, "Aracýn bagajýna yakýn deðilsin.");
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Silah yerleþtirmek için motorda sürücü olmalýsýn.");
			if(Silah_SayiKontrol(2, VehicleInfo[vid][carID]) >= AracSilahLimiti(VehicleInfo[vid][carModel])) return SendErrorMessage(playerid, "Bu araca daha fazla silah yerleþtiremezsiniz.");

			SendServerMessage(playerid, "%s model silahýný baþarýyla araca (ID: %d / SQLID: %d) yerleþtirdin. (%s)", GetWeaponNameEx(weaponid), vid, VehicleInfo[vid][carID], GetFullDate());
			Log_Kaydet("arac.txt", "%s: %s model silahýný baþarýyla araca (ID:%d/SQLID:%d) yerleþtirdi. (%s)", GetNameEx(playerid), GetWeaponNameEx(weaponid), VehicleInfo[vid][carID], VehicleInfo[vid][carID], GetFullDate());

			PlayerAME(playerid, "aracýnýn içerisine bir þey býrakýr.");

			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '2', vehicle = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", VehicleInfo[vid][carID], weaponid, PlayerInfo[playerid][pID]);
			mysql_query(dbHandle, queryx);

			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", id, PlayerInfo[playerid][pID], VehicleInfo[vid][carID], "silah araca yerleþtirildi");
			mysql_tquery(dbHandle, queryx);
		}
		else SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz.");
	}
	return 1;
}

Dialog:SilahListeGoruntule(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;

	if(isnull(inputtext)) return SendErrorMessage(playerid, "Hatalý onay kodu giriþi, iþlem baþarýsýz.");

	if(!strcmp("EVET", inputtext, true))
	{
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);

		if(!rows)
		{
			PlayerInfo[playerid][pSilahSistemi] = 0;
			SendErrorMessage(playerid, "%s adlý karaktere kayýtlý silah bulunamadý. (%s)", GetNameEx(playerid), GetFullDate());
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_SERVER2, "_____________________[%s (%s) | %s]_____________________", GetNameEx(playerid), PlayerInfo[playerid][pAccname], GetFullDate());

			new id, weaponid, ammo, status, house, vehicle, olusumid, biz, idstr[6], statusstr[24], omur;

			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", id);
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				cache_get_value_int(j, "status", status);
				cache_get_value_int(j, "house", house);
				cache_get_value_int(j, "vehicle", vehicle);
				cache_get_value_int(j, "faction_id", olusumid);
				cache_get_value_int(j, "biz", biz);
				cache_get_value_int(j, "omur", omur);
				format(idstr, 6, "%d", id);

				if(id < 10000)
					format(idstr, 6, "0%d", id);

				if(id < 1000)
					format(idstr, 6, "00%d", id);

				if(id < 100)
					format(idstr, 6, "000%d", id);

				if(id < 10)
					format(idstr, 6, "0000%d", id);

				switch(status)
				{
					case 0: format(statusstr, 24, "Üzerinizde");
					case 1: format(statusstr, 24, "Evde (%d)", house);
					case 2: format(statusstr, 24, "Araçta (%d)", vehicle);
					case 3: format(statusstr, 24, "Ýþletmede (%d)", biz);
					case 4: format(statusstr, 24, "Polis Zimmeti");
					case 5: format(statusstr, 24, "Yönetici Müdahalesi");
					case 6: format(statusstr, 24, "Geri Ödeme Yapýldý");
					case 7: format(statusstr, 24, "Oluþum kasasý (%d)", olusumid);
					case 8: format(statusstr, 24, "Vergili Evde Silindi (%d)", house);
					case 9: format(statusstr, 24, "Vergili Araçta Silindi (%d)", vehicle);
					case 10: format(statusstr, 24, "Bozuldu");
				}

				// SendClientMessageEx(playerid, COLOR_GREY, "Slot[%d] - ID[%s] - Silah[%s] - Mermi[%d] - Ömür[%d] - Durum[%s]", j+1, idstr, GetWeaponNameEx(weaponid), ammo, omur, statusstr);
				SendClientMessageEx(playerid, COLOR_GREY, "Silah: %s | Mermi: %d | Seri Numarasý: %d | Durum: %s | Ömür: %d", GetWeaponNameEx(weaponid), ammo, id, statusstr, omur);
			}
		}
		cache_delete(veri);
		PlayerInfo[playerid][SilahTick] = GetTickCount();
	}
	else SendErrorMessage(playerid, "Hatalý onay kodu giriþi, iþlem baþarýsýz.");
	return 1;
}

Dialog:SilahAracEnvanterPD(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vid = Arac_Yakin(playerid, 5.0);

		if(vid != -1)
		{
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE) return SendErrorMessage(playerid, "Bisikletlere silah yerleþtirilemediði için bu iþlemi yapamazsýnýz.");

			new Float:tX, Float:tY, Float:tZ;
			GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !IsPlayerInRangeOfPoint(playerid, 2.2, tX, tY, tZ)) return SendErrorMessage(playerid, "Aracýn bagajýna yakýn deðilsin.");

			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE vehicle = '%d'", VehicleInfo[vid][carID]);
			new Cache:veri = mysql_query(dbHandle, queryx, true);
			new rows;
			cache_get_row_count(rows);

			if(rows)
			{
				new xid, weaponid, xammo, xstatus, count, idstr[6];

				count = -1;
				for(new j; j < rows; j++)
				{
					cache_get_value_int(j, "id", xid);
					cache_get_value_int(j, "weaponid", weaponid);
					cache_get_value_int(j, "ammo", xammo);
					cache_get_value_int(j, "status", xstatus);
					format(idstr, 6, "%d", xid);
					if(xid < 1000) format(idstr, 6, "0%d", xid);
					if(xid < 100) format(idstr, 6, "00%d", xid);
					if(xid < 10) format(idstr, 6, "000%d", xid);

					if(xstatus != 2)continue;
					count++;
					if(listitem == count)break;
				}
				mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[playerid][pID], VehicleInfo[vid][carID], "silaha araçtan el koyuldu");
				mysql_tquery(dbHandle, queryx);

				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '4' WHERE id = '%d'", xid);
				mysql_query(dbHandle, queryx);

				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET vehicle = '-1' WHERE id = '%d'", xid);
				mysql_query(dbHandle, queryx);
			}
			cache_delete(veri);
		}
	}
	return 1;
}

Dialog:SilahAracEnvanter(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vid = Arac_Yakin(playerid, 5.0);

		if(vid != -1)
		{
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE) return SendErrorMessage(playerid, "Bisikletlere silah yerleþtirilemediði için bu iþlemi yapamazsýnýz.");
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carTrunkLock] || Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu iþlem için araç kilitsiz ve bagajý açýk olmalýdýr.");
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && !VehicleInfo[vid][carEngineOn] || Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && VehicleInfo[vid][carLocked]) return SendErrorMessage(playerid, "Bu iþlem için aracýn motoru açýk ve araç kilitsiz olmalý.");

			new Float:tX, Float:tY, Float:tZ;
			GetPosBehindVehicle(vid, tX, tY, tZ, 0.0);
			if(Arac_Model(VehicleInfo[vid][carModel]) != VEHICLE_TYPE_MBIKE && !IsPlayerInRangeOfPoint(playerid, 2.2, tX, tY, tZ)) return SendErrorMessage(playerid, "Aracýn bagajýna yakýn deðilsin.");
			if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_MBIKE && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Silahý araçtan almak için motorda sürücü olmalýsýn.");

			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE vehicle = '%d'", VehicleInfo[vid][carID]);
			new Cache:veri = mysql_query(dbHandle, queryx, true);
			new rows;
			cache_get_row_count(rows);

			if(rows)
			{
				new xid, weaponid, xammo, xstatus, lisans, count, owner;

				count = -1;
				for(new j; j < rows; j++)
				{
					cache_get_value_int(j, "id", xid);
					cache_get_value_int(j, "weaponid", weaponid);
					cache_get_value_int(j, "ammo", xammo);
					cache_get_value_int(j, "status", xstatus);
					cache_get_value_int(j, "lisans", lisans);
					cache_get_value_int(j, "owner", owner);

					if(xstatus != 2)continue;
					count++;
					if(listitem == count)break;
				}
				cache_delete(veri);

				if(lisans == 1 && owner != PlayerInfo[playerid][pID])
					return SendErrorMessage(playerid, "Lisanslý silahlar çalýnamaz.");

				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
				new Cache:yveri = mysql_query(dbHandle, queryx, true);
				cache_get_row_count(rows);

				if(!rows)
				{
					SendServerMessage(playerid, "%s (mermi: %d) model silahýný araçtan (ID: %d / SQLID: %d) aldýnýz. (%s)", GetWeaponNameEx(weaponid), xammo, vid, VehicleInfo[vid][carID], GetFullDate());

					new string[150];
					format(string, 150, "%s model silahý %s model araçtan alýr.", GetWeaponNameEx(weaponid), GetVehicleModelName(VehicleInfo[vid][carModel]));

					PlayerME(playerid, string);
					SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

					if(xammo > 0) AC_GivePlayerWeapon(playerid, weaponid, xammo);
					cache_delete(yveri);

					mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '0', vehicle = '-1', owner = '%d' WHERE id = '%d'", PlayerInfo[playerid][pID], xid);
					mysql_query(dbHandle, queryx);
				}
				else
				{
					new xweaponid;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "weaponid", xweaponid);
						if(weaponid == xweaponid)break;
					}

					if(weaponid == xweaponid) return SendErrorMessage(playerid, "Zaten sizde ayný silahtan var, bunu yapamazsýnýz."), cache_delete(yveri);
					if(SilahSlotBul(weaponid) == SilahSlotBul(xweaponid)) return SendErrorMessage(playerid, "Zaten sizde ayný tip silahtan var, bunu yapamazsýnýz."), cache_delete(yveri);
					SendServerMessage(playerid, "%s (mermi: %d) model silahýný araçtan (ID: %d / SQLID: %d) aldýnýz. (%s)", GetWeaponNameEx(weaponid), xammo, vid, VehicleInfo[vid][carID], GetFullDate());

					new string[150];
					format(string, 150, "%s model silahý %s model araçtan alýr.", GetWeaponNameEx(weaponid), GetVehicleModelName(VehicleInfo[vid][carModel]));

					PlayerME(playerid, string);
					SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

					if(xammo > 0) AC_GivePlayerWeapon(playerid, weaponid, xammo);
					PlayerInfo[playerid][pSilahSistemi] = 1;
					cache_delete(yveri);

					mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '0', vehicle = '-1', owner = '%d' WHERE id = '%d'", PlayerInfo[playerid][pID], xid);
					mysql_query(dbHandle, queryx);
				}

				mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[playerid][pID], VehicleInfo[vid][carID], "silah araçtan alýndý");
				mysql_tquery(dbHandle, queryx);
			}
		}
	}
	return 1;
}

Dialog:SilahEvEnvanter(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new h = GetNearInsideHouse(playerid);
		if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE house = '%d'", HouseInfo[h][hID]);
			new Cache:veri = mysql_query(dbHandle, queryx, true);
			new rows;
			cache_get_row_count(rows);

			if(rows)
			{
				new xid, weaponid, xammo, xstatus, lisansq, count, ownerid;

				count = -1;
				for(new j; j < rows; j++)
				{
					cache_get_value_int(j, "id", xid);
					cache_get_value_int(j, "weaponid", weaponid);
					cache_get_value_int(j, "ammo", xammo);
					cache_get_value_int(j, "status", xstatus);
					cache_get_value_int(j, "lisans", lisansq);
					cache_get_value_int(j, "owner", ownerid);

					if(xstatus != 1)continue;
					count++;
					if(listitem == count)break;
				}
				cache_delete(veri);

				if(lisansq == 1 && ownerid != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Lisanslý silahlar çalýnamaz.");

				mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
				new Cache:yveri = mysql_query(dbHandle, queryx, true);
				cache_get_row_count(rows);

				if(!rows)
				{
					mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET owner = '%d', status = '0', house = '-1' WHERE id = '%d'", PlayerInfo[playerid][pID], xid);
					mysql_query(dbHandle, queryx);

					new string[150];
					format(string, 150, "%s model silahý evin kasasýndan alýr.", GetWeaponNameEx(weaponid));
					PlayerME(playerid, string);
					SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

					if(xammo > 0) AC_GivePlayerWeapon(playerid, weaponid, xammo);
					cache_delete(yveri);
					SendServerMessage(playerid, "%s (mermi: %d) model %d SQL ID'li silahý, %d SQL ID'li evden aldýn.", GetWeaponNameEx(weaponid), xammo, xid, HouseInfo[h][hID]);
				}
				else
				{
					new xweaponid;

					for(new j; j < rows; j++)
					{
						cache_get_value_int(j, "weaponid", xweaponid);
						if(weaponid == xweaponid)break;
					}

					if(weaponid == xweaponid) return SendErrorMessage(playerid, "Zaten sizde ayný silahtan var, bunu yapamazsýnýz."), cache_delete(yveri);
					if(SilahSlotBul(weaponid) == SilahSlotBul(xweaponid)) return SendErrorMessage(playerid, "Zaten sizde ayný tip silahtan var, bunu yapamazsýnýz."), cache_delete(yveri);

					mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET owner = '%d', status = '0', house = '-1' WHERE id = '%d'", PlayerInfo[playerid][pID], xid);
					mysql_query(dbHandle, queryx);

					new string[150];
					format(string, 150, "%s model silahý evin kasasýndan alýr.", GetWeaponNameEx(weaponid));

					PlayerME(playerid, string);
					SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

					if(xammo > 0) AC_GivePlayerWeapon(playerid, weaponid, xammo);
					PlayerInfo[playerid][pSilahSistemi] = 1;
					SendServerMessage(playerid, "%s (mermi: %d) model %d SQL ID'li silahý, %d SQL ID'li evden aldýn.", GetWeaponNameEx(weaponid), xammo, xid, HouseInfo[h][hID]);
					cache_delete(yveri);
				}

				mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[playerid][pID], HouseInfo[h][hID], "silah evden alýndý");
				mysql_tquery(dbHandle, queryx);
			}
			else SendErrorMessage(playerid, "Ev silah envanteri boþ, iþlem yapamadýnýz."), cache_delete(veri);
		}
		else SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz.");
	}
	return 1;
}

Dialog:SilahEvEnvanterPD(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new h = GetNearInsideHouse(playerid);
		if(h != -1 && GetPlayerVirtualWorld(playerid) > 0)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE house = '%d'", HouseInfo[h][hID]);
			new Cache:veri = mysql_query(dbHandle, queryx, true);
			new rows;
			cache_get_row_count(rows);

			if(rows)
			{
				new xid, weaponid, xammo, xstatus, count, idstr[6];
				count = -1;
				for(new j; j < rows; j++)
				{
					cache_get_value_int(j, "id", xid);
					cache_get_value_int(j, "weaponid", weaponid);
					cache_get_value_int(j, "ammo", xammo);
					cache_get_value_int(j, "status", xstatus);
					format(idstr, 6, "%d", xid);

					if(xid < 1000)
						format(idstr, 6, "0%d", xid);

					if(xid < 100)
						format(idstr, 6, "00%d", xid);

					if(xid < 10)
						format(idstr, 6, "000%d", xid);

					if(xstatus != 1)continue;
					count++;
					if(listitem == count) break;
				}

				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '4', house = '-1' WHERE id = '%d'", xid);
				mysql_query(dbHandle, queryx);

				mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[playerid][pID], HouseInfo[h][hID], "silah evden el konuldu");
				mysql_tquery(dbHandle, queryx);

				cache_delete(veri);
			}
			else SendErrorMessage(playerid, "Ev silah envanteri boþ, iþlem yapamadýnýz."), cache_delete(veri);
		}
		else SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz.");
	}
	return 1;
}

Dialog:SilahVer(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext))
			return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz.");

		new id, weaponid = AC_GetPlayerWeapon(playerid);
		sscanf(inputtext, "u", id);

		if(!IsPlayerConnected(id) || !pTemp[id][pLogged]) return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz.");
		if(PlayerInfo[id][pLevel] < 3) return SendErrorMessage(playerid, "Kullanýcý 3 seviye olmadýðý için silah veremezsiniz.");
		if(GetPlayerState(id) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Sadece ayakta olan kullanýcýlara silah verebilirsin.");
		if(!PlayerNearPlayer(3.0, playerid, id)) return SendErrorMessage(playerid, "Oyuncuya yakýn deðilsiniz, bu iþlemi yapamazsýnýz.");
		if(!weaponid) return SendErrorMessage(playerid, "Elinizde silah yokken bu iþlemi yapamazsýnýz.");
		if(!Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]] || Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] < 1) return SendErrorMessage(playerid, "Bu silah ile bu iþlemi yapamazsýnýz.");
		if(Silah_Bilgi[id][sSilahID][SilahSlotuBul[weaponid]] && Silah_Bilgi[id][sMermi][SilahSlotuBul[weaponid]] >= 0) return SendErrorMessage(playerid, "Bu kullanýcý bu tip bir silaha sahip olduðu için veremezsin.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[id][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);

		new xid;

		if(rows)
		{
			new xweaponid;

			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", xid); // 1 mayis
				cache_get_value_int(j, "weaponid", xweaponid);
				if(weaponid == xweaponid)break;
			}

			if(weaponid == xweaponid) return SendErrorMessage(playerid, "Karþýdaki kullanýcýda ayný silahtan var, bunu yapamazsýnýz."), cache_delete(veri);
			if(SilahSlotBul(weaponid) == SilahSlotBul(xweaponid)) return SendErrorMessage(playerid, "Karþýdaki kullanýcýda ayný tip silahtan var, bunu yapamazsýnýz."), cache_delete(veri);
		}
		cache_delete(veri);

		xid = PlayerInfo[playerid][SilahVerDialogID];
		new ammo = Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]];

		PlayerTextDrawSetString(playerid, Silah_Bilgi[playerid][MermiTD], " ");
		Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] = 0;
		Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]] = false;
		SetPlayerAmmo(playerid, weaponid, 0);
		AC_RemovePlayerWeapon(playerid, weaponid);

		AC_GivePlayerWeapon(id, weaponid, ammo);

		PlayerInfo[id][pSilahSistemi] = 1;

		SendServerMessage(playerid, "%s kiþisine %s model silahýnýzý verdiniz.", GetNameEx(id), GetWeaponNameEx(weaponid));
		SendServerMessage(id, "%s kiþisinden %s model silah aldýnýz.", GetNameEx(playerid), GetWeaponNameEx(weaponid));

		mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET owner = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", PlayerInfo[id][pID], weaponid, PlayerInfo[playerid][pID]);
		mysql_query(dbHandle, queryx);

		mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[id][pID], PlayerInfo[playerid][pID], "silah alýndý");
		mysql_tquery(dbHandle, queryx);

		mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", xid, PlayerInfo[playerid][pID], PlayerInfo[id][pID], "silah verildi");
		mysql_tquery(dbHandle, queryx);
	}
	return 1;
}

/*
Dialog:MermiAl(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows) return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new weaponid, ammo, fiyat, maxmermi;
		new string[1024];

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);

				switch(weaponid)
				{
					case 22: fiyat = 120, maxmermi = MAX_MERMI_COLT;
					case 23: fiyat = 120, maxmermi = MAX_MERMI_SILENCED;
					case 24: fiyat = 190, maxmermi = MAX_MERMI_DEAGLE;
					case 25: fiyat = 210, maxmermi = MAX_MERMI_SHOTGUN;
					case 26: fiyat = 210, maxmermi = MAX_MERMI_SAWNOFF;
					case 28: fiyat = 120, maxmermi = MAX_MERMI_UZI;
					case 29: fiyat = 125, maxmermi = MAX_MERMI_MP5;
					case 30: fiyat = 240, maxmermi = MAX_MERMI_AK47;
					case 31: fiyat = 240, maxmermi = MAX_MERMI_M4;
					case 32: fiyat = 120, maxmermi = MAX_MERMI_TEC9;
					case 33: fiyat = 180, maxmermi = MAX_MERMI_RIFLE;
					case 34: fiyat = 180, maxmermi = MAX_MERMI_SNIPER;
					default: fiyat = 0, maxmermi = 0;
				}

				format(string, 800, "%s%s(%d/%d) (Mermi fiyatý: $%d)\n", string, GetWeaponNameEx(weaponid), ammo, maxmermi, fiyat);
			}
			cache_delete(veri);
			Dialog_Show(playerid, MermiSatinAl, DIALOG_STYLE_LIST, "Liberty City - Mermi Sistemi", string, "Ýleri", "Iptal");
		}
	}
	return 1;
}

Dialog:MermiAl_Fabrika(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows) return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new weaponid, ammo, fiyat, maxmermi;
		new string[1024];

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);

				switch(weaponid)
				{
					case 22: fiyat = 60, maxmermi = MAX_MERMI_COLT;
					case 23: fiyat = 60, maxmermi = MAX_MERMI_SILENCED;
					case 24: fiyat = 95, maxmermi = MAX_MERMI_DEAGLE;
					case 25: fiyat = 105, maxmermi = MAX_MERMI_SHOTGUN;
					case 26: fiyat = 105, maxmermi = MAX_MERMI_SAWNOFF;
					case 28: fiyat = 60, maxmermi = MAX_MERMI_UZI;
					case 29: fiyat = 60, maxmermi = MAX_MERMI_MP5;
					case 30: fiyat = 120, maxmermi = MAX_MERMI_AK47;
					case 31: fiyat = 120, maxmermi = MAX_MERMI_M4;
					case 32: fiyat = 60, maxmermi = MAX_MERMI_TEC9;
					case 33: fiyat = 90, maxmermi = MAX_MERMI_RIFLE;
					case 34: fiyat = 90, maxmermi = MAX_MERMI_SNIPER;
					default: fiyat = 0, maxmermi = 0;
				}

				format(string, 800, "%s%s(%d/%d) (Mermi fiyatý: $%d)\n", string, GetWeaponNameEx(weaponid), ammo, maxmermi, fiyat);
			}
			cache_delete(veri);
			Dialog_Show(playerid, MermiSatinAl_Fabrika, DIALOG_STYLE_LIST, "Liberty City - Mermi Sistemi", string, "Ýleri", "Iptal");
		}
	}
	return 1;
}

Dialog:MermiSatinAl_Fabrika(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), cache_delete(veri), PlayerInfo[playerid][pSilahSistemi] = 0;

		new weaponid;
		new ammo;
		new count = -1;
		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				count++;
				if(count == listitem)break;
			}
			cache_delete(veri);
			SetPVarInt(playerid, "SilahID", weaponid);
			SetPVarInt(playerid, "Mermi", ammo);
		}
		Dialog_Show(playerid, MermiSatinAl2_Fabrika, DIALOG_STYLE_INPUT, "Liberty City - Mermi Sistemi", "%s silahýna almak istediðiniz mermi tutarýný girin:", "Satýn al", "Iptal", GetWeaponNameEx(weaponid));
	}
	return 1;
}

Dialog:MermiSatinAl2_Fabrika(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext) || isnull(inputtext))
			return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		if(PlayerInfo[playerid][pOnDuty])
			return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		new weaponid = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "SilahID");

		//if(!Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]])return SendErrorMessage(playerid, "Bu silaha mermi satýn alamazsýn.");

		new ammo = strval(inputtext);
		new mermi = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "Mermi");

		if(ammo <= 0) return SendErrorMessage(playerid, "Hatalý mermi sayýsý giriþi tespit edildi.");
		
		if(weaponid == 24 && mermi + ammo > 50) return SendErrorMessage(playerid, "Desert Eagle silahý maksimum 50 mermi alabilir.");
		else if(weaponid == 30 && mermi + ammo > 90) return SendErrorMessage(playerid, "AK-47 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 31 && mermi + ammo > 90) return SendErrorMessage(playerid, "M4 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 25 && mermi + ammo > 35) return SendErrorMessage(playerid, "Shotgun silahý maksimum 35 mermi alabilir.");
		else if(weaponid == 22 && mermi + ammo > 68) return SendErrorMessage(playerid, "Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 23 && mermi + ammo > 68) return SendErrorMessage(playerid, "Silenced Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 32 && mermi + ammo > 150) return SendErrorMessage(playerid, "Tec-9 silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 28 && mermi + ammo > 150) return SendErrorMessage(playerid, "Uzi silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 29 && mermi + ammo > 90) return SendErrorMessage(playerid, "MP5 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 33 && mermi + ammo > 30) return SendErrorMessage(playerid, "County Rifle silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 34 && mermi + ammo > 30) return SendErrorMessage(playerid, "Sniper silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 26 && mermi + ammo > 40) return SendErrorMessage(playerid, "Sawnoff Shotgun silahý maksimum 40 mermi alabilir.");
		
		new maxmermi = 0, fiyat = 0;


		switch(weaponid)
		{
			case 22: fiyat = 60, maxmermi = MAX_MERMI_COLT;
			case 23: fiyat = 60, maxmermi = MAX_MERMI_SILENCED;
			case 24: fiyat = 95, maxmermi = MAX_MERMI_DEAGLE;
			case 25: fiyat = 105, maxmermi = MAX_MERMI_SHOTGUN;
			case 26: fiyat = 105, maxmermi = MAX_MERMI_SAWNOFF;
			case 28: fiyat = 60, maxmermi = MAX_MERMI_UZI;
			case 29: fiyat = 60, maxmermi = MAX_MERMI_MP5;
			case 30: fiyat = 120, maxmermi = MAX_MERMI_AK47;
			case 31: fiyat = 120, maxmermi = MAX_MERMI_M4;
			case 32: fiyat = 60, maxmermi = MAX_MERMI_TEC9;
			case 33: fiyat = 90, maxmermi = MAX_MERMI_RIFLE;
			case 34: fiyat = 90, maxmermi = MAX_MERMI_SNIPER;
			default: fiyat = 0, maxmermi = 0;
		}

		if(maxmermi == 0 || fiyat == 0) return SendErrorMessage(playerid, "Bu silaha mermi satýn alýnamaz.");
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] + ammo > maxmermi) return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz, hatalý deðer girdiniz.");
		if(PlayerInfo[playerid][pCash] < ammo * fiyat) return SendErrorMessage(playerid, "Üzerinizde yeterli miktarda para yok. ($%d)", ammo * fiyat);

		Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] += ammo;
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] > maxmermi)
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] = maxmermi;

		new odesunu = ammo * fiyat;
		if(odesunu < 0) odesunu = 1000;
		SendClientMessageEx(playerid, COLOR_GREY, "$%d karþýlýðýnda %s model silahýna %d adet mermi satýn aldýn.", odesunu, GetWeaponNameEx(weaponid), ammo);
		GiveCash(playerid, -odesunu);
		Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %s model silahina $%d karsiliginda %d adet mermi aldi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetWeaponNameEx(weaponid), ammo * fiyat, ammo);

		mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]], weaponid, PlayerInfo[playerid][pID]);
		mysql_query(dbHandle, queryx);

		AC_ResetPlayerWeapons(playerid);
		SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);
	}
	return 1;
}

Dialog:MermiAl_KaraPara(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendErrorMessage(playerid, "Bu komutu sadece ayakta kullanabilirsiniz.");
		if(PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz.");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true), rows;
		cache_get_row_count(rows);
		if(!rows) return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), PlayerInfo[playerid][pSilahSistemi] = 0, cache_delete(veri);

		new weaponid, ammo, fiyat, maxmermi;
		new string[1024];

		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);

				switch(weaponid)
				{
					case 22: fiyat = 144, maxmermi = MAX_MERMI_COLT;
					case 23: fiyat = 144, maxmermi = MAX_MERMI_SILENCED;
					case 24: fiyat = 228, maxmermi = MAX_MERMI_DEAGLE;
					case 25: fiyat = 252, maxmermi = MAX_MERMI_SHOTGUN;
					case 26: fiyat = 252, maxmermi = MAX_MERMI_SAWNOFF;
					case 28: fiyat = 144, maxmermi = MAX_MERMI_UZI;
					case 29: fiyat = 150, maxmermi = MAX_MERMI_MP5;
					case 30: fiyat = 288, maxmermi = MAX_MERMI_AK47;
					case 31: fiyat = 288, maxmermi = MAX_MERMI_M4;
					case 32: fiyat = 144, maxmermi = MAX_MERMI_TEC9;
					case 33: fiyat = 216, maxmermi = MAX_MERMI_RIFLE;
					case 34: fiyat = 216, maxmermi = MAX_MERMI_SNIPER;
					default: fiyat = 0, maxmermi = 0;
				}

				format(string, 800, "%s%s(%d/%d) (Mermi fiyatý: $%d)\n", string, GetWeaponNameEx(weaponid), ammo, maxmermi, fiyat);
			}
			cache_delete(veri);
			Dialog_Show(playerid, MermiSatinAl_KaraPara, DIALOG_STYLE_LIST, "Liberty City - Mermi Sistemi", string, "Ýleri", "Iptal");
		}
	}
	return 1;
}

Dialog:MermiSatinAl_KaraPara(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), cache_delete(veri), PlayerInfo[playerid][pSilahSistemi] = 0;

		new weaponid;
		new ammo;
		new count = -1;
		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				count++;
				if(count == listitem)break;
			}
			cache_delete(veri);
			SetPVarInt(playerid, "SilahID", weaponid);
			SetPVarInt(playerid, "Mermi", ammo);
		}
		Dialog_Show(playerid, MermiSatinAl2_KaraPara, DIALOG_STYLE_INPUT, "Liberty City - Mermi Sistemi", "%s silahýna almak istediðiniz mermi tutarýný girin:", "Satýn al", "Iptal", GetWeaponNameEx(weaponid));
	}
	return 1;
}

Dialog:MermiSatinAl2_KaraPara(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext) || isnull(inputtext))
			return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		if(PlayerInfo[playerid][pOnDuty])
			return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		new weaponid = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "SilahID");

		//if(!Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]])return SendErrorMessage(playerid, "Bu silaha mermi satýn alamazsýn.");

		new ammo = strval(inputtext);
		new mermi = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "Mermi");

		if(ammo <= 0) return SendErrorMessage(playerid, "Hatalý mermi sayýsý giriþi tespit edildi.");
		
		if(weaponid == 24 && mermi + ammo > 50) return SendErrorMessage(playerid, "Desert Eagle silahý maksimum 50 mermi alabilir.");
		else if(weaponid == 30 && mermi + ammo > 90) return SendErrorMessage(playerid, "AK-47 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 31 && mermi + ammo > 90) return SendErrorMessage(playerid, "M4 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 25 && mermi + ammo > 35) return SendErrorMessage(playerid, "Shotgun silahý maksimum 35 mermi alabilir.");
		else if(weaponid == 22 && mermi + ammo > 68) return SendErrorMessage(playerid, "Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 23 && mermi + ammo > 68) return SendErrorMessage(playerid, "Silenced Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 32 && mermi + ammo > 150) return SendErrorMessage(playerid, "Tec-9 silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 28 && mermi + ammo > 150) return SendErrorMessage(playerid, "Uzi silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 29 && mermi + ammo > 90) return SendErrorMessage(playerid, "MP5 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 33 && mermi + ammo > 30) return SendErrorMessage(playerid, "County Rifle silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 34 && mermi + ammo > 30) return SendErrorMessage(playerid, "Sniper silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 26 && mermi + ammo > 40) return SendErrorMessage(playerid, "Sawnoff Shotgun silahý maksimum 40 mermi alabilir.");
		
		new maxmermi = 0, fiyat = 0;

		switch(weaponid)
		{
			case 22: fiyat = 144, maxmermi = MAX_MERMI_COLT;
			case 23: fiyat = 144, maxmermi = MAX_MERMI_SILENCED;
			case 24: fiyat = 228, maxmermi = MAX_MERMI_DEAGLE;
			case 25: fiyat = 252, maxmermi = MAX_MERMI_SHOTGUN;
			case 26: fiyat = 252, maxmermi = MAX_MERMI_SAWNOFF;
			case 28: fiyat = 144, maxmermi = MAX_MERMI_UZI;
			case 29: fiyat = 150, maxmermi = MAX_MERMI_MP5;
			case 30: fiyat = 288, maxmermi = MAX_MERMI_AK47;
			case 31: fiyat = 288, maxmermi = MAX_MERMI_M4;
			case 32: fiyat = 144, maxmermi = MAX_MERMI_TEC9;
			case 33: fiyat = 216, maxmermi = MAX_MERMI_RIFLE;
			case 34: fiyat = 216, maxmermi = MAX_MERMI_SNIPER;
			default: fiyat = 0, maxmermi = 0;
		}

		if(maxmermi == 0 || fiyat == 0) return SendErrorMessage(playerid, "Bu silaha mermi satýn alýnamaz.");
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] + ammo > maxmermi) return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz, hatalý deðer girdiniz.");
		if(PlayerInfo[playerid][pKaraPara] < ammo * fiyat) return SendErrorMessage(playerid, "Üzerinizde yeterli miktarda kara para yok. ($%d)", ammo * fiyat);

		Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] += ammo;
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] > maxmermi)
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] = maxmermi;

		new odesunu = ammo * fiyat;
		if(odesunu < 0) odesunu = 1000;
		new aktor = Get_Nearest_Dynamic_Actor(playerid);
		SendClientMessageEx(playerid, COLOR_LIGHTGREEN2, "%s, sana %d adet %s mermisi verdi. Bunun karþýlýðýnda $%d ödeme yaptýn.", AktorBilgi[aktor][dynamicActorName], ammo, GetWeaponNameEx(weaponid), odesunu);

		Save_Dynamic_Actor(aktor);
		KaraGiveCash(playerid, -odesunu);
		Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %s model silahina $%d kara para karsiliginda %d adet mermi aldi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetWeaponNameEx(weaponid), ammo * fiyat, ammo);

		mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]], weaponid, PlayerInfo[playerid][pID]);
		mysql_query(dbHandle, queryx);

		AC_ResetPlayerWeapons(playerid);
		SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);
	}
	return 1;
}

Dialog:MermiSatinAl(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);
		if(!rows)
			return SendErrorMessage(playerid, "Bu fonksiyondan yararlanamazsýnýz."), cache_delete(veri), PlayerInfo[playerid][pSilahSistemi] = 0;

		new weaponid;
		new ammo;
		new count = -1;
		if(rows)
		{
			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				count++;
				if(count == listitem)break;
			}
			cache_delete(veri);
			SetPVarInt(playerid, "SilahID", weaponid);
			SetPVarInt(playerid, "Mermi", ammo);
		}
		Dialog_Show(playerid, MermiSatinAl2, DIALOG_STYLE_INPUT, "Liberty City - Mermi Sistemi", "%s silahýna almak istediðiniz mermi tutarýný girin:", "Satýn al", "Iptal", GetWeaponNameEx(weaponid));
	}
	return 1;
}

Dialog:MermiSatinAl2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!IsNumeric(inputtext) || isnull(inputtext))
			return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		if(PlayerInfo[playerid][pOnDuty])
			return SendErrorMessage(playerid, "Ýþbaþýnda bu sistemden yararlanamazsýnýz."), DeletePVar(playerid, "Mermi"), DeletePVar(playerid, "SilahID");

		new weaponid = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "SilahID");

		//if(!Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[weaponid]])return SendErrorMessage(playerid, "Bu silaha mermi satýn alamazsýn.");

		new ammo = strval(inputtext);
		new mermi = GetPVarInt(playerid, "SilahID");
		DeletePVar(playerid, "Mermi");

		if(ammo <= 0) return SendErrorMessage(playerid, "Hatalý mermi sayýsý giriþi tespit edildi.");
		
		if(weaponid == 24 && mermi + ammo > 50) return SendErrorMessage(playerid, "Desert Eagle silahý maksimum 50 mermi alabilir.");
		else if(weaponid == 30 && mermi + ammo > 90) return SendErrorMessage(playerid, "AK-47 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 31 && mermi + ammo > 90) return SendErrorMessage(playerid, "M4 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 25 && mermi + ammo > 35) return SendErrorMessage(playerid, "Shotgun silahý maksimum 35 mermi alabilir.");
		else if(weaponid == 22 && mermi + ammo > 68) return SendErrorMessage(playerid, "Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 23 && mermi + ammo > 68) return SendErrorMessage(playerid, "Silenced Pistol silahý maksimum 68 mermi alabilir.");
		else if(weaponid == 32 && mermi + ammo > 150) return SendErrorMessage(playerid, "Tec-9 silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 28 && mermi + ammo > 150) return SendErrorMessage(playerid, "Uzi silahý maksimum 150 mermi alabilir.");
		else if(weaponid == 29 && mermi + ammo > 90) return SendErrorMessage(playerid, "MP5 silahý maksimum 90 mermi alabilir.");
		else if(weaponid == 33 && mermi + ammo > 30) return SendErrorMessage(playerid, "County Rifle silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 34 && mermi + ammo > 30) return SendErrorMessage(playerid, "Sniper silahý maksimum 30 mermi alabilir.");
		else if(weaponid == 26 && mermi + ammo > 40) return SendErrorMessage(playerid, "Sawnoff Shotgun silahý maksimum 40 mermi alabilir.");
		
		new maxmermi = 0, fiyat = 0;


		switch(weaponid)
		{
			case 22: fiyat = 120, maxmermi = MAX_MERMI_COLT;
			case 23: fiyat = 120, maxmermi = MAX_MERMI_SILENCED;
			case 24: fiyat = 190, maxmermi = MAX_MERMI_DEAGLE;
			case 25: fiyat = 210, maxmermi = MAX_MERMI_SHOTGUN;
			case 26: fiyat = 210, maxmermi = MAX_MERMI_SAWNOFF;
			case 28: fiyat = 120, maxmermi = MAX_MERMI_UZI;
			case 29: fiyat = 125, maxmermi = MAX_MERMI_MP5;
			case 30: fiyat = 240, maxmermi = MAX_MERMI_AK47;
			case 31: fiyat = 240, maxmermi = MAX_MERMI_M4;
			case 32: fiyat = 120, maxmermi = MAX_MERMI_TEC9;
			case 33: fiyat = 180, maxmermi = MAX_MERMI_RIFLE;
			case 34: fiyat = 180, maxmermi = MAX_MERMI_SNIPER;
			default: fiyat = 0, maxmermi = 0;
		}

		if(maxmermi == 0 || fiyat == 0) return SendErrorMessage(playerid, "Bu silaha mermi satýn alýnamaz.");
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] + ammo > maxmermi) return SendErrorMessage(playerid, "Bu iþlemi yapamazsýnýz, hatalý deðer girdiniz.");
		if(PlayerInfo[playerid][pCash] < ammo * fiyat) return SendErrorMessage(playerid, "Üzerinizde yeterli miktarda para yok. ($%d)", ammo * fiyat);

		Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] += ammo;
		if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] > maxmermi)
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]] = maxmermi;

		new odesunu = ammo * fiyat;
		if(odesunu < 0) odesunu = 1000;
		new aktor = Get_Nearest_Weapon_Actor(playerid);
		SendClientMessageEx(playerid, COLOR_LIGHTGREEN2, "%s, sana %d adet %s mermisi verdi. Bunun karþýlýðýnda $%d ödeme yaptýn.", AktorBilgi[aktor][dynamicActorName], ammo, GetWeaponNameEx(weaponid), odesunu);

		Save_Dynamic_Actor(aktor);
		GiveCash(playerid, -odesunu);
		Log_Kaydet("loglar/silah.txt", "[%s] %s (C_ID: %d), %s model silahina $%d karsiliginda %d adet mermi aldi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetWeaponNameEx(weaponid), ammo * fiyat, ammo);

		mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE weaponid = '%d' AND owner = '%d' AND status = '0'", Silah_Bilgi[playerid][sMermi][SilahSlotuBul[weaponid]], weaponid, PlayerInfo[playerid][pID]);
		mysql_query(dbHandle, queryx);

		AC_ResetPlayerWeapons(playerid);
		SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);
	}
	return 1;
}*/

Dialog:DialogSilahPozisyon(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araçtayken bu komutu kullanamazsýn.");

		new weaponid = GetPlayerWeapon(playerid);
		if(!weaponid) return SendErrorMessage(playerid, "Elinizde silah yok.");
		if(!IsWeaponWearable(weaponid)) return SendErrorMessage(playerid, "Elinizdeki silah düzenlenemez.");

		switch(listitem)
		{
			case 0:
			{
				if(EditingWeapon[playerid]) return SendErrorMessage(playerid, "Düzenlediðiniz bir silahý gizleyemezsiniz, lütfen önce düzenlemeyi bitirin.");
				if(!IsWeaponHideable(weaponid)) return SendErrorMessage(playerid, "Bu silah gizlenemez.");

				new index = weaponid - 22, weaponname[18], string[150];

				GetWeaponName(weaponid, weaponname, sizeof(weaponname));

				if(WeaponSettings[playerid][index][Hidden])
				{
					SendServerMessage(playerid, "%s artýk üstünüzde görünecek.", weaponname);
					WeaponSettings[playerid][index][Hidden] = false;
				}
				else
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, GetWeaponObjectSlot(weaponid))) RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));

					SendServerMessage(playerid, "%s artýk üstünüzde görünmeyecek.", weaponname);
					WeaponSettings[playerid][index][Hidden] = true;
				}
				if(WeaponSettings[playerid][index][duzenlendi])
				{
					mysql_format(dbHandle, string, sizeof(string), "UPDATE weaponsettings SET Hidden = '%d' WHERE sOwner = '%d' AND WeaponID = '%d'", WeaponSettings[playerid][index][Hidden], PlayerInfo[playerid][pID], weaponid);
					mysql_tquery(dbHandle, string);
				}
			}
			case 1:
			{
				if(EditingWeapon[playerid]) return SendErrorMessage(playerid, "Zaten bir silah düzenliyorsunuz.");

				Dialog_Show(playerid, DialogKemikDuzenle, DIALOG_STYLE_LIST, "Kemik", "Gövde\nKafa\nSol üst kol\nSað üst kol\nSol el\nSað el\nSol kalça\nSað kalça\nSol ayak\nSað ayak\nSað baldýr\nSol baldýr\nSol ön kol\nSað ön kol\nSol omuz\nSað omuz\nBoyun\nÇene", "Seç", "Ýptal");
				EditingWeapon[playerid] = weaponid;
			}
			case 2:
			{
				if(EditingWeapon[playerid]) return SendErrorMessage(playerid, "Zaten bir silah düzenliyorsunuz.");
				if(WeaponSettings[playerid][weaponid - 22][Hidden]) return SendErrorMessage(playerid, "Gizli bir silahý düzenleyemezsiniz.");

				new index = weaponid - 22;

				SetPlayerArmedWeapon(playerid, 0); // Bu kod sorunlu olabilir.
				new slot = GetWeaponObjectSlot(weaponid);
				if(slot != -1)
				{
					SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModelEx(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
					EditAttachedObject(playerid, GetWeaponObjectSlot(weaponid));

					EditingWeapon[playerid] = weaponid;
				}
				else return SendErrorMessage(playerid, "Tüm aksesuar slotlarýný kullanýyorsunuz, lütfen bir aksesuar çýkartýp tekrar deneyin.");
			}
			case 3:
			{
				new string[200];
				mysql_format(dbHandle, string, sizeof(string), "DELETE FROM weaponsettings WHERE sOwner = '%d' AND WeaponID = '%d'", PlayerInfo[playerid][pID], weaponid);
				mysql_tquery(dbHandle, string);
				WeaponSettings[playerid][weaponid - 22][duzenlendi] = 0;
				SendServerMessage(playerid, "Silah pozisyon sistemini sýfýrladýnýz, re-log atmanýz tavsiye edilir.");
			}
		}
	}
	return 1;
}

Dialog:DialogKemikDuzenle(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new weaponid = EditingWeapon[playerid], weaponname[18], string[150];

		GetWeaponName(weaponid, weaponname, sizeof(weaponname));

		WeaponSettings[playerid][weaponid - 22][Bone] = listitem + 1;

		SendServerMessage(playerid, "%s adlý silahýnýzýn kemik seçeneðini deðiþtirdiniz.", weaponname);

		if(WeaponSettings[playerid][weaponid - 22][duzenlendi])
		{
			mysql_format(dbHandle, string, sizeof(string), "UPDATE weaponsettings SET Bone = '%d' WHERE sOwner = '%d' AND WeaponID = '%d'", listitem + 1, PlayerInfo[playerid][pID], weaponid);
			mysql_tquery(dbHandle, string);
		}
	}
	EditingWeapon[playerid] = 0;
	return 1;
}

stock Silah_SayiKontrol(tip, id)
{
	new sorgu[80];
	switch(tip) {
		case 1: mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT COUNT(*) as sayi FROM weapons WHERE status = %d AND house = %d", tip, id);
		case 2: mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT COUNT(*) as sayi FROM weapons WHERE status = %d AND vehicle = %d", tip, id);
		default: return 0;
	}
	new Cache:silah_sayi = mysql_query(dbHandle, sorgu);
	new sayi = 0;
	if(cache_num_rows()) sayi = vericek_int(0, "sayi");
	cache_delete(silah_sayi);
	return sayi;
}

stock Silah_Ver(playerid, silahid, ammo, admin = -1, adminsql = -1, lisans = 0)
{
	mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d' AND status = '0'", PlayerInfo[playerid][pID]);
	new Cache:veri = mysql_query(dbHandle, queryx, true);
	new rows;
	cache_get_row_count(rows);
	if(!rows)
	{
		if(admin != -1)
		{
			SendClientMessageEx(admin, COLOR_GREY, "%s adlý oyuncuya %s (mermi: %d) verdin.", GetNameEx(playerid), SilahAdi(silahid), ammo);
			SendClientMessageEx(playerid, COLOR_GREY, "%s, sana %s (mermi: %d) verdi.", PlayerInfo[admin][pAccname], SilahAdi(silahid), ammo);
			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin, lisans) VALUES ('%d', '%d', '%d', '%d', '%d', '%d')", PlayerInfo[playerid][pID], silahid, ammo, 0, adminsql, lisans);
			mysql_query(dbHandle, queryx);
			PlayerInfo[playerid][pSilahSistemi] = 1;
			AC_GivePlayerWeapon(playerid, silahid, ammo);
			Log_Kaydet("admin/silah.txt", "[%s] %s, %s (C_ID: %d | A_ID: %d) adli oyuncuya %s (mermi: %d) verdi.", GetFullDate(), PlayerInfo[admin][pAccname], GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], SilahAdi(silahid), ammo);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_GREY, "%s model silahýný teslim aldýn.", SilahAdi(silahid));
			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin, lisans) VALUES ('%d', '%d', '%d', '%d', '%d', '%d')", PlayerInfo[playerid][pID], silahid, ammo, 0, adminsql, lisans);
			mysql_query(dbHandle, queryx);
			PlayerInfo[playerid][pSilahSistemi] = 1;
			AC_GivePlayerWeapon(playerid, silahid, ammo);
		}
	}
	else
	{
		new xweaponid;

		for(new j; j < rows; j++)
		{
			cache_get_value_int(j, "weaponid", xweaponid);
			if(silahid == xweaponid)break;
		}

		if(admin != -1)
		{
			if(silahid == xweaponid) return SendErrorMessage(admin, "Karþýdaki kullanýcýnýn üzerinde ayný silahtan var, bunu yapamazsýnýz."), cache_delete(veri);
			if(SilahSlotBul(silahid) == SilahSlotBul(xweaponid)) return SendErrorMessage(admin, "Karþýdaki kullanýcýnýn üzerinde ayný tip silahtan var, bunu yapamazsýnýz."), cache_delete(veri);
			SendClientMessageEx(admin, COLOR_GREY, "%s adlý oyuncuya %s (mermi: %d) verdin.", GetNameEx(playerid), SilahAdi(silahid), ammo);
			SendClientMessageEx(playerid, COLOR_GREY, "%s, sana %s (mermi: %d) verdi.", PlayerInfo[admin][pAccname], SilahAdi(silahid), ammo);
			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin, lisans) VALUES ('%d', '%d', '%d', '%d', '%d', '%d')", PlayerInfo[playerid][pID], silahid, ammo, 0, adminsql, lisans);
			mysql_query(dbHandle, queryx);

			PlayerInfo[playerid][pSilahSistemi] = 1;
			AC_GivePlayerWeapon(playerid, silahid, ammo);
			Log_Kaydet("admin/silah.txt", "[%s] %s, %s (C_ID: %d | A_ID: %d) adli oyuncuya %s (mermi: %d) verdi.", GetFullDate(), PlayerInfo[admin][pAccname], GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], SilahAdi(silahid), ammo);
		}
		else
		{
			if(silahid == xweaponid) return SendErrorMessage(playerid, "Ayný silahýn üzerine silah koyulamaz."), cache_delete(veri);
			if(SilahSlotBul(silahid) == SilahSlotBul(xweaponid)) return SendErrorMessage(playerid, "Ayný tip silahýn üzerine silah koyulamaz."), cache_delete(veri);
			SendClientMessageEx(playerid, COLOR_GREY, "%s model silahýný teslim aldýn.", SilahAdi(silahid));
			mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapons (owner, weaponid, ammo, status, admin, lisans) VALUES ('%d', '%d', '%d', '%d', '%d', '%d')", PlayerInfo[playerid][pID], silahid, ammo, 0, adminsql, lisans);
			mysql_query(dbHandle, queryx);

			PlayerInfo[playerid][pSilahSistemi] = 1;
			AC_GivePlayerWeapon(playerid, silahid, ammo);
		}
	}

	cache_delete(veri);
	return 1;
}

SilahAdi(silahid)
{
	new silahadi[40];
	GetWeaponName(silahid, silahadi, sizeof(silahadi));
	return silahadi;
}

OnPlayerSetData(playerid); public OnPlayerSetData(playerid)
{
	if(!pTemp[playerid][pLogged])return 1;

	if(SilahSistemleri == 1)
	{
		if(!PlayerInfo[playerid][pOnDuty])
		{
			AC_ResetPlayerWeapons(playerid);

			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d'", PlayerInfo[playerid][pID]);
			mysql_tquery(dbHandle, queryx, "SilahlariYukle", "i", playerid);

			if(PlayerInfo[playerid][pKamera])
				AC_GivePlayerWeapon(playerid, 43, PlayerInfo[playerid][pKamera]);

			if(PlayerInfo[playerid][pCicek])
				AC_GivePlayerWeapon(playerid, 14, PlayerInfo[playerid][pCicek]);
            /*
			if(PlayerInfo[playerid][pSprey])
				AC_GivePlayerWeapon(playerid, 41, PlayerInfo[playerid][pSprey]);*/
		}
		else
		{
			for(new j; j < 12; j++)
			{
				if(PlayerInfo[playerid][pWeapons][j] != 0 && PlayerInfo[playerid][pAmmo][j] > 0)
					AC_GivePlayerWeapon(playerid, PlayerInfo[playerid][pWeapons][j], PlayerInfo[playerid][pAmmo][j]);

				PlayerInfo[playerid][pWeapons][j] = 0;
				PlayerInfo[playerid][pAmmo][j] = 0;
			}
		}
	}
	return 1;
}

AC_GivePlayerWeapon(playerid, gunid, ammo)
{
	if(gunid == 19 || gunid == 20 || gunid == 21)return 1;
	if(SilahYapabilirMi(playerid, gunid) == 0) return SendErrorMessage(playerid, "Ayný tip silahtan üzerinizde zaten var.");
	new slot = GetWeaponSlot(gunid);
	PlayerInfo[playerid][pScriptedGun][slot] = gunid;
	PlayerInfo[playerid][pScriptedAmmo][slot] += ammo;
	My_GivePlayerWeapon(playerid, gunid, ammo);
	return 1;
}

AC_GetPlayerWeapon(playerid)
{
	new gunid = GetPlayerWeapon(playerid);
	new slot = GetWeaponSlot(gunid);

	new strname[32];
	format(strname, sizeof(strname), "weapon%d", slot);

	if(PlayerInfo[playerid][pScriptedGun][slot] != gunid || GetPVarInt(playerid, strname) != gunid)return 0;

	return gunid;
}

stock AC_GetPlayerAmmo(playerid)
{
	new gunid = AC_GetPlayerWeapon(playerid);

	if(!gunid)return 0;

	new slot = GetWeaponSlot(gunid);
	new weapon, ammo;
	new strname[32];

	BWH_GetPlayerWeaponData(playerid, slot, weapon, ammo);

	format(strname, sizeof(strname), "ammo%d", slot);
	// if(PlayerInfo[playerid][pScriptedAmmo][slot] < ammo || GetPVarInt(playerid, strname) < ammo) CheatTimer(playerid);

	return ammo;
}

AC_PlayerHasWeapon(playerid, gunid)
{
	if(!gunid) return 1;

	new slot = GetWeaponSlot(gunid);
	new str[32];

	format(str, sizeof(str), "weapon%d", slot);

	if(PlayerInfo[playerid][pScriptedGun][slot] == gunid && GetPVarInt(playerid, str) == gunid)return 1;

	return 0;
}

AC_PlayerHasAmmo(playerid, gunid) {
	if(!gunid) return 0;
	new ammo;
	new slot = GetWeaponSlot(gunid);
	new str[32];

	format(str, sizeof(str), "weapon%d", slot);

	if(PlayerInfo[playerid][pScriptedGun][slot] == gunid && GetPVarInt(playerid, str) == gunid)
		ammo = PlayerInfo[playerid][pScriptedAmmo];
	return ammo;
}

AC_ResetPlayerWeapons(playerid)
{
	My_ResetPlayerWeapons(playerid);

	for(new i; i < 12; i++)
	{
		PlayerInfo[playerid][pScriptedGun][i] = 0;
		PlayerInfo[playerid][pScriptedAmmo][i] = 0;
	}

	return 1;
}

AC_RemovePlayerWeapon(playerid, gunid)
{
	if(gunid < 0 || gunid > 50)return 0;

	new weapons[12];
	new ammo[12];

	for(new i; i < 12; i++)
		BWH_GetPlayerWeaponData(playerid, i, weapons[i], ammo[i]);

	AC_ResetPlayerWeapons(playerid);

	for(new w; w < 12; w++)
	{
		if(weapons[w] == gunid)
		{
			PlayerInfo[playerid][pScriptedGun][w] = 0;
			PlayerInfo[playerid][pScriptedAmmo][w] = 0;
			continue;
		}

		AC_GivePlayerWeapon(playerid, weapons[w], ammo[w]);
	}

	return 1;
}

Dialog:aSilahDuzenle(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new sahip = GetPVarInt(playerid, "aSilahSahip");
		new silahid = GetPVarInt(playerid, "aSilahID");
		new mermi = GetPVarInt(playerid, "aSilahMermi");
		new omur = GetPVarInt(playerid, "aSilahOmur");

		switch(listitem)
		{
			case 0: Dialog_Show(playerid, aSilahMermi, DIALOG_STYLE_INPUT, "Silah Mermisi Deðiþtir", "%s model silahýn þu anda %d adet mermisi bulunuyor, yeni miktarý girin:", ">>", "<<", GetWeaponNameEx(silahid), mermi);
			case 1: Dialog_Show(playerid, aSilahSahip, DIALOG_STYLE_INPUT, "Silah Sahibi Deðiþtir", "%s model silahýn sahibi þu anda %s, yeni sahibi girin:", ">>", "<<", GetWeaponNameEx(silahid), GetNameEx(sahip));
			case 2: Dialog_Show(playerid, aSilahDurum, DIALOG_STYLE_LIST, "Silah Durumu Deðiþtir", "Üzerinde\nEvde\nAraçta\nÝþletmede\nPolis Zimmeti\nYönetici Müdahalesi\nGeri Ýade Yapýldý", ">>", "<<");
			case 3: Dialog_Show(playerid, aSilahOmur, DIALOG_STYLE_INPUT, "Silah Ömrü Deðiþtir", "%s model silahýn ömrü %d olarak tespit edildi, yeni miktarý girin:", ">>", "<<", GetWeaponNameEx(silahid), omur);
		}
	}
	else
	{
		DeletePVar(playerid, "aSilahSQLID");
		DeletePVar(playerid, "aSilahSahip");
		DeletePVar(playerid, "aSilahID");
		DeletePVar(playerid, "aSilahMermi");
		DeletePVar(playerid, "aSilahDurum");
	}
	return 1;
}

Dialog:aSilahOmur(playerid, response, listitem, inputtext[])
{
	if(response && isNumeric(inputtext))
	{
		new sqlid = GetPVarInt(playerid, "aSilahSQLID"), sahip = GetPVarInt(playerid, "aSilahSahip"), silahid = GetPVarInt(playerid, "aSilahID"), omur = GetPVarInt(playerid, "aSilahOmur"), yeniomur = strval(inputtext);

		new targetid = IDKarakterOnline(sahip);
		if(targetid != -1)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET omur = '%d' WHERE id = '%d'", yeniomur, sqlid);
			mysql_query(dbHandle, queryx);
			SendServerMessage(playerid, "%d nolu %s model silahýn mermisi %d olarak deðiþtirildi. (Eski Ömrü: %d)", sqlid, GetWeaponNameEx(silahid), yeniomur, omur);
			SendServerMessage(targetid, "Administrator tarafýndan %d nolu %s model silahýnýn mermisi %d olarak deðiþtirildi.", sqlid, GetWeaponNameEx(silahid), yeniomur);
			Log_Kaydet("admin/silah.txt", "[%s] %s, %d SQL ID'li %s model silahin omrunu %d olarak degistirdi. (Eski Omur: %d)", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yeniomur, omur);
		}
		else
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE id = '%d'", yeniomur, sqlid);
			mysql_query(dbHandle, queryx);
			SendServerMessage(playerid, "%d nolu %s model silahýn ömrü %d olarak deðiþtirildi. (Eski Ömrü: %d)", sqlid, GetWeaponNameEx(silahid), yeniomur, omur);
			Log_Kaydet("admin/silah.txt", "[%s] %s, %d SQL ID'li %s model silahin omrunu %d olarak degistirdi. (Eski Omur: %d)", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yeniomur, omur);
		}
	}
	DeletePVar(playerid, "aSilahSQLID"), DeletePVar(playerid, "aSilahSahip"), DeletePVar(playerid, "aSilahID"), DeletePVar(playerid, "aSilahOmur"), DeletePVar(playerid, "aSilahDurum");
	return 1;
}

Dialog:aSilahMermi(playerid, response, listitem, inputtext[])
{
	if(response && isNumeric(inputtext))
	{
		new sqlid = GetPVarInt(playerid, "aSilahSQLID");
		new sahip = GetPVarInt(playerid, "aSilahSahip");
		new silahid = GetPVarInt(playerid, "aSilahID");
		new mermi = GetPVarInt(playerid, "aSilahMermi");
		new durum = GetPVarInt(playerid, "aSilahDurum");
		new yenimermi = strval(inputtext);

		new targetid = IDKarakterOnline(sahip);
		if(targetid != -1)
		{
			if(durum == 0)
			{
				SendErrorMessage(playerid, "Silah kullanýcýnýn üzerindeyken mermi sayýsýný deðiþtiremezsiniz.");
				DeletePVar(playerid, "aSilahSQLID");
				DeletePVar(playerid, "aSilahSahip");
				DeletePVar(playerid, "aSilahID");
				DeletePVar(playerid, "aSilahMermi");
				DeletePVar(playerid, "aSilahDurum");
				return 1;
			}
			else
			{
				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE id = '%d'", yenimermi, sqlid);
				mysql_query(dbHandle, queryx);
				SendClientMessageEx(targetid, COLOR_GREY, "%s, %d SQL ID'li %s model silahýnýn mermisini %d olarak güncelledi.", PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yenimermi);
				SendAdmMessage("AdmCmd: %s, %d SQL ID'li %s model silahýn mermisini %d olarak deðiþtirdi. (Eski Mermi: %d)", PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yenimermi, mermi);
				Log_Kaydet("admin/silah.txt", "[%s] %s, %d SQL ID'li %s model silahin mermisini %d olarak degistirdi. (Eski Mermi: %d)", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yenimermi, mermi);
			}
		}
		else
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET ammo = '%d' WHERE id = '%d'", yenimermi, sqlid);
			mysql_query(dbHandle, queryx);
			SendAdmMessage("AdmCmd: %s, %d SQL ID'li %s model silahýn mermisini %d olarak deðiþtirdi. (Eski Mermi: %d)", PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yenimermi, mermi);
			Log_Kaydet("admin/silah.txt", "[%s] %s, %d SQL ID'li %s model silahin mermisini %d olarak degistirdi. (Eski Mermi: %d)", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), yenimermi, mermi);
		}
	}
	DeletePVar(playerid, "aSilahSQLID");
	DeletePVar(playerid, "aSilahSahip");
	DeletePVar(playerid, "aSilahID");
	DeletePVar(playerid, "aSilahMermi");
	DeletePVar(playerid, "aSilahDurum");
	return 1;
}

Dialog:Silah_Ev_Ayarla(playerid, response, listitem, inputtext[])
{
	if(!response) return Dialog_Show(playerid, aSilahDurum, DIALOG_STYLE_LIST, "Silah Durumu Deðiþtir", "Üzerinde\nEvde\nAraçta\nÝþletmede\nPolis Zimmeti\nYönetici Müdahalesi\nGeri Ýade Yapýldý", ">>", "<<");
	new sorgu[200];
	new evid = strval(inputtext);
	new sqlid = GetPVarInt(playerid, "aSilahSQLID");
	new sahip = GetPVarInt(playerid, "aSilahSahip");
	new silahid = GetPVarInt(playerid, "aSilahID");
	new durum = GetPVarInt(playerid, "aSilahDurum");

	if(evid < 0) return Dialog_Show(playerid, Silah_Ev_Ayarla, DIALOG_STYLE_INPUT, "Silah Ev Ayarla", "{FFFFFF}Belirliðiniz silahýn hangi evde olmasýný istiyorsunuz? Aþaðýda yer alan boþluða ID'sini girin.", "Tamamla", "Ýptal");


	format(sorgu, sizeof(sorgu), "UPDATE weapons SET vehicle = '-1', house = '%d', status = '1' WHERE id = '%d'", HouseInfo[evid][hID], sqlid);
	mysql_tquery(dbHandle, sorgu);

	SendAdmMessage("[/asilah duzenle] %s, %d ID'li silahýn evini %d olarak güncelledi. (Sahip: %s | Model: %s)", PlayerInfo[playerid][pAccname], sqlid, HouseInfo[evid][hID], GetNameEx(sahip), GetWeaponNameEx(silahid));

	if(IDKarakterOnline(sahip) != -1)
	{
		new targetid = IDKarakterOnline(sahip);
		
		if(durum == 0)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '1' WHERE id = '%d'", sqlid);
			mysql_query(dbHandle, queryx);

			AC_ResetPlayerWeapons(targetid);
			SetTimerEx("OnPlayerSetData", 1000, false, "d", targetid);
		}
	}
	return 1;
}

Dialog:Silah_Arac_Ayarla(playerid, response, listitem, inputtext[])
{
	if(!response) return Dialog_Show(playerid, aSilahDurum, DIALOG_STYLE_LIST, "Silah Durumu Deðiþtir", "Üzerinde\nEvde\nAraçta\nÝþletmede\nPolis Zimmeti\nYönetici Müdahalesi\nGeri Ýade Yapýldý", ">>", "<<");
	new sorgu[200];
	new aracid = strval(inputtext);
	new sqlid = GetPVarInt(playerid, "aSilahSQLID");
	new sahip = GetPVarInt(playerid, "aSilahSahip");
	new silahid = GetPVarInt(playerid, "aSilahID");
	new durum = GetPVarInt(playerid, "aSilahDurum");

	if(aracid < 0) return Dialog_Show(playerid, Silah_Arac_Ayarla, DIALOG_STYLE_INPUT, "Silah Araç Ayarla", "{FFFFFF}Belirliðiniz silahýn hangi araçta olmasýný istiyorsunuz? Aþaðýda yer alan boþluða SQL ID'sini girin.", "Tamamla", "Ýptal");

	format(sorgu, sizeof(sorgu), "UPDATE weapons SET vehicle = '%d', house = '-1', status = '2' WHERE id = '%d'", aracid, sqlid);
	mysql_tquery(dbHandle, sorgu);

	SendAdmMessage("AdmCmd: %s, %d SQL ID'li silahýn aracýný %d olarak deðiþtirdi.", PlayerInfo[playerid][pAccname], sqlid, aracid);
	Log_Kaydet("admin/silah.txt", "[%s] %s, %d ID'li %s model silahin ait oldugu araci %d olarak guncelledi.", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), aracid);

	if(IDKarakterOnline(sahip) != -1)
	{
		new targetid = IDKarakterOnline(sahip);
		
		if(durum == 0)
		{
			AC_ResetPlayerWeapons(targetid);
			SetTimerEx("OnPlayerSetData", 1000, false, "d", targetid);
		}
	}
	return 1;
}

Dialog:aSilahDurum(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new sqlid = GetPVarInt(playerid, "aSilahSQLID");
		new sahip = GetPVarInt(playerid, "aSilahSahip");
		new silahid = GetPVarInt(playerid, "aSilahID");
		new durum = GetPVarInt(playerid, "aSilahDurum");

		if(listitem == 0)
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET vehicle = '-1', house = '-1' WHERE id = '%d'", sqlid);
			mysql_query(dbHandle, queryx);
		}

		if(listitem == 1) return Dialog_Show(playerid, Silah_Ev_Ayarla, DIALOG_STYLE_INPUT, "Silah Ev Ayarla", "{FFFFFF}Belirliðiniz silahýn hangi evde olmasýný istiyorsunuz? Aþaðýda yer alan boþluða girin.", "Tamamla", "Ýptal");
		else if(listitem == 2) return Dialog_Show(playerid, Silah_Arac_Ayarla, DIALOG_STYLE_INPUT, "Silah Araç Ayarla", "{FFFFFF}Belirliðiniz silahýn hangi araçta olmasýný istiyorsunuz? Aþaðýda yer alan boþluða SQL ID'sini girin.", "Tamamla", "Ýptal");
		else if(listitem == 3)
		{
			SendErrorMessage(playerid, "Ýþletmelere silah yerleþtirme özelliði pasif durumdadýr.");
			DeletePVar(playerid, "aSilahSQLID");
			DeletePVar(playerid, "aSilahSahip");
			DeletePVar(playerid, "aSilahID");
			DeletePVar(playerid, "aSilahMermi");
			DeletePVar(playerid, "aSilahDurum");
			return 1;
		}

		if(IDKarakterOnline(sahip) != -1)
		{
			new targetid = IDKarakterOnline(sahip);
			
			if((durum == 0 && listitem != 0) || (durum != 0 && listitem == 0))
			{
				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '%d' WHERE id = '%d'", listitem, sqlid);
				mysql_query(dbHandle, queryx);

				AC_ResetPlayerWeapons(targetid);
				SetTimerEx("OnPlayerSetData", 1000, false, "d", targetid);
			}
			else
			{
				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '%d' WHERE id = '%d'", listitem, sqlid);
				mysql_query(dbHandle, queryx);
			}
		}
		else
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '%d' WHERE id = '%d'", listitem, sqlid);
			mysql_query(dbHandle, queryx);
		}
		SendServerMessage(playerid, "%d nolu %s model silahýn durumunu deðiþtirdiniz.", sqlid, GetWeaponNameEx(silahid));
	}
	DeletePVar(playerid, "aSilahSQLID");
	DeletePVar(playerid, "aSilahSahip");
	DeletePVar(playerid, "aSilahID");
	DeletePVar(playerid, "aSilahMermi");
	DeletePVar(playerid, "aSilahDurum");
	return 1;
}
Dialog:aSilahSahip(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new sqlid = GetPVarInt(playerid, "aSilahSQLID");
		new sahip = GetPVarInt(playerid, "aSilahSahip");
		new silahid = GetPVarInt(playerid, "aSilahID");
		new durum = GetPVarInt(playerid, "aSilahDurum");

		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM users WHERE name = '%e'", inputtext);
		new Cache:idveri = mysql_query(dbHandle, queryx, true), rows;
		cache_get_row_count(rows);

		new yenisahip;
		if(!rows)
		{
			SendErrorMessage(playerid, "%s adlý karakter bulunamadý. (%s)", inputtext, GetFullDate());
			cache_delete(idveri);
			DeletePVar(playerid, "aSilahSQLID");
			DeletePVar(playerid, "aSilahSahip");
			DeletePVar(playerid, "aSilahID");
			DeletePVar(playerid, "aSilahMermi");
			DeletePVar(playerid, "aSilahDurum");
			return 1;
		}
		else
		{
			cache_get_value_int(0, "id", yenisahip);
			cache_delete(idveri);
		}

		new targetid = IDKarakterOnline(sahip);
		if(targetid != -1)
		{
			if(durum == 0)
			{
				SendErrorMessage(playerid, "Bu silahýn sahibi %s þu anda çevrimiçi ve silah üzerinde, bu iþlemi yapamazsýnýz.", GetNameEx(targetid));
				DeletePVar(playerid, "aSilahSQLID"), DeletePVar(playerid, "aSilahSahip"), DeletePVar(playerid, "aSilahID"), DeletePVar(playerid, "aSilahMermi"), DeletePVar(playerid, "aSilahDurum");
				return 1;
			}
			else
			{
				mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET owner = '%d' WHERE id = '%d'", yenisahip, sqlid);
				mysql_query(dbHandle, queryx);
			}
		}
		else
		{
			mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET owner = '%d' WHERE id = '%d'", yenisahip, sqlid);
			mysql_query(dbHandle, queryx);
		}
		SendServerMessage(playerid, "%d nolu %s model silahýn sahibini %s olarak deðiþtirdiniz. (Eski: %s)", sqlid, GetWeaponNameEx(silahid), GetNameEx(yenisahip), GetNameEx(sahip));
		Log_Kaydet("admin/silah.txt", "[%s] %s, %d SQL ID'li %s model silahin sahibini %s olarak degistirdi. (Eski Sahip: %s)", GetFullDate(), PlayerInfo[playerid][pAccname], sqlid, GetWeaponNameEx(silahid), GetNameEx(yenisahip), GetNameEx(sahip));
	}
	DeletePVar(playerid, "aSilahSQLID"), DeletePVar(playerid, "aSilahSahip"), DeletePVar(playerid, "aSilahID"), DeletePVar(playerid, "aSilahMermi"), DeletePVar(playerid, "aSilahDurum");
	return 1;
}

IDKarakterOnline(id)
{
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pID] == id)
		{
			return i;
		}
	}
	return -1;
}
