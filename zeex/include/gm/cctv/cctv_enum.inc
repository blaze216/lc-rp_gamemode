enum CCTV_ENUM
{
	tvID,
	tvObject,
	tvCollision,
	tvName[32],
	tvInt,
	tvVW,
	Float:tvPosX,
	Float:tvPosY,
	Float:tvPosZ,
	Float:tvPosRX,
	Float:tvPosRY,
	Float:tvPosRZ,
    tvBreak,
    Text3D:tvText,
	tvSignal,
	tvSignalTime,
	tvObjectOn,
}
new CCTVInfo[MAX_CCTV][CCTV_ENUM];


enum PLAYER_CAMERA_ENUM
{
	pc_used,
	pc_time,
}
new PCamera[MAX_PLAYERS][MAX_CCTV][PLAYER_CAMERA_ENUM];