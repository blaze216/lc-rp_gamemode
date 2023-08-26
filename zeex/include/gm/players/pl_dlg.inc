Dialog:ChangeWalk(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowSettings(playerid);

	new str[5];
	format(str, sizeof(str), "1 %i", listitem);
	pc_cmd_stildegistir(playerid, str);
	ShowSettings(playerid);
	return 1;
}

Dialog:ChangeTalk(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowSettings(playerid);

	new str[5];
	format(str, sizeof(str), "2 %i", listitem);
	pc_cmd_stildegistir(playerid, str);
	ShowSettings(playerid);
	return 1;
}

Dialog:ChangeFightstyle(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowSettings(playerid);
	if (listitem == 3) return ShowSettings(playerid);

	new str[5];
	format(str, sizeof(str), "3 %i", listitem+1);
	pc_cmd_stildegistir(playerid, str);
	ShowSettings(playerid);
	return 1;
}

/*Dialog:ChangeHud(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowSettings(playerid);

	new str[5];
	format(str, sizeof(str), "4 %i", listitem+1);
	pc_cmd_stildegistir(playerid, str);
	ShowSettings(playerid);

	HideHudTextDraw(playerid);
	return 1;
}*/

Dialog:MainSettings(playerid, response, listitem, inputtext[])
{
	if (!response)					return pc_cmd_mm(playerid, "");
	if (!IsPlayerLogged(playerid))	return 1;

	switch(listitem)
	{
	    case 0: Dialog_Show(playerid, ChangeWalk, DIALOG_STYLE_LIST, "{FFFFFF}Yürüme Stili", "Kapalý\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11", "Seç", "Geri Dön");
		case 1: Dialog_Show(playerid, ChangeTalk, DIALOG_STYLE_LIST, "{FFFFFF}Konuþma Tarzý", "Kapalý\n1\n2\n3\n4\n5\n6\n7\n8\n9", "Seç", "Geri Dön");
		case 2: Dialog_Show(playerid, ChangeFightstyle, DIALOG_STYLE_LIST, "{FFFFFF}Dövüþ Tarzý", "Varsayýlan\nBoxing\nKungfu\n-\nGrabkick", "Seç", "Geri Dön");
		case 3: pc_cmd_tog(playerid, "ooc");
		case 4: pc_cmd_tog(playerid, "isim");
		case 5: pc_cmd_tog(playerid, "reklamlar");
		case 6: pc_cmd_tog(playerid, "giriscikis");
		case 7: pc_cmd_tog(playerid, "hukumet");
		case 8: pc_cmd_tog(playerid, "pm");
		case 9: pc_cmd_tog(playerid, "haberler");
		case 10: pc_cmd_tog(playerid, "afkbilgi");
		case 11: pc_cmd_tog(playerid, "hud");
		case 12: pc_cmd_tog(playerid, "mhud");
		case 13: pc_cmd_tog(playerid, "birliksohbet");
		case 14: pc_cmd_tog(playerid, "canbar");
		case 15: pc_cmd_tog(playerid, "dorenk");
		case 16: pc_cmd_tog(playerid, "giris");
		case 17: {
			 if (PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1) return SendErrorMessage(playerid, "Bu bölüme eriþemezsin.");
			 new string[188], text[144];
			switch(PlayerInfo[playerid][pSettings] & togAdmCmds)//17
			{
				case 0: text = "Admin Uyarýlarý\t[{90EE90}Aktif{FFFFFF}]\n";
				default: text = "Admin Uyarýlarý\t[{FF6347}Deaktif{FFFFFF}]\n";
			}
			strcat(string, text);
			switch(PlayerInfo[playerid][pSettings] & togTester)//11
			{
				case 0: text = "Tester Chat\t[{90EE90}Aktif{FFFFFF}]\n";
				default: text = "Tester Chat\t[{FF6347}Deaktif{FFFFFF}]\n";
			}
			strcat(string, text);
			switch(PlayerInfo[playerid][pSettings] & togAdmChat)//10
			{
				case 0: text = "Admin Chat\t[{90EE90}Aktif{FFFFFF}]\n";
				default: text = "Admin Chat\t[{FF6347}Deaktif{FFFFFF}]\n";
			}
			strcat(string, text);
			Dialog_Show(playerid, AdminSettings, DIALOG_STYLE_TABLIST, "{A9C4E4}Admin Ayarlarý", string, "Seç", "Kapat");
		}
		case 18:
		{
	        new string[188];
	        format(string, sizeof(string), "Seçenek\tAçýklama\n");
	        format(string, sizeof(string), "%s{A9C4E4}Görünebilecek Maksimum Obje Sayýsý\tharita üzerinde renderlanacak obje sayýsý\n", string);
	        format(string, sizeof(string), "%s{A9C4E4}Model Çizim Uzaklýðý\trender için gereken uzaklýk\n", string);

	        Dialog_Show(playerid, DIALOG_OBJECT_MENU, DIALOG_STYLE_TABLIST_HEADERS, "{A9C4E4}Obje Ayarlarý", string, "Seç", "Kapat");
		}
		case 19: pc_cmd_sifredegistir(playerid, "");
	}

	if (listitem < 0 && listitem > 19)  ShowSettings(playerid);

	return 1;
}

