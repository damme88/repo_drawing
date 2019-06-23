#include "stdafx.h"
#include "TDesk.h"


TDesk::TDesk()
{

}


TDesk::~TDesk()
{

}

void TDesk::Init()
{
    pAbove_ = new TBox(200, 400, 10);
    pAbove_->set_pos(VEC3D(0, 0, 100));

    pFoot1_ = new TBox(10, 10, 100);
    pFoot2_ = new TBox(10, 10, 100);
    pFoot3_ = new TBox(10, 10, 100);
    pFoot4_ = new TBox(10, 10, 100);

    pFoot1_->set_pos(VEC3D(0, 0, 0)); 
    pFoot2_->set_pos(VEC3D(200, 0, 0)); 
    pFoot3_->set_pos(VEC3D(0, 400, 0)); 
    pFoot4_->set_pos(VEC3D(200, 400, 0)); 
}

void TDesk::Render()
{
    pAbove_->Render();
    pFoot1_->Render();
    pFoot2_->Render();
    pFoot3_->Render();
    pFoot4_->Render();
}

EntityObject* TDesk::Clone()
{
    return NULL;
}