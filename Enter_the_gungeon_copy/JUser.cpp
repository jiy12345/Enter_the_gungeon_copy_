#include "JUser.h"
#include "gr_black_revolver.h"
#include "SpacePartition.h"
#include "ObjectManager.h"

bool JUser::init()
{
    JBaseObject::init();

    m_rtArea.Set({ 0, 0 }, { 28, 40 });
    m_wstrTextureName = L"../data/sprites/pilot.png";
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/pilot.txt");
    m_fSpeed = 300.0f;

    m_fHp = 10.0f;
    m_fMaxHp = 10.0f;

    m_pGun = new gr_black_revolver;
    m_pGun->init();

    m_pHand = new JBaseObject;
    m_pHand->init();
    m_pHand->m_wstrTextureName = L"../data/sprites/pilot.png";
    m_pHand->m_rtUV.Set({ 405 / 988.0f, 24 / 811.0f }, { 4 / 988.0f, 4 / 811.0f });
    m_pHand->m_rtArea.Set({ 0, 0 }, { 8, 8 });

    m_pGun->m_bIsUser = true;

    return true;
}

bool JUser::frame()
{
    if (m_bIsRoll == true) {
        if (m_iIndexOfSprite >= m_vSpriteInfo->at(m_curSprite).m_iNumFrame - 1) {
            m_bIsRoll = false;
        }

        m_rtArea.m_vLeftTop += m_vDirection * I_Timer.m_fElapseTimer * m_fSpeed;
        JBaseObject::frame();

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

    if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH) {
        JVector<2> curDirection{ curPosInViewX, -curPosInViewY };
        curDirection.normalize();
        m_pGun->shot(curDirection);
    }

    gunFrame();

    if (m_vDirection.length() != 0) m_vDirection.normalize();
    m_rtArea.m_vLeftTop += m_vDirection * I_Timer.m_fElapseTimer * m_fSpeed;
    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
    
    JBaseObject::frame();

    return true;
}

bool JUser::render()
{
    bool isEnd = JBaseObject::render();
    if (m_bIsDead) return isEnd;
    if (m_pGun && m_bIsRoll == false) m_pGun->render();
    if (m_pHand && m_bIsRoll == false) m_pHand->render();
    return true;
}

void JUser::setIdleSprite() {
    if (m_fAngle >= 150 || m_fAngle <= -120) {
        m_curSprite = IDLE_WEAPON_LEFT;
    }
    else if (120 < m_fAngle && m_fAngle <= 150) {
        m_curSprite = IDLE_WEAPON_LEFT_UP;
    }
    else if (90 < m_fAngle && m_fAngle <= 120) {
        m_curSprite = IDLE_WEAPON_UP_RIGHT;
    }
    else if (60 < m_fAngle && m_fAngle <= 90) {
        m_curSprite = IDLE_WEAPON_UP_LEFT;
    }
    else if (30 < m_fAngle && m_fAngle <= 60) {
        m_curSprite = IDLE_WEAPON_RIGHT_UP;
    }
    else if (-60 < m_fAngle && m_fAngle <= 60) {
        m_curSprite = IDLE_WEAPON_RIGHT;
    }
    else if (-120 < m_fAngle && m_fAngle <= -90) {
        m_curSprite = IDLE_WEAPON_DOWN_LEFT;
    }
    else if (-90 < m_fAngle && m_fAngle <= -60) {
        m_curSprite = IDLE_WEAPON_DOWN_RIGHT;
    }
}

void JUser::setWalkSprite()
{
    if (m_vDirection.length() != 0) {
        m_curSprite += 8;
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

bool JUser::checkCollision()
{
    if (m_bIsRoll == true) return true;

    std::vector<int> nodeToSearch = I_SP2D.FindCollisionSearchNode(0, m_rtArea);

    for (int curNode : nodeToSearch) {
        for (int curObjectNumber : I_SP2D.nodeList[curNode].m_dynamicObjectList) {
            if (I_ObjectManager.isUserBullet(curObjectNumber)) continue;

            JBaseObject* curObject = I_ObjectManager.getObject(curObjectNumber);

            if (curObject == nullptr) continue;

            if (JCollision<2>::CubeToCube(m_rtArea, curObject->m_rtArea) != CollisionType::C_OUT) {
                if(I_ObjectManager.isEnemyBullet(curObjectNumber)) curObject->setRecycle();
                m_fHp -= 1.0;

                if (m_fHp == 0) {
                    m_bIsDead = true;
                    m_curSprite = DEATH;
                    m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
                    break;
                }
            }
            curObject = nullptr;
        }
    }

    return true;
}
