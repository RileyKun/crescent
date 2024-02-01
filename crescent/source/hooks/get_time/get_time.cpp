#include "get_time.hpp"

float __fastcall hooks::get_time::function( REGISTERS ) {
	static const auto ret1 = c_utils::find_pattern( "engine.dll", "D9 43 ? DF F1" );
	static const auto ret2 = c_utils::find_pattern( "engine.dll", "E8 ? ? ? ? D9 43 ? DF F1" );

	auto ret_addr = ( uintptr_t )_ReturnAddress( );

	if ( ( ret_addr == ret1 || ret_addr == ret2 ) && settings::misc::remove_event_delay )
		return FLT_MAX;

	return o_call( ecx, edx );
}

void hooks::get_time::init( ) {
	if ( MH_CreateHook( ( fn )offsets::get_time, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook GetTime" );
}