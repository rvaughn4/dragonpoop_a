
/*

*/

#ifndef dpbuffer_wrapper_h
#define dpbuffer_wrapper_h

#include "../dpbuffer/dpbuffer.h"

namespace dp
{

    class dpbuffer_wrapper : public dpbuffer
    {

    private:

        dpbuffer *b;

    protected:

        //ctor
        dpbuffer_wrapper( void );
        //set wrapped
        void setWrapped( dpbuffer *b );

    public:

        //ctor
        dpbuffer_wrapper( dpbuffer *b );
        //dtor
        virtual ~dpbuffer_wrapper( void );
        //return read byte cursor
        virtual unsigned int getReadByteCursor( void );
        //set read byte cursor
        virtual void setReadByteCursor( unsigned int c );
        //return write byte cursor
        virtual unsigned int getWriteByteCursor( void );
        //set write byte cursor
        virtual void setWriteByteCursor( unsigned int c );
        //return read bit cursor
        virtual unsigned int getReadBitCursor( void );
        //set read bit cursor
        virtual void setReadBitCursor( unsigned int c );
        //return write bit cursor
        virtual unsigned int getWriteBitCursor( void );
        //set write bit cursor
        virtual void setWriteBitCursor( unsigned int c );
        //return bit offset in current byte for read cursor
        virtual unsigned int getReadBitOffset( void );
        //return bit offset in current byte for write cursor
        virtual unsigned int getWriteBitOffset( void );
        //read bit, returns true if read
        virtual bool readBit( bool *b );
        //write bit, returns true if written
        virtual bool writeBit( bool b );
        //read aligned byte, returns true if read
        virtual bool readAlignedByte( uint8_t *b );
        //write aligned byte, returns true if written
        virtual bool writeAlignedByte( uint8_t b );
        //read aligned byte, returns true if read
        virtual bool readUnalignedByte( uint8_t *b );
        //write aligned byte, returns true if written
        virtual bool writeUnalignedByte( uint8_t b );
        //read aligned byte, returns true if read
        virtual bool readUnalignedByte( uint8_t *b, unsigned int sz );
        //write aligned byte, returns true if written
        virtual bool writeUnalignedByte( uint8_t b, unsigned int sz );
        //read aligned bytes into buffer until all are read
        virtual bool readAlignedBytes( dpbuffer *b );
        //read aligned bytes into buffer until cnt bytes are read
        virtual bool readAlignedBytes( dpbuffer *b, unsigned int cnt );
        //read aligned bytes into buffer until all are read
        virtual bool readAlignedBytes( char *b, unsigned int sz );
        //read aligned bytes into buffer until cnt bytes are read
        virtual bool readAlignedBytes( char *b, unsigned int sz, unsigned int cnt );
        //write aligned bytes from buffer until all are written
        virtual bool writeAlignedBytes( dpbuffer *b );
        //write aligned bytes from buffer until cnt bytes are written
        virtual bool writeAlignedBytes( dpbuffer *b, unsigned int cnt );
        //write aligned bytes from buffer until all are written
        virtual bool writeAlignedBytes( char *b, unsigned int sz );
        //write aligned bytes from buffer until cnt bytes are written
        virtual bool writeAlignedBytes( char *b, unsigned int sz, unsigned int cnt );
        //return size in bytes
        virtual unsigned int getSize( void );
        //return size in bits
        virtual unsigned int getSizeBits( void );
        //copy buffer into this buffer
        virtual void copy( dpbuffer *b );
        //get pointer to buffer
        virtual char *getBuffer( void );
        //get section at offset with size
        virtual bool getSection( dpbuffer_static *bs, unsigned int offset, unsigned int sz );
        //load buffer from buffer
        virtual bool load( dpbuffer *b );
        //load buffer from file
        virtual bool load( const char *fname );
        //save buffer to file
        virtual bool save( const char *fname );
        //save buffer to buffer
        virtual bool save( dpbuffer *b );

    };

};

#endif

