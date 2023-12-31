/*CMD:up(playerid, params[])
{
	new amount, Float:x, Float:y, Float:z;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params,"d", amount)) 			return SendHelpMessage(playerid, "/up [blok]");

	GetPlayerPos(playerid, x, y ,z);
	SetPlayerPosEx(playerid, x, y, z+amount);
	return 1;
}

CMD:down(playerid, params[])
{
	new amount, Float:x, Float:y, Float:z;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params,"d", amount)) 			return SendHelpMessage(playerid, "/down [blok]");

	GetPlayerPos(playerid, x, y ,z);
	SetPlayerPosEx(playerid, x, y, z-amount);
	return 1;
}*/

CMD:policer(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))
		return SendErrorMessage(playerid, "Komutu kullanmak i�in yeterli yetkiniz bulunmuyor.");

	//SCMALL(COLOR_LIGHTBLUE, "<< THE ADMINISTRATOR PRODUCED RESPAVN OF POLICE TS >>");
	AMSG(COLOR_LIGHTRED, "%s adl� yetkili polis ara�lar�n� spawnlad�.", GetAccName(playerid));

	new vehicle,
	    occupied[MAX_VEHICLES char];

    foreach(new i : Player)
	{
	    if ((vehicle = GetPlayerVehicleID(i)) == 0 || !IsFactionPolice(VehicleInfo[vehicle][carFaction]))
	        continue;

		occupied{vehicle} = 1;
	}

	foreach(new i:Vehicle)
	{
		if (!IsFactionPolice(VehicleInfo[vehicle][carFaction]) || occupied{i} == 1)
			continue;

		RespawnVehicle(i);
	}
	return 1;
}

CMD:getincar(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/getincar [Ara� ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Bu ID'ye sahip ara� bulunamad�.");

	PutPlayerInVeh(playerid, vehicle, 0);
	SendAdmMessage("%s adl� y�netici araca ���nland�. [ID: %i]", GetAccName(playerid), vehicle);
	return 1;
}

alias:afire("ayangin");
CMD:afire(playerid,params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);

	new option[16];
	new secoption[128];

	if (sscanf(params, "s[16]S()[128]", option, secoption))
	{
		SendHelpMessage(playerid, "/afire [olustur / kaldir / hepsinikaldir]");
		return 1;
	}

	if (CompareStrings(option, "olustur"))
	{
		if (GetPVarInt(playerid, #crt_fire) == 0)
		{
			SetPVarInt(playerid, #crt_fire, 1);

  			GivePlayerWeapon(playerid, 24, 500);

			SendServerMessage(playerid, "Yang�n olu�turma moduna girdiniz.");
			SendServerMessage(playerid, "Ate� etti�iniz yerde otomatik olarak yang�n olu�turulacakt�r.");
			SendAdmMessage("%s adl� y�netici yang�n olu�turma moduna girdi.", GetAccName(playerid));
			return 1;
		}

		SendServerMessage(playerid, "Yang�n olu�turma modundan ��kt�n�z, T�m yang�nlar� kald�rmak i�in [/afire kaldir] komutunu kullan�n");
		SendAdmMessage("%s adl� y�netici yang�n olu�turma modundan ��kt�.", GetAccName(playerid));

		ResetPlayerWeapons(playerid);
		DeletePVar(playerid, #crt_fire);
	 	return 1;
	}

	else if (CompareStrings(option, "kaldir"))
	{
		new fireid = -1;
		if (sscanf(secoption, "i", fireid))		 return SendHelpMessage(playerid, "/afire kaldir [Yang�n ID]");
		if (FiresInfo[fireid][fireOn] == 0)	return SendErrorMessage(playerid, "Yang�n bulunamad�.");
		if (FiresInfo[fireid][fireOn] == 1) {
			SendAdmMessage("%s adl� y�netici (ID:%d) yang�n� kald�rd�.", GetAccName(playerid), fireid);
			DeleteFire(fireid);
			return 1;
			}
	}
	else if (CompareStrings(option, "hepsinikaldir"))
	{
		for(new i; i != MAX_FIRES; i++)
		{
			if (FiresInfo[i][fireOn] == 0) continue;

			DeleteFire(i);
		}
		SendAdmMessage("%s adl� y�netici sunucuda bulunan t�m yang�nlar� kald�rd�.", GetAccName(playerid));
	}

	else
	{
		SendHelpMessage(playerid, "/afire [olustur / kaldir / hepsinikaldir]");
	}
	return 1;
}

alias:aengine("amotor");
CMD:aengine(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (!IsPlayerInAnyVehicle(playerid))			return SendNotInVehicle(playerid);

	new vehicleid = GetPlayerVehicleID(playerid);

	ToggleVehicleEngine(vehicleid, playerid);
	return 1;
}

CMD:fillveh(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/fillveh [Ara� ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen ara� bulunamad�.");

    VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
	SendServerMessage(playerid, "%i ID'li arac�n yak�t�n� dolduruldunuz.", vehicle);
	return 1;
}

CMD:fillallveh(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(i));
	}

	SendAdmMessageToAll("%s adl� y�netici taraf�ndan sunucudaki t�m ara�lar�n yak�t� dolduruldu.", GetAccName(playerid));
	return 1;
}

CMD:battery(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/battery [Ara� ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen ara� bulunamad�.");

    VehicleInfo[vehicle][carBattery] = 100.00;
	SendServerMessage(playerid, "%i ID'li arac�n ak�s�n� de�i�tirdiniz.", vehicle);
	return 1;
}

CMD:batteryall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carBattery] = 100.00;
	}

	SendAdmMessageToAll("%s adl� y�netici taraf�ndan sunucudaki t�m ara�lar�n ak�s� de�i�tirildi.", GetAccName(playerid));
	return 1;
}

CMD:fillengine(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/fillengine [Ara� ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen ara� bulunamad�.");

    VehicleInfo[vehicle][carBattery] = 100.00;
	SendServerMessage(playerid, "%i ID'li arac�n motorunu de�i�tirdiniz.", vehicle);
	return 1;
}

CMD:engineall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carEngine] = 100.00;
	}

	SendAdmMessageToAll("%s adl� y�netici taraf�ndan sunucudaki t�m ara�lar�n motorunu de�i�tirdi.", GetAccName(playerid));
	return 1;
}


