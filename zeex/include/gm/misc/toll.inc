#define TOLL_COST (15) 					//
#define TOLL_DELAY_COP (4) 				//
#define TOLL_OPEN_DISTANCE (4.0) 		// 
#define MAX_TOLLS (10)

enum TOLL_ENUM
{
	E_tLocked,  // 0 & 1 = Richhman, 2 & 3 = Flint, 4 & 5 = LV, 6 & 7 = BlueBerry right
	E_tOpenTime // 0 & 1 = Richhman, 2 & 3 = Flint, 4 & 5 = LV, 6 & 7 = BlueBerry right
}
new aTolls[MAX_TOLLS][TOLL_ENUM];

new Float: toll_gate_pos[MAX_TOLLS][3] =
{
    {607.9684, -1194.2866, 19.0043},//Richman
	{623.9500, -1183.9774, 19.2260},//Richman
 	{39.7039, -1522.9891, 5.1995},//Flint
 	{62.7378, -1539.9891, 5.0639},//Flint
 	{1778.9886, 702.6728, 15.2574},//LV
    {1795.9447, 704.2550, 15.0006},//LV
    {612.53070, 346.59592, 17.92614},//BLR
    {604.37152, 346.88141, 17.92614},//BLR
    {-195.2768,252.2416,12.0781},//BLL
    {-199.5153,260.3405,12.0781}//BLL
};
	
new Float: toll_gate_rot[MAX_TOLLS][2] =
{
 	{0.000000, 23.81982421875},
	{0.000000, 214.37744140625},
	{0.000000, 270.67565917969},
	{0.000000, 87.337799072266},
	{0.000000, 348.10229492188},
	{0.000000, 169.43664550781},
	{0.00000, 35.00000},
	{0.00000, 215.92000},
	{0.00000, -14.94000},
	{0.00000, -195.00000}
};

new L_a_RequestAllowedCop;
new L_a_TollObject[MAX_TOLLS];

Toll_Init()
{
	CreateDynamicObject(966,613.9722900,-1197.7174100,17.4750300,0.0000000,0.0000000,23.8200000); // Richman
	CreateDynamicObject(966,619.4291400,-1181.6597900,18.7250300,0.0000000,0.0000000,214.3770000); //
	CreateDynamicObject(978,602.5300300,-1203.4530000,18.3230000,0.0000000,0.0000000,210.9350000); //
	CreateDynamicObject(978,617.2069700,-1185.0639600,19.8470000,0.0000000,0.0000000,247.3620000); //
	CreateDynamicObject(979,629.5009800,-1175.1540500,19.6140000,0.0000000,0.0000000,210.0000000); //
	CreateDynamicObject(979,615.7869900,-1193.4639900,18.4990000,0.0000000,0.0000000,253.7500000); //
	CreateDynamicObject(4642,613.6110200,-1193.1440400,19.7060000,0.0000000,0.0000000,31.1610000); //
	CreateDynamicObject(4642,619.1859700,-1185.9379900,20.1340000,0.0000000,0.0000000,211.1670000); //
	L_a_TollObject[0] = CreateDynamicObject( 968, 613.8935546875, -1197.7329101563, 18.109180450439, 0.000000, -90.000000, 23.81982421875, -1 );
	L_a_TollObject[1] = CreateDynamicObject( 968, 619.44201660156, -1181.6903076172, 19.525806427002, 0.000000, -90.000000, 214.37744140625, -1 );

	CreateDynamicObject(8168,61.2210000,-1532.8769500,5.9830000,0.0000000,0.0000000,6.5240000); // Flint County
	CreateDynamicObject(8168,41.4620000,-1529.3620600,6.1950000,0.0000000,0.0000000,186.5530000); //
	CreateDynamicObject(966,35.8897500,-1526.0096400,4.2410600,0.0000000,0.0000000,270.6760000); //
	CreateDynamicObject(966,67.0937300,-1536.8275100,3.9910600,0.0000000,0.0000000,87.3380000); //
	CreateDynamicObject(997,66.2930000,-1547.0909400,4.1310000,0.0000000,0.0000000,82.5240000); //
	CreateDynamicObject(997,34.0650000,-1516.4489700,4.3490000,0.0000000,0.0000000,299.9990000); //
	CreateDynamicObject(997,35.8150000,-1526.3490000,4.2150000,0.0000000,0.0000000,307.6700000); //
	CreateDynamicObject(997,64.8720000,-1533.9429900,4.2220000,0.0000000,0.0000000,312.1550000); //
	CreateDynamicObject(994,51.3200000,-1531.4289600,4.2310000,0.0000000,0.0000000,352.8330000); //
	CreateDynamicObject(994,45.0380000,-1530.6519800,4.2320000,0.0000000,0.0000000,352.8310000); //
   	L_a_TollObject[2] = CreateDynamicObject( 968, 35.838928222656, -1525.9034423828, 5.0012145042419, 0.000000, -90.000000, 270.67565917969, -1 );
 	L_a_TollObject[3] = CreateDynamicObject( 968, 67.116600036621, -1536.8218994141, 4.7504549026489, 0.000000, -90.000000, 87.337799072266, -1 );

	CreateDynamicObject(8168,1789.7659900,703.2520100,15.9380000,1.0070000,3.0090000,98.8260000); // Las Venturas
	CreateDynamicObject(8168,1784.8330100,703.9470200,15.9450000,358.0590000,356.9890000,278.5100000); //
	CreateDynamicObject(966,1781.4122300,697.3253200,14.6369100,0.0000000,0.0000000,348.0900000); //
	CreateDynamicObject(997,1781.7650100,697.2990100,14.6460000,0.0000000,2.9990000,79.9900000); //
	CreateDynamicObject(997,1792.7960200,706.3800000,13.9300000,0.0000000,2.9990000,81.3760000); //
	CreateDynamicObject(966,1793.4289600,709.8798200,13.6369100,0.0000000,0.0000000,169.4370000); //
	CreateDynamicObject(979,1771.3859900,702.2100200,15.0440000,0.0000000,0.0000000,307.2160000); //
	CreateDynamicObject(979,1803.6180400,704.8200100,14.6030000,0.0000000,0.0000000,125.6040000); //
   	L_a_TollObject[4] = CreateDynamicObject( 968, 1781.4133300781, 697.31750488281, 15.420023918152, 0.000000, -90.000000, 348.10229492188, -1 );
 	L_a_TollObject[5] = CreateDynamicObject( 968, 1793.6700439453, 709.84631347656, 14.405718803406, 0.000000, -90.000000, 169.43664550781, -1 );
   	
	CreateDynamicObject(966, 614.42188, 350.81711, 17.92480, 0.00000, 0.00000, 35.00000); // Blueberry right
	CreateDynamicObject(966, 602.91162, 342.59781, 17.92480, 0.00000, 0.00000, 215.92000);
	L_a_TollObject[6] = CreateDynamicObject(968, 614.42188, 350.81711, 18.66520, 0.00000, -90.00000, 35.00000);
	L_a_TollObject[7] = CreateDynamicObject(968, 602.91162, 342.59781, 18.66520, 0.00000, -90.00000, 215.92000);

	CreateDynamicObject(966, -190.35580, 254.64290, 11.07090, 0.00000, 0.00000, 345.00000); // Blueberry left
	CreateDynamicObject(966, -204.00880, 258.30411, 11.07090, 0.00000, 0.00000, -195.00000);
	L_a_TollObject[8] = CreateDynamicObject(968, -190.24850, 254.62019, 11.89360, 0.00000, -90.00000, -14.94000);
	L_a_TollObject[9] = CreateDynamicObject(968, -204.10410, 258.34149, 11.89360, 0.00000, -90.00000, -195.00000);
	return 1;
}

