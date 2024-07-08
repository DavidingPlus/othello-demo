#ifndef _CANVASCIRCLE_H_
#define _CANVASCIRCLE_H_


#include "lcanvasitem.h"
#include "lrect.h"
#include "lcircle.h"


class CanvasCircle : public LCanvasItem
{

public:

    CanvasCircle() : LCanvasItem() {}

    ~CanvasCircle() = default;

    virtual LRect boundingRect() const override;

    virtual void paint(LDrawContext *dc) override;


protected:

    virtual void onActivated() override;


private:

    LCircle m_circle;
};


#endif
