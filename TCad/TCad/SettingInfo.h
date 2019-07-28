#pragma once
#include "Const.h"
class SettingInfo
{
public:
    SettingInfo();
    ~SettingInfo();
    static SettingInfo* getInstance();
    INT GetStyle();
public:
    float   width_;
    VEC3D   color_;
    UINT     style_;
private:
    static SettingInfo* instance_;
    //Variable

};

