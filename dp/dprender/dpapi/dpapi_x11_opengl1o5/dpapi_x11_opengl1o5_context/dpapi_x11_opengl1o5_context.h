
/*

*/

#ifndef dpapi_x11_opengl1o5_context_h
#define dpapi_x11_opengl1o5_context_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5_context/dpapi_opengl1o5_context.h"
#include "../dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_functions.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_writelock.h"

namespace dp
{

    class dpapi_x11_opengl1o5_context : public dpapi_opengl1o5_context
    {

    private:

        opengl1o5_x11_lib_functions *gl;
        x11_window_Display *dpy;
        x11_window_Window *win;
        x11_window_XVisualInfo *vi;
        opengl1o5_lib_GLXContext *ctx;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //generate primary commandlist
        virtual dpapi_primary_commandlist *makePrimaryCommandList( dpapi_context_writelock *l );
        //return x11 display
        x11_window_Display *getDisplay( void );
        //return x11 window
        x11_window_Window *getWindow( void );
        //return x11 visual
        x11_window_XVisualInfo *getVisual( void );
        //return x11 context
        opengl1o5_lib_GLXContext *getContext( void );
        //make this context active in this thread
        virtual bool makeActive( dpapi_opengl1o5_context_writelock *l );

    public:

        //ctor
        dpapi_x11_opengl1o5_context( dpapi_writelock *awl, opengl1o5_x11_lib_functions *gl, opengl1o5_lib_GLXContext *ctx );
        //dtor
        virtual ~dpapi_x11_opengl1o5_context( void );


        friend class dpapi_x11_opengl1o5_context_writelock;
    };

}

#endif







