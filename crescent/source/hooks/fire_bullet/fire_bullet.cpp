#include "fire_bullet.hpp"

void __fastcall hooks::fire_bullet::function( REGISTERS, weapon_t* wpn, FireBulletsInfo_t& info, bool do_fx, int dmg_type, int custom_dmg_type ) {
	if ( !globals::local_player || ecx != globals::local_player )
		return o_call( ecx, edx, wpn, info, do_fx, dmg_type, custom_dmg_type );

	if ( settings::visuals::bullet_tracers && settings::visuals::bullet_tracers != 2 && dmg_type & DMG_CRITICAL )
		dmg_type &= ~DMG_CRITICAL;

	return o_call( ecx, edx, wpn, info, do_fx, dmg_type, custom_dmg_type );
}

void hooks::fire_bullet::init( ) {
	if ( MH_CreateHook( ( fn )offsets::fire_bullet, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook FireBullet" );
}