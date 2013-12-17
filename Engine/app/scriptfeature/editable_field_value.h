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
#ifndef __APP_EDITABLE_FIELD_H__
#define __APP_EDITABLE_FIELD_H__

#include "foundation/core/rtti.h"
#include "scriptfeature/inc/script_message.h"


namespace App
{
	typedef Util::Array<Util::Dictionary<Util::String,float> > SFDicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Math::float2> > SF2DicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Math::float3> > SF3DicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Math::float4> > SF4DicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Util::String> > SSDicArray;
	typedef Util::Array<Util::Dictionary<Util::String,int> > SIDicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Math::Color32> > SCDicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Util::String> > SIPDicArray;
	typedef Util::Array<Util::Dictionary<Util::String,Util::AssetPath> > SAPDicArray;

	class EditableFeilValue
	{
	public:
		EditableFeilValue();
		virtual ~EditableFeilValue();

		void Clear();
		void GrowAllArray();
		void RemoveArrayAt(int idx);
		void ClearValueAt(int idx);

		void AddInt(int row,Util::String key,int value);
		void AddFloat(int row,Util::String key,float value);
		void AddFloat2(int row,Util::String key,Math::float2& value);
		void AddFloat3(int row,Util::String key,Math::float3& value);
		void AddFloat4(int row,Util::String key,Math::float4& value);
		void AddString(int row,Util::String key,Util::String& value);
		void AddColor32(int row, Util::String key, Math::Color32& value);
		void AddImagePath(int row, Util::String key, Util::String& value);
		void AddAssetPath(int row, Util::String key, Util::AssetPath& value);

		void AssignAll(int row);
		void AssignInt(int row,Util::String key,int value);
		void AssignFloat(int row,Util::String key,float value);
		void AssignFloat2(int row,Util::String key,Math::float2& value);
		void AssignFloat3(int row,Util::String key,Math::float3& value);
		void AssignFloat4(int row,Util::String key,Math::float4& value);
		void AssignString(int row,Util::String key,Util::String& value);
		void AssignColor32(int row, Util::String key, Math::Color32& value);
		void AssignImagePath(int row, Util::String key, Util::String& value);
		void AssignAssetPath(int row, Util::String key, Util::AssetPath& value);		

		void SetInt(int row,Util::String key,int value);
		void SetFloat(int row,Util::String key,float value);
		void SetFloat2(int row,Util::String key,Math::float2& value);
		void SetFloat3(int row,Util::String key,Math::float3& value);
		void SetFloat4(int row,Util::String key,Math::float4& value);
		void SetString(int row,Util::String key,Util::String& value);
		void SetColor32(int row,Util::String key, Math::Color32& value);
		void SetImagePath(int row,Util::String key, Util::String& value);
		void SetAssetPath(int row, Util::String key, Util::AssetPath& value);

		const SIDicArray& GetArrInt() const;
		const SFDicArray& GetArrFloat() const;
		const SF2DicArray& GetArrFloat2() const;
		const SF3DicArray& GetArrFloat3() const;
		const SF4DicArray& GetArrFloat4() const;
		const SSDicArray& GetArrString() const;
		const SCDicArray& GetArrColor() const;
		const SIPDicArray& GetArrImagePath() const;
		const SAPDicArray& GetArrAssetPath() const;

		EditableFeilValue GetSingleValueAt(int i);
		void InsertValueAt(const EditableFeilValue& value,int i);
	private:
		SIDicArray m_arrInt;
		SFDicArray m_arrFloat;
		SF2DicArray m_arrFloat2;
		SF3DicArray m_arrFloat3;
		SF4DicArray m_arrFloat4;
		SSDicArray m_arrString;
		SCDicArray m_arrColor32;
		SIPDicArray m_arrImagePath;
		SAPDicArray m_arrAssetPath;
	};

	inline const SFDicArray& EditableFeilValue::GetArrFloat() const
	{
		return m_arrFloat;
	}

	inline const SF2DicArray& EditableFeilValue::GetArrFloat2() const
	{
		return m_arrFloat2;
	}

	inline const SF3DicArray& EditableFeilValue::GetArrFloat3() const
	{
		return m_arrFloat3;
	}

	inline const SF4DicArray& EditableFeilValue::GetArrFloat4() const
	{
		return m_arrFloat4;
	}

	inline const SSDicArray& EditableFeilValue::GetArrString() const
	{
		return m_arrString;
	}

	inline const SIDicArray& EditableFeilValue::GetArrInt() const
	{
		return m_arrInt;
	}

	inline const SCDicArray& EditableFeilValue::GetArrColor() const
	{
		return m_arrColor32;
	}


	inline const SIPDicArray& EditableFeilValue::GetArrImagePath() const
	{
		return m_arrImagePath;
	}


	inline const SAPDicArray& EditableFeilValue::GetArrAssetPath() const
	{
		return m_arrAssetPath;
	}

}

#endif