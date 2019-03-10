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
    void set_pos_cam(const POINT3D& cam_pt) { pos_cam_ = cam_pt; }
    UINT get_etype() const { return e_type_; }
    void set_etype(const UINT& type) { e_type_ = type; }
    virtual void Render() = 0;
    virtual EntityObject* Clone() = 0;
    virtual bool IsSelectedObject(const Vector3D &dir, const Vector3D& pos, Vector3D &p) = 0;
    void set_selected(const bool& is_select) { is_selected_ = is_select; }
    bool get_selected() const { return is_selected_; }
protected:
    POINT3D pos_pt_;
    POINT3D pos_cam_;
    UINT e_type_;
    bool is_selected_;
};

#endif



