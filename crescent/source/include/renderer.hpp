#pragma once
#include "offsets.hpp"

namespace sdk {
	enum text_align {
		align_default = ( 1 << 0 ),
		align_left = ( 1 << 1 ),
		align_top = ( 1 << 2 ),
		align_center_horiz = ( 1 << 3 ),
		align_center_vert = ( 1 << 4 ),
		align_center = ( align_center_horiz | align_center_vert )
	};

	struct font {
		const char* name = "";
		int tall = 0, weight = 0, flags = 0;
		unsigned long handle = 0x0;
	};

	class renderer {
		ITexture* blur_buffer_0 = nullptr;
		ITexture* blur_buffer_1 = nullptr;
		IMaterial* blur_x = nullptr;
		IMaterial* blur_y = nullptr;
		IMaterial* screen_mat = nullptr;
	private:
		rect_t clip_rect_backup = { };
		bool clip_disabled_backup = false;
	public:
		font ui_font = { "Tahoma", 12, 200, EFontFlags::FONTFLAG_NONE };
		font esp_font = { "Tahoma", 12, 0, EFontFlags::FONTFLAG_OUTLINE };
		font crit_font = { "Consolas", 12, 0, EFontFlags::FONTFLAG_OUTLINE };
	public:
		void init_fonts( ) {
			offsets::surface->SetFontGlyphSet( ui_font.handle = offsets::surface->CreateFont( ), ui_font.name, ui_font.tall, ui_font.weight, 0, 0, ui_font.flags );
			offsets::surface->SetFontGlyphSet( esp_font.handle = offsets::surface->CreateFont( ), esp_font.name, esp_font.tall, esp_font.weight, 0, 0, esp_font.flags );
			offsets::surface->SetFontGlyphSet( crit_font.handle = offsets::surface->CreateFont( ), crit_font.name, crit_font.tall, crit_font.weight, 0, 0, crit_font.flags );
		}

		void line( rect_t area, clr_t col ) {
			offsets::surface->DrawSetColor( col );
			offsets::surface->DrawLine( area.x, area.y, area.w, area.h );
		}

		void rectangle( rect_t area, clr_t col ) {
			offsets::surface->DrawSetColor( col );
			offsets::surface->DrawFilledRect( area.x, area.y, area.x + area.w, area.y + area.h );
		}

		void outlined_rectangle( rect_t area, clr_t col ) {
			offsets::surface->DrawSetColor( col );
			offsets::surface->DrawOutlinedRect( area.x, area.y, area.x + area.w, area.y + area.h );
		}

		CHudTexture* get_icon( const char* icon, int icon_format = 0 ) {
			using fn = CHudTexture*( __stdcall* )( const char*, int );
			return ( ( fn )offsets::get_icon )( icon, icon_format );
		}

		void hud_texture( float x, float y, float s, CHudTexture* texture, clr_t col ) {
			if ( !texture )
				return;

			if ( texture->bRenderUsingFont ) {
				offsets::surface->DrawSetTextPos( x, y );
				offsets::surface->DrawSetTextFont( texture->hFont );
				offsets::surface->DrawSetTextColor( col );
				offsets::surface->DrawUnicodeChar( texture->cCharacterInFont );
			}

			else if ( texture->textureId != -1 ) {
				offsets::surface->DrawSetTexture( texture->textureId );
				offsets::surface->DrawSetColor( col );
				offsets::surface->DrawTexturedSubRect( x, y, x + ( texture->rc.right - texture->rc.left ) * s, y + ( texture->rc.bottom - texture->rc.top ) * s, texture->texCoords[ 0 ], texture->texCoords[ 1 ], texture->texCoords[ 2 ], texture->texCoords[ 3 ] );
			}
		}

