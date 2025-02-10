#include "../lib/raylib/raylib.h"
#include <stdlib.h>
#include "debug_f3.h"

void debug_f3_show_debug(Camera3D *camera)
{
	
            DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(600, 5, 195, 100, BLUE);

            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- Projection: %s", (camera->projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                    (camera->projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera->position.x, camera->position.y, camera->position.z), 610, 60, 10, BLACK);
            DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera->target.x, camera->target.y, camera->target.z), 610, 75, 10, BLACK);
            DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera->up.x, camera->up.y, camera->up.z), 610, 90, 10, BLACK);


}

void debug_f3_update_time(frame_time *frame_time)
{
	frame_time->last_frame_time = frame_time->current_time;
	frame_time->current_time = GetTime();
	frame_time->delta_time = frame_time->current_time - frame_time->last_frame_time;
}

// Create a frame_time struct. 
frame_time* debug_f3_create_frame_time()
{
	frame_time *ft = (frame_time*) malloc(sizeof(frame_time));
	ft->current_time = GetTime();
	ft->last_frame_time = ft->current_time - 0.01;
	ft->last_frame_time = ft->current_time - ft->last_frame_time;

	return ft;
}
