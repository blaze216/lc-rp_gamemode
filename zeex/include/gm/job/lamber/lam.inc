#include 	<a_samp>
#include    <evf>           // by Emmet_ - http://forum.sa-mp.com/showthread.php?t=486060
#include    <izcmd>         // by Yashas - http://forum.sa-mp.com/showthread.php?t=576114
#include    <progress2>     // by [HLF]Southclaw - http://forum.sa-mp.com/showthread.php?t=537468
#include    <sqlitei>       // by Slice - http://forum.sa-mp.com/showthread.php?t=303682
#include    <sscanf2>       // by Y_Less - http://forum.sa-mp.com/showthread.php?t=602923
#include    <streamer>      // by Incognito - http://forum.sa-mp.com/showthread.php?t=102865
#include    <YSI\y_iterate> // by Y_Less - http://forum.sa-mp.com/showthread.php?t=570884

#define     MAX_TREES       (100)   // tree limit
#define     MAX_LOGS        (300)   // dropped log limit
#define     MAX_BUYERS      (20)    // log buyer limit

#define     CUTTING_TIME    (8)		// required seconds to cut a tree down (Default: 8)
#define     LOG_LIMIT     	(10)    // how many logs a player can load to a bobcat (if you change this, don't forget to modify LogAttachOffsets array) (Default: 10)
#define     ATTACH_INDEX    (7)     // for setplayerattachedobject (Default: 7)
#define     TREE_RESPAWN    (300)   // required seconds to respawn a tree (Default: 300)
#define     LOG_LIFETIME	(120)   // life time of a dropped log, in seconds (Default: 120)
#define     LOG_PRICE       (50)    // price of a log (Default: 50)
#define     CSAW_PRICE      (500)  	// price of a chainsaw (Default: 500)

enum    E_TREE
{
	// loaded from db
	Float: treeX,
	Float: treeY,
	Float: treeZ,
	Float: treeRX,
	Float: treeRY,
	Float: treeRZ,
	// temp
	treeLogs,
	treeSeconds,
	bool: treeGettingCut,
	treeObjID,
	Text3D: treeLabel,
	treeTimer
}

enum    E_LOG
{
	// temp
	logDroppedBy[MAX_PLAYER_NAME],
	logSeconds,
	logObjID,
	logTimer,
	Text3D: logLabel
}

enum    E_BUYER
{
	// loaded from db
	buyerSkin,
	Float: buyerX,
	Float: buyerY,
	Float: buyerZ,
	Float: buyerA,
	// temp
	buyerActorID,
	Text3D: buyerLabel
}

new
	TreeData[MAX_TREES][E_TREE],
	LogData[MAX_LOGS][E_LOG],
	BuyerData[MAX_BUYERS][E_BUYER];
	
new
	Iterator: Trees<MAX_TREES>,
	Iterator: Logs<MAX_LOGS>,
	Iterator: Buyers<MAX_BUYERS>;

new
	LogObjects[MAX_VEHICLES][LOG_LIMIT];
	
new
	CuttingTreeID[MAX_PLAYERS] = {-1, ...},
	CuttingTimer[MAX_PLAYERS] = {-1, ...},
	PlayerBar: CuttingBar[MAX_PLAYERS] = {INVALID_PLAYER_BAR_ID, ...},
	bool: CarryingLog[MAX_PLAYERS],
	EditingTreeID[MAX_PLAYERS] = {-1, ...};

new
	Float: LogAttachOffsets[LOG_LIMIT][4] = {
	    {-0.223, -1.089, -0.230, -90.399},
		{-0.056, -1.091, -0.230, 90.399},
		{0.116, -1.092, -0.230, -90.399},
		{0.293, -1.088, -0.230, 90.399},
		{-0.123, -1.089, -0.099, -90.399},
		{0.043, -1.090, -0.099, 90.399},
		{0.216, -1.092, -0.099, -90.399},
		{-0.033, -1.090, 0.029, -90.399},
		{0.153, -1.089, 0.029, 90.399},
		{0.066, -1.091, 0.150, -90.399}
	};

new
	DB: ScriptDBHandle;

new
	DBStatement: LoadTrees,
	DBStatement: AddTree,
	DBStatement: UpdateTree,
	DBStatement: RemoveTree;
	
new
	DBStatement: LoadBuyers,
	DBStatement: AddBuyer,
	DBStatement: UpdateBuyer,
	DBStatement: RemoveBuyer;

SetPlayerLookAt(playerid, Float:x, Float:y)
{
	// somewhere on samp forums, couldn't find the source
	new Float:Px, Float:Py, Float: Pa;
	GetPlayerPos(playerid, Px, Py, Pa);
	Pa = floatabs(atan((y-Py)/(x-Px)));
	if (x <= Px && y >= Py) Pa = floatsub(180, Pa);
	else if (x < Px && y < Py) Pa = floatadd(Pa, 180);
	else if (x >= Px && y <= Py) Pa = floatsub(360.0, Pa);
	Pa = floatsub(Pa, 90.0);
	if (Pa >= 360.0) Pa = floatsub(Pa, 360.0);
	SetPlayerFacingAngle(playerid, Pa);
}

ConvertToMinutes(time)
{
    // http://forum.sa-mp.com/showpost.php?p=3223897&postcount=11
    new string[15];//-2000000000:00 could happen, so make the string 15 chars to avoid any errors
    format(string, sizeof(string), "%02d:%02d", time / 60, time % 60);
    return string;
}

