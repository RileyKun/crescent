#include "globals.hpp"

#pragma warning ( disable : 6385 )

bool c_utils::world_to_screen( const vec3_t& world, vec2_t& screen ) {
	const matrix3x4_t& matrix = globals::screen_matrix.as_3x4( );
	auto w = matrix[ 3 ][ 0 ] * world[ 0 ] + matrix[ 3 ][ 1 ] * world[ 1 ] + matrix[ 3 ][ 2 ] * world[ 2 ] + matrix[ 3 ][ 3 ];

	if ( w > .001f ) {
		auto inv_w = 1.f / w;
		screen.x = ( ( float )globals::screen_width * .5f ) + ( .5f * ( ( matrix[ 0 ][ 0 ] * world[ 0 ] + matrix[ 0 ][ 1 ] * world[ 1 ] + matrix[ 0 ][ 2 ] * world[ 2 ] + matrix[ 0 ][ 3 ] ) * inv_w ) * ( float )globals::screen_width + .5f );
		screen.y = ( ( float )globals::screen_height * .5f ) - ( .5f * ( ( matrix[ 1 ][ 0 ] * world[ 0 ] + matrix[ 1 ][ 1 ] * world[ 1 ] + matrix[ 1 ][ 2 ] * world[ 2 ] + matrix[ 1 ][ 3 ] ) * inv_w ) * ( float )globals::screen_height + .5f );
		return true;
	}

	return false;
}

bool c_utils::is_visible( vec3_t start, vec3_t end, void* ignr_ent, void* target_ent ) {
	Ray_t ray;
	ray.Init( start, end );
	CTraceFilterHitscan filter;
	filter.pass_ent = ignr_ent;
	trace_t trace;
	offsets::engine_trace->TraceRay( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace );
	return ( trace.fraction > .99f || ( target_ent && trace.m_pEnt == target_ent ) );
}

bool c_utils::is_visible( vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, void* ignr_ent, void* target_ent ) {
	Ray_t ray;
	ray.Init( start, end, mins, maxs );
	CTraceFilterHitscan filter;
	filter.pass_ent = ignr_ent;
	trace_t trace;
	offsets::engine_trace->TraceRay( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace );
	return ( trace.fraction > .99f || ( target_ent && trace.m_pEnt == target_ent ) );
}

bool c_utils::is_low_fps( ) {
	return ( offsets::globals->frametime > offsets::globals->interval_per_tick );
}

void c_utils::fix_movement( CUserCmd* cmd, vec3_t ang ) {
	auto move = vec3_t( cmd->forwardmove, cmd->sidemove, cmd->upmove ),
		dir = vec3_t( ).look( move );
	auto speed = ::sqrtf( ::powf( move.x, 2.f ) + ::powf( move.y, 2.f ) ),
		yaw = deg_to_rad( ang.y - cmd->viewangles.y + dir.y );
	cmd->forwardmove = ( ::cosf( yaw ) * speed );
	cmd->sidemove = ( ::sinf( yaw ) * speed );
}

aim_type_t c_utils::get_aim_type( ) {
	if ( !globals::local_weapon )
		return aim_type_t::aim_unknown;

	if ( globals::local_weapon->get_slot( ) == weapon_slots_t::slot_melee )
		return aim_type_t::aim_melee;

	switch ( globals::local_weapon->item_def_idx( ) ) {
		case Soldier_m_RocketJumper:
		case Demoman_s_StickyJumper:
			return aim_type_t::aim_unknown;

		default:
			break;
	}

	switch ( globals::local_weapon->get_weapon_id( ) ) {
		case TF_WEAPON_MEDIGUN:
		case TF_WEAPON_LUNCHBOX:
		case TF_WEAPON_PDA:
		case TF_WEAPON_PDA_ENGINEER_BUILD:
		case TF_WEAPON_PDA_ENGINEER_DESTROY:
		case TF_WEAPON_PDA_SPY:
		case TF_WEAPON_PDA_SPY_BUILD:
		case TF_WEAPON_JAR:
		case TF_WEAPON_JAR_GAS:
		case TF_WEAPON_JAR_MILK:
		case TF_WEAPON_BUFF_ITEM:
		case TF_WEAPON_BUILDER:
		case TF_WEAPON_GRAPPLINGHOOK:
			return aim_type_t::aim_unknown;

		case TF_WEAPON_ROCKETLAUNCHER:
		case TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT:
		case TF_WEAPON_PIPEBOMBLAUNCHER:
		case TF_WEAPON_GRENADELAUNCHER:
		case TF_WEAPON_COMPOUND_BOW:
		case TF_WEAPON_CLEAVER:
		case TF_WEAPON_CANNON:
		case TF_WEAPON_FLAMETHROWER:
		case TF_WEAPON_FLAREGUN:
		case TF_WEAPON_FLAREGUN_REVENGE:
		case TF_WEAPON_CROSSBOW:
		case TF_WEAPON_SYRINGEGUN_MEDIC:
			return aim_type_t::aim_projectile;
	}

	return aim_type_t::aim_hitscan;
}

void c_utils::compute_can_shoot( ) {
	globals::can_shoot = false;
	globals::reloading = false;

	if ( globals::local_player && globals::local_weapon ) {
		auto server_time = globals::local_player->tickbase( ) * TICK_INTERVAL;

		globals::can_shoot = ( server_time >= globals::local_weapon->next_primary_attack( ) && server_time >= globals::local_player->next_attack( ) );
		globals::reloading = globals::local_weapon->reloading( );

		if ( globals::local_weapon->get_slot( ) != weapon_slots_t::slot_melee && globals::local_weapon->clip1( ) && globals::reloading )
			globals::can_shoot = true;
	}
}

