#include "on_screen_size_changed.hpp"

void __fastcall hooks::on_screen_size_changed::function( REGISTERS, int old_width, int old_height ) {
	o_call( ecx, edx, old_width, old_height );
	offsets::engine_client->GetScreenSize( globals::screen_width, globals::screen_height );
	sdk::render->init_fonts( );
}

void hooks::on_screen_size_changed::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::surface, 111 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook OnScreenSizeChanged" );
}