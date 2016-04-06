
/*

*/

#ifndef dpvertex_h
#define dpvertex_h

#include <stdint.h>

namespace dp
{

    struct dpxyzw
    {
        float x, y, z, w;
    };

    struct dpst
    {
        float s, t;
    };

    struct dpvertex
    {
        dpxyzw vert, norm;
        dpst texcoord[ 2 ];
    };

};

#endif
