DNPC_OnActorInit(actorid)
{
    new a_name[32], a_skin, Float:x, Float:y, Float:z, Float:r, a_int, a_world;

    SNPC_SetActorSex(actorid, SNPC_GenerateRandomSex(actorid));

    SNPC_GenerateRandomActor(actorid, a_name, a_surname, a_skin);
    DNPC_GetActorRandomPos(actorid, x, y, z, r, a_int, a_world);

    SNPC_SetActorType(actorid, ACTOR_TYPE_DRUGS);
    SNPC_SetActorName(actorid, a_name);
    SNPC_SetActorSkin(actorid, a_skin);
    SNPC_SetActorPos(actorid, x, y, z);
    SNPC_SetActorFacingAngle(actorid, r);
    SNPC_SetActorVirtualWorld(actorid, a_world);
    SNPC_SetActorInterior(actorid, a_int);
    printf("Actor Created");
    return 1;
}

DNPC_GetActorRandomPos(actorid, &Float:a_px, &Float:a_py, &Float:a_pz, &Float:a_r, a_int, a_world)
{
    new rand = random(sizeof(D_ACTOR_POS));

    while(D_ACTOR_POS[rand][aPosUsed])
    {
        rand = random(sizeof(D_ACTOR_POS));
    }

    a_px = D_ACTOR_POS[rand][dX];
    a_py = D_ACTOR_POS[rand][dY];
    a_pz = D_ACTOR_POS[rand][dZ];
    a_r = D_ACTOR_POS[rand][dR];
    a_int = D_ACTOR_POS[rand][dInterior];
    a_world = D_ACTOR_POS[rand][dWorld];
    D_ACTOR_POS[rand][dPosUsed] = 1;
}

DNPC_