alias:rtc("spawnveh", "vehspawn", "aracspawn");
CMD:rtc(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && PlayerInfo[playerid][pHelper] < 4)	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/rtc [Ara� ID]");
    if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen ara� bulunamad�.");
	if (!VehicleEmpty(vehicle))					return SendErrorMessage(playerid, "Bu ara� �u an kullan�l�yor.");

	if (VehicleInfo[vehicle][carOwnerID] > 0 && VehicleInfo[vehicle][carOwnerID] != INVALID_PLAYER_ID)
	{
	    new userid = GetVehicleOwner(vehicle);

	    if (userid != INVALID_PLAYER_ID)
	    {
	    	SendServerMessage(userid, "%s adl� y�netici %s arac�n� park etti.", GetAccName(playerid), VehicleNames[GetVehicleModel(vehicle)-400]);
			PlayerInfo[userid][pCarKey] = 0;
			VehicleInfo[vehicle][carOwnerPlayer] = INVALID_PLAYER_ID;
		}
		ResetVehicleStuff(vehicle, 1);
		DestroyVehicleEx(vehicle, 1);
	}
    else
	{
		SendServerMessage(playerid, "%s [ID: %i] arac�n� spawnlad�n�z.", VehicleNames[GetVehicleModel(vehicle)-400], vehicle);
		RespawnVehicle(vehicle);
	}
	return 1;
}

alias:rtcall("spawnvehall", "vehspawnall");
CMD:rtcall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);

	SendAdmMessage("%s adl� y�netici kullan�lmayan t�m ara�lar� respawnlad�.", GetAccName(playerid));

    new vehicle, occupied[MAX_VEHICLES char];

    foreach(new i : Player)
	{
	    if ((vehicle = GetPlayerVehicleID(i)) == 0) continue;

		occupied{vehicle} = 1;
	}

	for(new i = 1; i < MAX_VEHICLES; i++)
	{
		if (!IsValidVehicle(i) || occupied{i} == 1) continue;

		if (VehicleInfo[i][carOwnerID] > 0 && VehicleInfo[i][carOwnerID] != INVALID_PLAYER_ID)
		{
		    new userid = GetVehicleOwner(i);
		    if (userid != INVALID_PLAYER_ID)
		    {
		    	SendServerMessage(userid, "%s adl� y�netici %s model arac�n� park etti.", GetAccName(playerid), VehicleNames[GetVehicleModel(i)-400]);
				PlayerInfo[userid][pCarKey] = 0;
				VehicleInfo[i][carOwnerPlayer] = INVALID_PLAYER_ID;
			}
			ResetVehicleStuff(i, 1);
			DestroyVehicleEx(i, 1);
		}
	    else RespawnVehicle(i);
	}
	return 1;
}

