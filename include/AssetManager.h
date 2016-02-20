#ifndef CAPSTAN_RESOURCE_MANAGER_H
#define CAPSTAN_RESOURCE_MANAGER_H


#include "types.h"


namespace Capstan
{
    #define MAX_ASSET_COUNT 100

    typedef UInt32 AssetId;

    enum class AssetType {
        BITMAP,
        SOUND,
        MUSIC,
        SHADER
    };


    struct Asset
    {
        AssetId id;
        AssetType type;
        void * asset;
    };

    struct ShaderAsset
    {
        char * source;
        Int64 size;
    };

    struct BitmapAsset
    {
        Int32 width;
        Int32 height;
        void * data;
    };

    class AssetManager
    {
    public:
        AssetManager ();
        ~AssetManager ();

        void StartUp (size_t size);
        void ShutDown (void);

        void LoadResource (char * filename);
        ShaderAsset LoadShader (char * filename);
        void Unload (Asset asset);
    private:
        Asset assets[MAX_ASSET_COUNT];
        UInt32 current;
    };
}


#endif
