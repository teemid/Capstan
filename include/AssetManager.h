#ifndef CAPSTAN_RESOURCE_MANAGER_H
#define CAPSTAN_RESOURCE_MANAGER_H


#include "assets.h"
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
