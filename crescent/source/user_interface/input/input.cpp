#include "input.hpp"

void c_input::poll( ) {
	for ( auto n{ 0 }; n < 256; n++ ) {
		last_key_state[ n ] = prestine_key_state[ n ];
		key_state[ n ] = GetAsyncKeyState( n );
		prestine_key_state[ n ] = key_state[ n ];
	}

	offsets::surface->SurfaceGetCursorPos( mouse_x, mouse_y );
}

bool c_input::key_down( int key ) const {
	return key_state[ key ];
}

bool c_input::key_pressed( int key ) const {
	return key_state[ key ] && !last_key_state[ key ];
}

bool c_input::hovering( rect_t area ) const {
	return mouse_x > area.x && mouse_x < area.x + area.w && mouse_y > area.y && mouse_y < area.y + area.h;
}

void c_input::set_key( const int key, bool state ) {
	key_state[ key ] = state;
}

const char* c_input::key_to_str( const int key ) {
	return keys[ key ];
}