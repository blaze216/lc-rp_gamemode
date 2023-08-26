// 87  - 9314 (28)
// 100 - 7302 (28)
// - 11455 (28)

#define     MAX_BILLBOARDS     (30)

enum dyBollard
{
	bbObject,

    bbID,
    bbText[100],
    bbRentBy,
    bbRentDate,
    bbRentCost,
	Float: bbPosX,
	Float: bbPosY,
	Float: bbPosZ,
	Float: bbPosRX,
	Float: bbPosRY,
	Float: bbPosRZ,
	bbInt,
	bbVW,
	bbModel,
	bool:  bbActive,
}
new BillboardInfo[MAX_BILLBOARDS][dyBollard];

new billboard_obj[] = {
   7302,
   9314
};

/*

    8326,
    8423,
    7310,
    7309,
    7302,
    7303,
    8330,
    7301,
    8332,
    8328,
    8239,
    8730,
    8408,
    7905,
    7904,
    7900,
    7901,
    7907,
    7908,
    9188,
    9191,
    7906,
    9190,
    7912,
    7913,
    7909,
    7911,
    7914,
    7915,
    9184,
    9185,
    9186,
    9187,
    9189,
    7903

*/