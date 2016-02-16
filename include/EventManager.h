#ifndef ENGINE_EVENTMANAGER_H
#define ENGINE_EVENTMANAGER_H


namespace Capstan
{
    struct Event
    {
        void * message;
    };


    class EventManager
    {
    public:
        EventManager ();
        ~EventManager ();

        void StartUp (void);
        void ShutDown (void);
    private:
        Event * queue;
    };
}


#endif
