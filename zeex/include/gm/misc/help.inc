CMD:genelyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Genel");
	SCM(playerid, COLOUR_ALTO, "/envanter, /yerdenal, /arac, /paraver, /ehliyetal, /ehliyetgoster, /gps, /graffiti");
	SCM(playerid, COLOUR_ALTO, "/giris, /cikis, /ev, /isyeri, /admins, /helpers, /ceset, /ustara, /animasyonlar, /sonreklamlar");
	SCM(playerid, COLOUR_ALTO, "/rapor, /soru, /kiyafetlerim, /aksesuar, /cpsifirla, /mikrofon, /bugkurtar, /reklamlar");
    SCM(playerid, COLOUR_ALTO, "/reklam, /plakakontrol, /zar, /saat, /fare, /sonarac, /bagis, /evgps, /isyerigps");

	return 1;
}

alias:uyusturucuyardim("uyardim");
CMD:uyusturucuyardim(playerid)
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Uyu�turucu");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/u ya da /uyusturucularim: {FFFFFF}uyu�turucular�n� y�netmeye yarar");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/tohumtemizle: {FFFFFF}saks�da ekili tohumlara el koymaya yarar (lspd komutu)");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/paketsil: {FFFFFF}yerdeki uyu�turucu paketlerine el koyar (lspd)");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/arac paketler: {FFFFFF}ara�taki uyu�turucular� g�rmeye yarar");
	SendClientMessageEx(playerid, COLOUR_ORANGE, "/yerdenal: {FFFFFF}yerdeki paketi alman�za yarar");
	
	if(PlayerInfo[playerid][pAdmin] >= ADMIN_LEVEL_1)
	
	{
		SendClientMessageEx(playerid, COLOR_YELLOW, "Y�netici Komutlar�:");
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/atohumtemizle:{FFFFFF} ekilmi� bir tohumun �r�nlerine el koymaya yarar");
	}
	
	if(PlayerInfo[playerid][pAdmin] > ADMIN_LEVEL_1)
	{
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/auver:{FFFFFF} y�netici komutuyla uyu�turucu vermeye yarar");
		SendClientMessageEx(playerid, COLOUR_ORANGE, "/uyusturucuduzenle:{FFFFFF} bir kullan�c�n�n uyu�turucusunu d�zenlemeye yarar");
	}
	return 1;
}

CMD:silahyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Silah");
	SCM(playerid, COLOUR_ALTO, "/silah: t�m silah komutlar�");
	return 1;
}

CMD:evyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Ev");
	SCM(playerid, COLOUR_ALTO, "/ev, /evmenu, /ev satinal, /ddo, /dshout");

	return 1;
}

alias:isyeriyardim("mekanyardim");
CMD:isyeriyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, ��yeri");
	SCM(playerid, COLOUR_ALTO, "/isyeri veya /mekan, /mekan satinal, /mekanmenu");

	return 1;
}

CMD:ayarlaryardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Ayarlar");
	SCM(playerid, COLOUR_ALTO, "/ayarlar, /tog");

	return 1;
}

CMD:telsizyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Telsiz");
	SCM(playerid, COLOUR_ALTO, "/kanal, /slotayarla, /telsizsifre, /telsizsifredegis, /telsizuyeler, /kanaldanat, /t-/r, /rlow, /rr, /rrlow");

	return 1;
}

