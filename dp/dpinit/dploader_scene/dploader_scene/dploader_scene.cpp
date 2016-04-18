/*

*/

#include "dploader_scene.h"
#include "../dploader_root_gui/dploader_root_gui.h"

namespace dp
{

    //ctor
    dploader_scene::dploader_scene( void )
    {

    }

    //dtor
    dploader_scene::~dploader_scene( void )
    {

    }

    //override to handle scene start
    bool dploader_scene::onSceneStart( dpscene_writelock *sl )
    {
        return this->dpscene::onSceneStart( sl );
    }

    //override to handle scene stop
    bool dploader_scene::onSceneStop( dpscene_writelock *sl )
    {
        return this->dpscene::onSceneStop( sl );
    }

    //override to handle scene run
    bool dploader_scene::onSceneRun( dpscene_writelock *sl )
    {
        return this->dpscene::onSceneRun( sl );
    }

    //generate root gui
    dpgui *dploader_scene::genRootGui( dpscene_writelock *sl )
    {
        return new dploader_root_gui();
    }

};


