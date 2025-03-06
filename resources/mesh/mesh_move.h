#ifndef MESH_MOVE_H
#define MESH_MOVE_H
#include "lib/fast_obj.h"
#include "../lib/raylib/raylib.h"
#include "../world_funcs/debug_f3.h"


void mesh_move_const_vel_translate(fastObjMesh *mesh, Vector3 velocity, frame_time *ft);


#endif
