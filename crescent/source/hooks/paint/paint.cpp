#include "paint.hpp"
#include "../../user_interface/user_interface.hpp"
#include "../../visuals/visuals.hpp"
#include "../../notifications/notifications.hpp"

void __fastcall hooks::paint::function( REGISTERS, int mode ) {
	o_call( ecx, edx, mode );

	if ( mode & PAINT_UIPANELS ) {
		input->poll( );

		if ( !globals::screen_width && !globals::screen_height )
			offsets::engine_client->GetScreenSize( globals::screen_width, globals::screen_height );

		CViewSetup setup = { };
		if ( offsets::client->GetPlayerView( setup ) ) {
			vmatrix_t world_to_view = { }, view_to_projection = { }, world_to_pixels = { };
			offsets::render_view->GetMatricesForView( setup, &world_to_view, &view_to_projection, &globals::screen_matrix, &world_to_pixels );
		}

		offsets::surface->StartDrawing( );
		{
			visuals::main->on_paint( );
			misc::notifications->on_paint( );
			user_interface->on_paint( );
		}
		offsets::surface->FinishDrawing( );
	}
}

void hooks::paint::init( ) {
	if ( MH_CreateHook( c_utils::get_vfunc< fn >( offsets::engine_vgui, 14 ), &function, ( void** )&o_call ) != MH_STATUS::MH_OK )
		throw std::exception( "Failed to hook Paint" );
}