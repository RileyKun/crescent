#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace get_draw_position {
		using fn = void( __cdecl* )( float*, float*, bool*, vec3_t );
		inline fn o_call = nullptr;
		void __cdecl function( float* x, float* y, bool* behind_camera, vec3_t angle_offset );
		void init( );
	}
}