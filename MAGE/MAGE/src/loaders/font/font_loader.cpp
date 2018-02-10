//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\font\font_loader.hpp"
#include "loaders\font\font_reader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	void ImportFontFromFile(const wstring &fname, 
		                    D3D11Device *device, 
		                    SpriteFontOutput &output, 
		                    const SpriteFontDescriptor &desc) {
		
		Assert(device);

		SpriteFontReader reader(device, output, desc);
		reader.ReadFromFile(fname);
	}
}