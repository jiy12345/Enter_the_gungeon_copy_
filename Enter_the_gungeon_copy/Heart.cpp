#include "Heart.h"

bool Heart::init()
{
    JBaseObject::init();

    m_fRotateAngle = 0;
    m_rtArea.Set({ 0, 0 }, { 35, 35 });
    m_wstrTextureName = L"../data/sprites/heart.png";
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/heart.txt");

    return true;
}

void Heart::setHeart(SPRITE_HEART iSpriteHeart)
{
    m_curSprite = iSpriteHeart;
}

Heart::Heart()
{
    init();
}
