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
		return SendErrorMessage(playerid, "Komutu kullanmak için yeterli yetkiniz bulunmuyor.");

	//SCMALL(COLOR_LIGHTBLUE, "<< THE ADMINISTRATOR PRODUCED RESPAVN OF POLICE TS >>");
	AMSG(COLOR_LIGHTRED, "%s adlý yetkili polis araçlarýný spawnladý.", GetAccName(playerid));

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
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/getincar [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Bu ID'ye sahip araç bulunamadý.");

	PutPlayerInVeh(playerid, vehicle, 0);
	SendAdmMessage("%s adlý yönetici araca ýþýnlandý. [ID: %i]", GetAccName(playerid), vehicle);
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

			SendServerMessage(playerid, "Yangýn oluþturma moduna girdiniz.");
			SendServerMessage(playerid, "Ateþ ettiðiniz yerde otomatik olarak yangýn oluþturulacaktýr.");
			SendAdmMessage("%s adlý yönetici yangýn oluþturma moduna girdi.", GetAccName(playerid));
			return 1;
		}

		SendServerMessage(playerid, "Yangýn oluþturma modundan çýktýnýz, Tüm yangýnlarý kaldýrmak için [/afire kaldir] komutunu kullanýn");
		SendAdmMessage("%s adlý yönetici yangýn oluþturma modundan çýktý.", GetAccName(playerid));

		ResetPlayerWeapons(playerid);
		DeletePVar(playerid, #crt_fire);
	 	return 1;
	}

	else if (CompareStrings(option, "kaldir"))
	{
		new fireid = -1;
		if (sscanf(secoption, "i", fireid))		 return SendHelpMessage(playerid, "/afire kaldir [Yangýn ID]");
		if (FiresInfo[fireid][fireOn] == 0)	return SendErrorMessage(playerid, "Yangýn bulunamadý.");
		if (FiresInfo[fireid][fireOn] == 1) {
			SendAdmMessage("%s adlý yönetici (ID:%d) yangýný kaldýrdý.", GetAccName(playerid), fireid);
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
		SendAdmMessage("%s adlý yönetici sunucuda bulunan tüm yangýnlarý kaldýrdý.", GetAccName(playerid));
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
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/fillveh [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

    VehicleInfo[vehicle][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(vehicle));
	SendServerMessage(playerid, "%i ID'li aracýn yakýtýný dolduruldunuz.", vehicle);
	return 1;
}

CMD:fillallveh(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carFuel] = GetVehicleFuelCapacity(GetVehicleModel(i));
	}

	SendAdmMessageToAll("%s adlý yönetici tarafýndan sunucudaki tüm araçlarýn yakýtý dolduruldu.", GetAccName(playerid));
	return 1;
}

CMD:battery(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/battery [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

    VehicleInfo[vehicle][carBattery] = 100.00;
	SendServerMessage(playerid, "%i ID'li aracýn aküsünü deðiþtirdiniz.", vehicle);
	return 1;
}

CMD:batteryall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carBattery] = 100.00;
	}

	SendAdmMessageToAll("%s adlý yönetici tarafýndan sunucudaki tüm araçlarýn aküsü deðiþtirildi.", GetAccName(playerid));
	return 1;
}

CMD:fillengine(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/fillengine [Araç ID]");
	if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");

    VehicleInfo[vehicle][carBattery] = 100.00;
	SendServerMessage(playerid, "%i ID'li aracýn motorunu deðiþtirdiniz.", vehicle);
	return 1;
}

CMD:engineall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	foreach(new i:Vehicle)
	{
        VehicleInfo[i][carEngine] = 100.00;
	}

	SendAdmMessageToAll("%s adlý yönetici tarafýndan sunucudaki tüm araçlarýn motorunu deðiþtirdi.", GetAccName(playerid));
	return 1;
}


