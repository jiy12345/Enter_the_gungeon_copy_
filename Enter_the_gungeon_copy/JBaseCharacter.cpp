#include "JBaseCharacter.h"

bool JBaseCharacter::frame()
{
    return false;
}

bool JBaseCharacter::render()
{
    JBaseObject::render();
    if (m_pGun) m_pGun->render();
    return true;
}

void JBaseCharacter::gunFrame()
{
    m_pGun->m_rtArea.m_vLeftTop = m_rtArea.m_vLeftTop;
    if (-90 < m_fAngle && m_fAngle <= 90) {
        m_pGun->m_curSprite = GUN_RIGHT_IDLE;
        m_pGun->m_rtArea.m_vLeftTop[0] += m_rtArea.m_vSize[0];

        m_pGun->m_fRotateAngle = m_fAngle;
    }
    else {
        m_pGun->m_curSprite = GUN_LEFT_IDLE;
        m_pGun->m_rtArea.m_vLeftTop[0] -= m_rtArea.m_vSize[0];

        m_pGun->m_fRotateAngle = m_fAngle - 180;
    }
    m_pGun->m_rtArea.m_vLeftTop[1] += m_rtArea.m_vSize[1] * (2 / 5.0f);


    m_pGun->frame();
}