#define			 	MAX_METERS 					100 	
// Maximum Parking Meters that can be made in the server.
#define 			CASH_PARKING        		150   	
// $10 per minutes


enum ParkingMeters
{
	parkObject,
	parkVehicle,
	Text3D:parkLabel,
	parkID,
	Float:parkX,
	Float:parkY,
	Float:parkZ,
	Float:parkA,
	bool:parkAvailable
};

new pMeter[MAX_METERS][ParkingMeters];
