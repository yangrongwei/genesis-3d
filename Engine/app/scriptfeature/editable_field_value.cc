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
#include "app/scriptfeature/editable_field_value.h"

namespace App
{
	EditableFeilValue::EditableFeilValue():
		 m_arrFloat()
		,m_arrFloat2()
		,m_arrFloat4()
		,m_arrString()
		,m_arrInt()
		,m_arrColor32()
		,m_arrImagePath()
		,m_arrAssetPath()
	{

	}

	EditableFeilValue::~EditableFeilValue()
	{

	}

	void EditableFeilValue::Clear()
	{
		m_arrFloat.Clear();
		m_arrFloat2.Clear();
		m_arrFloat3.Clear();
		m_arrFloat4.Clear();
		m_arrString.Clear();
		m_arrInt.Clear();
		m_arrColor32.Clear();
		m_arrImagePath.Clear();
		m_arrAssetPath.Clear();
	}

	void EditableFeilValue::GrowAllArray()
	{
		Util::Dictionary<Util::String,int> insInt;
		Util::Dictionary<Util::String,float> insFloat;
		Util::Dictionary<Util::String,Math::float2> insFloat2;
		Util::Dictionary<Util::String,Math::float3> insFloat3;
		Util::Dictionary<Util::String,Math::float4> insFloat4;
		Util::Dictionary<Util::String,Util::String> insString;
		Util::Dictionary<Util::String,Math::Color32> insColor32;
		Util::Dictionary<Util::String,Util::String>  insImagePath;
		Util::Dictionary<Util::String,Util::AssetPath> insAssetPath;

		m_arrInt.Append(insInt);
		m_arrFloat.Append(insFloat);
		m_arrFloat2.Append(insFloat2);
		m_arrFloat3.Append(insFloat3);
		m_arrFloat4.Append(insFloat4);
		m_arrString.Append(insString);
		m_arrColor32.Append(insColor32);
		m_arrImagePath.Append(insImagePath);
		m_arrAssetPath.Append(insAssetPath);
	}

	void EditableFeilValue::RemoveArrayAt( int idx )
	{
		m_arrInt.EraseIndex(idx);
		m_arrFloat.EraseIndex(idx);
		m_arrFloat2.EraseIndex(idx);
		m_arrFloat3.EraseIndex(idx);
		m_arrFloat4.EraseIndex(idx);
		m_arrString.EraseIndex(idx);
		m_arrColor32.EraseIndex(idx);
		m_arrImagePath.EraseIndex(idx);
		m_arrAssetPath.EraseIndex(idx);
	}


	void EditableFeilValue::ClearValueAt( int idx )
	{
		m_arrInt[idx].Clear();
		m_arrFloat[idx].Clear();
		m_arrFloat2[idx].Clear();
		m_arrFloat3[idx].Clear();
		m_arrFloat4[idx].Clear();
		m_arrString[idx].Clear();
		m_arrColor32[idx].Clear();
		m_arrImagePath[idx].Clear();
		m_arrAssetPath[idx].Clear();
	}


	void EditableFeilValue::AddInt( int row,Util::String key,int value )
	{
		m_arrInt[row].Add(key,value);
	}

	void EditableFeilValue::AddFloat( int row,Util::String key,float value )
	{
		m_arrFloat[row].Add(key,value);
	}

	void EditableFeilValue::AddFloat2( int row,Util::String key,Math::float2& value )
	{
		m_arrFloat2[row].Add(key,value);
	}

	void EditableFeilValue::AddFloat3( int row,Util::String key,Math::float3& value )
	{
		m_arrFloat3[row].Add(key,value);
	}

	void EditableFeilValue::AddFloat4( int row,Util::String key,Math::float4& value )
	{
		m_arrFloat4[row].Add(key,value);
	}

	void EditableFeilValue::AddString( int row,Util::String key,Util::String& value )
	{
		m_arrString[row].Add(key,value);
	}


	void EditableFeilValue::AddColor32( int row, Util::String key, Math::Color32& value )
	{
		m_arrColor32[row].Add(key,value);
	}

	void EditableFeilValue::AddImagePath( int row, Util::String key, Util::String& value )
	{
		m_arrImagePath[row].Add(key,value);
	}

	void EditableFeilValue::AddAssetPath( int row, Util::String key, Util::AssetPath& value )
	{
		m_arrAssetPath[row].Add(key,value);
	}

