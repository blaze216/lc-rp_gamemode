
#define 	MAX_OYUNCU_UYUSTURUCU_SAYI	6
#define 	MAX_OYUNCU_PAKET_SAYI		6
#define 	MAX_OYUNCU_HAMMADDE_SAYI	100
//
#define 	MAX_UYUSTURUCU_GRAM 		15
#define 	MAX_UYUSTURUCU_KALITE		100
//
#define 	MAX_ARAC_PAKET_SAYI			10
//
#define 	HAMMADDE_FIYAT				5 // $
//
#define		MAX_TOHUM					300
#define 	TOHUM_OBJE 					15038 //1320
#define 	TOHUM_LABEL_RENK 			0xFFFFFFFF
#define 	TOHUM_LABEL_MESAFE 			5.0
//
#define 	PAKET_LABEL_MESAFE 			5.0
#define 	PAKET_LABEL_RENK 			0xFFFFFFFF

enum UyusVeriler
{
	Ad[30],
	HammaddeSayi // 1gr üretmek için gereken hammadde sayýsý
}

new UyusTipleri[11][UyusVeriler] =
{
	{"LSD", 5}, // ID: 0 | Üretim Fiyatý: $50
	{"Kokain", 9}, // ID: 1 | Üretim Fiyat: $60
	{"Eroin", 7}, // ID: 2 | Üretim Fiyatý: $50
	{"Amfetamin / pasif", 9999}, // ID: 3 | Üretim Fiyatý: $40
	{"Metamfetamin", 4}, // ID: 4 | Üretim Fiyatý: $30
	{"Ekstazi",	3}, // ID: 5 | Üretim Fiyatý: $45
	{"PCP / pasif",	9999}, // ID: 6 | Üretim Fiyatý: $35
	{"Ketamin / pasif",	9999}, // ID: 7 | Üretim Fiyatý: $55
	{"Marijuana", 5}, // ID: 8 | Üretim Fiyatý: $50
	{"Haþhaþ / pasif", 99999}, // ID: 9 | Üretim Fiyatý: $50
	{"Aþk Suyu", 99999}
};

enum PaketVeriler
{
	PaketAd[30],
	Boyut[15],
	MaxGram,
	PaketObje
}

new PaketTipleri[15][PaketVeriler] =
{
	{"Ziploc Poþet", "K", 7, -1575},
	{"Ziploc Poþet", "O", 14, -1575},
	{"Ziploc Poþet", "B", 28, -1575},
	{"Poþetle Sarýlmýþ Top", "K", 10, -1580},
	{"Poþetle Sarýlmýþ Top", "O", 20, -1580},
	{"Poþetle Sarýlmýþ Top", "B", 30, -1580},
	{"Sarýlý Folyo", "K", 8, -1576},
	{"Sarýlý Folyo", "B", 16, -1576},
	{"Ýlaç Kutusu", "K", 5, -1577},
	{"Ýlaç Kutusu", "O", 10, -1577},
	{"Ýlaç Kutusu", "B", 15, -1577},
	{"Pizza Kutusu", "O", 70, 1582},
	{"Pizza Kutusu", "B", 140, 1582},
	{"El Çantasý", "B", 250, 1210},
	{"Spor Çantasý", "B", 500, 371}
};

enum Tohumlar
{
	tohumObjeID,
	tohumHammadde,
	tohumSahip,
	tohumSure,
	Text3D: tohumLabel,
	Float: tohumX,
	Float: tohumY,
	Float: tohumZ,
	tohumVW,
	tohumInt
}
new Tohum[MAX_TOHUM][Tohumlar];

new UyusturucuDialog[MAX_PLAYERS][6];

OyuncuUyusturucuGoster(playerid, sqlid, tip)
{
	new sorgu[400];
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT name, hammadde FROM users WHERE id = %d", sqlid);
	mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, sqlid, 0, tip, 0, "");
}

OyuncuUyusturucuSayi(sqlid)
{
	new sayi, sorgu[100], Cache: onbellek;
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT sqlid FROM uyusturucular WHERE sqlid = %d", sqlid);
	onbellek = mysql_query(dbHandle, sorgu);
	sayi = cache_num_rows();
	cache_delete(onbellek);
	return sayi;
}

OyuncuPaketSayi(sqlid)
{
	new sayi, sorgu[100], Cache: onbellek;
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT sqlid FROM paketler WHERE sqlid = %d", sqlid);
	onbellek = mysql_query(dbHandle, sorgu);
	sayi = cache_num_rows();
	cache_delete(onbellek);
	return sayi;
}

OyuncuUyusturucuVer(sqlid, uindex, gram, kalite)
{
	new sorgu[120];
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "INSERT INTO uyusturucular (sqlid, uindex, gram, kalite) VALUES (%d, %d, %d, %d)", sqlid, uindex, gram, kalite);
	mysql_tquery(dbHandle, sorgu);
}

OyuncuPaketIstekSil(playerid)
{
	new hedefid = PlayerInfo[playerid][PaketVer][0];
	if(hedefid != INVALID_PLAYER_ID)
	{
		PlayerInfo[playerid][PaketVer][0] = PlayerInfo[hedefid][PaketVer][0] = INVALID_PLAYER_ID;
		PlayerInfo[playerid][PaketVer][1] = PlayerInfo[hedefid][PaketVer][1] = 0;
	}
}

OyuncuYerdenPaketAl(playerid)
{
	new Float:x, Float:y, Float:z, obje[2], Text3D: label[2];
	GetPlayerPos(playerid, Float:x, Float:y, Float:z);
	Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, obje, sizeof(obje), 4.0, GetPlayerVirtualWorld(playerid));
	Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_3D_TEXT_LABEL, label, sizeof(label), 4.0, GetPlayerVirtualWorld(playerid));
	if(IsValidDynamicObject(obje[0]))
	{
		new array[2], sorgu[130];
		Streamer_GetArrayData(STREAMER_TYPE_OBJECT, obje[0], E_STREAMER_EXTRA_ID, array);
		if(array[0] != 85) return SendErrorMessage(playerid, "Herhangi bir pakete yakýn deðilsiniz.");
		if(array[1] <= 0) return SendErrorMessage(playerid, "Bir hata oluþtu.");
		mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT * FROM paketler WHERE ID = %d", array[1]);
		if((OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE) && PlayerInfo[playerid][pOnDuty])
		{
			mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, PlayerInfo[playerid][pID], 20, 0, 1, "");
		}
		else
		{
			if(OyuncuPaketSayi(PlayerInfo[playerid][pID]) >= MAX_OYUNCU_PAKET_SAYI) return SendErrorMessage(playerid, "Üzerinize daha fazla uyuþturucu paketi alamazsýnýz.");
			mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, PlayerInfo[playerid][pID], 20, 0, 0, "");
		}
		DestroyDynamicObject(obje[0]);
	}
	return 1;
}

bosTohumID()
{
	new temp[123], Cache: result, lastid, id, returnable = 1, maxid = 1;
	result = mysql_query(dbHandle, "SELECT tohumID FROM tohumlar ORDER BY tohumID ASC");
	for(new i = 0; i < cache_num_rows(); i++)
	{
		maxid++;
		cache_get_value_name(i, "tohumID", temp), id = strval(temp);
		if(id - lastid > 1)
		{
			returnable = lastid + 1;
			cache_delete(result);
			return returnable;
		}
		lastid = id;
	}
	cache_delete(result);
	return maxid;
}

