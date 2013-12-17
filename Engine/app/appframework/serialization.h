/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __serialization_H__
#define __serialization_H__
#include "serialization/serialize.h"
#include "addons/resource/resourcepriority.h"

namespace App
{
	typedef Serialization::ISerialize ISerialization;
	typedef Serialization::SerializeReader  AppReader;
	typedef Serialization::SerializeWriter AppWriter;
	typedef Serialization::SVersion Version;

	class ComponentSerializationArgs : public Serialization::SerializationArgs
	{
	public:
		ComponentSerializationArgs(Resources::Priority priority);
		virtual ~ComponentSerializationArgs();
		int getPriority() const;
	private:
		Resources::Priority priority;
	};

	inline ComponentSerializationArgs::ComponentSerializationArgs(Resources::Priority priority)
	{
		this->priority = priority;
	}

	inline int ComponentSerializationArgs::getPriority() const
	{
		if ( this == SerializationArgs::Empty )
			return Resources::ResourcePriority::Undefinition;
		else
			return priority;
	}
}

#endif // __serialization_H__
