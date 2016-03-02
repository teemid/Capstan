#ifndef CAPSTAN_INPUT_MANAGER_H
#define CAPSTAN_INPUT_MANAGER_H


namespace Capstan
{
    class InputManager
    {
    public:
        InputManager (void);
        ~InputManager (void);

        void StartUp (void);
        void ShutDown (void);
    };
}


#endif