OyuncuUyusturucuKullan(playerid, tur, kalite)
{
	new Float: hp, dakika, havadurumu;
	switch(tur)
	{
		case 0: // LSD | Eski HP: 7
		{
			havadurumu = 273;
			if(kalite >= 1 && kalite <= 39) hp = 2.0;
			else if(kalite >= 40 && kalite <= 69) hp = 4.0;
			else if(kalite >= 70) hp = 5.0;
		}
		case 1: // Kokain | Eski HP: 9
		{
			havadurumu = 186;
			if(kalite >= 1 && kalite <= 39) hp = 3.0;
			else if(kalite >= 40 && kalite <= 69) hp = 6.0;
			else if(kalite >= 70) hp = 9.0;
		}
		case 2: // Eroin | Eski HP: 7
		{
			havadurumu = -66;
			if(kalite >= 1 && kalite <= 39) hp = 3.0;
			else if(kalite >= 40 && kalite <= 69) hp = 5.0;
			else if(kalite >= 70) hp = 7.0;
		}
		case 3: // Amfetamin | Kaldýrýldý, Metamfetamin olarak güncellendi.
		{
			havadurumu = 244;
			hp = 8.0;
		}
		case 4: // Metamfetamin | Eski HP: 4
		{
			havadurumu = 234;

			if(kalite >= 1 && kalite <= 39) hp = 1.0;
			else if(kalite >= 40 && kalite <= 69) hp = 2.0;
			else if(kalite >= 70) hp = 4.0;
		}
		case 5: // ekstazi 
		{
			havadurumu = 383;
			if(kalite >= 1 && kalite <= 39) hp = 1.0;
			else if(kalite >= 40 && kalite <= 69) hp = 2.0;
			else if(kalite >= 70) hp = 3.0;
		}
		case 6: // pcp | Kaldýrýldý, LSD olarak güncellendi.
		{
			havadurumu = 245;
			hp = 5.0;
		}
		case 7: // ketamin | Kaldýrýldý, Kokain olarak güncellendi.
		{
			havadurumu = 251;
			hp = 8.0;
		}
		case 8: // mari
		{
			havadurumu = 221;
			hp = 1.0;
		}
		case 9: // Haþhaþ | Kaldýrýldý, Marijuana olarak güncellendi.
		{
			havadurumu = 221;
			hp = 1.0;
		}
		case 10: // aþk suyu
		{
			havadurumu = 1001;
			hp = 15.0;
		}
	}

	if(PlayerInfo[playerid][pBagimlilikSeviye] > 0)
	{
		PlayerInfo[playerid][pKrizSure] = 240;
		SendClientMessageEx(playerid, COLOR_WHITE, "Kullandýðýn uyuþturucu '240 dakika oyun süresi' için seni idare ediyor olacaktýr. (Peþ peþe uyuþturucu kullanmanýz süreyi uzatmaz.)");
		if(PlayerInfo[playerid][pUTedaviEXP] > 0)
		{
			PlayerInfo[playerid][pUTedaviEXP] = 0;
			SendClientMessageEx(playerid, COLOR_WHITE, "Tedavi sürecinde uyuþturucu kullandýðýn için tüm tedaviler boþa gitti. Baþtan baþlýyorsun.");
		}
	}

	new bagimlilikorani = random(500);
	if(bagimlilikorani <= kalite)
	{
		PlayerInfo[playerid][pBagimlilikEXP]++;
		if(PlayerInfo[playerid][pBagimlilikEXP]%3 != 0)
		{
			SendClientMessageEx(playerid, COLOR_WHITE, "Kullandýðýn uyuþturucu, üzerinde 'baðýmlýlýk etkisi' göstermeye baþladý. %d kez daha..", 3 - PlayerInfo[playerid][pBagimlilikEXP]);
			SendClientMessageEx(playerid, COLOR_WHITE, "Bu mesajý görecek olursan, artýk bir 'baðýmlý' olacaksýn.");
		}
		else
		{
			PlayerInfo[playerid][pBagimlilikSeviye]++;
			PlayerInfo[playerid][pBagimlilikEXP] = 0;
			PlayerInfo[playerid][pKrizSure] = 240;
			SendClientMessageEx(playerid, COLOR_WHITE, "Defalarca kez uyuþturucu kullandýðýn için artýk uyuþturucu baðýmlýsý oldun.");
			SendClientMessageEx(playerid, COLOR_WHITE, "Belirsiz zamanlarda uyuþturucuya ihtiyaç duyabilir, kendini kötü hissedebilirsin.");
			SendClientMessageEx(playerid, COLOR_GREEN, "Saðlýk kuruluþlarý çalýþanlarý tarafýndan tedavi olmak istersen, 911'i aramayý ihmal etme.");			
		}
	}

	if(!(1 <= kalite <= 39)) dakika = 3;
	if(!(40 <= kalite <= 69)) dakika = 4;
	if(!(70 <= kalite <= 100)) dakika = 5;

    PlayerInfo[playerid][pHealth] = PlayerInfo[playerid][pHealth]+hp;
	SetPVarInt(playerid, "uyusgettime", gettime() + (dakika * 58));
	PlayerInfo[playerid][UyusKullan] = gettime() + (60 * 60);
	new sorgu[120];
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE users SET uyusgettime = %d WHERE id = %d", PlayerInfo[playerid][UyusKullan], PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, sorgu);
	SetTimerEx("OyuncuUyusturucuKullanFunc", 60000, false, "df", playerid, hp);
	SetTimerEx("OyuncuUyusturucuEfekt", 3000, false, "dd", playerid, havadurumu);
	return 1;
}

forward OyuncuUyusturucuEfekt(playerid, havadurum);
public OyuncuUyusturucuEfekt(playerid, havadurum)
{
	SetPlayerDrunkLevel(playerid, 1500);
	SetPlayerWeather(playerid, havadurum);
	SetPlayerTime(playerid, 12, 0);
	return 1;
}

forward OyuncuUyusturucuKullanFunc(playerid, Float: hp);
public OyuncuUyusturucuKullanFunc(playerid, Float: hp)
{
	if(!IsPlayerConnected(playerid) || GetPVarInt(playerid, "uyusgettime") < gettime())
	{
		SetPlayerCurrentTimeAndWeather(playerid);
		SetPlayerDrunkLevel(playerid, 0);
		return 1;
	}
	SetPlayerDrunkLevel(playerid, 1500);
/*	new Float: can;
	AC_GetPlayerHealth(playerid, can);
	AC_SetPlayerHealth(playerid, can+hp);
	if((can+hp) > (PlayerInfo[playerid][pSpawnHealth]+50))
		AC_SetPlayerHealth(playerid, PlayerInfo[playerid][pSpawnHealth]+50);*/
		
	SetTimerEx("OyuncuUyusturucuKullanFunc", 60000, false, "df", playerid, hp);
	return 1;
}

forward PaketYukle();
public PaketYukle()
{
	new veriler = cache_num_rows();
	if(veriler)
	{
		new pid, objeid, yukle, pindex, vw, interior, Float: x, Float: y, Float: z, label[60], array[2];
		while(yukle < veriler)
		{
			cache_get_value_int(yukle, "ID", pid);
			cache_get_value_int(yukle, "pindex", pindex);
			cache_get_value_float(yukle, "x", x);
			cache_get_value_float(yukle, "y", y);
			cache_get_value_float(yukle, "z", z);
			cache_get_value_int(yukle, "vw", vw);
			cache_get_value_int(yukle, "interior", interior);
			objeid = CreateDynamicObject(PaketTipleri[pindex][PaketObje], x, y, z - 0.6, 0.0, 0.0, 0.0, vw, interior);
			array[0] = 85;
			array[1] = pid;
			Streamer_SetArrayData(STREAMER_TYPE_OBJECT, objeid, E_STREAMER_EXTRA_ID, array);
			format(label, 60, "%s [%s]", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut][0]);
			yukle++;
		}
		printf("[PAKETLER] Toplam: %d", yukle);
	}
	else print("[PAKETLER] Toplam: Yok");
	return 1;
}

