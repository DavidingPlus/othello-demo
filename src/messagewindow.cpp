#include "messagewindow.h"

#include "othellowindow.h"

#include "lstring.h"
#include "lfont.h"
#include "lpalette.h"
#include "lcolor.h"


MessageWindow::MessageWindow() : LWindow(450, 100)
{
    LWindow::setTitle("消息窗口");

    m_HeadLabel = new LLabel(LString("您的棋子数: 2"), LWindow::rootComponent());
    m_HeadLabel->setColor(LPalette::ColorRole::GeneralText, LColor(0xff0000));
    m_HeadLabel->setFont(LFont(25));

    m_TailLabel = new LLabel(LString("电脑棋子数: 2"), LWindow::rootComponent());
    m_TailLabel->setColor(LPalette::ColorRole::GeneralText, LColor(0x0000ff));
    m_TailLabel->setFont(LFont(25));
    m_TailLabel->setX(LWindow::width() - m_TailLabel->width());

    m_whoseRoundLeftLabel = new LLabel(LString("当前是"), LWindow::rootComponent());
    m_whoseRoundLeftLabel->setFont(LFont(25));
    m_whoseRoundLeftLabel->setY(LWindow::height() - m_whoseRoundLeftLabel->height());

    m_whoseRoundMiddleLabel = new LLabel(LString("您的"), LWindow::rootComponent());
    m_whoseRoundMiddleLabel->setColor(LPalette::ColorRole::GeneralText, LColor(0xff0000));
    m_whoseRoundMiddleLabel->setFont(LFont(25));
    m_whoseRoundMiddleLabel->setY(LWindow::height() - m_whoseRoundMiddleLabel->height());

    m_whoseRoundRightLabel = new LLabel(LString("回合"), LWindow::rootComponent());
    m_whoseRoundRightLabel->setFont(LFont(25));
    m_whoseRoundRightLabel->setY(LWindow::height() - m_whoseRoundRightLabel->height());

    int widthSum = m_whoseRoundLeftLabel->width() + m_whoseRoundMiddleLabel->width() + m_whoseRoundRightLabel->width();
    m_whoseRoundLeftLabel->setX((LWindow::width() - widthSum) / 2);
    m_whoseRoundMiddleLabel->setX(m_whoseRoundLeftLabel->x() + m_whoseRoundLeftLabel->width());
    m_whoseRoundRightLabel->setX(m_whoseRoundMiddleLabel->x() + m_whoseRoundMiddleLabel->width());
}
