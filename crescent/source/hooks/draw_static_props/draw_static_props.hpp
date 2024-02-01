#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace draw_static_props {
		using fn = void( __fastcall* )( REGISTERS, void**, int, bool, bool );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, void** props, int count, bool shadow_depth, bool draw_vcollide_wireframe );
		void init( );
	}
}