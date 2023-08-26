/*==============================================================================
		Vehicle Iterator v1.0
			by Daniel_Cortez
		www.pro-pawn.ru

This include adds a Vehicle iterator and hooks CreateVehicle, AddStaticVehicle,
AddStaticVehicleEx and DestroyVehicle so all vehicles are added and removed from
the iterator automatically.
Requirements: foreach or y_iterate by Y_Less.


Copyright (c) 2014-2015 Stanislav Gromov (Daniel_Cortez)

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software in
	a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

2.	Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

3.	This notice may not be removed or altered from any source distribution.
==============================================================================*/


#if defined DC__FOREACH_VEH
	#endinput
#endif
#define	DC__FOREACH_VEH

// NOTE: "dc_foreach_veh__" prefix gives too long function names
// (34/31 symbols for AddStaticVehicleEx) so I'll use "dc_veh_iter__" instead.


#include <a_samp>

#if	!defined	foreach
	#tryinclude "../include/foreach.inc"
#endif
#if	!defined	foreach
	#tryinclude <foreach>
#endif
#if	!defined	foreach
	#tryinclude "../include/YSI/y_iterate.inc"
#endif
#if	!defined	foreach
	#tryinclude <YSI/y_iterate.inc>
#endif
#if	!defined	foreach
	#error Please include foreach.inc or y_iterate.inc before dc_foreach_veh.
#endif


new Iterator:Vehicle<MAX_VEHICLES>;
static dc_veh_iter__veh;


stock dc_veh_iter__CreateVehicle(
	modelid, Float:x, Float:y, Float:z, Float:angle,
	color1, color2, respawn_delay, addsiren = 0
)
{
	if (INVALID_VEHICLE_ID != (dc_veh_iter__veh = CreateVehicle(
		modelid, x, y, z, angle, color1, color2, respawn_delay, addsiren
	)))
		Iter_Add(Vehicle, dc_veh_iter__veh);
	return dc_veh_iter__veh;
}
#if	defined	_ALS_CreateVehicle
	#undef	CreateVehicle
#else
	#define	_ALS_CreateVehicle
#endif
#define	CreateVehicle(%0)	dc_veh_iter__CreateVehicle(%0)

stock dc_veh_iter__AddStaticVehicle(
	modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2
)
{
	if (INVALID_VEHICLE_ID != (dc_veh_iter__veh = AddStaticVehicle(
		modelid, x, y, z, angle, color1, color2
	)))
		Iter_Add(Vehicle, dc_veh_iter__veh);
	return dc_veh_iter__veh;
}
#if	defined	_ALS_AddStaticVehicle
	#undef	AddStaticVehicle
#else
	#define	_ALS_AddStaticVehicle
#endif
#define	AddStaticVehicle(%0)	dc_veh_iter__AddStaticVehicle(%0)

stock dc_veh_iter__AddStaticVehicleEx(
	modelid, Float:x, Float:y, Float:z, Float:angle,
	color1, color2, respawn_delay, addsiren = 0
)
{
	if (INVALID_VEHICLE_ID != (dc_veh_iter__veh = AddStaticVehicleEx(
		modelid, x, y, z, angle, color1, color2, respawn_delay, addsiren
	)))
		Iter_Add(Vehicle, dc_veh_iter__veh);
	return dc_veh_iter__veh;
}
#if	defined	_ALS_AddStaticVehicleEx
	#undef	AddStaticVehicleEx
#else
	#define	_ALS_AddStaticVehicleEx
#endif
#define	AddStaticVehicleEx(%0)	dc_veh_iter__AddStaticVehicleEx(%0)

stock dc_veh_iter__DestroyVehicle(vehicleid)
{
	Iter_Remove(Vehicle, vehicleid);
	return DestroyVehicle(vehicleid);
}
#if	defined	_ALS_DestroyVehicle
	#undef	DestroyVehicle
#else
	#define	_ALS_DestroyVehicle
#endif
#define	DestroyVehicle(%0)	dc_veh_iter__DestroyVehicle(%0)
