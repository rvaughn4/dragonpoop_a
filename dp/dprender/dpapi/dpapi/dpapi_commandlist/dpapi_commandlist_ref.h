
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_commandlist_ref_h
#define dpapi_commandlist_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_commandlist;
    class dpapi_commandlist_readlock;
    class dpapi_commandlist_writelock;

    class dpapi_commandlist_ref : public dpshared_ref
    {

    private:

        dpapi_commandlist *p;

    protected:

        //dtor
        virtual ~dpapi_commandlist_ref( void );

    public:

        //ctor
        dpapi_commandlist_ref( dpapi_commandlist *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_commandlist;
    };

}

#endif








