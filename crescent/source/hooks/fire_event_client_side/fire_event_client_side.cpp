#include "fire_event_client_side.hpp"
#include "../../networking/networking.hpp"

bool __fastcall hooks::fire_event_client_side::function( REGISTERS, IGameEvent* event ) {
	if ( misc::networking->handle_event( event ) )
		return false;
	return o_call( ecx, edx, event );
}

void hooks::fire_event_client_side::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::event_mgr, 8 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook FireEventClientSide" );
}