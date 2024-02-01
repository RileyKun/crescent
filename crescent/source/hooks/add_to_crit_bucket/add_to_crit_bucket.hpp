#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace add_to_crit_bucket {
		using fn = void( __fastcall* )( REGISTERS, float );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, float amount );
		void init( );
	}
}