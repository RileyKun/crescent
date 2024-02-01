#include "cl_move.hpp"

void __cdecl hooks::cl_move::function( float accumulated_extra_samples, bool final_tick ) {
	o_call( accumulated_extra_samples, final_tick );
}

void hooks::cl_move::init( ) {
	if ( MH_CreateHook( ( fn )offsets::cl_move, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CL_Move" );
}