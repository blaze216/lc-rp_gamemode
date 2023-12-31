alias:copculuk("copkutusu");
CMD:copculuk(playerid, params[])
{
    if (PlayerInfo[playerid][pJob] != JOB_TRASHMASTER)	return SendErrorMessage(playerid, "��ba��nda de�ilsiniz.");
	if (IsPlayerInAnyVehicle(playerid))                  return SendErrorMessage(playerid, "Bu komutu bir ara�tayken kullanamazs�n�z!");
    if (HasTrash[playerid])                              return SendErrorMessage(playerid, "Elinizde zaten bir ��p torbas� var!");

	if (!pTemp[playerid][pRentveh])  return SendErrorMessage(playerid, "�ncelikle bir ara� kiralaman�z gerekiyor! (/mak)");
    if (!pTemp[playerid][pJob])      return SendErrorMessage(playerid, "�ncelikle �al���labilecek bir ara� kiralaman�z gerekiyor! (/mak)");
    
    new vehicleid = pTemp[playerid][pRentveh];
    if (!IsTrashMasterCar(vehicleid) || !IsATrashTruck(vehicleid)) return SendErrorMessage(playerid, "Bir ��p kamyonuyla gelmediniz!");

    new id = Trash_Nearest(playerid);
	if (id == -1)                      return SendErrorMessage(playerid, "Yan�nda ��p kutusu yok!");
	if (TrashData[id][TrashLevel] < 1) return SendErrorMessage(playerid, "��p kutusu bo�!");

    new Float: x, Float: y, Float: z;
    GetVehicleBoot(vehicleid, x, y, z);
    if (GetPlayerDistanceFromPoint(playerid, x, y, z) >= 30.0) return SendErrorMessage(playerid, "Yak�n�n�zda ��p kamyonu yok!");

    TrashData[id][TrashLevel]--;
	KillTimer(TrashData[id][TrashTimer]);
    
    TrashData[id][TrashTimer] = SetTimerEx("FillTrash", REFILL_TIME * 1000, false, "i", id);
	
    TrashCP[playerid] = CreateDynamicCP(x, y, z, 3.0, .playerid = playerid);
	HasTrash[playerid] = true;
	
    ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, 0, 0, 0, 0, 0);
	SetPlayerAttachedObject(playerid, ATTACHMENT_INDEX, 1264, 6, 0.222, 0.024, 0.128, 1.90, -90.0, 0.0, 0.5,0.5, 0.5);
	
    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_COLOR, (TrashData[id][TrashLevel] == 0) ? 0xE74C3CFF : 0xF39C12FF);
	
    InfoMSG(playerid, "Cop torbasini ~h~~g~cop kamyonuna ~w~goturun.~n~ Torbayi atabilmek icin - ~r~~k~~CONVERSATION_NO~ tusuna basiniz.", 5);
	return 1;
}