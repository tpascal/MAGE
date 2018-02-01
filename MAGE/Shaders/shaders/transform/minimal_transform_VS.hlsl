//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view     : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view     : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform  : packoffset(c8);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	return Transform(input, g_object_to_view, g_view_to_projection, 
		             (float3x3)g_normal_to_view, g_texture_transform);
}
