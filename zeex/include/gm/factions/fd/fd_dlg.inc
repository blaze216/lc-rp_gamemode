Dialog:FDArmoury(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    if (!IsPlayerFactionMedic(playerid) || !IsPlayerFactionFire(playerid))	return 1;
    if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin.");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");

	if(response)   
	{     
	    switch(listitem)
	    {
		    case 0: AC_GivePlayerWeapon(playerid, 9, 1);
		    case 1: AC_GivePlayerWeapon(playerid, 42, 999);
		    case 2: AC_ResetPlayerWeapons(playerid);
     	}

	    GameTextForPlayer(playerid, "~g~+", 1500, 4);
    }
	Dialog_Show(playerid, FDArmoury, DIALOG_STYLE_LIST, "Ekipman", "� Testere\n� Yang�n S�nd�r�c�\n{FF6347}� Ekipmanlar� teslim et", "Se�", "Geri D�n");
 	return 1;
}