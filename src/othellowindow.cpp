#include "othellowindow.h"

#include "messagewindow.h"

#include "llog.h"
#include "lstring.h"
#include "ltimer.h"

namespace
{
    bool isAIMoving = false;
} // namespace


const LPair<int, int> OthelloWindow::directions[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};


OthelloWindow::OthelloWindow(int sideLen, MessageWindow *pMessageWindow) : LDrawWindow(sideLen, sideLen)
{
    LDrawWindow::setTitle("黑白棋");

    m_pMessageWindow = pMessageWindow;

    m_pAITimer = new LTimer(this);
    m_pAITimer->timeoutSignal.connect(this, &OthelloWindow::timeOutSlot);
    init();
}

void OthelloWindow::handleMousePressEvent(LMouseEvent *e)
{
    LLog::log() << (isAIMoving ? "TRUE" : "FALSE");
    if (isAIMoving)
    {
        return;
    }
    if (Lark::Mouse_LeftButton == e->buttonCode())
    {
        if (m_isGameOver)
        {
            init();

            return;
        }

        int sectionLen = LDrawWindow::width() / 8;

        int xIndex = e->x() / sectionLen;
        int yIndex = e->y() / sectionLen;

        bool res = move(xIndex, yIndex);

        if (res)
        {
            scan();
            if (m_target.empty())
            {
                m_nowPlayer ^= 1;
                AIMove();
                scan();

                if (m_target.empty())
                {
                    m_isGameOver = true;

                    LLog::log() << ((m_head.size() > m_tail.size()) ? "RED WIN!" : "BLUE WIN!");

                    LDrawWindow::repaint();

                    return;
                }
            }

            LDrawWindow::repaint();
            AIMove();
        }
    }
}

void OthelloWindow::scan()
{
    // 清理之前的提示
    for (auto &e : m_target.keys())
    {
        m_pDrawContext->setBrushColor(LColor(0xffffff));

        if (MyCircle::PieceState::UnActivated == m_data[e].state())
        {
            m_pDrawContext->fillCircle(m_data[e]);
        }
    }

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
                if (m_nowPlayer)
                {
                    m_pDrawContext->setBrushColor(LColor(0xF08080));
                }
                else
                {
                    m_pDrawContext->setBrushColor(LColor(0x87CEFA));
                }
                m_pDrawContext->fillCircle(LCircle(m_data[convertToIndex(x, y)].m_roundCenterX, m_data[convertToIndex(x, y)].m_roundCenterY, m_data[convertToIndex(x, y)].m_roundRadius - 20));


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

bool OthelloWindow::move(int x, int y)
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

    m_pMessageWindow->m_HeadLabel->clear();
    m_pMessageWindow->m_TailLabel->clear();

    m_pMessageWindow->m_HeadLabel->setText(LString("红方棋子数: ") << LString::fromInt(m_head.size()));

    m_pMessageWindow->m_TailLabel->setText(LString("蓝方棋子数: ") << LString::fromInt(m_tail.size()));
    m_pMessageWindow->m_TailLabel->setX(m_pMessageWindow->width() - m_pMessageWindow->m_TailLabel->width());

    m_pMessageWindow->m_whoseRoundMiddleLabel->setColor(LPalette::ColorRole::GeneralText, m_nowPlayer ? LColor(0xff0000) : LColor(0x0000ff));
    m_pMessageWindow->m_whoseRoundMiddleLabel->setText(m_nowPlayer ? LString("红") : LString("蓝"));

    return true;
}

void OthelloWindow::init()
{
    if (m_isGameOver)
    {
        m_data.clear();
        m_head.clear();
        m_tail.clear();
        m_target.clear();
        m_nowPlayer = true;

        // 重置消息窗口
        m_pMessageWindow->m_HeadLabel->clear();
        m_pMessageWindow->m_TailLabel->clear();

        m_pMessageWindow->m_HeadLabel->setText(LString("红方棋子数: 2"));

        m_pMessageWindow->m_TailLabel->setText(LString("蓝方棋子数: 2"));
        m_pMessageWindow->m_TailLabel->setX(m_pMessageWindow->width() - m_pMessageWindow->m_TailLabel->width());

        m_pMessageWindow->m_whoseRoundMiddleLabel->setColor(LPalette::ColorRole::GeneralText, LColor(0xff0000));
        m_pMessageWindow->m_whoseRoundMiddleLabel->setText(LString("红"));
    }

    int sideLen = LDrawWindow::width();
    int sectionLen = sideLen / 8;

    // 填充背景为白色
    m_pDrawContext->setBrushColor(LColor(0xffffff));
    m_pDrawContext->fillRect(LRect(0, 0, sideLen, sideLen));

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

    if (m_isGameOver)
    {
        m_isGameOver = false;

        LDrawWindow::repaint();
    }
}

void OthelloWindow::AIMove()
{
    isAIMoving = true;
    m_pAITimer->startOnce(1000);
}

int OthelloWindow::AIStrategy()
{
    if (!m_target.empty())
    {
        return m_target.begin().key();
    }
    return -1;
}

void OthelloWindow::timeOutSlot()
{
    isAIMoving = false;
    int index = AIStrategy();
    if (index != -1)
    {
        move(index % 8, index / 8);
        scan();
        if (m_target.empty())
        {
            m_nowPlayer ^= 1;
            scan();

            if (m_target.empty())
            {
                m_isGameOver = true;

                LLog::log() << ((m_head.size() == m_tail.size()) ? "DRAW!" : ((m_head.size() > m_tail.size()) ? "RED WIN!" : "BLUE WIN!"));

                LDrawWindow::repaint();

                return;
            }
        }

        LDrawWindow::repaint();
    }
}