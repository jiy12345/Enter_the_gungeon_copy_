#pragma once
#include "stdafx.h"
#include "IObejctPoolable.h"

class ObjectPool : public JSingleton<ObjectPool>
{
    friend class JSingleton<ObjectPool>;
public :
	std::vector<IObejctPoolable*> PoolObjects;

public :
	template<typename T>
	T* GetRecycledObject()
	{
        T* poolObj = nullptr;

        if (PoolObjects.size() == 0)
        {
            PoolObjects.push_back(dynamic_cast<IObejctPoolable*>(poolObj = new T));
            return poolObj;
        }

        for (auto elem : PoolObjects)
        {
            if (elem->CanRecylcable)
            {
                poolObj = static_cast<T*>(elem);
                break;
            }
        }

        if (poolObj == nullptr)
        {
            PoolObjects.push_back(dynamic_cast<IObejctPoolable*>(poolObj = new T));
            return poolObj;
        }

        poolObj->onRecycle();

        return poolObj;
	}
private:
    ObjectPool() {};
    ~ObjectPool() = default;
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;
};
#define I_ObjectPool ObjectPool::GetInstance()


