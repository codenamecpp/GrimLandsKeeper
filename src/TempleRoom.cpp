#include "pch.h"
#include "TempleRoom.h"
#include "RenderScene.h"
#include "WaterLavaMesh.h"
#include "MapTile.h"

#define TEMPLE_WATER_POOL_TRANSLUCENCY  0.90f
#define TEMPLE_WATER_POOL_WAVE_WIDTH    4.0f
#define TEMPLE_WATER_POOL_WAVE_HEIGHT   0.08f
#define TEMPLE_WATER_POOL_WAVE_FREQ     16.2f
#define TEMPLE_WATER_POOL_WATERLINE     0.78f

TempleRoom::TempleRoom(RoomDefinition* definition, ePlayerID owner, RoomInstanceID uid)
    : GenericRoom(definition, owner, uid)
{
}

TempleRoom::~TempleRoom()
{
    // destroy temple water pool
    if (mTempleWaterPool)
    {
        gRenderScene.DestroyObject(mTempleWaterPool);
        mTempleWaterPool = nullptr;
    }
}

void TempleRoom::OnReconfigure()
{
    TilesArray waterTiles;
    ScanWaterPoolTiles(waterTiles);

    if (waterTiles.empty())
    {
        // destroy temple water pool
        if (mTempleWaterPool)
        {
            gRenderScene.DestroyObject(mTempleWaterPool);
            mTempleWaterPool = nullptr;
        }

        return;
    }

    // create new water pool mesh
    if (mTempleWaterPool == nullptr)
    {
        mTempleWaterPool = gRenderScene.CreateWaterMesh(waterTiles);
        // setup surface
        mTempleWaterPool->SetSurfaceParams(TEMPLE_WATER_POOL_TRANSLUCENCY, TEMPLE_WATER_POOL_WAVE_WIDTH, 
            TEMPLE_WATER_POOL_WAVE_HEIGHT, TEMPLE_WATER_POOL_WAVE_FREQ, TEMPLE_WATER_POOL_WATERLINE);
        gRenderScene.AttachObject(mTempleWaterPool);

        return;
    }

    if (!cxx::collections_equals(waterTiles, mTempleWaterPool->mWaterLavaTiles))
    {
        mTempleWaterPool->SetWaterLavaTiles(waterTiles);
    }
}

void TempleRoom::ScanWaterPoolTiles(TilesArray& poolTiles)
{
    poolTiles = mInnerTiles;
    for (MapTile* currentTile: mRoomTiles)
    {
        if (currentTile->mIsRoomInnerTile)
            continue;

        #define IS_INNER(direction) \
            currentTile->mNeighbours[direction]->mIsRoomInnerTile  

        for (eDirection dir: gDirectionsCCW)
        {
            if (IS_INNER(dir))
            {
                poolTiles.push_back(currentTile);
                break;
            }
        }
        #undef IS_INNER
    }
}