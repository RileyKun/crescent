#pragma once
#include <inttypes.h>
#include <intrin.h>

template < typename fn > __forceinline fn call_vfunc( void* classbase, int index ) {
	if ( !classbase) return fn{ };
	return ( fn )( ( uintptr_t* )*( uintptr_t** )classbase )[ index ];
}

template < typename T > __forceinline T get_ebp( ) {
	__asm mov eax, ebp
}