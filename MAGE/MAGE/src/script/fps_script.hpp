#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class FPSScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		FPSScript(SharedPtr< SpriteText > text)
			: BehaviorScript(), m_spf(0.0), m_nb_frames(0), m_text(text) {}
		FPSScript(const FPSScript &script) = delete;
		FPSScript(FPSScript &&script) = default;
		virtual ~FPSScript() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		FPSScript &operator=(const FPSScript &script) = delete;
		FPSScript &operator=(FPSScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double elapsed_time, const Scene &scene) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		double m_spf;
		uint32_t m_nb_frames;
		SharedPtr< SpriteText > m_text;
	};
}