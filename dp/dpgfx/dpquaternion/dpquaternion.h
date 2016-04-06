/*

*/

#ifndef dpquaternion_h
#define dpquaternion_h

#include "../dpmatrix/dpmatrix.h"

namespace dp
{

    struct dpquaternion_inner
    {
        union
        {
            float fv[ 4 ];
            dpxyzw sv;
        };
    };

    class dpquaternion
    {

    private:

        dpquaternion_inner f;

    protected:

    public:

        //ctor
        dpquaternion( void );
        //dtor
        virtual ~dpquaternion( void );
        //get raw data
        dpquaternion_inner *getData( void );
        //set identity
        void setIdentity( void );
        //set position
        void setPosition( float x, float y, float z, float w );
        //set angle
        void setAngle( float x, float y, float z );
        //set angle
        void setAngle( dpxyzw *x );
        //get angle
        void getAngle( dpxyzw *x );
        //slerp
        void slerp( dpquaternion *a, dpquaternion *b, float r );

    };

};

#endif
