#include "TileInfo.h"

#include "SharedContext/SharedContext.h"
#include "ResourceManagement/TextureManager.h"
#include <SFML/Graphics/Rect.hpp>
#include "Utilities/TileHelper.h"


TileInfo::TileInfo(SharedContext* context, const std::string& textureName, TileID id) : Context(context)
{
	TextureName = textureName;
	std::shared_ptr<TextureManager> textureManager = Context->GetTextureManager();
	if (TextureName.empty())
	{
		ID = id;
		return;
	}

	if (!textureManager->RequireResource(textureName))
	{
		return;
	}

	TextureName = textureName;
	ID = id;
	if (const sf::Texture* const texture = textureManager->GetResource(TextureName))
	{
		Sprite.setTexture(*texture);
	}

	const int LeftX = ID % (ETileSheet::Width / ETileSheet::TileSize) * ETileSheet::TileSize;
	const int LeftY = ID / (ETileSheet::Height / ETileSheet::TileSize) * ETileSheet::TileSize;
	const int SizeX = ETileSheet::TileSize;
	const int SizeY = ETileSheet::TileSize;
	const sf::IntRect tileBoundaries(LeftX, LeftY, SizeX, SizeY);
	Sprite.setTextureRect(tileBoundaries);
}

TileInfo::~TileInfo()
{
	if (TextureName.empty())
	{
		return;
	}

	if (std::shared_ptr<TextureManager> textureManager = Context->GetTextureManager())
	{
		textureManager->ReleaseResource(TextureName);
	}
	
}
