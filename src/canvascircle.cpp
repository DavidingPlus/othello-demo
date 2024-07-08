#include "canvascircle.h"


void MyCircle::paint(LDrawContext *dc)
{
    switch (m_state)
    {
        case PieceState::unActivated:
            break;
        case PieceState::Head:
        {
            dc->setBrushColor(LColor(0xff0000));
            dc->fillCircle(LCircle(m_roundCenterX, m_roundCenterY, m_roundRadius));

            break;
        }
        case PieceState::Tail:
        {
            dc->setBrushColor(LColor(0x0000ff));
            dc->fillCircle(LCircle(m_roundCenterX, m_roundCenterY, m_roundRadius));

            break;
        }
    }
}
