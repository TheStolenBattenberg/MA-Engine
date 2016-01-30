#pragma once

#include "Scene.h"

#include <list>

class SceneImpl: public Scene {
public:
	SceneImpl(class MainImpl* main): main(main) { };
	~SceneImpl();

	uint release();

	ErrorCode createEntity(class Entity*& entity);

	void removeEntity(class Entity* entity);

private:
	class MainImpl* main;

	std::list<class EntityImpl*> entities;
};
