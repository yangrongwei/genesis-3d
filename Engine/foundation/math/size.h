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

#ifndef MATH_SIZE_H
#define MATH_SIZE_H

namespace Math
{
	template<typename T>
	class tsize
	{
	public:
		T width;
		T height;

		tsize() :
		width(0),
			height(0)
		{
		}

		tsize(T const& _width, T const& _height) :
		width(_width),
			height(_height)
		{
		}

		tsize(tsize const& _obj) :
		width(_obj.width),
			height(_obj.height)
		{
		}

		tsize& operator -= (tsize const& _obj)
		{
			width -= _obj.width;
			height -= _obj.height;
			return *this;
		}

		tsize& operator += (tsize const& _obj)
		{
			width += _obj.width;
			height += _obj.height;
			return *this;
		}

		tsize operator - (tsize const& _obj) const
		{
			return tsize(width - _obj.width, height - _obj.height);
		}

		tsize operator + (tsize const& _obj) const
		{
			return tsize(width + _obj.width, height + _obj.height);
		}

		tsize operator * (tsize const& _obj) const
		{
			return tsize(width * _obj.width, height * _obj.height);
		}

		tsize operator * (T const& _obj) const
		{
			return tsize(width * _obj, height * _obj);
		}

		tsize <float>operator / (const T& value) const
		{
			return tsize(width / value, height / value);
		}

		tsize& operator = (tsize const& _obj)
		{
			width = _obj.width;
			height = _obj.height;
			return *this;
		}

		template<typename U>
		tsize& operator = (tsize<U> const& _obj)
		{
			width = _obj.width;
			height = _obj.height;
			return *this;
		}

		bool operator == (tsize const& _obj) const
		{
			return ((width == _obj.width) && (height == _obj.height));
		}

		bool operator != (tsize const& _obj) const
		{
			return !((width == _obj.width) && (height == _obj.height));
		}

		void clear()
		{
			width = height = 0;
		}

		void set(T const& _width, T const& _height)
		{
			width = _width;
			height = _height;
		}

		void swap(tsize& _value)
		{
			tsize tmp = _value;
			_value = *this;
			*this = tmp;
		}

		bool empty() const
		{
			return ((width == 0) && (height == 0));
		}
	};

	typedef tsize<float> sizef;
	typedef tsize<int> sizei;
}


#endif //MATH_SIZE_H