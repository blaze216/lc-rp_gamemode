alias:tog("hudkapat", "gizle");
CMD:tog(playerid, params[])
{
	new option[16];
	if (sscanf(params, "s[16]", option))
	{
		SendHelpMessage(playerid, "/tog [se�enekler]");
		SendSyntaxMessage(playerid, "isim hud ooc giriscikis reklamlar hukumet canbar");
		SendSyntaxMessage(playerid, "pm adminuyari birliksohbet haberler afkbilgi giris animbilgi");
		return 1;
	}

	if (CompareStrings(option, "isim"))
	{
		if (PlayerInfo[playerid][pSettings] & togName)
		{
			PlayerInfo[playerid][pSettings] &= ~togName;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			foreach(new i : Player)
			{
				ShowPlayerNameTagForPlayer(playerid, i, 1);
			}
			SendSyntaxMessage(playerid, "Oyuncular�n isimlerini g�r�n�r yapt�n�z.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togName;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			foreach(new i : Player)
			{
				ShowPlayerNameTagForPlayer(playerid, i, 0);
			}
			SendSyntaxMessage(playerid, "Oyuncular�n isimlerini g�r�nmez yapt�n�z.");
		}
	}

	else if (CompareStrings(option, "hud"))
	{
		if (PlayerInfo[playerid][pSettings] & togHUD)
		{
			PlayerInfo[playerid][pSettings] &= ~togHUD;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			if(!(PlayerInfo[playerid][pSettings] & yesMHUD)){
				ShowHudTextDrawModern(playerid);
			} else ShowHudTextDraw(playerid);
			SendSyntaxMessage(playerid, "HUD'u a�t�n.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togHUD;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			HideHudTextDraw(playerid);
			SendSyntaxMessage(playerid, "HUD'u kapatt�n. ");
		}
	}

	else if (CompareStrings(option, "mhud"))
	{
		if ((PlayerInfo[playerid][pSettings] & togHUD)) return SendServerMessage(playerid, "�lk �nce Hud'u a��n.");
		if ((PlayerInfo[playerid][pSettings] & yesMHUD))
		{
			PlayerInfo[playerid][pSettings] &= ~yesMHUD;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			ShowHudTextDrawModern(playerid);
			SendSyntaxMessage(playerid, "Modern HUD'u a�t�n.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= yesMHUD;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			HideHudTextDrawModern(playerid);
			ShowHudTextDraw(playerid);
			SendSyntaxMessage(playerid, "Modern HUD'u kapatt�n. ");
		}
	}

	else if (CompareStrings(option, "ooc"))
	{
		if (PlayerInfo[playerid][pSettings] & togOOC)
		{
			PlayerInfo[playerid][pSettings] &= ~togOOC;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "OOC Duyuru Kanal�n� aktif ettin.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togOOC;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "OOC Duyuru Kanal�n� pasif duruma getirdin.");
		}
	}

	else if (CompareStrings(option, "giriscikis"))
	{
		if (PlayerInfo[playerid][pSettings] & togJoin)
		{
			PlayerInfo[playerid][pSettings] &= ~togJoin;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Size en yak�n oyuncular�n giri�/��k�� bilgilerini etkinle�tirdiniz.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togJoin;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Size en yak�n oyuncular�n giri�/��k�� bilgilerini devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "reklamlar"))
	{
		if (PlayerInfo[playerid][pSettings] & togAdv)
		{
			PlayerInfo[playerid][pSettings] &= ~togAdv;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Reklamlar�n g�r�nmesini etkinle�tirdiniz. ");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togAdv;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Reklamlar�n g�r�nt�lenmesini devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "hukumet"))
	{
		if (PlayerInfo[playerid][pSettings] & togGov)
		{
			PlayerInfo[playerid][pSettings] &= ~togGov;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "H�k�met haberlerinin g�r�nt�lenmesini aktifle�tirdiniz. ");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togGov;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "H�k�met haberlerinin g�r�nmesini devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "pm"))
	{
		if (PlayerInfo[playerid][pSettings] & togPM)
		{
			PlayerInfo[playerid][pSettings] &= ~togPM;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "PM almay� etkinle�tirdiniz.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togPM;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid,"PM almay� devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "dorenk"))
	{
		if (PlayerInfo[playerid][pSettings] & togDoSetting)
		{
			PlayerInfo[playerid][pSettings] &= ~togDoSetting;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Do rengini ye�il yapt�n.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togDoSetting;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid,"Do rengini mor yapt�n�z.");
		}
	}

	else if (CompareStrings(option, "adminuyari"))
	{
		if (PlayerInfo[playerid][pSettings] & togAdmCmds)
		{
			PlayerInfo[playerid][pSettings] &= ~togAdmCmds;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Admin bildirimlerini aktifle�tirdiniz.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togAdmCmds;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Admin bildirimlerini devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "adminchat"))
	{
		if (PlayerInfo[playerid][pSettings] & togAdmChat)
		{
			PlayerInfo[playerid][pSettings] &= ~togAdmChat;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Admin chat aktifle�tirdiniz.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togAdmChat;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Admin chat devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "helperchat"))
	{
		if (!IsTester(playerid, 1) && !CheckAdmin(playerid, ADMIN_LEVEL_1)) return SendNotAdmin(playerid);

		if (PlayerInfo[playerid][pSettings] & togTester)
		{
			PlayerInfo[playerid][pSettings] &= ~togTester;
			SendServerMessage(playerid, "Helper sohbeti �u anda aktif.");
		}
		else
		{
			PlayerInfo[playerid][pSettings] |= togTester;
			SendServerMessage(playerid, "Helper sohbeti �u anda deaktif.");
		}
	}

	else if (CompareStrings(option, "birliksohbet"))
	{
		if (PlayerInfo[playerid][pSettings] & togFaction)
		{
			PlayerInfo[playerid][pSettings] &= ~togFaction;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Birlik mesajlar�n�n g�r�nt�lenmesini aktifle�tirdiniz.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togFaction;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Birlik mesajlar�n�n g�r�nt�lenmesini devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "haberler"))
	{
		if (PlayerInfo[playerid][pSettings] & togNews)
		{
			PlayerInfo[playerid][pSettings] &= ~togNews;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Haber bildirimlerini aktifle�tirdiniz.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togNews;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Haber bildirimlerini devre d��� b�rakt�n�z. ");
		}
	}

	else if (CompareStrings(option, "afkbilgi"))
	{
		if (PlayerInfo[playerid][pSettings] & togAFK)
		{
			PlayerInfo[playerid][pSettings] &= ~togAFK;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "AFK'ta harcanan zaman� etkinle�tirdiniz. ");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togAFK;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "AFK'ta harcanan zaman� devre d��� b�rakt�n�z.");
		}
	}

	else if (CompareStrings(option, "canbar"))
	{
		if (PlayerInfo[playerid][pSettings] & togCustomBar)
		{
			PlayerInfo[playerid][pSettings] &= ~togCustomBar;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Custom can bar�n� a�t�n�z.");
			EnableHealthBarForPlayer(playerid, true);
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togCustomBar;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Custom can bar�n� kapatt�n�z.");
			EnableHealthBarForPlayer(playerid, false);
		}
	}

	else if (CompareStrings(option, "giris"))
	{
		if (PlayerInfo[playerid][pSettings] & togEnter)
		{
			PlayerInfo[playerid][pSettings] &= ~togEnter;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Y tu�u ile giri�/��k�� durumunu etkinle�tirdiniz.");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togEnter;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Y tu�u ile giri�/��k�� durumunu devre d��� b�rakt�n�z");
		}
	}	

	else if (CompareStrings(option, "raporsoru"))
	{
		if (PlayerInfo[playerid][pSettings] & togService)
		{
			PlayerInfo[playerid][pSettings] &= ~togService;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Hizmetlerin g�r�nt�lenmesini etkinle�tirdiniz [RAPOR | DESTEK | TALEP].");
		}
		else 
		{
			PlayerInfo[playerid][pSettings] |= togService;
			SQL_SetInteger("users", "settings", PlayerInfo[playerid][pSettings], PlayerInfo[playerid][pID]);
			SendSyntaxMessage(playerid, "Hizmetlerin g�r�nt�lenmesini devre d��� b�rakt�n�z [RAPOR | DESTEK | TALEP].");
		}
	}
	else 
	{
		SendHelpMessage(playerid, "/tog [se�enekler]");
		SendSyntaxMessage(playerid, "isim/hud/ooc/giriscikis/reklamlar/hukumet");
		SendSyntaxMessage(playerid, "pm/adminuyari/adminchat/helperchat/birliksohbet/haberler/afkbilgi/giris");
	}
	return 1;
}

HUD_OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        SpectateCheck(playerid);
    }

	if (newstate == PLAYER_STATE_DRIVER)
	{
		if (!(PlayerInfo[playerid][pSettings] & togHUD))
		{
			PlayerTextDrawShow(playerid, SpeedText[playerid]);
		}
	}
	
	if (oldstate == PLAYER_STATE_DRIVER)
	{
		PlayerTextDrawHide(playerid, SpeedText[playerid]);
	}

    if(newstate == PLAYER_STATE_SPECTATING && IsPlayerLoggedIn(playerid))
    {
        if (CheckAdmin(playerid, ADMIN_LEVEL_1))
        {
            if(StaffInfo[playerid][sSpec] == true)
            {
                ToggleSpectatingPanel(playerid, true);
            }
        }
    }

    else if(oldstate == PLAYER_STATE_SPECTATING && IsPlayerLoggedIn(playerid))
    {
        if (CheckAdmin(playerid, ADMIN_LEVEL_1))
        {
            if(StaffInfo[playerid][sSpec] == false)
            {
                ToggleSpectatingPanel(playerid, false);
            }
        }
    }
	return 1;
}