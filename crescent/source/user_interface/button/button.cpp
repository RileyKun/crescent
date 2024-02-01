#include "button.hpp"
#include "../user_interface.hpp"

c_button::c_button( callback_fn callback_, const char* name_ ) {
	callback = callback_;
	name = name_;
	type = element_type_t::element_button;
}

void c_button::paint( ) {
	if ( !once ) {
		switch_interp = 0.f;
		hover_interp = .5f;
		once = true;
	}

	switch_interp = sdk::render->lerp( switch_interp, pressed, settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, pressed ? 1.f : input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	sdk::render->rectangle( area, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::min( switch_interp, .5f ) ) );
	sdk::render->outlined_rectangle( area, clr_t::blend( settings::colors::ui_background, settings::colors::ui_accent, hover_interp ) );
	sdk::render->text( area.x + ( area.w / 2 ), area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, std::max( switch_interp, .7f ) ), name );
}

void c_button::update( ) {
	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ) {
		pressed = true;

		if ( callback )
			callback( );

		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( pressed && !input->key_down( VK_LBUTTON ) ) {
		pressed = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}
}