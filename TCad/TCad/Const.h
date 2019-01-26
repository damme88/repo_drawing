
#ifndef CONST_H_
#define CONST_H_
#include "stdafx.h"
#include "..\geoLib\Vector3d.h"


#define USE_VIEW_TYPE_1
const double VALUE_AXIS = 10000.0;
#define M_PI 3.1415

#define VEC3D Vector3D
#define POINT3D VEC3D


enum Type2D
{
    NONE = 100,
    DR_POINT = 101,
    DR_LINE = 102,
    DR_POLYGON = 103,
    DR_RECTANGLE,
    DR_CIRCLE,
    DR_ELIP,
};
#endif // 
