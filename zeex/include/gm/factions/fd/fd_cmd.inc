CMD:sedye(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid,"Saðlýk görevlisi veya itfaiyeci olmalýsýnýz.");
	if (IsPlayerInAnyVehicle(playerid))						return SendErrorMessage(playerid, "Bu iþlem için araçta olmamalýsýnýz.");

	if (pTemp[playerid][UsingBort]) {
		new idx = pTemp[playerid][UsingBort]-1, modelid = GetDynamicObjectModel(BortInfo[playerid][idx][bortObject]);

		DestroyDynamicObject(BortInfo[playerid][idx][bortObject]);

		new Float:x, Float:y, Float:z, Float:R;
		GetPlayerFacingAngle(playerid, R);
	  	GetXYInFrontOfPlayer(playerid, x, y, z, 1.5);
		BortInfo[playerid][idx][bortObject] = CreateDynamicObject(modelid, x, y, z - 0.5, 0.0, 0.0, 0.0, GetWorld(playerid), GetInterior(playerid));
		
		if (pTemp[playerid][UsingCorpse]) {
			new actorid = pTemp[playerid][UsingCorpse];
			SetActorPos(actorid, x, y, z + 0.60);
			SetActorFacingAngle(actorid, R);
			pTemp[playerid][UsingCorpse] = 0;
		}

		BortInfo[playerid][idx][bortUsing] = 0;
		pTemp[playerid][UsingBort] = 0;

		SendMedicMessage(playerid, "Sedyeyi býraktýn.");
		return 1;
	}

    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin.");

	new idx = -1;
	for(new i = 0; i < MAX_BORTES; i++)
	{
	    if (!BortInfo[playerid][i][bortOn]) continue;
		if (BortInfo[playerid][i][bortUsing] != 0) continue;

		new Float: x, Float: y, Float: z;
		GetDynamicObjectPos(BortInfo[playerid][i][bortObject], x, y, z);

		if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 1.5) continue;

		new modelid = GetDynamicObjectModel(BortInfo[playerid][i][bortObject]);
		if (modelid != 1997 && modelid != 2146) continue;

		idx = i;
		break;
	}
	
	if (idx == -1) return SendErrorMessage(playerid, "Yakýnda sedye bulunmuyor! (/barikat) ");

	BortInfo[playerid][idx][bortUsing] = playerid+1;
	pTemp[playerid][UsingBort] = idx+1;
	pTemp[playerid][UsingCorpse] = 0;

	AttachDynamicObjectToPlayer(BortInfo[playerid][idx][bortObject], playerid, 0.00, 1.50, -0.50, 0.0, 0.0, 0.0);

    SendMedicMessage(playerid, "Sedyeyý aldýn.");
	return 1;
}

CMD:terapi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid;

	if (!IsFactionMedic(faction))					return SendErrorMessage(playerid, "Saðlýk görevlisi olmalýsýn.");
	if (PlayerInfo[playerid][pRank] < 3)			return SendErrorMessage(playerid, "3. seviyeden itibaren mevcuttur.");
	if (!PlayerInfo[playerid][pOnDuty])				return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin.");
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/terapi [ID/Ýsim parçasý]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (userid == playerid)							return SendErrorMessage(playerid, "Geçersiz ID.");
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (PlayerInfo[userid][pDependence] == 0)		return SendErrorMessage(playerid, "Oyuncunun uyuþturucu baðýmlýlýðý yoktur. ");

    PlayerInfo[userid][pDependence] -= (PlayerInfo[userid][pDependence] < 20) ? (PlayerInfo[userid][pDependence]) : (20);
    pTemp[userid][pDemolitionTime] = 0;
	SetPlayerCurrentTimeAndWeather(userid);
	
	SendMedicMessage(userid, "%s %s adlý kiþi baðýmlýlýk puanýnýzý 20 azalttý.", GetRankName(playerid), GetNameWithMask(playerid));
    SendMedicMessage(playerid, "%s adlý kiþinin baðýmlýlýk puanýný 20 azalttýnýz.", GetNameWithMask(userid));

	return 1;
}