Dialog:AdminSettings(playerid, response, listitem, inputtext[])
{
	if(!response)
		return pc_cmd_ayarlar(playerid, "");

	switch(listitem)
	{
		case 0: pc_cmd_tog(playerid, "adminuyari");
		case 1: pc_cmd_tog(playerid, "helperchat");
		case 2: pc_cmd_tog(playerid, "adminchat");
	}
return 1;
}

Dialog:DIALOG_OBJECT_MENU(playerid, response, listitem, inputtext[])
{
	if(!response)
		return pc_cmd_ayarlar(playerid, "");

	switch(listitem)
	{
		case 0:
		{
	        new string[350];
	        format(string, sizeof(string), "Seçenek\tAçýklama\n");
	        format(string, sizeof(string), "%s{A9C4E4}Varsayýlan (1000)\tvarsayýlan görünebilecek obje sayýsý\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Orta (1250)\torta kalite iþlemciler için\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Yüksek (1500)\tyüksek kaliteli görüntü için\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Ultra (2000)\tultra kaliteli görüntü için (FPS düþüþü yaþanabilir)\n", string);

			SendServerMessage(playerid, "Belirtilen ayarlar kayýt edilmez, anlýk olarak oyununuza entegre edilir.");

	        Dialog_Show(playerid, DIALOG_OBJECT_MAXVISIBLE, DIALOG_STYLE_TABLIST_HEADERS, "{A9C4E4}Obje Ayarlarý", string, "Seç", "Kapat");
		}
		case 1:
		{
	        new string[350];
	        format(string, sizeof(string), "Seçenek\tAçýklama\n");
	        format(string, sizeof(string), "%s{A9C4E4}Varsayýlan (1.0)\tvarsayýlan render uzaklýðý\n", string);
	        format(string, sizeof(string), "%s{A9C4E4}Orta (2.0)\torta kalite iþlemciler için\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Yüksek (5.0)\tyüksek kalite iþlemciler için\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Ultra (7.0)\tultra kaliteli görüntü için\n", string);
			format(string, sizeof(string), "%s{A9C4E4}Extreme (10.0)\tekstrem görüntü için (FPS düþüþü yaþanabilir)\n", string);

			SendServerMessage(playerid, "Belirtilen ayarlar kayýt edilmez, anlýk olarak oyununuza entegre edilir.");

	        Dialog_Show(playerid, DIALOG_OBJECT_STREAM, DIALOG_STYLE_TABLIST_HEADERS, "{A9C4E4}Obje Ayarlarý", string, "Seç", "Kapat");
		}
	}

	return 1;
}

