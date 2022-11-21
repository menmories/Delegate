#include "FDelegate.h"

class FGlobalDelegate : public IDelegate
{
	friend IDelegate* MakeDelegate(GlobalCallbackFunc callback);
protected:
	FGlobalDelegate(GlobalCallbackFunc func);
	~FGlobalDelegate() {}
public:
	virtual void Call(void* args);

	virtual void Release();
private:
	GlobalCallbackFunc m_func;
};


FGlobalDelegate::FGlobalDelegate(GlobalCallbackFunc func)
	: m_func(func)
{
}

void FGlobalDelegate::Call(void * args)
{
	m_func(args);
}

void FGlobalDelegate::Release()
{
	delete this;
}

IDelegate * MakeDelegate(GlobalCallbackFunc callback)
{
	FGlobalDelegate* globalDelegate = new FGlobalDelegate(callback);
	return reinterpret_cast<IDelegate*>(globalDelegate);
}
