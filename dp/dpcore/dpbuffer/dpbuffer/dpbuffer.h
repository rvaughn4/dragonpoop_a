
/*

*/

#ifndef dpbuffer_h
#define dpbuffer_h

#include <stdint.h>

namespace dp
{

        class dpbuffer
        {

        private:

        protected:

            //ctor
            dpbuffer( void );

        public:

            //dtor
            virtual ~dpbuffer( void );
            //return read byte cursor
            virtual unsigned int getReadByteCursor( void ) = 0;
            //set read byte cursor
            virtual void setReadByteCursor( unsigned int c ) = 0;
            //return write byte cursor
            virtual unsigned int getWriteByteCursor( void ) = 0;
            //set write byte cursor
            virtual void setWriteByteCursor( unsigned int c ) = 0;
            //return read bit cursor
            virtual unsigned int getReadBitCursor( void ) = 0;
            //set read bit cursor
            virtual void setReadBitCursor( unsigned int c ) = 0;
            //return write bit cursor
            virtual unsigned int getWriteBitCursor( void ) = 0;
            //set write bit cursor
            virtual void setWriteBitCursor( unsigned int c ) = 0;
            //return bit offset in current byte for read cursor
            virtual unsigned int getReadBitOffset( void ) = 0;
            //return bit offset in current byte for write cursor
            virtual unsigned int getWriteBitOffset( void ) = 0;
            //read bit, returns true if read
            virtual bool readBit( bool *b ) = 0;
            //write bit, returns true if written
            virtual bool writeBit( bool b ) = 0;
            //read aligned byte, returns true if read
            virtual bool readAlignedByte( uint8_t *b ) = 0;
            //write aligned byte, returns true if written
            virtual bool writeAlignedByte( uint8_t b ) = 0;
            //read aligned byte, returns true if read
            virtual bool readUnalignedByte( uint8_t *b ) = 0;
            //write aligned byte, returns true if written
            virtual bool writeUnalignedByte( uint8_t b ) = 0;
            //read aligned bytes into buffer until all are read
            virtual bool readAlignedBytes( dpbuffer *b ) = 0;
            //read aligned bytes into buffer until cnt bytes are read
            virtual bool readAlignedBytes( dpbuffer *b, unsigned int cnt ) = 0;
            //read aligned bytes into buffer until all are read
            virtual bool readAlignedBytes( char *b, unsigned int sz ) = 0;
            //read aligned bytes into buffer until cnt bytes are read
            virtual bool readAlignedBytes( char *b, unsigned int sz, unsigned int cnt ) = 0;
            //write aligned bytes from buffer until all are written
            virtual bool writeAlignedBytes( dpbuffer *b ) = 0;
            //write aligned bytes from buffer until cnt bytes are written
            virtual bool writeAlignedBytes( dpbuffer *b, unsigned int cnt ) = 0;
            //write aligned bytes from buffer until all are written
            virtual bool writeAlignedBytes( char *b, unsigned int sz ) = 0;
            //write aligned bytes from buffer until cnt bytes are written
            virtual bool writeAlignedBytes( char *b, unsigned int sz, unsigned int cnt ) = 0;
            //return size in bytes
            virtual unsigned int getSize( void ) = 0;
            //return size in bits
            virtual unsigned int getSizeBits( void ) = 0;
            //copy buffer into this buffer
            virtual void copy( dpbuffer *b ) = 0;
            //get pointer to buffer
            virtual char *getBuffer( void ) = 0;

        };

};

#endif
