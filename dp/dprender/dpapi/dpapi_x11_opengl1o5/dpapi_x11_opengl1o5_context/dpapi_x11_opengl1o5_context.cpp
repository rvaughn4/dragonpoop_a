
/*

*/

#include "dpapi_x11_opengl1o5_context.h"
#include "dpapi_x11_opengl1o5_context_ref.h"
#include "dpapi_x11_opengl1o5_context_readlock.h"
#include "dpapi_x11_opengl1o5_context_writelock.h"
#include "../dpapi_x11_opengl1o5_primary_commandlist/dpapi_x11_opengl1o5_primary_commandlist.h"
#include "../dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_writelock.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_context::dpapi_x11_opengl1o5_context( dpapi_writelock *awl, opengl1o5_x11_lib_functions *gl, opengl1o5_lib_GLXContext *ctx ) : dpapi_opengl1o5_context( awl, &gl->gl_1o5 )
    {
        dpapi_x11_opengl1o5_writelock *wl;

        this->gl = gl;

        wl = (dpapi_x11_opengl1o5_writelock *)awl;
        this->dpy = wl->getDisplay();
        this->win = wl->getWindow();
        this->vi = wl->getVisual();
        this->ctx = ctx;
    }

    //dtor
    dpapi_x11_opengl1o5_context::~dpapi_x11_opengl1o5_context( void )
    {

    }

    //generate primary commandlist
    dpapi_primary_commandlist *dpapi_x11_opengl1o5_context::makePrimaryCommandList( dpapi_context_writelock *l )
    {
        return new dpapi_x11_opengl1o5_primary_commandlist( l, this->gl );
    }

    //generate readlock
    dpshared_readlock *dpapi_x11_opengl1o5_context::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_x11_opengl1o5_context_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_x11_opengl1o5_context::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_x11_opengl1o5_context_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_x11_opengl1o5_context::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_x11_opengl1o5_context_ref( this, k, t_sync );
    }

    //return x11 display
    x11_window_Display *dpapi_x11_opengl1o5_context::getDisplay( void )
    {
        return this->dpy;
    }

    //return x11 window
    x11_window_Window *dpapi_x11_opengl1o5_context::getWindow( void )
    {
        return this->win;
    }

    //return x11 visual
    x11_window_XVisualInfo *dpapi_x11_opengl1o5_context::getVisual( void )
    {
        return this->vi;
    }

    //return x11 context
    opengl1o5_lib_GLXContext *dpapi_x11_opengl1o5_context::getContext( void )
    {
        return this->ctx;
    }

    //make this context active in this thread
    bool dpapi_x11_opengl1o5_context::makeActive( dpapi_opengl1o5_context_writelock *l )
    {
        this->gl->glXMakeCurrent( this->dpy, *this->win, *this->ctx );
        return 1;
    }

}








