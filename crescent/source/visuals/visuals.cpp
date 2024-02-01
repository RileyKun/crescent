#include "visuals.hpp"

void visuals::main_::apply_modulation( clr_t col ) {
	for ( MaterialHandle_t h = offsets::matsystem->FirstMaterial( ); h != offsets::matsystem->InvalidMaterial( ); h = offsets::matsystem->NextMaterial( h ) ) {
		auto material = offsets::matsystem->GetMaterial( h );

		if ( !material || material->IsErrorMaterial( ) || !material->IsPrecached( ) )
			continue;

		std::string_view group( material->GetTextureGroupName( ) );

		if ( group.find( TEXTURE_GROUP_WORLD ) != group.npos || group.find( TEXTURE_GROUP_SKYBOX ) != group.npos ) {
			auto found = false;

			if ( auto color2 = material->FindVar( "$color2", &found ); color2 && found )
				color2->SetVecValue( col.r( ) / 255.f, col.g( ) / 255.f, col.b( ) / 255.f );

			else material->ColorModulate( col.r( ) / 255.f, col.g( ) / 255.f, col.b( ) / 255.f );
		}
	}

	world_is_modulated = true;
}

bool visuals::main_::should_render_entity( entity_t* ent ) {
	if ( !ent || ent->dormant( ) )
		return false;

	if ( ent->is_player( ) ) {

		if ( ent->deadflag( ) || ( ent == globals::local_player && !offsets::input->CAM_IsThirdPerson( ) ) )
			return false;

		if ( !settings::player_esp::enabled )
			return false;

		if ( settings::player_esp::ignore_teammates && ent->team( ) == globals::local_player->team( ) && !ent->is_player_on_steam_friends_list( ) && ent != globals::local_player )
			return false;

		if ( settings::player_esp::ignore_invisible && ent->invisibility( ) )
			return false;
	}

	if ( ent->is_object( ) ) {
		if ( !settings::object_esp::enabled )
			return false;

		if ( settings::object_esp::ignore_team && ent->team( ) == globals::local_player->team( ) )
			return false;
	}

	return true;
}

void visuals::main_::modulate_world( ) {
	apply_modulation( settings::colors::world_modulation );
}

void visuals::main_::restore_modulation( ) {
	if ( !world_is_modulated )
		return;

	apply_modulation( clr_t( 255, 255, 255 ) );
	world_is_modulated = false;
}

void visuals::main_::on_post_fsn( ) {
	auto is_color_changed = [ & ]( ) -> bool {
		static clr_t old = settings::colors::world_modulation;
		clr_t current = settings::colors::world_modulation;

		if ( current.r( ) != old.r( ) || current.g( ) != old.g( ) || current.b( ) != old.b( ) ) {
			old = current;
			return true;
		}

		return false;
	};

	if ( !world_is_modulated || is_color_changed( ) )
		apply_modulation( settings::colors::world_modulation );
}

void visuals::main_::on_shutdown( ) {
	esp_entities.clear( );
	animation.clear( );
}

