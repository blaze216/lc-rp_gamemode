CMD:isegir(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) 
		return 1;
	
	new i = Job_Nearest(playerid);
	if (i == -1) return 1;

	new title[32+22];
	format(title, sizeof(title), "%s", GetJobName(JobsInfo[i][jobType]));

	static const strdlg[] = "%s\n��e Gir\nKomutlar\n	\n{FFC46A}��ten ��k ";
	new mes[sizeof(strdlg) + 36];

	if (JobsInfo[i][jobType] == JOB_PIZZA) {
		format(mes, sizeof(mes), strdlg, "�kincil bir i�iniz olabilir");
		format(title, sizeof(title), "%s - Yan meslek", title);
	} else {
		format(mes, sizeof(mes), strdlg, "Ba�ka bir meslek yapamazs�n");
		format(title, sizeof(title), "%s - Ana meslek", title);
	}
	
	Dialog_Show(playerid, TakeJobMenu, DIALOG_STYLE_TABLIST_HEADERS, title, mes, "Se�", "�ptal");
	return 1;
}

alias:istencik("istenayril");
CMD:istencik(playerid, params[])
{
	new job = PlayerInfo[playerid][pJob];

	if (job == JOBLESS)																return SendErrorMessage(playerid, "Art�k i�sizsin.");
	if (pTemp[playerid][pJob])														return SendErrorMessage(playerid, "�nce i�inizi bitiriniz ve arac�n�z� teslim ediniz. (/makb)");

	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pCareer] = 0;

	pTemp[playerid][pJob] = 0;
	pTemp[playerid][pJobTime] = 0;

	SQL_SetInteger("users", "job", 0, PlayerInfo[playerid][pID]);
	SQL_SetInteger("users", "career", 0, PlayerInfo[playerid][pID]);
	
	SendSyntaxMessage(playerid, "%s%s i�inden ayr�ld�n�z", GetJobName(job), (job == JOB_TRUCKER)?(". Trucker seviyeniz s�f�rland�."):(","));
	return 1;
}

alias:yanmeslektencik("yanmeslektenayril");
CMD:yanmeslektencik(playerid, params[])
{
	new job = PlayerInfo[playerid][pSideJob];

	if (job == JOBLESS)	return SendErrorMessage(playerid, "�kinci bir i�iniz yok.");

	SendSyntaxMessage(playerid, "%s adl� meslekten ayr�ld�n.", GetJobName(job));
	PlayerInfo[playerid][pSideJob] = 0;
	return 1;
}

