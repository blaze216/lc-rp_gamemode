
#define MAX_REPAIR_ZONES 8
new gz_repair[MAX_REPAIR_ZONES];
new Float: repair_zones[MAX_REPAIR_ZONES][3] =
{
	{1289.9601,226.6236,19.5547},
	{1368.4257,279.1518,19.5669},
	{1273.6106,360.0854,19.5547},
	{1198.5424,314.0163,19.5547},
    {2334.2034,-108.4665,26.4869},
    {2214.3706,-50.3569,26.4844},
    {2472.8738,-17.8446,26.4844},
    {2541.7617,108.9385,26.4766}
};

/*Repair_Init()
{
	for(new i; i < MAX_REPAIR_ZONES; i++)
	{
    	gz_repair[i] = GangZoneCreate(repair_zones[i][0], repair_zones[i][1], repair_zones[i][2]);
    	GangZoneHideForAll(gz_repair[i]);
	}
	return 1;
}*/


CMD:tamirbolgeleri(playerid, params[])
{
	if (GetPVarInt(playerid, #show_repair) == 1)
	{
	    DeletePVar(playerid, #show_repair);
		for(new i; i < MAX_REPAIR_ZONES; i++) GangZoneHideForPlayer(playerid, gz_repair[i]);

	    SendSyntaxMessage(playerid, "Onarým alanlarý devre dýþý býrakýldý.");
	    return 1;
	}

	SetPVarInt(playerid, #show_repair, 1);
	for(new i; i < MAX_REPAIR_ZONES; i++) GangZoneShowForPlayer(playerid, gz_repair[i], 0xFF0000AA);

	SendSyntaxMessage(playerid, "Tamir edilecek alanlar haritada iþaretlendi. (ESC > Harita).");
	return 1;
}
