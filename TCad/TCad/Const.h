
#ifndef CONST_H_
#define CONST_H_
#include "stdafx.h"
#include "..\geoLib\Vector3d.h"

#define LASTER_VERSION 0x0005 
#define USE_VIEW_TYPE_1
const double VALUE_AXIS = 10000.0;
#define M_PI 3.1415926535897
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
#define K_WHITE     VEC3D(1.0, 1.0, 1.0)

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
    DR_ROOM,
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


#define ST_SOLID_DEF            0xFFFF
#define ST_DOTTED_DEF           0xAAAA
#define ST_DASH_DEF             0x00FF
#define ST_DASH_DOT_DEF         0x0C0F

enum StyleLine
{
    ST_SOLID = 300,
    ST_DOTTED,
    ST_DASHED,
    ST_DASH_DOT,
    ST_DASH_DOT_DOT,
    ST_FINE_DOT,
    ST_USER_PATTERN
};
#endif // 