Toll_CloseToll(tollid)
{
    return SetDynamicObjectRot(L_a_TollObject[tollid], toll_gate_rot[tollid][0], -90.0, toll_gate_rot[tollid][1]);
}

Toll_OpenToll(tollid)
{
	aTolls[tollid][E_tOpenTime] = 7;
	return SetDynamicObjectRot(L_a_TollObject[tollid], toll_gate_rot[tollid][0], 0.0, toll_gate_rot[tollid][1]);
}

Toll_Nearest(playerid)
{
	new tollid = -1;

	for(new i; i != MAX_TOLLS; i++)
	{
	    if (!IsPlayerInRangeOfPoint(playerid, TOLL_OPEN_DISTANCE, toll_gate_pos[i][0], toll_gate_pos[i][1], toll_gate_pos[i][2])) continue;
	        
		tollid = i;
		break;
	}

	return tollid;
}

CMD:gise(playerid, params[])
{
	new tollid;
	if ((tollid = Toll_Nearest(playerid)) == -1) return 1;

    if (aTolls[tollid][E_tOpenTime] > 0) 	return SendErrorMessage(playerid, "Giþe zaten açýk, kapanana kadar bekle. ");

	if (!PlayerInfo[playerid][pOnDuty])
	{
		if (aTolls[tollid][E_tLocked])		return SendClientMessage(playerid, COLOR_FADE1, "Çalýþan: Üzgünüm, geçiþine izin veremem.");
		if (GetCash(playerid) < TOLL_COST)	return SendClientMessage(playerid, COLOR_FADE1, "Çalýþan: Geçmek için $15 paraya ihtiyacýn var.");
		    
		GiveCash(playerid, -TOLL_COST);
		pc_cmd_server_ame(playerid, "geçiþ parasýný öder.");
	}
	
	SendClientMessage(playerid, COLOR_FADE1, "Çalýþan: Teþekkürler, dikkatli sürün! ");
	SendSyntaxMessage(playerid, "Geçmek için 6 saniyeniz var.");

	Toll_OpenToll(tollid);
	return 1;
}