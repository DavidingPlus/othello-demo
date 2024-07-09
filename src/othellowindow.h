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


class OthelloWindow : public LDrawWindow
{

    friend class MessageWindow;


public:

    OthelloWindow(int sideLen);


protected:

    void handleMousePressEvent(LMouseEvent *e) override;

    void handleCloseEvent(LEvent *e) override { exit(0); }


private:

    void scan();

    bool move(int x, int y);

    void init();

    static LPair<int, int> convertToPair(int index) { return LPair<int, int>(index % 8, index / 8); }

    static int convertToIndex(int x, int y) { return 8 * y + x; }

    static const LPair<int, int> directions[8];

    LVector<MyCircle> m_data;

    LSet<int> m_head;

    LSet<int> m_tail;

    LHash<int, LVector<int>> m_target;

    bool m_nowPlayer = true;

    bool m_isGameOver = false;
};


#endif
