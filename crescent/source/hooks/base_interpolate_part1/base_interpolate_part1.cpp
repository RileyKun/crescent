#include "base_interpolate_part1.hpp"

int __fastcall hooks::base_interpolate_part1::function( REGISTERS, float& current_time, vec3_t& old_origin, vec3_t& old_angles, vec3_t& old_velocity, int& no_more_changes ) {
	return o_call( ecx, edx, current_time, old_origin, old_angles, old_velocity, no_more_changes );
}

void hooks::base_interpolate_part1::init( ) {
	if ( MH_CreateHook( ( fn )offsets::base_interpolate_part1, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook BaseInterpolatePart1" );
}