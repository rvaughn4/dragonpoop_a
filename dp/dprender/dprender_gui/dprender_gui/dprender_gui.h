
/*
*/

#ifndef dprender_gui_h
#define dprender_gui_h

#include "../dprender_gui_list/dprender_gui_list.h"
#include "../../../dpgfx/dpmatrix/dpmatrix.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../../dpgfx/dpgui/dpgui.h"

namespace dp
{

    class dprender_gui_writelock;
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

    struct dprender_gui_attribs
    {
        dpgui_attribs g;
        dpbitmap_rectangle rc_exact;
        unsigned int bg_time, fg_time;
        dpxyzw mousepos, min_pos, drag_start, drag_off;
        float fhover, fMin, zoom;
        bool bIsFocus, bIsDrag, bIsMouseOver, bIsMouseDown, bHide, bIsSize;
    };

    class dprender_gui : public dprender_gui_list
    {

    private:

        dpshared_guard g;
        dpapi_context_writelock *ctx;
        dpapi_texture *t_bg, *t_fg, *t_bg_old, *t_fg_old;
        dpapi_vertexbuffer *vb;
        dpapi_indexbuffer *ib_fg, *ib_bg;
        dpapi_bundle *bdle_bg, *bdle_fg;
        dpmatrix mat, undo_mat, sz_mat;
        dpinput *inp;
        dpgui_ref *pgui;
        uint64_t t_spin, t_last_ftime;
        dprender_gui_attribs attr;

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
        //compare gui
        bool compare( dpgui *g );
        //returns true if linked
        bool isGuiLinked( void );

        friend class dprender_gui_writelock;
        friend class dprender_gui_readlock;
    };

}

#endif





