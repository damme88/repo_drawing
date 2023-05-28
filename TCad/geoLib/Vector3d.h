
#ifndef VEC_3D_H_
#define VEC_3D_H_

class Vector3D 
{
public:
    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(float v1[3]);
    ~Vector3D();

public:
    float distance(Vector3D pt);
    double scalar(const Vector3D & v1);

    const Vector3D &operator + (Vector3D &v1) 
    {
        Vector3D temp;
        temp.x_ = x_ + v1.x_;
        temp.y_ = y_ + v1.y_;
        temp.z_ = z_ + v1.z_;
        return temp;
    }

    const Vector3D &operator - (Vector3D &v1) 
    {
        Vector3D temp;
        temp.x_ = x_ - v1.x_;
        temp.y_ = y_ - v1.y_;
        temp.z_ = z_ - v1.z_;
        return temp;
    }

    const Vector3D &operator * (Vector3D &v1) 
    {
        Vector3D temp;
        temp.x_ = y_ * v1.z_ - z_ * v1.y_;
        temp.y_ = z_ * v1.x_ - x_ * v1.z_;
        temp.z_ = x_ * v1.y_ - y_ * v1.x_;
        return temp;
    }

    const Vector3D &operator *(double a) 
    {
        Vector3D temp;
        temp.x_ = x_ * a;
        temp.y_ = y_ * a;
        temp.z_ = z_ * a;
        return temp;
    }

    double abs();
    Vector3D Unit();
    void Set(double x, double y, double z);
    Vector3D CrossProduct(const Vector3D& v);
    double AngleTo(Vector3D& v);
    Vector3D GetPointDis(const Vector3D& v, float d);
    float x_;
    float y_;
    float z_;
};

#endif // VEC_3D_H_
