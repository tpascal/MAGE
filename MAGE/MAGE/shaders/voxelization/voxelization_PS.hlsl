//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"

#define DISSABLE_DIFFUSE_BRDF
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	
	return 0.0f;
}