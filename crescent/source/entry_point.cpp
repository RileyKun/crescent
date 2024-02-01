#include "hooks/hooks.hpp"
#include "user_interface/user_interface.hpp"
#include "visuals/visuals.hpp"
#include "materials/materials.hpp"

__forceinline unsigned long __stdcall entry_point( _In_ void* parameter ) {
	try {
		while ( !GetModuleHandleA( "mss32.dll" ) )
			std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

		offsets::engine_vgui = c_utils::get_interface< IEngineVGui >( "engine.dll","VEngineVGui002" );
		offsets::engine_client = c_utils::get_interface< IVEngineClient >( "engine.dll", "VEngineClient013" );
		offsets::client = c_utils::get_interface< IBaseClientDLL >( "client.dll", "VClient017" );
		offsets::surface = c_utils::get_interface< IMatSystemSurface >( "vguimatsurface.dll", "VGUI_Surface030" );
		offsets::entity_list = c_utils::get_interface< IClientEntityList >( "client.dll", "VClientEntityList003" );
		offsets::client_mode = **c_utils::find_pattern< void*** >( "client.dll", "8B 0D ? ? ? ? 8B 02 D9 05", 2 );
		offsets::client_state = *c_utils::find_pattern< CClientState** >( "engine.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 08 5F 5E 5B 5D C3", 1 );
		offsets::engine_trace = c_utils::get_interface< IEngineTrace >( "engine.dll", "EngineTraceClient003" );
		offsets::prediction = c_utils::get_interface< CPrediction >( "client.dll", "VClientPrediction001" );
		offsets::movement = c_utils::get_interface< IGameMovement >( "client.dll", "GameMovement001" );
		offsets::globals = *c_utils::find_pattern< CGlobalVarsBase** >( "engine.dll", "A1 ? ? ? ? 8B 11 68", 8 );
		offsets::movehelper = **c_utils::find_pattern< CGlobalVarsBase*** >( "client.dll", "8B 0D ? ? ? ? 8B 01 FF 50 28 56 8B C8", 2 );
		offsets::seed = *c_utils::find_pattern< int** >( "client.dll", "C7 05 ? ? ? ? ? ? ? ? 5D C3 8B 40 34", 2 );
		offsets::start_drawing = c_utils::find_pattern( "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A ? 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC ? 80 3D" );
		offsets::finish_drawing = c_utils::find_pattern( "vguimatsurface.dll", "55 8B EC 6A ? 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A" );
		offsets::calc_player_view = c_utils::find_pattern( "client.dll", "55 8B EC 83 EC 18 53 56 8B F1 8B 0D ? ? ? ? 57 8B 01 8B 40 38 FF D0 84 C0 75 0B" );
		offsets::get_tracer_type = c_utils::find_pattern( "client.dll", "55 8B EC 51 53 56 57 8B F9 E8 ? ? ? ? 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B 0D ? ? ? ? 83 C4 14 8D B0 ? ? ? ? 83 79 30 00 0F 84 ? ? ? ?" );
		offsets::fire_bullet = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B F9 8B 5D" );
		offsets::cl_move = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? 02 0F 8C ? ? 00 00 E8 ? ? ? 00 84 C0" );
		offsets::cl_send_move = c_utils::find_pattern( "engine.dll", "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 8D 4D CC 56 57 8B 3D ? ? ? ? 40 03 F8 C6 45 B0 01 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? E8 ? ? ? ? 8D 4D E4 E8 ? ? ? ? 6A FF 6A 00 68 ? ? ? ? 8D 85 ? ? ? ? C6 45 B0 00 50 8D 4D E4 E8 ? ? ? ? A1 ? ? ? ? 83 C0 01 C7 45 ? ? ? ? ? 79 04" );
		offsets::cl_load_whitelist = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC 30 56 8B 75 08 8B CE FF 75 0C 8B 06 FF 50 30 8B C8 81 F9 ? ? ? ? 74 56" );
		offsets::modelinfo = c_utils::get_interface< IVModelInfo >( "engine.dll", "VModelInfoClient006" );
		offsets::kv_load_from_buffer = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC 38 53 8B 5D 0C" );
		offsets::kv_initialize = c_utils::find_pattern( "engine.dll", "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6", -66 );
		offsets::kv_find_key = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? 56 8B 75 08 57 8B F9 85 F6 0F 84 ? ? ? ? 80 3E 00 0F 84 ? ? ? ?" );
		offsets::matsystem = c_utils::get_interface< IMaterialSystem >( "materialsystem.dll", "VMaterialSystem081" );
		offsets::base_interpolate_part1 = c_utils::find_pattern( "client.dll", "55 8B EC 53 8B 5D 18 56 8B F1" );
		offsets::input = **c_utils::find_pattern< IInput*** >( "client.dll", "8B 0D ? ? ? ? 56 8B 01 FF 50 ? 8B 45 ? 5F 5E 5B C7 40", 2 );
		offsets::render_view = c_utils::get_interface< IVRenderView >( "engine.dll", "VEngineRenderView014" );
		offsets::get_draw_position = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? 53 57 E8 ? ? ? ? 8B 08 89 4D C8 8B 48 04 8B 40 08" );
		offsets::modelrender = c_utils::get_interface< IVModelRender >( "engine.dll", "VEngineModel016" );
		offsets::calc_view_model_view = c_utils::find_pattern( "client.dll", "55 8B EC 83 EC 70 8B 55 0C 53 8B 5D 08 89 4D FC 8B 02 89 45 E8 8B 42 04 89 45 EC 8B 42 08 89 45 F0 56 57" );
		offsets::panel = c_utils::get_interface< IPanel >( "vgui2.dll", "VGUI_Panel009" );
		offsets::hud_paint = c_utils::find_pattern( "client.dll", "55 8B EC 83 EC 68 53 56 57" );
		offsets::in_cond = c_utils::find_pattern( "client.dll", "55 8B EC 83 EC 08 56 57 8B 7D 08 8B F1 83 FF 20" );
		offsets::attribute_hook_float = c_utils::find_pattern( "client.dll", "55 8B EC 83 EC 0C 8B 0D ? ? ? ? 53 56 57 33 F6 33 FF 89 75 F4 89 7D F8 8B 41 08 85 C0 74 38" );
		offsets::phys = c_utils::get_interface< IPhysics >( "vphysics.dll", "VPhysics031" );
		offsets::phys_coll = c_utils::get_interface< IPhysicsCollision >( "vphysics.dll", "VPhysicsCollision007" );
		offsets::phys_props = c_utils::get_interface< IPhysicsSurfaceProps >( "vphysics.dll", "VPhysicsSurfaceProps001" );
		offsets::phys_overlay = c_utils::get_interface< IVPhysicsDebugOverlay >( "engine.dll", "VPhysicsDebugOverlay001" );
		offsets::avoid_players = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 57 8B F9 89 7D ? 83 78 ? ? 0F 84 ? ? ? ? A1" );
		offsets::is_player_on_steam_friends_list = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? E8 ? ? ? ? 85 C0 74 7E 8B 4D 08 85 C9 74 77 A1 ? ? ? ? 83 78 08 00 74 6C 83 78 0C 00 74 66 A1 ? ? ? ? 83 C1 08 56 8B 30 8D 85 ? ? ? ? 50 8B 01" );
		offsets::debug_overlay = c_utils::get_interface< IVDebugOverlay >( "engine.dll", "VDebugOverlay003" );
		offsets::calc_is_attack_critical = c_utils::find_pattern( "client.dll", "53 57 6A ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 8B F9 E8 ? ? ? ? 50 E8 ? ? ? ? 8B D8 83 C4 ? 85 DB 0F 84" );
		offsets::can_fire_random_critical_shot = c_utils::find_pattern( "client.dll", "55 8B EC F3 0F 10 4D ? F3 0F 58 0D" );
		offsets::add_to_crit_bucket = c_utils::find_pattern( "client.dll", "55 8B EC A1 ? ? ? ? F3 0F 10 81 ? ? ? ? F3 0F 10 48" );
		offsets::event_mgr = c_utils::get_interface< IGameEventManager2 >( "engine.dll", "GAMEEVENTSMANAGER002" );
		offsets::is_allowed_to_withdraw_from_crit_bucket = c_utils::find_pattern( "client.dll", "55 8B EC 56 8B F1 0F B7 86" );
		offsets::get_ammo_count = c_utils::find_pattern( "client.dll", "55 8B EC 56 8B 75 08 57 8B F9 83 FE FF 75 08 5F 33 C0 5E 5D C2 04 00" );
		offsets::get_weapon_info = c_utils::find_pattern( "client.dll", "55 8B EC 66 8B ? ? 66 3B 05 ? ? ? ? 73" );
		offsets::get_time = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? ? 74 ? B9" );
		offsets::get_icon = c_utils::find_pattern( "client.dll", "55 8B EC 81 EC ? ? ? ? 83 7D 0C ? 56" );
		offsets::create_ragdoll = c_utils::find_pattern( "client.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? 53 56 57 8B F9 8B 8F" );
		offsets::draw_static_props = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC 10 8B 15 ? ? ? ? 53 56 57 33 F6 89 4D FC 33 FF 89 75 F0 89 7D F4 8B 42 08" );
		offsets::studio_render = c_utils::get_interface< void >( "studiorender.dll", "VStudioRender025" );
		offsets::compute_prop_opacity = c_utils::find_pattern( "engine.dll", "55 8B EC 83 EC ? A1 ? ? ? ? 53 56 57 8B 7D ? 8B D9" );
		offsets::render_line = c_utils::find_pattern( "engine.dll", "55 8B EC 81 EC ? ? ? ? 56 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 01 FF 90 ? ? ? ? 8B F0 85 F6" );
		offsets::render_box = c_utils::find_pattern( "engine.dll", "55 8B EC 51 8B 45 ? 8B C8 FF 75" );
		offsets::render_wireframe_box = c_utils::find_pattern( "engine.dll", "55 8B EC 81 EC ? ? ? ? 56 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 01 FF 90 ? ? ? ? 8B F0 89 75 ? 85 F6 74 ? 8B 06 8B CE FF 50 ? A1" );
		offsets::render_triangle = c_utils::find_pattern( "engine.dll", "55 8B EC 51 8B 45 ? 8B C8 C1 E9" );

		sdk::render->init_fonts( );
		user_interface->init( );
		visuals::materials->init( );

		if ( MH_Initialize( ) != MH_STATUS::MH_OK )
			throw std::exception( "Failed to init minhook" );

		hooks::add_to_crit_bucket::init( );
		hooks::avoid_players::init( );
		hooks::base_interpolate_part1::init( );
		hooks::calc_is_attack_critical::init( );
		hooks::calc_player_view::init( );
		hooks::calc_view_model_view::init( );
		hooks::can_fire_random_critical_shot::init( );
		hooks::cl_load_whitelist::init( );
		hooks::cl_move::init( );
		hooks::cl_send_move::init( );
		hooks::create_move::init( );
		hooks::create_ragdoll::init( );
		hooks::do_post_screen_space_effects::init( );
		hooks::draw_model_execute::init( );
		hooks::draw_static_props::init( );
		hooks::fire_bullet::init( );
		hooks::fire_event_client_side::init( );
		hooks::forced_material_override::init( );
		hooks::frame_stage_notify::init( );
		hooks::get_draw_position::init( );
		hooks::get_time::init( );
		hooks::get_tracer_type::init( );
		hooks::get_user_cmd::init( );
		hooks::hud_paint::init( );
		hooks::in_cond::init( );
		hooks::is_allowed_to_withdraw_from_crit_bucket::init( );
		hooks::level_init_post_entity::init( );
		hooks::level_shutdown::init( );
		hooks::lock_cursor::init( );
		hooks::on_screen_size_changed::init( );
		hooks::override_view::init( );
		hooks::paint::init( );
		hooks::random_seed::init( );
		hooks::set_alpha_modulation::init( );
		hooks::set_color_modulation::init( );
		hooks::should_draw_view_model::init( );
		hooks::wnd_proc::init( );

		if ( MH_EnableHook( MH_ALL_HOOKS ) != MH_STATUS::MH_OK )
			throw std::exception( "Failed to enable hooks" );

		while ( !GetAsyncKeyState( VK_DELETE ) )
			std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

		if ( MH_DisableHook( MH_ALL_HOOKS ) != MH_STATUS::MH_OK )
			throw std::exception( "Failed to disable hooks" );

		if ( MH_Uninitialize( ) != MH_STATUS::MH_OK )
			throw std::exception( "Failed to uninit minhook" );

		hooks::wnd_proc::uninit( );

		if ( user_interface->is_open )
			offsets::surface->SetCursorAlwaysVisible( false );

		visuals::main->restore_modulation( );
	}

	catch ( std::exception& exception ) {
		MessageBoxA( nullptr, exception.what( ), "tf2 - error", MB_OK | MB_ICONERROR );
	}

	FreeLibraryAndExitThread( ( HMODULE )parameter, 0 );
}

int __stdcall DllMain( _In_ HMODULE module, _In_ unsigned long reason, _In_ void* reserved ) {
	if ( reason == DLL_PROCESS_ATTACH ) {
		DisableThreadLibraryCalls( module );
		if ( auto* const module_handle = CreateThread( nullptr, 0, entry_point, module, 0, nullptr ) )
			CloseHandle( module_handle );
	}
	return 1;
}