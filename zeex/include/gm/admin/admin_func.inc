this::OfflineBlockPlayer (playerid, account [], reason [])
{
    if (cache_num_rows () == 0)
	return SendErrorMessage (playerid, "%s adlý karakter veritabanýnda bulunamadý.", account);

    new status;
	cache_get_value_int(0, "status", status);

	if (status == 3) return SendErrorMessage (playerid, "%s karakteri zaten engellenmiþ.", account);
    if (status != 1) return SendErrorMessage (playerid, "%s karakteri zaten aktif.", account);

	new query [256];
	mysql_format (dbHandle, query, sizeof (query), "UPDATE `users` SET `block_name`='%e', `block_reason`='%e', `status`='3' WHERE `name`='%e'", GetAccName(playerid), reason, account);
	mysql_tquery (dbHandle, query);

    format (query, sizeof (query), "[LOG] [OFFLINE] %s adlý karakter %s adlý yönetici tarafýndan engellendi. Sebep: %s", account, GetAccName (playerid), reason);
	SendClientMessageByAdmin (COLOUR_TOMATO, query);
	return 1;
}

this::UnBlockPlayer(playerid, account[])
{
	if (cache_num_rows() == 0) return SendErrorMessage(playerid, "%s adlý karakter veritabanýnda bulunamadý.", account);
	new status;
	cache_get_value_int(0, "status", status);
	if (status != 3) return SendErrorMessage(playerid, "%s karakteri yasaklý deðil.", account);
    
	SendAdmMessage("%s adlý kullanýcýnýn engeli %s adlý yetkili tarafýndan kaldýrýldý.", account, GetAccName(playerid));
    
	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `status`='1' WHERE `name`='%e'", account);
	mysql_tquery(dbHandle, query);
	return 1;
}

this::OfflineBanPlayer(playerid, account[], time, reason[])
{
    if (cache_num_rows() == 0) return SendErrorMessage(playerid, "%s adlý karakter veritabanýnda bulunamadý.", account);
	new banid;
	cache_get_value_int(0, "banid", banid);
	if (banid != 0) return SendErrorMessage(playerid, "%s adlý karakter yasaklý.", account);

	new admin; 
	cache_get_value_int(0, "admin", admin);
	new accountid; 
	cache_get_value_int(0, "forum_id", accountid);

	if (admin > PlayerInfo[playerid][pAdmin]) return SendAdmMessage("%s [ID: %i] adlý kiþi %s adlý kiþiyi offline olarak yasaklamaya çalýþtý. Sebep: %s.", GetAccName(playerid), account, reason);
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `bans` (accountid,name,admin,reason,date) VALUES (%i,'%e','%s','%e','%s')", accountid, account, GetAccName(playerid), reason, GetFullDate());
	mysql_tquery(dbHandle, query);

    format(query, sizeof(query), "[/offban] %s adlý karakter %s adlý yönetici tarafýndan %i gün yasaklandý. Sebep: %s", account, GetAccName(playerid), time, reason);
	insert_log(query, ADMIN_LOG, 1, accountid, PlayerInfo[playerid][pAccID]);

    format(query, sizeof(query), "[LOG] %s adlý karakter %s adlý yönetici tarafýndan %i gün yasaklandý. Sebep: %s", account, GetAccName(playerid), time, reason);
	SendClientMessageByAdmin(COLOUR_TOMATO, query);
	return 1;
}

this::UnBanPlayer(playerid, account[])
{
	if (!cache_num_rows())	return SendErrorMessage(playerid, "%s adlý karakter veritabanýnda bulunamadý.", account);
    SendAdmMessage("%s adlý karakterin yasaklamasý %s adlý yetkili tarafýndan kaldýrýldý.", account, GetAccName(playerid));
	
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `bans` WHERE `name` = '%e'", account);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "SELECT accountid FROM `bans` WHERE `name` = '%e' LIMIT 1", account);
	new Cache:cache = mysql_query(dbHandle, query),
		accountid;

    cache_get_value_int(0, "accountid", accountid);

	format(query, sizeof(query), "[/unban] %s adlý karakterin yasaklamasý %s adlý yetkili tarafýndan kaldýrýldý.", account, GetAccName(playerid));
	insert_log(query, ADMIN_LOG, 12, accountid, PlayerInfo[playerid][pAccID]);

	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return 1;
}

this::UnBanAnIP(playerid, ip[])
{
	if (!cache_num_rows())	return SendErrorMessage(playerid, "%s IP engelli deðil.", ip);

    SendAdmMessage("%s adlý yetkili tarafýndan %s IP engeli kaldýrýldý.", GetAccName(playerid), ip);

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `bans` WHERE `ip` = '%e'", ip);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "SELECT accountid FROM `bans` WHERE `ip` = '%e' LIMIT 1", ip);
	new Cache:cache = mysql_query(dbHandle, query),
		accountid;
	
    cache_get_value_int(0, "accountid", accountid);

	new mes[128];
	format(mes, sizeof(mes), "[/unbanip] IP: %s engeli %s adlý yetkili tarafýndan kaldýrýldý.", ip, GetAccName(playerid));
	insert_log(query, ADMIN_LOG, 12, accountid, PlayerInfo[playerid][pAccID]);

	cache_delete(cache);
	cache = MYSQL_INVALID_CACHE;
	return 1;
}

this::OnChangeName(playerid, userid, newname[])
{
	if (cache_num_rows())	return SendErrorMessage(playerid, "%s adlý karakter adý zaten kullanýlýyor.", newname);

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !CompareStrings(GetName(i), newname)) continue;

		SendErrorMessage(playerid, "%s adlý karakter adý zaten kullanýlýyor.", newname);
		return 1;
	}

	if (!PlayerInfo[userid][pNameChanges]) return SendErrorMessage(playerid, "Oyuncunun isim deðiþiklik hakký bulunmuyor.");

    PlayerInfo[userid][pNameChanges]--;
	SQL_SetStringAcc("accounts", "name_changes", PlayerInfo[userid][pNameChanges], PlayerInfo[userid][pAccID]);

	new oldname[MAX_PLAYER_NAME];
	GetPlayerName(userid, oldname, MAX_PLAYER_NAME);

	ChangeName(userid, newname);
	SendAdmMessage("%s adlý yetkili %s adlý karakterin isim deðiþikliðini onayladý. Yeni: %s.", GetAccName(playerid), oldname, newname);
	SendSyntaxMessage(userid, "%s adlý yetkili tarafýndan %s olan karakter adýnýz %s olarak deðiþtirildi.", GetAccName(playerid), oldname, newname);
	return 1;
}

this::OnAdminChangeNickName(playerid, userid, newname[])
{
	if (cache_num_rows())	return SendErrorMessage(playerid, "%s adlý forum adý zaten kullanýlýyor.", newname);
	    
	SendAdmMessage("%s adlý yetkili tarafýndan %s olan hesap adý deðiþtirildi. Yeni: %s.", GetAccName(playerid), GetAccName(userid), newname);
	SendSyntaxMessage(userid, "%s adlý yetkili tarafýndan %s olan hesap adýnýz %s olarak deðiþtirildi.", GetAccName(playerid), GetAccName(userid), newname);

    format(PlayerInfo[userid][pAccname], 36, newname);
	return 1;
}


this::OnAdminChangeName(playerid, userid, newname[])
{
	if (cache_num_rows())	return SendErrorMessage(playerid, "%s adlý karakter adý zaten kullanýlýyor.", newname);
	    
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || !CompareStrings(GetName(i), newname)) continue;
		SendErrorMessage(playerid, "%s adlý karakter adý zaten kullanýlýyor.", newname);
		return 1;
	}
	
	new oldname[MAX_PLAYER_NAME];
	GetPlayerName(userid, oldname, MAX_PLAYER_NAME);
	
	ChangeName(userid, newname);
	SendAdmMessage("%s adlý yetkili tarafýndan %s adlý karakterin adýný deðiþtirildi. Yeni: %s.", GetAccName(playerid), oldname, newname);
	SendSyntaxMessage(userid, "%s adlý yetkili tarafýndan %s olan karakter adýnýz %s olarak deðiþtirildi.", GetAccName(playerid), oldname, newname);
	return 1;
}

