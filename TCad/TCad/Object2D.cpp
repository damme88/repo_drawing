#include "stdafx.h"
#include "Object2D.h"


Object2D::Object2D()
{
    e_type_ = OBJ_2D;
    pos_pt_.Set(0.0, 0.0, 0.0);
    color_value_.Set(1.0, 1.0, 1.0);
}


Object2D::~Object2D()
{

}
