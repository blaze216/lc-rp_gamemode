Graffity_PlayerTimer(playerid)
{
    if (GetPVarInt(playerid, "Graffity:Edit"))
    {
        if (GetPVarInt(playerid, "Graffity:Showing"))
        {
            if (GetPVarInt(playerid, "Graffity:Show"))
            {
                SetPVarInt(playerid, "Graffity:Show", GetPVarInt(playerid, "Graffity:Show")-1);
            }
            else 
            {
                if (!GetPVarInt(playerid, "Graffity:BackState"))
                {
                    DeletePVar(playerid, "Graffity:Show");
                    DeletePVar(playerid, "Graffity:Showing");
                    Graffity_ShowPlayerEditDialog(playerid);
                }
            }
        }
    }
    if (GetPVarInt(playerid, "Graffity:Edit"))
    {
        new grafid = Graffity_GetPlayerEdit(playerid);
        if (!IsPlayerInRangeOfPoint(playerid, GRAFFITY_DISTANCE_WARN, E_GRAFFITY[grafid][gPosX], E_GRAFFITY[grafid][gPosY], E_GRAFFITY[grafid][gPosZ]) || GetWorld(playerid) != E_GRAFFITY[grafid][gVW] || GetInterior(playerid) != E_GRAFFITY[grafid][gInterior])
        {
            if (!GetPVarInt(playerid, "Graffity:BackState"))
            {
                SetPVarInt(playerid, "Graffity:BackState", 1);
                SetPVarInt(playerid, "Graffity:BackTime", GRAFFITY_DESTROY_TIME);
                SendSyntaxMessage(playerid, "Düzenlemeye geri dönmek için %i saniyeniz var.", GRAFFITY_DESTROY_TIME);
            }
            else 
            {
                if (GetPVarInt(playerid, "Graffity:BackTime"))
                {
                    SetPVarInt(playerid, "Graffity:BackTime", GetPVarInt(playerid, "Graffity:BackTime") - 1);
                }
                else 
                {
                    SendSyntaxMessage(playerid, "Graffiti iptal edildi. ");
                    Graffity_DestroyTemporary(grafid, 1);
                    
                    Graffity_ResetPlayer(playerid);
                }
            }
        }
        else 
        {
            if (GetPVarInt(playerid, "Graffity:BackState"))
            {
                DeletePVar(playerid, "Graffity:BackState");
                DeletePVar(playerid, "Graffity:BackTime");
            }
        }
    }
    if (GetPVarInt(playerid, "Graffity:Spraying"))
    {
        if (GetPVarInt(playerid, "Graffity:SprayingTime"))
        {
            if (!PlayerInfo[playerid][pInjured] || GetPlayerAnimationIndex(playerid) != 1469) {
                SetPVarInt(playerid, "Graffity:SprayingTime", GetPVarInt(playerid, "Graffity:SprayingTime")-1);
                new mes[32];
                format(mes, sizeof(mes), "~y~Graffiti boyaniyor... %i", GetPVarInt(playerid, "Graffity:SprayingTime"));
                GameTextForPlayer(playerid, mes, 1000, 4);
            } else {
                Graffity_DestroyTemporary(Graffity_GetPlayerEdit(playerid), 1); 
                Graffity_ResetPlayer(playerid);

                SendSyntaxMessage(playerid, "Graffiti iptal edildi.");
            }
        }
        else 
        {
            new g_id = Graffity_GetPlayerEdit(playerid);
            SendSyntaxMessage(playerid, "Graffiti yönetici onayýndan geçtikten sonra herkese açýk þekilde görünecek.");
            Graffity_ResetPlayer(playerid);
            Graffity_Insert(g_id);
            E_GRAFFITY[g_id][gEditing] = 0;
            UnFreezePlayer(playerid);
            pc_cmd_stopanim(playerid, "");
        }
    }
    if (GetPVarInt(playerid, "Tester:Graffity"))
    {
        new grafid = GetPVarInt(playerid, "Tester:Graffity")-1;
        if (GetPVarInt(playerid, "Tester:GraffityTime"))
        {
            SetPVarInt(playerid, "Tester:GraffityTime", GetPVarInt(playerid, "Tester:GraffityTime") - 1);
        }
        else 
        {
            Graffity_DestroyTemporary(grafid);
            DeletePVar(playerid, "Tester:Graffity");
            DeletePVar(playerid, "Tester:GraffityTime");
            SendSyntaxMessage(playerid, "10 saniyelik süre sonrasýnda graffiti önizlemesi bitti.");
        }
    }
    return 1;
}

Graffity_OnPlayerDisconnect(playerid)
{
    new grafid = Graffity_GetPlayerEdit(playerid);
    if(grafid > -1)
    {
    if (GetPVarInt(playerid, "Graffity:Edit"))
    {
        Graffity_DestroyTemporary(grafid, 1);
    }
    if (GetPVarInt(playerid, "Graffity:Spraying"))
    {
        Graffity_DestroyTemporary(grafid, 1);
    }
    if (GetPVarInt(playerid, "Tester:Graffity"))
    {
        Graffity_DestroyTemporary(GetPVarInt(playerid, "Tester:Graffity") - 1);
    }
    }
    return 1;
}

Graf_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ,
	Float:oldRotX, Float:oldRotY, Float:oldRotZ;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if (GetPVarInt(playerid, "Graffity:EditPos") && response == EDIT_RESPONSE_CANCEL)
    {
        new graf_id = Graffity_GetPlayerEdit(playerid);

        Graffity_DestroyTemporary(Graffity_GetPlayerEdit(playerid), 1); // buraya bak kagyolbug

        if (E_GRAFFITY[graf_id][gEditing] && E_GRAFFITY[graf_id][gON] && E_GRAFFITY[graf_id][gObject] == objectid)
        {
            SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
            SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
            Graffity_ShowPlayerEditDialog(playerid);
            DeletePVar(playerid, "Graffity:EditPos");
        }
    }
    else if (GetPVarInt(playerid, "Graffity:EditPos") && response == EDIT_RESPONSE_FINAL)
    {
        new graf_id = Graffity_GetPlayerEdit(playerid);

        if (E_GRAFFITY[graf_id][gEditing] && E_GRAFFITY[graf_id][gON] && E_GRAFFITY[graf_id][gObject] == objectid)
        {
            E_GRAFFITY[graf_id][gPosX] = x;
            E_GRAFFITY[graf_id][gPosY] = y;
            E_GRAFFITY[graf_id][gPosZ] = z;
            E_GRAFFITY[graf_id][gRotX] = rx;
            E_GRAFFITY[graf_id][gRotY] = ry;
            E_GRAFFITY[graf_id][gRotZ] = rz;
            Graffity_ShowPlayerEditDialog(playerid);
            DeletePVar(playerid, "Graffity:EditPos");
        }
    }
    return 1;
}

Graffity_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `graffities`", "LoadDynamicGraffities");
}

Graffity_OnPlayerDeath(playerid)
{
    if (Graffity_GetPlayerEdit(playerid) != -1 || GetPVarInt(playerid, "Graffity:Spraying"))
    {
        SendSyntaxMessage(playerid, "Graffiti oluþturma iptal edildi."); //îòìåà
        Graffity_DestroyTemporary(Graffity_GetPlayerEdit(playerid), 1);
        Graffity_ResetPlayer(playerid);
    }
    return 1;
}