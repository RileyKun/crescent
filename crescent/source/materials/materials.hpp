#pragma once
#include "../include/globals.hpp"

namespace visuals {
	struct outline_data {
		entity_t* ent = nullptr;
		clr_t col = clr_t( );
		float alpha = 1.f;
	};

	class materials_ {
		IMaterial* flat = nullptr, *flat_adt = nullptr, *shaded = nullptr, *shaded_adt = nullptr, *fresnel = nullptr, *fresnel_adt = nullptr,
			*glow_color = nullptr, *blur_x = nullptr, *blur_y = nullptr, *halo = nullptr;
		ITexture* full_frame = nullptr, *render_buffer_1 = nullptr, *render_buffer_2 = nullptr;
		std::vector< outline_data > outline_entities = { };
	public:
		bool rendering = false, rendering_outline = false, rendering_overlay = false;
		std::map< entity_t*, bool > drawn_entities = { };
	private:
		bool should_render_entity( entity_t* ent );
		IMaterial* find_material( bool is_overlay_material, int material );
		void set_matarial( bool should_force, bool is_overlay_material = false, int material = 0, clr_t col = clr_t( ), float alpha = 1.f );
		void draw_model( entity_t* ent, int flags, bool is_drawing_models, bool is_rendering_overlay = false );
		void do_chams( IMatRenderContext* context );
		void do_outlines( IMatRenderContext* context, int w, int h );
	public:
		void init( );
		void on_shutdown( );
		void on_screen_fx( );
	};

	inline materials_* materials = new materials_;
}