GetClosestTree(playerid, Float: range = 2.0)
{
	new id = -1, Float: dist = range, Float: tempdist;
	foreach(new i : Trees)
	{
	    tempdist = GetPlayerDistanceFromPoint(playerid, TreeData[i][treeX], TreeData[i][treeY], TreeData[i][treeZ]);

	    if (tempdist > range) continue;
		if (tempdist <= dist)
		{
			dist = tempdist;
			id = i;
		}
	}

	return id;
}

GetClosestLog(playerid, Float: range = 2.0)
{
	new id = -1, Float: dist = range, Float: tempdist, Float: pos[3];
	foreach(new i : Logs)
	{
		GetDynamicObjectPos(LogData[i][logObjID], pos[0], pos[1], pos[2]);
	    tempdist = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]);

	    if (tempdist > range) continue;
		if (tempdist <= dist)
		{
			dist = tempdist;
			id = i;
		}
	}

	return id;
}

IsPlayerNearALogBuyer(playerid)
{
	foreach(new i : Buyers)
	{
	    if (IsPlayerInRangeOfPoint(playerid, 2.0, BuyerData[i][buyerX], BuyerData[i][buyerY], BuyerData[i][buyerZ])) return 1;
	}
	
	return 0;
}

Player_Init(playerid)
{
    CuttingTreeID[playerid] = -1;
    CuttingTimer[playerid] = -1;
	CarryingLog[playerid] = false;
    EditingTreeID[playerid] = -1;
    
    CuttingBar[playerid] = CreatePlayerProgressBar(playerid, 498.0, 104.0, 113.0, 6.2, 0x61381BFF, CUTTING_TIME, 0);
    ApplyAnimation(playerid, "CHAINSAW", "null", 0.0, 0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "CARRY", "null", 0.0, 0, 0, 0, 0, 0, 0);
	return 1;
}

Player_ResetCutting(playerid)
{
	if (!IsPlayerConnected(playerid) || CuttingTreeID[playerid] == -1) return 0;
	new id = CuttingTreeID[playerid];
	TreeData[id][treeGettingCut] = false;
	if (TreeData[id][treeSeconds] < 1) Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_COLOR, 0x2ECC71FF);
	
	ClearAnimations(playerid);
    TogglePlayerControllable(playerid, 1);
    CuttingTreeID[playerid] = -1;
    
    if (CuttingTimer[playerid] != -1)
	{
	    KillTimer(CuttingTimer[playerid]);
		CuttingTimer[playerid] = -1;
	}
	
	SetPlayerProgressBarValue(playerid, CuttingBar[playerid], 0.0);
	HidePlayerProgressBar(playerid, CuttingBar[playerid]);
	return 1;
}

Player_GiveLog(playerid)
{
    if (!IsPlayerConnected(playerid)) return 0;
	CarryingLog[playerid] = true;
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	SetPlayerAttachedObject(playerid, ATTACH_INDEX, 19793, 6, 0.077999, 0.043999, -0.170999, -13.799953, 79.70, 0.0);
	
	SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Basýp {F1C40F}~k~~CONVERSATION_NO~ {FFFFFF}býrakabilirsiniz.");
	return 1;
}

Player_DropLog(playerid, death_drop = 0)
{
    if (!IsPlayerConnected(playerid) || !CarryingLog[playerid]) return 0;
    new id = Iter_Free(Logs);
    if (id != -1)
    {
        new Float: x, Float: y, Float: z, Float: a, label[128];
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        GetPlayerName(playerid, LogData[id][logDroppedBy], MAX_PLAYER_NAME);

		if (!death_drop)
		{
		    x += (1.0 * floatsin(-a, degrees));
			y += (1.0 * floatcos(-a, degrees));
			
			ApplyAnimation(playerid, "CARRY", "putdwn05", 4.1, 0, 1, 1, 0, 0, 1);
		}

		LogData[id][logSeconds] = LOG_LIFETIME;
		LogData[id][logObjID] = CreateDynamicObject(19793, x, y, z - 0.9, 0.0, 0.0, a);
		
		format(label, sizeof(label), "Odun (%d)\n\n{F1C40F}%s {FFFFFF}tarafýndan býrakýldý\n{FFFFFF}%s\nAlmak için {F1C40F}/log take", id, LogData[id][logDroppedBy], ConvertToMinutes(LOG_LIFETIME));
		LogData[id][logLabel] = CreateDynamic3DTextLabel(label, 0xF1C40FFF, x, y, z - 0.7, 5.0, .testlos = 1);
		
		LogData[id][logTimer] = SetTimerEx("RemoveLog", 1000, true, "i", id);
		Iter_Add(Logs, id);
    }
    
    Player_RemoveLog(playerid);
	return 1;
}

Player_RemoveLog(playerid)
{
	if (!IsPlayerConnected(playerid) || !CarryingLog[playerid]) return 0;
	RemovePlayerAttachedObject(playerid, ATTACH_INDEX);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	CarryingLog[playerid] = false;
	return 1;
}

Vehicle_LogCount(vehicleid)
{
	if (GetVehicleModel(vehicleid) == 0) return 0;
	new count;
	for(new i; i < LOG_LIMIT; i++) if (IsValidDynamicObject(LogObjects[vehicleid][i])) count++;
	return count;
}

