#ifndef TBOX_H_
#define TBOX_H_

#include "stdafx.h"
#include "Object3D.h"

class TBox : public Object3D
{
public:
    TBox();
    TBox(const float& length, const float& width, const float& height);
    ~TBox();
    void Render();
    GLuint MakeBox();
    EntityObject* Clone();
    float get_length()const { return length_; }
    float get_width()const { return width_; }
    float get_height() const { return heigth_; }
    CString get_info();
protected:
    float length_;
    float width_;
    float heigth_;
};

#endif

