//ñêåéòáîðä

#define MODE_SKATE (1)        // 0 - medium speed | 1 - fast speed
#define TYPE_SKATE (0)        // 0 - the skate is placed on the right arm | 1 - the skate is placed in the back
#define INDEX_SKATE (0)       //is the slot that used SetPlayerAttachedObject

enum skate
{
        bool:sActive,
        sSkate,
};
new InfoSkate[MAX_PLAYERS][skate];

CMD:kaykay(playerid, params[])
{
    new mes[128];

    if (!IsPlayerHasItem(playerid, INV_SKATE)) return SendErrorMessage(playerid, "Kaykaya sahip deðilsiniz.");
		
	if (InfoSkate[playerid][sActive] == true)
	{
		InfoSkate[playerid][sActive] = false;
        DestroyDynamicObject(InfoSkate[playerid][sSkate]);
        PlayerPlaySound(playerid,21000,0,0,0);
        format(mes, sizeof(mes),"kaykayý yerden alýr.");
		pc_cmd_me(playerid, mes);
	}
	else if (InfoSkate[playerid][sActive] == false)
	{
		InfoSkate[playerid][sActive] = true;
        CreateDynamicObject(InfoSkate[playerid][sSkate]);
        //PlayerPlaySound(playerid,21000,0,0,0);
        SendSyntaxMessage(playerid, "Kaykayý sürmek için mouse sað klik tuþuna basýn.");
	}

	return 1;
}

Skate_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (InfoSkate[playerid][sActive] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        static bool:act;

        SetPlayerArmedWeapon(playerid,0);
        
        if (newkeys & KEY_HANDBRAKE)
		{
            #if MODE_SKATE == 0
                ApplyAnimation(playerid, "SKATE","skate_run",4.1,1,1,1,1,1,1);
            #else
            	ApplyAnimation(playerid, "SKATE","skate_sprint",4.1,1,1,1,1,1,1);
            #endif
        	
			if (!act)
			{
                act = true;
                DestroyDynamicObject(InfoSkate[playerid][sSkate]);
                InfoSkate[playerid][sSkate] = CreateDynamicObject(19878,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
                AttachDynamicObjectToPlayer(InfoSkate[playerid][sSkate],playerid, -0.2,0,-0.9,0,0,90);
            }
		}
        if (oldkeys & KEY_HANDBRAKE)
		{
        	ApplyAnimation(playerid, "CARRY","crry_prtial",4.0,0,0,0,0,0);
        	
			if (act)
			{
                act = false;
                DestroyDynamicObject(InfoSkate[playerid][sSkate]);
            }
        }
	}
	return 1;
}