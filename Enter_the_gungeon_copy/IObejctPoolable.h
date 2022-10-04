#pragma once

class IObejctPoolable
{
public :
	bool CanRecylcable  = false;

public :
	virtual ~IObejctPoolable() = default;

	virtual void setRecycle()
	{ CanRecylcable = true; }

	virtual void onRecycle()
	{ CanRecylcable = false; }

	virtual bool update()
	{ 
		if (CanRecylcable) return true;
		else			   return false;
	}

	virtual bool render_objectPool() {
		return true;
	}
};