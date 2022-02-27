#include <Transformation.h>
#include <Matrix.h>
#include <cmath>

namespace matrix {
    Matrix4 Translation(float x, float y, float z) {
        Matrix4 ans = Matrix4::Identity();
        ans[0][3] = x;
        ans[1][3] = y;
        ans[2][3] = z;
        return ans;
    }

    Matrix4 Scale(float x, float y, float z) {
        Matrix4 ans = Matrix4::Identity();
        ans[0][0] = x;
        ans[1][1] = y;
        ans[2][2] = z;
        return ans;
    }

    Matrix4 RotationX(float rad) {
        Matrix4 ans = Matrix4::Identity();
        float sinr = sin(rad);
        float cosr = cos(rad);
        ans[1][1] = cosr;
        ans[1][2] = -sinr;
        ans[2][1] = sinr;
        ans[2][2] = cosr;
        return ans;
    }
    Matrix4 RotationY(float rad) {
        Matrix4 ans = Matrix4::Identity();
        float sinr = sin(rad);
        float cosr = cos(rad);
        ans[0][0] = cosr;
        ans[2][0] = -sinr;
        ans[0][2] = sinr;
        ans[2][2] = cosr;
        return ans;
    }
    Matrix4 RotationZ(float rad) {
        Matrix4 ans = Matrix4::Identity();
        float sinr = sin(rad);
        float cosr = cos(rad);
        ans[0][0] = cosr;
        ans[0][1] = -sinr;
        ans[1][0] = sinr;
        ans[1][1] = cosr;
        return ans;
    }

    Matrix4 Shear(float xy, float xz, float yx, float yz, float zx, float zy) {
        Matrix4 ans = Matrix4::Identity();
        ans[0][1] = xy;
        ans[0][2] = xz;
        ans[1][0] = yx;
        ans[1][2] = yz;
        ans[2][0] = zx;
        ans[2][1] = zy;
        return ans;
    }
}