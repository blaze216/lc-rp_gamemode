CMD:ceset(playerid, params[])
{
    new i;

    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");
    if (!IsPlayerLogged(playerid))                   return SendNotConnected(playerid);
    if ((i = GetNearestCorpse(playerid)) == -1)      return SendErrorMessage(playerid, "�evrenizde ceset bulunamad�.");
  
    Dialog_Show(playerid, CorpseInfo, DIALOG_STYLE_MSGBOX, "Ceset hakk�nda bilgi", CorpInfo[i][cNote], "Se�enekler", "Kapat");
    return 1;
}//������� ������