		void corner_rectangle( rect_t area, int _x, int _y, clr_t col ) {
			line( { area.x, area.y, area.x + ( area.w / _x ), area.y }, col );
			line( { area.x, area.y, area.x, area.y + ( area.h / _y ) }, col );
			line( { area.x + area.w, area.y, area.x + area.w - ( area.w / _x ), area.y }, col );
			line( { area.x + area.w, area.y, area.x + area.w, area.y + ( area.h / _y ) }, col );
			line( { area.x, area.y + area.h, area.x + ( area.w / _x ), area.y + area.h },  col );
			line( { area.x, area.y + area.h, area.x, area.y + area.h - ( area.h / _y ) }, col );
			line( { area.x + area.w, area.y + area.h, area.x + area.w - ( area.w / _x ), area.y + area.h }, col );
			line( { area.x + area.w, area.y + area.h, area.x + area.w, area.y + area.h - ( area.h / _y) }, col );
		}

		std::pair< int, int > get_text_size( unsigned long font_handle, const char* str, ... ) {
			if ( !str )
				return std::pair< int, int >( 0, 0 );

			va_list va_alist;
			char cbuffer[ 1024 ] = { '\0' };
			wchar_t wstr[ 1024 ] = { '\0' };

			va_start( va_alist, str );
			vsprintf_s( cbuffer, str, va_alist );
			va_end( va_alist );

			wsprintfW( wstr, L"%hs", cbuffer );

			auto w = 0, h = 0;
			offsets::surface->GetTextSize( font_handle, wstr, w, h );

			return std::pair< int, int >( w, h );
		}

		std::pair< int, int > get_text_size( unsigned long font_handle, const wchar_t* str, ... ) {
			if ( !str )
				return std::pair< int, int >( 0, 0 );

			va_list va_alist;
			wchar_t wstr[ 1024 ] = { '\0' };

			va_start( va_alist, str );
			vswprintf_s( wstr, str, va_alist );
			va_end( va_alist );

			auto w = 0, h = 0;
			offsets::surface->GetTextSize( font_handle, wstr, w, h );

			return std::pair< int, int >( w, h );
		}

		void text( int x, int y, unsigned long font_handle, short align, clr_t col, const char* str, ... ) {
			if ( !str )
				return;

			va_list va_alist;
			char cbuffer[ 1024 ] = { '\0' };
			wchar_t wstr[ 1024 ] = { '\0' };

			va_start( va_alist, str );
			vsprintf_s( cbuffer, str, va_alist );
			va_end( va_alist );

			wsprintfW( wstr, L"%hs", cbuffer );

			if ( align ) {
				int w = 0, h = 0;
				offsets::surface->GetTextSize( font_handle, wstr, w, h );

				if ( align & sdk::text_align::align_left )
					x -= w;

				if ( align & sdk::text_align::align_top )
					y -= h;

				if ( align & sdk::text_align::align_center_horiz )
					x -= ( w / 2 );

				if ( align & sdk::text_align::align_center_vert )
					y -= ( h / 2 );
			}

			offsets::surface->DrawSetTextPos( x, y );
			offsets::surface->DrawSetTextFont( font_handle );
			offsets::surface->DrawSetTextColor( col );
			offsets::surface->DrawPrintText( wstr, wcslen( wstr ) );
		}

		void text( int x, int y, unsigned long font_handle, short align, clr_t col, const wchar_t* str, ... ) {
			if ( !str )
				return;

			va_list va_alist;
			wchar_t wstr[ 1024 ] = { '\0' };

			va_start( va_alist, str );
			vswprintf_s( wstr, str, va_alist );
			va_end( va_alist );

			if ( align ) {
				int w = 0, h = 0;
				offsets::surface->GetTextSize( font_handle, wstr, w, h );

				if ( align & sdk::text_align::align_left )
					x -= w;

				if ( align & sdk::text_align::align_top )
					y -= h;

				if ( align & sdk::text_align::align_center_horiz )
					x -= ( w / 2 );

				if ( align & sdk::text_align::align_center_vert )
					y -= ( h / 2 );
			}

			offsets::surface->DrawSetTextPos( x, y );
			offsets::surface->DrawSetTextFont( font_handle );
			offsets::surface->DrawSetTextColor( col );
			offsets::surface->DrawPrintText( wstr, wcslen( wstr ) );
		}

		void clip( rect_t rec );
		void reset_clip( );
		void blurred_rectangle( rect_t area, clr_t col, int passes = 1 );
		float lerp( float start, float end, float speed );
	};

	inline renderer* render = new renderer;
}