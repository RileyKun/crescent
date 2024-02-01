#pragma once
#include "../base_element/base_element.hpp"

class c_separator : public c_base_element {
public:
	c_separator( const char* name_ );
	void paint( ) override;
	void update( ) override;
};