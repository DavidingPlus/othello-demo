#include "othellowindow.h"


const LPair<int, int> OthelloWindow::directions[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};


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
        auto pos = convertToPair(i);

        m_data.append(MyCircle(pos.first() * sectionLen + sectionLen / 2, pos.second() * sectionLen + sectionLen / 2, sectionLen / 2 - 10));
    }

    m_data[27].setState(MyCircle::PieceState::Tail);
    m_data[27].paint(m_pDrawContext);
    m_tail.insert(27);

    m_data[28].setState(MyCircle::PieceState::Head);
    m_data[28].paint(m_pDrawContext);
    m_head.insert(28);

    m_data[35].setState(MyCircle::PieceState::Head);
    m_data[35].paint(m_pDrawContext);
    m_head.insert(35);

    m_data[36].setState(MyCircle::PieceState::Tail);
    m_data[36].paint(m_pDrawContext);
    m_tail.insert(36);

    // 画棋盘的分割线
    m_pDrawContext->setPenColor(LColor(0x000000));
    for (int i = 1; i < 8; ++i)
    {
        m_pDrawContext->drawLine(0, i * sectionLen, sideLen, i * sectionLen);
        m_pDrawContext->drawLine(i * sectionLen, 0, i * sectionLen, sideLen);
    }

    scan();

    std::cout << "now is red's turn" << std::endl;
}

void OthelloWindow::handleMousePressEvent(LMouseEvent *e)
{
    if (Lark::Mouse_LeftButton == e->buttonCode())
    {
        int sectionLen = width() / 8;

        int xIndex = e->x() / sectionLen;
        int yIndex = e->y() / sectionLen;

        bool res = OthelloMove(xIndex, yIndex);

        if (res)
        {
            std::cout << (m_nowPlayer ? "now is red's turn" : "now is blue's turn") << std::endl;

            scan();

            repaint();
        }
    }
}

void OthelloWindow::scan()
{
    m_target.clear();

    auto &player = m_nowPlayer ? m_head : m_tail;

    for (auto &e : player)
    {
        auto p = convertToPair(e);

        for (auto &direction : directions)
        {
            int x = p.first();
            int y = p.second();

            int step = 0; // 存储走的步数

            do
            {
                x += direction.first();
                y += direction.second();

                ++step;

            } while (x >= 0 && x < 8 && y >= 0 && y < 8 && (m_nowPlayer ? MyCircle::PieceState::Tail : MyCircle::PieceState::Head) == m_data[convertToIndex(x, y)].state());

            // 要想正确吃到棋子，至少要走两步，保证中间至少有一颗对方的棋
            if (step > 1 && x >= 0 && x < 8 && y >= 0 && y < 8 && MyCircle::PieceState::UnActivated == m_data[convertToIndex(x, y)].state())
            {
                if (m_target.contains(convertToIndex(x, y)))
                {
                    m_target[convertToIndex(x, y)].append(e);
                }
                else
                {
                    m_target.insert(convertToIndex(x, y), LVector<int>({e}));
                }
            }
        }
    }
}

bool OthelloWindow::OthelloMove(int x, int y)
{
    int index = convertToIndex(x, y);

    if (!m_target.contains(index))
    {
        return false;
    }

    LVector<int> sources = m_target[index];

    for (int i = 0; i < sources.size(); i++)
    {
        LPair<int, int> sourcePos = convertToPair(sources[i]);

        int directionX = (x - sourcePos.first() > 0 ? 1 : (x - sourcePos.first() < 0 ? -1 : 0));
        int directionY = (y - sourcePos.second() > 0 ? 1 : (y - sourcePos.second() < 0 ? -1 : 0));

        int nowX = sourcePos.first();
        int nowY = sourcePos.second();
        int nowIndex = convertToIndex(nowX, nowY);

        do
        {
            nowX += directionX;
            nowY += directionY;
            nowIndex = convertToIndex(nowX, nowY);

            m_data[nowIndex].setState((m_nowPlayer ? MyCircle::PieceState::Head : MyCircle::PieceState::Tail));
            m_data[nowIndex].paint(m_pDrawContext);

            if (m_nowPlayer)
            {
                m_head.insert(nowIndex);
                m_tail.remove(nowIndex);
            }
            else
            {
                m_tail.insert(nowIndex);
                m_head.remove(nowIndex);
            }
        } while (nowIndex != index);
    }

    m_nowPlayer ^= 1;

    return true;
}
