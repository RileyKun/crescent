#include "is_allowed_to_withdraw_from_crit_bucket.hpp"

void __fastcall hooks::is_allowed_to_withdraw_from_crit_bucket::function( REGISTERS, float damage ) {
	return o_call( ecx, edx, damage );
}

void hooks::is_allowed_to_withdraw_from_crit_bucket::init( ) {
	if ( MH_CreateHook( ( fn )offsets::is_allowed_to_withdraw_from_crit_bucket, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook IsAllowedToWithdrawFromCritBucket" );
}