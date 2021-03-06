#pragma once

#include <d3d9.h>

#include <MAE/Core/Types.h>
#include <MAE/Core/Deletable.h>

class VertexBuffer: public Deletable {
public:
	enum {
		MapWrite = 0x01,
		MapRead  = 0x02
	};

	virtual ~VertexBuffer() { }

	template<typename T> T* map(uint offset, uint size, uint flags) {
		return (T*) map(offset, size, flags);
	}

	inline uint getSize() {
		return size;
	}

	virtual void* map(uint offset, uint size, uint flags) = 0;
	virtual void unmap() = 0;
	virtual void upload(const void* data, uint offset, uint size) = 0;

protected:
	uint size;
};
