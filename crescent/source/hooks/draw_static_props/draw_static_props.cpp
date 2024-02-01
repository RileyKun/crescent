#include "draw_static_props.hpp"

void __fastcall hooks::draw_static_props::function( REGISTERS, void** props, int count, bool shadow_depth, bool draw_vcollide_wireframe ) {
	globals::drawing_props = true;
	o_call( ecx, edx, props, count, shadow_depth, draw_vcollide_wireframe );
	globals::drawing_props = false;
}

void hooks::draw_static_props::init( ) {
	if ( MH_CreateHook( ( fn )offsets::draw_static_props, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook DrawStaticProps" );
}