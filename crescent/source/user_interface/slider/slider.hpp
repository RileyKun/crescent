#pragma once
#include "../base_draggable/base_draggable.hpp"

class c_slider_int : public c_base_draggable {
	int* value = nullptr, min = 0, max = 0, step = 1;
	float bar_interp = 0.f, hover_interp = 0.f;
	const char* unit = "";
	bool once = false;
public:
	c_slider_int( int* value_, int min_, int max_, int step_, const char* name_, const char* unit_ );
	void paint( ) override;
	void update( ) override;
};

class c_slider_float : public c_base_draggable {
	float* value = nullptr, min = 0.f, max = 0.f, step = 1.f;
	float bar_interp = 0.f, hover_interp = 0.f;
	const char* unit = "";
	bool once = false;
public:
	c_slider_float( float* value_, float min_, float max_, float step_, const char* name_, const char* unit_ );
	void paint( ) override;
	void update( ) override;
};