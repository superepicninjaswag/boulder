#include "Geometry.h"

bool Face::operator<(const Face &b) const
{
    float zSumFaceA = 0.0f;
    float zSumFaceB = 0.0f;
    for(int i = 0; i < 3; i++)
    {
        zSumFaceA += points[i].z;
        zSumFaceB += b.points[i].z;
    }
    zSumFaceA /= 3;
    zSumFaceB /= 3;
    return zSumFaceA > zSumFaceB;
}