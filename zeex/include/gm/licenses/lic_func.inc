forward ShowWeaponLicenseDialog(playerid, list);
forward ShowWeaponLicensePlayer(playerid);

LicenseOffice_Nearest(playerid)
{
	if (!IsPlayerLogged(playerid))	return -1;

	for(new i = 0; i < MAX_BIZ; i++)
	{		
	    if (BizInfo[i][bizID] == 0 || BizInfo[i][bizType] != BIZ_LICENSE)	continue;
	    if (PlayerToPoint(85.0,playerid,BizInfo[i][bizPosX], BizInfo[i][bizPosY], BizInfo[i][bizPosZ]) && GetWorld(playerid) == BizInfo[i][bizPosVW] && GetInterior(playerid) == BizInfo[i][bizPosInt])
		return i;
	}
	return -1;
}

ShowLicenses(playerid, targetid) //�� �����
{
	new gender = PlayerInfo[playerid][pSex];
	SCM(targetid, COLOR_SERVER2, "___________VATANDA�LIK___________");
	SendClientMessageEx(targetid, COLOR_WHITE, "�sim: {AFAFAF}%s{FFFFFF}, Ya�: {AFAFAF}%i", GetNameEx(playerid), PlayerInfo[playerid][pAge]);
	SendClientMessageEx(targetid, COLOR_WHITE, "K�ken: {AFAFAF}%s{FFFFFF}, Cinsiyet: {AFAFAF}%s", GetOriginName(PlayerInfo[playerid][pOrigin]), (gender == GENDER_MALE) ? ("Erkek") : ("Kad�n"));
	SCM(targetid, COLOR_SERVER2, "_________________________________");

    SCM(targetid, COLOR_SERVER2, "");

    SCM(targetid, COLOR_SERVER2, "____________L�SANSLAR____________");	
	SendClientMessageEx(targetid, COLOR_WHITE, "Ara� Ehliyeti: {AFAFAF}%s{FFFFFF}. {FF8C8C}Uyar�lar: (%i)", (PlayerInfo[playerid][pCarLic])?("Sahip"):("Sahip De�il"), PlayerInfo[playerid][pDriveWarns]);
	SendClientMessageEx(targetid, COLOR_WHITE, "Silah Ruhsat�: {AFAFAF}%s{FFFFFF}. {FF8C8C}Uyar�lar: (%i)", (PlayerInfo[playerid][pWepLic])?("Sahip"):("Sahip De�il"), PlayerInfo[playerid][pWepWarns]);
	SendClientMessageEx(targetid, COLOR_WHITE, "Hava Arac� Lisans�: {AFAFAF}%s{FFFFFF}.", (PlayerInfo[playerid][pFlyLic])?((PlayerInfo[playerid][pFlyLic] == 1)?("Sahip"):("Yasakl�")):("Sahip De�il"));
	SendClientMessageEx(targetid, COLOR_WHITE, "Taksi lisans�: {AFAFAF}%s{FFFFFF}.", (PlayerInfo[playerid][pTaxiLic])?((PlayerInfo[playerid][pTaxiLic] == 1)?("Sahip"):("Yasakl�")):("Sahip De�il"));
	SCM(targetid, COLOR_SERVER2, "_________________________________");
	return 1;
}

ShowLawyerLicenses(playerid, targetid)
{
	SCM(targetid, 0x8D8DFFFF, "__________AVUKAT L�SANSI__________");

	SendClientMessageEx(targetid, COLOR_GRAD2, "�sim: %s", GetNameEx(playerid));
	SendClientMessageEx(targetid, COLOR_GRAD2, "Bu kartvizit Liberty City H�k�meti taraf�ndan sa�lanm��t�r.");

	SCM(targetid, 0x8D8DFFFF, "__________STATE OF AMERICA__________");
	return 1;
}

ShowWeaponLicense(playerid, list)
{
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `id`,`name` FROM `users` WHERE `weplic`='1' LIMIT %i,%i", (30 * list), (30 * (list + 1)));
	mysql_tquery(dbHandle, query, "ShowWeaponLicenseDialog", "ii", playerid, list);
	return 1;
}

public ShowWeaponLicenseDialog(playerid, list)
{
	if (!cache_num_rows())
	{
  		SendErrorMessage(playerid, "Herhangi bir bilgi bulunamad�.");
  	 	return pc_cmd_mdc(playerid, "");
	}

	new mes[(MAX_PLAYER_NAME + 1) * 30 + 7] = "<<\n>>", name[MAX_PLAYER_NAME + 1];
	
	for(new i; i != cache_num_rows(); i++)
	{
	    cache_get_value_int(i, "id", pTemp[playerid][pWeaponListed][i]);
	    cache_get_value(i, "name", name);
	    strreplace(name, '_', ' ');
		format(mes, sizeof(mes), "%s\n%s", mes, name);
	}

	SetPVarInt(playerid, #weapon_list, list);
	Dialog_Show(playerid, MDCWeapon, DIALOG_STYLE_LIST, "Lisans Ge�mi�i", mes, "Se�", "Geri D�n");
	return 1;
}

public ShowWeaponLicensePlayer(playerid)
{
	if (!cache_num_rows())
	{
	    SendErrorMessage(playerid, "Herhangi bir bilgi bulunamad�.");
	    return pc_cmd_mdc(playerid, "");
	}
	
	new name[MAX_PLAYER_NAME+1], officer[MAX_PLAYER_NAME+1], data[24], price, warns;
	
	cache_get_value(0, "name", name);	
	strreplace(name, '_', ' ');
   	cache_get_value(0, "wep_officer", officer);
    cache_get_value(0, "wep_data", data);
    cache_get_value_int(0, "wep_price", price);
    cache_get_value_int(0, "wepwarns", warns);

	static const str_size[] = "{C3C3C3}- Ad, Soyad: %s\n{C3C3C3}- Uyar�lar: %i\n{C3C3C3}- memur: %s\n{C3C3C3}- Verili� Tarihi: %s\n{C3C3C3}- Fiyat: $%i\n- Lisans� �ptal Et\n- Bir uyar� yaz";
	new mes[sizeof(str_size) - 10 + MAX_PLAYER_NAME + MAX_PLAYER_NAME + 24 + 12];
	format(mes, sizeof(mes), str_size, name, warns, officer, data, price);
	Dialog_Show(playerid, MDCWeaponPlayer, DIALOG_STYLE_LIST, "Bilgi", mes, "Se�", "Geri D�n");
	
	cache_get_value_int(0, "id", pTemp[playerid][pMDCWepPlayer]);
	format(pTemp[playerid][pMDCWepName], MAX_PLAYER_NAME+1, name);

	return 1;
}