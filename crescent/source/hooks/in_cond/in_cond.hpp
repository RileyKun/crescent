#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace in_cond {
		using fn = bool( __fastcall* )( REGISTERS, int );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS, int cond );
		void init( );
	}
}