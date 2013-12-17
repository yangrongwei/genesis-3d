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
#include "graphicfeature/components/skinnedmeshrendercomponent.h"

namespace App
{
	class SkinnedMeshRenderComponentSerialization
	{
	public:
		SkinnedMeshRenderComponentSerialization( const SkinnedMeshRenderComponent* pComponent )
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
			if ( 2 == ver )
			{
				Load_2(pReader);
				return;
			}

			n_error(" SkinMeshRenderComponentSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Save( AppWriter* pWriter );
	protected:
		const SkinnedMeshRenderComponent* mObject;

	};

	const char* s_sShaderCount = "ShaderCount";
	const char* s_sShaderID = "ShaderID";
	const char* s_sTextureCount = "TextureCount";
	const char* s_sTextureParamName = "TextureParam";
	const char* s_sTextureID = "TextureID";
	const char* s_sDummyID = "EmptyNull";

	//------------------------------------------------------------------------
	void SkinnedMeshRenderComponentSerialization::Load_1(AppReader* pSerialize)
	{

	}
	//------------------------------------------------------------------------
	void SkinnedMeshRenderComponentSerialization::Load_2( AppReader* pReader )
	{

	}
	//------------------------------------------------------------------------
	void SkinnedMeshRenderComponentSerialization::Save(AppWriter* pSerialize)
	{

	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SkinnedMeshRenderComponent::GetVersion() const
	{
		return 2;	//	Use material, Version num 2
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void SkinnedMeshRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SkinnedMeshRenderComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void SkinnedMeshRenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SkinnedMeshRenderComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

}