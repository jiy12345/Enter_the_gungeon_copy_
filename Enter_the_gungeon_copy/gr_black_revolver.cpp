#include "gr_black_revolver.h"

bool gr_black_revolver::init()
{
    JGun::init();
    m_wstrTextureName = L"gr_black_revolver.png";
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/gr_black_revolver.txt");
    return true;
}
