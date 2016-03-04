
/*

*/

#ifndef dpapi_factory_h
#define dpapi_factory_h

namespace dp
{

    class dpapi;

    class dpapi_factory
    {

    private:

    protected:


    public:

        //ctor
        dpapi_factory( void );
        //dtor
        virtual ~dpapi_factory( void );
        //creates window
        virtual dpapi *makeApi( void );

    };

}

#endif






