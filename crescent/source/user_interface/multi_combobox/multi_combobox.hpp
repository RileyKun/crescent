#pragma once
#include "../base_element/base_element.hpp"

class c_multi_combobox : public c_base_element {
	std::vector< bool* > values = { };
	std::vector< std::string > options = { };
	float hover_interp = 0.f;
	bool pressed = false, toggled = false;
public:
	c_multi_combobox( std::vector< bool* > values_, std::vector< std::string > options_, const char* name_ );
	void paint( ) override;
	void update( ) override;
};