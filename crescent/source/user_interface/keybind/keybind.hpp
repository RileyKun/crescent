#pragma once
#include "../base_element/base_element.hpp"

class c_keybind : public c_base_element {
	int* value = nullptr;
	bool once = false, toggled = false, pressed = false;
	float switch_interp = 0.f, hover_interp = 0.f;
public:
	c_keybind( int* value_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};