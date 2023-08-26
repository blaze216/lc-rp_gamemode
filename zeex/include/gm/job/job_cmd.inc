CMD:isegir(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) 
		return 1;
	
	new i = Job_Nearest(playerid);
	if (i == -1) return 1;

	new title[32+22];
	format(title, sizeof(title), "%s", GetJobName(JobsInfo[i][jobType]));

	static const strdlg[] = "%s\nÝþe Gir\nKomutlar\n	\n{FFC46A}Ýþten Çýk ";
	new mes[sizeof(strdlg) + 36];

	if (JobsInfo[i][jobType] == JOB_PIZZA) {
		format(mes, sizeof(mes), strdlg, "Ýkincil bir iþiniz olabilir");
		format(title, sizeof(title), "%s - Yan meslek", title);
	} else {
		format(mes, sizeof(mes), strdlg, "Baþka bir meslek yapamazsýn");
		format(title, sizeof(title), "%s - Ana meslek", title);
	}
	
	Dialog_Show(playerid, TakeJobMenu, DIALOG_STYLE_TABLIST_HEADERS, title, mes, "Seç", "Ýptal");
	return 1;
}

alias:istencik("istenayril");
CMD:istencik(playerid, params[])
{
	new job = PlayerInfo[playerid][pJob];

	if (job == JOBLESS)																return SendErrorMessage(playerid, "Artýk iþsizsin.");
	if (pTemp[playerid][pJob])														return SendErrorMessage(playerid, "Önce iþinizi bitiriniz ve aracýnýzý teslim ediniz. (/makb)");

	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pCareer] = 0;

	pTemp[playerid][pJob] = 0;
	pTemp[playerid][pJobTime] = 0;

	SQL_SetInteger("users", "job", 0, PlayerInfo[playerid][pID]);
	SQL_SetInteger("users", "career", 0, PlayerInfo[playerid][pID]);
	
	SendSyntaxMessage(playerid, "%s%s iþinden ayrýldýnýz", GetJobName(job), (job == JOB_TRUCKER)?(". Trucker seviyeniz sýfýrlandý."):(","));
	return 1;
}

alias:yanmeslektencik("yanmeslektenayril");
CMD:yanmeslektencik(playerid, params[])
{
	new job = PlayerInfo[playerid][pSideJob];

	if (job == JOBLESS)	return SendErrorMessage(playerid, "Ýkinci bir iþiniz yok.");

	SendSyntaxMessage(playerid, "%s adlý meslekten ayrýldýn.", GetJobName(job));
	PlayerInfo[playerid][pSideJob] = 0;
	return 1;
}

