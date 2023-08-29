#define compat=1

#pragma dynamic 100001

#pragma warning disable 214
#pragma warning disable 239
#pragma warning disable 217
#pragma warning disable 203
#pragma warning disable 204

//////////////////////////////////////////////////////
//                                                  //
// 		VERÝTABANI AYARLARI:                        //
//		-	scriptfiles/mysqlsettings.ini           //
//                                                  //
//    	LIBERTY ROLEPLAY 2023                 		//
//      Tüm haklarý saklýdýr.                       //
//      Geliþtirici: BLAZE                          //
//                                                  //
//////////////////////////////////////////////////////

#define 	REGISTRATION 		(0)
#define 	GameModeVersion 	"1.0.6"
#define 	GameModeUpdate 		"24.08.2023"
#define 	SERVER_BONUS 		2000
#define 	GameModeText 		"Closed Beta "GameModeVersion""
#define 	WeburlName 			"libertycityrpg.com"
#define 	ProjectName 		"Liberty City"
#define 	ServerName 			""ProjectName" ["WeburlName"]"
#define 	MAP_NAME 			"Liberty City"

//////////////////////////////////////////////////////
//                   INCLUDES                       //
//////////////////////////////////////////////////////
#include 	<a_samp>
#include 	<crashdetect>
#include    <Pawn.RakNet>
#include    <streamer>
#include 	<Pawn.CMD>
#include 	<a_mysql>
#include 	<sscanf2>
#include 	<foreach>
#include 	<dc_foreach_veh>
#include    <SKY> 					// Version: 2.3.0
#include    <weapon-config> 		// Version: Edited by Blaze
#include 	<memory>
#include 	<PreviewModelDialog>
#include 	<eSelection>
#include 	<easyDialog>
#include 	<kalsin>
#include 	<messagebox>
#include 	<3dmenu>
#include 	<PlayerToPlayer>
#include	<strlib>
#include 	<acuf>
//#include 	<useful>
#include 	<mxdate>
#include 	<timestamp>
#include    <mxINI>
#include    <timerfix>
#include    <evf>
#include 	<evi>
#include    <md5>
//#include    <discord-connector>
#include    <anti_airbreak>
#include    <AntiVehicleSpawn>
//////////////////////////////////////////////////////
//                   GAMEMODE                       //
//////////////////////////////////////////////////////

#include "../include/furniture_list.inc"
#include "../include/vehicle_sells.inc"
#include "gm/a_build/build.inc"

//////////////////////////////////////////////////////
//                SUNUCU AYARLARI                   //
//////////////////////////////////////////////////////

main()
{
	print(" "ProjectName" Versiyon - "GameModeVersion"");
	print(" Son Guncelleme - "GameModeUpdate"");
	return 1;
}

public OnGameModeInit()
{
	//Map_OnGameModeInit();
	SQL_OnGameModeInit();
	Server_OnGameModeInit();
	Job_OnGameModeInit();
	TDraw_OnGameModeInit();
	Taxi_OnGameModeInit();
	ItemDrop_Init();
	Label_OnGameModeInit();
	Tower_OnGameModeInit();
	Garage_OnGameModeInit();
	Enterance_OnGameModeInit();
    Gate_OnGameModeInit();
	ATM_OnGameModeInit();
	Borsa_OnGameModeInit();
    Tele_OnGameModeInit();
    Obj_OnGameModeInit();
    CCTV_OnGameModeInit();
	ChopShop_OnGameModeInit();
	SC_OnGameModeInit();
    House_OnGameModeInit();
    Apart_OnGameModeInit();
    Biz_OnGameModeInit();
    Food_OnGameModeInit();
    APB_OnGameModeInit();
    Factions_OnGameModeInit();
    Radio_OnGameModeInit();
    Trucker_OnGameModeInit();
    PayPhone_OnGameModeInit();
    Marks_OnGameModeInit();
    Graffity_OnGameModeInit();
	Ship_Init();
	Patrul_Init();
    Fish_Init();
    Toll_Init();
	SetCurrentTime();
	Interior_OnGameModeInit();
	Timer_OnGameModeInit();
	License_OnGameModeInit();
	Donate_OnGameModeInit();
	LoadPayPhoneTD();
	Advert_OnGameModeInit();
	BillBoard_OnGameModeInit();
	Park_OnGameModeInit();
	RadarHud_OnGameModeInit();

	//StoreTD();
	Street_OnGameModeInit();

	SetTimer("Cars_OnGameModeInit", 5000, false);
	SetTimer("Vehicle_OnGameModeInit", 5000, false);

	mysql_tquery(dbHandle, "SELECT * FROM paketler WHERE sqlid = 0 AND aracsqlid = 0 AND faction_id = -1", "PaketYukle");
	mysql_tquery(dbHandle, "SELECT * FROM tohumlar", "TohumSorgu", "dddds", 0, 0, 0, 0, "");

	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000); // 900
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 1000);	

    // Weapon Config Ayarlarý
    SetVehiclePassengerDamage(true);
    SetDisableSyncBugs(true);	
	SetDamageFeed(false);
	SetDamageSounds(0, 0);

	//Streamer_ToggleErrorCallback(1);
    SetCrashDetectLongCallTime(0);
	DisableCrashDetectLongCall();

	UploadAntiCheatSettings();

	#include <interiors/main_lc/main.inc>

	return 1;
}

