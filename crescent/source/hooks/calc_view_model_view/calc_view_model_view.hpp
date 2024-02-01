#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace calc_view_model_view {
		using fn = void( __fastcall* )( REGISTERS, player_t*, vec3_t&, vec3_t& );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, player_t* owner, vec3_t& eye_origin, vec3_t& eye_angles );
		void init( );
	}
}