alias:rtc("spawnveh", "vehspawn", "aracspawn");
CMD:rtc(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1) && PlayerInfo[playerid][pHelper] < 4)	return SendNotAdmin(playerid);
	if (sscanf(params,"d",vehicle))				return SendHelpMessage(playerid, "/rtc [Araç ID]");
    if (!IsValidVehicle(vehicle))				return SendErrorMessage(playerid, "Belirtilen araç bulunamadý.");
	if (!VehicleEmpty(vehicle))					return SendErrorMessage(playerid, "Bu araç þu an kullanýlýyor.");

	if (VehicleInfo[vehicle][carOwnerID] > 0 && VehicleInfo[vehicle][carOwnerID] != INVALID_PLAYER_ID)
	{
	    new userid = GetVehicleOwner(vehicle);

	    if (userid != INVALID_PLAYER_ID)
	    {
	    	SendServerMessage(userid, "%s adlý yönetici %s aracýný park etti.", GetAccName(playerid), VehicleNames[GetVehicleModel(vehicle)-400]);
			PlayerInfo[userid][pCarKey] = 0;
			VehicleInfo[vehicle][carOwnerPlayer] = INVALID_PLAYER_ID;
		}
		ResetVehicleStuff(vehicle, 1);
		DestroyVehicleEx(vehicle, 1);
	}
    else
	{
		SendServerMessage(playerid, "%s [ID: %i] aracýný spawnladýnýz.", VehicleNames[GetVehicleModel(vehicle)-400], vehicle);
		RespawnVehicle(vehicle);
	}
	return 1;
}

alias:rtcall("spawnvehall", "vehspawnall");
CMD:rtcall(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);

	SendAdmMessage("%s adlý yönetici kullanýlmayan tüm araçlarý respawnladý.", GetAccName(playerid));

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
		    	SendServerMessage(userid, "%s adlý yönetici %s model aracýný park etti.", GetAccName(playerid), VehicleNames[GetVehicleModel(i)-400]);
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

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendErrorMessage(playerid, "Bu komutu kullanamazsýnýz");
	if (sscanf(params, "s[16]S()[144]", option, string))
	{
		SendHelpMessage(playerid, "/amark [destroy/info/goto]");
		return 1;
	}

	if (CompareStrings(option, "destroy"))
	{
		new markid;
		if (sscanf(string, "i", markid))								return SendHelpMessage(playerid, "/amark destroy [ID]");
		if (markid < 0 || markid >= MAX_MARKS || !E_MARKS[markid][mON])	return SendErrorMessage(playerid, "Bu ID'ye sahip iþaret mevcut deðil.");

		DestroyDynamicMark(markid);
		SendServerMessage(playerid, "Ýþareti baþarýlý þekilde kaldýrdýnýz. [ID: %i].", markid);
		return 1;
	}
	else if (CompareStrings(option, "info"))
	{
		new markid = Mark_Nearest(playerid);

		if (markid == -1) return SendErrorMessage(playerid, "Belirtilen ID'ye sahip iþaret bulunmuyor.");

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
		if (markid < 0 || markid > MAX_MARKS || !E_MARKS[markid][mON])	return SendErrorMessage(playerid, "Bu ID'ye sahip iþaret mevcut deðil.");

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
	if (sscanf(params,"ud", userid, hp))		return SendHelpMessage(playerid, "/sethp [ID/Karakter Adý] [1-300]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);
    if (PlayerInfo[playerid][pInjured]) 		return SendErrorMessage(playerid, "Belirtilen oyuncu yaralý veya ölüm aþamasýnda. /aheal kullanýn.");
	if (hp < 1 || hp > 300)						return SendErrorMessage(playerid, "Belirtilen deðer 1 ile 300 arasýnda olmalýdýr.");

	SendServerMessage(userid, "%s adlý yönetici canýnýzý düzenledi: %i HP.", GetAccName(playerid), hp);
	SendServerMessage(playerid, "%s adlý oyuncunun canýný düzenlediniz: %i HP.", GetNameEx(userid), hp);
	PlayerInfo[userid][pHealth] = hp;
	return 1;
}

alias:setarmour("setarmor");
CMD:setarmour(playerid, params[])
{
	new userid, armour;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"ud", userid, armour))	return SendHelpMessage(playerid, "/setarmour [ID/Karakter Adý] [1-300]");
	if (armour < 1 || armour > 300)				return SendErrorMessage(playerid, "Belirtilen deðer 1 ile 300 arasýnda olmalýdýr.");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	SendServerMessage(userid, "Yönetici zýrhýnýzý düzenledi: %i zýrh", armour);
	SendServerMessage(playerid, "%s adlý oyuncunun zýrhýný düzenlediniz: %i zýrh", GetNameEx(userid), armour);
    SetPlayerArmour(userid, armour);
	return 1;
}

