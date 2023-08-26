SNPC_OnGameModeInit()
{
    mysql_tquery(dbHandle, "SELECT * FROM `trade_prices`", "SNPC_LoadTradePrices");   
    DNPC_OnGameModeInit();
}