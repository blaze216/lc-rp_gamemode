enum ITEM_ENUM
{
	itemModel,
	itemType,
	itemSize,
	itemName[32],
	itemQ,
	itemSplit,
	itemFloat,
	itemID
};

//âñå ïðåäìåòû
#define MAX_ITEM_LIST 120
new inventory_items[MAX_ITEM_LIST][ITEM_ENUM] = 
{
	{0, 	ITEM_TYPE_NONE, 				ITEM_SIZE_NONE,		"Belirsiz", 					0,0,0, 0},
	{331, 	ITEM_TYPE_WEAPON, 				ITEM_SIZE_MEDIUM,	"Cassette", 					0,0,0, 1},
	{333,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Golf sopasý ", 		0,0,0, 2},
	{334,	ITEM_TYPE_WEAPON, 				ITEM_SIZE_MEDIUM,	"Cudgel", 					0,0,0, 3},
	{335,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Býçak",	 					0,0,0, 4},
	{336,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Sopa", 		0,0,0, 5},
	{337,  	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Kürek", 					0,0,0, 6},
	{338,	ITEM_TYPE_WEAPON, 				ITEM_SIZE_BIG,		"Cue",						0,0,0, 7},
	{339,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Katana",					0,0,0, 8},
	{341,	ITEM_TYPE_WEAPON,				ITEM_SIZE_VBIG,		"Testere", 				0,0,0, 9},
	{321,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Lilac dildo", 			0,0,0, 10},
	{322,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Dildo", 					0,0,0, 11},
	{323,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Vibratör", 				0,0,0, 12},
	{324,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Gümüþ vibratör", 	0,0,0, 13},
	{325,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Çiçek", 					0,0,0, 14},
	{326,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Cane", 					0,0,0, 15},
	{342,	ITEM_TYPE_WEAPON,				ITEM_SIZE_SMALL,	"El Bombasý", 					0,1,0, 16},
	{343,	ITEM_TYPE_WEAPON,				ITEM_SIZE_SMALL,	"Gaz", 						0,1,0, 17},
	{344,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Molotof", 		0,1,0, 18},
	{2656,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Araç stickerý",	0,1,0, 19},
	{19942,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Telsiz", 					0,1,0, 20},
	{19801,	ITEM_TYPE_MISC, 				ITEM_SIZE_MEDIUM,	"Maske", 					0,1,0, 21},
	{346,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"M1911", 					0,0,0, 22},
	{347,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"M1911 (susturuculu)", 	0,0,0, 23},
	{348,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Desert Eagle", 			0,0,0, 24},
	{349,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Shotgun", 					0,0,0, 25},
	{350,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Sawn-off Shotgun", 		0,0,0, 26},
	{351,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"Combat Shotgun", 			0,0,0, 27},
	{352,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Uzi", 						0,0,0, 28},
	{353,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"MP5", 						0,0,0, 29},
	{355,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"AK-47", 					0,0,0, 30},
	{356,	ITEM_TYPE_WEAPON,				ITEM_SIZE_BIG,		"M4", 						0,0,0, 31},
	{372,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Tec-9", 					0,0,0, 32},
	{357,	ITEM_TYPE_WEAPON,				ITEM_SIZE_VBIG,		"Country Rifle", 			0,0,0, 33},
	{358,	ITEM_TYPE_WEAPON,				ITEM_SIZE_VBIG,		"Sniper Rifle", 			0,0,0, 34},
	{19094,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Burger", 					0,1,0, 35},
	{2702,	ITEM_TYPE_FOOD, 				ITEM_SIZE_MEDIUM,	"Pizza", 					0,1,0, 36},
	{2663,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Tavuk", 		0,1,0, 37},
    {19346, ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Hot dog", 					0,1,0, 38},
	{1650,	ITEM_TYPE_MISC,					ITEM_SIZE_VBIG,		"Bidon", 				0,1,0, 39},
	{2226,	ITEM_TYPE_MISC,					ITEM_SIZE_VBIG,		"Boombox", 					0,1,0, 40},
	{365,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Sprey Kutusu", 				50,0,0, 41},
	{366,	ITEM_TYPE_WEAPON,				ITEM_SIZE_VBIG,		"Yangýn Söndürücü", 			50,0,0, 42},
	{367,	ITEM_TYPE_WEAPON,				ITEM_SIZE_MEDIUM,	"Kamera", 				50,0,0, 43},
	{2040,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Susturucu", 				0,0,0, 44},
	{2040,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Dürbün", 		0,0,0, 45},
	{371, 	ITEM_TYPE_WEAPON,				ITEM_SIZE_VBIG,		"Paraþüt", 					0,0,0, 46},
	{19998,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Çakmak", 				0,1,0, 47},
	{19897,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Sigara", 				0,1,0, 48},
	{1906,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Zar", 			0,1,0, 49},
	{11748,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Oyun Kartý", 			0,1,0, 50},
	{3027,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Kalem", 					0,1,0, 51},
	{19921,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Maymuncuk", 					0,1,0, 52},
	{2041,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Kovan", 					0,1,0, 53},
	{19792,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Toz", 					0,1,0, 54},
	{19792,	ITEM_TYPE_NONE,					ITEM_SIZE_SMALL, 	"Ceset Torbasý", 			0,1,0, 55},
    {2958,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Bira", 					0,1,0, 56},
    {1668,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Vodka", 					0,1,0, 57},
    {1546,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Cola", 					0,1,0, 58},
    {1455,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Su", 					0,1,0, 59},
    {1520,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Viski", 					0,1,0, 60},
    {19820,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Konyak", 					0,1,0, 61},
    {19346,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Soda", 					0,1,0, 62},
    {1664,	ITEM_TYPE_FOOD,					ITEM_SIZE_MEDIUM,	"Þarap", 					0,1,0, 63},
    {1664,	ITEM_TYPE_SEEDS,				ITEM_SIZE_SMALL,	"Kenevir Tohumu", 			0,1,0, 64},
    {1578,	ITEM_TYPE_DRUGS,				ITEM_SIZE_SMALL, 	"Týbbi esrar", 	0,1,1, 65},
    {1578, 	ITEM_TYPE_DRUGS,				ITEM_SIZE_SMALL,	"Marijuana", 				0,1,1, 66},
	{1579,	ITEM_TYPE_DRUGS,				ITEM_SIZE_SMALL,	"Uyuþturucu", 				0,1,1, 67},
    {1576,	ITEM_TYPE_NONE,					ITEM_SIZE_SMALL,	"Belirsiz", 					0,0,0, 68},
    {1577,	ITEM_TYPE_NONE,					ITEM_SIZE_SMALL,	"Belirsiz", 					0,0,0, 69},
    {1575,	ITEM_TYPE_NONE,					ITEM_SIZE_SMALL,	"Belirsiz", 					0,0,0, 70},
    {1664,	ITEM_TYPE_NONE,					ITEM_SIZE_SMALL,	"Belirsiz", 					0,0,0, 71},
    {1664,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Dietil",					0,1,0, 72},
    {1650,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Alkali", 					0,1,1, 73},
    {1664,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Hidroklorik Asit", 			0,1,1, 74},
    {11736,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Ýlk Yardim Kiti", 					0,1,0, 75},
    {19920,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"XM Radio", 				0,1,0, 76},
    {19878,	ITEM_TYPE_MISC,					ITEM_SIZE_BIG,		"Kaykay", 				0,0,0, 77},
	{2814, 	ITEM_TYPE_INSIDEABLE_OBJECT,	ITEM_SIZE_BIG,		"Pizza Kutusu",			0,0,0, 78},
	{2663,  ITEM_TYPE_INSIDEABLE_OBJECT, 	ITEM_SIZE_MEDIUM, 	"Paket 'Cluckin' Bell'",	0,0,0, 79},
	{1664, 	ITEM_TYPE_SEEDS, 				ITEM_SIZE_SMALL,	"Koka Tohumu",				0,1,0, 80},
	{1664, 	ITEM_TYPE_SEEDS,				ITEM_SIZE_SMALL, 	"Haþhaþ Tohumu",				0,1,0, 81},
	{2041, 	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	".45 ACP", 					7,0,0, 82}, 	// M1911 //82
    {2041, 	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	".45 ACP .ext", 			14,0,0, 83}, 	// M1911 //83
    {2041, 	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	".50AE", 					7,0,0, 84},	// DEAGLE //84
    {2041, 	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	".50AE .ext", 				14,0,0, 85},	// DEAGLE //85
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"12-G BIRDSHOT", 			6,0,0, 86},	// SHOTGUN //86
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"12-G BUCKSHOT", 			6,0,0, 87}, 	// SHOTGUN //87
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"12-G SLUG", 				6,0,0, 88},	// SHOTGUN //88
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"12-G BEANBAG", 			6,0,0, 89}, 	// SHOTGUN //89 //ðåçèíîâûå
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"9x19mm", 					30,0,0, 90}, 	// MAC/TEC //90
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"9x19mm .ext", 				60,0,0, 91}, 	// MAC/TEC //91
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"7.62x39mm", 				30,0,0, 92}, 	// AK47 //92
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"5.56x45mm", 				30,0,0, 93}, 	// M4A1 //93
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"7.62x39mm T", 				30,0,0, 94}, 	// AK47 //94
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"5.56x45mm T", 				30,0,0, 95}, 	// M4A1 //95
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"7.62x51mm", 				4,0,0, 96},	// SNIPER / RIFLE //96
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"7.62x39mm (drum)", 		80,0,0, 97},	// AK47 //97
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"5.56x45mm (drum)", 		60,0,0, 98}, 	// M4 //98
    {2041,	ITEM_TYPE_AMMO,					ITEM_SIZE_SMALL,	"5.56x45mm (plastik)",	 	30,0,0, 99}, 	// M4 //99
	{19921,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Alet Çantasý",				0,0,0, 100},
	{19257,	ITEM_TYPE_MISC,					ITEM_SIZE_SMALL,	"Sahte numara",			0,0,0, 101},
	{371,  ITEM_TYPE_INSIDEABLE_OBJECT, 	ITEM_SIZE_MEDIUM, 	"Sýrt Cantasi",					0,0,0, 102},
	{2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM,  	"Kýrmýzý fosfor",			0,1,1, 103},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Vinilbenzil alkol",	0,1,1, 104},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Metilamin",				0,1,1, 105},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Heliotropin",        	0,1,1, 106},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Efedrin",					0,1,1, 107},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Potasyum permanganat",		0,1,1, 108},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Kloroform",				0,1,1, 109},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Eter",           			0,1,1, 110},
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Hidrojen klorür",       	0,1,1, 111}, 
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Metanol",        	   		0,1,1, 112}, 
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Liserjik asit",			0,1,1, 113},	
    {2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Ekgonin",           		0,1,1, 114},
	{2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Koka yapraklarý",        		0,1,1, 115},
	{2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Mak",		         		0,1,1, 116},
	{2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Kurutulmuþ koka yapraklarý ",		0,1,1, 117},
	{2709, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"Kurutulmuþ afyon ",				0,1,1, 118},
    {19897,	ITEM_TYPE_MISC,					ITEM_SIZE_MEDIUM,	"Küba purosu", 				0,1,0, 119}	
};

enum DROP_ENUM
{
	dropBDID,
	dropID,
	dropAmount,
	dropEx,
	dropS,
	Float:dropQFloat,
	dropInvName[16],
	dropObject,
	Float:dropPosX,
	Float:dropPosY,
	Float:dropPosZ,
	Float:dropPosRX,
	Float:dropPosRY,
	Float:dropPosRZ,
	dropInt,
	dropVW,
	dropTime
}
new ItemDrop[MAX_ITEM_DROPS][DROP_ENUM];

enum FOOD_DROPS_ENUM
{
    foodDropped,
	foodObject,
	foodModel,
	Float:foodPosX,
	Float:foodPosY,
	Float:foodPosZ,
	foodVW,
	foodInt,
	foodTime
}
new FoodDrop[MAX_FOOD_DROPS][FOOD_DROPS_ENUM];