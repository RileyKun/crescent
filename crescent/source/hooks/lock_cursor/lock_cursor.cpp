#include "lock_cursor.hpp"
#include "../../user_interface/user_interface.hpp"

void __fastcall hooks::lock_cursor::function( REGISTERS ) {
	return user_interface->is_open ? offsets::surface->UnlockCursor( ) : o_call( ecx, edx );
}

void hooks::lock_cursor::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::surface, 62 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook LockCursor" );
}