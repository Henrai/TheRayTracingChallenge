#pragma once

#include "Matrix.h"

namespace matrix {
Matrix4 Translation(float x, float y, float z);
Matrix4 Scale(float x, float y, float z);
Matrix4 RotationX(float rad);
Matrix4 RotationY(float rad);
Matrix4 RotationZ(float rad);
Matrix4 Shear(float xy, float xz, float yx, float yz, float zx, float zy);
}