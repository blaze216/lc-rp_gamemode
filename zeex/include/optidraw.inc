/*
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ''AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
Contributors:
	- algorhitmically
	- Mergevos

Thanks to:
	- Incognito - streamer plugin.
	- Abagail and Crayder - modelsizes include.

Required plugins:
	- Streamer
*/

/*
	  ______   _______   ________  ______  _______   _______    ______   __       __ 
	 /      \ /       \ /        |/      |/       \ /       \  /      \ /  |  _  /  |
	/$$$$$$  |$$$$$$$  |$$$$$$$$/ $$$$$$/ $$$$$$$  |$$$$$$$  |/$$$$$$  |$$ | / \ $$ |
	$$ |  $$ |$$ |__$$ |   $$ |     $$ |  $$ |  $$ |$$ |__$$ |$$ |__$$ |$$ |/$  \$$ |
	$$ |  $$ |$$    $$/    $$ |     $$ |  $$ |  $$ |$$    $$< $$    $$ |$$ /$$$  $$ |
	$$ |  $$ |$$$$$$$/     $$ |     $$ |  $$ |  $$ |$$$$$$$  |$$$$$$$$ |$$ $$/$$ $$ |
	$$ \__$$ |$$ |         $$ |    _$$ |_ $$ |__$$ |$$ |  $$ |$$ |  $$ |$$$$/  $$$$ |
	$$    $$/ $$ |         $$ |   / $$   |$$    $$/ $$ |  $$ |$$ |  $$ |$$$/    $$$ |
	 $$$$$$/  $$/          $$/    $$$$$$/ $$$$$$$/  $$/   $$/ $$/   $$/ $$/      $$/ 
	 
*/
#include <YSI_Coding\y_hooks>
#define METHOD_BOX (0)
#define METHOD_SPHERE (1)

#if !defined OD_METHOD
	#define OD_METHOD (0)
#endif

#assert OD_METHOD >= 0 && OD_METHOD < 2

#include <a_samp>

#tryinclude "..\modelsizes"
#tryinclude "modelsizes"
#tryinclude <modelsizes>

#if !defined GetModelColDimensions || !defined GetColSphereRadius
	#error Optidraw: modelsizes doesn't have required functions or it's not loaded.
#endif

#if !defined _streamer_included
	#tryinclude <streamer>
	#tryinclude "streamer"
	#tryinclude "..\streamer"
#endif

#if !defined _streamer_included
	#error Optidraw: Couldn't load streamer.
#endif

Streamer_SetDynamicObjectData(STREAMER_TAG_OBJECT:objectid, Float:stream_distance, Float:draw_distance, priority)
{
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_DRAW_DISTANCE, stream_distance);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_STREAM_DISTANCE, draw_distance);
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_PRIORITY, priority);
}

Optidraw_DynamicObjectOptimize(STREAMER_TAG_OBJECT:objectid)
{
	if(!IsValidDynamicObject(objectid)) 
	{
		return 0;
	}

	new 
		od_modelid = -1,
		Float:od_DrawDistance;

	od_modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);
	#if OD_METHOD
		new Float:od_spherecol = GetColSphereRadius(od_modelid);
		if(od_spherecol <= 0.0) 
		{
			Streamer_SetDynamicObjectData(objectid, 275.0, 275.0, 0);
		}
		else if(od_spherecol <= 11.25)
		{
			od_DrawDistance = od_spherecol * 75;
			if(od_DrawDistance < 210.0) 
			{
				od_DrawDistance += 100.0;
			}
			Streamer_SetDynamicObjectData(objectid, od_DrawDistance, od_DrawDistance, floatround((od_spherecol), floatround_round));
		}
		else 
		{
			Streamer_SetDynamicObjectData(objectid, 1000.0, 1000.0, floatround((od_spherecol), floatround_round));
		}
	#else
		new 
			Float:od_priority,
			Float:od_ModelSize[3];
		
		if(GetModelColDimensions(od_modelid, od_ModelSize[0], od_ModelSize[1], od_ModelSize[2]))
		{
			if(od_ModelSize[0] > 40.0 && od_ModelSize[1] > 40.0 && od_ModelSize[2] < 12.0)
			{
				#if !defined OD_DISABLE_STATIC_OBJECTS
					Streamer_ToggleItemStatic(STREAMER_TYPE_OBJECT, objectid, 1);
				#else
					Streamer_SetDynamicObjectData(objectid, 400.0, 400.0, 5000);
				#endif
			}
			else
			{
				od_priority = (od_ModelSize[0] * od_ModelSize[1] + od_ModelSize[1] * od_ModelSize[2] + od_ModelSize[2] * od_ModelSize[0]);
				if(od_priority <= 100.0) 
				{
					od_DrawDistance = 300.0;
				}
				else if(od_priority <= 550.0) 
				{
					od_DrawDistance = 365.0;
				}
				else if(od_priority <= 750.0) 
				{
					od_DrawDistance = 435.0;
				}
				else if(od_priority <= 1000.0) 
				{ 
					od_DrawDistance = 575.0;
				}
				else if(od_priority <= 3000.0) 
				{ 
					od_DrawDistance = 700.0;
				}
				else if(od_priority <= 5000.0) 
				{ 
					od_DrawDistance = 850.0;
				}
				else if(od_priority <= 8000.0) 
				{ 
					od_DrawDistance = 1000.0;
				}
				else if(od_priority > 8000.0) 
				{
					od_DrawDistance = 1300.0;
				}
				Streamer_SetDynamicObjectData(objectid, od_DrawDistance, od_DrawDistance - 25, floatround((od_priority/450), floatround_round));
			}
		}
		else 
		{
			Streamer_SetDynamicObjectData(objectid, 275.0, 275.0, 0);
		}
	#endif
	return 1;
}

hook OnScriptInit()
{
	Streamer_ToggleChunkStream(true);
	Streamer_SetChunkSize(STREAMER_TYPE_OBJECT, 250);
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 975);
	Streamer_SetTickRate(25);
	#if !defined OD_DISABLE_STARTUP_MESSAGE
		print("==================================================");
		print("\t* OptiDraw loaded successfully * (12.12.2020.)");
		#if OD_METHOD
		print("\t* Current method: SPHERE");
		#else
		print("\t* Current method: BOX");
		#endif
		print("==================================================");
	#endif
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook function STREAMER_TAG_OBJECT:CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 325.0, Float:drawdistance = 365.0, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
{
	new 
		STREAMER_TAG_OBJECT:od_objectid = continue(modelid, x, y, z, rx, ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance, STREAMER_TAG_AREA:areaid, priority);
	Optidraw_DynamicObjectOptimize(od_objectid);
	return od_objectid;
}

hook function STREAMER_TAG_OBJECT:CreateDynamicObjectEx(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, const worlds[], const interiors[], const players[], const STREAMER_TAG_AREA:areas[], priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas)
{
	new 
		od_objectid = continue(modelid, x, y, z, rx, ry, rz, streamdistance, drawdistance, worlds, interiors, players, STREAMER_TAG_AREA:areas, priority, maxworlds, maxinteriors, maxplayers, maxareas);
	Optidraw_DynamicObjectOptimize(od_objectid);
	
	return od_objectid;
}