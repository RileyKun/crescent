#include "level_init_post_entity.hpp"
#include "../../visuals/visuals.hpp"
#include "../../materials/materials.hpp"

void __fastcall hooks::level_init_post_entity::function( REGISTERS ) {
	o_call( ecx, edx );
	visuals::main->modulate_world( );
	visuals::materials->init( );
}

void hooks::level_init_post_entity::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client, 6 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook LevelShutdown" );
}