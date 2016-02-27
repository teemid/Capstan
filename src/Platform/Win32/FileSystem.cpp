#include <windows.h>

#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/FileSystem.h"
#include "Platform/Win32/Debug.h"

#include "MemoryManager.h"
#include "SystemManager.h"


namespace Capstan
{
    // NOTE (Emil): I don't know if this needs padding or not.
    struct PlatformFileData
    {
        HANDLE handle; // typedef PVOID HANDLE
        // OVERLAPPED struct?
        UInt8 index;
    };

    FileSystem::FileSystem (void) { };
    FileSystem::~FileSystem (void) { };

    Int32 FileSystem::maxAsyncReads = 16;
    PlatformFileData * FileSystem::fileList = nullptr;

    void FileSystem::StartUp (void)
    {
        MemoryManager * gMemoryManager = (MemoryManager *)System::Get(System::Type::Memory);

        FileSystem::fileList = (PlatformFileData *)gMemoryManager->Allocate(sizeof(PlatformFileData) * FileSystem::maxAsyncReads);
    }

    void FileSystem::ShutDown (void)
    {
        MemoryManager * gMemoryManager = (MemoryManager *)System::Get(System::Type::Memory);

        gMemoryManager->Free((void *)FileSystem::fileList);
    }

    internal DWORD inline GetAccessRights (Int32 mode)
    {
        // using Mode = FileSystem::Mode;

        DWORD accessRights = 0;
        if (mode & FileSystem::ReadFlag) { accessRights |= GENERIC_READ; }
        else if (mode & FileSystem::WriteFlag) { accessRights |= GENERIC_WRITE; }

        assert(accessRights);

        Debug::OutputString("Access rights: %d\n", accessRights);

        return accessRights;
    }

    internal DWORD inline GetFileAttributes (Int32 mode)
    {
        // using Mode = FileSystem::Mode;

        DWORD fileAttributes = FILE_ATTRIBUTE_NORMAL;
        if (mode & FileSystem::SequentialFlag)
        {
            fileAttributes |= FILE_FLAG_SEQUENTIAL_SCAN;
        }
        else if (mode & FileSystem::RandomAccessFlag)
        {
            fileAttributes |= FILE_FLAG_RANDOM_ACCESS;
        }

        Debug::OutputString("File Attributes %d\n", fileAttributes);

        return fileAttributes;
    }

    Bool32 FileSystem::Create (char * filename, File * file, Int32 mode)
    {
        file->platform = FileSystem::fileList;
        file->platform->handle = CreateFile(
            (LPCSTR)filename,
            GetAccessRights(mode),
            0,
            NULL,
            CREATE_NEW,
            GetFileAttributes(mode),
            NULL
        );

        if (file->platform->handle == INVALID_HANDLE_VALUE)
        {
            Debug::Win32HandleError();

            return false;
        }

        file->open = true;
        file->size = 0;

        return true;
    }

    Bool32 FileSystem::Open (char * filename, File * file, Int32 mode)
    {
        // NOTE (Emil): Take the first element every time, since we're only doing sync reads.
        file->platform = FileSystem::fileList;
        file->platform->handle = CreateFile(
            (LPCSTR)filename,
            GetAccessRights(mode),
            0,
            NULL,
            OPEN_EXISTING,
            GetFileAttributes(mode),
            NULL
        );

        LARGE_INTEGER fileSize;
        DWORD result = GetFileSizeEx(file->platform->handle, &fileSize);

        if (result == INVALID_FILE_SIZE)
        {
            Debug::Win32HandleError();
        }

        file->size = (size_t)fileSize.QuadPart;

        if (file->platform->handle == INVALID_HANDLE_VALUE)
        {
            Debug::Win32HandleError();

            return false;
        }

        file->open = true;

        return true;
    }

    Bool32 FileSystem::Read (File * file, void * data, size_t bytesToRead, size_t offset)
    {
        DWORD bytesRead;
        BOOL result = ReadFile(
            file->platform->handle,
            data,
            (DWORD)bytesToRead,
            &bytesRead,
            NULL
        );

        if (!result) {
            Debug::Win32HandleError();

            return false;
        }

        if (bytesRead != bytesToRead)
        {
            Debug::Win32HandleError();

            assert(bytesRead == bytesToRead);

            return false;
        }

        return true;
    }

    Bool32 FileSystem::Write (File * file, void * data, size_t numberOfBytes)
    {
        return true;
    }

    Bool32 FileSystem::Delete (char * filename)
    {
        return true;
    }

    Bool32 FileSystem::Seek (File * file, Int64 position)
    {
        return true;
    }

    Bool32 FileSystem::Close (File * file)
    {
        if (file->platform->handle == INVALID_HANDLE_VALUE)
        {
            Debug::OutputString("Tried to close an invalid file handle.");

            assert(0);

            return false;
        }

        auto result = CloseHandle(file->platform->handle);

        if (!result)
        {
            Debug::Win32HandleError();

            assert(0);

            return false;
        }

        file->platform->handle = INVALID_HANDLE_VALUE;
        file->open = false;
        file->size = 0;

        return true;
    }

    Int64 GetFileSize (char * filename)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            Debug::Win32HandleError();
        }

        LARGE_INTEGER fileSize;
        auto result = ::GetFileSizeEx(fileHandle, &fileSize);

        // If the function fails and lpFilSizeHigh is NULL
        // If the function fails and lpFileSizeHigh is non-NULL
        if (!result)
        {
            Debug::Win32HandleError();
        }

        return (Int64)fileSize.QuadPart;
    }

    void Read (char * filename, void * buffer, size_t size, size_t offset)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            // FILE_FLAG_RANDOM_ACCESS
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );

        if (size == 0)
        {
            LARGE_INTEGER fileSize;
            auto result = ::GetFileSizeEx(fileHandle, &fileSize);

            size = (size_t)fileSize.QuadPart;
        }

        if (offset != 0)
        {
            LARGE_INTEGER li;

            li.QuadPart = offset;

            li.LowPart = SetFilePointer(
                fileHandle,
                li.LowPart,
                &li.HighPart,
                FILE_BEGIN
            );

            if (li.LowPart == INVALID_SET_FILE_POINTER)
            {

            }
        }

        if (fileHandle == INVALID_HANDLE_VALUE) {
            Debug::Win32HandleError();
        }

        DWORD bytesRead;
        BOOL result = ReadFile(
            fileHandle,
            buffer,
            (DWORD)size,
            &bytesRead,
            NULL
        );

        assert(bytesRead == size);

        if (!result) {
            Debug::Win32HandleError();
        }

        // TODO (Emil): Should something more be done here?
        // Should the function return a boolean for success?
    }

    void Write (char * filename, void * buffer, size_t)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );
    }
}