float c_utils::attribute_hook_float( float base_value, const char* search_string, void* entity, void* buffer, bool is_global_const_string ) {
	using fn = float( __cdecl* )( float, const char*, void*, void*, bool );
	return ( ( fn )offsets::attribute_hook_float )( base_value, search_string, entity, buffer, is_global_const_string );
}

float c_utils::get_latency( ) {
	if ( auto nc = offsets::engine_client->GetNetChannelInfo( ) )
		return nc->GetLatency( MAX_FLOWS );
	return 0.f;
}

void c_utils::get_projectile_fire_setup( vec3_t offset, vec3_t ang_in, vec3_t& pos_out, vec3_t& ang_out, bool pipes ) {
	auto forward = vec3_t( ), right = vec3_t( ), up = vec3_t( );
	ang_in.angle_vectors( &forward, &right, &up );

	auto shoot_pos = globals::local_player->shoot_pos( );
	pos_out = shoot_pos + ( forward * offset.x ) + ( right * offset.y ) + ( up * offset.z );

	if ( pipes )
		ang_out = ang_in;

	else {
		auto end_pos = shoot_pos + ( forward * 2000.f );
		ang_out = pos_out.look( end_pos );
	}
}

void c_utils::get_projectile_fire_setup( vec3_t offset, vec3_t ang_in, vec3_t& pos_out ) {
	auto forward = vec3_t( ), right = vec3_t( ), up = vec3_t( );
	ang_in.angle_vectors( &forward, &right, &up );

	auto shoot_pos = globals::local_player->shoot_pos( );
	pos_out = shoot_pos + ( forward * offset.x ) + ( right * offset.y ) + ( up * offset.z );
}

clr_t c_utils::get_entity_color( player_t* ent ) {
	if ( !ent )
		return clr_t( );

	if ( ent == globals::local_player || ent->is_player_on_steam_friends_list( ) )
		return settings::colors::friends;

	switch ( ent->team( ) ) {
		case TEAM_SPECTATOR: return settings::colors::spectators;
		case TF_TEAM_RED: return settings::colors::red_team;
		case TF_TEAM_BLUE: return settings::colors::blue_team;
	}

	return clr_t( 255, 255, 255 );
}

void c_utils::coll_trace( player_t* ent, vec3_t direction, trace_t& trace ) {
	Ray_t ray = { };
	ray.Init( ent->origin( ), ent->origin( ) + direction, ent->mins( ), ent->maxs( ) );

	CTraceFilterHitscan filter = { };
	filter.pass_ent = ent;

	offsets::engine_trace->TraceRay( ray, MASK_PLAYERSOLID, &filter, &trace );
}

void c_utils::line( const vec3_t& position, const vec3_t& position_, clr_t col ) {
	using fn = void( __cdecl* )( const vec3_t&, const vec3_t&, clr_t, bool );
	return fn( offsets::render_line )( position, position_, col, false );
}

void c_utils::box( const vec3_t& position, const vec3_t& angle, const vec3_t& mins, const vec3_t& maxs, clr_t col ) {
	using fn = void( __cdecl* )( const vec3_t&, const vec3_t&, const vec3_t&, const vec3_t&, clr_t, bool, bool );
	return fn( offsets::render_box )( position, angle, mins, maxs, col, false, false );
}

void c_utils::wireframe_box( const vec3_t& position, const vec3_t& angle, const vec3_t& mins, const vec3_t& maxs, clr_t col ) {
	using fn = void( __cdecl* )( const vec3_t&, const vec3_t&, const vec3_t&, const vec3_t&, clr_t, bool, bool );
	return fn( offsets::render_wireframe_box )( position, angle, mins, maxs, col, false, false );
}

void c_utils::triangle( const vec3_t& point1, const vec3_t& point2, const vec3_t& point3, clr_t col ) {
	using fn = void( __cdecl* )( const vec3_t&, const vec3_t&, const vec3_t&, clr_t, bool );
	return fn( offsets::render_triangle )( point1, point2, point3, col, false );
}

void c_utils::circle( const vec3_t& position, const vec3_t& orientation, float radius, clr_t col ) {
	matrix3x4_t xform;
	angle_matrix( orientation, position, xform );
	vec3_t x_axis, y_axis;
	matrix_get_column( xform, 2, x_axis );
	matrix_get_column( xform, 1, y_axis );

	const uint32_t segments = 64;
	const float rad_step = ( float )tau / ( float )segments;

	vec3_t last_position;
	
	vec3_t start = position + x_axis * radius;
	vec3_t position_ = start;

	for ( int i = 1; i <= segments; i++ ) {
		last_position = position_;

		float sin, cos;
		SinCos( rad_step * i, &sin, &cos );
		position_ = position + ( x_axis * cos * radius ) + ( y_axis * sin * radius );

		c_utils::line( last_position, position_, col );

		if ( col.a( ) && i > 1 )
			c_utils::triangle( start, last_position, position_, clr_t( col.r( ), col.g( ), col.b( ), 45 ) );
	}
}

bool c_utils::is_point_intersecting( const vec3_t& origin, const vec3_t& mins, const vec3_t& maxs, const vec3_t& origin_, const vec3_t& mins_, const vec3_t& maxs_ ) {
	auto min = origin + mins, max = origin + maxs;
	auto min_ = origin_ + mins_, max_ = origin_ + maxs_;

	return (
		min.x < max_.x && max.x > min_.x &&
		min.y < max_.y && max.y > min_.y &&
		min.z < max_.z && max.z > min_.z
	);
}