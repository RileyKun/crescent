#include "set_alpha_modulation.hpp"

void __fastcall hooks::set_alpha_modulation::function( REGISTERS, float alpha ) {
	return o_call( ecx, edx, globals::drawing_props ? settings::colors::prop_modulation.a( ) / 255.f : alpha );
}

void hooks::set_alpha_modulation::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::studio_render, 28 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook SetAlphaModulation" );
}