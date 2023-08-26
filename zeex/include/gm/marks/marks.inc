Marks_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `marks`", "LoadDynamicMarks");
}