Dialog:ANTICHEAT_SETTINGS(playerid, response, listitem, inputtext[])
{ 
    if (!response)
    { 
        pAntiCheatSettingsPage{playerid} = 0;
        return 1;
    } 

    if (!strcmp(inputtext, AC_DIALOG_NEXT_PAGE_TEXT))
    { 
        pAntiCheatSettingsPage{playerid}++;
    } 
    else if (!strcmp(inputtext, AC_DIALOG_PREVIOUS_PAGE_TEXT))
    { 
        pAntiCheatSettingsPage{playerid}--;
    } 
    else
    { 
        pAntiCheatSettingsEditCodeId[playerid] = pAntiCheatSettingsMenuListData[playerid][listitem];
        return ShowPlayer_AntiCheatEditCode(playerid, pAntiCheatSettingsEditCodeId[playerid]);
    } 
    return ShowPlayer_AntiCheatSettings(playerid);
} 

Dialog:ANTICHEAT_EDIT_CODE(playerid, response, listitem, inputtext[])
{ 
    if (!response)
    { 
        pAntiCheatSettingsEditCodeId[playerid] = -1;
        return ShowPlayer_AntiCheatSettings(playerid);
    } 

    new
        item = pAntiCheatSettingsEditCodeId[playerid];

    if (AC_CODE_TRIGGER_TYPE[item] == listitem)
        return ShowPlayer_AntiCheatSettings(playerid);

    if (AC_CODE_TRIGGER_TYPE[item] == AC_CODE_TRIGGER_TYPE_DISABLED && listitem != AC_CODE_TRIGGER_TYPE_DISABLED)
        EnableAntiCheat(item, 1);

    AC_CODE_TRIGGER_TYPE[item] = listitem;

    new 
        sql_query[101 - 4 + 1 + 2]; 

    format(sql_query, sizeof(sql_query), "UPDATE "AC_TABLE_SETTINGS" SET `"AC_TABLE_FIELD_TRIGGER"` = '%d' WHERE `"AC_TABLE_FIELD_CODE"` = '%d'", 
        listitem, 
        item); 

    mysql_query(dbHandle, sql_query, false);
    return ShowPlayer_AntiCheatSettings(playerid);
} 