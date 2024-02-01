#include "avoid_players.hpp"

void __fastcall hooks::avoid_players::function( REGISTERS, CUserCmd* cmd ) {
	if ( !settings::movement::no_teammate_push ) o_call( ecx, edx, cmd );
}

void hooks::avoid_players::init( ) {
	if ( MH_CreateHook( ( fn )offsets::avoid_players, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook AvoidPlayers" );
}