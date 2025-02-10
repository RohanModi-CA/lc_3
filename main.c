//main.c


#include <stdlib.h>
#include "resources/lib/raylib/raylib.h"
#include "resources/world_funcs/camera_setup.h"
#include <stdio.h>
#include <math.h>
#include "resources/mesh/mesh_load.h"
#include "resources/world_funcs/debug_f3.h"
#include "resources/mesh/mesh_triangularize.h"



void initialize_window(int width, int height, int fps, const char* title){
    SetTraceLogLevel(LOG_FATAL); // Prevent Raylib from spamming the console
    const int screenWidth = 1400;
    const int screenHeight = 950;
    InitWindow(screenWidth, screenHeight, "LC - 3");
	DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(fps);                   // Set our game to run at 60 frames-per-second
}

int launch_raylib(fastObjMesh *mesh)
{
	/* First we initialize our window and camera. */
	initialize_window(1300, 900, 30, "LC-3");
	Camera3D* camera = initialize_camera();
	frame_time *ft = debug_f3_create_frame_time();

	int debug_vertex_draw_count = 0; double debug_vertex_draw_start_time; 


	/* Main Loop */
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		UpdateCamera(camera, CAMERA_FREE);
		debug_f3_update_time(ft);
		BeginDrawing();


			ClearBackground(RAYWHITE);
			BeginMode3D(*camera);
			DrawGrid(150, 1.0f);

			mesh_load_draw_vertex_mesh(mesh); 


			EndMode3D();

			debug_f3_show_debug(camera);


		EndDrawing();
	}




	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context



	free(camera);
	return 0;
}


int main(void)
{
	fastObjMesh *mesh;

	const char obj_filepath[] = "/home/gram/Documents/FileFolder/Projects/lc_3/resources/models/scene/scene.obj";

	mesh = mesh_triangularize_gen_triangularized_mesh(obj_filepath);
	mesh_load_scale_mesh(mesh, 0.01);

	launch_raylib(mesh);

}