Vehicle_RemoveLogs(vehicleid)
{
    if (GetVehicleModel(vehicleid) == 0) return 0;
    for(new i; i < LOG_LIMIT; i++)
	{
	    if (IsValidDynamicObject(LogObjects[vehicleid][i]))
	    {
	        DestroyDynamicObject(LogObjects[vehicleid][i]);
	        LogObjects[vehicleid][i] = -1;
	    }
	}
	
	return 1;
}

Tree_BeingEdited(id)
{
	if (!Iter_Contains(Trees, id)) return 0;
	foreach(new i : Player) if (EditingTreeID[i] == id) return 1;
	return 0;
}

Tree_UpdateLogLabel(id)
{
    if (!Iter_Contains(Trees, id)) return 0;
    new label[96];
    
    if (TreeData[id][treeLogs] > 0) {
	    format(label, sizeof(label), "Tree (%d)\n\n{FFFFFF}[ODUN] {F1C40F}%d\n{FFFFFF}Odunu aðaçtan almak için: {F1C40F}/log takefromtree", id, TreeData[id][treeLogs]);
		UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], 0xE74C3CFF, label);
	}else{
	    TreeData[id][treeTimer] = SetTimerEx("RespawnTree", 1000, true, "i", id);
	    
	    format(label, sizeof(label), "Tree (%d)\n\n{FFFFFF}%s", id, ConvertToMinutes(TreeData[id][treeSeconds]));
		UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], 0xE74C3CFF, label);
	}
	
	return 1;
}

public OnFilterScriptInit()
{
    print("  [Lumberjack] Initializing...");
    
    // assign default values to variables
	for(new i; i < MAX_TREES; i++)
	{
		TreeData[i][treeObjID] = TreeData[i][treeTimer] = -1;
		TreeData[i][treeLabel] = Text3D: -1;
	}
	
	for(new i; i < MAX_LOGS; i++)
	{
	    LogData[i][logObjID] = LogData[i][logTimer] = -1;
	    LogData[i][logLabel] = Text3D: -1;
	}
	
	for(new i; i < MAX_BUYERS; i++)
	{
	    BuyerData[i][buyerActorID] = -1;
	    BuyerData[i][buyerLabel] = Text3D: -1;
	}
	
	for(new i; i < MAX_VEHICLES; i++) for(new x; x < LOG_LIMIT; x++) LogObjects[i][x] = -1;
	
	foreach(new i : Player) Player_Init(i);
	
	// open database & create tables
	ScriptDBHandle = db_open("lumberjack.db");
	db_query(ScriptDBHandle, "CREATE TABLE IF NOT EXISTS trees (ID INTEGER, PosX FLOAT, PosY FLOAT, PosZ FLOAT, RotX FLOAT, RotY FLOAT, RotZ FLOAT)");
	db_query(ScriptDBHandle, "CREATE TABLE IF NOT EXISTS buyers (ID INTEGER, Skin INTEGER, PosX FLOAT, PosY FLOAT, PosZ FLOAT, PosA FLOAT)");
	
	// prepare tree queries
	LoadTrees = db_prepare(ScriptDBHandle, "SELECT * FROM trees");
	AddTree = db_prepare(ScriptDBHandle, "INSERT INTO trees (ID, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES (?, ?, ?, ?, ?, ?, ?)");
    UpdateTree = db_prepare(ScriptDBHandle, "UPDATE trees SET PosX=?, PosY=?, PosZ=?, RotX=?, RotY=?, RotZ=? WHERE ID=?");
	RemoveTree = db_prepare(ScriptDBHandle, "DELETE FROM trees WHERE ID=?");
	
	// prepare buyer queries
	LoadBuyers = db_prepare(ScriptDBHandle, "SELECT * FROM buyers");
	AddBuyer = db_prepare(ScriptDBHandle, "INSERT INTO buyers (ID, Skin, PosX, PosY, PosZ, PosA) VALUES (?, ?, ?, ?, ?, ?)");
    UpdateBuyer = db_prepare(ScriptDBHandle, "UPDATE buyers SET Skin=?, PosX=?, PosY=?, PosZ=?, PosA=? WHERE ID=?");
	RemoveBuyer = db_prepare(ScriptDBHandle, "DELETE FROM buyers WHERE ID=?");
	
	// load trees
	new id, Float: pos[3], Float: rot[3];
	stmt_bind_result_field(LoadTrees, 0, DB::TYPE_INTEGER, id);
	stmt_bind_result_field(LoadTrees, 1, DB::TYPE_FLOAT, pos[0]);
	stmt_bind_result_field(LoadTrees, 2, DB::TYPE_FLOAT, pos[1]);
	stmt_bind_result_field(LoadTrees, 3, DB::TYPE_FLOAT, pos[2]);
	stmt_bind_result_field(LoadTrees, 4, DB::TYPE_FLOAT, rot[0]);
	stmt_bind_result_field(LoadTrees, 5, DB::TYPE_FLOAT, rot[1]);
	stmt_bind_result_field(LoadTrees, 6, DB::TYPE_FLOAT, rot[2]);

	if (stmt_execute(LoadTrees))
	{
	    print("  [Lumberjack] Loading trees...");

	    new label[96];
	    while(stmt_fetch_row(LoadTrees))
	    {
            TreeData[id][treeX] = pos[0];
		 	TreeData[id][treeY] = pos[1];
		  	TreeData[id][treeZ] = pos[2];
	        TreeData[id][treeRX] = rot[0];
		 	TreeData[id][treeRY] = rot[1];
		  	TreeData[id][treeRZ] = rot[2];

		    TreeData[id][treeObjID] = CreateDynamicObject(657, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ], TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);
			
			format(label, sizeof(label), "Aðaç (%d)\n\n{FFFFFF}kesmek için {F1C40F}~k~~CONVERSATION_NO~ {FFFFFF}tuþuna basýn.", id);
			TreeData[id][treeLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ] + 1.5, 5.0);

			Iter_Add(Trees, id);
		}

		printf("  [Lumberjack] %d agac yuklendi.", Iter_Count(Trees));
	}
	
	// load buyers
	new skin, Float: bpos[4];
	stmt_bind_result_field(LoadBuyers, 0, DB::TYPE_INTEGER, id);
	stmt_bind_result_field(LoadBuyers, 1, DB::TYPE_INTEGER, skin);
	stmt_bind_result_field(LoadBuyers, 2, DB::TYPE_FLOAT, bpos[0]);
	stmt_bind_result_field(LoadBuyers, 3, DB::TYPE_FLOAT, bpos[1]);
	stmt_bind_result_field(LoadBuyers, 4, DB::TYPE_FLOAT, bpos[2]);
	stmt_bind_result_field(LoadBuyers, 5, DB::TYPE_FLOAT, bpos[3]);

	if (stmt_execute(LoadBuyers))
	{
	    print("  [Lumberjack] Alicilar yukleniyor...");

	    new label[172];
	    while(stmt_fetch_row(LoadBuyers))
	    {
            BuyerData[id][buyerSkin] = skin;
		 	BuyerData[id][buyerX] = bpos[0];
		  	BuyerData[id][buyerY] = bpos[1];
	        BuyerData[id][buyerZ] = bpos[2];
		 	BuyerData[id][buyerA] = bpos[3];

		    BuyerData[id][buyerActorID] = CreateDynamicActor(BuyerData[id][buyerSkin], BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ], BuyerData[id][buyerA]);
            SetActorInvulnerable(BuyerData[id][buyerActorID], 1);

			format(label, sizeof(label), "Oduncu (%d)\n\n{FFFFFF}Elektrikli testere satýn almak için {F1C40F}/chainsaw {FFFFFF}Ücret: {2ECC71}$%d.\n{FFFFFF}Odunlarý satmak için: {F1C40F}/log sell {FFFFFF}Ücret: {2ECC71}$%d.", id, CSAW_PRICE, LOG_PRICE);
			BuyerData[id][buyerLabel] = CreateDynamic3DTextLabel(label, 0xF1C40FFF, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ] + 0.25, 5.0, .testlos = 1);

			Iter_Add(Buyers, id);
		}

		printf("  [Lumberjack] %d alici yuklendi.", Iter_Count(Buyers));
	}
	
	return 1;
}

