#define MAX_ADVERT_SLOT 	(10)
#define MAX_LAST_ADVERT     (10)

static const ReklamYasakli[][] = {
"allah",
"orospu",
"sikerim",
"URPG",
"ananý",
"Losland",
"U-RPG",
"Flexman",
"Muteo",
"skywalker",
"uroleplay"
};

stock FindBadWordsOnAdvert(inputtext[])
{
    for(new s; s < sizeof(ReklamYasakli); s++)
    {
        new pos;
        while((pos = strfind(inputtext,ReklamYasakli[s],true)) != -1)
        {
            for(new i = pos, j = pos + strlen(ReklamYasakli[s]); i < j; i++)
            {
                return 1;
            }
			break;
        }
    }
    return 0;
}

enum LAST_ADVERT_ENUM
{
	advertText[256],
	adverttime,
	advertnumber
}
new LastAdvertInfo[MAX_LAST_ADVERT][LAST_ADVERT_ENUM];

new lastadvert = 0;

stock Advert_OnGameModeInit()
{
	return 1;
}


alias:sonreklam("sonreklamlar");
CMD:sonreklam(playerid, params[])
{
	new mes[888 * MAX_LAST_ADVERT + 9] = "{FFFFFF}";
	
	for(new i; i != MAX_LAST_ADVERT; i++)
	{
		if (strlen(LastAdvertInfo[i][advertText]) == 0)	continue;

		if (strlen(LastAdvertInfo[i][advertText]) > MAXLEN)
		{
			new pos = MAXLEN;

			if (pos < MAXLEN-1) pos = MAXLEN;

			format(mes, sizeof(mes), "%s%i\t%.*s ...\n", mes, i+1, pos, LastAdvertInfo[i][advertText]);
			format(mes, sizeof(mes), "%s\t... %s", mes, LastAdvertInfo[i][advertText][pos]);
		}
		else
		{
			format(mes, sizeof(mes), "%s%i\t%s", mes, i+1, LastAdvertInfo[i][advertText]);
		}
			
		new time[32];

		if (gettime() - LastAdvertInfo[i][adverttime] <= 59)
			format(time, sizeof(time), "%d saniye önce", gettime() - LastAdvertInfo[i][adverttime]);
		else 
			format(time, sizeof(time), "%d dakika önce", floatround((gettime() - LastAdvertInfo[i][adverttime])/60, floatround_floor));
			
		format(mes, sizeof(mes), "%s\n\t{a9c4e4}No: %i\t(%s){FFFFFF}\n\n", mes, LastAdvertInfo[i][advertnumber], time);
	}
	
	if (strlen(mes) < 9)	return Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{bccd32}Son Reklamlar", "Reklam listesi boþ.", "Kapat", "");
	    
	Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{bccd32}Son Reklamlar", mes, "Kapat", "");
	return 1;
}

