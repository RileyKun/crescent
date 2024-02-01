#include "combobox.hpp"
#include "../user_interface.hpp"

c_combobox::c_combobox( int* value_, std::vector< std::string > options_, const char* name_ ) {
	value = value_;
	options = options_;
	name = name_;
	type = element_type_t::element_combobox;
}

void c_combobox::paint( ) {
	hover_interp = sdk::render->lerp( hover_interp, input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	sdk::render->rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->outlined_rectangle( area, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ), clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .2f ), hover_interp ) );
	sdk::render->text( area.x + 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, .75f ), name );
	sdk::render->text( area.x + area.w - 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_left | sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, .75f ), options[ *value ].c_str( ) );
}

void c_combobox::update( ) {
	if ( input->hovering( area ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ) {
		if ( input->key_pressed( VK_LBUTTON ) ) {
			pressed_l = true;
			offsets::surface->PlaySound( "ui/buttonclick.wav" );
		}

		else if ( input->key_pressed( VK_RBUTTON ) ) {
			pressed_r = true;
			offsets::surface->PlaySound( "ui/buttonclick.wav" );
		}

		if ( input->key_pressed( VK_LBUTTON ) )
			( *value < ( ( int )options.size( ) - 1 ) ) ? ( *value )++ : *value = 0;

		if ( input->key_pressed( VK_RBUTTON ) )
			( *value > 0 ) ? ( *value )-- : *value = ( ( int )options.size( ) - 1 );
	}

	if ( pressed_l && !input->key_down( VK_LBUTTON ) ) {
		pressed_l = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	else if ( pressed_r && !input->key_down( VK_RBUTTON ) ) {
		pressed_r = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}
}