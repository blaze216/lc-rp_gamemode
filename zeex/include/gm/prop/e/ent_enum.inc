enum ENTRANCE_ENUM
{
	eID,
	Float: eEnterX,
	Float: eEnterY,
	Float: eEnterZ,
	Float: eEnterA,
	Float: eExitX,
	Float: eExitY,
	Float: eExitZ,
	Float: eExitA,
	eText[128],
	gpsText[128],
	eEnterInt,
	eEnterVW,
	eExitInt,
	eExitVW,
	eEnterPickup,
	eExitPickup,
	eLocked,
	eFaction,
	eVehicle,
	entranceOn
}

new EntranceInfo[MAX_ENTRANCE][ENTRANCE_ENUM];