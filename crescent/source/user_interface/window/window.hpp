#pragma once
#include "../base_draggable/base_draggable.hpp"
#include "../tab/tab.hpp"

class c_window : public c_base_draggable {
	std::deque< std::shared_ptr< c_tab > > elements = { };
	rect_t title_area = { }, tab_area = { }, column_area = { };
	int selected_tab = 0;
	void paint_children( );
	void update_children( );
public:
	std::shared_ptr< c_tab > create_tab( const char* name );
	c_window( const char* name_, rect_t area_ );
	void paint( ) override;
	void update( ) override;
};