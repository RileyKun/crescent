#pragma once
#include "../base_element/base_element.hpp"

class c_button : public c_base_element {
	bool pressed = false, once = false;
	float switch_interp = 0.f, hover_interp = 0.f;
public:
	typedef void( *callback_fn )( void );
	callback_fn callback;
public:
	c_button( callback_fn callback_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};