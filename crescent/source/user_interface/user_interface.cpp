#include "user_interface.hpp"
#include "../materials/materials.hpp"
#include "../notifications/notifications.hpp"

void save_config( ) {
	misc::notifications->create( "saved config", settings::colors::ui_accent, 3.f );
	offsets::surface->PlaySound( "buttons/button10.wav" );
}

void load_config( ) {
	misc::notifications->create( "loaded config", settings::colors::ui_accent, 3.f );
	offsets::surface->PlaySound( "buttons/button10.wav" );
}

auto reload_materials_callback( ) {
	visuals::materials->init( );
	misc::notifications->create( "reloaded materials", settings::colors::ui_accent, 3.f );
	offsets::surface->PlaySound( "buttons/button10.wav" );
}

auto reload_fonts_callback( ) {
	sdk::render->init_fonts( );
	misc::notifications->create( "reloaded fonts", settings::colors::ui_accent, 3.f );
	offsets::surface->PlaySound( "buttons/button10.wav" );
}

auto cl_fullupdate_callback( ) {
	offsets::engine_client->ClientCmd_Unrestricted( "cl_fullupdate" );
}

auto itemtest_callback( ) {
	offsets::engine_client->ClientCmd_Unrestricted( "map itemtest" );
}

std::shared_ptr< c_window > c_user_interface::create_window( const char* name, rect_t area ) {
	auto e = std::make_shared< c_window >( name, area );
	elements.emplace_back( e );
	return e;
}

void c_user_interface::handle_multi_combo( ) {
	if ( !user_interface->is_open ) {
		multi_combo_data = { }; return; }

	if ( !multi_combo_data.is_active || multi_combo_data.values.empty( ) || multi_combo_data.options.empty( ) ||
		multi_combo_data.values.size( ) != multi_combo_data.options.size( ) ) {
		multi_combo_data = { }; return; }

	if ( !input->hovering( multi_combo_data.element_area ) && !input->hovering( multi_combo_data.render_area ) && input->key_pressed( VK_LBUTTON ) ) {
		multi_combo_data = { }; offsets::surface->PlaySound( "ui/buttonclickrelease.wav" ); return; }

	sdk::render->rectangle( multi_combo_data.render_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->outlined_rectangle( multi_combo_data.render_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );

	auto h = int( multi_combo_data.render_area.h / multi_combo_data.values.size( ) );

	for ( auto i = 0; i < multi_combo_data.values.size( ); i++ ) {
		sdk::render->text(
			multi_combo_data.render_area.x + 4,
			multi_combo_data.render_area.y + h * i + 1,
			sdk::render->ui_font.handle, sdk::align_default, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text,
			*multi_combo_data.values[ i ] ? 1.f : .7f ),
			multi_combo_data.options[ i ].c_str( )
		);

		if ( input->key_pressed( VK_LBUTTON ) && input->hovering( { multi_combo_data.render_area.x, multi_combo_data.render_area.y + h * i, multi_combo_data.render_area.w, h } ) )
			*multi_combo_data.values[ i ] = !*multi_combo_data.values[ i ];
	}
}

