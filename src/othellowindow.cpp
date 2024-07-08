#include "othellowindow.h"


OthelloWindow::OthelloWindow(int sideLen) : LDrawWindow(sideLen, sideLen)
{
    int sectionLen = sideLen / 8;

    m_data.reserve(64);
    for (int i = 0; i < 64; ++i)
    {
        int xIndex = i % 8;
        int yIndex = i / 8;

        m_data.append(LCircle(xIndex * sectionLen + sectionLen / 2, yIndex * sectionLen + sectionLen / 2, sectionLen / 2));
    }

    m_pDrawContext->setBrushColor(LColor(0xffffff));
    m_pDrawContext->fillRect(LRect(0, 0, sideLen, sideLen));

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

        m_data[8 * yIndex + xIndex].onActivated();
        m_data[8 * yIndex + xIndex].paint(drawContext());

        repaint();
    }
}
