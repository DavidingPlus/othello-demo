#include "messagewindow.h"

#include "othellowindow.h"

MessageWindow::MessageWindow(OthelloWindow *pOthelloWindow) : LWindow(450, 100)
{
    LWindow::setTitle("消息窗口");

    m_pOthelloWindow = pOthelloWindow;
}
