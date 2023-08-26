CMD:chopshop(playerid, params[])
{
    if (!IsAdminDuty(playerid) && !CheckAdmin(playerid, ADMIN_LEVEL_3) && !isLeader(playerid))
        return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!IsAdminDuty(playerid) && !CheckAdmin(playerid, ADMIN_LEVEL_3) && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_GANG && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_MAFIA)
        return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");

    if (GetChopshopID(playerid) != -1)
    {
        Dialog_Show(playerid, DIALOG_CHOPSHOP, DIALOG_STYLE_LIST, "Chopshop", "Chopshop sil\nAraç listesi güncelle\nChopshop istatistik\nYüzdeyi deðiþtir\nChopshop pozisyonu deðiþtir", "Seç", "<<");
    }
    else if (IsAdminDuty(playerid) && CheckAdmin(playerid, ADMIN_LEVEL_2) || !IsFactionHasChopShop(PlayerInfo[playerid][pFaction])) {
            Dialog_Show(playerid, DIALOG_CHOPSHOP, DIALOG_STYLE_LIST, "Chopshop", "Chopshop Oluþtur", "Seç", "<<");
    }
           
    return 1;
} //î