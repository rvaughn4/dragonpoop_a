
/*

*/

#include "dummy_game_client.h"
#include "../../../dpinit/dploader_scene/dploader_scene/dploader_scene.h"

namespace dp
{

    //ctor
    dummy_game_client::dummy_game_client( void )
    {
        dpscene *s;
        s = new dpscene();
        this->setFirstScene( &s );
    }

    //dtor
    dummy_game_client::~dummy_game_client( void )
    {

    }

};



