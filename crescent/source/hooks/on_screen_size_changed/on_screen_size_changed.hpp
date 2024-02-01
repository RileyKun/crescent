#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace on_screen_size_changed {
		using fn = void( __fastcall* )( REGISTERS, int, int );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, int old_width, int old_height );
		void init( );
	}
}