forward UyusturucuSorgu(playerid, sqlid, islem, tip, listitem, inputtext[]);
public UyusturucuSorgu(playerid, sqlid, islem, tip, listitem, inputtext[])
{
	new veriler = cache_num_rows(), yukle, baslik[100], liste[2000], karakteradi[24], index, gram, kalite, pindex, pgram, pkalite;
	new sorgu[600], uid; //, hammadde;
	UyusturucuDialog[playerid][0] = sqlid;
	UyusturucuDialog[playerid][1] = islem;
	UyusturucuDialog[playerid][2] = tip;
	if(veriler)
	{
		switch(islem)
		{
			case 0: // Oyuncu uyuþturucu seçenek
			{
				cache_get_value(yukle, "name", karakteradi, 24);
				format(baslik, sizeof(baslik), "Uyuþturucularým");
				format(liste, sizeof(liste), "Seçenek\tAçýklama\t#####\n");
				format(liste, sizeof(liste), "%s{A9C4E4}Uyuþturucular\t{FFFFFF}paketlenmemiþ uyuþturucularýnýzý yönetebilirsiniz (paketlemeden veremezsiniz)\t \n", liste);
				format(liste, sizeof(liste), "%s{A9C4E4}Paketler\t{FFFFFF}paketlenmiþ uyuþturucularýnýzý yönetebilirsiniz\t \n", liste);
				format(liste, sizeof(liste), "%s{A9C4E4}Hammaddeler\t{FFFFFF}uyuþturucu üretmek için kullanýlýr\t{b9f2ff}%d adet\t", liste, PlayerInfo[playerid][pHammadde]);

				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 1: // Oyuncu uyuþturucular
			{
				cache_get_value(yukle, "name", karakteradi, 24);

				new kalite_text[30];

				format(kalite_text, sizeof(kalite_text), "[?]");
				format(liste, sizeof(liste), "Uyuþturucu\tGram\tKalite\n");
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "gram", gram);
					cache_get_value_int(yukle, "kalite", kalite);

					if(kalite > 0 && kalite < 40) format(kalite_text, sizeof(kalite_text), "düþük kalite");
					else if(kalite > 39 && kalite < 70) format(kalite_text, sizeof(kalite_text), "normal kalite");
					else if(kalite > 69) format(kalite_text, sizeof(kalite_text), "yüksek kalite");
					format(liste, sizeof(liste), "%s%s\t%d\t%s (%d)\n", liste, UyusTipleri[index][Ad], gram, kalite_text, kalite);
					yukle++;
				}
				format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucular", karakteradi);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 2: // Oyuncu paketler
			{
				cache_get_value(yukle, "name", karakteradi, 24);

				new kalite_text[30];

				format(liste, sizeof(liste), "Paket\tGram\tKalite\n");
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "pindex", pindex);
					cache_get_value_int(yukle, "gram", pgram);
					cache_get_value_int(yukle, "kalite", pkalite);

					if(pkalite > 0 && pkalite < 40) format(kalite_text, sizeof(kalite_text), "düþük kalite");
					else if(pkalite > 39 && pkalite < 70) format(kalite_text, sizeof(kalite_text), "normal kalite");
					else if(pkalite > 69) format(kalite_text, sizeof(kalite_text), "yüksek kalite");

					format(liste, sizeof(liste), "%s%s [%c] (%s)\t%d\t%s (%d)\n", liste, PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], pgram, kalite_text, pkalite);
					yukle++;
				}
				format(baslik, sizeof(baslik), "%s adlý karaktere ait paketler", karakteradi);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 3: // Uyuþturucu detay iþlem
			{
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				format(liste, sizeof(liste), " \t \n");
				format(liste, sizeof(liste), "%s%s\t%dgr [%d kalite]\n", liste, UyusTipleri[index][Ad], gram, kalite);
				format(liste, sizeof(liste), "%s \t \n", liste);
				if(tip)
				{
					format(liste, sizeof(liste), "%s{A9C4E4}Tip Deðiþtir\t{FFFFFF}tip deðiþtirmeye yarar\n", liste);
					format(liste, sizeof(liste), "%sUyuþturucu tipini deðiþtir\t \n", liste);
					format(liste, sizeof(liste), "%sGram düzenle\t \n", liste);
					format(liste, sizeof(liste), "%sKalite düzenle\t \n", liste);
					format(liste, sizeof(liste), "%sSil\t \n", liste);
				}
				else
				{
					format(liste, sizeof(liste), "%s{A9C4E4}Kullan\t{FFFFFF}uyuþturucuyu kullanmaya yarar\n", liste);
					format(liste, sizeof(liste), "%s \t \n", liste);
					format(liste, sizeof(liste), "%s{A9C4E4}Birleþtir\t{FFFFFF}paketlenmiþ ayný tür uyuþturucuyla birleþtirmeye yarar\n", liste);
					format(liste, sizeof(liste), "%s{A9C4E4}Paketle\t{FFFFFF}uyuþturucunuzu bir pakete koymaya yarar, bu sayede verebilirsiniz\n", liste);
					format(liste, sizeof(liste), "%s{A9C4E4}At\t{FFFFFF}uyuþturucunuzu imha etmeye yarar, geri alýnamaz", liste);
				}
				format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu", karakteradi);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 4: // Uyuþturucu detay iþlem
			{
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				if(!strcmp(inputtext, "Uyuþturucu tipini deðiþtir"))
				{
					for(new i; i < sizeof(UyusTipleri); i++)
						format(liste, sizeof(liste), "%s%s\n", liste, UyusTipleri[i][Ad]);

					UyusturucuDialog[playerid][1] = 5;
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu deðiþtir", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_LIST, baslik, liste, "Seç", "Kapat");
				}
				else if(!strcmp(inputtext, "Gram düzenle"))
				{
					UyusturucuDialog[playerid][1] = 6;
					format(liste, sizeof(liste), "%s (%dgr [%d kalite]) adlý uyuþturucunun gramýný deðiþtirmek için aþaðýdaki kutuya yeni gram deðerini girin:", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu düzenle", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
				}
				else if(!strcmp(inputtext, "Kalite düzenle"))
				{
					UyusturucuDialog[playerid][1] = 7;
					format(liste, sizeof(liste), "%s (%dgr [%d kalite]) adlý uyuþturucunun kalitesini deðiþtirmek için aþaðýdaki kutuya yeni kalite deðerini girin:", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu düzenle", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
				}
				else if(!strcmp(inputtext, "Sil"))
				{
					UyusturucuDialog[playerid][1] = 8;
					format(liste, sizeof(liste), "%s (%dgr [%d kalite]) adlý uyuþturucuyu silmek istiyor musun?", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu düzenle", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_MSGBOX, baslik, liste, "Evet", "Hayýr");
				}
				else if(!strcmp(inputtext, "Kullan"))
				{
					gram -= 1;
					OyuncuUyusturucuKullan(playerid, index, kalite);
					PlayerAME2(playerid, "uyuþturucu kullanýr.");
					if(gram < 1) mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM uyusturucular WHERE ID = %d", uid);
					else mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET gram = %d WHERE ID = %d", gram, uid);
					mysql_tquery(dbHandle, sorgu);
				}
				else if(!strcmp(inputtext, "Paketle"))
				{
					new paketsayi;
					cache_get_value_int(yukle, "paketsayi", paketsayi);
					if(paketsayi >= MAX_OYUNCU_PAKET_SAYI) return SendErrorMessage(playerid, "Boþ paket slotun yok.");
					UyusturucuDialog[playerid][1] = 9;
					format(liste, sizeof(liste), "Paket\tBoyut\tKapasite\n");
					for(new i; i < sizeof(PaketTipleri); i++)
						format(liste, sizeof(liste), "%s%s\t%s\t%dgr\n", liste, PaketTipleri[i][PaketAd], PaketTipleri[i][Boyut], PaketTipleri[i][MaxGram]);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu yeni paket", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
				}
				else if(!strcmp(inputtext, "Birleþtir"))
				{
					new paketsayi;
					cache_get_value_int(yukle, "paketsayi", paketsayi);
					if(!paketsayi) return SendErrorMessage(playerid, "Mevcut paketin yok.");
					UyusturucuDialog[playerid][5] = uid;
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT paketler.*, uyusturucular.uindex as uyusindex, uyusturucular.gram as uyusgram, uyusturucular.kalite as uyuskalite, %s FROM paketler LEFT JOIN uyusturucular ON uyusturucular.ID = %d WHERE paketler.sqlid = %d", sorgu, uid, UyusturucuDialog[playerid][0]);
					mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 11, UyusturucuDialog[playerid][2], 0, inputtext);
				}
				else if(!strcmp(inputtext, "At"))
				{
					UyusturucuDialog[playerid][1] = 14;
					format(liste, sizeof(liste), "%s (%dgr [%d kalite]) adlý uyuþturucuyu atmak istiyor musun?", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucuyu at", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_MSGBOX, baslik, liste, "Evet", "Hayýr");
				}
			}
			case 5: // Uyuþturucu tipini deðiþtir
			{
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET uindex = %d WHERE ID = %d", listitem, uid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s adlý oyuncunun %s (%dgr [%d kalite]) uyuþturucusunu %s olarak deðiþtirdin.", karakteradi, UyusTipleri[index][Ad], gram, kalite, UyusTipleri[listitem][Ad]);
			}
			case 6: // Uyuþturucu gram düzenle
			{
				new yenigram = strval(inputtext);
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				if(!(0 <= yenigram <= MAX_UYUSTURUCU_GRAM)) 
				{
					format(liste, sizeof(liste), "Gram 0 ve "#MAX_UYUSTURUCU_GRAM" arasýnda olmalýdýr.\n%s (%dgr [%d kalite]) adlý uyuþturucunun gramýný deðiþtirmek için aþaðýdaki kutuya yeni gram deðerini girin:", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu düzenle", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET gram = %d WHERE ID = %d", yenigram, uid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s adlý oyuncunun %s (%dgr [%d kalite]) uyuþturucusunun gramýný %d olarak deðiþtirdin.", karakteradi, UyusTipleri[index][Ad], gram, kalite, yenigram);
			}
			case 7: // Uyuþturucu kalite düzenle
			{
				new yenikalite = strval(inputtext);
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				if(!(1 <= yenikalite <= MAX_UYUSTURUCU_KALITE)) 
				{
					format(liste, sizeof(liste), "Kalite 1 ve "#MAX_UYUSTURUCU_KALITE" arasýnda olmalýdýr.\n%s (%dgr [%d kalite]) adlý uyuþturucunun kalitesini deðiþtirmek için aþaðýdaki kutuya yeni kalite deðerini girin:", UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait uyuþturucu düzenle", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET kalite = %d WHERE ID = %d", yenikalite, uid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s adlý oyuncunun %s (%dgr [%d kalite]) uyuþturucusunun kalitesini %d olarak deðiþtirdin.", karakteradi, UyusTipleri[index][Ad], gram, kalite, yenikalite);
			}
			case 8: // Uyuþturucu sil
			{
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM uyusturucular WHERE ID = %d", uid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s adlý oyuncunun %s (%dgr [%d kalite]) uyuþturucusunu sildin.", karakteradi, UyusTipleri[index][Ad], gram, kalite);
			}
			case 9: // Uyuþturucu yeni paket oluþtur
			{
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				UyusturucuDialog[playerid][1] = 10;
				format(liste, sizeof(liste), "%s (%s) paketine %s koymak için uyuþturucu miktarýný girin.\nBu paket %d gram alabilir.", PaketTipleri[listitem][PaketAd], UyusTipleri[index][Ad], PaketTipleri[listitem][Boyut], PaketTipleri[listitem][MaxGram]);
				format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu için yeni paket oluþtur", UyusTipleri[index][Ad], gram, kalite);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
			}
			case 10: // Uyuþturucu yeni paket oluþtur onay
			{
				new paketsayi, paketgram = strval(inputtext);
				pindex = UyusturucuDialog[playerid][4];
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				cache_get_value_int(yukle, "paketsayi", paketsayi);
				if(paketgram <= 0)
				{
					format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu için yeni paket oluþtur", UyusTipleri[index][Ad], gram, kalite);
					format(liste, sizeof(liste), "Paket gramý 0'dan büyük olmalýdýr.\n%s (%s) paketine %s koymak için uyuþturucu miktarýný girin.\nBu paket %d gram alabilir.", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], PaketTipleri[pindex][MaxGram]);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(paketgram > PaketTipleri[pindex][MaxGram])
				{
					format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu için yeni paket oluþtur", UyusTipleri[index][Ad], gram, kalite);
					format(liste, sizeof(liste), "Bu paket bu kadar miktarý alamaz.\n%s (%s) paketine %s koymak için uyuþturucu miktarýný girin.\nBu paket %d gram alabilir.", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], PaketTipleri[pindex][MaxGram]);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(paketsayi >= MAX_OYUNCU_PAKET_SAYI) return SendErrorMessage(playerid, "Boþ paket slotun yok.");
				if(paketgram > gram) return SendErrorMessage(playerid, "Girdiðin miktar kadar uyuþturucun yok.");
				if(gram == paketgram)
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM uyusturucular WHERE ID = %d", uid);
					mysql_tquery(dbHandle, sorgu);
				}
				else
				{
					gram -= paketgram;
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET gram = %d WHERE ID = %d", gram, uid);
					mysql_tquery(dbHandle, sorgu);
				}
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "INSERT INTO paketler (sqlid, pindex, uindex, gram, kalite) VALUES (%d, %d, %d, %d, %d)", sqlid, pindex, index, paketgram, kalite);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "Paketiniz oluþturuldu.");
			}
			case 11: // Uyuþturucu mevcut pakete koy
			{
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uyusindex", index);
				cache_get_value_int(yukle, "uyusgram", gram);
				cache_get_value_int(yukle, "uyuskalite", kalite);
				format(liste, sizeof(liste), "Paket\tGram\tKalite\tKapasite\n");
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "pindex", pindex);
					cache_get_value_int(yukle, "gram", pgram);
					cache_get_value_int(yukle, "kalite", pkalite);
					format(liste, sizeof(liste), "%s%s [%c] (%s)\t%d\t%d\t%d / %d\n", liste, PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], pgram, pkalite, pgram, PaketTipleri[pindex][MaxGram]);
					yukle++;
				}
				format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu mevcut pakete koy", UyusTipleri[index][Ad], gram, kalite);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 12: // Uyuþturucu mevcut pakete koy
			{
				cache_get_value_int(yukle, "uyusindex", index);
				cache_get_value_int(yukle, "uyusgram", gram);
				cache_get_value_int(yukle, "uyuskalite", kalite);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "gram", pgram);
				format(liste, sizeof(liste), "%s (%s) paketine %s koymak için uyuþturucu gramýný girin.\n%d gram daha koyabilirsiniz.", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], PaketTipleri[pindex][MaxGram] - pgram);
				format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu mevcut pakete koy", UyusTipleri[index][Ad], gram, kalite);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
			}
			case 13: // Uyuþturucu mevcut pakete koy gram
			{
				new pid, gramkoy = strval(inputtext), paketuindex;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value_int(yukle, "uid", uid);
				cache_get_value_int(yukle, "uyusindex", index);
				cache_get_value_int(yukle, "uyusgram", gram);
				cache_get_value_int(yukle, "uyuskalite", kalite);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "uindex", paketuindex);
				cache_get_value_int(yukle, "gram", pgram);
				cache_get_value_int(yukle, "kalite", pkalite);
				if(gramkoy <= 0) 
				{
					format(liste, sizeof(liste), "Gram 0'dan büyük olmalýdýr.\n%s (%s) paketine %s koymak için uyuþturucu gramýný girin.\n%d gram daha koyabilirsiniz.", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], PaketTipleri[pindex][MaxGram] - pgram);
					format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu mevcut pakete koy", UyusTipleri[index][Ad], gram, kalite);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(gramkoy > PaketTipleri[pindex][MaxGram] || (pgram + gramkoy) > PaketTipleri[pindex][MaxGram])
				{
					format(liste, sizeof(liste), "Girilen gram paket kapasitesini aþýyor.\n%s (%s) paketine %s koymak için uyuþturucu gramýný girin.\n%d gram daha koyabilirsiniz.", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], PaketTipleri[pindex][MaxGram] - pgram);
					format(baslik, sizeof(baslik), "%s (%dgr [%d kalite]) uyuþturucu mevcut pakete koy", UyusTipleri[index][Ad], gram, kalite);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(paketuindex != index) return SendErrorMessage(playerid, "Bu pakete farklý tür uyuþturucu koyamazsýn.");
				if(gramkoy > gram) return SendErrorMessage(playerid, "Girdiðin miktar kadar uyuþturucun yok.");

				new yenikalite = ((pgram * pkalite) + (gramkoy * kalite)) / (pgram + gramkoy);
				pgram += gramkoy;
				if(gram == gramkoy)
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM uyusturucular WHERE ID = %d", uid);
					mysql_tquery(dbHandle, sorgu);
				}
				else
				{
					gram -= gramkoy;
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE uyusturucular SET gram = %d WHERE ID = %d", gram, uid);
					mysql_tquery(dbHandle, sorgu);
				}
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET gram = %d, kalite = %d WHERE ID = %d", pgram, yenikalite, pid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s paketine %s %dgr uyuþturucu koydun.", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gramkoy);
			}
			case 14: // Oyuncu uyuþturucu at
			{
				cache_get_value_int(yukle, "ID", uid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM uyusturucular WHERE ID = %d", uid);
				mysql_tquery(dbHandle, sorgu);
				SendServerMessage(playerid, "%s (%dgr [%d kalite]) uyuþturucu yere atýldý.", UyusTipleri[index][Ad], gram, kalite);
			}
			case 15: // Paket detay iþlem
			{
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				format(liste, sizeof(liste), " \t \n");
				format(liste, sizeof(liste), "%s%s %s\t%dgr [%d kalite]\n", liste, PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
				format(liste, sizeof(liste), "%s \t \n", liste);
				format(liste, sizeof(liste), "%sPaketten al\t \n", liste);
				format(liste, sizeof(liste), "%sPaketi yere býrak\t \n", liste);
				format(liste, sizeof(liste), "%sBaþkasýna ver\t \n", liste);
				format(liste, sizeof(liste), "%sAraca koy\t \n", liste);
				format(baslik, sizeof(baslik), "%s adlý karaktere ait paket", karakteradi);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Seç", "Kapat");
			}
			case 16: // Paket detay iþlem
			{
				new pid;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				if(PlayerInfo[playerid][PaketVer][0] != INVALID_PLAYER_ID && PlayerInfo[playerid][PaketVer][1] == pid)
					return SendErrorMessage(playerid, "Bu paket için istek gönderilmiþ, iþlem yapamazsýn.");
				if(!strcmp(inputtext, "Paketten al"))
				{
					UyusturucuDialog[playerid][1] = 17;
					format(liste, sizeof(liste), "%s paketten %s (%dgr [%d kalite]) adlý uyuþturucu almak için gram girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paketten al", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
				}
				else if(!strcmp(inputtext, "Paketi yere býrak"))
				{
					new label[60], objeid, Float: x, Float: y, Float: z, array[2];
					GetPlayerPos(playerid, x, y, z);
					format(label, 60, "%s [%s]", PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut][0]);
					objeid = CreateDynamicObject(PaketTipleri[pindex][PaketObje], x, y, z - 1, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
					array[0] = 85;
					array[1] = pid;
					Streamer_SetArrayData(STREAMER_TYPE_OBJECT, objeid, E_STREAMER_EXTRA_ID, array);
					SendServerMessage(playerid, "%s adlý paketi yere býraktýn.", PaketTipleri[pindex][PaketAd]);
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET olusturan = '%e', sqlid = 0, x = %f, y = %f, z = %f, vw = %d, interior = %d WHERE ID = %d", GetName(playerid), x, y, z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), pid);
					mysql_tquery(dbHandle, sorgu);
				}
				else if(!strcmp(inputtext, "Baþkasýna ver"))
				{
					UyusturucuDialog[playerid][1] = 18;
					format(liste, sizeof(liste), "%s paketini içindeki %s (%dgr [%d kalite]) uyuþturucu ile baþkasýna vermek için karakter adý veya ID girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paket baþkasýna ver", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
				}
				else if(!strcmp(inputtext, "Araca koy"))
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Bu iþlemi yapabilmek için bir araçta olmalýsýn.");
					new aracpaketsayi, vid = GetPlayerVehicleID(playerid);
					cache_get_value_int(yukle, "aracpaketsayi", aracpaketsayi);
					if(Arac_Model(VehicleInfo[vid][carModel]) == VEHICLE_TYPE_BIKE || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "Bu iþlemi bir aracýn sürücü koltuðundayken yapabilirsin.");
					if(Arac_Sahip(playerid, vid, false) == 0) return SendErrorMessage(playerid, "Sana ait olmayan araçlarda bunu yapamazsýn.");
					if(aracpaketsayi >= MAX_ARAC_PAKET_SAYI) return SendErrorMessage(playerid, "Bu aracýn boþ paket slotu yok.");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET sqlid = 0, aracsqlid = %d WHERE ID = %d", VehicleInfo[vid][carID], pid);
					mysql_tquery(dbHandle, sorgu);
					SendServerMessage(playerid, "%s paketini %s model aracýna koydun.", PaketTipleri[pindex][PaketAd], GetVehicleModelName(VehicleInfo[vid][carModel]));
				}
			}
			case 17: // Paketten al
			{
				new pid, gramal = strval(inputtext), uyusturucusayi;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				cache_get_value_int(yukle, "uyusturucusayi", uyusturucusayi);
				if(gramal <= 0)
				{
					format(liste, sizeof(liste), "Gram 0'dan büyük olmalýdýr.\n%s paketten %s (%dgr [%d kalite]) adlý uyuþturucu almak için gram girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paketten al", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(gramal > gram)
				{
					format(liste, sizeof(liste), "Pakette girilen gramda uyuþturucu yok.\n%s paketten %s (%dgr [%d kalite]) adlý uyuþturucu almak için gram girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paketten al", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(uyusturucusayi >= MAX_OYUNCU_UYUSTURUCU_SAYI) return SendErrorMessage(playerid, "Boþ uyuþturucu slotun yok.");
				if(gramal == gram)
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM paketler WHERE ID = %d", pid);
					mysql_tquery(dbHandle, sorgu);
				}
				else
				{
					gram -= gramal;
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET gram = %d WHERE ID = %d", gram, pid);
					mysql_tquery(dbHandle, sorgu);
				}
				OyuncuUyusturucuVer(sqlid, index, gramal, kalite);
				SendServerMessage(playerid, "%s paketinden %s %dgr uyuþturucu aldýn.", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gramal);
			}
			case 18: // Paketi baþkasýna ver
			{
				new pid, hedefid;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value(yukle, "name", karakteradi, 24);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "gram", gram);
				cache_get_value_int(yukle, "kalite", kalite);
				if(sscanf(inputtext, "u", hedefid))
				{
					format(liste, sizeof(liste), "Geçersiz karakter adý veya ID girdin.\n%s paketini içindeki %s (%dgr [%d kalite]) uyuþturucu ile baþkasýna vermek için karakter adý veya ID girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paket baþkasýna ver", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(!IsPlayerConnected(hedefid) || !pTemp[hedefid][pLogged])
				{
					format(liste, sizeof(liste), "Bu kiþi oyunda deðil veya giriþ yapmamýþ.\n%s paketini içindeki %s (%dgr [%d kalite]) uyuþturucu ile baþkasýna vermek için karakter adý veya ID girin:", PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
					format(baslik, sizeof(baslik), "%s adlý karaktere ait paket baþkasýna ver", karakteradi);
					Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_INPUT, baslik, liste, "Gir", "Kapat");
					return 1;
				}
				if(hedefid == playerid) return SendErrorMessage(playerid, "Kendine paket veremezsin.");
				if(PlayerInfo[hedefid][PaketVer][0] != INVALID_PLAYER_ID && PlayerInfo[hedefid][PaketVer][1] == pid)
					return SendErrorMessage(playerid, "Bu kiþiye zaten paket isteði göndermiþsin.");
				if(PlayerInfo[hedefid][PaketVer][0] != INVALID_PLAYER_ID && PlayerInfo[hedefid][PaketVer][1] != pid)
					return SendErrorMessage(playerid, "Bu kiþiye baþkasý paket isteði göndermiþ, istek gönderemezsin daha sonra tekrar deneyin.");
				if(!PlayerNearPlayer(4.0, playerid, hedefid)) return SendErrorMessage(playerid, "Girdiðin oyuncuya yakýn deðilsin.");
				PlayerInfo[playerid][PaketVer][0] = hedefid;
				PlayerInfo[hedefid][PaketVer][0] = playerid;
				PlayerInfo[playerid][PaketVer][1] = pid;
				PlayerInfo[hedefid][PaketVer][1] = pid;
				SendClientMessageEx(hedefid, COLOR_YELLOW, "%s, sana %s(%s, %d gram %d kalite) vermek istiyor. (/kabulet & /reddet paket)", GetNameEx(playerid), PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
				SendClientMessageEx(playerid, COLOR_YELLOW, "%s'e %s(%s, %d gram %d kalite) verme isteði gönderdin.", GetNameEx(hedefid), PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], gram, kalite);
			}
			case 19: // Paket istek kabul
			{
				new pid;
				cache_get_value_int(yukle, "ID", pid);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET sqlid = %d WHERE ID = %d", sqlid, pid);
				mysql_tquery(dbHandle, sorgu);
			}
			case 20: // Paket yerden al
			{
				new pid;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "pindex", pindex);
				if(listitem) SendServerMessage(playerid, "Yerdeki %s paketine el koydun.", PaketTipleri[pindex][PaketAd]);
				else SendServerMessage(playerid, "Yerden %s paketini aldýn.", PaketTipleri[pindex][PaketAd]);
				if(listitem) mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM paketler WHERE ID = %d", pid);
				else mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET sqlid = %d, x = 0.0, y = 0.0, z = 0.0, vw = 0, interior = 0 WHERE ID = %d", sqlid, pid); 
				mysql_tquery(dbHandle, sorgu);
			}
			case 21: // Uyuþturucular chat göster
			{
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "gram", gram);
					cache_get_value_int(yukle, "kalite", kalite);
					format(liste, sizeof(liste), "%s%s (%d gram, %d kalite) | ", liste, UyusTipleri[index][Ad], gram, kalite);
					yukle++;
				}
				SendServerMessage(playerid, "%s", liste);
			}
			case 22: // Paketler chat göster
			{
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "pindex", pindex);
					cache_get_value_int(yukle, "gram", pgram);
					cache_get_value_int(yukle, "kalite", pkalite);
					format(liste, sizeof(liste), "%s[%c] %s: %s (%d gram, %d kalite) | ", liste, PaketTipleri[pindex][Boyut], PaketTipleri[pindex][PaketAd], UyusTipleri[index][Ad], pgram, pkalite);
					yukle++;
				}
				SendServerMessage(playerid, "%s", liste);
			}
			case 23: // Araç paketleri
			{
				new model, aracsqlid, paketsayi;
				cache_get_value_int(yukle, "model", model);
				cache_get_value_int(yukle, "aracsqlid", aracsqlid);
				cache_get_value_int(yukle, "paketsayi", paketsayi);
				if(paketsayi >= MAX_OYUNCU_PAKET_SAYI) return SendErrorMessage(playerid, "Boþ paket slotun yok.");
				format(liste, sizeof(liste), "Paket\tGram\tKalite\n");
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "uindex", index);
					cache_get_value_int(yukle, "pindex", pindex);
					cache_get_value_int(yukle, "gram", pgram);
					cache_get_value_int(yukle, "kalite", pkalite);
					format(liste, sizeof(liste), "%s%s [%c] (%s)\t%d\t%d\n", liste, PaketTipleri[pindex][PaketAd], PaketTipleri[pindex][Boyut], UyusTipleri[index][Ad], pgram, pkalite);
					yukle++;
				}
				format(baslik, sizeof(baslik), "%s [SQLID: %d] model araca ait paketler", GetVehicleModelName(model), aracsqlid);
				Dialog_Show(playerid, DialogUyusturucu, DIALOG_STYLE_TABLIST_HEADERS, baslik, liste, "Al", "Kapat");
			}
			case 24: // Araç paket al
			{
				new model, aracsqlid, pid;
				cache_get_value_int(yukle, "ID", pid);
				cache_get_value_int(yukle, "model", model);
				cache_get_value_int(yukle, "aracsqlid", aracsqlid);
				cache_get_value_int(yukle, "pindex", pindex);
				cache_get_value_int(yukle, "uindex", index);
				cache_get_value_int(yukle, "gram", pgram);
				cache_get_value_int(yukle, "kalite", pkalite);
				if((OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE) && PlayerInfo[playerid][pOnDuty])
				{
					SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[EL KOYMA] %s, %d SQL ID'li araçtaki uyuþturucuya el koydu. (%s - %d gram - %d kalite)", GetNameEx(playerid), aracsqlid, UyusTipleri[index][Ad], pgram, pkalite);
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM paketler WHERE ID = %d", pid);
				}
				else
				{
					SendServerMessage(playerid, "%s [SQLID: %d] model araçtan %s paketi aldýn.", GetVehicleModelName(model), aracsqlid, PaketTipleri[pindex][PaketAd]);
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "UPDATE paketler SET aracsqlid = 0, sqlid = %d WHERE ID = %d", PlayerInfo[playerid][pID], pid);
				}
				mysql_tquery(dbHandle, sorgu);
			}
		}
	}
	else
	{
		if(islem == 1) SendErrorMessage(playerid, "Uyuþturucu bulunamadý.");
		else if(islem == 2 || islem == 23) SendErrorMessage(playerid, "Paket bulunamadý.");
	}
	return 1;
}

