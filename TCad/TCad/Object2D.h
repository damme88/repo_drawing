#ifndef OBJECT_2D_H_
#define OBJECT_2D_H_
#include "stdafx.h"
#include "EntityObject.h"

class Object2D : public EntityObject
{
public:
    enum Type2D
    {
        POINT = 0,
        LINE,
        POLY_LINE,
        RECTANGLE,
        POLYGON,
        CIRCLE,
        ELIPSE,
    };
    Object2D();
    ~Object2D();
    UINT get_type() const { return g_type_; }
    void set_type(const UINT& type) { g_type_ = type; }
    void set_color(VEC3D color) { color_value_ = color; }
    virtual void Render() = 0;
    virtual bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p) = 0;
    virtual EntityObject* Clone() = 0;
protected:
    UINT g_type_;
    VEC3D color_value_;
};

#endif

