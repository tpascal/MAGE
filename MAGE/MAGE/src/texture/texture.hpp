#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Texture : public FileResource {

	public:

		Texture(ComPtr< ID3D11Device2 > device, const wstring &fname);
		virtual ~Texture() = default;

		ComPtr< ID3D11ShaderResourceView > GetTextureResourceView() const {
			return m_texture_resource_view;
		}

	private:

		Texture(const Texture &texture) = delete;
		Texture(Texture &&texture) = delete;
		Texture &operator=(const Texture &texture) = delete;
		Texture &operator=(Texture &&texture) = delete;

		ComPtr< ID3D11Device2 > m_device;
		ComPtr< ID3D11ShaderResourceView > m_texture_resource_view;
	};

	SharedPtr< Texture > CreateTexture(const wstring &fname);
}