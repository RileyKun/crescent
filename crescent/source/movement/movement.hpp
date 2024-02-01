#pragma once
#include "../include/globals.hpp"

namespace misc {
	class movement_ {
		void bunnyhop( CUserCmd* cmd );
	public:
		void on_move( CUserCmd* cmd );
	};

	inline movement_* movement = new movement_;
}