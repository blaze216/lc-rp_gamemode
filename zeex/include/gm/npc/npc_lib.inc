SNPC_GetFreeID()
{
    for(new i = 0; i < MAX_SERVER_ACTORS; i++)
    {
        if (!E_ACTOR[i][aON]) return i;
    }
    return -1;
}

SNPC_Nearest(playerid)
{
    for(new i = 0; i < MAX_SERVER_ACTORS; i++)
    {
        if (E_ACTOR[i][aON])
        {
            if (IsPlayerInRangeOfPoint(playerid, 5.0, E_ACTOR[i][aPosX], E_ACTOR[i][aPosY], E_ACTOR[i][aPosZ) && GetWorld(playerid) == E_ACTOR[i][aWorld] && GetInterior(playerid) == E_ACTOR[i][aInterior])
            {
                return i;
            }
        }
    }
    return -1;
}

SNPC_SetActorType(actorid, actor_type)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (actor_type < ACTOR_TYPE_NONE || actor_type > ACTOR_TYPE_DRUGS) return -2;
       
    E_ACTOR[actorid][aType] = actor_type;

    return 1;
}

SNPC_GetActorType(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    
    return E_ACTOR[actorid][aType];
}

SNPC_SetActorPos(actorid, Float:a_px, Float:a_py, Float:a_pz)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    E_ACTOR[actorid][aPosX] = a_px;
    E_ACTOR[actorid][aPosY] = a_py;
    E_ACTOR[actorid][aPosZ] = a_pz;

    SNPC_OnActorUpdate(actorid);
    return SetDynamicActorPos(actorid, a_px, a_py, a_pz);
}

SNPC_GetActorPos(actorid, &Float:a_px, &Float:a_py, &Float:a_pz)
{
    a_px = E_ACTOR[actorid][aPosX];
    a_py = E_ACTOR[actorid][aPosY];
    a_pz = E_ACTOR[actorid][aPosZ];
}

SNPC_SetActorFacingAngle(actorid, Float:a_pr)
{
    if (!IsValidDynamicActor(actorid))   return -1;
    if (a_pr < 0.0 || a_pr > 360.0)      return -2;

    E_ACTOR[actorid][aPosR] = a_pr;

    SNPC_OnActorUpdate(actorid);
    return SetDynamicActorFacingAngle(actorid, a_pr);
}

SNPC_GetActorFacingAngle(actorid, &Float:a_pr)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (E_ACTOR[actorid][aPosR] < 0.0 || E_ACTOR[actorid][aPosR] > 360.0) return -2;

    return E_ACTOR[actorid][aPosR];
}

SNPC_SetActorInterior(actorid, a_int)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    E_ACTOR[actorid][aInterior] = a_int;
    DestroyDynamicActor(actorid);
    actorid = CreateDynamicActor(E_ACTOR[actorid][aSkin], E_ACTOR[actorid][aPosX], E_ACTOR[actorid][aPosY], E_ACTOR[actorid][aPosZ], E_ACTOR[actorid][aPosR], 1, 100.0, E_ACTOR[actorid][aWorld], E_ACTOR[actorid][aInterior]);
    
    SNPC_OnActorUpdate(actorid);
    return a_int;
}

SNPC_GetActorInterior(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    return E_ACTOR[actorid][aInterior];
}

SNPC_SetActorVirtualWorld(actorid, a_vw)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    E_ACTOR[actorid][aWorld] = a_vw;

    SNPC_OnActorUpdate(actorid);
    return SetDynamicActorVirtualWorld(actorid, a_vw);
}

SNPC_GetActorVirtualWorld(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    
    return E_ACTOR[actorid][aWorld];
}

SNPC_SetActorSkin(actorid, skinid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (skinid <= 0 || skinid > 311) return -2;

    E_ACTOR[actorid][aSkin] = skinid;
    DestroyDynamicActor(actorid);
    actorid = CreateDynamicActor(E_ACTOR[actorid][aSkin], E_ACTOR[actorid][aPosX], E_ACTOR[actorid][aPosY], E_ACTOR[actorid][aPosZ], E_ACTOR[actorid][aPosR], 1, 100.0, E_ACTOR[actorid][aWorld], E_ACTOR[actorid][aInterior]);
    return 1;
}

