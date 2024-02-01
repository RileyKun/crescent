#include "netvar_mgr.hpp"
#include "offsets.hpp"
#include <string_view>

int c_netvar_mgr::get_offset( RecvTable* table, const char* varname ) {
	for ( int i = 0; i < table->m_nProps; i++ ) {
		RecvProp Prop = table->m_pProps[ i ];

		if ( std::string_view( Prop.m_pVarName ).compare( varname ) == 0 )
			return Prop.GetOffset( );

		if ( auto DataTable = Prop.GetDataTable( ) ) {
			if ( auto nOffset = get_offset( DataTable, varname ) )
				return nOffset + Prop.GetOffset( );
		}
	}

	return 0;
}

int c_netvar_mgr::get_offset( const char* class_, const char* varname ) {
	ClientClass* pClasses = offsets::client->GetAllClasses();

	for ( auto node = pClasses; node; node = node->next_class ) {
		if ( std::string_view( class_ ).compare( node->network_name ) == 0 )
			return get_offset( node->recv_table, varname );
	}

	return 0;
}