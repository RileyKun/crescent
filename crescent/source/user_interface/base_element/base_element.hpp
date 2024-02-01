#pragma once
#include "../input/input.hpp"

enum struct element_type_t {
	element_unknown,
	element_window,
	element_dynamic,
	element_tab,
	element_column,
	element_separator,
	element_checkbox,
	element_slider,
	element_keybind,
	element_combobox,
	element_button,
	element_color_picker,
};

class c_base_element {
public:
	const char* name = "";
	rect_t area = { };
	element_type_t type = element_type_t::element_unknown;
	virtual void paint( ) = 0;
	virtual void update( ) = 0;
};