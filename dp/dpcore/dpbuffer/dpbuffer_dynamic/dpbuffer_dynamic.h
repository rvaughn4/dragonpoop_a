
/*

*/

#ifndef dpbuffer_dynamic_h
#define dpbuffer_dynamic_h

#include "../dpbuffer_concrete/dpbuffer_concrete.h"

namespace dp
{

    struct dpbuffer_dynamic_buffer
    {
        char *b;
        unsigned int sz;
    };

    class dpbuffer_dynamic : public dpbuffer_concrete
    {

    private:

        dpbuffer_dynamic_buffer b;

    protected:

        //returns buffer
        virtual char *_getBuffer( void );
        //returns size of buffer (override)
        virtual unsigned int _getSize( void );
        //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
        virtual bool _autoResize( unsigned int sz );

    public:

        //ctor
        dpbuffer_dynamic( void );
        //dtor
        virtual ~dpbuffer_dynamic( void );

    };

};

#endif


