#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace cl_move {
		using fn = void( __cdecl* )( float, bool );
		inline fn o_call = nullptr;
		void __cdecl function( float accumulated_extra_samples, bool final_tick );
		void init( );
	}
}