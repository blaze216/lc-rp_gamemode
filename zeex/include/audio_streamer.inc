/*
 *  audio_streamer.inc
 *  Динамическое радио
 *
 *   редиты:
 *    Dema
 *
 *  Создано 25.01.2017, январь 25.
*/

// Максимальное количество аудио потоков.
#if !defined MAX_DYNAMIC_AUDIO
	#define MAX_DYNAMIC_AUDIO	1000
#endif

// Tick rate
#if !defined AUDIO_TICK_RATE
	#define AUDIO_TICK_RATE		500
#endif

//Invalid id
#if !defined INVALID_AUDIO_ID
	#define INVALID_AUDIO_ID		-1
#endif

enum e_DynamicAudio
{
	e_AudioUsed,
	e_AudioUrl[128],
	Float:e_AudioX,
	Float:e_AudioY,
	Float:e_AudioZ,
	Float:e_AudioDistance,
	e_AudioVW,
	e_AudioInt,
	e_AudioVehicle,
	e_AudioTimer
};


static
	s_DynamicAudio[MAX_DYNAMIC_AUDIO][e_DynamicAudio],
	s_PlayersAudio[MAX_PLAYERS] = {INVALID_AUDIO_ID, ...}
;

public OnFilterScriptExit()
{
	for (new i = 0; i < MAX_DYNAMIC_AUDIO; i ++)
	{
		if (s_DynamicAudio[i][e_AudioUsed] == 0)
			continue;
		
		DestroyDynamicAudio(i);
	}

	#if defined AD_OnFilterScriptExit
		return AD_OnFilterScriptExit();
	#else
		return 1;
	#endif
}

public OnGameModeExit()
{
	for (new i = 0; i < MAX_DYNAMIC_AUDIO; i ++)
	{
		if (s_DynamicAudio[i][e_AudioUsed] == 0)
			continue;
		
		DestroyDynamicAudio(i);
	}

	#if defined AD_OnGameModeExit
		return AD_OnGameModeExit();
	#else
		return 1;
	#endif
}

