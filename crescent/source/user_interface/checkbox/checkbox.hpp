#pragma once
#include "../base_element/base_element.hpp"

class c_checkbox : public c_base_element {
	bool* value = nullptr, once = false, pressed = false;
	float switch_interp = 0.f, hover_interp = 0.f;
public:
	c_checkbox( bool* value_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};