CMD:setskin(playerid, params[])
{
	new targetid, skinid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_1 && !PlayerInfo[playerid][pEbc]))	return SendNotAdmin(playerid);
	if (sscanf(params,"ui", targetid, skinid))		return SendHelpMessage(playerid, "/setskin [ID/Karakter Adý] [ID]");
	if (!IsPlayerLogged(targetid))					return SendNotConnected(playerid);
	if (skinid < 1 || skinid == 74)					return SendErrorMessage(playerid, "Geçersiz skin id girdiniz.");

	SetPlayerSkinEx(targetid, skinid);
	SendServerMessage(targetid, "Yönetici kýyafetinizi deðiþtirdi. [ID: %i].", skinid);
	SendServerMessage(playerid, "%s adlý oyuncunun kýyafetini deðiþtirdiniz. [ID: %i].", GetNameEx(targetid), skinid);
	return 1;
}

CMD:showpm(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/showpm [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

    pTemp[playerid][pPMPlayer] = userid;
	SendServerMessage(playerid, "%s adlý oyuncunun PM'lerini görüntülemeye baþladýnýz. Kapatmak için /showpmoff", GetNameEx(userid));
	return 1;
}

CMD:showpmoff(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))				return SendNotAdmin(playerid);
	if (pTemp[playerid][pPMPlayer] == INVALID_PLAYER_ID)	return SendErrorMessage(playerid, "Herhangi bir PM'e bakmýyorsunuz.");

	SendServerMessage(playerid, "%s adlý oyuncunun PM izlemesini kapattýnýz.", GetNameEx(pTemp[playerid][pPMPlayer]));
	pTemp[playerid][pPMPlayer] = INVALID_PLAYER_ID;
	return 1;
}

CMD:showpms(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL)) return SendNotAdmin(playerid);

	SendServerMessage(playerid, "Tüm sunucunun PM'lerini görüntülüyorsunuz. Kapatmak için /nopms");
	SetPVarInt(playerid, #spypm_all, 1);
	return 1;
}

CMD:nopms(playerid, params[])
{
	if (!CheckAdmin(playerid, HIGH_ADMIN_LEVEL))
		return SendNotAdmin(playerid);

	if (GetPVarInt(playerid, #spypm_all) == 0)
		return SendErrorMessage(playerid, "Herhangi birini izlemiyorsunuz.");

	SendServerMessage(playerid, "PM izlemesini kapattýnýz.");
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
		return SendHelpMessage(playerid, "/makehouseint [1-küçük, 2-orta, 3-büyük] [interior ismi]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Ev tipi: 1-küçük, 2-orta, 3-büyük.");

    if (strlen(mapname) < 1 || strlen(mapname) > 32)
	    return SendErrorMessage(playerid, "Interior ismi 1 ile 32 karakter arasýnda olmalýdýr..");

	new id = -1;
	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (0 != AdminTeles[i][telesOn])
			continue;

		id = i;
		break;
	}

	if (id == -1)
	    return SendErrorMessage(playerid, "Iþýnlanma sýnýrýna ulaþýldý.");

	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = type-1;
	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
    AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], type-1);
 	SendClientMessageEx(playerid,COLOR_SERVER2,"Yeni interior oluþturuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
	return 1;
}

CMD:delplayertickets(playerid, params[])
{
	new userid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"u", userid))				return SendHelpMessage(playerid, "/delplayertickets [ID/Karakter Adý]");
	if (!IsPlayerLogged(userid))				return SendNotConnected(playerid);

	DeletePlayerTickets(userid);

	SendServerMessage(playerid, "%s adlý oyuncunun cezalarý silindi.", GetNameEx(userid));
	SendServerMessage(userid, "Yönetici tüm cezalarýnýzý sildi.");

	return 1;
}

CMD:delvehtickets(playerid, params[])
{
	new vehid;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params,"i", vehid))				return SendHelpMessage(playerid, "/delvehtickets [Araç ID]");
	if (VehicleInfo[vehid][carModel] < 400 && VehicleInfo[vehid][carModel] > 600) return SendErrorMessage(playerid, "Bu araç yönetici aracý olduðu için iþlem yapýlamaz.");

	DeleteVehicleTickets(vehid);

	SendServerMessage(playerid, "%s [ID: %i] belirtilen aracýnýn tüm cezalarýný kaldýrdýnýz.", VehicleNames[VehicleInfo[vehid][carModel]-400], vehid);

	return 1;
}

