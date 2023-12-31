CMD:paypark(playerid, params[]) //������ ��������
{
	new id = -1, 
        vid = -1, 
        Float:x, Float:y, Float:z;
	
	if (IsPlayerInAnyVehicle(playerid))				 return SendErrorMessage(playerid, "Ara�tan inmelisiniz.");
	if ((id = ParkMeter_Nearest(playerid)) == -1)     return SendErrorMessage(playerid, "Yak�n�n�zda parkmetre yok.");
    if (!pMeter[id][parkAvailable])                   return SendErrorMessage(playerid, "Parkmetreyi zaten �demi�siniz!"); 

    if (GetPlayerMoney(playerid) < CASH_PARKING)      return SendErrorMessage(playerid, "Yeterli paran�z yok. Parkmetre �cretini �demek i�in $%d'ye ihtiyac�n�z var.", CASH_PARKING);
		
    for(new i = 1; i < MAX_VEHICLES; i++)
    {
        if (IsValidVehicle(i) && (!IsAPlane(i) || !IsABiker(i) || !IsAHelicopter(i) || !IsABoat(i) || !IsABicycle(i)))
        {
            GetVehiclePos(i, x, y, z);
            if (IsPlayerInRangeOfPoint(playerid, 6.0, x, y, z))
            {
                vid = i;
                break;
            }
        }
    }

    if (vid == -1) return SendErrorMessage(playerid, "Herhangi bir ara�ta de�ilsiniz.");

    SendClientMessageEx(playerid, 0x33AA33FF, "> %s park yeri i�in $%d �dedinz..", VehicleNames[GetVehicleModel(vid)-400], CASH_PARKING);
		
    GivePlayerMoney(playerid, -CASH_PARKING);

    pMeter[id][parkVehicle] = vid;
    pMeter[id][parkAvailable] = false;
		
	return 1;
}