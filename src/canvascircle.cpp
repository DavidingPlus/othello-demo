#include "canvascircle.h"


void CanvasCircle::paint(LDrawContext *dc)
{
    switch (m_mode)
    {
        case PieceMode::unActivated:
            break;
        case PieceMode::Head:
        {
            dc->setBrushColor(LColor(0xff0000));
            dc->fillCircle(m_circle);

            break;
        }
        case PieceMode::Tail:
        {
            dc->setBrushColor(LColor(0x0000ff));
            dc->fillCircle(m_circle);

            break;
        }
    }
}

void CanvasCircle::onActivated()
{
    switch (m_mode)
    {
        case PieceMode::unActivated:
            m_mode = PieceMode::Head;
            break;
        case PieceMode::Head:
            m_mode = PieceMode::Tail;
            break;
        case PieceMode::Tail:
            m_mode = PieceMode::Head;
            break;
    }
}
