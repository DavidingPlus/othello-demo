#include "lwindowapplication.h"

#include "othellowindow.h"
#include "messagewindow.h"


int main()
{
    LWindowApplication app;

    MessageWindow mw;
    OthelloWindow ow(640, &mw);

    ow.show();

    mw.setPosition(ow.x() + ow.width() + 100, ow.y());
    mw.show();

    return app.exec();
}
