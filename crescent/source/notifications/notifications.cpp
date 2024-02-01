#include "notifications.hpp"

void misc::notifications_::on_paint( ) {
	constexpr auto x{ 4 };
	auto y{ 4 }, h{ sdk::render->ui_font.tall + 7 };

	std::ranges::sort( notifs, [ & ]( const std::shared_ptr< notification >& first, const std::shared_ptr< notification >& second ) -> bool {
		return first->duration > second->duration;
	} );

	for ( auto i{ 0u }; i < notifs.size( ); ++i ) {
		auto n = notifs[ i ];
		n->time -= offsets::globals->absoluteframetime;

		if ( n->time <= 0.f )
			notifs.erase( notifs.begin( ) + i );
	}

	if ( notifs.empty( ) )
		return;

	for ( auto i{ 0u }; i < notifs.size( ); ++i ) {
		auto n = notifs[ i ];
		auto w = sdk::render->get_text_size( sdk::render->ui_font.handle, n->text.c_str( ) ).first;
		auto alpha_mult = .85f, delta = settings::config::animation_speed * 5.f;

		if ( n->time >= n->duration - delta )
			alpha_mult = ::remap( n->time, n->duration - delta, n->duration, .85f, .0f );

		else if ( n->time <= delta ) {
			alpha_mult = ::remap( n->time, delta, .0f, .85f, .0f );
			y -= ( int )::remap( n->time, delta, .0f, .0f, ( float )h );
		}

		offsets::surface->DrawSetAlphaMultiplier( alpha_mult );
		{
			auto bar_width = ( int )RemapValClamped( n->time, 0.f, n->duration, 0.f, ( float )w + 8.f );

			sdk::render->rectangle( { x, y, w + 8, h - 3 }, settings::colors::ui_background );
			sdk::render->rectangle( { x + bar_width, y + h - 3, ( w + 8 ) - bar_width, 2 }, clr_t::blend( n->col, settings::colors::ui_background, .5f ) );
			sdk::render->rectangle( { x, y + h - 3, bar_width, 2 }, n->col );
			sdk::render->outlined_rectangle( { x, y, w + 8, h }, clr_t::blend( settings::colors::ui_background, clr_t( 255, 255, 255 ), .1f ) );
			sdk::render->text( x + 4, y + ( ( h - 3 ) / 2 ), sdk::render->ui_font.handle, sdk::text_align::align_center_vert, settings::colors::ui_text, n->text.c_str( ) );
		}
		offsets::surface->DrawSetAlphaMultiplier( 1.f );
		y += h + 4;
	}
}

void misc::notifications_::create( const std::string& text, clr_t col, float duration ) {
	auto n = std::make_shared< notification >( text, col, duration );
	notifs.emplace_back( n );
}