Dialog:DIALOG_OBJECT_STREAM(playerid, response, listitem, inputtext[])
{
	if(!response)
		return pc_cmd_ayarlar(playerid, "");

	new Float:maxf;

	switch(listitem)
	{
		case 0: maxf = 1.0;
		case 1: maxf = 2.0;
		case 2: maxf = 5.0;
		case 3: maxf = 7.0;
		case 4: maxf = 10.0;
	}

    Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, maxf, playerid);

	SendServerMessage(playerid, "Obje render uzaklýðýnýz %f olarak deðiþtirilmiþtir.", maxf);
	SendServerMessage(playerid, "Bu deðer FPS düþüþü yaþatýyorsa varsayýlan deðere geçiniz.");

	return 1;
}

Dialog:DIALOG_OBJECT_MAXVISIBLE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return pc_cmd_ayarlar(playerid, "");

	new maxx;

	switch(listitem)
	{
		case 0: maxx = 1000;
		case 1: maxx = 1250;
		case 2: maxx = 1500;
		case 3: maxx = 2000;
	}

    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, maxx, playerid);

	SendServerMessage(playerid, "Maksimum obje görünürlük deðeriniz %d olarak deðiþtirilmiþtir.", maxx);
	SendServerMessage(playerid, "Bu deðer FPS düþüþü yaþatýyorsa varsayýlan deðere geçiniz.");

	return 1;
}

CMD:sifredegistir(playerid, params[])
{
	Dialog_Show(playerid, ChangePass, DIALOG_STYLE_PASSWORD, "Gizli bilgileri girme", "Deðiþtirmek için mevcut þifreyi girin:", ">>>", "Ýptal");
	return 1;
}

alias:mm("menu");
CMD:mm(playerid, params[])
{
	Dialog_Show(playerid, MainMenu, DIALOG_STYLE_LIST, "{FFFFFF}Menu", "1. Envanter\n\
	2. Karakter Ýstatistikleri\n\
	3. Oyuncu þikayet edin {ffc46a} (/rapor) {FFFFFF}\n\
	4. Yönetime soru sor {ffc46a} (/soru) {FFFFFF}\n\
	5. Sunucu komutlarýyla ilgili yardým\n\
	6. Ayarlar", "Seç", "Ýptal");
	return 1;
}

CMD:ayarlar(playerid, params[])
{
	ShowSettings(playerid);
	return 1;
}

CMD:ssmod(playerid, params[])
{
    switch(GetPVarInt(playerid, PVAR_DARKSCREEN_ISACTIVE))
    {
        case false:
        {
            TextDrawShowForPlayer(playerid, ServerTextdraws[std_DarkScreen]);
            SetPVarInt(playerid, PVAR_DARKSCREEN_ISACTIVE, 1);
        }

        case true:
        {
            TextDrawHideForPlayer(playerid, ServerTextdraws[std_DarkScreen]);
            DeletePVar(playerid, PVAR_DARKSCREEN_ISACTIVE);
        }
    }

    return 1;
}
alias:ssmod("gozkapat", "gozac", "ss");

Dialog:MainMenu(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	switch(listitem)
	{
		case 0: pc_cmd_envanter(playerid, "");
		case 1: pc_cmd_karakter(playerid, "");
		case 2: Dialog_Show(playerid, MakeReport, DIALOG_STYLE_INPUT, "{FFFFFF}Rapor"," {FFFFFF} Oyuncu ID'sini ve þikayetin içeriðini aþaðýda bulunan kutuya giriniz: ","Gönder", "Ýptal");
		case 3: Dialog_Show(playerid, MakeHelp, DIALOG_STYLE_INPUT, "{FFFFFF}Soru"," {FFFFFF} Soru içeriðinizi aþaðýda bulunan kutuya giriniz: "," Sor ", "Ýptal");
		case 4: pc_cmd_yardim(playerid);
		case 5: ShowSettings(playerid);
		//case 6: pc_cmd_donate(playerid, "");
		//case 7: return pc_cmd_mm(playerid, "");
	}
	return 1;
}

