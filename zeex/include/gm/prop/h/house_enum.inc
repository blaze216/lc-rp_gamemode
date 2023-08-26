enum HOUSE_ENUM
{
	hID,
	Text3D:hLabelDDoor,
	hCheckPoint,
	hPickup,
	//hExtCheckPoint,
	hExtPickup,

	Float:hPosX,
	Float:hPosY,
	Float:hPosZ,
	hPosInt,
	hPosVW,
	Float:hExitX,
	Float:hExitY,
	Float:hExitZ,
	hExitInt,
	hExitVW,

	Float:hExtX[2],
	Float:hExtY[2],
	Float:hExtZ[2],
	hExtInt[2],
	hExtVW[2],

	hOwner[MAX_PLAYER_NAME],
	hOwnerID,
	hLocked,
	hPrice,
	hLevelbuy,
	hCash,

	hApart,

	hRobbed, // hRobbed = gettime() + 12 * 3600;
	hRobber, // Who? ID  30 sec = 10% safe AND if 3 policer online and non afk
	hAlarmA,
	hAlarmTime,
	Text3D:hAText,

	Float:hCheckPosX,
	Float:hCheckPosY,
	Float:hCheckPosZ,
	hRadio,
	hLock,
	hAlarm,
	hDoor,
	hDDoor,
	hRadioOn,
	hRadioURL[156],
	hClass,
	hHeal,
	hHealAmount,
	hCupboard,

	hFireTimer,

	hFurniture,
	hOutsideFurniture,
	Float: hFurnitureRadius /*ALTER TABLE `houses` ADD `furniture_radius` FLOAT NOT NULL DEFAULT '7.0' ;*/
};
new HouseInfo[MAX_HOUSES][HOUSE_ENUM];
