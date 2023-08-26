Food_OnGameModeInit()
{
	return mysql_tquery(dbHandle, "SELECT * FROM `foodstand`", "LoadDynamicStands");
}
