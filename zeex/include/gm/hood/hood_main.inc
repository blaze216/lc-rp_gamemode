#define MAX_ONAYLIHOOD (100)

enum hoodData {
	hoodID,
	hoodAd[32],
	hoodVarmi,
	Float:hoodPos[4],
	hoodPickup,
	hZone,
	bool:hExists,
	Text3D:hoodText3D
};

new OnayliHoodlar[MAX_ONAYLIHOOD][hoodData]; 

stock Hood_Sil(hoodid)
{
	if (hoodid != -1 && OnayliHoodlar[hoodid][hoodVarmi])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `onaylihoodlar` WHERE `hoodID` = '%d'", OnayliHoodlar[hoodid][hoodID]);
		mysql_tquery(dbHandle, string);

        if (IsValidDynamicArea(OnayliHoodlar[hoodid][hZone])) DestroyDynamicArea(OnayliHoodlar[hoodid][hZone]);

        if (IsValidDynamic3DTextLabel(OnayliHoodlar[hoodid][hoodText3D]))
		    DestroyDynamic3DTextLabel(OnayliHoodlar[hoodid][hoodText3D]);

		if (IsValidDynamicPickup(OnayliHoodlar[hoodid][hoodPickup]))
		    DestroyDynamicPickup(OnayliHoodlar[hoodid][hoodPickup]);

	    OnayliHoodlar[hoodid][hoodVarmi] = false;
	    OnayliHoodlar[hoodid][hoodID] = 0;
	}
	return 1;
}

this::Hood_Yukle()
{
    new rows = cache_num_rows();

    if(!rows) printf("Hood bulunamadi");

	for (new i = 0; i < rows; i ++) if (i < MAX_ONAYLIHOOD)
	{
	    OnayliHoodlar[i][hoodVarmi] = true;
    	cache_get_value_int(i, "hoodID", OnayliHoodlar[i][hoodID]);
    	cache_get_value_int(i, "hoodPickup", OnayliHoodlar[i][hoodPickup]);
		cache_get_value(i, "hoodAd", OnayliHoodlar[i][hoodAd], 32);
	    cache_get_value_float(i, "hoodPosX", OnayliHoodlar[i][hoodPos][0]);
	    cache_get_value_float(i, "hoodPosY", OnayliHoodlar[i][hoodPos][1]);
	    cache_get_value_float(i, "hoodPosZ", OnayliHoodlar[i][hoodPos][2]);
	    cache_get_value_float(i, "hoodPosA", OnayliHoodlar[i][hoodPos][3]);

	    Hood_Yenile(i);
	}
	return 1;
}

Hood_Kaydet(hoodid)
{
	static
	    query[1024];

	format(query, sizeof(query), "UPDATE `onaylihoodlar` SET `hoodAd` = '%s', `hoodPickup` = '%d', `hoodPosX` = '%.4f', `hoodPosY` = '%.4f', `hoodPosZ` = '%.4f', `hoodPosA` = '%.4f'",
	    SQL_ReturnEscaped(OnayliHoodlar[hoodid][hoodAd]),
		OnayliHoodlar[hoodid][hoodPickup],
	    OnayliHoodlar[hoodid][hoodPos][0],
	    OnayliHoodlar[hoodid][hoodPos][1],
	    OnayliHoodlar[hoodid][hoodPos][2],
	    OnayliHoodlar[hoodid][hoodPos][3]
	);
	format(query, sizeof(query), "%s WHERE `hoodID` = '%d'",
	    query,
	    OnayliHoodlar[hoodid][hoodID]
	);
	return mysql_tquery(dbHandle, query);
}

this:OnHoodCreated(hoodid)
{
	if (hoodid == -1 || !OnayliHoodlar[hoodid][hoodVarmi])
	    return 0;

	OnayliHoodlar[hoodid][hoodID] = cache_insert_id(dbHandle);
	Hood_Kaydet(hoodid);
	return 1;
}

