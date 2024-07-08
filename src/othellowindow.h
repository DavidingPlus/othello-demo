#ifndef _OTHELLOWINDOW_H_
#define _OTHELLOWINDOW_H_

#include "ldrawwindow.h"
#include "lvector.h"
#include "canvascircle.h"
#include "lmouseevent.h"


class OthelloWindow : public LDrawWindow
{

public:

    OthelloWindow(int sideLen);


protected:

    void handleMousePressEvent(LMouseEvent *e) override;


private:

    LVector<CanvasCircle> m_data;
};


#endif
