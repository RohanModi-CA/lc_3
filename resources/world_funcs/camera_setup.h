//
// Created by gram on 23/11/24.
//
#include <stdlib.h>
#include "raylib.h"

#ifndef CAMERA_SETUP_H
#define CAMERA_SETUP_H

#endif //CAMERA_SETUP_H

Camera3D* initialize_camera(void){
  Camera3D* camera = (Camera3D*)malloc(sizeof(Camera3D));
  camera->position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
  camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera->fovy = 45.0f;                                // Camera field-of-view Y
  camera->projection = CAMERA_PERSPECTIVE;             // Camera projection type
  return camera;
}
