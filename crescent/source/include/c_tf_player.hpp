#pragma once
#include "vector.hpp"
#include "util.hpp"
#include "icliententitylist.hpp"
#include "netvar_mgr.hpp"
#include "shareddefs.hpp"
#include "color.hpp"

class weapon_t;
class CUserCmd;
class ClientClass;
struct model_t;

class IHandleEntity {
public:
	virtual ~IHandleEntity( ) { }
	virtual void SetRefEHandle( const unsigned int& handle ) = 0;
	virtual const unsigned int& GetRefEHandle( ) const = 0;
};

class player_resource_t {
public:
    __forceinline int GetHealth( int idx ) {
        if ( !this ) return 0;
        static auto offset = netvar_mgr->get_offset( "CPlayerResource", "m_iHealth" );
        return *( int* )( ( uintptr_t )this + offset + ( idx * 4 ) );
    }

    __forceinline int GetPlayerClass( int idx ) {
        if ( !this ) return 0;
        static auto offset = netvar_mgr->get_offset( "CTFPlayerResource", "m_iPlayerClass" );
        return *( int* )( ( uintptr_t )this + offset + ( idx * 4 ) );
    }

    __forceinline int GetDamage( int idx ) {
        if ( !this ) return 0;
        static auto offset = netvar_mgr->get_offset( "CTFPlayerResource", "m_iDamage" );
        return *( int* )( ( uintptr_t )this + offset + ( idx * 4 ) );
    }
};

class player_t {
public:
	netvar(simtime, float, "CBaseEntity", "m_flSimulationTime");
	netvar(thrower, int, "CBaseGrenade", "m_hThrower");
	netvar(team, int, "CBaseEntity", "m_iTeamNum");
	netvar(hitboxset, int, "CBaseAnimating", "m_nHitboxSet");
	netvar(origin, vec3_t, "CBaseEntity", "m_vecOrigin");
	netvar(mins, vec3_t, "CBaseEntity", "m_vecMins");
	netvar(maxs, vec3_t, "CBaseEntity", "m_vecMaxs");
	netvar(view_offset, vec3_t, "CBasePlayer", "m_vecViewOffset[0]");
	netvar(punch_ang, vec3_t, "CBasePlayer", "m_vecPunchAngle");
	netvar(deadflag, bool, "CBasePlayer", "deadflag");
	netvar(tickbase, int, "CBasePlayer", "m_nTickBase");
	netvar(velocity, vec3_t, "CBasePlayer", "m_vecVelocity[0]");
	netvar(base_velocity, vec3_t, "CBasePlayer", "m_vecBaseVelocity");
	netvar(max_speed, float, "CBasePlayer", "m_flMaxspeed");
	netvar(flags, int, "CBasePlayer", "m_fFlags");
	netvar(class_, int, "CTFPlayer", "m_iClass");
	netvar(force_taunt_cam, int, "CTFPlayer", "m_nForceTauntCam");
	netvar(fov, int, "CBasePlayer", "m_iFOV" );
	netvar(health, int, "CBasePlayer", "m_iHealth");
	netvar(next_attack, float, "CBaseCombatCharacter", "m_flNextAttack");
	netvar(feign_death_ready, bool, "CTFPlayer", "m_bFeignDeathReady");
	netvar(condition_bits, int, "CTFPlayer", "_condition_bits");
	netvar(player_cond, int, "CTFPlayer", "m_nPlayerCond");
	netvar(player_cond_ex, int, "CTFPlayer", "m_nPlayerCondEx");
	netvar(player_cond_ex2, int, "CTFPlayer", "m_nPlayerCondEx2");
	netvar(player_cond_ex3, int, "CTFPlayer", "m_nPlayerCondEx3");
	netvar(player_cond_ex4, int, "CTFPlayer", "m_nPlayerCondEx4");
	netvar(observer_mode, int, "CBasePlayer", "m_iObserverMode");
	netvar(ground_ent, int, "CBasePlayer", "m_hGroundEntity");
	netvar(water_lvl, unsigned char, "CTFPlayer", "m_nWaterLevel");
	netvar(ducked, bool, "CBasePlayer", "m_bDucked");
	netvar(ducking, bool, "CBasePlayer", "m_bDucking");
	netvar(in_duck_jump, bool, "CBasePlayer", "m_bInDuckJump");
	netvar(ducktime, float, "CBasePlayer", "m_flDucktime");
	netvar(duck_jump_time, float, "CBasePlayer", "m_flDuckJumpTime");
	netvar(model_scale, float, "CBaseAnimating", "m_flModelScale");
	netvar(obj_health, int, "CBaseObject", "m_iHealth");
	netvar(obj_max_health, int, "CBaseObject", "m_iMaxHealth");
	netvar(crit_mult, int, "CTFPlayer", "m_iCritMult");
	netvar(eye_angles, vec3_t, "CTFPlayer", "m_angEyeAngles[0]");
	netvar(precip_type, int, "CPrecipitation", "m_nPrecipType");

