#ifndef _OTHELLOWINDOW_H_
#define _OTHELLOWINDOW_H_

#include "ldrawwindow.h"
#include "lvector.h"
#include "lmouseevent.h"
#include "lpair.h"
#include "lset.h"
#include "lhash.h"

#include "mycircle.h"


class MessageWindow;
class LTimer;

class OthelloWindow : public LDrawWindow
{

public:

    OthelloWindow(int sideLen, MessageWindow *pMessageWindow);


protected:

    void handleMousePressEvent(LMouseEvent *e) override;

    void handleCloseEvent(LEvent *e) override { exit(0); }


private:

    void scan();

    bool move(int x, int y);

    void init();

    void AIMove();

    // TODO 目前的AI只实现了下棋功能本身，没有任何策略
    int AIStrategy();

    void timeOutSlot();

    static LPair<int, int> convertToPair(int index) { return LPair<int, int>(index % 8, index / 8); }

    static int convertToIndex(int x, int y) { return 8 * y + x; }

    static const LPair<int, int> directions[8];

    LVector<MyCircle> m_data;

    LSet<int> m_head;

    LSet<int> m_tail;

    LHash<int, LVector<int>> m_target;

    bool m_nowPlayer = true;

    bool m_isGameOver = false;

    MessageWindow *m_pMessageWindow = nullptr;

    LTimer *m_pAITimer = nullptr;
};


#endif
