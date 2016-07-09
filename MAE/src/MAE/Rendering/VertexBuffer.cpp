#include <MAE/Rendering/VertexBufferImpl.h>

#include <exception>

VertexBufferImpl::VertexBufferImpl(uint length, LPDIRECT3DDEVICE9 device) {
	if (FAILED(device->CreateVertexBuffer(length, 0, 0, D3DPOOL_DEFAULT, &vb, 0)))
		throw new std::exception("Failed to allocate VertexBuffer");
}

VertexBufferImpl::~VertexBufferImpl() {
	vb->Release();
}

void VertexBufferImpl::release() {
	::delete this;
}

void* VertexBufferImpl::map(uint offset, uint size, uint flags) {
	void* ptr;

	if (FAILED(vb->Lock(offset, size, &ptr, flags)))
		throw new std::exception("Failed to map VertexBuffer");

	return ptr;
}

void VertexBufferImpl::unmap() {
	vb->Unlock();
}

void VertexBufferImpl::upload(const void* data, uint offset, uint size) {
	memcpy(map(offset, size, 0), data, size);
	unmap();
}