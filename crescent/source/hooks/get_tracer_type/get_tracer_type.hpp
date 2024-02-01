#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace get_tracer_type {
		using fn = const char*( __fastcall* )( REGISTERS );
		inline fn o_call = nullptr;
		const char* __fastcall function( REGISTERS );
		void init( );
	}
}