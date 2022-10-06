#include "ObjectManager.h"

Bullet* ObjectManager::GetRecycledEnemyBullet()
{
    Bullet* poolObj = nullptr;

    if (enemyBulletList.size() == 0)
    {
        poolObj = new Bullet();
        poolObj->init();
        poolObj->m_iSerialNumber = MIN_ENEMY_BULLET_SERIAL_NUM + enemyBulletList.size();
        enemyBulletList.push_back(poolObj);
        return poolObj;
    }

    for (auto elem : enemyBulletList)
    {
        if (elem->CanRecylcable)
        {
            poolObj = elem;
            break;
        }
    }

    if (poolObj == nullptr)
    {
        poolObj = new Bullet();
        poolObj->init();
        poolObj->m_iSerialNumber = MIN_ENEMY_BULLET_SERIAL_NUM + enemyBulletList.size();
        enemyBulletList.push_back(poolObj);
        return poolObj;
    }

    poolObj->onRecycle();

    return poolObj;
}

Bullet* ObjectManager::GetRecycledUserBullet()
{
    Bullet* poolObj = nullptr;

    if (userBulletList.size() == 0)
    {
        poolObj = new Bullet();
        poolObj->m_iSerialNumber = MIN_USER_BULLET_SERIAL_NUM + userBulletList.size();
        userBulletList.push_back(poolObj);
        return poolObj;
    }

    for (auto elem : userBulletList)
    {
        if (elem->CanRecylcable)
        {
            poolObj = elem;
            break;
        }
    }

    if (poolObj == nullptr)
    {
        poolObj = new Bullet();
        poolObj->init();
        poolObj->m_iSerialNumber = MIN_USER_BULLET_SERIAL_NUM + userBulletList.size();
        userBulletList.push_back(poolObj);
        return poolObj;
    }

    poolObj->onRecycle();

    return poolObj;
}
JBaseObject* ObjectManager::getObject(int iSerialNum)
{
    if (isEnemy(iSerialNum)) return getEnemy(iSerialNum);
    if (isEnemyBullet(iSerialNum)) return getEnemyBullet(iSerialNum);
    if (isUserBullet(iSerialNum)) return getUserBullet(iSerialNum);
}
JEnemy* ObjectManager::getEnemy(int iEnemySerialNum)
{
    iEnemySerialNum -= MIN_ENEMY_SERIAL_NUM;
    if (iEnemySerialNum >= getNumOfEnemy() || 
        enemyList[iEnemySerialNum]->CanRecylcable == true) 
        return nullptr;
    return enemyList[iEnemySerialNum];
}

Bullet* ObjectManager::getEnemyBullet(int iEnemyBulletSerialNum)
{
    iEnemyBulletSerialNum -= MIN_ENEMY_BULLET_SERIAL_NUM;
    if (iEnemyBulletSerialNum >= getNumOfEnemyBullet() ||
        enemyBulletList[iEnemyBulletSerialNum]->CanRecylcable == true)
        return nullptr;
    return enemyBulletList[iEnemyBulletSerialNum];
}

Bullet* ObjectManager::getUserBullet(int iUserBulletSerialNum)
{
    iUserBulletSerialNum -= MIN_USER_BULLET_SERIAL_NUM;
    if (iUserBulletSerialNum >= getNumOfUserBullet() ||
        userBulletList[iUserBulletSerialNum]->CanRecylcable == true)
        return nullptr;
    return userBulletList[iUserBulletSerialNum];
}

bool ObjectManager::release()
{
    for (auto Object : enemyList) {
        delete(Object);
    }
    enemyList.clear();
    for (auto Object : enemyBulletList) {
        delete(Object);
    }
    for (auto Object : userBulletList) {
        delete(Object);
    }

    enemyList.clear();

    return true;
}

bool ObjectManager::isEnemy(int iEnemySerialNum)
{
    return MIN_ENEMY_SERIAL_NUM <= iEnemySerialNum && iEnemySerialNum <= MAX_ENEMY_SERIAL_NUM;
}

bool ObjectManager::isEnemyBullet(int iEnemyBulletSerialNum)
{
    return MIN_ENEMY_BULLET_SERIAL_NUM <= iEnemyBulletSerialNum && iEnemyBulletSerialNum <= MAX_ENEMY_BULLET_SERIAL_NUM;
}

bool ObjectManager::isUserBullet(int iUserBulletSerialNum)
{
    return MIN_USER_BULLET_SERIAL_NUM <= iUserBulletSerialNum && iUserBulletSerialNum <= MAX_USER_BULLET_SERIAL_NUM;
}
