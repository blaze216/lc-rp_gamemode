PreloadAnimations(playerid)
{
	for (new i = 0; i < sizeof(PreloadAnimLibs); i ++) 
    {
	    ApplyAnimation(playerid, PreloadAnimLibs[i], "null", 4.0, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

OnPlayAnim(playerid,animlib[],animname[], Float:Speed, looping, lockx, locky, lockz, lp)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || PlayerInfo[playerid][pInjured] || JackingEngine[playerid] != 0 || JackingLock[playerid] != 0 || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
	{
		return 0;
	}
	
	/*if (!pTemp[playerid][pPlantTime] && !pTemp[playerid][pCargoID])
		InfoMSG(playerid, "~y~/animdurdur~w~ ile animasyonu ~r~ durdurabilirsiniz", 5);*/
	
	OnAnim{playerid} = true;
	ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, 1);
	
	return 1;
}

ChatAnimation(playerid, len)
{
	if (pTemp[playerid][pEmergency] != 0 || GetPVarInt(playerid, #selfie) || pTemp[playerid][pCallStatus] == 2 || 0 == PlayerInfo[playerid][pTalk] || PlayerInfo[playerid][pInjured] || IsPlayerInAnyVehicle(playerid) || JackingEngine[playerid] != 0 || JackingLock[playerid] != 0 || AntiCheatGetSpecialAction(playerid) == SPECIAL_ACTION_DUCK || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
	{
		return 1;
	}
	
	switch(PlayerInfo[playerid][pTalk])
	{
	    case 1: ApplyAnimation(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
	    case 2: ApplyAnimation(playerid,"GANGS","prtial_gngtlkA",4.0,1,0,0,1,1);
	    case 3: ApplyAnimation(playerid,"GANGS","prtial_gngtlkB",4.0,1,0,0,1,1);
	    case 4: ApplyAnimation(playerid,"GANGS","prtial_gngtlkC",4.0,1,0,0,1,1);
	    case 5: ApplyAnimation(playerid,"GANGS","prtial_gngtlkD",4.0,1,0,0,1,1);
	    case 6: ApplyAnimation(playerid,"GANGS","prtial_gngtlkE",4.0,1,0,0,1,1);
	    case 7: ApplyAnimation(playerid,"GANGS","prtial_gngtlkF",4.0,1,0,0,1,1);
	    case 8: ApplyAnimation(playerid,"GANGS","prtial_gngtlkG",4.0,1,0,0,1,1);
	    case 9: ApplyAnimation(playerid,"GANGS","prtial_gngtlkH",4.0,1,0,0,1,1);
	}
	SetTimerEx("TalkTimer", len * 25, 0, "i", playerid);
	return 1;
}

StopPlayerAnims(playerid)
{
	if (PlayerInfo[playerid][pInjured] || JackingEngine[playerid] != 0 || JackingLock[playerid] != 0 || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 0;
	//GetPlayerState(playerid) != PLAYER_STATE_ONFOOT

	OnAnim{playerid} = false;
	ClearAnimations(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	return 1;
}