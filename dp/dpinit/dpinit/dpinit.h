
/*

*/

#ifndef dpinit_h
#define dpinit_h

namespace dp
{

    class dpscene;
    class dptaskmgr;
    class dpgfx;

    class dpinit
    {
    private:

            dptaskmgr *tskmgr;
            dpgfx *gfx;
            dpscene *s;

    protected:

    public:

        //ctor
        dpinit( void );
        //dtor
        virtual ~dpinit( void );
        //start dp
        bool start( void );
        //stop dp
        void stop( void );
        //set first scene
        void setFirstScene( dpscene **s );
        //block until engine dies
        void blockUntilDead( void );
        //returns true if engine is running
        bool isAlive( void );

    };

};

#endif

