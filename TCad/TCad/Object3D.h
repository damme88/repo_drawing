#ifndef OBJECT_3D_H_
#define OBJECT_3D_H_
#include "EntityObject.h"

class Object3D : public EntityObject
{
public:
    Object3D();
    ~Object3D();
    
    enum Type3D
    {
        NONE_OBJ = 200,
        BOX_OBJ,
        CUBE_OBJ,
        SPHERE_OBJ,
        CYLINDER_OBJ,
        TRUNCATED_CONE_OBJ,
        CONE_OBJ,
        PYRAMID_OBJ,
        FRUSTUM_OBJ,
        OCTAGON_OBJ,
    };

    void set_type(const UINT& gType) { g_type_ = gType; }
    UINT get_type() const { return g_type_; }
    void set_color(VEC3D color) { color_value_ = color; }
    virtual void Render() = 0;
    virtual EntityObject* Clone() = 0;

    bool IsSelectedObject(const VEC3D& ppVector, const POINT3D& clickPt, POINT3D &retPt);
    bool LineCutBoundingBox(const VEC3D& ppVector, const POINT3D& clickPt, POINT3D &retPt);
    bool LineCutSurface(const VEC3D& ppVector, const POINT3D& clickPt, VEC3D &normalV, POINT3D& A, POINT3D &B, POINT3D &retPt);

protected:
    UINT g_type_;
    VEC3D color_value_;
    POINT3D bbmin_pt_;
    POINT3D bbmax_pt_;
};

#endif

