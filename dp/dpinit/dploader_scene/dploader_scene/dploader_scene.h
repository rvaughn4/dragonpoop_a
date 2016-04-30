/*

*/

#ifndef dploader_scene_h
#define dploader_scene_h

#include "../../../dpgfx/dpscene/dpscene.h"

namespace dp
{

    class dploader_scene : public dpscene
    {

    private:

        dpscene *next_scene;
        uint64_t t;

    protected:

        //override to handle scene start
        virtual bool onSceneStart( dpscene_writelock *sl );
        //override to handle scene stop
        virtual bool onSceneStop( dpscene_writelock *sl );
        //override to handle scene run
        virtual bool onSceneRun( dpscene_writelock *sl );
        //generate root gui
        virtual dpgui *genRootGui( dpscene_writelock *sl );

    public:

        //ctor
        dploader_scene( dpscene **s );
        //dtor
        virtual ~dploader_scene( void );

    };

};

#endif

