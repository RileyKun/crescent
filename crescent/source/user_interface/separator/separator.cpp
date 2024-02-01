#include "separator.hpp"

c_separator::c_separator( const char* name_ ) {
	name = name_;
	type = element_type_t::element_separator;
}

void c_separator::paint( ) {
	//sdk::render->rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255, 125 ), .02f ) );
	sdk::render->text( area.x + 2, area.y, sdk::render->ui_font.handle, sdk::text_align::align_default, clr_t::blend( settings::colors::ui_background, settings::colors::ui_accent, .7f ), name );
	sdk::render->line( { area.x, area.y + area.h, area.x + area.w, area.y + area.h }, clr_t::blend( settings::colors::ui_background, settings::colors::ui_accent, .7f ) );
}

void c_separator::update( ) {

}