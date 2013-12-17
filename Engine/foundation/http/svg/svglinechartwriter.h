/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
#pragma once
//------------------------------------------------------------------------------
/**
    @class Http::SvgLineChartWriter
    
    Specialized SVG page writer which draws a line chart diagrams.

*/
#include "http/svg/svgpagewriter.h"
#include "timing/time.h"

//------------------------------------------------------------------------------
namespace Http
{
class SvgLineChartWriter : public SvgPageWriter
{
    __DeclareClass(SvgLineChartWriter);
public:
    /// constructor
    SvgLineChartWriter();
    /// destructor
    virtual ~SvgLineChartWriter();
    
    /// begin writing to the stream
    virtual bool Open();
    /// setup the x axis
    void SetupXAxis(const Util::String& axisName, const Util::String& unitName, int minVal, int maxVal);
    /// setup the y axis
    void SetupYAxis(const Util::String& axisName, const Util::String& unitName, float minVal, float maxVal);
    /// add a value track
    void AddTrack(const Util::String& name, const Util::String& color, const Util::Array<float>& values);
    /// add a value track with timestamps
    void AddTrack(const Util::String& name, const Util::String& color, const Util::Array<float>& values, const Util::Array<Timing::Tick>& timeStamps);
    /// draw diagram
    void Draw();

private:
    struct Track
    {
        Util::String name;
        Util::String color;
        Util::Array<float> values;
        Util::Array<Timing::Tick> times;
    };

    Util::String xAxisName;
    Util::String xAxisUnitName;
    int xAxisMinVal;
    int xAxisMaxVal;
    Util::String yAxisName;
    Util::String yAxisUnitName;
    float yAxisMinVal;
    float yAxisMaxVal;
    Util::Array<Track> tracks;
};

} // namespace Http
//------------------------------------------------------------------------------
   