CMD:amark(playerid, params[])
{
	new option[16], string[145];

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendErrorMessage(playerid, "Bu komutu kullanamazs�n�z");
	if (sscanf(params, "s[16]S()[144]", option, string))
	{
		SendHelpMessage(playerid, "/amark [destroy/info/goto]");
		return 1;
	}

	if (CompareStrings(option, "destroy"))
	{
		new markid;
		if (sscanf(string, "i", markid))								return SendHelpMessage(playerid, "/amark destroy [ID]");
		if (markid < 0 || markid >= MAX_MARKS || !E_MARKS[markid][mON])	return SendErrorMessage(playerid, "Bu ID'ye sahip i�aret mevcut de�il.");

		DestroyDynamicMark(markid);
		SendServerMessage(playerid, "��areti ba�ar�l� �ekilde kald�rd�n�z. [ID: %i].", markid);
		return 1;
	}
	else if (CompareStrings(option, "info"))
	{
		new markid = Mark_Nearest(playerid);

		if (markid == -1) return SendErrorMessage(playerid, "Belirtilen ID'ye sahip i�aret bulunmuyor.");

		new mark_info[512];
		mark_info[0] = EOS;

		format(mark_info, sizeof(mark_info), "ID\t%i\nOlusturan\t%s\nOlusturma Tarihi\t%s", markid, E_MARKS[markid][mCreator], E_MARKS[markid][mCreateDate]);
		Dialog_Show(playerid, None, DIALOG_STYLE_TABLIST, "{FFFFFF}Isaret Bilgisi", mark_info, "Kapat", "");
		return 1;
	}
	else if (CompareStrings(option, "goto"))
	{
		new markid;
		if (sscanf(string, "i", markid))								return SendHelpMessage(playerid, "/amark goto [ID]");
		if (markid < 0 || markid > MAX_MARKS || !E_MARKS[markid][mON])	return SendErrorMessage(playerid, "Bu ID'ye sahip i�aret mevcut de�il.");

		SetPlayerPosEx(playerid, E_MARKS[markid][mPosX], E_MARKS[markid][mPosY], E_MARKS[markid][mPosZ]);
		SetInterior(playerid, E_MARKS[markid][mInt]);
		SetWorld(playerid, E_MARKS[markid][mVW]);
	}
	else
	{
		SendHelpMessage(playerid, "/amark [destroy/info/goto]");
	}
	return 1;
}

CMD:sethp(playerid, params[])
{
	new userid, hp;
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL && !IsTesterLead(playerid) && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);
	if (sscanf(params,"ud", userid, hp))		return SendHelpMessage(playerid, "/sethp [ID/Karakter Ad�] [1-300]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
    if (PlayerInfo[playerid][pInjured]) 		return SendErrorMessage(playerid, "Belirtilen oyuncu yaral� veya �l�m a�amas�nda. /aheal kullan�n.");
	if (hp < 1 || hp > 300)						return SendErrorMessage(playerid, "Belirtilen de�er 1 ile 300 aras�nda olmal�d�r.");

	SendServerMessage(userid, "%s adl� y�netici can�n�z� d�zenledi: %i HP.", GetAccName(playerid), hp);
	SendServerMessage(playerid, "%s adl� oyuncunun can�n� d�zenlediniz: %i HP.", GetNameEx(userid), hp);
	PlayerInfo[userid][pHealth] = hp;
	return 1;
}

