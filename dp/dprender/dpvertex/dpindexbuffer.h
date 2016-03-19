
/*

*/

#ifndef dpindexbuffer_h
#define dpindexbuffer_h

#include "dpvarbuffer.h"
#include "dpindex.h"

namespace dp
{

    class dpindexbuffer : public dpvarbuffer
    {

    private:


    protected:

        //override to set element size
        virtual unsigned int _getElementSize( void );

    public:

        //ctor
        dpindexbuffer( void );
        //dtor
        virtual ~dpindexbuffer( void );
        //write element
        bool write( dpindex *i );
        //read element
        bool read( dpindex *i );
        //write element at index
        bool write( dpindex *i, unsigned int index );
        //read element at index
        bool read( dpindex *i, unsigned int index );

    };

};

#endif
