#include "window.hpp"
#include "../user_interface.hpp"

void c_window::paint_children( ) {
	for ( const auto& e : elements )
		e->paint( );
}

void c_window::update_children( ) {
	if ( elements.empty( ) )
		return;

	auto tab_width = ( tab_area.w / ( int )elements.size( ) );

	for ( auto i{ 0u }; i < elements.size( ); i++ ) {
		auto& e = elements[ i ];

		e->area = { tab_area.x + ( ( int )i * tab_width ), tab_area.y, tab_width, tab_area.h };

		if ( input->key_pressed( VK_LBUTTON ) && input->hovering( e->area ) )
			selected_tab = i;

		e->enabled = ( selected_tab == ( int )i );
		e->column_area = column_area;
		e->update( );
	}
}

std::shared_ptr< c_tab > c_window::create_tab( const char* name ) {
	auto e = std::make_shared< c_tab >( name );
	elements.emplace_back( e );
	return e;
}

c_window::c_window( const char* name_, rect_t area_ ) {
	name = name_;
	area = area_;
	type = element_type_t::element_window;
}

void c_window::paint( ) {
	sdk::render->clip( area );
	{
		sdk::render->rectangle( title_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .03f ) );
		sdk::render->rectangle( tab_area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ) );
		sdk::render->rectangle( column_area, settings::colors::ui_background );
		sdk::render->text( title_area.x + ( title_area.w / 2 ), title_area.y + ( title_area.h / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center, clr_t::blend( settings::colors::ui_background, settings::colors::ui_text, .7f ), name );
	}
	sdk::render->reset_clip( );

	paint_children( );
	sdk::render->outlined_rectangle( area, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );
}

void c_window::update( ) {
	hovering = input->hovering( title_area );

	if ( hovering && input->key_pressed( VK_LBUTTON ) )
		clicked = true;

	if ( !input->key_down( VK_LBUTTON ) )
		clicked = false;

	if ( dragging && !clicked )
		dragging = false;

	if ( dragging && clicked ) {
		area.x = std::clamp( input->mouse_x - drag_offset_x, 0, globals::screen_width - area.w );
		area.y = std::clamp( input->mouse_y - drag_offset_y, 0, globals::screen_height - area.h );
	}

	if ( hovering ) {
		dragging = true;
		drag_offset_x = input->mouse_x - area.x;
		drag_offset_y = input->mouse_y - area.y;
	}

	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) )
		last_click_time = offsets::engine_client->Time( );

	title_area = { area.x, area.y, area.w, sdk::render->ui_font.tall + 4 };
	tab_area = { area.x, area.y + title_area.h, area.w, sdk::render->ui_font.tall + 6 };
	column_area = { area.x, area.y + title_area.h + tab_area.h, area.w, area.h - title_area.h - tab_area.h };

	update_children( );
}