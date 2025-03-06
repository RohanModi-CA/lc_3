#include "lib/fast_obj.h"
#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include <stdlib.h>
#include "mesh_load.h"
#include "../world_funcs/debug_f3.h"


fastObjMesh* mesh_load_init_mesh(const char* fp)
{
	fastObjMesh* mesh = fast_obj_read(fp);
	if (!mesh)
	{
		fprintf(stderr, "mesh_load: Failed to generate mesh from OBJ. Check filepath. \n");
		exit(1);
	}
	else
	{
		return mesh;
	}
} // mesh_load_init_mesh

void mesh_load_draw_vertex_mesh(fastObjMesh* mesh)
{
    // initialize x,y,z to be used for each triangle to extract from their Vector3s:
    float x_0; float y_0; float z_0;
    float x_1; float y_1; float z_1;
	float x_2; float y_2; float z_2;
	int pos_index_0; int pos_index_1; int pos_index_2;
	Vector3 vec0, vec1, vec2;
	Color color;

	if(mesh->index_count % 3 != 0){
		fprintf(stderr, "mesh_load.c: Not a triangular mesh.\n");
		exit(1);
	}


    // save the old state onto the stack, not necessary in this case.
    rlPushMatrix();

    // We are making lines
    rlColor4ub(0, 0, 100, 255);

		// Loop through each triangle. 
		for(int index=0; index < mesh->index_count; index += 3)
		{

			color.r = 0; color.b = 0; color.g=0; color.a=255;
			ClearBackground(RAYWHITE);


			// We need to make three lines, from vertex to vertex.
			// First we find the indices of the positions of each vertex.
			pos_index_0 = mesh->indices[index].p;
			pos_index_1 = mesh->indices[index + 1].p;
			pos_index_2 = mesh->indices[index + 2].p;

			// Now we need to extract the position x,y,z from each.
			x_0 = mesh->positions[3*pos_index_0 + 0];     x_1 = mesh->positions[3*pos_index_1 + 0];	 	  x_2 = mesh->positions[3*pos_index_2 + 0];
			y_0 = mesh->positions[3*pos_index_0 + 1]; 	  y_1 = mesh->positions[3*pos_index_1 + 1];       y_2 = mesh->positions[3*pos_index_2 + 1];
			z_0 = mesh->positions[3*pos_index_0 + 2]; 	  z_1 = mesh->positions[3*pos_index_1 + 2];       z_2 = mesh->positions[3*pos_index_2 + 2];

			// Process them into Vector3s
			vec0.x = x_0; vec0.y = y_0; vec0.z = z_0;
			vec1.x = x_1; vec1.y = y_1; vec1.z = z_1;
			vec2.x = x_2; vec2.y = y_2; vec2.z = z_2;

			// Draw Each Triangle
			DrawLine3D( vec0 , vec1, color);
			DrawLine3D( vec1 , vec2, color);
			DrawLine3D( vec2 , vec0, color);


		}
    rlPopMatrix();

} // mesh_load_draw_vertex_mesh

/* Multiplies all positions in a mesh by a scale_factor. */
void mesh_load_scale_mesh(fastObjMesh* mesh, float scale_factor)
{
	// Three position entries for each position_count.
	for(int i=0; i < 3 * mesh->position_count; ++i)
	{
		mesh->positions[i] *= scale_factor;
	}
} // mesh_load_scale_mesh


/* A debugging tool that will draw out the triangle side by side. Give it the mesh, a frame_time struct, the starting time, 
 * as well as an int counter which should be initialized to zero. */
