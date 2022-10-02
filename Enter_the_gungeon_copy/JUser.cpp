#include "JUser.h"

bool JUser::init()
{
    JBaseObject::init();
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/pilot.txt");
    return false;
}

bool JUser::frame()
{
    float curPosInViewY = -(I_Input.m_ptPos.y - I_Window.m_rtClient.bottom / 2);
    float curPosInViewX = I_Input.m_ptPos.x - I_Window.m_rtClient.right / 2;
    float angle = static_cast<float>(atan2(curPosInViewY, curPosInViewX) * 180 / PI);
    setCurSprite(angle);

    JVector<2> vPos = m_rtArea.m_vLeftTop;
    if (I_Input.GetKey('W'))
    {
        vPos[1] += -1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        vPos[1] += +1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        vPos[0] += -1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        vPos[0] += +1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    m_rtArea.m_vLeftTop = vPos;

    return true;
}

void JUser::setCurSprite(float angle) {
    if (angle >= 150 || angle <= -120) {
        m_curSprite = IDLE_LEFT;
    }
    else if (120 < angle && angle <= 150) {
        m_curSprite = IDLE_LEFT_UP;
    }
    else if (60 < angle && angle <= 120) {
        m_curSprite = IDLE_UP;
    }
    else if (30 < angle && angle <= 60) {
        m_curSprite = IDLE_RIGHT_UP;
    }
    else if (-60 < angle && angle <= 60) {
        m_curSprite = IDLE_RIGHT;
    }
    else if (-120 < angle && angle <= -60) {
        m_curSprite = IDLE_DOWN;
    }
    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
}