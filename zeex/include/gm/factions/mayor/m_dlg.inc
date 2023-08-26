Dialog:CITYGUN(playerid, response, listitem, inputtext[])
{
	if (!response)															return pc_cmd_isbasi(playerid, "");
    if (!IsPlayerFactionCity(playerid))										return 1;
    if (!PlayerInfo[playerid][pOnDuty])										return SendErrorMessage(playerid, "Ýlk önce göreve gitmelisin.");
    new locker_id = GetPlayerNearestLocker(playerid);
	if(locker_id < 1) return SendErrorMessage(playerid, "Bu komutu kullanmak için ekipman dolabýna yakýn olmalýsýnýz.");
		
	GameTextForPlayer(playerid, "~r~-", 1500, 4);

	GameTextForPlayer(playerid, "~g~+", 1500, 4);

	Dialog_Show(playerid, CITYGUN, DIALOG_STYLE_LIST, "Ekipman Dolabý", "• Desert Eagle ( .50AE .ext )\n\t{ffc46a}- Extra þarjör al (.50AE .ext)\n{FFFFFF} • MP5 (9x19mm .ext)\n\t{ffc46a} - Extra þarjör al (9x19mm .ext)\n{FFFFFF} • M4 (5.56x45mm (drum))\n\t{ffc46a} - Extra þarjör al (5.56x45mm (drum))\n\t{ffc46a} - Extra þarjör al (5.56x45mm (plastik))\n{FF6347} • Tüm silahlarýný teslim et", "Seç", "Kapat");
 	return 1;
}