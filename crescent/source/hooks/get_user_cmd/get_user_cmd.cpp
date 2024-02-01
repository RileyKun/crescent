#include "get_user_cmd.hpp"

CUserCmd* __fastcall hooks::get_user_cmd::function( REGISTERS, int sequence_num ) {
	if ( CUserCmd* cmd_list = *reinterpret_cast< CUserCmd** >( ( uintptr_t )ecx + 0xfc ) ) if ( CUserCmd* cmd = &cmd_list[ sequence_num % 90 ] )
		return cmd;
	return o_call( ecx, edx, sequence_num );
}

void hooks::get_user_cmd::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::input, 8 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook GetUserCmd" );
}