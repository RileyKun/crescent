#include "globals.hpp"

bool player_t::is_player( ) {
	if ( !this )
		return false;
	if ( auto cc = client_class( ) )
		return cc->class_id == classid_t::CTFPlayer;
	return false;
}

bool player_t::is_projectile( ) {
	if ( !this )
		return false;

	auto cc = client_class( );

	if ( !cc )
		return false;

	switch ( cc->class_id ) {
		case classid_t::CTFProjectile_Arrow:
		case classid_t::CTFProjectile_SentryRocket:
		case classid_t::CTFProjectile_Cleaver:
		case classid_t::CTFProjectile_Rocket:
		case classid_t::CTFProjectile_Flare:
		case classid_t::CTFGrenadePipebombProjectile: return true;
		default: return false;
	}
}

bool player_t::is_stickybomb( ) {
	if ( !this )
		return false;

	auto cc = client_class( );

	if ( !cc )
		return false;

	if ( cc->class_id == classid_t::CTFGrenadePipebombProjectile )
		return ( pipebomb_type( ) == TYPE_STICKY );

	return false;
}

bool player_t::is_resource( ) {
	if ( !this )
		return false;
	if ( auto cc = client_class( ) )
		return cc->class_id == classid_t::CTFPlayerResource;
	return false;
}

bool player_t::is_building( ) {
	if ( !this )
		return false;
	if ( auto cc = client_class( ) )
		return cc->class_id == classid_t::CObjectSentrygun || cc->class_id == classid_t::CObjectDispenser || cc->class_id == classid_t::CObjectTeleporter;
	return false;
}

bool player_t::is_sentrygun( ) {
	if ( !this )
		return false;
	if ( auto cc = client_class( ) )
		return cc->class_id == classid_t::CObjectSentrygun;
	return false;
}

bool player_t::is_object( ) {
	if ( !this )
		return false;

	auto cc = client_class( );

	if ( !cc )
		return false;

	switch ( cc->class_id ) {
		case classid_t::CObjectSentrygun:
		case classid_t::CObjectDispenser:
		case classid_t::CObjectTeleporter: return true;
		default: return false;
	}
}

const char* player_t::object_name( ) {
	if ( !this )
		return "";

	auto cc = client_class( );

	if ( !cc )
		return "";

	switch ( cc->class_id ) {
		case classid_t::CObjectSentrygun: return "Sentry";
		case classid_t::CObjectDispenser: return "Dispenser";
		case classid_t::CObjectTeleporter: return "Teleporter";
		default: return "Object";
	}
}

bool player_t::is_player_on_steam_friends_list( ) {
	if ( this && is_player( ) && offsets::is_player_on_steam_friends_list )
		return ( ( bool( __thiscall* )( void*, void* ) )offsets::is_player_on_steam_friends_list )( this, this );
	return false;
}

int player_t::hitbox_count( ) {
	if ( auto model = get_model( ) ) {
		if ( auto hdr = offsets::modelinfo->GetStudiomodel( model ) ) {
			matrix3x4_t bones[ 128 ];
			if ( setup_bones( bones, 128, 0x100, offsets::globals->curtime ) ) {
				if ( auto set = hdr->GetHitboxSet( hitboxset( ) ) )
					return set->numhitboxes;
			}
		}
	}

	return 0;
}

vec3_t player_t::hitbox_pos( int idx ) {
	if ( auto model = get_model( ) ) {
		if ( auto hdr = offsets::modelinfo->GetStudiomodel( model ) ) {
			matrix3x4_t bones[ 128 ];
			if ( setup_bones( bones, 128, 0x100, offsets::globals->curtime ) ) {
				if ( auto set = hdr->GetHitboxSet( hitboxset( ) ) ) {
					if ( auto box = set->pHitbox( idx ) )
						return ( ( box->bbmin + box->bbmax ) * 0.5f ).transform( bones[ box->bone ] );
				}
			}
		}
	}

	return { };
}

weapon_t* player_t::active_weapon( ) {
	return ( weapon_t* )offsets::entity_list->GetClientEntityFromHandle( *( int* )( ( uintptr_t )this + 0xdb8 ) );
}