Dialog:DialogUyusturucu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new sorgu[600];
		switch(UyusturucuDialog[playerid][1])
		{
			case 0: // Oyuncu uyuþturucu seçenek
			{
				if(!strcmp(inputtext, "Uyuþturucular"))
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d", sorgu, UyusturucuDialog[playerid][0]);
					mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 1, UyusturucuDialog[playerid][2], 0, inputtext);
				}
				else if(!strcmp(inputtext, "Paketler"))
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d", sorgu, UyusturucuDialog[playerid][0]);
					mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 2, UyusturucuDialog[playerid][2], 0, inputtext);
				}
			}
			case 1: // Oyuncu uyuþturucular
			{
				UyusturucuDialog[playerid][3] = listitem;
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], listitem);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 3, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 2: // Oyuncu paketler
			{
				UyusturucuDialog[playerid][3] = listitem;
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], listitem);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 15, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 3: // Oyuncu uyuþturucu iþlem
			{
				if(!strcmp(inputtext, "Paketle") || !strcmp(inputtext, "Birleþtir"))
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT COUNT(*) FROM paketler WHERE sqlid = uyusturucular.sqlid LIMIT 1) as paketsayi");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "%s, (SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name", sorgu);
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				}
				else
				{
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
					mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				}
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 4, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 5: // Oyuncu uyuþturucu tipini deðiþtir
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 5, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 6: // Oyuncu uyuþturucu gram düzenle
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 6, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 7: // Oyuncu uyuþturucu kalite düzenle
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 7, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 8: // Oyuncu uyuþturucu sil
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 8, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 9: // Oyuncu uyuþturucu yeni paket oluþtur
			{
				UyusturucuDialog[playerid][4] = listitem;
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 9, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 10: // Oyuncu uyuþturucu yeni paket oluþtur
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT COUNT(*) FROM paketler WHERE sqlid = uyusturucular.sqlid LIMIT 1) as paketsayi");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "%s, (SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name", sorgu);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 10, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 11: // Oyuncu uyuþturucu mevcut pakete koy
			{
				UyusturucuDialog[playerid][4] = listitem;
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT paketler.*, uyusturucular.uindex as uyusindex, uyusturucular.gram as uyusgram, uyusturucular.kalite as uyuskalite, %s FROM paketler LEFT JOIN uyusturucular ON uyusturucular.ID = %d WHERE paketler.sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][5], UyusturucuDialog[playerid][0], listitem);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 12, UyusturucuDialog[playerid][2], 0, inputtext);
			}
			case 12: // Oyuncu uyuþturucu mevcut pakete koy
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT paketler.*, uyusturucular.ID as uid, uyusturucular.uindex as uyusindex, uyusturucular.gram as uyusgram, uyusturucular.kalite as uyuskalite, %s FROM paketler LEFT JOIN uyusturucular ON uyusturucular.ID = %d WHERE paketler.sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][5], UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][4]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 13, UyusturucuDialog[playerid][2], 0, inputtext);
			}
			case 14: // Oyuncu uyuþturucu at
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 14, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 15: // Oyuncu paket detay
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT COUNT(*) FROM cars WHERE id = paketler.aracsqlid LIMIT 1) as aracpaketsayi");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "%s, (SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name", sorgu);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 16, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 17: // Oyuncu paketten al
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT COUNT(*) FROM uyusturucular WHERE sqlid = paketler.sqlid LIMIT 1) as uyusturucusayi");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "%s, (SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name", sorgu);
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 17, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 18: // Oyuncu paketi baþkasýna ver
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 18, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 23: // Araç paketleri
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT model FROM cars WHERE id = paketler.aracsqlid LIMIT 1) as model");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE aracsqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], listitem);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 24, UyusturucuDialog[playerid][2], 0, inputtext);
			}
			case 25: // Oyuncu uyuþturucu teslim
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = uyusturucular.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM uyusturucular WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 25, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
			case 26: // Oyuncu paket teslim
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "(SELECT name FROM users WHERE id = paketler.sqlid LIMIT 1) as name");
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT *, %s FROM paketler WHERE sqlid = %d LIMIT %d, 1", sorgu, UyusturucuDialog[playerid][0], UyusturucuDialog[playerid][3]);
				mysql_tquery(dbHandle, sorgu, "UyusturucuSorgu", "ddddds", playerid, UyusturucuDialog[playerid][0], 26, UyusturucuDialog[playerid][2], listitem, inputtext);
			}
		}
	}
	return 1;
}

