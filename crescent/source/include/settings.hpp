#pragma once
#include "util.hpp"
#include "color.hpp"

namespace settings {
	namespace visuals {
		inline bool remove_recoil = true;
		inline bool remove_scope = true;
		inline bool remove_taunts = false;
		inline bool remove_disguises = true;
		inline int field_of_view = 90;
		inline int thirdperson_key = 'X';
		inline int bullet_tracers = 2;
	}

	namespace ragdoll_fx {
		inline bool burning = true;
		inline bool electrocuted = true;
		inline bool become_ash = true;
		inline bool dissolving = true;
		inline bool gold = true;
		inline bool ice = true;
	}

	namespace materials {
		inline bool no_depth = false;
		inline int base_material = 0;
		inline int overlay_material = 1;
		inline float overlay_blend = .3f;
	}

	namespace crosshair {
		inline bool show_thirdperson_angles = true;
	}

	namespace viewmodel {
		inline int distance = 0;
		inline int distance_right = 0;
		inline int distance_up = 0;
	}

	namespace player_esp {
		inline bool enabled = true;
		inline float alpha = .9f;
		inline bool ignore_teammates = true;
		inline bool ignore_invisible = true;
		inline bool name = true;
		inline bool bounding_box = false;
		inline bool health_bar = true;
		inline bool weapon_icon = true;
		inline bool flags = true;
		inline bool material_override = true;
		inline bool outline = true;
	}

	namespace object_esp {
		inline bool enabled = true;
		inline float alpha = .9f;
		inline bool show_sentryguns = true;
		inline bool show_dispensers = true;
		inline bool show_teleporters = true;
		inline bool ignore_team = true;
		inline bool name = true;
		inline bool bounding_box = false;
		inline bool health_bar = true;
		inline bool flags = true;
		inline bool material_override = true;
		inline bool outline = true;
	}

	namespace misc {
		inline bool bypass_sv_pure = true;
		inline bool remove_event_delay = true;
	}

	namespace movement {
		inline bool bunnyhop = true;
		inline bool no_teammate_push = true;
	}

	namespace notifications {
		inline bool enabled = true;
		inline bool log_damage = true;
	}

	namespace networking {
		inline bool enabled = true;
		inline bool marker_show_distance = true;
		inline int marker_key = 0;
		inline int popuber_key = 0;
	}

	namespace config {
		inline float animation_speed = .04f;
		inline int menu_key = VK_INSERT;
	}

	namespace colors {
		inline clr_t friends = clr_t( 230, 230, 230, 175 );
		inline clr_t red_team = clr_t( 255, 100, 100, 175 );
		inline clr_t blue_team = clr_t( 88, 143, 192, 175 );
		inline clr_t spectators = clr_t( 126, 126, 126, 175 );
		inline clr_t ui_background = clr_t( 35, 35, 35 );
		inline clr_t ui_accent = clr_t( 255, 85, 85, 235 );
		inline clr_t ui_text = clr_t( 238, 238, 238, 235 );
		inline clr_t world_modulation = clr_t( 85, 85, 85 );
		inline clr_t prop_modulation = clr_t( 85, 85, 85, 200 );
		inline clr_t fresnel_base = clr_t( 8, 8, 8, 153 );
	}
}