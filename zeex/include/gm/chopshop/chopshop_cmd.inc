CMD:chopshop(playerid, params[])
{
    if (!IsAdminDuty(playerid) && !CheckAdmin(playerid, ADMIN_LEVEL_3) && !isLeader(playerid))
        return SendErrorMessage(playerid, "Bu komutu kullanamazs�n�z.");
    if (!IsAdminDuty(playerid) && !CheckAdmin(playerid, ADMIN_LEVEL_3) && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_GANG && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_MAFIA)
        return SendErrorMessage(playerid, "Bu komutu kullanamazs�n�z.");

    if (GetChopshopID(playerid) != -1)
    {
        Dialog_Show(playerid, DIALOG_CHOPSHOP, DIALOG_STYLE_LIST, "Chopshop", "Chopshop sil\nAra� listesi g�ncelle\nChopshop istatistik\nY�zdeyi de�i�tir\nChopshop pozisyonu de�i�tir", "Se�", "<<");
    }
    else if (IsAdminDuty(playerid) && CheckAdmin(playerid, ADMIN_LEVEL_2) || !IsFactionHasChopShop(PlayerInfo[playerid][pFaction])) {
            Dialog_Show(playerid, DIALOG_CHOPSHOP, DIALOG_STYLE_LIST, "Chopshop", "Chopshop Olu�tur", "Se�", "<<");
    }
           
    return 1;
} //