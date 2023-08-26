#define PAYPHONE_STATE_NONE 	0
#define PAYPHONE_STATE_INCALL 	1
#define PAYPHONE_STATE_RINGING  2

enum PAYPHONE_ENUM
{
	phID,
	phType,
	Float: phX,
	Float: phY,
	Float: phZ,
	Float: phRX,
	Float: phRY,
	Float: phRZ,
	phInt,
	phVW,
	phNumber,

	//Local
	phObj,
	Text3D:phLabel,
	phUsed,
	phCaller,
	bool:pp_exist,
	phRing,
	phState
	
}
new PayphoneInfo[MAX_PAYPHONES][PAYPHONE_ENUM];