Hood_Yenile(hoodid)
{
	if (hoodid != -1 && OnayliHoodlar[hoodid][hoodVarmi])
	{
		if (IsValidDynamic3DTextLabel(OnayliHoodlar[hoodid][hoodText3D]))
		    DestroyDynamic3DTextLabel(OnayliHoodlar[hoodid][hoodText3D]);

		if (IsValidDynamicPickup(OnayliHoodlar[hoodid][hoodPickup]))
		    DestroyDynamicPickup(OnayliHoodlar[hoodid][hoodPickup]);

        if (IsValidDynamicArea(OnayliHoodlar[hoodid][hZone])) DestroyDynamicArea(OnayliHoodlar[hoodid][hZone]);

        OnayliHoodlar[hoodid][hZone] = CreateDynamicRectangle(OnayliHoodlar[hoodid][hoodPos][0]-45, OnayliHoodlar[hoodid][hoodPos][1]-45, OnayliHoodlar[hoodid][hoodPos][0]+45, OnayliHoodlar[hoodid][hoodPos][1]+45, 0, 0);

		new string[1024];
		format(string,sizeof(string),"\
				[Onaylý Hood %d] \n\
				Birlik: %s \n\
		",hoodid, OnayliHoodlar[hoodid][hoodAd], OnayliHoodlar[hoodid][hoodAd]);

        OnayliHoodlar[hoodid][hoodPickup] = CreateDynamicPickup(1313, 23, OnayliHoodlar[hoodid][hoodPos][0], OnayliHoodlar[hoodid][hoodPos][1], OnayliHoodlar[hoodid][hoodPos][2], 0, 0);
		OnayliHoodlar[hoodid][hoodText3D] = CreateDynamic3DTextLabel(string, COLOR_SERVER2, OnayliHoodlar[hoodid][hoodPos][0], OnayliHoodlar[hoodid][hoodPos][1]+0.5, OnayliHoodlar[hoodid][hoodPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

  	}
	return 1;
}

Hood_Olustur(playerid, ad[])
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

    if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_ONAYLIHOOD; i ++)
		{
	    	if (!OnayliHoodlar[i][hoodVarmi])
		    {
            	x += 1.0 * floatsin(-angle, degrees);
				y += 1.0 * floatcos(-angle, degrees);

    	        OnayliHoodlar[i][hoodVarmi] = true;
    	        OnayliHoodlar[i][hoodPos][0] = x;
    	        OnayliHoodlar[i][hoodPos][1] = y;
    	        OnayliHoodlar[i][hoodPos][2] = z;
    	        OnayliHoodlar[i][hoodPos][3] = angle;
				format(OnayliHoodlar[i][hoodAd], 32, ad);
				Hood_Yenile(i);
				mysql_tquery(dbHandle, "INSERT INTO `onaylihoodlar` (`hoodPickup`) VALUES('0')", "OnHoodCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

CMD:hoodsil(playerid, params[])
{
	static
	    id = 0;

    if (PlayerInfo[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "Yetkin yok!");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/hoodsil [hood id]");

	if ((id < 0 || id >= MAX_ONAYLIHOOD) || !OnayliHoodlar[id][hoodVarmi])
	    return SendErrorMessage(playerid, "Geçersiz onaylý hood ID.");

	Hood_Sil(id);
	SendServerMessage(playerid, "%d nolu onaylý hood baþarýyla silindi.", id);
	return 1;
}

CMD:hoodolustur(playerid, params[])
{
    if (PlayerInfo[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "Yetkin yok!");

	if (isnull(params) || strlen(params) > 32)
	    return SendSyntaxMessage(playerid, "/hoodolustur [birlik ad]");

	new id = Hood_Olustur(playerid, params);

	if (id == -1)
	    return SendErrorMessage(playerid, "Sunucu onaylý hood sýnýrýna ulaþmýþtýr.");
	return 1;
}