#pragma once

#include "Matrix.h"

class Tuple;

namespace matrix {
Matrix4 Translation(double x, double y, double z);
Matrix4 Scale(double x, double y, double z);
Matrix4 RotationX(double rad);
Matrix4 RotationY(double rad);
Matrix4 RotationZ(double rad);
Matrix4 Shear(double xy, double xz, double yx, double yz, double zx, double zy);
Matrix4 ViewTransformation(Tuple from, Tuple to, Tuple up);
}