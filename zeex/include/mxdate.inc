/*
	˜˜˜˜˜˜˜˜˜˜ UNIX TIMESTAMP ˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜.

	˜˜˜˜˜˜˜˜˜
		UNIX TIMESTAMP ˜˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜ 01.01.1970, 00:00:00 ˜˜
		˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜

	˜˜˜˜˜˜
		˜˜˜˜˜ integer (4 ˜˜˜˜˜)
*/
stock date_to_timestamp
(
	year = 1970,	month  = 1,	day    = 1,
	hour =    0,	minute = 0,	second = 0
)
{
	switch ( month )
	{
		case  2 : day +=  31;	case  3 : day +=  59;	case  4 : day +=  90;
		case  5 : day += 120;	case  6 : day += 151;	case  7 : day += 181;
		case  8 : day += 212;	case  9 : day += 243;	case 10 : day += 273;
		case 11 : day += 304;	case 12 : day += 334;
	}

	return ( second + minute*60 + hour*3600 + (day - 1)*86400
		+ (year - 1970)*31557600 + ( year % 4 == 0 ? 21600 : 0 ) );
}


/*
	˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ UNIX TIMESTAMP.

	˜˜˜˜˜˜˜˜˜
		UNIX TIMESTAMP ˜˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜ 01.01.1970, 00:00:00 ˜˜
		˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜, ˜˜ ˜
		year ˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜, ˜ month - ˜˜˜˜˜, ˜ day - ˜˜˜˜,
		˜ hour - ˜˜˜, ˜ minute - ˜˜˜˜˜˜, ˜ second - ˜˜˜˜˜˜˜.

	˜˜˜˜˜˜
		˜˜˜˜˜˜
*/
stock timestamp_to_date
(
	unix_timestamp = 0,

	& year = 1970,		& month  = 1,		& day    = 1,
	& hour =    0,		& minute = 0,		& second = 0
)
{
	year = unix_timestamp / 31557600;
	unix_timestamp -= year * 31557600;
	year += 1970;

	if ( year % 4 == 0 ) unix_timestamp -= 21600;

	day = unix_timestamp / 86400;

	switch ( day )
	{
		// ˜ second ˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		case    0..30 : { second = day;       month =  1; }
		case   31..58 : { second = day -  31; month =  2; }
		case   59..89 : { second = day -  59; month =  3; }
		case  90..119 : { second = day -  90; month =  4; }
		case 120..150 : { second = day - 120; month =  5; }
		case 151..180 : { second = day - 151; month =  6; }
		case 181..211 : { second = day - 181; month =  7; }
		case 212..242 : { second = day - 212; month =  8; }
		case 243..272 : { second = day - 243; month =  9; }
		case 273..303 : { second = day - 273; month = 10; }
		case 304..333 : { second = day - 304; month = 11; }
		case 334..366 : { second = day - 334; month = 12; }
	}

	unix_timestamp -= day * 86400;
	hour = unix_timestamp / 3600;

	unix_timestamp -= hour * 3600;
	minute = unix_timestamp / 60;

	unix_timestamp -= minute * 60;
	day = second + 1;
	second = unix_timestamp;
}

/*
	˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜ ˜˜˜˜˜˜˜˜
	˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ UNIX TIMESTAMP

	˜˜˜˜˜˜˜˜˜
		UNIX TIMESTAMP ˜˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜ 01.01.1970, 00:00:00 ˜˜
		˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜, ˜˜ ˜
		˜˜˜˜˜˜ format ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜
		˜˜ ˜˜ ˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ UNIX TIMESTAMP.

		˜˜˜˜˜˜˜ ˜˜˜˜:	˜˜˜˜˜˜˜˜ ˜˜:
		%yyyy			˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜
		%yy			˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜
		%m			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		%mm			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜
		%d			˜˜˜˜˜˜˜˜ ˜˜˜
		%dd			˜˜˜˜˜˜˜˜ ˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜
		%h			˜˜˜˜˜˜˜˜ ˜˜˜˜
		%hh			˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜
		%i			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		%ii			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜
		%s			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
		%ss			˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜

	˜˜˜˜˜˜
		˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜˜
		˜˜˜˜˜˜ ˜˜˜˜˜˜ = sizeOfOutput
*/
stock get_date ( formatStr[] = "%dd.%mm.%yyyy, %hh:%ii:%ss", timestamp = 0 )
{
	// ------------
	const sizeOfOutput = 128; // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜

	new yyyy, mm, dd, h, m, s,
		pos, foundPos, searchStartPos, outStrLen,
		tmpNumStr[5], outStr[sizeOfOutput];

	timestamp_to_date( timestamp+36000, yyyy,mm,dd, h,m,s ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜
	// ------------


	// -------------------
	// ˜˜˜˜˜˜˜˜˜ formatStr ˜ outStr
	memcpy( outStr, formatStr, 0, (sizeOfOutput - 1)*4 );
	outStr[sizeOfOutput - 1] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜

	outStrLen = strlen(outStr);
	// -------------------


	// YEAR
	// -------------------
	searchStartPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 4; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos < outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		searchStartPos = foundPos + 4; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ += 4

		if ( searchStartPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	searchStartPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%yy", false, searchStartPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos + 2];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		searchStartPos = foundPos + 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( searchStartPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%yy", false, searchStartPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// MONTH
	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%mm", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", mm ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%mm", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%m", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", mm ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		if ( mm < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
			foundPos++; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
		}
		else
			foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%m", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// DAY
	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%dd", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", dd ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%dd", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%d", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", dd ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		if ( dd < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
			foundPos++; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
		}
		else
			foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%d", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// HOUR
	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%hh", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", h ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%hh", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%h", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", h ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		if ( h < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
			foundPos++; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
		}
		else
			foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%h", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// MINUTE
	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%ii", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", m ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%ii", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%i", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", m ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		if ( m < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
			foundPos++; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
		}
		else
			foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%i", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// SECOND
	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%ss", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", s ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
		outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
		foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%ss", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	// -------------------
	foundPos = 0; // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ = 0
	foundPos = strfind( outStr, "%s", false, foundPos ); // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", s ); // tmpNumStr = ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ˜˜˜˜˜ ˜˜˜˜˜ ˜˜ 1 ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
		if ( s < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			outStrLen = strlen(outStr); // ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
			foundPos++; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
		}
		else
			foundPos += 2; // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜. ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

		if ( foundPos < outStrLen ) // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜
			foundPos = strfind( outStr, "%s", false, foundPos ); // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
		else break; // ˜˜˜˜˜ - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜
	}
	// -------------------


	return outStr;
}
