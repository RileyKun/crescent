#include "hud_paint.hpp"

void __fastcall hooks::hud_paint::function( REGISTERS ) {
	if ( !settings::visuals::remove_scope ) return o_call( ecx, edx );
}

void hooks::hud_paint::init( ) {
	if ( MH_CreateHook( ( fn )offsets::hud_paint, &function, (void**)&o_call) != MH_STATUS::MH_OK)
		throw std::exception( "Failed to hook HudPaint" );
}