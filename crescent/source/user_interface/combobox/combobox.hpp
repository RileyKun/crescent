#pragma once
#include "../base_element/base_element.hpp"

class c_combobox : public c_base_element {
	int* value = nullptr;
	std::vector< std::string > options = { };
	float hover_interp = 0.f;
	bool pressed_l = false, pressed_r = false;
public:
	c_combobox( int* value_, std::vector< std::string > options_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};