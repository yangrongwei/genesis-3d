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
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;
namespace ScriptGUI
{
    internal class ImageBox : Widget
    {
        internal ImageBox(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.ImageBox)
        {

        }
        internal ImageBox(Instance inst, FString name, Layout parent, WidgetType type)
            : base(inst, name, parent, type)
        {

        }

        //------------------------------------------------------------------------------//
        // The interface with support of resources
        //------------------------------------------------------------------------------//
        /** Select current items resource used in ImageBox
            @param _name Resource name
            @return false if resource with such name not exist
        */
        internal bool SetItemResource(string name)
        {
            return ICall_setItemResource(mInstance.Ptr, name);
        }
        /** Select current item group */
        internal void SetItemGroup(string name)
        {
            ICall_setItemGroup(mInstance.Ptr, name);
        }
        /** Select current item mane */
        internal void SetItemName(string name)
        {
            ICall_setItemName(mInstance.Ptr, name);
        }

        //------------------------------------------------------------------------------//
        // The simple interface
        //------------------------------------------------------------------------------//

        /* Set texture and size of image _tile
            @param _texture file name or texture name
            @param _coord - part of texture where we take tiles
            @param _tile size
        */
        internal void SetImageInfo(string texture, IntCoord coord, IntSize tile)
        {
            ICall_setImageInfo(mInstance.Ptr, texture, ref coord, ref tile);
        }

		/* Set texture
			@param _texture file name or texture name
		*/
        internal void SetImageTexture(string value)
        {
            ICall_setImageTexture(mInstance.Ptr, value);
        }

		/** Set _rect - part of texture where we take tiles */
        internal void SetImageRect(IntRect value)
        {
            ICall_setImageRect(mInstance.Ptr, ref value);
        }

		/** Set _coord - part of texture where we take tiles */
        internal void SetImageCoord(IntCoord value)
        {
            ICall_setImageCoord(mInstance.Ptr, ref value);
        }

		/** Set _tile size */
        internal void SetImageTile(IntSize value)
        {
            ICall_setImageTile(mInstance.Ptr, ref value);
        }

		/** Set current tile index
			@param index - tile index
			@remarks Tiles in file start numbering from left to right and from top to bottom.
			\n For example:\n
			<pre>
				+---+---+---+
				| 0 | 1 | 2 |
				+---+---+---+
				| 3 | 4 | 5 |
				+---+---+---+
			</pre>
		*/
        internal void SetImageIndex(int index)
        {
            ICall_setImageIndex(mInstance.Ptr, (uint)index);
        }
		/** Get current tile index */
        internal int GetImageIndex()
        {
            return (int)ICall_getImageIndex(mInstance.Ptr);
        }


        //------------------------------------------------------------------------------//
		// The expanded interface
		//------------------------------------------------------------------------------//

		//! Get number of items
        internal int GetItemCount()
        {
            return (int)ICall_getItemCount(mInstance.Ptr);
        }

		//! Select specified index
        internal void SetItemSelect(int index)
        {
            ICall_setItemSelect(mInstance.Ptr, (uint)index);
        }
		//! Get index of selected item (ITEM_NONE if none selected)
        internal int GetItemSelect()
        {
            uint temp = ICall_getItemSelect(mInstance.Ptr);

            return (temp >= int.MaxValue) ? -1 : (int)temp;
        }
		//! Reset item selection
        internal void ResetItemSelect()
        {
            ICall_resetItemSelect(mInstance.Ptr);
        }

		//! Insert an item into a list at a specified position
        internal void InsertItem(int index, IntCoord item)
        {
            ICall_insertItem(mInstance.Ptr, (uint)index, ref item);
        }
		//! Add an item to the end of a list
        internal void AddItem(IntCoord item)
        {
            ICall_addItem(mInstance.Ptr, ref item);
        }
		//! Replace an item at a specified position
        internal void SetItem(int index, IntCoord item)
        {
            ICall_setItem(mInstance.Ptr, (uint)index, ref item);
        }

		//! Delete item at a specified position
        internal void DeleteItem(int index)
        {
            ICall_deleteItem(mInstance.Ptr, (uint)index);
        }
		//! Delete all items
        internal void DeleteAllItems()
        {
            ICall_deleteAllItems(mInstance.Ptr);
        }

		// работа с фреймами анимированных индексов
		/** Add frame
			@param index Image item index
			@param _item Frame coordinates at image texture
		*/
        internal void AddItemFrame(int index, IntCoord item)
        {
            ICall_addItemFrame(mInstance.Ptr, (uint)index,ref item);
        }

