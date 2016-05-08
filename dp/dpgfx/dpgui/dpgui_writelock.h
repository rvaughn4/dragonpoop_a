
/*
*/

#ifndef dpgui_writelock_h
#define dpgui_writelock_h

#include "../dpgui_list/dpgui_list_writelock.h"

namespace dp
{

    class dpgui;
    class dpbitmap_32bit_uncompressed;
    class dpinput;
    struct dpxyzw;

    class dpgui_writelock : public dpgui_list_writelock
    {

        dpgui *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_writelock( void );

    public:

        //ctor
        dpgui_writelock( dpgui *p, dpmutex_writelock *ml );
        //set dimensions
        void setDimensions( unsigned int w, unsigned int h );
        //set position
        void setPosition( int x, int y );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );
        //force bg to be redrawn
        void redrawBg( void );
        //force fg to be redrawn
        void redrawFg( void );
        //return z
        unsigned int getZ( void );
        //set z
        void setZ( unsigned int z );
        //returns bg bitmap
        dpbitmap_32bit_uncompressed *getBg( void );
        //returns fg bitmap
        dpbitmap_32bit_uncompressed *getFg( void );
        //attach renderer input
        void attachInput( dpinput *i );
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
        //set alignment
        void setAlignment( unsigned int a );
        //get alignment
        unsigned int getAlignment( void );
        //set zoom
        void setZoom( float z );
        //get zoom
        float getZoom( void );
        //zoom in
        void zoomIn( void );
        //zoom out
        void zoomOut( void );
        //set horizontal auto-fill/stretch
        void setHorizFill( bool b );
        //returns true if horiz fill enabled
        bool isHorizFill( void );
        //set input mode
        void setInputMode( bool b );
        //returns true if accepts input
        bool isInput( void );
        //set select mode
        void setSelectMode( bool b );
        //returns true if can have text selected and has cursor
        bool isSelect( void );

    };

}

#endif






