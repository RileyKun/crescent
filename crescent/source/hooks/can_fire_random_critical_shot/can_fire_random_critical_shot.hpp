#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace can_fire_random_critical_shot {
		using fn = bool( __fastcall* )( REGISTERS, float );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS, float crit_chance );
		void init( );
	}
}