#include "calc_player_view.hpp"

void __fastcall hooks::calc_player_view::function( REGISTERS, vec3_t& eye_origin, vec3_t& eye_angles, float& fov ) {
	if ( !settings::visuals::remove_recoil || !ecx )
		return o_call( ecx, edx, eye_origin, eye_angles, fov );

	auto old_punch = ( ( player_t* )ecx )->punch_ang( );
	( ( player_t* )ecx )->punch_ang( ) = vec3_t( );
	o_call( ecx, edx, eye_origin, eye_angles, fov );
	( ( player_t* )ecx )->punch_ang( ) = old_punch;
}

void hooks::calc_player_view::init( ) {
	if ( MH_CreateHook( ( fn )offsets::calc_player_view, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CalcPlayerView" );
}