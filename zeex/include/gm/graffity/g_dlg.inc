Dialog:Graffity_CE(playerid, response, listitem, inputtext[])
{
    if (!response) return Dialog_Show(playerid, Graffity_CE_Cancel, DIALOG_STYLE_MSGBOX, "{FFFFFF}Grafiti olu�turmay� iptal et", "{FFFFFF}Graffiti olu�turma i�lemini iptal etmek istedi�inizden emin misiniz?", "Evet", "Hay�r");

    new grafid = Graffity_GetPlayerEdit(playerid);
    switch(listitem)
    {
        case 0:
        {
            SetPVarInt(playerid, "Graffity:Showing", 1);
            SetPVarInt(playerid, "Graffity:Show", 8);
            SendSyntaxMessage(playerid, "D�zenleme penceresi 8 saniye sonra tekrar g�r�necektir.");
            SendSyntaxMessage(playerid, "Grafitiye yak�n durun.");
        }
        case 1:
        {
            Dialog_Show(playerid, Graffity_CE_Done, DIALOG_STYLE_MSGBOX, "{FFFFFF}Grafiti olu�turma", "{FFFFFF}Bu parametrelerle grafiti boyamak istedi�inizden emin misiniz?", "Evet", "Hay�r");
        }
        case 2:
        {
            EditDynamicObject(playerid, E_GRAFFITY[grafid][gObject]);
            SetPVarInt(playerid, "Graffity:EditPos", 1);
            SendSyntaxMessage(playerid, "Kameray� hareket ettirmek i�in {FF6347}SPACE {FFFFFF}tu�unu kullanabilirsiniz.");
        }
        case 3:
        {
            new graf_string[256];
            format(graf_string, sizeof(graf_string), "{FFFFFF}Ge�erli metin: %s\n\n* Metin en az %i karakter, en fazla %i karakter aral���nda olmal�d�r.\n\nA�a��daki kutuya yeni metni girin:", E_GRAFFITY[grafid][gText], MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            Dialog_Show(playerid, Graffity_CE_Text, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - metni de�i�tir", graf_string, ">>>", "Geri D�n");
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
            Dialog_Show(playerid, Graffity_CE_Color, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - renk se�imi", graf_string, "Se�", "Geri D�n");
        }
        case 6:
        {
            new graf_string[256];
            graf_string[0] = EOS;

            for(new i = 0; i < MAX_GRAFFITY_BACKS; i++)
            {
                format(graf_string, sizeof(graf_string), "%s%s%s\n", graf_string, GRAFFITY_BACK[i][color_dlg], GRAFFITY_BACK[i][color_name]);
            }
            Dialog_Show(playerid, Graffity_CE_BackColor, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - arka plan se�imi", graf_string, "Se�", "Geri D�n");
        }
        case 7:
        {
            new graf_string[256];
            graf_string[0] = EOS;

            for(new i = 0; i < MAX_GRAFFITY_FONTS; i++)
            {
                format(graf_string, sizeof(graf_string), "%s%s\n", graf_string, GRAFFITY_FONT[i][font_name]);

            }
            Dialog_Show(playerid, Graffity_CE_Font, DIALOG_STYLE_LIST, "{FFFFFF}Grafiti - yaz� tipi se�imi", graf_string, "Se�", "Geri D�n");
        }
        case 8:
        {
            new graf_string[196];
            format(graf_string, sizeof(graf_string), "{FFFFFF}�u anki boyutu: %i\n\n* Yaz� tipi boyutu %i ile %i aras�nda olmal�d�r.\n\nA�a��daki kutuya yeni de�eri girin:", E_GRAFFITY[grafid][gFontSize], MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);
            Dialog_Show(playerid, Graffity_CE_FontSize, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - yaz� tipi boyutu", graf_string, "Se�", "Geri D�n");
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
    SendSyntaxMessage(playerid, "Grafiti �izmeyi durdurmak i�in komut kullan�n: /gr durdur");
    return 1;
}

Dialog:Graffity_CE_Text(playerid, response, listitem, inputtext[])
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if (response)
    {
        if (strlen(inputtext) > MAX_GRAFFITY_TEXT || strlen(inputtext) < MIN_GRAFFITY_TEXT)
        {
            SendErrorMessage(playerid, "Grafiti yaz�s� minimum %i, maksimum %i karakter olmal�d�r.", MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            
            new graf_string[256];
            
            format(graf_string, sizeof(graf_string), "{FFFFFF}Ge�erli metin: %s\n\n* Grafiti yaz�s� minimum %i, maksimum %i karakter olmal�d�r.\n\nA�a��daki kutuya yeni metni girin:", E_GRAFFITY[grafid][gText], MIN_GRAFFITY_TEXT, MAX_GRAFFITY_TEXT);
            Dialog_Show(playerid, Graffity_CE_Text, DIALOG_STYLE_INPUT, "{FFFFFF}Grafiti - yaz� de�i�tir", graf_string, ">>>", "Geri D�n");
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
            SendErrorMessage(playerid, "Yaz� tipi boyutu %i ile %i aras�nda olmal�d�r.", MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);

            new graf_string[196];

            format(graf_string, sizeof(graf_string), "{FFFFFF}Ge�erli boyut: %i\n\n* Yaz� tipi boyutu %i ile %i aras�nda olmal�d�r.\n\nYeni de�eri a�a��daki kutuya girin:", E_GRAFFITY[grafid][gFontSize], MIN_GRAFFITY_FONTSIZE, MAX_GRAFFITY_FONTSIZE);
            Dialog_Show(playerid, Graffity_CE_FontSize, DIALOG_STYLE_INPUT, "{FFFFFF} Grafiti - yaz� tipi boyutu", graf_string, "Se�", "Geri D�n");
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