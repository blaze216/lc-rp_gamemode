Dialog:CITYGUN(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    if (!IsPlayerFactionCity(playerid))										return 1;
    if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin.");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
		
	GameTextForPlayer(playerid, "~r~-", 1500, 4);

	GameTextForPlayer(playerid, "~g~+", 1500, 4);

	Dialog_Show(playerid, CITYGUN, DIALOG_STYLE_LIST, "Ekipman Dolab�", "� Desert Eagle ( .50AE .ext )\n\t{ffc46a}- Extra �arj�r al (.50AE .ext)\n{FFFFFF} � MP5 (9x19mm .ext)\n\t{ffc46a} - Extra �arj�r al (9x19mm .ext)\n{FFFFFF} � M4 (5.56x45mm (drum))\n\t{ffc46a} - Extra �arj�r al (5.56x45mm (drum))\n\t{ffc46a} - Extra �arj�r al (5.56x45mm (plastik))\n{FF6347} � T�m silahlar�n� teslim et", "Se�", "Kapat");
 	return 1;
}