#ifndef _MYCIRCLE_H_
#define _MYCIRCLE_H_

#include "lrect.h"
#include "lcircle.h"
#include "ldrawcontext.h"


class MyCircle : public LCircle
{

public:

    enum PieceState
    {
        UnActivated = 0, ///< 未激活
        ReadyToActivate, ///< 在当前的棋盘的状态下可以被激活
        Head,            ///< 正面
        Tail             ///< 反面
    };

    MyCircle() : LCircle() {}

    MyCircle(int x, int y, int r) : LCircle(x, y, r) {}

    PieceState state() const { return m_state; }

    void setState(PieceState state) { m_state = state; }

    void paint(LDrawContext *dc);


private:

    PieceState m_state = PieceState::UnActivated;
};


#endif
