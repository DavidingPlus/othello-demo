#include "lwindowapplication.h"

#include "othellowindow.h"
#include "messagewindow.h"


int main()
{
    LWindowApplication app;

    OthelloWindow ow(640);
    MessageWindow mw(&ow);

    ow.show();

    mw.setPosition(ow.x() + ow.width() + 100, ow.y());
    mw.show();

    return app.exec();
}
