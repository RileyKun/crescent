#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace create_move {
		using fn = bool( __fastcall* )( REGISTERS, float, CUserCmd* );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS, float input_sample_time, CUserCmd* cmd );
		void init( );
	}
}