CMD:meslekyardim(playerid, params[])
{
	if (PlayerInfo[playerid][pJob] == JOBLESS)	return SendErrorMessage(playerid, "Herhangi bir i�in yok. /gps ile yak�ndaki i�lere bakabillirsin.");

	if(PlayerInfo[playerid][pJob] == JOB_TAXI)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yard�m, Taksicilik Mesle�i");
	    SCM(playerid, COLOUR_ALTO, "/taksi isbasi - i�ba�� yapman�z� ve i�ba��ndan ��kman�z� sa�lar.");
		SCM(playerid, COLOUR_ALTO, "/taksi ucret - taksimetre �cretini belirlemenizi sa�lar.");
		SCM(playerid, COLOUR_ALTO, "/taksi kabul - gelen taksi �a�r�s�n� kabul edersiniz.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek arac�n� kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek arac�n�n kiras�n� bitirebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "Portland merkezinde daha �ok para kazan�rs�n�z.");
	}

	else if(PlayerInfo[playerid][pJob] == JOB_MECHANIC)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yard�m, Tamircilik Mesle�i");
	    SCM(playerid, COLOUR_ALTO, "/benzindoldur - benzini biten araca benzin doldurabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/tamir - arac�n tipine g�re tamir iste�i g�nderebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/aracboya - bir arac� boyayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/araccek - bir arac� park b�lgesine �ekebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/materyalal - mesle�i yapmak i�in gereken materyalleri sat�n alabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/materyallerim - g�ncel materyallerinizi kontrol edebilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek arac�n� kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek arac�n�n kiras�n� bitirebilirsiniz.");
		SCM(playerid, COLOR_SERVER2, sprintf("G�ncel meslek puan�n�z: %d", PlayerInfo[playerid][pCareer]));
	}

	else if(PlayerInfo[playerid][pJob] == JOB_TRUCKER)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yard�m, Ta��mac�l�k Mesle�i");
	    SCM(playerid, COLOUR_ALTO, "/tasimacilik - yeni bir teslimat noktas� belirler.");
		SCM(playerid, COLOUR_ALTO, "/koli - kolileri kontrol edebildi�iniz komutlar.");
		SCM(playerid, COLOR_SERVER2, sprintf("G�ncel meslek puan�n�z: %d", PlayerInfo[playerid][pCareer]));

        switch(PlayerInfo[playerid][pCareer])
		{
		    case 0..11: SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite.");
			case 12..23: SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito.");
		    case 24..31: SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.");
		    case 32..47:
			{
				SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar.");
			}
			case 48..58:
			{
				SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar, Yankee, Flatbed.");
			}
			default:
			{
				SCM(playerid, COLOR_SERVER2, "Kullan�labilir ara�lar: Picador, Sadler, Bobcat, Walton, Yosemite, Pony, Berkley's RC Van, Burrito, Rumpo, Boxville.\n");
                SCM(playerid, COLOR_SERVER2, "Benson, Mule, DFT-30, Tanker, Securicar, Yankee, Flatbed, ��������.");
			}
		}		
	}	

	if(PlayerInfo[playerid][pSideJob] == JOB_PIZZA)
	{
	    SCM(playerid, COLOR_SERVER2, "* Yard�m, Kuryecilik Mesle�i");
	    SCM(playerid, COLOUR_ALTO, "/kurye - sistemi ba�latman�za yarar. Herhangi bir lokasyon belirler.");
		SCM(playerid, COLOUR_ALTO, "/pizza - motordan indikten sonra elinize pizza kutusunu al�rs�n�z.");
		SCM(playerid, COLOUR_ALTO, "/mak - meslek arac�n� kiralayabilirsiniz.");
		SCM(playerid, COLOUR_ALTO, "/makb - meslek arac�n�n kiras�n� bitirebilirsiniz.");
	}			

	return 1;
}

CMD:rolyardim(playerid, params[])
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Rol");
	SCM(playerid, COLOUR_ALTO, "/me, /do, /shout, /low, /pm, /reply, /ame, /ado, /dene, /ddo, /ozellik, /pmengel, /engellistesi, /e(ikinci dil)");
	SCM(playerid, COLOUR_ALTO, "/sme, /sdo, /carwhisper, /whisper, /selamlas, /boombox, /aksiyon, /sandalye, /masasandalye, /dolow, /melow");

	return 1;
}