alias:setarmour("setarmor");
CMD:setarmour(playerid, params[])
{
	new userid, armour;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"ud", userid, armour))	return SendHelpMessage(playerid, "/setarmour [ID/Karakter Ad�] [1-300]");
	if (armour < 1 || armour > 300)				return SendErrorMessage(playerid, "Belirtilen de�er 1 ile 300 aras�nda olmal�d�r.");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	SendServerMessage(userid, "Y�netici z�rh�n�z� d�zenledi: %i z�rh", armour);
	SendServerMessage(playerid, "%s adl� oyuncunun z�rh�n� d�zenlediniz: %i z�rh", GetNameEx(userid), armour);
    SetPlayerArmour(userid, armour);
	return 1;
}

CMD:setskin(playerid, params[])
{
	new targetid, skinid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);
	if (sscanf(params,"ui", targetid, skinid))		return SendHelpMessage(playerid, "/setskin [ID/Karakter Ad�] [ID]");
	if (!IsPlayerLogged(targetid))					return SendNotConnected(playerid);
	if (skinid < 1 || skinid == 74)					return SendErrorMessage(playerid, "Ge�ersiz skin id girdiniz.");

	SetPlayerSkinEx(targetid, skinid);
	SendServerMessage(targetid, "Y�netici k�yafetinizi de�i�tirdi. [ID: %i].", skinid);
	SendServerMessage(playerid, "%s adl� oyuncunun k�yafetini de�i�tirdiniz. [ID: %i].", GetNameEx(targetid), skinid);
	return 1;
}

CMD:showpm(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/showpm [ID/Karakter Ad�]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

    pTemp[playerid][pPMPlayer] = userid;
	SendServerMessage(playerid, "%s adl� oyuncunun PM'lerini g�r�nt�lemeye ba�lad�n�z. Kapatmak i�in /showpmoff", GetNameEx(userid));
	return 1;
}

CMD:showpmoff(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))				return SendNotAdmin(playerid);
	if (pTemp[playerid][pPMPlayer] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Herhangi bir PM'e bakm�yorsunuz.");

	SendServerMessage(playerid, "%s adl� oyuncunun PM izlemesini kapatt�n�z.", GetNameEx(pTemp[playerid][pPMPlayer]));
	pTemp[playerid][pPMPlayer] = INVALID_PLAYER_ID;
	return 1;
}

CMD:showpms(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	SendServerMessage(playerid, "T�m sunucunun PM'lerini g�r�nt�l�yorsunuz. Kapatmak i�in /nopms");
	SetPVarInt(playerid, #spypm_all, 1);
	return 1;
}

CMD:nopms(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))
		return SendNotAdmin(playerid);

	if (GetPVarInt(playerid, #spypm_all) == 0)
		return SendErrorMessage(playerid, "Herhangi birini izlemiyorsunuz.");

	SendServerMessage(playerid, "PM izlemesini kapatt�n�z.");
	DeletePVar(playerid, #spypm_all);
	return 1;
}

CMD:telecmds(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_3)) return SendNotAdmin(playerid);

	SCM(playerid, COLOR_WHITE, "[Level 3]: {C3C3C3}/atp /maketele /makehouseint /removetele");
	return 1;
}

alias:makehouseint("mhouseint");
CMD:makehouseint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	new mapname[32],
		type;

	if (sscanf(params,"is[32]", type, mapname))
		return SendHelpMessage(playerid, "/makehouseint [1-k���k, 2-orta, 3-b�y�k] [interior ismi]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Ev tipi: 1-k���k, 2-orta, 3-b�y�k.");

    if (strlen(mapname) < 1 || strlen(mapname) > 32)
	    return SendErrorMessage(playerid, "Interior ismi 1 ile 32 karakter aras�nda olmal�d�r..");

	new id = -1;
	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (0 != AdminTeles[i][telesOn])
			continue;

		id = i;
		break;
	}

	if (id == -1)
	    return SendErrorMessage(playerid, "I��nlanma s�n�r�na ula��ld�.");

	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = type-1;
	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
    AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], type-1);
 	SendClientMessageEx(playerid,COLOR_SERVER2,"Yeni interior olu�turuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
	return 1;
}

