#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace do_post_screen_space_effects {
		using fn = bool( __fastcall* )( REGISTERS, const CViewSetup* );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS, const CViewSetup* setup );
		void init( );
	}
}