#include "gmath.h"

Matrix4x4::Matrix4x4() : a{ 0 }
{

}

Matrix4x4::~Matrix4x4()
{

}

float &Matrix4x4::operator()(int row, int col)
{
    return a[row][col];
}

vector3 Matrix4x4::operator*(const vector3 &i)
{
    vector3 o;
    o.x = i.x * (*this)(0,0) + i.y * (*this)(1,0) + i.z * (*this)(2,0) + (*this)(3,0);
    o.y = i.x * (*this)(0,1) + i.y * (*this)(1,1) + i.z * (*this)(2,1) + (*this)(3,1);
    o.z = i.x * (*this)(0,2) + i.y * (*this)(1,2) + i.z * (*this)(2,2) + (*this)(3,2);
    float w = i.x * (*this)(0,3) + i.y * (*this)(1,3) + i.z * (*this)(2,3) + (*this)(3,3);

    if (w != 0)
    {
        o.x /= w; o.y /= w; o.z /= w;
    }

    return o;
}
