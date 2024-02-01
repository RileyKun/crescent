#include "column.hpp"

void c_column::paint_children( ) {
	for ( const auto& e : elements )
		e->paint( );
}

void c_column::update_children( ) {
	if ( elements.empty( ) )
		return;

	auto offset_x = 4, offset_y = 4;
	std::shared_ptr< c_base_element > active_combobox = { };

	for ( auto i{ 0u }; i < elements.size( ); i++ ) {
		auto& e = elements[ i ];

		switch ( e->type ) {
			case element_type_t::element_separator: {
				e->area = { area.x + offset_x, area.y + offset_y, area.w - offset_x * 2, sdk::render->ui_font.tall + 2 };
				offset_y += e->area.h + 5;
				break;
			}

			case element_type_t::element_checkbox:
			case element_type_t::element_slider: {
				e->area = { area.x + offset_x, area.y + offset_y, area.w - offset_x * 2, sdk::render->ui_font.tall };
				offset_y += e->area.h + 5;
				break;
			}

			case element_type_t::element_keybind:
			case element_type_t::element_combobox:
			case element_type_t::element_button:
			case element_type_t::element_color_picker: {
				e->area = { area.x + offset_x, area.y + offset_y, area.w - offset_x * 2, sdk::render->ui_font.tall + 4 };
				offset_y += e->area.h + 5;
				break;
			}

			default: break;
		}

		e->update( );
	}
}

std::shared_ptr< c_separator > c_column::create_separator( const char* name ) {
	auto e = std::make_shared< c_separator >( name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_checkbox > c_column::create_checkbox( bool& value, const char* name ) {
	auto e = std::make_shared< c_checkbox >( &value, name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_slider_int > c_column::create_slider( int& value, int min, int max, int step, const char* name, const char* unit ) {
	auto e = std::make_shared< c_slider_int >( &value, min, max, step, name, unit );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_slider_float > c_column::create_slider( float& value, float min, float max, float step, const char* name, const char* unit ) {
	auto e = std::make_shared< c_slider_float >( &value, min, max, step, name, unit );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_combobox > c_column::create_combobox( int& value, std::vector< std::string > options, const char* name ) {
	auto e = std::make_shared< c_combobox >( &value, options, name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_multi_combobox > c_column::create_multi_combobox( std::vector< bool* > values, std::vector< std::string > options, const char* name ) {
	auto e = std::make_shared< c_multi_combobox >( values, options, name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_keybind > c_column::create_keybind( int& value, const char* name ) {
	auto e = std::make_shared< c_keybind >( &value, name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_button > c_column::create_button( c_button::callback_fn callback, const char* name ) {
	auto e = std::make_shared< c_button >( callback, name );
	elements.emplace_back( e );
	return e;
}

std::shared_ptr< c_color_picker > c_column::create_color_picker( clr_t& value, const char* name ) {
	auto e = std::make_shared< c_color_picker >( &value, name );
	elements.emplace_back( e );
	return e;
}

c_column::c_column( ) {
	type = element_type_t::element_column;
}

void c_column::paint( ) {
	sdk::render->clip( { area.x, area.y, area.w + 1, area.h } );
	{
		if ( !is_last )
			sdk::render->line( { area.x + area.w, area.y + 4, area.x + area.w, area.y + area.h - 4 }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );

		paint_children( );
	}
	sdk::render->reset_clip( );
}

void c_column::update( ) {
	update_children( );
}