alias:reklam("reklamver");
CMD:reklam(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (!PlayerInfo[playerid][pNumber])				return SendErrorMessage(playerid, "Bir telefona ihtiyacýn var.");
    if (sscanf(params, "s[144]", params)) 		return SendHelpMessage(playerid, "/reklam [yazý]");
    //if (PlayerInfo[playerid][pSettings] & togAdv)	return SendErrorMessage(playerid, "Reklam vermek için reklam görmeyi etkinleþtirin. /ayarlar");
	//if (pTemp[playerid][pAdvertTime] > gettime())	return SendErrorMessage(playerid, "Tekrar reklam vermek için %s dakika beklemen gerek.", ConvertSecond(pTemp[playerid][pAdvertTime] - gettime()));
    if(FindBadWordsOnAdvert(params))
    {
        SendErrorMessage(playerid,"Sohbet kutucuðuna girdiðiniz bir kelime yasaklýdýr. Tekrarlamayýnýz.");
		SendAdmMessage("%s adlý kiþi reklama yasaklý kelime girdi.", GetNameEx(playerid));
        return 0;
    }

    new anunt[144];
	new bizid = -1;

    if ((bizid = Advertisement_Nearest(playerid)) == -1)				return SendErrorMessage(playerid, "Ajansta deðilsin.");
	if (BizInfo[bizid][bizLocked] == 1)									return GameTextForPlayer(playerid, "~r~KILITLI!", 2500, 1);
	if (BizInfo[bizid][bizOwnerID] != 0 && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Ýþ yerinin yeterli ürünü yok.");
	if (GetCash(playerid) < BizInfo[bizid][bizEntrance])				return SendErrorMessage(playerid, "Yeterli paranýz yok. $%i gerekiyor.", BizInfo[bizid][bizEntrance]);
	if(sscanf(params, "s[144]", anunt)) return SendErrorMessage(playerid, "Reklamýz çok kýsa veya uzun.");
    

    if (BizInfo[bizid][bizOwnerID] != 0)
    {
        BizInfo[bizid][bizProduct]--;
        GiveBizCash(bizid, BizInfo[bizid][bizEntrance]);
    }

	foreach(new i : Player)
	{
		if(PlayerInfo[playerid][pSettings] & togAdv) continue;

	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_GREENFORADVERT, "[%s] %s: %.*s ...", BizInfo[bizid][bizName], GetNameEx(playerid), pos, params);
			SendClientMessageEx(i, COLOR_GREENFORADVERT, "... %s No: %d", params[pos], PlayerInfo[playerid][pNumber]);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_GREENFORADVERT, "[%s] %s: %s No: %d", BizInfo[bizid][bizName], GetNameEx(playerid), params, PlayerInfo[playerid][pNumber]);
	    }		
	}	

    //SendDiscordAdvertisements(GetNameEx(playerid), PlayerInfo[playerid][pNumber], params);

	SendServerMessage(playerid, "Baþarýyla reklam verdiniz. Bir sonraki reklam için 300 saniye beklemelisiniz.");

	if (lastadvert >= MAX_LAST_ADVERT) lastadvert = 0;
	else lastadvert++;
	format(LastAdvertInfo[lastadvert][advertText], 144, "%s", params);
	LastAdvertInfo[lastadvert][adverttime] = gettime();
	LastAdvertInfo[lastadvert][advertnumber] = PlayerInfo[playerid][pNumber];

    pTemp[playerid][pAdvertTime] = gettime() + 300;
	GiveCash(playerid, -BizInfo[bizid][bizEntrance]);
	return 1;
}

