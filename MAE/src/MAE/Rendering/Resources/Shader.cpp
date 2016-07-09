#include <MAE/Rendering/Resources/Shader.h>
#include <MAE/MainImpl.h>
#include <MAE/Rendering/Resources/ShaderImpl.h>

#include <cassert>

ShaderImpl::~ShaderImpl() {
	main->removeShader(this);

	if (vtable != 0)
		vtable->Release();

	if (ptable != 0)
		ptable->Release();

	if (vshd != 0)
		vshd->Release();

	if (pshd != 0)
		pshd->Release();
}

void ShaderImpl::release() {
	::delete this;
}

void ShaderImpl::compileD3D9ASM(const std::string& vert, const std::string& pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	if (FAILED(D3DXAssembleShader(vert.c_str(), vert.length(), NULL, NULL, 0, &code, &err))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		throw new std::exception(error.c_str());
	}

	result = main->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &vshd);
	code->Release();

	if (FAILED(result))
		throw new std::exception("Failed to create Vertex Shader");

	if (FAILED(D3DXAssembleShader(pixel.c_str(), pixel.length(), NULL, NULL, 0, &code, &err))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		vshd->Release();
		vshd = 0;

		throw new std::exception(error.c_str());
	}

	result = main->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &pshd);
	code->Release();

	if (FAILED(result)) {
		vshd->Release();
		vshd = 0;

		throw new std::exception("Failed to create Pixel Shader");
	}
}

void ShaderImpl::compileD3D9(const std::string& vert, const std::string& pixel) {
	LPD3DXBUFFER code;
	LPD3DXBUFFER err;

	HRESULT result;

	if (FAILED(D3DXCompileShader(vert.c_str(), vert.length(), NULL, NULL, "main", D3DXGetVertexShaderProfile(main->d3ddev), 0, &code, &err, &vtable))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		throw new std::exception(error.c_str());
	}

	result = main->d3ddev->CreateVertexShader((DWORD*) code->GetBufferPointer(), &vshd);
	code->Release();

	if (FAILED(result))
		throw new std::exception("Failed to create Vertex Shader");

	if (FAILED(D3DXCompileShader(pixel.c_str(), pixel.length(), NULL, NULL, "main", D3DXGetPixelShaderProfile(main->d3ddev), 0, &code, &err, &ptable))) {
		std::string error = (char*) err->GetBufferPointer();
		err->Release();

		vshd->Release();
		vshd = 0;

		throw new std::exception(error.c_str());
	}

	result = main->d3ddev->CreatePixelShader((DWORD*) code->GetBufferPointer(), &pshd);
	code->Release();

	if (FAILED(result)) {
		vshd->Release();
		vshd = 0;

		throw new std::exception("Failed to create Pixel Shader");
	}
}

uint ShaderImpl::find(const std::string& c) {
	Handles h = {
		vtable->GetConstantByName(0, c.c_str()),
		ptable->GetConstantByName(0, c.c_str())
	};
	
	auto it = std::find(handles.begin(), handles.end(), h);

	if (it == handles.end()) {
		auto ind = handles.size();
		handles.push_back(h);
		return ind;
	}

	return it - handles.begin();
}

void ShaderImpl::setSampler(uint c, class Texture* sampler) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		main->setTexture(vtable->GetSamplerIndex(handles[c].vshd), sampler);

	if (handles[c].pshd)
		main->setTexture(vtable->GetSamplerIndex(handles[c].pshd), sampler);
}

void ShaderImpl::setFloat(uint c, float f) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloat(main->d3ddev, handles[c].vshd, f);

	if (handles[c].pshd)
		vtable->SetFloat(main->d3ddev, handles[c].pshd, f);
}

void ShaderImpl::setVec2(uint c, const vec2& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setVec3(uint c, const vec3& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setVec4(uint c, const vec4& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].vshd, v.data, v.components);

	if (handles[c].pshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].pshd, v.data, v.components);
}

void ShaderImpl::setMat3(uint c, const mat3& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].vshd, v.data, v.size * v.size);

	if (handles[c].pshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].pshd, v.data, v.size * v.size);
}

void ShaderImpl::setMat4(uint c, const mat4& v) {
	assert(("Invalid constant index", c < handles.size()));

	if (handles[c].vshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].vshd, v.data, v.size * v.size);

	if (handles[c].pshd)
		vtable->SetFloatArray(main->d3ddev, handles[c].pshd, v.data, v.size * v.size);
}