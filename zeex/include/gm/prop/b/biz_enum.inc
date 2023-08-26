enum BIZ_ENUM
{
	bizID,
	Text3D:bizLabelDDoor,
	Float:bizPosX,
	Float:bizPosY,
	Float:bizPosZ,
	Float:bizExitX,
	Float:bizExitY,
	Float:bizExitZ,
	Float:bizSpawn[4], 	//-------- Dealership --------// 
	bizSpawnInt, 		//-------- Dealership --------// 
	bizSpawnVW, 		//-------- Dealership --------// 
	bizPickUp,
	bizName[32],
	bizInfo[32],
	bizMes[128],
	bizOwner[MAX_PLAYER_NAME],
	bizOwnerID,
	bizLocked,
	bizPrice,
	bizFreeze,
	bizLevelbuy,
	bizExitInt,
	bizExitVW,
	bizPosInt,
	bizPosVW,
	bizCash,
	bizType,
	bizEntrance,
	bizRadio,
	bizRadioOn,
	bizRadioURL[156],
	bizDDoor,
	bizProductPrice[12],
	bizProduct,
	bizBuyPrice,

	bFireTimer,

	bFurniture,
	bOutsideFurniture,
	Float: bFurnitureRadius

	/*bizPrName[12][32],
	bizPrItem[12],
	bizPrPrice[12]*/
};
new BizInfo[MAX_BIZ][BIZ_ENUM];

#define MAX_WORK_SPACE 10

enum BIZ_WORKERS
{
	bizJobOn,
	bizWorker[24],
	bizPosition[24]
};
new BizWorkers[MAX_BIZ][MAX_WORK_SPACE][BIZ_WORKERS];