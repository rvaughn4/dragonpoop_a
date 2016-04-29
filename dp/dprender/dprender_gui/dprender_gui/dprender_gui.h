
/*
*/

#ifndef dprender_gui_h
#define dprender_gui_h

#include "../dprender_gui_list/dprender_gui_list.h"
#include "../../../dpgfx/dpbitmap/dpbitmap/dpbitmap.h"
#include "../../../dpgfx/dpmatrix/dpmatrix.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    class dprender_gui_writelock;
    class dpgui;
    class dpgui_ref;
    class dpapi_context_writelock;
    class dpapi_texture;
    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_bundle;
    class dpapi_commandlist_writelock;
    class dpgui_readlock;
    struct dpinput_event;
    class dpinput;

    class dprender_gui : public dprender_gui_list
    {

    private:

        dpshared_guard g;
        dpbitmap_rectangle rc;
        unsigned int z, bg_time, fg_time, sz_time, align;
        dpapi_context_writelock *ctx;
        dpapi_texture *t_bg, *t_fg;
        dpapi_vertexbuffer *vb;
        dpapi_indexbuffer *ib_fg, *ib_bg;
        dpapi_bundle *bdle_bg, *bdle_fg;
        dpmatrix mat, mat_bg, undo_mat;
        dpinput *inp;
        dpgui_ref *pgui;
        struct
        {
            float x, y;
        } mousepos, min_pos, drag_start, drag_off;
        float fhover, fMin;
        dpxyzw rot, spin;
        uint64_t t_spin;
        bool bIsCentered, bIsFloating, bFollowCursor, bIsMouseOver, bIsMouseDown, bGrows, bMin, bIsDrag, bFocus;

        //create vertex buffer
        bool makeVB( dpapi_context_writelock *ctx, dpgui_readlock *g );
        //create bg index buffer
        void makeBgIB( dpapi_context_writelock *ctx );
        //create fg index buffer
        void makeFgIB( dpapi_context_writelock *ctx );
        //make bg texture, return false if not remade/up-to-date
        bool makeBgTex( dpapi_context_writelock *ctx, dpgui_readlock *g );
        //make bg texture, return false if not remade/up-to-date
        bool makeFgTex( dpapi_context_writelock *ctx, dpgui_readlock *g );
        //make matrix
        void calcMatrix( dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *mparent, dpbitmap_rectangle *rc_parent );

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
        virtual void passContext( dprender_gui_writelock *wl, dpapi_context_writelock *ctx );
        //render
        virtual void render( dprender_gui_writelock *wl, dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );
        //process input event
        virtual bool processEvent( dprender_gui_list_writelock *l, dpinput_event *e );
        //handle event
        virtual void onEvent( dprender_gui_writelock *l, dpinput_event *e );

    public:

        //ctor
        dprender_gui( dpgui *g );
        //dtor
        virtual ~dprender_gui( void );
        //return z
        virtual unsigned int getZ( void );
        //set z
        virtual void setZ( unsigned int z );
        //compare gui
        bool compare( dpgui *g );
        //returns true if linked
        bool isGuiLinked( void );

        friend class dprender_gui_writelock;
        friend class dprender_gui_readlock;
    };

}

#endif