SNPC_GetActorSkin(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (E_ACTOR[actorid][aSkin] <= 0 || E_ACTOR[actorid][aSkin] > 311) return -2;

    return E_ACTOR[actorid][aSkin];
}

SNPC_SetActorSex(actorid, sex = ACTOR_SEX_MALE)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (sex < ACTOR_SEX_MALE || sex > ACTOR_SEX_FEMALE) return -2;

    E_ACTOR[actorid][aSex] = sex;
}

SNPC_GetActorSex(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (sex < ACTOR_SEX_MALE || sex > ACTOR_SEX_FEMALE) return -2;

    return E_ACTOR[actorid][aSex];
}

SNPC_SetActorName(actorid, actor_name[])
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (strlen(actor_name) < 4 || strlen(actor_name) > 11) return -2;

    format(E_ACTOR[actorid][aName], 32, "%s", actor_name);

    SNPC_OnActorUpdate(actorid);
    return 1;
}

SNPC_GetActorName(actorid, &act_name[])
{
    if (!IsValidDynamicActor(actorid)) return -1;
    if (strlen(act_name) < 4 || strlen(actor_name) > 11) return -2;

    format(act_name, sizeof(act_name), "%s", E_ACTOR[actorid][aName]);
}

SNPC_GenerateRandomActor(actorid, &act_name[], &act_surname[], &act_skin)
{
    format(act_name, sizeof(act_name), "%s", SNPC_GenerateRandomName(actorid));
    act_skin = SNPC_GenerateRandomSkin(actorid);
}


SNPC_GenerateRandomSex(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;
        
    new rand = random(2);
    
    return rand;
}

SNPC_GenerateRandomName(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    new rand, aname[32];

    if (GetActorSex(actorid) == ACTOR_SEX_MALE)
    {
        rand = random(sizeof(ACTOR_MNAMES));
        format(aname, 12, "%s", ACTOR_MNAMES[rand][dName]);
    }
    else 
    {
        rand = random(sizeof(ACTOR_FNAMES));
        format(aname, 12, "%s", ACTOR_FNAMES[rand][dName]);
    }  
    
    rand = random(sizeof(ACTOR_SURNAMES));
    format(aname, sizeof(aname), "%s %s", aname, ACTOR_SURNAMES[rand][dSurname]);
    
    return aname;
}

SNPC_GenerateRandomSkin(actorid)
{
    if (!IsValidDynamicActor(actorid)) return -1;

    if (SNPC_GetActorType(actorid) == ACTOR_TYPE_DRUGS)
    {
        if (E_ACTOR[actorid][aSex] == ACTOR_SEX_MALE) 
        {
            new rand = random(sizeof(DRUGS_MALE_ACTOR_SKINS));
            return rand;
        }
        else
        {
            new rand = random(sizeof(DRUGS_FEMALE_ACTOR_SKINS));
            return rand;
        }
    }
    return -1;
}

SNPC_OnActorUpdate(actorid)
{
    if (!IsValidDynamicActor(actorid)) return 1;

    new label_name[64];
    format(label_name, sizeof(label_name), "%s\n(( /say ))", E_ACTOR[actorid][aName], E_ACTOR[actorid][aSurname]);

    if (IsValidDynamic3DTextLabel(E_ACTOR[actorid][aLabel]))
    {
        DestroyDynamic3DTextLabel(E_ACTOR[actorid][aLabel]);
        E_ACTOR[actorid][aLabel] = CreateDynamic3DTextLabel(label_name, 0xFFFFFFFF, E_ACTOR[actorid][aPosX], E_ACTOR[actorid][aPosY], E_ACTOR[actorid][aPosZ], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, E_ACTOR[actorid][aWorld], E_ACTOR[actorid][aInterior]);
    }
    else 
    {
        E_ACTOR[actorid][aLabel] = CreateDynamic3DTextLabel(label_name, 0xFFFFFFFF, E_ACTOR[actorid][aPosX], E_ACTOR[actorid][aPosY], E_ACTOR[actorid][aPosZ], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, E_ACTOR[actorid][aWorld], E_ACTOR[actorid][aInterior]);
    }
    return 1;
}