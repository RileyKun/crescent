#include "add_to_crit_bucket.hpp"

void __fastcall hooks::add_to_crit_bucket::function( REGISTERS, float amount ) {
	return o_call( ecx, edx, amount );
}

void hooks::add_to_crit_bucket::init( ) {
	if ( MH_CreateHook( ( fn )offsets::add_to_crit_bucket, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook AddToCritBucket" );
}