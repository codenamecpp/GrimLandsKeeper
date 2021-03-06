#pragma once

// forwards
class DungeonBuilder;

// generic room class
class GenericRoom: public cxx::handled_object<GenericRoom>
{
    friend class RoomsManager;

public:
    // readonly
    RoomDefinition* mDefinition; // cannot be null
    RoomInstanceID mInstanceID; // instance unique identifier
    TilesList mRoomTiles;
    Rectangle mOccupationArea; // approximate size in tiles
    ePlayerID mOwnerID;

public:
    GenericRoom(RoomDefinition* definition, ePlayerID owner, RoomInstanceID uid);
    virtual ~GenericRoom();

    // move tiles and objects from other room to this room
    // @param sourceRoom: Donor
    // @param targetTiles: Target tiles to absorb
    void AbsorbRoom(GenericRoom* sourceRoom, const TilesList& targetTiles);
    void AbsorbRoom(GenericRoom* sourceRoom);

    // process single frame logic
    void UpdateFrame();

    // remove specific tiles from room, this will lead to reevaluation of remaining tiles
    void ReleaseTiles(const TilesList& terrainTiles);
    void ReleaseTiles();

    // expand room with new tiles which must not be owned by any room so far
    void EnlargeRoom(const TilesList& terrainTiles);

    // force construct geometries of all room tiles and wall sections
    void BuildTilesMesh();

    // construct geometries of all invalidated room tiles and wall sections
    void UpdateTilesMesh();

    // test whether room does own some tiles 
    bool HasTiles() const;

    // handle situation when adjacent solid tils is reinforced or destroyed, so room must reevaluate
    // its walls and add or demove objects
    // @param targetTile: Target tile
    void NeighbourTileChange(TerrainTile* targetTile);

protected:
    void AttachTiles(const TilesList& terrainTiles);
    void DetachTiles(const TilesList& terrainTiles);

    void ReevaluateOccupationArea();
    void ReevaluateInnerSquares();
    void ReevaluateWallSections();
    
    void ReleaseWallSections();
    void DetachFromWall(TerrainTile* roomTile);

    static void ScanWallSection(TerrainTile* terrainTile, eTileFace faceId, WallSection* section);
    static void ScanWallSection(TerrainTile* terrainTile, eDirection faceDirection, WallSection* section);
    static void ScanWallSectionImpl(TerrainTile* terrainTile, WallSection* section);

    void FinalizeWallSection(WallSection* section);

    // overridables

    // each time room gets modified it must be reconfigured
    // for example, tiles added or removed, wall sections updated
    virtual void Reconfigure() {}

protected:
    // walls construction
    void ConstructWalls(DungeonBuilder& builder, bool forceConstructAll);

    // construct floor tiles mesh
    void ConstructFloorTiles(DungeonBuilder& builder, const TilesList& terrainTiles);

    // tile mesh construction procs
    void ConstructTiles_DoubleQuad      (DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_5x5Rotated      (DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_3x3             (DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_Quad            (DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_Normal          (DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_HeroGateFrontEnd(DungeonBuilder& builder, const TilesList& terrainTiles);
    void ConstructTiles_HeroGate3x1     (DungeonBuilder& builder, const TilesList& terrainTiles);

protected:
    std::vector<WallSection*> mWallSections;
    TilesList mInnerTiles;
};