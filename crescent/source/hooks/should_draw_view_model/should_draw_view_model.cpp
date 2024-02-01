#include "should_draw_view_model.hpp"

bool __fastcall hooks::should_draw_view_model::function( REGISTERS ) {
	if ( settings::visuals::remove_scope && !offsets::input->CAM_IsThirdPerson( ) && globals::local_player && globals::local_player->in_cond( TF_COND_ZOOMED ) )
		return true;
	return o_call( ecx, edx );
}

void hooks::should_draw_view_model::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client_mode, 24 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook ShouldDrawViewModel" );
}