this::OnAdminTraceNumber(playerid, number)
{
	new rows = cache_num_rows(), name[MAX_PLAYER_NAME];
	if(rows)
	{
		cache_get_value(0, "name", name);
		SendServerMessage(playerid, "%d numarasý %s adlý kiþiye ait.", number, name);
	}
	else return SendErrorMessage(playerid, "Bu numaraya ait bir kiþi bulunamadý.");
	return 1;
}

ChangeName(userid, newname[])
{
    new oldname[MAX_PLAYER_NAME];
	GetPlayerName(userid, oldname, MAX_PLAYER_NAME);

	format(PlayerInfo[userid][pUsername], MAX_PLAYER_NAME+1, newname);
    format(PlayerInfo[userid][pUsername_], MAX_PLAYER_NAME+1, newname);
    strreplace(PlayerInfo[userid][pUsername_], '_', ' ');

    if (!maskOn{userid}) 
	{
	    SetPlayerName(userid, newname);
    	format(PlayerInfo[userid][pMaskname], 32, PlayerInfo[userid][pUsername_]);
	}
	
	for(new i; i != MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID] || HouseInfo[i][hOwnerID] != PlayerInfo[userid][pID]) continue;

		format(HouseInfo[i][hOwner], MAX_PLAYER_NAME, GetNameEx(userid));
	}

	for(new i; i != MAX_BIZ; i++)
	{
	    if (!BizInfo[i][bizID] || BizInfo[i][bizOwnerID] != PlayerInfo[userid][pID]) continue;

		format(BizInfo[i][bizOwner], MAX_PLAYER_NAME, GetName(userid));
	}
	
	foreach(new i:Vehicle)
	{
		if (VehicleInfo[i][carOwnerID] != PlayerInfo[userid][pID]) continue;

		format(VehicleInfo[i][carOwner], MAX_PLAYER_NAME, GetNameEx(userid));
	}
	
	SQL_SetString("users", "name", newname, PlayerInfo[userid][pID]);
	
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `tickets` WHERE `userid`=%i", PlayerInfo[userid][pID]);
	mysql_tquery(dbHandle, query);
	
	DeletePlayerTickets(userid);
	return 1;
}

this::AdminSetPlate(playerid, vehicleid, plate[])
{
	if (cache_num_rows())	return SendErrorMessage(playerid, "Belirtilen plaka baþka bir araç tarafýndan kullanýlýyor.");
	    
    format(VehicleInfo[vehicleid][carPlate], 24, "%s", plate);
	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][carPlate]);
	RespawnVehicle(vehicleid, 1);
	Save_Car(vehicleid);

	SendSyntaxMessage(playerid, "%s olan plaka deðiþtirildi. Yeni plaka: %s.", VehicleNames[GetVehicleModel(vehicleid)-400], plate);
	
	SAMALL("%s adlý kiþi tarafýndan %s model aracýn [ID %i] plakasý deðiþtirildi. Yeni: %s.", GetAccName(playerid), VehicleNames[GetVehicleModel(vehicleid)-400], vehicleid, plate);
	
	new mes[128];
	format(mes, sizeof(mes), "[/asetplate] %s adlý yetkili tarafýndan %s model aracýn plakasý deðiþtirildi. Plaka: %s.", GetAccName(playerid), VehicleNames[GetVehicleModel(vehicleid)-400], plate);
	insert_log(mes, ADMIN_LOG, 6, 0, PlayerInfo[playerid][pAccID]);
	return 1;
}

this::OnPlayerOfflineJail(playerid, name[32], time, reason[32])
{
    new rows, fields;

	rows = cache_num_rows();
	fields = cache_num_fields();

	if (rows)
	{
		new prefix[16] = "oyuncu";
		if (PlayerInfo[playerid][pAdmin] > 0) prefix = "yönetici";

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "SELECT accountid FROM `users` WHERE `name` = '%e' LIMIT 1", name);
		new Cache:cache = mysql_query(dbHandle, query),
			accountid;

		cache_get_value_int(0, "accountid", accountid);	

		new mes[128];
		format(mes, sizeof(mes), "[LOG] %s adlý karakter %s %s tarafýndan %i dakika hapise gönderildi. Sebep: %s", name, prefix, GetAccName(playerid), time, reason);
		SendClientMessageByAdmin(COLOUR_TOMATO, mes);

		format(mes, sizeof(mes), "[/offjail] %s adlý karakter %s %s tarafýndan %i dakika hapise gönderildi. Sebep: %s", name, prefix, GetAccName(playerid), time, reason);
		insert_log(mes, ADMIN_LOG, 51, accountid, PlayerInfo[playerid][pAccID]);

	    mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `ajailed`='1',`ajailtime`='%d' WHERE `name`='%e'", time, name);
	    mysql_tquery(dbHandle, query);		

		cache_delete(cache);
		cache = MYSQL_INVALID_CACHE;
	}
	else
	{
		SendErrorMessage(playerid, "%s adlý karakteri hapise gönderemediniz.", name);
	}
	return 1;
}

this::BanAnIP(playerid, ip[], reason[])
{
	if (cache_num_rows()) return SendErrorMessage(playerid, "Belirtilen IP (%s) zaten engellenmiþ.", ip);

    SendAdmMessage("%s tarafýndan IP engellendi. IP: %s.", GetAccName(playerid), ip);

	new pIP[24];
	foreach(new i : Player)
	{
		GetPlayerIp(i, pIP, sizeof(pIP));

		if (!IsPlayerLogged(i) || !CompareStrings(ip, pIP)) continue;

		SendErrorMessage(i, "IP\'niz bu sunucudan engelli. IP: %s", ip);
		KickEx(i);
	}

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `bans` (admin, reason, date, ip) VALUES ('%s', '%e', '%s', '%e')", GetAccName(playerid), reason, GetFullDate(), ip);
	mysql_tquery(dbHandle, query);
	return 1;
}

ClearKillFeed(playerid = INVALID_PLAYER_ID)
{
	if ((playerid != INVALID_PLAYER_ID) && (0 == IsPlayerConnected(playerid))) return 0;

	goto L_start;
	{
		new dummy[16/(cellbits/charbits)];
		#emit const.pri dummy
	}

	#if __Pawn < 0x030A
		SendDeathMessage(0, 0, 0),
		SendDeathMessageToPlayer(0, 0, 0, 0);
	#endif

	L_start:

	const SDM_MAGIC_ID = INVALID_PLAYER_ID-1;
	new i = 5;

	#emit    push.c    SDM_MAGIC_ID
	#emit    push.c    SDM_MAGIC_ID

	if (playerid == INVALID_PLAYER_ID)
	{
		#emit    push.c    12
		do
		{
			#emit    sysreq.c    SendDeathMessage
		}
		while(--i != 0);

		#emit    stack    12
	}
	else
	{
		#emit    push.s    playerid
		#emit    push.c    16
		do
		{	
			#emit    sysreq.c    SendDeathMessageToPlayer
		}
		while(--i != 0);

		#emit    stack    16
	}
	return 1;
}

SendClientMessageByAdmin(color, string[])
{
    foreach(new i : Player)
	{
		if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togAdmCmds)) continue;

		SendClientMessage(i, color, string);
	}
	return 1;
}


