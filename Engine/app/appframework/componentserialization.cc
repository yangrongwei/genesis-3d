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
#include "stdneb.h"
#include "appframework/component.h"

namespace App
{
	class ComponentSerialization
	{
	public:
		ComponentSerialization( const Component* pComponent )
			:mObject(pComponent)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			n_error(" SceneSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Save( AppWriter* pWriter );
	protected:
		const Component* mObject;

	};



	//------------------------------------------------------------------------
	void ComponentSerialization::Load_1(AppReader* pSerialize)
	{
		return;
	}
	//------------------------------------------------------------------------
	void ComponentSerialization::Save(AppWriter* pSerialize)
	{
		return;
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version Component::GetVersion() const
	{
		return 1;	//	当前版本号是1
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void Component::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		ComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void Component::Save( AppWriter* pWriter ) const
	{
		ComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

}


