
/*

*/

#ifndef dpbitmap_uncompressed_h
#define dpbitmap_uncompressed_h

#include "../dpbitmap/dpbitmap.h"
#include "../../../dpcore/dpbuffer/dpbuffer_static/dpbuffer_static.h"

namespace dp
{

#pragma pack( 1 )
//BITMAPFILEHEADER
    struct dpbitmap_uncompressed_file_header
    {
        uint16_t bfType;    //The file type; must be BM.
        uint32_t bfSize;    //The size, in bytes, of the bitmap file.
        uint16_t bfReserved1;   //0
        uint16_t bfReserved2;   //0
        uint32_t bfOffBits; //The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
    };

//BITMAPCOREHEADER //OS21XBITMAPHEADER
    struct dpbitmap_uncompressed_core_header
    {
        uint32_t    bcSize;     //size of header
        uint16_t    bcWidth;    //width unsigned
        uint16_t    bcHeight;   //height unsigned
        uint16_t    bcPlanes;   //1
        uint16_t    bcBitCount; //bits per pixel, 1, 2, 4, 8, 24
    };

//OS22XBITMAPHEADER
    struct dpbitmap_uncompressed_os2v2_header
    {
        dpbitmap_uncompressed_core_header h1;
        uint32_t    biCompression;  //use flags below
        uint32_t    biSizeImage;    //size of pixel data
        uint32_t    biXPelsPerMeter;    //pixels per meter
        uint32_t    biYPelsPerMeter;    //pixels per meter
        uint32_t    biClrUsed;      //# of palette colors used
        uint32_t    biClrImportant; //# of palette colors needed
        uint16_t    biUnits;        //type of units measured resolution
        uint16_t    biReserved;
        uint16_t    biRecording;    //recording algorithm
        uint16_t    biRendering;    //halftoning algorithm used
        uint32_t    biRenderingSize1;
        uint32_t    biRenderingSize2;
        uint32_t    biColorEncoding;    //color model
        uint32_t    biIdentifier;       //reserved for app use
    };

//BITMAPINFOHEADER
    struct dpbitmap_uncompressed_winv3_header
    {
        uint32_t    biSize;     //size of header
        int32_t     biWidth;    //width signed
        int32_t     biHeight;   //height signed, negative is right side up
        uint16_t    biPlanes;   //1
        uint16_t    biBitCount; //bits per pixel 0, 1, 4, 8, 16, 24, 32
        uint32_t    biCompression;  //use flags below
        uint32_t    biSizeImage;    //size of pixel data
        int32_t     biXPelsPerMeter;    //pixels per meter
        int32_t     biYPelsPerMeter;    //pixels per meter
        uint32_t    biClrUsed;      //# of palette colors used
        uint32_t    biClrImportant; //# of palette colors needed
    };

//BI_RGB
    #define			dpbitmap_uncompressed_winv1_header_BI_RGB               0
//BI_RLE8
    #define			dpbitmap_uncompressed_winv1_header_BI_RLE8              1
//BI_RLE4
    #define			dpbitmap_uncompressed_winv1_header_BI_RLE4              2
//BI_BITFIELDS
    #define			dpbitmap_uncompressed_winv2_header_BI_BITFIELDS		    3
//BI_HUFFMAN_1D
    #define         dpbitmap_uncompressed_os2v2_header_BI_HUFFMAN_1D        3
//BI_RLE24
    #define         dpbitmap_uncompressed_os2v2_header_BI_RLE24             4
//BI_JPEG
    #define         dpbitmap_uncompressed_winv1_header_BI_JPEG              4
//BI_PNG
    #define         dpbitmap_uncompressed_winv1_header_BI_PNG               5
//BI_ALPHABITFIELDS
    #define         dpbitmap_uncompressed_winv3_header_BI_ALPHABITFIELDS    6
//BI_SRCPREROTATE	0x8000 (?)
    #define         dpbitmap_uncompressed_winv1_header_BI_SRCPREROTATE      0x8000

//BITMAPV2HEADER
    struct dpbitmap_uncompressed_winv3NT_header
    {
        dpbitmap_uncompressed_winv3_header h;
        uint32_t    biRedMask;
        uint32_t    biGreenMask;
        uint32_t    biBlueMask;
    };

//BITMAPV3HEADER
    struct dpbitmap_uncompressed_winv3NT2_header
    {
        dpbitmap_uncompressed_winv3NT_header h;
        uint32_t    biAlphaMask;
    };

//CIEXYZ
    struct dpbitmap_uncompressed_winv4_header_CIEXYZ
    {
        int32_t x, y, z;
    };

//CIEXYZTRIPLE
    struct dpbitmap_uncompressed_winv4_header_CIEXYZTRIPLE
    {
        dpbitmap_uncompressed_winv4_header_CIEXYZ r, g, b;
    };

//BITMAPV4HEADER
    struct dpbitmap_uncompressed_winv4_header
    {
        dpbitmap_uncompressed_winv3NT2_header h;
        uint32_t    biCsType;                   //The color space of the DIB.
        dpbitmap_uncompressed_winv4_header_CIEXYZTRIPLE
                    biEndpoints;                //A CIEXYZTRIPLE structure that specifies the x, y, and z coordinates of the three colors that correspond to the red, green, and blue endpoints for the logical color space associated with the bitmap.
        uint32_t    biGammaRed;                 //Toned response curve for red. Used if bV5CSType is set to LCS_CALIBRATED_RGB. Specify in unsigned fixed 16.16 format. The upper 16 bits are the unsigned integer value. The lower 16 bits are the fractional part.
        uint32_t    biGammaGreen;
        uint32_t    biGammaBlue;
    };

//LCS_CALIBRATED_RGB
    #define dpbitmap_uncompressed_winv4_header_LCS_CALIBRATED_RGB           0x0
//LCS_sRGB
    #define dpbitmap_uncompressed_winv4_header_LCS_sRGB                     0x73524742
//LCS_WINDOWS_COLOR_SPACE
    #define dpbitmap_uncompressed_winv4_header_LCS_WINDOWS_COLOR_SPACE      0x57696E20

//BITMAPV5HEADER
    struct dpbitmap_uncompressed_winv5_header
    {
        dpbitmap_uncompressed_winv4_header h;
        uint32_t    biIntent;
        uint32_t    biProfileData;
        uint32_t    biProfileSize;
        uint32_t    bireserved;
    };

#pragma pack()

