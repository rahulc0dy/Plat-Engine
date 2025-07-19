#include "Engine.hpp"
#include "ECS/Scene.hpp"
#include "ECS/Transform.hpp"
#include "ECS/Animation.hpp"
#include "ECS/AssetManager.hpp"
#include "ECS/Audio.hpp"
#include "ECS/Camera.hpp"
#include "ECS/Collider.hpp"
#include "ECS/Event.hpp"
#include "ECS/Input.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/PhysicsBody.hpp"
#include "ECS/Script.hpp"
#include "ECS/Velocity.hpp"
#include "ECS/Name.hpp"

class Editor {
public:
	Editor();
	~Editor();

	void run();

private:
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Font m_font;

	Scene m_scene;
	Entity selectedEntity = Scene::INVALID_ENTITY;
	bool m_gridEnabled = true;
	float m_gridSize = 32.0f;

	void drawMenuBar();
	void drawEntityList();
	void drawInspector();
	void drawToolbar();
	void drawGridSettings();
	void drawScenesWidget();
};