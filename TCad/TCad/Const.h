
#ifndef CONST_H_
#define CONST_H_
#include "stdafx.h"
#include "..\geoLib\Vector3d.h"

#define LASTER_VERSION 0x0005 
#define USE_VIEW_TYPE_1
const double VALUE_AXIS = 10000.0;
#define M_PI 3.1415
#define BUFSIZE 512

#define VEC3D Vector3D
#define POINT3D VEC3D

const double EPSILON = 0.01;
const double EPSILON_SMALL = 0.1;
const double EPSILON_LARGE = 8;

#define K_RED       VEC3D(1.0, 0.0, 0.0)
#define K_GREEN     VEC3D(0.0, 1.0, 0.0)
#define K_BLUE      VEC3D(0.0, 0.0, 1.0)
#define K_YELLOW    VEC3D(1.0, 1.0, 0.0)
#define K_PINK      VEC3D(1.0, 0.0, 1.0)

enum Type2D
{
    NONE = 100,
    DR_POINT,
    DR_LINE,
    DR_POLY_LINE,
    DR_POLYGON,
    DR_RECTANGLE,
    DR_CIRCLE,
    DR_ARC,
    DR_ELIP,
};

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

#endif // 
