#include "calc_is_attack_critical.hpp"

void __fastcall hooks::calc_is_attack_critical::function( REGISTERS ) {
	o_call( ecx, edx );
}

void hooks::calc_is_attack_critical::init( ) {
	if ( MH_CreateHook( ( fn )offsets::calc_is_attack_critical, &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook CalcIsAttackCritical" );
}