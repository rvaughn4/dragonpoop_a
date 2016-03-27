
/*

*/

#ifndef dpbitmap_png_h
#define dpbitmap_png_h

#include "../dpbitmap_compressed/dpbitmap_compressed.h"

namespace dp
{

#pragma pack( 1 )
    struct dpbitmap_png_file_hdr
    {
        uint8_t high_bit;
        uint8_t c_png[ 3 ];
        uint8_t c_crlf[ 2 ];
        uint8_t c_eof;
        uint8_t c_lf;
    };

    struct dpbitmap_png_chunk_start
    {
        uint32_t len;
        uint32_t type;
    };

    struct dpbitmap_png_chunk_end
    {
        uint32_t crc;
    };

    struct dpbitmap_png_IHDR
    {
        uint32_t    w;      //width
        uint32_t    h;      //height
        uint8_t     bits;   //bits per pixel channel
        uint8_t     colorType;  //color type
        uint8_t     compType;   //compressiong type
        uint8_t     filterType; //filter type
        uint8_t     interlaceType;  //interlace type
    };

    struct dpbitmap_png_IHDR_outter
    {
        dpbitmap_png_chunk_start c_start;
        dpbitmap_png_IHDR chnk;
        dpbitmap_png_chunk_end c_end;
    };

    #define dpbitmap_png_IHDR_color_greyscale 0
    #define dpbitmap_png_IHDR_color_truecolor 2
    #define dpbitmap_png_IHDR_color_indexed 3
    #define dpbitmap_png_IHDR_color_greyscale_alpha 4
    #define dpbitmap_png_IHDR_color_truecolor_alpha 6

    struct dpbitmap_png_IPLTE_entry
    {
        uint8_t rgb;
    };

    struct dpbitmap_png_IEND
    {
        dpbitmap_png_chunk_start c_start;
        dpbitmap_png_chunk_end c_end;
    };

#pragma pack()

    class dpbuffer_dynamic;

    class dpbitmap_png : public dpbitmap_compressed
    {

    private:

    protected:

        //uncompress image and store in bitmap
        virtual bool uncompress( dpbitmap *b );
        //compress image and overrwrite previous data
        virtual bool compress( dpbitmap *b );
        //generate default png header and chunks
        bool genDefaults( int w, int h );
        //generate default png file header
        bool genFileHdr( void );
        //generate default png ihdr chunck
        bool genIHDR( int w, int h );
        //generate default png plte chunk
        bool genPLTE( void );
        //generate default idat chunk
        bool genIDAT( dpbitmap *bm );
        //generate default iend chunk
        bool genIEND( void );

    public:

        //ctor
        dpbitmap_png( int w, int h );
        //ctor
        dpbitmap_png( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_png( void );
        //returns width
        virtual int getWidth( void );
        //returns height
        virtual int getHeight( void );
        //get file header
        virtual bool getFileHeader( dpbuffer_static *b );
        //get IHDR chunck
        virtual bool getIHDR( dpbuffer_static *b );
        //get PLTE chunck
        virtual bool getPLTE( dpbuffer_static *b );
        //get IDAT chuncks
        virtual bool getIHDR( dpbuffer_dynamic *b );
        //get IEND chunck
        virtual bool getIEND( dpbuffer_static *b );
        //find chunck offset and size
        virtual bool findChunk( const char *cname, unsigned int loc_start, unsigned int *ploc, unsigned int *psize );

    };

};

#endif




