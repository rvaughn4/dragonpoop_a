
/*
*/

#ifndef dpgui_readlock_h
#define dpgui_readlock_h

#include "../dpgui_list/dpgui_list_readlock.h"

namespace dp
{

    class dpgui;
    class dpbitmap_32bit_uncompressed;
    struct dpxyzw;

    class dpgui_readlock : public dpgui_list_readlock
    {

        dpgui *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_readlock( void );

    public:

        //ctor
        dpgui_readlock( dpgui *p, dpmutex_readlock *ml );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );
        //return z
        unsigned int getZ( void );
        //returns bg bitmap
        dpbitmap_32bit_uncompressed *getBg( void );
        //returns fg bitmap
        dpbitmap_32bit_uncompressed *getFg( void );
        //return bg time
        unsigned int getBgTime( void );
        //return fg time
        unsigned int getFgTime( void );
        //return size time
        unsigned int getSzTime( void );
        //return true if centered
        bool isCentered( void );
        //return true if floating
        bool isFloating( void );
        //return true if follows cursor
        bool isFollowingCursor( void );
        //get rotation
        void getRotation( dpxyzw *p );
        //get spin
        void getSpin( dpxyzw *p );
        //returns true if grows when mouse hovers over
        bool doesGrow( void );
        //returns true if minimized
        bool isMinimized( void );
        //get alignment
        unsigned int getAlignment( void );
        //get zoom
        float getZoom( void );
        //returns true if horiz fill enabled
        bool isHorizFill( void );
        //returns true if accepts input
        bool isInput( void );
        //returns true if can have text selected and has cursor
        bool isSelect( void );

    };

}

#endif





