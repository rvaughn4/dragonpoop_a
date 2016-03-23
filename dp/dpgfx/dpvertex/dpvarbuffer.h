
/*

*/

#ifndef dpvarbuffer_h
#define dpvarbuffer_h

#include "../../dpcore/dpbuffer/dpbuffer_dynamic/dpbuffer_dynamic.h"
#include "../../dpcore/dpbuffer/dpbuffer_wrapper/dpbuffer_wrapper.h"

namespace dp
{

    class dpvarbuffer : public dpbuffer_wrapper
    {

    private:

        unsigned int sz_element;
        dpbuffer_dynamic b;

    protected:

        //override to set element size
        virtual unsigned int _getElementSize( void );
        //ctor
        dpvarbuffer( void );

    public:

        //dtor
        virtual ~dpvarbuffer( void );
        //write bytes to buffer
        bool write( char *b, unsigned int sz );
        //read bytes from bufffer
        bool read( char *b, unsigned int sz );
        //write bytes to buffer at index
        bool write( char *b, unsigned int sz, unsigned int index );
        //read bytes from bufffer at index
        bool read( char *b, unsigned int sz, unsigned int index );
        //return count of elements
        unsigned int getCount( void );

    };

};

#endif
