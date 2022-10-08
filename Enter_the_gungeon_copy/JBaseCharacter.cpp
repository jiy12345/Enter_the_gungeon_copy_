#include "JBaseCharacter.h"
#include "SpacePartition.h"


bool JBaseCharacter::init()
{
    m_bIsDynamic = true;
    m_iCurNodeNumber = I_SP2D.FindNode(0, m_rtArea);
    return true;
}

bool JBaseCharacter::frame()
{
    return false;
}

bool JBaseCharacter::render()
{
    JBaseObject::render();
    if (m_pGun) m_pGun->render();
    if (m_pHand) m_pHand->render();
    return true;
}

bool JBaseCharacter::release()
{
    if (m_pHand) {
        m_pHand->release();
        delete m_pHand;
        m_pHand = nullptr;
    }
    if (m_pGun) {
        m_pGun->release();
        delete m_pGun;
        m_pGun = nullptr;
    }

    return true;
}

void JBaseCharacter::gunFrame()
{
    m_pGun->m_rtArea.m_vLeftTop = m_rtArea.m_vLeftTop;

    if (-90 < m_fAngle && m_fAngle <= 90) {
        m_pGun->m_curSprite = GUN_RIGHT_IDLE;
        m_pGun->m_rtArea.m_vLeftTop[0] += m_rtArea.m_vSize[0] * 4 / 5;

        m_pGun->m_fRotateAngle = m_fAngle;
    }
    else {
        m_pGun->m_curSprite = GUN_LEFT_IDLE;
        m_pGun->m_rtArea.m_vLeftTop[0] -= m_rtArea.m_vSize[0] * 4 / 5;

        m_pGun->m_fRotateAngle = m_fAngle - 180;
    }
    m_pGun->m_rtArea.m_vLeftTop[1] += m_rtArea.m_vSize[1] * (2 / 5.0f);

    if (m_pHand) {
        m_pHand->m_rtArea.m_vLeftTop = m_pGun->m_rtArea.m_vLeftTop;

        m_pHand->m_rtArea.m_vLeftTop[1] += m_pGun->m_rtArea.m_vSize[1] * 1 / 2;

        if (-90 < m_fAngle && m_fAngle <= 90) {
        }
        else {
            m_pHand->m_rtArea.m_vLeftTop[0] += m_pGun->m_rtArea.m_vSize[0] * 3 / 4;
        }
    }

    m_pGun->frame();
}