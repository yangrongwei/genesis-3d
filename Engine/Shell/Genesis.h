//
//  Genesis.h
//  GenesisEngineLib
//
//  Created by 宋 琦 on 13-9-18.
//  Copyright (c) 2013年 webJet. All rights reserved.
//

#ifndef GenesisEngineLib_Genesis_h
#define GenesisEngineLib_Genesis_h
#include <vector>


namespace EngineShell
{
    enum InputAciton
    {
        IA_DOWN = 0,
        IA_MOVE,
        IA_UP,
    };

    struct Pointf
    {
        float x,y;
    };

    typedef std::vector<Pointf> PointfVector;

    void InitEngine( const int& w, const int& h, const char* path,const char* appWritableDic, const char* scene );
    void Update();
    void TouchPoint( const PointfVector& points, const InputAciton& action );
    void OnResumed();
    void OnStopped();

}
#endif