AMSG(color, const str[], {Float,_}:...)
{
    static args, start, end, string[144];
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togAdmCmds) || PlayerInfo[i][pAdmin] == 0) continue;

			SendClientMessage(i, color, string);
		}
		Log_Kaydet("adminuyari.txt", sprintf("[%s] %s", GetFullDate(), string));
		return 1;
	}

	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togAdmCmds)) continue;

		SendClientMessage(i, color, str);
	}	
	Log_Kaydet("adminuyari.txt", sprintf("[%s] %s", GetFullDate(), string));
	return 1;
}

StaffMSG(color, const str[], {Float,_}:...)
{
    static args, start, end, string[144];

	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}

		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach(new i : Player)
		{
		    if (!IsPlayerLogged(i) || (!CheckAdmin(i, ADMIN_LEVEL_1) && !IsTester(i, 1))) continue;
		    SendClientMessage(i, color, string);
			Log_Kaydet("staffmessage.txt", sprintf("%s", string));	
		}
		return 1;
	}
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || (!CheckAdmin(i, ADMIN_LEVEL_1) && !IsTester(i, 1))) continue;
	    SendClientMessage(i, color, str);
		Log_Kaydet("staffmessage.txt", sprintf("%s", string));	
	}
	return 1;
}

CheckAdmin(playerid, level)
{
	return PlayerInfo[playerid][pAdmin] >= level ? 1 : 0;
}

IsTester(playerid, level)
{
	return PlayerInfo[playerid][pHelper] >= level ? 1 : 0;
}

IsTesterLead(playerid)
{
	return PlayerInfo[playerid][pHelperLead] >= 1 ? 1 : 0;
}

IsAdminDuty(playerid)
{
	return pTemp[playerid][pAdminDuty] == 1 ? 1 : 0;
}

IsTesterDuty(playerid)
{
	return pTemp[playerid][pTesterDuty] == 1 ? 1 : 0;
}

/*
SendStaffMessage(color, string[])
{
	foreach(new i : Player)
	{
	    if (!IsPlayerLogged(i) || (!IsTester(i) && !CheckAdmin(i, ADMIN_LEVEL_1)) || (PlayerInfo[i][pSettings] & togTester)) continue;

        SCM(i, color, string);
	}
	return 1;
}*/

this::OnPlayerListSkins(playerid)
{
	new rows = cache_num_rows();

	if(rows)
	{
		new bincostr[5000];

		new skin_id;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_int(i, "model_id", skin_id);
		
			format(bincostr, sizeof(bincostr), "%s%d\n", bincostr, skin_id);
		}

		Dialog_Show(playerid, MODEL_SEL_BUYCLOTHES, DIALOG_STYLE_PREVIEW_MODEL, "Kiyafetler", bincostr, "Satin Al", "Kapat");
	}

	return 1;
}

this::OnStaffListSkins(playerid)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new bigstr[4000];

        new model_id, id, gender, race;

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_int(i, "id", id);
            cache_get_value_int(i, "gender", gender);
            cache_get_value_int(i, "model_id", model_id);	
			cache_get_value_int(i, "race", race);		
        
            format(bigstr, sizeof(bigstr), "%s%d\tID: %d~n~M: %d~n~C: %d~n~T: %d\n", bigstr, model_id, id, model_id, gender, race);
        }

        Dialog_Show(playerid, None, DIALOG_STYLE_PREVIEW_MODEL, "Kiyafetler", bigstr, "Sec", "Kapat");
    }

    else SendErrorMessage(playerid, "Listelenebilecek kýyafet verisi bulunamadý.");

    return 1;
}

this::OnStaffEditSkinGender(playerid, skin_id, gender)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý skinin cinsiyetini düzenledi. (Cinsiyet: %s)", GetNameEx(playerid), skin_id, Gender(gender));
    }

    else SendErrorMessage(playerid, "Skin için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffEditSkinRace(playerid, skin_id, race)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý skinin tenini düzenledi. (Ten: %s)", GetNameEx(playerid), skin_id, Race(race));
    }

    else SendErrorMessage(playerid, "Skin için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffEditSkinPrice(playerid, skin_id, price)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        SendAdmMessage("%s, %d numaralý skinin fiyatýný düzenledi. (Fiyat: $%d)", GetNameEx(playerid), skin_id, price);
    }

    else SendErrorMessage(playerid, "Skin için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffDeleteSkin(playerid, model_id)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new skin_id, gender, race;

        cache_get_value_int(0, "id", skin_id);
        cache_get_value_int(0, "gender", gender);	
		cache_get_value_int(0, "race", race);	

        SendAdmMessage("%s, %d numaralý skini kaldýrdý. (Model: %d | Cinsiyet: %s | Ten: %s)", GetNameEx(playerid), skin_id, model_id, Gender(gender), Race(race));
    
        mysql_tquery(dbHandle, sprintf("DELETE FROM game_skins WHERE id = '%d'", skin_id));
    }

    else SendErrorMessage(playerid, "Geçersiz skin model numarasý girdiniz.");

    return 1;
}

this::OnStaffCreateSkinEnd(playerid, model_id, gender, race, price)
{
    new skin_id = cache_insert_id();

    SendAdmMessage("%s, %d numaralý skini ekledi. (Model: %d | Cinsiyet: %s | Ten: %s | Fiyat: $%d)", GetNameEx(playerid), skin_id, model_id, Gender(gender), Race(race), price);

    return 1;
}

this::OnStaffCreateSkin(playerid, model_id, gender, race, price)
{
    new rows = cache_num_rows();

    if(!rows)
    {
        mysql_tquery(dbHandle, EditSkin(0, model_id, gender, race, price), "OnStaffCreateSkinEnd", "ddddd", playerid, model_id, gender, race, price);
    }

    else SendErrorMessage(playerid, "%d model numarasýyla %s %s skini sunucuda zaten bulunuyor.", model_id, (race == RACE_WHITE) ? ("beyaz") : ("siyahi"), (gender == GENDER_MALE) ? ("erkek") : ("kadýn"));

    return 1;
}

stock Gender(type)
{
    new gender_name[6];

    switch(type)
    {
        case GENDER_MALE: gender_name = "Erkek";
        case GENDER_FEMALE: gender_name = "Kadýn";
    }

    return gender_name;
}

stock GenderAbbv(type)
{
    new gender_name[6];

    switch(type)
    {
        case GENDER_MALE: gender_name = "E";
        case GENDER_FEMALE: gender_name = "K";
    }

    return gender_name;
}

stock Race(type)
{
    new race_name[6];

    switch(type)
    {
        case RACE_WHITE: race_name = "Beyaz";
        case RACE_BLACK: race_name = "Siyah";
    }

    return race_name;
}

stock EditSkin(id = 0, model_id = -1, gender = -1, race = -1, price = -1)
{
    new query[96 + (11 * 5) + 1];

    if(id < 1)
    {
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO game_skins SET model_id = '%d', gender = '%d', race = '%d', price = '%d'", model_id, gender, race, price);
    }

    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE game_skins SET");

        if(model_id != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, model_id = '%d'", query, model_id);
        }

        if(gender != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, gender = '%d'", query, gender);
        }

        if(race != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, race = '%d'", query, race);
        }

        if(price != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, price = '%d'", query, price);
        }

        if(strfind(query, ", ") != -1)
            strdel(query, strfind(query, ", "), strfind(query, ", ") + 1);

        mysql_format(dbHandle, query, sizeof(query), "%s WHERE id = '%d'", query, id);
    }

    return query;
}

