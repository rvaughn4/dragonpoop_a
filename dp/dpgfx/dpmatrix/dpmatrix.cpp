
/*

*/

#include "dpmatrix.h"
#include "../dpquaternion/dpquaternion.h"
#include <math.h>

namespace dp
{

    //ctor
    dpmatrix::dpmatrix( void )
    {
        this->setIdentity();
    }

    //dtor
    dpmatrix::~dpmatrix( void )
    {

    }

    //copy
    void dpmatrix::copy( dpmatrix *m )
    {
        this->values = m->values;
    }

    //load identity
    void dpmatrix::setIdentity( void )
    {
        int i;
        for( i = 0; i < 16; i++ )
            this->values.fv[ i ] = 0;

        this->values.col._1.row._1 = 1;
        this->values.col._2.row._2 = 1;
        this->values.col._3.row._3 = 1;
        this->values.col._4.row._4 = 1;
    }

    //load raw matrix from pointer
    void dpmatrix::loadRaw4by4( float *fv )
    {
        unsigned int i;
        for( i = 0; i < 16; i++ )
            this->values.fv[ i ] = fv[ i ];
    }

    //get raw matrix pointer
    float *dpmatrix::getRaw4by4( void )
    {
        return this->values.fv;
    }

    //multiply matrix
    void dpmatrix::multiply( dpmatrix *m )
    {
        dpmatrix r;

        r.values.col._1.row._1 = this->values.col._1.row._1 * m->values.col._1.row._1 + this->values.col._2.row._1 * m->values.col._1.row._2 + this->values.col._3.row._1 * m->values.col._1.row._3 + this->values.col._4.row._1 * m->values.col._1.row._4;
        r.values.col._2.row._1 = this->values.col._1.row._1 * m->values.col._2.row._1 + this->values.col._2.row._1 * m->values.col._2.row._2 + this->values.col._3.row._1 * m->values.col._2.row._3 + this->values.col._4.row._1 * m->values.col._2.row._4;
        r.values.col._3.row._1 = this->values.col._1.row._1 * m->values.col._3.row._1 + this->values.col._2.row._1 * m->values.col._3.row._2 + this->values.col._3.row._1 * m->values.col._3.row._3 + this->values.col._4.row._1 * m->values.col._3.row._4;
        r.values.col._4.row._1 = this->values.col._1.row._1 * m->values.col._4.row._1 + this->values.col._2.row._1 * m->values.col._4.row._2 + this->values.col._3.row._1 * m->values.col._4.row._3 + this->values.col._4.row._1 * m->values.col._4.row._4;
        r.values.col._1.row._2 = this->values.col._1.row._2 * m->values.col._1.row._1 + this->values.col._2.row._2 * m->values.col._1.row._2 + this->values.col._3.row._2 * m->values.col._1.row._3 + this->values.col._4.row._2 * m->values.col._1.row._4;
        r.values.col._2.row._2 = this->values.col._1.row._2 * m->values.col._2.row._1 + this->values.col._2.row._2 * m->values.col._2.row._2 + this->values.col._3.row._2 * m->values.col._2.row._3 + this->values.col._4.row._2 * m->values.col._2.row._4;
        r.values.col._3.row._2 = this->values.col._1.row._2 * m->values.col._3.row._1 + this->values.col._2.row._2 * m->values.col._3.row._2 + this->values.col._3.row._2 * m->values.col._3.row._3 + this->values.col._4.row._2 * m->values.col._3.row._4;
        r.values.col._4.row._2 = this->values.col._1.row._2 * m->values.col._4.row._1 + this->values.col._2.row._2 * m->values.col._4.row._2 + this->values.col._3.row._2 * m->values.col._4.row._3 + this->values.col._4.row._2 * m->values.col._4.row._4;
        r.values.col._1.row._3 = this->values.col._1.row._3 * m->values.col._1.row._1 + this->values.col._2.row._3 * m->values.col._1.row._2 + this->values.col._3.row._3 * m->values.col._1.row._3 + this->values.col._4.row._3 * m->values.col._1.row._4;
        r.values.col._2.row._3 = this->values.col._1.row._3 * m->values.col._2.row._1 + this->values.col._2.row._3 * m->values.col._2.row._2 + this->values.col._3.row._3 * m->values.col._2.row._3 + this->values.col._4.row._3 * m->values.col._2.row._4;
        r.values.col._3.row._3 = this->values.col._1.row._3 * m->values.col._3.row._1 + this->values.col._2.row._3 * m->values.col._3.row._2 + this->values.col._3.row._3 * m->values.col._3.row._3 + this->values.col._4.row._3 * m->values.col._3.row._4;
        r.values.col._4.row._3 = this->values.col._1.row._3 * m->values.col._4.row._1 + this->values.col._2.row._3 * m->values.col._4.row._2 + this->values.col._3.row._3 * m->values.col._4.row._3 + this->values.col._4.row._3 * m->values.col._4.row._4;
        r.values.col._1.row._4 = this->values.col._1.row._4 * m->values.col._1.row._1 + this->values.col._2.row._4 * m->values.col._1.row._2 + this->values.col._3.row._4 * m->values.col._1.row._3 + this->values.col._4.row._4 * m->values.col._1.row._4;
        r.values.col._2.row._4 = this->values.col._1.row._4 * m->values.col._2.row._1 + this->values.col._2.row._4 * m->values.col._2.row._2 + this->values.col._3.row._4 * m->values.col._2.row._3 + this->values.col._4.row._4 * m->values.col._2.row._4;
        r.values.col._3.row._4 = this->values.col._1.row._4 * m->values.col._3.row._1 + this->values.col._2.row._4 * m->values.col._3.row._2 + this->values.col._3.row._4 * m->values.col._3.row._3 + this->values.col._4.row._4 * m->values.col._3.row._4;
        r.values.col._4.row._4 = this->values.col._1.row._4 * m->values.col._4.row._1 + this->values.col._2.row._4 * m->values.col._4.row._2 + this->values.col._3.row._4 * m->values.col._4.row._3 + this->values.col._4.row._4 * m->values.col._4.row._4;

        this->loadRaw4by4( r.values.fv );
    }

