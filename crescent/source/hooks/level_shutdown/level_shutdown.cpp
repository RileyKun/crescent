#include "level_shutdown.hpp"

void __fastcall hooks::level_shutdown::function( REGISTERS ) {
	o_call( ecx, edx );
	globals::local_player = nullptr;
	globals::local_weapon = nullptr;
	globals::player_resource = nullptr;
	globals::tp_toggled = false;
}

void hooks::level_shutdown::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client, 7 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook LevelShutdown" );
}