CMD:mekanreklam(playerid, params[])
{
	new anunt[144];
	if (!PlayerInfo[playerid][pNumber])				return SendErrorMessage(playerid, "Ýlan vermek için bir telefon veya sim kartýna ihtiyacýn var.");
	if (sscanf(params, "s[144]", params)) 		return SendHelpMessage(playerid, "/mekanreklam [yazý]");
    if (PlayerInfo[playerid][pSettings] & togAdv)	return SendErrorMessage(playerid, "Lütfen önce reklamlarý etkinleþtirin. /ayarlar");
	if (GetCash(playerid) < 100)				return SendErrorMessage(playerid, "Yeterli paranýz yok. Reklam Fiyatý: $100.");
	if (pTemp[playerid][pAdvertTime] > gettime())	return SendErrorMessage(playerid, "Tekrar reklam vermek için %s dakika beklemen gerek.", ConvertSecond(pTemp[playerid][pAdvertTime] - gettime()));
	if(sscanf(params, "s[144]", anunt)) return SendErrorMessage(playerid, "Reklamýz çok kýsa veya uzun.");
    if(FindBadWordsOnAdvert(params))
    {
        SendErrorMessage(playerid,"Sohbet kutucuðuna girdiðiniz bir kelime yasaklýdýr. Tekrarlamayýnýz.");
		SendAdmMessage("%s adlý kiþi reklama yasaklý kelime girdi.", GetNameEx(playerid));
        return 0;
    }
	
    new bizid = GetNearBiz(playerid), calisan = 0;
	for(new listitem = 0; listitem < MAX_WORK_SPACE; listitem++)
	{
	    for(new i; i < GetPlayerPoolSize(); i++)
	    {
		    if (PlayerInfo[i][pID] == BizWorkers[bizid][listitem][bizJobOn])
		    {
			    calisan = 1;
			    break;
	     	}
	    }	
	}	 
	if (bizid != -1 && BizInfo[bizid][bizOwnerID] != PlayerInfo[playerid][pID] && !calisan) return SendErrorMessage(playerid, "Kendine ait bir iþyerinde deðilsin.");


    pTemp[playerid][pAdvertTime] = gettime() + 300;

	foreach(new i : Player)
	{
		if(PlayerInfo[playerid][pSettings] & togAdv) continue;

	    if (strlen(params) > MAXLEN)
	    {
		    new pos = MAXLEN;

		    if (pos < MAXLEN-1) pos = MAXLEN;
                
			SendClientMessageEx(i, COLOR_GREENFORADVERT, "[%s] %.*s ...", BizInfo[bizid][bizName], pos, params);
			SendClientMessageEx(i, COLOR_GREENFORADVERT, "... %s (/igps %d)", params[pos], bizid);
	    }
	    else
	    {
  		    SendClientMessageEx(i, COLOR_GREENFORADVERT, "[%s] %s (/igps %d)", BizInfo[bizid][bizName], params, bizid);
	    }		
	}

	SendServerMessage(playerid, "Baþarýyla reklam verdiniz. Bir sonraki reklam için 300 saniye beklemelisiniz.");

   // SendDiscordAdvertisements(GetNameEx(playerid), PlayerInfo[playerid][pNumber], params);

	if (lastadvert >= MAX_LAST_ADVERT) lastadvert = 0;
	else lastadvert++;
	format(LastAdvertInfo[lastadvert][advertText], 144, "%s", params);
	LastAdvertInfo[lastadvert][adverttime] = gettime();
	LastAdvertInfo[lastadvert][advertnumber] = PlayerInfo[playerid][pNumber];
	return 1;
}

CMD:reklamlar(playerid, params[])
{
	return pc_cmd_sonreklam(playerid, "");
}

Advertisement_Nearest(playerid)
{
 	if (!IsPlayerLogged(playerid))	return -1;

	for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0 || BizInfo[i][bizType] != BIZ_ADVERT)	continue;
		if (PlayerToPoint(7.0,playerid,BizInfo[i][bizPosX], BizInfo[i][bizPosY], BizInfo[i][bizPosZ]) && GetWorld(playerid) == BizInfo[i][bizPosVW] && GetInterior(playerid) == BizInfo[i][bizPosInt])	return i;
	}
	
	return -1;
}

/*
stock DiscordLetterFixAdvert(info[])
{
    new namefix[256];
	ReplaceText(info, "ð", "(009)");
	ReplaceText(info, "Ð", "(0009)");
	ReplaceText(info, "ü", "(026)");
	ReplaceText(info, "Ü", "(0026)");
	ReplaceText(info, "þ", "(023)");
	ReplaceText(info, "Þ", "(0023)");
	ReplaceText(info, "ç", "(004)");
	ReplaceText(info, "Ç", "(0004)");
	ReplaceText(info, "ö", "(019");
	ReplaceText(info, "Ö", "(0019)");
	ReplaceText(info, "ý", "(011)");
	ReplaceText(info, "Ý", "(0012)");
    format(namefix, sizeof(namefix), info);
    return namefix;
}

stock SendDiscordAdvertisements(adv_poster[], adv_ph, adv_content[])
{
    new adv_command[256];

	ReplaceText(adv_poster, " ", "_");

    format(adv_command, sizeof(adv_command), "/adv %s %d %s", adv_poster, adv_ph, DiscordLetterFixAdvert(adv_content));
    DCC_SendChannelMessage(DCC_FindChannelById("1141521480644050954"), adv_command);
    return 1;
}*/