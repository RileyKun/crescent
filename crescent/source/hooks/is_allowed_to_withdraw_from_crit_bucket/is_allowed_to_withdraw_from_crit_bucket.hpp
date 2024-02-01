#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace is_allowed_to_withdraw_from_crit_bucket {
		using fn = void( __fastcall* )( REGISTERS, float );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, float damage );
		void init( );
	}
}