	__forceinline CUserCmd*& current_cmd( ) {
		return *( CUserCmd**)( ( uintptr_t )this + 0x1184 );
	};

	__forceinline float& invisibility( ) {
		return *( float* )( ( uintptr_t )this + 0x1A38 );
	};

	__forceinline vec3_t& velocity_( ) {
		return *( vec3_t* )( ( uintptr_t )this + 0x120 );
	};

	__forceinline int& pipebomb_type( ) {
		return *( int* )( ( uintptr_t )this + 0x8fc );
	};

	__forceinline bool& touched( ) {
		return *( bool* )( ( uintptr_t )this + 0x8f8 );
	};

	__forceinline MoveType_t& movetype( ) {
		return *( MoveType_t* )( ( uintptr_t )this + 0x1A4 );
	};

	__forceinline int idx( ) {
		return c_utils::get_vfunc< 9, int >( this + 8 );
	}

	__forceinline int max_health( ) {
		return c_utils::get_vfunc< 107, int >( this );
	}

	__forceinline void on_pre_data_changed( int type ) {
		return c_utils::get_vfunc< 4, void >( this + 8, type );
	}

	__forceinline void on_data_changed( int type ) {
		return c_utils::get_vfunc< 5, void >( this + 8, type );
	}

	__forceinline void pre_data_update( int type ) {
		return c_utils::get_vfunc< 6, void >( this + 8, type );
	}

	__forceinline void post_data_update( int type ) {
		return c_utils::get_vfunc< 7, void >( this + 8, type );
	}

	__forceinline bool dormant( ) {
		return c_utils::get_vfunc< 8, bool >( this + 8 );
	}

	__forceinline ClientClass* client_class( ) {
		return c_utils::get_vfunc< 2, ClientClass* >( this + 8 );
	}

	__forceinline vec3_t shoot_pos( ) {
		return origin( ) + view_offset( );
	}

	__forceinline bool setup_bones(matrix3x4_t* pOut, int nMax, int nMask, float flTime) {
		return c_utils::get_vfunc< 16, bool, matrix3x4_t*, int, int, float >(this + 4, pOut, nMax, nMask, flTime);
	}

	__forceinline model_t* get_model( ) {
		return c_utils::get_vfunc< 9, model_t* >( this + 4 );
	}

	__forceinline int draw_model( int flags ) {
		return c_utils::get_vfunc< 10, int, int >( this + 4, flags );
	}


	inline matrix3x4_t& world_transform( ) {
		return c_utils::get_vfunc< 34, matrix3x4_t& >( this + 4 );
	}

	__forceinline vec3_t center_pos( ) {
		return origin( ) + vec3_t( .0f, .0f, ( mins( ).z + maxs( ).z ) * .5f );
	}

	__forceinline bool has_hitboxes( ) {
		return ( is_player( ) || is_sentrygun( ) );
	}

	bool is_player( );
	bool is_projectile( );
	bool is_stickybomb( );
	bool is_resource( );
	bool is_building( );
	bool is_sentrygun( );
	bool is_object( );
	const char* object_name( );
	bool is_player_on_steam_friends_list( );
	int hitbox_count( );
	vec3_t hitbox_pos( int idx );
	weapon_t* active_weapon( );
	bool compute_bbox( rect_t& bbox_out );
	bool in_cond( int cond );
	bool is_crit_boosted( );
	bool is_invulnerable( );
	int get_ammo_count( int ammo_type );
	player_t* first_move_child( );
	player_t* next_move_peer( );
	player_t* get_thrower( );
};

using entity_t = player_t;