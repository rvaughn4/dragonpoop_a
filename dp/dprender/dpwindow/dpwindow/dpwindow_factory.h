
/*

*/

#ifndef dpwindow_factory_h
#define dpwindow_factory_h

namespace dp
{

    class dpwindow;

    class dpwindow_factory
    {

    private:

    protected:


    public:

        //ctor
        dpwindow_factory( void );
        //dtor
        virtual ~dpwindow_factory( void );
        //creates window
        virtual dpwindow *makeWindow( void );

    };

}

#endif





