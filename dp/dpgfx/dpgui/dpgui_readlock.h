
/*
*/

#ifndef dpgui_readlock_h
#define dpgui_readlock_h

#include "../dpgui_list/dpgui_list_readlock.h"

namespace dp
{

    class dpgui;
    class dpbitmap_32bit_uncompressed;
    struct dpgui_attribs;

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
        //returns bg bitmap
        dpbitmap_32bit_uncompressed *getBg( void );
        //returns fg bitmap
        dpbitmap_32bit_uncompressed *getFg( void );
        //get attributes
        void getAttributes( dpgui_attribs *a );

    };

}

#endif





