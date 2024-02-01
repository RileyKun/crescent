#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace wnd_proc {
		inline WNDPROC o_call = nullptr;
		inline HWND game_window = nullptr;
		LRESULT CALLBACK function( HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam );
		void init( );
		void uninit( );
	}
}