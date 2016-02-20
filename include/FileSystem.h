#ifndef CAPSTAN_FILESYSTEM_H
#define CAPSTAN_FILESYSTEM_H


#include "types.h"


namespace Capstan
{
    class FileSystem
    {
    public:
        FileSystem (void);
        ~FileSystem (void);

        void StartUp (void);
        void ShutDown (void);

        struct File
        {
            Bool32 open;
            size_t size;
            struct PlatformFileData * platform;
        };

        enum Mode
        {
            InvalidFlag      = 0,
            ReadFlag         = 1 << 0,
            WriteFlag        = 1 << 1,
            SequentialFlag   = 1 << 2,
            RandomAccessFlag = 1 << 3
        };

        static Bool32 Create (char * filename, File * file, Int32 mode = WriteFlag);
        static Bool32 Open (char * filename, File * file, Int32 mode = ReadFlag | SequentialFlag);
        static Bool32 Read (File * file, void * data, size_t bytesToRead = 0, size_t offset = 0);
        static Bool32 Write (File * file, void * data, size_t numberOfBytes);
        static Bool32 Delete (char * filename);
        // Int64 might not be necessary, atleast on Windows.
        // Check if max file size is 4 GB and if Int32 is enough?
        static Bool32 Seek (File * file, Int64 position);
        static Bool32 Close (File * file);
    private:
        static Int32 maxAsyncReads;
        static PlatformFileData * fileList;
    };

    Int64 GetFileSize (char * filename);
    void Read (char * filename, void * buffer, size_t size = 0, size_t offset = 0);
    void Write (char * filename, void * buffer, size_t size);
}


#endif
