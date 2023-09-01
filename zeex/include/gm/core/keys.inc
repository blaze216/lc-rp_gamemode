#if !defined KEY_AIM
	#define KEY_AIM 128
#endif

HoldingKey(playerid, key)
{
	new keys, ud, lr;

	GetPlayerKeys(playerid, keys, ud, lr);
	return (keys & key == key) ? (1):(0);
}

Keys_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new Float:vx,Float:vy,Float:vz;
	GetPlayerVelocity(playerid,vx,vy,vz);
	if (PRESSED(KEY_JUMP) && PRESSED(KEY_SPRINT) && (vy > 0.01 || vy <-0.01 || vx > 0.01 || vx <-0.01) && !IsPlayerInAnyVehicle(playerid) && InSprung[playerid] == 0 && PlayerInfo[playerid][pAdmin] < 1)
	{
		if(vz > 0.01 || vz < -0.01) return 1;
		InSprung[playerid] = 1;
		TimerIDSprung = SetTimerEx("FunktionInSprung",1,false,"i",playerid);
	}

	if(StaffInfo[playerid][sSpec])
	{
		new currentSpecID = StaffInfo[playerid][sSpecID];

		switch(newkeys)
		{
			case KEY_FIRE:
			{
				if(StaffInfo[playerid][sSpecType] == SPECTATE_TYPE_PLAYER)
				{
					for(new pid = currentSpecID + 1; pid < MAX_PLAYERS; pid++)
					{
						if(!IsPlayerLoggedIn(pid) || pid == playerid || PlayerInfo[pid][pAdmin] != 0)
							continue;

						Spectate(playerid, SPECTATE_TYPE_PLAYER, pid);
						return -1;
					}

					SendErrorMessage(playerid, "Daha fazla ileri gidecek karakter yok.");
					return -1;
				}

				else if(StaffInfo[playerid][sSpecType] == SPECTATE_TYPE_VEHICLE)
				{
					for(new vid = currentSpecID + 1; vid < MAX_VEHICLES; vid++)
					{
						if(!IsValidVehicle(vid))
							continue;

						Spectate(playerid, SPECTATE_TYPE_VEHICLE, vid);
						return -1;
					}

					SendErrorMessage(playerid, "Daha fazla ileri gidecek araç yok.");
					return -1;
				}
			}

			case KEY_HANDBRAKE:
			{
				if(StaffInfo[playerid][sSpecType] == SPECTATE_TYPE_PLAYER)
				{
					for(new pid = currentSpecID - 1; pid >= 0; pid--)
					{
						if(!IsPlayerLoggedIn(pid) || pid == playerid || PlayerInfo[pid][pAdmin] != 0)
							continue;

						Spectate(playerid, SPECTATE_TYPE_PLAYER, pid);
						return -1;
					}

					SendErrorMessage(playerid, "Daha fazla geri gidecek karakter yok.");
					return -1;
				}

				else if(StaffInfo[playerid][sSpecType] == SPECTATE_TYPE_VEHICLE)
				{
					for(new vid = currentSpecID - 1; vid >= 0; vid--)
					{
						if(!IsValidVehicle(vid))
							continue;

						Spectate(playerid, SPECTATE_TYPE_VEHICLE, vid);
						return -1;
					}

					SendErrorMessage(playerid, "Daha fazla geri gidecek araç yok.");
					return -1;
				}
			}

			case KEY_SPRINT:
			{
				Spectate(playerid, StaffInfo[playerid][sSpecType], currentSpecID);
			}
		}
	}

    if(!pCBugging[playerid] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(PRESSED(KEY_FIRE))
		{
			switch(GetPlayerWeapon(playerid))
			{
				case WEAPON_DEAGLE, WEAPON_SHOTGUN, WEAPON_SNIPER:
				{
					ptsLastFiredWeapon[playerid] = gettime();
				}
			}
		}
		else if(PRESSED(KEY_CROUCH))
		{
			if((gettime() - ptsLastFiredWeapon[playerid]) < 1)
			{
				//TogglePlayerControllable(playerid, false);

				pCBugging[playerid] = true;

				SendErrorMessage(playerid, "C-Bug yapmayýn.");

				KillTimer(ptmCBugFreezeOver[playerid]);
				ptmCBugFreezeOver[playerid] = SetTimerEx("CBugFreezeOver", 1500, false, "i", playerid);
			}
		}
	}

	if (PlayerInfo[playerid][pWalk] > 0 && ((newkeys & KEY_WALK && newkeys & KEY_UP) || (newkeys & KEY_WALK && newkeys & KEY_DOWN) || (newkeys & KEY_WALK && newkeys & KEY_LEFT) || (newkeys & KEY_WALK && newkeys & KEY_RIGHT))
		|| ((oldkeys & KEY_WALK && newkeys & KEY_UP) || (oldkeys & KEY_WALK && newkeys & KEY_DOWN) || (oldkeys & KEY_WALK && newkeys & KEY_LEFT) || (oldkeys & KEY_WALK && newkeys & KEY_RIGHT))
		|| ((newkeys & KEY_WALK && oldkeys & KEY_UP) || (newkeys & KEY_WALK && oldkeys & KEY_DOWN) || (newkeys & KEY_WALK && oldkeys & KEY_LEFT) || (newkeys & KEY_WALK && oldkeys & KEY_RIGHT))
		&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
			if(PlayerInfo[playerid][pInjured] == 0 && !IsPlayerInAnyVehicle(playerid)) YuruyusTimer[playerid] = SetTimerEx("YuruyusAnim", 200, false, "d", playerid);
	}

	if (VehicleInfo[JackingVehicle[playerid]][ePhysicalAttack] && RELEASED(KEY_FIRE) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !VehicleInfo[JackingVehicle[playerid]][vCooldown])
    {
		new weaponid = GetPlayerWeapon(playerid);
		new vehicleid = JackingVehicle[playerid];
		if (IsValidVehicle(vehicleid))
		{
			new Float:ccX, Float:ccY, Float:ccZ;
			new Float:dX, Float:dY, Float:dZ, Float: playerHealth;
			
			AntiCheatGetHealth(playerid, playerHealth);
			GetVehicleModelInfo(VehicleInfo[vehicleid][carModel], VEHICLE_MODEL_INFO_FRONTSEAT, ccX, ccY, ccZ);
			GetVehicleRelativePos(vehicleid, dX, dY, dZ, -ccX - 0.5, ccY, ccZ);
			
			if (GetVehicleDriver(vehicleid) != -1 || VehicleInfo[vehicleid][eDoorHealth] <= 0.0 || !IsPlayerInFrontVDoor(playerid, vehicleid)) return 1;
			
		    switch(VehicleInfo[vehicleid][eDoorEffect])
		    {
		        case LESS_DAMAGE_FIST:
		        {
		            if (weaponid == 0)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 1 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 1;
		                if (playerHealth > 15.0)
		                {
		                    PlayerInfo[playerid][pHealth] = playerHealth - 10.0;
		                }
		            }
		            if (weaponid >= 1 && weaponid <= 9)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 10 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 10;
		            }
		          	if (weaponid >= 22 && weaponid <= 24)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 15 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 15;
              		}
		          	if (weaponid >= 25 && weaponid <= 34)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 30 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 30;
		            }
		        }
		        case BLOCK_FIST:
		        {
					if (weaponid == 0) if (playerHealth > 15.0) PlayerInfo[playerid][pHealth] = playerHealth - 5.0;

		            if (weaponid >= 1 && weaponid <= 9)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 10 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 10;
		            }
		          	if (weaponid >= 22 && weaponid <= 24)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 15 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 15;
		            }
					if (weaponid >= 25 && weaponid <= 34)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 30 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 30;
		            }
		        }
		        case LESS_DAMAGE_MELEE:
		        {
					if (weaponid == 0) if (playerHealth > 15.0) PlayerInfo[playerid][pHealth] = playerHealth - 5.0;
		          	if (weaponid >= 22 && weaponid <= 24)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 5 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 5;
		            }
		          	if (weaponid >= 25 && weaponid <= 34)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 20 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 20;
		            }
		        }
		        case BLOCK_PHYSICAL:
		        {
					if (weaponid == 0) if (playerHealth > 15.0) PlayerInfo[playerid][pHealth] = playerHealth - 5.0;
		          	if (weaponid >= 25 && weaponid <= 34)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 30 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 30;
		            }
		        }
		        default:
		        {
		            if (weaponid == 0)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 2 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 2;
		                if (playerHealth > 15.0)
		                {
		                   PlayerInfo[playerid][pHealth] = playerHealth - 5.0;
		                }
		            }
		            if (weaponid >= 1 && weaponid <= 9)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 10 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 10;
		            }
		          	if (weaponid >= 22 && weaponid <= 24)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 15 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 15;
		            }
		          	if (weaponid >= 25 && weaponid <= 34)
		            {
		                VehicleInfo[vehicleid][eDoorHealth] = (VehicleInfo[vehicleid][eDoorHealth] - 30 <= 0) ? 0 : VehicleInfo[vehicleid][eDoorHealth] - 30;
		            }
				}
			}

			new engine, lights, alarm, doors, bonnet, boot, objective, panels, tires;
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			switch(VehicleInfo[vehicleid][eDoorHealth])
			{
			
				case 0: UpdateVehicleDamageStatus(vehicleid, panels, encode_doors(0, 0, 4, 0, 0, 0), lights, tires);
				case 1 .. 20: UpdateVehicleDamageStatus(vehicleid, panels, encode_doors(0, 0, 2, 0, 0, 0), lights, tires);
			}

			new doorhealth[12];
			format(doorhealth, 12, "%d%%", VehicleInfo[vehicleid][eDoorHealth]);
			UpdateDynamic3DTextLabelText(VehicleInfo[vehicleid][eVehicleLabel], COLOR_WHITE, doorhealth);

			VehicleInfo[vehicleid][vCooldown] = true;
			SetTimerEx("OnCoolDown", 1000, false, "i", vehicleid);
			
			AlarmOn(vehicleid);

			if (VehicleInfo[vehicleid][eDoorHealth] <= 0)
			{
			    DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][eVehicleLabel]);
			    VehicleInfo[vehicleid][vCooldown] = false;
			    VehicleInfo[vehicleid][ePhysicalAttack] = false;
			    VehicleInfo[vehicleid][eDoorHealth] = 0;
				JackingVehicle[playerid] = 0;

				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, false, bonnet, boot, objective);
				
				ToggleVehicleLock(JackingVehicle[playerid], false);
				PlaySound(playerid, 1145);
				InfoMSG(playerid, "ARACIN KAPISINI KIRDIN!", 3);
				AlarmOn(JackingVehicle[playerid]);
			}
		}
    }

	if (HOLDING(KEY_FIRE) && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS) && GetPVarInt(playerid, #use_food) && GetPVarInt(playerid, #time_food) < gettime())
	{
	    SetPVarInt(playerid, #time_food, gettime()+2);
		SetPVarInt(playerid, #use_food, GetPVarInt(playerid, #use_food)-1);
		
		if (GetPVarInt(playerid, #use_food) == 0)
		{
		    DeletePVar(playerid, #use_food);
			RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		}

		else
		{
			OnPlayAnim(playerid, "FOOD", "EAT_Burger", 4.1,0,1,1,0,0);
		}
		return 1;
	}
	
    if (HOLDING(KEY_SECONDARY_ATTACK) && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS) && GetPVarInt(playerid, #use_food))
	{
	    DeletePVar(playerid, #use_food);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		return 1;
	}
	
	if (OnAnim{playerid} && HOLDING(KEY_SECONDARY_ATTACK) && GetPlayerAnimationIndex(playerid) && !PlayerInfo[playerid][pInjured])
	{
		StopPlayerAnims(playerid);
	}

    if (HOLDING(KEY_SECONDARY_ATTACK) && GetPVarInt(playerid, #selfie))
	{
        pc_cmd_selfie(playerid, "");
	}

    if (((PRESSING(newkeys, KEY_SPRINT) || PRESSING(newkeys, KEY_JUMP)) || (HOLDING(KEY_SPRINT) || HOLDING(KEY_JUMP))) && pTemp[playerid][pInjuredLegTime] && !IsPlayerInAnyVehicle(playerid))
	{
		TogglePlayerControllable(playerid,0);
		StopPlayerAnims(playerid);
		TogglePlayerControllable(playerid,1);

		if (PRESSED(KEY_SPRINT) || HOLDING(KEY_SPRINT))	ApplyAnimation(playerid, "PED", "FALL_collapse", 4.1, 0, 1, 1, 0, 0);
		else if (PRESSED(KEY_JUMP)|| HOLDING(KEY_JUMP))	ApplyAnimation(playerid, "PED", "getup_front", 4.0, 0, 0, 0, 0, 0);
	}

	if (HOLDING(KEY_SECONDARY_ATTACK) && pTemp[playerid][p3DMenu] != -1)
	{
    	Destroy3DMenu(pTemp[playerid][p3DMenu]);
		pTemp[playerid][p3DMenu] = -1;
		
		SetTimerEx("ShowEditFurniture", 1000, false, "i", playerid);
		return 1;
	}

	if (PRESSED(KEY_CTRL_BACK))
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
			if (pTemp[playerid][pCargoID] != 0)
			{
				if (GetNearBootVehicle(playerid) == 0) 	return pc_cmd_koli(playerid, "yerebirak");
				else 									return pc_cmd_koli(playerid, "yerlestir");
			}
			else if (IsPlayerNearCargo(playerid) != -1) 	return pc_cmd_koli(playerid, "yerdenal");

			if (ATM_Nearest(playerid) != -1) 		pc_cmd_atm(playerid, "");
			if (Payphone_Nearest(playerid) != -1) 	pc_cmd_ankesorlutelefon(playerid, "");
			if (GetNearestCorpse(playerid) != -1)	pc_cmd_ceset(playerid, "");
			if (BoomboxInfo[playerid][bUsed] != 0)	ShowBoomboxMenu(playerid);

			if (Trash_Nearest(playerid, 1.5) != -1 && PlayerInfo[playerid][pJob] == JOB_TRASHMASTER && pTemp[playerid][pJob]) 
				pc_cmd_copculuk(playerid, "");
			
			if (AntiCheatGetSpecialAction(playerid) == SPECIAL_ACTION_DUCK) { 
				if (ItemDrop_Nearest(playerid) != -1) pc_cmd_yerdenal(playerid, "");
			}
		}
	}

	if (RELEASED(KEY_YES) && !IsPlayerInAnyVehicle(playerid)) {
		if (!(PlayerInfo[playerid][pSettings] & togEnter) && pTemp[playerid][p3DMenu] == -1 && PlayerInfo[playerid][pInjured] == 0)
		{
			pc_cmd_giris(playerid, "");
	    	pc_cmd_cikis(playerid, "");
		}
	    /*if (TruckCargo_Nearest(playerid, 1.5) != -1)
		{
			if (pTemp[playerid][pCargoID] == 0)
				pc_cmd_endustri(playerid, "");
			else pc_cmd_koli(playerid, "sat");
		}*/
		if (Job_Nearest(playerid) != -1) pc_cmd_isegir(playerid, "");		
	}

	if (HOLDING(KEY_CROUCH) && IsPlayerInAnyVehicle(playerid))
	{
	    pc_cmd_gateac(playerid, "");

		pc_cmd_giris(playerid, "");
	    pc_cmd_cikis(playerid, "");

		if (Toll_Nearest(playerid) != -1) 	pc_cmd_gise(playerid, "");
		if (AZC_Nearest(playerid) != -1)	pc_cmd_benzin(playerid, "");

	    return 1;
	}

	if (HOLDING(KEY_LOOK_BEHIND) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{	
		pc_cmd_ahe(playerid, "");
		return 1;
	}

	if (HOLDING(KEY_CTRL_BACK) && !IsPlayerInAnyVehicle(playerid) && pTemp[playerid][p3DMenu] != -1)
	{
	    UpdateIntVar(playerid, "chose_texture", 1);
	    
		if (GetPVarInt(playerid, "chose_texture") > 4) SetPVarInt(playerid, "chose_texture", 0);

		new mes[32];
		format(mes, sizeof(mes), "~y~Texture degistirildi: ~w~%i", GetPVarInt(playerid, "chose_texture")+1);
		InfoMSG(playerid, mes, 4);
		return 1;
	}

	/*if (PRESSED(KEY_CTRL_BACK))
	{
	    
	}*/

	if (HOLDING(KEY_NO))
	{
		if (GetPlayerDeniedAction(playerid) != 0) return 1;
		if (GetNearVehicle(playerid, 3.0) != 0) pc_cmd_arac(playerid, "kilit");
		if (HasTrash[playerid]) Trash_ResetPlayer(playerid);
	}

	if (RELEASED(KEY_YES))
	{
		if (pTemp[playerid][pFactionInvite] > 0) return pc_cmd_birlikdavetkabul(playerid, "");
		if (GetPVarInt(playerid, #accept_time) > gettime()) return GetPlayerAcceptAction(playerid);
		if (pTemp[playerid][pServePlayer] != INVALID_PLAYER_ID) return false;

		
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			pc_cmd_motor(playerid, "");
			return 1;
		}
		
        return 1;	
	}

	if (pTemp[playerid][pFoodStand] != 0 && (PRESSED(KEY_JUMP) || PRESSED(KEY_FIRE) || PRESSED(KEY_CROUCH)))
	{

		OnPlayAnim(playerid,"PED","IDLE_tired",4.1,0,1,1,0,1);
		RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
		pTemp[playerid][pFoodStand] = 0;
		SetPlayerChatBubble(playerid, "elindeki yemeði çöpe atar.", COLOR_PURPLE, 20.0, 4000);
	}

	if (PRESSED(KEY_FIRE) && RepairService[playerid] != 0 && RepairOffer[playerid] != INVALID_PLAYER_ID && RepairToVehicle[playerid] != INVALID_VEHICLE_ID)
	{
		if (GetNearVehicle(playerid, 4.2, RepairToVehicle[playerid]) == 0)	ShowJobMessage(playerid, "~h~~p~ARACIN YAKININDA OLMALISIN.");
		else
		{
			RepairOffer[playerid] = INVALID_PLAYER_ID;
			RepairTime[playerid] = 15;
		}
	}
    return 1;
}