Dialog:Graffity_CE(playerid, response, listitem, inputtext[])
{
    if (!response) return Dialog_Show(playerid, Graffity_CE_Cancel, DIALOG_STYLE_MSGBOX, "{FFFFFF}Grafiti oluþturmayý iptal et", "{FFFFFF}Graffiti oluþturma iþlemini iptal etmek istediðinizden emin misiniz?", "Evet", "Hayýr");

    new grafid = Graffity_GetPlayerEdit(playerid);
    switch(listitem)
    {
        case 0:
        {
            SetPVarInt(playerid, "Graffity:Showing", 1);
            SetPVarInt(playerid, "Graffity:Show", 8);
            SendSyntaxMessage(playerid, "Düzenleme penceresi 8 saniye sonra tekrar görünecektir.");
            SendSyntaxMessage(playerid, "Grafitiye yakýn durun.");
        }
        case 1:
        {
            Dialog_Show(playerid, Graffity_CE_Done, DIALOG_STYLE_MSGBOX, "{FFFFFF}Grafiti oluþturma", "{FFFFFF}Bu parametrelerle grafiti boyamak istediðinizden emin misiniz?", "Evet", "Hayýr");
        }
        case 2:
        {
            EditDynamicObject(playerid, E_GRAFFITY[grafid][gObject]);
            SetPVarInt(playerid, "Graffity:EditPos", 1);
            SendSyntaxMessage(playerid, "Kamerayý hareket ettirmek için {FF6347}SPACE {FFFFFF}tuþunu kullanabilirsiniz.");
        }
        case 3:
        {
            new graf_string[256];
            format(graf_string, sizeof(graf_string), "{FFFFFF}Geçerli metin: %s\n\n* Metin en az %i karakter, en fazla %i karakter aralýðýnda olmalýdýr.\n\nAþaðýdaki kutuya yeni metni girin:", E_GRAFFITY[grafid][gText], MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            Dialog_Show(playerid, Graffity_CE_Text, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - metni deðiþtir", graf_string, ">>>", "Geri Dön");
        }
        case 4:
        {
            Graffity_ShowPlayerEditDialog(playerid);
        }
        case 5:
        {
            new graf_string[196];
            graf_string[0] = EOS;

            for(new i = 0; i < MAX_GRAFFITY_COLORS; i++)
            {
                format(graf_string, sizeof(graf_string), "%s%s%s\n", graf_string, GRAFFITY_COLOR[i][color_dlg], GRAFFITY_COLOR[i][color_name]);
            }
            Dialog_Show(playerid, Graffity_CE_Color, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - renk seçimi", graf_string, "Seç", "Geri Dön");
        }
        case 6:
        {
            new graf_string[256];
            graf_string[0] = EOS;

            for(new i = 0; i < MAX_GRAFFITY_BACKS; i++)
            {
                format(graf_string, sizeof(graf_string), "%s%s%s\n", graf_string, GRAFFITY_BACK[i][color_dlg], GRAFFITY_BACK[i][color_name]);
            }
            Dialog_Show(playerid, Graffity_CE_BackColor, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - arka plan seçimi", graf_string, "Seç", "Geri Dön");
        }
        case 7:
        {
            new graf_string[256];
            graf_string[0] = EOS;

            for(new i = 0; i < MAX_GRAFFITY_FONTS; i++)
            {
                format(graf_string, sizeof(graf_string), "%s%s\n", graf_string, GRAFFITY_FONT[i][font_name]);

            }
            Dialog_Show(playerid, Graffity_CE_Font, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - yazý tipi seçimi", graf_string, "Seç", "Geri Dön");
        }
        case 8:
        {
            new graf_string[196];
            format(graf_string, sizeof(graf_string), "{FFFFFF}Þu anki boyutu: %i\n\n* Yazý tipi boyutu %i ile %i arasýnda olmalýdýr.\n\nAþaðýdaki kutuya yeni deðeri girin:", E_GRAFFITY[grafid][gFontSize], MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);
            Dialog_Show(playerid, Graffity_CE_FontSize, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - yazý tipi boyutu", graf_string, "Seç", "Geri Dön");
        }
        case 9:
        {
            Graffity_SetBold(grafid, !E_GRAFFITY[grafid][gBold]);
            Graffity_ShowPlayerEditDialog(playerid);
        }
    }
    return 1;
}

Dialog:Graffity_CE_Cancel(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (!response)   return Graffity_ShowPlayerEditDialog(playerid);

    Graffity_DestroyTemporary(grafid);
    Graffity_ResetPlayer(playerid);
    SendSyntaxMessage(playerid, "Graffiti creation has been canceled.");
    
    return 1;
}

Dialog:Graffity_CE_Done(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);

    if (!response) return Graffity_ShowPlayerEditDialog(playerid);
    Graffity_DestroyTemporary(playerid);
    SetPVarInt(playerid, "Graffity:Spraying", 1);
    FreezePlayer(playerid);
    ApplyAnimation(playerid,"SPRAYCAN","spraycan_full",4.0,1,0,0,0,0);
    SetPVarInt(playerid, "Graffity:SprayingTime", strlen(E_GRAFFITY[grafid][gText]));
    SendSyntaxMessage(playerid, "Grafiti çizmeyi durdurmak için komut kullanýn: /gr durdur");
    return 1;
}

Dialog:Graffity_CE_Text(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (response)
    {
        if (strlen(inputtext) > MAX_GRAFFITY_TEXT || strlen(inputtext) < MIN_GRAFFITY_TEXT)
        {
            SendErrorMessage(playerid, "Grafiti yazýsý minimum %i, maksimum %i karakter olmalýdýr.", MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            
            new graf_string[256];
            
            format(graf_string, sizeof(graf_string), "{FFFFFF}Geçerli metin: %s\n\n* Grafiti yazýsý minimum %i, maksimum %i karakter olmalýdýr.\n\nAþaðýdaki kutuya yeni metni girin:", E_GRAFFITY[grafid][gText], MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            Dialog_Show(playerid, Graffity_CE_Text, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - yazý deðiþtir", graf_string, ">>>", "Geri Dön");
            return 1;
        }

        Graffity_SetText(grafid, inputtext);
        Graffity_ShowPlayerEditDialog(playerid);
    }
    else 
    {
        Graffity_ShowPlayerEditDialog(playerid);
    }
    return 1;
}

Dialog:Graffity_CE_Color(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (response)
    {
        Graffity_SetColor(grafid, GRAFFITY_COLOR[listitem][color_data]);
        SetPVarInt(playerid, "Graffity:Color", listitem+1);
        Graffity_ShowPlayerEditDialog(playerid);
    }
    else 
    {
        Graffity_ShowPlayerEditDialog(playerid);
    }
    return 1;
}

Dialog:Graffity_CE_BackColor(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (response)
    {
        Graffity_SetBackColor(grafid, GRAFFITY_BACK[listitem][color_data]);
        SetPVarInt(playerid, "Graffity:Back", listitem+1);
        Graffity_ShowPlayerEditDialog(playerid);
    }
    else 
    {
        Graffity_ShowPlayerEditDialog(playerid);
    }
    return 1;
}

Dialog:Graffity_CE_Font(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (response)
    { 
        Graffity_SetFont(grafid, GRAFFITY_FONT[listitem][font_name]);
        SetPVarInt(playerid, "Graffity:Font", listitem+1);
        Graffity_ShowPlayerEditDialog(playerid);
    }
    else 
    {
        Graffity_ShowPlayerEditDialog(playerid);
    }
    return 1;
}

Dialog:Graffity_CE_FontSize(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid), fsz = strval(inputtext);
    if (response)
    {
        if (fsz > MAX_GRAFFITY_FONTSIZE || fsz < MIN_GRAFFITY_FONTSIZE)
        {
            SendErrorMessage(playerid, "Yazý tipi boyutu %i ile %i arasýnda olmalýdýr.", MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);

            new graf_string[196];

            format(graf_string, sizeof(graf_string), "{FFFFFF}Geçerli boyut: %i\n\n* Yazý tipi boyutu %i ile %i arasýnda olmalýdýr.\n\nYeni deðeri aþaðýdaki kutuya girin:", E_GRAFFITY[grafid][gFontSize], MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);
            Dialog_Show(playerid, Graffity_CE_FontSize, DIALOG_STYLE_INPUT, "{FFFFFF} Grafiti - yazý tipi boyutu", graf_string, "Seç", "Geri Dön");
            return 1;
        }

        Graffity_SetFontSize(grafid, fsz);
        Graffity_ShowPlayerEditDialog(playerid);
    }
    else 
    {
        Graffity_ShowPlayerEditDialog(playerid);
    }
    return 1;
}