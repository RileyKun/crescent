#include "frame_stage_notify.hpp"
#include "../../visuals/visuals.hpp"

void __fastcall hooks::frame_stage_notify::function( REGISTERS, ClientFrameStage_t stage ) {
	o_call( ecx, edx, stage );

	if ( stage == ClientFrameStage_t::FRAME_NET_UPDATE_END ) {
		if ( globals::local_player = ( player_t* )offsets::entity_list->GetClientEntity( offsets::engine_client->GetLocalPlayer( ) ) )
			globals::local_weapon = globals::local_player->active_weapon( );

		if ( !globals::player_resource ) for ( auto i{ 1 }; i < offsets::entity_list->GetHighestEntityIndex( ); i++ ) if ( auto ent = ( player_t* )offsets::entity_list->GetClientEntity( i ); ent && ent->is_resource( ) ) {
			globals::player_resource = ( player_resource_t* )ent;
			break;
		}
	}

	if ( stage == ClientFrameStage_t::FRAME_NET_UPDATE_START ) {
		globals::local_player = nullptr;
		globals::local_weapon = nullptr;
	}

	if ( stage == ClientFrameStage_t::FRAME_RENDER_START )
		visuals::main->on_post_fsn( );
}

void hooks::frame_stage_notify::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client, 35 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook FrameStageNotify" );
}