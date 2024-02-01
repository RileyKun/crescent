#pragma once
#include "../../include/globals.hpp"

namespace hooks {
	namespace draw_model_execute {
		using fn = void( __fastcall* )( REGISTERS, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t* );
		inline fn o_call = nullptr;
		void __fastcall function( REGISTERS, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone_to_world );
		void init( );
	}
}