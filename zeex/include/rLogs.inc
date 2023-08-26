#include <  a_samp  >
#include < YSI\y_va >

#if defined _ServerLogs_included
	#endinput
#endif

#define _ServerLogs_included

#define LogExist fexist

stock WriteInLog( const Log_File[ ], Log_Com[ ], Log_Par[ ], va_args< > )
{
    if( !LogExist( Log_File ) )
    {
        new
			File:File_Rk = fopen( Log_File, io_write )
		;
    	fclose( File_Rk );
    }
    
    new
		rGz_iSTRG[ 300 ],   rYear,      rHour,
		rQz_iSTRG[ 100 ],   rMonth,     rMinute,
		rYz_iSTRG[ 300 ],   rDay,       rSecond,
		rTz_iSTRG[ 300 ]
	;
	
	va_format( rTz_iSTRG, sizeof( rTz_iSTRG ), Log_Par, va_start< 3 > );
	
    getdate( rYear, rMonth, rDay );
    gettime( rHour, rMinute, rSecond );
    format( rQz_iSTRG, 100,  "COMMENT: %s\r\n", Log_Com );
    format( rGz_iSTRG, 300, "(%d/%d/%d)[%02d:%02d:%d] %s\r\n", rDay, rMonth, rYear, rHour, rMinute , rSecond, rTz_iSTRG );
    
   	strcat( rQz_iSTRG, rGz_iSTRG );
   	strcat( rYz_iSTRG, rQz_iSTRG );
    
    new File:File_r = fopen( Log_File, io_append );
    fwrite( File_r, rYz_iSTRG );
    fclose( File_r );

    return 1;
}