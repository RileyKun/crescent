#include "get_tracer_type.hpp"

const char* __fastcall hooks::get_tracer_type::function( REGISTERS ) {
	if ( !settings::visuals::bullet_tracers || !globals::local_weapon || ecx != globals::local_weapon )
		goto original_call;

	switch ( settings::visuals::bullet_tracers ) {
		case 1: return globals::local_player->team( ) == TF_TEAM_RED ? "dxhr_sniper_rail_red" : "dxhr_sniper_rail_blue";
		case 2: return globals::local_player->team( ) == TF_TEAM_RED ? "bullet_tracer_raygun_red" : "bullet_tracer_raygun_blue";
		case 3: return "merasmus_zap";
		case 4: return "tfc_sniper_distortion_trail";
		case 5: return globals::local_player->team( ) == TF_TEAM_RED ? "bullet_bignasty_tracer01_red" : "bullet_bignasty_tracer01_blue";
	}

original_call:
	return o_call( ecx, edx );
}

void hooks::get_tracer_type::init( ) {
	if ( MH_CreateHook( ( fn )offsets::get_tracer_type, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook GetTracerType" );
}