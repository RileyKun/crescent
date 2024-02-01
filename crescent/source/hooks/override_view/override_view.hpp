#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace override_view {
		using fn = void( __fastcall* )( REGISTERS, CViewSetup* );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, CViewSetup* setup );
		void init( );
	}
}