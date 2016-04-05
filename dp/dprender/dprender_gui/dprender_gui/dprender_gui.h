
/*
*/

#ifndef dprender_gui_h
#define dprender_gui_h

#include "../dprender_gui_list/dprender_gui_list.h"
#include "../../../dpgfx/dpbitmap/dpbitmap/dpbitmap.h"

namespace dp
{

    class dprender_gui_writelock;
    class dpgui;
    class dpapi_context_writelock;
    class dpapi_texture;
    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_bundle;

    class dprender_gui : public dprender_gui_list
    {

    private:

        dpbitmap_rectangle rc;
        unsigned int z;
        dpapi_context_writelock *ctx;
        dpapi_texture *t_bg, *t_fg;
        dpapi_vertexbuffer *vb;
        dpapi_indexbuffer *ib_fg, *ib_bg;
        dpapi_bundle *bdle;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //set dimensions
        virtual void setDimensions( unsigned int w, unsigned int h );
        //set position
        virtual void setPosition( int x, int y );
        //get dimensions
        virtual void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        virtual void getPosition( int *x, int *y );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //override to handle processing
        virtual void onRun( dpshared_writelock *wl );
        //pass in context
        virtual void passContext( dpapi_context_writelock *ctx );

    public:

        //ctor
        dprender_gui( dpgui *g );
        //dtor
        virtual ~dprender_gui( void );
        //return z
        virtual unsigned int getZ( void );
        //set z
        virtual void setZ( unsigned int z );

        friend class dprender_gui_writelock;
        friend class dprender_gui_readlock;
    };

}

#endif





