alias:gps("harita");
CMD:gps(playerid, params[])
{
	Dialog_Show(playerid, DIALOG_GPS, DIALOG_STYLE_LIST, "GPS > Ana Sayfa", "1. Popüler lokasyonlar\n2. Ýþyerleri \n3. Meslekler\n4. Ýþyeri bul\n5. Ev bul", "Seç", "Ýptal");
	return 1;
}

CMD:cpsifirla(playerid, params[])
{
	if(pTemp[playerid][pTruckerOn]) return false;
	if(pTemp[playerid][pPizzaBoy]) return false;
	
	SendSyntaxMessage(playerid, "Tüm checkpointler haritadan kaldýrýldý.");
	DisableWaypoint(playerid);
	return 1;
}