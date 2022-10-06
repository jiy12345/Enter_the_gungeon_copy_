#pragma once
#include "stdafx.h"
#include "JEnemy.h"
#include "JUser.h"
#include "Bullet.h"

#define MIN_ENEMY_SERIAL_NUM 0
#define MAX_ENEMY_SERIAL_NUM MIN_ENEMY_BULLET_SERIAL_NUM - 1
#define MIN_ENEMY_BULLET_SERIAL_NUM 1000
#define MAX_ENEMY_BULLET_SERIAL_NUM MIN_USER_BULLET_SERIAL_NUM - 1
#define MIN_USER_BULLET_SERIAL_NUM 10000
#define MAX_USER_BULLET_SERIAL_NUM 20000

class ObjectManager final : public JSingleton<ObjectManager>
{
    friend class JSingleton<ObjectManager>;
private:
    std::vector<JEnemy*> enemyList;
    std::vector<Bullet*> enemyBulletList;
    std::vector<Bullet*> userBulletList;
public:
    template <typename T>
    JEnemy* GetRecycledEnemy() {
        JEnemy* poolObj = nullptr;

        if (enemyList.size() == 0)
        {
            poolObj = dynamic_cast<JEnemy*>(new T());
            poolObj->init();
            poolObj->m_iSerialNumber = MIN_ENEMY_SERIAL_NUM + enemyList.size();
            enemyList.push_back(poolObj);
            return poolObj;
        }

        for (auto elem : enemyList)
        {
            if (elem->CanRecylcable)
            {
                poolObj = elem;
                break;
            }
        }

        if (poolObj == nullptr)
        {
            poolObj = dynamic_cast<JEnemy*>(new T());
            poolObj->init();
            poolObj->m_iSerialNumber = MIN_ENEMY_SERIAL_NUM + enemyList.size();
            enemyList.push_back(poolObj);
            return poolObj;
        }

        poolObj->onRecycle();

        return poolObj;
    }

    Bullet* GetRecycledEnemyBullet();
    Bullet* GetRecycledUserBullet();
    JBaseObject* getObject(int iSerialNum);
    JEnemy* getEnemy(int iEnemySerialNum);
    Bullet* getEnemyBullet(int iEnemyBulletSerialNum);
    Bullet* getUserBullet(int iUserBulletSerialNum);
public:
    bool release();
    int getNumOfEnemy() {
        return enemyList.size();
    }
    int getNumOfEnemyBullet() {
        return enemyBulletList.size();
    }    
    int getNumOfUserBullet() {
        return userBulletList.size();
    }
public:
    bool isEnemy(int iEnemySerialNum);
    bool isEnemyBullet(int iEnemyBulletSerialNum);
    bool isUserBullet(int iUserBulletSerialNum);
private:
    ObjectManager() {};
    ~ObjectManager() = default;
    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
};
#define I_ObjectManager ObjectManager::GetInstance()