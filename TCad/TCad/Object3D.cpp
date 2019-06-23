#include "stdafx.h"
#include "Object3D.h"


Object3D::Object3D()
{
    color_value_.Set(1.0, 1.0, 1.0);
    g_type_ = NONE_OBJ;
}


Object3D::~Object3D()
{
}

void Object3D::Serialize(CArchive &ar)
{
    EntityObject::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << g_type_;
        ar << color_value_.x_;
        ar << color_value_.y_;
        ar << color_value_.z_;
    }
    else
    {
        ar >> g_type_;
        ar >> color_value_.x_;
        ar >> color_value_.y_;
        ar >> color_value_.z_;
    }
}

bool Object3D::IsSelectedObject(const VEC3D &ppVector, const POINT3D& clickPt, POINT3D &retPt)
{
    bool ret = LineCutBoundingBox(ppVector, clickPt, retPt);
    return ret;
}


bool Object3D::LineCutBoundingBox(const VEC3D& ppVector, const POINT3D& clickPt, POINT3D &p_on_bb)
{
    Vector3D normal;
    POINT3D ePt;
    bool has_a_point = false;
    POINT3D bbmax = bbmax_pt_;
    POINT3D bbmin = bbmin_pt_;

    // thuc hien kiem tra giao diem cua duong vuong goc screen va pos voi 6 mat bounding
    //Left Face (Y axis)
    POINT3D p = bbmax;
    p.x_ = bbmin.x_;
    normal.Set(1, 0, 0);
    if (LineCutSurface(ppVector, clickPt, normal, bbmin, p, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    //Front Face (xoz)
    p = bbmax;
    p.y_ = bbmin.y_;
    normal.Set(0, 1, 0);
    if (LineCutSurface(ppVector, clickPt, normal, bbmin, p, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    //Bottom face
    p = bbmax;
    p.z_ = bbmin.z_;
    normal.Set(0, 0, 1);
    if (LineCutSurface(ppVector, clickPt, normal, bbmin, p, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    //right face
    p = bbmin;
    p.x_ = bbmax.x_;
    normal.Set(1, 0, 0);
    if (LineCutSurface(ppVector, clickPt, normal, p, bbmax, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    //Back face
    p = bbmin;
    p.y_ = bbmax.y_;
    normal.Set(0, 1, 0);
    if (LineCutSurface((Vector3D)ppVector, clickPt, normal, p, bbmax, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    //Top Face
    p = bbmin;
    p.z_ = bbmax.z_;
    normal.Set(0, 0, 1);
    if (LineCutSurface(ppVector, clickPt, normal, p, bbmax, ePt))
    {
        if (!has_a_point)
        {
            p_on_bb = ePt;
            has_a_point = true;
        }
        else
        {
            Vector3D temp = p_on_bb - ePt;
            if (temp.scalar(ppVector) < 0)
            {
                p_on_bb = ePt;
            }
        }
    }

    return has_a_point;
}

bool Object3D::LineCutSurface(const VEC3D &ppVector, const POINT3D &clickPt, VEC3D &norV, POINT3D &A, POINT3D &B, POINT3D &retPt)
{
    // Neu ppVector vuong goc voi vector phap tuyen cua face
    // => KO TON TAI GIAO DIEM
    if (norV.scalar(ppVector) == 0)
    {
        return false;
    }

    // Phuong trinh mat phang co cong thuc la: Ax + By + Cz + D = 0  
    // Vector(A,B,C) = n la vector phap tuyen
    //  <=>  n.x_*x + n.y_*y + n.z_*z + D = 0 
    // Voi hai diem A B thuoc mat phang. Giai he phuong trinh de tim hang so D
    //    n.x_*A.x_ + n.y_*A.y_ + n.z_*A.z_ + D = 0
    //    n.x_*B.x_ + n.y_*B.y_ + n.z_*B.z_ + D = 0


    double D = -(norV.x_ * (A.x_ + B.x_) + norV.y_ * (A.y_ + B.y_) + norV.z_ * (A.z_ * B.z_)) / 2.0;

    /* phuong trinh duong thang voi vector chi phuong ppVector
    x = clickPt.x_ + ppVector.x *t;
    y = clickPt.y_ + ppVector.y *t;
    z = clickPt.y_ + ppVector.z *t;
    */

    // neu x,y,z la tao do giao diem cua duong thang va mat phang.
    // =>  (clickpt.x + ppVector.x*t).n.x + (clickpt.y + ppVector.y*t).n.y + (clickpt.z + ppVector.z*t).n.z + D = 0  
    // => tinh toan dc t theo cong thuc duoi day.

    double t = -1 * (D + norV.x_ * clickPt.x_ + norV.y_ * clickPt.y_ + norV.z_ * clickPt.z_) / (norV.x_ * ppVector.x_ + norV.y_ * ppVector.y_ + norV.z_ * ppVector.z_);

    // Tinh dc t roi thi se tim ra giao diem cua duong thang vao mat phang

    retPt.x_ = clickPt.x_ + ppVector.x_ * t;
    retPt.y_ = clickPt.y_ + ppVector.y_ * t;
    retPt.z_ = clickPt.z_ + ppVector.z_ * t;

    // Phai kiem tra xem giao diem nay co nam trong vung bounding khong

#if 1
    if (retPt.x_ >= A.x_ && retPt.x_ <= B.x_ &&
        retPt.y_ >= A.y_ && retPt.y_ <= B.y_ &&
        retPt.z_ >= A.z_ && retPt.z_ <= B.z_)
    {
        return true;
    }
#else
    if (norV.x_ == 0)
    {
        // mat phang ko bao gio la mat yoz. (trong mat yoz, moi diem deu co x = 0)
        // Do do khi ko phai la yoz thi B luon co x > so voi x cua A
        // Suy retPt nam trong vung AB thi phai co x nam trong khoang [A.x va B.x]
        if (retPt.x_ < A.x_ || retPt.x_ > B.x_)
        {
            // Va khi dieu kien do ko xay ra => no nam ngoai vung
            return false;
        }
    }

    // Tuong tu nhu vay
    if (norV.y_ == 0)
    {
        if (retPt.y_ < A.y_ || retPt.y_ > B.y_)
        {
            return false;
        }
    }

    if (norV.z_ == 0)
    {
        if (A.z_ > retPt.z_ || retPt.z_ > B.z_)
        {
            return false;
        }
    }
#endif


    return false;
}