
 /*
*/

#include "dprender_gui_writelock.h"
#include "dprender_gui.h"

namespace dp
{

    //ctor
    dprender_gui_writelock::dprender_gui_writelock( dprender_gui *p, dpmutex_writelock *ml ) : dprender_gui_list_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_gui_writelock::~dprender_gui_writelock( void )
    {

    }

    //set dimensions
    void dprender_gui_writelock::setDimensions( unsigned int w, unsigned int h )
    {
        this->p->setDimensions( w, h );
    }

    //set position
    void dprender_gui_writelock::setPosition( int x, int y )
    {
        this->p->setPosition( x, y );
    }

    //get dimensions
    void dprender_gui_writelock::getDimensions( unsigned int *w, unsigned int *h )
    {
        this->p->getDimensions( w, h );
    }

    //get position
    void dprender_gui_writelock::getPosition( int *x, int *y )
    {
        this->p->getPosition( x, y );
    }

    //return z
    unsigned int dprender_gui_writelock::getZ( void )
    {
        return this->p->getZ();
    }

    //set z
    void dprender_gui_writelock::setZ( unsigned int z )
    {
        this->p->setZ( z );
    }

    //pass in context
    void dprender_gui_writelock::passContext( dpapi_context_writelock *ctx )
    {
        this->p->passContext( this, ctx );
    }

    //render
    void dprender_gui_writelock::render( dpmatrix *m_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        this->p->render( this, m_parent, ctx, cll );
    }

    //process input event
    bool dprender_gui_writelock::processEvent( dpinput_event *e )
    {
        return this->p->processEvent( this, e );
    }

}








