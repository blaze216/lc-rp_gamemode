#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03

#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1

#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8

enum noclipenum
{
	cameramode,
	flyobject,
	mode,
	lrold,
	udold,
	lastmove,
	Float:accelmul
}
new noclipdata[MAX_PLAYERS][noclipenum];

new bool:FlyMode[MAX_PLAYERS];

#define InFlyMode(%0) FlyMode[%0]

stock IsFlyMode(playerid) { return noclipdata[playerid][cameramode]; }

alias:specmode("flymode");
CMD:specmode(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1) return SendNotAdmin(playerid);
	if(FlyMode[playerid]) CancelFlyMode(playerid);
	else StartFlyMode(playerid);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(noclipdata[playerid][cameramode] == CAMERA_MODE_FLY)
	{
		new keys,ud,lr;
		GetPlayerKeys(playerid,keys,ud,lr);
		

		if(noclipdata[playerid][mode] && (GetTickCount() - noclipdata[playerid][lastmove] > 100))
		{
		    MoveCamera(playerid);
		}

		if(noclipdata[playerid][udold] != ud || noclipdata[playerid][lrold] != lr)
		{
			if((noclipdata[playerid][udold] != 0 || noclipdata[playerid][lrold] != 0) && ud == 0 && lr == 0)
			{
				StopPlayerObject(playerid, noclipdata[playerid][flyobject]);
				noclipdata[playerid][mode]      = 0;
				noclipdata[playerid][accelmul]  = 0.0;
			}
			else
			{

				noclipdata[playerid][mode] = GetMoveDirectionFromKeys(ud, lr);

				MoveCamera(playerid);
			}
		}
		noclipdata[playerid][udold] = ud; noclipdata[playerid][lrold] = lr; // Store current keys pressed for comparison next update
	}
	return CallLocalFunction("Specmode_OnPlayerUpdate", "d", playerid);
}


stock MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);

	if(noclipdata[playerid][accelmul] <= 1) noclipdata[playerid][accelmul] += ACCEL_RATE;

	new Float:speed = MOVE_SPEED * noclipdata[playerid][accelmul];

	new Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(noclipdata[playerid][mode], CP, FV, X, Y, Z);
	MovePlayerObject(playerid, noclipdata[playerid][flyobject], X, Y, Z, speed);

	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

stock SetFlyModePos(playerid, Float:x, Float:y, Float:z)
{
    SetPlayerObjectPos(playerid, noclipdata[playerid][flyobject], x, y, z);
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}


stock GetNextCameraPosition(move_mode, const Float:CP[3], const Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
    #define OFFSET_X (FV[0]*6000.0)
	#define OFFSET_Y (FV[1]*6000.0)
	#define OFFSET_Z (FV[2]*6000.0)
	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
}

stock CancelFlyMode(playerid)
{
	SendServerMessage(playerid, "Spec Mode passif.");
	new Float:x, Float:y, Float:z;
	GetPlayerCameraPos(playerid, x, y, z);

	//SetTimerEx("DelaySetPos", 2000, false, "ifff", playerid, x, y, z);

	FlyMode[playerid] = false;
	CancelEdit(playerid);
	TogglePlayerSpectating(playerid, false);

	DestroyPlayerObject(playerid, noclipdata[playerid][flyobject]);
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	SetPlayerPos(playerid, x, y, z);
	return 1;
}

stock StartFlyMode(playerid, oyuncuid = -1)
{
	SendServerMessage(playerid, "Spec Mode etkin.");
	new Float:X, Float:Y, Float:Z;
	if(oyuncuid == -1) GetPlayerPos(playerid, X, Y, Z);
	else {
		if(StaffInfo[playerid][sSpecID] != INVALID_PLAYER_ID) pc_cmd_specoff(playerid, "");
		GetPlayerPos(oyuncuid, X, Y, Z);
	}
	noclipdata[playerid][flyobject] = CreatePlayerObject(playerid, 19300, X, Y, Z, 0.0, 0.0, 0.0);

	TogglePlayerSpectating(playerid, true);
	AttachCameraToPlayerObject(playerid, noclipdata[playerid][flyobject]);

	FlyMode[playerid] = true;
	noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;
	return 1;
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate Specmode_OnPlayerUpdate

forward Specmode_OnPlayerUpdate(playerid);