#include "Tile.h"

bool Tile::init()
{
    JBaseObject::init();

    m_fRotateAngle = 0;
    m_rtArea.Set({ 0, 0 }, { 200, 200 });
    m_rtUV.Set({ 0, 0 }, { 1, 1 });
    m_wstrTextureName = L"../data/sprites/Tile12.jpg";

    return true;
}

Tile::Tile()
{
    init();
}
