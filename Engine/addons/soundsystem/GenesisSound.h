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
#ifndef GENESISSOUND_H
#define GENESISSOUND_H

typedef unsigned int              GENESISOUND_MODE;
typedef unsigned int              GENESIS_FILE_FORMAT;

#define GENESISSOUND_DEFAULT                   0x00000000 
#define GENESISSOUND_LOOP_OFF                  0x00000001 
#define GENESISSOUND_LOOP_NORMAL               0x00000002 
#define GENESISSOUND_LOOP_BIDI                 0x00000004 
#define GENESISSOUND_2D                        0x00000008 
#define GENESISSOUND_3D                        0x00000010 
#define GENESISSOUND_HARDWARE                  0x00000020 
#define GENESISSOUND_SOFTWARE                  0x00000040 
#define GENESISSOUND_CREATESTREAM              0x00000080 
#define GENESISSOUND_CREATESAMPLE              0x00000100 
#define GENESISSOUND_CREATECOMPRESSEDSAMPLE    0x00000200 
#define GENESISSOUND_OPENUSER                  0x00000400 
#define GENESISSOUND_OPENMEMORY                0x00000800 
#define GENESISSOUND_OPENMEMORY_POINT          0x10000000 
#define GENESISSOUND_OPENRAW                   0x00001000 
#define GENESISSOUND_OPENONLY                  0x00002000 
#define GENESISSOUND_ACCURATETIME              0x00004000 
#define GENESISSOUND_MPEGSEARCH                0x00008000 
#define GENESISSOUND_NONBLOCKING               0x00010000 
#define GENESISSOUND_UNIQUE                    0x00020000 
#define GENESISSOUND_3D_HEADRELATIVE           0x00040000 
#define GENESISSOUND_3D_WORLDRELATIVE          0x00080000 
#define GENESISSOUND_3D_INVERSEROLLOFF         0x00100000 
#define GENESISSOUND_3D_LINEARROLLOFF          0x00200000 
#define GENESISSOUND_3D_LINEARSQUAREROLLOFF    0x00400000 
#define GENESISSOUND_3D_CUSTOMROLLOFF          0x04000000 
#define GENESISSOUND_3D_IGNOREGEOMETRY         0x40000000 
#define GENESISSOUND_UNICODE                   0x01000000 
#define GENESISSOUND_IGNORETAGS                0x02000000 
#define GENESISSOUND_LOWMEM                    0x08000000 
#define GENESISSOUND_LOADSECONDARYRAM          0x20000000 
#define GENESISSOUND_VIRTUAL_PLAYFROMSTART     0x80000000 

enum DistanMode
{
	EXPONENT_DISTANCE = 0,
	LINEAR_MODE = 1,
};

#define GENESIS_FILE_FORMAT_MP3           0x00000001
#define GENESIS_FILE_FORMAT_OGG           0x00000002
#define GENESIS_FILE_FORMAT_WAV			  0x00000004



#endif //GENESISSOUND_H