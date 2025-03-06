#ifndef MESH_LOAD_H
#define MESH_LOAD_H

#include "lib/fast_obj.h"
#include "../world_funcs/debug_f3.h"

// Function to load a mesh from a file using fast_obj
fastObjMesh* mesh_load_init_mesh(const char* fp);

// Function to draw the mesh as a wireframe.
void mesh_load_draw_vertex_mesh(fastObjMesh* mesh);

// Scale the mesh by scale_factor. 
void mesh_load_scale_mesh(fastObjMesh* mesh, float scale_factor);


void mesh_load_debug_animate_vertex_draw(fastObjMesh *mesh, frame_time *frame_time, double start_time, int *count);

void mesh_load_render_mesh(fastObjMesh *mesh);

#endif
