SendTaxiRequest(playerid, location[])
{
    foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !TaxiDuty[i] || PlayerInfo[i][pJob] != JOB_TAXI) continue;

        SendClientMessage(i, COLOR_SERVER2, "|___________Taksi �a�r�s�___________|");
		if (pTemp[playerid][pPayphone] == -1) 
			SendClientMessageEx(i, COLOR_WHITE, "Arayan: %s Telefon: %i", GetNameEx(playerid), PlayerInfo[playerid][pNumber]);
		else
			SendClientMessageEx(i, COLOR_WHITE, "Arayan: Ankes�rl� Telefon, Telefon: %i", PayphoneInfo[pTemp[playerid][pPayphone]][phNumber]);
		SendClientMessageEx(i, COLOR_WHITE, "Lokasyon: %s", location);
		SendClientMessageEx(i, COLOR_SERVER2, "(( �a�r�y� kabul etmek i�in: /taksi kabul %i ))", playerid);
	}
	return 1;
}

Taxi_OnGameModeInit()
{
    return SetTimer("Taxi_FiveSecTimer", 5000, false);
}