public OnFilterScriptExit()
{
	foreach(new i : Player)
	{
	    Player_ResetCutting(i);
		Player_RemoveLog(i);
		
		DestroyPlayerProgressBar(i, CuttingBar[i]);
	}
	
	foreach(new i : Buyers) DestroyDynamicActor(BuyerData[i][buyerActorID]);
	
	db_close(ScriptDBHandle);
	print("  [Lumberjack] Kaldirildi.");
	return 1;
}

public OnPlayerConnect(playerid)
{
	Player_Init(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	Player_ResetCutting(playerid);
	Player_RemoveLog(playerid);
	
	EditingTreeID[playerid] = -1;
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	Vehicle_RemoveLogs(vehicleid);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	Vehicle_RemoveLogs(vehicleid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    Player_ResetCutting(playerid);
    Player_DropLog(playerid, 1);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate != PLAYER_STATE_WASTED)
	{
	    Player_ResetCutting(playerid);
	    Player_RemoveLog(playerid);
	}
	
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && (newkeys & KEY_NO))
	{
	    if (CarryingLog[playerid]) return Player_DropLog(playerid);
	    
	    if (GetPlayerWeapon(playerid) == WEAPON_CHAINSAW && CuttingTreeID[playerid] == -1 && !CarryingLog[playerid])
	    {
		    new id = GetClosestTree(playerid);

		    if (id != -1)
		    {
		        if (!Tree_BeingEdited(id) && !TreeData[id][treeGettingCut] && TreeData[id][treeSeconds] < 1)
				{
		            SetPlayerLookAt(playerid, TreeData[id][treeX], TreeData[id][treeY]);

		            Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_COLOR, 0xE74C3CFF);
		            CuttingTimer[playerid] = SetTimerEx("CutTree", 1000, true, "i", playerid);
					CuttingTreeID[playerid] = id;
					SetPlayerProgressBarValue(playerid, CuttingBar[playerid], 0.0);
					ShowPlayerProgressBar(playerid, CuttingBar[playerid]);
					TogglePlayerControllable(playerid, 0);
					SetPlayerArmedWeapon(playerid, WEAPON_CHAINSAW);
					ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csaw", 4.1, 1, 0, 0, 1, 0, 1);

					TreeData[id][treeGettingCut] = true;
		        }
		    }
	    }
	}

	return 1;
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (EditingTreeID[playerid] != -1 && Iter_Contains(Trees, EditingTreeID[playerid]))
	{
	    if (response == EDIT_RESPONSE_FINAL)
	    {
	        new id = EditingTreeID[playerid];
	        TreeData[id][treeX] = x;
	        TreeData[id][treeY] = y;
	        TreeData[id][treeZ] = z;
	        TreeData[id][treeRX] = rx;
	        TreeData[id][treeRY] = ry;
	        TreeData[id][treeRZ] = rz;

	        SetDynamicObjectPos(objectid, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]);
	        SetDynamicObjectRot(objectid, TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_X, TreeData[id][treeX]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_Y, TreeData[id][treeY]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_Z, TreeData[id][treeZ] + 1.5);

		    stmt_bind_value(UpdateTree, 0, DB::TYPE_FLOAT, TreeData[id][treeX]);
		    stmt_bind_value(UpdateTree, 1, DB::TYPE_FLOAT, TreeData[id][treeY]);
		    stmt_bind_value(UpdateTree, 2, DB::TYPE_FLOAT, TreeData[id][treeZ]);
		    stmt_bind_value(UpdateTree, 3, DB::TYPE_FLOAT, TreeData[id][treeRX]);
		    stmt_bind_value(UpdateTree, 4, DB::TYPE_FLOAT, TreeData[id][treeRY]);
		    stmt_bind_value(UpdateTree, 5, DB::TYPE_FLOAT, TreeData[id][treeRZ]);
		    stmt_bind_value(UpdateTree, 6, DB::TYPE_INTEGER, id);
			stmt_execute(UpdateTree);

	        EditingTreeID[playerid] = -1;
	    }

	    if (response == EDIT_RESPONSE_CANCEL)
	    {
	        new id = EditingTreeID[playerid];
	        SetDynamicObjectPos(objectid, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]);
	        SetDynamicObjectRot(objectid, TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);
	        EditingTreeID[playerid] = -1;
	    }
	}

	return 1;
}

