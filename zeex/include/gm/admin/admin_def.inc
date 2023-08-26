#define ADMIN_LEVEL_1       (1) // game admin
#define ADMIN_LEVEL_2       (2) // senior
#define ADMIN_LEVEL_3       (3) // lead
#define HIGH_ADMIN_LEVEL    (4) //leadership
#define DEVELOPER_LEVEL     (5) //developer

// Spectate defines
#define INVALID_SPECTATE_TYPE				(0)
#define SPECTATE_TYPE_PLAYER				(1)
#define SPECTATE_TYPE_VEHICLE				(2)

// Flymode
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

new g_ModelsAwaiting = 0;

// noclip
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