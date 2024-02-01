#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace paint {
		using fn = void( __fastcall* )( REGISTERS, int );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, int mode );
		void init( );
	}
}