CMD:aunimpound(playerid, params[])
{
	new vehicle;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_3))	return SendNotAdmin(playerid);
	if (sscanf(params,"i", vehicle))			return SendHelpMessage(playerid, "/aunimpound [Araç ID]");

	if (!IsValidVehicle(vehicle))			return SendErrorMessage(playerid, "Belirtilen araç spawnlanmamýþ.");
	if (!VehicleInfo[vehicle][Impounded])	return SendErrorMessage(playerid, "Araç baðlanmamýþ.");

	VehicleInfo[vehicle][Impounded] = 0;
	Save_Car(vehicle);

	SendServerMessage(playerid, "%i ID'li, sahibi %s olan, araç artýk baðlanmamýþ halde.", vehicle, GetNameEx(VehicleInfo[vehicle][carOwnerID]));
	SendServerMessage(VehicleInfo[vehicle][carOwnerID], "Yönetici %s model aracýnýzýný ceza durumundan kurtardý.", VehicleNames[VehicleInfo[vehicle][carModel]-400]);
	return 1;
}

alias:makebizint("mbizint");
CMD:makebizint(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) return SendNotAdmin(playerid);

	new mapname[32];

	if (sscanf(params,"s[32]", mapname))
		return SendHelpMessage(playerid, "/makebizint [interior adý]");

	if (strlen(mapname) < 1 || strlen(mapname) > 32)
	    return SendErrorMessage(playerid, "Belirtilen isim minimum 1, maksimum 32 karakter olmalýdýr.");

	new id = -1;
	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (0 != AdminTeles[i][telesOn])
			continue;

		id = i;
		break;
	}

	if (id == -1)
	    return SendErrorMessage(playerid, "Iþýnlanma sýnýrýna ulaþýldý.");

	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = BUSSINESS_INT_TYPE;
	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
    AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], 4);
 	SendClientMessageEx(playerid,COLOR_SERVER2, "Yeni interior (%s) ID: %i eklendi.", AdminTeles[id][telesMapName], id); //íîâûé èíò
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
 	SendServerMessage(playerid, "Yeni teleport noktasý oluþturuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
	return 1;
}

alias:makegps("mgps");
CMD:makegps(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	new mapname[32];

	if (sscanf(params,"s[32]", mapname))				return SendHelpMessage(playerid, "/makegps [görünecek ad]");
	if (strlen(mapname) < 1 || strlen(mapname) > 32)	return SendErrorMessage(playerid, "1-32 karakter olmalý isim.");

	new id = -1;

	for(new i = 0; i < MAX_INTERIORS; i++)
	{
	    if (AdminTeles[i][telesOn]) continue;

		id = i;
		break;
	}

	if (id == -1)	 return SendErrorMessage(playerid, "Limite ulaþýldý.");

	format(AdminTeles[id][telesMapName], 32, "%s", mapname);
	GetPlayerPos(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	AdminTeles[id][telesInt] = GetInterior(playerid);
	AdminTeles[id][telesType] = GPS_TELE_TYPE;
	AdminTeles[id][telesOn] = 1;

	AddTeleToFile(playerid, id, mapname, AdminTeles[id][telesInt], AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ], GPS_TELE_TYPE);
 	SendServerMessage(playerid, "Yeni GPS noktasý oluþturuldu. (%s) ID: %i", AdminTeles[id][telesMapName], id);
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
	    return SendErrorMessage(playerid, "Belirtilen ID geçersiz.");

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `ateles` WHERE `id` = %i", AdminTeles[teleid][aID]);
	mysql_tquery(dbHandle, query);

	SendServerMessage(playerid, "Belirtilen teleport noktasý silindi. ID %i.", teleid);

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
	if (model == 520 || model == 425 || model == 432 || model == 447 || model == 476)	return SendErrorMessage(playerid, "Bu tür modeller sunucuda yasaktýr.");
	if (model < 400 || model > 611) 													return SendErrorMessage(playerid, "Araç modelleri 400 ile 611 arasýnda olmalýdýr.");
	if (color1 > 255 || color1 < 0 || color2 > 255 || color2 < 0)						return SendErrorMessage(playerid, "Renk 0 ile 255 arasýnda olmalýdýr.");

	GetPlayerPos(playerid, x, y ,z);
	GetPlayerFacingAngle(playerid, a);
  	x += (distance * floatsin(-a, degrees));
    y += (distance * floatcos(-a, degrees));
	a += 90.0;

	if (a > 360.0) a -= 360.0;

	new vehicle = CreateVehicle(model, x, y, z, a, color1, color2, -1);

	if (vehicle == INVALID_VEHICLE_ID)	return SendErrorMessage(playerid, "Araç oluþturulamadý.");

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

	SendAdmMessageToPlayer(playerid, "Araç Oluþturuldu: %s [ID: %i | MODEL: %i].", VehicleNames[model-400], vehicle, model);
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
	SendAdmMessageToPlayer(playerid, "Nokta ayarlandý, ýþýnlanmak için: \"/gotomark\"");
	return 1;
}

