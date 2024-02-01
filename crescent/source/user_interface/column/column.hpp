#pragma once
#include "../separator/separator.hpp"
#include "../checkbox/checkbox.hpp"
#include "../slider/slider.hpp"
#include "../combobox/combobox.hpp"
#include "../keybind/keybind.hpp"
#include "../button/button.hpp"
#include "../color_picker/color_picker.hpp"
#include "../multi_combobox/multi_combobox.hpp"

class c_column : public c_base_element {
	std::deque< std::shared_ptr< c_base_element > > elements = { };
	void paint_children( );
	void update_children( );
public:
	bool is_last = false;
	std::shared_ptr< c_separator > create_separator( const char* name );
	std::shared_ptr< c_checkbox > create_checkbox( bool& value, const char* name );
	std::shared_ptr< c_slider_int > create_slider( int& value, int min, int max, int step, const char* name, const char* unit );
	std::shared_ptr< c_slider_float > create_slider( float& value, float min, float max, float step, const char* name, const char* unit );
	std::shared_ptr< c_combobox > create_combobox( int& value, std::vector< std::string > options, const char* name );
	std::shared_ptr< c_multi_combobox > create_multi_combobox( std::vector< bool* > values, std::vector< std::string > options, const char* name );
	std::shared_ptr< c_keybind > create_keybind( int& value, const char* name );
	std::shared_ptr< c_button > create_button( c_button::callback_fn callback, const char* name );
	std::shared_ptr< c_color_picker > create_color_picker( clr_t& value, const char* name );
	c_column( );
	void paint( ) override;
	void update( ) override;
};