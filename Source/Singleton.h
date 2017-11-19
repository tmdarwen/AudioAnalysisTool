#pragma once

// Note To User: If you're going to use this with your class (say "Foo"),
// make sure you've declared Singleton<Foo> as a friend.

template <class T>
class Singleton
{
	public:
		Singleton() { }
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;

		static T& GetInstance()
		{
			if(instance_ == nullptr)
			{
				instance_ = new T();
			}

			return *instance_;
		}

	protected:
		static T* instance_;
};

template <class T> T* Singleton<T>::instance_ = nullptr;