CMD:u(playerid) return pc_cmd_uyusturucularim(playerid);
CMD:uyusturucularim(playerid)
{
	OyuncuUyusturucuGoster(playerid, PlayerInfo[playerid][pID], 0);
	return 1;
}

CMD:paketsil(playerid)
{
    if(!IsPlayerFactionPolice(playerid)) return false;
	new Float: x, Float: y, Float: z, obje[2], Text3D: label[2];
	GetPlayerPos(playerid, x, y, z);
	Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, obje, sizeof(obje), 3.0, GetPlayerVirtualWorld(playerid));
	Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_3D_TEXT_LABEL, label, sizeof(label), 3.0, GetPlayerVirtualWorld(playerid));
	if(IsValidDynamicObject(obje[0]))
	{
		new array[2];
		Streamer_GetArrayData(STREAMER_TYPE_OBJECT, obje[0], E_STREAMER_EXTRA_ID, array);
		if(array[0] != 85) return SendErrorMessage(playerid, "Pakete yeterince yakýn deðilsiniz.");
		new sorgu[80];
		DestroyDynamicObject(obje[0]);
		mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM paketler WHERE ID = %d", array[1]);
		mysql_tquery(dbHandle, sorgu);
	}
	return 1;
}

TohumYakin(playerid, Float: mesafe = 3.0)
{
	new id, Float: OyuncuKonum, Float: mesafe2 = 9999.0;
	for(new tohumid = 1; tohumid < MAX_TOHUM; tohumid++)
	{
		if(Tohum[tohumid][tohumSahip] < 0) continue;
		OyuncuKonum = GetPlayerDistanceFromPoint(playerid, Tohum[tohumid][tohumX], Tohum[tohumid][tohumY], Tohum[tohumid][tohumZ]);
		if(OyuncuKonum > mesafe) continue;
		if(OyuncuKonum <= mesafe2 && GetPlayerVirtualWorld(playerid) == Tohum[tohumid][tohumVW] && GetPlayerInterior(playerid) == Tohum[tohumid][tohumInt])
		{
			mesafe2 = OyuncuKonum;
			id = tohumid;
			break;
		}
	}
	return id;
}

