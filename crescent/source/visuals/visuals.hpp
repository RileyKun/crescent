#pragma once
#include "../include/globals.hpp"

namespace visuals {
	struct esp_entity_t {
		player_t* ent = nullptr;
		vec3_t pos = vec3_t( );
		float dist_to = 0.f;
	};

	struct animation_info_t {
		float global_progress = 0.f;
		float healthbar_progress = 0.f;
		float uberbar_progress = 0.f;
		float invisbar_progress = 0.f;
		clr_t render_col = clr_t( );
		CHudTexture* weapon_icon = nullptr;
	};

	class main_ {
		bool world_is_modulated = false;
	public:
		std::vector< esp_entity_t > esp_entities = { };
		std::map< player_t*, animation_info_t > animation = { };
	private:
		void apply_modulation( clr_t col );
		bool should_render_entity( entity_t* ent );
	public:
		void modulate_world( );
		void restore_modulation( );
		void on_post_fsn( );
		void on_shutdown( );
		void on_paint( );
		void on_screen_fx( );
		void draw_hitbox_matrix( player_t* ent, clr_t col, float time );
	};

	inline main_* main = new main_;
}