CCTV_PlayerTimer(playerid)
{
    for(new j = 0; j < MAX_CCTV; j++)
	{
        new cam_arr = PCamera[playerid][j];

		if (cam_arr[pc_used])
		{
			if (cam_arr[pc_time] > 0) cam_arr[pc_time]--;
			else
			{
				cam_arr[pc_used] = 
				cam_arr[pc_time] = 0;
			}
		}
    }
    return 1;
}