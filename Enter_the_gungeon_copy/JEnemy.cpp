#include "JEnemy.h"

bool JEnemy::init()
{
    JBaseObject::init();

    m_pGun = new gr_black_revolver;
    m_pGun->init();
    m_pGun->m_bIsUser = false;

    return true;
}

bool JEnemy::frame()
{
    float curUserPosInViewY = -(m_rtArea.vCenter()[1] - I_Window.m_rtClient.bottom / 2);
    float curUserPosInViewX = m_rtArea.vCenter()[0] - I_Window.m_rtClient.right / 2;
    float curPositionX = I_Camera.m_rtCamera.vCenter()[0];
    float curPositionY = I_Camera.m_rtCamera.vCenter()[1];
    m_fAngle = static_cast<float>(atan2(-m_rtArea.vCenter()[1] - curPositionY, m_rtArea.vCenter()[0] - curPositionX) * 180 / PI);
    
    std::cout << curPositionX << " " << curPositionY <<'\n';
    std::cout << m_fAngle << '\n';
    gunFrame();

    if (m_vDirection.length() != 0) m_vDirection.normalize();
    m_rtArea.m_vLeftTop += m_vDirection * I_Timer.m_fElapseTimer * m_fSpeed;
    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
    return true;
}
