#include "gameoverwindow.h"

#include "othellowindow.h"

#include "lstring.h"
#include "lfont.h"


GameOverWindow::GameOverWindow(OthelloWindow *pOthelloWindow) : LWindow(450, 100)
{
    LWindow::setTitle("游戏结束");

    m_pOthelloWindow = pOthelloWindow;

    LWindow::setPosition(m_pOthelloWindow->x() + m_pOthelloWindow->width() + 100, m_pOthelloWindow->y() + 200);

    m_textLabel = new LLabel(LString("连电脑都打不过，菜就多练"), LWindow::rootComponent());
    m_textLabel->setFont(LFont(25));
    m_textLabel->setX((LWindow::width() - m_textLabel->width()) / 2);

    m_reStartBtn = new LButton(LString("再来一把"), LWindow::rootComponent());
    m_reStartBtn->setY(LWindow::height() - m_reStartBtn->height());
    m_reStartBtn->clickSignal.connect(
        [&]()
        {
            m_pOthelloWindow->init();

            LWindow::hide();
        });

    m_exitBtn = new LButton(LString("遗憾退场"), LWindow::rootComponent());
    m_exitBtn->setY(LWindow::height() - m_exitBtn->height());
    m_exitBtn->setX(LWindow::width() - m_exitBtn->width());
    m_exitBtn->clickSignal.connect(
        []()
        {
            exit(0);
        });
}
