#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace base_interpolate_part1 {
		using fn = int( __fastcall* )( REGISTERS, float&, vec3_t&, vec3_t&, vec3_t&, int& );
		inline fn o_call = nullptr;
		int __fastcall function( REGISTERS, float& current_time, vec3_t& old_origin, vec3_t& old_angles, vec3_t& old_velocity, int& no_more_changes );
		void init( );
	}
}