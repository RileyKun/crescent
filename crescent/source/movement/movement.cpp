#include "movement.hpp"

void misc::movement_::bunnyhop( CUserCmd* cmd ) {
	auto has_ground_entity = ( offsets::entity_list->GetClientEntityFromHandle( globals::local_player->ground_ent( ) ) != nullptr );
	static auto jump_state = false;

	if ( cmd->buttons & IN_JUMP ) {
		if ( !jump_state && !has_ground_entity )
			cmd->buttons &= ~IN_JUMP;

		else if ( jump_state )
			jump_state = false;
	}

	else if ( !jump_state )
		jump_state = true;
}

void misc::movement_::on_move( CUserCmd* cmd ) {
	if ( !globals::local_player || globals::local_player->deadflag( ) )
		return;

	if ( globals::local_player->water_lvl( ) >= WL_Waist ||
		globals::local_player->in_cond( TF_COND_HALLOWEEN_KART ) || globals::local_player->in_cond( TF_COND_HALLOWEEN_GHOST_MODE ) ||
		globals::local_player->movetype( ) == MOVETYPE_NOCLIP || globals::local_player->movetype( ) == MOVETYPE_OBSERVER )
		return;

	if ( settings::movement::bunnyhop )
		bunnyhop( cmd );
}