TohumlariGuncelle()
{
	for(new i = 0; i < MAX_TOHUM; i++)
	{
		if(Tohum[i][tohumSahip] >= 0)
		{
			if(Tohum[i][tohumSure] <= 361) Tohum[i][tohumSure]++;
			TohumGuncelle(i);
		}
	}
}

stock TohumGuncelle(tohumID)
{
	new mesaj[120];

	if(Tohum[tohumID][tohumSure] <= 60) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{AA0000}yeni ekildi");
	else if(Tohum[tohumID][tohumSure] > 60 && Tohum[tohumID][tohumSure] < 121) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{FF6347}filizleniyor");
	else if(Tohum[tohumID][tohumSure] > 120 && Tohum[tohumID][tohumSure] < 181) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{FFFF00}olgunlaþýyor");
	else if(Tohum[tohumID][tohumSure] > 180 && Tohum[tohumID][tohumSure] < 241) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{50C878}olgun");
	else if(Tohum[tohumID][tohumSure] > 240 && Tohum[tohumID][tohumSure] < 301) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{FFFF00}solgunlaþýyor");
	else if(Tohum[tohumID][tohumSure] > 300 && Tohum[tohumID][tohumSure] < 361) format(mesaj, sizeof(mesaj), "[Marijuana Tohumu]\n{Ff6347}ölüyor");
	else format(mesaj, sizeof(mesaj), "{AA0000}solmuþ tohum");

	UpdateDynamic3DTextLabelText(Tohum[tohumID][tohumLabel], COLOR_WHITE, mesaj);
	return 1;
}

