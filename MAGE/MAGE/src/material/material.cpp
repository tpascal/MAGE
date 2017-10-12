#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Material::Material(const string &name)
		: m_name(name), 
		m_light_interaction(true), 
		m_transparent(false), 
		m_base_color(RGBASpectrum(1.0f)),
		m_base_color_texture(CreateWhiteTexture()),
		m_roughness(0.5f), m_metalness(0.0f),
		m_material_texture(CreateWhiteTexture()),
		m_normal_texture() {}
}