
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dptask_ref.h"
#include "dptask.h"
#include <string.h>

namespace dp
{

    //ctor
    dptask_ref::dptask_ref( dptask *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        std::string s;
        this->p = p;
        p->getName( &s );
        this->setName( (char *)s.c_str(), s.length() );
    }

    //dtor
    dptask_ref::~dptask_ref( void )
    {

    }

    //get name
    void dptask_ref::getName( std::string *s )
    {
        s->assign( this->cname );
    }

    //set name
    void dptask_ref::setName( char *cname, unsigned int sz )
    {
        if( sz > sizeof( this->cname ) )
            sz = sizeof( this->cname );
        memcpy( this->cname, cname, sz );
    }

}





