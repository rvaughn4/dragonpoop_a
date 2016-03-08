
/*

*/

#include "dpapi_opengl1o5.h"
#include "dpapi_opengl1o5_ref.h"
#include "dpapi_opengl1o5_readlock.h"
#include "dpapi_opengl1o5_writelock.h"
#include <sstream>

namespace dp
{

    //ctor
    dpapi_opengl1o5::dpapi_opengl1o5( dpwindow_factory *wf ) : dpapi( wf )
    {

    }

    //dtor
    dpapi_opengl1o5::~dpapi_opengl1o5( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_ref( this, k, t_sync );
    }

    //override to init api
    bool dpapi_opengl1o5::initApi( dpwindow_writelock *wl, dpapi_writelock *aal )
    {
        opengl1o5_lib_functions *pgl;
        dpapi_opengl1o5_writelock *al = (dpapi_opengl1o5_writelock *)aal;
        bool r;
        const char *c;
        std::size_t p0, p1;
        std::string s;

        al = (dpapi_opengl1o5_writelock *)aal;
        if( !this->loadGL( wl, al ) )
            return 0;

        r = 1;
        r &= ( this->gl.glGetString = (opengl1o5_lib_functions_glGetString)this->loadFunction( wl, al, "glGetString" ) ) != 0;
        r &= ( this->gl.glEnableClientState = (opengl1o5_lib_functions_glEnableClientState)this->loadFunction( wl, al, "glEnableClientState" ) ) != 0;
        r &= ( this->gl.glGenTextures = (opengl1o5_lib_functions_glGenTextures)this->loadFunction( wl, al, "glGenTextures" ) ) != 0;
        r &= ( this->gl.glDeleteTextures = (opengl1o5_lib_functions_glDeleteTextures)this->loadFunction( wl, al, "glDeleteTextures" ) ) != 0;
        r &= ( this->gl.glBindTexture = (opengl1o5_lib_functions_glBindTexture)this->loadFunction( wl, al, "glBindTexture" ) ) != 0;
        r &= ( this->gl.glDrawElements = (opengl1o5_lib_functions_glDrawElements)this->loadFunction( wl, al, "glDrawElements" ) ) != 0;
        r &= ( this->gl.glTexCoordPointer = (opengl1o5_lib_functions_glTexCoordPointer)this->loadFunction( wl, al, "glTexCoordPointer" ) ) != 0;
        r &= ( this->gl.glNormalPointer = (opengl1o5_lib_functions_glNormalPointer)this->loadFunction( wl, al, "glNormalPointer" ) ) != 0;
        r &= ( this->gl.glVertexPointer = (opengl1o5_lib_functions_glVertexPointer)this->loadFunction( wl, al, "glVertexPointer" ) ) != 0;
        r &= ( this->gl.glTexImage2D = (opengl1o5_lib_functions_glTexImage2D)this->loadFunction( wl, al, "glTexImage2D" ) ) != 0;
        r &= ( this->gl.glTexParameteri = (opengl1o5_lib_functions_glTexParameteri)this->loadFunction( wl, al, "glTexParameteri" ) ) != 0;
        r &= ( this->gl.glClearColor = (opengl1o5_lib_functions_glClearColor)this->loadFunction( wl, al, "glClearColor" ) ) != 0;
        r &= ( this->gl.glClearDepth = (opengl1o5_lib_functions_glClearDepth)this->loadFunction( wl, al, "glClearDepth" ) ) != 0;
        r &= ( this->gl.glClear = (opengl1o5_lib_functions_glClear)this->loadFunction( wl, al, "glClear" ) ) != 0;
        r &= ( this->gl.glViewport = (opengl1o5_lib_functions_glViewport)this->loadFunction( wl, al, "glViewport" ) ) != 0;
        r &= ( this->gl.glDisable = (opengl1o5_lib_functions_glDisable)this->loadFunction( wl, al, "glDisable" ) ) != 0;
        r &= ( this->gl.glEnable = (opengl1o5_lib_functions_glEnable)this->loadFunction( wl, al, "glEnable" ) ) != 0;
        r &= ( this->gl.glPushMatrix = (opengl1o5_lib_functions_glPushMatrix)this->loadFunction( wl, al, "glPushMatrix" ) ) != 0;
        r &= ( this->gl.glPopMatrix = (opengl1o5_lib_functions_glPopMatrix)this->loadFunction( wl, al, "glPopMatrix" ) ) != 0;
        r &= ( this->gl.glMultMatrixf = (opengl1o5_lib_functions_glMultMatrixf)this->loadFunction( wl, al, "glMultMatrixf" ) ) != 0;
        r &= ( this->gl.glColor4f = (opengl1o5_lib_functions_glColor4f)this->loadFunction( wl, al, "glColor4f" ) ) != 0;
        r &= ( this->gl.glLightfv = (opengl1o5_lib_functions_glLightfv)this->loadFunction( wl, al, "glLightfv" ) ) != 0;
        r &= ( this->gl.glDepthFunc = (opengl1o5_lib_functions_glDepthFunc)this->loadFunction( wl, al, "glDepthFunc" ) ) != 0;
        r &= ( this->gl.glBlendFunc = (opengl1o5_lib_functions_glBlendFunc)this->loadFunction( wl, al, "glBlendFunc" ) ) != 0;
        r &= ( this->gl.glFlush = (opengl1o5_lib_functions_glFlush)this->loadFunction( wl, al, "glFlush" ) ) != 0;
        r &= ( this->gl.glGetError = (opengl1o5_lib_functions_glGetError)this->loadFunction( wl, al, "glGetError" ) ) != 0;
        r &= ( this->gl.glDeleteLists = (opengl1o5_lib_functions_glDeleteLists)this->loadFunction( wl, al, "glDeleteLists" ) ) != 0;
        r &= ( this->gl.glGenLists = (opengl1o5_lib_functions_glGenLists)this->loadFunction( wl, al, "glGenLists" ) ) != 0;
        r &= ( this->gl.glNewList = (opengl1o5_lib_functions_glNewList)this->loadFunction( wl, al, "glNewList" ) ) != 0;
        r &= ( this->gl.glEndList = (opengl1o5_lib_functions_glEndList)this->loadFunction( wl, al, "glEndList" ) ) != 0;
        r &= ( this->gl.glCallList = (opengl1o5_lib_functions_glCallList)this->loadFunction( wl, al, "glCallList" ) ) != 0;

        if( !r )
            return 0;


        //get version and extensions
        c = (const char *)this->gl.glGetString( opengl1o5_lib_VERSION );
        if( c )
            this->sver.assign( c );
        c = (const char *)this->gl.glGetString( opengl1o5_lib_EXTENSIONS );
        if( c )
            this->sext.assign( c );

        //extract version number
        p1 = this->sver.size();
        p0 = this->sver.find( "." );
        if( p0 + 1 < p1 )
            p1 = this->sver.find( ".", p0 + 1 );
        if( p0 < this->sver.size() )
        {
            std::stringstream ss;
            s = this->sver.substr( 0, p0 );
            ss << s;
            ss >> this->gl.version.major;
        }
        if( p1 >= this->sver.size() )
            p1 = this->sver.size();
        if( p0 + 1 < this->sver.size() && p1 > p0 )
        {
            std::stringstream ss;
            s = this->sver.substr( p0 + 1, p1 - p0 - 1 );
            ss << s;
            ss >> this->gl.version.minor;
        }

        //get vbo extension
        this->gl.glGenBuffers = (opengl1o5_lib_functions_glGenBuffers)this->loadFunction( wl, al, "glGenBuffers" );
        if( !this->gl.glGenBuffers )
            this->gl.glGenBuffers = (opengl1o5_lib_functions_glGenBuffers)this->loadFunction( wl, al, "glGenBuffersARB" );
        this->gl.glBindBuffer = (opengl1o5_lib_functions_glBindBuffer)this->loadFunction( wl, al, "glBindBuffer" );
        if( !this->gl.glBindBuffer )
            this->gl.glBindBuffer = (opengl1o5_lib_functions_glBindBuffer)this->loadFunction( wl, al, "glBindBufferARB" );
        this->gl.glBufferData = (opengl1o5_lib_functions_glBufferData)this->loadFunction( wl, al, "glBufferData" );
        if( !this->gl.glBufferData )
            this->gl.glBufferData = (opengl1o5_lib_functions_glBufferData)this->loadFunction( wl, al, "glBufferDataARB" );
        this->gl.glDeleteBuffers = (opengl1o5_lib_functions_glDeleteBuffers)this->loadFunction( wl, al, "glDeleteBuffers" );
        if( !this->gl.glDeleteBuffers )
            this->gl.glDeleteBuffers = (opengl1o5_lib_functions_glDeleteBuffers)this->loadFunction( wl, al, "glDeleteBuffersARB" );
        this->gl.bUseVB = this->gl.glGenBuffers != 0 && this->gl.glDeleteBuffers != 0 && this->gl.glBindBuffer != 0 && this->gl.glBufferData != 0;

        p0 = this->sext.find( "GL_ARB_vertex_buffer_object" );
        if( p0 < this->sext.size() )
            this->gl.bUseVB &= 1;
        else
            this->gl.bUseVB = 0;

        pgl = this->getGL();
        if( pgl )
            *pgl = this->gl;

        return 1;
    }

    //override to generate rendering context
    dpapi_context *dpapi_opengl1o5::makeContext( dpapi_writelock *al )
    {
        return this->dpapi::makeContext( al );
    }

    //override to load opengl library
    bool dpapi_opengl1o5::loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al )
    {
        return 0;
    }

    //override to handle loading of function pointers
    void *dpapi_opengl1o5::loadFunction( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al, const char *cname )
    {
        return 0;
    }

    //override to provide pointer to gl function pointers
    opengl1o5_lib_functions *dpapi_opengl1o5::getGL( void )
    {
        return 0;
    }

    //override to handle end of frame
    void dpapi_opengl1o5::onFrameEnd( void )
    {

    }

    //override to handle start of frame
    void dpapi_opengl1o5::onFrameStart( void )
    {
        this->gl.glClearDepth( 1.0 );
        this->gl.glClearColor( 1, 1, 1, 1 );
        this->gl.glClear( opengl1o5_lib_COLOR_BUFFER_BIT | opengl1o5_lib_DEPTH_BUFFER_BIT );
    }

}