forward CutTree(playerid);
public CutTree(playerid)
{
    if (CuttingTreeID[playerid] != -1)
	{
	    new id = CuttingTreeID[playerid], Float: value = GetPlayerProgressBarValue(playerid, CuttingBar[playerid]) + 1.0;
	    
		if (value >= CUTTING_TIME) {
		    Player_ResetCutting(playerid);
			MoveDynamicObject(TreeData[id][treeObjID], TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ] + 0.03, 0.025, TreeData[id][treeRX], TreeData[id][treeRY] - 80.0, TreeData[id][treeRZ]);

			TreeData[id][treeLogs] = 5;
			TreeData[id][treeSeconds] = TREE_RESPAWN;
			Tree_UpdateLogLabel(id);
		}else{
		    SetPlayerProgressBarValue(playerid, CuttingBar[playerid], value);
		}
	}

	return 1;
}

forward RespawnTree(id);
public RespawnTree(id)
{
	new label[96];
	if (TreeData[id][treeSeconds] > 1) {
	    TreeData[id][treeSeconds]--;
	    
	    format(label, sizeof(label), "Agac (%d)\n\n{FFFFFF}%s", id, ConvertToMinutes(TreeData[id][treeSeconds]));
		UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], 0xE74C3CFF, label);
	}else if (TreeData[id][treeSeconds] == 1) {
	    KillTimer(TreeData[id][treeTimer]);

	    TreeData[id][treeLogs] = 0;
	    TreeData[id][treeSeconds] = 0;
	    TreeData[id][treeTimer] = -1;
	    
	    SetDynamicObjectPos(TreeData[id][treeObjID], TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]);
     	SetDynamicObjectRot(TreeData[id][treeObjID], TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);
     	
     	format(label, sizeof(label), "Agac (%d)\n\n{FFFFFF}Kesmek icin {F1C40F}~k~~CONVERSATION_NO~ {FFFFFF}tusuna basin.", id);
     	UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], 0x2ECC71FF, label);
	}
	
	return 1;
}

forward RemoveLog(id);
public RemoveLog(id)
{
	if (!Iter_Count(Logs, id)) return 1;
	
	if (LogData[id][logSeconds] > 1) {
	    LogData[id][logSeconds]--;

        new label[128];
	    format(label, sizeof(label), "Odun (%d)\n\n{F1C40F}%s {FFFFFF}tarafindan birakildi\n{FFFFFF}%s\nGeri almak icin {F1C40F}/log take", id, LogData[id][logDroppedBy], ConvertToMinutes(LogData[id][logSeconds]));
		UpdateDynamic3DTextLabelText(LogData[id][logLabel], 0xF1C40FFF, label);
	}else if (LogData[id][logSeconds] == 1) {
	    KillTimer(LogData[id][logTimer]);
	    DestroyDynamicObject(LogData[id][logObjID]);
		DestroyDynamic3DTextLabel(LogData[id][logLabel]);
		
	    LogData[id][logTimer] = -1;
        LogData[id][logObjID] = -1;
        LogData[id][logLabel] = Text3D: -1;

		Iter_Remove(Logs, id);
	}
	
	return 1;
}

