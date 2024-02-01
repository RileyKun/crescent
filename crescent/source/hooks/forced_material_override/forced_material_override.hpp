#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace forced_material_override {
		using fn = void( __fastcall* )( REGISTERS, IMaterial*, OverrideType_t );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, IMaterial* mat, OverrideType_t ovr_type );
		void init( );
	}
}