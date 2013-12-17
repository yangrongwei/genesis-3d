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
    @class Debug::DebugPageHandler
    
    Http request handler for the Debug subsystem.
*/
#include "http/httprequesthandler.h"
#include "timing/time.h"

//------------------------------------------------------------------------------
namespace Debug
{
class DebugPageHandler : public Http::HttpRequestHandler
{
    __DeclareClass(DebugPageHandler);
public:
    /// constructor
    DebugPageHandler();
    /// handle a http request
    virtual void HandleRequest(const GPtr<Http::HttpRequest>& request);

protected:
    /// compute the min, max and average time from an array of times
    void ComputeMinMaxAvgTimes(const Util::Array<Timing::Time>& times, Timing::Time& outMin, Timing::Time& outMax, Timing::Time& outAvg) const;
    /// compute min, max and average values from an array of counter samples
    void ComputeMinMaxAvgCounts(const Util::Array<int>& counterValues, int& outMin, int& outMax, int& outAvg) const;

private:
    /// handle HTTP request for a debug timer
    void HandleTimerRequest(const Util::String& timerName, const GPtr<Http::HttpRequest>& request);
    /// handle HTTP request for a debug counter
    void HandleCounterRequest(const Util::String& counterName, const GPtr<Http::HttpRequest>& request);
    /// handle HTTP request to render a timer chart
    void HandleTimerChartRequest(const Util::String& timerName, const GPtr<Http::HttpRequest>& request);
    /// handle HTTP request to render a counter char
    void HandleCounterChartRequest(const Util::String& counterName, const GPtr<Http::HttpRequest>& request);
    /// handle HTTP request to sort table
    void HandleTableSortRequest(const Util::String& columnName, const GPtr<Http::HttpRequest>& request);

    Util::String sortByColumn;
};

} // namespace Debug
//------------------------------------------------------------------------------

