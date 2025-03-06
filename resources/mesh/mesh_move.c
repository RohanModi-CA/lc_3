#include "mesh_move.h"
#include "../world_funcs/debug_f3.h"
#include "lib/fast_obj.h"
#include <stdio.h>
#include "raylib.h"

// Simple translation of a mesh by addition. Possibly needs triangularized.
void mesh_move_translate_mesh(fastObjMesh *mesh, Vector3 delta_pos)
{

	for(int i=0; i< 3 * mesh->position_count; i+=3)
	{
		// This avoids doing division for every single movement.
		mesh->positions[i] += delta_pos.x;
		mesh->positions[i+1] += delta_pos.y;
		mesh->positions[i+2] += delta_pos.z;
		
	}
    

}

void mesh_move_const_vel_translate(fastObjMesh *mesh, Vector3 velocity, frame_time *ft)
{
	Vector3 displacement;

	displacement.x = velocity.x * ft->delta_time;
	displacement.y = velocity.y * ft->delta_time;
	displacement.z = velocity.z * ft->delta_time;

	mesh_move_translate_mesh(mesh, displacement);
} // mesh_move_const_vel_translate;
