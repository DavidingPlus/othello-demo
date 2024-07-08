#ifndef _CANVASCIRCLE_H_
#define _CANVASCIRCLE_H_


#include "lcanvasitem.h"
#include "lrect.h"
#include "lcircle.h"


class CanvasCircle : public LCanvasItem
{

public:

    enum PieceMode
    {
        unActivated = 0, ///< 未激活
        Head,            ///< 正面
        Tail             ///< 反面
    };

    CanvasCircle() : LCanvasItem() {}

    const LCircle &circle() const { return m_circle; }

    virtual void paint(LDrawContext *dc) override;


protected:

    virtual void onActivated() override;


private:

    LCircle m_circle;

    PieceMode m_mode = PieceMode::unActivated;
};


#endif
