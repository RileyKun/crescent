#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace random_seed {
		using fn = void( __cdecl* )( int );
		inline fn o_call = nullptr;
		void __cdecl function( int seed );
		void init( );
	}
}