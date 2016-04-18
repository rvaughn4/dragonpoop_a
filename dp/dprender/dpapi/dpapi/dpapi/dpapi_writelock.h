 /*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#ifndef dpapi_writelock_h
#define dpapi_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi;
    class dpmutex_writelock;
    class dpapi_ref;
    class dpapi_context;
    class dpwindow_ref;
    class dpshared_guard;

    class dpapi_writelock : public dpshared_writelock
    {

    private:

        dpapi *p;

    protected:

        //dtor
        virtual ~dpapi_writelock( void );

    public:

        //ctor
        dpapi_writelock( dpapi *p, dpmutex_writelock *ml );
        //returns true if open
        bool isOpen( void );
        //override to generate rendering context
        dpapi_context *makeContext( void );
        //get dimensions
        void getDimensions( unsigned int **w, unsigned int **h );
        //show window
        bool show( void );
        //hide window
        bool hide( void );
        //returns true if window is shown
        bool isShown( void );
        //make window fullscreen
        bool fullscreen( void );
        //make window windowed
        bool windowed( void );
        //returns true if window is fullscreen
        bool isFullscreen( void );
        //create window ref
        dpwindow_ref *getWindow( dpshared_guard *g );

    };

}

#endif







