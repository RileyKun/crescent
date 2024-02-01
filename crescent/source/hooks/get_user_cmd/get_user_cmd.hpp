#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace get_user_cmd {
		using fn = CUserCmd*( __fastcall* )( REGISTERS, int );
		inline fn o_call = nullptr;
		CUserCmd* __fastcall function( REGISTERS, int sequence_num );
		void init( );
	}
}