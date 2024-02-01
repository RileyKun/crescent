#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace frame_stage_notify {
		using fn = void( __fastcall* )( REGISTERS, ClientFrameStage_t );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, ClientFrameStage_t stage );
		void init( );
	}
}