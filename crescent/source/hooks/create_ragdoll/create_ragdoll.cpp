#include "create_ragdoll.hpp"

void __fastcall hooks::create_ragdoll::function( REGISTERS ) {
	if ( !ecx || !globals::local_player || ( ( player_t* )ecx )->team( ) == globals::local_player->team( ) )
		goto original_call;

	*( bool* )( ( uintptr_t )ecx + 0xc92 ) = ( settings::ragdoll_fx::burning );
	*( bool* )( ( uintptr_t )ecx + 0xc93 ) = ( settings::ragdoll_fx::electrocuted );
	*( bool* )( ( uintptr_t )ecx + 0xc99 ) = ( settings::ragdoll_fx::become_ash );
	*( bool* )( ( uintptr_t )ecx + 0xc95 ) = ( settings::ragdoll_fx::dissolving );
	*( bool* )( ( uintptr_t )ecx + 0xca0 ) = ( settings::ragdoll_fx::gold );
	*( bool* )( ( uintptr_t )ecx + 0xca1 ) = ( settings::ragdoll_fx::ice );

original_call:
	return o_call( ecx, edx );
}

void hooks::create_ragdoll::init( ) {
	if ( MH_CreateHook( ( fn )offsets::create_ragdoll, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CreateRagdoll" );
}