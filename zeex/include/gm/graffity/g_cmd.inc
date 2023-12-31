alias:graffiti("graffitiyap"); //��������
CMD:graffiti(playerid, params[])
{
    new option[16], parameters[145];
    if (sscanf(params, "s[16]S()[144]", option, parameters))
    {
        SendHelpMessage(playerid, "/graffiti [olustur / iptal]");
        return 1;
    }
    if (CompareStrings(option, "olustur"))
    {
        new g_text[33];
        if (sscanf(parameters, "s[32]", g_text))                                         return SendHelpMessage(playerid, "/graffiti olustur [yaz�]");
        if (strlen(g_text) > MAX_GRAFFITY_TEXT || strlen(g_text) < MIN_GRAFFITY_TEXT)    return SendErrorMessage(playerid, "Grafiti yaz�s� minimum %i, maksimum %i karakter olmal�d�r.", MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
        if (Graffity_GetFreeID() == -1)                                                  return SendErrorMessage(playerid, "Grafiti s�n�r� a��ld�. L�tfen daha sonra grafiti yapmay� deneyin.");
        if (AntiCheatGetWeapon(playerid) != 41)                                          return SendErrorMessage(playerid, "Elinizde bir sprey kutu olmal�.");
        if (GetPlayerVirtualWorld(playerid) != 0 && GetPlayerInterior(playerid) != 0)    return SendErrorMessage(playerid, "Interior i�inde bu yap�lamaz.");
        if (Graffity_GetAccepts(playerid) != -1) 
        {
            SendErrorMessage(playerid, "Halihaz�rda grafiti olu�turmu�sunuz ve bu grafiti hala inceleme a�amas�nda.");
            SendSyntaxMessage(playerid, "Yeni bir grafiti olu�turmadan �nce eski grafitinizin reddedilmesini veya onaylanmas�n� beklemelisiniz.");
            return 1;
        }
        if (Graffity_Nearest(playerid) != -1)        return SendErrorMessage(playerid, "Yak�n�n�zda bir grafiti bulunuyor.");
        if (Graffity_GetPlayerEdit(playerid) != -1)  return SendErrorMessage(playerid, "Zaten graffiti d�zenliyorsunuz");
        if (IsPlayerInAnyVehicle(playerid))          return SendErrorMessage(playerid, "Bu i�lem i�in ara�ta olmamal�s�n�z.");
        if (PlayerInfo[playerid][pInjured])          return SendErrorMessage(playerid, "Yaral� veya �l� durumundayken grafiti �izemezsiniz.");
        
        Graffity_CreateTemporary(playerid, g_text);
        return 1;
    }
    else if (CompareStrings(option, "iptal"))
    {
        if (Graffity_GetPlayerEdit(playerid) == -1)      return SendErrorMessage(playerid, "Grafiti d�zenlemiyorsunuz.");
        if (!GetPVarInt(playerid, "Graffity:Spraying"))   return SendErrorMessage(playerid, "Grafiti �izmiyorsun.");
        
        SendSyntaxMessage(playerid, "Grafiti olu�turma i�lemi iptal edildi.");
        Graffity_DestroyTemporary(Graffity_GetPlayerEdit(playerid), 1);
        Graffity_ResetPlayer(playerid);
        UnFreezePlayer(playerid);
        pc_cmd_stopanim(playerid, "");
        return 1;
    }
    else
    {
        SendHelpMessage(playerid, "/graffiti [olustur / iptal]");
    }
    return 1;
}