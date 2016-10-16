#ifndef CAPSTAN_ASSET_MANAGER_H
#define CAPSTAN_ASSET_MANAGER_H

#include "Capstan/Types.h"


namespace Capstan
{
    #define MAX_ASSET_COUNT 200

    typedef UInt32 AssetId;

    enum class AssetType : UInt32 {
        BITMAP,
        SOUND,
        MUSIC,
        SHADER
    };

    enum class AssetStatus : UInt32 {
        UNLOADED,
        RETREIVING,
        LOADED
    };

    struct Asset
    {
        void * asset;
        AssetId id;
        AssetType type;
        AssetStatus status;
    };

    struct ShaderAsset
    {
        char * source;
        Int64 size;
    };

    enum class PixelLayout {
        RGB24,
        BGR24,
        RGBA32,
        BGRA32
    };

    struct ImageAsset
    {
        Int32 width;
        Int32 height;
        PixelLayout layout;
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
        ImageAsset LoadTexture (char * filename);
        void Unload (Asset asset);
    private:
        Asset assets[MAX_ASSET_COUNT];
        UInt32 current;
    };
}


#endif
