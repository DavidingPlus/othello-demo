#ifndef _OTHELLOWINDOW_H_
#define _OTHELLOWINDOW_H_

#include "lcanvaswindow.h"


class OthelloWindow : public LCanvasWindow
{

public:

    OthelloWindow(int sideLen);


protected:

    void handleMousePressEvent(LMouseEvent *e) {}
};


#endif
