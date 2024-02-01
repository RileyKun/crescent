#pragma once
#include "../base_element/base_element.hpp"

class c_base_draggable : public c_base_element {
public:
	bool dragging = false, clicked = false, hovering = false;
	int drag_offset_x = 0, drag_offset_y = 0;
	float last_click_time = 0.f;
};