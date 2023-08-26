CMD:paypark(playerid, params[]) //îïëàòà ïàğêîâêè
{
	new id = -1, 
        vid = -1, 
        Float:x, Float:y, Float:z;
	
	if (IsPlayerInAnyVehicle(playerid))				 return SendErrorMessage(playerid, "Araçtan inmelisiniz.");
	if ((id = ParkMeter_Nearest(playerid)) == -1)     return SendErrorMessage(playerid, "Yakınınızda parkmetre yok.");
    if (!pMeter[id][parkAvailable])                   return SendErrorMessage(playerid, "Parkmetreyi zaten ödemişsiniz!"); 

    if (GetPlayerMoney(playerid) < CASH_PARKING)      return SendErrorMessage(playerid, "Yeterli paranız yok. Parkmetre ücretini ödemek için $%d'ye ihtiyacınız var.", CASH_PARKING);
		
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

    if (vid == -1) return SendErrorMessage(playerid, "Herhangi bir araçta değilsiniz.");

    SendClientMessageEx(playerid, 0x33AA33FF, "> %s park yeri için $%d ödedinz..", VehicleNames[GetVehicleModel(vid)-400], CASH_PARKING);
		
    GivePlayerMoney(playerid, -CASH_PARKING);

    pMeter[id][parkVehicle] = vid;
    pMeter[id][parkAvailable] = false;
		
	return 1;
}