bool player_t::compute_bbox( rect_t& bbox_out ) {
	const auto& mins_ = mins( ), &maxs_ = maxs( );
	const matrix3x4_t& matrix = world_transform( );

	std::array< vec3_t, 8 > points = {
		vec3_t( mins_.x, mins_.y, mins_.z ),
		vec3_t( mins_.x, maxs_.y, mins_.z ),
		vec3_t( maxs_.x, maxs_.y, mins_.z ),
		vec3_t( maxs_.x, mins_.y, mins_.z ),
		vec3_t( maxs_.x, maxs_.y, maxs_.z ),
		vec3_t( mins_.x, maxs_.y, maxs_.z ),
		vec3_t( mins_.x, mins_.y, maxs_.z ),
		vec3_t( maxs_.x, mins_.y, maxs_.z )
	};

	auto left = std::numeric_limits< float >::max( );
	auto top = std::numeric_limits< float >::max( );
	auto right = std::numeric_limits< float >::lowest( );
	auto bottom = std::numeric_limits< float >::lowest( );

	std::array< vec2_t, 8 > screen;

	for ( std::size_t i = 0; i < 8; i++ ) {
		if ( !c_utils::world_to_screen( points[ i ].transform( matrix ), screen[ i ] ) )
			return { };

		left = std::min( left, screen[ i ].x );
		top = std::min( top, screen[ i ].y );
		right = std::max( right, screen[ i ].x );
		bottom = std::max( bottom, screen[ i ].y );
	}

	auto x = left;
	auto y = top;
	auto w = right - left;
	auto h = bottom - top;

	if ( is_player( ) ) {
		x += ( ( right - left ) / 8.f );
		w -= ( ( ( right - left ) / 8.f ) * 2.f );
	}

	bbox_out = { ( int )x, ( int )y, ( int )w, ( int )h };
	return true;
}

bool player_t::in_cond( int cond ) {
	switch ( cond / 32 ) {
		case 0: {
			const int bit = ( 1 << cond );
			if ( ( player_cond( ) & bit ) == bit )
				return true;
			if ( ( condition_bits( ) & bit ) == bit )
				return true;
			return false;
		}

		case 1: {
			const int bit = 1 << ( cond - 32 );
			if ( ( player_cond_ex( ) & bit ) == bit )
				return true;
			return false;
		}

		case 2: {
			const int bit = 1 << ( cond - 64 );
			if ( ( player_cond_ex2( ) & bit ) == bit )
				return true;
			return false;
		}

		case 3: {
			const int bit = 1 << ( cond - 96 );
			if ( ( player_cond_ex3( ) & bit ) == bit )
				return true;
			return false;
		}

		case 4: {
			const int bit = 1 << ( cond - 128 );
			if ( ( player_cond_ex4( ) & bit ) == bit )
				return true;
			return false;
		}

		default: return false;
	}
}

bool player_t::is_crit_boosted( ) {
    if ( in_cond( TF_COND_CRITBOOSTED ) || in_cond( TF_COND_CRITBOOSTED_PUMPKIN ) || in_cond( TF_COND_CRITBOOSTED_USER_BUFF ) || in_cond( TF_COND_CRITBOOSTED_DEMO_CHARGE ) ||
        in_cond( TF_COND_CRITBOOSTED_FIRST_BLOOD ) || in_cond( TF_COND_CRITBOOSTED_BONUS_TIME ) || in_cond( TF_COND_CRITBOOSTED_CTF_CAPTURE ) || in_cond( TF_COND_CRITBOOSTED_ON_KILL ) ||
        in_cond( TF_COND_CRITBOOSTED_CARD_EFFECT ) || in_cond( TF_COND_CRITBOOSTED_RUNE_TEMP ) )
        return true;

    if ( auto weapon = active_weapon( ) ) {
        if ( in_cond( TF_COND_CRITBOOSTED_RAGE_BUFF ) && weapon->get_slot( ) == weapon_slots_t::slot_primary )
            return true;

        auto crit_health_percent = c_utils::attribute_hook_float( 1.f, "mult_crit_when_health_is_below_percent", weapon );

        if ( crit_health_percent < 1.f && std::clamp( ( float )health( ) / ( float )max_health( ), .0f, 1.f ) < crit_health_percent )
            return true;
    }

    return false;
}

bool player_t::is_invulnerable( ) {
    return ( in_cond( TF_COND_INVULNERABLE ) || in_cond( TF_COND_PHASE ) );
}

int player_t::get_ammo_count( int ammo_type ) {
	return ( ( int( __thiscall* )( void*, int ) )offsets::get_ammo_count )( this, ammo_type );
}

player_t* player_t::first_move_child( ) {
	return ( player_t* )offsets::entity_list->GetClientEntity( *( int* )( ( uintptr_t )this + 0x1b0 ) & 0xfff );
}

player_t* player_t::next_move_peer( ) {
	return ( player_t* )offsets::entity_list->GetClientEntity( *( int* )( ( uintptr_t )this + 0x1b4 ) & 0xfff );
}

player_t* player_t::get_thrower( ) {
	return ( player_t* )offsets::entity_list->GetClientEntityFromHandle( thrower( ) );
}