Dialog:MakeReport(playerid, response, listitem, inputtext[])
{
	if (!response)			return pc_cmd_mm(playerid, "");
    if (!strlen(inputtext))	return Dialog_Show(playerid, MakeReport, DIALOG_STYLE_INPUT, "{FFFFFF}Rapor", "{FFFFFF}Oyuncu ID'sini ve þikayetin içeriðini aþaðýda bulunan kutuya giriniz:\n{C3C3C3}Form: [Oyuncu ID] [Þikayet]", "Gönder", "Ýptal");

	pc_cmd_rapor(playerid, inputtext);
	return 1;
}

Dialog:CmdServer2(playerid, response, listitem, inputtext[])
{
	if (response) pc_cmd_yardim(playerid);

	return 1;
}

Dialog:MakeHelp(playerid, response, listitem, inputtext[])
{
	if (!response)			return pc_cmd_mm(playerid, "");
	if (!strlen(inputtext))	return Dialog_Show(playerid, MakeHelp, DIALOG_STYLE_INPUT, "{FFFFFF}Soru"," {FFFFFF} Soru içeriðinizi aþaðýda bulunan kutuya giriniz: "," Sor ", "Ýptal");

	pc_cmd_rapor(playerid, "");
	return 1;
}

Dialog:ChangePass(playerid, response, listitem, inputtext[])
{
	if (!response) 																return 1;
	if (isnull(inputtext) || strlen(inputtext) < 2 || strlen(inputtext) > 64)	return Dialog_Show(playerid, ChangePass, DIALOG_STYLE_PASSWORD, "{FFFFFF}Gizli bilgileri girme", "{FFFFFF}Deðiþtirmek için mevcut þifrenizi girin:", ">>>", "Ýptal");

	new query[128 + 129];

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `forum_id`= %i AND `password`= '%e'", PlayerInfo[playerid][pAccID], MD5_Hash(inputtext));
	mysql_tquery(dbHandle, query, "OnPlayerChangePass", "i", playerid);
	return 1;
}

Dialog:ChangePass2(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    if (strlen(inputtext) < 6 || strlen(inputtext) > 32)
    {
        Dialog_Show(playerid, ChangePass2, DIALOG_STYLE_PASSWORD, "{FFFFFF}Yeni Þifre "," {FFFFFF} Yeni þifrenizi giriniz:", "Deðiþtir", "Ýptal");
		return SendErrorMessage(playerid, "Þifreniz en az 6, en fazla 32 karakter olmalýdýr.");
	}

	for(new i = 0; i < strlen(inputtext); i++)
	{
		switch(inputtext[i])
		{
			case '!', '@', '#', '$','%','^','&','*','(',')','_','+','=','|','[',']','{','}','-','.','`','~','<','>','?',',','/':
			{
			    Dialog_Show(playerid, ChangePass2, DIALOG_STYLE_PASSWORD, "Yeni Þifre", "Yeni þifrenizi giriniz:", "Deðiþtir", "Ýptal");
				return SendErrorMessage(playerid, "Þifrenin içinde yasaklanmýþ bir simge kullandýnýz.");
			}
			default: continue;
		}
	}

	new query[128 + 129];

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `accounts` SET `password`='%e' WHERE `forum_id` = %i", MD5_Hash(inputtext), PlayerInfo[playerid][pAccID]);
	mysql_tquery(dbHandle, query);

	SendSyntaxMessage(playerid, "Þifreniz deðiþtirildi.");
	return 1;
}

Dialog:ChangeFight(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	SendAdmMessage("%s adlý yönetici %s adlý oyuncunun dövüþ tarzýný deðiþtirdi: %s.", GetAccName(playerid), GetNameEx(GetPVarInt(playerid, "ChangeFightTo")), fight_name[listitem]);
	SendErrorMessage(GetPVarInt(playerid, "ChangeFightTo"), "%s adlý yönetici tarafýndan dövüþ tarzýnýz deðiþtirildi: %s", GetAccName(playerid), fight_name[listitem]);
	SetPlayerFightingStyle(GetPVarInt(playerid, "ChangeFightTo"), fight_id[listitem]);
	PlayerInfo[GetPVarInt(playerid, "ChangeFightTo")][pFightStyle] = fight_id[listitem];
	DeletePVar(playerid, "ChangeFightTo");
	return 1;
}

