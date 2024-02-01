#include "forced_material_override.hpp"
#include "../../visuals/visuals.hpp"

void __fastcall hooks::forced_material_override::function( REGISTERS, IMaterial* mat, OverrideType_t ovr_type ) {
	o_call( ecx, edx, mat, ovr_type );
}

void hooks::forced_material_override::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::modelrender, 1 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook ForcedMaterialOverride" );
}