stock SaveServer()
{
    new query[2048];

    mysql_format(dbHandle, query, sizeof(query), "UPDATE server_settings SET hostname = '%e', weburl = '%e', language = '%e', map = '%e', version = '%e', maintenance = '%d', password = '%e'",
        ServerInfo[sHostName],
        ServerInfo[sWebUrl],
        ServerInfo[sLanguage],
        ServerInfo[sMap],
        ServerInfo[sVersion],
        ServerInfo[sMaintenance],
        ServerInfo[sPassword]
    );

    mysql_format(dbHandle, query, sizeof(query), "%s, price_payday = '%d', price_park = '%d', dealership_percent = '%f'",
        query,
        ServerInfo[sPricePayday],
        ServerInfo[sPricePark],
        ServerInfo[sDealershipPercent]
    );

    mysql_format(dbHandle, query, sizeof(query), "%s, spawn_interior = '%d', spawn_world = '%d', spawn_x = '%f', spawn_y = '%f', spawn_z = '%f', spawn_a = '%f'",
        query,
        ServerInfo[sSpawnInterior],
        ServerInfo[sSpawnWorld],
        ServerInfo[sSpawnX],
        ServerInfo[sSpawnY],
        ServerInfo[sSpawnZ],
        ServerInfo[sSpawnA]
    );

    mysql_format(dbHandle, query, sizeof(query), "%s, locale_min_salary = '%d', locale_max_salary = '%d', price_taxi_license = '%d', price_taxi_ad = '%d', price_vehicle_register_percent = '%f', price_vehicle_weekly_tax_percent = '%f', price_driver_license = '%d', price_fuel = '%d', locale_sale_percent = '%f'",
        query,
        ServerInfo[lMinSalary],
        ServerInfo[lMaxSalary],
        ServerInfo[sPriceTaxiLicense],
        ServerInfo[sPriceTaxiAd],
        ServerInfo[sPriceVehRegisterPercent],
        ServerInfo[sPriceVehWeeklyTaxPercent],
        ServerInfo[sPriceDriverLicense],
        ServerInfo[sPriceFuel],
        ServerInfo[sLocaleSalePercent]
    );

    mysql_tquery(dbHandle, query);
}

stock SpectatorMessage(playerid, message[])
{
    foreach(new i : Player)
    {
        if(!StaffInfo[i][sSpec])
            continue;

        if(StaffInfo[i][sSpecType] != SPECTATE_TYPE_PLAYER)
            continue;

        if(StaffInfo[i][sSpecID] != playerid)
            continue;

        SendClientMessageEx(i, 0xFFFFFFFF, "{5681C0}[SPEC - %s (ID: %d)] {F1F1F1}%s", GetNameEx(playerid), playerid, message);
    }

    return 1;
}

stock MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);

	if(noclipdata[playerid][accelmul] <= 1) noclipdata[playerid][accelmul] += ACCEL_RATE;

	new Float:speed = MOVE_SPEED * noclipdata[playerid][accelmul];

	new Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(noclipdata[playerid][mode], CP, FV, X, Y, Z);
	MovePlayerObject(playerid, noclipdata[playerid][flyobject], X, Y, Z, speed);

	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

stock SetFlyModePos(playerid, Float:x, Float:y, Float:z)
{
    SetPlayerObjectPos(playerid, noclipdata[playerid][flyobject], x, y, z);
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}


stock GetNextCameraPosition(move_mode, const Float:CP[3], const Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
    #define OFFSET_X (FV[0]*6000.0)
	#define OFFSET_Y (FV[1]*6000.0)
	#define OFFSET_Z (FV[2]*6000.0)
	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
}

GetMoveDirectionFromKeys(ud, lr)
{
	new direction = 0;

	if(lr < 0)
	{
		if(ud < 0) 		direction = MOVE_FORWARD_LEFT; 	// Up & Left key pressed
		else if(ud > 0) direction = MOVE_BACK_LEFT; 	// Back & Left key pressed
		else            direction = MOVE_LEFT;          // Left key pressed
	}
	else if(lr > 0) 	// Right pressed
	{
		if(ud < 0)      direction = MOVE_FORWARD_RIGHT;  // Up & Right key pressed
		else if(ud > 0) direction = MOVE_BACK_RIGHT;     // Back & Right key pressed
		else			direction = MOVE_RIGHT;          // Right key pressed
	}
	else if(ud < 0) 	direction = MOVE_FORWARD; 	// Up key pressed
	else if(ud > 0) 	direction = MOVE_BACK;		// Down key pressed

	return direction;
}

Flymode_OnPlayerUpdate(playerid)
{
	if(noclipdata[playerid][cameramode] == CAMERA_MODE_FLY)
	{
		new keys,ud,lr;
		GetPlayerKeys(playerid,keys,ud,lr);
		

		if(noclipdata[playerid][mode] && (GetTickCount() - noclipdata[playerid][lastmove] > 100))
		{
		    MoveCamera(playerid);
		}

		if(noclipdata[playerid][udold] != ud || noclipdata[playerid][lrold] != lr)
		{
			if((noclipdata[playerid][udold] != 0 || noclipdata[playerid][lrold] != 0) && ud == 0 && lr == 0)
			{
				StopPlayerObject(playerid, noclipdata[playerid][flyobject]);
				noclipdata[playerid][mode]      = 0;
				noclipdata[playerid][accelmul]  = 0.0;
			}
			else
			{

				noclipdata[playerid][mode] = GetMoveDirectionFromKeys(ud, lr);

				MoveCamera(playerid);
			}
		}
		noclipdata[playerid][udold] = ud; noclipdata[playerid][lrold] = lr; // Store current keys pressed for comparison next update
	}
	return 1;
}

stock CancelFlyMode(playerid)
{
	SendServerMessage(playerid, "Spec Mode pasif.");
	new Float:x, Float:y, Float:z;
	GetPlayerCameraPos(playerid, x, y, z);

	DebugMessage(playerid, sprintf("%f, %f, %f", x, y, z));

	SetTimerEx("DelaySetPos", 1000, false, "ifff", playerid, x, y, z);

	FlyMode[playerid] = false;
	CancelEdit(playerid);
	TogglePlayerSpectating(playerid, false);

	DestroyPlayerObject(playerid, noclipdata[playerid][flyobject]);
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	SetPlayerPosEx(playerid, x, y, z);

	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	noclipdata[playerid][lrold]	= 0;
	noclipdata[playerid][udold] = 0;
	noclipdata[playerid][mode] = 0;
	noclipdata[playerid][lastmove] = 0;
	noclipdata[playerid][accelmul] = 0.0;
	SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);		
	return 1;
}

this::DelaySetPos(playerid, Float:x, Float:y, Float:z)
{
	SetPlayerPosEx(playerid, x, y, z);
	return 1;
}

stock StartFlyMode(playerid, oyuncuid = -1)
{
	SendServerMessage(playerid, "Spec Mode etkin.");
	new Float:X, Float:Y, Float:Z;
	if(oyuncuid == -1) GetPlayerPos(playerid, X, Y, Z);
	else {
		if(StaffInfo[playerid][sSpecID] != INVALID_PLAYER_ID) pc_cmd_specoff(playerid, "");
		GetPlayerPos(oyuncuid, X, Y, Z);
	}
	noclipdata[playerid][flyobject] = CreatePlayerObject(playerid, 19300, X, Y, Z, 0.0, 0.0, 0.0);

	TogglePlayerSpectating(playerid, true);
	AttachCameraToPlayerObject(playerid, noclipdata[playerid][flyobject]);

	FlyMode[playerid] = true;
	noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;
	return 1;
}

stock SpectateCheck(playerid)
{
    foreach(new i : Player)
    {
        if(IsPlayerLogged(i))
            continue;

        if(StaffInfo[i][sSpec] == false)
            continue;

        if(StaffInfo[i][sSpecType] != SPECTATE_TYPE_PLAYER)
            continue;

        if(StaffInfo[i][sSpecID] != playerid)
            continue;

        Spectate(i, SPECTATE_TYPE_PLAYER, playerid);
    }

    return 1;
}

