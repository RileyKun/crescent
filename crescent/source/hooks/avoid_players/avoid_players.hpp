#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace avoid_players {
		using fn = void( __fastcall* )( REGISTERS, CUserCmd* );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, CUserCmd* cmd );
		void init( );
	}
}