void mesh_load_debug_animate_vertex_draw(fastObjMesh *mesh, frame_time *frame_time, double start_time, int *count)
{
	double time_between_animates = 0.5;
	double time_since_start;
	int max_count;


	// max_count is equal to the total number of triangle legs
	max_count = mesh->index_count;
	// Check whether we've drawn the appropriate leg for this time.
	time_since_start = frame_time->current_time - start_time;
	if (*count < max_count)
	{
		if( (*count == 0) || (int) (time_since_start/time_between_animates) > *count)
		{
			++*count;
		}
	}




    // initialize x,y,z to be used for each triangle to extract from their Vector3s:
    float x_0; float y_0; float z_0;
    float x_1; float y_1; float z_1;
	float x_2; float y_2; float z_2;
	int pos_index_0; int pos_index_1; int pos_index_2;
	Vector3 vec0, vec1, vec2;
	Color color;

	if(mesh->index_count % 3 != 0){
		fprintf(stderr, "mesh_load.c: Not a triangular mesh.\n");
		exit(1);
	}


    // save the old state onto the stack, not necessary in this case.
    rlPushMatrix();

    // We are making lines
	rlSetLineWidth(5.0);	
    rlColor4ub(0, 0, 100, 255);

		// Loop through each triangle. 
		for(int index=0; index < *count; index += 3)
		{

			color.r = 0; color.b = 0; color.g=0; color.a=255;

			// Change only if you're drawing the final one.
			if( index > *count - 3 )
			{
				color.r = 200; color.b = 20; color.g=20;
				rlColor4ub(200, 20, 20, 255);
			}



			// We need to make three lines, from vertex to vertex.
			// First we find the indices of the positions of each vertex.
			pos_index_0 = mesh->indices[index].p;
			pos_index_1 = mesh->indices[index + 1].p;
			pos_index_2 = mesh->indices[index + 2].p;

			// Now we need to extract the position x,y,z from each.
			x_0 = mesh->positions[3*pos_index_0 + 0];     x_1 = mesh->positions[3*pos_index_1 + 0];	 	  x_2 = mesh->positions[3*pos_index_2 + 0];
			y_0 = mesh->positions[3*pos_index_0 + 1] + 1; 	  y_1 = mesh->positions[3*pos_index_1 + 1] + 1;       y_2 = mesh->positions[3*pos_index_2 + 1]  + 1;
			z_0 = mesh->positions[3*pos_index_0 + 2]; 	  z_1 = mesh->positions[3*pos_index_1 + 2];       z_2 = mesh->positions[3*pos_index_2 + 2];

			// Process them into Vector3s
			vec0.x = x_0; vec0.y = y_0; vec0.z = z_0;
			vec1.x = x_1; vec1.y = y_1; vec1.z = z_1;
			vec2.x = x_2; vec2.y = y_2; vec2.z = z_2;

			// Draw Each Triangle
			DrawLine3D( vec0 , vec1, color);
			DrawLine3D( vec1 , vec2, color);
			DrawLine3D( vec2 , vec0, color);


		}

    rlPopMatrix();
}

// Assumes a triangular mesh
void mesh_load_render_mesh(fastObjMesh *mesh)
{
    // initialize x,y,z to be used for each triangle to extract from their Vector3s:
    float x_0; float y_0; float z_0;
    float x_1; float y_1; float z_1;
	float x_2; float y_2; float z_2;
	int pos_index_0; int pos_index_1; int pos_index_2;
	unsigned int face;
	Color face_color;


	if(mesh->index_count % 3 != 0){
		fprintf(stderr, "mesh_load.c: Not a triangular mesh.\n");
		exit(1);
	}


    // save the old state onto the stack, not necessary in this case.
    rlPushMatrix();

    // We are making lines
    rlBegin(RL_TRIANGLES);
    rlColor4ub(0, 0, 100, 255);

		//rlDisableBackfaceCulling();
		// Loop through each triangle. 
		for(int index=0; index < mesh->index_count; index += 3)
		{
			// Now we get the color.
			face = (int) index/3;
			face_color = mesh->face_colors[face];
			rlColor4ub(face_color.r, face_color.g, face_color.b, face_color.a);

			// We need to make three lines, from vertex to vertex.
			// First we find the indices of the positions of each vertex.
			pos_index_0 = mesh->indices[index].p;
			pos_index_1 = mesh->indices[index + 1].p;
			pos_index_2 = mesh->indices[index + 2].p;

			// Now we need to extract the position x,y,z from each.
			x_0 = mesh->positions[3*pos_index_0 + 0];     x_1 = mesh->positions[3*pos_index_1 + 0];	 	  x_2 = mesh->positions[3*pos_index_2 + 0];
			y_0 = mesh->positions[3*pos_index_0 + 1]; 	  y_1 = mesh->positions[3*pos_index_1 + 1];       y_2 = mesh->positions[3*pos_index_2 + 1];
			z_0 = mesh->positions[3*pos_index_0 + 2]; 	  z_1 = mesh->positions[3*pos_index_1 + 2];       z_2 = mesh->positions[3*pos_index_2 + 2];

			// Draw Each Triangle
			rlVertex3f(x_0, y_0, z_0);
			rlVertex3f(x_1, y_1, z_1);
			rlVertex3f(x_2, y_2, z_2);

		}

    rlEnd();
    rlPopMatrix();
}
