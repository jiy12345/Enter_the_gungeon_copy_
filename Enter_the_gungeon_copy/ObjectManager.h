#pragma once
#include "stdafx.h"
#include "JEnemy.h"
#include "JUser.h"
#include "Bullet.h"

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
            poolObj->m_iSerialNumber = enemyList.size();
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
            poolObj->m_iSerialNumber = enemyList.size();
            enemyList.push_back(poolObj);
            return poolObj;
        }

        poolObj->onRecycle();

        return poolObj;
    }

    Bullet* GetRecycledEnemyBullet();
    Bullet* GetRecycledUserBullet();
    JEnemy* getEnemy(int iEnemySerialNum);
    Bullet* getEnemyBullet(int iEnemyBulletSerialNum);
    Bullet* getUserBullet(int iUserBulletSerialNum);

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
private:
    ObjectManager() {};
    ~ObjectManager() = default;
    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
};
#define I_ObjectManager ObjectManager::GetInstance()