CMD:delplayertickets(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/delplayertickets [ID/Karakter Ad�]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	DeletePlayerTickets(userid);

	SendServerMessage(playerid, "%s adl� oyuncunun cezalar� silindi.", GetNameEx(userid));
	SendServerMessage(userid, "Y�netici t�m cezalar�n�z� sildi.");

	return 1;
}

CMD:delvehtickets(playerid, params[])
{
	new vehid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"i", vehid))				return SendHelpMessage(playerid, "/delvehtickets [Ara� ID]");
	if (VehicleInfo[vehid][carModel] < 400 && VehicleInfo[vehid][carModel] > 600) return SendErrorMessage(playerid, "Bu ara� y�netici arac� oldu�u i�in i�lem yap�lamaz.");

	DeleteVehicleTickets(vehid);

	SendServerMessage(playerid, "%s [ID: %i] belirtilen arac�n�n t�m cezalar�n� kald�rd�n�z.", VehicleNames[VehicleInfo[vehid][carModel]-400], vehid);

	return 1;
}

CMD:aunimpound(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params,"i", vehicle))			return SendHelpMessage(playerid, "/aunimpound [Ara� ID]");

	if (!IsValidVehicle(vehicle))			return SendErrorMessage(playerid, "Belirtilen ara� spawnlanmam��.");
	if (!VehicleInfo[vehicle][Impounded])	return SendErrorMessage(playerid, "Ara� ba�lanmam��.");

	VehicleInfo[vehicle][Impounded] = 0;
	Save_Car(vehicle);

	SendServerMessage(playerid, "%i ID'li, sahibi %s olan, ara� art�k ba�lanmam�� halde.", vehicle, GetNameEx(VehicleInfo[vehicle][carOwnerID]));
	SendServerMessage(VehicleInfo[vehicle][carOwnerID], "Y�netici %s model arac�n�z�n� ceza durumundan kurtard�.", VehicleNames[VehicleInfo[vehicle][carModel]-400]);
	return 1;
}

alias:makebizint("mbizint");
CMD:makebizint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	new mapname[32];

	if (sscanf(params,"s[32]", mapname))
		return SendHelpMessage(playerid, "/makebizint [interior ad�]");

	if (strlen(mapname) < 1 || strlen(mapname) > 32)
	    return SendErrorMessage(playerid, "Belirtilen isim minimum 1, maksimum 32 karakter olmal�d�r.");

	new id = -1;
	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (0 != AdminTeles[i][telesOn])
			continue;

		id = i;
		break;
	}

	if (id == -1)
	    return SendErrorMessage(playerid, "I��nlanma s�n�r�na ula��ld�.");

	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = BUSSINESS_INT_TYPE;
	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
    AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], 4);
 	SendClientMessageEx(playerid,COLOR_SERVER2, "Yeni interior (%s) ID: %i eklendi.", AdminTeles[id][telesMapName], id); //����� ���
	return 1;
}

alias:maketele("mtele");
CMD:maketele(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	new mapname[32];

	if (sscanf(params,"s[32]", mapname))				return SendHelpMessage(playerid, "/maketele [Name int]");
	if (strlen(mapname) < 1 || strlen(mapname) > 32)	return SendErrorMessage(playerid, "Characters 1-32.");

	new id = -1;

	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (AdminTeles[i][telesOn]) continue;

		id = i;
		break;
	}

	if (id == -1)	 return SendErrorMessage(playerid, "Teleport limit reached.");

	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = 3;
	AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], 3);
 	SendServerMessage(playerid, "Yeni teleport noktas� olu�turuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
	return 1;
}

alias:makegps("mgps");
CMD:makegps(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	new mapname[32];

	if (sscanf(params,"s[32]", mapname))				return SendHelpMessage(playerid, "/makegps [g�r�necek ad]");
	if (strlen(mapname) < 1 || strlen(mapname) > 32)	return SendErrorMessage(playerid, "1-32 karakter olmal� isim.");

	new id = -1;

	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (AdminTeles[i][telesOn]) continue;

		id = i;
		break;
	}

	if (id == -1)	 return SendErrorMessage(playerid, "Limite ula��ld�.");

	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = GPS_TELE_TYPE;
	AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], GPS_TELE_TYPE);
 	SendServerMessage(playerid, "Yeni GPS noktas� olu�turuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
	return 1;
}

