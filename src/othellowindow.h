#ifndef _OTHELLOWINDOW_H_
#define _OTHELLOWINDOW_H_

#include "ldrawwindow.h"
#include "lvector.h"
#include "lmouseevent.h"
#include "lpair.h"
#include "lset.h"
#include "lhash.h"
#include "ltimer.h"
#include "lrect.h"
#include "lcolor.h"
#include "lpixmap.h"

#include "mycircle.h"
#include "gameoverwindow.h"


class GameOverWindow;


class OthelloWindow : public LDrawWindow
{

    friend class GameOverWindow;


public:

    OthelloWindow(int sideLen);


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

    /**
     * @brief 判断玩家是否应当弃权，若是则相应执行
     */
    void judgeSkip();

    void gameEnd();

    /**
     * @brief 画侧边栏信息
     */
    void drawSidebar();

    static LPair<int, int> convertToPair(int index) { return LPair<int, int>(index % 8, index / 8); }

    static int convertToIndex(int x, int y) { return 8 * y + x; }

    static const LPair<int, int> directions[8];

    static const LColor m_headColor;

    // 当前红旗可以下的位置的颜色
    static const LColor m_headReadyColor;

    static const LColor m_tailColor;

    static const LColor m_tailReadyColor;

    static const LColor m_backgroundColor;

    int m_sideLen = 0;

    GameOverWindow *m_pGameOverWindow = nullptr;

    LVector<MyCircle> m_data;

    LSet<int> m_head;

    LSet<int> m_tail;

    LHash<int, LVector<int>> m_target;

    bool m_nowPlayer = true;

    bool m_isGameOver = false;

    LTimer *m_pAITimer = nullptr;

    bool isAIMoving = false;

    LRect m_headRect;

    LRect m_tailRect;

    LRect m_roundRect;

    LRect m_logoRect;

    LPixmap *m_logoPixmap = nullptr;

    LRect m_endMsgRect;
};


#endif
