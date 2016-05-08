
/*
*/

#ifndef dpgui_taskman_h
#define dpgui_taskman_h

#include "../dpgui_window/dpgui_window.h"

namespace dp
{

    class dpgui_taskman : public dpgui_window
    {

    private:

        uint64_t t;

    protected:

        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );
        //override to handle gui ran
        virtual bool onGuiRun( dpgui_writelock *tl );

    public:

        //ctor
        dpgui_taskman( void );
        //dtor
        virtual ~dpgui_taskman( void );

    };

}

#endif







