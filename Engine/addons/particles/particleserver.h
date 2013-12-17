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
#ifndef __particleserver_H__
#define __particleserver_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particlesystem.h"

namespace Particles
{
	/// for Serialization. !!!!Do not create extern!!!!!
	class ParticleSystemContainer: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass( ParticleSystemContainer ); 
	public:
		ParticleSystemContainer(){ };
		virtual ~ParticleSystemContainer(){ };

		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		Util::Dictionary<Util::StringAtom, ParticleSystemPtr> mContainer;
	};

	class ParticleServer: public Core::RefCounted
	{
		__DeclareClass(ParticleServer);
		__DeclareImageSingleton(ParticleServer);
	public:
		ParticleServer();
		virtual ~ParticleServer();

		//-------------------------------manage template-----------------------------------------
		/**
		void OpenTemplateFile( Util::String filePath = Util::String("atp:particle.atp") );

		void SaveTemplateFile( Util::String filePath = Util::String("atp:particle.atp") );

		ParticleSystemPtr CreateFromTemplate(const Util::StringAtom& tplname);

		SizeT GetTemplateCount(void) const;

		bool HasTemplate(const Util::StringAtom&) const;

		const ParticleSystemPtr& GetTemplate(IndexT index ) const;  

		const ParticleSystemPtr& FindTemplate(const Util::StringAtom& name) const;

		// add template . if exist, replace; Else add a new template.
		bool AddTemplate(const Util::StringAtom& tplname, const ParticleSystemPtr& parSystem );

		// Remove template. 
		void RemoveTemplate( const Util::StringAtom& tplName );
		**/

		//-------------------------------manage active ParticleSystem -----------------------------------------
		SizeT GetActiveCount(void) const;

		//--------------------------------update----------------------------------------
		void Update();

	protected:
		void _attachParticleSystem( const ParticleSystemPtr& particleSystem );
		void _deattachParticleSystem( const ParticleSystemPtr& particleSystem );


		void _RegisterDynamicClass() const;
	protected:

		//GPtr<ParticleSystemContainer> mTemplates;

		Util::Array<ParticleSystemPtr> mActives;

		Util::Array<ParticleJobPtr> mJobs;

		friend class ParticleSystem;
	};

	/***
	//------------------------------------------------------------------------
	inline
	SizeT 
	ParticleServer::GetTemplateCount(void) const
	{
	return mTemplates->mContainer.Size();
	}
	//------------------------------------------------------------------------
	inline
	bool
	ParticleServer::HasTemplate(const Util::StringAtom& name) const
	{
	return mTemplates->mContainer.FindIndex( name ) != InvalidIndex;
	}
	//------------------------------------------------------------------------
	inline
	const ParticleSystemPtr& 
	ParticleServer::GetTemplate(IndexT index ) const
	{
	if ( index >= 0 && index < mTemplates->mContainer.Size() )
	{
	return mTemplates->mContainer.ValueAtIndex( index );
	}
	else
	{
	return ParticleSystem::NullParSystem;
	}
	}
	//------------------------------------------------------------------------
	inline
	const ParticleSystemPtr& 
	ParticleServer::FindTemplate(const Util::StringAtom& name) const
	{
	IndexT findIndex = mTemplates->mContainer.FindIndex( name );
	return GetTemplate( findIndex );
	}
	***/
	//------------------------------------------------------------------------
	inline
		SizeT 
		ParticleServer::GetActiveCount(void) const
	{
		return mActives.Size();
	}


}












#endif // __particleserver_H__
