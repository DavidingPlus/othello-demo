#ifndef _GAMEOVERWINDOW_H_
#define _GAMEOVERWINDOW_H_


#include "lwindow.h"
#include "llabel.h"
#include "lbutton.h"
#include "levent.h"


class OthelloWindow;


class GameOverWindow : public LWindow
{

    friend class OthelloWindow;


public:

    GameOverWindow(OthelloWindow *pOthelloWindow);


protected:

    void handleCloseEvent(LEvent *e) override { exit(0); }


private:

    LLabel *m_textLabel = nullptr;

    LButton *m_reStartBtn = nullptr;

    LButton *m_exitBtn = nullptr;

    OthelloWindow *m_pOthelloWindow = nullptr;
};


#endif
