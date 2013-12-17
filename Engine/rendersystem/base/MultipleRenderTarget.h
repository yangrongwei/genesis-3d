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

#ifndef MULTIPLERENDERTARGET_H_
#define MULTIPLERENDERTARGET_H_

#include "RenderCommandType.h"
#include "RenderDeviceTypes.h"

namespace RenderBase
{
	class RenderTarget;

	const IndexT MaxNumRenderTargets = 4;

	class MultipleRenderTarget : public RenderCommandType
{
	__DeclareClass(MultipleRenderTarget);

public:

	MultipleRenderTarget();

	virtual ~MultipleRenderTarget();

	/// set rendertarget
	void AddRenderTarget(const GPtr<RenderTarget>& rt);
	/// get rendertarget at index
	const GPtr<RenderTarget>& GetRenderTarget(IndexT i) const;
	/// get number of rendertargets used
	SizeT GetNumRendertargets() const;

protected:

	GPtr<RenderTarget>      m_RenderTargets[MaxNumRenderTargets];
	SizeT                  m_NumRenderTargets;
};

inline const GPtr<RenderTarget>& MultipleRenderTarget::GetRenderTarget(IndexT i) const
{
	n_assert( i < m_NumRenderTargets );
	return m_RenderTargets[i];
}

inline SizeT MultipleRenderTarget::GetNumRendertargets() const
{
	return m_NumRenderTargets;
}

}




#endif