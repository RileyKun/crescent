#pragma once
#include "renderer.hpp"

namespace globals {
	// entities
	inline player_t* local_player = nullptr;
	inline weapon_t* local_weapon = nullptr;
	inline player_resource_t* player_resource = nullptr;

	// screen stuff
	inline int screen_width = 0, screen_height = 0;
	inline vmatrix_t screen_matrix = { };

	// other stuff
	inline bool can_shoot = false, reloading = false, tp_toggled = false, drawing_props = false;
}