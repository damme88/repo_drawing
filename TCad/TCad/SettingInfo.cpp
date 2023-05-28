#include "stdafx.h"
#include "SettingInfo.h"

SettingInfo* SettingInfo::instance_ = NULL;

SettingInfo::SettingInfo()
{
    width_ = 0.01;
    style_ = 0;
    color_ = VEC3D(1.0, 1.0, 1.0);
}

INT SettingInfo::GetStyle()
{
    INT st = ST_SOLID_DEF;
    switch (style_)
    {
    case ST_SOLID:
        st = ST_SOLID_DEF;      break;
    case ST_DOTTED:
        st = ST_DOTTED;         break;
    case ST_DASHED:
        st = ST_DASH_DEF;       break;
    case ST_DASH_DOT:
        st = ST_DASH_DOT_DEF;   break;
    default:
        break;
    }
    return st;
}

SettingInfo::~SettingInfo()
{
}

SettingInfo* SettingInfo::getInstance()
{
    if (instance_ == NULL)
    {
        instance_ = new SettingInfo();
    }

    return instance_;
}