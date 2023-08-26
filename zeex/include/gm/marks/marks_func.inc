forward LoadDynamicMarks();
forward OnLoadPlayerMarks(playerid);

public LoadDynamicMarks()
{
    new rows = cache_num_rows(), time = GetTickCount(), total, id;

    if (!rows)   return print("[Marks] Kayit bulunamadi.");

    for(new i = 0; i < rows; i++)
    {
        if (i >= MAX_MARKS) break;
        cache_get_value_int(i, "id", id);
        cache_get_value(i, "text", E_MARKS[id][mText], 196);
        cache_get_value(i, "creator", E_MARKS[id][mCreator], 32);
        cache_get_value(i, "c_date", E_MARKS[id][mCreateDate], 64);
        cache_get_value_float(i, "posx", E_MARKS[id][mPosX]);
        cache_get_value_float(i, "posy", E_MARKS[id][mPosY]);
        cache_get_value_float(i, "posz", E_MARKS[id][mPosZ]);
        cache_get_value_int(i, "interior", E_MARKS[id][mInt]);
        cache_get_value_int(i, "world", E_MARKS[id][mVW]);

        E_MARKS[id][mON] = 1;
        E_MARKS[id][mLabel] = CreateDynamic3DTextLabel(E_MARKS[i][mText], 0xFFFFFFFF, E_MARKS[i][mPosX], E_MARKS[i][mPosY], E_MARKS[i][mPosZ], 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, E_MARKS[i][mVW], E_MARKS[i][mInt]);

        total++;
    }

    printf("[Marks] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
    return 1;
}

public OnLoadPlayerMarks(playerid)
{
    new rows = cache_num_rows();

    if (!rows) return 1;

    for(new i = 0; i < rows; i++)
    {
        cache_get_value_int(i, "id", PlayerInfo[playerid][pMark][i]);
    }
    return 1;
}

LoadPlayerMarks(playerid)
{
    new query[196];
    mysql_format(dbHandle, query, sizeof(query), "SELECT `id` FROM `marks` WHERE `creator` = '%e' LIMIT %i", GetNameEx(playerid), MAX_PLAYER_MARKS);
    mysql_tquery(dbHandle, query, "OnLoadPlayerMarks", "d", playerid);
    return 1;
}

Mark_Nearest(playerid)
{
    for(new i = 0; i < MAX_MARKS; i++)
    {
        if (E_MARKS[i][mON])
        {
            if (IsPlayerInRangeOfPoint(playerid, 5.0, E_MARKS[i][mPosX], E_MARKS[i][mPosY], E_MARKS[i][mPosZ]) && GetInterior(playerid) == E_MARKS[i][mInt] && GetWorld(playerid) == E_MARKS[i][mVW]) 
            {
                return i;
            }
        }
    }
    return -1;
}

Mark_GetFreeID()
{
    for(new i = 0; i < MAX_MARKS; i++)
    {
        if (!E_MARKS[i][mON]) return i;
    }
    return -1;
}

Mark_GetPlayerFreeSlot(playerid)
{
    for(new i = 0; i < MAX_PLAYER_MARKS; i++)
    {
        if (PlayerInfo[playerid][pMark][i] == -1) return i;
    }
    return -1;
}

CreateDynamicMark(playerid, mark_id, mark_text[])
{
    new Float:x, Float:y, Float:z;
    
    GetPlayerPos(playerid, x, y, z);

    E_MARKS[mark_id][mID] = mark_id;
    format(E_MARKS[mark_id][mText], 196, "%s\n(( %s ))", mark_text, GetNameEx(playerid));
    format(E_MARKS[mark_id][mCreator], 32, "%s", GetNameEx(playerid));
    format(E_MARKS[mark_id][mCreateDate], 64, "%s", GetFullDate());
    E_MARKS[mark_id][mPosX] = x;
    E_MARKS[mark_id][mPosY] = y;
    E_MARKS[mark_id][mPosZ] = z;
    E_MARKS[mark_id][mInt] = GetInterior(playerid);
    E_MARKS[mark_id][mVW] = GetWorld(playerid);

    E_MARKS[mark_id][mON] = 1;
    E_MARKS[mark_id][mLabel] = CreateDynamic3DTextLabel(E_MARKS[mark_id][mText], 0xFFFFFFFF, E_MARKS[mark_id][mPosX], E_MARKS[mark_id][mPosY], E_MARKS[mark_id][mPosZ], 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, E_MARKS[mark_id][mVW], E_MARKS[mark_id][mInt]);

    new query[512];
    mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `marks` (`id`, `text`, `creator`, `c_date`, `posx`, `posy`, `posz`, `interior`, `world`) VALUES (%i, '%s', '%s', '%s', %f, %f, %f, %i, %i)",
    mark_id, E_MARKS[mark_id][mText], E_MARKS[mark_id][mCreator], E_MARKS[mark_id][mCreateDate], E_MARKS[mark_id][mPosX], E_MARKS[mark_id][mPosY], E_MARKS[mark_id][mPosZ], E_MARKS[mark_id][mInt], E_MARKS[mark_id][mVW]);
    mysql_tquery(dbHandle, query);
}

DestroyDynamicMark(markid)
{
    foreach(new i : Player)
    {
        if (CompareStrings(E_MARKS[markid][mCreator], GetNameEx(i)))
        {
            for(new j = 0; j < MAX_PLAYER_MARKS; j++)
            {
                if (PlayerInfo[i][pMark][j] == markid)
                {
                     PlayerInfo[i][pMark][j] = -1;
                }
            }   
        }
    }

    E_MARKS[markid][mID] = -1;
    E_MARKS[markid][mText][0] = EOS;
    E_MARKS[markid][mCreator][0] = EOS;
    E_MARKS[markid][mCreateDate][0] = EOS;
    E_MARKS[markid][mON] = 0;
    E_MARKS[markid][mPosX] = 0.0;
    E_MARKS[markid][mPosY] = 0.0;
    E_MARKS[markid][mPosZ] = 0.0;
    E_MARKS[markid][mInt] = 0;
    E_MARKS[markid][mVW] = 0;

    if (IsValidDynamic3DTextLabel(E_MARKS[markid][mLabel])) DestroyDynamic3DTextLabel(E_MARKS[markid][mLabel]);
    
    new query[256];
    mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `marks` WHERE `id` = %i", markid);
    mysql_tquery(dbHandle, query);
    return 1;
}