enum CARGO_OBJECT_ENUM
{
	oOn,
	oObj,
	Text3D:oLabel,
	Float:oX,
	Float:oY,
	Float:oZ,
	oInt,
	oVW,
	oProduct
}

new CargoObject[MAX_CARGO_OBJ][CARGO_OBJECT_ENUM];

enum TRUCK_CARGO_ENUM
{
	tID,
	tType,
	tName[64],
	tStorage,
	tStorageSize,
	tPrice,
	tProductID,
	tProductAmount,
	tPack,
	tGps,
	tLocked,
	Float: tPosX,
	Float: tPosY,
	Float: tPosZ,
	Text3D:tLabel,
	tPickup,
	tOn,
	tResult
}

new TruckCargo[MAX_TRUCK_CARGO][TRUCK_CARGO_ENUM];

enum E_Job_Data
{
    bool:jActive,
    jType,
    jLocationID,
    jFee,
    jStartDate
}

new CharacterJob[MAX_PLAYERS][E_Job_Data];
new JobFinished[MAX_PLAYERS];
new Float:DeliveryHiringX = 2260.3518,
    Float:DeliveryHiringY = -2353.4138,
    Float:DeliveryHiringZ = 13.5469;

enum E_DeliveryL
{
    dItem[32],
    dDescription[64],
    dWaitTime,
	Float: deliveryX,
	Float: deliveryY,
    Float: deliveryZ
}