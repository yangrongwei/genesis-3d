#pragma once
/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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

#include "core/types.h"
#include "util/array.h"

//------------------------------------------------------------------------------
namespace Util
{
template<class VALUETYPE> class SimpleTree
{
public:
    /// public node class
    class Node
    {
    public:
        /// default constructor
        Node();
        /// constructor with parent and value
        Node(const Node& parent, const VALUETYPE& val);
        /// destructor
        ~Node();
        /// increment refcount
        void AddRef();
        /// decrement refcount
        void Release();
        /// get read-only child by index
        const Node& operator[](IndexT i) const;
        /// get read/write child by index
        Node& operator[](IndexT i);
        /// get read-only child element at index
        const Node& Child(IndexT i) const;
        /// get read/write child element at index
        Node& Child(IndexT i);
        /// return true if the node has a parent
        bool HasParent() const;
        /// read/write access to parent
        Node& Parent();
        /// read-only access to parent
        const Node& Parent() const;
        /// clear children
        void Clear();
        /// number of children
        SizeT Size() const;
        /// return true if empty
        bool IsEmpty() const;
        /// return first element
        Node& Front() const;
        /// return last element
        Node& Back() const;
        /// add element at back of array
        void Append(const VALUETYPE& val);
        /// erase at index
        void Erase(IndexT i);
        /// insert element before element at index
        void Insert(IndexT index, const VALUETYPE& val);
        /// find identical element (slow);
        IndexT Find(const VALUETYPE& val) const;
        /// read/write access to value
        VALUETYPE& Value();
        /// read-only access to value
        const VALUETYPE& Value() const;

    private:
        uint refCount;
        Node* parent;
        VALUETYPE value;
        Array<GPtr<Node> > children;
    };

    /// default constructor
    SimpleTree();
    /// read/write access to root element
    Node& Root();
    /// read-only access to root element
    const Node& Root() const;

private:
    Node rootNode;
};

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
SimpleTree<VALUETYPE>::Node::Node() :
    refCount(0),
    parent(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
SimpleTree<VALUETYPE>::Node::Node(const Node& p, const VALUETYPE& val) :
    refCount(0),    
    parent(const_cast<Node*>(&p)),
    value(val)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 != this->parent);
    #endif
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
SimpleTree<VALUETYPE>::Node::~Node()
{
    #if NEBULA3_BOUNDSCHECKS    
    n_assert(0 == this->refCount);
    #endif
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
void
SimpleTree<VALUETYPE>::Node::AddRef()
{
    ++this->refCount;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
void
SimpleTree<VALUETYPE>::Node::Release()
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(this->refCount > 0);
    #endif
    --this->refCount;
    if (this->refCount == 0)
    {
        n_delete(this);
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
const typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::operator[](IndexT i) const
{
    return *(this->children[i]);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::operator[](IndexT i)
{
    return *(this->children[i]);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
const typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Child(IndexT i) const
{
    return *(this->children[i]);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Child(IndexT i)
{
    return *(this->children[i]);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
bool
SimpleTree<VALUETYPE>::Node::HasParent() const
{
    return (0 != this->parent);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
const typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Parent() const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 != this->parent);
    #endif   
    return *this->parent;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Parent()
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 != this->parent);
    #endif
    return *this->parent;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
void
SimpleTree<VALUETYPE>::Node::Clear()
{
    this->children.Clear();
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
SizeT
SimpleTree<VALUETYPE>::Node::Size() const
{
    return this->children.Size();
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
bool
SimpleTree<VALUETYPE>::Node::IsEmpty() const
{
    return this->children.IsEmpty();
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Front() const
{
    return *(this->children.Front());
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Node::Back() const
{
    return *(this->children.Back());
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
void
SimpleTree<VALUETYPE>::Node::Append(const VALUETYPE& val)
{
    GPtr<Node> newNode = n_new(Node(*this, val));
    this->children.Append(newNode);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
void
SimpleTree<VALUETYPE>::Node::Erase(IndexT i)
{
    this->children.EraseIndex(i);
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
const VALUETYPE& 
SimpleTree<VALUETYPE>::Node::Value() const
{
    return this->value;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
VALUETYPE& 
SimpleTree<VALUETYPE>::Node::Value()
{
    return this->value;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
IndexT
SimpleTree<VALUETYPE>::Node::Find(const VALUETYPE& val) const
{
    IndexT i;
    SizeT num = this->children.Size();
    for (i = 0; i < num; i++)
    {
        if (val == this->children[i]->Value())
        {
            return i;
        }
    }
    return InvalidIndex;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
SimpleTree<VALUETYPE>::SimpleTree()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Root()
{
    return this->rootNode;
}

//------------------------------------------------------------------------------
/**
*/
template<class VALUETYPE>
const typename SimpleTree<VALUETYPE>::Node&
SimpleTree<VALUETYPE>::Root() const
{
    return this->rootNode;
}

} // namespace Util
//------------------------------------------------------------------------------
    