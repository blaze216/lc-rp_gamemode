CMD:genelyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Genel");
	SCM(playerid, COLOUR_ALTO, "/envanter, /yerdenal, /arac, /paraver, /ehliyetal, /ehliyetgoster, /gps, /graffiti");
	SCM(playerid, COLOUR_ALTO, "/giris, /cikis, /ev, /isyeri, /admins, /helpers, /ceset, /ustara, /animasyonlar, /sonreklamlar");
	SCM(playerid, COLOUR_ALTO, "/rapor, /soru, /kiyafetlerim, /aksesuar, /cpsifirla, /mikrofon, /bugkurtar, /reklamlar");
    SCM(playerid, COLOUR_ALTO, "/reklam, /plakakontrol, /zar, /saat, /fare, /sonarac, /bagis, /evgps, /isyerigps");

	return 1;
}

alias:uyusturucuyardim("uyardim");
CMD:uyusturucuyardim(playerid)
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Uyuþturucu");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/u ya da /uyusturucularim: {FFFFFF}uyuþturucularýný yönetmeye yarar");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/tohumtemizle: {FFFFFF}saksýda ekili tohumlara el koymaya yarar (lspd komutu)");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/paketsil: {FFFFFF}yerdeki uyuþturucu paketlerine el koyar (lspd)");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/arac paketler: {FFFFFF}araçtaki uyuþturucularý görmeye yarar");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/yerdenal: {FFFFFF}yerdeki paketi almanýza yarar");
	
	if(PlayerInfo[playerid][pAdmin] >= ADMIN_LEVEL_1)
	
	{
		SendClientMessageEx(playerid, COLOR_YELLOW, "Yönetici Komutlarý:");
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/atohumtemizle:{FFFFFF} ekilmiþ bir tohumun ürünlerine el koymaya yarar");
	}
	
	if(PlayerInfo[playerid][pAdmin] > ADMIN_LEVEL_1)
	{
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/auver:{FFFFFF} yönetici komutuyla uyuþturucu vermeye yarar");
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/uyusturucuduzenle:{FFFFFF} bir kullanýcýnýn uyuþturucusunu düzenlemeye yarar");
	}
	return 1;
}

CMD:silahyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Silah");
	SCM(playerid, COLOUR_ALTO, "/silah: tüm silah komutlarý");
	return 1;
}

CMD:evyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Ev");
	SCM(playerid, COLOUR_ALTO, "/ev, /evmenu, /ev satinal, /ddo, /dshout");

	return 1;
}

alias:isyeriyardim("mekanyardim");
CMD:isyeriyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Ýþyeri");
	SCM(playerid, COLOUR_ALTO, "/isyeri veya /mekan, /mekan satinal, /mekanmenu");

	return 1;
}

CMD:ayarlaryardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Ayarlar");
	SCM(playerid, COLOUR_ALTO, "/ayarlar, /tog");

	return 1;
}

CMD:telsizyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Telsiz");
	SCM(playerid, COLOUR_ALTO, "/kanal, /slotayarla, /telsizsifre, /telsizsifredegis, /telsizuyeler, /kanaldanat, /t-/r, /rlow, /rr, /rrlow");

	return 1;
}