void visuals::main_::on_paint( ) {
	if ( !globals::local_player || offsets::engine_vgui->IsGameUIVisible( ) )
		return;

	esp_entities.clear( );

	for ( auto n{ 1 }; n < offsets::entity_list->GetHighestEntityIndex( ); n++ ) {
		if ( auto ent = ( player_t* )offsets::entity_list->GetClientEntity( n ) ) {
			auto& anim = animation[ ent ];
			
			if ( should_render_entity( ent ) )
				anim.global_progress = std::clamp( sdk::render->lerp( anim.global_progress, 1.f, settings::config::animation_speed ), 0.f, 1.f );

			else {
				anim.global_progress = std::clamp( sdk::render->lerp( anim.global_progress, 0.f, settings::config::animation_speed ), 0.f, 1.f ); }

			auto col = c_utils::get_entity_color( ent );

			//if ( aim::general->current_target == ent )
			//	col = clr_t::blend( col, clr_t( 255, 255, 255 ), .7f );

			anim.render_col = clr_t::blend( anim.render_col, col, settings::config::animation_speed * 3.f );

			esp_entity_t e = { };
			e.ent = ent;
			e.pos = ent->center_pos( );
			e.dist_to = globals::local_player->shoot_pos( ).dist_to( e.pos );

			esp_entities.emplace_back( e );
		}
	}

	if ( esp_entities.empty( ) )
		return;

	std::sort( esp_entities.begin( ), esp_entities.end( ), [ & ]( const esp_entity_t& first, const esp_entity_t& second ) -> bool {
		return ( first.dist_to > second.dist_to );
	} );

	for ( const auto& e : esp_entities ) {
		if ( settings::player_esp::enabled && e.ent->is_player( ) ) {
			auto& anim = animation[ e.ent ];
			rect_t bbox = { };

			if ( !e.ent->compute_bbox( bbox ) )
				continue;

			offsets::surface->DrawSetAlphaMultiplier( std::min( anim.global_progress, settings::player_esp::alpha ) );
			{
				if ( settings::player_esp::name ) {
					player_info_t info = { };
					if ( offsets::engine_client->GetPlayerInfo( e.ent->idx( ), &info ) ) {
						sdk::render->text(
							bbox.x + ( bbox.w / 2 ), bbox.y,
							sdk::render->esp_font.handle, sdk::text_align::align_top | sdk::text_align::align_center_horiz,
							anim.render_col, c_utils::utf_to_wide( info.name ).c_str( )
						);
					}
				}

				if ( settings::player_esp::bounding_box ) {
					sdk::render->corner_rectangle( bbox, 3, 5, clr_t( 35, 35, 35, 175 ) );
					sdk::render->corner_rectangle( { bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2 }, 3, 5, anim.render_col );
				}

				if ( settings::player_esp::health_bar ) {
					anim.healthbar_progress = sdk::render->lerp( anim.healthbar_progress, ( float )e.ent->health( ) / ( float )e.ent->max_health( ), settings::config::animation_speed );
					auto health_bar_height = ( int )RemapValClamped( anim.healthbar_progress, 0.f, 1.f, 0.f, ( float )bbox.h );
					sdk::render->rectangle( { bbox.x - 6, bbox.y, 3, bbox.h }, clr_t( 35, 35, 35, 175 ) );
					sdk::render->outlined_rectangle( { bbox.x - 6, bbox.y, 3, bbox.h }, clr_t( 35, 35, 35, 75 ) );
					sdk::render->rectangle( { bbox.x - 6, bbox.y + ( bbox.h - health_bar_height ), 3, health_bar_height }, clr_t( 0, 175, 0, 175 ) );
					sdk::render->outlined_rectangle( { bbox.x - 6, bbox.y + ( bbox.h - health_bar_height ), 3, health_bar_height }, clr_t( 35, 35, 35, 175 ) );

					if ( !e.ent->deadflag( ) && e.ent->health( ) < e.ent->max_health( ) ) {
						sdk::render->text(
							bbox.x - 7, bbox.y + ( bbox.h - health_bar_height ),
							sdk::render->esp_font.handle, sdk::text_align::align_left,
							clr_t( 200, 200, 200, 120 ), "%i", e.ent->health( )
						);
					}
				}

				if ( settings::player_esp::weapon_icon ) {
					auto weapon = e.ent->active_weapon( );

					if ( weapon ) if ( auto icon = weapon->get_weapon_icon( ) )
						anim.weapon_icon = icon;

					if ( anim.weapon_icon ) {
						auto icon_width = ( float )anim.weapon_icon->Width( );
						float scale = std::clamp( ( ( float )bbox.w * .75f ) / icon_width, .5f, .6f );

						sdk::render->hud_texture(
							( float )bbox.x + ( float )bbox.w * .5f - icon_width * scale * .5f,
							( float )( bbox.y + bbox.h ), scale, anim.weapon_icon,
							clr_t( 255, 255, 255 )
						);
					}
				}

				if ( settings::player_esp::flags ) {
					auto y_offset = 0;

					if ( e.ent->health( ) > e.ent->max_health( ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 255, 142, 142 ), "overheal" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_INVULNERABLE ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 133, 71, 255 ), "invuln" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_SMALL_BULLET_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "bullet resist" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_SMALL_BLAST_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "blast resist" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_SMALL_FIRE_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "fire resist" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_UBER_BULLET_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "bullet uber" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_UBER_BLAST_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "blast uber" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_MEDIGUN_UBER_FIRE_RESIST ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 153, 102, 255 ), "fire uber" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->is_crit_boosted( ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 255, 77, 71 ), "crits" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_PHASE ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 238, 255, 71 ), "bonked" );
						y_offset += sdk::render->esp_font.tall;
					}

					if ( e.ent->in_cond( TF_COND_ZOOMED ) ) {
						sdk::render->text( bbox.x + bbox.w + 3, bbox.y + y_offset, sdk::render->esp_font.handle, sdk::text_align::align_default, clr_t( 255, 137, 71 ), "scoped" );
						y_offset += sdk::render->esp_font.tall;
					}
				}
			}
			offsets::surface->DrawSetAlphaMultiplier( 1.f );
		}

		if ( settings::object_esp::enabled && e.ent->is_object( ) ) {
			auto& anim = animation[ e.ent ];
			rect_t bbox = { };

			if ( !e.ent->compute_bbox( bbox ) )
				continue;

			offsets::surface->DrawSetAlphaMultiplier( std::min( anim.global_progress, settings::object_esp::alpha ) );
			{
				if ( settings::object_esp::name ) {
					sdk::render->text(
						bbox.x + ( bbox.w / 2 ), bbox.y,
						sdk::render->esp_font.handle, sdk::text_align::align_top | sdk::text_align::align_center_horiz,
						anim.render_col, e.ent->object_name( )
					);
				}

				if ( settings::object_esp::bounding_box ) {
					sdk::render->corner_rectangle( bbox, 3, 5, clr_t( 35, 35, 35, 175 ) );
					sdk::render->corner_rectangle( { bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2 }, 3, 5, anim.render_col );
				}

				if ( settings::object_esp::health_bar ) {
					anim.healthbar_progress = sdk::render->lerp( anim.healthbar_progress, ( float )e.ent->obj_health( ) / ( float )e.ent->obj_max_health( ), settings::config::animation_speed );
					auto health_bar_height = ( int )RemapValClamped( anim.healthbar_progress, 0.f, 1.f, 0.f, ( float )bbox.h );
					sdk::render->rectangle( { bbox.x - 5, bbox.y, 2, bbox.h }, clr_t( 35, 35, 35, 175 ) );
					sdk::render->outlined_rectangle( { bbox.x - 6, bbox.y, 3, bbox.h }, clr_t( 35, 35, 35, 75 ) );
					sdk::render->rectangle( { bbox.x - 6, bbox.y + ( bbox.h - health_bar_height ), 3, health_bar_height }, clr_t( 0, 175, 0, 175 ) );
					sdk::render->outlined_rectangle( { bbox.x - 6, bbox.y + ( bbox.h - health_bar_height ), 3, health_bar_height }, clr_t( 35, 35, 35, 175 ) );

					if ( e.ent->is_building( ) && e.ent->obj_health( ) < e.ent->obj_max_health( ) ) {
						sdk::render->text(
							bbox.x - 7, bbox.y + ( bbox.h - health_bar_height ),
							sdk::render->esp_font.handle, sdk::text_align::align_left,
							clr_t( 200, 200, 200, 120 ), "%i", e.ent->obj_health( )
						);
					}
				}
			}
			offsets::surface->DrawSetAlphaMultiplier( 1.f );
		}
	}
}

