#include "ISurface.hpp"
#include "offsets.hpp"

void IMatSystemSurface::StartDrawing( ) {
	using fn = void( __thiscall* )( ISurface* );
	return ( ( fn )offsets::start_drawing )( this );
}

void IMatSystemSurface::FinishDrawing( ) {
	using fn = void( __thiscall* )( ISurface* );
	return ( ( fn )offsets::finish_drawing )( this );
}