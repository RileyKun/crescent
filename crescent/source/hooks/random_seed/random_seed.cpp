#include "random_seed.hpp"

void __cdecl hooks::random_seed::function( int seed ) {
	if ( !globals::local_weapon )
		return o_call( seed );

	static auto ret1 = c_utils::find_pattern( "client.dll", "83 C4 ? 0F 57 ? 80 7D FF" );
	static auto ret2 = c_utils::find_pattern( "client.dll", "83 C4 ? 68 ? ? ? ? 6A ? FF 15 ? ? ? ? F3 0F ? ? ? 83 C4 ? 0F 28" );
	static auto ret3 = c_utils::find_pattern( "client.dll", "83 C4 ? 68 ? ? ? ? 6A ? FF 15 ? ? ? ? F3 0F ? ? ? 83 C4 ? F3 0F" );
	
	auto ret_addr = ( uintptr_t )_ReturnAddress( );

	if ( ret_addr == ret1 || ret_addr == ret2 || ret_addr == ret3 )
		globals::local_weapon->random_seed( ) = seed;

	o_call( seed );
}

void hooks::random_seed::init( ) {
	if ( auto module = GetModuleHandleA( "vstdlib.dll" ) ) if ( MH_CreateHook( GetProcAddress( module, "RandomSeed" ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook RandomSeed" );
}