CMD:gotomark(playerid, params[])
{
	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 		return SendNotAdmin(playerid);
	if (GetPVarInt(playerid, "MarkedSpot") == 0) 	return SendErrorMessage(playerid, "Nokta belirlenmedi. \"/mark\" komutunu kullanýn.");

	SetPlayerPosEx(playerid, GetPVarFloat(playerid, "MarkX"), GetPVarFloat(playerid, "MarkY"), GetPVarFloat(playerid, "MarkZ"));
	SetWorld(playerid, GetPVarInt(playerid, "MarkWorld"));
	SetInterior(playerid, GetPVarInt(playerid, "MarkInterior"));
	SCM(playerid, COLOR_GREY, "* Iþýnlandýnýz.");
	return 1;
}

CMD:settime(playerid, params[])
{
	new time;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", time))				return SendHelpMessage(playerid, "/settime [0-23]");
	if (time < 0 || time > 23)					return SendErrorMessage(playerid, "Zaman 0 ile 23 arasýnda olmalýdýr.");

	SetWorldTime(time);
	SAMALL("%s adlý yönetici sunucu saatini deðiþtirdi. Saat: %i:00.", GetAccName(playerid), time);
	return 1;
}
CMD:weather(playerid, params[])
{
	new weather;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "d", weather))			return SendHelpMessage(playerid, "/weather [hava durumu]");
	if (weather < 0 || weather > 45)				return SendErrorMessage(playerid, "Hava durumu 0 ile 45 arasýnda olmalýdýr.");

	SetPlayerWeather(playerid, weather);
	return 1;
}

CMD:weatherall(playerid, params[])
{
	new weather;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "d", weather))			return SendHelpMessage(playerid, "/weatherall [hava durumu]");
	if (weather < 0||weather > 45)				return SendErrorMessage(playerid, "Hava durumu 0 ile 45 arasýnda olmalýdýr.");

    server_weather = weather;
	SetWeather(server_weather);

	SAMALL("%s adlý yönetici hava durumunu deðiþtirdi. [ID %i].", GetAccName(playerid), weather);
	return 1;
}

CMD:govw(playerid, params[])
{
	new vw;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 	return SendNotAdmin(playerid);
	if (sscanf(params, "i", vw))				return SendHelpMessage(playerid, "/govw [0-65535]");
	if (vw < 0 || vw > 65535)					return SendErrorMessage(playerid, "Belirtilen deðer 0 ile 65535 arasýnda olmalýdýr.");

	SetWorld(playerid, vw);
	SendServerMessage(playerid, "Dünyanýzý deðiþtirdiniz: %i.", vw);
	return 1;
}

CMD:goint(playerid, params[])
{
	new interior;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2))	return SendNotAdmin(playerid);
	if (sscanf(params, "i", interior)) 			return SendHelpMessage(playerid, "/goint [0-255]");
	if (interior < 0 || interior > 255)			return SendErrorMessage(playerid, "Belirtilen deðer 0 ile 255 arasýnda olmalýdýr.");

	SetInterior(playerid, interior);
	SendServerMessage(playerid, "Interiorunuzu deðiþtirdiniz: %i.", interior);
	return 1;
}

CMD:go(playerid, params[])
{
	new Float:x, Float:y, Float:z, interior, vw;

	if (!CheckAdmin(playerid, ADMIN_LEVEL_2)) 				 return SendNotAdmin(playerid);
	if (sscanf(params,"fffI(0)I(0)", x, y ,z, interior, vw)) return SendHelpMessage(playerid, "/go [x] [y] [z] {c7c7c7}[interior (0-255)] [vw (0-65535)]");
	if (interior < 0 || interior > 255)						 return SendErrorMessage(playerid, "Interior 0 ile 255 arasýnda olmalýdýr.");
	if (vw < 0 || vw > 65535)								 return SendErrorMessage(playerid, "VW 0 ile 65535 arasýnda olmalýdýr.");

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
	if (noooc == false) SCMALL(COLOR_GRAD2, "OOC sohbet yönetici tarafýndan aktif edildi.");
	else				SCMALL(COLOR_GRAD2, "OOC sohbet yönetici tarafýndan deaktif edildi.");
	return 1;
}
