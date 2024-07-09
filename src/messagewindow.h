#ifndef _MESSAGEWINDOW_H_
#define _MESSAGEWINDOW_H_

#include "lwindow.h"
#include "levent.h"


class OthelloWindow;


class MessageWindow : public LWindow
{

public:

    MessageWindow(OthelloWindow *pOthelloWindow);


protected:

    void handleCloseEvent(LEvent *e) override { exit(0); }


private:

    OthelloWindow *m_pOthelloWindow = nullptr;
};


#endif
