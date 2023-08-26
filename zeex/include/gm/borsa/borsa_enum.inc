enum BORSA_ENUM {
	bID,
	bName[50 char],
	bPrice
};
new Borsa[MAX_BORSA][BORSA_ENUM];


Borsa_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `borsa`", "LoadBorsa");
}

forward LoadBorsa();

public LoadBorsa()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)	return print("[Borsa] Kayit bulunamadi.");
	 

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", Borsa[i][bID]);
		cache_get_value(i, "name", Borsa[i][bName]);
	    cache_get_value_int(i, "price", Borsa[i][bPrice]);
		total++;
	}
	printf("[Borsa] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}