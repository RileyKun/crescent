#pragma once
#include "ienginevgui.hpp"
#include "ISurface.hpp"
#include "usercmd.hpp"
#include "view_shared.hpp"
#include "icliententitylist.hpp"
#include "settings.hpp"
#include "c_tf_player.hpp"
#include "tf_weaponbase.hpp"
#include "IVEngineClient.hpp"
#include "IBaseClientDLL.hpp"
#include "IEngineTrace.hpp"
#include "dt_recv.hpp"
#include "bitbuf.hpp"
#include "iprediction.hpp"
#include "md5.hpp"
#include "ivmodelinfo.hpp"
#include "studio.hpp"
#include "imaterialsystem.hpp"
#include "iinput.hpp"
#include "ivrenderview.hpp"
#include "ivmodelrender.hpp"
#include "IPanel.hpp"
#include "vphysics_interface.hpp"
#include "ivdebugoverlay.hpp"
#include "igameevents.hpp"
#include "worldsize.hpp"

namespace offsets {
	// interfaces
	inline IEngineVGui* engine_vgui = nullptr;
	inline IVEngineClient* engine_client = nullptr;
	inline IBaseClientDLL* client = nullptr;
	inline IMatSystemSurface* surface = nullptr;
	inline IClientEntityList* entity_list = nullptr;
	inline void* client_mode = nullptr;
	inline CClientState* client_state = nullptr;
	inline IEngineTrace* engine_trace = nullptr;
	inline CPrediction* prediction = nullptr;
	inline CGlobalVarsBase* globals = nullptr;
	inline void* movehelper = nullptr;
	inline int* seed = nullptr;
	inline IGameMovement* movement = nullptr;
	inline IVModelInfo* modelinfo = nullptr;
	inline IMaterialSystem* matsystem = nullptr;
	inline IInput* input = nullptr;
	inline IVRenderView* render_view = nullptr;
	inline IVModelRender* modelrender = nullptr;
	inline IPanel* panel = nullptr;
	inline IPhysics* phys = nullptr;
	inline IPhysicsSurfaceProps* phys_props = nullptr;
	inline IPhysicsCollision* phys_coll = nullptr;
	inline IVPhysicsDebugOverlay* phys_overlay = nullptr;
	inline IVDebugOverlay* debug_overlay = nullptr;
	inline IGameEventManager2* event_mgr = nullptr;
	inline void* studio_render = nullptr;

	// signatures
	inline uintptr_t start_drawing = 0;
	inline uintptr_t finish_drawing = 0;
	inline uintptr_t calc_player_view = 0;
	inline uintptr_t calc_view_model_view = 0;
	inline uintptr_t get_tracer_type = 0;
	inline uintptr_t fire_bullet = 0;
	inline uintptr_t cl_move = 0;
	inline uintptr_t cl_send_move = 0;
	inline uintptr_t cl_load_whitelist = 0;
	inline uintptr_t kv_load_from_buffer = 0;
	inline uintptr_t kv_initialize = 0;
	inline uintptr_t kv_find_key = 0;
	inline uintptr_t base_interpolate_part1 = 0;
	inline uintptr_t get_draw_position = 0;
	inline uintptr_t hud_paint = 0;
	inline uintptr_t in_cond = 0;
	inline uintptr_t attribute_hook_float = 0;
	inline uintptr_t avoid_players = 0;
	inline uintptr_t is_player_on_steam_friends_list = 0;
	inline uintptr_t calc_is_attack_critical = 0;
	inline uintptr_t can_fire_random_critical_shot = 0;
	inline uintptr_t add_to_crit_bucket = 0;
	inline uintptr_t is_allowed_to_withdraw_from_crit_bucket = 0;
	inline uintptr_t get_ammo_count = 0;
	inline uintptr_t get_weapon_info = 0;
	inline uintptr_t get_time = 0;
	inline uintptr_t get_icon = 0;
	inline uintptr_t create_ragdoll = 0;
	inline uintptr_t draw_static_props = 0;
	inline uintptr_t compute_prop_opacity = 0;
	inline uintptr_t render_line = 0;
	inline uintptr_t render_box = 0;
	inline uintptr_t render_wireframe_box = 0;
	inline uintptr_t render_triangle = 0;
}

#define TICK_INTERVAL		( offsets::globals->interval_per_tick )
#define TIME_TO_TICKS( dt )	( ( int )( .5f + ( float )dt / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )	( TICK_INTERVAL * ( t ) )