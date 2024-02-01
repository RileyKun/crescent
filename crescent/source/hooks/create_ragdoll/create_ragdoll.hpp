#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace create_ragdoll {
		using fn = void( __fastcall* )( REGISTERS );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS );
		void init( );
	}
}