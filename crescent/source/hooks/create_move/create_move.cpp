#include "create_move.hpp"
#include "../../prediction/prediction.hpp"
#include "../../movement/movement.hpp"
#include "../../networking/networking.hpp"

bool __fastcall hooks::create_move::function( REGISTERS, float input_sample_time, CUserCmd* cmd ) {
	uintptr_t _bp; __asm mov _bp, ebp;
	bool* send_packet = ( bool* )( ***( uintptr_t*** )_bp - 0x1 );

	if ( !cmd || cmd->command_number <= 0 )
		return o_call( ecx, edx, input_sample_time, cmd );

	if ( o_call( ecx, edx, input_sample_time, cmd ) )
		offsets::prediction->SetLocalViewAngles( cmd->viewangles );

	c_utils::compute_can_shoot( );

	// pre prediction.
	misc::networking->on_move( cmd );
	misc::movement->on_move( cmd );

	// in prediction.
	misc::prediction->begin( cmd );

	// post prediction.
	misc::prediction->finish( );

	return false;
}

void hooks::create_move::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::client_mode, 21 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CreateMove" );
}