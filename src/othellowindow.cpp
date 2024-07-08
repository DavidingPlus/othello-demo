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
        if (!OthelloMove(xIndex, yIndex))
        {
            std::cout << "Wrong Move at:" << yIndex * 8 + xIndex << "(" << xIndex << "," << yIndex << ")\n";
            return;
        }

        m_data[8 * yIndex + xIndex].setState(nowPlayer ? MyCircle::PieceState::Head : MyCircle::PieceState::Tail);
        m_data[8 * yIndex + xIndex].paint(m_pDrawContext);

        repaint();
    }
}

bool OthelloWindow::OthelloMove(int xIndex, int yIndex)
{
    bool rightflag = false;
    int x = xIndex, y = yIndex;
    if (nowPlayer == 0 && m_data[yIndex * 8 + xIndex].state() == MyCircle::UnActivated)
    {
        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[y * 8 + x + 1].state() == MyCircle::Head && x != xIndex)
            {
                while (x > xIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x].state() == MyCircle::Head && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[y * 8 + x - 1].state() == MyCircle::Head && x != xIndex)
            {
                while (x < xIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (y > 0)
        {
            y--;
        }
        while ((m_data[y * 8 + x].state() != MyCircle::Head) && (m_data[y * 8 + x].state() != MyCircle::UnActivated))
        {
            if (m_data[(y - 1) * 8 + x].state() == MyCircle::Head && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (y > 0)
            {
                y--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x + 1].state() == MyCircle::Head && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x - 1].state() == MyCircle::Head && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        if (y > 0)
        {
            y--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y - 1) * 8 + x + 1].state() == MyCircle::Head && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
            if (y > 0)
            {
                y--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        if (y > 0)
        {
            y--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Head && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y - 1) * 8 + x - 1].state() == MyCircle::Head && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Head);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
            if (y > 0)
            {
                y--;
            }
        }
    }
    else if (nowPlayer == 1 && m_data[yIndex * 8 + xIndex].state() == MyCircle::UnActivated)
    {
        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[y * 8 + x + 1].state() == MyCircle::Tail && x != xIndex)
            {
                while (x > xIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x].state() == MyCircle::Tail && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[y * 8 + x - 1].state() == MyCircle::Tail && x != xIndex)
            {
                while (x < xIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (y > 0)
        {
            y--;
        }
        while ((m_data[y * 8 + x].state() != MyCircle::Tail) && (m_data[y * 8 + x].state() != MyCircle::UnActivated))
        {
            if (m_data[(y - 1) * 8 + x].state() == MyCircle::Tail && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (y > 0)
            {
                y--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x + 1].state() == MyCircle::Tail && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        if (y < 7)
        {
            y++;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y + 1) * 8 + x - 1].state() == MyCircle::Tail && y != yIndex)
            {
                while (y > yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                    if (y > 0)
                    {
                        y--;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
            if (y < 7)
            {
                y++;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x < 7)
        {
            x++;
        }
        if (y > 0)
        {
            y--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y - 1) * 8 + x + 1].state() == MyCircle::Tail && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x > 0)
                    {
                        x--;
                    }
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x < 7)
            {
                x++;
            }
            if (y > 0)
            {
                y--;
            }
        }

        x = xIndex;
        y = yIndex;
        if (x > 0)
        {
            x--;
        }
        if (y > 0)
        {
            y--;
        }
        while (m_data[y * 8 + x].state() != MyCircle::Tail && m_data[y * 8 + x].state() != MyCircle::UnActivated)
        {
            if (m_data[(y - 1) * 8 + x - 1].state() == MyCircle::Tail && y != yIndex)
            {
                while (y < yIndex)
                {
                    m_data[y * 8 + x].setState(MyCircle::Tail);
                    m_data[y * 8 + x].paint(m_pDrawContext);
                    if (x < 7)
                    {
                        x++;
                    }
                    if (y < 7)
                    {
                        y++;
                    }
                }
                rightflag = true;
                break;
            }
            if (x > 0)
            {
                x--;
            }
            if (y > 0)
            {
                y--;
            }
        }
        if (rightflag != 1) rightflag = false;
    }
    else if (m_data[yIndex * 8 + xIndex].state() != MyCircle::UnActivated)
    {
        rightflag = false;
    }
    if (rightflag)
    {
        nowPlayer ^= 1;
    }
    return rightflag;
}