#pragma once
#include "../include/globals.hpp"

namespace misc {
	enum message_type {
		message_unknown,
		message_marker,
		message_popuber
	};

	class networking_ {
		bool should_popuber = false, marker_delay = false, popuber_delay = false;
	public:
		void on_move( CUserCmd* cmd );
		bool handle_event( IGameEvent* event );
	};

	inline networking_* networking = new networking_;
}