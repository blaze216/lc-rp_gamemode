CMD:avukatizni(playerid, params[])
{
	new userid;

	if (sscanf(params,"u",userid))										return SendHelpMessage(playerid, "/avukatizni [ID / Karakter Adý]"); //Komut
	if (!IsPlayerFactionCity(playerid))									return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz.");
    if (!isLeader(playerid))											return SendErrorMessage(playerid, "Birlik yetkilisi deðilsiniz.");
	if (!IsPlayerLogged(userid))										return SendNotConnected(playerid);
	if (!PlayerNearPlayer(3.0, playerid, userid))						return SendNotNearPlayer(playerid);
    if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Oyuncu birliðinize üye deðil.");

	if (PlayerInfo[userid][pLawyer] == 0)
	{
		PlayerInfo[userid][pLawyer] = 1;
		SendSyntaxMessage(userid, "%s %s adlý kiþi size avukat lisansý verdi.", GetRankName(playerid), GetNameEx(playerid));
		SendSyntaxMessage(playerid, "%s adlý kiþiye avukat lisansý verdiniz.", GetNameEx(userid));
		return 1;
	}

	PlayerInfo[userid][pLawyer] = 0;
	SendSyntaxMessage(userid, "%s %s adlý kiþi sizin avukat lisansýnýza elkoydu.", GetRankName(playerid), GetNameEx(playerid));
	SendSyntaxMessage(playerid, "%s adlý kiþinin avukat lisansýna elkoydunuz.", GetNameEx(userid));
	return 1;
}