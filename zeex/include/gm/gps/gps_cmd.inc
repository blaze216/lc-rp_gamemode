alias:gps("harita");
CMD:gps(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_GPS, DIALOG_STYLE_LIST, "GPS > Ana Sayfa", "1. Pop�ler lokasyonlar\n2. ��yerleri \n3. Meslekler\n4. ��yeri bul\n5. Ev bul", "Se�", "�ptal");
	return 1;
}

CMD:cpsifirla(playerid, params[])
{
	if(pTemp[playerid][pTruckerOn]) return false;
	if(pTemp[playerid][pPizzaBoy]) return false;
	
	SendSyntaxMessage(playerid, "T�m checkpointler haritadan kald�r�ld�.");
	DisableWaypoint(playerid);
	return 1;
}