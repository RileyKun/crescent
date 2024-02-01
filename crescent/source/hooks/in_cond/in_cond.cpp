#include "in_cond.hpp"

bool __fastcall hooks::in_cond::function( REGISTERS, int cond ) {
	auto get_outer = [ &ecx ]( ) -> void* {
		static const auto offset = netvar_mgr->get_offset( "CTFPlayer", "m_nHalloweenBombHeadStage" ) - netvar_mgr->get_offset( "CTFPlayer", "m_Shared" ) + 0x4;
		return *( void** )( ( uintptr_t )ecx + offset );
	};

	if ( settings::visuals::remove_scope && cond == TF_COND_ZOOMED ) {
		static const auto player_should_draw = c_utils::find_pattern( "client.dll", "E8 ? ? ? ? 84 C0 75 C5", 0x5 );
		static const auto wearable_should_draw = c_utils::find_pattern( "client.dll", "E8 ? ? ? ? 84 C0 75 E1 6A 03", 0x5 );

		const auto ret_addr = ( uintptr_t )_ReturnAddress( );

		if ( ret_addr == player_should_draw || ret_addr == wearable_should_draw )
			return false;
	}

	if ( globals::local_player != get_outer( ) ) {
		if ( settings::visuals::remove_taunts && cond == TF_COND_TAUNTING )
			return false;

		if ( settings::visuals::remove_disguises && cond == TF_COND_DISGUISED )
			return false;
	}

	return o_call( ecx, edx, cond );
}

void hooks::in_cond::init( ) {
	if ( MH_CreateHook( ( fn )offsets::in_cond, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook InCond" );
}