void visuals::main_::on_screen_fx( ) {

}

void visuals::main_::draw_hitbox_matrix( player_t* ent, clr_t col, float time ) {
	if ( !ent )
		return;

	const model_t* model = ent->get_model( );
	studiohdr_t* hdr = offsets::modelinfo->GetStudiomodel( model );
	mstudiohitboxset_t* set = hdr->GetHitboxSet( ent->hitboxset( ) );

	for ( auto n{ 0 }; n < set->numhitboxes; ++n ) {
		mstudiobbox_t* bbox = set->pHitbox( n );
		if ( !bbox )
			continue;

		matrix3x4_t rot_matrix;
		angle_matrix( bbox->angle, rot_matrix );

		matrix3x4_t matrix;
		matrix3x4_t bones[ 128 ];

		ent->setup_bones( bones, 128, 0x100, offsets::globals->curtime );
		concat_transforms( bones[ bbox->bone ], rot_matrix, matrix );

		auto bbox_angle = vec3_t( );
		matrix_angles( matrix, bbox_angle );

		auto matrix_origin = vec3_t( );
		get_matrix_origin( matrix, matrix_origin );

		offsets::debug_overlay->AddBoxOverlay( matrix_origin, bbox->bbmin, bbox->bbmax, bbox_angle, col.r( ), col.g( ), col.b( ), col.a( ), time );
	}
}