stock Spectate(playerid, type, targetid)
{
    TogglePlayerSpectating(playerid, true);

    StaffInfo[playerid][sSpecID] = targetid;
    StaffInfo[playerid][sSpecType] = type;
    StaffInfo[playerid][sSpec] = true;

    StaffInfo[playerid][sSpecInterior] = GetPlayerInterior(playerid);
    StaffInfo[playerid][sSpecWorld] = GetPlayerVirtualWorld(playerid);

    if(type == SPECTATE_TYPE_VEHICLE)
    {
        PlayerSpectateVehicle(playerid, targetid);
        SetPlayerInterior(playerid, VehicleInfo[targetid][carInt]);
        SetPlayerVirtualWorld(playerid, VehicleInfo[targetid][carVW]);
    }

    else
    {
        new interior, world;

        interior = GetPlayerInterior(targetid);
        world = GetPlayerVirtualWorld(targetid);

        SetPlayerInterior(playerid, interior);
        SetPlayerVirtualWorld(playerid, world);

        if(IsPlayerInAnyVehicle(targetid))
        {
            new vehicleid = GetPlayerVehicleID(targetid);

            PlayerSpectateVehicle(playerid, vehicleid);
        }

        else
        {
            PlayerSpectatePlayer(playerid, targetid);
        }
    }

    if(FlyMode[playerid]) {
		FlyMode[playerid] = false;
		DestroyPlayerObject(playerid, noclipdata[playerid][flyobject]);
		noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	}

    return 1;
}

stock WeaponName(weaponid)
{
    new weapon[22];
    switch(weaponid)
    {
        case 0: weapon = "Yumruk";
        case 18: weapon = "Molotov Cocktail";
        case 44: weapon = "Night Vision Goggles";
        case 45: weapon = "Thermal Goggles";
        case 54: weapon = "Fall";
        default: GetWeaponName(weaponid, weapon, sizeof(weapon));
    }

    return weapon;
}


forward Float:GetSpeed(playerid);
stock Float:GetSpeed(playerid)
{
    static Float:velocity[3];

    if (IsPlayerInAnyVehicle(playerid))
        GetVehicleVelocity(GetPlayerVehicleID(playerid), velocity[0], velocity[1], velocity[2]);
    else
        GetPlayerVelocity(GetPlayerVehicleID(playerid), velocity[0], velocity[1], velocity[2]);

    return floatsqroot((velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2])) * 100.0;
}

this::SpectateOffTimer(playerid)
{
    SetPlayerPosEx(playerid, GetPVarFloat(playerid, "SpecX"), GetPVarFloat(playerid, "SpecY"), GetPVarFloat(playerid, "SpecZ"));
    SetPlayerFacingAngle(playerid, GetPVarFloat(playerid, "SpecA"));
    SetPlayerInterior(playerid, GetPVarInt(playerid, "SpecINT"));
    SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "SpecVW"));
    DeletePVar(playerid, "SpecX");
    DeletePVar(playerid, "SpecY");
    DeletePVar(playerid, "SpecZ");
    DeletePVar(playerid, "SpecA");
    DeletePVar(playerid, "SpecINT");
    DeletePVar(playerid, "SpecVW");
	return 1;
}
stock SpectateOff(playerid)
{
    SetPlayerPosEx(playerid, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ]);
    SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pPosA]);
    SetPlayerInterior(playerid, PlayerInfo[playerid][pInt]);
    SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pWorld]);	
	SetTimerEx("SpectateOffTimer", 1000, false, "i", playerid);
	SetTimerEx("OnPlayerSetData", 1000, false, "d", playerid);
    TogglePlayerSpectating(playerid, false);
	ResetSpectateVariables(playerid);		
    return 1;
}

stock SyncSpectatingPanel(playerid)
{
	if(StaffInfo[playerid][sSpecID] == INVALID_PLAYER_ID) return 0;
    if(StaffInfo[playerid][sSpec] == true)
    {
        new targetid;

        targetid = StaffInfo[playerid][sSpecID];

        switch(StaffInfo[playerid][sSpecType])
        {
            case SPECTATE_TYPE_PLAYER:
            {
                new Float:health, Float:armour;

                GetPlayerHealth(targetid, health);
                GetPlayerArmour(targetid, armour);

                new player_ip[16 + 1];

                GetPlayerIp(targetid, player_ip, sizeof(player_ip));

                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], sprintf("~y~%s (ID: %d) - Hesap: %d - Karakter: %d - IP: %s", GetNameEx(targetid), targetid, PlayerInfo[targetid][pAccID], PlayerInfo[targetid][pID], player_ip));
                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], sprintf("Hiz: %.2f~n~Int/World: %d/%d~n~Ping: %d P/L: %.2f~n~Can CS: %.2f~n~Zirh: CS:%.2f/SS:%.2f", GetSpeed(targetid), GetPlayerInterior(targetid), GetPlayerVirtualWorld(targetid), GetPlayerPing(targetid), NetStats_PacketLossPercent(targetid), health, armour, PlayerInfo[targetid][pArmour]));

                new vehicleid;

                vehicleid = GetPlayerVehicleID(targetid);

                if(IsValidVehicle(vehicleid))
                {
                    PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], sprintf("%s (ID: %d)~n~Benzin: %.2f~n~Sahip: %d Birlik: %d", GetVehicleModelName(GetVehicleModel(vehicleid)), vehicleid, VehicleInfo[vehicleid][carFuel], VehicleInfo[vehicleid][carOwnerID], VehicleInfo[vehicleid][carFaction]));
                }

                else PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], "Aracta Degil");

                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], sprintf("%s (%d mermi)~n~Yarali: %dsn~n~Skin: %d~n~Anim: %d", WeaponName(GetPlayerWeapon(targetid)), GetPlayerAmmo(targetid), pTemp[playerid][pInjuredTime], GetPlayerSkin(targetid), GetPlayerAnimationIndex(targetid)));
            }

            case SPECTATE_TYPE_VEHICLE:
            {
                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], "~y~Arac Izleniyor");
                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], "~r~Veri yok");
                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], "~r~Veri yok");

                PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], sprintf("%s (ID: %d)~n~Benzin: %.2f~n~Sahip: %d Birlik: %d", GetVehicleModelName(GetVehicleModel(targetid)), targetid, VehicleInfo[targetid][carFuel], VehicleInfo[targetid][carOwnerID], VehicleInfo[targetid][carFaction]));
            }
        }
    }
	return 1;
}

stock ToggleSpectatingPanel(playerid, bool:status)
{
    switch(status)
    {
        case false:
        {
            for(new i = 0; i < 6; i++)
            {
                PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][SpectatingInfo][i]);
            }
        }

        case true:
        {
            for(new i = 0; i < 6; i++)
            {
                PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][SpectatingInfo][i]);
            }
        }
    }

    return 1;
}

stock ResetSpectateVariables(playerid)
{
    StaffInfo[playerid][sSpecID] = INVALID_PLAYER_ID;
    StaffInfo[playerid][sSpecType] = INVALID_SPECTATE_TYPE;
    StaffInfo[playerid][sSpec] = false;
    StaffInfo[playerid][sSpecX] = 0.0;
    StaffInfo[playerid][sSpecY] = 0.0;
    StaffInfo[playerid][sSpecZ] = 0.0;
    StaffInfo[playerid][sSpecA] = 0.0;
    StaffInfo[playerid][sSpecInterior] = 0;
    StaffInfo[playerid][sSpecWorld] = 0;

    return 1;
}

stock GetVehicleModelName(model)
{
    static modelname[32] = "Yok";
    if(model < 400 || model > 611)
        return modelname;

    format(modelname, sizeof(modelname), VehicleNames[model - 400]);
    return modelname;
}

stock valstrEx(value)
{
	new string[8];
	format(string, sizeof string, "%d", value);
	return string;
}

PutPlayerInVeh(playerid, vehicleid, seat); public PutPlayerInVeh(playerid, vehicleid, seat)
{
	pTemp[playerid][AntiHileSistemi] = -1;
	PutPlayerInVehicle(playerid, vehicleid, seat);
	pTemp[playerid][AntiHileSistemi] = vehicleid;
	return 1;
}

