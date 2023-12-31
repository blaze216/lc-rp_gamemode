CMD:pizza(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");

	if (!pTemp[playerid][pPizzaBoy])								return SendErrorMessage(playerid, "�u an teslimat s�recinde de�ilsiniz. (/kurye)");
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))		return SendWarningMessage(playerid, "Elleriniz dolu.");
        
	new vehicle = GetPlayerVehicleID(playerid);

	if (vehicle != 0)																		return SendErrorMessage(playerid, "Herhangi bir ara�ta de�ilsin.");
    if ((vehicle = GetNearVehicle(playerid, 3.0)) == 0 || GetVehicleModel(vehicle) != 448)	return SendErrorMessage(playerid, "Kurye motorunun yan�nda olmal�s�n�z.");
    
    SetPlayerAttachedObject(playerid, ATTACH_HANDS, 19571, 6, -0.157999, -0.002000, -0.169000, -21.999990, 87.000022, 0.000000, 1.186000, 1.000000, 1.170000);
  	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
  	InfoMSG(playerid, "Pizzayi birakmak icin \" ~r~ENTER ~w~\" tusuna basin.", 5);
	return 1;
}

CMD:kurye(playerid, params[])
{
	if(!MeslekSistemleri) return SendErrorMessage(playerid, "Meslek sistemleri pasife �ekildi. Rol modu aktif edildi. (PayDay y�kseltildi)");
	if (pTemp[playerid][pPizzaBoy])
	{
	    pTemp[playerid][pPizzaBoy] = 0;
	    SendSyntaxMessage(playerid, "Sipari�inizi teslim etmeyi reddettiniz. Yeni sipari� iki dakika i�inde haz�r olacak.");
	    DisableWaypoint(playerid);
	    SetPVarInt(playerid, #pizza_time, gettime() + 120);
	    return 1;
	}
	
	if (GetPVarInt(playerid, #pizza_time) > gettime())									return SendErrorMessage(playerid, "Sipari� yok, l�tfen daha sonra ileti�ime ge�in.");
	if (!IsDriver(playerid) || GetVehicleModel(GetPlayerVehicleID(playerid)) != 448)	return SendErrorMessage(playerid, "Kurye motoru kullan�yor olmal�s�n�z.");
		
	new i, apartid = random(MAX_APART);
		
	while(i == 0)
	{
	    if (!ApartInfo[apartid][aID])
		{
			apartid = random(MAX_APART);
		}
		else
		{
		    i = 1;
		    pTemp[playerid][pPizzaBoy] = apartid+1;
		    SendClientMessageEx(playerid, COLOR_SERVER2, "Yeni sipari�, adres: %s", GetApartmentZone(ApartInfo[apartid][aID]));
            SendHelpMessage(playerid, "Konuma gittikten sonra motordan /pizza ile pizzay� al�p noktaya teslim edin.");

			Waypoint_Set(playerid, ApartInfo[apartid][aPosX], ApartInfo[apartid][aPosY], ApartInfo[apartid][aPosZ]);

		    return 1;
		}
	}
	return 1;
}
