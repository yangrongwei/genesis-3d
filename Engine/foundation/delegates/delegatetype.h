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
#ifndef __DELEGATE_TYPE_H__
#define __DELEGATE_TYPE_H__

#include <list>

#ifndef DELEGATE_RTTI_DISABLE_TYPE_INFO
#include <typeinfo>
#endif

// source
// http://rsdn.ru/article/cpp/delegates.xml

namespace Delegates
{

	namespace delegates
	{
		class IDelegateUnlink
		{
		public:
			virtual ~IDelegateUnlink() { }

			IDelegateUnlink()
			{
				m_baseDelegateUnlink = this;
			}
			bool compare(IDelegateUnlink* _unlink) const
			{
				return m_baseDelegateUnlink == _unlink->m_baseDelegateUnlink;
			}

		private:
			IDelegateUnlink* m_baseDelegateUnlink;
		};

		inline IDelegateUnlink* GetDelegateUnlink(void* _base)
		{
			return 0;
		}
		inline IDelegateUnlink* GetDelegateUnlink(IDelegateUnlink* _base)
		{
			return _base;
		}
	}

	// 忌快戒 扭忘把忘技快找把抉志
	#define GENESIS_SUFFIX       0
	#define GENESIS_TEMPLATE
	#define GENESIS_TEMPLATE_PARAMS
	#define GENESIS_TEMPLATE_ARGS
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T>
	#define GENESIS_T_TEMPLATE_ARGS <T>
	#define GENESIS_PARAMS
	#define GENESIS_ARGS
	#define GENESIS_TYPENAME

	#include "delegate_implement.h"

	// 抉忱我扶 扭忘把忘技快找把
	#define GENESIS_SUFFIX       1
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1>
	#define GENESIS_TEMPLATE_ARGS    <TP1>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1>
	#define GENESIS_PARAMS       TP1 p1
	#define GENESIS_ARGS         p1
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"

	// 忱志忘 扭忘把忘技快找把忘
	#define GENESIS_SUFFIX       2
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1, typename TP2>
	#define GENESIS_TEMPLATE_ARGS    <TP1, TP2>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1, TP2>
	#define GENESIS_PARAMS       TP1 p1, TP2 p2
	#define GENESIS_ARGS         p1, p2
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"

	// 找把我 扭忘把忘技快找把忘
	#define GENESIS_SUFFIX       3
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3>
	#define GENESIS_TEMPLATE_ARGS    <TP1, TP2, TP3>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3>
	#define GENESIS_PARAMS       TP1 p1, TP2 p2, TP3 p3
	#define GENESIS_ARGS         p1, p2, p3
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"

	// 折快找抑把快 扭忘把忘技快找把忘
	#define GENESIS_SUFFIX       4
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4>
	#define GENESIS_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4>
	#define GENESIS_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4
	#define GENESIS_ARGS         p1, p2, p3, p4
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"

	// 扭攸找抆 扭忘把忘技快找把抉志
	#define GENESIS_SUFFIX       5
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
	#define GENESIS_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4, TP5>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4, TP5>
	#define GENESIS_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5
	#define GENESIS_ARGS         p1, p2, p3, p4, p5
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"

	// 扭攸找抆 扭忘把忘技快找把抉志
	#define GENESIS_SUFFIX       6
	#define GENESIS_TEMPLATE	template
	#define GENESIS_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6>
	#define GENESIS_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4, TP5, TP6>
	#define GENESIS_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6>
	#define GENESIS_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4, TP5, TP6>
	#define GENESIS_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5, TP6 p6
	#define GENESIS_ARGS         p1, p2, p3, p4, p5, p6
	#define GENESIS_TYPENAME     typename

	#include "delegate_implement.h"


}

#endif //
