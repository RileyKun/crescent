#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace cl_load_whitelist {
		using fn = void*( __cdecl* )( void*, const char* );
		inline fn o_call = nullptr;
		void* __cdecl function( void* table, const char* name );
		void init( );
	}
}