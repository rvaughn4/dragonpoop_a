
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

        //returns buffer
        virtual char *_getBuffer( void );
        //returns size of buffer (override)
        virtual unsigned int _getSize( void );
        //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
        virtual bool _autoResize( unsigned int sz );
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

    };

};

#endif