    class dpbitmap_uncompressed : public dpbitmap
    {

    private:

    protected:

        //ctor
        dpbitmap_uncompressed( int w, int h, int bits, int bitmap_header_size, int offset_to_pixels, int file_size );
        //ctor
        dpbitmap_uncompressed( dpbuffer *b );
        //return default red mask
        virtual uint32_t getRedMask( void ) = 0;
        //return default green mask
        virtual uint32_t getGreenMask( void ) = 0;
        //return default blue mask
        virtual uint32_t getBlueMask( void ) = 0;
        //return default alpha mask
        virtual uint32_t getAlphaMask( void ) = 0;

    public:

        //dtor
        virtual ~dpbitmap_uncompressed( void );
        //set pixel color
        virtual bool setPixel( int x, int y, dpbitmap_color *c );
        //get pixel color
        virtual bool getPixel( int x, int y, dpbitmap_color *c );
        //returns width
        virtual int getWidth( void );
        //returns height
        virtual int getHeight( void );
        //returns bits per pixel
        virtual int getBits( void ) = 0;
        //returns scan line length
        virtual unsigned int getScanSize( void ) = 0;
        //get file header
        virtual bool getFileHeader( dpbuffer_static *b );
        //get bitmap header
        virtual bool getBitmapHeader( dpbuffer_static *b );
        //get pixel data
        virtual bool getPixelData( dpbuffer_static *b );
        //get extra data
        virtual bool getExtraData( dpbuffer_static *b );

    };

};

#endif



