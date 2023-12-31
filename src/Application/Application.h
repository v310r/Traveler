#pragma once

#include "Window/Window.h"
#include <iostream>
#include "States/StateManager.h"
#include "Entities/EntityManagerOld.h"
#include "ResourceManagement/TextureManager.h"
#include <memory>


class Application
{
public:
	Application();

	~Application();

	void HandleInput();

	void Update();

	void Render();

	std::shared_ptr<Window>& GetWindow();

	void PostUpdate();

private:


	sf::Clock m_clock;

	SharedContext m_SharedContext;

	std::shared_ptr<TextureManager> m_TextureManager;
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<StateManager> m_StateManager;
	std::shared_ptr<EntityManagerOld> m_EntityManager;
};
