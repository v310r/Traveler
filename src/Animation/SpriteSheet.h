#pragma once

#include "ResourceManagement/TextureManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SpriteDirection.h"

class AnimBase;

using Animations = std::unordered_map<std::string, AnimBase*>;


class SpriteSheet
{
public:
	SpriteSheet(const std::shared_ptr<TextureManager>& textureManager);
	~SpriteSheet();

	void CropSprite(const sf::IntRect& rect);

	bool LoadSheet(const std::string& path);
	void ReleaseSheet();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void SetSpriteSize(const sf::Vector2i& size);
	sf::Vector2i GetSpriteSize();

	void SetSpritePosition(const sf::Vector2f pos);

	void SetDirection(SpriteDirection dir);
	SpriteDirection GetDirection();

	AnimBase* GetCurrentAnimation() const { return m_CurrentAnimation; }
	bool SetAnimation(const std::string& name, bool bPlay = false, bool bLoop = false);

private:
	std::string m_TextureName;
	sf::Sprite m_Sprite;
	
	SpriteDirection m_SpriteDirection = SpriteDirection::Right;
	sf::Vector2i m_SpriteSize;
	sf::Vector2f m_SpriteScale = {1.0f , 1.0f};


	std::string m_AnimType;
	Animations m_Animations;
	AnimBase* m_CurrentAnimation = nullptr;

	// hardcoded value, which of course would be better to fix, making user to choose default anim through UI
	std::string m_DefaultAnimationName = "Idle";

	std::shared_ptr<TextureManager> m_TextureManager;
};
