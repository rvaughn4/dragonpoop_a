
/*

*/

#ifndef dpmatrix_h
#define dpmatrix_h

#include "../dpvertex/dpvertex.h"

namespace dp
{

    class dpquaternion;

    struct dpmatrix_col
    {
        union
        {
            struct
            {
                float _1, _2, _3, _4;
            } row;
            float rows[ 4 ];
        };
    };

    struct dpmatrix_int
    {
        union
        {
            float fv[ 16 ];
            float f4v[ 4 ][ 4 ];
            dpmatrix_col cols[ 4 ];
            struct
            {
                dpmatrix_col _1, _2, _3, _4;
            } col;
        };
    };

    class dpmatrix
    {

    private:

        dpmatrix_int values;

    protected:

    public:

        //ctor
        dpmatrix( void );
        //dtor
        ~dpmatrix( void );
        //copy
        void copy( dpmatrix *m );
        //load identity
        void setIdentity( void );
        //load raw matrix from pointer
        void loadRaw4by4( float *fv );
        //get raw matrix pointer
        float *getRaw4by4( void );
        //multiply matrix
        void multiply( dpmatrix *m );
        //multiply translation to matrix
        void translate( float x, float y, float z );
        //multiply rotation to matrix
        void rotateX( float deg );
        //multiply rotation to matrix
        void rotateY( float deg );
        //multiply rotation to matrix
        void rotateZ( float deg );
        //multiply rotation to matrix
        void rotateXrad( float rad );
        //multiply rotation to matrix
        void rotateYrad( float rad );
        //multiply rotation to matrix
        void rotateZrad( float rad );
        //multiply scaling to matrix
        void scale( float x, float y, float z );
        //set ortho matrix
        void setOrtho( float x0, float y0, float z0, float x1, float y1, float z1 );
        //set perspective matrix
        void setPerspective( float x0, float y0, float z0, float x1, float y1, float z1, float fov );
        //set tranlation matrix
        void setTranslation( float x, float y, float z );
        //set rotation matrix
        void setRotationX( float deg );
        //set rotation matrix
        void setRotationY( float deg );
        //set rotation matrix
        void setRotationZ( float deg );
        //set rotation matrix
        void setRotationXrad( float rad );
        //set rotation matrix
        void setRotationYrad( float rad );
        //set rotation matrix
        void setRotationZrad( float rad );
        //set scaling matrix
        void setScaling( float x, float y, float z );
        //transform
        void transform( float *px, float *py, float *pz, float *pw );
        //transform
        void transform( dpxyzw *p );
        //inverse transform
        void itransform( float *px, float *py, float *pz, float *pw );
        //inverse transform
        void itransform( dpxyzw *p );
        //rotate ( Z * Y ) * X
        void rotateRad( float x, float y, float z );
        //rotate ( Z * Y ) * X
        void rotate( float x, float y, float z );
        //set angle (radians) and position
        void setAngleRadAndPosition( dpxyzw *angles, dpxyzw *pos );
        //set this to inverse of matrix
        void inverse( dpmatrix *m );
        //returns position
        void getPosition( dpxyzw *p );
        //sets position
        void setPosition( dpxyzw *p );
        //create matrix from quaternion
        void setQuat( dpquaternion *q );
        //find angles
        void getAngles( dpxyzw *o );

    };

};

#endif
