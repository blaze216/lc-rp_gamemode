alias:graffiti("graffitiyap"); //ãðàôôèòè
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
        if (sscanf(parameters, "s[32]", g_text))                                         return SendHelpMessage(playerid, "/graffiti olustur [yazý]");
        if (strlen(g_text) > MAX_GRAFFITY_TEXT || strlen(g_text) < MIN_GRAFFITY_TEXT)    return SendErrorMessage(playerid, "Grafiti yazýsý minimum %i, maksimum %i karakter olmalýdýr.", MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
        if (Graffity_GetFreeID() == -1)                                                  return SendErrorMessage(playerid, "Grafiti sýnýrý aþýldý. Lütfen daha sonra grafiti yapmayý deneyin.");
        if (AntiCheatGetWeapon(playerid) != 41)                                          return SendErrorMessage(playerid, "Elinizde bir sprey kutu olmalý.");
        if (GetPlayerVirtualWorld(playerid) != 0 && GetPlayerInterior(playerid) != 0)    return SendErrorMessage(playerid, "Interior içinde bu yapýlamaz.");
        if (Graffity_GetAccepts(playerid) != -1) 
        {
            SendErrorMessage(playerid, "Halihazýrda grafiti oluþturmuþsunuz ve bu grafiti hala inceleme aþamasýnda.");
            SendSyntaxMessage(playerid, "Yeni bir grafiti oluþturmadan önce eski grafitinizin reddedilmesini veya onaylanmasýný beklemelisiniz.");
            return 1;
        }
        if (Graffity_Nearest(playerid) != -1)        return SendErrorMessage(playerid, "Yakýnýnýzda bir grafiti bulunuyor.");
        if (Graffity_GetPlayerEdit(playerid) != -1)  return SendErrorMessage(playerid, "Zaten graffiti düzenliyorsunuz");
        if (IsPlayerInAnyVehicle(playerid))          return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýnýz.");
        if (PlayerInfo[playerid][pInjured])          return SendErrorMessage(playerid, "Yaralý veya ölü durumundayken grafiti çizemezsiniz.");
        
        Graffity_CreateTemporary(playerid, g_text);
        return 1;
    }
    else if (CompareStrings(option, "iptal"))
    {
        if (Graffity_GetPlayerEdit(playerid) == -1)      return SendErrorMessage(playerid, "Grafiti düzenlemiyorsunuz.");
        if (!GetPVarInt(playerid, "Graffity:Spraying"))   return SendErrorMessage(playerid, "Grafiti çizmiyorsun.");
        
        SendSyntaxMessage(playerid, "Grafiti oluþturma iþlemi iptal edildi.");
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