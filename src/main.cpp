#include "lwindowapplication.h"

#include "othellowindow.h"


int main()
{
    LWindowApplication app;
    OthelloWindow ow(640);
    ow.show();
    return app.exec();
}
