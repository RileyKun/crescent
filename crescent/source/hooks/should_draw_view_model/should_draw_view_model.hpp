#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace should_draw_view_model {
		using fn = bool( __fastcall* )( REGISTERS );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS );
		void init( );
	}
}