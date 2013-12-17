/****************************************************************************
Copyright (c) 2010,Radon Labs GmbH
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
#ifndef __observercontext_H__
#define __observercontext_H__

#include "core/refcounted.h"
#include "math/bbox.h"

//------------------------------------------------------------------------------
namespace Vis
{   
	class ObserverContext : public Core::RefCounted
	{
		__DeclareClass(ObserverContext);
	public:    
		enum ObserverCullingType
		{
			ViewProjectionMatrix = 0,	//	
			BoundingBox,			//	
			SeeAll,					//	
			InvalidObserverType
		};

		/// constructor
		ObserverContext();
		/// destructor
		virtual ~ObserverContext();   

		/// get observer culling type
		ObserverCullingType GetType() const;

		ObserverCullingType* GetTypeRef();

		/// ObserverCullingType = ProjectionMatrix
		void Setup( const Math::matrix44& viewProj, const Math::point& observerPos);

		/// ObserverCullingType = BoundingBox
		void Setup( const Math::bbox& box, const Math::point& observerPos );

		/// ObserverCullingType = SeeAll
		void SetupSeeAll( const Math::point& observerPos );

		/// get projection matrix
		const Math::matrix44& GetViewProjectionMatrix(void) const;  
		Math::matrix44& GetViewProjectionMatrixRef(void);

		/// get bbox  
		const Math::bbox& GetBoundingBox(void) const;
		Math::bbox& GetBoundingBoxRef(void);

		//  get Observer Position
		const Math::point& GetPosition(void) const;

		void SetUserData( Core::RefCounted* userData );

		const Core::RefCounted* GetUserData(void) const;


		Math::ClipStatus::Type ComputeClipStatus(const Math::bbox& boundingBox);

	protected: 
		Core::RefCounted* mUserData;
		ObserverCullingType mType;    
		Math::bbox mBoundingBox;    
		Math::matrix44 mViewProjection;
		Math::point mObserverPos;
	};
	//------------------------------------------------------------------------
	inline
	ObserverContext::ObserverCullingType 
	ObserverContext::GetType() const
	{
		return mType;
	}
	//------------------------------------------------------------------------
	inline
	ObserverContext::ObserverCullingType*
	ObserverContext::GetTypeRef()
	{
		return &mType;
	}
	//------------------------------------------------------------------------
	/// get projection matrix
	inline
	const Math::matrix44& 
	ObserverContext::GetViewProjectionMatrix() const
	{
		return mViewProjection;
	}
	//------------------------------------------------------------------------
	inline
	Math::matrix44& 
	ObserverContext::GetViewProjectionMatrixRef(void)
	{
		return mViewProjection;
	}
	//------------------------------------------------------------------------
	/// get bbox
	inline
	const Math::bbox& 
	ObserverContext::GetBoundingBox() const
	{
		return mBoundingBox;
	}
	//------------------------------------------------------------------------
	inline
	Math::bbox& 
	ObserverContext::GetBoundingBoxRef(void)
	{
		return mBoundingBox;
	}
	//------------------------------------------------------------------------
	//  get Observer Position
	inline
	const Math::point& 
	ObserverContext::GetPosition() const
	{
		return mObserverPos;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ObserverContext::SetUserData( Core::RefCounted* userData )
	{
		mUserData = userData; 
	}
	//------------------------------------------------------------------------
	inline
	const Core::RefCounted* 
	ObserverContext::GetUserData(void) const
	{
		return mUserData;
	}
} // namespace Vis
//------------------------------------------------------------------------------






#endif // __observercontext_H__

