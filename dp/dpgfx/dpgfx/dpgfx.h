
/*
gpgfx manages models and gui elements and scenes
*/

#ifndef dpgfx_h
#define dpgfx_h

#include "../../dpcore/dptask/dptask.h"

namespace dp
{

    class dpscene;
    class dprender;
    #define dpgfx_max_scenes 128

    class dpgfx : public dptask
    {

    private:

        dpscene *scenes[ dpgfx_max_scenes ];
        dprender *renderer;

        //zero scenes
        void zeroScenes( void );
        //delete scenes
        void deleteScenes( void );
        //stop scenes
        void stopScenes( void );
        //load a renderer
        void initAnyRenderer( void );

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
        //add scene
        bool addScene( dpscene **s );
        //get all scenes
        unsigned int getScenes( dpscene **lst, unsigned int max_sz );

    public:

        //ctor
        dpgfx( void );
        //dtor
        virtual ~dpgfx( void );

        friend class dpgfx_writelock;
        friend class dpgfx_readlock;
    };

}

#endif