    //multiply translation to matrix
    void dpmatrix::translate( float x, float y, float z )
    {
        dpmatrix m;
        m.setTranslation( x, y, z );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateX( float deg )
    {
        dpmatrix m;
        m.setRotationX( deg );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateY( float deg )
    {
        dpmatrix m;
        m.setRotationY( deg );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateZ( float deg )
    {
        dpmatrix m;
        m.setRotationZ( deg );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateXrad( float rad )
    {
        dpmatrix m;
        m.setRotationXrad( rad );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateYrad( float rad )
    {
        dpmatrix m;
        m.setRotationYrad( rad );
        this->multiply( &m );
    }

    //multiply rotation to matrix
    void dpmatrix::rotateZrad( float rad )
    {
        dpmatrix m;
        m.setRotationZrad( rad );
        this->multiply( &m );
    }

    //multiply scaling to matrix
    void dpmatrix::scale( float x, float y, float z )
    {
        dpmatrix m;
        m.setScaling( x, y, z );
        this->multiply( &m );
    }

    //set ortho matrix
    void dpmatrix::setOrtho( float x0, float y0, float z0, float x1, float y1, float z1 )
    {
        this->setIdentity();

        this->values.col._1.row._1 = 2.0f / ( x1 - x0 );
        this->values.col._2.row._2 = 2.0f / ( y1 - y0 );
        this->values.col._3.row._3 = -2.0f / ( z1 - z0 );
        this->values.col._4.row._1 = -( x1 + x0 ) / ( x1 - x0 );
        this->values.col._4.row._2 = -( y1 + y0 ) / ( y1 - y0 );
        this->values.col._4.row._3 = -( z1 + z0 ) / ( z1 - z0 );
        this->values.col._4.row._4 = 1.0f;
    }

    //set perspective matrix
    void dpmatrix::setPerspective( float x0, float y0, float z0, float x1, float y1, float z1, float fov )
    {
        float aspect;

        this->setIdentity();

        fov = fov * 3.14f / 180.0f;
        fov = 1.0f / tan( fov * 0.5f );
        aspect = fabs( ( x1 - x0 ) / ( y1 - y0 ) );

        this->values.col._1.row._1 = fov / aspect;
        this->values.col._2.row._2 = fov;
        this->values.col._3.row._3 = ( z1 + z0 ) / ( z0 - z1 );
        this->values.col._4.row._3 = ( 2.0f * z1 * z0 ) / ( z0 - z1 );
        this->values.col._3.row._4 = -1.0f;
    }

    //set tranlation matrix
    void dpmatrix::setTranslation( float x, float y, float z )
    {
        this->setIdentity();

        this->values.col._4.row._1 = x;
        this->values.col._4.row._2 = y;
        this->values.col._4.row._3 = z;
    }

    //set rotation matrix
    void dpmatrix::setRotationX( float deg )
    {
        deg = deg * 3.14f / 180.0f;
        this->setRotationXrad( deg );
    }

    //set rotation matrix
    void dpmatrix::setRotationY( float deg )
    {
        deg = deg * 3.14f / 180.0f;
        this->setRotationYrad( deg );
    }

    //set rotation matrix
    void dpmatrix::setRotationZ( float deg )
    {
        deg = deg * 3.14f / 180.0f;
        this->setRotationZrad( deg );
    }

    //set rotation matrix
    void dpmatrix::setRotationXrad( float rad )
    {
        this->setIdentity();
        this->values.col._2.row._2 = cos( rad );
        this->values.col._3.row._2 = -sin( rad );
        this->values.col._2.row._3 = sin( rad );
        this->values.col._3.row._3 = cos( rad );
    }

    //set rotation matrix
    void dpmatrix::setRotationYrad( float rad )
    {
        this->setIdentity();
        this->values.col._1.row._1 = cos( rad );
        this->values.col._3.row._1 = sin( rad );
        this->values.col._1.row._3 = -sin( rad );
        this->values.col._3.row._3 = cos( rad );
    }

    //set rotation matrix
    void dpmatrix::setRotationZrad( float rad )
    {
        this->setIdentity();
        this->values.col._1.row._1 = cos( rad );
        this->values.col._2.row._1 = -sin( rad );
        this->values.col._1.row._2 = sin( rad );
        this->values.col._2.row._2 = cos( rad );
    }

    //set scaling matrix
    void dpmatrix::setScaling( float x, float y, float z )
    {
        this->setIdentity();
        this->values.col._1.row._1 = x;
        this->values.col._2.row._2 = y;
        this->values.col._3.row._3 = z;
        this->values.col._4.row._4 = 1;
    }

    //transform
    void dpmatrix::transform( float *px, float *py, float *pz, float *pw )
    {
        float x, y, z, w;
        float rx, ry, rz, rw;

        x = y = z = 0;
        w = 1.0f;

        if( px )
            x = *px;
        if( py )
            y = *py;
        if( pz )
            z = *pz;
        if( pw )
            w = *pw;

        rx = this->values.col._1.row._1 * x + this->values.col._2.row._1 * y + this->values.col._3.row._1 * z + this->values.col._4.row._1 * w;
        ry = this->values.col._1.row._2 * x + this->values.col._2.row._2 * y + this->values.col._3.row._2 * z + this->values.col._4.row._2 * w;
        rz = this->values.col._1.row._3 * x + this->values.col._2.row._3 * y + this->values.col._3.row._3 * z + this->values.col._4.row._3 * w;
        rw = this->values.col._1.row._4 * x + this->values.col._2.row._4 * y + this->values.col._3.row._4 * z + this->values.col._4.row._4 * w;

        if( px )
            *px = rx;
        if( py )
            *py = ry;
        if( pz )
            *pz = rz;
        if( pw )
            *pw = rw;
    }

    //transform
    void dpmatrix::transform( dpxyzw *p )
    {
        this->transform( &p->x, &p->y, &p->z, &p->w );
    }

    //inverse transform
    void dpmatrix::itransform( float *px, float *py, float *pz, float *pw )
    {
        float x, y, z, w;
        float rx, ry, rz, rw;

        x = y = z = 0;
        w = 1.0f;

        if( px )
            x = *px;
        if( py )
            y = *py;
        if( pz )
            z = *pz;
        if( pw )
            w = *pw;

        x = x - this->values.col._4.row._1;
        y = y - this->values.col._4.row._2;
        z = z - this->values.col._4.row._3;

        rx = x * this->values.col._1.row._1 + y * this->values.col._1.row._2 + z * this->values.col._1.row._3;
        ry = y * this->values.col._2.row._1 + y * this->values.col._2.row._2 + z * this->values.col._2.row._3;
        rz = z * this->values.col._3.row._1 + y * this->values.col._3.row._2 + z * this->values.col._3.row._3;
        rw = w;

        if( px )
            *px = rx;
        if( py )
            *py = ry;
        if( pz )
            *pz = rz;
        if( pw )
            *pw = rw;
    }

    //inverse transform
    void dpmatrix::itransform( dpxyzw *p )
    {
        this->itransform( &p->x, &p->y, &p->z, &p->w );
    }

    //rotate ( Z * Y ) * X
    void dpmatrix::rotateRad( float x, float y, float z )
    {
        dpmatrix zm, ym, xm;

        xm.setRotationXrad( x );
        ym.setRotationYrad( y );
        zm.setRotationZrad( z );

        zm.multiply( &ym );
        zm.multiply( &xm );

        this->multiply( &zm );
    }

    //rotate ( Z * Y ) * X
    void dpmatrix::rotate( float x, float y, float z )
    {
        dpmatrix zm, ym, xm;

        xm.setRotationX( x );
        ym.setRotationY( y );
        zm.setRotationZ( z );

        zm.multiply( &ym );
        zm.multiply( &xm );

        this->multiply( &zm );
    }

    //set angle (radians) and position
    void dpmatrix::setAngleRadAndPosition( dpxyzw *angles, dpxyzw *pos )
    {
        float sr, sp, sy, cr, cp, cy;

        this->setIdentity();

        sy = sin( angles->z );
        cy = cos( angles->z );

        sp = sin( angles->y );
        cp = cos( angles->y );

        sr = sin( angles->x );
        cr = cos( angles->x );

        this->values.col._1.row._1 = cp * cy;
        this->values.col._1.row._2 = cp * sy;
        this->values.col._1.row._3 = -sp;

        this->values.col._2.row._1 = sr * sp * cy + cr * -sy;
        this->values.col._2.row._2 = sr * sp * sy + cr * cy;
        this->values.col._2.row._3 = sr * cp;

        this->values.col._3.row._1 = ( cr * sp * cy + -sr * -sy );
        this->values.col._3.row._2 = ( cr * sp * sy + -sr * cy );
        this->values.col._3.row._3 = cr * cp;

        this->values.col._4.row._1 = pos->x;
        this->values.col._4.row._2 = pos->y;
        this->values.col._4.row._3 = pos->z;
        this->values.col._4.row._4 = 1;
    }

    //set this to inverse of matrix
    void dpmatrix::inverse( dpmatrix *m )
    {
        float s0, s1, s2, s3, s4, s5;
        float c0, c1, c2, c3, c4, c5;
        float det, invdet;

        s0 = m->values.col._1.row._1 * m->values.col._2.row._2 - m->values.col._2.row._1 * m->values.col._1.row._2;
        s1 = m->values.col._1.row._1 * m->values.col._2.row._3 - m->values.col._2.row._1 * m->values.col._1.row._3;
        s2 = m->values.col._1.row._1 * m->values.col._2.row._4 - m->values.col._2.row._1 * m->values.col._1.row._4;
        s3 = m->values.col._1.row._2 * m->values.col._2.row._3 - m->values.col._2.row._2 * m->values.col._1.row._3;
        s4 = m->values.col._1.row._2 * m->values.col._2.row._4 - m->values.col._2.row._2 * m->values.col._1.row._4;
        s5 = m->values.col._1.row._3 * m->values.col._2.row._4 - m->values.col._2.row._3 * m->values.col._1.row._4;

        c5 = m->values.col._3.row._3 * m->values.col._4.row._4 - m->values.col._4.row._3 * m->values.col._3.row._4;
        c4 = m->values.col._3.row._2 * m->values.col._4.row._4 - m->values.col._4.row._2 * m->values.col._3.row._4;
        c3 = m->values.col._3.row._2 * m->values.col._4.row._3 - m->values.col._4.row._2 * m->values.col._3.row._3;
        c2 = m->values.col._3.row._1 * m->values.col._4.row._4 - m->values.col._4.row._1 * m->values.col._3.row._4;
        c1 = m->values.col._3.row._1 * m->values.col._4.row._3 - m->values.col._4.row._1 * m->values.col._3.row._3;
        c0 = m->values.col._3.row._1 * m->values.col._4.row._2 - m->values.col._4.row._1 * m->values.col._3.row._2;

    // Should check for 0 determinant
        det = ( s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0 );
        if( det * det > 0.0f )
            invdet = 1.0 / det;
        else
            invdet = 0;

        this->values.col._1.row._1 = ( m->values.col._2.row._2 * c5 - m->values.col._2.row._3 * c4 + m->values.col._2.row._4 * c3 ) * invdet;
        this->values.col._1.row._2 = (-m->values.col._1.row._2 * c5 + m->values.col._1.row._3 * c4 - m->values.col._1.row._4 * c3 ) * invdet;
        this->values.col._1.row._3 = ( m->values.col._4.row._2 * s5 - m->values.col._4.row._3 * s4 + m->values.col._4.row._4 * s3 ) * invdet;
        this->values.col._1.row._4 = (-m->values.col._3.row._2 * s5 + m->values.col._3.row._3 * s4 - m->values.col._3.row._4 * s3 ) * invdet;

        this->values.col._2.row._1 = (-m->values.col._2.row._1 * c5 + m->values.col._2.row._3 * c2 - m->values.col._2.row._4 * c1 ) * invdet;
        this->values.col._2.row._2 = ( m->values.col._1.row._1 * c5 - m->values.col._1.row._3 * c2 + m->values.col._1.row._4 * c1 ) * invdet;
        this->values.col._2.row._3 = (-m->values.col._4.row._1 * s5 + m->values.col._4.row._3 * s2 - m->values.col._4.row._4 * s1 ) * invdet;
        this->values.col._2.row._4 = ( m->values.col._3.row._1 * s5 - m->values.col._3.row._3 * s2 + m->values.col._3.row._4 * s1 ) * invdet;

        this->values.col._3.row._1 = ( m->values.col._2.row._1 * c4 - m->values.col._2.row._2 * c2 + m->values.col._2.row._4 * c0 ) * invdet;
        this->values.col._3.row._2 = (-m->values.col._1.row._1 * c4 + m->values.col._1.row._2 * c2 - m->values.col._1.row._4 * c0 ) * invdet;
        this->values.col._3.row._3 = ( m->values.col._4.row._1 * s4 - m->values.col._4.row._2 * s2 + m->values.col._4.row._4 * s0 ) * invdet;
        this->values.col._3.row._4 = (-m->values.col._3.row._1 * s4 + m->values.col._3.row._2 * s2 - m->values.col._3.row._4 * s0 ) * invdet;

        this->values.col._4.row._1 = (-m->values.col._2.row._1 * c3 + m->values.col._2.row._2 * c1 - m->values.col._2.row._3 * c0 ) * invdet;
        this->values.col._4.row._2 = ( m->values.col._1.row._1 * c3 - m->values.col._1.row._2 * c1 + m->values.col._1.row._3 * c0 ) * invdet;
        this->values.col._4.row._3 = (-m->values.col._4.row._1 * s3 + m->values.col._4.row._2 * s1 - m->values.col._4.row._3 * s0 ) * invdet;
        this->values.col._4.row._4 = ( m->values.col._3.row._1 * s3 - m->values.col._3.row._2 * s1 + m->values.col._3.row._3 * s0 ) * invdet;
    }

    //returns position
    void dpmatrix::getPosition( dpxyzw *p )
    {
        p->x = this->values.col._4.row._1;
        p->y = this->values.col._4.row._2;
        p->z = this->values.col._4.row._3;
    }

    //sets position
    void dpmatrix::setPosition( dpxyzw *p )
    {
        this->values.col._4.row._1 = p->x;
        this->values.col._4.row._2 = p->y;
        this->values.col._4.row._3 = p->z;
    }

    //create matrix from quaternion
    void dpmatrix::setQuat( dpquaternion *q )
    {
        dpmatrix_int *matrix;
        dpquaternion_inner *quaternion;

        matrix = &this->values;
        quaternion = q->getData();

        matrix->f4v[ 0 ][ 0 ] = 1.0f - 2.0f * quaternion->fv[ 1 ] * quaternion->fv[ 1 ] - 2.0f * quaternion->fv[ 2 ] * quaternion->fv[ 2 ];
        matrix->f4v[ 0 ][ 1 ] = 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 1 ] + 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 2 ];
        matrix->f4v[ 0 ][ 2 ] = 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 2 ] - 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 1 ];

        matrix->f4v[ 1 ][ 0 ] = 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 1 ] - 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 2 ];
        matrix->f4v[ 1 ][ 1 ] = 1.0f - 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 0 ] - 2.0f * quaternion->fv[ 2 ] * quaternion->fv[ 2 ];
        matrix->f4v[ 1 ][ 2 ] = 2.0f * quaternion->fv[ 1 ] * quaternion->fv[ 2 ] + 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 0 ];

        matrix->f4v[ 2 ][ 0 ] = 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 2 ] + 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 1 ];
        matrix->f4v[ 2 ][ 1 ] = 2.0f * quaternion->fv[ 1 ] * quaternion->fv[ 2 ] - 2.0f * quaternion->fv[ 3 ] * quaternion->fv[ 0 ];
        matrix->f4v[ 2 ][ 2 ] = 1.0f - 2.0f * quaternion->fv[ 0 ] * quaternion->fv[ 0 ] - 2.0f * quaternion->fv[ 1 ] * quaternion->fv[ 1 ];
    }

    //find angles
    void dpmatrix::getAngles( dpxyzw *o )
    {
        float a;

        o->x = atan2f( this->values.f4v[ 1 ][ 2 ], this->values.f4v[ 2 ][ 2 ] );

        a = this->values.f4v[ 1 ][ 2 ] * this->values.f4v[ 1 ][ 2 ];
        a += this->values.f4v[ 2 ][ 2 ] * this->values.f4v[ 2 ][ 2 ];
        o->y = atan2f( -this->values.f4v[ 0 ][ 2 ], sqrtf( a ) );

        o->z = atan2f( this->values.f4v[ 0 ][ 1 ], this->values.f4v[ 0 ][ 0 ] );
    }

};

