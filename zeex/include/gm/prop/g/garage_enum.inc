enum GARAGE_ENUM
{
	garageID,
	garageOwner,
	garageOwnerName[MAX_PLAYER_NAME],
	
	garageHouse,
	garageBiz,
	
	garageDDoor,
	Text3D:garageLabelDDoor,
	
	garagePrice,
	garageLocked,
	Float: garageVeh_Enter[4],
	Float: garageVeh_Exit[4],
	garageEnterInt,
	garageEnterVW,
	Float: garagePlayer_Enter[3],
	garageExitInt,
	garageExitVW,
	Float: garagePlayer_Exit[3],
	garageCP,

	gFireTimer,

	gFurniture,
	gOutsideFurniture,
	Float: gFurnitureRadius
}

new GarageInfo[MAX_GARAGES][GARAGE_ENUM];