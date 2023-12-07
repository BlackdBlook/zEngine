#include "Mesh_Plan.h"

float Mesh_Plan::vertices[] = {
    // positions          // normal           // texture coords
    0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
   -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f  // top left 
};
unsigned int Mesh_Plan::indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3,  // second triangle
};

float Mesh_Plan::planeVertices[] = {
    // positions        // normal         // texture Coords 
    5.0f, -0.5f,  5.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,    // 右后
   -5.0f, -0.5f,  5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,    // 左后
   -5.0f, -0.5f, -5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 2.0f,    // 左前
    5.0f, -0.5f,  5.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,    // 右后
   -5.0f, -0.5f, -5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 2.0f,    // 左前
    5.0f, -0.5f, -5.0f,   0.0f, 1.0f, 0.0f,   2.0f, 2.0f     // 右前
};