void c_user_interface::handle_color_picker( ) {
	if ( !user_interface->is_open ) {
		picker_data = { }; return; }

	if ( !picker_data.is_active || !picker_data.value ) {
		picker_data = { }; return; }

	if ( !input->hovering( picker_data.element_area ) && !input->hovering( picker_data.render_area ) && input->key_pressed( VK_LBUTTON ) ) {
		picker_data = { }; offsets::surface->PlaySound( "ui/buttonclickrelease.wav" ); return; }

	sdk::render->rectangle( picker_data.render_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->outlined_rectangle( picker_data.render_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );

	const auto x = picker_data.render_area.x + 3, y = picker_data.render_area.y + 3;
	auto hue = picker_data.value->hue( ), saturation = picker_data.value->saturation( ), brightness = picker_data.value->brightness( ) / 255.f,
		alpha = ( float )picker_data.value->a( ) / 255.f;

	if ( hue > 1.f )
		hue -= 359.f;

	for ( auto i{ 0 }; i < 100; i++ ) {
		for ( auto n{ 0 }; n < 100; n++ ) {
			sdk::render->rectangle( { x + i + 1, y + n + 1, 1, 1 },
				clr_t::from_hsb( hue, float( i ) * .01f, float( 100 - n ) * .01f ) );
		}
	}

	// handle saturation and brightness
	{
		auto mouse_x_c = std::clamp( input->mouse_x, x, x + 100 ), mouse_y_c = std::clamp( input->mouse_y, y, y + 100 ),
			delta_y = std::clamp( mouse_y_c - y, 0, 100 ), delta_x = std::clamp( mouse_x_c - x, 0, 100 );

		if ( input->hovering( { x, y, 100, 100 } ) && input->key_pressed( VK_LBUTTON ) ) {
			picker_data.picker_ = true;
			offsets::surface->PlaySound( "ui/buttonclick.wav" );
		}

		if ( picker_data.picker_ && !input->key_down( VK_LBUTTON ) ) {
			picker_data.picker_ = false;
			offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
		}

		if ( picker_data.picker_ ) {
			saturation = ( float )delta_x * .01f;
			brightness = float( 100 - delta_y ) * .01f;
			*picker_data.value = clr_t::from_hsb( hue, saturation, brightness );
			picker_data.value->a( ) = alpha * 255.f;
		}

		sdk::render->outlined_rectangle( { x + int( saturation * 100.f ) - 1, y + ( 100 - int( brightness * 100.f ) ) - 1, 3, 3 }, clr_t( 255, 255, 255, 145 ) );
	}

	// handle hue
	{
		auto mouse_y_c = std::clamp( input->mouse_y, y, y + 100 ), delta_y = std::clamp( mouse_y_c - y, 0, 100 );

		if ( input->hovering( { x + 100, y, 13, 100 } ) && input->key_pressed( VK_LBUTTON ) ) {
			picker_data.hue_ = true;
			offsets::surface->PlaySound( "ui/buttonclick.wav" );
		}

		if ( picker_data.hue_ && !input->key_down( VK_LBUTTON ) ) {
			picker_data.hue_ = false;
			offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
		}

		if ( picker_data.hue_ ) {
			hue = std::clamp( delta_y * .01f, 0.f, 1.f );
			*picker_data.value = clr_t::from_hsb( hue, saturation, brightness );
			picker_data.value->a( ) = alpha * 255.f;
		}

		auto max_hue_height = ( picker_data.render_area.h - 13 ), hue_height = ( int )::remap( hue, 0.f, 1.f, 0.f, ( float )max_hue_height );

		for ( auto n{ 0.f }; n < 1.f; n += .01f ) {
			auto h = ( int )::remap( n, 0.f, 1.f, 0.f, ( float )max_hue_height - 1 );
			sdk::render->rectangle( { picker_data.render_area.x + picker_data.render_area.w - 7, picker_data.render_area.y + h + 4, 4, 2 }, clr_t::from_hsb( n, 1.f, 1.f ) );
		}

		// bar outline.
		sdk::render->outlined_rectangle( { picker_data.render_area.x + picker_data.render_area.w - 7, picker_data.render_area.y + 4, 4, max_hue_height }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );

		// current hue knob.
		sdk::render->rectangle( { picker_data.render_area.x + picker_data.render_area.w - 9, picker_data.render_area.y + hue_height + 2, 8, 4 }, clr_t( 145, 145, 145, 255 ) );
		sdk::render->outlined_rectangle( { picker_data.render_area.x + picker_data.render_area.w - 9, picker_data.render_area.y + hue_height + 2, 8, 4 }, clr_t( 255, 255, 255 ) );
	}

	// handle alpha
	{
		auto mouse_x_c = std::clamp( input->mouse_x, x, x + 100 ), delta_x = std::clamp( mouse_x_c - x, 0, 100 );

		if ( input->hovering( { x, y + 100, 100, 13 } ) && input->key_pressed( VK_LBUTTON ) ) {
			picker_data.alpha_ = true;
			offsets::surface->PlaySound( "ui/buttonclick.wav" );
		}

		if ( picker_data.alpha_ && !input->key_down( VK_LBUTTON ) ) {
			picker_data.alpha_ = false;
			offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
		}

		if ( picker_data.alpha_ ) {
			alpha = std::clamp( delta_x * .01f, 0.f, 1.f );
			picker_data.value->a( ) = uint8_t( alpha * 255.f );
		}

		auto max_alpha_width = ( picker_data.render_area.w - 13 ), alpha_width = ( int )::remap( alpha, 0.f, 1.f, 0.f, ( float )max_alpha_width );

		for ( auto n{ 0.f }; n < 1.f; n += .01f ) {
			auto w = ( int )::remap( n, 0.f, 1.f, 0.f, ( float )max_alpha_width - 1 );
			sdk::render->rectangle( { picker_data.render_area.x + w + 4, picker_data.render_area.y + picker_data.render_area.h - 7, 2, 4 }, clr_t::blend( clr_t( ), clr_t( 255, 255, 255 ), n ) );
		}

		// bar outline.
		sdk::render->outlined_rectangle( { picker_data.render_area.x + 4, picker_data.render_area.y + picker_data.render_area.h - 7, max_alpha_width, 4 }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );

		// current hue knob.
		sdk::render->rectangle( { picker_data.render_area.x + alpha_width + 2, picker_data.render_area.y + picker_data.render_area.h - 9, 4, 8 }, clr_t( 145, 145, 145, 255 ) );
		sdk::render->outlined_rectangle( { picker_data.render_area.x + alpha_width + 2, picker_data.render_area.y + picker_data.render_area.h - 9, 4, 8 }, clr_t( 255, 255, 255 ) );
	}
}

void c_user_interface::init( ) {
	if ( auto window = create_window( "settings", { 200, 200, 450, 300 } ) ) {
		if ( auto tab = window->create_tab( "aimbot" ) ) {

		}

		if ( auto tab = window->create_tab( "visuals" ) ) {
			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "general" );
				column->create_slider( settings::visuals::field_of_view, 70, 120, 1, "field of view", "°" );
				column->create_keybind( settings::visuals::thirdperson_key, "thirdperson key" );
				column->create_combobox( settings::visuals::bullet_tracers, { "default", "machina", "raygun", "merasmus", "classic", "big nasty" }, "bullet tracers" );
				column->create_multi_combobox( { &settings::ragdoll_fx::burning, &settings::ragdoll_fx::electrocuted, &settings::ragdoll_fx::become_ash, &settings::ragdoll_fx::dissolving, &settings::ragdoll_fx::gold, &settings::ragdoll_fx::ice }, { "burning", "electrocuted", "become ash", "dissolving", "gold", "ice" }, "ragdoll fx" );
				column->create_multi_combobox( { &settings::visuals::remove_recoil, &settings::visuals::remove_scope, &settings::visuals::remove_taunts, &settings::visuals::remove_disguises }, { "recoil", "scope", "taunts", "disguises" }, "removals" );
				column->create_separator( "crosshair" );
				column->create_checkbox( settings::crosshair::show_thirdperson_angles, "show thirdperson angles" );
			}

			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "player esp" );
				column->create_checkbox( settings::player_esp::enabled, "enabled" );
				column->create_slider( settings::player_esp::alpha, 0.f, 1.f, .1f, "alpha", "" );
				column->create_multi_combobox( { &settings::player_esp::ignore_teammates, &settings::player_esp::ignore_invisible }, { "teammates", "invisible" }, "ignore" );
				column->create_multi_combobox( { &settings::player_esp::name, &settings::player_esp::bounding_box, &settings::player_esp::health_bar, &settings::player_esp::weapon_icon, &settings::player_esp::flags, &settings::player_esp::material_override, &settings::player_esp::outline }, { "name", "box", "health bar", "weapon icon", "flags", "material", "outline" }, "elements" );
				column->create_separator( "object esp" );
				column->create_checkbox( settings::object_esp::enabled, "enabled" );
				column->create_slider( settings::object_esp::alpha, 0.f, 1.f, .1f, "alpha", "" );
				column->create_multi_combobox( { &settings::object_esp::name, &settings::object_esp::bounding_box, &settings::object_esp::health_bar, &settings::object_esp::material_override, &settings::object_esp::outline }, { "name", "box", "health bar", "material", "outline" }, "elements" );
			}

			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "viewmodel" );
				column->create_slider( settings::viewmodel::distance, -15, 15, 1, "distance", "" );
				column->create_slider( settings::viewmodel::distance_right, -15, 15, 1, "distance right", "" );
				column->create_slider( settings::viewmodel::distance_up, -15, 15, 1, "distance up", "" );
				column->create_separator( "materials" );
				column->create_checkbox( settings::materials::no_depth, "no depth" );
				column->create_slider( settings::materials::overlay_blend, 0.f, 1.f, .05f, "overlay blend", "" );
				column->create_combobox( settings::materials::base_material, { "original", "flat", "shaded", "fresnel" }, "base material" );
				column->create_combobox( settings::materials::overlay_material, { "none", "flat", "shaded", "fresnel" }, "overlay material" );
			}
		}

		if ( auto tab = window->create_tab( "misc" ) ) {
			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "general" );
				column->create_checkbox( settings::misc::bypass_sv_pure, "bypass sv_pure" );
				column->create_checkbox( settings::misc::remove_event_delay, "remove event delay" );
				column->create_separator( "movement" );
				column->create_checkbox( settings::movement::bunnyhop, "bunnyhop" );
				column->create_checkbox( settings::movement::no_teammate_push, "no teammate push" );
				column->create_separator( "notifications" );
				column->create_checkbox( settings::notifications::enabled, "enabled" );
				column->create_checkbox( settings::notifications::log_damage, "log damage" );
			}

			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "ticks" );
				column->create_separator( "crits" );
			}

			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "networking" );
				column->create_checkbox( settings::networking::enabled, "enabled" );
				column->create_checkbox( settings::networking::marker_show_distance, "marker show distance" );
				column->create_keybind( settings::networking::marker_key, "marker key" );
				column->create_keybind( settings::networking::popuber_key, "pop uber key" );
				column->create_separator( "automations" );
			}
		}

		if ( auto tab = window->create_tab( "config" ) ) {
			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "general" );
				column->create_keybind( settings::config::menu_key, "menu key" );
				column->create_slider( settings::config::animation_speed, .01f, .2f, .01f, "animation speed", "" );
				column->create_button( save_config, "save config" );
				column->create_button( load_config, "load config" );
				column->create_button( reload_materials_callback, "reload materials" );
				column->create_button( reload_fonts_callback, "reload fonts" );
				column->create_button( cl_fullupdate_callback, "cl_fullupdate" );
				column->create_button( itemtest_callback, "itemtest" );
			}

			if ( auto column = tab->create_column( ) ) {
				column->create_separator( "colors" );
				column->create_color_picker( settings::colors::friends, "friends" );
				column->create_color_picker( settings::colors::red_team, "red team" );
				column->create_color_picker( settings::colors::blue_team, "blue team" );
				column->create_color_picker( settings::colors::spectators, "spectators" );
				column->create_color_picker( settings::colors::ui_background, "ui background" );
				column->create_color_picker( settings::colors::ui_accent, "ui accent" );
				column->create_color_picker( settings::colors::ui_text, "ui text" );
				column->create_color_picker( settings::colors::world_modulation, "world modulation" );
				column->create_color_picker( settings::colors::prop_modulation, "prop modulation" );
				column->create_color_picker( settings::colors::fresnel_base, "fresnel base" );
			}
		}
	}
}

void c_user_interface::on_paint( ) {
	is_keybind_active = false;

	if ( input->key_pressed( settings::config::menu_key ) )
		offsets::surface->SetCursorAlwaysVisible( is_open = !is_open );

	for ( const auto& e : elements ) {
		switch ( e->type ) {
			case element_type_t::element_window: { 
				if ( !is_open ) break;
				e->update( );
				e->paint( );
				break;
			}

			default: {
				if ( is_open ) e->update( );
				if ( is_open || ( !offsets::engine_vgui->IsGameUIVisible( ) && offsets::engine_client->IsInGame( ) && offsets::engine_client->IsConnected( ) ) ) e->paint( );
				break;
			}
		}
	}

	handle_multi_combo( );
	handle_color_picker( );

	if ( is_open ) {
		std::ranges::sort( elements, [ & ]( const std::shared_ptr< c_base_draggable >& first, const std::shared_ptr< c_base_draggable >& second ) -> bool {
			return first->last_click_time < second->last_click_time;
		} );
	}
}