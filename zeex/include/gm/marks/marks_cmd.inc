CMD:mark(playerid, params[]) //ìåòêà
{
    if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
    
    new option[16], string[145];
    if (sscanf(params, "s[16]S()[144]", option, string))
    {
        SendHelpMessage(playerid, "/mark [ayarlar]");
        SendSyntaxMessage(playerid, "list / create / destroy / edit");
        return 1;
    }

    if (CompareStrings(option, "list"))
    {
        new list[512] = "{FFFFFF}Slot\t{FFFFFF}ID\n";
        for(new i = 0; i < MAX_PLAYER_MARKS; i++)
        {
            new markid = PlayerInfo[playerid][pMark][i];
            if (PlayerInfo[playerid][pMark][i] != -1)
            {
                format(list, sizeof(list), "%s%i\t%i\n", list, i + 1, markid);
            }
            else
            {
                format(list, sizeof(list), "%s%i\t%s\n", list, i + 1, RIGHT_NO);
            }
        }
        Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Mark listesi", list, "Kapat", "");
        return 1;
    }
    else if (CompareStrings(option, "create"))
    {
        new m_mes[129];
        if (sscanf(string, "s[128]",  m_mes))                    return SendHelpMessage(playerid, "/mark create [metin]");
        if (strlen(m_mes) > 128)                                 return SendErrorMessage(playerid, "Metin maksimum 128 karakter olmalýdýr.");

        new markid = Mark_GetPlayerFreeSlot(playerid);

        if (markid == -1)                                        return SendErrorMessage(playerid, "Daha fazla mark oluþturamazsýnýz: %i", MAX_PLAYER_MARKS);
        if (Mark_GetFreeID() == -1)                              return SendErrorMessage(playerid, "Etiket sýnýrý aþýldý. Bir süre sonra yeni bir etiket oluþturmaya çalýþýn.");
        if (Mark_Nearest(playerid) != -1)                        return SendErrorMessage(playerid, "Yakýnýnýzda bir iþaret var.");

        new mark = Mark_GetFreeID();

        PlayerInfo[playerid][pMark][markid] = mark;
        CreateDynamicMark(playerid, mark, m_mes);
        SendSyntaxMessage(playerid, "Etiket oluþturuldu: [ID: %i | SLOT: %i]", mark, markid + 1);
        return 1;
    }
    else if (CompareStrings(option, "destroy"))
    {
        new markid = Mark_Nearest(playerid);
        
        if (markid == -1)                                                    return SendErrorMessage(playerid, "Yakýnýnýzda marker bulunmuyor.");
        if (!CompareStrings(E_MARKS[markid][mCreator], GetNameEx(playerid)))  return SendErrorMessage(playerid, "Bu etiket size ait deðil.");

        DestroyDynamicMark(markid);
        SendSyntaxMessage(playerid, "Etiket silindi [ID: %i].", markid);
        return 1;
    }
    else if (CompareStrings(option, "edit"))
    {
        new m_mes[129];
        if (sscanf(string, "s[128]", m_mes))         return SendHelpMessage(playerid, "/mark edit [yeni metin]");
        if (strlen(m_mes) > 128)                     return SendErrorMessage(playerid, "Metin maksimum 128 karakter olmalýdýr.");

        new markid = Mark_Nearest(playerid);

        if (markid == -1)                                                                    return SendErrorMessage(playerid, "Yakýnýnýzda marker bulunmuyor.");
        if (!CompareStrings(E_MARKS[markid][mCreator], GetNameEx(playerid)))                 return SendErrorMessage(playerid,"Bu etiket size ait deðil.");

        format(E_MARKS[markid][mText], 128, "%s\n(( %s ))", m_mes, GetNameEx(playerid));
        SQL_SetString("marks", "text", E_MARKS[markid][mText], markid);
        UpdateDynamic3DTextLabelText(E_MARKS[markid][mLabel], 0xFFFFFFFF, E_MARKS[markid][mText]);
        SendSyntaxMessage(playerid, "Etiketin metini deðiþtirildi. [ID: %i].", markid);
    }
    else 
    {
        SendHelpMessage(playerid, "/mark [ayarlar]");
        SendSyntaxMessage(playerid, "list/create/destroy/edit");
    }
    return 1;
}