alias:removetele("rtele");
CMD:removetele(playerid,params[])
{
	new teleid;
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	if (sscanf(params,"d",teleid))
		return SendHelpMessage(playerid, "/removetele [ID Teleport]");

	if (AdminTeles[teleid][telesOn] == 0)
	    return SendErrorMessage(playerid, "Belirtilen ID ge�ersiz.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `ateles` WHERE `id` = %i", AdminTeles[teleid][aID]);
	mysql_tquery(dbHandle, query);

	SendServerMessage(playerid, "Belirtilen teleport noktas� silindi. ID %i.", teleid);

	AdminTeles[teleid][telesOn] = 0;
	AdminTeles[teleid][telesType] = 0;
	return 1;
}

/*
CMD:aveh(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	new model, color1, color2, Float:x, Float:y, Float:z, Float:a, Float: distance = 5.0;

	if (sscanf(params, "iI(0)I(0)", model, color1, color2))								return SendHelpMessage(playerid, "/aveh [model] {c7c7c7}[color1] [color2]");
	if (model == 520 || model == 425 || model == 432 || model == 447 || model == 476)	return SendErrorMessage(playerid, "Bu t�r modeller sunucuda yasakt�r.");
	if (model < 400 || model > 611) 													return SendErrorMessage(playerid, "Ara� modelleri 400 ile 611 aras�nda olmal�d�r.");
	if (color1 > 255 || color1 < 0 || color2 > 255 || color2 < 0)						return SendErrorMessage(playerid, "Renk 0 ile 255 aras�nda olmal�d�r.");

	GetPlayerPos(playerid, x, y ,z);
	GetPlayerFacingAngle(playerid, a);
  	x += (distance * floatsin(-a, degrees));
    y += (distance * floatcos(-a, degrees));
	a += 90.0;

	if (a > 360.0) a -= 360.0;

	new vehicle = CreateVehicle(model, x, y, z, a, color1, color2, -1);

	if (vehicle == INVALID_VEHICLE_ID)	return SendErrorMessage(playerid, "Ara� olu�turulamad�.");

	SetVehicleHealth(vehicle, 1000.0);
	SetVehicleNumberPlate(vehicle, GetVehicleNumber());
	SetVehicleVirtualWorld(vehicle, GetWorld(playerid));
	LinkVehicleToInterior(vehicle, GetInterior(playerid));
    VehicleInfo[vehicle][carDriver] = INVALID_PLAYER_ID;
	VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
	VehicleInfo[vehicle][carAdmin] = 1;
	VehicleInfo[vehicle][carColor1] = color1;
	VehicleInfo[vehicle][carColor2] = color2;
	VehicleInfo[vehicle][carType] = 0;

	SendAdmMessageToPlayer(playerid, "Ara� Olu�turuldu: %s [ID: %i | MODEL: %i].", VehicleNames[model-400], vehicle, model);
	return 1;
}
*/

CMD:makemark(playerid, params[])
{
	new Float:x, Float:y, Float:z, interior, world;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	interior = GetInterior(playerid);
	world = GetWorld(playerid);
	GetPlayerPos(playerid, x, y, z);
	SetPVarInt(playerid, "MarkedSpot", 1);
	SetPVarFloat(playerid, "MarkX", x);
	SetPVarFloat(playerid, "MarkY", y);
	SetPVarFloat(playerid, "MarkZ", z);
	SetPVarInt(playerid, "MarkInterior", interior);
	SetPVarInt(playerid, "MarkWorld", world);
	SendAdmMessageToPlayer(playerid, "Nokta ayarland�, ���nlanmak i�in: \"/gotomark\"");
	return 1;
}

CMD:gotomark(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 		return SendNotAdmin(playerid);
	if (GetPVarInt(playerid, "MarkedSpot") == 0) 	return SendErrorMessage(playerid, "Nokta belirlenmedi. \"/mark\" komutunu kullan�n.");

	SetPlayerPosEx(playerid, GetPVarFloat(playerid, "MarkX"), GetPVarFloat(playerid, "MarkY"), GetPVarFloat(playerid, "MarkZ"));
	SetWorld(playerid, GetPVarInt(playerid, "MarkWorld"));
	SetInterior(playerid, GetPVarInt(playerid, "MarkInterior"));
	SCM(playerid, COLOR_GREY, "* I��nland�n�z.");
	return 1;
}