this::LoadDynamicRentalPoint()
{
	new rows = cache_num_rows(), id;

	if (!rows)
	{
	    return 1;
	}

	for (new i = 0, jx = cache_num_rows(); i < jx; i ++) if (i < MAX_RENTAL)
	{
		id = i;
		Iter_Add(RentalPoints, id);
		cache_get_value_int(i, "id", RentalPoint[id][rentalID]);
		cache_get_value_int(i, "rental_type", RentalPoint[id][rentalType]);

		cache_get_value_float(i, "x", RentalPoint[id][rentalX]);
		cache_get_value_float(i, "y", RentalPoint[id][rentalY]);
		cache_get_value_float(i, "z", RentalPoint[id][rentalZ]);
		cache_get_value_int(i, "interior", RentalPoint[id][rentalInterior]);
		cache_get_value_int(i, "world", RentalPoint[id][rentalWorld]);
		cache_get_value_int(i, "job", RentalPoint[id][rentalJob]);

		new str[175];
        if (RentalPoint[id][rentalType] == 1) format(str, sizeof(str), "{EDEDED}Kiralama Noktasý{A9C4E4}[%d]\n{A9C4E4}Etkileþim: {EDEDED}/meslekarackirala", id);	
		else if (RentalPoint[id][rentalType] == 2) format(str, sizeof(str), "{EDEDED}Kiralama Noktasý{A9C4E4}[%d]\n{A9C4E4}Etkileþim: {EDEDED}/arackirala", id);	
		
		RentalPoint[id][rental3D] = CreateDynamic3DTextLabel(str, -1, RentalPoint[id][rentalX], RentalPoint[id][rentalY], RentalPoint[id][rentalZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RentalPoint[id][rentalWorld], RentalPoint[id][rentalInterior]);
		RentalPoint[id][rentalPickup] = CreateDynamicPickup(1276, 1, RentalPoint[id][rentalX], RentalPoint[id][rentalY], RentalPoint[id][rentalZ], RentalPoint[id][rentalWorld], RentalPoint[id][rentalInterior], -1, 100.0);
	}

	return 1;
}


stock InsertRental(playerid, Float:x, Float:y, Float:z, rental_type)
{
	new nextid = Iter_Free(RentalPoints), query[333];
	
	if (nextid < 0)
	{
	    SendErrorMessage(playerid, "Bir hata oluþtu.");
	}
	else
	{
		RentalPoint[nextid][rentalID] = nextid;
		RentalPoint[nextid][rentalType] = rental_type;
		RentalPoint[nextid][rentalX] = x;
		RentalPoint[nextid][rentalY] = y;
		RentalPoint[nextid][rentalZ] = z;
		RentalPoint[nextid][rentalWorld] = GetPlayerVirtualWorld(playerid);
		RentalPoint[nextid][rentalInterior] = GetPlayerInterior(playerid);
		RentalPoint[nextid][rentalJob] = 0;

		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `rental_points` (`rental_type`, `x`, `y`, `z`, `interior`, `world`, `job`) VALUES ('%i', '%.4f', '%.4f', '%.4f', '%i', '%i', '%i')", RentalPoint[nextid][rentalType], RentalPoint[nextid][rentalX], RentalPoint[nextid][rentalY],RentalPoint[nextid][rentalZ], RentalPoint[nextid][rentalInterior], RentalPoint[nextid][rentalWorld], RentalPoint[nextid][rentalJob]);
		mysql_tquery(dbHandle, query);

		if (IsValidDynamic3DTextLabel(RentalPoint[nextid][rental3D]))
		{
			DestroyDynamic3DTextLabel(RentalPoint[nextid][rental3D]);
			RentalPoint[nextid][rental3D] = Text3D:INVALID_3DTEXT_ID;
		}

		if(IsValidDynamicPickup(RentalPoint[nextid][rentalPickup]))
			DestroyDynamicPickup(RentalPoint[nextid][rentalPickup]);

		new str[175];
        if (rental_type == 1) format(str, sizeof(str), "{EDEDED}Kiralama Noktasý{A9C4E4}[%d]\n{A9C4E4}Etkileþim: {EDEDED}/meslekarackirala", nextid);	
		else if (rental_type == 2) format(str, sizeof(str), "{EDEDED}Kiralama Noktasý{A9C4E4}[%d]\n{A9C4E4}Etkileþim: {EDEDED}/arackirala", nextid);	

		RentalPoint[nextid][rentalPickup] = CreateDynamicPickup(1276, 1, RentalPoint[nextid][rentalX], RentalPoint[nextid][rentalY], RentalPoint[nextid][rentalZ], RentalPoint[nextid][rentalWorld], RentalPoint[nextid][rentalInterior], -1, 100.0);
		RentalPoint[nextid][rental3D] = CreateDynamic3DTextLabel(str, -1, RentalPoint[nextid][rentalX], RentalPoint[nextid][rentalY], RentalPoint[nextid][rentalZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RentalPoint[nextid][rentalWorld], RentalPoint[nextid][rentalInterior]);
		Iter_Add(RentalPoints, nextid);
	}
	return nextid;
}

stock Rental_Nearest(playerid)
{
	new id = -1;

	for(new i; i < MAX_RENTAL; i++)
	{
		if (RentalPoint[i][rentalID] > -1 && IsPlayerInRangeOfPoint(playerid, 6.0, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ]))
		{
		    if (id != -1) { 
				new Float: x, Float: y, Float: z;

				GetPlayerPos(playerid, x, y, z);
				if (GetDistanceBetweenPoints(x, y, z, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ]) <
					GetDistanceBetweenPoints(x, y, z, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ])) id = i;
			}
			else id = i;
		}
	}
	return id;
}

stock Locker_RentalNearestType(playerid, type)
{
	new id = -1;

	for(new i; i < MAX_RENTAL; i++)
	{
		if (RentalPoint[i][rentalID] > -1 && IsPlayerInRangeOfPoint(playerid, 5.0, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ]) && RentalPoint[i][rentalType] == type)
		{
		    if (id != -1) { 
				new Float: x, Float: y, Float: z;

				GetPlayerPos(playerid, x, y, z);
				if (GetDistanceBetweenPoints(x, y, z, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ]) <
					GetDistanceBetweenPoints(x, y, z, RentalPoint[i][rentalX], RentalPoint[i][rentalY], RentalPoint[i][rentalZ])) id = i;
			}
			else id = i;
		}
	}
	return id;
}

getRandomPlayer()
{
	new count = 0, randomid = INVALID_PLAYER_ID;

	while(randomid == INVALID_PLAYER_ID || !IsPlayerConnected(randomid))
	{
		count++;
		randomid = random(MAX_PLAYERS);
		if(count > 200 || IsPlayerConnected(randomid)) break;
	}
	return randomid;
}

CekilisMesafe(playerid, Float: menzil)
{
	new count = 0, randomid = INVALID_PLAYER_ID;
	new Float: x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new vw = GetPlayerVirtualWorld(playerid);

	while(randomid == INVALID_PLAYER_ID || GetPlayerVirtualWorld(randomid) != vw || !IsPlayerInRangeOfPoint(randomid, menzil, x, y, z) || !IsPlayerConnected(randomid) || !pTemp[randomid][pLogged])
	{
		count++;
		randomid = random(MAX_PLAYERS);
		if(count > 200 || IsPlayerConnected(randomid)) break;
	}
	return randomid;
}

