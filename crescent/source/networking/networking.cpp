#include "networking.hpp"

void misc::networking_::on_move( CUserCmd* cmd ) {
	if ( !settings::networking::enabled || !globals::local_player || globals::local_player->deadflag( ) )
		return;

	std::string message = "tf_party_chat \"SW$";

	if ( should_popuber ) {
		cmd->buttons |= IN_ATTACK2;
		should_popuber = false;
	}

	if ( settings::networking::marker_key && GetAsyncKeyState( settings::networking::marker_key ) ) {
		if ( !marker_delay ) {
			auto forward = vec3_t( );
			cmd->viewangles.angle_vectors( &forward );

			trace_t trace = { };
			Ray_t ray = { };
			ray.Init( globals::local_player->shoot_pos( ), globals::local_player->shoot_pos( ) + forward * ( float )MAX_TRACE_LENGTH );
			CTraceFilterHitscan filter = { };
			filter.pass_ent = globals::local_player;

			offsets::engine_trace->TraceRay( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace );

			if ( trace.did_hit( ) ) {
				std::stringstream stream;
				stream << std::to_string( message_type::message_marker ) << "#" << trace.endpos.x << "#" << trace.endpos.y << "#" << trace.endpos.z << "#" << globals::local_player->idx( ) << "\"";
				message.append( stream.str( ) );
				offsets::engine_client->ClientCmd_Unrestricted( message.c_str( ) );
			}

			marker_delay = true;
			return;
		}
	}

	else {
		marker_delay = false;
	}

	if ( settings::networking::popuber_key && GetAsyncKeyState( settings::networking::popuber_key ) ) {
		if ( !popuber_delay ) {
			std::stringstream stream;
			stream << std::to_string( message_type::message_popuber ) << "#" << globals::local_player->idx( ) << "\"";
			message.append( stream.str( ) );
			offsets::engine_client->ClientCmd_Unrestricted( message.c_str( ) );
		}

		popuber_delay = true;
		return;
	}

	else {
		popuber_delay = false;
	}
}

bool misc::networking_::handle_event( IGameEvent* event ) {
	auto content = std::string( event->GetString( "text" ) );

	if ( !c_utils::string_begins_with( content.c_str( ), "SW$" ) )
		return false;

	if ( !settings::networking::enabled )
		return true;

	content.erase( 0, 3 );
	auto data = c_utils::split_string( content, "#" );

	switch ( std::stoi( data[ 0 ] ) ) {
		case message_type::message_marker: {
			auto pos_x = std::stof( data[ 1 ] ), pos_y = std::stof( data[ 2 ] ),
				pos_z = std::stof( data[ 3 ] );
			auto player_idx = std::stoi( data[ 4 ] );

			player_info_t info = { };
			offsets::engine_client->GetPlayerInfo( player_idx, &info );

			auto marker = offsets::event_mgr->CreateEventA( "show_annotation" );

			if ( info.userID && marker ) {
				marker->SetInt( "id", player_idx );
				marker->SetBool( "show_distance", settings::networking::marker_show_distance );
				marker->SetFloat( "worldPosX", pos_x );
				marker->SetFloat( "worldPosY", pos_y );
				marker->SetFloat( "worldPosZ", pos_z );
				marker->SetFloat( "lifetime", 5.f );
				marker->SetString( "text", info.name );
				marker->SetString( "play_sound", "ui/system_message_alert.wav" );
				offsets::event_mgr->FireEventClientSide( marker );
			}

			return true;
		}

		case message_type::message_popuber: {
			auto player_idx = std::stoi( data[ 1 ] );

			if ( globals::local_weapon && globals::local_weapon->get_weapon_id( ) == TF_WEAPON_MEDIGUN && globals::local_weapon->uber_charge( ) >= 1.f ) {
				if ( auto target = globals::local_weapon->get_healing_target( ); target && target->idx( ) == player_idx )
					should_popuber = true;
			}

			return true;
		}
	}

	return false;
}