#include "can_fire_random_critical_shot.hpp"

bool __fastcall hooks::can_fire_random_critical_shot::function( REGISTERS, float crit_chance ) {
	return o_call( ecx, edx, crit_chance );
}

void hooks::can_fire_random_critical_shot::init( ) {
	if ( MH_CreateHook( ( fn )offsets::can_fire_random_critical_shot, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CanFireRandomCriticalShot" );
}