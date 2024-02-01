#include "get_draw_position.hpp"

void __cdecl hooks::get_draw_position::function( float* x, float* y, bool* behind_camera, vec3_t angle_offset ) {
	if ( settings::crosshair::show_thirdperson_angles && globals::local_player && offsets::input->CAM_IsThirdPerson( ) ) {
		auto local_pos = globals::local_player->shoot_pos( );
		auto local_ang = offsets::engine_client->GetViewAngles( );

		Ray_t ray = { };
		ray.Init( local_pos, local_pos + local_ang.to_vec( ) * ( float )MAX_TRACE_LENGTH );

		CTraceFilterHitscan filter = { };
		filter.pass_ent = globals::local_player;

		trace_t trace = { };
		offsets::engine_trace->TraceRay( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace );

		auto screen = vec2_t( );
		if ( trace.did_hit( ) && c_utils::world_to_screen( trace.endpos, screen ) ) {
			if ( x )
				*x = screen.x;

			if ( y )
				*y = screen.y;

			if ( behind_camera )
				*behind_camera = false;

			return;
		}
	}

	return o_call( x, y, behind_camera, angle_offset );
}

void hooks::get_draw_position::init( ) {
	if ( MH_CreateHook( ( fn )offsets::get_draw_position, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook GetDrawPosition" );
}