alias:rentcarjob("meslekarackirala", "mak");
CMD:rentcarjob(playerid, params[])
{
	if(!MeslekSistemleri) return SendErrorMessage(playerid, "Meslek sistemleri pasife çekildi. Rol modu aktif edildi. (PayDay yükseltildi)");
	new rentalid = Locker_RentalNearestType(playerid, 1);
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (Locker_RentalNearestType(playerid, 1) == -1) return SendErrorMessage(playerid, "Herhangi bir meslek aracý kiralama noktasýna yakýn deðilsin.");
	
	if (pTemp[playerid][pJob])					return SendErrorMessage(playerid, "Halihazýrda bir iþ aracýnýz var. Geri dönmek için /meslekarackirabitir(/makb) komutunu kullanýn. ");
	
	new kiraucret = 100;

	if (PlayerInfo[playerid][pJob] == JOBLESS && PlayerInfo[playerid][pSideJob] == 0) return SendErrorMessage(playerid,"Mesleðin yok.");
	if (GetCash(playerid) < kiraucret) return SendErrorMessage(playerid, "Aracýn kiralama ücretine yetecek kadar paranýz yok. Ücret: %d", kiraucret);
	if (pTemp[playerid][pRentveh])				return SendErrorMessage(playerid, "Zaten kiralýk aracýnýz var. /meslekarackirabitir(/makb) komutunu kullanýnýz!");

	if (RentalPoint[rentalid][rentalJob] != PlayerInfo[playerid][pJob] && RentalPoint[rentalid][rentalJob] != PlayerInfo[playerid][pSideJob]) return SendErrorMessage(playerid, "Bu nokta sizin mesleðiniz için araç kiralamýyor.");

    new Float:x, Float:y, Float:z, Float:a, model;
    GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);	

    switch (RentalPoint[rentalid][rentalJob])
	{
		case JOB_MECHANIC:
		{
		    new vehicle = CreateFactionVehicle(false, 525, x, y, z, a, 1, 1, 9, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun oluþtu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullanýlabilir komutlarýn listesi için /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adlý iþ aracýný aldýnýz. Kullanabildiðiniz komutlar: /makb(kirayý bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Aracý 5 dakika kullanmazsanýz araç silenecektir! ");				
		}
		case JOB_TAXI:
		{
		    new vehicle = CreateFactionVehicle(false, 420, x, y, z, a, 1, 1, 7, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun oluþtu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullanýlabilir komutlarýn listesi için /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adlý iþ aracýný aldýnýz. Kullanabildiðiniz komutlar: /makb(kirayý bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Aracý 5 dakika kullanmazsanýz araç silenecektir! ");							
		}
		case JOB_TRUCKER:
		{
		    new vehicle = CreateFactionVehicle(false, 413, x, y, z, a, 1, 1, 8, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun oluþtu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullanýlabilir komutlarýn listesi için /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adlý iþ aracýný aldýnýz. Kullanabildiðiniz komutlar: /makb(kirayý bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Aracý 5 dakika kullanmazsanýz araç silenecektir! ");							
		}
		case JOB_PIZZA:
		{
		    new vehicle = CreateFactionVehicle(false, 448, x, y, z, a, 1, 1, 6, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun oluþtu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

		    pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullanýlabilir komutlarýn listesi için /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adlý iþ aracýný aldýnýz. Kullanabildiðiniz komutlar: /makb(kirayý bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Aracý 5 dakika kullanmazsanýz araç silenecektir! ");			
		}
	}
/*
	if (IsTruckCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TRUCKER && GetAvailableTruck(playerid, GetVehicleModel(vehicle)))
	{
		pTemp[playerid][pJob] = 1;
		pTemp[playerid][pJobTime] = gettime();
	}
	else if (IsTaxiCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TAXI) {
		pTemp[playerid][pJob] = 1;
		pTemp[playerid][pJobTime] = gettime();
	}
	else if (IsMechanicCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_MECHANIC) {
		pTemp[playerid][pJob] = 1;
	}
	else if (IsTrashMasterCar(vehicle) && PlayerInfo[playerid][pJob] == JOB_TRASHMASTER) {
		pTemp[playerid][pJob] = 1;
		Trash_InitPlayer(playerid);
	}
	else if (IsPizzaCar(vehicle) && PlayerInfo[playerid][pSideJob] == JOB_PIZZA) {
		pTemp[playerid][pJob] = 1;
	}
	else {
		SendErrorMessage(playerid, "Geçersiz araç tipi!");
		if (PlayerInfo[playerid][pJob] == JOB_TRUCKER) SendSyntaxMessage(playerid, "Kullanabileceðiniz araçlarý /meslekyardim komutuyla öðrenebilirsiniz!");
		return 1;
	}

	pTemp[playerid][pRentveh] = vehicle;
	VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	GiveCash(playerid, -kiraucret);

	SendHelpMessage(playerid, "Kullanýlabilir komutlarýn listesi için /meslekyardim komutunu kullanabilirsiniz. ");
	SendSyntaxMessage(playerid, "%s adlý iþ aracýný aldýnýz. Kullanabildiðiniz komutlar: /makb(kirayý bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	SendSyntaxMessage(playerid, "Dikkat! Aracý 10 dakika kullanmazsanýz araç silenecektir! ");
	*/

	return 1;
}

alias:unrentcarjob("unrcj", "meslekarackirabitir", "makb");
CMD:unrentcarjob(playerid, params[])
{
	if (!pTemp[playerid][pRentveh]) return 1;

    SendSyntaxMessage(playerid, "Bir iþ aracýný iade ettiniz.");
	EndJob(playerid);
	return 1;
}

EndJob(playerid) {
	//Ñäåëàòü òàê, ÷òîáû íå âûãîíÿëî è íåëüçÿ áûëî çàâåñòè äâèãàòåëü
	new vehicle = pTemp[playerid][pRentveh];
	
	if (PlayerInfo[playerid][pJob] == JOB_TRASHMASTER && pTemp[playerid][pJob])
	{
		Trash_ResetPlayer(playerid, 1);
		EndTrashJob(playerid);
	}
	
	pTemp[playerid][pRentveh] = 0;
    VehicleInfo[vehicle][carRent] = 0;

	pTemp[playerid][pTruckerOn] = 0;
	pTemp[playerid][pTruckerPrice] = 0;
	pTemp[playerid][pTruckerTime] = 0;	
	pTemp[playerid][pPizzaBoy] = 0;		

	pTemp[playerid][pJob] = 0;
	pTemp[playerid][pJobTime] = 0;

    AracKiraBitir(vehicle);
	return 1;
}
/*
CMD:buydrugs(playerid, params[])
{
	new faction = PlayerInfo[playerid][pFaction];
	
	if (!PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Herhangi bir oluþumunun üyesi deðilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_DRUGDEALER)	return SendErrorMessage(playerid, "Uyuþturucu satýn alamazsýnýz.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

	if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "Rýhtýmda olmalýsýnýz.");
	}

    Dialog_Show(playerid, BuyDrugs, DIALOG_STYLE_TABLIST, "Uyuþturucu Satýn Al", "Marijuana yapraklarý\tadet baþýna 50$ \nLSD\tgram baþýna 150$ \nHeroin\tgram baþýna 100 $ \nCocaine\tgram baþýna 200$.\nEfedrin\tadet baþýna 50$.", "Satýn Al", "Ýptal");
	return 1;
}*/
/*
CMD:buygun(playerid, params[])
{
    new bizid = -1;

	if ((bizid = GetNearInsideBiz(playerid)) != -1 && BizInfo[bizid][bizType] == BIZ_AMMO) return BuyGunMenu(playerid);

	new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])	 													return SendErrorMessage(playerid, "Herhangi bir oluþumunun üyesi deðilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)										return SendErrorMessage(playerid, "Silah satýn alamazsýnýz, eriþminiz yok! ");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

	if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "Rýhtýmda olmalýsýnýz.");
	}

	new title[56];
	format(title, sizeof(title), "On the account of your faction - %i exp.", Factions[faction][fPoint]);
	Dialog_Show(playerid, BuyGunMain, DIALOG_STYLE_LIST, title, "- Silah\n- Mermi", "Seç", "Ýptal");
	return 1;
}*/

CMD:radyocal(playerid, params[])
{
	new vehicle = GetPlayerVehicleID(playerid);

    if (!vehicle || !IsDriver(playerid))				return SendErrorMessage(playerid, "Sürücü koltuðunun arkasýna oturmanýz gerekir.");
	if (!VehicleInfo[vehicle][carOwnerID])				return SendErrorMessage(playerid, "Sadece kiþisel araçlarýn teybini çalabilirsiniz. ");
    if (!VehicleInfo[vehicle][carRadio])				return SendErrorMessage(playerid, "Bu araçta teyp bulunmamakta.");
    if (IsPlayerHasItem(playerid, INV_CARSOUND))		return SendErrorMessage(playerid, "Envanterinizde zaten bir teyp mevcut.");
    if (GiveInvItem(playerid, INV_CARSOUND, 1) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
    
	VehicleInfo[vehicle][carRadio] = 0;
	
	new mes[128];
	format(mes, sizeof(mes), "%s model aracýn radyosunu çalar.", VehicleNames[GetVehicleModel(vehicle)-400]);
	pc_cmd_me(playerid, mes);
	return 1;
}

/*
CMD:birlikmeslek(playerid, params[])
{
	if (!PlayerInfo[playerid][pFaction])																										return SendErrorMessage(playerid, "Onaylý illegal birlik üyesi deðilsiniz.");
	if (Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_GANG && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_MAFIA)	return SendErrorMessage(playerid, "Onaylý illegal birlikte olmalýsýnýz.");
    if (!isLeader(playerid))																													return SendErrorMessage(playerid, "Bu iþ sadece onaylý illegal birlik liderleri tarafýndan kullanýlabilir.");

	new userid, level;

	if (sscanf(params, "ud", userid, level)) return SendHelpMessage(playerid, "/birlikmeslek [ID/Ýsimn [0 - eriþimi kapat | 1 - uyuþturucu satýn alma eriþimi | 2 - silah satýn alma eriþimi] ");

	if (!IsPlayerLogged(userid))											return SendNotConnected(playerid);
	if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Bu oyuncu sizin birliðinizin bir üyesi deðil.");
    if (level > 2 || level < 0)											return SendErrorMessage(playerid, "Seçenek 0 ila 2 arasýnda olabilir.");
		
	if (!level)
	{
	    if (PlayerInfo[userid][pSideJob] == 0)	return SendErrorMessage(playerid, "Oyuncunun herhangi bir yan mesleði yok.");

		SendSyntaxMessage(userid, "%s adlý birlik lideri yetkinizi  %s yetkisine çevirdi. ", GetNameEx(playerid), GetJobName(PlayerInfo[userid][pSideJob]));
		SendSyntaxMessage(playerid, "%s adlý kiþiyi %s adlý meslekten çýkardýnýz.", GetNameEx(userid), GetJobName(PlayerInfo[userid][pSideJob]));
        PlayerInfo[userid][pSideJob] = 0;
		return 1;
	}
	
    PlayerInfo[userid][pSideJob] = level + 3;
	SendSyntaxMessage(userid, "%s adlý birlik lideri yetkinizi  %s yetkisine çevirdi", GetNameEx(playerid), GetJobName(PlayerInfo[userid][pSideJob]));
	SendSyntaxMessage(playerid, "%s adlý kiþiye %s izni verdiniz.", GetNameEx(userid), GetJobName(PlayerInfo[userid][pSideJob]));
	return 1;
}*/