CMD:avukatizni(playerid, params[])
{
	new userid;

	if (sscanf(params,"u",userid))										return SendHelpMessage(playerid, "/avukatizni [ID / Karakter Ad�]"); //Komut
	if (!IsPlayerFactionCity(playerid))									return SendErrorMessage(playerid, "Bu komutu kullanamazs�n�z.");
    if (!isLeader(playerid))											return SendErrorMessage(playerid, "Birlik yetkilisi de�ilsiniz.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Oyuncu birli�inize �ye de�il.");

	if (PlayerInfo[userid][pLawyer] == 0)
	{
		PlayerInfo[userid][pLawyer] = 1;
		SendSyntaxMessage(userid, "%s %s adl� ki�i size avukat lisans� verdi.", GetRankName(playerid), GetNameEx(playerid));
		SendSyntaxMessage(playerid, "%s adl� ki�iye avukat lisans� verdiniz.", GetNameEx(userid));
		return 1;
	}

	PlayerInfo[userid][pLawyer] = 0;
	SendSyntaxMessage(userid, "%s %s adl� ki�i sizin avukat lisans�n�za elkoydu.", GetRankName(playerid), GetNameEx(playerid));
	SendSyntaxMessage(playerid, "%s adl� ki�inin avukat lisans�na elkoydunuz.", GetNameEx(userid));
	return 1;
}