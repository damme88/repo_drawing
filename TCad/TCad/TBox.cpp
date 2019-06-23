#include "stdafx.h"
#include "TBox.h"
#include "TLine.h"


TBox::TBox()
{
    e_type_ = OBJ_3D;
    v_dir_ = VEC3D(1.0, 0.0, 0.0);
    angle_ = 0.0;
    g_type_ = BOX_OBJ;
}

TBox::TBox(const float& length, const float& width, const float& height)
{
    length_ = length;
    width_ = width;
    heigth_ = height;
    e_type_ = OBJ_3D;
    g_type_ = BOX_OBJ;
    angle_ = 0.0;
}

TBox::~TBox()
{
}

void TBox::CopyFrom(TBox* obj)
{
    this->length_ = obj->length_;
    this->width_ = obj->width_;
    this->heigth_ = obj->heigth_;
    this->color_value_ = obj->color_value_;
    this->angle_ = obj->angle_;
}

EntityObject* TBox::Clone()
{
    TBox* new_obj = new TBox();
    new_obj->length_ = this->length_;
    new_obj->width_ = this->width_;
    new_obj->heigth_ = this->heigth_;
    new_obj->color_value_ = this->color_value_;
    new_obj->angle_ = this->angle_;
    new_obj->g_type_ = this->g_type_;
    new_obj->e_type_ = this->e_type_;
    return new_obj;
}

CString TBox::get_info()
{
    CString str = _T("BOX_");
    CString strL;
    strL.Format(_T("%d"), (int)length_);
    CString strW;
    strW.Format(_T("%d"), (int)width_);
    CString strH;
    strH.Format(_T("%d"), (int)heigth_);
    str += strL + _T("x") + strW + _T("x") + strH;

    return str;
}

void TBox::Render()
{
    glPushMatrix();
    glTranslatef(pos_pt_.x_, pos_pt_.y_, pos_pt_.z_);
    glRotatef(angle_, 0.0, 0.0, 1.0);
    MakeBox();
    glPopMatrix();
}

GLuint TBox::MakeBox()
{
    VEC3D vZ = VEC3D(0.0, 0.0, 1.0);
    VEC3D vVer = vZ.CrossProduct(v_dir_);
    float x = length_;
    float y = width_;
    float z = heigth_;

    if (is_selected_) 
      glColor3f(1.0, 0.0, 0);
    else 
      glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    //Bottom
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(0, y, 0);
    glEnd();

    // right
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(0, y, 0);
    glEnd();

    ////Top
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, 0, z);
    glEnd();

    //// left
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, 0, z);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glEnd();

    //Front
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, y, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glVertex3f(0, y, z);
    glEnd();

    //Back
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, 0, z);
    glVertex3f(0, 0, z);

    glEnd();

    bbmin_pt_ = pos_pt_;
    bbmax_pt_ = POINT3D(bbmin_pt_.x_ + length_, bbmin_pt_.y_ + width_, bbmin_pt_.z_ + heigth_);
    return 1;
}

void TBox::Serialize(CArchive &ar)
{
    Object3D::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << length_;
        ar << width_;
        ar << heigth_;
        ar << angle_;
        ar << v_dir_.x_;
        ar << v_dir_.y_;
        ar << v_dir_.z_;
    }
    else
    {
        ar >> length_;
        ar >> width_;
        ar >> heigth_;
        ar >> angle_;
        ar >> v_dir_.x_;
        ar >> v_dir_.y_;
        ar >> v_dir_.z_;
    }
}