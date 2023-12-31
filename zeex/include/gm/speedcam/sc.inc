SC_OnGameModeInit()
{
	return mysql_tquery(dbHandle, "SELECT * FROM `speedcams`", "LoadDynamicSpeed");
}

SC_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
    new scid = GetPVarInt(playerid, "SC:ID") - 1;

    GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

	if (GetPVarInt(playerid, "SC:Edit") && speedcam[scid][sc_object] == objectid)
	{
		if (response == EDIT_RESPONSE_FINAL)
		{
	    	DeletePVar(playerid, "SC:Edit");
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			
			new query[256];

			mysql_format(dbHandle, query, sizeof(query), "UPDATE `speedcams` SET `posx` = %f, `posy` = %f, `posz` = %f, `posrx` = %f, `posry` = %f, `posrz` = %f WHERE `id` = %i", x, y, z, rx, ry, rz, speedcam[scid][sc_id]);
			mysql_tquery(dbHandle, query);
			
			GetDynamicObjectPos(objectid, speedcam[scid][sc_x], speedcam[scid][sc_y], speedcam[scid][sc_z]);
            GetDynamicObjectRot(objectid, speedcam[scid][sc_rx], speedcam[scid][sc_ry], speedcam[scid][sc_rz]);

  			SendSyntaxMessage(playerid, "Radar� d�zenlendiniz. [ID: %i | %s].", scid, speedcam[scid][sc_name]);
            SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "(( %s adl� ki�i h�z kameras�n� d�zenledi: [ID: %i | %s] ))", GetName(playerid), scid, speedcam[scid][sc_name]);
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
		    DeletePVar(playerid, "SC:Edit");
			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		}
	}
	return 1;
}

SpeedCam_OnPlayerEnterArea(playerid, areaid)
{
	if (VehicleInfo[GetPlayerVehicleID(playerid)][carAdmin]) return 1;

	new sp_camid = -1;
    for(new i = 0; i < Iter_Count(speedcamObjects); i++)
	{
		if (areaid == speedcam[i][sc_areaid]) 
		{
			sp_camid = i;
			break;
		}
	}
	if (sp_camid == -1) return 1;

    new faction = PlayerInfo[playerid][pFaction], 
        sc_vehid = GetPlayerVehicleID(playerid)
    ;
    if ((IsFactionPolice(faction) || IsFactionMedic(faction) || IsFactionFire(faction)) && PlayerInfo[playerid][pOnDuty]) return 1;
	if (IsFactionPolice(VehicleInfo[sc_vehid][carFaction]))	    return 1;
    if (!IsPlayerInAnyVehicle(playerid))						return 1; 
    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)		return 1;
	if (VehicleInfo[sc_vehid][carType] > 0)                     return 1;
    if (IsNotAEngineCar(sc_vehid))							    return 1;
    
    if (speedcam[sp_camid][sc_speed]+20+random(10) > GetVehicleSpeed(sc_vehid))	return 1; 

	SM2(playerid, "Radar sizi yakalad�: %s. H�z s�n�r�n� a�t�n�z.", speedcam[sp_camid][sc_name]);

	PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0);

	new msg[150];

	if (!VehicleInfo[sc_vehid][carRent])
	{
		if (VehicleInfo[sc_vehid][carPlate] == '_') 
			return SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: Radar [ID: %i | %s]: %s model plakas�z ara� radara yakaland� - %i km/h. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], GetVehicleSpeed(sc_vehid));
		else if (VehicleInfo[sc_vehid][carFakePlate])
			return SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: Radar [ID: %i | %s]: %s model sisteme kay�t edilmemi� plakal� ara� radara yakaland� - %i km/h. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], GetVehicleSpeed(sc_vehid));
		else if (VehicleInfo[sc_vehid][carWanted])
			SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: Radar [ID: %i | %s]: %s [%s], aran�yor - %i km/h. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate], GetVehicleSpeed(sc_vehid));
		
		GiveVehicleTicket(0, sc_vehid, SC_DEF_TICKET_SUM, "H�z s�n�r�n� a�mak", 1);
		format(msg, sizeof(msg), "%s [%s] arac�n�z h�z s�n�r�n� a�t��� i�in radara yakaland� ve radar arac�n�za $%d ceza kesti. Tespit Edilen H�z: %i km/h.", VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate], SC_DEF_TICKET_SUM, GetVehicleSpeed(sc_vehid));
		new find = 0;
		foreach(new i : Player)
		{
			if (VehicleInfo[sc_vehid][carOwnerID] == PlayerInfo[i][pID])
			{
				playerid = i;
				find++;
			}
		}
		if (!find)
		{
			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id`=%i", VehicleInfo[sc_vehid][carRent]);
			mysql_tquery(dbHandle, query, "SmsToPlayerOff", "sss", "1199", "LCPD", msg);
		}
		else SendSMStoPlayer(playerid, "1199", "LCPD", msg);
		
		return SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: Radar [ID: %i | %s]: %s [%s] - %i km/h. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate], GetVehicleSpeed(sc_vehid));
	}
	else 
	{
		GivePlayerTicket(0, VehicleInfo[sc_vehid][carRent], SC_DEF_TICKET_SUM, "H�z s�n�r�n� a�mak.", 1);
		format(msg, sizeof(msg), "%s [%s] kiral�k arac�n�z ile h�z s�n�r� a��ld��� i�in radara yakaland� ve radar arac�n�za $%d ceza kesti. Tespit Edilen H�z: %i km/h.", VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate], SC_DEF_TICKET_SUM, GetVehicleSpeed(sc_vehid)-speedcam[sp_camid][sc_speed]);
		new find = 0;
		foreach(new i : Player)
		{
			if (VehicleInfo[sc_vehid][carRent] == PlayerInfo[i][pID])
			{
				playerid = i;
				find++;
			}
		}
		if (!find)
		{
			new query[256];
			mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id`=%i", VehicleInfo[sc_vehid][carOwnerID]);
			mysql_tquery(dbHandle, query, "SmsToPlayerOff", "sss", "1199", "LCPD", msg);
		}
		else SendSMStoPlayer(playerid, "1199", "LCPD", msg);

		return SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: Radar [ID: %i | %s]: %s [%s] - %i km/h. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate], GetVehicleSpeed(sc_vehid));
		//return SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: SpeedCam [ID: %i | %s] ������������� ������������ ���������� ����� %s [%s]. **", sp_camid, speedcam[sp_camid][sc_name], VehicleNames[GetVehicleModel(sc_vehid)-400], VehicleInfo[sc_vehid][carPlate]);
	}
    //return 1;
}