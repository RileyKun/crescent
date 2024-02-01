#include "override_view.hpp"

static bool set = false;

void __fastcall hooks::override_view::function( REGISTERS, CViewSetup* setup ) {
	o_call( ecx, edx, setup );

	if ( !globals::local_player )
		return;

	if ( settings::visuals::thirdperson_key && GetAsyncKeyState( settings::visuals::thirdperson_key ) ) {
		if ( !set ) {
			globals::tp_toggled = !globals::tp_toggled;
			set = true;
		}
	}

	else {
		set = false;
	}

	auto thirdperson = [ ]( ) {
		auto is_thirdperson = offsets::input->CAM_IsThirdPerson( );

		if ( !globals::tp_toggled || ( globals::local_player->in_cond( TF_COND_ZOOMED ) && !settings::visuals::remove_scope ) ) {
			if ( is_thirdperson )
				globals::local_player->force_taunt_cam( ) = 0;
			return;
		}

		if ( !is_thirdperson )
			globals::local_player->force_taunt_cam( ) = 1;
	};

	thirdperson( );

	if ( globals::local_player->observer_mode( ) == OBS_MODE_FIRSTPERSON || ( globals::local_player->in_cond( TF_COND_ZOOMED ) && !settings::visuals::remove_scope ) )
		return;

	setup->fov = ( float )settings::visuals::field_of_view;

	if ( !globals::local_player->deadflag( ) )
		globals::local_player->fov( ) = settings::visuals::field_of_view;
}

void hooks::override_view::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client_mode, 16 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook OverrideView" );
}