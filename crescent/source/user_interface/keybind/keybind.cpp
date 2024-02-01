#include "keybind.hpp"
#include "../user_interface.hpp"

c_keybind::c_keybind( int* value_, const char* name_ ) {
	value = value_;
	name = name_;
	type = element_type_t::element_keybind;
}

void c_keybind::paint( ) {
	if ( !once ) {
		switch_interp = .75f;
		hover_interp = .5f;
		once = true;
	}

	switch_interp = sdk::render->lerp( switch_interp, toggled ? 1.f : .75f, settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, toggled ? 1.f : input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	sdk::render->rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->outlined_rectangle( area, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ), clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .2f ), hover_interp ) );
	sdk::render->text( area.x + 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, switch_interp ), name );
	sdk::render->text( area.x + area.w - 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_left | sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, switch_interp ), toggled ? "..." : input->key_to_str( *value ) );
}

void c_keybind::update( ) {
	if ( input->hovering( area ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) && input->key_pressed( VK_LBUTTON ) ) {
		toggled = !toggled;
		pressed = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( pressed && !input->key_down( VK_LBUTTON ) ) {
		pressed = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	if ( !toggled )
		return;

	user_interface->is_keybind_active = true;

	for ( auto i{ 0 }; i < 255; ++i ) {
		if ( GetAsyncKeyState( i ) && i != 3 ) {
			if ( i == VK_SHIFT || i == VK_LBUTTON || i == VK_RBUTTON )
				continue;

			if ( i == VK_ESCAPE ) {
				*value = 0;
				toggled = false;
				break;
			}

			else if ( strcmp( "none", input->key_to_str( i ) ) != 0 ) {
				*value = i;
				toggled = false;
				break;
			}
		}
	}
}