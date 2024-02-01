#pragma once
#include "window/window.hpp"

struct multi_combo_data_t {
	bool is_active = false;
	std::vector< bool* > values = { };
	std::vector< std::string > options = { };
	rect_t element_area = { }, render_area = { };

	multi_combo_data_t( ) {
		is_active = false;
		values = { }, options = { };
		element_area = { }, render_area = { };
	}
};

struct picker_data_t {
	bool is_active = false, picker_ = false,
		hue_ = false, alpha_ = false;
	clr_t* value = nullptr;
	rect_t element_area = { }, render_area = { };

	picker_data_t( ) {
		is_active = false, picker_ = false,
			hue_ = false, alpha_ = false;
		value = nullptr;
		element_area = { }, render_area = { };
	}
};

class c_user_interface {
	std::deque< std::shared_ptr< c_base_draggable > > elements = { };
public:
	bool is_open = false, is_keybind_active = false;
	multi_combo_data_t multi_combo_data = multi_combo_data_t( );
	picker_data_t picker_data = picker_data_t( );
private:
	std::shared_ptr< c_window > create_window( const char* name, rect_t area );
private:
	void handle_multi_combo( );
	void handle_color_picker( );
public:
	void init( );
	void on_paint( );
};

inline c_user_interface* user_interface = new c_user_interface;