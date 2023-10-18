#pragma once

struct Vec3
{
    float x, y, z;
    Vec3 operator+(const Vec3 &i);
};

class Matrix4x4
{
private:
    float a[4][4];
public:
    Matrix4x4(/* args */);
    ~Matrix4x4();
    float &operator()(int row, int col);
    Vec3 operator*(const Vec3 &i);
};