CMD:meslekyardim(playerid, params[])
{
	if (PlayerInfo[playerid][pJob] == JOBLESS)	return SendErrorMessage(playerid, "Herhangi bir iþin yok. /gps ile yakýndaki iþlere bakabillirsin.");

	if(PlayerInfo[playerid][pJob] == JOB_TAXI)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yardým, Taksicilik Mesleði");
	    SCM(playerid, COLOUR_ALTO, "/taksi isbasi - iþbaþý yapmanýzý ve iþbaþýndan çýkmanýzý saðlar.");
		SCM(playerid, COLOUR_ALTO, "/taksi ucret - taksimetre ücretini belirlemenizi saðlar.");
		SCM(playerid, COLOUR_ALTO, "/taksi kabul - gelen taksi çaðrýsýný kabul edersiniz.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek aracýný kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek aracýnýn kirasýný bitirebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "Portland merkezinde daha çok para kazanýrsýnýz.");
	}

	else if(PlayerInfo[playerid][pJob] == JOB_MECHANIC)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yardým, Tamircilik Mesleði");
	    SCM(playerid, COLOUR_ALTO, "/benzindoldur - benzini biten araca benzin doldurabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/tamir - aracýn tipine göre tamir isteði gönderebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/aracboya - bir aracý boyayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/araccek - bir aracý park bölgesine çekebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/materyalal - mesleði yapmak için gereken materyalleri satýn alabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/materyallerim - güncel materyallerinizi kontrol edebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek aracýný kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek aracýnýn kirasýný bitirebilirsiniz.");
		SCM(playerid, COLOR_SERVER2, sprintf("Güncel meslek puanýnýz: %d", PlayerInfo[playerid][pCareer]));
	}

	else if(PlayerInfo[playerid][pJob] == JOB_TRUCKER)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yardým, Taþýmacýlýk Mesleði");
	    SCM(playerid, COLOUR_ALTO, "/tasimacilik - yeni bir teslimat noktasý belirler.");
		SCM(playerid, COLOUR_ALTO, "/koli - kolileri kontrol edebildiðiniz komutlar.");
		SCM(playerid, COLOR_SERVER2, sprintf("Güncel meslek puanýnýz: %d", PlayerInfo[playerid][pCareer]));

        switch(PlayerInfo[playerid][pCareer])
		{
		    case 0..11: SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite.");
			case 12..23: SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito.");
		    case 24..31: SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.");
		    case 32..47:
			{
				SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar.");
			}
			case 48..58:
			{
				SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar, Yankee, Flatbed.");
			}
			default:
			{
				SCM(playerid, COLOR_SERVER2, "Kullanýlabilir araçlar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar, Yankee, Flatbed, Òðåéëåðû.");
			}
		}		
	}	

	if(PlayerInfo[playerid][pSideJob] == JOB_PIZZA)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yardým, Kuryecilik Mesleði");
	    SCM(playerid, COLOUR_ALTO, "/kurye - sistemi baþlatmanýza yarar. Herhangi bir lokasyon belirler.");
		SCM(playerid, COLOUR_ALTO, "/pizza - motordan indikten sonra elinize pizza kutusunu alýrsýnýz.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek aracýný kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek aracýnýn kirasýný bitirebilirsiniz.");
	}			

	return 1;
}

CMD:rolyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Rol");
	SCM(playerid, COLOUR_ALTO, "/me, /do, /shout, /low, /pm, /reply, /ame, /ado, /dene, /ddo, /ozellik, /pmengel, /engellistesi, /e(ikinci dil)");
	SCM(playerid, COLOUR_ALTO, "/sme, /sdo, /carwhisper, /whisper, /selamlas, /boombox, /aksiyon, /sandalye, /masasandalye, /dolow, /melow");

	return 1;
}

