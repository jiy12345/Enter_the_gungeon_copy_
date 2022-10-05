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
    float curUserPosInViewX = I_Camera.m_rtCamera.vCenter()[0] + I_Window.m_rtClient.right / 2;
    float curUserPosInViewY = I_Camera.m_rtCamera.vCenter()[1] + I_Window.m_rtClient.bottom / 2;
    m_vDirection[0] = -(m_rtArea.vCenter()[0] - curUserPosInViewX);
    m_vDirection[1] = -(m_rtArea.vCenter()[1] - curUserPosInViewY);
    m_fAngle = static_cast<float>(atan2(-m_vDirection[1], m_vDirection[0]) * 180 / PI);

    JVector<2> vMoveDirection;
    if (-500.0f <= m_vDirection.length() && m_vDirection.length() <= 500.0f) {
        vMoveDirection[0] = rand() % 100 - 100;
        vMoveDirection[1] = rand() % 100 - 100;
    }
    else {
        vMoveDirection = m_vDirection;
    }
    vMoveDirection.normalize();
    m_vDirection.normalize();

    if (m_bIsMoving) {
        if (m_fCurLeftTime <= 0) {
            m_iCurLeftShots = rand() % 7;
            m_bIsMoving = false;
        }
        else {
            m_fCurLeftTime -= I_Timer.m_fElapseTimer;
        }
        setIdleSprite();
        setWalkSprite();
        m_rtArea.m_vLeftTop += vMoveDirection * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    else {
        m_fAttackTime -= I_Timer.m_fElapseTimer;

        if (m_fAttackTime <= 0) {
            if (m_iCurLeftShots <= 0) {
                m_fCurLeftTime = rand() % 7;
                m_bIsMoving = true;
            }
            else {
                m_iCurLeftShots--;
            }
            setIdleSprite();
            m_pGun->shot(m_vDirection);

            m_fAttackTime = rand() % MAX_ATTACK_TERM + MIN_ATTACK_TERM;
        }
    }

    gunFrame();

    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
    return true;
}

void JEnemy::setIdleSprite() {
    if (0 <= m_fAngle && m_fAngle <= 180) {
        m_curSprite = IDLE_UP_ENEMY;
    }
    else {
        m_curSprite = IDLE_DOWN_ENEMY;
    }
}

void JEnemy::setWalkSprite()
{
    if (m_vDirection.length() != 0) {
        m_curSprite += 2;
    }
    //switch (m_iDirection) {
    //case DOWN:
    //    m_curSprite = WALKING_DOWN;
    //    break;
    //case RIGHT: case DOWN_RIGHT:
    //    m_curSprite = WALKING_RIGHT;
    //    break;
    //case LEFT: case DOWN_LEFT:
    //    m_curSprite = WALKING_LEFT;
    //    break;
    //case UP:
    //    m_curSprite = WALKING_UP;
    //    break;
    //case RIGHT_UP:
    //    m_curSprite = WALKING_RIGHT_UP;
    //    break;
    //case LEFT_UP:
    //    m_curSprite = WALKING_LEFT_UP;
    //    break;
    //}
}