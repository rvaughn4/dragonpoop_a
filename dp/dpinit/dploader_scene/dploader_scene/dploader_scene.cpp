/*

*/

#include "dploader_scene.h"
#include "../dploader_root_gui/dploader_root_gui.h"

namespace dp
{

    //ctor
    dploader_scene::dploader_scene( dpscene **s )
    {
        this->next_scene = 0;
        if( s )
        {
            this->next_scene = *s;
            *s = 0;
        }
    }

    //dtor
    dploader_scene::~dploader_scene( void )
    {
        if( this->next_scene )
            delete this->next_scene;
    }

    //override to handle scene start
    bool dploader_scene::onSceneStart( dpscene_writelock *sl )
    {
        this->t = this->getTicks();
        return this->dpscene::onSceneStart( sl );
    }

    //override to handle scene stop
    bool dploader_scene::onSceneStop( dpscene_writelock *sl )
    {
        if( this->next_scene )
            this->addScene( &this->next_scene );
        this->next_scene = 0;
        return this->dpscene::onSceneStop( sl );
    }

    //override to handle scene run
    bool dploader_scene::onSceneRun( dpscene_writelock *sl )
    {
        //uint64_t t;

        //t = this->getTicks();
        //if( t - this->t > 10000 )
          //  this->stop();

        return this->dpscene::onSceneRun( sl );
    }

    //generate root gui
    dpgui *dploader_scene::genRootGui( dpscene_writelock *sl )
    {
        return new dploader_root_gui();
    }

};


