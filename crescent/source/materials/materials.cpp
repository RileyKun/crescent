#include "materials.hpp"
#include "../visuals/visuals.hpp"

bool visuals::materials_::should_render_entity( entity_t* ent ) {
	return true;
}

IMaterial* visuals::materials_::find_material( bool is_overlay_material, int material ) {
	switch ( material ) {
		case 1: return is_overlay_material ? flat_adt : flat;
		case 2: return is_overlay_material ? shaded_adt : shaded;
		case 3: return is_overlay_material ? fresnel_adt : fresnel;
		default: return nullptr;
	}
}

void visuals::materials_::set_matarial( bool should_force, bool is_overlay_material, int material, clr_t col, float alpha ) {
	auto mat = find_material( is_overlay_material, material );

	if ( should_force && mat ) {
		if ( material == 3 ) {
			auto base_col = clr_t::blend( col, settings::colors::fresnel_base, settings::colors::fresnel_base.a( ) / 255.f );

			if ( auto envmaptint = mat->FindVar( "$envmaptint", nullptr, false ) )
				envmaptint->SetVecValue( col.r( ) / 255.f, col.g( ) / 255.f, col.b( ) / 255.f );

			if ( auto selfillumtint = mat->FindVar( "$selfillumtint", nullptr, false ) )
				selfillumtint->SetVecValue( base_col.r( ) / 255.f, base_col.g( ) / 255.f, base_col.b( ) / 255.f );
		}

		offsets::modelrender->ForcedMaterialOverride( mat );
		offsets::render_view->SetColorModulation( material != 3 ? col : clr_t( 255, 255, 255 ) );
		offsets::render_view->SetBlend( alpha );
	}

	else {
		offsets::modelrender->ForcedMaterialOverride( nullptr );
		offsets::render_view->SetColorModulation( 1.f, 1.f, 1.f );
		offsets::render_view->SetBlend( 1.f );
	}
}

void visuals::materials_::draw_model( entity_t* ent, int flags, bool is_drawing_models, bool is_rendering_overlay ) {
	rendering = true;

	if ( !is_drawing_models )
		rendering_outline = true;

	if ( is_rendering_overlay )
		rendering_overlay = true;

	ent->draw_model( flags );

	if ( is_drawing_models )
		drawn_entities[ ent ] = true;

	if ( !is_drawing_models )
		rendering_outline = false;

	if ( is_rendering_overlay )
		rendering_overlay = false;

	rendering = false;
}

void visuals::materials_::do_chams( IMatRenderContext* context ) {
	if ( settings::materials::no_depth )
		context->DepthRange( .0f, .2f );

	for ( auto n{ 1 }; n < offsets::entity_list->GetHighestEntityIndex( ); n++ ) {
		auto ent = ( entity_t* )offsets::entity_list->GetClientEntity( n );

		if ( !ent )
			continue;

		auto& anim = visuals::main->animation[ ent ];

		if ( ent->is_player( ) ) {
			set_matarial( settings::player_esp::material_override, false, settings::materials::base_material, anim.render_col );
			draw_model( ent, STUDIO_RENDER, true );

			if ( settings::materials::overlay_material ) {
				set_matarial( settings::player_esp::material_override, true, settings::materials::overlay_material, anim.render_col, settings::materials::overlay_blend );
				draw_model( ent, STUDIO_RENDER, true, true );
			}

			if ( settings::player_esp::outline )
				outline_entities.push_back( { ent, anim.render_col, anim.global_progress } );

			if ( auto weapon = ( entity_t* )ent->active_weapon( ) ) {
				set_matarial( settings::player_esp::material_override, false, settings::materials::base_material, anim.render_col );
				draw_model( weapon, STUDIO_RENDER, true );

				if ( settings::materials::overlay_material ) {
					set_matarial( settings::player_esp::material_override, true, settings::materials::overlay_material, anim.render_col, settings::materials::overlay_blend );
					draw_model( weapon, STUDIO_RENDER, true, true );
				}

				if ( settings::player_esp::outline )
					outline_entities.push_back( { weapon, anim.render_col, anim.global_progress } );
			}

			auto attachment = ent->first_move_child( );

			for ( auto n{ 0 }; n < 10; n++ ) {
				if ( !attachment )
					break;

				if ( attachment->client_class( )->class_id == classid_t::CTFWearable ) {
					set_matarial( settings::player_esp::material_override, false, settings::materials::base_material, anim.render_col );
					draw_model( attachment, STUDIO_RENDER, true );

					if ( settings::materials::overlay_material ) {
						set_matarial( settings::player_esp::material_override, true, settings::materials::overlay_material, anim.render_col, settings::materials::overlay_blend );
						draw_model( attachment, STUDIO_RENDER, true, true );
					}

					if ( settings::player_esp::outline )
						outline_entities.push_back( { attachment, anim.render_col, anim.global_progress } );
				}

				attachment = attachment->next_move_peer( );
			}
		}

		if ( ent->is_object( ) ) {
			set_matarial( settings::object_esp::material_override, false, settings::materials::base_material, anim.render_col, 1.f );
			draw_model( ent, STUDIO_RENDER, true );

			if ( settings::materials::overlay_material ) {
				set_matarial( settings::object_esp::material_override, true, settings::materials::overlay_material, anim.render_col, settings::materials::overlay_blend );
				draw_model( ent, STUDIO_RENDER, true, true );
			}

			if ( settings::object_esp::outline )
				outline_entities.push_back( { ent, anim.render_col, anim.global_progress } );
		}

		set_matarial( false );
	}

	if ( settings::materials::no_depth )
		context->DepthRange( 0.f, 1.f );
}

