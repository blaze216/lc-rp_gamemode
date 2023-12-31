CMD:sedye(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid,"Sa�l�k g�revlisi veya itfaiyeci olmal�s�n�z.");
	if (IsPlayerInAnyVehicle(playerid))						return SendErrorMessage(playerid, "Bu i�lem i�in ara�ta olmamal�s�n�z.");

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

		SendMedicMessage(playerid, "Sedyeyi b�rakt�n.");
		return 1;
	}

    if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin.");

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
	
	if (idx == -1) return SendErrorMessage(playerid, "Yak�nda sedye bulunmuyor! (/barikat) ");

	BortInfo[playerid][idx][bortUsing] = playerid+1;
	pTemp[playerid][UsingBort] = idx+1;
	pTemp[playerid][UsingCorpse] = 0;

	AttachDynamicObjectToPlayer(BortInfo[playerid][idx][bortObject], playerid, 0.00, 1.50, -0.50, 0.0, 0.0, 0.0);

    SendMedicMessage(playerid, "Sedyey� ald�n.");
	return 1;
}

CMD:terapi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid;

	if (!IsFactionMedic(faction))					return SendErrorMessage(playerid, "Sa�l�k g�revlisi olmal�s�n.");
	if (PlayerInfo[playerid][pRank] < 3)			return SendErrorMessage(playerid, "3. seviyeden itibaren mevcuttur.");
	if (!PlayerInfo[playerid][pOnDuty])				return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin.");
	if (sscanf(params, "u", userid))				return SendHelpMessage(playerid, "/terapi [ID/�sim par�as�]");
	if (!IsPlayerLogged(userid))					return SendNotConnected(playerid);
	if (userid == playerid)							return SendErrorMessage(playerid, "Ge�ersiz ID.");
	if (!PlayerNearPlayer(3.0, playerid, userid))	return SendNotNearPlayer(playerid);
	if (PlayerInfo[userid][pDependence] == 0)		return SendErrorMessage(playerid, "Oyuncunun uyu�turucu ba��ml�l��� yoktur. ");

    PlayerInfo[userid][pDependence] -= (PlayerInfo[userid][pDependence] < 20) ? (PlayerInfo[userid][pDependence]) : (20);
    pTemp[userid][pDemolitionTime] = 0;
	SetPlayerCurrentTimeAndWeather(userid);
	
	SendMedicMessage(userid, "%s %s adl� ki�i ba��ml�l�k puan�n�z� 20 azaltt�.", GetRankName(playerid), GetNameWithMask(playerid));
    SendMedicMessage(playerid, "%s adl� ki�inin ba��ml�l�k puan�n� 20 azaltt�n�z.", GetNameWithMask(userid));

	return 1;
}

CMD:recete(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid, days;

	if (!IsFactionMedic(faction))						return SendErrorMessage(playerid, "Sa�l�k g�revlisi olmal�s�n.");
	if (PlayerInfo[playerid][pRank] < 3)				return SendErrorMessage(playerid, "3. seviyeden itibaren mevcuttur.");
	if (!PlayerInfo[playerid][pOnDuty])					return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin. ");	
	if (sscanf(params,"uI(0)",userid, days))			return SendHelpMessage(playerid, "/recete [ID / isim] [g�n say�s� 1-93]");
	if (!IsPlayerLogged(userid))						return SendNotConnected(playerid);
	if (userid == playerid)								return SendErrorMessage(playerid, "Ge�ersiz ID.");
	if (!PlayerNearPlayer(3.0, playerid, userid))		return SendNotNearPlayer(playerid);	
	if (PlayerInfo[userid][pPrescribe] < gettime())
	{
	    if (days < 1 || days > 93)					return SendErrorMessage(playerid, "Ge�ersiz re�ete son kullanma tarihi. ");
	        
	    PlayerInfo[playerid][pPrescribe] = gettime() + days * 86400;
	    SendMedicMessage(userid, "%s %s size t�bbi esrar i�in bir re�ete verdi.", GetRankName(playerid), GetNameWithMask(playerid));
		SendHelpMessage(userid, "Re�eteyi g�stermek i�in /recetegoster kullan�n.");
        SendMedicMessage(playerid, "%s adl� ki�iye medikal esrar re�etesi verdiniz. ", GetNameWithMask(userid));
	}
	else
	{
	    PlayerInfo[userid][pPrescribe] = 0;
	    SendMedicMessage(userid, "%s %s t�bbi esrar re�etenizi ald�.", GetRankName(playerid), GetNameWithMask(playerid));
        SendMedicMessage(playerid, "%s'den t�bbi esrar re�etesi ald�n�z.", GetNameWithMask(userid));
	}
	return 1;
}