CMD:mermiyardim(playerid, params[])
{
	static const dlg[] = "{ffc46a}M1911 /M1911 (susturuculu){FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- .45 ACP (7 mermili)\n\		
			- .45 ACP .ext (14 mermili)\n\n\		
			{ffc46a}Desert Eagle{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- .50AE (7 mermili)\n\		
			- .50AE .ext (14 mermili)\n\n\		
			{ffc46a}Shotgun /Sawn-off Shotgun{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- 12-G BIRDSHOT (6 mermili)\n\		
    		- 12-G BUCKSHOT (6 mermili)\n\		
    		- 12-G SLUG (6 mermili)\n\		
    		- 12-G BEANBAG (6 mermili) - öldürücü oolmayan\n\n\		
			{ffc46a}Tec-9 /MP5 /UZI{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- 9x19mm (30 mermili)\n\		
			- 9x19mm .ext (60 mermili)\n\n\		
			{ffc46a}Country Rifle /Sniper Rifle{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- 7.62x51mm (4 mermili)\n\n\		
			{ffc46a}M4{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- 5.56x45mm (30 mermili)\n\		
			- 5.56x45mm T (30 mermili)\n\		
			- 5.56x45mm (büyük þarjör) (60 mermili)\n\		
			- 5.56x45mm (plastik) (30 mermili) - öldürücü olmayan\n\n\		
			{ffc46a}AK-47{FFFFFF}\nKullanýlabilir þarjörler:\n\		
			- 7.62x39mm (30 mermili)\n\		
			- 7.62x39mm T (30 mermili)\n\		
			- 7.62x39mm (büyük þarjör) (60 mermili)";

	new mes[sizeof(dlg)];
	format(mes, sizeof(mes), dlg);
	
	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Mermi", mes, "X", "");
	return 1;
}

CMD:birlikyardim(playerid, params[])
{
	if (PlayerInfo[playerid][pFaction] == 0)
		return SCM(playerid, -1, "Bir birlikte olmalýsýn. Eðer birlik kurmak istiyorsan: /birlikkur");

	SCM(playerid, COLOR_SERVER2, "* Yardým, Birlik");

	if (IsPlayerFactionPolice(playerid))
	{
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /kelepce /kelepcecikar (/m)egafon /mdc /(gov)ernment /rozetgoster /ekiplistesi /pdkisayol");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] (/r)adyo(telsiz) (/r 10-27) (/r 10-28) /rlow /barikat /barikatliste /tutukla /senaryo");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /elkoy /gozalti /apb /tutukla /gisedurum /(sp)ike /cctv /cctvayril /aracicek");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /aracbagla /callsign /pdtag /gate /fbirim /siren /plakakontrol /beanbag /lth");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /kilitkir /kapikir /takip /aracaat /izinlerim /plakabelirle /cezakes /araccezakes ");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /cezakontrol /araccezakontrol /ihbarkabul /radar /aractamir /birlikuyeleri /snakecam /flashbang /taser");
		SCM(playerid, COLOUR_ALTO, "[POLÝS] /birlikaksesuar /bagajara /torpidoara /mulkara /ustara /callsign /sokak /hizkamerasi");
	}
    else if (IsPlayerFactionCity(playerid)) 
	{
		SCM(playerid, COLOUR_ALTO,"[GOV] /birlikaktif /(d)epartman /(f)action(birlik) /rozetgoster /(r)adyo /(m)egafon /(gov)ernment");
		SCM(playerid, COLOUR_ALTO,"[GOV] /barikat /barikatliste /kelepce /kelepcecikar /siren /yt(yakýn telsiz)");
	}
	else if (IsPlayerFactionMedic(playerid))
	{
		SCM(playerid, COLOUR_ALTO,"[MD] /birlikaktif (/d)epartman (/f)action(birlik) /rozetgoster (/r)adio /rlow /barikat /barikatliste /sedye");
		SCM(playerid, COLOUR_ALTO,"[MD] /iyilestir /aracaat /tedavi /siren (/m)egafon (/gov)ernment /recete /terapi /birlikaksesuar");
	}
	else if (IsPlayerFactionFire(playerid))
	{
		SCM(playerid, COLOUR_ALTO,"[FD] /birlikaktif (/d)epartman (/f)action(birlik) /rozetgoster (/r)adio /rlow /barikat /barikatliste /sedye");
		SCM(playerid, COLOUR_ALTO,"[FD] /iyilestir /aracaat /tedavi /siren (/m)egafon (/gov)ernment /birlikaksesuar /choke");
	}
	else if (IsPlayerFactionDocs(playerid))
	{
		SCM(playerid, COLOUR_ALTO,"[DOC] /birlikaktif /(d)epartman /(f)action(birlik)  /rozetgoster /(r)adio /rlow /(m)egafon /(gov)ernment /ozgurbirak /kogusagonder");
		SCM(playerid, COLOUR_ALTO,"[DOC] /siren /gozalti /barikat /barikatliste /kelepce /kelepcecikar /frisk /taser /beanbag /lth /prisonlist /prison");
	}
	else if (IsPlayerFactionNews(playerid))
	{
		SCM(playerid, COLOUR_ALTO,"[HABER] /birlikaktif /(f)action /yayinbaslat /yayinbitir /yayindavet /yayindancikar /basinkarti /basingoster");
	}
	else if (IsPlayerFactionNewsOff(playerid))
	{
		SCM(playerid, COLOUR_ALTO,"[HABER] /birlikaktif /(f)action /yayinbaslat /yayinbitir /yayindavet /yayindancikar /basinkarti /basingoster");
	}
	else
	{
		SCM(playerid, COLOUR_ALTO, "/birlik, /birlikskin");
	}
	return 1;
}

CMD:yardim(playerid)
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Komutlar");
	SCM(playerid, COLOUR_ALTO, "/genelyardim, /birlikyardim, /ayarlaryardim, /meslekyardim, /silahyardim, /balikyardim");
	SCM(playerid, COLOUR_ALTO, "/rolyardim, /evyardim, /isyeriyardim, /telsizyardim, /uyusturucuyardim");

	return 1;
}

CMD:balikyardim(playerid)
{
	SCM(playerid, COLOR_SERVER2, "* Yardým, Balýkçýlýk");
	SCM(playerid, COLOUR_ALTO, "/baliklarim, /baliktut, /balikdurdur, /baliksat");
	SCM(playerid, COLOUR_ALTO, "Oltayý aksesuar dükkanlarýndan alabilirsiniz. /gps");
	SCM(playerid, COLOUR_ALTO, "Balýk tutmak için su kenarlarýnda olmanýz yeterlidir.");
	return 1;
}