CMD:tohum(playerid, params[])
{
	new secenek[20], sorgu[650], tohumid = TohumYakin(playerid);

	if(sscanf(params, "s[20]", secenek))
	{
		SendHelpMessage(playerid, "/tohum [seçenek]");
		SendHelpMessage(playerid, "topla, ek");
		if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE || OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_CITY) SendHelpMessage(playerid, "temizle");
		if(PlayerInfo[playerid][pAdmin] >= HIGH_ADMIN_LEVEL) SendHelpMessage(playerid, "atemizle [admin komutu]");
		return 1;
	}
	if(!strcmp(secenek, "atemizle"))
	{
		if(PlayerInfo[playerid][pAdmin] < HIGH_ADMIN_LEVEL) return SendErrorMessage(playerid, "Bu komutu kullanmak için Admin 5 ve üstü yetkiye sahip olmalýsýnýz.");
		if(!tohumid) return SendErrorMessage(playerid, "Yakýnýnýzda silinebilecek bir tohum bulunmuyor.");
		SendAdmMessage("[UYUÞTURUCU] %s, %d ID'li tohumu sildi. (Sahip: %s)", PlayerInfo[playerid][pUsername], tohumid, GetCharacterName(Tohum[tohumid][tohumSahip]));
		TohumSil(tohumid);
	}
	else if(!strcmp(secenek, "temizle"))
	{
		if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) != FACTION_POLICE && OlusumTipGetir(PlayerInfo[playerid][pFaction]) != FACTION_CITY) return SendErrorMessage(playerid, "Bu komutu LSPD, LSSD ve FBI üyeleri kullanabilir.");
		if(!PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Bu komutu kullanmak için birlik iþbaþýnda olmalýsýnýz.");
		if(!tohumid) return SendErrorMessage(playerid, "Yakýnýnýzda silinebilecek bir tohum bulunmuyor.");
		SendFactionMessage(PlayerInfo[playerid][pFaction], COLOR_LSPD, "[BÝRLÝK] %s, %d ID'li tohuma el koydu.", GetNameEx(playerid), tohumid);
		TohumSil(tohumid);
	}
	else if(!strcmp(secenek, "suredoldur"))
	{
		if(PlayerInfo[playerid][pAdmin] < HIGH_ADMIN_LEVEL) return SendNotAdmin(playerid);
		if(!tohumid) return SendErrorMessage(playerid, "Yakýnýnýzda bir tohum bulunmuyor.");
		Tohum[tohumid][tohumSure] = 300;
	}
	else if(!strcmp(secenek, "topla"))
	{
		if(!tohumid) return SendErrorMessage(playerid, "Herhangi bir tohuma yakýn deðilsiniz.");
		if(Tohum[tohumid][tohumSahip] != PlayerInfo[playerid][pID]) return SendErrorMessage(playerid, "Bu tohumu siz ekmemiþsiniz.");
		if(OyuncuUyusturucuSayi(PlayerInfo[playerid][pID]) >= MAX_OYUNCU_UYUSTURUCU_SAYI) return SendErrorMessage(playerid, "Boþ uyuþturucu slotun yok.");
		new dakika = Tohum[tohumid][tohumSure], gram, kalite;
		if(dakika < 60) return SendErrorMessage(playerid, "Bu tohum büyümemiþ.");
		if(dakika > 360)
		{
			SendServerMessage(playerid, "Bu tohum çürümüþ.");
			TohumSil(tohumid);
			return 1;
		}
		switch(dakika)
		{
			case 61..120: // filizleniyor
			{	
				gram = 4;
				kalite = randomEx(0, 30);
			}
			case 121..180: // olgunlaþýyor
			{	
				gram = 8;
				kalite = randomEx(25, 65);
			}
			case 181..240: // olgun
			{	
				gram = 15;
				kalite = randomEx(60, 100);
			}
			case 241..300: // solgunlaþýyor
			{	
				gram = 8;
				kalite = randomEx(25, 65);
			}
			case 301..360: // ölüyor
			{	
				gram = 4;
				kalite = randomEx(25, 65);
			}
		}
		OyuncuUyusturucuVer(PlayerInfo[playerid][pID], Tohum[tohumid][tohumHammadde], gram, kalite);
		SendServerMessage(playerid, "Yerden %s %dgr %d kalite topladýn.", UyusTipleri[Tohum[tohumid][tohumHammadde]][Ad], gram, kalite);
		TohumSil(tohumid);
	}
	else if(!strcmp(secenek, "ek"))
	{
		if(PlayerInfo[playerid][pHammadde] < 5) return SendErrorMessage(playerid, "Bunun için üzerinde yeterli hammadde yok.");
		//if(!Olusum[PlayerInfo[playerid][pFaction]][oTohumIzin]) return SendErrorMessage(playerid, "Bulunduðunuz oluþumun uyuþturucu izin statüsü bulunmuyor.");
		new tohumID = bosTohumID(), tohumsayi = 0;
		if(tohumID >= MAX_TOHUM) return SendErrorMessage(playerid, "Tohum oluþturulamadý, tekrar deneyin.");
		
	    for(new tohumkontrol = 1; tohumkontrol < MAX_TOHUM; tohumkontrol++)
	    {
	        if(Tohum[tohumkontrol][tohumSahip] == PlayerInfo[playerid][pID])
			tohumsayi++;
		}

		if(tohumsayi >= 3) return SendErrorMessage(playerid, "Ayný anda en fazla '3 adet' tohum ekebilirsiniz.");

		new mesaj[200];
		Tohum[tohumID][tohumSahip] = PlayerInfo[playerid][pID];
		Tohum[tohumID][tohumHammadde] = 8;
		Tohum[tohumID][tohumVW] = GetPlayerVirtualWorld(playerid);
		Tohum[tohumID][tohumInt] = GetPlayerInterior(playerid);
		Tohum[tohumID][tohumSure] = 0;
		GetPlayerPos(playerid, Tohum[tohumID][tohumX], Tohum[tohumID][tohumY], Tohum[tohumID][tohumZ]);
		mysql_format(dbHandle, sorgu, sizeof(sorgu), "INSERT INTO tohumlar (tohumID, hammadde, kalansure, sahip, x, y, z, vw, interior) VALUES (%d, 5, %d, %d, %f, %f, %f, %d, %d)", tohumID, Tohum[tohumID][tohumSure], Tohum[tohumID][tohumSahip], Tohum[tohumID][tohumX], Tohum[tohumID][tohumY], Tohum[tohumID][tohumZ], Tohum[tohumID][tohumVW], Tohum[tohumID][tohumInt]);
		mysql_tquery(dbHandle, sorgu);
		format(mesaj, sizeof(mesaj), "Marijuana tohumu\nDurum: {F82D02} Filizlenme (Toplanamaz)");
		Tohum[tohumID][tohumObjeID] = CreateDynamicObject(TOHUM_OBJE, Tohum[tohumID][tohumX], Tohum[tohumID][tohumY], Tohum[tohumID][tohumZ] - 0.4, 0.0, 0.0, 0.0, Tohum[tohumID][tohumVW], Tohum[tohumID][tohumInt]);
		Tohum[tohumID][tohumLabel] = CreateDynamic3DTextLabel(mesaj, COLOR_WHITE, Tohum[tohumID][tohumX], Tohum[tohumID][tohumY], Tohum[tohumID][tohumZ] - 0.4, 7.0);
		SendServerMessage(playerid, "Marijuana tohumu ektin.");
		PlayerInfo[playerid][pHammadde] -= 5;
		Save_User(playerid);
	}
	return 1;
}

