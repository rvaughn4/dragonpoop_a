
/*

*/

#ifndef dpinput_h
#define dpinput_h

#include "../../dpcore/dpshared/dpshared.h"

namespace dp
{

    #define dpinput_event_type_mouse 0
    #define dpinput_event_type_keypress 1
    #define dpinput_event_type_text 2

    struct dpinput_event_header
    {
        uint8_t etype;
        uint64_t t;
    };

    struct dpinput_event_mouse
    {
        dpinput_event_header h;
        float x, y;
        bool isRight, isDown;
    };

    #define dpinput_event_keypress_name_max 24
    struct dpinput_event_keypress
    {
        dpinput_event_header h;
        bool bIsDown;
        char keyName[ dpinput_event_keypress_name_max ];
    };

    #define dpinput_event_text_txt_max 32
    struct dpinput_event_text
    {
        dpinput_event_header h;
        char txt[ dpinput_event_text_txt_max ];
    };

    struct dpinput_event
    {
        union
        {
            dpinput_event_header h;
            dpinput_event_mouse mse;
            dpinput_event_keypress keyp;
            dpinput_event_text txt;
        };
    };

    class dpinput_readlock;
    class dpinput_writelock;

    #define dpinput_events_max 200
    class dpinput : public dpshared
    {

    private:

        dpinput_event events[ dpinput_events_max ];

        //returns next free event or oldest event
        dpinput_event *allocEvent( void );
        //get newest event time
        uint64_t getNewestTime( void );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //override to handle processing
        virtual void onRun( dpshared_writelock *wl );
        //add mouse event
        virtual void addMouseEvent( float x, float y, bool bIsRight, bool bIsDown );
        //add keypress event
        virtual void addKeyPressEvent( bool bIsDown, std::string *sname );
        //add text event
        virtual void addTextEvent( std::string *stxt );
        //add event
        virtual void addEvent( dpinput_event *e );
        //get events newer than time
        virtual unsigned int getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t );

    public:

        //ctor
        dpinput( void );
        //dtor
        virtual ~dpinput( void );

        friend class dpinput_writelock;
        friend class dpinput_readlock;
    };

}

#endif





