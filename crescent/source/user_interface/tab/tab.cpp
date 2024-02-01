#include "tab.hpp"
#include "../user_interface.hpp"

void c_tab::paint_children( ) {
	for ( const auto& e : elements )
		e->paint( );
}

void c_tab::update_children( ) {
	if ( elements.empty( ) )
		return;

	auto column_width = ( column_area.w / ( int )elements.size( ) );

	for ( auto i{ 0u }; i < elements.size( ); i++ ) {
		auto& e = elements[ i ];

		e->area = { column_area.x + ( ( int )i * column_width ), column_area.y, column_width, column_area.h };
		e->is_last = { i == elements.size( ) - 1 };
		e->update( );
	}
}

std::shared_ptr< c_column > c_tab::create_column( ) {
	auto e = std::make_shared< c_column >( );
	elements.emplace_back( e );
	return e;
}

c_tab::c_tab( const char* name_ ) {
	name = name_;
	type = element_type_t::element_tab;
}

void c_tab::paint( ) {
	if ( !once ) {
		switch_interp = enabled ? 1.f : 0.f;
		once = true;
	}

	switch_interp = sdk::render->lerp( switch_interp, enabled ? 1.f : input->hovering( area ) ? .2f : .0f, settings::config::animation_speed );

	sdk::render->rectangle( { area.x, area.y + area.h - 2, area.w, 2 }, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .02f ), settings::colors::ui_accent, switch_interp ) );
	sdk::render->text( area.x + ( area.w / 2 ), area.y + ( area.h / 2 ) - 2, sdk::render->ui_font.handle, sdk::text_align::align_center, clr_t::blend( clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .01f ), settings::colors::ui_text, std::max( switch_interp, .7f ) ), name );

	if ( enabled )
		paint_children( );
}

void c_tab::update( ) {
	if ( enabled )
		update_children( );

	if ( input->hovering( area ) && input->key_pressed( VK_LBUTTON ) ) {
		clicked = true;
		offsets::surface->PlaySound( "ui/buttonclick.wav" );
	}

	if ( clicked && !input->key_down( VK_LBUTTON ) ) {
		clicked = false;
		offsets::surface->PlaySound( "ui/buttonclickrelease.wav" );
	}
}