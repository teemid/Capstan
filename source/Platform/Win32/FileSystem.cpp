#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Capstan/Globals.h"
#include "Capstan/Utils.h"

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/FileSystem.h"
#include "Capstan/Platform/Win32/Debug.h"


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
        FileSystem::fileList = (PlatformFileData *)gMemoryManager.Allocate(sizeof(PlatformFileData) * FileSystem::maxAsyncReads);
    }

    void FileSystem::ShutDown (void)
    {
        gMemoryManager.Free((void *)FileSystem::fileList);
    }

    internal DWORD inline GetAccessRights (Int32 mode)
    {
        // using Mode = FileSystem::Mode;

        DWORD accessRights = 0;
        if (mode & FileSystem::ReadFlag) { accessRights |= GENERIC_READ; }
        else if (mode & FileSystem::WriteFlag) { accessRights |= GENERIC_WRITE; }

        Assert(accessRights, "Failed to set access rights for file.\n");

        // Debug::Print("Access rights: %d\n", accessRights);

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

        // Debug::Print("File Attributes %d\n", fileAttributes);

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

        Assert((file->platform->handle != INVALID_HANDLE_VALUE), "Invalid file handle.\n");

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
    
        Assert((result != INVALID_FILE_SIZE), "Could not get file size for %s.\n", filename);
    
        file->size = (size_t)fileSize.QuadPart;

        Assert((file->platform->handle != INVALID_HANDLE_VALUE), "Invalid file handle.\n");

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

        Assert(result, "Could not read file.\n");
        Assert(bytesRead == bytesToRead, "Failed to read entire file.\n");

        return true;
    }

    Bool32 FileSystem::Write (File * file, void * data, size_t numberOfBytes)
    {
        return false;
    }

    Bool32 FileSystem::Delete (char * filename)
    {
        return false;
    }

    Bool32 FileSystem::Seek (File * file, Int64 position)
    {
        return false;
    }

    Bool32 FileSystem::Close (File * file)
    {
        Assert((file->platform->handle != INVALID_HANDLE_VALUE), "Tried to close an invalid file handle.\n");

        auto result = CloseHandle(file->platform->handle);

        Assert(result, "Failed to close a file handle.\n");

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

        Assert((fileHandle != INVALID_HANDLE_VALUE), "Invalid file handle.\n");

        LARGE_INTEGER fileSize;
        auto result = ::GetFileSizeEx(fileHandle, &fileSize);

        // If the function fails and lpFilSizeHigh is NULL
        // If the function fails and lpFileSizeHigh is non-NULL
        Assert(result, "Failed to get file size.\n");

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

        Assert((fileHandle != INVALID_HANDLE_VALUE), "Invalid file handle.\n");

        DWORD bytesRead;
        BOOL result = ReadFile(
            fileHandle,
            buffer,
            (DWORD)size,
            &bytesRead,
            NULL
        );

        Assert(result, "Failed to read the file.\n");
        Assert(bytesRead == size, "Failed to read the entire file.\n");

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
