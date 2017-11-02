//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ToneMapperPass *ToneMapperPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetToneMapperPass();
	}

	ToneMapperPass::ToneMapperPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateToneMapperCS()) {}

	ToneMapperPass::ToneMapperPass(ToneMapperPass &&render_pass) = default;

	ToneMapperPass::~ToneMapperPass() = default;

	void ToneMapperPass::BindFixedState() const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);
	}

	void ToneMapperPass::Render(const Viewport &viewport) {

		// Dispatch.
		const U32 nb_groups_x
			= static_cast< U32 >(ceil(viewport.GetWidth()
				/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y
			= static_cast< U32 >(ceil(viewport.GetHeight()
				/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}