void visuals::materials_::do_outlines( IMatRenderContext* context, int w, int h ) {
	context->SetStencilEnable( false );

	if ( outline_entities.empty( ) )
		return;

	offsets::modelrender->ForcedMaterialOverride( glow_color );

	context->PushRenderTargetAndViewport( );
	{
		context->SetRenderTarget( render_buffer_1 );
		context->Viewport( 0, 0, w, h );
		context->ClearColor4ub( 0, 0, 0, 0 );
		context->ClearBuffers( true, false, false );

		for ( auto& o : outline_entities ) {
			offsets::render_view->SetBlend( std::min( o.col.a( ) / 255.f, o.alpha ) );
			offsets::render_view->SetColorModulation( o.col );
			draw_model( o.ent, STUDIO_RENDER | STUDIO_NOSHADOWS, false );
		}
	}
	context->PopRenderTargetAndViewport( );

	context->PushRenderTargetAndViewport( );
	{
		context->Viewport( 0, 0, w, h );
		context->SetRenderTarget( render_buffer_2 );
		context->DrawScreenSpaceRectangle( blur_x, 0, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->SetRenderTarget( render_buffer_1 );
		context->DrawScreenSpaceRectangle( blur_y, 0, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	}
	context->PopRenderTargetAndViewport( );

	context->SetStencilEnable( true );
	context->SetStencilCompareFunction( STENCILCOMPARISONFUNCTION_EQUAL );
	context->SetStencilPassOperation( STENCILOPERATION_KEEP );
	context->SetStencilFailOperation( STENCILOPERATION_KEEP );
	context->SetStencilZFailOperation( STENCILOPERATION_KEEP );
	context->SetStencilReferenceValue( 0 );
	context->SetStencilTestMask( 0xFF );
	context->SetStencilWriteMask( 0x0 );

	context->DrawScreenSpaceRectangle( halo, -1, -1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, -1, -0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, -1, 1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, 0, -1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, 0, 1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, 1, -1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, 1, -0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	context->DrawScreenSpaceRectangle( halo, 1, 1, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );

	context->SetStencilEnable( false );
	offsets::modelrender->ForcedMaterialOverride( nullptr );
}

void visuals::materials_::init( ) {
	glow_color = offsets::matsystem->FindMaterial( "dev/glow_color", TEXTURE_GROUP_OTHER );
	full_frame = offsets::matsystem->FindTexture( "_rt_FullFrameFB", TEXTURE_GROUP_RENDER_TARGET );

	render_buffer_1 = offsets::matsystem->CreateNamedRenderTargetTextureEx( "render_buffer_1", full_frame->GetActualWidth( ), full_frame->GetActualHeight( ),
		RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED, TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
	render_buffer_1->IncrementReferenceCount( );

	render_buffer_2 = offsets::matsystem->CreateNamedRenderTargetTextureEx( "render_buffer_2", full_frame->GetActualWidth( ), full_frame->GetActualHeight( ),
		RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED, TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
	render_buffer_2->IncrementReferenceCount( );

	if ( auto kv = new KeyValues( "BlurFilterX" ) ) {
		kv->SetString( "$basetexture", "render_buffer_1" );
		kv->SetString( "$wireframe", "1" );
		blur_x = offsets::matsystem->CreateMaterial( "sw_outline_blur_x", kv );
	}

	if ( auto kv = new KeyValues( "BlurFilterY" ) ) {
		kv->SetString( "$basetexture", "render_buffer_2" );
		kv->SetString( "$wireframe", "1" );
		blur_y = offsets::matsystem->CreateMaterial( "sw_outline_blur_y", kv );
	}

	if ( auto kv = new KeyValues( "UnlitGeneric" ) ) {
		kv->SetString( "$basetexture", "render_buffer_1" );
		kv->SetString( "$additive", "1" );
		halo = offsets::matsystem->CreateMaterial( "sw_outline_halo", kv );
	}

	if ( auto kv = new KeyValues( "UnlitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		flat = offsets::matsystem->CreateMaterial( "sw_cham_flat", kv );
	}

	if ( auto kv = new KeyValues( "UnlitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		kv->SetString( "$additive", "1" );
		flat_adt = offsets::matsystem->CreateMaterial( "sw_cham_flat_adt", kv );
	}

	if ( auto kv = new KeyValues( "VertexLitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		kv->SetString( "$bumpmap", "models/player/shared/shared_normal" );
		kv->SetString( "$selfillum", "1" );
		kv->SetString( "$selfillumfresnel", "1" );
		kv->SetString( "$selfillumfresnelminmaxexp", "[-0.25 1 1]" );
		shaded = offsets::matsystem->CreateMaterial( "sw_cham_shaded", kv );
	}

	if ( auto kv = new KeyValues( "VertexLitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		kv->SetString( "$bumpmap", "models/player/shared/shared_normal" );
		kv->SetString( "$selfillum", "1" );
		kv->SetString( "$selfillumfresnel", "1" );
		kv->SetString( "$selfillumfresnelminmaxexp", "[-0.25 1 1]" );
		kv->SetString( "$additive", "1" );
		shaded_adt = offsets::matsystem->CreateMaterial( "sw_cham_shaded_adt", kv );
	}

	if ( auto kv = new KeyValues( "VertexLitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		kv->SetString( "$bumpmap", "models/player/shared/shared_normal" );
		kv->SetString( "$envmap", "skybox/sky_dustbowl_01" );
		kv->SetString( "$envmapfresnel", "1" );
		kv->SetString( "$phong", "1" );
		kv->SetString( "$phongfresnelranges", "[0.3 2 3]" );
		kv->SetString( "$selfillum", "1" );
		kv->SetString( "$selfillumfresnel", "1" );
		kv->SetString( "$selfillumfresnelminmaxexp", "[0.5 0.5 0]" );
		kv->SetString( "$envmaptint", "[1 1 1]" );
		kv->SetString( "$selfillumtint", "[0.03 0.03 0.03]" );
		fresnel = offsets::matsystem->CreateMaterial( "sw_cham_fresnel", kv );
	}

	if ( auto kv = new KeyValues( "VertexLitGeneric" ) ) {
		kv->SetString( "$basetexture", "vgui/white_additive" );
		kv->SetString( "$bumpmap", "models/player/shared/shared_normal" );
		kv->SetString( "$envmap", "skybox/sky_dustbowl_01" );
		kv->SetString( "$envmapfresnel", "1" );
		kv->SetString( "$phong", "1" );
		kv->SetString( "$phongfresnelranges", "[0.3 2 3]" );
		kv->SetString( "$selfillum", "1" );
		kv->SetString( "$selfillumfresnel", "1" );
		kv->SetString( "$selfillumfresnelminmaxexp", "[0.5 0.5 0]" );
		kv->SetString( "$envmaptint", "[1 1 1]" );
		kv->SetString( "$selfillumtint", "[0.03 0.03 0.03]" );
		kv->SetString( "$additive", "1" );
		fresnel_adt = offsets::matsystem->CreateMaterial( "sw_cham_fresnel_adt", kv );
	}
}

void visuals::materials_::on_shutdown( ) {
	flat = nullptr;
	flat_adt = nullptr;
	shaded = nullptr;
	shaded_adt = nullptr;
	fresnel = nullptr;
	fresnel_adt = nullptr;
	drawn_entities.clear( );
	outline_entities.clear( );
}

void visuals::materials_::on_screen_fx( ) {
	auto context = offsets::matsystem->GetRenderContext( );
	auto w = globals::screen_width, h = globals::screen_height;

	drawn_entities.clear( );
	outline_entities.clear( );

	if ( !globals::local_player || !context || w < 1 || h < 1 || w > 4096 || h > 4096 )
		return;

	if ( !offsets::engine_client->IsInGame( ) || !offsets::engine_client->IsConnected( ) || offsets::engine_vgui->IsGameUIVisible( ) )
		return;

	if ( settings::player_esp::outline || settings::object_esp::outline ) {
		context->SetStencilEnable( true );
		context->SetStencilCompareFunction( STENCILCOMPARISONFUNCTION_ALWAYS );
		context->SetStencilPassOperation( STENCILOPERATION_REPLACE );
		context->SetStencilFailOperation( STENCILOPERATION_KEEP );
		context->SetStencilZFailOperation( STENCILOPERATION_REPLACE );
		context->SetStencilReferenceValue( 1 );
		context->SetStencilTestMask( 0xFFFFFFFF );
		context->SetStencilWriteMask( 0xFFFFFFFF );
	}

	float blend_backup = offsets::render_view->GetBlend( );
	float color_backup[ 3 ] = { }; offsets::render_view->GetColorModulation( color_backup );
	{
		// first we render the entity models, and use them for stenciling if glow is enabled.
		do_chams( context );

		// then we draw the outlines.
		do_outlines( context, w, h );
	}
	offsets::render_view->SetBlend( blend_backup );
	offsets::render_view->SetColorModulation( color_backup );
}