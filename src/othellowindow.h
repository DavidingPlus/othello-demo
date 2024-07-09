#ifndef _OTHELLOWINDOW_H_
#define _OTHELLOWINDOW_H_

#include "ldrawwindow.h"
#include "lvector.h"
#include "lmouseevent.h"
#include "lpair.h"
#include "lset.h"

#include "mycircle.h"


class OthelloWindow : public LDrawWindow
{

public:

    OthelloWindow(int sideLen);


protected:

    void handleMousePressEvent(LMouseEvent *e) override;


private:

    void scan();

    static LPair<int, int> convertToPair(int index) { return LPair<int, int>(index % 8, index / 8); }

    static int convertToIndex(int x, int y) { return 8 * y + x; }

    static const LPair<int, int> directions[8];

    LVector<MyCircle> m_data;

    LSet<int> m_head;

    LSet<int> m_tail;

    LVector<LPair<int, int>> m_target;

    bool m_nowPlayer = true;
};


#endif
