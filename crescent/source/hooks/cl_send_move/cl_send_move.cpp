#include "cl_send_move.hpp"

void __fastcall hooks::cl_send_move::function( REGISTERS ) {
	byte data[ 4000 ];
	const int nextcommandnr = offsets::client_state->lastoutgoingcommand + offsets::client_state->chokedcommands + 1;

	CLC_Move move_message;
	move_message.m_DataOut.StartWriting( data, sizeof( data ) );
	move_message.m_nNewCommands = std::clamp( 1 + offsets::client_state->chokedcommands, 0, 15 );
	const int extra_commands = offsets::client_state->chokedcommands + 1 - move_message.m_nNewCommands;
	const int backup_commands = std::max( 2, extra_commands );
	move_message.m_nBackupCommands = std::clamp( backup_commands, 0, 7 );

	const int numcmds = move_message.m_nNewCommands + move_message.m_nBackupCommands;

	int from = -1;
	bool ok = true;

	for ( int to = nextcommandnr - numcmds + 1; to <= nextcommandnr; to++ ) {
		const bool isnewcmd = to >= nextcommandnr - move_message.m_nNewCommands + 1;
		ok = ok && offsets::client->WriteUsercmdDeltaToBuffer( &move_message.m_DataOut, from, to, isnewcmd );
		from = to;
	}

	if ( ok ) {
		if ( extra_commands )
			offsets::client_state->m_NetChannel->m_nChokedPackets -= extra_commands;

		call_vfunc< bool( __thiscall* )( void*, INetMessage* msg, bool, bool ) >( offsets::client_state->m_NetChannel, 37 )( offsets::client_state->m_NetChannel, &move_message, false, false );
	}
}

void hooks::cl_send_move::init( ) {
	if ( MH_CreateHook( ( fn )offsets::cl_send_move, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CL_SendMove" );
}