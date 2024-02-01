#include "do_post_screen_space_effects.hpp"
#include "../../materials/materials.hpp"
#include "../../visuals/visuals.hpp"

bool __fastcall hooks::do_post_screen_space_effects::function( REGISTERS, const CViewSetup* setup ) {
	visuals::materials->on_screen_fx( );
	visuals::main->on_screen_fx( );
	return o_call( ecx, edx, setup );
}

void hooks::do_post_screen_space_effects::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client_mode, 39 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook DoPostScreenSpaceEffects" );
}