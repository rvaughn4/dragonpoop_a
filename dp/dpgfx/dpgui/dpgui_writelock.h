
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
    struct dpgui_attribs;

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
        //force bg to be redrawn
        void redrawBg( void );
        //force fg to be redrawn
        void redrawFg( void );
        //returns bg bitmap
        dpbitmap_32bit_uncompressed *getBg( void );
        //returns fg bitmap
        dpbitmap_32bit_uncompressed *getFg( void );
        //attach renderer input
        void attachInput( dpinput *i );
        //zoom in
        void zoomIn( void );
        //zoom out
        void zoomOut( void );
        //get attributes
        void getAttributes( dpgui_attribs *a );
        //set attributes
        void setAttributes( dpgui_attribs *a );

    };

}

#endif






