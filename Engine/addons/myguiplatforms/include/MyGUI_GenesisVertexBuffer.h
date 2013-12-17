/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#ifndef __MYGUI_GENESIS_VERTEX_BUFFER_H__
#define __MYGUI_GENESIS_VERTEX_BUFFER_H__


#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_VertexData.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "graphicsystem/base/GraphicBufferData.h"

namespace MyGUI
{

	class GenesisVertexBuffer :
		public IVertexBuffer
	{
	public:
		GenesisVertexBuffer();
		virtual ~GenesisVertexBuffer();

		virtual void setVertexCount(size_t _count);
		virtual size_t getVertexCount();

		virtual Vertex* lock();
		virtual void unlock();
		RenderBase::PrimitiveHandle GetPrimitiveHandle() const;
		void resizeVertexBuffer();
	private:
		void createVertexBuffer();
		void destroyVertexBuffer();

	private:
		size_t mVertexCount;
		size_t mNeedVertexCount;
		Graphic::DynamicBuffer mDynamicBuffer;
		size_t mVertexBufferSize;
		RenderBase::PrimitiveHandle		m_primHandle;

		//Ogre::RenderOperation mRenderOperation;
		//Ogre::HardwareVertexBufferSharedPtr mVertexBuffer;


	};
	inline RenderBase::PrimitiveHandle GenesisVertexBuffer::GetPrimitiveHandle() const
	{
		return m_primHandle;
	}

} // namespace MyGUI

#endif // __MYGUI_GENESIS_VERTEX_BUFFER_H__
