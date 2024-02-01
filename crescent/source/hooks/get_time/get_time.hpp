#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace get_time {
		using fn = float( __fastcall* )( REGISTERS );
		inline fn o_call = nullptr;
		float __fastcall function( REGISTERS );
		void init( );
	}
}