CMD:mermiyardim(playerid, params[])
{
	static const dlg[] = "{ffc46a}M1911 /M1911 (susturuculu){FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- .45 ACP (7 mermili)\n\		
			- .45 ACP .ext (14 mermili)\n\n\		
			{ffc46a}Desert Eagle{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- .50AE (7 mermili)\n\		
			- .50AE .ext (14 mermili)\n\n\		
			{ffc46a}Shotgun /Sawn-off Shotgun{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- 12-G BIRDSHOT (6 mermili)\n\		
    		- 12-G BUCKSHOT (6 mermili)\n\		
    		- 12-G SLUG (6 mermili)\n\		
    		- 12-G BEANBAG (6 mermili) - �ld�r�c� oolmayan\n\n\		
			{ffc46a}Tec-9 /MP5 /UZI{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- 9x19mm (30 mermili)\n\		
			- 9x19mm .ext (60 mermili)\n\n\		
			{ffc46a}Country Rifle /Sniper Rifle{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- 7.62x51mm (4 mermili)\n\n\		
			{ffc46a}M4{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- 5.56x45mm (30 mermili)\n\		
			- 5.56x45mm T (30 mermili)\n\		
			- 5.56x45mm (b�y�k �arj�r) (60 mermili)\n\		
			- 5.56x45mm (plastik) (30 mermili) - �ld�r�c� olmayan\n\n\		
			{ffc46a}AK-47{FFFFFF}\nKullan�labilir �arj�rler:\n\		
			- 7.62x39mm (30 mermili)\n\		
			- 7.62x39mm T (30 mermili)\n\		
			- 7.62x39mm (b�y�k �arj�r) (60 mermili)";

	new mes[sizeof(dlg)];
	format(mes, sizeof(mes), dlg);
	
	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "Mermi", mes, "X", "");
	return 1;
}

CMD:birlikyardim(playerid, params[])
{
	if (PlayerInfo[playerid][pFaction] == 0)
		return SCM(playerid, -1, "Bir birlikte olmal�s�n. E�er birlik kurmak istiyorsan: /birlikkur");

	SCM(playerid, COLOR_SERVER2, "* Yard�m, Birlik");

	if (IsPlayerFactionPolice(playerid))
	{
		SCM(playerid, COLOUR_ALTO, "[POL�S] /kelepce /kelepcecikar (/m)egafon /mdc /(gov)ernment /rozetgoster /ekiplistesi /pdkisayol");
		SCM(playerid, COLOUR_ALTO, "[POL�S] (/r)adyo(telsiz) (/r 10-27) (/r 10-28) /rlow /barikat /barikatliste /tutukla /senaryo");
		SCM(playerid, COLOUR_ALTO, "[POL�S] /elkoy /gozalti /apb /tutukla /gisedurum /(sp)ike /cctv /cctvayril /aracicek");
		SCM(playerid, COLOUR_ALTO, "[POL�S] /aracbagla /callsign /pdtag /gate /fbirim /siren /plakakontrol /beanbag /lth");
		SCM(playerid, COLOUR_ALTO, "[POL�S] /kilitkir /kapikir /takip /aracaat /izinlerim /plakabelirle /cezakes /araccezakes ");
		SCM(playerid, COLOUR_ALTO, "[POL�S] /cezakontrol /araccezakontrol /ihbarkabul /radar /aractamir /birlikuyeleri /snakecam /flashbang /taser");
		SCM(playerid, COLOUR_ALTO, "[POL�S] /birlikaksesuar /bagajara /torpidoara /mulkara /ustara /callsign /sokak /hizkamerasi");
	}
    else if (IsPlayerFactionCity(playerid)) 
	{
		SCM(playerid, COLOUR_ALTO,"[GOV] /birlikaktif /(d)epartman /(f)action(birlik) /rozetgoster /(r)adyo /(m)egafon /(gov)ernment");
		SCM(playerid, COLOUR_ALTO,"[GOV] /barikat /barikatliste /kelepce /kelepcecikar /siren /yt(yak�n telsiz)");
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
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Komutlar");
	SCM(playerid, COLOUR_ALTO, "/genelyardim, /birlikyardim, /ayarlaryardim, /meslekyardim, /silahyardim, /balikyardim");
	SCM(playerid, COLOUR_ALTO, "/rolyardim, /evyardim, /isyeriyardim, /telsizyardim, /uyusturucuyardim");

	return 1;
}

CMD:balikyardim(playerid)
{
	SCM(playerid, COLOR_SERVER2, "* Yard�m, Bal�k��l�k");
	SCM(playerid, COLOUR_ALTO, "/baliklarim, /baliktut, /balikdurdur, /baliksat");
	SCM(playerid, COLOUR_ALTO, "Oltay� aksesuar d�kkanlar�ndan alabilirsiniz. /gps");
	SCM(playerid, COLOUR_ALTO, "Bal�k tutmak i�in su kenarlar�nda olman�z yeterlidir.");
	return 1;
}