stock GetPlayerNearestArrestPoint(playerid, Float:distance = 5.0)
{
    new arrestpoint_id;

    new interior, world, Float:x, Float:y, Float:z;

    interior = GetPlayerInterior(playerid);
    world = GetPlayerVirtualWorld(playerid);

    GetPlayerPos(playerid, x, y, z);

    new wheres[168 + (6 * 6) + 1];

    mysql_format(dbHandle, wheres, sizeof(wheres), "arrest_points.interior = '%d' AND arrest_points.world = '%d' AND POW(arrest_points.x - %f, 2) + POW(arrest_points.y - %f, 2) + POW(arrest_points.z - %f, 2) < POW(%f, 2)", interior, world, x, y, z, distance);
    
    new Cache:search = mysql_query(dbHandle, GetArrestPoint("arrest_points.id", "", wheres));

    if(cache_num_rows())
    {
        cache_get_value_index_int(0, 0, arrestpoint_id);
    }

    cache_delete(search);
    search = MYSQL_INVALID_CACHE;

    return arrestpoint_id;
}

stock GetPlayerNearestLocker(playerid, Float:distance = 5.0)
{
    new locker_id;

    new interior, world, Float:x, Float:y, Float:z;

    interior = GetPlayerInterior(playerid);
    world = GetPlayerVirtualWorld(playerid);

    GetPlayerPos(playerid, x, y, z);

    new wheres[216 + (7 * 6) + 1];

    mysql_format(dbHandle, wheres, sizeof(wheres), "faction_lockers.faction_id = '%d' AND faction_lockers.interior = '%d' AND faction_lockers.world = '%d' AND POW(faction_lockers.x - %f, 2) + POW(faction_lockers.y - %f, 2) + POW(faction_lockers.z - %f, 2) < POW(%f, 2)", PlayerInfo[playerid][pFaction], interior, world, x, y, z, distance);
    
    new Cache:search = mysql_query(dbHandle, GetLocker("faction_lockers.id", "", wheres));

    if(cache_num_rows())
    {
        cache_get_value_index_int(0, 0, locker_id);
    }

    cache_delete(search);
    search = MYSQL_INVALID_CACHE;

    return locker_id;
}

stock RefreshLocker(id, bool:forcedestroy = true)
{
    mysql_tquery(dbHandle, GetLocker("factions.name, faction_lockers.label_id, faction_lockers.interior, faction_lockers.world, faction_lockers.x, faction_lockers.y, faction_lockers.z", "LEFT JOIN factions ON factions.factionid = faction_lockers.faction_id", "", 1, -1, id), "OnLockerRefreshed", "dd", id, forcedestroy);

    return 1;
}

stock EditLocker(id, faction_id = -1, Text3D:label_id = Text3D:-1, interior = -1, world = -1, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
    new query[138 + (11 * 7) + 1];

    if(id < 1)
    {
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO faction_lockers SET faction_id = '%d', label_id = '%d', interior = '%d', world = '%d', x = '%f', y = '%f', z = '%f'", faction_id, _:label_id, interior, world, x, y, z);
    }

    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE faction_lockers SET");

        if(faction_id != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, faction_id = '%d'", query, faction_id); 
        }

        if(Text3D:label_id != Text3D:-1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, label_id = '%d'", query, _:label_id);
        }

        if(interior != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, interior = '%d'", query, interior);
        }

        if(world != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, world = '%d'", query, world);
        }

        if(x != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, x = '%f'", query, x);
        }

        if(y != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, y = '%f'", query, y);
        }

        if(z != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, z = '%f'", query, z);
        }

        if(strfind(query, ", ") != -1)
            strdel(query, strfind(query, ", "), strfind(query, ", ") + 1);

        mysql_format(dbHandle, query, sizeof(query), "%s WHERE id = '%d'", query, id);
    }

    return query;
}

stock GetLocker(const fields[] = "faction_lockers.*", const joins[] = "", const wheres[] = "", page = 1, limit = -1, sqlid = -1, faction_id = -1)
{
    new query[512];

    format(query, sizeof(query), "SELECT %s FROM faction_lockers", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(sqlid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND faction_lockers.id = '%d'", query, sqlid);
    }

    if(faction_id != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND faction_lockers.faction_id = '%d'", query, faction_id);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY faction_lockers.id DESC", query);

    if(limit == -1)
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 10000", query, ((page - 1) * ITEM_PER_PAGE));
    else
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 1", query, ((page - 1) * ITEM_PER_PAGE) + limit);

    return query;
}

this::OnStaffListLockers(playerid)
{
	new rows = cache_num_rows();

	if(rows)
	{
		new id, name[MAX_FACTION_LENGHT], faction_id;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_index_int(i, 0, id);
			cache_get_value_index(i, 1, name);
			cache_get_value_index_int(i, 2, faction_id);

			SendServerMessage(playerid, "#%d - %s (ID: %d)", id, name, faction_id);
		}

		SendServerMessage(playerid, "%d dolap verisi bulundu.", rows);
	}

	else SendErrorMessage(playerid, "Listelenebilecek dolap verisi bulunamadý.");

	return 1;
}

this::OnStaffEditLockerPos(playerid, locker_id)
{
	new rows = cache_affected_rows();

	if(rows)
	{
		SendAdmMessage("%s, %d numaralý dolabýn pozisyonunu deðiþtirdi.", GetNameEx(playerid), locker_id);
	}

	else SendErrorMessage(playerid, "Dolap için deðiþiklik gerçekleþtirilmedi.");

	return 1;
}

this::OnStaffEditLockerFaction(playerid, locker_id, faction_id)
{
	new rows = cache_affected_rows();

	if(rows)
	{
		SendAdmMessage("%s, %d numaralý dolabýn birliðini deðiþtirdi. (yeni: %d)", GetNameEx(playerid), locker_id, faction_id);
	}

	else SendErrorMessage(playerid, "Dolap için deðiþiklik gerçekleþtirilmedi.");

	return 1;
}

this::OnStaffDeleteLocker(playerid, locker_id)
{
	new rows = cache_num_rows();

	if(rows)
	{
		new name[MAX_FACTION_LENGHT], faction_id, Text3D:label_id;

		cache_get_value_index(0, 0, name);
		cache_get_value_index_int(0, 1, faction_id);
		cache_get_value_index_int(0, 2, _:label_id);
	
		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		{
			DestroyDynamic3DTextLabel(Text3D:label_id);
		}

		SendAdmMessage("%s, %s (ID: %d) birliðinin %d numaralý dolabýný sildi.", GetNameEx(playerid), name, faction_id, locker_id);
	
		mysql_tquery(dbHandle, sprintf("DELETE FROM faction_lockers WHERE id = '%d'", locker_id));
	}

	else SendErrorMessage(playerid, "Geçersiz dolap numarasý girdiniz.");

	return 1;
}

this::OnStaffCreateLocker(playerid, faction_id)
{
	new rows = cache_num_rows();

	if(rows)
	{
		new name[MAX_FACTION_LENGHT];

		cache_get_value_index(0, 0, name);

		new interior, world, Float:x, Float:y, Float:z;

		interior = GetPlayerInterior(playerid);
		world = GetPlayerVirtualWorld(playerid);

		GetPlayerPos(playerid, x, y, z);

		mysql_tquery(dbHandle, EditLocker(0, faction_id, Text3D:-1, interior, world, x, y, z), "OnStaffCreateLockerEnd", "dds", playerid, faction_id, name);
	}

	else SendErrorMessage(playerid, "Geçersiz birlik numarasý girdiniz.");

	return 1;
}

this::OnStaffCreateLockerEnd(playerid, faction_id, name[])
{
	new id = cache_insert_id();

	SendAdmMessage("%s, %s (ID: %d) birlik için ekipman dolabý ekledi. (dolap id: %d)", GetNameEx(playerid), name, faction_id, id);

	RefreshLocker(id, false);

	return 1;
}

