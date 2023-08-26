#define     TRASH_BAG_VALUE     (125)    	// value of a collected trash bag (default: 125)
#define     REFILL_TIME         (300)   	// trash container refill time - in seconds (default: 300)
#define     ATTACHMENT_INDEX    (4)     	// for setplayerattachedobject (default: 4)
#define     TRASH_LIMIT         (10)    	// trashmaster capacity (default: 10)
#define     MAX_TRASHES         (100)       // max trashes
#define     MAX_FACTORIES       (3)         // max factories

#define		TYPE_DUMPSTER		(1)			// type of trash
#define 	TYPE_BIN			(2)			// type of trash

enum	e_trashdata
{
	TrashID,
	TrashType,
	Float: TrashX,
	Float: TrashY,
	Float: TrashZ,			
	Float: TrashRZ,			
	TrashObject,			
	Text3D: TrashLabel,		
	TrashLevel,				
	TrashTimer				
}

enum    e_factorydata
{
	FactoryID,
    FactoryName[32],
	Float: FactoryX,
	Float: FactoryY,
	Float: FactoryZ,
	FactoryCurrent,
	FactoryCP,
	Text3D: FactoryLabel
}

new	TrashData[MAX_TRASHES][e_trashdata],
	FactoryData[MAX_FACTORIES][e_factorydata],
    LoadedTrash[MAX_VEHICLES];

new
	bool: HasTrash[MAX_PLAYERS],
	TrashCP[MAX_PLAYERS] = {-1, ...},
    FactoryIcons[MAX_PLAYERS][sizeof(FactoryData)],
    //PlayerBar: CapacityBar[MAX_PLAYERS],
    PlayerText: CapacityText[MAX_PLAYERS];

