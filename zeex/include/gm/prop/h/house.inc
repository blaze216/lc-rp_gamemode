House_OnPlayerSelectedMenuRow(playerid, row)
{
    if (GetPlayerMenu(playerid) != buy_interior) return 1;
	
	new houseid = pTemp[playerid][pInteriorHouse]-1;

	switch(row)
	{
	    case 0:
    	{
	        for(new i = pTemp[playerid][pInteriorID]+1; i < MAX_INTERIORS; i++)
	        {
	            if (!AdminTeles[i][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[i][telesType]) continue;
					
                pTemp[playerid][pInteriorID] = i;
				DestroyPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
	            pTemp[playerid][pInteriorObj] = CreatePlayerObject(playerid, 19300, AdminTeles[i][telesPosX], AdminTeles[i][telesPosY], AdminTeles[i][telesPosZ], 0.0, 0.0, 0.0);
				AttachCameraToPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
			    break;
	        }

	        ShowMenuForPlayer(buy_interior, playerid);
		}
		
	    case 1:
		{
		    for(new i = pTemp[playerid][pInteriorID]-1; i != 0; i--)
	        {
	            if (!AdminTeles[i][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[i][telesType]) continue;

                pTemp[playerid][pInteriorID] = i;
				DestroyPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
	            pTemp[playerid][pInteriorObj] = CreatePlayerObject(playerid, 19300, AdminTeles[i][telesPosX], AdminTeles[i][telesPosY], AdminTeles[i][telesPosZ], 0.0, 0.0, 0.0);
				AttachCameraToPlayerObject(playerid, pTemp[playerid][pInteriorObj]);
			    break;
	        }

	        ShowMenuForPlayer(buy_interior, playerid);
		}

		case 2:
		{
		    new id = pTemp[playerid][pInteriorID];
		    if (!AdminTeles[id][telesOn] || HouseInfo[houseid][hClass] != AdminTeles[id][telesType])	return SendErrorMessage(playerid, "Interior hatasý."); //îøèáêà èíòû
				
			Dialog_Show(playerid, BuyInteriorAccept, DIALOG_STYLE_MSGBOX, "{FFFFFF}Interior", "{ffffff}$750 karþýlýðýnda bir ev dekorasyonu almak istiyorsunuz.\nSatýn alýnan tüm mobilyalar satýlacak!", "Satýn Al", "Ýptal");
		}
	    case 3:	SetPlayerBuyInterior(playerid, 0);
	    
	}
    return 1;
}

Ho_OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		for(new i = 0; i < MAX_HOUSES; i++)
		{
		    if (!HouseInfo[i][hID] || (pickupid != HouseInfo[i][hPickup])) continue;
			
			new
				string[128]
			;

            if (!HouseInfo[i][hOwnerID] && pickupid == HouseInfo[i][hPickup])
			{
				new door[11];
				switch(HouseInfo[i][hDoor])
				{
					case 0: door = "Normal";
					case 1: door = "Ahþap";
					case 2: door = "Demir";
				}

				format(string, sizeof(string), "Kilit Seviyesi: %i / Alarm Seviyesi: %i / Kapi: %s~n~~y~/giris /(ds)hout /ddo /kapitikla~n~~g~~h~/evkontrol /ev satinal", HouseInfo[i][hLock], HouseInfo[i][hAlarm], door);
				InfoMSG(playerid, string, 5);

				format(string, sizeof(string), "~h~~p~SATILIK EV! ~w~/ FIYAT: ~g~$%i~n~~y~%s", HouseInfo[i][hPrice], (!HouseInfo[i][hApart])?(GetHouseZone(i, 2)):(GetApartmentZone(HouseInfo[i][hApart], 2)));
				CreateLableText(playerid, string, "~h~Satin almak icin ~y~~h~Y ~w~ tusuna basin veya ~y~~h~/ev satinal~h~~w~ komutunu kullanin.");
				return 1;
	   		}
			else if (HouseInfo[i][hOwnerID] != 0)
   			{
				if (pickupid == HouseInfo[i][hPickup]) {
					format(string, sizeof(string), "%s kapisinda duruyorsun ~h~~g~Ev~w~.~n~~y~/giris /(ds)hout /ddo /kapitikla.", (HouseInfo[i][hOwnerID] != PlayerInfo[playerid][pID])?("Baskasina ait evin"):("Sana ait evin"));
					InfoMSG(playerid, string, 5);

					format(string, sizeof(string),"~h~~p~Ev %s~n~%s", HouseInfo[i][hOwner], (!HouseInfo[i][hApart])?(GetHouseZone(i, 2)):(GetApartmentZone(HouseInfo[i][hApart], 2))); 
					CreateLableText(playerid, string, "~h~Girmek icin ~y~~h~Y ~w~tusuna basin veya ~y~~h~/giris~h~~w~ komutunu kullanin");
				} /*else if (checkpointid == HouseInfo[i][hExtCheckPoint]) {
					format(string, sizeof(string), "%s kapisinda duruyorsun ~h~~g~Ev~w~.~n~~y~/giris /(ds)hout /ddo /kapitikla.", (HouseInfo[i][hOwnerID] != PlayerInfo[playerid][pID])?("baskasina ait"):("sana ait"));
					InfoMSG(playerid, string, 5);

					format(string, sizeof(string),"~h~~p~Arka Kapi~n~%s", (!HouseInfo[i][hApart])?(GetHouseZone(i, 2)):(GetApartmentZone(HouseInfo[i][hApart], 2))); 
					CreateLableText(playerid, string, "~h~Girmek icin ~y~~h~Y ~w~tusuna basin veya ~y~~h~/giris~h~~w~ komutunu kullanin");
				}*/
				

                return 1;
			}
		}
    }
    return 1;
}

House_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT *, (SELECT name FROM users WHERE id = houses.owner) as ownername, (SELECT last_login FROM users WHERE id = houses.owner) as last_login FROM `houses`", "LoadDynamicHouses");
}

House_PlayerTimer(playerid)
{
	if (GetPVarInt(playerid, #check_int))
	{
	    UpdateIntVar(playerid, #check_int, -1);

	    new hid = -1;

		if (!GetPVarInt(playerid, #check_int) && (hid = GetNearInsideHouse(playerid)) != -1)
		{		        
			SetPlayerPosEx(playerid, HouseInfo[hid][hPosX], HouseInfo[hid][hPosY], HouseInfo[hid][hPosZ]);
			SetInterior(playerid, HouseInfo[hid][hPosInt]);
			SetWorld(playerid, HouseInfo[hid][hPosVW]);
		 	pTemp[playerid][pHouseEntered] = -1;
	      	SendSyntaxMessage(playerid, "Görüntüleme süresi doldu.");
		    DeletePVar(playerid, #check_int);
		}
	}
	return 1;
}