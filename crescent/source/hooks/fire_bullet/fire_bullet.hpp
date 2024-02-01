#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace fire_bullet {
		using fn = void( __fastcall* )( REGISTERS, weapon_t*, const FireBulletsInfo_t&, bool, int, int );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, weapon_t* wpn, FireBulletsInfo_t& info, bool do_fx, int dmg_type, int custom_dmg_type );
		void init( );
	}
}