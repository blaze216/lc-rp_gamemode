enum TELES_ENUM
{
	aID,
	Float:telesPosX,
	Float:telesPosY,
	Float:telesPosZ,
	telesInt,
	telesMapName[32],
	telesOn,
	telesType
};
new AdminTeles[MAX_INTERIORS][TELES_ENUM];


// TELES TYPES //
#define 		HOUSE_SMALL_INT_TYPE 	0
#define 		HOUSE_MID_INT_TYPE 		1
#define 		HOUSE_BIG_INT_TYPE 		2
#define 		ENTRANCES_INT_TYPE 		3
#define 		BUSSINESS_INT_TYPE 		4
#define         GPS_TELE_TYPE           10

enum E_Staff {
    sSpecID,
    sSpecType,
    bool:sSpec,
    Float:sSpecX,
    Float:sSpecY,
    Float:sSpecZ,
    Float:sSpecA,
    sSpecInterior,
    sSpecWorld
}

new StaffInfo[MAX_PLAYERS][E_Staff];

enum RENTAL_ENUM
{
	rentalID,
	rentalType,
	rentalJob,
	Float:rentalX,
	Float:rentalY,
	Float:rentalZ,
	rentalInterior,
	rentalWorld,
	rentalPickup,
	Text3D: rental3D
};
new RentalPoint[MAX_RENTAL][RENTAL_ENUM];
new Iterator:RentalPoints<MAX_RENTAL>;