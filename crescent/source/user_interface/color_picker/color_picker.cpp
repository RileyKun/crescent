#include "color_picker.hpp"
#include "../user_interface.hpp"

c_color_picker::c_color_picker( clr_t* value_, const char* name_ ) {
	value = value_;
	name = name_;
	type = element_type_t::element_color_picker;
}

void c_color_picker::paint( ) {
	if ( !once ) {
		switch_interp = .75f;
		hover_interp = .5f;
		once = true;
	}

	switch_interp = sdk::render->lerp( switch_interp, toggled ? 1.f : .75f, settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, toggled ? 1.f : input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	sdk::render->rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->rectangle( { area.x + area.w - area.h - 4, area.y, area.h + 4, area.h }, *value );
	sdk::render->outlined_rectangle( area, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ), clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .2f ), hover_interp ) );
	sdk::render->text( area.x + 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, switch_interp ), name );
}

void c_color_picker::update( ) {
	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ) {
		user_interface->picker_data = { };

		if ( toggled = !toggled ) {
			user_interface->picker_data.is_active = true;
			user_interface->picker_data.element_area = area;
			user_interface->picker_data.render_area = { input->mouse_x, input->mouse_y, 113, 113 };
			user_interface->picker_data.value = value;
		}

		pressed = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( pressed && !input->key_down( VK_LBUTTON ) ) {
		pressed = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	if ( user_interface->picker_data.value != value )
		toggled = false;
}