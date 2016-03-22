
#ifndef dpapi_opengl1o5_functions_h
#define dpapi_opengl1o5_functions_h

namespace dp
{

    typedef int opengl1o5_lib_GLint;
    typedef unsigned int opengl1o5_lib_GLuint;
    typedef int opengl1o5_lib_GLenum;
    typedef int opengl1o5_lib_GLsizei;
    typedef void opengl1o5_lib_GLvoid;
    typedef unsigned char opengl1o5_lib_GLubyte;
    typedef float opengl1o5_lib_GLfloat;
    typedef double opengl1o5_lib_GLdouble;
    typedef unsigned int opengl1o5_lib_GLbitfield;

    #define opengl1o5_lib_VENDOR				0x1F00
    #define opengl1o5_lib_RENDERER				0x1F01
    #define opengl1o5_lib_VERSION				0x1F02
    #define opengl1o5_lib_EXTENSIONS				0x1F03
    typedef const opengl1o5_lib_GLubyte * (* opengl1o5_lib_functions_glGetString )( opengl1o5_lib_GLenum name );

#define opengl1o5_lib_VERTEX_ARRAY				0x8074
#define opengl1o5_lib_NORMAL_ARRAY				0x8075
#define opengl1o5_lib_INDEX_ARRAY				0x8077
#define opengl1o5_lib_TEXTURE_COORD_ARRAY			0x8078

    typedef void (* opengl1o5_lib_functions_glEnableClientState )( opengl1o5_lib_GLint state );
    typedef void (* opengl1o5_lib_functions_glTexCoordPointer )( opengl1o5_lib_GLint size, opengl1o5_lib_GLenum type, opengl1o5_lib_GLsizei stride, const opengl1o5_lib_GLvoid *ptr );
    typedef void (* opengl1o5_lib_functions_glNormalPointer )( opengl1o5_lib_GLenum type, opengl1o5_lib_GLsizei stride, const opengl1o5_lib_GLvoid *ptr );
    typedef void (* opengl1o5_lib_functions_glVertexPointer )( opengl1o5_lib_GLint size, opengl1o5_lib_GLenum type, opengl1o5_lib_GLsizei stride, const opengl1o5_lib_GLvoid *ptr );
    typedef void (* opengl1o5_lib_functions_glDrawElements )( opengl1o5_lib_GLenum mode, opengl1o5_lib_GLsizei count, opengl1o5_lib_GLenum type, const opengl1o5_lib_GLvoid *indicies );
    typedef void (* opengl1o5_lib_functions_glGenTextures )( opengl1o5_lib_GLsizei n, opengl1o5_lib_GLuint *textures );
    typedef void (* opengl1o5_lib_functions_glDeleteTextures )( opengl1o5_lib_GLsizei n, opengl1o5_lib_GLuint *textures );
    typedef void (* opengl1o5_lib_functions_glBindTexture )( opengl1o5_lib_GLenum target, opengl1o5_lib_GLuint texture );
    typedef void (* opengl1o5_lib_functions_glTexImage2D )( opengl1o5_lib_GLenum target, opengl1o5_lib_GLint level, opengl1o5_lib_GLint internal_format, opengl1o5_lib_GLsizei w, opengl1o5_lib_GLsizei h, opengl1o5_lib_GLint border, opengl1o5_lib_GLenum format, opengl1o5_lib_GLenum type, opengl1o5_lib_GLvoid *pixels );
    typedef void (* opengl1o5_lib_functions_glTexParameteri )( opengl1o5_lib_GLenum target, opengl1o5_lib_GLenum pname, opengl1o5_lib_GLint param );
    typedef void (* opengl1o5_lib_functions_glClearColor )( opengl1o5_lib_GLfloat r, opengl1o5_lib_GLfloat g, opengl1o5_lib_GLfloat b, opengl1o5_lib_GLfloat a );
    typedef void (* opengl1o5_lib_functions_glClearDepth )( opengl1o5_lib_GLdouble depth );

    #define opengl1o5_lib_COLOR_BUFFER_BIT			0x00004000
    #define opengl1o5_lib_DEPTH_BUFFER_BIT			0x00000100
    typedef void (* opengl1o5_lib_functions_glClear )( opengl1o5_lib_GLbitfield mask );

