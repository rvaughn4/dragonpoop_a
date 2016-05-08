
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

    //return z
    unsigned int dprender_gui_writelock::getZ( void )
    {
        return this->p->getZ();
    }


    //pass in context
    void dprender_gui_writelock::passContext( dpapi_context_writelock *ctx )
    {
        this->p->passContext( this, ctx );
    }

    //render
    void dprender_gui_writelock::render( dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        this->p->render( this, m_world, rc_world, m_parent, rc_parent, ctx, cll );
    }

    //process input event
    bool dprender_gui_writelock::processEvent( dpinput_event *e )
    {
        return this->p->processEvent( this, e );
    }

}








