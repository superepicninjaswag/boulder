#pragma once

#include <cmath>

struct Vec3
{
public:
    float x, y, z;
    Vec3 operator+(const Vec3 &i);
    Vec3 operator-(const Vec3 &i);
    float operator*(const Vec3 &i);
    Vec3 operator*(const float &i);
    void Normalize();
    float Length();
    Vec3 CrossProduct(const Vec3 &i);
};

class Matrix4x4
{
private:
    float a[4][4];
public:
    Matrix4x4();
    float &operator()(int row, int col);
    Vec3 operator*(const Vec3 &i);
};