CMD:tedavi(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], userid;

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid, "Sa�l�k g�revlisi veya itfaiyeci olmal�s�n�z.");
	if (!PlayerInfo[playerid][pOnDuty])							return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin. ");
	if (sscanf(params, "u", userid))							return SendHelpMessage(playerid, "/tedavi [ID / isim]");
	if (!IsPlayerLogged(userid))								return SendNotConnected(playerid);
	if (userid == playerid)										return SendErrorMessage(playerid, "Kendini tedavi etmek imkans�zd�r. ");
	if (!PlayerNearPlayer(3.0, playerid, userid))				return SendNotNearPlayer(playerid);
	if (PlayerInfo[userid][pInjured] != 1)						return SendErrorMessage(playerid, "Oyuncunun tedavi ihtiyac� yok. ");
	if (pTemp[userid][pInvulnerable] != 0.0)					return SendErrorMessage(playerid, "Daha sonra tekrar deneyin!");
    ResetDamages(userid);
    PlayerInfo[playerid][pHealth] = 100.0;
	StopPlayerAnims(userid);
	UnFreezePlayer(userid);

	SendMedicMessage(playerid, "%s adl� ki�iyi iyile�tirdiniz.", GetNameWithMask(userid));
	SendMedicMessage(userid, "%s %s adl� ki�i sizi iyile�tirdi.", GetRankName(playerid), GetNameWithMask(playerid));
	return 1;
}

CMD:sorgu(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction], id, vehicle = GetPlayerVehicleID(playerid);

	if (!IsFactionMedic(faction) && !IsFactionFire(faction))	return SendErrorMessage(playerid, "Sa�l�k g�revlisi veya itfaiyeci olmal�s�n�z.");
	if (sscanf(params,"u",id))							return SendHelpMessage(playerid, "/sorgu [ID / isim]");
	if (!IsPlayerLogged(id))								return SendNotConnected(playerid);
	if (VehicleInfo[vehicle][carFaction] != faction)		return SendErrorMessage(playerid, "Kurulu�unuzun arac�nda olmal�s�n�z.");

	SendMedicMessage(playerid, "Bilgi - %s", GetFullDate());
	SendMedicMessage(playerid, "Ad Soyad: %s, Ya�: %i, Telefon: %i.", GetNameEx(id), PlayerInfo[id][pAge], PlayerInfo[id][pNumber]);

	new count;
    for(new i; i < MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0 || HouseInfo[i][hOwnerID] != PlayerInfo[id][pID])	continue;

		SendMedicMessage(playerid, "Kay�tl� adresler: %s.", (!HouseInfo[i][hApart])?(GetHouseZone(i)):(GetApartmentZone(HouseInfo[i][hApart])));
		count++;
		if (count > 4) break;
	}

	if (!count) SendMedicMessage(playerid, "Kay�t adresi bilinmiyor.");

	return 1;
}

alias:choke("yanginsondur");
CMD:choke(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];

	if (!IsFactionFire(faction))			return SendErrorMessage(playerid, "Bir itfaiyeci olmal�s�n.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce i�ba��na gitmelisin.");
	
	DeleteNearFire(playerid);
	return 1;
}

CMD:itfaiyekiyafet(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	
	if (!IsFactionFire(faction)) 		return SendErrorMessage(playerid,"Bir itfaiyeci olmal�s�n.");
	if (!PlayerInfo[playerid][pOnDuty])	return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin. ");
	if (!PlayerInfo[playerid][pChar])	return SendErrorMessage(playerid, "Resmi �niformal� olmal�s�n�z.");

	if (GetPlayerSkin(playerid) == PlayerInfo[playerid][pChar])
	{
		if (PlayerInfo[playerid][pChar] == 277 || PlayerInfo[playerid][pChar] == 278 
		|| PlayerInfo[playerid][pChar] == 279 || PlayerInfo[playerid][pChar] == 191) return SendErrorMessage(playerid, "Zaten itfaiyeci �niformas� i�indesin! ");
		Dialog_Show(playerid, MODEL_SELECTION_SHAPE, DIALOG_STYLE_PREVIEW_MODEL, "�niforma", "277\tID: 277\n278\tID: 278\n279\tID: 279\n191\tID: 191", "Sec", "Kapat");
	} else {
		SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	}
	return 1;
}
