#pragma once
#include "../include/globals.hpp"

namespace misc {
	struct notification {
		std::string text = "";
		clr_t col = clr_t( );
		float time = 0.f, duration = 0.f;

		notification( ) { }
		notification( std::string text_, clr_t col_, float duration_ ) {
			text = text_, col = col_, time = duration = duration_;
		}
	};

	class notifications_ {
		std::vector< std::shared_ptr< notification > > notifs = { };
	public:
		void on_paint( );
		void create( const std::string& text, clr_t col, float duration = 1.f );
	};

	inline notifications_* notifications = new notifications_;
}