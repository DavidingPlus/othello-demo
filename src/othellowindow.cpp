#include "othellowindow.h"

#include "llog.h"
#include "lstring.h"
#include "lglyphicon.h"
#include "lfilesystementry.h"


const LPair<int, int> OthelloWindow::directions[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

const LColor OthelloWindow::m_headColor = LColor(0xff0000);

const LColor OthelloWindow::m_headReadyColor = LColor(0xF08080);

const LColor OthelloWindow::m_tailColor = LColor(0x0000ff);

const LColor OthelloWindow::m_tailReadyColor = LColor(0x87CEFA);

const LColor OthelloWindow::m_backgroundColor = LColor(0xffffff);


OthelloWindow::OthelloWindow(int sideLen) : LDrawWindow(200 + sideLen, sideLen)
{
    LDrawWindow::setTitle("黑白棋");

    m_sideLen = sideLen;

    m_headRect = LRect(m_sideLen, 0, 200, 80);
    m_tailRect = LRect(m_sideLen, 80, 200, 80);
    m_roundRect = LRect(m_sideLen, 160, 200, 80);
    m_logoRect = LRect(m_sideLen, 240, 200, 200);
    m_endMsgRect = LRect(m_sideLen, 440, 200, 200);

    LString logo = LFileSystemEntry(LFileSystemPath("res/logo.png")).absolutePath();
    m_logoPixmap = new LPixmap(logo);

    m_pGameOverWindow = new GameOverWindow(this);

    m_pAITimer = new LTimer(this);
    m_pAITimer->timeoutSignal.connect(this, &OthelloWindow::timeOutSlot);

    init();
}

void OthelloWindow::handleMousePressEvent(LMouseEvent *e)
{
    if (isAIMoving)
    {
        return;
    }

    if (Lark::Mouse_LeftButton == e->buttonCode())
    {
        // 如果处于游戏已结束的状态,那么只有点击m_endMsgRect才会响应
        if (m_isGameOver)
        {
            if (m_endMsgRect.contains(LPoint(e->x(), e->y())))
            {
                init();
            }
            else
            {
                return;
            }
        }

        // 限制鼠标的坐标必须在棋盘内
        if (e->x() >= m_sideLen || e->y() >= m_sideLen)
        {
            return;
        }

        int sectionLen = m_sideLen / 8;

        int xIndex = e->x() / sectionLen;
        int yIndex = e->y() / sectionLen;

        bool res = move(xIndex, yIndex);

        if (res)
        {
            scan();
            judgeSkip();
            AIMove();

            LDrawWindow::repaint();
        }
    }
}

void OthelloWindow::scan()
{
    // 清理之前的提示
    for (auto &e : m_target.keys())
    {
        m_pDrawContext->setBrushColor(m_backgroundColor);

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
                    m_pDrawContext->setPenColor(m_headReadyColor);
                }
                else
                {
                    m_pDrawContext->setPenColor(m_tailReadyColor);
                }
                m_pDrawContext->drawGlyphIcon(m_data[convertToIndex(x, y)].m_roundCenterX - LGlyphIcon::IconWidth / 2, m_data[convertToIndex(x, y)].m_roundCenterY - LGlyphIcon::IconHeight / 2, LGlyphIcon::IconName::Crosshair);

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
    drawSidebar();

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
    }

    int sectionLen = m_sideLen / 8;

    // 填充背景为白色
    m_pDrawContext->setBrushColor(m_backgroundColor);
    m_pDrawContext->fillRect(LRect(0, 0, LDrawWindow::width(), LDrawWindow::height()));

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
    for (int i = 1; i <= 8; ++i)
    {
        m_pDrawContext->drawLine(0, i * sectionLen, m_sideLen, i * sectionLen);
        m_pDrawContext->drawLine(i * sectionLen, 0, i * sectionLen, m_sideLen);
    }

    // 画 logo 。像素点 1 到像素点 200 刚好就是 200 个像素整
    m_pDrawContext->drawPixmap(1 + m_logoRect.x(), m_logoRect.y(), m_logoPixmap);

    // 画右边的消息提示区域
    drawSidebar();

    scan();

    if (m_isGameOver)
    {
        m_isGameOver = false;
        if (isAIMoving)
        {
            isAIMoving = false;
            m_pAITimer->stop();
        }

        LDrawWindow::repaint();
    }
}

