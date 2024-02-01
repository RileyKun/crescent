#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace calc_player_view {
		using fn = void( __fastcall* )( REGISTERS, vec3_t&, vec3_t&, float& );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, vec3_t& eye_origin, vec3_t& eye_angles, float& fov );
		void init( );
	}
}