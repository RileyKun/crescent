#include "checkbox.hpp"
#include "../user_interface.hpp"

c_checkbox::c_checkbox( bool* value_, const char* name_ ) {
	value = value_;
	name = name_;
	type = element_type_t::element_checkbox;
}

void c_checkbox::paint( ) {
	if ( !once ) {
		switch_interp = ( float )*value;
		hover_interp = *value ? 1.f : .5f;
		once = true;
	}

	switch_interp = sdk::render->lerp( switch_interp, *value ? 1.f : 0.f, settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, *value ? 1.f : input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	sdk::render->rectangle( { area.x, area.y + 2, area.h + 2, area.h - 2 }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::min( switch_interp, .5f ) ) );
	sdk::render->outlined_rectangle( { area.x, area.y + 2, area.h + 2, area.h - 2 }, clr_t::blend( settings::colors::ui_background, settings::colors::ui_accent, hover_interp ) );
	sdk::render->text( area.x + area.h + 6, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, std::max( switch_interp, .7f ) ), name );
}

void c_checkbox::update( ) {
	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ) {
		*value = !*value;
		pressed = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( pressed && !input->key_down( VK_LBUTTON ) ) {
		pressed = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}
}