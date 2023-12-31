#pragma once

#include "Utilities/TileHelper.h"
#include "Tile.h"
#include "TileInfo.h"
#include "SharedContext/SharedContext.h"
#include "States/BaseState.h"
#include <unordered_map>


using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;

class EntityManagerOld;


class Map : public std::enable_shared_from_this<Map>
{
public:
	Map(SharedContext* context, BaseState* currentState);

	~Map();

	Tile* GetTile(unsigned int x, unsigned int y);

	TileInfo* GetDefaultTile() { return &m_DefaultTile; }

	float GetGravity() const { return m_Gravity; }
	void SetGravity(float value) { m_Gravity = value; }

	unsigned int GetTileSize() const { return TileSheet::TileSize; }

	const sf::Vector2u& GetMapSize() const { return m_MaxSize; }

	const sf::Vector2f& GetPlayerStart() const { return m_PlayerStart; }
	void SetPlayerStart(sf::Vector2f position) { m_PlayerStart = position; }

	void LoadMap(const std::string& path);

	void LoadNext();

	void Update(float deltaTime);

	void Draw();

	std::shared_ptr<EntityManagerOld>& GetEntityManager() { return m_EntityManager; }

	void AssociateWithContext(SharedContext* context);

	void AssociateWithCurrentContext();

private:
	/*
	*	Method for converting 2D coordinates to 1D ints.
	*/ 
	unsigned int ConvertCoords(unsigned int x, unsigned int y) { return (y * m_MaxSize.x) + x; }

	void LoadTiles(const std::string& path);

	/*
	*	Clear all tiles
	*/
	void PurgeEverything();

	/*
	*	Clear all of the actual tile types
	*/
	void PurgeTileSet();

	
	TileSet m_TileSet;
	TileMap m_Tiles;
	TileInfo m_DefaultTile;

	sf::Sprite m_Background;
	std::string m_BackgroundTextureName;

	sf::Vector2u m_MaxSize = {32, 32};
	sf::Vector2f m_PlayerStart;

	unsigned int m_TileCount = 0;
	unsigned int m_TileSetCount = 0;

	float m_Gravity = 1024.0f;

	std::string m_NextMap;
	bool m_LoadNextMap = false;

	BaseState* m_CurrentState;
	SharedContext* m_Context;
	std::shared_ptr<EntityManagerOld> m_EntityManager;
};
