//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"
#include "shader\cso\transform_VS.hpp"
#include "shader\cso\diffuse_PS.hpp"
#include "shader\cso\lambertian_PS.hpp"
#include "shader\cso\phong_PS.hpp"
#include "shader\cso\blinn_phong_PS.hpp"
#include "shader\cso\modified_blinn_phong_PS.hpp"
#include "shader\cso\sprite_VS.hpp"
#include "shader\cso\sprite_PS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CompiledVertexShader CreateCompiledTransformVertexShader() {
		return CompiledVertexShader(MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
	}

	const CompiledPixelShader CreateCompiledDiffusePixelShader() {
		return CompiledPixelShader(MAGE_GUID_DIFFUSE_PS, g_diffuse_ps, sizeof(g_diffuse_ps));
	}

	const CompiledPixelShader CreateCompiledLambertianPixelShader() {
		return CompiledPixelShader(MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps));
	}

	const CompiledPixelShader CreateCompiledPhongPixelShader() {
		return CompiledPixelShader(MAGE_GUID_PHONG_PS, g_phong_ps, sizeof(g_phong_ps));
	}

	const CompiledPixelShader CreateCompiledBlinnPhongPixelShader() {
		return CompiledPixelShader(MAGE_GUID_BLINN_PHONG_PS, g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
	}

	const CompiledPixelShader CreateCompiledModifiedBlinnPhongPixelShader() {
		return CompiledPixelShader(MAGE_GUID_MODIFIED_BLINN_PHONG_PS, g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
	}

	const CompiledVertexShader CreateCompiledSpriteVertexShader() {
		return CompiledVertexShader(MAGE_GUID_SPRITE_VS, g_sprite_vs, sizeof(g_sprite_vs));
	}

	const CompiledPixelShader CreateCompiledSpritePixelShader() {
		return CompiledPixelShader(MAGE_GUID_SPRITE_PS, g_sprite_ps, sizeof(g_sprite_ps));
	}
}