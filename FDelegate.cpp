#include "stdafx.h"
#include "FDelegate.h"

namespace FantacyUI
{
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

}

FantacyUI::FGlobalDelegate::FGlobalDelegate(GlobalCallbackFunc func)
	: m_func(func)
{
}

void FantacyUI::FGlobalDelegate::Call(void * args)
{
	m_func(args);
}

void FantacyUI::FGlobalDelegate::Release()
{
	delete this;
}

FantacyUI::IDelegate * FantacyUI::MakeDelegate(GlobalCallbackFunc callback)
{
	FGlobalDelegate* globalDelegate = new FGlobalDelegate(callback);
	return reinterpret_cast<IDelegate*>(globalDelegate);
}
