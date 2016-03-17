
/*

*/

#include <stdint.h>

namespace dp
{

    struct dpvertex
    {
        struct
        {
            float x, y, z, w;
        } vert, norm;
        struct
        {
            float s, t;
        } texcoord[ 2 ];
    };

};

