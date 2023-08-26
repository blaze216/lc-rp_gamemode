stock LoadMySQLSettings()
{
	new mysqlSettings = ini_openFile("mysql_settings.ini"), 
		errCode;
		
	if(mysqlSettings < 0) {
		printf("[scriptfiles/mysql_settings.ini]: MySQL ayarlari acilirken hata olustu. Hata kodu: %d",mysqlSettings);
		return 0;
	}

	errCode = ini_getString(mysqlSettings,"host", sqlData[SQL_HOST]);
	if(errCode < 0) printf("[scriptfiles/mysql_settings.ini]: MySQL ayarlar dosyasi (ana bilgisayar) okunurken hata olustu. Hata kodu: %d",errCode);

	errCode = ini_getString(mysqlSettings,"user", sqlData[SQL_USER]);
	if(errCode < 0) printf("[scriptfiles/mysql_settings.ini]: MySQL ayarlar dosyasi (kullanici adi) okunurken hata olustu. Hata kodu: %d",errCode);

	errCode = ini_getString(mysqlSettings,"password", sqlData[SQL_PASS]);
	if(errCode < 0) printf("[scriptfiles/mysql_settings.ini]: MySQL ayarlar dosyasi (sifre) okunurken hata olustu. Hata kodu: %d",errCode);

	errCode = ini_getString(mysqlSettings,"database", sqlData[SQL_DB]);
	if(errCode < 0) printf("[scriptfiles/mysql_settings.ini]: MySQL ayarlar dosyasi (veritabanir) okunurken hata olustu. Hata kodu: %d",errCode);

	ini_closeFile(mysqlSettings);
	return 1;
}

stock SQL_OnQueryError(errorid, error[], callback[], query[])
{
    if (errorid == CR_SERVER_LOST)
	{
		if(!LoadMySQLSettings()) return 0;
		
	    dbHandle = mysql_connect(sqlData[SQL_HOST], sqlData[SQL_USER], sqlData[SQL_DB], sqlData[SQL_PASS]);
		mysql_log();
		if (mysql_errno() != 0) printf("[MySQL]: Yeniden baglanilamadi: %s", sqlData[SQL_HOST]);
		else
		{
			printf("[MySQL]: Yeniden baglanildi: %s | Kullanici Adi: %s", sqlData[SQL_HOST], sqlData[SQL_USER]);
			
            new infoLog[144];

            mysql_get_charset(infoLog);

            printf("[?] MySQL charset: %s", infoLog);

            mysql_set_charset("latin5");
            mysql_get_charset(infoLog);

		    new name[32];
			mysql_get_charset(name, 32);
			printf("[MySQL]: Encoding: %s", name);
		}
	}
	printf("[MySQL]: <|| error: %s | callback: %s | query: %s ||>", error, callback, query);
    return 1;
}

stock SQL_OnGameModeInit()
{
	if(!LoadMySQLSettings()) return 0;

    dbHandle = mysql_connect("localhost", "root", "", "gamemode");

    if(dbHandle == MYSQL_INVALID_HANDLE)
    {
        print("[!] Oyun MySQL sunucusuna baglanti basarisiz.");
        SendRconCommand("exit");
    }
    
    else
    {
		mysql_query(dbHandle, "set names utf8mb4");
        new infoLog[144];

        mysql_get_charset(infoLog);

        printf("[?] MySQL charset: %s", infoLog);

	    mysql_set_charset("latin5", dbHandle);
	    mysql_query(dbHandle, "SET NAMES latin5");
        mysql_get_charset(infoLog);

        printf("[?] MySQL ayarlari uygulandiktan sonra charset: %s", infoLog);
        printf("[+] Oyun MYSQL sunucusuna baglanti basarili.");
    }
	return 1;
}//дб
