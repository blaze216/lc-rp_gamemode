#define NT_DISTANCE 25.0
#define ITEM_PER_PAGE                         (25)
new Text3D:cNametag[MAX_PLAYERS];
new YuruyusTimer[MAX_PLAYERS];

new male_skins[177] =
{
    1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 37, 42, 43, 44, 46, 47, 48, 49, 50,
	57, 58, 59, 60, 61, 62, 66, 67, 68, 72, 73, 78, 79, 82, 83, 84, 86, 94, 95, 96,
	98, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115,
	116, 117, 118, 120, 121, 122, 123, 124, 125, 126, 127, 128, 132, 133, 134, 135,
	136, 137, 142, 143, 144, 146, 147, 153, 154, 155, 156, 158, 159, 160, 161, 162,
 	168, 170, 161, 173, 174, 175, 176, 177, 179, 180, 181, 182, 183, 184, 185, 186,
	187, 188, 189, 200, 202, 206, 208, 210, 212, 213, 217, 220, 221, 222, 223, 227, 228,
	229, 230, 234, 235, 236, 239, 240, 241, 242, 247, 248, 249, 250, 254, 255, 258, 259,
	260, 261, 262, 268, 269, 270, 271, 272, 273, 289, 290, 291, 292, 293, 294, 295,
	296, 297, 299

};

new female_skins[64] =
{
    55, 56, 63, 64, 65, 69, 75, 76, 77, 85,
	87, 88, 89, 90, 91, 93, 129, 130, 131, 141, 148, 150, 151, 152, 157, 169, 172, 178,
	190, 191, 192, 193, 194, 195, 198, 201, 207, 211, 214, 215, 216, 219, 224, 225, 226,
 	233, 237, 238, 243, 244, 245, 256, 263, 9, 10, 11, 12, 13, 31, 39, 40, 41, 53, 54
};

// anti cbug
new bool:pCBugging[MAX_PLAYERS];
new ptmCBugFreezeOver[MAX_PLAYERS];
new ptsLastFiredWeapon[MAX_PLAYERS];

// anti bunny
new InSprung[MAX_PLAYERS] = 0;
new TimerIDSprung;

new cameraSession[MAX_PLAYERS];

#define YURUYUS_NORMAL     				(1)
#define YURUYUS_PED       				(2)
#define YURUYUS_GANGSTER   				(3)
#define YURUYUS_GANGSTER2  				(4)
#define YURUYUS_YASLI       			(5)
#define YURUYUS_SISKO_YASLI   			(6)
#define YURUYUS_SISKO      				(7)
#define YURUYUS_KADIN     				(8)
#define YURUYUS_KADIN2    				(9)
#define YURUYUS_FAHISE    				(10)
#define YURUYUS_FAHISE2   				(11)
#define YURUYUS_SARHOS     				(12)
#define YURUYUS_KOR     				(13)
#define YURUYUS_ARMED     				(14)