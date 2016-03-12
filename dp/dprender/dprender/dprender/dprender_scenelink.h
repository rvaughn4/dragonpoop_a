
/*
*/

#ifndef dprender_scenelink_h
#define dprender_scenelink_h

#include <atomic>

namespace dp
{

    class dprender_scene_ref;
    class dpapi_commandlist;

    struct dprender_scenelink_clist_link
    {
        dpapi_commandlist *cl;
        std::atomic<bool> b;
    };

    struct dprender_scenelink_clist
    {
        struct
        {
            dprender_scenelink_clist_link a, b;
            struct
            {
                dprender_scenelink_clist_link *pnext, *pprev;
            } creator, consumer;
        } clists;
    };

    struct dprender_scenelink
    {
        std::atomic<bool> bAlive;
        std::atomic<dprender_scene_ref *> rscene;
        dprender_scenelink_clist guis, sky, terrain, models;
    };

    #define dprender_scenelink_MAX 64

    struct dprender_scenelink_list
    {
        dprender_scenelink scenes[ dprender_scenelink_MAX ];
    };


}

#endif








