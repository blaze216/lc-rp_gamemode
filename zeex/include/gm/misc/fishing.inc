#define MAX_FISH_ZONES 4

new gz_fish[MAX_FISH_ZONES];

new Float: fish_pos[MAX_FISH_ZONES][5] =
{
	{1429.9701,-237.4749,1.3174,182.8500},
	{1429.9701,-237.4749,1.3174,182.8500},
	{1429.9701,-237.4749,1.3174,182.8500},
	{1429.9701,-237.4749,1.3174,182.8500}
};

#define FISH_THRESHOLD 3.0

#define WATER_CHECK_RADIUS 5.0



IsPlayerNearWater(playerid)
{

new 
Float:x, 
Float:y, 
Float:z;

GetPlayerPos(playerid, x, y, z);

if(z > 23.0 || z < 28.0) return 1;

return 0;

} 

new fish_names[10][10] =
{
	{"Somon"},
	{"Sazan"},
	{"Yayýn"},
	{"Çipura"},
	{"Turna"},
	{"Levrek"},
	{"Mezgit"},
	{"Palamut"},
	{"Uskumru"},
	{"Sardalya"}
};

Fish_Init()
{
	for(new i; i < MAX_FISH_ZONES; i++)
	{
    	gz_fish[i] = GangZoneCreate(fish_pos[i][0], fish_pos[i][1], fish_pos[i][2], fish_pos[i][3]);
    	GangZoneHideForAll(gz_fish[i]);
	}
	return 1;
}

CMD:baliklarim(playerid, params[])
{
	SendSyntaxMessage(playerid, "Üzerinizde %i kg balýk bulunuyor.", PlayerInfo[playerid][pFishCount]);
	SendSyntaxMessage(playerid, "Bu balýklarý þehirdeki balýk restoranýna satabilirsin. (Detaylar için /baliksat)");
	if (PlayerInfo[playerid][pFishCount] >= 300)
	{
		return SendSyntaxMessage(playerid, "Üzerinizde taþýnacak maksimum balýk sayýsýna ulaþmýþsýnýz.");
	}
	return 1;
}

CMD:balikdurdur(playerid, params[])
{
    if (pTemp[playerid][pFishTime] == 0) return SendErrorMessage(playerid, "Oltanýzý atmadýnýz.");

    pTemp[playerid][pFishTime] = 0;
    StopPlayerAnims(playerid);
	return 1;
}

CMD:baliksat(playerid, params[])
{
	if (!PlayerToPoint(4,playerid,855.7153,-518.4639,46.1044))
	{
		SendFishMessage(playerid, "Balýk satma alanýnda deðilsiniz.");
		InfoMSG(playerid, "Rota olusturuldu ~r~(/cpsifirla)", 3);
		Waypoint_Set(playerid, 855.7153,-518.4639,46.1044, 8.0);
		return 1;
	}

	if (PlayerInfo[playerid][pFishTime] > gettime())	return SendErrorMessage(playerid, "Balýklarý teslim etmen için %s saniye beklemen gerek.", ConvertSecond(PlayerInfo[playerid][pFishTime] - gettime()));
	if (PlayerInfo[playerid][pFishCount] < 1)			return SendErrorMessage(playerid, "Üzerinde balýk bulunmuyor.");

    new money = floatround(1.2 * float(PlayerInfo[playerid][pFishCount]));

	GiveCash(playerid, money);
	SendSyntaxMessage(playerid, "%i kg balýk satarak $%i kazandýnýz.", PlayerInfo[playerid][pFishCount], money);
	PlayerInfo[playerid][pFishCount] = 0;
	PlayerInfo[playerid][pFishTime] = gettime() + 1000;
	SendHelpMessage(playerid, "Restorantta artýk yeterince balýk var. Daha sonra tekrar uðra. ");
	return 1;
}

alias:baliktut("balik");
CMD:baliktut(playerid, params[])
{
	if (PlayerInfo[playerid][pInjured] != 0 || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed] || PlayerInfo[playerid][pJailed] != 0)
		return SendErrorMessage(playerid, "Bu özelliði þu anda kullanamazsýnýz.");	

    if (PlayerInfo[playerid][pFishCount] >= 300) 			return SendErrorMessage(playerid, "Daha fazla balýk tutamazsýn.");
	if (pTemp[playerid][pFishTime] != 0)					return SendErrorMessage(playerid, "Oltanýzý zaten attýnýz. Biraz bekleyin.");
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)	return SendErrorMessage(playerid, "Araçta bu iþlemi yapamazsýn.");

	if(!IsPlayerNearWater(playerid) && GetPlayerVirtualWorld(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendErrorMessage(playerid, "Denize yakýn deðilsiniz.");

	new id = -1;

	for(new i; i != MAX_PLAYER_ATTACH; i++)
	{
	    if (!AttachInfo[playerid][i][aID] || AttachInfo[playerid][i][aModel] != 18632 || !AttachInfo[playerid][i][aUsed]) continue;

		id = i;
		break;
	}

	if (id == -1) return SendErrorMessage(playerid, "Oltan yok. Aksesuar dükkanlarýndan olta satýn alabilirsin. /gps");

	if (!OnPlayAnim(playerid, "SWORD", "SWORD_BLOCK", 4.1, 0, 0, 0, 1, 0))		return SendErrorMessage(playerid, "Yeterli yeriniz olmadýðý için balýk tutamazsýnýz.");

	pTemp[playerid][pFishTime] = 10 + random(10);

	if(PlayerInfo[playerid][pFishCount] >= 300) {
	    SendErrorMessage(playerid, "Bu balýk tutma iþleminden sonra balýklarýný satabilirsin. Envanterin doldu.");
	}
	return 1;
}

