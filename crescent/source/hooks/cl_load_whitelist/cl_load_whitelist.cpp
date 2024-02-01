#include "cl_load_whitelist.hpp"

void* __cdecl hooks::cl_load_whitelist::function( void* table, const char* name ) {
	return settings::misc::bypass_sv_pure ? nullptr : o_call( table, name );
}

void hooks::cl_load_whitelist::init( ) {
	if ( MH_CreateHook( ( fn )offsets::cl_load_whitelist, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CL_LoadWhitelist" );
}