#include "lwindowapplication.h"
#include "lcanvaswindow.h"


class OthelloWindow : public LCanvasWindow
{

public:

    OthelloWindow(int sideLen) : LCanvasWindow(sideLen, sideLen, 8)
    {
        m_pDrawContext->setBrushColor(LColor(0xffffff));
        m_pDrawContext->fillRect(LRect(0, 0, sideLen, sideLen));
        int sectionLen = sideLen / 8;
        for (int i = 1; i < 8; ++i)
        {
            m_pDrawContext->drawLine(0, i * sectionLen, sideLen, i * sectionLen);
            m_pDrawContext->drawLine(i * sectionLen, 0, i * sectionLen, sideLen);
        }
    }


protected:

    void handleMousePressEvent(LMouseEvent *e) {}
};


int main()
{
    LWindowApplication app;
    OthelloWindow w(640);
    w.show();
    return app.exec();
}
