 /*
represents the lifecycle of a writelock on a dpapi_primary_commandlist
this object is returned from a dpapi_primary_commandlist when writelocked
deleting this object releases the writelock on the dpapi_primary_commandlist
*/

#include "dpapi_primary_commandlist_writelock.h"
#include "dpapi_primary_commandlist.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_writelock::dpapi_primary_commandlist_writelock( dpapi_primary_commandlist *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_primary_commandlist_writelock::~dpapi_primary_commandlist_writelock( void )
    {

    }

    //clear commandlist and make ready for new commands / record mode
    bool dpapi_primary_commandlist_writelock::clearAndRecord( dpapi_context_writelock *ctxl )
    {
        return this->p->clearAndRecord( this, ctxl );
    }

    //compile commands to make ready for execute
    bool dpapi_primary_commandlist_writelock::compile( dpapi_context_writelock *ctxl )
    {
        return this->p->compile( this, ctxl );
    }

    //execute commands
    bool dpapi_primary_commandlist_writelock::execute( dpapi_context_writelock *ctxl )
    {
        return this->p->execute( this, ctxl );
    }

    //add clear color buffer command
    bool dpapi_primary_commandlist_writelock::clearColor( float r, float g, float b, float a )
    {
        return this->p->clearColor( r, g, b, a );
    }

    //add clear depth buffer command
    bool dpapi_primary_commandlist_writelock::clearDepth( float d )
    {
        return this->p->clearDepth( d );
    }

    //add begin renderpass command
    bool dpapi_primary_commandlist_writelock::startRenderpass( dpapi_renderpass *rp )
    {
        return this->p->startRenderpass( rp );
    }

    //add end renderpass command
    bool dpapi_primary_commandlist_writelock::endRenderpass( void )
    {
        return this->p->endRenderpass();
    }

    //add commandlist command
    bool dpapi_primary_commandlist_writelock::addCommandList( dpapi_commandlist *cl )
    {
        return this->p->addCommandList( cl );
    }

    //add swap buffers
    bool dpapi_primary_commandlist_writelock::swapBuffers( void )
    {
        return this->p->swapBuffers();
    }

}











