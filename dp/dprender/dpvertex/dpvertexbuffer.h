
/*

*/

#ifndef dpvertexbuffer_h
#define dpvertexbuffer_h

#include "dpvarbuffer.h"
#include "dpvertex.h"

namespace dp
{

    class dpvertexbuffer : public dpvarbuffer
    {

    private:


    protected:

        //override to set element size
        virtual unsigned int _getElementSize( void );

    public:

        //ctor
        dpvertexbuffer( void );
        //dtor
        virtual ~dpvertexbuffer( void );
        //write element
        bool write( dpvertex *i );
        //read element
        bool read( dpvertex *i );
        //write element at index
        bool write( dpvertex *i, unsigned int index );
        //read element at index
        bool read( dpvertex *i, unsigned int index );

    };

};

#endif

