
#ifndef TDESK_H_
#define TDESK_H_
#include "Const.h"
#include "stdafx.h"
#include "EntityObject.h"
#include "Object3D.h"
#include "TBox.h"

class TDesk : public Object3D
{
public:
    TDesk();
    ~TDesk();
    void Init();

    void Render();
    EntityObject* Clone();
private:
    Object3D* pAbove_;
    Object3D* pFoot1_;
    Object3D* pFoot2_;
    Object3D* pFoot3_;
    Object3D* pFoot4_;
};


#endif

