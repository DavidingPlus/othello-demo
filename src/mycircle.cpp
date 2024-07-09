#include "mycircle.h"


void MyCircle::paint(LDrawContext *dc)
{
    switch (m_state)
    {
        case PieceState::UnActivated:
        {
            dc->setBrushColor(LColor(0xffffff));
            dc->fillCircle(LCircle(m_roundCenterX, m_roundCenterY, m_roundRadius));

            break;
        }
        case PieceState::ReadyToActivate:
        {
            dc->setBrushColor(LColor(0xffff00));
            dc->fillCircle(LCircle(m_roundCenterX, m_roundCenterY, m_roundRadius - 20));

            break;
        }
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
