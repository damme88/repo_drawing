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
        LINE = 1,
        POLYGON = 2,
        CIRCLE = 3,
        ELIPSE = 4,
    };
    Object2D();
    ~Object2D();
    UINT get_type() const { return g_type_; }
    void set_type(const UINT& type) { g_type_ = type; }
    virtual void Render() = 0;
protected:
    UINT g_type_;
};

#endif

