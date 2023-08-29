static const Yasaklikelime[][] = {
".delfriend",
".banall",
".kick",
".rapid",
".silent",
"/.cmds",
".cmds",
".silentaim",
".enemy",
"/.slapper",
"/.slap",
"/.silentaim",
"/.kick",
"/.friend",
"/.silent",
"/.inv",
".inv",
"/.enemy",
".silenton",
"URPG",
"Losland",
"U-RPG",
"Flexman",
"Muteo",
"uroleplay",
".toggle"
};

stock FindBadWords(inputtext[])
{
    for(new s; s < sizeof(Yasaklikelime); s++)
    {
        new pos;
        while((pos = strfind(inputtext,Yasaklikelime[s],true)) != -1)
        {
            for(new i = pos, j = pos + strlen(Yasaklikelime[s]); i < j; i++)
            {
                return 1;
            }
			break;
        }
    }
    return 0;
}

Player_OnPlayerText(playerid, text[])
{
	new str[144], vehicle = GetPlayerVehicleID(playerid);

    if(FindBadWords(text))
    {
        SendErrorMessage(playerid,"Sohbet kutucuðuna girdiðiniz bir kelime yasaklýdýr. Tekrarlamayýnýz.");
		SendAdmMessage("%s adlý kiþi sohbet kutusuna yasaklý kelime girdi.", GetNameEx(playerid));
        return 0;
    }

	if(!strcmp(text, ":D", true))
	{
		pc_cmd_me(playerid, "kahkaha atar.");
		return 0;
	}

	if(!strcmp(text, ":(", true))
	{
		pc_cmd_me(playerid, "somurtur.");
		return 0;
	}

	if(!strcmp(text, ":/", true))
	{
		pc_cmd_me(playerid, "dudak büzer.");
		return 0;
	}

	if(!strcmp(text, ":)", true))
	{
		pc_cmd_me(playerid, "gülümser.");
		return 0;
	}

	if(!strcmp(text, ";)", true))
	{
		pc_cmd_me(playerid, "göz kýrpar.");
		return 0;
	}

	if(!strcmp(text, ":O", true))
	{
		pc_cmd_me(playerid, "þaþýrýr.");
		return 0;
	}

	if(!strcmp(text, "xD", true))
	{
		pc_cmd_me(playerid, "sýrýtýr.");
		return 0;
	}

	if (PlayerInfo[playerid][UyusKullan] > gettime()) format(text, 160, "%s", MulStringHandler(text));

    if (pTemp[playerid][pEmergency] == 444)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Maalesef sizi anlamadým, lütfen tekrar edin. ");
			return 0;
		}

		SendMechanicHelp(playerid, text);

		SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Aramanýz çalýþanlarýmýza bildirilmiþtir, beklemede kalýn.");

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 555)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Maalesef sizi anlamadým, lütfen tekrar edin. ");
			return 0;
		}

		SendTaxiRequest(playerid, text);

		SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Aramanýz sürücülerimize bildirildi, beklemede kalýn. ");

		SetPVarInt(playerid, "NeedTaxi", 1);

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 911)
	{
		if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Maalesef anlayamadým, lütfen tekrar edin. ");
			return 0;
		}

		if (strval(text) != 1 && strval(text) != 2 && strval(text) != 3)
		{
		    SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Tekrar edin... Hangi departmana ihtiyacýnýz var? ");
		    return 0;
		}

		SCM(playerid, COLOR_YELLOWG, "911 Operatörü (telefon): Lütfen yerinizi ve durumunuzu açýklayýn. ");
		pTemp[playerid][pEmergency] = 911 + strval(text);
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 912)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Maalesef anlayamadým, ne oldu? ");
			return 0;
		}

		new location[MAX_ZONE_NAME];
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

		SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "|__________Acil Çaðrý__________|");

		if (pTemp[playerid][pPayphone] == -1)
		{
			SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Arayan: %s, No: %i", GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);
		}
		else
		{
			SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Arayan: Ankesörlü Telefon, No: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
		}

		SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Servis: Polis");
		SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Konum: %s", location);
		
		if (strlen(text) > MAXLEN)
		{
			SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Durum: %.*s ...", MAXLEN, text);
			SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Durum: ... %s", text[MAXLEN]);
		}
		else
			SendFactionMessageF(FACTION_POLICE, COLOR_LIGHTBLUE, "Durum: %s", text);

		SendLocalMessage(25.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", GetNameEx(playerid), text);	

		Add_Call(playerid, 1, text);
		

		SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Bölgenizdeki tüm ekiplere haber verdik, lütfen olduðunuz yerde kalýn. ");

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 913)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Maalesef anlayamadým, durumu net anlatýr mýsýnýz?");
			return 0;
		}
        new location[MAX_ZONE_NAME];
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

		for(new i = FACTION_MEDICS; i <= FACTION_FIRE; i++)
		{
			SendFactionMessageF(i, LSFD_DUTY, "|__________Acil Çaðrý__________|"); //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			if (pTemp[playerid][pPayphone] == -1)
			{
				SendFactionMessageF(i, LSFD_DUTY, "Arayan: %s, No: %i", GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);
			}
			else
			{
				SendFactionMessageF(i, LSFD_DUTY, "Arayan: Ankesörlü Telefon, No: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
			}
			SendFactionMessageF(i, LSFD_DUTY, "Servis: Polis, Ambulans / Ýtfaiyeciler");
			SendFactionMessageF(i, LSFD_DUTY, "Konum: %s", location);
			if (strlen(text) > MAXLEN)
			{
				SendFactionMessageF(i, LSFD_DUTY, "Durum: %.*s ...", MAXLEN, text);
				SendFactionMessageF(i, LSFD_DUTY, "Durum: ... %s", text[MAXLEN]);
			}
			else
				SendFactionMessageF(i, LSFD_DUTY, "Durum: %s", text);
		}

		Add_Call(playerid, 2, text);

		SendLocalMessage(25.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", GetNameEx(playerid), text);	

		SCM(playerid, COLOR_YELLOWG, "911 Operatörü (telefon): Bölgenizdeki tüm ekipleri uyardýk, lütfen olduðunuz yerde kalýn. ");

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");

	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 914)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Maalesef anlayamadým, ne oldu? ");
			return 0;
		}

		new location[MAX_ZONE_NAME];
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

		for(new i = FACTION_POLICE; i <= FACTION_FIRE; i++)
		{
			SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "|__________Acil Çaðrý__________|");
			printf("-1");
			if (pTemp[playerid][pPayphone] == -1)
			{
				printf("0");
				SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Arayan: %s, NO: %i", GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);//, GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);
				printf("1");
			}
			else
			{
				SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Arayan: Ankesörlü telefon, No: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
			}
			SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Servis: Polis, Ambulans / Ýtfaiyeciler");
			SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Konum: %s", location);
			if (strlen(text) > MAXLEN)
			{
				SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Durum: %.*s ...", MAXLEN, text);
				SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Durum: ... %s", text[MAXLEN]);
			}
			else
				SendFactionMessage(i, i == FACTION_POLICE ? COLOR_LIGHTBLUE : LSFD_DUTY, "Durum: %s", text);
		}

		Add_Call(playerid, 3, text);

		SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Bölgenizdeki tüm ekiplere haber verdik, lütfen olduðunuz yerde kalýn. ");

		SendLocalMessage(25.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", GetNameEx(playerid), text);	

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}
	else if (pTemp[playerid][pEmergency] == 991)
	{
	    if (!strlen(text) || CheckTextDrawString(text))
		{
			SCM(playerid, COLOR_YELLOWG, "911 Operatör (telefon): Maalesef sizi anlamadým. ");
			return 0;
		}

		new location[MAX_ZONE_NAME];
		GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);
        foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !IsPlayerFactionPolice(i) || (PlayerInfo[i][pSettings] & togFaction))
				continue;

			SendClientMessage(i, COLOR_POLICECHAT, "|____________ Acil arama ____________|");
			if (pTemp[playerid][pPayphone] == -1)
			{
				SendClientMessageEx(i, COLOR_POLICECHAT, "Arayan kiþi: %s, No: %i", GetNameWithMask(playerid), PlayerInfo[playerid][pNumber]);
			}
			else
			{
				SendClientMessageEx(i, COLOR_POLICECHAT, "Arayan kiþi: Ankesörlü telefon, No: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
			}
			SendClientMessageEx(i, COLOR_POLICECHAT, "Konum: %s", location);
			if (strlen(text) > MAXLEN)
			{
				SendClientMessageEx(i, COLOR_POLICECHAT, "Durum: %.*s ...", MAXLEN, text);
				SendClientMessageEx(i, COLOR_POLICECHAT, "Durum: ... %s", text[MAXLEN]);
			}
			else
				SendClientMessageEx(i, COLOR_POLICECHAT, "Durum: %s", text);
		}
		GetPlayerPos(playerid, pTemp[playerid][pCallPosX], pTemp[playerid][pCallPosY], pTemp[playerid][pCallPosZ]);

		SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "ÝPUCU:{FFFFFF} Aramayý kabul etmek için: /ihbarkabul %i", playerid);

		SendLocalMessage(25.0, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", GetNameEx(playerid), text);	

		pTemp[playerid][pCallOn] = 1;

		SCM(playerid, COLOR_YELLOWG, "Operatör (telefon): Bölgenizdeki tüm devriyeleri uyardýk, lütfen olduðunuz yerde kalýn. ");

		pTemp[playerid][pEmergency] = 0;
		pTemp[playerid][pCallStatus] = 0;
	    SendCellMessage(playerid, "Telefon kapandý.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    if (pTemp[playerid][pPayphone] != -1) cancelPayphone(playerid);
		else
		{
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			Phone_Destroy(playerid);
		}
		return 0;
	}

	if (pTemp[playerid][pInterview] != INVALID_PLAYER_ID)
	{
	    if (strlen(text) > MAXLEN)
	    {
			format(str, sizeof(str), "** [Yayýn] Misafir %s: %.*s ...", GetNameWithMask(playerid), MAXLEN, text);
			NewsChat(0x76F134AA,str);
			format(str, sizeof(str), "... %s", text[MAXLEN]);
			NewsChat(0x76F134AA,str);
		}
		else
		{
		    format(str, sizeof(str), "** [Yayýn] Misafir %s: %s", GetNameWithMask(playerid), text);
			NewsChat(0x76F134AA,str);
		}
		return 0;
	}
	else if (pTemp[playerid][pNews] == 1)
	{
	    if (strlen(text) > MAXLEN)
	    {
			format(str, sizeof(str), "** [Yayýn] Muhabir %s: %.*s ...", GetNameWithMask(playerid), MAXLEN, text);
			NewsChat(0x76F134AA,str);
			format(str, sizeof(str), "... %s", text[MAXLEN]);
			NewsChat(0x76F134AA,str);
		}
		else
		{
		    format(str, sizeof(str), "** [Yayýn] Muhabir %s: %s", GetNameWithMask(playerid), text);
			NewsChat(0x76F134AA,str);
		}
		return 0;
	}

	if (IsPlayerInAnyVehicle(playerid) && !IsADontWindow(vehicle))
	{
		if (0 != IsWindowsClose(GetPlayerVehicleID(playerid))) {
			if (strlen(text) > MAXLEN-15)
			{
				format(str, sizeof(str), "%s (araç içi%s): %.*s ...", GetNameWithMask(playerid), ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])?("  / telefon"):(""), MAXLEN-15, text);
				SendVehicleMessage(GetPlayerVehicleID(playerid),COLOR_FADE1,str);
				format(str, sizeof(str), "... %s", text[MAXLEN-15]);
				SendVehicleMessage(GetPlayerVehicleID(playerid),COLOR_FADE1,str);
			}
			else
			{
				format(str, sizeof(str), "%s (araç içi%s): %s", GetNameWithMask(playerid), ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])?(" / telefon"):(""), text);
				SendVehicleMessage(GetPlayerVehicleID(playerid),COLOR_FADE1,str);
			}
		} else {
			if (strlen(text) > MAXLEN-15)
			{
				format(str, sizeof(str), "%s%s: %.*s ...", GetNameWithMask(playerid), ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])?(" (telefon)"):(""), MAXLEN-15, text);
				SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,str);
				format(str, sizeof(str), "... %s", text[MAXLEN-15]);
				SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,str);
			}
			else
			{
				format(str, sizeof(str), "%s%s: %s", GetNameWithMask(playerid), ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])?(" (telefon)"):(""), text);
				SendLocalMessage(Range_VShort, playerid, COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,COLOR_FADE1,str);
			}
		}
	}
	else
	{
	    if (strlen(text) > MAXLEN)
	    {
	        if ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])
	        {
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %.*s ...", GetNameWithMask(playerid), MAXLEN, text);
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", text[MAXLEN]);
	        }
	        else
	        {
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s: %.*s ...", GetNameWithMask(playerid), MAXLEN, text);
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "... %s", text[MAXLEN]);
			}
		}
		else
		{
		    if ((pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2) || pTemp[playerid][pEmergency])
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", GetNameWithMask(playerid), text);
	        else
				SendLocalMessage(Range_Normal, playerid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s: %s", GetNameWithMask(playerid), text);
		}
	}
	ChatAnimation(playerid, strlen(text));

	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID && pTemp[playerid][pCallStatus] == 2)
	{
	    new targetid = pTemp[playerid][pCallLine];
	    if (IsPlayerLogged(targetid) == 0)
	    {
	        HangupCall(playerid);
	        return 0;
	    }
        if (strlen(text) > MAXLEN)
		{
			SendPhoneMessageEx(targetid, COLOR_YELLOWG, "%s %s (telefon): %.*s ...", GetPhoneSexName(targetid), pTemp[targetid][pCallName], MAXLEN, text);
			SendPhoneMessageEx(targetid, COLOR_YELLOWG, "%s %s (telefon): ... %s", GetPhoneSexName(targetid), pTemp[targetid][pCallName], text[MAXLEN]);

			if (GetPVarInt(targetid, #loud_speak) == 1)
			{
				SendLocalMessage(10.0, targetid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %.*s ...", pTemp[targetid][pCallName], MAXLEN, text);
				SendLocalMessage(10.0, targetid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): ... %s", pTemp[targetid][pCallName], text[MAXLEN]);
			}
		}
		else
		{
			SendPhoneMessageEx(targetid, COLOR_YELLOWG, "%s %s (telefon): %s", GetPhoneSexName(targetid), pTemp[targetid][pCallName], text);

			if (GetPVarInt(targetid, #loud_speak) == 1)
				SendLocalMessage(10.0, targetid, COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5, "%s (telefon): %s", pTemp[targetid][pCallName], text);
		}
	}
    return 1;
}


Phone_OnPlayerUpdate(playerid)
{
    if (GetPVarInt(playerid, #selfie))
	{
		new keys[3];
		GetPlayerKeys(playerid, keys[0], keys[1], keys[2]);

	    if (keys[1] == KEY_UP)
	    {
	        new Float: pz =
	        	GetPVarFloat(playerid, #selfie_z);

			pz += 0.01;
			if (pz < 0.70)
			{
			    new Float: rot;
     			GetPlayerFacingAngle(playerid, rot);

                SetPVarFloat(playerid, #selfie_z, pz);

		        new Float: x,
					Float: y,
					Float: z,
					Float: new_x,
					Float: new_y,
					Float: radius = 0.9;

			    GetPlayerPos(playerid, x, y, z);
		        new_x = x + radius * floatcos(rot - 270.0, degrees);
		        new_y = y + radius * floatsin(rot - 270.0, degrees);

				SetPlayerCameraPos(playerid, new_x, new_y, z + 0.78);
				SetPlayerCameraLookAt(playerid, x, y, z + pz);
				SetPlayerFacingAngle(playerid, rot);
			}
	    }
	    else if (keys[1] == KEY_DOWN)
	    {
	        new Float: pz =
	        	GetPVarFloat(playerid, #selfie_z);

			pz -= 0.01;
			if (pz > 0.50)
			{
			    new Float: rot;
     			GetPlayerFacingAngle(playerid, rot);

                SetPVarFloat(playerid, #selfie_z, pz);

		        new Float: x,
					Float: y,
					Float: z,
					Float: new_x,
					Float: new_y,
					Float: radius = 0.9;

			    GetPlayerPos(playerid, x, y, z);
		        new_x = x + radius * floatcos(rot - 270.0, degrees);
		        new_y = y + radius * floatsin(rot - 270.0, degrees);

				SetPlayerCameraPos(playerid, new_x, new_y, z + 0.78);
				SetPlayerCameraLookAt(playerid, x, y, z + pz);
				SetPlayerFacingAngle(playerid, rot);
			}
	    }
	    if (keys[2] == KEY_LEFT)
	    {
	        new Float: rot;
	        GetPlayerFacingAngle(playerid, rot);

			rot += 1.0;
			if (rot >= 359.0) rot = 0.0;

	        new Float: x,
				Float: y,
				Float: z,
				Float: new_x,
				Float: new_y,
				Float: radius = 0.9;

		    GetPlayerPos(playerid, x, y, z);
	        new_x = x + radius * floatcos(rot - 270.0, degrees);
	        new_y = y + radius * floatsin(rot - 270.0, degrees);

			SetPlayerCameraPos(playerid, new_x, new_y, z + 0.78);
			SetPlayerCameraLookAt(playerid, x, y, z + GetPVarFloat(playerid, #selfie_z));
			SetPlayerFacingAngle(playerid, rot);
	    }
	    else if (keys[2] == KEY_RIGHT)
	    {
	        new Float: rot;
	        GetPlayerFacingAngle(playerid, rot);

	        rot -= 1.0;
			if (rot <= 1.0) rot = 359.0;

	        new Float: x,
				Float: y,
				Float: z,
				Float: new_x,
				Float: new_y,
				Float: radius = 0.9;

		    GetPlayerPos(playerid, x, y, z);
	        new_x = x + radius * floatcos(rot - 270.0, degrees);
	        new_y = y + radius * floatsin(rot - 270.0, degrees);

			SetPlayerCameraPos(playerid, new_x, new_y, z + 0.78);
			SetPlayerCameraLookAt(playerid, x, y, z + GetPVarFloat(playerid, #selfie_z));
			SetPlayerFacingAngle(playerid, rot);
	    }
	}
    return 1;
}

Ph_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(playertextid == TD_iphone_keypad[playerid][9] && IsPlayerPhoneCreated(playerid) != 0 && PhoneInfo[playerid][phoneKeypad] != 0)
	{
	    if(strlen(pTemp[playerid][pCallKeypad]) < 1)
	    	return 1;

	    pc_cmd_ara(playerid, pTemp[playerid][pCallKeypad]);
		return 1;
	}

	if(playertextid == TD_iphone_keypad[playerid][22] && IsPlayerPhoneCreated(playerid) != 0 && PhoneInfo[playerid][phoneKeypad] != 0)
	{
	    if(strlen(pTemp[playerid][pCallKeypad]) < 1)
	    	return 1;

	    strdel(pTemp[playerid][pCallKeypad], strlen(pTemp[playerid][pCallKeypad])-1, 11);
 		PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], pTemp[playerid][pCallKeypad]);
 		PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][0] && IsPlayerPhoneCreated(playerid) != 0 && PlayerInfo[playerid][pPhoneOff] == 0)
	{
        PlayerInfo[playerid][pPhoneOff] = 1;

        Phone_Setting(playerid, 0);

        PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][12], 0x000000FF);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][12]);

        PlayerTextDrawHide(playerid, TD_iphone[playerid][17]);
        PlayerTextDrawHide(playerid, TD_iphone[playerid][18]);
        PlayerTextDrawHide(playerid, TD_iphone[playerid][19]);
        PlayerTextDrawHide(playerid, TD_iphone[playerid][20]);
        PlayerTextDrawHide(playerid, TD_iphone[playerid][21]);

        PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
		return 1;
	}

	if(playertextid == TD_iphone[playerid][22] && PlayerInfo[playerid][pPhoneOff] == 1 && IsPlayerPhoneCreated(playerid))
	{
	    PlayerInfo[playerid][pPhoneOff] = 0;

        PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][12], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][12]);

        PlayerTextDrawShow(playerid, TD_iphone[playerid][17]);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][18]);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][19]);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][20]);
        PlayerTextDrawShow(playerid, TD_iphone[playerid][21]);

        Phone_Block(playerid, 1);
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);

        new query[256];
   		mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `read`='0' WHERE `to_number`=%i AND `read`='-1'", PlayerInfo[playerid][pNumber]);
		mysql_tquery(dbHandle, query);
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][1] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    PlayerInfo[playerid][pPhoneAirplane] = (PlayerInfo[playerid][pPhoneAirplane])?(0):(1);

	    if(PlayerInfo[playerid][pPhoneAirplane] == 1 && (pTemp[playerid][pEmergency] || pTemp[playerid][pCallLine] != INVALID_PLAYER_ID))
	        pc_cmd_telefonkapat(playerid, "");

	    if(PlayerInfo[playerid][pPhoneAirplane] == 0)
	    {
	        new query[256];
   			mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `read`='0' WHERE `to_number`=%i AND `read`='-1'", PlayerInfo[playerid][pNumber]);
			mysql_tquery(dbHandle, query);
	    }

	    PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][1], (PlayerInfo[playerid][pPhoneAirplane] == 0)?("Ucak Modu: Kapali"):("Ucak Modu: Acik"));
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][1]);
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		return 1;
	}
	if(playertextid == TD_iphone_setting[playerid][2] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    PlayerInfo[playerid][pPhoneSound] = (PlayerInfo[playerid][pPhoneSound])?(0):(1);
	    PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][2], (PlayerInfo[playerid][pPhoneSound] == 0)?("Ses: Acik"):("Ses: Kapali"));
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][2]);
		PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][8] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PlayerInfo[playerid][pPhoneRingtone]-- < 1)
	        PlayerInfo[playerid][pPhoneRingtone] = sizeof(phone_ringtons)-1;

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
    	PlayerPlaySound(playerid, phone_ringtons[PlayerInfo[playerid][pPhoneRingtone]], 0.0, 0.0, 0.0);

		new mes[32];
		format(mes, sizeof(mes), "zil-%i.mp3", PlayerInfo[playerid][pPhoneRingtone]+1);
		PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][10], mes);
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][10]);
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][9] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PlayerInfo[playerid][pPhoneRingtone]++ >= sizeof(phone_ringtons)-1)
	        PlayerInfo[playerid][pPhoneRingtone] = 0;

		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
    	PlayerPlaySound(playerid, phone_ringtons[PlayerInfo[playerid][pPhoneRingtone]], 0.0, 0.0, 0.0);

		new mes[32];
		format(mes, sizeof(mes), "zil-%i.mp3", PlayerInfo[playerid][pPhoneRingtone]+1);
		PlayerTextDrawSetString(playerid, TD_iphone_setting[playerid][10], mes);
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][10]);
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][5] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PlayerInfo[playerid][pPhoneStyle]-- < 1)
	        PlayerInfo[playerid][pPhoneStyle] = sizeof(phone_panel)-1;

		PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][4]);

		PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][12], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone[playerid][12]);

		PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][17], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone[playerid][17]);

		PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][1]);

        PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][2]);

        for(new i; i != 34; i++)
        {
            if(i == 9)
                continue;

			switch(i)
			{
			    case 0..11, 23..33: PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][i], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
				default: PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][i], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
			}
        }
		return 1;
	}

	if(playertextid == TD_iphone_setting[playerid][6] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PlayerInfo[playerid][pPhoneStyle]++ >= sizeof(phone_panel)-1)
	        PlayerInfo[playerid][pPhoneStyle] = 0;

        PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][4]);

		PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][12], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone[playerid][12]);

		PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][17], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
		PlayerTextDrawShow(playerid, TD_iphone[playerid][17]);

		PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][1]);

        PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
        PlayerTextDrawShow(playerid, TD_iphone_setting[playerid][2]);
		return 1;
	}

    if(playertextid == TD_iphone_contact[playerid][1] && IsPlayerPhoneCreated(playerid) != 0)
	{
        if(GetPVarInt(playerid, #select_sms) == 0)
	    {
	    	new mes[32];
	    	format(mes, sizeof(mes), "%i", PlayerContacts[playerid][GetPVarInt(playerid, #select_contact)][contactNumber]);
	    	pc_cmd_ara(playerid, mes);
		}
		else
		{
			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `sms` WHERE `id`=%i", GetPVarInt(playerid, #select_sms));
			mysql_tquery(dbHandle, query, "ShowSMS", "ii", playerid, GetPVarInt(playerid, #select_sms));
		}
		return 1;
	}
	if(playertextid == TD_iphone_contact[playerid][2] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(GetPVarInt(playerid, #select_sms) == 0)
	    {
	    	new mes[128];
	    	format(mes, sizeof(mes), "[%s]", PlayerContacts[playerid][GetPVarInt(playerid, #select_contact)][contactName]);
	    	Dialog_Show(playerid, SendSMS3, DIALOG_STYLE_INPUT, mes, "Mesajý girin:", "Ýlerle", "Geri Dön");
		}
		else
		{
		    new mes[32];
		    GetPVarString(playerid, #sms_number, mes, 32);
	    	Dialog_Show(playerid, SendSMS2, DIALOG_STYLE_INPUT, mes, "Mesajý girin:", "Ýlerle", "Geri Dön");
		}
		return 1;
	}
	if(playertextid == TD_iphone_contact[playerid][3] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(GetPVarInt(playerid, #select_sms) == 0)
	    {
   	 		new mes[128];
	    	format(mes, sizeof(mes), "Bu kiþiyi rehberden silmek istiyor musun? %s (%i)", PlayerContacts[playerid][GetPVarInt(playerid, #select_contact)][contactName], PlayerContacts[playerid][GetPVarInt(playerid, #select_contact)][contactNumber]);
	    	Dialog_Show(playerid, DeleteContact, DIALOG_STYLE_MSGBOX, "[Rehber]", mes, "Evet", "Hayýr");
		}
		else
		{
	    	Dialog_Show(playerid, DeleteSMS, DIALOG_STYLE_MSGBOX, "[Rehber]", "{ffffff}Bu mesajý silmek istediðinize emin misiniz?", "Evet", "Hayýr");
		}
		return 1;
	}
    if(playertextid == TD_iphone_contact[playerid][4] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(GetPVarInt(playerid, #select_sms) == 0)
	    {
	    	Phone_Contact_Info(playerid);
	   		Phone_Contacts(playerid, 0);
	   	}
	   	else
	   	{
	   	    Phone_SMS_Info(playerid);
	   	    Phone_SMS(playerid, 0);
	   	}
		return 1;
	}

	if(IsPlayerPhoneCreated(playerid) != 0)
	{
	    for(new i; i != 3; i++)
	    {
	        if(playertextid != TD_iphone_block[playerid][i + 3] || PhoneInfo[playerid][phoneBlockSMS][i] == 0)
	            continue;

			new id = PhoneInfo[playerid][phoneBlockSMS][i];

			Phone_Block(playerid, 0);
			Phone_SMS_Info(playerid, id);
			return 1;
	    }

	    for(new i; i != 3; i++)
	    {
	        if(playertextid != TD_iphone_list[playerid][i + 13] || PhoneInfo[playerid][phoneListed][i] == -1)
	            continue;

			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `history_calls` WHERE `id` = %i", PhoneInfo[playerid][phoneListed][i]);
			mysql_tquery(dbHandle, query, "ShowHistoryInfo", "ii", playerid, PhoneInfo[playerid][phoneListed][i]);
			return 1;
	    }

	    for(new i; i != 10; i++)
	    {
	        if(playertextid != TD_iphone_keypad[playerid][i + 12])
	            continue;

			if(strlen(pTemp[playerid][pCallKeypad]) > 10)
			    return 1;

			switch(i)
			{
			    case 0: strcat(pTemp[playerid][pCallKeypad], "1", 11);
			    case 1: strcat(pTemp[playerid][pCallKeypad], "2", 11);
			    case 2: strcat(pTemp[playerid][pCallKeypad], "3", 11);
			    case 3: strcat(pTemp[playerid][pCallKeypad], "4", 11);
			    case 4: strcat(pTemp[playerid][pCallKeypad], "5", 11);
			    case 5: strcat(pTemp[playerid][pCallKeypad], "6", 11);
			    case 6: strcat(pTemp[playerid][pCallKeypad], "7", 11);
			    case 7: strcat(pTemp[playerid][pCallKeypad], "8", 11);
			    case 8: strcat(pTemp[playerid][pCallKeypad], "9", 11);
			    case 9: strcat(pTemp[playerid][pCallKeypad], "0", 11);
			}
			PlayerTextDrawSetString(playerid, TD_iphone_name[playerid], pTemp[playerid][pCallKeypad]);
	   		PlayerTextDrawShow(playerid, TD_iphone_name[playerid]);
			return 1;
	    }

	    for(new i; i != 9; i++)
	    {
	        if(playertextid != TD_iphone_list[playerid][i + 4] || PhoneInfo[playerid][phoneListed][i] == -1)
	            continue;

			if(PhoneInfo[playerid][phoneContact] == 1)
			{
            	Phone_Contacts(playerid);
            	Phone_Contact_Info(playerid, PhoneInfo[playerid][phoneListed][i]);
			}
			if(PhoneInfo[playerid][phoneSMS] == 1)
			{
            	Phone_SMS(playerid);
            	Phone_SMS_Info(playerid, PhoneInfo[playerid][phoneListed][i]);
			}
			if(PhoneInfo[playerid][phoneGPS] == 1)
			{
			    new mes[128];
				format(mes, sizeof(mes), "{ffffff}GPS lokasyonu - %s. Checkpoint belirlensin mi?", gps_location[PhoneInfo[playerid][phoneListed][i]][gpsName]);
				Dialog_Show(playerid, SelectGPS, DIALOG_STYLE_MSGBOX, "[GPS]", mes, "Belirle", "Kapat");
				SetPVarInt(playerid, #select_gps, PhoneInfo[playerid][phoneListed][i]);
			}
			return 1;
	    }
	}
    if(playertextid == TD_iphone_list[playerid][2] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PhoneInfo[playerid][phoneContact] == 1)
	    {
	    	if(GetPVarInt(playerid, #contacts_list) + 1 <= 4)
		    	Phone_Contacts(playerid, GetPVarInt(playerid, #contacts_list) + 1);
		}
		if(PhoneInfo[playerid][phoneSMS] == 1)
	    {
	    	Phone_SMS(playerid, GetPVarInt(playerid, #contacts_list) + 1);
		}
		if(PhoneInfo[playerid][phoneGPS] == 1)
	    {
	    	if(GetPVarInt(playerid, #contacts_list) + 1 <= 2)
		    	Phone_GPS(playerid, GetPVarInt(playerid, #contacts_list) + 1);
		}
        if(PhoneInfo[playerid][phoneHistory] == 1)
	    {
 			Phone_History(playerid, GetPVarInt(playerid, #contacts_list) + 1);
		}
		return 1;
	}
	if(playertextid == TD_iphone_list[playerid][1] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    if(PhoneInfo[playerid][phoneContact] == 1)
	    {
	    	if(GetPVarInt(playerid, #contacts_list) - 1 >= 0)
	        	Phone_Contacts(playerid, GetPVarInt(playerid, #contacts_list) - 1);
		}
		if(PhoneInfo[playerid][phoneSMS] == 1)
	    {
	        if(GetPVarInt(playerid, #contacts_list) - 1 >= 0)
	    		Phone_SMS(playerid, GetPVarInt(playerid, #contacts_list) - 1);
		}
		if(PhoneInfo[playerid][phoneGPS] == 1)
	    {
	        if(GetPVarInt(playerid, #contacts_list) - 1 >= 0)
	    		Phone_GPS(playerid, GetPVarInt(playerid, #contacts_list) - 1);
		}
		if(PhoneInfo[playerid][phoneHistory] == 1)
	    {
	        if(GetPVarInt(playerid, #contacts_list) - 1 >= 0)
	    		Phone_History(playerid, GetPVarInt(playerid, #contacts_list) - 1);
		}
		return 1;
	}
	if(playertextid == TD_iphone_list[playerid][3] && IsPlayerPhoneCreated(playerid) != 0 && PhoneInfo[playerid][phoneContact] != 0)
	{
	    Dialog_Show(playerid, AddContact, DIALOG_STYLE_INPUT, "[Rehber]", "Numarayý girin:", "Ýlerle", "Geri Dön");
	    return 1;
	}
	if(playertextid == TD_iphone_list[playerid][3] && IsPlayerPhoneCreated(playerid) != 0 && PhoneInfo[playerid][phoneSMS] != 0)
	{
	    Dialog_Show(playerid, SendSMS, DIALOG_STYLE_INPUT, "[Mesaj]", "Numarayý girin:", "Ýlerle", "Geri Dön");
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][0] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
	    Phone_Contacts(playerid, 0);//0 - ñòðàíèöà
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][1] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
 		Phone_Setting(playerid, 1);
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][2] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
	    Phone_SMS(playerid, 0);//0 - ñòðàíèöà
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][3] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
	    Phone_History(playerid, 0);//0 - ñòðàíèöà
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][4] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    pc_cmd_selfie(playerid, "");
	    return 1;
	}
	if(playertextid == TD_iphone_menu[playerid][5] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
	    Phone_GPS(playerid, 0);//0 - ñòðàíèöà
	    return 1;
	}
    if(playertextid == TD_iphone_menu[playerid][6] && IsPlayerPhoneCreated(playerid) != 0)
	{
	    Phone_Menu(playerid, 0);
 		Phone_Keypad(playerid, 1);
	    return 1;
	}

	if(playertextid == TD_iphone_button[playerid][4] && IsPlayerPhoneCreated(playerid) != 0)
		return pc_cmd_telefonac(playerid, "");

    if((playertextid == TD_iphone_button[playerid][0] || playertextid == TD_iphone_button[playerid][2]) && IsPlayerPhoneCreated(playerid) != 0)
		return pc_cmd_telefonkapat(playerid, "");

    if(playertextid == TD_iphone[playerid][22] && (PhoneInfo[playerid][phoneSetting] != 0 || PhoneInfo[playerid][phoneBlock] != 0 || PhoneInfo[playerid][phoneContact] != 0 || PhoneInfo[playerid][phoneSMS] != 0 || PhoneInfo[playerid][phoneHistory] != 0 || PhoneInfo[playerid][phoneKeypad] != 0 || PhoneInfo[playerid][phoneGPS] != 0) && IsPlayerPhoneCreated(playerid))
	{
	    Phone_Block(playerid, 0);
		Phone_Contacts(playerid);
		Phone_SMS(playerid);
		Phone_History(playerid);
		Phone_GPS(playerid);
		Phone_Setting(playerid, 0);
		Phone_Keypad(playerid, 0);
		Phone_Menu(playerid, 1);
		return 1;
	}
	return 1;
}
