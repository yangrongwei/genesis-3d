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
#include "graphicfeature/components/simpleskycomponent.h"

namespace App
{
  class SimpleSkyComponentSerialization
   {
    public:

	    SimpleSkyComponentSerialization( const SimpleSkyComponent* pComponent)
		  : mObject(pComponent)
	  {

	   }

	    inline void Load( Version ver, AppReader* pReader)
	  {
		if (ver == 2)
		{
			Load_2(pReader);
			return;
		}
        if (ver == 3)
		{
			Load_3(pReader);
			return;
		}

		  n_error(" SimpleSkyComponentSerialization::Load unknown version " );
	   }

	   void Load_2( AppReader* pReader );
	   void Load_3( AppReader* pReader );
	   void Save( AppWriter* pWriter );

    protected:
	   const SimpleSkyComponent* mObject;
   };

   const char* s_sky0 = "simpleSky0";
   const char* s_sky1 = "simpleSky1";
   const char* s_sky2 = "simpleSky2";
   const char* s_sky3 = "simpleSky3";
   const char* s_sky4 = "simpleSky4";
   const char* s_sky5 = "simpleSky5";

	void SimpleSkyComponentSerialization::Load_2( AppReader* pReader )
	{

	}
	void SimpleSkyComponentSerialization::Load_3( AppReader* pReader )
	{
		n_assert( mObject );
		SimpleSkyComponent* pSky = const_cast<SimpleSkyComponent*>(mObject);
		n_assert(pSky);

		Load_2(pReader);


		for (int i = 0; i < 6; ++i)
		{
			pSky->SetMaterialByShaderID(i,"sys:Fx_SkyBox.shader",false);		
		}

		//add by wangyanqing,2013.9.26
		Util::String skyTex; 
		pReader->SerializeString( s_sky0,   skyTex );
		pSky->SetSkyTexByNum(0,skyTex);

		pReader->SerializeString( s_sky1,   skyTex );
		pSky->SetSkyTexByNum(1,skyTex);

		pReader->SerializeString( s_sky2,   skyTex );
		pSky->SetSkyTexByNum(2,skyTex);

		pReader->SerializeString( s_sky3,   skyTex );
		pSky->SetSkyTexByNum(3,skyTex);

		pReader->SerializeString( s_sky4,   skyTex );
		pSky->SetSkyTexByNum(4,skyTex);

		pReader->SerializeString( s_sky5,   skyTex );
		pSky->SetSkyTexByNum(5,skyTex);
	}
	void SimpleSkyComponentSerialization::Save(App::AppWriter *pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);
		SimpleSkyComponent* pSky = const_cast<SimpleSkyComponent*>(mObject);
		//add by wangyanqing,2013.9.26
	    pWriter->SerializeString( s_sky0, pSky->GetSkyTexByNum(0) );
	    pWriter->SerializeString( s_sky1, pSky->GetSkyTexByNum(1) );
		pWriter->SerializeString( s_sky2, pSky->GetSkyTexByNum(2) );
		pWriter->SerializeString( s_sky3, pSky->GetSkyTexByNum(3) );
		pWriter->SerializeString( s_sky4, pSky->GetSkyTexByNum(4) );
		pWriter->SerializeString( s_sky5, pSky->GetSkyTexByNum(5) );
	}

	Version SimpleSkyComponent::GetVersion() const
	{
		//return 2;
		return 3;//add by wangyanqing,2013.9.26
	}

	void SimpleSkyComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SimpleSkyComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	void SimpleSkyComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SimpleSkyComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}
}