	void EditableFeilValue::SetInt( int row,Util::String key,int value )
	{
		int idx = m_arrInt[row].FindIndex(key);
		m_arrInt[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetFloat( int row,Util::String key,float value )
	{
		int idx = m_arrFloat[row].FindIndex(key);
		m_arrFloat[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetFloat2( int row,Util::String key,Math::float2& value )
	{
		int idx = m_arrFloat2[row].FindIndex(key);
		m_arrFloat2[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetFloat3( int row,Util::String key,Math::float3& value )
	{
		int idx = m_arrFloat3[row].FindIndex(key);
		m_arrFloat3[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetFloat4( int row,Util::String key,Math::float4& value )
	{
		int idx = m_arrFloat4[row].FindIndex(key);
		m_arrFloat4[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetString( int row,Util::String key,Util::String& value )
	{
		int idx = m_arrString[row].FindIndex(key);
		m_arrString[row].ValueAtIndex(idx) = value;
	}


	void EditableFeilValue::SetColor32( int row,Util::String key, Math::Color32& value )
	{
		int idx = m_arrColor32[row].FindIndex(key);
		m_arrColor32[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetImagePath( int row,Util::String key, Util::String& value )
	{
		int idx = m_arrImagePath[row].FindIndex(key);
		m_arrImagePath[row].ValueAtIndex(idx) = value;
	}

	void EditableFeilValue::SetAssetPath( int row, Util::String key, Util::AssetPath& value )
	{
		int idx = m_arrAssetPath[row].FindIndex(key);
		m_arrAssetPath[row].ValueAtIndex(idx) = value;
	}


	void EditableFeilValue::AssignInt( int row,Util::String key,int value )
	{
		if( row == m_arrInt.Size() )
		{
			Util::Dictionary<Util::String,int> insInt;
			m_arrInt.Append(insInt);
		}
		else if( row > m_arrInt.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrInt[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrInt[row].Add(key,value);
		}
		else
		{
			m_arrInt[row].ValueAtIndex(idx) = value;
		}
	}

	void EditableFeilValue::AssignFloat( int row,Util::String key,float value )
	{
		if( row == m_arrFloat.Size() )
		{
			Util::Dictionary<Util::String,float> insFloat;
			m_arrFloat.Append(insFloat);
		}
		else if( row > m_arrFloat.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrFloat[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrFloat[row].Add(key,value);
		}
		else
		{
			m_arrFloat[row].ValueAtIndex(idx) = value;
		}
	}

	void EditableFeilValue::AssignFloat2( int row,Util::String key,Math::float2& value )
	{
		if( row == m_arrFloat2.Size() )
		{
			Util::Dictionary<Util::String,Math::float2> insFloat2;
			m_arrFloat2.Append(insFloat2);
		}
		else if( row > m_arrFloat2.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrFloat2[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrFloat2[row].Add(key,value);
		}
		else
		{
			m_arrFloat2[row].ValueAtIndex(idx) = value;
		}
	}

	void EditableFeilValue::AssignFloat3( int row,Util::String key,Math::float3& value )
	{
		if( row == m_arrFloat3.Size() )
		{
			Util::Dictionary<Util::String,Math::float3> insFloat3;
			m_arrFloat3.Append(insFloat3);
		}
		else if( row > m_arrFloat3.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrFloat3[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrFloat3[row].Add(key,value);
		}
		else
		{
			m_arrFloat3[row].ValueAtIndex(idx) = value;
		}
	}

	void EditableFeilValue::AssignFloat4( int row,Util::String key,Math::float4& value )
	{
		if( row == m_arrFloat4.Size() )
		{
			Util::Dictionary<Util::String,Math::float4> insFloat4;
			m_arrFloat4.Append(insFloat4);
		}
		else if( row > m_arrFloat4.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrFloat4[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrFloat4[row].Add(key,value);
		}
		else
		{
			m_arrFloat4[row].ValueAtIndex(idx) = value;
		}
	}

	void EditableFeilValue::AssignString( int row,Util::String key,Util::String& value )
	{
		if( row == m_arrString.Size() )
		{
			Util::Dictionary<Util::String,Util::String> insString;
			m_arrString.Append(insString);
		}
		else if( row > m_arrString.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrString[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrString[row].Add(key,value);
		}
		else
		{
			m_arrString[row].ValueAtIndex(idx) = value;
		}
	}


	void EditableFeilValue::AssignColor32( int row, Util::String key, Math::Color32& value )
	{
		if( row == m_arrColor32.Size() )
		{
			Util::Dictionary<Util::String,Math::Color32> insColor32;
			m_arrColor32.Append(insColor32);
		}
		else if( row > m_arrColor32.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrColor32[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrColor32[row].Add(key,value);
		}
		else
		{
			m_arrColor32[row].ValueAtIndex(idx) = value;
		}
	}


	void EditableFeilValue::AssignImagePath( int row, Util::String key, Util::String& value )
	{
		if( row == m_arrImagePath.Size() )
		{
			Util::Dictionary<Util::String,Util::String> insString;
			m_arrImagePath.Append(insString);
		}
		else if( row > m_arrImagePath.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrImagePath[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrImagePath[row].Add(key,value);
		}
		else
		{
			m_arrImagePath[row].ValueAtIndex(idx) = value;
		}
	}


	void EditableFeilValue::AssignAssetPath( int row, Util::String key, Util::AssetPath& value )
	{
		if( row == m_arrAssetPath.Size() )
		{
			Util::Dictionary<Util::String,Util::AssetPath> insString;
			m_arrAssetPath.Append(insString);
		}
		else if( row > m_arrAssetPath.Size())
		{
			n_error("feild assign error\n");
		}
		int idx = m_arrAssetPath[row].FindIndex(key);
		if( idx == -1 )
		{
			m_arrAssetPath[row].Add(key,value);
		}
		else
		{
			m_arrAssetPath[row].ValueAtIndex(idx) = value;
		}
	}


	void EditableFeilValue::AssignAll( int row )
	{
		if( row == m_arrString.Size() )
		{
			Util::Dictionary<Util::String,Util::String> insString;
			m_arrString.Append(insString);
		}
		if( row == m_arrFloat4 .Size() )
		{
			Util::Dictionary<Util::String,Math::float4> insString;
			m_arrFloat4.Append(insString);
		}
		if( row == m_arrFloat3.Size() )
		{
			Util::Dictionary<Util::String,Math::float3> insString;
			m_arrFloat3.Append(insString);
		}
		if( row == m_arrFloat2.Size() )
		{
			Util::Dictionary<Util::String,Math::float2> insString;
			m_arrFloat2.Append(insString);
		}
		if( row == m_arrFloat.Size() )
		{
			Util::Dictionary<Util::String,float> insString;
			m_arrFloat.Append(insString);
		}
		if( row == m_arrInt.Size() )
		{
			Util::Dictionary<Util::String,int> insString;
			m_arrInt.Append(insString);
		}
		if ( row == m_arrColor32.Size() )
		{
			Util::Dictionary<Util::String,Math::Color32> insString;
			m_arrColor32.Append(insString);
		}
		if ( row == m_arrImagePath.Size() )
		{
			Util::Dictionary<Util::String,Util::String> insString;
			m_arrImagePath.Append(insString);
		}
		if( row == m_arrAssetPath.Size() )
		{
			Util::Dictionary<Util::String,Util::AssetPath> insString;
			m_arrAssetPath.Append(insString);
		}
	}

	App::EditableFeilValue EditableFeilValue::GetSingleValueAt( int i )
	{
		EditableFeilValue ret;
		ret.GrowAllArray();

		ret.m_arrFloat[0] = this->m_arrFloat[i];
		ret.m_arrFloat2[0] = this->m_arrFloat2[i];
		ret.m_arrFloat3[0] = this->m_arrFloat3[i];
		ret.m_arrFloat4[0] = this->m_arrFloat4[i];
		ret.m_arrInt[0] = this->m_arrInt[i];
		ret.m_arrString[0] = this->m_arrString[i];
		ret.m_arrColor32[0] = this->m_arrColor32[i];
		ret.m_arrImagePath[0] = this->m_arrImagePath[i];
		ret.m_arrAssetPath[0] = this->m_arrAssetPath[i];

		return ret;
	}

	void EditableFeilValue::InsertValueAt( const EditableFeilValue& evalue,int i )
	{
		if(m_arrFloat.Size()==0)
		{
			m_arrFloat.Reserve(1);
		}
		if(m_arrFloat2.Size()==0)
		{
			m_arrFloat2.Reserve(1);
		}
		if(m_arrFloat3.Size()==0)
		{
			m_arrFloat3.Reserve(1);
		}
		if(m_arrFloat4.Size()==0)
		{
			m_arrFloat4.Reserve(1);
		}
		if(m_arrInt.Size()==0)
		{
			m_arrInt.Reserve(1);
		}
		if(m_arrString.Size()==0)
		{
			m_arrString.Reserve(1);
		}
		if(m_arrColor32.Size() == 0)
		{
			m_arrColor32.Reserve(1);
		}
		if(m_arrImagePath.Size() == 0)
		{
			m_arrImagePath.Reserve(1);
		}
		if(m_arrAssetPath.Size() == 0)
		{
			m_arrAssetPath.Reserve(1);
		}

		this->m_arrFloat.Insert(i,evalue.m_arrFloat[0]);
		this->m_arrFloat2.Insert(i,evalue.m_arrFloat2[0]);
		this->m_arrFloat3.Insert(i,evalue.m_arrFloat3[0]);
		this->m_arrFloat4.Insert(i,evalue.m_arrFloat4[0]);
		this->m_arrInt.Insert(i,evalue.m_arrInt[0]);
		this->m_arrString.Insert(i,evalue.m_arrString[0]);
		this->m_arrColor32.Insert(i,evalue.m_arrColor32[0]);
		this->m_arrImagePath.Insert(i,evalue.m_arrImagePath[0]);
		this->m_arrAssetPath.Insert(i,evalue.m_arrAssetPath[0]);
	}

}

