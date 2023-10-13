struct vector3
{
    float x, y, z;
};

class Matrix4x4
{
private:
    float a[4][4];
public:
    Matrix4x4(/* args */);
    ~Matrix4x4();
    float &operator()(int row, int col);
    vector3 operator*(const vector3 &i);
};