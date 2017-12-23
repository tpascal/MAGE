//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\font\font_reader.hpp"
#include "loaders\font\font_tokens.hpp"
#include "texture\texture_utils.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	SpriteFontReader::SpriteFontReader(ID3D11Device5 *device, 
		SpriteFontOutput &output, const SpriteFontDescriptor &desc)
		: BigEndianBinaryReader(), 
		m_device(device), 
		m_output(output), 
		m_desc(desc) {

		Assert(device);
	}

	SpriteFontReader::SpriteFontReader(
		SpriteFontReader &&reader) noexcept = default;

	SpriteFontReader::~SpriteFontReader() = default;

	void SpriteFontReader::ReadData() {
	
		// Read the header.
		{
			const bool result = IsHeaderValid();
			ThrowIfFailed(result,
				"%ls: invalid sprite font header.", GetFilename().c_str());
		}

		// Read glyphs.
		const U32 glyph_count   = Read< U32 >();
		const Glyph *glyph_data = ReadArray< Glyph >(glyph_count);
		m_output.m_glyphs.assign(glyph_data, glyph_data + glyph_count);

		// Read font properties.
		m_output.m_line_spacing = Read< F32 >();
		
		// Read default character.
		m_output.m_default_character = static_cast< wchar_t >(Read< U32 >());

		// Read texture.
		ReadTexture();
	}

	bool SpriteFontReader::IsHeaderValid() {
		const char *magic = g_font_token_magic;
		
		while (*magic != L'\0') {
			if (Read< U8 >() != *magic) {
				return false;
			}
			++magic;
		}
		
		return true;
	}

	void SpriteFontReader::ReadTexture() {
		// Read texture data.
		const U32 texture_width     = Read< U32 >();
		const U32 texture_height    = Read< U32 >();
		const DXGI_FORMAT format    = Read< DXGI_FORMAT >();
		const DXGI_FORMAT texture_format = m_desc.ForceSRGB() ? 
			                               ConvertToSRGB(format) : format;
		const U32 texture_stride    = Read< U32 >();
		const U32 texture_rows      = Read< U32 >();
		const U8 *texture_data      = ReadArray< U8 >(texture_stride * texture_rows);

		// Create the texture descriptor.
		CD3D11_TEXTURE2D_DESC texture_desc(
			texture_format, texture_width, texture_height, 
			1u, 1u, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_IMMUTABLE);
		
		// Create the texture data.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem     = texture_data;
		init_data.SysMemPitch = texture_stride;
		
		// Create the texture resource.
		ComPtr< ID3D11Texture2D > texture;
		{
			const HRESULT result = m_device->CreateTexture2D(
				&texture_desc, &init_data, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "%ls: Texture creation failed: %08X.",
				GetFilename().c_str(), result);
		}

		// Create the SRV descriptor.
		CD3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc(
			D3D11_SRV_DIMENSION_TEXTURE2D, texture_format);
		
		// Create the SRV.
		{
			const HRESULT result = m_device->CreateShaderResourceView(
				texture.Get(), &shader_resource_view_desc,
				m_output.m_texture_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "%ls: SRV creation failed: %08X.",
				GetFilename().c_str(), result);
		}
	}
}