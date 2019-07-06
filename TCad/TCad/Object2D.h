#ifndef OBJECT_2D_H_
#define OBJECT_2D_H_
#include "stdafx.h"
#include "EntityObject.h"

class Object2D : public EntityObject
{
public:
    enum Type2D
    {
        POINT = 100,
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

    //virtual function
    virtual void Render() { ; }
    virtual EntityObject* Clone() {return NULL;}
    virtual void Serialize(CArchive &ar);
    virtual bool IsSelectedObject(const Vector3D &dir, const POINT3D& pos, POINT3D &p){return false;}
    virtual void DoGripPoint();
    virtual void GetGripPoint(const POINT3D& pt);
protected:
    UINT g_type_;
    VEC3D color_value_;
};

#endif

