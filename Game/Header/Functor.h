#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	static T* GetInstance()
	{
		if (!m_pInstance)
		{
			struct MakeSharedEnabler : public T
			{
				MakeSharedEnabler() : T() { }
			};
			m_pInstance =  make_shared<MakeSharedEnabler>();
			
		}
		return m_pInstance.get();
	}


private:
	static shared_ptr<T> m_pInstance;
	static once_flag m_onceFlag;
};

template <typename T>
shared_ptr<T> Singleton<T>::m_pInstance = nullptr;

template <typename T>
once_flag Singleton<T>::m_onceFlag;