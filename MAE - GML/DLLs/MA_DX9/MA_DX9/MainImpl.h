#pragma once

#include "Main.h"

#include <list>

class MainImpl: public Main
{
public:
	MainImpl(LPDIRECT3DDEVICE9 d3ddev);
	~MainImpl();

	uint release();

	ErrorCode surfaceCreate(class Surface*& surf);
	ErrorCode surfaceExists(const class Surface* surf, bool& exists);
	void surfaceRemove(const class Surface* surf);

	ErrorCode textureCreate(class Texture*& tex);
	ErrorCode textureExists(const class Texture* tex, bool& exists);
	void textureRemove(const class Texture* tex);

	ErrorCode setTexture(uint stage, class Texture* tex);
	ErrorCode resetTexture(uint stage);

	ErrorCode setError(ErrorCode code);
	ErrorCode getError();

private:
	ErrorCode errCode;
	std::list<class SurfaceImpl*> surfaces;
	std::list<class TextureImpl*> textures;
};