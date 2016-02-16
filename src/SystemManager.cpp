#include <stdarg.h>

#include "SystemManager.h"

#include "assert.h"


namespace Capstan
{
namespace System
{
    Bool32 Start (Type system, ...)
    {
        switch (system)
        {
            case Type::Asset:
            {
                va_list args;
                va_start(args, system);

                size_t reserve = va_arg(args, size_t);

                gAssetManager.StartUp(reserve);

                va_end(args);
            } break;
            case Type::Renderer:
            {
                gRenderManager.StartUp();
            } break;
            case Type::Memory:
            {
                va_list args;
                va_start(args, system);

                size_t reserve = va_arg(args, size_t);

                gMemoryManager.StartUp(reserve);

                va_end(args);
            } break;
            default:
            {
                Debug::OutputString("Tried to start up illegal system.");
                assert(false);

                return false;
            } break;
        }

        return true;
    }

    Bool32 ShutDown (Type system)
    {
        switch (system)
        {
            case Type::Asset:
            {
                gAssetManager.ShutDown();
            } break;
            case Type::Renderer:
            {
                gRenderManager.ShutDown();
            } break;
            case Type::Memory:
            {
                gMemoryManager.ShutDown();
            } break;
            default:
            {
                Debug::OutputString("Tried to shut down illegal system.");
                assert(false);

                return false;
            } break;
        }

        return true;
    }

    void * Get (Type system)
    {
        switch (system)
        {
            case Type::Asset:
            {
                void * ptr = &gAssetManager;

                return ptr;
            } break;
            case Type::Memory:
            {
                void * ptr = &gMemoryManager;

                return ptr;
            } break;
            case Type::Renderer:
            {
                void * ptr = &gRenderManager;

                return ptr;
            } break;
            default:
            {
                Debug::OutputString("Illegal system value");
                assert(false);

                return nullptr;
            }
        }
    }
}
}