    typedef void (* opengl1o5_lib_functions_glViewport )( opengl1o5_lib_GLint x, opengl1o5_lib_GLint y, opengl1o5_lib_GLsizei w, opengl1o5_lib_GLsizei h );
    typedef void (* opengl1o5_lib_functions_glDisable )( opengl1o5_lib_GLenum cap );
    typedef void (* opengl1o5_lib_functions_glEnable )( opengl1o5_lib_GLenum cap );
    typedef void (* opengl1o5_lib_functions_glPushMatrix )( void );
    typedef void (* opengl1o5_lib_functions_glPopMatrix )( void );
    typedef void (* opengl1o5_lib_functions_glMultMatrixf )( const opengl1o5_lib_GLfloat *fv );
    typedef void (* opengl1o5_lib_functions_glColor4f )( opengl1o5_lib_GLfloat r, opengl1o5_lib_GLfloat g, opengl1o5_lib_GLfloat b, opengl1o5_lib_GLfloat a );
    typedef void (* opengl1o5_lib_functions_glLightfv )( opengl1o5_lib_GLenum light, opengl1o5_lib_GLenum pname, const opengl1o5_lib_GLfloat *params );
    typedef void (* opengl1o5_lib_functions_glDepthFunc )( opengl1o5_lib_GLenum func );
    typedef void (* opengl1o5_lib_functions_glBlendFunc )( opengl1o5_lib_GLenum sfactor, opengl1o5_lib_GLenum dfactor );

#define opengl1o5_lib_TRIANGLES				0x0004
#define opengl1o5_lib_UNSIGNED_SHORT			0x1403
#define opengl1o5_lib_UNSIGNED_INT				0x1405
#define opengl1o5_lib_FLOAT				0x1406
#define opengl1o5_lib_ARRAY_BUFFER                   0x8892
#define opengl1o5_lib_ELEMENT_ARRAY_BUFFER           0x8893
#define opengl1o5_lib_STATIC_DRAW                    0x88E4
    typedef void (* opengl1o5_lib_functions_glGenBuffers )( opengl1o5_lib_GLsizei n, opengl1o5_lib_GLuint *buffers );
    typedef void (* opengl1o5_lib_functions_glBindBuffer )( opengl1o5_lib_GLenum target, opengl1o5_lib_GLuint buffer );
    typedef void (* opengl1o5_lib_functions_glBufferData )( opengl1o5_lib_GLenum target, opengl1o5_lib_GLsizei size, const opengl1o5_lib_GLvoid *data, opengl1o5_lib_GLenum usage );
    typedef void (* opengl1o5_lib_functions_glDeleteBuffers )( opengl1o5_lib_GLsizei n, opengl1o5_lib_GLuint *buffers );
    typedef void (* opengl1o5_lib_functions_glCopyBufferSubData )( opengl1o5_lib_GLenum readtarget, opengl1o5_lib_GLenum writetarget, opengl1o5_lib_GLint readoffset, opengl1o5_lib_GLint writeoffset, opengl1o5_lib_GLsizei size );
    typedef void (* opengl1o5_lib_functions_glFlush )( void );
    typedef opengl1o5_lib_GLenum (* opengl1o5_lib_functions_glGetError )( void );
    typedef void (* opengl1o5_lib_functions_glDeleteLists )( opengl1o5_lib_GLuint list, opengl1o5_lib_GLsizei range );
    typedef opengl1o5_lib_GLuint (* opengl1o5_lib_functions_glGenLists )( opengl1o5_lib_GLsizei range );
    typedef void (* opengl1o5_lib_functions_glNewList )( opengl1o5_lib_GLuint list, opengl1o5_lib_GLenum mode );
    typedef void (* opengl1o5_lib_functions_glEndList )( void );
    typedef void (* opengl1o5_lib_functions_glCallList )( opengl1o5_lib_GLuint list );

    struct opengl1o5_lib_functions
    {
        struct
        {
            unsigned int major, minor;
        } version;

        opengl1o5_lib_functions_glGetString glGetString;
        opengl1o5_lib_functions_glGetError glGetError;
        opengl1o5_lib_functions_glFlush glFlush;
        opengl1o5_lib_functions_glEnableClientState glEnableClientState;
        opengl1o5_lib_functions_glTexCoordPointer glTexCoordPointer;
        opengl1o5_lib_functions_glNormalPointer glNormalPointer;
        opengl1o5_lib_functions_glVertexPointer glVertexPointer;
        opengl1o5_lib_functions_glDrawElements glDrawElements;
        opengl1o5_lib_functions_glGenTextures glGenTextures;
        opengl1o5_lib_functions_glDeleteTextures glDeleteTextures;
        opengl1o5_lib_functions_glBindTexture glBindTexture;
        opengl1o5_lib_functions_glTexImage2D glTexImage2D;
        opengl1o5_lib_functions_glTexParameteri glTexParameteri;
        opengl1o5_lib_functions_glClearColor glClearColor;
        opengl1o5_lib_functions_glClearDepth glClearDepth;
        opengl1o5_lib_functions_glClear glClear;
        opengl1o5_lib_functions_glViewport glViewport;
        opengl1o5_lib_functions_glDisable glDisable;
        opengl1o5_lib_functions_glEnable glEnable;
        opengl1o5_lib_functions_glPushMatrix glPushMatrix;
        opengl1o5_lib_functions_glPopMatrix glPopMatrix;
        opengl1o5_lib_functions_glMultMatrixf glMultMatrixf;
        opengl1o5_lib_functions_glColor4f glColor4f;
        opengl1o5_lib_functions_glLightfv glLightfv;
        opengl1o5_lib_functions_glDepthFunc glDepthFunc;
        opengl1o5_lib_functions_glBlendFunc glBlendFunc;
        opengl1o5_lib_functions_glGenBuffers glGenBuffers;
        opengl1o5_lib_functions_glBindBuffer glBindBuffer;
        opengl1o5_lib_functions_glBufferData glBufferData;
        opengl1o5_lib_functions_glDeleteBuffers glDeleteBuffers;
        opengl1o5_lib_functions_glCopyBufferSubData glCopyBufferSubData;
        bool bUseVB;
        opengl1o5_lib_functions_glDeleteLists glDeleteLists;
        opengl1o5_lib_functions_glGenLists glGenLists;
        opengl1o5_lib_functions_glNewList glNewList;
        opengl1o5_lib_functions_glEndList glEndList;
        opengl1o5_lib_functions_glCallList glCallList;
    };

};

#endif
