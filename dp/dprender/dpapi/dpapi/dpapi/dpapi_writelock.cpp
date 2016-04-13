 /*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#include "dpapi_writelock.h"
#include "dpapi.h"

namespace dp
{

    //ctor
    dpapi_writelock::dpapi_writelock( dpapi *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_writelock::~dpapi_writelock( void )
    {

    }

    //returns true if open
    bool dpapi_writelock::isOpen( void )
    {
        return this->p->isOpen();
    }

    //override to generate rendering context
    dpapi_context *dpapi_writelock::makeContext( void )
    {
        return this->p->makeContext( this );
    }

    //get dimensions
    void dpapi_writelock::getDimensions( unsigned int **w, unsigned int **h )
    {
        this->p->getDimensions( w, h );
    }

}








