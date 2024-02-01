#pragma once
#include "minhook/minhook.h"
#include "fnv.hpp"
#include "pattern.hpp"
#include <thread>
#include <deque>
#include <vector>
#include <map>
#include <array>
#include <string>

#undef CreateFont
#undef PlaySound
#undef min
#undef max

#define REGISTERS void* ecx, void* edx

class vec3_t;
class vec2_t;
class CUserCmd;
class player_t;
class CGameTrace;
typedef CGameTrace trace_t;

enum struct aim_type_t {
	aim_unknown,
	aim_hitscan,
	aim_projectile,
	aim_melee
};

class c_utils {
public:
	template < typename fn > static fn get_vfunc( void* classbase, int index ) {
		if ( !classbase ) return fn{ };
		return ( fn )( *( uintptr_t** )classbase )[ index ];
	}

	template < size_t index, typename ret, class ... args_ >
	static ret get_vfunc( void* thisptr, args_... args ) {
		using fn = ret( __thiscall* )( void*, args_... );
		auto fn_ptr = ( fn )( *( uintptr_t** )thisptr )[ index ];
		return fn_ptr( thisptr, args... );
	}

	template < typename T = void > static T* get_interface( const char* module_name, const char* interface_name ) {
		if ( const auto module_handle = GetModuleHandleA( module_name ) ) {
			if ( const auto create_interface = ( void*( * )( const char*, int* ) )GetProcAddress( module_handle, "CreateInterface" ) )
				return ( T* )create_interface( interface_name, nullptr );
		}
		return nullptr;
	}

	template < typename T = uintptr_t > static T find_pattern( const char* module_name, const char* pattern, ptrdiff_t offset = 0 ) {
		if ( const auto module_handle = GetModuleHandleA( module_name ) )
			return pattern::first_code_match< T >( module_handle, pattern, offset );
		return ( T )0;
	}

	static std::wstring utf_to_wide( const std::string_view& str ) {
		int count = MultiByteToWideChar( CP_UTF8, 0, str.data( ), str.length( ), NULL, 0 );
		std::wstring wstr( count, 0 );
		MultiByteToWideChar( CP_UTF8, 0, str.data( ), str.length( ), &wstr[ 0 ], count );
		return wstr;
	}

	static void random_seed( int seed ) {
		static auto function = ( void( _cdecl* )( int ) )( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomSeed" ) );
		function( seed );
	}

	static int random_int( int min_val = 0, int max_val = 0x7FFF ) {
		static auto function = ( int( _cdecl* )( int, int ) )( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomInt" ) );
		return function( min_val, max_val );
	}

	static bool string_begins_with( const char* a, const char* b ) {
		if ( strncmp( a, b, strlen( b ) ) == 0 )
			return true;
		return false;
	}

	static std::vector< std::string > split_string( const std::string& str, const std::string& delimiter ) {
		std::vector< std::string > out = { };
		std::string::size_type curr = 0, old = 0;

		while ( ( curr = str.find( delimiter, old ) ) != std::string::npos ) {
			out.push_back( str.substr( old, curr - old ) );
			old = curr + 1;
		}

		out.push_back( str.substr( old ) );
		return out;
	}

	static std::string to_lowercase( std::string input ) {
		std::transform( input.begin( ), input.end( ), input.begin( ),
			[ ]( unsigned char c ) { return std::tolower( c ); } );
		return input;
	}

	static bool world_to_screen( const vec3_t& world, vec2_t& screen );
	static bool is_visible( vec3_t start, vec3_t end, void* ignr_ent, void* target_ent );
	static bool is_visible( vec3_t start, vec3_t end, vec3_t mins, vec3_t maxs, void* ignr_ent, void* target_ent );
	static bool is_low_fps( );
	static void fix_movement( CUserCmd* cmd, vec3_t ang );
	static aim_type_t get_aim_type( );
	static void compute_can_shoot( );
	static float attribute_hook_float( float base_value, const char* search_string, void* entity, void* buffer = nullptr, bool is_global_const_string = false );
	static float get_latency( );
	static void get_projectile_fire_setup( vec3_t offset, vec3_t ang_in, vec3_t& pos_out, vec3_t& ang_out, bool pipes );
	static void get_projectile_fire_setup( vec3_t offset, vec3_t ang_in, vec3_t& pos_out );
	static clr_t get_entity_color( player_t* ent );
	static void coll_trace( player_t* ent, vec3_t direction, trace_t& trace );
	static void line( const vec3_t& position, const vec3_t& position_, clr_t col );
	static void box( const vec3_t& position, const vec3_t& angle, const vec3_t& mins, const vec3_t& maxs, clr_t col );
	static void wireframe_box( const vec3_t& position, const vec3_t& angle, const vec3_t& mins, const vec3_t& maxs, clr_t col );
	static void triangle( const vec3_t& point1, const vec3_t& point2, const vec3_t& point3, clr_t col );
	static void circle( const vec3_t& position, const vec3_t& orientation, float radius, clr_t col );
	static bool is_point_intersecting( const vec3_t& proj_origin, const vec3_t& proj_mins, const vec3_t& proj_maxs, const vec3_t& origin, const vec3_t& mins, const vec3_t& maxs );
};