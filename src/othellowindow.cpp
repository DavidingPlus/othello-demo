#include "othellowindow.h"


OthelloWindow::OthelloWindow(int sideLen) : LDrawWindow(sideLen, sideLen)
{
    // 填充背景为白色
    m_pDrawContext->setBrushColor(LColor(0xffffff));
    m_pDrawContext->fillRect(LRect(0, 0, sideLen, sideLen));

    int sectionLen = sideLen / 8;

    // 初始化所有棋子的数据
    m_data.reserve(64);
    for (int i = 0; i < 64; ++i)
    {
        int xIndex = i % 8;
        int yIndex = i / 8;

        m_data.append(MyCircle(xIndex * sectionLen + sectionLen / 2, yIndex * sectionLen + sectionLen / 2, sectionLen / 2 - 10));
    }

    m_data[27].setState(MyCircle::PieceState::Tail);
    m_data[27].paint(m_pDrawContext);

    m_data[28].setState(MyCircle::PieceState::Head);
    m_data[28].paint(m_pDrawContext);

    m_data[35].setState(MyCircle::PieceState::Head);
    m_data[35].paint(m_pDrawContext);

    m_data[36].setState(MyCircle::PieceState::Tail);
    m_data[36].paint(m_pDrawContext);

    // 画棋盘的分割线
    m_pDrawContext->setPenColor(LColor(0x000000));
    for (int i = 1; i < 8; ++i)
    {
        m_pDrawContext->drawLine(0, i * sectionLen, sideLen, i * sectionLen);
        m_pDrawContext->drawLine(i * sectionLen, 0, i * sectionLen, sideLen);
    }
}

void OthelloWindow::handleMousePressEvent(LMouseEvent *e)
{
    if (Lark::Mouse_LeftButton == e->buttonCode())
    {
        int sectionLen = width() / 8;

        int xIndex = e->x() / sectionLen;
        int yIndex = e->y() / sectionLen;

        m_data[8 * yIndex + xIndex].setState(m_data[8 * yIndex + xIndex].state() == MyCircle::PieceState::Head ? MyCircle::PieceState::Tail : MyCircle::PieceState::Head);
        m_data[8 * yIndex + xIndex].paint(m_pDrawContext);

        repaint();
    }
}