this::OnLockerRefreshed(id, bool:forcedestroy)
{
	new rows = cache_num_rows();

	if(rows)
	{
		new name[MAX_FACTION_LENGHT], Text3D:label_id, interior, world, Float:x, Float:y, Float:z;

		cache_get_value_index(0, 0, name);
		cache_get_value_index_int(0, 1, _:label_id);
		cache_get_value_index_int(0, 2, interior);
		cache_get_value_index_int(0, 3, world);
		cache_get_value_index_float(0, 4, x);
		cache_get_value_index_float(0, 5, y);
		cache_get_value_index_float(0, 6, z);
	
		if(forcedestroy == true)
		{
			if(IsValidDynamic3DTextLabel(Text3D:label_id))
			{
				DestroyDynamic3DTextLabel(Text3D:label_id);
			}
		}

		label_id = CreateDynamic3DTextLabel(sprintf(EMBED_ALTO "[" EMBED_SERVER2 "%s" EMBED_ALTO " #%d]\n/ekipman", name, id), -1, x, y, z, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);

		mysql_tquery(dbHandle, EditLocker(id, -1, label_id));
	}

	return 1;
}

this::LoadLockers()
{
	new rows = cache_num_rows();

	if(rows)
	{
		new locker_id;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_index_int(i, 0, locker_id);

			RefreshLocker(locker_id, false);
		}

		printf("[!] Sunucudan %d dolap verisi alindi.", rows);
	}

	else printf("[!] Sunucudan dolap verisi alinamadi.");

	return 1;
}

/// arrest

this::LoadArrestPoints()
{
	new rows = cache_num_rows();

	if(rows)
	{
		new id;

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_index_int(i, 0, id);

			RefreshArrestPoint(id, false);
		}

		printf("[!] Sunucudan %d hapis noktasi verisi alindi.", rows);
	}

	printf("[!] Sunucudan hapis noktasi verisi alinamadi.");

	return 1;
}

this::OnStaffEditArrestPointPos(playerid, id)
{
    new rows = cache_affected_rows();

    if(rows)
    {
        RefreshArrestPoint(id);

        SendAdmMessage("%s, %d numaralý hapis noktasýnýn pozisyonunu deðiþtirdi.", GetNameEx(playerid), id);
    }

    else SendErrorMessage(playerid, "Hapis noktasý için deðiþiklik gerçekleþtirilmedi.");

    return 1;
}

this::OnStaffDeleteArrestPoint(playerid, id)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new pickup_id, Text3D:label_id;

        cache_get_value_index_int(0, 0, pickup_id);
        cache_get_value_index_int(0, 1, _:label_id);
    
        if(IsValidDynamicPickup(pickup_id))
            DestroyDynamicPickup(pickup_id);

		

        if(IsValidDynamic3DTextLabel(Text3D:label_id))
            DestroyDynamic3DTextLabel(Text3D:label_id);

        mysql_tquery(dbHandle, sprintf("DELETE FROM arrest_points WHERE id = '%d'", id));
        
        SendAdmMessage("%s, %d numaralý hapis noktasýný sildi.", GetNameEx(playerid), id);
    }

    else SendErrorMessage(playerid, "Geçersiz hapis noktasý numarasý girdiniz.");

    return 1;
}

this::OnStaffCreateArrestPoint(playerid)
{
    new id = cache_insert_id();

	

    RefreshArrestPoint(id, false);

    SendAdmMessage("%s, yeni hapis noktasý ekledi. (id: %d)", GetNameEx(playerid), id);

    return 1;
}

this::OnArrestPointRefreshed(id, bool:forcedestroy)
{
    new rows = cache_num_rows();

    if(rows)
    {
        new pickup_id, Text3D:label_id, interior, world, Float:x, Float:y, Float:z;

        cache_get_value_index_int(0, 0, pickup_id);
        cache_get_value_index_int(0, 1, _:label_id);
        cache_get_value_index_int(0, 2, interior);
        cache_get_value_index_int(0, 3, world);
        cache_get_value_index_float(0, 4, x);
        cache_get_value_index_float(0, 5, y);
        cache_get_value_index_float(0, 6, z);
    
        if(forcedestroy)
        {
            if(IsValidDynamic3DTextLabel(Text3D:label_id))
                DestroyDynamic3DTextLabel(Text3D:label_id);

            if(IsValidDynamicPickup(pickup_id))
                DestroyDynamicPickup(pickup_id);
        }

        label_id = CreateDynamic3DTextLabel(sprintf(EMBED_ALTO "[" EMBED_SERVER2 "Hapis Ýþlemleri Noktasý " EMBED_ALTO "(#%d)]\n/hapis", id), -1, x, y, z, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
        pickup_id = CreateDynamicPickup(1247, 23, x, y, z, world, interior);

        mysql_tquery(dbHandle, EditArrestPoint(id, pickup_id, label_id));
    }

    return 1;
}

stock RefreshArrestPoint(id, bool:forcedestroy = true)
{
    return mysql_tquery(dbHandle, GetArrestPoint("arrest_points.pickup_id, arrest_points.label_id, arrest_points.interior, arrest_points.world, arrest_points.x, arrest_points.y, arrest_points.z", "", "", 1, -1, id), "OnArrestPointRefreshed", "dd", id, forcedestroy);
}

stock EditArrestPoint(id = 0, pickup_id = -1, Text3D:label_id = Text3D:-1, interior = -1, world = -1, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
    new query[100 + (11 * 5) + 1];

    if(id < 1)
    {
        mysql_format(dbHandle, query, sizeof(query), "INSERT INTO arrest_points SET interior = '%d', world = '%d', x = '%f', y = '%f', z = '%f'", interior, world, x, y, z);
    }

    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE arrest_points SET");

        if(pickup_id != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, pickup_id = '%d'", query, pickup_id);
        }

        if(Text3D:label_id != Text3D:-1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, label_id = '%d'", query, _:label_id);
        }

        if(interior != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, interior = '%d'", query, interior);
        }

        if(world != -1)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, world = '%d'", query, world);
        }

        if(x != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, x = '%f'", query, x);
        }

        if(y != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, y = '%f'", query, y);
        }

        if(z != 0.0)
        {
            mysql_format(dbHandle, query, sizeof(query), "%s, z = '%f'", query, z);
        }

        if(strfind(query, ", ") != -1)
            strdel(query, strfind(query, ", "), strfind(query, ", ") + 1);

        mysql_format(dbHandle, query, sizeof(query), "%s WHERE id = '%d'", query, id);
    }

    return query;
}

stock GetArrestPoint(const fields[] = "arrest_points.*", const joins[] = "", const wheres[] = "", page = 1, limit = -1, sqlid = -1)
{
    new query[600];

    format(query, sizeof(query), "SELECT %s FROM arrest_points", fields);

    if(!isnull(joins))
    {
        format(query, sizeof(query), "%s %s", query, joins);
    }

    format(query, sizeof(query), "%s WHERE 1", query);

    if(sqlid != -1)
    {
        mysql_format(dbHandle, query, sizeof(query), "%s AND arrest_points.id = '%d'", query, sqlid);
    }

    if(!isnull(wheres))
    {
        format(query, sizeof(query), "%s AND %s", query, wheres);
    }

    mysql_format(dbHandle, query, sizeof(query), "%s ORDER BY arrest_points.id DESC", query);

    if(limit == -1)
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 10000", query, ((page - 1) * ITEM_PER_PAGE));
    else
        mysql_format(dbHandle, query, sizeof(query), "%s LIMIT %d, 1", query, ((page - 1) * ITEM_PER_PAGE) + limit);

    return query;
}

Dialog:CreateArrestConfirmation(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new interior, world, Float:x, Float:y, Float:z;

        interior = GetPlayerInterior(playerid);
        world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, x, y, z);

        mysql_tquery(dbHandle, EditArrestPoint(0, -1, Text3D:-1, interior, world, x, y, z), "OnStaffCreateArrestPoint", "d", playerid);
    }

    return 1;
}