CMD:recete(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid, days;

	if (!IsFactionMedic(faction))						return SendErrorMessage(playerid, "Saðlýk görevlisi olmalýsýn.");
	if (PlayerInfo[playerid][pRank] < 3)				return SendErrorMessage(playerid, "3. seviyeden itibaren mevcuttur.");
	if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin. ");	
	if (sscanf(params,"uI(0)",userid, days))			return SendHelpMessage(playerid, "/recete [ID / isim] [gün sayýsý 1-93]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (userid == playerid)								return SendErrorMessage(playerid, "Geçersiz ID.");
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);	
	if (PlayerInfo[userid][pPrescribe] < gettime())
	{
	    if (days < 1 || days > 93)					return SendErrorMessage(playerid, "Geçersiz reçete son kullanma tarihi. ");
	        
	    PlayerInfo[playerid][pPrescribe] = gettime() + days * 86400;
	    SendMedicMessage(userid, "%s %s size týbbi esrar için bir reçete verdi.", GetRankName(playerid), GetNameWithMask(playerid));
		SendHelpMessage(userid, "Reçeteyi göstermek için /recetegoster kullanýn.");
        SendMedicMessage(playerid, "%s adlý kiþiye medikal esrar reçetesi verdiniz. ", GetNameWithMask(userid));
	}
	else
	{
	    PlayerInfo[userid][pPrescribe] = 0;
	    SendMedicMessage(userid, "%s %s týbbi esrar reçetenizi aldý.", GetRankName(playerid), GetNameWithMask(playerid));
        SendMedicMessage(playerid, "%s'den týbbi esrar reçetesi aldýnýz.", GetNameWithMask(userid));
	}
	return 1;
}

CMD:tedavi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid;

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid, "Saðlýk görevlisi veya itfaiyeci olmalýsýnýz.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin. ");
	if (sscanf(params, "u", userid))							return SendHelpMessage(playerid, "/tedavi [ID / isim]");
	if (!IsPlayerLogged(userid))								return SendNotConnected(playerid);
	if (userid == playerid)										return SendErrorMessage(playerid, "Kendini tedavi etmek imkansýzdýr. ");
	if (!PlayerNearPlayer(3.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (PlayerInfo[userid][pInjured] != 1)						return SendErrorMessage(playerid, "Oyuncunun tedavi ihtiyacý yok. ");
	if (pTemp[userid][pInvulnerable] != 0.0)					return SendErrorMessage(playerid, "Daha sonra tekrar deneyin!");
    ResetDamages(userid);
    PlayerInfo[playerid][pHealth] = 100.0;
	StopPlayerAnims(userid);
	UnFreezePlayer(userid);

	SendMedicMessage(playerid, "%s adlý kiþiyi iyileþtirdiniz.", GetNameWithMask(userid));
	SendMedicMessage(userid, "%s %s adlý kiþi sizi iyileþtirdi.", GetRankName(playerid), GetNameWithMask(playerid));
	return 1;
}

CMD:sorgu(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], id, vehicle = GetPlayerVehicleID(playerid);

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid, "Saðlýk görevlisi veya itfaiyeci olmalýsýnýz.");
	if (sscanf(params,"u",id))							return SendHelpMessage(playerid, "/sorgu [ID / isim]");
	if (!IsPlayerLogged(id))								return SendNotConnected(playerid);
	if (VehicleInfo[vehicle][carFaction] != faction)		return SendErrorMessage(playerid, "Kuruluþunuzun aracýnda olmalýsýnýz.");

	SendMedicMessage(playerid, "Bilgi - %s", GetFullDate());
	SendMedicMessage(playerid, "Ad Soyad: %s, Yaþ: %i, Telefon: %i.", GetNameEx(id), PlayerInfo[id][pAge], PlayerInfo[id][pNumber]);

	new count;
    for(new i; i < MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0 || HouseInfo[i][hOwnerID] != PlayerInfo[id][pID])	continue;

		SendMedicMessage(playerid, "Kayýtlý adresler: %s.", (!HouseInfo[i][hApart])?(GetHouseZone(i)):(GetApartmentZone(HouseInfo[i][hApart])));
		count++;
		if (count > 4) break;
	}

	if (!count) SendMedicMessage(playerid, "Kayýt adresi bilinmiyor.");

	return 1;
}

alias:choke("yanginsondur");
CMD:choke(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionFire(faction))			return SendErrorMessage(playerid, "Bir itfaiyeci olmalýsýn.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýlk önce iþbaþýna gitmelisin.");
	
	DeleteNearFire(playerid);
	return 1;
}

CMD:itfaiyekiyafet(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	
	if (!IsFactionFire(faction)) 		return SendErrorMessage(playerid,"Bir itfaiyeci olmalýsýn.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin. ");
	if (!PlayerInfo[playerid][pChar])	return SendErrorMessage(playerid, "Resmi üniformalý olmalýsýnýz.");

	if (GetPlayerSkin(playerid) == PlayerInfo[playerid][pChar])
	{
		if (PlayerInfo[playerid][pChar] == 277 || PlayerInfo[playerid][pChar] == 278 
		|| PlayerInfo[playerid][pChar] == 279 || PlayerInfo[playerid][pChar] == 191) return SendErrorMessage(playerid, "Zaten itfaiyeci üniformasý içindesin! ");
		Dialog_Show(playerid, MODEL_SELECTION_SHAPE, DIALOG_STYLE_PREVIEW_MODEL, "Üniforma", "277\tID: 277\n278\tID: 278\n279\tID: 279\n191\tID: 191", "Sec", "Kapat");
	} else {
		SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	}
	return 1;
}
