Dialog:AccountRegister(playerid, response, listitem, inputtext[])
{
	if(!response)	KickEx(playerid);
	ClearChatbox(playerid, 50);

	if(isnull(inputtext) || strlen(inputtext) > 24 || strlen(inputtext) < 5) {
		Dialog_Show(playerid, AccountRegister, DIALOG_STYLE_INPUT, "Hesap kayd�", "�stedi�iniz kullan�c� ad�n� girin (24 karakter):\n{C7C7C7}�rnek: {FFFFFF}matta", ">>>", "");
		return SendErrorMessage(playerid, "Hesap ad�n�n uzunlu�u 5 ile 24 karakter aras�nda olmal�d�r!");
	}
	
	if(strfind(inputtext, "/") != -1 || strfind(inputtext, "\\") != -1 ||
		strfind(inputtext, ":") != -1 || strfind(inputtext, "*") != -1 ||
		strfind(inputtext, "?") != -1 || strfind(inputtext, "\"") != -1 ||
		strfind(inputtext, "<") != -1 || strfind(inputtext, ">") != -1 ||
		strfind(inputtext, "|") != -1 || isnull(inputtext) || strfind(inputtext, " ") != -1)	{
		
		Dialog_Show(playerid, AccountRegister, DIALOG_STYLE_INPUT, "Hesap kayd�", "�stedi�iniz kullan�c� ad�n� girin (24 karakter):\n{C7C7C7}�rnek: {FFFFFF}matta", ">>>", "");
		return SendErrorMessage(playerid, "Hesap ad�nda ge�ersiz karakterler var!");
	}

	SetPVarString(playerid, #AccountName, inputtext);
	
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `login` = '%e'", inputtext);
	mysql_tquery(dbHandle, query, "CheckAccName", "i", playerid);
	return 1;
}

this::CheckAccName(playerid)
{
	if(cache_num_rows()) {
		SendErrorMessage(playerid, "Bu kullan�c� ad� kullan�l�yor!");
		Dialog_Show(playerid, AccountRegister, DIALOG_STYLE_INPUT, "Hesap kayd�", "�stedi�iniz kullan�c� ad�n� girin (24 karakter):\n{C7C7C7}�rnek: {FFFFFF}matta", ">>>", "");
		return 1;
	}

	ClearChatbox(playerid, 50);
	SendServerMessage(playerid, "Ge�erli bir eposta adresi giriniz.");
	Dialog_Show(playerid, EmailRegister, DIALOG_STYLE_INPUT, "Hesap kayd�", "E-posta:", ">>>", "");
	return 1;
}

Dialog:EmailRegister(playerid, response, listitem, inputtext[])
{
	if(!response)	KickEx(playerid);
	ClearChatbox(playerid, 50);
	
	SetPVarString(playerid, #EmailName, inputtext);

	SendServerMessage(playerid, "Bir �ifre gir:");

	Dialog_Show(playerid, PassRegister, DIALOG_STYLE_PASSWORD, "Hesap kayd�", "G��l� bir parola olu�turun ve girin:", ">>>", "");
	return 1;
}

Dialog:PassRegister(playerid, response, listitem, inputtext[])
{
	if(!response)	KickEx(playerid);

    if(strlen(inputtext) < 6 || strlen(inputtext) > 32)
    {
        Dialog_Show(playerid, PassRegister, DIALOG_STYLE_PASSWORD, "{FFFFFF} Yeni �ifre", "{FFFFFF} �ifre gir:", ">>>", "");
		return SendErrorMessage(playerid, "�ifre en az 6 en fazla 32 karakter olmal�d�r.");
	}

	for(new i = 0; i < strlen(inputtext); i++)
	{
		switch(inputtext[i])
		{
			case '!', '@', '#', '$','%','^','&','*','(',')','_','+','=','|','[',']','{','}','-','.','`','~','<','>','?',',','/':
			{
			    Dialog_Show(playerid, PassRegister, DIALOG_STYLE_PASSWORD,"Yeni �ifre", "�ifre gir:", ">>>", "");
				return SendErrorMessage(playerid, "Ge�ersiz karakterler kulland�n�z.");
			}
			default: continue;
		}
	}

	new query[512], pass[129], ip_reg[8], name[24], email[24];

	GetPlayerIp(playerid, ip_reg, sizeof(ip_reg));
	GetPVarString(playerid, #AccountName, name, 24);
	GetPVarString(playerid, #EmailName, email, 24);
	
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `accounts` (`login`,`password`,`email`,`reg_ip`,`reg_date`) VALUES ('%s','%e','%e','%s','%e')", MD5_Hash(inputtext), pass, email, ip_reg, get_date("%dd/%mm/%yyyy, %hh:%ii", gettime()));
	mysql_tquery(dbHandle, query);
	
	ClearChatbox(playerid, 50);
	SendServerMessage(playerid, "Tebrikler, ba�ar�yla bir hesap kaydettiniz! Biraz bekle...");

	SetPlayerName(playerid, name);

	SetTimerEx("CheckAccount", 1500, false, "i", playerid);
	return 1;
}

Dialog:CreateCharacter(playerid, response, listitem, inputtext[])
{
	if(!response)	return ShowCharacterMenu(playerid);

	if(strfind(inputtext, "/") != -1 || strfind(inputtext, "\\") != -1 ||
		strfind(inputtext, ":") != -1 || strfind(inputtext, "*") != -1 ||
		strfind(inputtext, "?") != -1 || strfind(inputtext, "\"") != -1 ||
		strfind(inputtext, "<") != -1 || strfind(inputtext, ">") != -1 ||
		strfind(inputtext, "|") != -1 || isnull(inputtext) || strfind(inputtext, " ") != -1)	{
		Dialog_Show(playerid, CreateCharacter, DIALOG_STYLE_INPUT, "Karakter olu�tur", "Karakterin ad�n� girin:", ">>>", "Geri D�n");
		return SendErrorMessage(playerid, "Karakter ad�nda ge�ersiz karakterler bulunuyor!");
	}
	
	if(!RPnamecheck(inputtext)) {
		Dialog_Show(playerid, CreateCharacter, DIALOG_STYLE_INPUT, "Karakter olu�tur", "Karakterin ad�n� girin:", ">>>", "Geri D�n");
		return SendErrorMessage(playerid, "Karakter ad�nda ge�ersiz karakterler bulunuyor!");
	}

	new underline=0, maxname = strlen(inputtext);

    for(new i=0; i<maxname; i++)
    {
       if(inputtext[i] == '_') underline ++;
    }
    if(underline != 1) return 0;
    inputtext[0] = toupper(inputtext[0]);
    for(new x=1; x<maxname; x++)
    {
        if(inputtext[x] == '_') inputtext[x+1] = toupper(inputtext[x+1]);
        else if(inputtext[x] != '_' && inputtext[x-1] != '_') inputtext[x] = tolower(inputtext[x]);
    }

	SetPVarString(playerid, #CharacterName, inputtext);

	const MAX_SKINS = 312;
    new subString[16];
    static string[MAX_SKINS * sizeof(subString)];

    if (string[0] == EOS) {
        for (new i; i < MAX_SKINS; i++) {
            format(subString, sizeof(subString), "%i\tID: %i\n", i, i);
            strcat(string, subString);
        }
    }

    Dialog_Show(playerid, CreationCharSkinSel, DIALOG_STYLE_PREVIEW_MODEL, "Karakter skininizi se�in", string, "Sec", "�ptal");
	return 1;
}

Dialog:CreationCharSkinSel(playerid, response, listitem, inputtext[])
{
	if (!response) ShowCharacterMenu(playerid);

	new name[MAX_PLAYER_NAME], query[78 - 2 - 2 - 2 + 4 + MAX_PLAYER_NAME + 3];
	GetPVarString(playerid, #CharacterName, name, 24);

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `users` (`accountid`,`name`,`skin`,`status`) VALUES (%i,'%e',%i,1)", PlayerInfo[playerid][pAccID], name, listitem);
	mysql_tquery(dbHandle, query);

	ShowCharacterMenu(playerid);
}

Dialog:Login(playerid, response, listitem, inputtext[])
{
	if (!response)	
	{
		SendSyntaxMessage(playerid, "Sunucudan ayr�ld�n�z.");
  		KickEx(playerid);
	    return 1;
	}

	if (isnull(inputtext))
	{	
		static const str_size[] = "{c7c3c3}LIBERTY:\t{FFFFFF}Giri� yapmak i�in 5 dakikan�z var\n\
								   {c7c3c3}�PUCU:\t\t{FFFFFF}Hesap �ifrenizi kurtarabilirsiniz\n\
								   \t\tForum: {c7c3c3}"WeburlName"\n\
								   \t\t{FFFFFF}UCP k�sm�na eri�ebilirsin\n\n\
								   �ifrenizi girin:"; 
		new mes[sizeof(str_size)+103];
		
		if (pTemp[playerid][pLoggedTry] != 0) format(mes, sizeof(mes), "{FF6347}[ ! ] {FFFFFF}Yanl�� �ifre girdiniz!\n{FF6347}[ ! ] {FFFFFF}Kalan hak: {FF6347}%d\n\n%s", 3-pTemp[playerid][pLoggedTry], str_size);	
		else format(mes, sizeof(mes), str_size);
		
	    
		Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, ""ProjectName"", mes, "Giri� Yap", "�ptal");
		return 1;
	}

	new query[128 + 129];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `accounts` WHERE `forum_id` = %i AND `password`='%e'", PlayerInfo[playerid][pAccID], MD5_Hash(inputtext));
	mysql_tquery(dbHandle, query, "LoginPlayer", "i", playerid);
	return 1;
}

Dialog:CustomizationVerify(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strfind(inputtext, "Evet", true) != -1)
		{
			mysql_tquery(dbHandle, sprintf("UPDATE users SET status = 1 WHERE id = '%d'", GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));

			SM1(playerid, "Karakteriniz olu�turuldu. Giri� yap tu�u ile giri� yapabilirsiniz.");
			SelectTextDraw(playerid, COLOUR_DANDELION);
		}

		CustomizeCharacter(playerid, CUSTOMIZATION_VERIFY + 1);
	}

	else CustomizeCharacter(playerid, CUSTOMIZATION_VERIFY - 1);

	return 1;
}

Dialog:CustomizationOrigin(playerid, response, listitem, inputtext[])
{
	if(response)
	{	
		mysql_tquery(dbHandle, sprintf("UPDATE users SET origin = '%d' WHERE id = '%d'", GetOriginID(inputtext), GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));
		PlayerInfo[playerid][pOrigin] = GetOriginID(inputtext);

		SM1(playerid, "K�keniniz %s olarak belirlendi.", inputtext);
		CustomizeCharacter(playerid, CUSTOMIZATION_ORIGIN + 1);
	}	

	else CustomizeCharacter(playerid, CUSTOMIZATION_ORIGIN - 1);

	return 1;
}

Dialog:CustomizationAge(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new age;

		if(sscanf(inputtext, "d", age))
			return CustomizeCharacter(playerid, CUSTOMIZATION_AGE);

		if(age < MIN_CHARACTER_AGE || age > MAX_CHARACTER_AGE)
			return CustomizeCharacter(playerid, CUSTOMIZATION_AGE);
	
		mysql_tquery(dbHandle, sprintf("UPDATE users SET age = '%d' WHERE id = '%d'", age, GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));
		PlayerInfo[playerid][pAge] = age;

		SM1(playerid, "Ya��n�z %d olarak belirlendi.", age);
		CustomizeCharacter(playerid, CUSTOMIZATION_AGE + 1);
	}

	else CustomizeCharacter(playerid, CUSTOMIZATION_AGE - 1);

	return 1;
}

Dialog:CustomizationGender(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strfind(inputtext, "Erkek", true) != -1)
		{
			PlayerInfo[playerid][pSex] = 1;
		}

		else if(strfind(inputtext, "Kad�n", true) != -1)
		{
			PlayerInfo[playerid][pSex] = 2;
		}

		else return CustomizeCharacter(playerid, CUSTOMIZATION_GENDER);
	
		mysql_tquery(dbHandle, sprintf("UPDATE users SET sex = '%d' WHERE id = '%d'", PlayerInfo[playerid][pSex], GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));

		SM1(playerid, "Cinsiyetiniz %s olarak belirlendi.", inputtext);
		CustomizeCharacter(playerid, CUSTOMIZATION_GENDER + 1);
	}

	else CustomizeCharacter(playerid, CUSTOMIZATION_GENDER - 1);

	return 1;
}

Dialog:CustomizationRace(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strfind(inputtext, "Beyaz", true) != -1)
		{
			PlayerInfo[playerid][pRace] = 1;
		}

		else if(strfind(inputtext, "Siyah", true) != -1)
		{
			PlayerInfo[playerid][pRace] = 2;
		}

		else return CustomizeCharacter(playerid, CUSTOMIZATION_RACE);
	
		mysql_tquery(dbHandle, sprintf("UPDATE users SET race = '%d' WHERE id = '%d'", PlayerInfo[playerid][pRace], GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));

		SM1(playerid, "Ten renginiz %s olarak belirlendi.", inputtext);
		CustomizeCharacter(playerid, CUSTOMIZATION_RACE + 1);
	}

	else CustomizeCharacter(playerid, CUSTOMIZATION_RACE - 1);

	return 1;
}

Dialog:CustomizationSkinSelect(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new model_id = strval(inputtext);

		mysql_tquery(dbHandle, sprintf("UPDATE users SET skin = '%d' WHERE id = '%d'", model_id, GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID)));

		CustomizeCharacter(playerid, CUSTOMIZATION_SKIN + 1);
	}

	else CustomizeCharacter(playerid, CUSTOMIZATION_SKIN - 1);

	return 1;
}