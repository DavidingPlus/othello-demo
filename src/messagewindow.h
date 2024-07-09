#ifndef _MESSAGEWINDOW_H_
#define _MESSAGEWINDOW_H_

#include "lwindow.h"
#include "levent.h"
#include "llabel.h"


class OthelloWindow;


class MessageWindow : public LWindow
{

    friend class OthelloWindow;


public:

    MessageWindow();


protected:

    void handleCloseEvent(LEvent *e) override { exit(0); }


private:

    LLabel *m_HeadLabel = nullptr;

    LLabel *m_TailLabel = nullptr;

    LLabel *m_whoseRoundLeftLabel = nullptr;

    LLabel *m_whoseRoundMiddleLabel = nullptr;

    LLabel *m_whoseRoundRightLabel = nullptr;
};


#endif
