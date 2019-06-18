#include "stdafx.h"
#include "TBox.h"
#include "TLine.h"


TBox::TBox()
{
    e_type_ = OBJ_3D;
}

TBox::TBox(const float& length, const float& width, const float& height)
{
    length_ = length;
    width_ = width;
    heigth_ = height;
    e_type_ = OBJ_3D;
}

TBox::~TBox()
{
}

EntityObject* TBox::Clone()
{
    TBox* new_obj = new TBox();
    new_obj->length_ = this->length_;
    new_obj->width_ = this->width_;
    new_obj->heigth_ = this->heigth_;
    new_obj->color_value_ = this->color_value_;
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
    MakeBox();
    glPopMatrix();
}

GLuint TBox::MakeBox()
{
    float x = length_;
    float y = width_;
    float z = heigth_;

    if (is_selected_) 
      glColor3f(1.0, 0.0, 0);
    else 
      glColor3f(color_value_.x_, color_value_.y_, color_value_.z_);
    //Back
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(0, y, 0);
    glEnd();

    // left
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(0, y, 0);
    glEnd();

    //front
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, 0, z);
    glEnd();

    //// right
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, 0, z);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, y, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glVertex3f(0, y, z);

    //Bottom
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