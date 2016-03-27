
/*

*/

#ifndef dpbitmap_loader_h
#define dpbitmap_loader_h

namespace dp
{

    class dpbitmap;
    class dpbuffer;

    class dpbitmap_loader
    {

    private:

    protected:

        //attemp windows style bitmap
        dpbitmap *tryOS2Bitmap( dpbuffer *b );
        //attempt png
        dpbitmap *tryPng( dpbuffer *b );

    public:

        //ctor
        dpbitmap_loader( void );
        //dtor
        virtual ~dpbitmap_loader( void );
        //parse buffer and generate correct bitmap object
        dpbitmap *load( dpbuffer *b );
        //parse file and generate correct bitmap object
        dpbitmap *load( const char *fname );

    };

};

#endif