alias:rentcarjob("meslekarackirala", "mak");
CMD:rentcarjob(playerid, params[])
{
	if(!MeslekSistemleri) return SendErrorMessage(playerid, "Meslek sistemleri pasife �ekildi. Rol modu aktif edildi. (PayDay y�kseltildi)");
	new rentalid = Locker_RentalNearestType(playerid, 1);
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (Locker_RentalNearestType(playerid, 1) == -1) return SendErrorMessage(playerid, "Herhangi bir meslek arac� kiralama noktas�na yak�n de�ilsin.");
	
	if (pTemp[playerid][pJob])					return SendErrorMessage(playerid, "Halihaz�rda bir i� arac�n�z var. Geri d�nmek i�in /meslekarackirabitir(/makb) komutunu kullan�n. ");
	
	new kiraucret = 100;

	if (PlayerInfo[playerid][pJob] == JOBLESS && PlayerInfo[playerid][pSideJob] == 0) return SendErrorMessage(playerid,"Mesle�in yok.");
	if (GetCash(playerid) < kiraucret) return SendErrorMessage(playerid, "Arac�n kiralama �cretine yetecek kadar paran�z yok. �cret: %d", kiraucret);
	if (pTemp[playerid][pRentveh])				return SendErrorMessage(playerid, "Zaten kiral�k arac�n�z var. /meslekarackirabitir(/makb) komutunu kullan�n�z!");

	if (RentalPoint[rentalid][rentalJob] != PlayerInfo[playerid][pJob] && RentalPoint[rentalid][rentalJob] != PlayerInfo[playerid][pSideJob]) return SendErrorMessage(playerid, "Bu nokta sizin mesle�iniz i�in ara� kiralam�yor.");

    new Float:x, Float:y, Float:z, Float:a, model;
    GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);	

    switch (RentalPoint[rentalid][rentalJob])
	{
		case JOB_MECHANIC:
		{
		    new vehicle = CreateFactionVehicle(false, 525, x, y, z, a, 1, 1, 9, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun olu�tu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullan�labilir komutlar�n listesi i�in /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adl� i� arac�n� ald�n�z. Kullanabildi�iniz komutlar: /makb(kiray� bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Arac� 5 dakika kullanmazsan�z ara� silenecektir! ");				
		}
		case JOB_TAXI:
		{
		    new vehicle = CreateFactionVehicle(false, 420, x, y, z, a, 1, 1, 7, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun olu�tu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullan�labilir komutlar�n listesi i�in /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adl� i� arac�n� ald�n�z. Kullanabildi�iniz komutlar: /makb(kiray� bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Arac� 5 dakika kullanmazsan�z ara� silenecektir! ");							
		}
		case JOB_TRUCKER:
		{
		    new vehicle = CreateFactionVehicle(false, 413, x, y, z, a, 1, 1, 8, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun olu�tu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

			pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullan�labilir komutlar�n listesi i�in /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adl� i� arac�n� ald�n�z. Kullanabildi�iniz komutlar: /makb(kiray� bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Arac� 5 dakika kullanmazsan�z ara� silenecektir! ");							
		}
		case JOB_PIZZA:
		{
		    new vehicle = CreateFactionVehicle(false, 448, x, y, z, a, 1, 1, 6, 0, GetVehicleNumber(), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        
		    if(!vehicle) return SendErrorMessage(playerid, "Bir sorun olu�tu. Kod: 1055");

	        GiveCash(playerid, -kiraucret);
	        pTemp[playerid][pRentveh] = vehicle;
            VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	        FixVehicle(vehicle);
	        VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));

		    pTemp[playerid][pJob] = 1;
		    pTemp[playerid][pJobTime] = gettime();

		    PutPlayerInVeh(playerid, vehicle, 0);	
	        SendHelpMessage(playerid, "Kullan�labilir komutlar�n listesi i�in /meslekyardim komutunu kullanabilirsiniz. ");
	        SendSyntaxMessage(playerid, "%s adl� i� arac�n� ald�n�z. Kullanabildi�iniz komutlar: /makb(kiray� bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	        SendSyntaxMessage(playerid, "Dikkat! Arac� 5 dakika kullanmazsan�z ara� silenecektir! ");			
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
		SendErrorMessage(playerid, "Ge�ersiz ara� tipi!");
		if (PlayerInfo[playerid][pJob] == JOB_TRUCKER) SendSyntaxMessage(playerid, "Kullanabilece�iniz ara�lar� /meslekyardim komutuyla ��renebilirsiniz!");
		return 1;
	}

	pTemp[playerid][pRentveh] = vehicle;
	VehicleInfo[vehicle][carRent] = PlayerInfo[playerid][pID];

	GiveCash(playerid, -kiraucret);

	SendHelpMessage(playerid, "Kullan�labilir komutlar�n listesi i�in /meslekyardim komutunu kullanabilirsiniz. ");
	SendSyntaxMessage(playerid, "%s adl� i� arac�n� ald�n�z. Kullanabildi�iniz komutlar: /makb(kiray� bitirir), /kilit.", VehicleNames[GetVehicleModel(vehicle)-400]);
	SendSyntaxMessage(playerid, "Dikkat! Arac� 10 dakika kullanmazsan�z ara� silenecektir! ");
	*/

	return 1;
}

alias:unrentcarjob("unrcj", "meslekarackirabitir", "makb");
CMD:unrentcarjob(playerid, params[])
{
	if (!pTemp[playerid][pRentveh]) return 1;

    SendSyntaxMessage(playerid, "Bir i� arac�n� iade ettiniz.");
	EndJob(playerid);
	return 1;
}

EndJob(playerid) {
	//������� ���, ����� �� �������� � ������ ���� ������� ���������
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
	
	if (!PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Herhangi bir olu�umunun �yesi de�ilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_DRUGDEALER)	return SendErrorMessage(playerid, "Uyu�turucu sat�n alamazs�n�z.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

	if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "R�ht�mda olmal�s�n�z.");
	}

    Dialog_Show(playerid, BuyDrugs, DIALOG_STYLE_TABLIST, "Uyu�turucu Sat�n Al", "Marijuana yapraklar�\tadet ba��na 50$ \nLSD\tgram ba��na 150$ \nHeroin\tgram ba��na 100 $ \nCocaine\tgram ba��na 200$.\nEfedrin\tadet ba��na 50$.", "Sat�n Al", "�ptal");
	return 1;
}*/
/*
CMD:buygun(playerid, params[])
{
    new bizid = -1;

	if ((bizid = GetNearInsideBiz(playerid)) != -1 && BizInfo[bizid][bizType] == BIZ_AMMO) return BuyGunMenu(playerid);

	new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])	 													return SendErrorMessage(playerid, "Herhangi bir olu�umunun �yesi de�ilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)										return SendErrorMessage(playerid, "Silah sat�n alamazs�n�z, eri�miniz yok! ");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

	if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "R�ht�mda olmal�s�n�z.");
	}

	new title[56];
	format(title, sizeof(title), "On the account of your faction - %i exp.", Factions[faction][fPoint]);
	Dialog_Show(playerid, BuyGunMain, DIALOG_STYLE_LIST, title, "- Silah\n- Mermi", "Se�", "�ptal");
	return 1;
}*/

CMD:radyocal(playerid, params[])
{
	new vehicle = GetPlayerVehicleID(playerid);

    if (!vehicle || !IsDriver(playerid))				return SendErrorMessage(playerid, "S�r�c� koltu�unun arkas�na oturman�z gerekir.");
	if (!VehicleInfo[vehicle][carOwnerID])				return SendErrorMessage(playerid, "Sadece ki�isel ara�lar�n teybini �alabilirsiniz. ");
    if (!VehicleInfo[vehicle][carRadio])				return SendErrorMessage(playerid, "Bu ara�ta teyp bulunmamakta.");
    if (PlayerInfo[playerid][pCalintiRadyo] == 5)		return SendErrorMessage(playerid, "Maksimum 5 adet �al�nt� radyo ta��yabilirsin.");
    
	VehicleInfo[vehicle][carRadio] = 0;
	PlayerInfo[playerid][pCalintiRadyo]++;
	
	new mes[128];
	format(mes, sizeof(mes), "%s model arac�n radyosunu �alar.", VehicleNames[GetVehicleModel(vehicle)-400]);
	pc_cmd_me(playerid, mes);
	return 1;
}

/*
CMD:birlikmeslek(playerid, params[])
{
	if (!PlayerInfo[playerid][pFaction])																										return SendErrorMessage(playerid, "Onayl� illegal birlik �yesi de�ilsiniz.");
	if (Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_GANG && Factions[PlayerInfo[playerid][pFaction]][fType] != FACTION_MAFIA)	return SendErrorMessage(playerid, "Onayl� illegal birlikte olmal�s�n�z.");
    if (!isLeader(playerid))																													return SendErrorMessage(playerid, "Bu i� sadece onayl� illegal birlik liderleri taraf�ndan kullan�labilir.");

	new userid, level;

	if (sscanf(params, "ud", userid, level)) return SendHelpMessage(playerid, "/birlikmeslek [ID/�simn [0 - eri�imi kapat | 1 - uyu�turucu sat�n alma eri�imi | 2 - silah sat�n alma eri�imi] ");

	if (!IsPlayerLogged(userid))											return SendNotConnected(playerid);
	if (PlayerInfo[userid][pFaction] != PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Bu oyuncu sizin birli�inizin bir �yesi de�il.");
    if (level > 2 || level < 0)											return SendErrorMessage(playerid, "Se�enek 0 ila 2 aras�nda olabilir.");
		
	if (!level)
	{
	    if (PlayerInfo[userid][pSideJob] == 0)	return SendErrorMessage(playerid, "Oyuncunun herhangi bir yan mesle�i yok.");

		SendSyntaxMessage(userid, "%s adl� birlik lideri yetkinizi  %s yetkisine �evirdi. ", GetNameEx(playerid), GetJobName(PlayerInfo[userid][pSideJob]));
		SendSyntaxMessage(playerid, "%s adl� ki�iyi %s adl� meslekten ��kard�n�z.", GetNameEx(userid), GetJobName(PlayerInfo[userid][pSideJob]));
        PlayerInfo[userid][pSideJob] = 0;
		return 1;
	}
	
    PlayerInfo[userid][pSideJob] = level + 3;
	SendSyntaxMessage(userid, "%s adl� birlik lideri yetkinizi  %s yetkisine �evirdi", GetNameEx(playerid), GetJobName(PlayerInfo[userid][pSideJob]));
	SendSyntaxMessage(playerid, "%s adl� ki�iye %s izni verdiniz.", GetNameEx(userid), GetJobName(PlayerInfo[userid][pSideJob]));
	return 1;
}*/