// CMD:tohum(playerid, params[])
// {
// 	new secim[20];
// 	if(sscanf(params, "s[20]", secim))
// 	{
// 		SendHelpMessage(playerid, "/tohum [seçim]");
// 		if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) == FACTION_POLICE)
// 			SendHelpMessage(playerid, "topla - ek - temizle");
// 		else if(PlayerInfo[playerid][pAdmin] >= YETKI_GENELYETKILI)
// 			SendHelpMessage(playerid, "topla - ek - atemizle");
// 		else SendHelpMessage(playerid, "topla - ek");
// 		return 1;
// 	}
// 	if(!strcmp(secim, "atemizle"))
// 	{
// 		if(PlayerInfo[playerid][pAdmin] < YETKI_GENELYETKILI) return SendErrorMessage(playerid, "Bu komutu kullanmak için admin olmalýsýnýz.");
// 		new tohumid = TohumYakin(playerid), sorgu[120];
// 		if(!tohumid) return SendErrorMessage(playerid, "Herhangi bir tohuma yakýn deðilsiniz.");
// 		mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT * FROM tohumlar WHERE tohumID = %d", tohumid);
// 		mysql_tquery(dbHandle, sorgu, "TohumSorgu", "dddds", playerid, tohumid, 2, 1, "");
// 	}
// 	else if(!strcmp(secim, "temizle"))
// 	{
// 		if(OlusumTipGetir(PlayerInfo[playerid][pFaction]) != FACTION_POLICE) return SendErrorMessage(playerid, "Polis deðilsin.");
// 		if(!PlayerInfo[playerid][pOnDuty]) return SendErrorMessage(playerid, "Bu komutu kullanmak için iþbaþýnda olmalýsýnýz.");
// 		new tohumid = TohumYakin(playerid), sorgu[120];
// 		if(!tohumid) return SendErrorMessage(playerid, "Herhangi bir tohuma yakýn deðilsiniz.");
// 		mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT * FROM tohumlar WHERE tohumID = %d", tohumid);
// 		mysql_tquery(dbHandle, sorgu, "TohumSorgu", "dddds", playerid, tohumid, 2, 0, "");
// 	}

// 	return 1;
// }

TohumSil(tohumid)
{
	new sorgu[120];
	mysql_format(dbHandle, sorgu, sizeof(sorgu), "SELECT * FROM tohumlar WHERE tohumID = %d", tohumid);
	mysql_tquery(dbHandle, sorgu, "TohumSorgu", "dddds", 0, tohumid, 1, 0, "");
}

forward TohumSorgu(playerid, tohumid, islem, listitem, inputtext[]);
public TohumSorgu(playerid, tohumid, islem, listitem, inputtext[])
{
	new veriler = cache_num_rows(), yukle, sorgu[300];
	if(veriler)
	{
		switch(islem)
		{
			case 0: // Tohumlarý yükle
			{
				while(yukle < veriler)
				{
					cache_get_value_int(yukle, "tohumID", tohumid);
					cache_get_value_int(yukle, "hammadde", Tohum[tohumid][tohumHammadde]);
					cache_get_value_int(yukle, "kalansure", Tohum[tohumid][tohumSure]);
					cache_get_value_int(yukle, "sahip", Tohum[tohumid][tohumSahip]);
					cache_get_value_float(yukle, "x", Tohum[tohumid][tohumX]);
					cache_get_value_float(yukle, "y", Tohum[tohumid][tohumY]);
					cache_get_value_float(yukle, "z", Tohum[tohumid][tohumZ]);
					cache_get_value_int(yukle, "vw", Tohum[tohumid][tohumVW]);
					cache_get_value_int(yukle, "interior", Tohum[tohumid][tohumInt]);
					Tohum[tohumid][tohumObjeID] = CreateDynamicObject(TOHUM_OBJE, Tohum[tohumid][tohumX], Tohum[tohumid][tohumY], Tohum[tohumid][tohumZ] - 0.4, 0.0, 0.0, 0.0, Tohum[tohumid][tohumVW], Tohum[tohumid][tohumInt]);
					Tohum[tohumid][tohumLabel] = CreateDynamic3DTextLabel(".", COLOR_WHITE, Tohum[tohumid][tohumX], Tohum[tohumid][tohumY], Tohum[tohumid][tohumZ] - 0.4, 7.0);
					TohumGuncelle(tohumid);
					yukle++;
				}
				printf("[TOHUMLAR] Toplam: %d", veriler);
			}
			case 1: // Tohum sil
			{
				mysql_format(dbHandle, sorgu, sizeof(sorgu), "DELETE FROM tohumlar WHERE tohumID = %d", tohumid);
				mysql_tquery(dbHandle, sorgu);
				Tohum[tohumid][tohumSahip] = -1;
				Tohum[tohumid][tohumX] = Tohum[tohumid][tohumY] = Tohum[tohumid][tohumZ] = 0.0;
				DestroyDynamicObject(Tohum[tohumid][tohumObjeID]);
				DestroyDynamic3DTextLabelEx(Tohum[tohumid][tohumLabel]);
			}
		}
	}
	else
	{
		if(islem == 0) print("[TOHUMLAR] Toplam: Yok");
	}
	return 1;
}