public OnGameModeExit()
{
	mysql_tquery(dbHandle, "UPDATE `users` SET `online`=0 WHERE `online` = 1");
	for(new i; i < MAX_BIZ; i++) Save_Business(i);
	for(new i; i < MAX_HOUSES; i++) Save_House(i);
	for(new i; i < MAX_VEHICLES; i++) Save_Car(i);
	for(new i; i < MAX_PLAYERS; i++) Save_User(i);

	SaveServer();

	mysql_close(dbHandle);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if (IsPlayerNPC(playerid))
		return 1;

    if (IsPlayerLogged(playerid))
	{
     	SetSpawnInfoEx(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
    	SpawnPlayer(playerid);
		return 1;
	}
    else
	{
	    SetTimerEx("CheckAccount", 1200, false, "i", playerid);
		SendServerMessage(playerid, "Hesap verileriniz alýnýyor. Lütfen bekleyin.");
	}
	return 1;
}


public OnPlayerConnect(playerid)
{
	Login_OnPlayerConnect(playerid);
	Anticheat_OnPlayerConnect(playerid);
	//Mapping_OnPlayerConnect(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	Login_OnPlayerDisconnect(playerid, reason);
	Graffity_OnPlayerDisconnect(playerid);
	Police_OnPlayerDisconnect(playerid);
    if(IsPlayerPhoneCreated(playerid)) Phone_Destroy(playerid);
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if (PlayerInfo[playerid][pChar] > 0 && PlayerInfo[playerid][pOnDuty])	SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]);
	else	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	Login_OnPlayerSpawn(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if (!IsPlayerLogged(playerid)) 			return 0;
	GetPlayerPos(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
	SetSpawnInfoEx(playerid, PlayerInfo[playerid][pPosX],PlayerInfo[playerid][pPosY],PlayerInfo[playerid][pPosZ]);
    Police_OnPlayerDeath(playerid);
	Death_OnPlayerDeath(playerid, killerid, reason);
	Graffity_OnPlayerDeath(playerid);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
    Vehicle_OnVehicleSpawn(vehicleid);
	return 1;
}

public OnVehicleRequestDeath(vehicleid, killerid)
{
    new Float:Health;
    GetVehicleHealth(vehicleid, Health);
    
    if(Health > 300.0)
    {
        return 0;
    }
    
    return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
    Police_OnVehicleDeath(vehicleid);
	Vehicle_OnVehicleDeath(vehicleid, killerid);
	Radar_OnVehicleDeath(vehicleid);
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (!IsPlayerLogged(playerid)) 			return 0;
	if (result == -1)	return SendErrorMessage(playerid, "\"/%s\" komutu bulunamadý. Yardým için {FF6347}/yardim{FFFFFF} veya {FF6347}/soru{FFFFFF} komutunu kullanabilirsiniz.", cmd);
    
	printf(sprintf("%s: /%s %s", GetNameEx(playerid), cmd, params));
	return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if (!IsPlayerLogged(playerid)) return 0;
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if (!IsPlayerLogged(playerid)) 			return 0;
	if (GetPVarInt(playerid, #buing_phone))	return 0;

	if (PlayerInfo[playerid][pMutedTime] > 0)
	{
		SendErrorMessage(playerid, "Yönetici sizin konuþmanýzý yasaklamýþ.");
		return 0;
	}
	if (PlayerInfo[playerid][pInjured] == 2)
	{
		SendErrorMessage(playerid, "Aðýr yaralýyken konuþamazsýn.");
		return 0;
	}

	Player_OnPlayerText(playerid, text);
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_CONFIRM_SYS) ConfirmDialog_Response(playerid, response);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if ((newstate == 2 && oldstate == 3) || (newstate == 3 && oldstate == 2)) 	return Kick(playerid);
	if (IsPlayerNPC(playerid)) 													return 1;

	Box_OnPlayerStateChange(playerid, newstate);
	Weapon_OnPlayerStateChange(playerid, newstate);
	Taxi_OnPlayerStateChange(playerid, newstate);
	Vehicle_OnPlayerStateChange(playerid, newstate, oldstate);
	HUD_OnPlayerStateChange(playerid, newstate, oldstate);
	Lic_OnPlayerStateChange(playerid, newstate);
	Radar_OnPlayerStateChange(playerid, newstate, oldstate);
	Trash_OnPlayerStateChange(playerid, newstate, oldstate);
	return 1;
}
public OnPlayerEnterCheckpoint(playerid)
{
    if (GetPVarInt(playerid, #SWATROPE) && PlayerInfo[playerid][pSwatDuty])
    {
        DeletePVar(playerid, #SWATROPE);
        DeletePVar(playerid, #CHOPID);

        ClearAnimations(playerid);
        TogglePlayerControllable(playerid,0);
        TogglePlayerControllable(playerid,1);

        DisablePlayerCheckpoint(playerid);

		for (new i = 0; i < MAX_ROPE_LENGTH; i++) {
            DestroyObject(RopesInfo[playerid][i]);
        }
    }
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	printf(cmd);
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if (IsPlayerNPC(playerid))
		return 1;

	return 0;
}

public OnDynamicObjectMoved(objectid)
{
    Ship_OnDynamicObjectMoved(objectid);

	return 1;
}


public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	V_OnVehicleDamageStatusUpdate(vehicleid);
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	House_OnPlayerSelectedMenuRow(playerid, row);
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
    if (pTemp[playerid][pInteriorBiz])	ShowMenuForPlayer(buy_interior, playerid);

	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	Admin_OnPlayerKeyStateChange(playerid, newkeys);
	Attach_OnPlayerKeyStateChange(playerid, newkeys);
	Keys_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	//Skate_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	Player_OnPlayerUpdate(playerid);
	Vehicle_OnPlayerUpdate(playerid);
	Phone_OnPlayerUpdate(playerid);
	Corpse_OnPlayerUpdate(playerid);
	Flymode_OnPlayerUpdate(playerid);
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    if ((PlayerInfo[forplayerid][pSettings] & togName) || maskOn{playerid})	ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);

	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	if (IsPlayerLogged(playerid) && maskOn{playerid})	ShowPlayerNameTagForPlayer(playerid, playerid, false);

	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	if (VehicleInfo[vehicleid][carLocked]) SetVehicleParamsForPlayer(vehicleid,forplayerid,0,1)
	;
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
    SetVehicleParamsForPlayer(vehicleid,forplayerid,0,0);
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &WEAPON:weapon, &bodypart)
{
    Weapon_OnPlayerDamage(playerid, amount, issuerid, weapon, bodypart);
	return 1;
}

forward OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    Weapon_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
    Fire_OnPlayerWeaponShot(playerid);
    CCTV_OnPlayerWeaponShot(playerid, weaponid);
	return 1;
}

public OnPlayerChange3DMenuBox(playerid,MenuID,boxid,list,boxes)
{
	return 1;
}

public OnPlayerSelect3DMenuBox(playerid,MenuID,boxid,list,boxes)
{
	Furn_OnPlayerSelect3DMenuBox(playerid, MenuID, boxid, list, boxes);

	return 1;
}

public OnPlayerSelectDynamicObject(playerid, STREAMER_TAG_OBJECT objectid, modelid, Float:x, Float:y, Float:z)
{
	Ob_OnPlayerSelectDynamicObject(playerid, objectid);
	Fu_OnPlayerSelectDynamicObject(playerid, objectid);

	return 1;
}

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	/*
	0 - EDIT_RESPONSE_CANCEL   // player cancelled (ESC)
	1 - EDIT_RESPONSE_FINAL    // player clicked on save
	2 - EDIT_RESPONSE_UPDATE   // player moved the object (edition did not stop at all)
	*/
    if (GetPVarInt(playerid, #edit_street)) 	 		St_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
 	else if (GetPVarInt(playerid, #edit_food))  		Food_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_item))  		Item_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_atm))   		ATM_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rz);
	else if (GetPVarInt(playerid, #edit_trash))   		Trash_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rz);
	else if (GetPVarInt(playerid, #edit_pp))   			PP_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rz);
	else if (GetPVarInt(playerid, #edit_pm))   			PM_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rz);
	else if (pTemp[playerid][pEditBort]) 				Fact_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #veh_editor))			Veh_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_object))		Obj_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_cctv))			CCTV_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_tower))			Tow_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #edit_gate) ||
			GetPVarInt(playerid, #2_edit_gate))			Gate_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, "edit_furniture"))	Bu_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, "Graffity:EditPos"))	Graf_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, "SC:Edit"))			SC_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #EditChopShop))		ChSh_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, "BB:Edit"))			BB_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
	else if (GetPVarInt(playerid, #CorpsEdit))			Corpse_OnPlayerEdit(playerid, objectid, response, x, y, z, rz);
	return 1;
}

public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
	Lic_OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
	return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	//Vehicle_OnPlayerEnterDynamicCP(playerid, checkpointid);
	GPS_OnPlayerEnterDynamicCP(playerid, checkpointid);
	Garage_OnPlayerEnterDynamicCP(playerid, checkpointid);
	Trash_OnPlayerEnterDynamicCP(playerid, checkpointid);
	return 1;
}
public OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	Biz_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	Ent_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	Lab_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	Fo_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	Ho_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	Ap_OnPlayerPickUpDynamicPickup(playerid, pickupid);
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    Attach_EditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
	Faction_EditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
	Weapon_EditAttachedObject(playerid, response, index, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ);
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if (!IsPlayerLogged(playerid)) return 0;

	for(new i; i < Iter_Count(boomboxIter); i++) 	 if (areaid == BoomboxInfo[i][bArea])  Box_OnPlayerEnterArea(playerid, areaid);
	for(new i; i < Iter_Count(speedcamObjects); i++) if (areaid == speedcam[i][sc_areaid]) SpeedCam_OnPlayerEnterArea(playerid, areaid);
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	Box_OnPlayerLeaveArea(playerid, areaid);
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == Text:INVALID_TEXT_DRAW)
	{
		if (pTemp[playerid][pPayphone] != -1)
			return cancelPayphone(playerid);

		else if (GetPVarInt(playerid, #spawnveh_id))
		{
			CancelSelectTextDraw(playerid);
			DeletePVar(playerid, #spawnveh_id);

			PlayerTextDrawHide(playerid, SpawnVeh_Model[playerid]);
			PlayerTextDrawHide(playerid, SpawnVeh_Box[playerid]);
			for(new i = 0; i < 2; i++) PlayerTextDrawHide(playerid, SpawnVeh_Arrows[playerid][i]);
			for(new e = 0; e < 3; e++) PlayerTextDrawHide(playerid, SpawnVeh_Base[playerid][e]);
		}
	}
	TD_OnPlayerClickTextDraw(playerid, clickedid);
	PP_OnPlayerClickTextDraw(playerid, clickedid);
	return 1;
}
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(CharacterSelection[playerid][sIsSelecting])
    {
        if(playertextid == PlayerTextdraws[playerid][LoginCharacterTD][1])
        {
            // Giris Yap
            new query[1024];
            format(query, sizeof(query), "SELECT users.*, accounts.* FROM users, accounts WHERE users.id = %i", GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID));
            mysql_tquery(dbHandle, query, "LoadCharacter", "i", playerid);

			mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weaponsettings WHERE sOwner = %d", GetPVarInt(playerid, PVAR_LISTCHARS_CDETAILS_CID));
		    mysql_tquery(dbHandle, queryx, "OnLoadWeapons", "d", playerid);
        }

        if(playertextid == PlayerTextdraws[playerid][LoginCharacterTD][2])
        {
            // Geri

            LoginScreenDisplayCharacter(playerid, CharacterSelection[playerid][sCurrentSlotID] - 1);
            SyncCharacterSelectionButtons(playerid);
        }

        else if(playertextid == PlayerTextdraws[playerid][LoginCharacterTD][3])
        {
            // Ileri

            LoginScreenDisplayCharacter(playerid, CharacterSelection[playerid][sCurrentSlotID] + 1);
            SyncCharacterSelectionButtons(playerid);
        }
    }

    Ph_OnPlayerClickPlayerTextDraw(playerid, playertextid);
    Fo_OnPlayerClickPlayerTextDraw(playerid, playertextid);
    PP_OnPlayerClickPlayerTextDraw(playerid, playertextid);
    Vh_OnPlayerClickPlayerTextDraw(playerid, playertextid);
    MD_OnPlayerClickPlayerTextDraw(playerid, playertextid);
    return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	Admin_OnPlayerClickMap(playerid, fX, fY, fZ);
	return 1;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
    if (errorid == CR_SERVER_LOST)
	{
		if(!LoadMySQLSettings()) return 0;
		
	    dbHandle = mysql_connect("localhost", "root", "", "gamemode");
		mysql_log();
		if (mysql_errno() != 0) printf("[MySQL]: Yeniden baglanilamadi: %s", sqlData[SQL_HOST]);
		else
		{
			printf("[MySQL]: Yeniden baglanildi: %s | Kullanici Adi: %s", sqlData[SQL_HOST], sqlData[SQL_USER]);
			
	        if(mysql_errno(dbHandle) != 0) printf("[SQL] Oyun sunucusu veritabanýna baðlanamadý.");

	        mysql_set_charset("latin5", dbHandle);
	        mysql_query(dbHandle, "SET NAMES latin5");

	        mysql_log(ERROR | WARNING); 
		}
	}

	printf("MYSQL HATASI: %s\n%s", query, error);

	return SendAdmMessage("MYSQL HATASI: %s - %s", query, error);
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
    return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z)
{
	CCTV_OnPlayerShootDynamicObject(playerid, weaponid, objectid);
	return 1;
}

public OnPlayerRequestDownload(playerid, type, crc)
{
	if(!IsPlayerConnected(playerid)) return 0;

    new forummodel[] = "http://51.210.222.58/fastdl-models";
    new fullurl[256], dlfilename[64], foundfilename = 0;
    if(type == DOWNLOAD_REQUEST_TEXTURE_FILE) foundfilename = FindTextureFileNameFromCRC(crc, dlfilename, 64);
    else if(type == DOWNLOAD_REQUEST_MODEL_FILE) foundfilename = FindModelFileNameFromCRC(crc, dlfilename, 64);
	if(foundfilename)
	{
		format(fullurl, sizeof(fullurl), "%s/%s", forummodel, dlfilename);
		RedirectDownload(playerid, fullurl);
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	Weapon_OnPlayerExitVehicle(playerid, vehicleid);
	Mechanic_OnPlayerExitVehicle(playerid);
	License_OnPlayerExitVehicle(playerid, vehicleid);
	Vehicle_OnPlayerExitVehicle(playerid, vehicleid);
	Box_OnPlayerExitVehicle(playerid);
	Death_OnPlayerExitVehicle(playerid, vehicleid);
	Police_OnPlayerExitVehicle(playerid);
	pTemp[playerid][AntiHileSistemi] = -1;
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY)	ClearAnimations(playerid);
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return SendErrorMessage(playerid, "Þu an herhangi bir araca binemezsiniz.");
    if (VehicleInfo[vehicleid][carTerminate] > 0 && VehicleInfo[vehicleid][carType] != 0) VehicleInfo[vehicleid][carTerminate] = 0;
	if (VehicleInfo[vehicleid][carTerminateEx] > 0) VehicleInfo[vehicleid][carTerminateEx] = 0;

	Police_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	Corpse_OnPlayerEnterVehicle(playerid);

	pTemp[playerid][AntiHileSistemi] = vehicleid;
	return 1;
}