CMD:settime(playerid, params[])
{
	new time;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", time))				return SendHelpMessage(playerid, "/settime [0-23]");
	if (time < 0 || time > 23)					return SendErrorMessage(playerid, "Zaman 0 ile 23 aras�nda olmal�d�r.");

	SetWorldTime(time);
	SAMALL("%s adl� y�netici sunucu saatini de�i�tirdi. Saat: %i:00.", GetAccName(playerid), time);
	return 1;
}
CMD:weather(playerid, params[])
{
	new weather;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", weather))			return SendHelpMessage(playerid, "/weather [hava durumu]");
	if (weather < 0 || weather > 45)				return SendErrorMessage(playerid, "Hava durumu 0 ile 45 aras�nda olmal�d�r.");

	SetPlayerWeather(playerid, weather);
	return 1;
}

CMD:weatherall(playerid, params[])
{
	new weather;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "d", weather))			return SendHelpMessage(playerid, "/weatherall [hava durumu]");
	if (weather < 0||weather > 45)				return SendErrorMessage(playerid, "Hava durumu 0 ile 45 aras�nda olmal�d�r.");

    server_weather = weather;
	SetWeather(server_weather);

	SAMALL("%s adl� y�netici hava durumunu de�i�tirdi. [ID %i].", GetAccName(playerid), weather);
	return 1;
}

CMD:govw(playerid, params[])
{
	new vw;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "i", vw))				return SendHelpMessage(playerid, "/govw [0-65535]");
	if (vw < 0 || vw > 65535)					return SendErrorMessage(playerid, "Belirtilen de�er 0 ile 65535 aras�nda olmal�d�r.");

	SetWorld(playerid, vw);
	SendServerMessage(playerid, "D�nyan�z� de�i�tirdiniz: %i.", vw);
	return 1;
}

CMD:goint(playerid, params[])
{
	new interior;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "i", interior)) 			return SendHelpMessage(playerid, "/goint [0-255]");
	if (interior < 0 || interior > 255)			return SendErrorMessage(playerid, "Belirtilen de�er 0 ile 255 aras�nda olmal�d�r.");

	SetInterior(playerid, interior);
	SendServerMessage(playerid, "Interiorunuzu de�i�tirdiniz: %i.", interior);
	return 1;
}

CMD:go(playerid, params[])
{
	new Float:x, Float:y, Float:z, interior, vw;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 				 return SendNotAdmin(playerid);
	if (sscanf(params,"fffI(0)I(0)", x, y ,z, interior, vw)) return SendHelpMessage(playerid, "/go [x] [y] [z] {c7c7c7}[interior (0-255)] [vw (0-65535)]");
	if (interior < 0 || interior > 255)						 return SendErrorMessage(playerid, "Interior 0 ile 255 aras�nda olmal�d�r.");
	if (vw < 0 || vw > 65535)								 return SendErrorMessage(playerid, "VW 0 ile 65535 aras�nda olmal�d�r.");

	SetPlayerPosEx(playerid, x, y, z);
	SetInterior(playerid, interior);
 	SetWorld(playerid, vw);
	return 1;
}

CMD:x(playerid, params[])
{
	new Float: coord;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"f", coord))				return SendHelpMessage(playerid, "/x [+x koordinat]");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerPosEx(playerid, x + coord, y, z);
	return 1;
}

CMD:y(playerid, params[])
{
	new Float: coord;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"f", coord))				return SendHelpMessage(playerid, "/y [+y koordinat]");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerPosEx(playerid, x, y + coord, z);
	return 1;
}

CMD:z(playerid, params[])
{
	new Float: coord;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"f", coord))				return SendHelpMessage(playerid, "/z  [+z koordinat]");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerPosEx(playerid, x, y, z + coord);
	return 1;
}

CMD:noooc(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	noooc = !noooc;
	if (noooc == false) SCMALL(COLOR_GRAD2, "OOC sohbet y�netici taraf�ndan aktif edildi.");
	else				SCMALL(COLOR_GRAD2, "OOC sohbet y�netici taraf�ndan deaktif edildi.");
	return 1;
}
