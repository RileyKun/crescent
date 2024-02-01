#include "calc_view_model_view.hpp"

void __fastcall hooks::calc_view_model_view::function( REGISTERS, player_t* owner, vec3_t& eye_origin, vec3_t& eye_angles ) {
	auto is_huntsman = ( globals::local_weapon && globals::local_weapon->get_weapon_id( ) == TF_WEAPON_COMPOUND_BOW );
	auto right_mult = is_huntsman ? -1.f : 1.f;

	auto forward = vec3_t( ), right = vec3_t( ), up = vec3_t( );
	eye_angles.angle_vectors( &forward, &right, &up );

	eye_origin += ( forward * ( float )settings::viewmodel::distance ) 
		+ ( right * ( float )settings::viewmodel::distance_right * right_mult )
		+ ( up * ( float )settings::viewmodel::distance_up );

	return o_call( ecx, edx, owner, eye_origin, eye_angles );
}

void hooks::calc_view_model_view::init( ) {
	if ( MH_CreateHook( ( fn )offsets::calc_view_model_view, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CalcViewModelView" );
}