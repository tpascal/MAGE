//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\cornell\cornell_scene.hpp"
#include "samples\sponza\sponza_scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture_factory.hpp"

#include "character_motor_script.hpp"
#include "mouse_look_script.hpp"
#include "editor_script.hpp"
#include "stats_script.hpp"
#include "switch_scene_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CornellScene::CornellScene()
		: Scene("cornell_scene") {}

	CornellScene::CornellScene(CornellScene&& scene) = default;

	CornellScene::~CornellScene() = default;

	void CornellScene::Load([[maybe_unused]] Engine& engine) {
		using namespace rendering;

		const auto& rendering_manager = engine.GetRenderingManager();
		const auto& display_config    = rendering_manager.GetDisplayConfiguration();
		auto& rendering_world         = rendering_manager.GetWorld();
		auto& rendering_factory       = rendering_manager.GetResourceManager();
		const auto display_resolution = display_config.GetDisplayResolution();

		//---------------------------------------------------------------------
		// Resources
		//---------------------------------------------------------------------
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);

		const auto cornell_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/cornell/cornell.obj", mesh_desc);
		const auto cube_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/cube/cube.obj", mesh_desc);
		const auto plane_model_desc 
			= rendering_factory.GetOrCreate< ModelDescriptor >(
				L"assets/models/plane/plane.obj", mesh_desc);
		const auto logo_texture = CreateMAGETexture(rendering_factory);

		//---------------------------------------------------------------------
		// Cameras
		//---------------------------------------------------------------------
		const auto camera = rendering_world.Create< PerspectiveCamera >();

		const auto camera_node = Create< Node >("Player");
		camera_node->Add(camera);
		camera_node->GetTransform().SetTranslationY(2.0f);

		//---------------------------------------------------------------------
		// Models
		//---------------------------------------------------------------------
		const auto cornell_box_node = Import(engine, *cornell_model_desc);
		const auto short_box_node   = Import(engine, *cube_model_desc);
		const auto tall_box_node    = Import(engine, *cube_model_desc);
		cornell_box_node->AddChild(short_box_node);
		cornell_box_node->AddChild(tall_box_node);

		cornell_box_node->SetName("Cornell Box");
		cornell_box_node->GetTransform().SetScale(10.0f, 10.0f, 10.0f);

		short_box_node->SetName("Short Box");
		short_box_node->GetTransform().SetTranslation(0.15f, -0.35f, -0.2f);
		short_box_node->GetTransform().SetRotationY(0.3f);
		short_box_node->GetTransform().SetScale(0.25f, 0.3f, 0.25f);

		tall_box_node->SetName("Tall Box");
		tall_box_node->GetTransform().SetTranslation(-0.15f, -0.2f, 0.0f);
		tall_box_node->GetTransform().SetRotationY(-0.35f);
		tall_box_node->GetTransform().SetScale(0.25f, 0.6f, 0.25f);
		
		//---------------------------------------------------------------------
		// Lights
		//---------------------------------------------------------------------
		const auto omni_light = rendering_world.Create< OmniLight >();
		omni_light->SetRange(50.0f);
		omni_light->SetPower(4.0f);
		omni_light->EnableShadows();

		const auto omni_light_node = Create< Node >("Omni Light");
		omni_light_node->Add(omni_light);
		cornell_box_node->AddChild(omni_light_node);
		omni_light_node->GetTransform().SetTranslationY(0.4f);
		
		//---------------------------------------------------------------------
		// Sprites
		//---------------------------------------------------------------------
		const auto logo = rendering_world.Create< SpriteImage >();

		logo->SetBaseColorTexture(logo_texture);
		logo->GetSpriteTransform().SetScale(0.25f, 0.25f);
		logo->GetSpriteTransform().SetTranslation(
			NormalizedToAbsolute(F32x2(0.90f, 0.88f),
								 static_cast< F32x2 >(display_resolution)));

		camera_node->Add(logo);

		const auto text = rendering_world.Create< SpriteText >();

		camera_node->Add(text);

		//---------------------------------------------------------------------
		// Scripts
		//---------------------------------------------------------------------
		Create< script::SwitchSceneScript< SponzaScene > >();
		Create< script::EditorScript >();

		camera_node->Add(Create< script::StatsScript >());
		camera_node->Add(Create< script::MouseLookScript >());
		camera_node->Add(Create< script::CharacterMotorScript >());
	}
}