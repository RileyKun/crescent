#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace set_alpha_modulation {
		using fn = void( __fastcall* )( REGISTERS, float );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, float alpha );
		void init( );
	}
}