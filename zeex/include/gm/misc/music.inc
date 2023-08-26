enum MUSIC_ENUM
{
	mID,
	mName[64],
	mUrl[128]
}
new PlayerMusic[MAX_PLAYERS][MAX_PLAYER_MUSIC][MUSIC_ENUM];

forward OnMusicInsert(playerid, slot);
forward OnPlayerLoadMusic(playerid);

public OnMusicInsert(playerid, slot)
{
	PlayerMusic[playerid][slot][mID] = cache_insert_id();
	return 1;
}

public OnPlayerLoadMusic(playerid)
{
    for(new i; i != MAX_PLAYER_MUSIC; i++)
   	{
    	PlayerMusic[playerid][i][mID] = 0;
    	PlayerMusic[playerid][i][mUrl] =
    	PlayerMusic[playerid][i][mName] = EOS;
    }
    
    if (!cache_num_rows()) return 1;

    for(new i = 0; i < cache_num_rows(); i++)
	{
     	if (i > MAX_PLAYER_MUSIC) break;
	        
        cache_get_value_int(i, "id", PlayerMusic[playerid][i][mID]);
	    cache_get_value(i, "name", PlayerMusic[playerid][i][mName], 64);
	    cache_get_value(i, "url", PlayerMusic[playerid][i][mUrl], 156);
	}
	return 1;
}

ShowMusicList(playerid)
{
	new string[641];

    for(new i; i != MAX_PLAYER_MUSIC; i++)
   	{
    	if (PlayerMusic[playerid][i][mID] == 0)	format(string, sizeof(string), "%s\n{C3C3C3}Bir müzik linki ekle...", string);
		else									format(string, sizeof(string), "%s\n%s", string, PlayerMusic[playerid][i][mName]);
    }

	Dialog_Show(playerid, MusicList, DIALOG_STYLE_LIST, "Ses Kayýtlarý", string, "Seç", "Geri");
	return 1;
}

LoadPlayerMusic(playerid)
{
    new query[256];

	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `player_music` WHERE `userid` = %i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "OnPlayerLoadMusic", "i", playerid);
	return 1;
}

OnPlayerAddMusic(playerid, slot, name[], url[])
{
    new query[128 + 56 + 156];

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `player_music` (userid, name, url) VALUES (%i, '%e', '%e')", PlayerInfo[playerid][pID], name, url);
	mysql_tquery(dbHandle, query, "OnMusicInsert", "ii", playerid, slot);
	return 1;
}  



Dialog:MusicList(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    SetPVarInt(playerid, #edit_music, listitem);
    
    if (PlayerMusic[playerid][listitem][mID] == 0)
	{
		Dialog_Show(playerid, AddMusic, DIALOG_STYLE_INPUT, "Hazýr Müzik Kaydý", "{FFFFFF}Ses kaydý için bir baþlýk girin.\n\nÝzin verilen karakter listesi À-ß, A-Z, 0-9, \"-\", \"[\", \"]\", \"(\", \")\". Maksimum 64 karakter.", ">>>", "Geri Dön");
	}
	else
	{
		Dialog_Show(playerid, MyMusic, DIALOG_STYLE_LIST, PlayerMusic[playerid][listitem][mName], "Kaydý etkinleþtir\nGiriþi sil", "Seç", "Geri");
	}
	return 1;
}

Dialog:MyMusic(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowBoomboxMenu(playerid);
	    
	new music = GetPVarInt(playerid, #edit_music);

	if (listitem == 0)
	{
	    SendSyntaxMessage(playerid, "%s adlý ses kaydýný baþlattýnýz.", PlayerMusic[playerid][music][mName]);
	    ChangeUrlBoombox(playerid, PlayerMusic[playerid][music][mUrl]);
	    return 1;
	}
	
	SendSyntaxMessage(playerid, "%s adlý ses kayýdýný sildiniz.", PlayerMusic[playerid][music][mName]);
	
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `player_music` WHERE `id` = %i", PlayerMusic[playerid][music][mID]);
	mysql_tquery(dbHandle, query);

	PlayerMusic[playerid][music][mID] = 0;
	PlayerMusic[playerid][music][mName] = EOS;
	PlayerMusic[playerid][music][mUrl] = EOS;
	ShowMusicList(playerid);
	return 1;
}

Dialog:AddMusic(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowMusicList(playerid);

	if (isnull(inputtext) || strlen(inputtext) >= 128)
	{
		return Dialog_Show(playerid, AddMusic, DIALOG_STYLE_INPUT, "Hazýr Müzik Kaydý", "{FFFFFF}Ses kayýdý için bir baþlýk girin\n\nIzin verilen karakter listesi: À-ß, A-Z, 0-9, \"-\", \"[\", \"]\", \"(\", \")\". Maksimum 128 karakter.", ">>>", "Iptal");
	}

	for(new i = 0; i < strlen(inputtext); i++)
	{
		switch(inputtext[i])
		{
			case '!', '@', '#', '$','%','^','&','*','_','+','=','|','{','}','.','`','~','<','>','?',',','/':
			{
				Dialog_Show(playerid, AddMusic, DIALOG_STYLE_INPUT, "Hazýr Müzik Kaydý", "{FFFFFF}Ses kayýdý için bir baþlýk girin\n\nIzin verilen karakter listesi: À-ß, A-Z, 0-9, \"-\", \"[\", \"]\", \"(\", \")\". Maksimum 128 karakter.", ">>>", "Iptal");
				return 1;
			}
			default: continue;
		}
	}
	
	SetPVarString(playerid, #music_add, inputtext);
	Dialog_Show(playerid, AddMusic1, DIALOG_STYLE_INPUT, "Hazýr Müzik Kaydý", "{FFFFFF}Boombax'a linki girin.\nBoomboxu nasýl kullanacaðýnýzý forumdan görüntüleyebilirsiniz:\n"WeburlName"", "Ekle", "Iptal");
	return 1;
}

Dialog:AddMusic1(playerid, response, listitem, inputtext[])
{
	if (!response) return ShowMusicList(playerid);
		
	if (isnull(inputtext) || strlen(inputtext) >= 128)
	{
		Dialog_Show(playerid, AddMusic1, DIALOG_STYLE_INPUT, "Hazýr Müzik Kaydý", "Boombax'a linki girin.\nForumda nasýl URL ekleyebileceðinizi bulabilirsiniz:\n"WeburlName"", "Ekle", "Iptal");
		return 1;
	}
	//ìóçûêà
	new music = GetPVarInt(playerid, #edit_music);
	
	if (music < 0 || music >= MAX_PLAYER_MUSIC || PlayerMusic[playerid][music][mID] != 0) return SendErrorMessage(playerid, "Ses Kaydý Hatasý");

	GetPVarString(playerid, #music_add, PlayerMusic[playerid][music][mName], 64);
	DeletePVar(playerid, #music_add);
	format(PlayerMusic[playerid][music][mUrl], 128, inputtext);
	OnPlayerAddMusic(playerid, music, PlayerMusic[playerid][music][mName], PlayerMusic[playerid][music][mUrl]);
	ShowMusicList(playerid);

	return 1;
}