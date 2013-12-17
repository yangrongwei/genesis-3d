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
#ifndef __visserver_H__
#define __visserver_H__

#include "core/refcounted.h"
#include "vis/visentity.h"
#include "vis/vissystems/vissystembase.h"
#include "vis/visquery.h"
#include "vis/visentity.h"
#include "core/singleton.h"
              
//------------------------------------------------------------------------------
namespace Vis
{    

class VisServer : public Core::RefCounted
{
	__DeclareClass(VisServer);
public:        
    /// constructor
    VisServer();
    /// destructor
    virtual ~VisServer();

    /// open
    void Open();
    /// close
    void Close();

    /**
    * AttachVisSystem  add a visible system.
    * @param: const GPtr<VisSystemBase> & system  
    * @return: void  
    * @see: 
    * @remark:  
    */
    void AttachVisSystem(const GPtr<VisSystemBase>& system);


    /**
    * AttachVisSystems  add a visible system array.
    * @param: const Util::Array<GPtr<VisSystemBase> > & systems  
    * @return: void  
    * @see: 
    * @remark:  
    */
    void AttachVisSystems(const Util::Array<GPtr<VisSystemBase> >& systems);

    /**
    * RemoveVisSystem  remove a visible system.
    * @param: const GPtr<VisSystemBase> & system  
    * @return: void  
    * @see: 
    * @remark:  
    */
    void RemoveVisSystem(const GPtr<VisSystemBase>& system);

	/**
	* GetVisSystems  get the visible system array.
	* @param: void  
	* @return: const Util::Array<GPtr<VisSystemBase> >&  
	* @see: 
	* @remark:  
	*/
	const Util::Array<GPtr<VisSystemBase> >& GetVisSystems(void);

	/**
	* RegisterVisEntity  
	* @param: const GPtr<VisEntity> & entity  
	* @param: IndexT VisibilitySystemIndex 
	* @return: void  
	* @see: 
	* @remark:  
	*/
	void RegisterVisEntity(const GPtr<VisEntity>& entity, IndexT VisibilitySystemIndex = InvalidIndex );

    /**
    * UnregisterVisEntity  
    * @param: const GPtr<VisEntity> & entity  
    * @param: IndexT VisibilitySystemIndex  InvalidIndex means all visible system.
    * @return: void  
    * @see: 
    * @remark:  
    */
    void UnregisterVisEntity(const GPtr<VisEntity>& entity, IndexT VisibilitySystemIndex = InvalidIndex );

    /** 
    * UpdateVisEntity 
    * @param: const GPtr<VisEntity> & entity  
    * @return: void  
    * @see: 
    * @remark:  
    */
    void UpdateVisEntity(const GPtr<VisEntity>& entity);

	/**
	* PerformVisQuery 
	* @param: const GPtr<ObserverContext> & observer  
	* @param: const Util::Array<IndexT> & systemIndex InvalidIndex means all visible system.
	* @return: GPtr<VisQuery> 
	* @see: 
	* @remark:  
	*/
	GPtr<VisQuery> PerformVisQuery(const GPtr<ObserverContext>& observer , 
		                                        const Util::Array<IndexT>& systemIndex );



	/**
	* PerformVisQuery 
	* @param: const Util::Array< GPtr<ObserverContext> > & observers    
	* @param: const Util::Array<IndexT> & systemIndex  
	* @param: Util::Array< GPtr<VisQuery> >& results
	* @return: void  
	* @see: 
	* @remark:  
	*/
	void PerformVisQuery( const Util::Array< GPtr<ObserverContext> >& observers , 
								 const Util::Array<IndexT>& systemIndex,
								 Util::Array< GPtr<VisQuery> >& results );


    /// on render debug
    void OnRenderDebug();

protected:
	GPtr<VisQuery> CreateVisQuery(const GPtr<ObserverContext>& observer , const Util::Array<IndexT>& systemIndex );

private:       
    bool mIsOpen;
    Util::Array<GPtr<VisSystemBase> > mVisibilitySystems;  
};

} // namespace Vis
//------------------------------------------------------------------------------





#endif // __visserver_H__



