
/*

*/

#ifndef dpbuffer_static_h
#define dpbuffer_static_h

#include "../dpbuffer/dpbuffer.h"

namespace dp
{

        class dpbuffer_static : public dpbuffer
        {

        private:

            char *b;
            unsigned int sz;

        protected:

            //returns buffer
            virtual char *_getBuffer( void );
            //returns size of buffer (override)
            virtual unsigned int _getSize( void );
            //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
            virtual bool _autoResize( unsigned int sz );

        public:

            //ctor
            dpbuffer_static( char *b, unsigned int sz );
            //dtor
            virtual ~dpbuffer_static( void );

        };


};

#endif

