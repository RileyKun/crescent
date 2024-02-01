#pragma once
#include "../../include/globals.hpp"

class c_input {
	bool key_state[ 256 ] = { }, last_key_state[ 256 ] = { }, prestine_key_state[ 256 ] = { };
	const char* keys[ 253 ] = { "none", "mouse 1", "mouse 2", "ctrl+break", "mouse 3", "mouse 4", "mouse 5", "none", "backspace", "tab", "none", "none", "none", "enter", "none", "none", "shift", "ctrl", "alt", "pause", "caps lock", "none", "none", "none", "none", "none", "none", "esc", "none", "none", "none", "none", "spacebar", "page up", "page down", "end", "home", "left", "up", "right", "down", "none", "print", "none", "print screen", "insert", "delete", "none", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "none", "none", "none", "none", "none", "none", "none", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "left windows", "right windows", "none", "none", "none", "num 0", "num 1", "num 2", "num 3", "num 4", "num 5", "num 6", "num 7", "num 8", "num 9", "*", "+", "_", "-", ".", "/", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24", "none", "none", "none", "none", "none", "none", "none", "none", "num lock", "scroll lock", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "left shift", "right shift", "left ctrl", "right ctrl", "lmenu", "rmenu", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "next track", "previous track", "stop", "play/pause", "none", "none", "none", "none", "none", "none", ";", "+", ",", "-", ".", "/?", "~", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "[{", "\\|", "}]", "'\"", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none", "none" };
public:
	int mouse_x = 0, mouse_y = 0;
public:
	void poll( );
	bool key_down( int key ) const;
	bool key_pressed( int key ) const;
	bool hovering( rect_t area ) const;
	void set_key( const int key, bool state );
	const char* key_to_str( const int key );
};

inline c_input* input = new c_input;