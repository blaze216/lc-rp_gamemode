CMD:taksi(playerid, params[])
{
	new option[11], secoption, vehicle = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][pJob] != JOB_TAXI)	return SendErrorMessage(playerid, "Taksi �of�r� de�ilsiniz.");
	if (sscanf(params,"s[11]D(-1)", option, secoption))
	{
		SendHelpMessage(playerid, "/taksi [ayarlar]"); //���������
		SendSyntaxMessage(playerid, "isbasi / ucret / kabul");
		return 1;
	}

	if (!IsDriver(playerid))	return SendErrorMessage(playerid, "Bir taksi veya cabbie arac�nda olmal�s�n�z.");
	if (!IsATaxi(vehicle))	return SendErrorMessage(playerid, "Bir taksi veya cabbie arac�nda olmal�s�n�z.");

	if (CompareStrings(option, "isbasi"))
	{
		if (TaxiDuty[playerid])
		{
			SCM(playerid, COLOR_YELLOWG, "[TAKS�] ��ba��ndan ��kt�n�z, art�k sizin i�in aramalar aktif de�il. ");
			SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKS�] $%i tutar�nda �deme ald�n�z.", TaxiMade[playerid]);
			GiveCash(playerid, TaxiMade[playerid]);
			SetPlayerColor(playerid, TEAM_HIT_COLOR);
			TaxiDuty[playerid] = false;
			TaxiMade[playerid] = 0;
			TaxiMoney[playerid] = 0;
			TaxiPassenger[playerid] = INVALID_PLAYER_ID;
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKS�] ��ba��na girdiniz ve �a�r�lar� alabilirsiniz. �cret: $%i/5 saniye.", TaxiFare[playerid]);
		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKS�] E�er Portland'in merkez sahalar�nda dola��rsan�z ekstra �cret alacaks�n�z.");
		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKS�] �cretinizi i�iniz bittikten sonra i�ba��n�z� kapatarak alabilirsiniz.");
		TaxiDuty[playerid] = true;
		TaxiMoney[playerid] = 0;
		TaxiMade[playerid] = 0;
		TaxiPassenger[playerid] = INVALID_PLAYER_ID;

		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicle) || GetPlayerState(i) != PLAYER_STATE_PASSENGER)	continue;

			TaxiPassenger[playerid] = i;
			SendClientMessageEx(i, COLOR_YELLOWG, "[TAKS�] %s taksi tuttu. �cret: $%i/5 saniye.", GetNameEx(playerid), TaxiFare[playerid]);
			break;
		}

		return 1;
	}

	else if (CompareStrings(option, "ucret"))
	{
		new fare;

		if (sscanf(params,"{s[11]}d",fare))			return SendHelpMessage(playerid, "/taksi ucret [taksimetre �creti]");
		if (fare < 1 || fare > 25)					return SendErrorMessage(playerid, "�cret $1 ile $25 aras�nda olmal�d�r.");
		if (IsPlayerLogged(TaxiPassenger[playerid]))	return SendErrorMessage(playerid, "�cretlendirmeyi de�i�tirmeden �nce m��teriyi b�rakmal�s�n�z.");
		    
		SendClientMessageEx(playerid,COLOR_YELLOWG,"[TAKS�] �cretlendirme de�i�tirildi: $%i/5 saniye", fare);
		TaxiFare[playerid] = fare;
	}

	else if (CompareStrings(option, "kabul"))
	{
		new id, Float:x, Float:y, Float:z;

		if (sscanf(params,"{s[11]}u",id))	return SendHelpMessage(playerid, "/taksi kabul [ID / isim]");
		if (!TaxiDuty[playerid])				return SendErrorMessage(playerid, "�a�r�y� kabul etmek i�in i�ba��nda olmal�s�n�z. /taksi isbasi");
		if (!IsPlayerLogged(id))				return SendNotConnected(playerid);
		if (GetPVarInt(id, "NeedTaxi") == 0)	return SendErrorMessage(playerid, "Bu oyuncu bir taksi �a��rmad� veya birisi aramay� kabul etti.");

		SendSyntaxMessage(id, "%s �a�r�y� kabul etti. �cretlendirme: $%i/5 saniye.", GetNameEx(playerid), TaxiFare[playerid]);
		SendSyntaxMessage(playerid, "%s adl� ki�inin �a�r�s�n� kabul ettiniz, Telefon: %i", GetNameEx(id), PlayerInfo[id][pNumber]);
		GetPlayerPos(id, x, y, z);
		Waypoint_Set(playerid, x, y, z, 3.0);
		DeletePVar(id, "NeedTaxi");
	}
	return 1;
}