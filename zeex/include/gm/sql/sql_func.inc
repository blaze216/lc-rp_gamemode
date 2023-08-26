stock SQL_SetInteger(sql_table[], sql_field[], sql_integer, sql_id)
{
    new sql_query[256];
    mysql_format(dbHandle, sql_query, sizeof(sql_query), "UPDATE `%s` SET `%s`=%i WHERE `id`=%i", sql_table, sql_field, sql_integer, sql_id);
    return mysql_tquery(dbHandle, sql_query);
}

stock SQL_SetIntegerAcc(sql_table[], sql_field[], sql_integer, sql_id)
{
    new sql_query[256];
    mysql_format(dbHandle, sql_query, sizeof(sql_query), "UPDATE `%s` SET `%s`=%i WHERE `forum_id`=%i", sql_table, sql_field, sql_integer, sql_id);
    return mysql_tquery(dbHandle, sql_query);
}

stock SQL_SetFloat(sql_table[], sql_field[], Float:sql_float, sql_id)
{
    new sql_query[256];
    mysql_format(dbHandle, sql_query, sizeof(sql_query), "UPDATE `%s` SET `%s`=%f WHERE `id`=%i", sql_table, sql_field, sql_float, sql_id);
    return mysql_tquery(dbHandle, sql_query);
}

stock SQL_SetString(sql_table[], sql_field[], sql_string[], sql_id)
{
    new sql_query[256];
    mysql_format(dbHandle, sql_query, sizeof(sql_query), "UPDATE `%s` SET `%s`='%e' WHERE `id`=%i", sql_table, sql_field, sql_string, sql_id);
    return mysql_tquery(dbHandle, sql_query);
}

stock SQL_SetStringAcc(sql_table[], sql_field[], sql_string[], sql_id)
{
    new sql_query[256];
    mysql_format(dbHandle, sql_query, sizeof(sql_query), "UPDATE `%s` SET `%s`='%e' WHERE `forum_id`=%i", sql_table, sql_field, sql_string, sql_id);
    return mysql_tquery(dbHandle, sql_query);
}