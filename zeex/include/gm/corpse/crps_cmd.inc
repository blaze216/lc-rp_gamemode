CMD:ceset(playerid, params[])
{
    new i;

    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");
    if (!IsPlayerLogged(playerid))                   return SendNotConnected(playerid);
    if ((i = GetNearestCorpse(playerid)) == -1)      return SendErrorMessage(playerid, "Çevrenizde ceset bulunamadý.");
  
    Dialog_Show(playerid, CorpseInfo, DIALOG_STYLE_MSGBOX, "Ceset hakkýnda bilgi", CorpInfo[i][cNote], "Seçenekler", "Kapat");
    return 1;
}//ñèñòåìà òðóïîâ