/*!
	@file
	@author		Albert Semenov
	@date		11/2007
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
//Copy from mygui.

namespace delegates
{
	#ifndef GENESIS_OBSOLETE			//mygui里的调试相关的信息，我没有引用调试部分，所以要忽略掉
	#define GENESIS_OBSOLETE(text)
	#endif

	#ifndef GENESIS_EXCEPT			//mygui里的调试相关的信息，我没有引用调试部分，所以要忽略掉
	#define GENESIS_EXCEPT(dest)		//n_error(dest);
	#endif

	#define GENESIS_COMBINE(a, b)									GENESIS_COMBINE1(a, b)
	#define GENESIS_COMBINE1(a, b)								a##b

	#define MYGUI_I_DELEGATE									GENESIS_COMBINE(IDelegate, GENESIS_SUFFIX)

	#define MYGUI_C_STATIC_DELEGATE					GENESIS_COMBINE(CStaticDelegate, GENESIS_SUFFIX)
	#define MYGUI_C_METHOD_DELEGATE					GENESIS_COMBINE(CMethodDelegate, GENESIS_SUFFIX)

	#define MYGUI_C_DELEGATE									GENESIS_COMBINE(CDelegate, GENESIS_SUFFIX)
	#define MYGUI_C_MULTI_DELEGATE						GENESIS_COMBINE(CMultiDelegate, GENESIS_SUFFIX)

	#ifndef nullptr
	#define nullptr 0
	#endif


	// базовый класс всех делегатов
	GENESIS_TEMPLATE   GENESIS_TEMPLATE_PARAMS
	class MYGUI_I_DELEGATE
	{
	public:
		virtual ~MYGUI_I_DELEGATE() { }
#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
		virtual bool isType( const std::type_info& _type) = 0;
#endif
		virtual void invoke( GENESIS_PARAMS ) = 0;
		virtual bool compare(  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS* _delegate) const = 0;
		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return false;
		}
	};


	// делегат для статической функции
	GENESIS_TEMPLATE   GENESIS_TEMPLATE_PARAMS
	class MYGUI_C_STATIC_DELEGATE : public  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS
	{
	public:
		typedef void (*Func)( GENESIS_PARAMS );

		MYGUI_C_STATIC_DELEGATE (Func _func) : mFunc(_func) { }

#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
		virtual bool isType( const std::type_info& _type)
		{
			return typeid( MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS ) == _type;
		}
#endif

		virtual void invoke( GENESIS_PARAMS )
		{
			mFunc( GENESIS_ARGS );
		}

		virtual bool compare(  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS* _delegate) const
		{
#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
			if (nullptr == _delegate || !_delegate->isType(typeid(MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS)) ) return false;
			MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS* cast = static_cast<MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS*>(_delegate);
#else
			MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS* cast = dynamic_cast<MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS*>(_delegate);
			if (nullptr == cast) return false;
#endif
			return cast->mFunc == mFunc;
		}
		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return false;
		}

	private:
		Func mFunc;
	};


	// делегат для метода класса
	template GENESIS_T_TEMPLATE_PARAMS
	class MYGUI_C_METHOD_DELEGATE : public  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS
	{
	public:
		typedef void (T::*Method)( GENESIS_PARAMS );

		MYGUI_C_METHOD_DELEGATE(IDelegateUnlink* _unlink, T* _object, Method _method) : mUnlink(_unlink), mObject(_object), mMethod(_method) { }

#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
		virtual bool isType( const std::type_info& _type)
		{
			return typeid( MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS ) == _type;
		}
#endif

		virtual void invoke( GENESIS_PARAMS )
		{
			(mObject->*mMethod)( GENESIS_ARGS );
		}

		virtual bool compare(  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS* _delegate) const
		{
#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
			if (nullptr == _delegate || !_delegate->isType(typeid(MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS)) ) return false;
			MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS* cast = static_cast<  MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS* >(_delegate);
#else
			MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS* cast = dynamic_cast<  MYGUI_C_METHOD_DELEGATE GENESIS_T_TEMPLATE_ARGS* >(_delegate);
			if (nullptr == cast) return false;
#endif
			return cast->mObject == mObject && cast->mMethod == mMethod;
		}

		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return mUnlink == _unlink;
		}

	private:
		IDelegateUnlink* mUnlink;
		T* mObject;
		Method mMethod;
	};

} // namespace delegates

// шаблон для создания делегата статической функции
// параметры : указатель на функцию
// пример : newDelegate(funk_name);
// пример : newDelegate(class_name::static_method_name);
GENESIS_TEMPLATE   GENESIS_TEMPLATE_PARAMS
inline  delegates::MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS* newDelegate( void (*_func)( GENESIS_PARAMS ) )
{
	return new delegates::MYGUI_C_STATIC_DELEGATE GENESIS_TEMPLATE_ARGS  (_func);
}


// шаблон для создания делегата метода класса
// параметры : указатель на объект класса и указатель на метод класса
// пример : newDelegate(&object_name, &class_name::method_name);
template GENESIS_T_TEMPLATE_PARAMS
inline  delegates::MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS* newDelegate( T* _object, void (T::*_method)( GENESIS_PARAMS ) )
{
	return new delegates::MYGUI_C_METHOD_DELEGATE  GENESIS_T_TEMPLATE_ARGS  (delegates::GetDelegateUnlink(_object), _object, _method);
}

namespace delegates
{
	// шаблон класса делегата
	GENESIS_TEMPLATE   GENESIS_TEMPLATE_PARAMS
	class MYGUI_C_DELEGATE
	{
	public:
		typedef  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS  IDelegate;

		MYGUI_C_DELEGATE () : mDelegate(nullptr) { }
		MYGUI_C_DELEGATE (const MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& _event) : mDelegate(nullptr)
		{
			// забираем себе владение
			IDelegate* del = _event.mDelegate;
			const_cast< MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& >(_event).mDelegate = nullptr;

			if (mDelegate != nullptr && !mDelegate->compare(del))
				delete mDelegate;

			mDelegate = del;
		}
		~MYGUI_C_DELEGATE ()
		{
			clear();
		}

		bool empty() const
		{
			return mDelegate == nullptr;
		}

		void clear()
		{
			if (mDelegate)
			{
				delete mDelegate;
				mDelegate = nullptr;
			}
		}

		MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& operator=(IDelegate* _delegate)
		{
			delete mDelegate;
			mDelegate = _delegate;
			return *this;
		}

		MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& operator=(const MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& _event)
		{
			// забираем себе владение
			IDelegate* del = _event.mDelegate;
			const_cast< MYGUI_C_DELEGATE  GENESIS_TEMPLATE_ARGS& >(_event).mDelegate = nullptr;

			if (mDelegate != nullptr && !mDelegate->compare(del))
				delete mDelegate;

			mDelegate = del;

			return *this;
		}

		void operator()( GENESIS_PARAMS )
		{
			if (mDelegate == nullptr) return;
			mDelegate->invoke( GENESIS_ARGS );
		}

	private:
		IDelegate* mDelegate;
	};


	// шаблон класса мульти делегата
	GENESIS_TEMPLATE   GENESIS_TEMPLATE_PARAMS
	class MYGUI_C_MULTI_DELEGATE
	{
	public:
		typedef  MYGUI_I_DELEGATE GENESIS_TEMPLATE_ARGS  IDelegate;
		typedef GENESIS_TYPENAME std::list<IDelegate* /*, Allocator<IDelegate*>*/ > ListDelegate;
		typedef GENESIS_TYPENAME ListDelegate::iterator ListDelegateIterator;
		typedef GENESIS_TYPENAME ListDelegate::const_iterator ConstListDelegateIterator;

		MYGUI_C_MULTI_DELEGATE () { }
		~MYGUI_C_MULTI_DELEGATE ()
		{
			clear();
		}

		bool empty() const
		{
			for (ConstListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter) return false;
			}
			return true;
		}

		void clear()
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter)
				{
					delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

		void clear(IDelegateUnlink* _unlink)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_unlink))
				{
					delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

		MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& operator+=(IDelegate* _delegate)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_delegate))
				{
					GENESIS_EXCEPT("Trying to add same delegate twice.");
				}
			}
			mListDelegates.push_back(_delegate);
			return *this;
		}

		MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& operator-=(IDelegate* _delegate)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_delegate))
				{
					// проверяем на идентичность делегатов
					if ((*iter) != _delegate) delete (*iter);
					(*iter) = nullptr;
					break;
				}
			}
			delete _delegate;
			return *this;
		}

		void operator()( GENESIS_PARAMS )
		{
			ListDelegateIterator iter = mListDelegates.begin();
			while (iter != mListDelegates.end())
			{
				if (nullptr == (*iter))
				{
					iter = mListDelegates.erase(iter);
				}
				else
				{
					(*iter)->invoke( GENESIS_ARGS );
					++iter;
				}
			}
		}

		MYGUI_C_MULTI_DELEGATE (const MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& _event)
		{
			// забираем себе владение
			ListDelegate del = _event.mListDelegates;
			const_cast< MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& >(_event).mListDelegates.clear();

			safe_clear(del);

			mListDelegates = del;
		}

		MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& operator=(const MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& _event)
		{
			// забираем себе владение
			ListDelegate del = _event.mListDelegates;
			const_cast< MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& >(_event).mListDelegates.clear();

			safe_clear(del);

			mListDelegates = del;

			return *this;
		}

		GENESIS_OBSOLETE("use : operator += ")
		MYGUI_C_MULTI_DELEGATE  GENESIS_TEMPLATE_ARGS& operator=(IDelegate* _delegate)
		{
			clear();
			*this += _delegate;
			return *this;
		}

	private:
		void safe_clear(ListDelegate& _delegates)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter)
				{
					IDelegate* del = (*iter);
					(*iter) = nullptr;
					delete_is_not_found(del, _delegates);
				}
			}
		}

		void delete_is_not_found(IDelegate* _del, ListDelegate& _delegates)
		{
			for (ListDelegateIterator iter = _delegates.begin(); iter != _delegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_del))
				{
					return;
				}
			}

			delete _del;
		}

	private:
		ListDelegate mListDelegates;
	};


	#undef GENESIS_COMBINE
	#undef GENESIS_COMBINE1

	#undef MYGUI_I_DELEGATE

	#undef MYGUI_C_STATIC_DELEGATE
	#undef MYGUI_C_METHOD_DELEGATE

	#undef MYGUI_C_DELEGATE
	#undef MYGUI_C_MULTI_DELEGATE

	#undef GENESIS_SUFFIX
	#undef GENESIS_TEMPLATE
	#undef GENESIS_TEMPLATE_PARAMS
	#undef GENESIS_TEMPLATE_ARGS
	#undef GENESIS_T_TEMPLATE_PARAMS
	#undef GENESIS_T_TEMPLATE_ARGS
	#undef GENESIS_PARAMS
	#undef GENESIS_ARGS
	#undef GENESIS_TYPENAME

} // namespace delegates
