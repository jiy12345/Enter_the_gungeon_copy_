#include "ObjectManager.h"

Bullet* ObjectManager::GetRecycledEnemyBullet()
{
    Bullet* poolObj = nullptr;

    if (enemyBulletList.size() == 0)
    {
        poolObj = new Bullet();
        poolObj->init();
        poolObj->m_iSerialNumber = enemyBulletList.size();
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
        poolObj->m_iSerialNumber = enemyBulletList.size();
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
        poolObj->m_iSerialNumber = userBulletList.size();
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
        poolObj->m_iSerialNumber = userBulletList.size();
        userBulletList.push_back(poolObj);
        return poolObj;
    }

    poolObj->onRecycle();

    return poolObj;
}
JEnemy* ObjectManager::getEnemy(int iEnemySerialNum)
{
    if (iEnemySerialNum >= getNumOfEnemy() || 
        enemyList[iEnemySerialNum]->CanRecylcable == true) 
        return nullptr;
    return enemyList[iEnemySerialNum];
}

Bullet* ObjectManager::getEnemyBullet(int iEnemyBulletSerialNum)
{
    if (iEnemyBulletSerialNum >= getNumOfEnemyBullet() ||
        enemyBulletList[iEnemyBulletSerialNum]->CanRecylcable == true)
        return nullptr;
    return enemyBulletList[iEnemyBulletSerialNum];
}

Bullet* ObjectManager::getUserBullet(int iUserBulletSerialNum)
{
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
