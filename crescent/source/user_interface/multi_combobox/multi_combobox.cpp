#include "multi_combobox.hpp"
#include "../user_interface.hpp"

c_multi_combobox::c_multi_combobox( std::vector< bool* > values_, std::vector< std::string > options_, const char* name_ ) {
	values = values_;
	options = options_;
	name = name_;
	type = element_type_t::element_combobox;
}

constexpr auto max_selected_options_length = 15;

void c_multi_combobox::paint( ) {
	if ( values.empty( ) || options.empty( ) || values.size( ) != options.size( ) )
		return;

	hover_interp = sdk::render->lerp( hover_interp, input->hovering( area ) ? .75f : .5f, settings::config::animation_speed );

	std::string selected_options = "";

	for ( auto i = 0; i < values.size( ); i++ ) {
		if ( *values[ i ] ) {
			if ( !selected_options.empty( ) )
				selected_options.append( ", " );

			selected_options.append( options[ i ] );
		}

		if ( i != 0 && selected_options.length( ) > max_selected_options_length ) {
			selected_options.resize( max_selected_options_length - 3 );
			selected_options.append( "..." );
			break;
		}
	}

	if ( selected_options.empty( ) )
		selected_options = "none";

	sdk::render->rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->outlined_rectangle( area, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ), clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .2f ), hover_interp ) );
	sdk::render->text( area.x + 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, .75f ), name );
	sdk::render->text( area.x + area.w - 5, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_left | sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, .75f ), selected_options.c_str( ) );
}

void c_multi_combobox::update( ) {
	if ( values.empty( ) || options.empty( ) || values.size( ) != options.size( ) )
		return;

	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ) {
		user_interface->multi_combo_data = { };

		if ( toggled = !toggled ) {
			auto max_width = 0;

			for ( auto& o : options ) {
				auto w = sdk::render->get_text_size( sdk::render->ui_font.handle, o.c_str( ) ).first;

				if ( w > max_width )
					max_width = w;
			}

			user_interface->multi_combo_data.is_active = true;
			user_interface->multi_combo_data.element_area = area;
			user_interface->multi_combo_data.render_area = { input->mouse_x, input->mouse_y, max_width + 6, ( int )values.size( ) * area.h };
			user_interface->multi_combo_data.values = values;
			user_interface->multi_combo_data.options = options;
		}

		pressed = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( pressed && !input->key_down( VK_LBUTTON ) ) {
		pressed = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	if ( user_interface->multi_combo_data.values != values )
		toggled = false;
}