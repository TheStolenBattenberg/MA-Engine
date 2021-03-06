#pragma once

#include <MAE/Core/Deletable.h>
#include <MAE/Core/Types.h>
#include <string>

class Renderer: public Deletable {
public:
	enum {
		IndexBuffer16 = 0,
		IndexBuffer32 = 1
	};

	enum {
		MipMapsNone     = 0,
		MipMapsGenerate = 1,
		MipMapsFromFile = 2
	};

	enum {
		PrimitveTypePointList     = 0,
		PrimitveTypeLineList      = 1,
		PrimitveTypeLineStrip     = 2,
		PrimitveTypeTriangleList  = 3,
		PrimitveTypeTriangleStrip = 4,
		PrimitveTypeTriangleFan   = 5
	};

	enum {
		DataEnd  = 0,
		DataVB   = 1,
		DataElem = 2
	};

	virtual ~Renderer() { }

	inline class Shader* createShader(const std::string& vshd, const std::string& pshd) {
		return createShader(vshd.c_str(), pshd.c_str());
	}

	inline class Texture* createTextureFromFile(const std::string& file, uint mipmaps) {
		return createTextureFromFile(file.c_str(), mipmaps);
	}

	virtual class IndexBuffer* createIndexBuffer(uint length, uint format, const void* data = nullptr) = 0;
	virtual class Shader* createShader(const char* vshd, const char* pshd) = 0;
	virtual class Texture* createTextureFromFile(const char* file, uint mipmaps) = 0;
	virtual class Texture* createTextureFromFileInMemory(const void* data, uint length, uint mipmaps) = 0;
	virtual class VertexBuffer* createVertexBuffer(uint length, const void* data = nullptr) = 0;
	virtual class VertexData* createVertexData() = 0;
	virtual class VertexData* copyVertexData(class VertexData* vd) = 0;
	virtual void draw(class VertexData* vd, uint type, uint index, uint count) = 0;
	virtual void drawIndexed(class VertexData* vd, uint type, uint count) = 0;
	virtual void setShader(class Shader* shd) = 0;
	virtual void setTexture(uint stage, class Texture* tex) = 0;
};
