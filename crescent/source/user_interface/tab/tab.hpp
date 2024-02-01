#pragma once
#include "../column/column.hpp"

class c_tab : public c_base_element {
	std::deque< std::shared_ptr< c_column > > elements = { };
	float switch_interp = 0.f;
	bool once = false, clicked = false;
	void paint_children( );
	void update_children( );
public:
	bool enabled = false;
	rect_t column_area = { };
	std::shared_ptr< c_column > create_column( );
	c_tab( const char* name_ );
	void paint( ) override;
	void update( ) override;
};