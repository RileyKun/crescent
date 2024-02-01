#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace fire_event_client_side {
		using fn = bool( __fastcall* )( REGISTERS, IGameEvent* );
		inline fn o_call = nullptr;
		bool __fastcall function( REGISTERS, IGameEvent* event );
		void init( );
	}
}