public OnPlayerConnect(playerid)
{
	s_PlayersAudio[playerid] = INVALID_AUDIO_ID;

	#if defined AD_OnPlayerConnect
		return AD_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	s_PlayersAudio[playerid] = INVALID_AUDIO_ID;
	
	#if defined AD_OnPlayerDisconnect
		return AD_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

stock CreateDynamicAudio(url[], Float:x, Float:y, Float:z, Float: distance = 1.0, vehicle = 0, worldid = -1, interiorid = -1)
{
	for (new i = 0; i < MAX_DYNAMIC_AUDIO; i ++)
	{
		if (!s_DynamicAudio[i][e_AudioUsed])
		{
			s_DynamicAudio[i][e_AudioUsed] = 1;
			format(s_DynamicAudio[i][e_AudioUrl], 128, url);
			s_DynamicAudio[i][e_AudioX] = x;
			s_DynamicAudio[i][e_AudioY] = y;
			s_DynamicAudio[i][e_AudioZ] = z;
			s_DynamicAudio[i][e_AudioVW] = worldid;
			s_DynamicAudio[i][e_AudioInt] = interiorid;
			s_DynamicAudio[i][e_AudioDistance] = distance;
			s_DynamicAudio[i][e_AudioVehicle] = vehicle;
			// Timer used for update checking.
			s_DynamicAudio[i][e_AudioTimer] = SetTimerEx("OnAudioUpdate", AUDIO_TICK_RATE, true, "i", i);
			return i;
		}
	}
	return INVALID_AUDIO_ID;
}

stock IsValidDynamicAudio(audioid)
{
	if(audioid >= 0 && audioid < MAX_DYNAMIC_AUDIO && s_DynamicAudio[audioid][e_AudioUsed] != 0)
	{
		return 1;
	}
	return 0;
}

stock DestroyDynamicAudio(audioid)
{
	if(audioid >= 0 && audioid < MAX_DYNAMIC_AUDIO && s_DynamicAudio[audioid][e_AudioUsed] != 0)
	{
		s_DynamicAudio[audioid][e_AudioUsed] = 0;
		s_DynamicAudio[audioid][e_AudioUrl] = EOS;
		s_DynamicAudio[audioid][e_AudioX] = 0.0;
		s_DynamicAudio[audioid][e_AudioY] = 0.0;
		s_DynamicAudio[audioid][e_AudioZ] = 0.0;
		s_DynamicAudio[audioid][e_AudioVW] = -1;
		s_DynamicAudio[audioid][e_AudioInt] = -1;
		KillTimer(s_DynamicAudio[audioid][e_AudioTimer]);
		 
		#if defined _inc_foreach
		foreach (new i : Player)
		#else
		for (new i = 0, j = GetPlayerPoolSize(); i <= j; ++i)
		#endif
		{
			if(s_PlayersAudio[i] == audioid)
			{
				s_PlayersAudio[i] = INVALID_AUDIO_ID;
				StopAudioStreamForPlayer(i);
				break;
			}
		}
		return 1;
	}
	return 0;
}

stock IsDynamicAudioStreamedIn(playerid, audioid)
{
	if(audioid >= 0 && audioid < MAX_DYNAMIC_AUDIO && s_DynamicAudio[audioid][e_AudioUsed] != 0)
	{
		
		if(s_DynamicAudio[audioid][e_AudioVehicle] != 0 && GetPlayerVehicleID(playerid) == s_DynamicAudio[audioid][e_AudioVehicle])
			return 1;
		
		if(s_DynamicAudio[audioid][e_AudioVehicle] == 0 && IsPlayerInRangeOfPoint(playerid, s_DynamicAudio[audioid][e_AudioDistance], s_DynamicAudio[audioid][e_AudioZ], s_DynamicAudio[audioid][e_AudioY], s_DynamicAudio[audioid][e_AudioZ]))
		{
			if ((s_DynamicAudio[audioid][e_AudioInt] != -1 && GetPlayerInterior(playerid) != s_DynamicAudio[audioid][e_AudioInt]) || (s_DynamicAudio[audioid][e_AudioVW] != -1 && GetPlayerVirtualWorld(playerid) != s_DynamicAudio[audioid][e_AudioVW]))
			{
				return 0;
			}
			return 1;
		}	
	}
	return 0;
}

forward OnAudioUpdate(audioid);
public OnAudioUpdate(audioid)
{
	#if defined _inc_foreach
	foreach (new i : Player)
	#else
	for (new i = 0, j = GetPlayerPoolSize(); i <= j; ++i)
	#endif
	{
		if(s_PlayersAudio[i] == audioid && IsDynamicAudioStreamedIn(i, audioid) == 0)
		{
			s_PlayersAudio[i] = INVALID_AUDIO_ID;
			StopAudioStreamForPlayer(i);
			break;
		}
		else if(s_PlayersAudio[i] == 0 || IsDynamicAudioStreamedIn(i, audioid) != 0)
		{
			PlayAudioStreamForPlayer(i, s_DynamicAudio[audioid][e_AudioUrl]);
			s_PlayersAudio[i] = i;
			break;
		}
	}
}


#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit AD_OnFilterScriptExit

#if defined AD_OnFilterScriptExit
	forward AD_OnFilterScriptExit();
#endif

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit AD_OnGameModeExit

#if defined AD_OnGameModeExit
	forward AD_OnGameModeExit();
#endif


#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect AD_OnPlayerConnect

#if defined AD_OnPlayerConnect
	forward AD_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect AD_OnPlayerDisconnect

#if defined AD_OnPlayerDisconnect
	forward AD_OnPlayerDisconnect(playerid, reason);
#endif

/*
native CreateDynamicAudio(url[], Float:x, Float:y, Float:z, Float: distance = 1.0, vehicle = 0, worldid = -1, interiorid = -1);
native DestroyDynamicAudio(audioid);
native IsValidDynamicAudio(audioid);
*/