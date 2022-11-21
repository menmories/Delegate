

#ifndef __DELEGATE_H__
#define __DELEGATE_H__
class IDelegate
{
public:
	//called callback function.
	virtual void Call(void* args = nullptr) = 0;

	virtual void Release() = 0;
};

template<class TClass>
class FDelegate : public IDelegate
{
	typedef void(TClass::*CallbackFunc)(void* args);
	template<class TClass>
	friend IDelegate* MakeDelegate(TClass* pClass, void(TClass::*CallbackFunc)(void*));
protected:
	
	FDelegate(TClass* pClass, CallbackFunc func)
	{
		this->Obj = pClass;
		this->Callback = func;
	}
public:
	virtual void Call(void* args)
	{
		(this->Obj->*Callback)(args);
	}

	virtual void Release()
	{
		delete this;
	}
private:
	TClass* Obj;
	CallbackFunc Callback;
};

template<class TClass>
IDelegate* MakeDelegate(TClass* pClass, void(TClass::*CallbackFunc)(void*))
{
	FDelegate<TClass>* pDelegate = new FDelegate<TClass>(pClass, CallbackFunc);
	return reinterpret_cast<IDelegate*>(pDelegate);
}

typedef void(*GlobalCallbackFunc)(void* args);
IDelegate* MakeDelegate(GlobalCallbackFunc callback);


#endif	//__DELEGATE_H__

