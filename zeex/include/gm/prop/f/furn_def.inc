#define IsFurnitureFirable(%0) (%0 < 5 && %0 == 7 && %0 == 8 && %0 == 15 && %0 == 29)

#define MAX_FURNITURE_LIST      20
#define MAX_FURNITURE 			500

enum FURNITURE_ENUM
{
	fID,
	fModel,
	fObject,
	fName[64],
	//fBuildingID,
	fInterior,
	fVirtualWorld,
	fMarketPrice,
	Float:fPosX,
	Float:fPosY,
	Float:fPosZ,
	Float:fPosRX,
	Float:fPosRY,
	Float:fPosRZ,
	fLocked,
	fOpened,
	fOn,
	fTexture[5],
	fCategory,

	ChemIdx
}

new HFurn[MAX_HOUSES][MAX_FURNITURE][FURNITURE_ENUM];
new BFurn[MAX_BIZ][MAX_FURNITURE][FURNITURE_ENUM];
new GFurn[MAX_GARAGES][MAX_FURNITURE][FURNITURE_ENUM];
//new TFurn[MAX_TRAILERS][MAX_FURNITURE][FURNITURE_ENUM];