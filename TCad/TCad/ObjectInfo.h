#ifndef OBJECT_INFO_H_
#define OBJECT_INFO_H_

#include "stdafx.h"
#include "EntityObject.h"

class ObjectInfo
{
public:
    CString name_;
    CString properties_;
    CString type_;
    EntityObject* obj_data_;

    ObjectInfo();
    ~ObjectInfo();
};
#endif

