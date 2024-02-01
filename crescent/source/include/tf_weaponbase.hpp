#pragma once
#include "netvar_mgr.hpp"
#include "shareddefs.hpp"

enum struct weapon_slots_t {
	slot_primary, slot_secondary, slot_melee
};

class weapon_t {
public:
	netvar( item_def_idx, int, "CEconEntity", "m_iItemDefinitionIndex" );
	netvar( clip1, int, "CBaseCombatWeapon", "m_iClip1" );
	netvar( next_primary_attack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack" );
	netvar( next_secondary_attack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack" );
	netvar( weapon_state, MinigunState_t, "CTFMinigun", "m_iWeaponState" );
	netvar( crit_shot, bool, "CTFMinigun", "m_bCritShot" );
	netvar( owner_entity, int, "CBaseEntity", "m_hOwnerEntity" );
	netvar( last_fire_time, float, "CTFWeaponBase", "m_flLastFireTime" );
	netvar( charge_dmg, float, "CTFSniperRifle", "m_flChargedDamage" );
	netvar( charge_begin_time, float, "CTFPipebombLauncher", "m_flChargeBeginTime" );
	netvar( observed_crit_chance, float, "CTFWeaponBase", "m_flObservedCritChance" );
	netvar( primary_ammo_type, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType" );

	__forceinline int airblast_cost( ) {
		switch ( item_def_idx( ) ) {
			case Pyro_m_FestiveBackburner:
			case Pyro_m_TheBackburner: return 50;
			case Pyro_m_TheDegreaser: return 25;
			default: return 20;
		}
	}

	__forceinline float get_swing_range( ) {
		return ( get_weapon_id( ) == TF_WEAPON_SWORD ) ? 72.f : 48.f;
	}

	__forceinline float get_smack_time( ) {
		static auto offset = netvar_mgr->get_offset( "CTFWeaponBase", "m_nInspectStage" ) + 0x1c;
		return *( float* )( ( uintptr_t )this + offset );
	}

	__forceinline int idx( ) {
		return c_utils::get_vfunc< 9, int >( this + 8 );
	}

	__forceinline bool are_random_crits_enabled( ) {
		return c_utils::get_vfunc< 402, bool >( this );
	}

	__forceinline int& weapon_mode( ) {
		return *( int* )( ( uintptr_t )this + 0xb28 );
	}

	__forceinline bool is_drag_affected( ) {
		return ( get_weapon_id( ) == TF_WEAPON_PIPEBOMBLAUNCHER || get_weapon_id( ) == TF_WEAPON_GRENADELAUNCHER );
	}

	__forceinline bool is_rapidfire( ) {
		if ( !this )
			return false;

		switch ( item_def_idx( ) ) {
			case Heavy_m_Tomislav:
			case Sniper_s_TheCleanersCarbine:
			case Scout_m_TheShortstop: return true;
		}

		switch ( get_weapon_id( ) ) {
			case TF_WEAPON_MINIGUN:
			case TF_WEAPON_FLAMETHROWER:
			case TF_WEAPON_PISTOL:
			case TF_WEAPON_SMG:
			case TF_WEAPON_PISTOL_SCOUT: return true;
		}

		return false;
	}

	__forceinline float rapidfire_fire_delay( ) {
		if ( !this )
			return 0.f;

		switch ( item_def_idx( ) ) {
			case Heavy_m_Tomislav: return .12f;
			case Scout_m_TheShortstop: return .36f;
			case Sniper_s_TheCleanersCarbine: return .135f;
		}

		switch ( get_weapon_id( ) ) {
			case TF_WEAPON_SMG:
			case TF_WEAPON_MINIGUN:
			case TF_WEAPON_FLAMETHROWER: return .105f;
			case TF_WEAPON_PISTOL: return .15f;
			case TF_WEAPON_PISTOL_SCOUT: return .1275f;
		}

		return 0.f;
	}

	__forceinline int& random_seed( ) {
		return *( int* )( ( uintptr_t )this + 0xb5c );
	}

	__forceinline float& crit_token_bucket( ) {
		return *( float* )( ( uintptr_t )this + 0xa54 );
	}

	__forceinline int& crit_checks( ) {
		return *( int* )( ( uintptr_t )this + 0xa58 );
	}

	__forceinline int& crit_seed_requests( ) {
		return *( int* )( ( uintptr_t )this + 0xa5c );
	}

	__forceinline float& crit_time( ) {
		return *( float* )( ( uintptr_t )this + 0xb50 );
	}

	__forceinline float& last_crit_check_time( ) {
		return *( float* )( ( uintptr_t )this + 0xb54 );
	}

	__forceinline float& last_rapid_fire_crit_check_time( ) {
		return *( float* )( ( uintptr_t )this + 0xb60 );
	}

	__forceinline float& uber_charge( ) {
		return *( float* )( ( uintptr_t )this + 0xc6c );
	}

	__forceinline int& reload_mode( ) {
		return *( int* )( ( uintptr_t )this + 0xb28 );
	}

	__forceinline weapon_slots_t get_slot( ) {
		return c_utils::get_vfunc< 330, weapon_slots_t >( this );
	}

	__forceinline int get_weapon_id( ) {
		return c_utils::get_vfunc< 381, int >( this );
	}

	__forceinline bool reloading( ) {
		static auto offset = netvar_mgr->get_offset( "CBaseCombatWeapon", "m_flNextPrimaryAttack" ) + 0xc;
		auto in_reload = *( bool* )( this + offset );
		return ( in_reload || reload_mode( ) != 0 );
	}

	__forceinline bool can_headshot( ) {
		return ( is_headshot_weapon( ) && can_fire_critical_shot( true ) && ambassador_can_headshot( ) );
	}

	CHudTexture* get_weapon_icon( );
	weapon_info_t* get_weapon_info( );
	player_t* get_healing_target( );
	bool is_headshot_weapon( );
	bool can_fire_critical_shot( const bool headshot );
	bool can_weapon_random_crit( );
	bool ambassador_can_headshot( );
};