// Player Commands
CMD:chainsaw(playerid, params[])
{
    if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu araçta kullanamazsýnýz.");
    if (!IsPlayerNearALogBuyer(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir alýcýnýn yanýnda deðilsiniz.");
	if (GetPlayerMoney(playerid) < CSAW_PRICE) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Yeterli paran yok.");
    GivePlayerMoney(playerid, -CSAW_PRICE);
    GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
    
    new string[64];
    format(string, sizeof(string), "[LUMBERJACK] {FFFFFF}Elektrikli testere satýn alýndý. {2ECC71}$%d.", CSAW_PRICE);
   	SendClientMessage(playerid, 0x3498DBFF, string);
	return 1;
}

CMD:log(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu araçta kullanamazsýnýz.");
    if (isnull(params)) return SendClientMessage(playerid, 0xE88732FF, "KOMUTLAR: {FFFFFF}/log [load/take/takefromcar/takefromtree/sell]");
    
    if (!strcmp(params, "load", true)) {
        // loading to a bobcat
        if (!CarryingLog[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir kütük taþýmýyorsun.");
		new id = GetNearestVehicle(playerid);
		if (GetVehicleModel(id) != 422) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir Bobcat'in yakýnýnda deðilsin.");
		new Float: x, Float: y, Float: z;
    	GetVehicleBoot(id, x, y, z);
    	if (!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Þu anda bir Bobcat kullanmýyorsun.");
    	if (Vehicle_LogCount(id) >= LOG_LIMIT) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu araca daha fazla kütük yükleyemezsiniz.");
    	for(new i; i < LOG_LIMIT; i++)
    	{
    	    if (!IsValidDynamicObject(LogObjects[id][i]))
    	    {
    	        LogObjects[id][i] = CreateDynamicObject(19793, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    			AttachDynamicObjectToVehicle(LogObjects[id][i], id, LogAttachOffsets[i][0], LogAttachOffsets[i][1], LogAttachOffsets[i][2], 0.0, 0.0, LogAttachOffsets[i][3]);
    			break;
    	    }
    	}
    	
    	Streamer_Update(playerid);
    	Player_RemoveLog(playerid);
    	SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Kereste Yuklendi.");
    	// done
    }else if (!strcmp(params, "take")) {
        // taking from ground
        if (CarryingLog[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Zaten bir kütük taþýyorsunuz.");
		new id = GetClosestLog(playerid);
		if (id == -1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir kütüðün yakýnýnda deðilsiniz.");
		LogData[id][logSeconds] = 1;
		RemoveLog(id);
		
		Player_GiveLog(playerid);
		SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Yerden bir kutuk aldiniz.");
		// done
    }else if (!strcmp(params, "takefromcar")) {
        // taking from a bobcat
        if (CarryingLog[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Zaten bir kütük taþýyorsun.");
        new id = GetNearestVehicle(playerid);
		if (GetVehicleModel(id) != 422) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir Bobcat'in yakýnýnda deðilsin.");
		new Float: x, Float: y, Float: z;
    	GetVehicleBoot(id, x, y, z);
    	if (!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Þu anda bir Bobcat kullanmýyorsun.");
    	if (Vehicle_LogCount(id) < 1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu araçta kütük bulunmuyor.");
    	for(new i = (LOG_LIMIT - 1); i >= 0; i--)
    	{
    	    if (IsValidDynamicObject(LogObjects[id][i]))
    	    {
    	        DestroyDynamicObject(LogObjects[id][i]);
    	        LogObjects[id][i] = -1;
    			break;
    	    }
    	}

    	Streamer_Update(playerid);
    	Player_GiveLog(playerid);
        SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Bobcat'dan bir kütük aldýnýz.");
        // done
    }else if (!strcmp(params, "takefromtree")) {
		// taking from a cut tree
		if (CarryingLog[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Zaten bir kütük taþýyorsun..");
        new id = GetClosestTree(playerid);
        if (id == -1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir aðaca yakýn deðilsin.");
        if (TreeData[id][treeSeconds] < 1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu aðaç kesilmedi.");
        if (TreeData[id][treeLogs] < 1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu aðaçta herhangi bir kütük bulunamadý.");
        TreeData[id][treeLogs]--;
        Tree_UpdateLogLabel(id);
        
        Player_GiveLog(playerid);
        SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Kesilen aðaçtan bir kütük aldýnýz.");
        // done
    }else if (!strcmp(params, "sell")) {
        // selling a log
        if (!CarryingLog[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir kütük taþýmýyorsun.");
		if (!IsPlayerNearALogBuyer(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bir alýcýnýýn yanýnda deðilsiniz.");
		Player_RemoveLog(playerid);
		GivePlayerMoney(playerid, LOG_PRICE);
		
		new string[64];
		format(string, sizeof(string), "[LUMBERJACK] {FFFFFF}Odun satýldý {2ECC71}$%d.", LOG_PRICE);
    	SendClientMessage(playerid, 0x3498DBFF, string);
        // done
    }

	return 1;
}

// Admin Commands - Trees
CMD:createtree(playerid, params[])
{
	if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticileri kullanabilir.");
	new id = Iter_Free(Trees);
	if (id == -1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Daha fazla aðaç eklenemez.");
 	new Float: x, Float: y, Float: z, Float: a;
 	GetPlayerPos(playerid, x, y, z);
 	GetPlayerFacingAngle(playerid, a);
 	x += (3.0 * floatsin(-a, degrees));
	y += (3.0 * floatcos(-a, degrees));
	z -= 1.0;
	
	TreeData[id][treeX] = x;
	TreeData[id][treeY] = y;
	TreeData[id][treeZ] = z;
	TreeData[id][treeRX] = TreeData[id][treeRY] = TreeData[id][treeRZ] = 0.0;
	
	TreeData[id][treeObjID] = CreateDynamicObject(657, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ], TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);

	new label[96];
	format(label, sizeof(label), "Agac (%d)\n\n{FFFFFF}Kesmek icin {F1C40F}~k~~CONVERSATION_NO~ {FFFFFF}tusuna basin.", id);
	TreeData[id][treeLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ] + 1.5, 5.0);
	Iter_Add(Trees, id);
	
	stmt_bind_value(AddTree, 0, DB::TYPE_INTEGER, id);
    stmt_bind_value(AddTree, 1, DB::TYPE_FLOAT, TreeData[id][treeX]);
    stmt_bind_value(AddTree, 2, DB::TYPE_FLOAT, TreeData[id][treeY]);
    stmt_bind_value(AddTree, 3, DB::TYPE_FLOAT, TreeData[id][treeZ]);
    stmt_bind_value(AddTree, 4, DB::TYPE_FLOAT, TreeData[id][treeRX]);
    stmt_bind_value(AddTree, 5, DB::TYPE_FLOAT, TreeData[id][treeRY]);
    stmt_bind_value(AddTree, 6, DB::TYPE_FLOAT, TreeData[id][treeRZ]);
    
    if (stmt_execute(AddTree))
    {
        EditingTreeID[playerid] = id;
        EditDynamicObject(playerid, TreeData[id][treeObjID]);
        
        SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Aðaç oluþturuldu.");
        SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Hemen þimdi düzenleyebilir veya düzenlemeyi iptal edip baþka bir zaman düzenleyebilirsiniz..");
	}
	
	return 1;
}

CMD:edittree(playerid, params[])
{
    if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir.");
    if (EditingTreeID[playerid] != -1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Zaten bir aðacý düzenliyorsunuz.");
	new id;
	if (sscanf(params, "i", id)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/edittree [aðaçid]");
	if (!Iter_Contains(Trees, id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz ID.");
	if (TreeData[id][treeGettingCut]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Aðaç kesilmekte olduðu için komut gerçekleþtirilemiyor..");
	if (!IsPlayerInRangeOfPoint(playerid, 30.0, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ])) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Düzenlemek istediðiniz aðacýn yakýnýnda deðilsiniz.");
	EditingTreeID[playerid] = id;
	EditDynamicObject(playerid, TreeData[id][treeObjID]);
	return 1;
}

CMD:removetree(playerid, params[])
{
    if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir.");
	new id;
	if (sscanf(params, "i", id)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/removetree [aðaç id]");
	if (!Iter_Contains(Trees, id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz ID.");
	if (TreeData[id][treeGettingCut]) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Kesilmekte olduðu için belirtilen aðaç kaldýrýlamýyor.");
	if (Tree_BeingEdited(id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Düzenlenmekte olduðu için belirtilen aðaç kaldýrýlamýyor.");
	DestroyDynamicObject(TreeData[id][treeObjID]);
	DestroyDynamic3DTextLabel(TreeData[id][treeLabel]);
	if (TreeData[id][treeTimer] != -1) KillTimer(TreeData[id][treeTimer]);
	
	TreeData[id][treeLogs] = TreeData[id][treeSeconds] = 0;
	TreeData[id][treeObjID] = TreeData[id][treeTimer] = -1;
	TreeData[id][treeLabel] = Text3D: -1;
	Iter_Remove(Trees, id);
	
	stmt_bind_value(RemoveTree, 0, DB::TYPE_INTEGER, id);
	if (stmt_execute(RemoveTree)) SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Aðaç kaldýrýldý.");
	return 1;
}

// Admin Commands - Log Buyers
CMD:createbuyer(playerid, params[])
{
	if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir");
	new skin;
	if (sscanf(params, "i", skin)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/createbuyer [skin id]");
	if (!(0 <= skin <= 311)) return SendClientMessage(playerid, 0xE74C3CFF, "KOMUT: {FFFFFF}Geçersiz skin ID.");
	new id = Iter_Free(Buyers);
	if (id == -1) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Daha fazla alýcý eklenemez.");
	GetPlayerPos(playerid, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ]);
	GetPlayerFacingAngle(playerid, BuyerData[id][buyerA]);

	BuyerData[id][buyerActorID] = CreateDynamicActor(skin, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ], BuyerData[id][buyerA]);
	SetActorInvulnerable(BuyerData[id][buyerActorID], 1);
	
	new label[172];
	format(label, sizeof(label), "Oduncu (%d)\n\n{FFFFFF}Elektrikli testere satin almak icin {F1C40F}/chainsaw {FFFFFF}Ucret: {2ECC71}$%d.\n{FFFFFF}Odunlarý satmak icin: {F1C40F}/log sell {FFFFFF}Ucret: {2ECC71}$%d.", id, CSAW_PRICE, LOG_PRICE);
	BuyerData[id][buyerLabel] = CreateDynamic3DTextLabel(label, 0xF1C40FFF, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ] + 0.25, 5.0, .testlos = 1);
	Iter_Add(Buyers, id);
	
	stmt_bind_value(AddBuyer, 0, DB::TYPE_INTEGER, id);
	stmt_bind_value(AddBuyer, 1, DB::TYPE_INTEGER, skin);
    stmt_bind_value(AddBuyer, 2, DB::TYPE_FLOAT, BuyerData[id][buyerX]);
    stmt_bind_value(AddBuyer, 3, DB::TYPE_FLOAT, BuyerData[id][buyerY]);
    stmt_bind_value(AddBuyer, 4, DB::TYPE_FLOAT, BuyerData[id][buyerZ]);
    stmt_bind_value(AddBuyer, 5, DB::TYPE_FLOAT, BuyerData[id][buyerA]);

    if (stmt_execute(AddBuyer))
	{
		SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Alýcý eklendi.");
		SetPlayerPos(playerid, BuyerData[id][buyerX] + (1.5 * floatsin(-BuyerData[id][buyerA], degrees)), BuyerData[id][buyerY] + (1.5 * floatcos(-BuyerData[id][buyerA], degrees)), BuyerData[id][buyerZ]);
	}
	
	return 1;
}

CMD:setbuyerskin(playerid, params[])
{
	if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir.");
	new id, skin;
	if (sscanf(params, "ii", id, skin)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/setbuyerskin [alýcý id] [skin id]");
	if (!Iter_Contains(Buyers, id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz ID.");
	if (!(0 <= skin <= 311)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz skin ID.");
	BuyerData[id][buyerSkin] = skin;
	
	DestroyDynamicActor(BuyerData[id][buyerActorID]);
	BuyerData[id][buyerActorID] = CreateDynamicActor(skin, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ], BuyerData[id][buyerA]);
	SetActorInvulnerable(BuyerData[id][buyerActorID], 1);
	
	stmt_bind_value(UpdateBuyer, 0, DB::TYPE_INTEGER, skin);
    stmt_bind_value(UpdateBuyer, 1, DB::TYPE_FLOAT, BuyerData[id][buyerX]);
    stmt_bind_value(UpdateBuyer, 2, DB::TYPE_FLOAT, BuyerData[id][buyerY]);
    stmt_bind_value(UpdateBuyer, 3, DB::TYPE_FLOAT, BuyerData[id][buyerZ]);
    stmt_bind_value(UpdateBuyer, 4, DB::TYPE_FLOAT, BuyerData[id][buyerA]);
    stmt_bind_value(UpdateBuyer, 5, DB::TYPE_INTEGER, id);

    if (stmt_execute(UpdateBuyer)) SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Alýcý güncellendi.");
	return 1;
}

CMD:setbuyerpos(playerid, params[])
{
	if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir.");
	new id;
	if (sscanf(params, "i", id)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/setbuyerpos [alýcý id]");
	if (!Iter_Contains(Buyers, id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz ID.");
	GetPlayerPos(playerid, BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ]);
	GetPlayerFacingAngle(playerid, BuyerData[id][buyerA]);

	DestroyDynamicActor(BuyerData[id][buyerActorID]);
	BuyerData[id][buyerActorID] = CreateDynamicActor(BuyerData[id][buyerSkin], BuyerData[id][buyerX], BuyerData[id][buyerY], BuyerData[id][buyerZ], BuyerData[id][buyerA]);
	SetActorInvulnerable(BuyerData[id][buyerActorID], 1);

    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BuyerData[id][buyerLabel], E_STREAMER_X, BuyerData[id][buyerX]);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BuyerData[id][buyerLabel], E_STREAMER_Y, BuyerData[id][buyerY]);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BuyerData[id][buyerLabel], E_STREAMER_Z, BuyerData[id][buyerZ] + 0.25);

	stmt_bind_value(UpdateBuyer, 0, DB::TYPE_INTEGER, BuyerData[id][buyerSkin]);
    stmt_bind_value(UpdateBuyer, 1, DB::TYPE_FLOAT, BuyerData[id][buyerX]);
    stmt_bind_value(UpdateBuyer, 2, DB::TYPE_FLOAT, BuyerData[id][buyerY]);
    stmt_bind_value(UpdateBuyer, 3, DB::TYPE_FLOAT, BuyerData[id][buyerZ]);
    stmt_bind_value(UpdateBuyer, 4, DB::TYPE_FLOAT, BuyerData[id][buyerA]);
    stmt_bind_value(UpdateBuyer, 5, DB::TYPE_INTEGER, id);

    if (stmt_execute(UpdateBuyer))
	{
		SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Alýcý güncellendi.");
        SetPlayerPos(playerid, BuyerData[id][buyerX] + (1.5 * floatsin(-BuyerData[id][buyerA], degrees)), BuyerData[id][buyerY] + (1.5 * floatcos(-BuyerData[id][buyerA], degrees)), BuyerData[id][buyerZ]);
	}
	
	return 1;
}

CMD:removebuyer(playerid, params[])
{
	if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Bu komutu yalnýzca yöneticiler kullanabilir.");
	new id;
	if (sscanf(params, "i", id)) return SendClientMessage(playerid, 0xE88732FF, "KOMUT: {FFFFFF}/removebuyer [alýcý id]");
	if (!Iter_Contains(Buyers, id)) return SendClientMessage(playerid, 0xE74C3CFF, "HATA: {FFFFFF}Geçersiz ID.");
	DestroyDynamicActor(BuyerData[id][buyerActorID]);
	DestroyDynamic3DTextLabel(BuyerData[id][buyerLabel]);
	
	BuyerData[id][buyerActorID] = -1;
	BuyerData[id][buyerLabel] = Text3D: -1;
	Iter_Remove(Buyers, id);
	
	stmt_bind_value(RemoveBuyer, 0, DB::TYPE_INTEGER, id);
    if (stmt_execute(RemoveBuyer)) SendClientMessage(playerid, 0x3498DBFF, "ODUNCU: {FFFFFF}Alýcý kaldýrýldý.");
	return 1;
}