void OthelloWindow::AIMove()
{
    if (m_nowPlayer)
    {
        return;
    }

    isAIMoving = true;

    if (m_pAITimer->isActive())
    {
        timeOutSlot();
    }
    else
    {
        m_pAITimer->startOnce(10);
    }
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
        judgeSkip();

        LDrawWindow::repaint();
    }
}

void OthelloWindow::gameEnd()
{
    m_isGameOver = true;

    LDrawWindow::repaint();

    m_pDrawContext->setPenColor(LColor(0x303030));
    if (m_head.size() == m_tail.size())
    {
        m_pDrawContext->drawText(m_endMsgRect, LString("平局!点此重新开始"), LFont(20), Lark::AlignCenter);
        // m_pGameOverWindow->m_textLabel->setText("平局，再大战 300 回合？");
    }
    else if (m_head.size() > m_tail.size())
    {
        m_pDrawContext->drawText(m_endMsgRect, LString("红胜!点此重新开始"), LFont(20), Lark::AlignCenter);
        // m_pGameOverWindow->m_textLabel->setText("恭喜您战胜电脑，可能是运气好？");
    }
    else
    {
        m_pDrawContext->drawText(m_endMsgRect, LString("蓝胜!点此重新开始"), LFont(20), Lark::AlignCenter);
        // m_pGameOverWindow->m_textLabel->setText("您连电脑都打不过，菜就多练！");
    }

    // m_pGameOverWindow->m_textLabel->setX((m_pGameOverWindow->width() - m_pGameOverWindow->m_textLabel->width()) / 2);

    // m_pGameOverWindow->show();
}

void OthelloWindow::judgeSkip()
{
    // m_target为空[无子可下]是当前玩家弃权的条件
    while (m_target.empty())
    {
        // 交换玩家
        m_nowPlayer ^= 1;
        drawSidebar();
        scan();
        // 如果另一方也无子可下，游戏结束
        if (m_target.empty())
        {
            gameEnd();
            return;
        }
        if (m_nowPlayer) // AI玩家弃权，人类玩家走棋
        {
            return; // 退出，由人类玩家通过点击鼠标继续走棋
        }
        else // 人类玩家弃权，AI玩家走棋
        {
            AIMove();
        }
    }
}

void OthelloWindow::drawSidebar()
{
    m_pDrawContext->setBrushColor(m_backgroundColor);
    // 加一个像素是防止把棋盘的线边缘覆盖掉，并且不重绘 logo 区域
    m_pDrawContext->fillRect(LRect(1 + m_sideLen, 0, 200, 240));
    m_pDrawContext->fillRect(LRect(1 + m_sideLen, 440, 200, 200));

    m_pDrawContext->setPenColor(m_headColor);
    m_pDrawContext->drawText(m_headRect, LString("您的棋子数: ") << LString::fromInt(m_head.size()), LFont(25), Lark::AlignCenter);

    m_pDrawContext->setPenColor(m_tailColor);
    m_pDrawContext->drawText(m_tailRect, LString("电脑棋子数: ") << LString::fromInt(m_tail.size()), LFont(25), Lark::AlignCenter);

    m_pDrawContext->setPenColor(m_nowPlayer ? m_headColor : m_tailColor);
    m_pDrawContext->drawText(m_roundRect, LString("当前是") << (m_nowPlayer ? LString("您的") : LString("电脑")) << LString("回合"), LFont(25), Lark::AlignCenter);
}
