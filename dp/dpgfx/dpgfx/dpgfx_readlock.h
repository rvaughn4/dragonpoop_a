 /*
represents the lifecycle of a readlock on a dpgfx
this object is returned from a dpgfx when readlocked
deleting this object releases the readlock on the dpgfx
*/

#ifndef dpgfx_readlock_h
#define dpgfx_readlock_h

#include "../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dpgfx;
    class dpscene;

    class dpgfx_readlock : public dptask_readlock
    {

        dpgfx *p;

    private:

    protected:

        //dtor
        virtual ~dpgfx_readlock( void );

    public:

        //ctor
        dpgfx_readlock( dpgfx *p, dpmutex_readlock *ml );
        //get all scenes
        unsigned int getScenes( dpscene **lst, unsigned int max_sz );

    };

}

#endif






