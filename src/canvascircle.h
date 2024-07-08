#ifndef _CANVASCIRCLE_H_
#define _CANVASCIRCLE_H_

#include "lcanvasitem.h"
#include "lrect.h"
#include "lcircle.h"


class OthelloWindow;


class CanvasCircle : public LCanvasItem
{

    friend class OthelloWindow;

public:

    enum PieceMode
    {
        unActivated = 0, ///< 未激活
        Head,            ///< 正面
        Tail             ///< 反面
    };

    CanvasCircle() : LCanvasItem() {}

    CanvasCircle(const LCircle &circle) : m_circle(circle) {}

    const LCircle &circle() const { return m_circle; }

    PieceMode mode() const { return m_mode; }

    virtual LRect boundingRect() const override { return LRect(m_circle.m_roundCenterX - m_circle.m_roundRadius, m_circle.m_roundCenterY - m_circle.m_roundRadius, 2 * m_circle.m_roundRadius, 2 * m_circle.m_roundRadius); }

    virtual void paint(LDrawContext *dc) override;


protected:

    virtual void onActivated() override;


private:

    LCircle m_circle;

    PieceMode m_mode = PieceMode::unActivated;
};


#endif
