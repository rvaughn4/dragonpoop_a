
/*
*/

#ifndef dpgui_factory_h
#define dpgui_factory_h


namespace dp
{

    class dpgui;

    class dpgui_factory
    {
    private:

    protected:

    public:

        //ctor
        dpgui_factory( void );
        //dtor
        virtual ~dpgui_factory( void );
        //generate gui
        virtual dpgui *genGui( void );

    };

}

#endif





