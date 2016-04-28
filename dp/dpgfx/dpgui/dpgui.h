
/*
*/

#ifndef dpgui_h
#define dpgui_h

#include "../dpgui_list/dpgui_list.h"
#include "../dpbitmap/dpbitmap/dpbitmap.h"
#include "../dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "../dpvertex/dpvertex.h"

#include <string>

namespace dp
{

    class dpgui_writelock;
    class dpinput;
    struct dpinput_event;
    struct dpinput_event_mouse;
    struct dpinput_event_keypress;
    struct dpinput_event_text;

    class dpgui : public dpgui_list
    {

    private:

        dpbitmap_rectangle rc;
        dpbitmap_32bit_uncompressed *bm_bg, *bm_fg;
        bool bBgDrawn, bFgDrawn;
        unsigned int z, bg_time, fg_time, sz_time;
        std::string stxt;
        uint64_t t_input;
        dpinput *inp;
        dpxyzw rot, spin;
        bool bIsCentered, bIsFloating, bFollowCursor, bGrows, bMin;

        //run input
        void runInput( void );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );
        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //render second pass of background image
        virtual void renderBackgroundPass1( dpbitmap *bm );
        //render first pass of foreground image
        virtual void renderForegroundPass0( dpbitmap *bm );
        //render second pass of foreground image
        virtual void renderForegroundPass1( dpbitmap *bm );
        //render text
        virtual void renderText( dpbitmap *bm );
        //override to handle gui ran
        virtual bool onGuiRun( dpgui_writelock *tl );
        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );
        //override to handle gui stop
        virtual bool onGuiStop( dpgui_writelock *tl );
        //set dimensions
        virtual void setDimensions( unsigned int w, unsigned int h );
        //set position
        virtual void setPosition( int x, int y );
        //get dimensions
        virtual void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        virtual void getPosition( int *x, int *y );
        //force bg to be redrawn
        virtual void redrawBg( void );
        //force fg to be redrawn
        virtual void redrawFg( void );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //returns bg bitmap
        virtual dpbitmap *getBg( void );
        //returns fg bitmap
        virtual dpbitmap *getFg( void );
        //set text
        virtual void setText( const char *ctxt );
        //get text
        virtual void getText( std::string *s );
        //return bg time
        unsigned int getBgTime( void );
        //return fg time
        unsigned int getFgTime( void );
        //return size time
        unsigned int getSzTime( void );
        //attach renderer input
        void attachInput( dpinput *i );
        //override to handle input events
        virtual void onInput( dpinput_event *e );
        //override to handle left clicks
        virtual void onLeftClick( dpinput_event_mouse *e );
        //override to handle right clicks
        virtual void onRightClick( dpinput_event_mouse *e );
        //override to handle mouse movement
        virtual void onMouseMove( dpinput_event_mouse *e );
        //override to handle key press down
        virtual void onKeyDown( dpinput_event_keypress *e );
        //override to handle key press up
        virtual void onKeyUp( dpinput_event_keypress *e );
        //override to handle text input
        virtual void onText( dpinput_event_text *e );
        //return true if centered
        bool isCentered( void );
        //set centered mode
        void setCentered( bool b );
        //return true if floating
        bool isFloating( void );
        //set floating mode
        void setFloating( bool b );
        //return true if follows cursor
        bool isFollowingCursor( void );
        //set cursor following mode
        void setFollowingCursor( bool b );
        //get rotation
        void getRotation( dpxyzw *p );
        //set rotation
        void setRotation( dpxyzw *p );
        //get spin
        void getSpin( dpxyzw *p );
        //set spin
        void setSpin( dpxyzw *p );
        //returns true if grows when mouse hovers over
        bool doesGrow( void );
        //set mouse hover mode
        void setGrow( bool b );
        //returns true if minimized
        bool isMinimized( void );
        //set minimized
        void setMinimized( bool b );

    public:

        //ctor
        dpgui( int x, int y, unsigned int w, unsigned int h, const char *ctxt );
        //dtor
        virtual ~dpgui( void );
        //return z
        virtual unsigned int getZ( void );
        //set z
        virtual void setZ( unsigned int z );

        friend class dpgui_writelock;
        friend class dpgui_readlock;
    };

}

#endif




