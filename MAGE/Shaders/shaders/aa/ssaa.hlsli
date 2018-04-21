#ifndef MAGE_HEADER_SSAA
#define MAGE_HEADER_SSAA

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_INVERTED_Z_BUFFER                | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
struct InputTexturesSSAA {
	Texture2D< float4 > image;
	Texture2D< float3 > normal;
	Texture2D< float  > depth;
};

struct OutputTexturesSSAA {
	RWTexture2D< float4 > image;
	RWTexture2D< float3 > normal;
	RWTexture2D< float  > depth;
};

void ResolveSSAA(uint2 p_display, 
				 uint2 nb_samples, 
				 float weight,
				 InputTexturesSSAA input_textures,
				 OutputTexturesSSAA output_textures) {

	const uint2 p_ss_display = p_display * nb_samples;
	
	float4 ldr        = 0.0f;
	float3 normal_sum = 0.0f;
	#ifdef DISABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
	#else  // DISABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
	#endif // DISABLE_INVERTED_Z_BUFFER

	// Resolve the (super-sampled) radiance, normal and depth.
	for (uint i = 0u; i < nb_samples.x; ++i) {
		for (uint j = 0u; j < nb_samples.y; ++j) {

			const uint2 p_ss_display_ij = p_ss_display + uint2(i,j);
			
			const float4 hdr = input_textures.image[p_ss_display_ij];
			ldr += ToneMap_Max3(hdr, weight);
			
			normal_sum += input_textures.normal[p_ss_display_ij];
			
			#ifdef DISABLE_INVERTED_Z_BUFFER
			depth = min(depth, input_textures.depth[p_ss_display_ij]);
			#else  // DISABLE_INVERTED_Z_BUFFER
			depth = max(depth, input_textures.depth[p_ss_display_ij]);
			#endif // DISABLE_INVERTED_Z_BUFFER
		}
	}

	const float4 hdr    = InverseToneMap_Max3(ldr);
	const float3 normal = normalize(normal_sum);

	// Store the resolved radiance.
	output_textures.image[p_display]  = hdr;
	// Store the resolved normal.
	output_textures.normal[p_display] = normal;
	// Store the resolved depth.
	output_textures.depth[p_display]  = depth;
}

#endif // MAGE_HEADER_SSAA