Dialog:SendPM(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new userid = GetPVarInt(playerid, #pm_to), text[128];

	GetPVarString(playerid, #pm_text, text, 128);
	SendPMToPlayer(playerid, userid, text);
	return 1;
}

alias:greet("selamlas");
CMD:greet(playerid, params[])
{
	new userid, type;

	if (sscanf(params,"ud", userid, type))
	{
		SendHelpMessage(playerid, "/selamlas [ID / isim] [Tip]");
		SendSyntaxMessage(playerid, "[1] Öpüþme [2-9] Tokalaþma");
		return 1;
	}

	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (userid == playerid)								return 1;
	if (type > 9 || type < 1)							return SendErrorMessage(playerid, "Tip 1 ile 9 arasýnda olmalýdýr.");
	if (IsPlayerInAnyVehicle(playerid) || IsPlayerInAnyVehicle(userid)) return SendErrorMessage(playerid, "Aracýn içerisinde bu komut kullanýlamaz.");
	if (!PlayerNearPlayer(2.0, playerid, userid))		return SendNotNearPlayer(playerid);

    pTemp[userid][pGreetPlayer] = playerid;
	pTemp[userid][pGreetType] = type;
    SetPVarInt(userid, #accept_time, gettime() + 30);

	SendSyntaxMessage(playerid, "%s adlý kiþiye istek gönderdiniz.", GetNameWithMask(userid));
	SendSyntaxMessage(userid, "%s adlý kiþi (%s) teklifi gönderdi.", GetNameWithMask(playerid), (type == 1)?("öpüþme"):("tokalaþma"));

	InfoMSG(userid, "~h~~g~Y~w~ - kabul et~n~~h~~r~N~w~ - reddet", 5);
	return 1;
}

forward OnPlayerChangePass(playerid);
public OnPlayerChangePass(playerid)
{
	if (!cache_num_rows())	return Dialog_Show(playerid, ChangePass, DIALOG_STYLE_PASSWORD, "{FFFFFF}Gizli bilgilerin girilmesi "," {FFFFFF} Deðiþtirmek için mevcut þifreyi girin:", ">>>", "Ýptal");

	Dialog_Show(playerid, ChangePass2, DIALOG_STYLE_PASSWORD, "Yeni Þifre", "Yeni þifrenizi giriniz:", "Deðiþtir", "Ýptal");
	return 1;
}

Dialog:BuyClothes(playerid, response, listitem, inputtext[])
{
    new modelid = GetPVarInt(playerid, "clothes_model");

    if (modelid < 1) 	return 1;
	if (GetCash(playerid) < 100)			return SendErrorMessage(playerid, "Yeterli paranýz yok, en az 100$'a ihtiyacýnýz var.");
	if (response)
	{
	PlayerInfo[playerid][pTog][listitem] = PlayerInfo[playerid][pSkin];
    SendSyntaxMessage(playerid, "100$ karþýlýðýnda kýyafet satýn aldýnýz. Tebrikler!");
	SendSyntaxMessage(playerid, "(/kiyafetlerim) komutunu kullanarak dolabýnýzý görüntüleyebilirsiniz.");
	SendSyntaxMessage(playerid, "Komutu kullanmak için binco veya ev içerisinde olup, evinize dolap eklentisi almalýsýnýz..");
    SetPlayerSkinEx(playerid, modelid);
	GiveCash(playerid, -100);
	DeletePVar(playerid, "clothes_model");
	}
	else DeletePVar(playerid, "clothes_model");
	return 1;
}

Dialog:DIALOG_KIYAFETDOLAP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new modelid = strval(inputtext);
	if(modelid == 0) return 1;
	SetPlayerSkinEx(playerid, modelid);
	PlayerInfo[playerid][pSkin] = modelid;
	SendServerMessage(playerid, "Özel modelinizi giydiniz.");
	return 1;
}

Dialog:EditClothes(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    if (PlayerInfo[playerid][pTog][listitem] == 0)
    {
        PlayerInfo[playerid][pTog][listitem] = PlayerInfo[playerid][pSkin];
        pc_cmd_soyun(playerid, "");
        PlayerInfo[playerid][pSkin] = 0;
        return 1;
    }
    new title[32];

    format(title, 32,"{FFFFFF}Kýyafet %i.", PlayerInfo[playerid][pTog][listitem]);
    Dialog_Show(playerid, EditClothes2, DIALOG_STYLE_LIST, title, "- Kullan\n- Sil", "Seç", "Ýptal");
	SetPVarInt(playerid, "select_tog", listitem);
	return 1;
}

Dialog:EditClothes2(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new slot = GetPVarInt(playerid, "select_tog");

    if (PlayerInfo[playerid][pTog][slot] == 0) return 1;

	if (!listitem)
	{
	    new skin = PlayerInfo[playerid][pSkin];
    	SetPlayerSkinEx(playerid,PlayerInfo[playerid][pTog][slot]);
    	PlayerInfo[playerid][pTog][slot] = skin;
    	return 1;
	}

    PlayerInfo[playerid][pTog][slot] = 0;
    return 1;
}

Dialog:BugKurtar(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new houseid = GetNearInsideHouse(playerid, 500.0);
				new buildingid = GetNearInsideBiz(playerid, 500.0);
				new Float:pXa, Float:pYa, Float:pZa;
				GetPlayerPos(playerid, pXa, pYa, pZa);

				if(GetNearInsideHouse(playerid, 500.0) != -1 && houseid != -1 && !IsPlayerInRangeOfPoint(playerid, 100.0, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY], HouseInfo[houseid][hExitZ]) && GetPlayerVirtualWorld(playerid) == HouseInfo[houseid][hExitVW] && GetPlayerInterior(playerid) == HouseInfo[houseid][hExitInt])
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SetPlayerPosEx(playerid, HouseInfo[houseid][hExitX], HouseInfo[houseid][hExitY], HouseInfo[houseid][hExitZ]);
					SetPlayerInterior(playerid, HouseInfo[houseid][hExitInt]);
					SetPlayerVirtualWorld(playerid, HouseInfo[houseid][hExitVW]);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), evdeyken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetNearInsideBiz(playerid, 500.0) != -1 && buildingid != -1 && !IsPlayerInRangeOfPoint(playerid, 100.0, BizInfo[buildingid][bizExitX], BizInfo[buildingid][bizExitY], BizInfo[buildingid][bizExitZ]) && GetPlayerVirtualWorld(playerid) == BizInfo[buildingid][bizExitVW] && GetPlayerInterior(playerid) == BizInfo[buildingid][bizExitInt])
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SetPlayerPosEx(playerid, BizInfo[buildingid][bizExitX], BizInfo[buildingid][bizExitY], BizInfo[buildingid][bizExitZ]);
					SetPlayerInterior(playerid, BizInfo[buildingid][bizExitInt]);
					SetPlayerVirtualWorld(playerid, BizInfo[buildingid][bizExitVW]);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), isletmedeyken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerInterior(playerid) == 0 && pZa > 200)
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SendClientMessageEx(playerid, COLOUR_TOMATO, "VW deðeriniz sýfýrlandý.");
					SetPlayerVirtualWorld(playerid, 0);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), VW bugundayken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerInterior(playerid) == 0 && pZa < 200)
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SendClientMessageEx(playerid, COLOUR_TOMATO, "VW deðerini sýfýrlamak için Liberty City'a ýþýnlandýn.");
					SetPlayerPosEx(playerid, 785.9385,-868.3475,35.3712);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), VW bugundayken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) != 0 && pZa < 200)
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SendClientMessageEx(playerid, COLOUR_TOMATO, "Interior deðerini sýfýrlamak için Liberty City'a ýþýnlandýn.");
					SetPlayerPosEx(playerid, 785.9385,-868.3475,35.3712);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), INT bugundayken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) != 0 && pZa > 200.0)
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SendClientMessageEx(playerid, COLOUR_TOMATO, "Interior deðeriniz sýfýrlandý.");
					SetPlayerInterior(playerid, 0);
					Log_Kaydet("loglar/bugkurtar.txt", sprintf("[%s] %s (C_ID: %d | A_ID: %d), INT bugundayken /bugkurtar komutunu kullandi.", GetFullDate(), GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID]));
				}
				else if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0 && pZa < 20.0)
				{
					if(PlayerInfo[playerid][pJailTime] > 1) return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");
					SendClientMessageEx(playerid, COLOUR_TOMATO, "Bulunduðun bug durumundan kurtuldun.");
					SetPlayerPosEx(playerid, 785.9385,-868.3475,35.3712);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
					Log_Kaydet("genelLog.txt", sprintf("[/bugkurtar] %s (C_ID: %d | A_ID: %d), disaridayken /bugkurtar komutunu kullandi. (vw/int sifirla, lc gonder) [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetFullDate()));
				}
				else return SendErrorMessage(playerid, "Bu komutu þu anda kullanamazsýn, daha sonra tekrar deneyin.");

				if(PlayerInfo[playerid][pInjured] > 0)
				{
	                PlayerInfo[playerid][pHealth] = 100.0;
	                ResetDamages(playerid);
	                StopPlayerAnims(playerid);
	                UnFreezePlayer(playerid);
	                SetPlayerSkill(playerid);

					Log_Kaydet("genelLog.txt", sprintf("[/bugkurtar] %s (C_ID: %d | A_ID: %d), kullandigi /bugkurtar komutuyla birlikte canlandirildi. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetFullDate()));
				}
			}
			case 1:
			{
				if(PlayerInfo[playerid][pJailTime] > 1 || PlayerInfo[playerid][pInjured] != 0)
					return SendErrorMessage(playerid, "Bu fonksiyondan þu anda yararlanamazsýn.");

				if(GetPVarInt(playerid, "BugKurtar") == 1)
					return SendErrorMessage(playerid, "Sonraki paydaye kadar ya da relog atana kadar bu komutu tekrar kullanamazsýn.");

				if(PlayerInfo[playerid][pInjured] > 0)
					return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");

				new Float:oXa, Float:oYa, Float:oZa;
				GetPlayerPos(playerid, oXa, oYa, oZa);
				SetPlayerPosEx(playerid, oXa, oYa, oZa + 2.0);
				SetPVarInt(playerid, "BugKurtar", 1);
				Log_Kaydet("genelLog.txt", sprintf("[/bugkurtar] %s (C_ID: %d | A_ID: %d), /bugkurtar > slap ozelligini kullandi. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetFullDate()));

			}
			case 2:
			{
				if(PlayerInfo[playerid][pJailTime] > 1 || PlayerInfo[playerid][pInjured] != 0)
					return SendErrorMessage(playerid, "Bu fonksiyondan þu anda yararlanamazsýn.");

				if(GetPVarInt(playerid, "BugKurtar") == 1)
					return SendErrorMessage(playerid, "Sonraki paydaye kadar ya da relog atana kadar bu komutu tekrar kullanamazsýn.");

				if(PlayerInfo[playerid][pInjured] > 0)
					return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");

				if(GetPlayerVirtualWorld(playerid) == 0)
					return SendErrorMessage(playerid, "Bu komutu kullanamazsýn.");

				new Float:oXa, Float:oYa, Float:oZa;
				GetPlayerPos(playerid, oXa, oYa, oZa);
				SetPlayerPosEx(playerid, oXa, oYa, oZa - 2.0);
				SetPVarInt(playerid, "BugKurtar", 1);
				Log_Kaydet("genelLog.txt", sprintf("[/bugkurtar] %s (C_ID: %d | A_ID: %d), /bugkurtar > slap ozelligini kullandi. [Tarih: %s]", GetNameEx(playerid), PlayerInfo[playerid][pID], PlayerInfo[playerid][pAccID], GetFullDate()));
			}
			case 3:
			{
                Streamer_Update(playerid);
				SendServerMessage(playerid, "Çevrenizde bulunan objeler güncellenip, yenilendi.");				
			}
		}
	}
	return 1;
}