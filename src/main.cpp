#include "lwindowapplication.h"
#include "othellowindow.h"


int main()
{
    LWindowApplication app;
    OthelloWindow w(640);
    w.show();
    return app.exec();
}
