#ifndef DEBUG_F3_H
#define DEBUG_F3_H
#include "../lib/raylib/raylib.h"

void debug_f3_show_debug(Camera3D *camera);

typedef struct
{
	double current_time;
	double last_frame_time;
	double delta_time;
} frame_time;

void debug_f3_update_time(frame_time *frame_time);

frame_time* debug_f3_create_frame_time();


#endif
