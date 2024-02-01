#include "draw_model_execute.hpp"
#include "../../materials/materials.hpp"

void __fastcall hooks::draw_model_execute::function( REGISTERS, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone_to_world ) {
	auto ent = ( entity_t* )offsets::entity_list->GetClientEntity( info.entity_index );

	if ( ent && visuals::materials->drawn_entities[ ent ] && !visuals::materials->rendering_outline && !visuals::materials->rendering_overlay )
		return;

	return o_call( ecx, edx, state, info, bone_to_world );
}

void hooks::draw_model_execute::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::modelrender, 19 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook DrawModelExecute" );
}