		/** Insert frame
			@param index Image item index
			@param indexFrame Frame index where we insert frame
			@param _item Frame coordinates at image texture
		*/
        internal void InsertItemFrame(int index, int indexFrame, IntCoord item)
        {
            ICall_insertItemFrame(mInstance.Ptr, (uint)index, (uint)indexFrame, ref item);
        }

		/** Add copy of frame (similar to ImageBox::addItemFrame but we copy frame coordinates)
			@param index Image item index
			@param indexSourceFrame Frame index of frame that we copying
		*/
        internal void AddItemFrameDublicate(int index, int indexSourceFrame)
        {
            ICall_addItemFrameDublicate(mInstance.Ptr, (uint)index, (uint)indexSourceFrame);
        }

		/** Insert copy of frame (similar to ImageBox::insertItemFrame but we copy frame coordinates)
			@param index Image item index
			@param indexFrame Frame index where we insert frame
			@param indexSourceFrame Frame index of frame that we copying
		*/
        internal void InsertItemFrameDublicate(int index, int indexFrame, int indexSourceFrame)
        {
            ICall_insertItemFrameDublicate(mInstance.Ptr, (uint)index, (uint)indexFrame, (uint)indexSourceFrame);
        }

		/** Change frame
			@param index Image item index
			@param indexFrame Frame index to change
			@param _item Frame coordinates at image texture
		*/
        internal void SetItemFrame(int index, int indexFrame, IntCoord item)
        {
            ICall_setItemFrame(mInstance.Ptr, (uint)index, (uint)indexFrame, ref item);
        }

		/** Delete frame
			@param index Image item index
			@param indexFrame Frame index that we delete
		*/
        internal void DeleteItemFrame(int index, int indexFrame)
        {
            ICall_deleteItemFrame(mInstance.Ptr, (uint)index, (uint)indexFrame);
        }

		/** Delete all frames
			@param index Image item index
		*/
        internal void DeleteAllItemFrames(int index)
        {
            ICall_deleteAllItemFrames(mInstance.Ptr, (uint)index);
        }

		/** Set item frame rate
			@param index Image item index
			@param _rate Duration of one frame in seconds
		*/
        internal void SetItemFrameRate(int index, float rate)
        {
            ICall_setItemFrameRate(mInstance.Ptr, (uint)index, rate);
        }

		/** Get item frame rate
			@param index Image item index
		*/
        internal float GetItemFrameRate(int index)
        {
            return ICall_getItemFrameRate(mInstance.Ptr, (uint)index);
        }



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_setItemResource(IntPtr widget_ptr, String value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemGroup(IntPtr widget_ptr, String value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemName(IntPtr widget_ptr, String value);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageInfo(IntPtr widget_ptr, String texture, ref IntCoord coord, ref IntSize tile);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageTexture(IntPtr widget_ptr, String texture);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageRect(IntPtr widget_ptr, ref IntRect value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageCoord(IntPtr widget_ptr, ref IntCoord coord);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageTile(IntPtr widget_ptr, ref IntSize tile);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setImageIndex(IntPtr widget_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getImageIndex(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getItemCount(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemSelect(IntPtr widget_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_getItemSelect(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_resetItemSelect(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_insertItem(IntPtr widget_ptr, uint index, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_addItem(IntPtr widget_ptr, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItem(IntPtr widget_ptr, uint index, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_deleteItem(IntPtr widget_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_deleteAllItems(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_addItemFrame(IntPtr widget_ptr, uint index, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_insertItemFrame(IntPtr widget_ptr, uint index, uint indexFrame, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_addItemFrameDublicate(IntPtr widget_ptr, uint index, uint indexSourceFrame);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_insertItemFrameDublicate(IntPtr widget_ptr, uint index, uint indexFrame, uint indexSourceFrame);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemFrame(IntPtr widget_ptr, uint index, uint indexFrame, ref IntCoord item);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_deleteItemFrame(IntPtr widget_ptr, uint index, uint indexFrame);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_deleteAllItemFrames(IntPtr widget_ptr, uint index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setItemFrameRate(IntPtr widget_ptr, uint index, float rate);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_getItemFrameRate(IntPtr widget_ptr, uint index);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_(IntPtr widget_ptr);

        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern private static void ICall_(IntPtr widget_ptr);

    }
}
