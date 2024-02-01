#include "set_color_modulation.hpp"

void __fastcall hooks::set_color_modulation::function( REGISTERS, float* color ) {
	float blend[ 3 ] = { settings::colors::prop_modulation.r( ) / 255.f, settings::colors::prop_modulation.g( ) / 255.f, settings::colors::prop_modulation.b( ) / 255.f };
	return o_call( ecx, edx, globals::drawing_props ? blend : color );
}

void hooks::set_color_modulation::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::studio_render, 27 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook SetColorModulation" );
}