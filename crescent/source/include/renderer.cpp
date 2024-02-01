#include "globals.hpp"

void sdk::renderer::blurred_rectangle( rect_t area, clr_t col, int passes ) {
	auto rc = offsets::matsystem->GetRenderContext( );

	if ( !globals::screen_width || !globals::screen_height || !rc || passes <= 0 )
		return;

	if ( !blur_buffer_0 ) {
		blur_buffer_0 = offsets::matsystem->CreateNamedRenderTargetTextureEx( "blur_buffer_0", globals::screen_width, globals::screen_height, RT_SIZE_LITERAL, ImageFormat::IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED, TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
		blur_buffer_0->IncrementReferenceCount( );
	}

	if ( !blur_buffer_1 ) {
		blur_buffer_1 = offsets::matsystem->CreateNamedRenderTargetTextureEx( "blur_buffer_1", globals::screen_width, globals::screen_height, RT_SIZE_LITERAL, ImageFormat::IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED, TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
		blur_buffer_1->IncrementReferenceCount( );
	}

	if ( !blur_x ) {
		KeyValues* kv = new KeyValues( "BlurFilterX" );
		kv->SetString( "$basetexture", "blur_buffer_0" );
		blur_x = offsets::matsystem->CreateMaterial( "blur_x", kv );
	}

	if ( !blur_y ) {
		KeyValues* kv = new KeyValues( "BlurFilterY" );
		kv->SetString( "$basetexture", "blur_buffer_1" );
		kv->SetString( "$bloomamount", "1" );
		blur_y = offsets::matsystem->CreateMaterial( "blur_y", kv );
	}

	if ( !screen_mat ) {
		KeyValues* kv = new KeyValues( "UnlitGeneric" );
		kv->SetString( "$basetexture", "blur_buffer_0" );
		kv->SetString( "$color2", "[1 1 1]" );
		kv->SetString( "$alpha", "1.0" );
		screen_mat = offsets::matsystem->CreateMaterial( "screen_mat", kv );
	}

	if ( !blur_buffer_0 || !blur_buffer_1 || !blur_x || !blur_y || !screen_mat )
		return;

	screen_mat->ColorModulate( col.r( ) / 255.f, col.g( ) / 255.f, col.b( ) / 255.f );
	screen_mat->AlphaModulate( col.a( ) / 255.f );

	rc->CopyRenderTargetToTexture( blur_buffer_0 );
	rc->CopyRenderTargetToTexture( blur_buffer_1 );

	rc->PushRenderTargetAndViewport( );
	rc->Viewport( 0, 0, globals::screen_width, globals::screen_height );

	for ( auto n{ 0 }; n < passes; n++ ) {
		rc->SetRenderTarget( blur_buffer_1 );
		rc->DrawScreenSpaceRectangle
		(
			blur_x,
			0, 0,
			globals::screen_width, globals::screen_height,
			0.0f, 0.0f,
			( float )( globals::screen_width - 1 ), ( float )( globals::screen_height - 1 ),
			globals::screen_width, globals::screen_height
		);

		rc->SetRenderTarget( blur_buffer_0 );
		rc->DrawScreenSpaceRectangle (
			blur_y,
			0, 0,
			globals::screen_width, globals::screen_height,
			0.0f, 0.0f,
			( float )( globals::screen_width - 1 ), ( float )( globals::screen_height - 1 ),
			globals::screen_width, globals::screen_height
		);
	}

	rc->PopRenderTargetAndViewport( );

	rc->DrawScreenSpaceRectangle (
		screen_mat,
		area.x, area.y,
		area.w, area.h,
		( float )area.x, ( float )area.y,
		( float )( area.x + ( area.w - 1 ) ), ( float )( area.y + ( area.h - 1 ) ),
		globals::screen_width, globals::screen_height
	);
}

void sdk::renderer::clip( rect_t rec ) {
	offsets::surface->GetClippingRect( clip_rect_backup.x, clip_rect_backup.y, clip_rect_backup.w, clip_rect_backup.h, clip_disabled_backup );
	offsets::surface->DisableClipping( false );
	offsets::surface->SetClippingRect( rec.x, rec.y, rec.x + rec.w, rec.y + rec.h );
}

void sdk::renderer::reset_clip( ) {
	offsets::surface->DisableClipping( clip_disabled_backup );
	offsets::surface->SetClippingRect( clip_rect_backup.x, clip_rect_backup.y, clip_rect_backup.w, clip_rect_backup.h );
}

float sdk::renderer::lerp( float start, float end, float speed ) {
	return start + ( end - start ) * speed;
}