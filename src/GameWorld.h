#pragma once

#include "GameMap.h"
#include "DungeonBuilder.h"
#include "TerrainTilesCursor.h"

// game world state
class GameWorld: public cxx::noncopyable
{
public:
    // readonly
    ScenarioData mScenarioData;
    GameMap mMapData;
    DungeonBuilder mDungeonBuilder;
    TerrainTilesCursor mTerrainCursor;

public:
    // setup game world internal resources
    bool Initialize();
    void Deinit();

    // load world data, level map, setup players, build rooms etc
    // @param scenarioName: Scenario name
    bool LoadScenario(const std::string& scenarioName);
    void EnterWorld();
    void ClearWorld();

    // process single frame logic
    void UpdateFrame();

    // set or clear tagged state of terrain tiles
    // @param tilesArea: Tiles in specific area
    void TagTerrain(const Rectangle& tilesArea);
    void UnTagTerrain(const Rectangle& tilesArea);

    // build room within specified area, will merge contiguous rooms
    // @param ownerID: Owner player identifier
    // @param roomDefinition: Room class definition
    // @param tilesArea: Target area
    void ConstructRoom(ePlayerID ownerID, RoomDefinition* roomDefinition, const Rectangle& tilesArea);

    // sell rooms within specified area, will split rooms
    // @param ownerID: Initiator of sell operation
    // @param tilesRect: Target area
    void SellRooms(ePlayerID ownerID, const Rectangle& tilesRect);

    // test whether room is buildable on specific terrain spot
    // @param mapTile: Target tile
    // @param playerIdentifier: Owner
    // @param roomDefinition: Room definition
    bool CanPlaceRoomOnLocation(TerrainTile* terrainTile, ePlayerID playerIdentifier, RoomDefinition* roomDefinition) const;

    // get terrain definition by type name or type identifier
    // @param typeName: Type name
    // @param typeID: Type identifier
    TerrainDefinition* GetTerrainDefinition(const std::string& typeName);
    TerrainDefinition* GetTerrainDefinition(TerrainTypeID typeID);

    // well known terrain types
    TerrainDefinition* GetLavaTerrain();
    TerrainDefinition* GetWaterTerrain();
    TerrainDefinition* GetPlayerColouredPathTerrain();
    TerrainDefinition* GetPlayerColouredWallTerrain();
    TerrainDefinition* GetFogOfWarTerrain();

    // get game object definition by type name or type identifier
    // @param typeName: Type name
    // @param typeID: Type identifier
    GameObjectDefinition* GetGameObjectDefinition(const std::string& typeName);
    GameObjectDefinition* GetGameObjectDefinition(GameObjectTypeID typeID);

    // get room definition by type name or type identifier
    // @param typeName: Type name
    // @param typeID: Type identifier
    RoomDefinition* GetRoomDefinition(const std::string& typeName);
    RoomDefinition* GetRoomDefinition(RoomTypeID typeID);

    // get creature definition by type name or type identifier
    // @param typeName: Type name
    // @param typeID: Type identifier
    CreatureDefinition* GetCreatureDefinition(const std::string& typeName);
    CreatureDefinition* GetCreatureDefinition(CreatureTypeID typeID);

    // get room definition by corresponding terrain identifier
    RoomDefinition* GetRoomDefinitionByTerrain(TerrainDefinition* terrainDefinition);
    RoomDefinition* GetRoomDefinitionByTerrain(TerrainTypeID typeID);

    // test whether terrain is room
    bool IsRoomTypeTerrain(TerrainDefinition* terrainDefinition) const;
    bool IsRoomTypeTerrain(TerrainTypeID typeID) const;

private:
    template<typename TEnumProc>
    void EnumAdjacentRooms(const TilesList& tilesToScan, ePlayerID ownerID, TEnumProc enumProc);

    void SetupMapData(unsigned int seed);
    void ConstructStartupRooms();
    void ConstructStartupRoom(TerrainTile* initialTile);
};

extern GameWorld gGameWorld;