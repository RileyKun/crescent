#include "wnd_proc.hpp"
#include "../../user_interface/user_interface.hpp"

LRESULT CALLBACK hooks::wnd_proc::function( HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam ) {
	return ( user_interface->is_open && ( user_interface->is_keybind_active || offsets::engine_vgui->IsGameUIVisible( ) ) ) ? 1 : o_call( hwnd, umsg, wparam, lparam );
}

void hooks::wnd_proc::init( ) {
	while ( !game_window ) {
		game_window = FindWindowW( L"Valve001", nullptr );
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}

	o_call = ( WNDPROC )SetWindowLongW( game_window, GWL_WNDPROC, ( LONG )function );
}

void hooks::wnd_proc::uninit( ) {
	if ( o_call )
		SetWindowLongW( game_window, GWL_WNDPROC, ( LONG )o_call );
}