#pragma once
#include "../base_element/base_element.hpp"

class c_color_picker : public c_base_element {
	clr_t* value = nullptr;
	bool once = false, toggled = false, pressed = true;
	float switch_interp = 0.f, hover_interp = 0.f;
public:
	c_color_picker( clr_t* value_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};