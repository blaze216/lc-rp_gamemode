Dialog:DOCSGUN(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    if (!IsPlayerFactionDocs(playerid))										return 1;
	if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "�lk �nce g�reve gitmelisin.");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak i�in ekipman dolab�na yak�n olmal�s�n�z.");
	    	
	GameTextForPlayer(playerid, "~r~-", 1500, 4);
	GameTextForPlayer(playerid, "~g~+", 1500, 4);

	Dialog_Show(playerid, DOCSGUN, DIALOG_STYLE_LIST, "Ekipman Dolab�"," {FFFFFF} � Jop\n� Biber Gaz�\n� Desert Eagle (.50AE .ext)\n\t{ffc46a} - Daha fazla �arj�r (.50AE .ext)\n{FFFFFF} � MP5 (9x19mm .ext)\n\t{ffc46a} - Daha fazla �arj�r (9x19mm .ext)\n{FFFFFF} � Shotgun (12-G BIRDSHOT)\n\t{ffc46a} - Daha fazla �arj�r (12-G BIRDSHOT)\n\t{ffc46a} - Plastik mermiler (12-G BEANBAG)\n{FFFFFF} � �4 (5.56x45mm (drum))\n\t{ffc46a} - Ekstra �arj�rler (5.56x45mm (drum))\n\t{ffc46a} - Plastik mermiler (5.56x45mm (plastik))\n{FFFFFF} � Sniper Rifle (7.62x51mm)\n\t{ffc46a} - Ekstra �arj�rler (7.62x51mm)\n{FFFFFF} � Sis bombas�\n� Kamera\n{FF6347} � T�m silahlar� teslim et "," Se� "," Kapat ");
	return 1;
}