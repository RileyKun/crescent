#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace set_color_modulation {
		using fn = void( __fastcall* )( REGISTERS, float* );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, float* color );
		void init( );
	}
}