#pragma once

// frequently used tile rotations
// 0: -90 degrees
// 1: +90 degrees
// 2: -180 degrees
// 3: -120 degrees
// 4: +120 degress
extern const glm::mat3 g_TileRotations[5];

// subtile piece translations, quads
// 0: TOP-LEFT (NW)
// 1: TOP-RIGHT (NE)
// 2: BOTTOM-RIGHT (SE)
// 3: BOTTOM-LEFT (SW)
extern const glm::vec3 g_SubTileTranslations[4];

// tile face geometry
struct TileMesh
{
public:
    MeshMaterial mMaterial;

    std::vector<glm::ivec3> mTriangles;
    std::vector<Vertex3D_Terrain> mVertices;
};

// tile face data
struct TileFaceData 
{
public:
    std::vector<TileMesh> mMeshArray;

    // specified if tile face is part of the room
    // only defined for sides N, E, S, W 
    WallSection* mWallSection = nullptr;
};

// gamemap block data
class TerrainTile
{
public:
    TerrainTile();

    // reset mesh geometries for specific tile face
    // @param faceid: Face index
    void ClearTileMesh(eTileFace faceid);
    void ClearTileMesh();

    // mark tile mesh invalidated
    void InvalidateTileMesh();
    void InvalidateNeighbourTilesMesh();

    // apply new terrain type (base or room) to tile
    void SetTerrain(TerrainDefinition* terrainDefinition);

    // mark tile tagged
    void SetTagged(bool isTagged);

    // get current terrain type for tile
    inline TerrainDefinition* GetTerrain() const { return mRoomTerrain ? mRoomTerrain : mBaseTerrain; }
    inline TerrainDefinition* GetBaseTerrain() const { return mBaseTerrain; }

public:
    Point mTileLocation; // logical tile location 2D

    TerrainDefinition* mBaseTerrain = nullptr; // used to determine base terrain type, cannot be null
    TerrainDefinition* mRoomTerrain = nullptr; // overrides base terrain with room specific terrain, optional

    ePlayerID mOwnerID = ePlayerID_Null; // neutral maybe ?

    GenericRoom* mBuiltRoom = nullptr; // room that built on tile
    TileFaceData mFaces[eTileFace_COUNT];
    TerrainTile* mNeighbours[eDirection_COUNT];

    unsigned int mRandomValue = 0; // effects on visuals only
    unsigned int mFloodFillCounter = 0; // increments on each flood fill operation

    // current state flags
    bool mIsTagged;
    bool mIsRoomInnerTile; // tile is center of 3x3 square of room, flag is valid only if tile is a part of room
    bool mIsRoomEntrance; // flag is valid only if tile is a part of room

    bool mIsMeshInvalidated; // tile mesh is dirty and should be regenerated
};