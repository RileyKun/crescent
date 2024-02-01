#pragma once
#include "dt_recv.hpp"

class c_netvar_mgr {
public:
	int get_offset( RecvTable* table, const char* varname );
	int get_offset( const char* class_, const char* varname );
};

inline c_netvar_mgr* netvar_mgr = new c_netvar_mgr;

#define netvar( name, type, class_, varname ) __forceinline type& name( ) {\
	static const auto offset = netvar_mgr->get_offset( class_, varname );\
	return *( type* )( ( uintptr_t )this + offset );\
}