#include "slider.hpp"
#include "../user_interface.hpp"

c_slider_int::c_slider_int( int* value_, int min_, int max_, int step_, const char* name_, const char* unit_ ) {
	value = value_;
	min = min_;
	max = max_;
	step = step_;
	unit = unit_;
	name = name_;
	type = element_type_t::element_slider;
}

void c_slider_int::paint( ) {
	if ( !once ) {
		bar_interp = RemapValClamped( ( float )*value, ( float )min, ( float )max, 0.f, ( float )area.w * .5f );
		hover_interp = .7f;
		once = true;
	}

	bar_interp = sdk::render->lerp( bar_interp, RemapValClamped( ( float )*value, ( float )min, ( float )max, 0.f, ( float )area.w * .5f ), settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, ( dragging && clicked ) ? 1.f : input->hovering( area ) ? 1.f : .7f, settings::config::animation_speed );

	sdk::render->rectangle( { area.x, area.y, area.w / 2, area.h }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->rectangle( { area.x, area.y, ( int )bar_interp, area.h }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::clamp( hover_interp - .5f, .3f, .7f ) ) );
	sdk::render->outlined_rectangle( { area.x, area.y, area.w / 2, area.h }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, hover_interp ) );
	sdk::render->text( area.x + area.w / 2 + 4, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, std::max( hover_interp, .7f ) ), name );
	sdk::render->text( area.x + ( area.w / 4 ), area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::max( hover_interp, .7f ) ), std::string( std::to_string( *value ) + unit ).c_str( ) );
}

void c_slider_int::update( ) {
	hovering = input->hovering( area ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ;

	if ( hovering && input->key_pressed( VK_LBUTTON ) ) {
		clicked = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( clicked && !input->key_down( VK_LBUTTON ) ) {
		clicked = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	if ( dragging && !clicked )
		dragging = false;

	if ( dragging && clicked )
		*value = ( int )RemapValClamped( ( float )( input->mouse_x - area.x ), 0.f, ( float )area.w * .5f, ( float )min, ( float )max );

	else if ( hovering ) {
		dragging = true;

		if ( input->key_pressed( VK_RBUTTON ) ) {
			*value += ( ( float )( input->mouse_x - area.x ) > ( float )area.w * .25f ) ? step : -step;
			*value = std::clamp( *value, min, max );
		}
	}
}

c_slider_float::c_slider_float( float* value_, float min_, float max_, float step_, const char* name_, const char* unit_ ) {
	value = value_;
	min = min_;
	max = max_;
	step = step_;
	unit = unit_;
	name = name_;
	type = element_type_t::element_slider;
}

void c_slider_float::paint( ) {
	if ( !once ) {
		bar_interp = RemapValClamped( ( float )*value, ( float )min, ( float )max, 0.f, ( float )area.w * .5f );
		hover_interp = .7f;
		once = true;
	}

	bar_interp = sdk::render->lerp( bar_interp, RemapValClamped( ( float )*value, ( float )min, ( float )max, 0.f, ( float )area.w * .5f ), settings::config::animation_speed );
	hover_interp = sdk::render->lerp( hover_interp, ( dragging && clicked ) ? 1.f : input->hovering( area ) ? 1.f : .7f, settings::config::animation_speed );

	char buffer[ 64 ];
	sprintf_s( buffer, "%.2f", *value );

	sdk::render->rectangle( { area.x, area.y, area.w / 2, area.h }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
	sdk::render->rectangle( { area.x, area.y, ( int )bar_interp, area.h }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::clamp( hover_interp - .5f, .3f, .7f ) ) );
	sdk::render->outlined_rectangle( { area.x, area.y, area.w / 2, area.h }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, hover_interp ) );
	sdk::render->text( area.x + area.w / 2 + 4, area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, std::max( hover_interp, .7f ) ), name );
	sdk::render->text( area.x + ( area.w / 4 ), area.y + ( area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, std::max( hover_interp, .7f ) ), std::string( std::string( buffer ) + unit ).c_str( ) );
}

void c_slider_float::update( ) {
	hovering = input->hovering( area ) && !input->hovering( user_interface->picker_data.render_area ) && !input->hovering( user_interface->multi_combo_data.render_area ) ;

	if ( hovering && input->key_pressed( VK_LBUTTON ) ) {
		clicked = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( clicked && !input->key_down( VK_LBUTTON ) ) {
		clicked = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}

	if ( dragging && !clicked )
		dragging = false;

	if ( dragging && clicked )
		*value = RemapValClamped( ( float )( input->mouse_x - area.x ), 0.f, ( float )area.w * .5f, ( float )min, ( float )max );

	else if ( hovering ) {
		dragging = true;

		if ( input->key_pressed( VK_RBUTTON ) ) {
			*value += ( ( float )( input->mouse_x - area.x ) > ( float )area.w * .25f ) ? step : -step;
			*value = std::clamp( *value, min, max );
		}
	}
}