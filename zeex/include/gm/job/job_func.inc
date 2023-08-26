forward LoadDynamicJobs();
forward OnJobInsert(JobID);

public OnJobInsert(JobID)
{
	JobsInfo[JobID][jobID] = cache_insert_id();
	return 1;
}

public LoadDynamicJobs()
{
	new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows) return print("[Jobs] Herhangi bir kayýt bulunamadý.");
	    

	for(new i; i < rows; i++)
	{
		cache_get_value_int(i, "id", JobsInfo[i][jobID]);
		cache_get_value_int(i, "jobid", JobsInfo[i][jobType]);
		cache_get_value_float(i, "posx", JobsInfo[i][jobX]);
		cache_get_value_float(i, "posy", JobsInfo[i][jobY]);
		cache_get_value_float(i, "posz", JobsInfo[i][jobZ]);
		cache_get_value_int(i, "interior", JobsInfo[i][jobInt]);
		cache_get_value_int(i, "vw", JobsInfo[i][jobVW]);
		JobsInfo[i][jobOn] = 1;

		JobsInfo[i][jobPickUp] = CreateDynamicPickup(1210, 1, JobsInfo[i][jobX], JobsInfo[i][jobY], JobsInfo[i][jobZ], JobsInfo[i][jobVW], JobsInfo[i][jobInt], -1, 100.0);

		total++;
	}

	printf("[Jobs] Rows - %i. Load - %i. Time: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

AddJobToFile(jobid, type, Float:x, Float:y, Float:z, interior, vw)
{
    new query[128 + 128];

	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `jobs` (jobid,posx,posy,posz,interior,vw) VALUES (%i,%f,%f,%f,%i,%i)", type, x, y, z, interior, vw);
	mysql_tquery(dbHandle, query, "OnJobInsert", "d", jobid);
	return 1;
}

JobMessage(playerid, string[], length = 5)
{
	PlayerTextDrawShow(playerid, TD_job_message[playerid][0]);
	PlayerTextDrawSetString(playerid, TD_job_message[playerid][0], string);
	SetPVarInt(playerid, #hide_job_message, gettime() + length);
	return 1;
}

ShowJobMessage(playerid, message[])
{
	PlayerTextDrawShow(playerid, TD_job_message[playerid][0]);
	PlayerTextDrawSetString(playerid, TD_job_message[playerid][0], message);
	SetPVarInt(playerid, #hide_job_message, gettime() + 5);
	return 1;
}

Job_Nearest(playerid)
{
	for(new i = 0; i != MAX_JOBS; i++)
	{
		if (JobsInfo[i][jobOn] != 1 || !PlayerToPoint(2.0, playerid, JobsInfo[i][jobX], JobsInfo[i][jobY], JobsInfo[i][jobZ]) || GetWorld(playerid) != JobsInfo[i][jobVW] || GetInterior(playerid) != JobsInfo[i][jobInt]) continue;
		return i;
	}
	return -1;
}


stock GetClosestTypeJob(playerid, type, &Float:radius)
{
	new cl_ID = -1, Float:cl_Dist;
	radius = 9999.0;
	
	for(new i = 0; i < MAX_JOBS; i++)
	{
	    if ( !JobsInfo[i][jobOn] || JobsInfo[i][jobType] != type ) continue;
		if ( (cl_Dist = GetPlayerDistanceToPointEx(playerid, JobsInfo[i][jobX], JobsInfo[i][jobY], JobsInfo[i][jobZ])) < radius )
		{
		    cl_ID = i;
		    radius = cl_Dist;
		}
	}
	return cl_ID;
}