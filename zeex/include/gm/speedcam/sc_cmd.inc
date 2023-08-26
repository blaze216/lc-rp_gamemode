alias:hizkamerasi("speedcam");
CMD:hizkamerasi(playerid, params[])
{
    new option[16], secoption[128], faction = PlayerInfo[playerid][pFaction];

    if (!IsFactionPolice(faction))       return SendErrorMessage(playerid, "Bu komutu kullanmak için polis memuru olmalýsýnýz.");
    if (!PlayerInfo[playerid][pOnDuty])  return SendErrorMessage(playerid, "Bu komutu kullanmak için iþbaþýnda olmalýsýnýz.");

    if (sscanf(params, "s[16]S()[128]", option, secoption)) 
    {
        SendHelpMessage(playerid, "/speedcam [seçenekler]");
        SendHelpMessage(playerid, "ekle / kaldir / duzenle / liste");
        return 1;
    }

    if (CompareStrings(option, "ekle"))
    {
        new id = SC_GetFreeID(), sp_limit, sp_name[32], sp_near = GetNearestSpeed(playerid, 20.0), sp_zone[64];

        if (id == -1)                                        return SendErrorMessage(playerid, "Bütün kamera slotlarý dolu.");
        if (sp_near != -1)                                   return SendErrorMessage(playerid, "Bu yarýçapta zaten aktif bir radar var");
        if (PlayerInfo[playerid][pRank] < SC_MIN_INSTALL)    return SendErrorMessage(playerid, "Bu komutu kullanmak için %i yetkisinde olmalýsýnýz.", SC_MIN_INSTALL);
        if (sscanf(secoption, "d", sp_limit))                return SendHelpMessage(playerid, "/speedcam ekle [hýz limiti]");
        if (sp_limit <= 0 || sp_limit > SC_MAX_SPEED)        return SendErrorMessage(playerid, "Hýz limiti 1 ile %d arasýnda olmalýdýr.", SC_MAX_SPEED);

        GetPlayerPos(playerid, speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z]);
        GetPlayer2DZone(playerid, sp_zone, sizeof(sp_zone));

        format(speedcam[id][sc_name], 64, "%s %i", sp_zone, id);
        new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z); 

        speedcam[id][sc_speed] = sp_limit;
        speedcam[id][sc_x] = x;
        speedcam[id][sc_y] = y+1;
        speedcam[id][sc_z] = z;
		speedcam[id][sc_rx] = 0;
        speedcam[id][sc_ry] = 0;
        speedcam[id][sc_rz] = 0;
        speedcam[id][sc_int] = GetPlayerInterior(playerid);
        speedcam[id][sc_vw] = GetPlayerVirtualWorld(playerid);
        speedcam[id][sc_object] = CreateDynamicObject(18880, speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], speedcam[id][sc_rx], speedcam[id][sc_ry], speedcam[id][sc_rz], speedcam[id][sc_vw], speedcam[id][sc_int]);
        Iter_Add(speedcamObjects, id);

        speedcam[id][sc_areaid] = CreateDynamicSphere(speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], SC_DEF_RADIUS, speedcam[id][sc_vw], speedcam[id][sc_int]);

        AddSpeedcamToFile(id, sp_limit, sp_name, speedcam[id][sc_x], speedcam[id][sc_y], speedcam[id][sc_z], 0.0, 0.0, 0.0, speedcam[id][sc_int], speedcam[id][sc_vw]);
        SM2(playerid, "Hýz kamerasý oluþturuldu: [ID: %i] %s | Hýz limiti: %d.", id, speedcam[id][sc_name], sp_limit);
        SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "(( %s adlý kiþi %s hýz kamerasýný kurdu. | Hýz Limiti: %d. ))", GetName(playerid), speedcam[id][sc_name], sp_limit);
        return 1;
    }

    else if (CompareStrings(option, "kaldir"))
    {
        new sp_near = GetNearestSpeed(playerid, 20.0);
        
        if (sp_near == -1)                                   return SendErrorMessage(playerid, "Bu yarýçapta herhangi bir hýz kamerasý yok.");
        if (PlayerInfo[playerid][pRank] < SC_MIN_INSTALL)    return SendErrorMessage(playerid, "Bu komutu kullanmak için %i yetkisinde olmalýsýnýz.", SC_MIN_INSTALL);

        if (IsValidDynamicObject(speedcam[sp_near][sc_object]))
        {
            DestroyDynamicObject(speedcam[sp_near][sc_object]);
            speedcam[sp_near][sc_object] = INVALID_OBJECT_ID;
        }

        new sql_query[256];

        SendWarningMessage(playerid, "Kamerayý kaldýrdýn. [ID: %i | %s].", sp_near, speedcam[sp_near][sc_name]);
        SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "(( %s adlý kiþi hýz kamerasýný [%s] kaldýrdý. ))", GetName(playerid), speedcam[sp_near][sc_name]);

        speedcam[sp_near][sc_name] = EOS;
        Iter_Remove(speedcamObjects, sp_near);
        
        mysql_format(dbHandle, sql_query, sizeof(sql_query), "DELETE FROM `speedcams` WHERE `id` = %i", sp_near);
        mysql_tquery(dbHandle, sql_query);
        return 1;
    }

    else if (CompareStrings(option, "duzenle"))
    {
        new sp_near = GetNearestSpeed(playerid, 15.0), thirdoption[64], fouroption[64];

        if (sp_near == -1)                                   return SendErrorMessage(playerid, "Bu yarýçapta herhangi bir hýz kamerasý yok.");   
        if (PlayerInfo[playerid][pRank] < SC_MIN_INSTALL)    return SendErrorMessage(playerid, "Bu komutu kullanmak için %i yetkisinde olmalýsýnýz.", SC_MIN_INSTALL);
        
        if (sscanf(secoption, "s[64]S()[64]", thirdoption, fouroption))        
        {
            SendHelpMessage(playerid, "/sc duzenle [ayarlar]");
            SendHelpMessage(playerid, "pozisyon/limit");
            return 1;
        }

        else if (CompareStrings(thirdoption, "limit"))
        {
            new sp_limit;

            if (sscanf(fouroption, "d", sp_limit))           return SendHelpMessage(playerid, "/sc edit limit [hýz limiti]");
            if (sp_limit <= 0 || sp_limit > SC_MAX_SPEED)    return SendErrorMessage(playerid, "Hýz limiti 1 ile %d arasýnda olmalýdýr.", SC_MAX_SPEED);

            speedcam[sp_near][sc_speed] = sp_limit;
            SQL_SetInteger("speedcams", "speed", speedcam[sp_near][sc_speed], speedcam[sp_near][sc_id]);
            SendSyntaxMessage(playerid, "Yakýnýnýzda bulunan hýz kamerasýnýn limitini deðiþtirdiniz: %s [ID: %i] | Yeni Limit: %d.", speedcam[sp_near][sc_name], sp_near, sp_limit);
            SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "(( %s adlý kiþi hýz kamerasýnýn limiti deðiþtirdi: %s [ID: %i]| Yeni Limit: %d. ))", GetName(playerid), speedcam[sp_near][sc_name], sp_near, sp_limit);
            return 1;
        }

        else if (CompareStrings(thirdoption, "pozisyon"))
        {
            SetPVarInt(playerid, "SC:ID", sp_near + 1);
            SetPVarInt(playerid, "SC:Edit", 1);
            EditDynamicObject(playerid, speedcam[sp_near][sc_object]);
            return 1;
        }
    }

    else if (CompareStrings(option, "liste"))
    {
		new dialog_header[96] = "{FFFFFF}Kamera\t{FFFFFF}ID\t{FFFFFF}Hýz Limiti\n", dialog_body[3072];

		format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

        for(new i = 0; i < Iter_Count(speedcamObjects); i++)
		{
			format(dialog_body, sizeof(dialog_body), "%s%s\t%i\t%d\n", dialog_body, speedcam[i][sc_name], i, speedcam[i][sc_speed]);
		}

		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST_HEADERS, "{FFFFFF}Kamera listesi", dialog_body, "Kapat", "");
    }  
    return 1;
}//î