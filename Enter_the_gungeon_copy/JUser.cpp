#include "JUser.h"
#include "gr_black_revolver.h"

bool JUser::init()
{
    JBaseObject::init();
    m_rtArea.Set({ 0, 0 }, { 25, 40 });
    m_wstrTextureName = L"../data/sprites/pilot.png";
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/pilot.txt");
    m_fSpeed = 300.0f;

    m_pGun = new gr_black_revolver;
    m_pGun->init();
    return false;
}

bool JUser::frame()
{
    m_pGun->m_rtArea.Set(m_rtArea.m_vLeftTop + JVector<2>(3, 0), { 10, 10 });
    if (m_bIsRoll == true) {
        if (m_iIndexOfSprite >= m_vSpriteInfo->at(m_curSprite).m_iNumFrame - 1) {
            m_bIsRoll = false;
        }

        m_rtArea.m_vLeftTop += m_vDirection * I_Timer.m_fElapseTimer * m_fSpeed;
        return true;
    }
    float curPosInViewY = -(I_Input.m_ptPos.y - I_Window.m_rtClient.bottom / 2);
    float curPosInViewX = I_Input.m_ptPos.x - I_Window.m_rtClient.right / 2;
    m_fAngle = static_cast<float>(atan2(curPosInViewY, curPosInViewX) * 180 / PI);
    setIdleSprite();

    m_iDirection = NO_DIRECTION;
    m_vDirection = { 0, 0 };
    if (I_Input.GetKey('W'))
    {
        m_iDirection |= UP;
        m_vDirection[1] += -1;
    }
    if (I_Input.GetKey('S'))
    {
        m_iDirection |= DOWN;
        m_vDirection[1] += +1;
    }
    if (I_Input.GetKey('A'))
    {
        m_iDirection |= LEFT;
        m_vDirection[0] += -1;
    }
    if (I_Input.GetKey('D'))
    {
        m_iDirection |= RIGHT;
        m_vDirection[0] += +1;
    }
    setWalkSprite();

    if (I_Input.GetKey(VK_RBUTTON) == KEY_PUSH && m_vDirection.length() != 0) {
        m_bIsRoll = true;
        setRollSprite();
    }

    if (m_vDirection.length() != 0) m_vDirection.normalize();
    m_rtArea.m_vLeftTop += m_vDirection * I_Timer.m_fElapseTimer * m_fSpeed;
    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
    return true;
}

void JUser::setIdleSprite() {
    if (m_fAngle >= 150 || m_fAngle <= -120) {
        m_curSprite = IDLE_LEFT;
    }
    else if (120 < m_fAngle && m_fAngle <= 150) {
        m_curSprite = IDLE_LEFT_UP;
    }
    else if (60 < m_fAngle && m_fAngle <= 120) {
        m_curSprite = IDLE_UP;
    }
    else if (30 < m_fAngle && m_fAngle <= 60) {
        m_curSprite = IDLE_RIGHT_UP;
    }
    else if (-60 < m_fAngle && m_fAngle <= 60) {
        m_curSprite = IDLE_RIGHT;
    }
    else if (-120 < m_fAngle && m_fAngle <= -60) {
        m_curSprite = IDLE_DOWN;
    }
    
}

void JUser::setWalkSprite()
{
    switch (m_iDirection) {
    case DOWN:
        m_curSprite = WALKING_DOWN;
        break;
    case RIGHT: case DOWN_RIGHT:
        m_curSprite = WALKING_RIGHT;
        break;
    case LEFT: case DOWN_LEFT:
        m_curSprite = WALKING_LEFT;
        break;
    case UP:
        m_curSprite = WALKING_UP;
        break;
    case RIGHT_UP:
        m_curSprite = WALKING_RIGHT_UP;
        break;
    case LEFT_UP:
        m_curSprite = WALKING_LEFT_UP;
        break;
    }
}

void JUser::setRollSprite()
{
    switch (m_iDirection) {
    case DOWN:
        m_curSprite = ROLLING_DOWN;
        break;
    case RIGHT: case DOWN_RIGHT:
        m_curSprite = ROLLING_RIGHT;
        break;
    case LEFT: case DOWN_LEFT:
        m_curSprite = ROLLING_LEFT;
        break;
    case UP:
        m_curSprite = ROLLING_UP;
        break;
    case RIGHT_UP:
        m_curSprite = ROLLING_RIGHT_UP;
        break;
    case LEFT_UP:
        m_curSprite = ROLLING_LEFT_UP;
        break;
    }
}
