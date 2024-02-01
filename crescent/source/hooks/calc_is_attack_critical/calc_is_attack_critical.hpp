#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace calc_is_attack_critical {
		using fn = void( __fastcall* )( REGISTERS );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS );
		void init( );
	}
}