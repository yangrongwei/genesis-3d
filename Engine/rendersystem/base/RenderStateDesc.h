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
#ifndef RENDERSTATEDESC_H_
#define RENDERSTATEDESC_H_
#include "RenderCommandType.h"
#include "RenderDeviceTypes.h"
namespace RenderBase
{


	class RenderStateDesc : public RenderCommandType
	{
	public:
		enum RenderStateFlag
		{
			eInvalidRenderState = 0,
			eRenderSamplerState = 1,
			eRenderDepthAndStencilState = 2,
			eRenderBlendState = 4,
			eRenderRasterizerState = 8,
			eAllRenderState = (eRenderSamplerState|eRenderDepthAndStencilState|eRenderBlendState|eRenderRasterizerState)
		};

		__DeclareSubClass(RenderStateDesc,RenderCommandType)
	public:
		RenderStateDesc();
		virtual ~RenderStateDesc();
		void Setup();

		void SetSamplerState(const DeviceSamplerState& state);
		const DeviceSamplerState& GetSamplerState() const;

		void SetBlendState(const DeviceBlendState& state);
		const DeviceBlendState& GetBlendState() const;

		void SetRasterizerState(const DeviceRasterizerState& state);
		const DeviceRasterizerState& GetRasterizerState() const;

		void SetDepthAndStencilState(const DeviceDepthAndStencilState& state);
		const DeviceDepthAndStencilState& GetDepthAndStencilState() const;

		void SetUpdateFlag(unsigned int flag);
		unsigned int GetUpdateFlag() const;
	private:
		DeviceSamplerState		m_renderSamplerState;
		DeviceBlendState		m_renderBlendState;
		DeviceRasterizerState	m_renderRasterizerState;
		DeviceDepthAndStencilState	m_renderDepthStencilState;
		unsigned int			m_updateFlag;
	};

	inline void
		RenderStateDesc::SetSamplerState(const DeviceSamplerState& state)
	{
		m_renderSamplerState = state;
	}

	inline const DeviceSamplerState&
		RenderStateDesc::GetSamplerState() const
	{
		return m_renderSamplerState;
	}

	inline void
		RenderStateDesc::SetBlendState(const DeviceBlendState& state)
	{
		m_renderBlendState = state;
		m_updateFlag |= eRenderBlendState;
	}

	inline const DeviceBlendState&
		RenderStateDesc::GetBlendState() const
	{
		return m_renderBlendState;
	}

	inline void
		RenderStateDesc::SetRasterizerState(const DeviceRasterizerState& state)
	{
		m_renderRasterizerState = state;
		m_updateFlag |= eRenderRasterizerState;
	}

	inline const DeviceRasterizerState&
		RenderStateDesc::GetRasterizerState() const
	{
		return m_renderRasterizerState;
	}

	inline void
		RenderStateDesc::SetDepthAndStencilState(const DeviceDepthAndStencilState& state)
	{
		m_renderDepthStencilState = state;
		m_updateFlag |= eRenderDepthAndStencilState;
	}

	inline const DeviceDepthAndStencilState&
		RenderStateDesc::GetDepthAndStencilState() const
	{
		return m_renderDepthStencilState;
	}

	inline void
		RenderStateDesc::SetUpdateFlag(unsigned int flag)
	{
		m_updateFlag = flag;
	}
	inline unsigned int
		RenderStateDesc::GetUpdateFlag() const
	{
		return m_updateFlag;
	}
}
#endif
