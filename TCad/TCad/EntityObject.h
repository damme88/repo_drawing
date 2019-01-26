#ifndef ENTITY_OBJ_H_
#define ENTITY_OBJ_H_

#include "stdafx.h"
#include "..\geoLib\Vector3d.h"

class EntityObject
{
public:
    EntityObject();
    ~EntityObject();

    enum EntityType
    {
        NONE = 0,
        OBJ_2D = 1,
        OBJ_3D = 2
    };

    POINT3D get_pos() const { return pos_pt_; }
    void set_pos(const POINT3D& pt) { pos_pt_ = pt; }
    UINT get_etype() const { return e_type_; }
    void set_etype(const UINT& type) { e_type_ = type; }
    virtual void Render() = 0;
protected:
    POINT3D pos_pt_;
    UINT e_type_;
};

#endif



