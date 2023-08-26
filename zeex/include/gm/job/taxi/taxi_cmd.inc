CMD:taksi(playerid, params[])
{
	new option[11], secoption, vehicle = GetPlayerVehicleID(playerid);

	if (PlayerInfo[playerid][pJob] != JOB_TAXI)	return SendErrorMessage(playerid, "Taksi þoförü deðilsiniz.");
	if (sscanf(params,"s[11]D(-1)", option, secoption))
	{
		SendHelpMessage(playerid, "/taksi [ayarlar]"); //äîñòóïíûå
		SendSyntaxMessage(playerid, "isbasi / ucret / kabul");
		return 1;
	}

	if (!IsDriver(playerid))	return SendErrorMessage(playerid, "Bir taksi veya cabbie aracýnda olmalýsýnýz.");
	if (!IsATaxi(vehicle))	return SendErrorMessage(playerid, "Bir taksi veya cabbie aracýnda olmalýsýnýz.");

	if (CompareStrings(option, "isbasi"))
	{
		if (TaxiDuty[playerid])
		{
			SCM(playerid, COLOR_YELLOWG, "[TAKSÝ] Ýþbaþýndan çýktýnýz, artýk sizin için aramalar aktif deðil. ");
			SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSÝ] $%i tutarýnda ödeme aldýnýz.", TaxiMade[playerid]);
			GiveCash(playerid, TaxiMade[playerid]);
			SetPlayerColor(playerid, TEAM_HIT_COLOR);
			TaxiDuty[playerid] = false;
			TaxiMade[playerid] = 0;
			TaxiMoney[playerid] = 0;
			TaxiPassenger[playerid] = INVALID_PLAYER_ID;
			return 1;
		}

		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSÝ] Ýþbaþýna girdiniz ve çaðrýlarý alabilirsiniz. Ücret: $%i/5 saniye.", TaxiFare[playerid]);
		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSÝ] Eðer Portland'in merkez sahalarýnda dolaþýrsanýz ekstra ücret alacaksýnýz.");
		SendClientMessageEx(playerid, COLOR_YELLOWG, "[TAKSÝ] Ücretinizi iþiniz bittikten sonra iþbaþýnýzý kapatarak alabilirsiniz.");
		TaxiDuty[playerid] = true;
		TaxiMoney[playerid] = 0;
		TaxiMade[playerid] = 0;
		TaxiPassenger[playerid] = INVALID_PLAYER_ID;

		foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || !IsPlayerInVehicle(i, vehicle) || GetPlayerState(i) != PLAYER_STATE_PASSENGER)	continue;

			TaxiPassenger[playerid] = i;
			SendClientMessageEx(i, COLOR_YELLOWG, "[TAKSÝ] %s taksi tuttu. Ücret: $%i/5 saniye.", GetNameEx(playerid), TaxiFare[playerid]);
			break;
		}

		return 1;
	}

	else if (CompareStrings(option, "ucret"))
	{
		new fare;

		if (sscanf(params,"{s[11]}d",fare))			return SendHelpMessage(playerid, "/taksi ucret [taksimetre ücreti]");
		if (fare < 1 || fare > 25)					return SendErrorMessage(playerid, "Ücret $1 ile $25 arasýnda olmalýdýr.");
		if (IsPlayerLogged(TaxiPassenger[playerid]))	return SendErrorMessage(playerid, "Ücretlendirmeyi deðiþtirmeden önce müþteriyi býrakmalýsýnýz.");
		    
		SendClientMessageEx(playerid,COLOR_YELLOWG,"[TAKSÝ] Ücretlendirme deðiþtirildi: $%i/5 saniye", fare);
		TaxiFare[playerid] = fare;
	}

	else if (CompareStrings(option, "kabul"))
	{
		new id, Float:x, Float:y, Float:z;

		if (sscanf(params,"{s[11]}u",id))	return SendHelpMessage(playerid, "/taksi kabul [ID / isim]");
		if (!TaxiDuty[playerid])				return SendErrorMessage(playerid, "Çaðrýyý kabul etmek için iþbaþýnda olmalýsýnýz. /taksi isbasi");
		if (!IsPlayerLogged(id))				return SendNotConnected(playerid);
		if (GetPVarInt(id, "NeedTaxi") == 0)	return SendErrorMessage(playerid, "Bu oyuncu bir taksi çaðýrmadý veya birisi aramayý kabul etti.");

		SendSyntaxMessage(id, "%s çaðrýyý kabul etti. Ücretlendirme: $%i/5 saniye.", GetNameEx(playerid), TaxiFare[playerid]);
		SendSyntaxMessage(playerid, "%s adlý kiþinin çaðrýsýný kabul ettiniz, Telefon: %i", GetNameEx(id), PlayerInfo[id][pNumber]);
		GetPlayerPos(id, x, y, z);
		Waypoint_Set(playerid, x, y, z, 3.0);
		DeletePVar(id, "NeedTaxi");
	}
	return 1;
}